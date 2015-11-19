#ifndef IMAGE_LAZY_HPP
#define IMAGE_LAZY_HPP

#include <cstddef>
#include <iostream>
#include <functional>
#include <memory>

#include "strict.hpp"

#include "../utils/log.hpp"
using Utils::log;

namespace Image {

template <typename Q, typename I, typename P>
class LazyImage {
public:
    typedef Q pixel_type;

    LazyImage(std::shared_ptr<I> base, const std::function<Q(P)> func)
        : mBase(base), mFunc(func)
    { log << "LazyImage(std::shared_ptr<I>, const std::function<Q(P)>)\n"; };

    LazyImage(const LazyImage<Q, I, P> &&img);
    LazyImage<Q, I, P>& operator=(const LazyImage<Q, I, P> &&img);

    // TODO: allow for manifesting cropped image
    StrictImage<Q>&& manifest() const;

    size_t height() const { return mBase->height(); }
    size_t width() const { return mBase->width(); }

    Q get(const size_t x, const size_t y) const { return mFunc(mBase->get(x, y)); }

private:
    std::shared_ptr<I> mBase;
    std::function<Q(P)> mFunc;
};

template <typename Q, typename I, typename P>
StrictImage<Q>&& LazyImage<Q, I, P>::manifest() const {
    StrictImage<Q> strict(height(), width());
    // TODO: optimize by iterating over linear pixel array
    for (size_t x = 0; x != height(); ++x)
        for (size_t y = 0; y != width(); ++y)
            strict.set(x, y, get(x, y));
    return strict;
}

template <typename Q, typename I, typename P>
LazyImage<Q, I, P>::LazyImage(const LazyImage<Q, I, P> &&img)
    : mBase(std::move(img.mBase)), mFunc(img.mFunc)
{ log << "LazyImage(const LazyImage&&)\n"; };

template <typename Q, typename I, typename P>
LazyImage<Q, I, P>& LazyImage<Q, I, P>::operator=(const LazyImage<Q, I, P> &&img) {
    log << "LazyImage::operator=(const LazyImage&&)\n";
    mBase = std::move(img.mBase);
    mFunc = img.mFunc;
    return *this;
}
}

#endif
