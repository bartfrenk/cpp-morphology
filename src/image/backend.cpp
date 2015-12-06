#include "backend.hpp"
#include "../utils/log.hpp"
#include <iostream>

using Utils::log;

namespace Image {

FreeImage::~FreeImage() {
    log << "~FreeImage() [mPixels = " << mPixels << "]\n";
    FreeImage_Unload(mPixels);
}

FreeImage::FreeImage(const FREE_IMAGE_FORMAT fif, const std::string filename) {
    mPixels = FreeImage_Load(fif, filename.c_str());
    if (mPixels != nullptr)
        init();
}

FreeImage::FreeImage(const size_t width, const size_t height, const int bpp) {
    mPixels = FreeImage_Allocate(width, height, bpp);
    if (mPixels != nullptr)
        init();
}

FreeImage::FreeImage(FIBITMAP * const pixels) : mPixels(pixels) {
    if (mPixels != nullptr)
        init();
}

FreeImage::FreeImage(const FreeImage &&img) : mPixels(img.mPixels) {
    log << "FreeImage(const FreeImage&&)\n";
    // TODO: no need to query, take from img
    init();
}

FreeImage& FreeImage::operator=(const FreeImage &img) {
    std::cout << "FreeImage::operator=(const FreeImage&)\n";
    FreeImage_Unload(mPixels);
    mPixels = FreeImage_Clone(img.mPixels);
    if (mPixels != nullptr)
        init();
    return *this;
}

void FreeImage::init() {
    mPitch = FreeImage_GetPitch(mPixels);
    mWidth = FreeImage_GetWidth(mPixels);
    mHeight = FreeImage_GetHeight(mPixels);
}

void FreeImage::save(const FREE_IMAGE_FORMAT fif, const std::string filename) const {
    FreeImage_Save(fif, mPixels, filename.c_str());
}

uint32_t FreeImage::width() const {
    return FreeImage_GetWidth(mPixels);
}

uint32_t FreeImage::height() const {
    return FreeImage_GetHeight(mPixels);
}

}
