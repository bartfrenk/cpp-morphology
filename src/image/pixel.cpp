#include "pixel.hpp"

#include <iomanip>
#include <sstream>

namespace Image {

std::string toString(const RGB pixel) {
    std::stringstream ss;
    ss << std::hex << "#";
    ss << std::setfill('0') << std::setw(2) << (int) pixel.red;
    ss << std::setfill('0') << std::setw(2) << (int) pixel.green;
    ss << std::setfill('0') << std::setw(2) << (int) pixel.blue;
    return ss.str();
}

std::string toString(const Intensity pixel) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0') << std::setw(2) << (int) pixel;
    return ss.str();
}

Intensity average(const RGB& rgb) {
    return (rgb.red + rgb.green + rgb.blue) / 3;
}

}
