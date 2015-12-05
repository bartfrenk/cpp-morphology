
#include "image/strict.hpp"
#include "image/pixel.hpp"

using Image::Intensity;
using Image::Point;
using Image::Domain;

int main() {
    Domain<int> domain(Point<int>(0, 0), Point<int>(10, 10));
    Image::Strict<Intensity, int> img(domain);
}
