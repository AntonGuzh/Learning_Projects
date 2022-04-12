#pragma once

#include "virtual_filters.h"

class Crop : public Filter {
public:
    Crop(size_t width, size_t height);

    Picture operator()(const Picture& pic) override;

protected:
    void ChangePixel(size_t x, size_t y, const Picture& origin, Picture& res) const override;

private:
    size_t height_;
    size_t width_;
};
