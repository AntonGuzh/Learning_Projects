#include "posterize.h"

//#include <iostream>

Posterize::Posterize(size_t levels) : levels_(levels) {
}

void Posterize::ChangePixel(size_t x, size_t y, const Picture& origin, Picture& res) const {
    if (levels_ < 2) {
        res.SetColor(x, y, {0, 0, 0});
        return;
    }
    if (levels_ > 255) {
        return;
    }
    Color color = origin.GetColor(x, y);
    Color tmp_color;

    //std::cout << "get\n";
    for (size_t channel = 0; channel < 3; ++channel) {
        if (color[channel] <= 1. / levels_ * 255) {
            tmp_color[channel] = 0;
            //std::cout << "blaaaaaaaaaaaaaaaaaaaaaaack\n";
        }

        for (size_t i = 1; i < levels_ - 1; ++i) {
            double left = static_cast<double>(i) / levels_ * 255;
            double right = static_cast<double>(i + 1) / levels_ * 255;
            if (left < color[channel] && color[channel] <= right) {
                tmp_color[channel] = (left + right) / 2;
                //std::cout << "MIIIIIIIIIIdleeeeeeeeeeee\n";
            }
        }

        if (color[channel] > static_cast<double>(levels_ - 1) / levels_ * 255) {
            tmp_color[channel] = 255;

        }
    }
    res.SetColor(x, y, tmp_color);
}