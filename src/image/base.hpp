#ifndef IMAGE_BASE_HPP
#define IMAGE_BASE_HPP

#include <FreeImage.h>
#include <string>

namespace Image {

class BaseImage {
public:
    size_t width() const { return mWidth; }
    size_t height() const { return mHeight; }
    bool contains(const int x, const int y) const {
        return 0 <= x && x < (int) mWidth && 0 <= y && y < (int) mHeight;
    }
    virtual ~BaseImage();
    BaseImage& operator=(const BaseImage &img);
protected:
    BaseImage(const FREE_IMAGE_FORMAT fif, const std::string filename);
    BaseImage(const size_t width, const size_t height, const int bpp);
    BaseImage(FIBITMAP * const pixels);
    BaseImage(const BaseImage &&img);

    void init();
    FIBITMAP *mPixels;
    unsigned int mPitch;
    unsigned int mWidth;
    unsigned int mHeight;
};

}
#endif
