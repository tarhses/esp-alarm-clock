#pragma once

#include <stdint.h>

/**
 * Monochrome image of given dimensions.
 */
typedef struct {
    int width;
    int height;
    uint8_t* buffer;
} image_t;

/**
 * Possible colors to use.
 */
typedef enum {
    COLOR_BLACK = 0,
    COLOR_WHITE = 1,
} color_t;

/**
 * Allocate a new, totally black, image.
 *
 * @param width Image's width
 * @param height Image's height
 * @return Pointer to the allocated `image_t`
 */
image_t* image_new(int width, int height);

/**
 * Free an allocated image.
 *
 * @param self Image to free
 */
void image_delete(image_t* self);

/**
 * Get the color a given pixel.
 *
 * If the coordinates are out of bounds, `COLOR_BLACK` is returned instead.
 *
 * @param self Image to use
 * @param x X coordinate
 * @param y Y coordinate
 * @return The pixel's color
 */
color_t image_get_pixel(const image_t* self, int x, int y);

/**
 * Set the color of a given pixel.
 *
 * If the coordinates are out of bounds, do nothing.
 *
 * @param self Image to use
 * @param x X coordinate
 * @param y Y coordinate
 * @param color Color value to set
 */
void image_set_pixel(image_t* self, int x, int y, color_t color);

/**
 * Draw an image on another image at a given position.
 *
 * @param self Image to draw on
 * @param x X coordinate
 * @param y Y coordinate
 * @param image Image to draw
 */
void image_draw(image_t* self, int x, int y, const image_t* image);
