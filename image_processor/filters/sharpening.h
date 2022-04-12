#pragma once

#include "virtual_filters.h"

class Sharpening : public MatrixFilter {
private:
    long long Matrix(long long dx, long long dy) const override;
    long long VerticalRange() const override;
    long long HorizontalRange() const override;
};
