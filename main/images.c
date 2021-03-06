#include "images.h"

const image_t BELL_ICONS[2] = {
    { // "icons/bell_off.png"
        .width = 24,
        .height = 24,
        .buffer = (uint8_t[]){
            0x3f, 0xff, 0xff,
            0x1f, 0xf0, 0x1f,
            0x8f, 0xe7, 0xc7,
            0xc7, 0xcf, 0xf3,
            0xe3, 0x9f, 0xfb,
            0xf1, 0x3f, 0xf9,
            0xf8, 0xff, 0xfd,
            0xc4, 0x7f, 0xfd,
            0x9e, 0x3f, 0xfd,
            0xbf, 0x1f, 0xfd,
            0x9f, 0x8f, 0xfd,
            0xcf, 0xc7, 0xf9,
            0xe7, 0xe3, 0xf3,
            0xf3, 0xf1, 0xe7,
            0xf9, 0xf8, 0xcf,
            0xfc, 0xfc, 0x5f,
            0xf6, 0x7e, 0x3f,
            0xe3, 0x3f, 0x1f,
            0xe1, 0x9f, 0x8f,
            0xe0, 0xcf, 0x47,
            0xf1, 0xe7, 0x63,
            0xff, 0xf2, 0x71,
            0xff, 0xf8, 0xf8,
            0xff, 0xff, 0xfc,
        },
    },
    { // "icons/bell_on.png"
        .width = 24,
        .height = 24,
        .buffer = (uint8_t[]){
            0xff, 0xff, 0xff,
            0xff, 0xf0, 0x1f,
            0xff, 0xe0, 0x07,
            0xff, 0xc0, 0x03,
            0xff, 0x80, 0x03,
            0xfe, 0x00, 0x01,
            0xf8, 0x00, 0x01,
            0xc0, 0x00, 0x01,
            0x80, 0x00, 0x01,
            0x80, 0x00, 0x01,
            0x80, 0x00, 0x01,
            0xc0, 0x00, 0x01,
            0xe0, 0x00, 0x03,
            0xf0, 0x00, 0x07,
            0xf8, 0x00, 0x0f,
            0xfc, 0x00, 0x1f,
            0xf6, 0x00, 0x1f,
            0xe3, 0x00, 0x3f,
            0xe1, 0x80, 0x3f,
            0xe0, 0xc0, 0x7f,
            0xf1, 0xe0, 0x7f,
            0xff, 0xf0, 0x7f,
            0xff, 0xf8, 0xff,
            0xff, 0xff, 0xff,
        },
    },
};

const image_t WIFI_ICONS[2] = {
    { // "icons/wifi_off.png"
        .width = 24,
        .height = 24,
        .buffer = (uint8_t[]){
            0x3f, 0xff, 0xff,
            0x1f, 0xfe, 0xff,
            0x8f, 0xfe, 0x7f,
            0xc7, 0xef, 0x3f,
            0xe3, 0xe7, 0xbf,
            0xf1, 0xf3, 0x9f,
            0xf8, 0xfb, 0xdf,
            0xfc, 0x79, 0xdf,
            0xfe, 0x3d, 0xcf,
            0xff, 0x1d, 0xef,
            0xf3, 0x8d, 0xef,
            0xed, 0xc5, 0xef,
            0xed, 0xe3, 0xef,
            0xf3, 0xd1, 0xef,
            0xff, 0x98, 0xef,
            0xff, 0xbc, 0x4f,
            0xff, 0x3a, 0x3f,
            0xfe, 0x7b, 0x1f,
            0xff, 0xf3, 0x8f,
            0xff, 0xe7, 0xc7,
            0xff, 0xef, 0x23,
            0xff, 0xfe, 0x71,
            0xff, 0xfe, 0xf8,
            0xff, 0xff, 0xfc,
        },
    },
    { // "icons/wifi_on.png"
        .width = 24,
        .height = 24,
        .buffer = (uint8_t[]){
            0xff, 0xff, 0xff,
            0xff, 0xfe, 0xff,
            0xff, 0xfe, 0x7f,
            0xff, 0xef, 0x3f,
            0xff, 0xe7, 0xbf,
            0xff, 0xf3, 0x9f,
            0xfe, 0x7b, 0xdf,
            0xff, 0x39, 0xdf,
            0xff, 0xbd, 0xcf,
            0xff, 0x9d, 0xef,
            0xf3, 0xdd, 0xef,
            0xe1, 0xdd, 0xef,
            0xe1, 0xdd, 0xef,
            0xf3, 0xdd, 0xef,
            0xff, 0x9d, 0xef,
            0xff, 0xbd, 0xcf,
            0xff, 0x39, 0xdf,
            0xfe, 0x7b, 0xdf,
            0xff, 0xf3, 0x9f,
            0xff, 0xe7, 0xbf,
            0xff, 0xef, 0x3f,
            0xff, 0xfe, 0x7f,
            0xff, 0xfe, 0xff,
            0xff, 0xff, 0xff,
        },
    },
};

const image_t DIGITS_16[11] = {
    { // "digits16/0.png"
        .width = 16,
        .height = 10,
        .buffer = (uint8_t[]){
            0xf0, 0x0f,
            0xc0, 0x03,
            0x8f, 0xf1,
            0x3f, 0xfc,
            0x3f, 0xfc,
            0x3f, 0xfc,
            0x3f, 0xfc,
            0x8f, 0xf1,
            0xc0, 0x03,
            0xf0, 0x0f,
        },
    },
    { // "digits16/1.png"
        .width = 16,
        .height = 6,
        .buffer = (uint8_t[]){
            0x00, 0x00,
            0x00, 0x00,
            0xff, 0xf9,
            0xff, 0xf1,
            0xff, 0xe3,
            0xff, 0xf7,
        },
    },
    { // "digits16/2.png"
        .width = 16,
        .height = 10,
        .buffer = (uint8_t[]){
            0x3f, 0xff,
            0x3f, 0x83,
            0x3f, 0x01,
            0x3c, 0x78,
            0x38, 0xfc,
            0x31, 0xfc,
            0x23, 0xfc,
            0x0f, 0xfc,
            0x1f, 0xf9,
            0x3f, 0xfd,
        },
    },
    { // "digits16/3.png"
        .width = 16,
        .height = 10,
        .buffer = (uint8_t[]){
            0xc3, 0xff,
            0x81, 0xc3,
            0x9c, 0x81,
            0x3e, 0xb8,
            0x3e, 0x7c,
            0x3e, 0x7c,
            0x3e, 0x7c,
            0x3e, 0x7c,
            0x3f, 0xf9,
            0xbf, 0xfd,
        },
    },
    { // "digits16/4.png"
        .width = 16,
        .height = 11,
        .buffer = (uint8_t[]){
            0xf3, 0xff,
            0xf3, 0xff,
            0x00, 0x00,
            0x00, 0x00,
            0xf3, 0xf9,
            0xf3, 0xe3,
            0xf3, 0xcf,
            0xf3, 0x1f,
            0xf2, 0x7f,
            0xf0, 0xff,
            0xf3, 0xff,
        },
    },
    { // "digits16/5.png"
        .width = 16,
        .height = 10,
        .buffer = (uint8_t[]){
            0xe1, 0xff,
            0x80, 0x7c,
            0x9e, 0x7c,
            0x3f, 0x3c,
            0x3f, 0x3c,
            0x3f, 0x3c,
            0x3f, 0x3c,
            0x3f, 0x3c,
            0x3f, 0x00,
            0xbf, 0x01,
        },
    },
    { // "digits16/6.png"
        .width = 16,
        .height = 10,
        .buffer = (uint8_t[]){
            0xe0, 0xff,
            0x80, 0x7c,
            0x9e, 0x3c,
            0x3f, 0x3c,
            0x3f, 0x3c,
            0x3f, 0x3c,
            0x3f, 0x39,
            0x9e, 0x61,
            0xc0, 0x07,
            0xf0, 0x1f,
        },
    },
    { // "digits16/7.png"
        .width = 16,
        .height = 10,
        .buffer = (uint8_t[]){
            0xff, 0xf8,
            0xff, 0xe0,
            0xff, 0x84,
            0xfc, 0x1c,
            0xf0, 0x7c,
            0xc3, 0xfc,
            0x0f, 0xfc,
            0x3f, 0xfc,
            0xff, 0xfc,
            0xff, 0xfc,
        },
    },
    { // "digits16/8.png"
        .width = 16,
        .height = 10,
        .buffer = (uint8_t[]){
            0xc3, 0xff,
            0x81, 0xc1,
            0x1c, 0x81,
            0x3c, 0x3c,
            0x3e, 0x7c,
            0x3e, 0x7c,
            0x3e, 0x3c,
            0x3c, 0x81,
            0x81, 0xc1,
            0xc3, 0xff,
        },
    },
    { // "digits16/9.png"
        .width = 16,
        .height = 10,
        .buffer = (uint8_t[]){
            0xf8, 0x0f,
            0xe0, 0x03,
            0x86, 0x79,
            0x9c, 0xfc,
            0x3c, 0xfc,
            0x3c, 0xfc,
            0x3c, 0xfc,
            0x3c, 0x79,
            0x3e, 0x01,
            0xff, 0x07,
        },
    },
    { // "digits16/colon.png"
        .width = 16,
        .height = 3,
        .buffer = (uint8_t[]){
            0xc7, 0xe3,
            0xc7, 0xe3,
            0xc7, 0xe3,
        },
    },
};

const image_t DIGITS_72[11] = {
    { // "digits72/0.png"
        .width = 72,
        .height = 44,
        .buffer = (uint8_t[]){
            0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff,
            0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff,
            0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff,
            0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff,
            0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff,
            0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff,
            0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f,
            0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
            0xf0, 0x00, 0x00, 0x1f, 0xff, 0xf8, 0x00, 0x00, 0x0f,
            0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x0f,
            0xe0, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x07,
            0xc0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x03,
            0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x03,
            0x80, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x01,
            0x80, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x01,
            0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x01,
            0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00,
            0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00,
            0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00,
            0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00,
            0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00,
            0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00,
            0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00,
            0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00,
            0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00,
            0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x01,
            0x80, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x01,
            0x80, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x01,
            0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x03,
            0xc0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x03,
            0xe0, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x07,
            0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x0f,
            0xf0, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x0f,
            0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
            0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f,
            0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff,
            0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff,
            0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff,
            0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
            0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff,
            0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
        },
    },
    { // "digits72/1.png"
        .width = 72,
        .height = 24,
        .buffer = (uint8_t[]){
            0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
            0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
            0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
            0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x01,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x03,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x03,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x07,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x07,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x07,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0f,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0f,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0f,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x1f,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x1f,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x1f,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x3f,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x7f,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff,
        },
    },
    { // "digits72/2.png"
        .width = 72,
        .height = 43,
        .buffer = (uint8_t[]){
            0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0x80, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff,
            0x00, 0x7f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x0f, 0xff,
            0x00, 0x7f, 0xff, 0xff, 0xff, 0x80, 0x00, 0x03, 0xff,
            0x00, 0x7f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0xff,
            0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x7f,
            0x00, 0x7f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x3f,
            0x00, 0x7f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x1f,
            0x00, 0x7f, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x0f,
            0x00, 0x7f, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x07,
            0x00, 0x7f, 0xff, 0xff, 0x00, 0x01, 0xfe, 0x00, 0x07,
            0x00, 0x7f, 0xff, 0xfc, 0x00, 0x0f, 0xff, 0xc0, 0x03,
            0x00, 0x7f, 0xff, 0xf8, 0x00, 0x1f, 0xff, 0xe0, 0x03,
            0x00, 0x7f, 0xff, 0xf0, 0x00, 0x7f, 0xff, 0xf0, 0x01,
            0x00, 0x7f, 0xff, 0xe0, 0x00, 0xff, 0xff, 0xf8, 0x01,
            0x00, 0x7f, 0xff, 0xc0, 0x01, 0xff, 0xff, 0xfc, 0x01,
            0x00, 0x7f, 0xff, 0x80, 0x03, 0xff, 0xff, 0xfc, 0x00,
            0x00, 0x7f, 0xff, 0x00, 0x0f, 0xff, 0xff, 0xfe, 0x00,
            0x00, 0x7f, 0xfe, 0x00, 0x1f, 0xff, 0xff, 0xfe, 0x00,
            0x00, 0x7f, 0xf8, 0x00, 0x3f, 0xff, 0xff, 0xfe, 0x00,
            0x00, 0x7f, 0xf0, 0x00, 0x7f, 0xff, 0xff, 0xfe, 0x00,
            0x00, 0x7f, 0xe0, 0x00, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0x00, 0x7f, 0xc0, 0x01, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0x00, 0x7f, 0x80, 0x07, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0x00, 0x7f, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0x00, 0x7e, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0x00, 0x78, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xfc, 0x01,
            0x00, 0x70, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xfc, 0x01,
            0x00, 0x60, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x01,
            0x00, 0x40, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x01,
            0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x03,
            0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x03,
            0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x00, 0x07,
            0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f,
            0x00, 0x00, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x0f,
            0x00, 0x01, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x1f,
            0x00, 0x03, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x3f,
            0x00, 0x07, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x7f,
            0x00, 0x0f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0xff,
            0x00, 0x1f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x03, 0xff,
            0x00, 0x7f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x07, 0xff,
            0x80, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x1f, 0xff,
            0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff,
        },
    },
    { // "digits72/3.png"
        .width = 72,
        .height = 46,
        .buffer = (uint8_t[]){
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xe0, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xc0, 0x00, 0x00, 0xff, 0xff, 0xc0, 0x1f, 0xff,
            0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x00, 0x07, 0xff,
            0xfe, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x01, 0xff,
            0xfc, 0x00, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x7f,
            0xf8, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x3f,
            0xf0, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x1f,
            0xf0, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f,
            0xe0, 0x01, 0xff, 0xe0, 0x03, 0x80, 0x00, 0x00, 0x0f,
            0xe0, 0x07, 0xff, 0xf8, 0x01, 0x80, 0x06, 0x00, 0x07,
            0xc0, 0x0f, 0xff, 0xfc, 0x01, 0x00, 0x3f, 0xc0, 0x03,
            0xc0, 0x1f, 0xff, 0xfe, 0x00, 0x00, 0xff, 0xf0, 0x03,
            0x80, 0x3f, 0xff, 0xff, 0x00, 0x01, 0xff, 0xf8, 0x01,
            0x80, 0x3f, 0xff, 0xff, 0x80, 0x03, 0xff, 0xfc, 0x01,
            0x80, 0x7f, 0xff, 0xff, 0x80, 0x03, 0xff, 0xfc, 0x01,
            0x00, 0x7f, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xfe, 0x01,
            0x00, 0x7f, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xfe, 0x00,
            0x00, 0x7f, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0x00,
            0x00, 0xff, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0x00,
            0x00, 0xff, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0x00,
            0x00, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0x00,
            0x00, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0x00,
            0x00, 0xff, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0x00,
            0x00, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xfe, 0x00,
            0x00, 0x7f, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfe, 0x00,
            0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x01,
            0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x01,
            0x80, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x01,
            0x80, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x01,
            0xc0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x03,
            0xc0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x03,
            0xc0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x07,
            0xe0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x07,
            0xe0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x0f,
            0xf0, 0x00, 0x7f, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f,
            0xf8, 0x00, 0x03, 0xff, 0xff, 0xff, 0x80, 0x00, 0x3f,
            0xfc, 0x00, 0x00, 0x7f, 0xff, 0xff, 0x80, 0x00, 0x7f,
            0xfc, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x00, 0x00, 0xff,
            0xfe, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x80, 0x01, 0xff,
            0xff, 0x80, 0x00, 0x1f, 0xff, 0xff, 0x80, 0x07, 0xff,
            0xff, 0xc0, 0x00, 0x1f, 0xff, 0xff, 0xe0, 0x3f, 0xff,
            0xff, 0xf0, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xfc, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        },
    },
    { // "digits72/4.png"
        .width = 72,
        .height = 54,
        .buffer = (uint8_t[]){
            0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
            0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
            0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
            0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xfe, 0x00, 0x0f,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xf8, 0x00, 0x1f,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xf0, 0x00, 0x7f,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xe0, 0x00, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0x80, 0x01, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0x00, 0x07, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xfe, 0x00, 0x0f, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xf8, 0x00, 0x1f, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xf0, 0x00, 0x3f, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0xe0, 0x00, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0x80, 0x01, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xff, 0x00, 0x03, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xfe, 0x00, 0x0f, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xf8, 0x00, 0x1f, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xf0, 0x00, 0x3f, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xe0, 0x00, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0xc0, 0x01, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7f, 0x00, 0x03, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7e, 0x00, 0x0f, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x7c, 0x00, 0x1f, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x70, 0x00, 0x3f, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x60, 0x00, 0x7f, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x40, 0x01, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x80, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        },
    },
    { // "digits72/5.png"
        .width = 72,
        .height = 47,
        .buffer = (uint8_t[]){
            0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xf8, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xe0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xc0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0x03,
            0xff, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xfe, 0x01,
            0xfe, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xfe, 0x00,
            0xfc, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xfe, 0x00,
            0xf8, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00,
            0xf8, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00,
            0xf0, 0x00, 0x3f, 0xf8, 0x00, 0x1f, 0xff, 0xfe, 0x00,
            0xe0, 0x00, 0xff, 0xfe, 0x00, 0x0f, 0xff, 0xfe, 0x00,
            0xe0, 0x01, 0xff, 0xff, 0x00, 0x0f, 0xff, 0xfe, 0x00,
            0xc0, 0x03, 0xff, 0xff, 0x80, 0x07, 0xff, 0xfe, 0x00,
            0xc0, 0x07, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xfe, 0x00,
            0x80, 0x0f, 0xff, 0xff, 0xe0, 0x03, 0xff, 0xfe, 0x00,
            0x80, 0x1f, 0xff, 0xff, 0xf0, 0x03, 0xff, 0xfe, 0x00,
            0x80, 0x1f, 0xff, 0xff, 0xf0, 0x03, 0xff, 0xfe, 0x00,
            0x00, 0x3f, 0xff, 0xff, 0xf8, 0x03, 0xff, 0xfe, 0x00,
            0x00, 0x3f, 0xff, 0xff, 0xf8, 0x01, 0xff, 0xfe, 0x00,
            0x00, 0x3f, 0xff, 0xff, 0xf8, 0x01, 0xff, 0xfe, 0x00,
            0x00, 0x3f, 0xff, 0xff, 0xf8, 0x01, 0xff, 0xfe, 0x00,
            0x00, 0x7f, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xfe, 0x00,
            0x00, 0x7f, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xfe, 0x00,
            0x00, 0x7f, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xfe, 0x00,
            0x00, 0x3f, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xfe, 0x00,
            0x00, 0x3f, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xfe, 0x00,
            0x00, 0x3f, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xfe, 0x00,
            0x00, 0x3f, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xfe, 0x00,
            0x80, 0x1f, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xfe, 0x00,
            0x80, 0x1f, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xfe, 0x00,
            0x80, 0x0f, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xfe, 0x00,
            0xc0, 0x0f, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xfe, 0x00,
            0xc0, 0x07, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xfe, 0x00,
            0xe0, 0x03, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
            0xe0, 0x00, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
            0xf0, 0x00, 0x3f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
            0xf0, 0x00, 0x07, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
            0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00,
            0xfc, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0x00,
            0xfe, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x00, 0x00,
            0xff, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x00, 0x01,
            0xff, 0x80, 0x00, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0x03,
            0xff, 0xe0, 0x00, 0x0f, 0xff, 0x80, 0x00, 0x00, 0x0f,
            0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xfe, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
        },
    },
    { // "digits72/6.png"
        .width = 72,
        .height = 43,
        .buffer = (uint8_t[]){
            0xff, 0xff, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xf8, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xe0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff,
            0xff, 0x80, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff,
            0xff, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff,
            0xfc, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff,
            0xf8, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff,
            0xf8, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff,
            0xf0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
            0xe0, 0x00, 0xff, 0xe0, 0x00, 0x7f, 0xff, 0xff, 0xff,
            0xe0, 0x03, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0xff, 0x83,
            0xc0, 0x07, 0xff, 0xfe, 0x00, 0x3f, 0xff, 0xfe, 0x01,
            0xc0, 0x0f, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xf8, 0x00,
            0x80, 0x1f, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xf0, 0x00,
            0x80, 0x3f, 0xff, 0xff, 0xc0, 0x1f, 0xff, 0xc0, 0x00,
            0x80, 0x3f, 0xff, 0xff, 0xc0, 0x1f, 0xff, 0x00, 0x00,
            0x00, 0x7f, 0xff, 0xff, 0xe0, 0x0f, 0xfe, 0x00, 0x00,
            0x00, 0x7f, 0xff, 0xff, 0xe0, 0x0f, 0xf8, 0x00, 0x01,
            0x00, 0x7f, 0xff, 0xff, 0xe0, 0x0f, 0xe0, 0x00, 0x03,
            0x00, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xc0, 0x00, 0x0f,
            0x00, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0x00, 0x00, 0x3f,
            0x00, 0xff, 0xff, 0xff, 0xf0, 0x0c, 0x00, 0x00, 0x7f,
            0x00, 0xff, 0xff, 0xff, 0xf0, 0x08, 0x00, 0x01, 0xff,
            0x00, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x07, 0xff,
            0x00, 0x7f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x0f, 0xff,
            0x00, 0x7f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x3f, 0xff,
            0x00, 0x7f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0xff, 0xff,
            0x80, 0x3f, 0xff, 0xff, 0xc0, 0x00, 0x01, 0xff, 0xff,
            0x80, 0x3f, 0xff, 0xff, 0xc0, 0x00, 0x07, 0xff, 0xff,
            0x80, 0x1f, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xff, 0xff,
            0xc0, 0x0f, 0xff, 0xff, 0x00, 0x00, 0x3f, 0xff, 0xff,
            0xc0, 0x07, 0xff, 0xfe, 0x00, 0x00, 0xff, 0xff, 0xff,
            0xe0, 0x01, 0xff, 0xf8, 0x00, 0x03, 0xff, 0xff, 0xff,
            0xe0, 0x00, 0x7f, 0xe0, 0x00, 0x07, 0xff, 0xff, 0xff,
            0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff,
            0xf8, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff,
            0xfc, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
            0xfe, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff,
            0xff, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff,
            0xff, 0x80, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xe0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xf8, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
        },
    },
    { // "digits72/7.png"
        .width = 72,
        .height = 45,
        .buffer = (uint8_t[]){
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x01,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x02, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x0e, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x3e, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0xfe, 0x00,
            0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x03, 0xfe, 0x00,
            0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x0f, 0xfe, 0x00,
            0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x3f, 0xfe, 0x00,
            0xff, 0xff, 0xff, 0xc0, 0x00, 0x01, 0xff, 0xfe, 0x00,
            0xff, 0xff, 0xff, 0x00, 0x00, 0x07, 0xff, 0xfe, 0x00,
            0xff, 0xff, 0xfc, 0x00, 0x00, 0x1f, 0xff, 0xfe, 0x00,
            0xff, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xff, 0xfe, 0x00,
            0xff, 0xff, 0x80, 0x00, 0x01, 0xff, 0xff, 0xfe, 0x00,
            0xff, 0xfe, 0x00, 0x00, 0x07, 0xff, 0xff, 0xfe, 0x00,
            0xff, 0xf8, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xfe, 0x00,
            0xff, 0xe0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfe, 0x00,
            0xff, 0x80, 0x00, 0x01, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0xfe, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0xf8, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0xe0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0x80, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0x80, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0x80, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x01,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87,
        },
    },
    { // "digits72/8.png"
        .width = 72,
        .height = 42,
        .buffer = (uint8_t[]){
            0xff, 0xff, 0xc0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xfc, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xf0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xe0, 0x3f, 0xff,
            0xff, 0x00, 0x00, 0x00, 0x1f, 0xfe, 0x00, 0x03, 0xff,
            0xfe, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0xff,
            0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x7f,
            0xf8, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x1f,
            0xf0, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x0f,
            0xf0, 0x00, 0x0f, 0x80, 0x00, 0x80, 0x00, 0x00, 0x07,
            0xe0, 0x00, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x07,
            0xc0, 0x03, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x03,
            0xc0, 0x07, 0xff, 0xfe, 0x00, 0x00, 0x0f, 0x80, 0x01,
            0x80, 0x0f, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xf0, 0x01,
            0x80, 0x1f, 0xff, 0xff, 0x80, 0x00, 0xff, 0xf8, 0x01,
            0x80, 0x3f, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xfc, 0x00,
            0x80, 0x3f, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xfe, 0x00,
            0x00, 0x7f, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xfe, 0x00,
            0x00, 0x7f, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0x00,
            0x00, 0x7f, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0x00,
            0x00, 0x7f, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0x00,
            0x00, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0x00,
            0x00, 0x7f, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0x00,
            0x00, 0x7f, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0x00,
            0x00, 0x7f, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xfe, 0x00,
            0x00, 0x7f, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xfe, 0x00,
            0x80, 0x3f, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xfc, 0x00,
            0x80, 0x3f, 0xff, 0xff, 0x80, 0x01, 0xff, 0xf8, 0x00,
            0x80, 0x1f, 0xff, 0xff, 0x80, 0x00, 0xff, 0xf0, 0x01,
            0xc0, 0x0f, 0xff, 0xff, 0x00, 0x00, 0x3f, 0xc0, 0x01,
            0xc0, 0x07, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x03,
            0xe0, 0x01, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x03,
            0xe0, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07,
            0xf0, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x0f,
            0xf0, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x1f,
            0xf8, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x3f,
            0xfc, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x7f,
            0xff, 0x00, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x01, 0xff,
            0xff, 0x80, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x0f, 0xff,
            0xff, 0xc0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xf0, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xfe, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
        },
    },
    { // "digits72/9.png"
        .width = 72,
        .height = 43,
        .buffer = (uint8_t[]){
            0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x7f, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x0f, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x03, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x01, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x7f,
            0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x3f,
            0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x1f,
            0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x1f,
            0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x0f,
            0xff, 0xff, 0xff, 0xe0, 0x00, 0x0f, 0xff, 0x00, 0x07,
            0xff, 0xff, 0xff, 0x80, 0x00, 0x3f, 0xff, 0xc0, 0x07,
            0xff, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xe0, 0x03,
            0xff, 0xff, 0xfc, 0x00, 0x00, 0xff, 0xff, 0xf0, 0x03,
            0xff, 0xff, 0xf0, 0x00, 0x01, 0xff, 0xff, 0xf8, 0x01,
            0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xfc, 0x01,
            0xff, 0xff, 0x80, 0x00, 0x03, 0xff, 0xff, 0xfe, 0x01,
            0xff, 0xfe, 0x00, 0x00, 0x07, 0xff, 0xff, 0xfe, 0x00,
            0xff, 0xf8, 0x00, 0x00, 0x07, 0xff, 0xff, 0xfe, 0x00,
            0xff, 0xf0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xfe, 0x00,
            0xff, 0xc0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x00,
            0xff, 0x00, 0x00, 0x10, 0x0f, 0xff, 0xff, 0xff, 0x00,
            0xfe, 0x00, 0x00, 0x70, 0x0f, 0xff, 0xff, 0xff, 0x00,
            0xf8, 0x00, 0x01, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0x00,
            0xe0, 0x00, 0x03, 0xf0, 0x0f, 0xff, 0xff, 0xfe, 0x00,
            0xc0, 0x00, 0x0f, 0xf0, 0x07, 0xff, 0xff, 0xfe, 0x00,
            0x80, 0x00, 0x3f, 0xf0, 0x07, 0xff, 0xff, 0xfe, 0x00,
            0x00, 0x00, 0x7f, 0xf8, 0x07, 0xff, 0xff, 0xfe, 0x01,
            0x00, 0x01, 0xff, 0xf8, 0x03, 0xff, 0xff, 0xfc, 0x01,
            0x00, 0x07, 0xff, 0xf8, 0x03, 0xff, 0xff, 0xfc, 0x01,
            0x00, 0x0f, 0xff, 0xf8, 0x01, 0xff, 0xff, 0xf8, 0x01,
            0x80, 0x3f, 0xff, 0xfc, 0x00, 0xff, 0xff, 0xf0, 0x03,
            0x80, 0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0xe0, 0x03,
            0xc1, 0xff, 0xff, 0xfe, 0x00, 0x1f, 0xff, 0x80, 0x07,
            0xff, 0xff, 0xff, 0xfe, 0x00, 0x03, 0xfc, 0x00, 0x07,
            0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x0f,
            0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x1f,
            0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x3f,
            0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x7f,
            0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x03, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x07, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x3f, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x01, 0xff, 0xff,
        },
    },
    { // "digits72/colon.png"
        .width = 72,
        .height = 14,
        .buffer = (uint8_t[]){
            0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff,
            0xff, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xe0, 0x3f, 0xff,
            0xff, 0xe0, 0x03, 0xff, 0xff, 0xff, 0xc0, 0x1f, 0xff,
            0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 0x80, 0x0f, 0xff,
            0xff, 0xc0, 0x01, 0xff, 0xff, 0xff, 0x80, 0x07, 0xff,
            0xff, 0xc0, 0x01, 0xff, 0xff, 0xff, 0x00, 0x07, 0xff,
            0xff, 0xc0, 0x01, 0xff, 0xff, 0xff, 0x00, 0x07, 0xff,
            0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 0x00, 0x07, 0xff,
            0xff, 0xe0, 0x03, 0xff, 0xff, 0xff, 0x80, 0x07, 0xff,
            0xff, 0xe0, 0x07, 0xff, 0xff, 0xff, 0x80, 0x0f, 0xff,
            0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xc0, 0x0f, 0xff,
            0xff, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xe0, 0x1f, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xff,
        },
    },
};
