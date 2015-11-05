#include <cstddef>

template <typename Pixel>
class Image {
public:
    Image(const size_t rows, const size_t columns);
    Pixel& at(const size_t r, const size_t c) {
        return mPixels[r * mColumns + c];
    }
    size_t rows() { return mRows; }
    size_t columns() { return mColumns; }
private:
    size_t mRows;
    size_t mColumns;
    Pixel mPixels[];
};

template <typename Pixel>
Image<Pixel>::Image(const size_t rows, const size_t columns)
    : mRows(rows), mColumns(columns)
{
    mPixels = new Pixel[rows * columns];
}
