#ifndef CONFIG_H
#define CONFIG_H


#ifdef __GNUC__

#define KLIB_CONSTEXPR constexpr
#define KLIB_PURE __attribute__((__pure__))
#define KLIB_CONST __attribute__((__const__))
#define KLIB_NORETURN __attribute__((__noreturn__))
#define KLIB_UNUSED __attribute__((__unused__))
#define KLIB_ALWAYS_INLINE __attribute__((always_inline))
#define KLIB_NOEXCEPT noexcept
#define KLIB_NODISCARD [[__nodiscard__]]

#define KLIB_LIKELY(x) __builtin_expect((x), 1)
#define KLIB_UNLIKELY(x) __builtin_expect((x), 0)


#define KLIB_CONSTANT_EVALUATED constant_evaluated()

#endif


#endif //CONFIG_H
