#include <exception>
#include "rgb.hpp"

namespace Image {

ImageRGB::ImageRGB(const size_t width, const size_t height) {
    mBitmap = FreeImage_Allocate(width, height, 24);
    if (mBitmap != nullptr && isValid())
        init();
}

ImageRGB::ImageRGB(const std::string fileName) {
    mBitmap = FreeImage_Load(FIF_PNG, fileName.c_str());
    if (mBitmap != nullptr && isValid())
        init();
    else
        throw std::invalid_argument(fileName + " is not a valid RGB image");
}

void ImageRGB::init() {
    mPitch = FreeImage_GetPitch(mBitmap);
    mWidth = FreeImage_GetWidth(mBitmap);
    mHeight = FreeImage_GetHeight(mBitmap);
}

bool ImageRGB::isValid() {
    return FreeImage_GetBPP(mBitmap) == 24;
}

}
