#ifndef IMAGE_BITMAP_HPP
#define IMAGE_BITMAP_HPP

#include <memory>
#include <iostream>
#include <FreeImage.h>


namespace Image {

class Bitmap {
public:
    static std::unique_ptr<Bitmap> load(const std::string fileName) {
        return std::unique_ptr<Bitmap>(new Bitmap(fileName));
    }
    static std::unique_ptr<Bitmap> create() {
        return std::unique_ptr<Bitmap>(new Bitmap(1, 1, 12));
    }
    void diagnostics(std::ostream &os);
private:
    Bitmap(const size_t width, const size_t height, int bpp);
    Bitmap(const std::string fileName);
    FIBITMAP *mBitmap;
};

Bitmap::Bitmap(const size_t width, const size_t height, int bpp) {
    mBitmap = FreeImage_Allocate(width, height, bpp);
}

Bitmap::Bitmap(const std::string fileName) {
    mBitmap = FreeImage_Load(FIF_PNG, fileName.c_str());
}

void Bitmap::diagnostics(std::ostream& os) {
    os << "Image type: " << FreeImage_GetImageType(mBitmap) << std::endl;
    os << "Dimensions: " << FreeImage_GetWidth(mBitmap) << " x "
       << FreeImage_GetHeight(mBitmap) << std::endl;
    os << "Bits per pixel: " << FreeImage_GetBPP(mBitmap) << std::endl;
    os << "Width in bytes: " << FreeImage_GetLine(mBitmap) << std::endl;
    os << "Pitch: " << FreeImage_GetPitch(mBitmap) << std::endl;
}





}

#endif
