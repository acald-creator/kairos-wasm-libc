#ifndef __kairos_libc_stdlib_h
#define __kairos_libc_stdlib_h

#define __need_size_t
#define __need_NULL

#include "sys/types.h"
#include "sys/cdefs.h"

#include <stddef.h>

__BEGIN_C_CODE

void *malloc(ksize_t);
void free(void *);
void *calloc(ksize_t *, ksize_t *);
void *realloc(void *, ksize_t *);

__END_C_CODE

#endif // __kairos_libc_stdlib_h