#ifndef __kairos_libc_cdefs_h
#define __kairos_libc_cdefs_h 1

#define __kairos_libc 1

#ifdef __cplusplus
#define __BEGIN_C_CODE \
    extern "C"         \
    {
#define __END_C_CODE }
#else
#define __BEGIN_C_CODE
#define __END_C_CODE
#endif

#endif
// __kairos_libc_cdefs_h