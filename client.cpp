#include <iostream>
#include <functional>

#include "image/strict.hpp"
#include "image/transforms.hpp"
#include "geometry/point.hpp"
//#include "filter/kernel.hpp"
#include "filter/transforms.hpp"

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

/*
void test_filter() {
    StrictImage<bool> sourceImage(4, 4);
    StrictImage<bool> kernelImage(3, 3);
    kernelImage.set(0, 1, true);
    kernelImage.set(1, 0, true);
    kernelImage.set(1, 1, true);
    kernelImage.set(1, 2, true);
    kernelImage.set(2, 1, true);
    write(cout, sourceImage);
    write(cout, kernelImage);
    Image::Point center(1, 1);

}
*/

int main() {

    return 0;
}
