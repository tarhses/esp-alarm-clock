#pragma once

/**
 * Return the ceiling of a division of a by b.
 */
int div_ceil(int a, int b);

/**
 * Return the minimum value between a and b.
 */
int min(int a, int b);

/**
 * Return the maximum value between a and b.
 */
int max(int a, int b);

/**
 * Return the closest value to x checking a <= x <= b.
 */
int clamp(int a, int x, int b);
