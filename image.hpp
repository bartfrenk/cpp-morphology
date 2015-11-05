#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstddef>
#include <vector>
#include <functional>
#include <memory>
#include <iostream>

#include "point.hpp"

namespace Image {

typedef Geometry::Point<2, size_t> Point;

template <typename P>
class StrictImage {
public:
    StrictImage(const size_t rows, const size_t columns);

    size_t rows() const { return mRows; }
    size_t columns() const { return mColumns; }

    P get(const size_t r, const size_t c) const { return mPixels[toLinear(r, c)]; }
    void set(const size_t r, const size_t c, const P p) { mPixels[toLinear(r, c)] = p; }

private:
    size_t toLinear(const size_t r, const size_t c) const { return r * mColumns + c; }
    size_t mRows;
    size_t mColumns;
    // TODO: reconsider in context of LazyImage wrapper and shared resources
    std::vector<P> mPixels;
};

template <typename Image, typename P, typename Q>
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

template <typename P>
StrictImage<P>::StrictImage(const size_t rows, const size_t columns)
    : mRows(rows), mColumns(columns), mPixels(rows * columns) {}

template <typename Image, typename P, typename Q>
std::unique_ptr<StrictImage<Q>> LazyImage<Image, P, Q>::manifest() const {
    // TODO: optimize by iterating over linear pixel array
    auto strict = std::unique_ptr<StrictImage<Q>>(new StrictImage<Q>(rows(), columns()));
    for (size_t r = 0; r != rows(); ++r)
        for (size_t c = 0; c != columns(); ++c)
            strict->set(r, c, get(r, c));
    return strict;
}

template <typename Image>
void write(std::ostream& os, const Image &img) {
    for (size_t r = 0; r != img.rows(); ++r) {
        for (size_t c = 0; c != img.columns(); ++c)
            os << img.get(r, c) << " ";
        os << std::endl;
    }
}

template <typename Image, typename P, typename Q>
std::unique_ptr<LazyImage<Image, P, Q>> map(const Image &base, const std::function<Q(P)> &func) {
    return std::unique_ptr<LazyImage<Image, P, Q>>(new LazyImage<Image, P, Q>(base, func));
}

}
#endif
