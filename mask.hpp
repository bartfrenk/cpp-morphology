#ifndef MASK_HPP
#define MASK_HPP

#include "image.hpp"
#include "point.hpp"


/** Applies {@code mask} to {@code img} of offset {@code os} through function {@code fn}. */
/*template <typename P, typename Q, typename F>
Image<P>& applyMask(Image<P> &img, const Image<Q>& mask, Offset shift, const F fn) {
    P value;
    for (size_t r = 0; r != mask.rows(); ++r) {
        for (size_t c = 0; c != mask.columns(); ++c) {
            if (shift.x + r < img.rows() && shift.y + c < img.columns()) {
                value = fn(img.get(shift.x + r, shift.y + c), mask.get(r, c));
                img.set(shift.x + r, shift.y + c, value);
            }
        }
    }
    return img;
}
*/

template <typename I>
class Mask {
    Mask(const I &img, const Image::Point center);
};
// mask


#endif
