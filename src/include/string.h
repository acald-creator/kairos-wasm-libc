#ifndef __kairos_libc_string_h
#define __kairos_libc_string_h

#define __need_size_t
#define __need_kchar_t
#define __need_NULL

#include "sys/types.h"
#include "sys/cdefs.h"

#include <stddef.h>

__BEGIN_C_CODE

void *memcpy(void *, const void *, ksize_t);
void *memmove(void *, const void *, ksize_t);
void *memset(void *, int, ksize_t);

__END_C_CODE

#endif // __kairos_libc_string_h