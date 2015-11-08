#ifndef POINT_HPP
#define POINT_HPP

#include <cstddef>

namespace Geometry {

template <const size_t dim, typename T>
struct Point {
    Point(const T x, const T y) : x(x), y(y) {};
    const T x;
    const T y;
};

}

#endif
