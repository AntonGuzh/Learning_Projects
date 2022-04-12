#pragma once

#include "virtual_filters.h"

class Posterize : public Filter {
public:
    Posterize(size_t levels);

protected:
    void ChangePixel(size_t x, size_t y, const Picture &origin, Picture &res) const override;

private:
    size_t levels_;
};