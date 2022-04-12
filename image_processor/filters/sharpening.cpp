#include "sharpening.h"

long long Sharpening::Matrix(long long dx, long long dy) const {
    if (dx == 0 && dy == 0) {
        return 5;
    } else if (dx == 0 || dy == 0) {
        return -1;
    } else {
        return 0;
    }
}

long long Sharpening::VerticalRange() const {
    return 1;
}

long long Sharpening::HorizontalRange() const {
    return 1;
}
