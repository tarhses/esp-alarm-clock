#include <math.h>

#include <esp_log.h>
#include <esp_event.h>
#include <nvs_flash.h>
#include <driver/gpio.h>
#include <driver/adc.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include "pot.h"
#include "alarm.h"
#include "config.h"
#include "mathx.h"

static const char* TAG = "potentiometers";

static TaskHandle_t calib_task_handle = NULL;
static QueueHandle_t calib_queue_handle = NULL;


/**
 * Current calibrated values read from the potentiometers.
 *
 * Each member should approximately be in range [0..1]. "Approximately" means
 * that, depending on the calibration and reading error margins, the values
 * could actually be lower than 0 or higher than 1.
 */
typedef struct {
    float hours;
    float minutes;
} values_t;

#define UNINITIALIZED_VALUES { -1.f, -1.f }

/**
 * Calibration values of the potentiometers.
 *
 * ESP32's analog to digital converters gives 12 bits integers in range
 * [0..4096[ corresponding to 0 mV up to 3300 mV. However the recommended
 * range is 150 mV to 2450 mV. Below or above theses values, the readings won't
 * be linear.
 *
 * The solution here is to put resistors on the circuitry, tuning the voltage
 * to the right range; and to calibrate the potentiometers, having minimum and
 * maximum reachable values. The minimum and maximum values are stored in this
 * struct.
 */
typedef struct {
    int hours_min;
    int hours_max;
    int minutes_min;
    int minutes_max;
} calibration_t;

#define DEFAULT_CALIBRATION { 0, 4095, 0, 4095 }
#define UNINITIALIZED_CALIBRATION { 4095, 0, 4095, 0 }

/**
 * Main thread reading and updating the potentiometers value at constant rate.
 *
 * An `ALARM_EVENT_CHANGED` event is posted at start, and when a significant
 * difference is detected from the previous reading.
 */
static void _Noreturn reading_task(void* _);

/**
 * Second thread to calibrate the potentiometers.
 *
 * When the calibration button is pressed this task will record minimum and
 * maximum values from each potentiometer.
 *
 * Once the button is pressed again, the calibration values are sent to the
 * main task and stored into non-volatile storage.
 */
static void _Noreturn calibration_task(void* _);

/**
 * Interrupt service routine waking the calibration task up when the
 * calibration button is pressed.
 */
static void IRAM_ATTR calibration_isr(void* _);

/**
 * Update the potentiometers values if there is a significant difference from
 * the previous values.
 *
 * @param calib Calibration values
 * @param values Potentiometers values to update
 * @return Whether the values have been updated
 */
static bool update(const calibration_t* calib, values_t* values);

/**
 * Update a single value if there is a significant difference.
 *
 * @param value Previous reading, value to update
 * @param reading New reading
 * @return Whether there is a significant difference
 */
static bool update_reading(float* value, float reading);

/**
 * Get the current readings and update minimum and maximum values.
 *
 * @param calib Calibration values to update
 */
static void calibrate(calibration_t* calib);

/**
 * Get a calibrated reading from the hour potentiometer.
 *
 * @param calib Calibration values
 * @return Reading in range [0..1] approximately (see `values_t`)
 */
static float read_hours(const calibration_t* calib);

/**
 * Get a calibrated reading from the minute potentiometer.
 *
 * @param calib Calibration values
 * @return Reading in range [0..1] approximately (see `values_t`)
 */
static float read_minutes(const calibration_t* calib);

/**
 * Get a raw reading from the hour potentiometer.
 *
 * @return Reading in range [0..4095]
 */
static int read_hours_raw(void);

/**
 * Get a raw reading from the minute potentiometer.
 *
 * @return Reading in range [0..4095]
 */
static int read_minutes_raw(void);

/**
 * Get a calibrated reading from a specific ADC channel.
 *
 * @param chan Channel to read from
 * @param min Calibration minimum value
 * @param max Calibration maximum value
 * @return Reading in range [0..1] approximately (see `values_t`)
 */
static float read_normalized(adc1_channel_t chan, int min, int max);

/**
 * Get a raw reading from a specific ADC channel.
 *
 * @param chan Channel to read from
 * @return Reading in range [0..4095]
 */
static int read_raw(adc1_channel_t chan);

/**
 * Load calibration values previously stored in non-volatile storage.
 *
 * @param calib Calibration values to update
 */
static void load_calibration_nvs(calibration_t* calib);

/**
 * Store calibration values into non-volatile storage.
 *
 * @param calib Calibration values to store
 */
static void store_calibration_nvs(const calibration_t* calib);


void init_potentiometers(void) {
    ESP_LOGI(TAG, "initializing potentiometers");

    // To avoid glitches on GPIO39
    // https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#_CPPv412adc1_get_raw14adc1_channel_t
    // TODO: use debouncing instead?
    adc_power_acquire();

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(POT_ADC_HOURS_CHAN, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(POT_ADC_MINUTES_CHAN, ADC_ATTEN_DB_11);

    gpio_config(&(gpio_config_t){
        .pin_bit_mask = BIT64(POT_PIN_CALIB_LED),
        .mode = GPIO_MODE_OUTPUT,
    });

    gpio_config(&(gpio_config_t){
        .pin_bit_mask = BIT64(POT_PIN_CALIB_BTN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .intr_type = GPIO_INTR_POSEDGE,
    });

    gpio_isr_handler_add(POT_PIN_CALIB_BTN, &calibration_isr, NULL);

    calib_queue_handle = xQueueCreate(1, sizeof(calibration_t));
}

void start_potentiometers(void) {
    xTaskCreate(&reading_task, "pot_reading", 2048, NULL, 1, NULL);
    xTaskCreate(&calibration_task, "pot_calibration", 2048, NULL, 1, &calib_task_handle);
}

void reading_task(void* _) {
    values_t values = UNINITIALIZED_VALUES;
    calibration_t calib = DEFAULT_CALIBRATION;

    load_calibration_nvs(&calib);

    for (;;) {
        if (update(&calib, &values)) {
            alarm_time_t event = {
                .hours = clamp(0, (int)(roundf(24.f * values.hours)), 23),
                .minutes = clamp(0, (int)(roundf(60.f * values.minutes)), 59),
            };

            ESP_LOGI(TAG, "alarm changed to %02d:%02d", event.hours, event.minutes);
            esp_event_post(ALARM_EVENT, ALARM_EVENT_CHANGED, &event, sizeof(alarm_time_t), portMAX_DELAY);
        }

        // Sleep a bit. We can wake up early if the potentiometers have been calibrated.
        xQueueReceive(calib_queue_handle, &calib, pdMS_TO_TICKS(500));
    }
}

void calibration_task(void* _) {
    for (;;) {
        // Wait for the calibration button to be pressed
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        ESP_LOGI(TAG, "calibration start");
        gpio_set_level(POT_PIN_CALIB_LED, 1);

        // Update the calibration values until it is pressed again
        calibration_t calib = UNINITIALIZED_CALIBRATION;
        do {
            calibrate(&calib);
        } while (!ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(100)));

        // Send them to the main task, and then store them
        xQueueOverwrite(calib_queue_handle, &calib);
        store_calibration_nvs(&calib);

        gpio_set_level(POT_PIN_CALIB_LED, 0);
        ESP_LOGI(TAG, "calibration stop");
    }
}

void calibration_isr(void* _) {
    if (calib_task_handle != NULL) {
        vTaskNotifyGiveFromISR(calib_task_handle, NULL);
    }
}

bool update(const calibration_t* calib, values_t* values) {
    // Don't use `||`, it evaluates its operands lazily.
    // That would imply that minutes wouldn't be updated if hours aren't.
    bool updated = false;
    updated |= update_reading(&values->hours, read_hours(calib));
    updated |= update_reading(&values->minutes, read_minutes(calib));
    return updated;
}

bool update_reading(float* value, float reading) {
    if (fabsf(*value - reading) > .02f) {
        *value = reading;
        return true;
    } else {
        return false;
    }
}

void calibrate(calibration_t* calib) {
    int reading;

    reading = read_hours_raw();
    calib->hours_min = min(reading, calib->hours_min);
    calib->hours_max = max(reading, calib->hours_max);

    reading = read_minutes_raw();
    calib->minutes_min = min(reading, calib->minutes_min);
    calib->minutes_max = max(reading, calib->minutes_max);
}

float read_hours(const calibration_t* calib) {
    return read_normalized(POT_ADC_HOURS_CHAN, calib->hours_min, calib->hours_max);
}

float read_minutes(const calibration_t* calib) {
    return read_normalized(POT_ADC_MINUTES_CHAN, calib->minutes_min, calib->minutes_max);
}

int read_hours_raw(void) {
    return read_raw(POT_ADC_HOURS_CHAN);
}

int read_minutes_raw(void) {
    return read_raw(POT_ADC_MINUTES_CHAN);
}

float read_normalized(adc1_channel_t chan, int min, int max) {
    return (float)(read_raw(chan) - min) / (float)(max - min);
}

int read_raw(adc1_channel_t chan) {
    // Using multi-sampling to enhance precision
    // https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#minimizing-noise
    int value = 0;
    for (int i = 0; i < 128; ++i) {
        value += adc1_get_raw(chan);
    }
    return value / 128;
}

void load_calibration_nvs(calibration_t* calib) {
    esp_err_t error;
    nvs_handle_t handle;

    error = nvs_open(TAG, NVS_READONLY, &handle);
    if (error != ESP_OK) {
        ESP_LOGE(TAG, "non-volatile storage error (%s), calibration might be needed", esp_err_to_name(error));
        return;
    }

    ESP_ERROR_CHECK_WITHOUT_ABORT(nvs_get_i32(handle, "hours_min", &calib->hours_min));
    ESP_ERROR_CHECK_WITHOUT_ABORT(nvs_get_i32(handle, "hours_max", &calib->hours_max));
    ESP_ERROR_CHECK_WITHOUT_ABORT(nvs_get_i32(handle, "minutes_min", &calib->minutes_min));
    ESP_ERROR_CHECK_WITHOUT_ABORT(nvs_get_i32(handle, "minutes_max", &calib->minutes_max));

    ESP_LOGI(TAG, "calibration loaded from non-volatile storage "
                  "(hours_min=%d, hours_max=%d, minutes_min=%d, minutes_max=%d)",
                  calib->hours_min, calib->hours_max, calib->minutes_min, calib->minutes_max);

    nvs_close(handle);
}

void store_calibration_nvs(const calibration_t* calib) {
    esp_err_t error;
    nvs_handle_t handle;

    error = nvs_open(TAG, NVS_READWRITE, &handle);
    if (error != ESP_OK) {
        ESP_LOGE(TAG, "non-volatile storage error (%s)", esp_err_to_name(error));
        return;
    }

    ESP_LOGI(TAG, "storing calibration into non-volatile storage "
                  "(hours_min=%d, hours_max=%d, minutes_min=%d, minutes_max=%d)",
                  calib->hours_min, calib->hours_max, calib->minutes_min, calib->minutes_max);

    ESP_ERROR_CHECK_WITHOUT_ABORT(nvs_set_i32(handle, "hours_min", calib->hours_min));
    ESP_ERROR_CHECK_WITHOUT_ABORT(nvs_set_i32(handle, "hours_max", calib->hours_max));
    ESP_ERROR_CHECK_WITHOUT_ABORT(nvs_set_i32(handle, "minutes_min", calib->minutes_min));
    ESP_ERROR_CHECK_WITHOUT_ABORT(nvs_set_i32(handle, "minutes_max", calib->minutes_max));

    nvs_close(handle);
}
