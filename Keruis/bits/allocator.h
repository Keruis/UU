#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "new_allocator.h"

namespace Keruis {

template <typename Tp_>
using allocator_base = bits::new_allocator<Tp_>;

template <typename Tp_>
class allocator : public allocator_base<Tp_> {
public:
    using value_type = Tp_;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    KLIB_ALWAYS_INLINE KLIB_CONSTEXPR
    allocator() KLIB_NOEXCEPT { }
    KLIB_ALWAYS_INLINE KLIB_CONSTEXPR
    allocator(const allocator& a) KLIB_NOEXCEPT : allocator_base<Tp_>(a) { }
    template <typename Tp1_>
    KLIB_ALWAYS_INLINE KLIB_CONSTEXPR
    allocator(const allocator<Tp1_>&) KLIB_NOEXCEPT { }
    KLIB_ALWAYS_INLINE KLIB_CONSTEXPR
    ~allocator() KLIB_NOEXCEPT { }
    allocator& operator=(const allocator&) = default;
    KLIB_ALWAYS_INLINE KLIB_NODISCARD KLIB_CONSTEXPR
    Tp_* allocate(std::size_t n) {
        if (std::is_constant_evaluated()) {
            if (__builtin_mul_overflow(n, sizeof(Tp_), &n)) {
                std::__throw_bad_array_new_length();
            }
            return static_cast<Tp_*>(operator new(n));
        }
        return allocator_base<Tp_>::template allocate(n);
    }

    KLIB_ALWAYS_INLINE KLIB_CONSTEXPR
    void deallocate(Tp_* p, std::size_t n) {
        if (std::is_constant_evaluated()) {
            operator delete(p);
            return;
        }
        allocator_base<Tp_>::template deallocate(p, n);
    }

    friend KLIB_ALWAYS_INLINE KLIB_CONSTEXPR
    bool operator==(const allocator&, const allocator&) KLIB_NOEXCEPT {
        return true;
    }
};

template <typename Ty1_, typename Ty2_>
KLIB_ALWAYS_INLINE KLIB_CONSTEXPR
bool operator==(const allocator<Ty1_>&, const allocator<Ty2_>&) KLIB_NOEXCEPT {
    return true;
}

template <typename Tp_>
class allocator<const Tp_> {
public:
    using value_type = Tp_;
    allocator() KLIB_NOEXCEPT { }
    template <typename Up_>
    allocator(const allocator<Up_>&) KLIB_NOEXCEPT { }
};

template <typename Tp_>
class allocator<volatile Tp_> {
public:
    using value_type = Tp_;
    allocator() KLIB_NOEXCEPT { }
    template <typename Up_>
    allocator(const allocator<Up_>&) KLIB_NOEXCEPT { }
};

template <typename Tp_>
class allocator<const volatile Tp_> {
public:
    using value_type = Tp_;
    allocator() KLIB_NOEXCEPT { }
    template <typename Up_>
    allocator(const allocator<Up_>&) KLIB_NOEXCEPT { }
};

template <>
class allocator<void> {
public:
    using value_type = void;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    allocator() = default;
    ~allocator() = default;

    template <typename Up_> KLIB_ALWAYS_INLINE KLIB_CONSTEXPR
    allocator(const allocator<Up_>&) KLIB_NOEXCEPT { }
};

extern template class allocator<char>;
extern template class allocator<wchar_t>;

}

#endif //ALLOCATOR_H
