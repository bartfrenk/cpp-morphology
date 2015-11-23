#include "pixel.hpp"

#include <iomanip>

namespace Image {

std::ostream& operator<<(std::ostream& os, const RGB& pixel) {
    // TODO: avoid changing the format flag
    os.setf(std::ios::hex, std::ios::basefield);
    os << "#";
    os << std::setfill('0') << std::setw(2) << (int) pixel.red;
    os << std::setfill('0') << std::setw(2) << (int) pixel.green;
    os << std::setfill('0') << std::setw(2) << (int) pixel.blue;
    os.unsetf(std::ios::basefield);
    return os;
}

template <>
void writePixel<Gray>(std::ostream &os, const Gray &pixel) {
    os.setf(std::ios::hex, std::ios::basefield);
    os << std::setfill('0') << std::setw(2) << (int) pixel;
}

Gray average(const RGB& rgb) {
    return (rgb.red + rgb.green + rgb.blue) / 3;
}

}
