#ifndef FILTER_KERNEL_HPP
#define FILTER_KERNEL_HPP

#include <memory>

#include "../image/base.hpp"

namespace Filter {

template <typename I, typename P>
class Kernel {
    Kernel(const I &kernel, const Image::Point center) : mKernel(kernel), mCenter(center) {};
    P get(const int row, const int column) {
        return mKernel.get(mCenter.x + row, mCenter.y + column);
    }
    Image::Box box() {
        return Box(mCenter, mKernel.rows(), mKernel.columns());
    }
private:
    const I &mKernel;
    const Image::Point mCenter;

};

template <typename P>
template <typename I>
std::unique_ptr<Kernel<I, P>> createKernel(const I &kernel, const Image::Point center) {
    return std::unique_ptr<Kernel<I, P>>(new Kernel<I, P>(kernel, center));
};

}

#endif
