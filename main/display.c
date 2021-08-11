#include <esp_log.h>
#include <esp_event.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include "display.h"
#include "alarm.h"

static const char* TAG = "display";

static QueueHandle_t alarm_event_queue;
static QueueHandle_t alarm_tick_queue;
static QueueHandle_t alarm_changed_queue;


static void _Noreturn display_task(void* _);
static void event_handler(void* _, esp_event_base_t base, int32_t id, void* data);


void init_display(void) {
    ESP_LOGI(TAG, "initializing display");

    alarm_event_queue = xQueueCreate(16, sizeof(int32_t));
    alarm_tick_queue = xQueueCreate(1, sizeof(alarm_time_t));
    alarm_changed_queue = xQueueCreate(1, sizeof(alarm_time_t));

    esp_event_handler_instance_register(ALARM_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL, NULL);
}

void start_display(void) {
    xTaskCreate(&display_task, "display", 2048, NULL, 1, NULL);
}

void display_task(void* _) {
    bool dirty = true;
    alarm_time_t clock = MIDNIGHT;
    alarm_time_t alarm = MIDNIGHT;
    bool alarm_enabled = false;
    bool alarm_ringing = false;
    int alarm_delay = 0;

    for (;;) {
        if (xQueueReceive(alarm_tick_queue, &clock, 0)) {
            dirty = true;
        }

        if (alarm_delay == 0 && xQueueReceive(alarm_changed_queue, &alarm, 0)) {
            dirty = true;
        }

        if (dirty) {
            dirty = false;
            ESP_LOGW(TAG, "clock=%02d:%02d\talarm=%02d:%02d+%d\tenabled=%d\tringing=%d",
                     clock.hours, clock.minutes, alarm.hours, alarm.minutes, alarm_delay, alarm_enabled, alarm_ringing);
        }

        int32_t event_id;
        if (xQueueReceive(alarm_event_queue, &event_id, pdMS_TO_TICKS(1000))) {
            switch (event_id) {
                case ALARM_EVENT_ENABLED:
                    if (!alarm_enabled) {
                        dirty = true;
                        alarm_enabled = true;
                    }
                    break;

                case ALARM_EVENT_DISABLED:
                    if (alarm_enabled) {
                        dirty = true;
                        alarm_enabled = false;
                        alarm_ringing = false;
                        alarm_delay = 0;
                    }
                    break;

                case ALARM_EVENT_STARTED:
                    if (!alarm_ringing) {
                        dirty = true;
                        alarm_ringing = true;
                    }
                    break;

                case ALARM_EVENT_STOPPED:
                    if (alarm_ringing || alarm_delay > 0) {
                        dirty = true;
                        alarm_ringing = false;
                        alarm_delay = 0;
                    }
                    break;

                case ALARM_EVENT_DELAYED:
                    if (alarm_ringing) {
                        dirty = true;
                        alarm_ringing = false;
                        alarm_delay += 5;
                    }
                    break;

                default:
                    break;
            }
        }
    }
}

void event_handler(void* _, esp_event_base_t base, int32_t id, void* data) {
    if (id == ALARM_EVENT_TICK) {
        xQueueOverwrite(alarm_tick_queue, data);
    } else if (id == ALARM_EVENT_CHANGED) {
        xQueueOverwrite(alarm_changed_queue, data);
    }

    xQueueSend(alarm_event_queue, &id, portMAX_DELAY);
}
