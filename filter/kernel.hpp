#ifndef FILTER_KERNEL_HPP
#define FILTER_KERNEL_HPP

#include <memory>

#include "../image/utils.hpp"

namespace Filter {

template <typename I>
class Kernel {
public:
    using pixel_t = typename I::pixel_t;

    Kernel(const I &kernel, const Image::Point center) : mKernel(kernel), mCenter(center) {};
    pixel_t get(const int x, const int y) const {
        return mKernel.get(mCenter.x + x, mCenter.y + y);
    }
    Image::Box box() const {
        return Image::Box(mCenter, mKernel.height(), mKernel.width());
    }
private:
    // TODO: change this to the appropriate vector type,
    // since we do not need save and load functionality for
    // kernels.
    const I &mKernel;
    const Image::Point mCenter;

};

template <typename I>
Kernel<I> createKernel(const I &img, const Image::Point center) {
    return Kernel<I>(img, center);
};

}

#endif
