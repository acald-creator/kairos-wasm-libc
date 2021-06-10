#include "string.h"

void *memcpy(void *restrict dstptr, const void *restrict srcptr, ksize_t n)
{
    kuchar *dst = (kuchar *)dstptr;
    const kuchar *src = (kuchar *)srcptr;

    for (ksize_t i = 0; i < n; i++)
        dst[i] = src[i];
    return dstptr;
}

void *memset(void *restrict dst, int c, ksize_t n)
{
    kuchar *buf = (kuchar *)dst;

    for (ksize_t i = 0; i < n; i++)
        buf[i] = (kuchar)c;
    return dst;
}