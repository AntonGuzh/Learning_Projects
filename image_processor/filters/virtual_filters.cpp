#include "virtual_filters.h"

Picture Filter::operator()(const Picture& pic) {
    Picture res(pic);
    for (size_t y = 0; y < pic.Height(); ++y) {
        for (size_t x = 0; x < pic.Width(); ++x) {
            ChangePixel(x, y, pic, res);
        }
    }
    return res;
}

void MatrixFilter::ChangePixel(size_t x, size_t y, const Picture& origin, Picture& res) const {
    long long sum_r = 0;
    long long sum_g = 0;
    long long sum_b = 0;
    for (long long dy = -VerticalRange(); dy <= VerticalRange(); ++dy) {
        for (long long dx = -HorizontalRange(); dx <= HorizontalRange(); ++dx) {
            size_t y0 = RangeSum(y, dy, origin.Height());
            size_t x0 = RangeSum(x, dx, origin.Width());
            sum_r += origin.GetColor(x0, y0).red * Matrix(dx, dy);
            sum_g += origin.GetColor(x0, y0).green * Matrix(dx, dy);
            sum_b += origin.GetColor(x0, y0).blue * Matrix(dx, dy);
        }
    }
    Color color = {BitNormalize(sum_r), BitNormalize(sum_g), BitNormalize(sum_b)};
    res.SetColor(x, y, color);
}
