#include "base.hpp"
#include <iostream>

namespace Image {

BaseImage::~BaseImage() {
    std::cout << "~BaseImage() [mPixels = " << mPixels << "]\n";
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

}
