#pragma once

#define SD_MOUNT_POINT "/sdcard"
#define SD_PIN_MOSI 15
#define SD_PIN_MISO 2
#define SD_PIN_CLK 14
#define SD_PIN_CS 13
#define SD_DMA_CHAN 1

#define NET_CONFIG_PATH (SD_MOUNT_POINT "/config.json")

#define POT_ADC_HOURS_CHAN 4
#define POT_ADC_MINUTES_CHAN 5
#define POT_PIN_CALIB_LED 19
#define POT_PIN_CALIB_BTN 39

#define SOUND_PIN_ENABLE 27
#define SOUND_RINGINGS_PATH (SD_MOUNT_POINT "/ringings")

#define EPD_PIN_BUSY 4
#define EPD_PIN_RES 16
#define EPD_PIN_DC 17
#define EPD_PIN_CS 5
#define EPD_PIN_SCL 18
#define EPD_PIN_SDA 23

#define ALARM_PIN_BTN 21
#define ALARM_PIN_SWITCH 22
