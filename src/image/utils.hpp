#ifndef IMAGE_TRANSFORMS_HPP
#define IMAGE_TRANSFORMS_HPP

#include <memory>
#include <iostream>
#include <iomanip>

#include "lazy.hpp"
#include "pixel.hpp"

namespace Image {

template <typename I>
void writeImage(std::ostream& os, const I &img) {
    for (auto y = img.domain().lo.y; y != img.domain().hi.y; ++y) {
        writePixel(os, img(0, y));
        for (auto x = img.domain().lo.x + 1; x != img.domain().hi.x; ++x) {
            os << " ";
            writePixel(os, img(x, y));
        }
        os << std::endl;
    }
}

template <typename Q, typename I, typename P>
LazyImage<Q, I, P> map(const std::shared_ptr<I> img, const std::function<Q(P)> &func) {
    return LazyImage<Q, I, P>(img, func);
}

// TODO: implement crop: I -> Box -> LazyImage

}
#endif
