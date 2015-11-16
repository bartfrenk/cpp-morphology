#include <iostream>
#include "freeimage.hpp"

namespace Image {

std::ostream& operator<<(std::ostream& os, const RGB& pixel) {
    // TODO: avoid changing the format flag
    os.setf(std::ios::hex, std::ios::basefield);
    os << "#";
    os << std::setfill('0') << std::setw(2) << (int) pixel.red;
    os << std::setfill('0') << std::setw(2) << (int) pixel.green;
    os << std::setfill('0') << std::setw(2) << (int) pixel.blue;
    os.unsetf(std::ios::basefield);
    return os;
}

FreeImage<RGB>::FreeImage(const size_t width, const size_t height)
    : BaseImage(width, height, 24) {
    std::cout << "FreeImage<RGB>::FreeImage(const size_t width, const size_t height)\n";
};

FreeImage<RGB>::FreeImage(const std::string filename)
    : BaseImage(FIF_PNG, filename) {
    std::cout << "FreeImage<RGB>::FreeImage(const std::string)\n";
};

FreeImage<RGB>::FreeImage(const FreeImage<RGB> &img)
    : BaseImage(FreeImage_Clone(img.mPixels)) {
    std::cout << "FreeImage<RGB>::FreeImage(const FreeImage<RGB>&)\n";
}

RGB FreeImage<RGB>::get(const size_t x, const size_t y) const {
    size_t index = y * mPitch + 3 * x;
    BYTE *buffer = (BYTE *) FreeImage_GetBits(mPixels);
    return RGB(buffer[index], buffer[index + 1], buffer[index + 2]);
};

void FreeImage<RGB>::set(const size_t x, const size_t y, const RGB pixel) {
    size_t index = y * mPitch + 3 * x;
    BYTE *buffer = (BYTE *) FreeImage_GetBits(mPixels);
    buffer[index] = pixel.red;
    buffer[index + 1] = pixel.green;
    buffer[index + 2] = pixel.blue;
}

}
