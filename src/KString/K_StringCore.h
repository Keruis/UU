#ifndef K_STRINGCORE_H
#define K_STRINGCORE_H

#include <cstddef>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <string>
#include <type_traits>

#include "K_StringConfig.h"
#include "K_StringCore.h"

#include "../bits/allocator.h"

#include "../config.h"
#include "../../../../SDK/include/10.0.26100.0/ucrt/errno.h"

namespace Keruis::core::KString {

template <typename CharT_, typename Alloc_ = allocator<CharT_>>
class K_core_string {
public:
    using char_t            =   CharT_;
    using Alloc_t           =   Alloc_;
    using pointer_t         =   CharT_*;
    using const_pointer_t   =   const CharT_*;


    KLIB_CONSTEXPR
    void reset() KLIB_NOEXCEPT { setSSOBufferSize(0);}

    K_core_string& operator=(const K_core_string& rhs) = delete;

    KLIB_CONSTEXPR
    K_core_string() KLIB_NOEXCEPT {
        setSSOBufferSize(0);
    }

    KLIB_CONSTEXPR
    K_core_string(const K_core_string& rhs) {
        assert(&rhs != this);
        switch (rhs.category()) {
        case Category::isSmall:
            setSSOBufferSize(rhs.sso_size());
            std::memcpy(this->sso_buffer_, rhs.sso_buffer_, rhs.sso_size() + 1);
            break;
        case Category::isLarge:
{}

        default:
{}
        }
    }

    // template <typename traits_ = std::char_traits<char_t>, typename alloc_ = std::allocator<char_t>>
    // KLIB_CONSTEXPR
    // K_core_string(const std::basic_string<char_t, traits_, alloc_>& stl_string) KLIB_NOEXCEPT {
    //
    // }
    //
    // template <typename traits_ = std::char_traits<char_t>>
    // KLIB_CONSTEXPR
    // K_core_string(const std::basic_string<char_t, traits_>& stl_string) KLIB_NOEXCEPT {
    //
    // }

    KLIB_CONSTEXPR
    K_core_string(K_core_string&& rhs) KLIB_NOEXCEPT {
        this->ds_ = rhs.ds_;
        rhs.reset();
    }

    KLIB_CONSTEXPR
    K_core_string(const_pointer_t data) KLIB_NOEXCEPT {
        std::size_t size = std::strlen(data);
        if (size <= maxSmallSize) {
            std::memcpy(this->sso_buffer_, data, size);
            setSSOBufferSize(size);
        } else {
            Alloc_t alloc;
            pointer_t buf = alloc.allocate(size + 1);
            buf[size] = '\0';
            set_ds_range(buf, buf + size);
            std::memcpy(ds_begin(), data, size);
            sso_flag() = static_cast<uint8_t>(Category::isLarge);
        }
    }

    // KLIB_CONSTEXPR
    // K_core_string(char_t ch) KLIB_NOEXCEPT {
    //
    // }
    //
    // KLIB_CONSTEXPR
    // K_core_string(
    //     const pointer_t str,
    //     const std::size_t size
    // ) KLIB_NOEXCEPT {
    //
    // }
    //
    // KLIB_CONSTEXPR
    // K_core_string(
    //     const pointer_t str1,
    //     const pointer_t str2,
    //     const std::size_t size
    // ) KLIB_NOEXCEPT {
    //
    // }

    KLIB_CONSTEXPR
    ~K_core_string() KLIB_NOEXCEPT {
        if (category() == Category::isLarge && ds_begin()) {
            Alloc_t alloc;
            alloc.deallocate(ds_begin(), ds_capacity());
        }
    }

    const_pointer_t c_str() KLIB_NOEXCEPT {
        if (this->category() == Category::isSmall) {
            return this->sso_buffer_;
        }
        if (this->category() == Category::isLarge) {
            return this->ds_.begin_;
        }
        return nullptr;
    }

public:
    enum class Category : uint8_t {
        isSmall = 0,
        isLarge = 1,
    };

    struct DynamicStorage {
        pointer_t begin_;
        pointer_t end_;
        std::size_t capacity_;
    };

    constexpr static std::size_t maxSmallSize = sizeof(DynamicStorage) / sizeof(char_t) - 3;

    union {
        DynamicStorage ds_;
        CharT_ sso_buffer_[sizeof(DynamicStorage) / sizeof(char_t)];
    };

public:
    KLIB_CONSTEXPR
    void setSSOBufferSize(const std::uint8_t size) KLIB_NOEXCEPT {
        assert(size <= maxSmallSize);
        sso_flag() = static_cast<uint8_t>(Category::isSmall);
        sso_len() = size;
        this->sso_buffer_[size] = '\0';
    }

    KLIB_CONSTEXPR
    uint8_t& sso_flag() KLIB_NOEXCEPT {
        return reinterpret_cast<uint8_t&>(this->sso_buffer_[sizeof(sso_buffer_) - 1]);
    }
    KLIB_CONSTEXPR
    uint8_t& sso_len() KLIB_NOEXCEPT {
        return reinterpret_cast<uint8_t&>(this->sso_buffer_[sizeof(sso_buffer_) - 2]);
    }
    KLIB_NODISCARD KLIB_CONSTEXPR
    uint8_t sso_flag() const KLIB_NOEXCEPT {
        return reinterpret_cast<const uint8_t&>(this->sso_buffer_[sizeof(sso_buffer_) - 1]);
    }
    KLIB_NODISCARD KLIB_CONSTEXPR
    uint8_t sso_len() const KLIB_NOEXCEPT {
        return reinterpret_cast<const uint8_t&>(this->sso_buffer_[sizeof(sso_buffer_) - 2]);
    }
    KLIB_CONSTEXPR
    uint8_t& sso_null() KLIB_NOEXCEPT {
        return this->sso_buffer_[sizeof(sso_buffer_) - 3];
    }
    KLIB_NODISCARD KLIB_CONSTEXPR
    uint8_t sso_size() const KLIB_NOEXCEPT {
        return sso_len();
    }
    KLIB_NODISCARD KLIB_CONSTEXPR
    std::size_t ds_capacity() const KLIB_NOEXCEPT {
        return this->ds_.capacity_;
    }
    KLIB_NODISCARD KLIB_CONSTEXPR
    std::size_t ds_size() const KLIB_NOEXCEPT {
        return this->ds_.end_ - this->ds_.begin_;
    }
    KLIB_CONSTEXPR
    void set_ds_capacity(std::size_t capacity) KLIB_NOEXCEPT {
        this->ds_.capacity_ = capacity;
    }
    KLIB_CONSTEXPR
    void set_ds_size(std::size_t size) KLIB_NOEXCEPT {
        this->ds_.end_ = this->ds_.begin_ + size;
    }
    KLIB_CONSTEXPR
    pointer_t ds_begin() KLIB_NOEXCEPT {
        return this->ds_.begin_;
    }
    KLIB_CONSTEXPR
    pointer_t ds_end() KLIB_NOEXCEPT {
        return this->ds_.end_;
    }
    KLIB_CONSTEXPR
    void set_ds_range(pointer_t begin, pointer_t end) KLIB_NOEXCEPT {
        assert(begin <= end);
        this->ds_.begin_ = begin;
        this->ds_.end_ = end;
    }
    KLIB_CONSTEXPR
    Category category() const KLIB_NOEXCEPT {
        return static_cast<Category>(sso_flag());
    }

};

}

#endif //K_STRINGCORE_H
