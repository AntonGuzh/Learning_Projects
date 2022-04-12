#pragma once

#include "picture.h"

class Load {
public:
    virtual Picture operator()(const char* path) = 0;
};

class Save {
public:
    virtual void operator()(const char* path, const Picture& picture) = 0;
};

class BMPLoader : public Load {
public:
    Picture operator()(const char* path) override;
};

class BMPSaver : public Save {
public:
    void operator()(const char* path, const Picture& picture) override;
};