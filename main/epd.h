#pragma once

#include <stdint.h>

void epd_init(void);
void epd_on(void);
void epd_draw(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t* data);
void epd_update(void);
void epd_off(void);
