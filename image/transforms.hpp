#ifndef IMAGE_TRANSFORMS_HPP
#define IMAGE_TRANSFORMS_HPP

#include <memory>
#include <iostream>

#include "lazy.hpp"

namespace Image {

template <typename I>
void write(std::ostream& os, const I &img) {
    for (size_t y = 0; y != img.height(); ++y) {
        for (size_t x = 0; x != img.width(); ++x)
            os << img.get(x, y) << " ";
        os << std::endl;
    }
}

template <typename Q, typename I, typename P>
std::unique_ptr<LazyImage<Q, I, P>> map(const I &base, const std::function<Q(P)> &func) {
    return std::unique_ptr<LazyImage<Q, I, P>>(new LazyImage<Q, I, P>(base, func));
}

}
#endif
