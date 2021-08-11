#include <time.h>

#include <esp_log.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <freertos/queue.h>

#include "alarm.h"
#include "config.h"

static const char* TAG = "clock";

static SemaphoreHandle_t switch_semaphore = NULL;
static QueueHandle_t button_queue = NULL;
static QueueHandle_t alarm_queue = NULL;


ESP_EVENT_DEFINE_BASE(ALARM_EVENT);

static void _Noreturn clock_task(void* _);
static void alarm_changed_handler(void* _, esp_event_base_t _base, int32_t _id, void* data);
static void _Noreturn switch_task(void* _);
static void _Noreturn button_task(void* _);
static void IRAM_ATTR notify_isr(void* task_handle);
static void update_clock(alarm_time_t* clock);
static void delay_alarm(alarm_time_t* alarm);
static bool is_alarm_enabled(void);
static bool is_button_pressed(void);


void init_alarm(void) {
    ESP_LOGI(TAG, "initializing alarm");

    gpio_config(&(gpio_config_t) {
        .pin_bit_mask = BIT64(ALARM_PIN_BTN) | BIT64(ALARM_PIN_SWITCH),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
    });

    gpio_set_intr_type(ALARM_PIN_SWITCH, GPIO_INTR_ANYEDGE);
    gpio_set_intr_type(ALARM_PIN_BTN, GPIO_INTR_NEGEDGE);

    switch_semaphore = xSemaphoreCreateBinary();
    button_queue = xQueueCreate(1, sizeof(bool));
    alarm_queue = xQueueCreate(1, sizeof(alarm_time_t));

    esp_event_handler_instance_register(ALARM_EVENT, ALARM_EVENT_CHANGED, &alarm_changed_handler, NULL, NULL);
}

void start_alarm(void) {
    TaskHandle_t button_task_handle, switch_task_handle;

    xTaskCreate(&clock_task, "alarm_clock", 2048, NULL, 1, NULL);
    xTaskCreate(&button_task, "alarm_button", 2048, NULL, 1, &button_task_handle);
    xTaskCreate(&switch_task, "alarm_switch", 2048, NULL, 1, &switch_task_handle);

    gpio_isr_handler_add(ALARM_PIN_BTN, &notify_isr, button_task_handle);
    gpio_isr_handler_add(ALARM_PIN_SWITCH, &notify_isr, switch_task_handle);
}

void clock_task(void* _) {
    TickType_t wake_time = xTaskGetTickCount();
    alarm_time_t clock = MIDNIGHT;
    alarm_time_t alarm = MIDNIGHT;
    bool delayed = false;

    if (is_alarm_enabled()) {
        esp_event_post(ALARM_EVENT, ALARM_EVENT_ENABLED, NULL, 0, portMAX_DELAY);
    }

    for (;;) {
        update_clock(&clock);
        if (!delayed) {
            xQueueReceive(alarm_queue, &alarm, 0);
        }

        ESP_LOGI(TAG, "clock tick, it's %02d:%02d", clock.hours, clock.minutes);
        esp_event_post(ALARM_EVENT, ALARM_EVENT_TICK, &clock, sizeof(alarm_time_t), portMAX_DELAY);

        bool ringing = (is_alarm_enabled() && clock.hours == alarm.hours && clock.minutes == alarm.minutes);
        if (ringing) {
            ESP_LOGI(TAG, "alarm started");
            xQueueReset(button_queue);
            esp_event_post(ALARM_EVENT, ALARM_EVENT_STARTED, NULL, 0, portMAX_DELAY);
        }

        // Sleep until the next minute.
        // `adjtime` corrects 0.9375 seconds per minute (1/64th of a minute).
        // So we'll add 940 ms to be sure that the next tick will be on the next minute.
        vTaskDelayUntil(&wake_time, pdMS_TO_TICKS((60 - clock.seconds) * 1000 + 940));

        bool alarm_disabled = xSemaphoreTake(switch_semaphore, 0);
        bool alarm_stopped = false;
        bool button_pressed = xQueuePeek(button_queue, &alarm_stopped, 0);
        if (delayed || ringing) {
            if (alarm_disabled || alarm_stopped) {
                delayed = false;
                ESP_LOGI(TAG, "alarm stopped");
            } else if (ringing) {
                xQueueSend(alarm_queue, &alarm, 0);
                delay_alarm(&alarm);
                delayed = true;
                ESP_LOGI(TAG, "alarm delayed to %02d:%02d", alarm.hours, alarm.minutes);
                if (!button_pressed) {
                    xQueueOverwrite(button_queue, &alarm_stopped);
                    esp_event_post(ALARM_EVENT, ALARM_EVENT_DELAYED, NULL, 0, portMAX_DELAY);
                }
            }
        }
    }
}

void alarm_changed_handler(void* _, esp_event_base_t _base, int32_t _id, void* data) {
    xQueueOverwrite(alarm_queue, data);
}

void switch_task(void* _) {
    bool state = is_alarm_enabled();

    for (;;) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(50));
        ulTaskNotifyTake(pdTRUE, 0);

        if (state != is_alarm_enabled()) {
            state = !state;
            if (state) {
                ESP_LOGI(TAG, "alarm enabled");
                esp_event_post(ALARM_EVENT, ALARM_EVENT_ENABLED, NULL, 0, portMAX_DELAY);
            } else {
                ESP_LOGI(TAG, "alarm disabled");
                xSemaphoreGive(switch_semaphore);
                esp_event_post(ALARM_EVENT, ALARM_EVENT_DISABLED, NULL, 0, portMAX_DELAY);
            }
        }
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
            bool alarm_stopped = (i < 20);
            ESP_LOGI(TAG, "button pressed (alarm_stopped=%d)", alarm_stopped);
            if (alarm_stopped) {
                xQueueOverwrite(button_queue, &alarm_stopped);
                esp_event_post(ALARM_EVENT, ALARM_EVENT_STOPPED, NULL, 0, portMAX_DELAY);
            } else if (uxQueueSpacesAvailable(button_queue)) {
                xQueueOverwrite(button_queue, &alarm_stopped);
                esp_event_post(ALARM_EVENT, ALARM_EVENT_DELAYED, NULL, 0, portMAX_DELAY);
            }
        }
    }
}

void notify_isr(void* task_handle) {
    vTaskNotifyGiveFromISR(task_handle, NULL);
}

void update_clock(alarm_time_t* clock) {
    time_t raw_time;
    struct tm day_time;

    raw_time = time(NULL);
    localtime_r(&raw_time, &day_time);

    clock->hours = day_time.tm_hour;
    clock->minutes = day_time.tm_min;
    clock->seconds = day_time.tm_sec;
}

void delay_alarm(alarm_time_t* alarm) {
    alarm->minutes = (alarm->minutes + 5) % 60;
    if (alarm->minutes < 5) {
        alarm->hours = (alarm->hours + 1) % 24;
    }
}

bool is_alarm_enabled(void) {
    return !gpio_get_level(ALARM_PIN_SWITCH);
}

bool is_button_pressed(void) {
    return !gpio_get_level(ALARM_PIN_BTN);
}
