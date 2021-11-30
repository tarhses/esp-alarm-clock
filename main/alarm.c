#include <time.h>

#include <esp_log.h>
#include <esp_event.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

#include "alarm.h"
#include "config.h"

static void _Noreturn main_task(void* _);
static void _Noreturn button_task(void* _);
static void IRAM_ATTR button_isr(void* _);
static void _Noreturn switch_task(void* _);
static void IRAM_ATTR switch_isr(void* _);
static void alarm_changed_handler(void* _, esp_event_base_t _base, int32_t _id, void* data);
static bool update_clock(alarm_time_t* clock);
static void delay_alarm(alarm_time_t* alarm);
static bool is_button_pressed(void);
static bool is_switch_enabled(void);


static const char* TAG = "alarm";

ESP_EVENT_DEFINE_BASE(ALARM_EVENT);

static TaskHandle_t main_task_handle = NULL;
static TaskHandle_t button_task_handle = NULL;
static TaskHandle_t switch_task_handle = NULL;
static QueueHandle_t alarm_queue = NULL;
static QueueHandle_t button_queue = NULL;
static SemaphoreHandle_t switch_disabled_semaphore = NULL;

void init_alarm(void) {
    ESP_LOGI(TAG, "initializing alarm");

    gpio_config(&(gpio_config_t){
        .pin_bit_mask = BIT64(ALARM_PIN_BTN) | BIT64(ALARM_PIN_SWITCH),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
    });

    gpio_set_intr_type(ALARM_PIN_BTN, GPIO_INTR_NEGEDGE);
    gpio_isr_handler_add(ALARM_PIN_BTN, &button_isr, NULL);

    gpio_set_intr_type(ALARM_PIN_SWITCH, GPIO_INTR_ANYEDGE);
    gpio_isr_handler_add(ALARM_PIN_SWITCH, &switch_isr, NULL);

    alarm_queue = xQueueCreate(1, sizeof(alarm_time_t));
    button_queue = xQueueCreate(4, sizeof(bool));
    switch_disabled_semaphore = xSemaphoreCreateBinary();

    esp_event_handler_instance_register(ALARM_EVENT, ALARM_EVENT_CHANGED, &alarm_changed_handler, NULL, NULL);
}

void start_alarm(void) {
    xTaskCreate(&main_task, "alarm_main", 2048, NULL, 1, &main_task_handle);
    xTaskCreate(&button_task, "alarm_button", 2048, NULL, 1, &button_task_handle);
    xTaskCreate(&switch_task, "alarm_switch", 2048, NULL, 1, &switch_task_handle);
}

void main_task(void* _) {
    alarm_time_t clock = MIDNIGHT;
    alarm_time_t alarm = MIDNIGHT;
    bool delayed = false;

    if (is_switch_enabled()) {
        esp_event_post(ALARM_EVENT, ALARM_EVENT_ENABLED, NULL, 0, portMAX_DELAY);
    }

    for (;;) {
        bool long_press;
        if (xQueueReceive(button_queue, &long_press, 0) && delayed) {
            esp_event_post(ALARM_EVENT, ALARM_EVENT_STOPPED, NULL, 0, portMAX_DELAY);
            if (long_press) {
                esp_event_post(ALARM_EVENT, ALARM_EVENT_DELAYED, &alarm, sizeof(alarm_time_t), portMAX_DELAY);
            } else {
                delayed = false;
            }
        }

        if (xSemaphoreTake(switch_disabled_semaphore, 0)) {
            if (delayed) {
                delayed = false;
                esp_event_post(ALARM_EVENT, ALARM_EVENT_STOPPED, NULL, 0, portMAX_DELAY);
            }
        }

        if (!delayed) {
            xQueueReceive(alarm_queue, &alarm, 0);
        }

        if (update_clock(&clock)) {
            ESP_LOGI(TAG, "clock tick: %02d:%02d", clock.hours, clock.minutes);
            esp_event_post(ALARM_EVENT, ALARM_EVENT_TICK, &clock, sizeof(alarm_time_t), portMAX_DELAY);

            if (is_switch_enabled() && clock.hours == alarm.hours && clock.minutes == alarm.minutes) {
                ESP_LOGI(TAG, "alarm started");
                xQueueSend(alarm_queue, &alarm, 0); // store the current alarm for later
                delay_alarm(&alarm);
                delayed = true;
                esp_event_post(ALARM_EVENT, ALARM_EVENT_STARTED, NULL, 0, portMAX_DELAY);
            }
        }

        ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS((60 - clock.seconds) * 1000));
    }
}

void button_task(void* _) {
    for (;;) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(50));
        ulTaskNotifyTake(pdTRUE, 0);

        int i = 1;
        while (i < 20 && is_button_pressed()) {
            vTaskDelay(pdMS_TO_TICKS(50));
            i += 1;
        }

        if (i > 1) {
            bool long_press = (i == 20);
            ESP_LOGI(TAG, "button pressed (long_press=%d)", long_press);
            xQueueSend(button_queue, &long_press, portMAX_DELAY);
            xTaskNotifyGive(main_task_handle);
        }
    }
}

void button_isr(void* _) {
    if (button_task_handle != NULL) {
        vTaskNotifyGiveFromISR(button_task_handle, NULL);
    }
}

void switch_task(void* _) {
    bool enabled = is_switch_enabled();

    for (;;) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(50));
        ulTaskNotifyTake(pdTRUE, 0);

        if (enabled != is_switch_enabled()) {
            enabled = !enabled;
            if (enabled) {
                ESP_LOGI(TAG, "switch on");
                esp_event_post(ALARM_EVENT, ALARM_EVENT_ENABLED, NULL, 0, portMAX_DELAY);
            } else {
                ESP_LOGI(TAG, "switch off");
                xSemaphoreGive(switch_disabled_semaphore);
                xTaskNotifyGive(main_task_handle);
                esp_event_post(ALARM_EVENT, ALARM_EVENT_DISABLED, NULL, 0, portMAX_DELAY);
            }
        }
    }
}

void switch_isr(void* _) {
    if (switch_task_handle != NULL) {
        vTaskNotifyGiveFromISR(switch_task_handle, NULL);
    }
}

void alarm_changed_handler(void* _, esp_event_base_t _base, int32_t _id, void* data) {
    xQueueOverwrite(alarm_queue, data);
}

bool update_clock(alarm_time_t* clock) {
    struct tm now;
    time_t raw_now;
    bool updated;

    raw_now = time(NULL);
    localtime_r(&raw_now, &now);

    updated = (clock->hours != now.tm_hour || clock->minutes != now.tm_min);
    clock->hours = now.tm_hour;
    clock->minutes = now.tm_min;
    clock->seconds = now.tm_sec;

    return updated;
}

void delay_alarm(alarm_time_t* alarm) {
    alarm->minutes = (alarm->minutes + 5) % 60;
    if (alarm->minutes < 5) {
        alarm->hours = (alarm->hours + 1) % 24;
    }
}

bool is_button_pressed(void) {
    return !gpio_get_level(ALARM_PIN_BTN);
}

bool is_switch_enabled(void) {
    return !gpio_get_level(ALARM_PIN_SWITCH);
}
