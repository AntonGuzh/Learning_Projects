#include "parser.h"

#include <stdexcept>

namespace {
    bool IsPath(const std::string& path) {
        for (const auto& chr: path) {
            if (!std::isalpha(chr) && chr != '.' && chr != '/' && chr != '_') {
                return false;
            }
        }
        return true;
    }

    bool IsFilter(const std::string& filter) {
        return filter[0] == '-';
    }

    size_t CorrectSizeTArg(const char* str, const std::string& filter) {
        size_t res = 0;
        try {
            if (str[0] == '-') {
                throw 0;
            }
            res = std::stoll(str);
            if (res == 0) {
                throw 0;
            }
        } catch (...) {
            throw std::invalid_argument("Expected to get a positive \"long long\" for the " + filter);
        }
        return res;
    }

    double CorrectDoubleArg(const char* str, const std::string& filter) {
        double res = 0;
        try {
            res = std::stod(str);
            if (res <= 0) {
                throw 0;
            }
        } catch (...) {
            throw std::invalid_argument("Expected to get a positive \"double\" for the " + filter);
        }
        return res;
    }
}

Parser::Parser(int argc, char* argv[]) : all_(argc) {
    if (argc < 3) {
        throw std::invalid_argument("The first three arguments should be: program name, input path, output path");
    }

    for (size_t i = 0; i < 3; ++i) {
        all_[i] = std::string(argv[i]);
        if (!IsPath(all_[i])) {
            throw std::invalid_argument("The first three arguments should be: program name, input path, output path");
        }
    }

    for (size_t i = 3; i < argc; ++i) {
        all_[i] = std::string(argv[i]);
        if (!IsFilter(all_[i])) {
            throw std::invalid_argument("Invalid argument for the filter");
        }

        if (all_[i] == "-crop") {
            size_t width = CorrectSizeTArg(argv[++i], "-crop");
            size_t height = CorrectSizeTArg(argv[++i], "-crop");
            filters_.push_back(new Crop(width, height));
        } else if (all_[i] == "-gs") {
            filters_.push_back(new Grayscale());
        } else if (all_[i] == "-neg") {
            filters_.push_back(new Negative());
        } else if (all_[i] == "-post") {
            size_t levels = CorrectSizeTArg(argv[++i], "-post");
            filters_.push_back(new Posterize(levels));
        } else if (all_[i] == "-sharp") {
            filters_.push_back(new Sharpening());
        } else if (all_[i] == "-edge") {
            double threshold = CorrectDoubleArg(argv[++i], "-edge");
            filters_.push_back(new EdgeDetection(threshold));
        } else if (all_[i] == "-blur") {
            double sigma = CorrectDoubleArg(argv[++i], "-blur");
            filters_.push_back(new GaussianBlur(sigma));
        } else {
            throw std::invalid_argument("Invalid filter \"" + all_[i] + "\'");
        }
    }
}

Parser::~Parser() {
    for (auto& filter_ptr: filters_) {
        delete filter_ptr;
    }
}

const std::vector<std::string>& Parser::GetAll() {
    return all_;
}

const std::string& Parser::GetProgramName() {
    return all_[0];
}

const std::string& Parser::GetInput() {
    return all_[1];
}

const std::string& Parser::GetOutput() {
    return all_[2];
}

const std::vector<Filter*>& Parser::GetFilters() {
    return filters_;
}