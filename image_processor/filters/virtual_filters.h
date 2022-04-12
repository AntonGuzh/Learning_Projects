#pragma once

#include "../picture.h"

#include "helper_functions.h"

class Filter {
public:
    Filter() = default;
    virtual ~Filter() = default;

    virtual Picture operator()(const Picture& pic);

protected:
    virtual void ChangePixel(size_t x, size_t y, const Picture& origin, Picture& res) const = 0;
};

class MatrixFilter : public Filter {
protected:
    void ChangePixel(size_t x, size_t y, const Picture& origin, Picture& res) const override;

    virtual long long Matrix(long long dx, long long dy) const = 0;
    virtual long long VerticalRange() const = 0;
    virtual long long HorizontalRange() const = 0;
};
