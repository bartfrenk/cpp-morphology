#ifndef IMAGE_STRICT_HPP
#define IMAGE_STRICT_HPP

#include <cstddef>
#include <string>
#include <FreeImage.h>

#include "base.hpp"
#include "backend.hpp"
#include "pixel.hpp"
#include "../utils/log.hpp"

namespace Image {

using format_t = FREE_IMAGE_FORMAT;
using Utils::log;

template <typename P, typename T>
class Strict : public FreeImage {
public:

    using pixel_t = P;
    using coord_t = T;

    Strict(const Domain<T> domain);
    Strict(const std::string path, const format_t format);
    Strict(const Strict<P, T> &img);
    Strict(const Strict<P, T> &&img);

    bool contains(const coord_t x, const coord_t y) const;
    Domain<coord_t> domain() const;
    pixel_t& operator()(const coord_t x, const coord_t y);
    pixel_t operator()(const coord_t x, const coord_t y) const;

    void save(const std::string path, const format_t format) const;

private:

    static constexpr size_t bytes_per_pixel = sizeof(P);

    const Domain<T> mDomain;

    static constexpr size_t to_bits(const size_t bytes);
    uint32_t index(const coord_t x, const coord_t y) const;

};

template <typename P, typename T>
Strict<P, T>::Strict(const Domain<T> domain)
    : mDomain(domain), FreeImage(width(domain), height(domain), to_bits(bytes_per_pixel)) {
    log << "Strict<RGB>::Strict(const coord_t width, const coord_t height)\n";
};

template <typename P, typename T>
Strict<P, T>::Strict(const std::string filename, const format_t format)
    : FreeImage(format, filename) {
    log << "Strict<RGB>::Strict(const std::string)\n";
};

template <typename P, typename T>
Strict<P, T>::Strict(const Strict<P, T> &img)
    : FreeImage(FreeImage_Clone(img.mPixels)) {
    log << "Strict<RGB>::Strict(const Strict<RGB>&)\n";
}

template <typename P, typename T>
Strict<P, T>::Strict(const Strict<P, T> &&img)
    : FreeImage(std::move(img)) {
    log << "Strict<RGB>::Strict(const Strict<RGB>&&)\n";
}

template <typename P, typename T>
Domain<T> Strict<P, T>::domain() const {
    return mDomain;
}

template <typename P, typename T>
bool Strict<P, T>::contains(const coord_t x, const coord_t y) const {
    return mDomain.contains(x, y);
}

template <typename P, typename T>
void Strict<P, T>::save(const std::string path, const format_t format) const {
    FreeImage::save(format, path);
}

template <typename P, typename T>
P& Strict<P, T>::operator()(const coord_t x, const coord_t y) {
    uint32_t idx = index(x, y);
    BYTE *buffer = (BYTE *) FreeImage_GetBits(mPixels);
    return (P&) buffer[idx];
}

template <typename P, typename T>
P Strict<P, T>::operator()(const coord_t x, const coord_t y) const {
    uint32_t idx = index(x, y);
    BYTE *buffer = (BYTE *) FreeImage_GetBits(mPixels);
    return P(buffer + idx);
};

template <typename P, typename T>
uint32_t Strict<P, T>::index(const coord_t x, const coord_t y) const {
    return (y - mDomain.lo.y) * mPitch + (x - mDomain.lo.x);
}

template <typename P, typename T>
constexpr size_t Strict<P, T>::to_bits(const size_t bytes) {
    return 8 * bytes;
}

}

#endif
