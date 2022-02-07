#include <esp_log.h>
#include <esp_event.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include "display.h"
#include "alarm.h"
#include "epd.h"
#include "image.h"
#include "images.h"

typedef struct {
    alarm_time_t clock;
    alarm_time_t alarm;
    bool alarm_enabled;
    bool network_connected;
} screen_status_t;

static void _Noreturn control_task(void* _);
static void _Noreturn render_task(void* _);
static void alarm_event_handler(void* _, esp_event_base_t _base, int32_t id, void* data);
static void draw_clock(image_t* screen, int x, int y, const alarm_time_t* clock, const image_t* digits, int digit_sep, int colon_sep);


static const char* TAG = "display";

static QueueHandle_t alarm_event_queue;
static QueueHandle_t alarm_time_queue;
static QueueHandle_t screen_status_queue;

void init_display(void) {
    ESP_LOGI(TAG, "initializing display");

    epd_init();

    alarm_event_queue = xQueueCreate(16, sizeof(int32_t));
    alarm_time_queue = xQueueCreate(16, sizeof(alarm_time_t));
    screen_status_queue = xQueueCreate(16, sizeof(screen_status_t));

    esp_event_handler_instance_register(ALARM_EVENT, ESP_EVENT_ANY_ID, &alarm_event_handler, NULL, NULL);
}

void start_display(void) {
    xTaskCreate(&control_task, "display_control", 2048, NULL, 1, NULL);
    xTaskCreate(&render_task, "display_render", 2048, NULL, 1, NULL);
}

void control_task(void* _) {
    screen_status_t status = {
        .clock = MIDNIGHT,
        .alarm = MIDNIGHT,
        .alarm_enabled = false,
        .network_connected = false,
    };

    alarm_time_t normal_alarm = MIDNIGHT;
    alarm_time_t delayed_alarm = MIDNIGHT;
    bool alarm_delayed = false;
    bool dirty = true;

    for (;;) {
        int32_t event_id;
        xQueueReceive(alarm_event_queue, &event_id, portMAX_DELAY);
        switch (event_id) {
            case ALARM_EVENT_TICK:
                xQueueReceive(alarm_time_queue, &status.clock, 0);
                dirty = true;
                break;

            case ALARM_EVENT_CHANGED:
                xQueueReceive(alarm_time_queue, &normal_alarm, 0);
                if (!alarm_delayed) {
                    dirty = true;
                }
                break;

            case ALARM_EVENT_ENABLED:
                if (!status.alarm_enabled) {
                    status.alarm_enabled = true;
                    dirty = true;
                }
                break;

            case ALARM_EVENT_DISABLED:
                if (status.alarm_enabled) {
                    status.alarm_enabled = false;
                    dirty = true;
                }
                break;

            case ALARM_EVENT_STOPPED:
                if (alarm_delayed) {
                    alarm_delayed = false;
                    dirty = true;
                }
                break;

            case ALARM_EVENT_DELAYED:
                xQueueReceive(alarm_time_queue, &delayed_alarm, 0);
                if (!alarm_delayed) {
                    alarm_delayed = true;
                    dirty = true;
                }
                break;

            case ALARM_EVENT_CONNECTED:
                if (!status.network_connected) {
                    status.network_connected = true;
                    dirty = true;
                }
                break;

            case ALARM_EVENT_DISCONNECTED:
                if (status.network_connected) {
                    status.network_connected = false;
                    dirty = true;
                }
                break;

            default:
                break;
        }

        if (dirty && !xQueuePeek(alarm_event_queue, &event_id, pdMS_TO_TICKS(1000))) {
            status.alarm = alarm_delayed ? delayed_alarm : normal_alarm;
            xQueueSend(screen_status_queue, &status, portMAX_DELAY);
            dirty = false;
        }
    }
}

void render_task(void* _) {
    screen_status_t status;
    image_t* screen = image_new(122, 250);

    for (;;) {
        xQueueReceive(screen_status_queue, &status, portMAX_DELAY);

        image_clear(screen);
        draw_clock(screen, 24 + 6 + 6 + 8, -1, &status.clock, DIGITS_72, 2, 8);
        draw_clock(screen, 8, 250 - 24 - 6 - 6, &status.alarm, DIGITS_16, 2, 4);
        image_draw(screen, 6, 250 - 24 - 6, &BELL_ICONS[status.alarm_enabled]);
        image_draw(screen, 6, 6, &WIFI_ICONS[status.network_connected]);

        epd_on();
        epd_draw(0, 0, screen->width, screen->height, screen->buffer);
        epd_update();
        epd_off();
    }
}

void alarm_event_handler(void* _, esp_event_base_t _base, int32_t id, void* data) {
    if (id == ALARM_EVENT_TICK || id == ALARM_EVENT_CHANGED || id == ALARM_EVENT_DELAYED) {
        xQueueSend(alarm_time_queue, data, portMAX_DELAY);
    }

    xQueueSend(alarm_event_queue, &id, portMAX_DELAY);
}

void draw_clock(image_t* screen, int x, int y, const alarm_time_t* clock, const image_t* digits, int digit_sep, int colon_sep) {
    const image_t* images[5] = {
        &digits[clock->hours / 10],
        &digits[clock->hours % 10],
        &digits[10],
        &digits[clock->minutes / 10],
        &digits[clock->minutes % 10],
    };

    if (y == -1) {
        int total_height = digit_sep * 2 + colon_sep * 2;
        for (int i = 0; i < 5; ++i) {
            total_height += images[i]->height;
        }

        y = screen->height - (screen->height - total_height) / 2;
    }

    for (int i = 0; i < 5; ++i) {
        y -= images[i]->height;
        image_draw(screen, x, y, images[i]);
        if (i == 0 || i == 3) {
            y -= digit_sep;
        } else {
            y -= colon_sep;
        }
    }
}
