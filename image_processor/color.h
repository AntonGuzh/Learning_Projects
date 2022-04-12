#pragma once

#include <initializer_list>
#include <stdint.h>

using Bit = uint8_t;

class Color {
public:
    Color();
    Color(const std::initializer_list<Bit>& list);

    Bit& operator[](size_t i);
    Bit operator[](size_t i) const;

    Bit red;
    Bit green;
    Bit blue;
};
