#ifndef GEOMETRY_RECTANGLE_HPP
#define GEOMETRY_RECTANGLE_HPP

#include <cstddef>

#include "point.hpp"

namespace Geometry {

// Rectangle with lower corner <lo> and upper corner <hi>
template <const size_t dim, typename T>
struct Rectangle {
    Rectangle(const Point<dim, T> lo, const Point<dim, T> hi) : lo(lo), hi(hi) {};
    const Point<dim, T> lo;
    const Point<dim, T> hi;
};

template <>
struct Rectangle<2, int> {
    Rectangle(const Point<2, int> lo, const Point<2, int> hi) : lo(lo), hi(hi) {};
    Rectangle(const Point<2, size_t> center, const size_t rows, const size_t columns) :
        Rectangle(Point<2, int>(-center.x, -center.y),
                  Point<2, int>(rows - center.x - 1, columns - center.y - 1)) {};
    const Point<2, int> lo;
    const Point<2, int> hi;
};

}

#endif
