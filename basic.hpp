

template <typename P, typename Q, P (*Func)(P, Q)>
void zipWith(Image<P> &dst, const Image<Q>& src, const Vector<2, size_t> offset,
             const Q value, const Func fn) {
}
