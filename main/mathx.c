#include "mathx.h"

int div_ceil(int a, int b) {
    return a / b + (a % b != 0);
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int clamp(int a, int x, int b) {
    return max(a, min(x, b));
}
