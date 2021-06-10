#define HAVE_MMAP 0
#define MORECORE_CANNOT_TRIM 1
#define ABORT __builtin_unreachable()
#ifndef WASM_THREAD_MODEL_SINGLE
#define USE_LOCKS 1
#endif

#define LACKS_TIME_H 1
#define LACKS_SCHED_H
#define NO_MALLINFO 1
#define NO_MALLOC_STATS 1
extern const int __ENOMEM;
#define ENOMEM __ENOMEM
extern const int __EINVAL;
#define EINVAL __EINVAL
#define USE_DL_PREFIX 1
#define DLMALLOC_EXPORT static inline

#include "malloc.c"

void *malloc(size_t size)
{
    return dlmalloc(size);
}

void free(void *ptr)
{
    return dlfree(ptr);
}

void *calloc(size_t nmemb, size_t size)
{
    return dlcalloc(nmemb, size);
}

void *realloc(void *ptr, size_t size)
{
    return dlrealloc(ptr, size);
}

int posix_memalign(void **memptr, size_t alignment, size_t size)
{
    return dlposix_memalign(memptr, alignment, size);
}
