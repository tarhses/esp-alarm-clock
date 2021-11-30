#include <string.h>

#include <esp_log.h>
#include <esp_event.h>
#include <esp_random.h>
#include <driver/i2s.h>

#include "sound.h"
#include "config.h"
#include "alarm.h"
#include "storage.h"

static void _Noreturn sound_task(void* _);
static void alarm_started_handler(void* _, esp_event_base_t _base, int32_t _id, void* _data);
static void alarm_stopped_handler(void* _, esp_event_base_t _base, int32_t _id, void* _data);


static const char* TAG = "sound";

static TaskHandle_t sound_task_handle = NULL;
static char** ringings;
static size_t ringings_count;
static uint8_t sound_buffer[512];

void init_sound(void) {
    ESP_LOGI(TAG, "initializing sound");

    gpio_config(&(gpio_config_t){
        .pin_bit_mask = BIT64(SOUND_PIN_ENABLE),
        .mode = GPIO_MODE_OUTPUT,
    });

    i2s_driver_install(I2S_NUM_0, &(i2s_config_t) {
        .mode = I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN,
        .sample_rate = 44100,
        .bits_per_sample = 16,
        .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = 0,
        .dma_buf_count = 2,
        .dma_buf_len = 1024,
        .use_apll = false,
    }, 0, NULL);
    i2s_set_dac_mode(I2S_DAC_CHANNEL_RIGHT_EN);
    i2s_stop(I2S_NUM_0);

    list_files(SOUND_RINGINGS_PATH, &ringings, &ringings_count);
    ESP_LOGI(TAG, "%zu ringings found", ringings_count);

    esp_event_handler_instance_register(ALARM_EVENT, ALARM_EVENT_STARTED, &alarm_started_handler, NULL, NULL);
    esp_event_handler_instance_register(ALARM_EVENT, ALARM_EVENT_STOPPED, &alarm_stopped_handler, NULL, NULL);
}

void start_sound(void) {
    xTaskCreate(&sound_task, "sound", 2048, NULL, 1, &sound_task_handle);
}

void sound_task(void* _) {
    uint32_t running = 0;
    for (;;) {
        xTaskNotifyWait(0, 0, &running, portMAX_DELAY);

        if (running) {
            file_handle_t file;
            size_t choice = esp_random() % ringings_count;
            char* ringing = concat_paths(SOUND_RINGINGS_PATH, ringings[choice]);
            bool success = open_file(ringing, &file);
            free(ringing);

            if (!success) {
                // TODO: play some fallback ringing
                continue;
            }

            gpio_set_level(SOUND_PIN_ENABLE, 1);
            i2s_start(I2S_NUM_0);

            size_t bytes_read, bytes_written;
            while (running && read_file_into(file, sound_buffer, sizeof(sound_buffer), &bytes_read)) {
                i2s_write_expand(I2S_NUM_0, sound_buffer, bytes_read, 8, 16, &bytes_written, portMAX_DELAY);
                xTaskNotifyWait(0, 0, &running, 0);
            }

            i2s_stop(I2S_NUM_0);
            gpio_set_level(SOUND_PIN_ENABLE, 0);

            close_file(file);
        }
    }
}

void alarm_started_handler(void* _, esp_event_base_t _base, int32_t _id, void* _data) {
    if (sound_task_handle != NULL) {
        xTaskNotify(sound_task_handle, 1, eSetValueWithOverwrite);
    }
}

void alarm_stopped_handler(void* _, esp_event_base_t _base, int32_t _id, void* _data) {
    if (sound_task_handle != NULL) {
        xTaskNotify(sound_task_handle, 0, eSetValueWithOverwrite);
    }
}
