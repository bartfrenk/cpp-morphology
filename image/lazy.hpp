#ifndef IMAGE_LAZY_HPP
#define IMAGE_LAZY_HPP

#include <cstddef>
#include <functional>
#include <memory>

#include "strict.hpp"

namespace Image {

template <typename Q, typename I, typename P>
class LazyImage {
public:
    typedef Q pixel_type;

    LazyImage(const I &base, const std::function<Q(P)> &func) : mBase(base), mFunc(func) {}

    // TODO: allow for manifesting cropped image
    std::unique_ptr<StrictImage<Q>> manifest() const;

    size_t height() const { return mBase.height(); }
    size_t width() const { return mBase.width(); }

    Q get(const size_t r, const size_t c) const { return mFunc(mBase.get(r, c)); }
private:
    const I &mBase;
    const std::function<Q(P)>& mFunc;
};

template <typename Q, typename I, typename P>
std::unique_ptr<StrictImage<Q>> LazyImage<Q, I, P>::manifest() const {
    // TODO: optimize by iterating over linear pixel array
    auto strict = std::unique_ptr<StrictImage<Q>>(new StrictImage<Q>(height(), width()));
    for (size_t r = 0; r != height(); ++r)
        for (size_t c = 0; c != width(); ++c)
            strict->set(r, c, get(r, c));
    return strict;
}

}

#endif
