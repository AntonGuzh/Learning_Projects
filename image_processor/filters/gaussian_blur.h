#pragma once

#include "virtual_filters.h"

class GaussianBlur : public Filter {
public:
    GaussianBlur(double sigma);

    Picture operator()(const Picture& pic) override;

protected:
    void ChangePixel(size_t x, size_t y, const Picture &origin, Picture &res) const override;

private:
    std::vector<double> weights_;
    bool horizontal_;
};