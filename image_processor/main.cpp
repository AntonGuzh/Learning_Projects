#include "filters.h"
#include "parser.h"
#include "picture.h"
#include "serialize.h"

#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    try {
        Parser parser(argc, argv);
        BMPLoader load;
        Picture pic = load(parser.GetInput().c_str());

        for (const auto& filter_ptr: parser.GetFilters()) {
            pic = filter_ptr->operator()(pic);
        }

        BMPSaver save;
        save(parser.GetOutput().c_str(), pic);
        std::cout << "Finish";
    } catch (const std::exception& e) {
        std::cerr << e.what();
    }
}
