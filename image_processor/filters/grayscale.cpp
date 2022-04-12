#include "grayscale.h"

void Grayscale::ChangePixel(size_t x, size_t y, const Picture& origin, Picture& res) const {
    Color color = res.GetColor(x, y);
    color.red = color.green = color.blue =
            static_cast<Bit>(0.299 * color.red) + static_cast<Bit>(0.587 * color.green) +
            static_cast<Bit>(0.114 * color.blue);
    res.SetColor(x, y, color);
}
