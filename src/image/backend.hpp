#ifndef IMAGE_BACKEND_HPP
#define IMAGE_BACKEND_HPP

#include <FreeImage.h>
#include <string>

namespace Image {

class FreeImage {
public:
    bool contains(const int x, const int y) const {
        return 0 <= x && x < (int) mWidth && 0 <= y && y < (int) mHeight;
    }
    virtual ~FreeImage();
    FreeImage& operator=(const FreeImage &img);
protected:
    FreeImage(const FREE_IMAGE_FORMAT fif, const std::string filename);
    FreeImage(const size_t width, const size_t height, const int bpp);
    FreeImage(FIBITMAP * const pixels);
    FreeImage(const FreeImage &&img);

    void init();
    void save(const FREE_IMAGE_FORMAT fif, const std::string filename) const;

    uint32_t width() const;
    uint32_t height() const;

    FIBITMAP *mPixels;
    unsigned int mPitch;
    unsigned int mWidth;
    unsigned int mHeight;
};

}
#endif
