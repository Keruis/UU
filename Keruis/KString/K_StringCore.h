#ifndef K_STRINGCORE_H
#define K_STRINGCORE_H

#include <cstddef>
#include <cassert>
#include <cstdint>

#include "K_StringConfig.h"
#include "K_StringCore.h"

#include "../config.h"
#include "../../../../SDK/include/10.0.26100.0/ucrt/errno.h"

namespace Keruis::core::KString {

template <typename CharT_>
class K_core_string {
public:
    KLIB_ALWAYS_INLINE
    void reset() KLIB_NOEXCEPT {setSSOBufferSize(0);}

    K_core_string& operator=(const K_core_string& rhs) = delete;

    K_core_string() KLIB_NOEXCEPT {
        setSSOBufferSize(0);
    }

    K_core_string(const K_core_string& rhs) {
        assert(&rhs != this);
        switch (rhs.category()) {
        case Category::isSmall:

            break;
        case Category::isLarge:

            break;
        default:

        }
    }

    K_core_string(K_core_string&& rhs) KLIB_NOEXCEPT {
        this->ds_ = rhs.ds_;
        this->capacity_ = rhs.capacity_;
        rhs.reset();
    }

    K_core_string(
        const CharT_* str,
        const std::size_t size
    ) {

    }

    K_core_string(
        const CharT_* str1,
        const CharT_* str2,
        const std::size_t size
    ) {

    }

    ~K_core_string() KLIB_NOEXCEPT {

    }

private:
    KLIB_ALWAYS_INLINE
    void setSSOBufferSize(const std::uint8_t size) KLIB_NOEXCEPT {
        assert(size <= maxSmallSize);
        capacity_ = static_cast<std::uint32_t>(size);
        sso_buffer_[size] = '\0';
    }

private:
    enum class Category : uint8_t {
        isSmall = 0,
        isLarge = 1,
    };

    struct DynamicStorage {
        CharT_* begin_;
        CharT_* end_;
    };

    std::uint32_t  capacity_;

    constexpr static size_t maxSmallSize = sizeof(DynamicStorage) - 1 / sizeof(CharT_);

    union {
        DynamicStorage ds_;
        CharT_ sso_buffer_[sizeof(DynamicStorage) / sizeof(CharT_)];
    };

private:
    KLIB_ALWAYS_INLINE
    Category category() const KLIB_NOEXCEPT {
        return static_cast<Category>((capacity_ > maxSmallSize) ? Category::isLarge : Category::isSmall);
    }

};

}

#endif //K_STRINGCORE_H
