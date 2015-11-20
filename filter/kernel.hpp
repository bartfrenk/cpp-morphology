#ifndef FILTER_KERNEL_HPP
#define FILTER_KERNEL_HPP

#include <memory>
#include <vector>

#include "../image/utils.hpp"

namespace Filter {

template <typename P>
class Kernel {
public:
    using pixel_t = P;

    Kernel(const size_t width, const size_t height, const P pixels[], const Image::Point center) :
        mPixels(width * height), mCenter(center), mWidth(width), mHeight(height)
    {
        set(pixels);
    };

    pixel_t get(const int x, const int y) const {
        return mPixels[linearIndex(mCenter.x + x, mCenter.y + y)];
    }


    Image::Box box() const;
private:
    size_t linearIndex(const size_t x, const size_t y) const {
        return y * mWidth + x;
    }
    void set(const P pixels[]);

    std::vector<P> mPixels;
    const Image::Point mCenter;
    const size_t mWidth;
    const size_t mHeight;

};

template <typename P>
Image::Box Kernel<P>::box() const {
    return Image::Box(mCenter, mHeight, mWidth);
}

template <typename P>
void Kernel<P>::set(const P pixels[]) {
    size_t n = mWidth * mHeight;
    for (size_t i = 0; i < n; ++i) {
        mPixels[i] = pixels[i];
    }
}

}

#endif
