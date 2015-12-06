#ifndef IMAGE_PIXEL_HPP
#define IMAGE_PIXEL_HPP

#include <string>

namespace Image {

typedef unsigned char byte;

struct RGB {
    RGB(byte red, byte green, byte blue) : red(red), green(green), blue(blue) {};
    byte red;
    byte green;
    byte blue;
};

typedef byte Intensity;

std::string toString(const RGB pixel);

std::string toString(const Intensity pixel);

Intensity average(const RGB& rgb);

}

#endif
