#pragma once

#include <exception>

class OpenFailed : public std::exception {
public:
    const char* what() const noexcept override;
};

class InvalidFormatBMP : public std::exception {
public:
    const char* what() const noexcept override;
};
