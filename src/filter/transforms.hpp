#ifndef FILTER_TRANSFORMS_HPP
#define FILTER_TRANSFORMS_HPP

#include <memory>
#include <iostream>

#include "../image/strict.hpp"
#include "../image/utils.hpp"

namespace Filter {

/**
 * Applies generalized filter.
 *
 * @param img the image to which to apply the filter
 * @param kernel the kernel of the filter
 * @param zip function that combines a pixel of the image with a pixel of the kernel
 * @param fold function that folds the combined results into a single pixel of type Q
 */
template <typename I, typename K, typename Z, typename F, typename P>
Image::StrictImage<P> apply(const I &img, const K &ker, const Z &zip, const F &fold, const P unit)
{
    Image::Box bounds = ker.box();

    size_t width = img.width();
    size_t height = img.height();

    Image::StrictImage<P> result(width, height);
    for (size_t img_x = 0; img_x != width; ++img_x) {
        for (size_t img_y = 0; img_y != height; ++img_y) {
            P value = unit;
            for (int ker_x = bounds.lo.x; ker_x <= bounds.hi.x; ++ker_x) {
                for (int ker_y = bounds.lo.y; ker_y <= bounds.hi.y; ++ker_y) {
                    if (img.contains(img_x + ker_x, img_y + ker_y)) {
                        value = fold(value, zip(img.get(img_x + ker_x, img_y + ker_y),
                                                ker.get(ker_x, ker_y)));
                    }
                }
            }
            result.set(img_x, img_y, value);
        }
    }
    return result;
}

}

#endif
