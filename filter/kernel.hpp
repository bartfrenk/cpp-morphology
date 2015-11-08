#ifndef FILTER_KERNEL_HPP
#define FILTER_KERNEL_HPP

#include <memory>

#include "../image/base.hpp"

namespace Filter {

template <typename I>
class Kernel {
public:
    typedef typename I::pixel_type pixel_type;

    Kernel(const I &kernel, const Image::Point center) : mKernel(kernel), mCenter(center) {};
    typename I::pixel_type get(const int row, const int column) const {

        return mKernel.get(mCenter.x + row, mCenter.y + column);
    }
    Image::Box box() const {
        return Image::Box(mCenter, mKernel.rows(), mKernel.columns());
    }
private:
    const I &mKernel;
    const Image::Point mCenter;

};

// TODO: make this instantiate with I type constructor LazyImage
template <typename I>
std::unique_ptr<Kernel<I>> createKernel(const I &kernel, const Image::Point center) {
    return std::unique_ptr<Kernel<I>>(new Kernel<I>(kernel, center));
};

}

#endif
