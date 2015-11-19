#ifndef IMAGE_TRANSFORMS_HPP
#define IMAGE_TRANSFORMS_HPP

#include <memory>
#include <iostream>
#include <iomanip>

#include "lazy.hpp"
#include "pixel.hpp"

#include "../utils/log.hpp"
using Utils::log;

namespace Image {

template <typename I>
void writeImage(std::ostream& os, const I &img) {
    log << "writeImage(std::ostream&, const I&)\n";
    for (size_t y = 0; y != img.height(); ++y) {
        writePixel(os, img.get(0, y));
        for (size_t x = 1; x != img.width(); ++x) {
            os << " ";
            writePixel(os, img.get(x, y));
        }
        os << std::endl;
    }
}

template <typename Q, typename I, typename P>
LazyImage<Q, I, P> map(const std::shared_ptr<I> img, const std::function<Q(P)> &func) {
    log << "map(std::shared_ptr<I>, const std::function<Q(P)>&)\n";
    auto x = LazyImage<Q, I, P>(img, func);
    return x;
}

// TODO: implement crop: I -> Box -> LazyImage

}
#endif
