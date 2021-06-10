#ifndef __kairos_libc_errno_h
#define __kairos_libc_errno_h

#include "sys/cdefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef KAIROS_THREAD_MODEL_SINGLE
    extern int errno;
#else
#ifdef __cplusplus
extern thread_local int errno;
#else
extern _Thread_local int errno;
#endif
#endif

#define errno errno

#ifdef __cplusplus
}
#endif

#endif