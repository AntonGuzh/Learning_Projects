#include "serialize.h"

#include "serialize_exceptions.h"

#include <iostream>
#include <fstream>

namespace {
    const int FILE_HEADER_SIZE = 14;
    const int INFORMATION_HEADER_SIZE = 40;
    const int PRINT_RESOLUTION = 2835;

    size_t CalculatePaddingAmount(size_t width) {
        return (4 - width * 3 % 4) % 4;
    }

    size_t ReadFourBits(const Bit* const start) {
        return start[0] + (start[1] << 8) + (start[2] << 16) + (start[3] << 24);
    }

    void WriteFourBits(Bit* start, size_t value) {
        start[0] = value;
        start[1] = value >> 8;
        start[2] = value >> 16;
        start[3] = value >> 24;
    }

    void WriteTwoBits(Bit* start, size_t value) {
        start[0] = value;
        start[1] = value >> 8;
    }

    void WriteHeader(std::fstream& f, size_t height, size_t width) {
        Bit header[FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE];

        size_t padding_amount = CalculatePaddingAmount(width);
        size_t file_size = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + height * (3 * width + padding_amount);

        header[0] = 'B';
        header[1] = 'M';
        WriteFourBits(header + 2, file_size);
        WriteFourBits(header + 6, 0);
        WriteFourBits(header + 10, FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE);
        WriteFourBits(header + 14, INFORMATION_HEADER_SIZE);
        WriteFourBits(header + 18, width);
        WriteFourBits(header + 22, height);
        WriteTwoBits(header + 26, 1);
        WriteTwoBits(header + 28, 24);
        WriteFourBits(header + 30, 0);
        WriteFourBits(header + 34, height * (3 * width + padding_amount));
        WriteFourBits(header + 38, PRINT_RESOLUTION);
        WriteFourBits(header + 42, PRINT_RESOLUTION);
        WriteFourBits(header + 46, 0);
        WriteFourBits(header + 50, 0);

        f.write(reinterpret_cast<char*>(header), FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE);
    }

    Color ReadColor(std::fstream& f) {
        Bit bit_color[3];
        f.read(reinterpret_cast<char*>(bit_color), 3);
        return Color({bit_color[2], bit_color[1], bit_color[0]});
    }

    void WriteColor(std::fstream& f, const Color& color) {
        Bit bit_color[3];
        bit_color[2] = color.red;
        bit_color[1] = color.green;
        bit_color[0] = color.blue;

        f.write(reinterpret_cast<char*>(bit_color), 3);
    }
}

Picture BMPLoader::operator()(const char* path) {
    std::fstream f(path, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        throw OpenFailed();
    }

    Bit file_header[FILE_HEADER_SIZE];
    f.read(reinterpret_cast<char*>(file_header), FILE_HEADER_SIZE);
    if (file_header[0] != 'B' || file_header[1] != 'M') {
        f.close();
        throw InvalidFormatBMP();
    }
    Bit information_header[INFORMATION_HEADER_SIZE];
    f.read(reinterpret_cast<char*>(information_header), INFORMATION_HEADER_SIZE);

    size_t width = ReadFourBits(information_header + 4);
    size_t height = ReadFourBits(information_header + 8);
    size_t padding_amount = CalculatePaddingAmount(width);

    std::vector<std::vector<Color>> picture(height, std::vector<Color>(width));

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            picture[y][x] = ReadColor(f);
        }
        f.ignore(static_cast<long long>(padding_amount));
    }

    f.close();
    return Picture(picture);
}

void BMPSaver::operator()(const char* path, const Picture& picture) {
    std::fstream f(path, std::ios::out | std::ios::binary);
    if (!f.is_open()) {
        throw OpenFailed();
    }

    WriteHeader(f, picture.Height(), picture.Width());

    Bit tmp[3] = {0, 0, 0};
    for (size_t y = 0; y < picture.Height(); ++y) {
        for (size_t x = 0; x < picture.Width(); ++x) {
            WriteColor(f, picture.GetColor(x, y));
        }
        size_t padding_amount = CalculatePaddingAmount(picture.Width());
        f.write(reinterpret_cast<char*>(tmp), static_cast<long long>(padding_amount));
    }

    f.close();
}