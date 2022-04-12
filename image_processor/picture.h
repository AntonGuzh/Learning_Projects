#pragma once

#include "color.h"

#include <vector>

class Picture {
public:
    Picture();
    Picture(const Picture& other, size_t height, size_t width);
    explicit Picture(const std::vector<std::vector<Color>>& picture);

    Color GetColor(size_t x, size_t y) const;
    void SetColor(size_t x, size_t y, const Color& color);

    size_t Width() const;
    size_t Height() const;

private:
    size_t width_;
    size_t height_;

    std::vector<std::vector<Color>> picture_;
};
