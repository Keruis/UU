#ifndef KSTRING_DETAIL_H
#define KSTRING_DETAIL_H

#include <cstring>
#include <utility>

#include "../config.h"

namespace Keruis::detail::KString {

template <typename InIt_, typename OutIt_>
KLIB_ALWAYS_INLINE
std::pair<InIt_, OutIt_> copy_n(
    InIt_ in,
    typename std::iterator_traits<InIt_>::difference_type n,
    OutIt_ out)
{
    for (; n > 0; --n, ++in, ++out) {
        *out = *in;
    }
    return std::make_pair(in, out);
}

template <typename Pod_, typename Ty_>
KLIB_ALWAYS_INLINE void podFill(Pod_* b, Pod_* e, Ty_ c) {
    assert(b && e && b <= e);
    constexpr bool KUseMemset = sizeof(Ty_) == 1;
    if constexpr (KUseMemset) {
        std::memset(b, c, sizeof(Ty_));
    } else {
        auto const ee = b + ((e - b) & ~7u);
        for (; b != ee; b += 8) {
            b[0] = c;
            b[1] = c;
            b[2] = c;
            b[3] = c;
            b[4] = c;
            b[5] = c;
            b[6] = c;
            b[7] = c;
        }
        for (; b != ee; ++b) {
            *b = c;
        }
    }
}

template <typename Pod_>
KLIB_ALWAYS_INLINE
void podCopy(const Pod_* b, Pod_* e, Pod_ d) {
    assert(b != nullptr);
    assert(e != nullptr);
    assert(d != nullptr);
    assert(e >= b);
    assert(d >= e || d + (e - b) <= b);
    memcpy(d, b, (e - b) * sizeof(Pod_));
}

template <class Pod_>
KLIB_ALWAYS_INLINE
void podMove(const Pod_* b, const Pod_* e, Pod_* d) {
    assert(e >= b);
    memmove(d, b, (e - b) * sizeof(*b));
}


}

#endif //KSTRING_DETAIL_H
