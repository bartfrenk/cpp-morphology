#ifndef FREE_IMAGE_HPP
#define FREE_IMAGE_HPP

#include <cstddef>
#include <string>
#include <iostream>
#include <iomanip>

#include "common.hpp"

namespace Image {

typedef BYTE byte;

template <typename P>
class FreeImage {
public:
};

struct RGB {
    RGB(byte red, byte green, byte blue) : red(red), green(green), blue(blue) {};
    byte red;
    byte green;
    byte blue;
};

std::ostream& operator<<(std::ostream& os, const RGB& pixel);

template <>
class FreeImage<RGB> : public BaseImage {
public:
    FreeImage(const size_t width, const size_t height);
    FreeImage(const std::string filename);
    FreeImage(const FreeImage<RGB> &img);

    RGB get(const size_t x, const size_t y) const;
    void set(const size_t x, const size_t y, const RGB pixel);

    bool contains(const size_t x, const size_t y) const {
        return x <= mWidth && y <= mHeight;
    }
};


}

#endif
