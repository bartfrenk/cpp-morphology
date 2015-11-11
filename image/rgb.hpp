#ifndef IMAGE_RGB_HPP
#define IMAGE_RGB_HPP

#include <memory>
#include <iostream>
#include <FreeImage.h>

typedef unsigned char byte;

namespace Image {

class ImageRGB {
public:

    struct Pixel {
        Pixel(byte red, byte green, byte blue) : red(red), green(green), blue(blue) {};
        byte red;
        byte green;
        byte blue;
    };

    static std::unique_ptr<ImageRGB> load(const std::string fileName) {
        return std::unique_ptr<ImageRGB>(new ImageRGB(fileName));
    }
    static std::unique_ptr<ImageRGB> create(const size_t width, const size_t height) {
        return std::unique_ptr<ImageRGB>(new ImageRGB(width, height));
    }
    ~ImageRGB() {
        FreeImage_Unload(mBitmap);
    }
    size_t width() { return mWidth; }
    size_t height() { return mHeight; }

    Pixel get(const size_t x, const size_t y) const {
        return Pixel(0, 0, 0);
        // TODO: implement this
    }
private:
    ImageRGB(const size_t width, const size_t height);
    ImageRGB(const std::string fileName);
    void init();
    bool isValid();
    FIBITMAP * mBitmap;
    unsigned mPitch;
    unsigned mWidth;
    unsigned mHeight;
};


}

#endif
