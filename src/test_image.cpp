#include <iostream>
#include <memory>

#include "image/strict.hpp"
#include "image/pixel.hpp"
#include "image/utils.hpp"

using namespace Image;

using std::cout;

void test_strict_basic() {
    Domain<int> domain(Point<int>(2, 2), Point<int>(10, 10));
    Strict<Intensity, int> img(domain);
    img(3, 4) = (Intensity) 0xFF;
    writeImage(cout, img);
}

void test_strict_io(const std::string in_path, const std::string out_path) {
    auto input = std::make_shared<Strict<RGB, uint32_t>>(in_path, Format::PNG);
    auto output = map(input, std::function<Intensity(RGB)>(average)).manifest();
    output.save(out_path, Format::BMP);
}

int main(const int argc, char** argv) {
    if (argc < 3) {
        cout << "Syntax: " << argv[0] << " <input> <output>\n";
        return 0;
    }

    test_strict_io(std::string(argv[1]), std::string(argv[2]));
    return 0;
}
