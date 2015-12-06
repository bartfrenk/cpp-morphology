#ifndef IMAGE_BASE_HPP
#define IMAGE_BASE_HPP

#include <cstddef>
#include "../geometry/point.hpp"
#include "../geometry/box.hpp"

namespace Image {

template <typename T>
using Point = Geometry::Point<2, T>;

template <typename T>
using Domain = Geometry::Box<2, T>;

template <typename T>
constexpr T width(const Domain<T> &domain) {
    return domain.hi.x - domain.lo.x;
}

template <typename T>
constexpr T height(const Domain<T> &domain) {
    return domain.hi.y - domain.lo.y;
}


}

#endif
