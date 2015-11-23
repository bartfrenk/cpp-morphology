#ifndef IMAGE_PIXEL_HPP
#define IMAGE_PIXEL_HPP

#include <FreeImage.h>
#include <iostream>
#include <iomanip>

namespace Image {

typedef BYTE byte;

struct RGB {
    RGB(byte red, byte green, byte blue) : red(red), green(green), blue(blue) {};
    byte red;
    byte green;
    byte blue;
};

typedef unsigned char Gray;

std::ostream& operator<<(std::ostream &os, const RGB& pixel);

template <typename P>
void writePixel(std::ostream &os, const P &pixel) {
    os << pixel;
}

Gray average(const RGB& rgb);

}

#endif
