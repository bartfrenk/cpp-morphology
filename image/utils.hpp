#ifndef IMAGE_BASE_HPP
#define IMAGE_BASE_HPP

#include "../geometry/point.hpp"
#include "../geometry/rectangle.hpp"

namespace Image {

typedef Geometry::Point<2, size_t> Point;

typedef Geometry::Rectangle<2, int> Box;

}

#endif
