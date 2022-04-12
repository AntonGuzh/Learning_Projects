#include "crop.h"

Crop::Crop(size_t width, size_t height) : height_(height), width_(width) {}

Picture Crop::operator()(const Picture& pic) {
    return Picture(pic, height_, width_);
}

void Crop::ChangePixel(size_t x, size_t y, const Picture& origin, Picture& res) const {}