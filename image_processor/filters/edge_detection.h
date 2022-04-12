#pragma once

#include "virtual_filters.h"

class EdgeDetection : public MatrixFilter {
public:
    EdgeDetection(double threshold);

    Picture operator()(const Picture& pic) override;

private:
    long long Matrix(long long dx, long long dy) const override;
    long long VerticalRange() const override;
    long long HorizontalRange() const override;

    double threshold_;
};
