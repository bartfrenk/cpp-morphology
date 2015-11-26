#include "strict.hpp"

#include "../utils/log.hpp"
using Utils::log;

namespace Image {

const FREE_IMAGE_FORMAT StrictImage<RGB>::format = FIF_PNG;

StrictImage<RGB>::StrictImage(const size_t width, const size_t height)
    : BaseImage(width, height, 24) {
    log << "StrictImage<RGB>::StrictImage(const size_t width, const size_t height)\n";
};

StrictImage<RGB>::StrictImage(const std::string filename)
    : BaseImage(format, filename) {
    log << "StrictImage<RGB>::StrictImage(const std::string)\n";
};

StrictImage<RGB>::StrictImage(const StrictImage<RGB> &img)
    : BaseImage(FreeImage_Clone(img.mPixels)) {
    log << "StrictImage<RGB>::StrictImage(const StrictImage<RGB>&)\n";
}

StrictImage<RGB>::StrictImage(const StrictImage<RGB> &&img)
    : BaseImage(std::move(img)) {
    log << "StrictImage<RGB>::StrictImage(const StrictImage<RGB>&&)\n";
}

void StrictImage<RGB>::save(const std::string filename) const {
    BaseImage::save(format, filename);
}

RGB StrictImage<RGB>::get(const size_t x, const size_t y) const {
    size_t index = y * mPitch + 3 * x;
    BYTE *buffer = (BYTE *) FreeImage_GetBits(mPixels);
    return RGB(buffer[index], buffer[index + 1], buffer[index + 2]);
};

void StrictImage<RGB>::set(const size_t x, const size_t y, const RGB pixel) {
    size_t index = y * mPitch + 3 * x;
    BYTE *buffer = (BYTE *) FreeImage_GetBits(mPixels);
    buffer[index] = pixel.red;
    buffer[index + 1] = pixel.green;
    buffer[index + 2] = pixel.blue;
}

const FREE_IMAGE_FORMAT StrictImage<Gray>::format = FIF_BMP;

StrictImage<Gray>::StrictImage(const size_t width, const size_t height)
    : BaseImage(width, height, 8) {
    log << "StrictImage<RGB>::StrictImage(const size_t width, const size_t height)\n";
};

StrictImage<Gray>::StrictImage(const std::string filename)
    : BaseImage(format, filename) {
    log << "StrictImage<RGB>::StrictImage(const std::string)\n";
};

StrictImage<Gray>::StrictImage(const StrictImage<Gray> &img)
    : BaseImage(FreeImage_Clone(img.mPixels)) {
    log << "StrictImage<RGB>::StrictImage(const StrictImage<RGB>&)\n";
}

StrictImage<Gray>::StrictImage(const StrictImage<Gray> &&img)
    : BaseImage(std::move(img)) {
    log << "StrictImage<Gray>::StrictImage(const StrictImage<Gray>&&)\n";
}

void StrictImage<Gray>::save(const std::string filename) const {
    BaseImage::save(format, filename);
}

Gray StrictImage<Gray>::get(const size_t x, const size_t y) const {
    size_t index = y * mPitch + x;
    BYTE *buffer = (BYTE *) FreeImage_GetBits(mPixels);
    return buffer[index];
}

void StrictImage<Gray>::set(const size_t x, const size_t y, const Gray pixel) {
    size_t index = y * mPitch + x;
    BYTE *buffer = (BYTE *) FreeImage_GetBits(mPixels);
    buffer[index] = pixel;
}

}
