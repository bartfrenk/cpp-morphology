#ifndef GEOMETRY_RECTANGLE_HPP
#define GEOMETRY_RECTANGLE_HPP

#include <cstdint>

#include "point.hpp"

namespace Geometry {

// Rectangle with lower corner <lo> and upper corner <hi>
template <const uint32_t dim, typename T>
struct Box {
    using coord_t = T;
    Box(const Point<dim, T> lo, const Point<dim, T> hi) : lo(lo), hi(hi) {};
    const Point<dim, T> lo;
    const Point<dim, T> hi;
    bool contains(const Point<dim, T>& p) const;
};

template <typename T>
struct Box<2, T> {
    using coord_t = T;
    Box(const Point<2, T> lo, const Point<2, T> hi) : lo(lo), hi(hi) {};
    Box(const uint32_t width, const uint32_t height, const Point<2, T> &lo);
    const Point<2, T> lo;
    const Point<2, T> hi;
    bool contains(const Point<2, T>& p) const;
    T width() const;
    T height() const;
};

template <const uint32_t dim, typename T>
bool Box<dim, T>::contains(const Point<dim, T> &p) const {
    return lo <= p && p <= hi;
}

template <typename T>
Box<2, T>::Box(const uint32_t width, const uint32_t height, const Point<2, T> &lo)
    : lo(lo), hi(lo + Point<2, T>(width, height)) {};

template <typename T>
bool Box<2, T>::contains(const Point<2, T> &p) const {
    return lo <= p && p <= hi;
}

template <typename T>
T Box<2, T>::width() const {
    return hi.x - lo.x;
}

template <typename T>
T Box<2, T>::height() const {
    return hi.y - lo.y;
}

}

#endif
