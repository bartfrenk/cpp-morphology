#ifndef IMAGE_LAZY_HPP
#define IMAGE_LAZY_HPP

#include <cstddef>
#include <iostream>
#include <functional>
#include <memory>

#include "base.hpp"
#include "strict.hpp"

#include "../utils/log.hpp"
using Utils::log;

namespace Image {

template <typename Q, typename I, typename P>
class LazyImage {
public:

    using pixel_t = Q;
    using coord_t = typename I::coord_t;

    LazyImage(std::shared_ptr<I> base, const std::function<Q(P)> func);
    LazyImage(const LazyImage<Q, I, P> &&img);
    LazyImage<Q, I, P>& operator=(const LazyImage<Q, I, P> &&img);

    bool contains(const coord_t x, const coord_t y) const;
    Domain<coord_t> domain() const;
    pixel_t operator()(const coord_t x, const coord_t y) const;

    Strict<pixel_t, coord_t> manifest() const;

private:
    std::shared_ptr<I> mBase;
    std::function<Q(P)> mFunc;
};


template <typename Q, typename I, typename P>
LazyImage<Q, I, P>::LazyImage(std::shared_ptr<I> base, const std::function<Q(P)> func)
    : mBase(base), mFunc(func)
{ log << "LazyImage(std::shared_ptr<I>, const std::function<Q(P)>)\n"; };

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

template <typename Q, typename I, typename P>
bool LazyImage<Q, I, P>::contains(const coord_t x, const coord_t y) const {
    return domain().contains(Point<int>(x, y));
}

template <typename Q, typename I, typename P>
Domain<typename LazyImage<Q, I, P>::coord_t> LazyImage<Q, I, P>::domain() const {
    return mBase->domain();
}

template <typename Q, typename I, typename P>
Q LazyImage<Q, I, P>::operator()(const coord_t x, const coord_t y) const {
    return mFunc((*mBase)(x, y));
}

template <typename Q, typename I, typename P>
Strict<Q, typename I::coord_t> LazyImage<Q, I, P>::manifest() const {
    Domain<coord_t> dom = domain();
    Point<coord_t> lo = dom.lo;
    Point<coord_t> hi = dom.hi;
    Strict<Q, coord_t> img(dom);

    for (auto x = lo.x; x < hi.x; ++x)
        for (auto y = lo.y; y < hi.y; ++y) {
            img(x, y) = (*this)(x, y);
        }
    return img;
}

}

#endif
