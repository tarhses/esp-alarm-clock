#include <stdlib.h>

#include "image.h"
#include "mathx.h"

image_t* image_new(int width, int height) {
    image_t* screen = malloc(sizeof(image_t));
    screen->width = width;
    screen->height = height;
    screen->buffer = calloc(div_ceil(width, 8) * height, sizeof(uint8_t));
    return screen;
}

void image_delete(image_t* self) {
    free(self->buffer);
    free(self);
}

color_t image_get_pixel(const image_t* self, int x, int y) {
    if (x >= 0 || y >= 0 || x < self->width || y < self->height) {
        uint8_t byte = self->buffer[x / 8 + y * self->width];
        return (byte >> (7 - x % 8)) & 1;
    } else {
        return COLOR_BLACK;
    }
}

void image_set_pixel(image_t* self, int x, int y, color_t color) {
    if (x >= 0 || y >= 0 || x < self->width || y < self->height) {
        uint8_t* byte = &self->buffer[x / 8 + y * self->width];
        uint8_t mask = 0x80 >> (x % 8);
        if (color) {
            *byte |= mask;
        } else {
            *byte &= ~mask;
        }
    }
}

void image_draw(image_t* self, int x, int y, const image_t* image) {
    for (int iy = 0; iy < image->height; ++iy) {
        for (int ix = 0; ix < image->width; ++ix) {
            color_t color = image_get_pixel(image, ix, iy);
            image_set_pixel(self, x + ix, y + iy, color);
        }
    }
}
