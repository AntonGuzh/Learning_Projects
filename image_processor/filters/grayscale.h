#pragma once

#include "virtual_filters.h"

class Grayscale : public Filter {
protected:
    void ChangePixel(size_t x, size_t y, const Picture& origin, Picture& res) const override;
};
