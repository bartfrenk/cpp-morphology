#ifndef IMAGE_UTILS_HPP
#define IMAGE_UTILS_HPP

#include <memory>
#include <iostream>
#include <iomanip>

#include "pixel.hpp"
#include "mapped.hpp"

namespace Image {

template <typename I>
void writeImage(std::ostream& os, const I &img) {
    using coord_t = typename I::coord_t;
    coord_t m = img.domain().hi.x;
    coord_t n = img.domain().hi.y;

    for (auto y = img.domain().lo.y; y != n; ++y) {
        auto x = img.domain().lo.x;
        os << toString(img(x, y));
        for (++x; x != m; ++x) {
            os << " " << toString(img(x, y));
        }
        os << std::endl;
    }
}

template <typename Q, typename I, typename P>
Mapped<Q, I, P> map(const std::shared_ptr<I> img, const std::function<Q(P)> &func) {
    return Mapped<Q, I, P>(img, func);
}

}
#endif
