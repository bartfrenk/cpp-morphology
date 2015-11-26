#include "base.hpp"
#include "../utils/log.hpp"
#include <iostream>

using Utils::log;

namespace Image {

BaseImage::~BaseImage() {
    log << "~BaseImage() [mPixels = " << mPixels << "]\n";
    FreeImage_Unload(mPixels);
}

BaseImage::BaseImage(const FREE_IMAGE_FORMAT fif, const std::string filename) {
    mPixels = FreeImage_Load(fif, filename.c_str());
    if (mPixels != nullptr)
        init();
}

BaseImage::BaseImage(const size_t width, const size_t height, const int bpp) {
    mPixels = FreeImage_Allocate(width, height, bpp);
    if (mPixels != nullptr)
        init();
}

BaseImage::BaseImage(FIBITMAP * const pixels) : mPixels(pixels) {
    if (mPixels != nullptr)
        init();
}

BaseImage::BaseImage(const BaseImage &&img) : mPixels(img.mPixels) {
    log << "BaseImage(const BaseImage&&)\n";
    // TODO: no need to query, take from img
    init();
}

BaseImage& BaseImage::operator=(const BaseImage &img) {
    std::cout << "BaseImage::operator=(const BaseImage&)\n";
    FreeImage_Unload(mPixels);
    mPixels = FreeImage_Clone(img.mPixels);
    if (mPixels != nullptr)
        init();
    return *this;
}

void BaseImage::init() {
    mPitch = FreeImage_GetPitch(mPixels);
    mWidth = FreeImage_GetWidth(mPixels);
    mHeight = FreeImage_GetHeight(mPixels);
}

void BaseImage::save(const FREE_IMAGE_FORMAT fif, const std::string filename) const {
    FreeImage_Save(fif, mPixels, filename.c_str());
}

}
