#include <iostream>
#include <functional>

#include "image.hpp"
#include "point.hpp"

using std::cout;
using namespace Image;

int main() {
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
    return 0;
}
