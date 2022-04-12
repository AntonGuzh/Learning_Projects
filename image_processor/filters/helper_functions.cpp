#include "helper_functions.h"

size_t RangeSum(size_t a, long long b, size_t max) {
    if (max == 0) {
        return 0;
    }
    if (0 <= a + b && a + b < max) {
        return a + b;
    }
    if (b < 0) {
        return 0;
    } else {
        return max - 1;
    }
}

Bit BitNormalize(long long a) {
    if (0 <= a && a < 256) {
        return a;
    } else if (a < 0) {
        return 0;
    } else {
        return 255;
    }
}