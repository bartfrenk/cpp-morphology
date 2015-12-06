namespace Utils {

template <typename T, typename S>
T cast(const S x) {
    return static_cast<T>(x);
}

}
