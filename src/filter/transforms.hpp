#ifndef FILTER_TRANSFORMS_HPP
#define FILTER_TRANSFORMS_HPP

#include <memory>
#include <iostream>

#include "../image/strict.hpp"
#include "../image/pixel.hpp"
#include "../utils/misc.hpp"

namespace Filter {

/**
 * Applies generalized filter.
 *
 * @param img the image to which to apply the filter
 * @param kernel the kernel of the filter
 * @param zip function that combines a pixel of the image with a pixel of the kernel
 * @param fold function that folds the combined results into a single pixel of type Q
 */
template <typename I, typename K, typename Z, typename F, typename P, typename Q>
Image::Strict<Q, typename I::coord_t> filter(const I &img, const K &ker, const Z &zip,
                                             const F &fold, Q (*round)(P), const P unit)
{
    // TODO: use compile time asserts to ensure type safety

    using ker_coord_t = typename K::coord_t;
    using img_coord_t = typename I::coord_t;

    Image::Domain<img_coord_t> img_domain = img.domain();
    img_coord_t img_m = img_domain.hi.x;
    img_coord_t img_n = img_domain.hi.y;

    Image::Domain<ker_coord_t> ker_domain = ker.domain();
    ker_coord_t ker_m = ker_domain.hi.x;
    ker_coord_t ker_n = ker_domain.hi.y;

    Image::Strict<Q, img_coord_t> result(img_domain);
    for (auto img_x = img_domain.lo.x; img_x != img_m; ++img_x) {
        for (auto img_y = img.domain.lo.y; img_y != img_n; ++img_y) {
            P value = unit;

            for (auto ker_x = ker_domain.lo.x; ker_x != ker_m; ++ker_x) {
                for (auto ker_y = ker_domain.lo.y; ker_y <= ker_n; ++ker_y) {
                    if (img.contains(img_x + ker_x, img_y + ker_y)) {
                        value = fold(value, zip(img(img_x + ker_x, img_y + ker_y),
                                                ker(ker_x, ker_y)));
                    }
                }
            }

            result(img_x, img_y) = round(value);
        }
    }
    return result;
}


/// Simple baseline implementation of linear image filtering. Quite slow!
template <typename I, template <typename P> class K>
Image::Strict<Image::Intensity, typename I::coord_t> linear(const I &img, const K<double> &ker) {
    auto product = [](double p, double q) { return p * q; };
    auto sum = [](double acc, double p) { return acc + p; };
    return apply(img, ker, product, sum, Utils::cast<Image::Intensity, double>, 0.0);
}

}

#endif
