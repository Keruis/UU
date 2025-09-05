#ifndef NEW_ALLOCATOR_H
#define NEW_ALLOCATOR_H
#include <cstddef>
#include <new>
#include <type_traits>
#include <bits/functexcept.h>

#include "../config.h"

namespace Keruis::bits {

template <typename Tp_>
class new_allocator {
public:
    using value_type        = Tp_;
    using pointer           = Tp_*;
    using const_pointer     = const Tp_*;
    using reference         = Tp_&;
    using const_reference   = const Tp_&;
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;

    template <typename Other_>
    using rebind = new_allocator<Other_>;

    KLIB_ALWAYS_INLINE KLIB_CONSTEXPR
    new_allocator() KLIB_NOEXCEPT { }
    KLIB_ALWAYS_INLINE KLIB_CONSTEXPR
    new_allocator(const new_allocator&) KLIB_NOEXCEPT { }
    template <typename Ty1_>
    KLIB_ALWAYS_INLINE KLIB_CONSTEXPR
    new_allocator(const new_allocator<Ty1_>&) KLIB_NOEXCEPT { }

    new_allocator& operator=(const new_allocator&) = default;

    KLIB_NODISCARD
    pointer allocate(size_type n, const void* = 0) {
        static_assert(sizeof(Tp_) != 0, "cannot allocate incomplete types");

        if (KLIB_UNLIKELY(n == 0)) return nullptr;

        if (KLIB_UNLIKELY(n > max_size())) {
            if (n > (static_cast<std::size_t>(-1) / sizeof(Tp_))) {
                std::__throw_bad_array_new_length();
            }
            std::__throw_bad_alloc();
        }

        if (alignof(Tp_) > 16) {
            const auto al = static_cast<std::align_val_t>(alignof(Tp_));
            return static_cast<pointer>(operator new(n * sizeof(Tp_), al));
        }
        return static_cast<pointer>(operator new(n * sizeof(Tp_)));
    }

    void deallocate(pointer p, const size_type n) {
        if (alignof(Tp_) > 16) {
            operator delete(p, n * sizeof(Tp_), static_cast<std::align_val_t>(alignof(Tp_)));
        }
    }

    template <typename Up_>
    KLIB_ALWAYS_INLINE KLIB_CONSTEXPR
    friend bool operator==(const new_allocator&, const new_allocator<Up_>&) KLIB_NOEXCEPT {
        return true;
    }


public:
    KLIB_ALWAYS_INLINE KLIB_CONSTEXPR
    size_type max_size() KLIB_NOEXCEPT {
        return static_cast<std::size_t>(0x7fffffffffffffffLL) / sizeof(Tp_);
    }
};

}

#endif //NEW_ALLOCATOR_H
