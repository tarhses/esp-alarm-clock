#include <esp_log.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "epd.h"
#include "mathx.h"
#include "config.h"

static void write_command(uint8_t command, size_t data_size, const uint8_t* data);
static void write_byte(uint8_t byte);
static void wait_while_busy(void);


static const char* TAG = "epd";

void epd_init(void) {
    ESP_LOGI(TAG, "initializing e-paper display");

    gpio_config(&(gpio_config_t){
        .pin_bit_mask = BIT64(EPD_PIN_BUSY),
        .mode = GPIO_MODE_INPUT,
    });
    
    gpio_config(&(gpio_config_t){
        .pin_bit_mask = BIT64(EPD_PIN_RES) | BIT64(EPD_PIN_DC) | BIT64(EPD_PIN_CS) | BIT64(EPD_PIN_SCL) | BIT64(EPD_PIN_SDA),
        .mode = GPIO_MODE_OUTPUT,
    });
}

void epd_on() {
    ESP_LOGI(TAG, "power on");

    // Hardware reset
    gpio_set_level(EPD_PIN_RES, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(EPD_PIN_RES, 1);
    vTaskDelay(pdMS_TO_TICKS(10));

    // Software reset
    write_command(0x12, 0, NULL);

    // Driver output control
    write_command(0x01, 3, (uint8_t[]){
        0xf9, 0x00, // number of lines (height - 1 = 249)
        0x00,       // scanning sequence and direction
    });

    // Data entry mode setting - 0x00: Y-X-, 0x01: Y-X+, 0x02: Y+X-, 0x03: Y+X+
    write_command(0x11, 1, (uint8_t[]){ 0x01 });

    // Border waveform control - 0x05: GS transition (follow LUT1), 0x80: VCOM (?)
    write_command(0x3c, 1, (uint8_t[]){ 0x05 });

    // Temperature sensor control (why?) - 0x48: external, 0x80: internal
    write_command(0x18, 1, (uint8_t[]){ 0x80 });

    // Display update control (why? not in specs)
    write_command(0x21, 2, (uint8_t[]){
        0x00, // normal RAM access (ignoring or inverting is also possible)
        0x80, // available source from S8 to S167 (?)
    });
}

void epd_draw(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t* data) {
    uint8_t x2, y2;
    size_t data_size;

    x /= 8;
    w = div_ceil(w, 8);
    x2 = x + w - 1;
    y2 = y + h - 1;
    data_size = w * h;

    ESP_LOGI(TAG, "sending image data");

    // Set RAM address range
    write_command(0x44, 2, (uint8_t[]){ x, x2 });
    write_command(0x45, 4, (uint8_t[]){ y2, 0x00, y, 0x00 });

    // Set RAM address counter
    write_command(0x4e, 1, (uint8_t[]){ x });
    write_command(0x4f, 2, (uint8_t[]){ y2, 0x00 });

    // Write RAM (black white)
    write_command(0x24, data_size, data);
}

void epd_update() {
    ESP_LOGI(TAG, "starting screen update");

    // Display update control 2 - 0xf7: display mode 1, 0xff: display mode 2 (?)
    write_command(0x22, 1, (uint8_t[]){ 0xf7 });

    // Activate display update sequence
    write_command(0x20, 0, NULL);
}

void epd_off(void) {
    // Deep sleep mode - 0x00: normal mode, 0x01: mode 1, 0x02: mode 2 (?)
    write_command(0x10, 1, (uint8_t[]){ 0x01 });
    vTaskDelay(pdMS_TO_TICKS(100));

    ESP_LOGI(TAG, "power off");
}

void write_command(uint8_t command, size_t data_size, const uint8_t* data) {
    // TODO: hard-coded SPI without any timing, maybe use ESP-32's SPI controller?
    wait_while_busy();
    ESP_LOGD(TAG, "command 0x%02x with %d byte(s) of data", command, data_size);

    gpio_set_level(EPD_PIN_CS, 0);

    gpio_set_level(EPD_PIN_DC, 0);
    write_byte(command);

    gpio_set_level(EPD_PIN_DC, 1);
    for (size_t i = 0; i < data_size; ++i) {
        write_byte(data[i]);
    }

    gpio_set_level(EPD_PIN_CS, 1);
}

void write_byte(uint8_t byte) {
    for (int i = 0; i < 8; ++i, byte <<= 1) {
        gpio_set_level(EPD_PIN_SCL, 0);
        gpio_set_level(EPD_PIN_SDA, (byte & 0x80) != 0);
        gpio_set_level(EPD_PIN_SCL, 1);
    }
}

void wait_while_busy(void) {
    // TODO: maybe use an interrupt instead of polling?
    bool waiting = false;
    while (gpio_get_level(EPD_PIN_BUSY)) {
        if (!waiting) {
            waiting = true;
            ESP_LOGD(TAG, "waiting for BUSY pin");
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // to avoid a busy loop
    }
}
