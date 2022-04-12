#include "picture.h"

Picture::Picture() : width_(0), height_(0) {}

Picture::Picture(const Picture& other, size_t height, size_t width){
    height_ = std::min(height, other.Height());
    width_ = std::min(width, other.Width());

    picture_.assign(height_, std::vector<Color>(width_));
    for (size_t y = other.Height() - height; y < other.Height(); ++y) {
        for (size_t x = 0; x < width_; ++x) {
            picture_[y + height_ - other.Height()][x] = other.GetColor(x, y);
        }
    }
}

Picture::Picture(const std::vector<std::vector<Color>>& picture) {
    picture_ = picture;

    height_ = picture.size();
    if (height_ != 0) {
        width_ = picture[0].size();
    } else {
        width_ = 0;
    }
}

Color Picture::GetColor(size_t x, size_t y) const {
    return picture_[y][x];
}

void Picture::SetColor(size_t x, size_t y, const Color& color) {
    picture_[y][x] = color;
}

size_t Picture::Width() const{
    return width_;
}

size_t Picture::Height() const {
    return height_;
}
