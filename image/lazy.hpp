#ifndef IMAGE_LAZY_HPP
#define IMAGE_LAZY_HPP

#include <cstddef>
#include <functional>
#include <memory>

#include "strict.hpp"

namespace Image {

template <typename Q, typename Image, typename P>
class LazyImage {
public:
    LazyImage(const Image &base, const std::function<Q(P)> &func) : mBase(base), mFunc(func) {}

    // TODO: allow for manifesting cropped image
    std::unique_ptr<StrictImage<Q>> manifest() const;

    size_t rows() const { return mBase.rows(); }
    size_t columns() const { return mBase.columns(); }

    Q get(const size_t r, const size_t c) const { return mFunc(mBase.get(r, c)); }
private:
    const Image &mBase;
    const std::function<Q(P)>& mFunc;
};

template <typename Q, typename Image, typename P>
std::unique_ptr<StrictImage<Q>> LazyImage<Q, Image, P>::manifest() const {
    // TODO: optimize by iterating over linear pixel array
    auto strict = std::unique_ptr<StrictImage<Q>>(new StrictImage<Q>(rows(), columns()));
    for (size_t r = 0; r != rows(); ++r)
        for (size_t c = 0; c != columns(); ++c)
            strict->set(r, c, get(r, c));
    return strict;
}

}

#endif
