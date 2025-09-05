#ifndef K_STRINGCONFIG_H
#define K_STRINGCONFIG_H

#ifdef K_SANITIZE_ADDRESS
    #define KSTRING_DISABLE_SSO true
#else
    #define KSTRING_DISABLE_SSO false
#endif

#endif //K_STRINGCONFIG_H
