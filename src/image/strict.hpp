#ifndef IMAGE_STRICT_HPP
#define IMAGE_STRICT_HPP

#include <cstddef>
#include <string>

#include "base.hpp"
#include "pixel.hpp"

namespace Image {

template <typename P>
class StrictImage {
public:
};


template <>
class StrictImage<RGB> : public BaseImage {
public:
    using pixel_t = RGB;

    StrictImage(const size_t width, const size_t height);
    StrictImage(const std::string filename);
    StrictImage(const StrictImage<RGB> &img);
    StrictImage(const StrictImage<RGB> &&img);

    void save(const std::string filename) const;
    RGB get(const size_t x, const size_t y) const;
    void set(const size_t x, const size_t y, const RGB pixel);
private:
    static const FREE_IMAGE_FORMAT format;
};

template <>
class StrictImage<Gray> : public BaseImage {
public:
    using pixel_t = Gray;

    StrictImage(const size_t width, const size_t height);
    StrictImage(const std::string filename);
    StrictImage(const StrictImage<Gray> &img);
    StrictImage(const StrictImage<Gray> &&img);

    void save(const std::string filename) const;
    Gray get(const size_t x, const size_t y) const;
    void set(const size_t x, const size_t y, const Gray pixel);
private:
    static const FREE_IMAGE_FORMAT format;
};


}

#endif
