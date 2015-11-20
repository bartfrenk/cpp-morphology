#include <iostream>
#include <functional>

#include "image/strict.hpp"
#include "image/transforms.hpp"
#include "image/utils.hpp"
#include "filter/kernel.hpp"
#include "filter/transforms.hpp"

using std::cout;
using namespace Image;

void test_freeimage() {
    auto base = std::make_shared<StrictImage<RGB>>(10, 10);
    base->set(1, 1, RGB(0xFF, 0x00, 0x00));
    writeImage(cout, *base);
    auto lazy = map(base, std::function<Gray(RGB)>(average));
    writeImage(cout, lazy);
    auto strict = lazy.manifest();
    writeImage(cout, strict);

    StrictImage<Gray> img(3, 3);
    img.set(0, 0, 1);
    img.set(1, 1, 1);
    img.set(1, 2, 1);
    writeImage(cout, img);
    auto kernel = Filter::createKernel(img, Image::Point(1, 1));
    auto result = Filter::apply(strict, kernel,
                                [](Gray p, Gray q) { return p * q + 1; },
                                [](Gray acc, Gray p) { return (Gray) p + acc; },
                                (Gray) 0);
    writeImage(cout, result);
}

int main() {
    FreeImage_Initialise();
    test_freeimage();
    FreeImage_DeInitialise();
    return 0;
}
