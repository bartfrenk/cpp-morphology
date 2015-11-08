#ifndef FILTER_TRANSFORMS_HPP
#define FILTER_TRANSFORMS_HPP

#include <memory>

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
template <typename I, typename K, typename Q, typename F, typename G>
std::unique_ptr<Image::StrictImage<Q>> apply(const I& img, const K &kernel,
                                             const F &zipFn, const G &foldFn,
                                             const Q unit) {

    using Image::StrictImage;

    Image::Box bounds = kernel.box();
    size_t rows = img.rows();
    size_t columns = img.columns();

    auto result = std::unique_ptr<StrictImage<Q>>(new StrictImage<Q>(rows, columns));
    for (size_t img_r = 0; img_r != rows; ++img_r) {
        for (size_t img_c = 0; img_c != columns; ++img_c) {
            Q value = unit;
            for (int ker_r = bounds.lo.x; ker_r <= bounds.hi.x; ++ker_r) {
                for (int ker_c = bounds.lo.y; ker_c <= bounds.hi.y; ++ker_c) {
                    if (img.contains(img_r + ker_r, img_c + ker_c)) {
                        value = foldFn(value, zipFn(img.get(img_r + ker_r, img_c + ker_c),
                                                    kernel.get(ker_r, ker_c)));
                    }
                }
            }
            result->set(img_r, img_c, value);
        }
    }

}

}

#endif
