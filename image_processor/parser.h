#pragma once

#include "filters.h"

#include <string>
#include <vector>

class Parser {
public:
    Parser(int argc, char* argv[]);
    ~Parser();

    const std::vector<std::string>& GetAll();
    const std::string& GetProgramName();
    const std::string& GetInput();
    const std::string& GetOutput();
    const std::vector<Filter*>& GetFilters();

private:
    std::vector<std::string> all_;
    std::vector<Filter*> filters_;
};