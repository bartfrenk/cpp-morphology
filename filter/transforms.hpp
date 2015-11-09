#ifndef FILTER_TRANSFORMS_HPP
#define FILTER_TRANSFORMS_HPP

#include <memory>
#include <iostream>

#include "../image/strict.hpp"
#include "../image/base.hpp"

namespace Filter {

/**
 * Applies generalized filter.
 *
 * @param img the image to which to apply the filter
 * @param kernel the kernel of the filter
 * @param zipFn function that combines a pixel of the image with a pixel of the kernel
 * @param foldFn function that folds the combined results into a single pixel of type Q
 */
template <typename I, typename K, typename Z, typename F, typename P>
auto apply(const I &img, const K &ker, const F &zip, const Z &fold, const P unit)
    -> std::unique_ptr<Image::StrictImage<decltype(fold(unit, zip(img.get(0,0), ker.get(0,0))))>>
{

    using Image::StrictImage;

    Image::Box bounds = ker.box();

    size_t rows = img.rows();
    size_t columns = img.columns();

    auto result = std::unique_ptr<StrictImage<P>>(new StrictImage<P>(rows, columns));
    for (size_t img_r = 0; img_r != rows; ++img_r) {
        for (size_t img_c = 0; img_c != columns; ++img_c) {
            P value = unit;
            for (int ker_r = bounds.lo.x; ker_r <= bounds.hi.x; ++ker_r) {
                for (int ker_c = bounds.lo.y; ker_c <= bounds.hi.y; ++ker_c) {
                    if (img.contains(img_r + ker_r, img_c + ker_c)) {
                        value = fold(value, zip(img.get(img_r + ker_r, img_c + ker_c),
                                                ker.get(ker_r, ker_c)));
                    }
                }
            }
            result->set(img_r, img_c, value);
        }
    }
    return result;
}

}

#endif
