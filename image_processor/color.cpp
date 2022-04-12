#include "color.h"

#include <stdexcept>

Color::Color() : red(0), green(0), blue(0) {}

Color::Color(const std::initializer_list <Bit>& list) {
    auto it = list.begin();
    red = *(it++);
    green = *(it++);
    blue = *it;
}

Bit& Color::operator[](size_t i) {
    if (i == 0) {
        return red;
    }
    if (i == 1) {
        return green;
    }
    if (i == 2) {
        return blue;
    } else {
        throw std::out_of_range("Color have only 3 components");
    }
}

Bit Color::operator[](size_t i) const {
    if (i == 0) {
        return red;
    }
    if (i == 1) {
        return green;
    }
    if (i == 2) {
        return blue;
    } else {
        throw std::out_of_range("Color have only 3 components");
    }
}
