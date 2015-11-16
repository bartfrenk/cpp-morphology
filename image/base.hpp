#ifndef IMAGE_BASE_HPP
#define IMAGE_BASE_HPP

#include <FreeImage.h>
#include <string>

namespace Image {

class BaseImage {
public:
    size_t width() const { return mWidth; }
    size_t height() const { return mHeight; }
    virtual ~BaseImage();
    BaseImage& operator=(const BaseImage &img);
protected:
    BaseImage(const FREE_IMAGE_FORMAT fif, const std::string filename);
    BaseImage(const size_t width, const size_t height, const int bpp);
    BaseImage(FIBITMAP * const pixels);
    void init();
    FIBITMAP *mPixels;
    unsigned int mPitch;
    unsigned int mWidth;
    unsigned int mHeight;
};

}
#endif
