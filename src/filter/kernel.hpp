#ifndef FILTER_KERNEL_HPP
#define FILTER_KERNEL_HPP

#include <memory>
#include <vector>

#include "../image/utils.hpp"
using Image::coord_t;

namespace Filter {

template <typename P>
class Kernel {
public:
    using pixel_t = P;

    Kernel(const coord_t width, const coord_t height, const P pixels[], const Image::Point center) :
        mPixels(width * height), mCenter(center), mWidth(width), mHeight(height)
    {
        set(pixels);
    };

    pixel_t operator()(const coord_t x, const coord_t y) const;
    Image::Box box() const;
private:
    size_t linearIndex(const coord_t x, const coord_t y) const {
        return y * mWidth + x;
    }
    void set(const P pixels[]);

    std::vector<P> mPixels;
    const Image::Point mCenter;
    const coord_t mWidth;
    const coord_t mHeight;

};

template <typename P>
P Kernel<P>::operator()(const coord_t x, const coord_t y) const {
    return mPixels[linearIndex(mCenter.x + x, mCenter.y + y)];
}

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
