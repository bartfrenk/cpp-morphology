#include <iostream>
#include <functional>

#include "image/strict.hpp"
#include "image/transforms.hpp"
#include "image/utils.hpp"
#include "filter/kernel.hpp"
#include "filter/transforms.hpp"

using std::cout;
using std::endl;
using namespace Image;

void test_filter() {
    auto base = std::make_shared<StrictImage<RGB>>(10, 10);
    base->set(1, 1, RGB(0xFF, 0x00, 0x00));
    writeImage(cout, *base);
    auto lazy = map(base, std::function<Gray(RGB)>(average));
    writeImage(cout, lazy);
    auto strict = lazy.manifest();
    writeImage(cout, strict);

    Gray data[] = {1, 0, 1,
                   1, 0, 1,
                   1, 0, 1};
    Filter::Kernel<Gray> kernel(3, 3, data, Image::Point(1, 1));
    auto result = Filter::apply(strict, kernel,
                                [](Gray p, Gray q) { return p * q; },
                                [](Gray acc, Gray p) { return (Gray) p + acc; },
                                (Gray) 0);
    writeImage(cout, result);
}

void test_io(const std::string srcname, const std::string destname) {
    auto src = std::make_shared<StrictImage<RGB>>(srcname);
    map(src, std::function<Gray(RGB)>(average)).manifest().save(destname);
}

int main(int argc, char **argv) {
    FreeImage_Initialise();
    if (argc < 2) {
        cout << "Syntax: " << argv[0] << " <input file> <output file>\n";
        return 0;
    }
    test_io(argv[1], argv[2]);
    FreeImage_DeInitialise();
    return 0;
}
