#include "serialize_exceptions.h"

const char* OpenFailed::what() const noexcept {
    return "The file cannot be opened";
}

const char* InvalidFormatBMP::what() const noexcept {
    return "The file format must be BMP";
}