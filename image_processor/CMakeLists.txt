cmake_minimum_required(VERSION 3.21)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(image_processor
        color.cpp
        filters/crop.cpp
        filters/edge_detection.cpp
        filters/gaussian_blur.cpp
        filters/grayscale.cpp
        filters/helper_functions.cpp
        filters/negative.cpp
        filters/posterize.cpp
        filters/sharpening.cpp
        filters/virtual_filters.cpp
        main.cpp
        parser.cpp
        picture.cpp
        serialize.cpp
        serialize_exceptions.cpp
        )
