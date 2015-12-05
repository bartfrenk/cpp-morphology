#ifndef POINT_HPP
#define POINT_HPP

#include <cstdint>

namespace Geometry {

template <const uint32_t dim, typename T>
struct Point {
    Point(const T x, const T y) : x(x), y(y) {};
    const T x;
    const T y;
    bool operator<=(const Point<dim, T> &p) const;
};

template <const uint32_t dim, typename T>
bool Point<dim, T>::operator<=(const Point<dim, T> &p) const {
    return (*this).x <= p.x && (*this).y <= p.y;
}

}

#endif
