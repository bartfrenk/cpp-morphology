#ifndef IMAGE_TRANSFORMS_HPP
#define IMAGE_TRANSFORMS_HPP

#include <memory>
#include <iostream>

#include "lazy.hpp"

namespace Image {

template <typename Image>
void write(std::ostream& os, const Image &img) {
    for (size_t r = 0; r != img.rows(); ++r) {
        for (size_t c = 0; c != img.columns(); ++c)
            os << img.get(r, c) << " ";
        os << std::endl;
    }
}

/*
template <typename Image, typename P, typename Q>
std::unique_ptr<LazyImage<Image, P, Q>> map(const Image &base, const std::function<Q(P)> &func) {
    return std::unique_ptr<LazyImage<Image, P, Q>>(new LazyImage<Image, P, Q>(base, func));
}
*/


template <template <typename P> class I, typename P, typename Q>
std::unique_ptr<LazyImage<Q, I<P>, P>> map(const I<P> &base, const std::function<Q(P)> &func) {
    return std::unique_ptr<LazyImage<Q, I<P>, P>>(new LazyImage<Q, I<P>, P>(base, func));
}
}
#endif