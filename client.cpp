#include <iostream>
#include <functional>

#include "image/strict.hpp"
#include "image/transforms.hpp"
#include "geometry/point.hpp"
#include "filter/kernel.hpp"
#include "filter/transforms.hpp"
#include "image/bitmap.hpp"

using std::cout;
using namespace Image;



void test_base() {
    StrictImage<bool> img(4, 4);
    write(cout, img);
    cout << std::endl;

    std::function<bool(bool)> negate = [](bool p){
        cout << "*";
        return !p;
    };
    auto neg = map(img, negate);

    write(cout, *neg);
    cout << std::endl;

    write(cout, *map(*neg, negate));
    cout << std::endl;
}

void test_bitmap(const std::string fileName) {
    auto bitmap = Bitmap::load(fileName);
    bitmap->diagnostics(cout);
}

void test_filter() {
    StrictImage<bool> sourceImage(4, 4);
    sourceImage.set(1, 1, true);
    sourceImage.set(1, 2, true);
    StrictImage<bool> kernelImage(3, 3);
    kernelImage.set(0, 1, true);
    kernelImage.set(1, 0, true);
    kernelImage.set(1, 1, true);
    kernelImage.set(1, 2, true);
    kernelImage.set(2, 1, true);
    write(cout, sourceImage);
    write(cout, kernelImage);
    Image::Point center(1, 1);
    auto kernel = Filter::createKernel(kernelImage, center);
    auto result = Filter::apply(sourceImage, *kernel,
                                [](bool p, bool q) { return p && q; },
                                [](bool acc, bool p) { return p || acc; },
                                false);
    write(cout, *result);
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        test_bitmap(argv[1]);
    }
    return 0;
}
