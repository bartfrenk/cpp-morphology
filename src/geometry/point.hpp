#ifndef POINT_HPP
#define POINT_HPP

#include <cstdint>

namespace Geometry {

template <const uint32_t dim, typename T>
struct Point {
};

template <typename T>
struct Point<2, T> {
    Point(const T x, const T y) : x(x), y(y) {};
    const T x;
    const T y;
    bool operator<=(const Point<2, T> &p) const;
};

template <typename T>
bool Point<2, T>::operator<=(const Point<2, T> &p) const {
    return (*this).x <= p.x && (*this).y <= p.y;
}

template <typename T>
Point<2, T> operator+(const Point<2, T> &p, const Point<2, T> &q) {
    return Point<2, T>(p.x + q.x, p.y + q.y);
}

}

#endif
