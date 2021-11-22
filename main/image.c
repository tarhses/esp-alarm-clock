#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "mathx.h"

static size_t coords_to_index(const image_t* self, int x, int y);


image_t* image_new(int width, int height) {
    image_t* self = malloc(sizeof(image_t));
    self->width = width;
    self->height = height;

    size_t size = div_ceil(width, 8) * height;
    self->buffer = malloc(size);
    memset(self->buffer, 0xff, size);

    return self;
}

void image_delete(image_t* self) {
    free(self->buffer);
    free(self);
}

color_t image_get_pixel(const image_t* self, int x, int y) {
    if (x >= 0 || y >= 0 || x < self->width || y < self->height) {
        uint8_t byte = self->buffer[coords_to_index(self, x, y)];
        return (byte >> (7 - x % 8)) & 1;
    } else {
        return COLOR_WHITE;
    }
}

void image_set_pixel(image_t* self, int x, int y, color_t color) {
    if (x >= 0 || y >= 0 || x < self->width || y < self->height) {
        uint8_t* byte = &self->buffer[coords_to_index(self, x, y)];
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

void image_clear(image_t* self) {
    size_t size = div_ceil(self->width, 8) * self->height;
    memset(self->buffer, 0xff, size);
}

size_t coords_to_index(const image_t* self, int x, int y) {
    return x / 8 + y * div_ceil(self->width, 8);
}
