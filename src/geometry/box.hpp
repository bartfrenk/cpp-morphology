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

template <const uint32_t dim, typename T>
bool Box<dim, T>::contains(const Point<dim, T> &p) const {
    return lo <= p && p <= hi;
}

}

#endif
