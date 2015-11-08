#ifndef IMAGE_STRICT_HPP
#define IMAGE_STRICT_HPP

#include <cstddef>
#include <vector>

namespace Image {

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

template <typename P>
StrictImage<P>::StrictImage(const size_t rows, const size_t columns)
    : mRows(rows), mColumns(columns), mPixels(rows * columns) {}

}

#endif
