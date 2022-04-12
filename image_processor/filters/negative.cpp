#include "negative.h"

void Negative::ChangePixel(size_t x, size_t y, const Picture& origin, Picture& res) const {
    Color color = res.GetColor(x, y);
    color.red = 255 - color.red;
    color.green = 255 - color.green;
    color.blue = 255 - color.blue;
    res.SetColor(x, y, color);
}
