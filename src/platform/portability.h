#ifndef PORTABILITY_H
#define PORTABILITY_H

#if defined(_MSC_VER)
    #define KERUIS_CPLUSPLUS _MSVC_LANG
#else
    #define KERUIS_CPLUSPLUS __cplusplus
#endif

#define KERUIS_X86_64  0
#define KERUIS_ARM     0
#define KERUIS_AARCH64 0
#define KERUIS_PPC64   0
#define KERUIS_S390X   0

#if defined(__x86_64__) || defined(_M_X64)
#undef KERUIS_X86_64
    #define KERUIS_X86_64   1
#elif defined(__arm__)
#undef KERUIS_ARM
    #define KERUIS_ARM      1
#elif defined(__aarch64__)
#undef KERUIS_AARCH64
    #define KERUIS_AARCH64  1
#elif defined(__powerpc64__)
#undef KERUIS_PPC64
    #define KERUIS_PPC64    1
#elif defined(__s390x__)
#undef KERUIS_S390X
    #define KERUIS_S390X    1
#endif

namespace Keruis {

#if defined(KERUIS_HAVE_UNALIGNED_ACCESS) && KERUIS_HAVE_UNALIGNED_ACCESS
    constexpr bool KHasUnalignedAccess = true;
#else
    constexpr bool KHasUnalignedAccess = false;
#endif

constexpr bool KIsArchArm     = KERUIS_ARM      == 1;
constexpr bool KIsArchAmd64   = KERUIS_X86_64   == 1;
constexpr bool KIsArchPPC64   = KERUIS_PPC64    == 1;
constexpr bool KIsArchS390X   = KERUIS_S390X    == 1;
constexpr bool KIsArchArch64  = KERUIS_AARCH64  == 1;

}




#endif //PORTABILITY_H
