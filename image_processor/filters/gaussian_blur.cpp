#include "gaussian_blur.h"

#include <iostream>

#include <cmath>

GaussianBlur::GaussianBlur(double sigma) : horizontal_(true) {
    for (size_t i = 0; true; ++i) {
        weights_.push_back(1 / std::sqrt(2 * M_PI * sigma * sigma) * exp((i * i) / (2 * sigma * sigma) * -1));
        if (weights_[i] < 10e-9) {
            break;
        }
    }
}

Picture GaussianBlur::operator()(const Picture& pic) {
    Picture tmp(pic);
    horizontal_ = true;
    for (size_t y = 0; y < pic.Height(); ++y) {
        for (size_t x = 0; x < pic.Width(); ++x) {
            ChangePixel(x, y, pic, tmp);
        }
    }
    horizontal_ = false;
    Picture res(tmp);
    for (size_t y = 0; y < pic.Height(); ++y) {
        for (size_t x = 0; x < pic.Width(); ++x) {
            ChangePixel(x, y, tmp, res);
        }
    }
    return res;
}

void GaussianBlur::ChangePixel(size_t x, size_t y, const Picture& origin, Picture& res) const {
    double sum_r = 0;
    double sum_g = 0;
    double sum_b = 0;
    if (horizontal_) {
        for (long long i = RangeSum(x, -weights_.size() + 1, res.Width());
             i < res.Width() && i < x + weights_.size(); ++i) {
            sum_r += origin.GetColor(i, y).red * weights_[std::abs(i - static_cast<long long>(x))];
            sum_g += origin.GetColor(i, y).green * weights_[std::abs(i - static_cast<long long>(x))];
            sum_b += origin.GetColor(i, y).blue * weights_[std::abs(i - static_cast<long long>(x))];
        }
    } else {
        for (long long i = RangeSum(y, -weights_.size() + 1, res.Height());
             i < res.Height() && i < y + weights_.size(); ++i) {
            sum_r += origin.GetColor(x, i).red * weights_[std::abs(i - static_cast<long long>(y))];
            sum_g += origin.GetColor(x, i).green * weights_[std::abs(i - static_cast<long long>(y))];
            sum_b += origin.GetColor(x, i).blue * weights_[std::abs(i - static_cast<long long>(y))];
        }
    }
    Color color = {BitNormalize(sum_r), BitNormalize(sum_g), BitNormalize(sum_b)};
    res.SetColor(x, y, color);
}