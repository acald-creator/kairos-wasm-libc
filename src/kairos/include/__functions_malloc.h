#ifndef __kairos___functions_malloc_h
#define __kairos___functions_malloc_h

#define __need_size_t
#define __need_NULL

#include "sys/types.h"
#include "sys/cdefs.h"

#include <stddef.h>

__BEGIN_C_CODE

void *malloc(ksize_t);
void free(void *);
void *calloc(ksize_t mnemb, ksize_t size);
void *realloc(void *ptr, ksize_t size);

__END_C_CODE

#endif // __kairos_libc_stdlib_h