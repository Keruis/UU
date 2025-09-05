#ifndef K_STRINGCORE_H
#define K_STRINGCORE_H

#include <cstddef>

#include "K_StringConfig.h"

#include "../config.h"

namespace Keruis::core::KString {

template <typename CharT_>
class K_core_string {
public:
    K_core_string& operator=(const K_core_string& rhs) = delete;

    K_core_string() KLIB_NOEXCEPT {

    }

    K_core_string(const K_core_string& rhs) {
        assert(&rhs != this);

    }

    K_core_string(K_core_string&& rhs) KLIB_NOEXCEPT {

    }

    K_core_string(
        const CharT_* str,
        const std::size_t size,
        bool disableSSO = KSTRING_DISABLE_SSO
    ) {

    }
};

}

#endif //K_STRINGCORE_H
