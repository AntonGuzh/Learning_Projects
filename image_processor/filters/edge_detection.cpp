#include "edge_detection.h"

#include "grayscale.h"

EdgeDetection::EdgeDetection(double threshold) : threshold_(threshold) {}

Picture EdgeDetection::operator()(const Picture& pic) {
    Grayscale gs;
    Picture res = gs(pic);
    for (size_t y = 0; y < pic.Height(); ++y) {
        for (size_t x = 0; x < pic.Width(); ++x) {
            ChangePixel(x, y, pic, res);
            if (res.GetColor(x, y).red > static_cast<Bit>(threshold_ * 255)) {
                res.SetColor(x, y, {255, 255, 255});
            } else {
                res.SetColor(x, y, {0, 0, 0});
            }
        }
    }
    return res;
}

long long EdgeDetection::Matrix(long long dx, long long dy) const {
    if (dx == 0 && dy == 0) {
        return 4;
    } else if (dx == 0 || dy == 0) {
        return -1;
    } else {
        return 0;
    }
}

long long EdgeDetection::VerticalRange() const {
    return 1;
}

long long EdgeDetection::HorizontalRange() const {
    return 1;
}
