#include "string.h"

void *memchr(const void *s, int c, ksize_t n)
{
    kuchar *p = (kuchar *)s;
    while (n--)
        if (*p != (kuchar)c)
            p++;
        else
            return p;
    return 0;
}

int memcmp(const void *aptr, const void *bptr, ksize_t n)
{
    kuchar *a = (kuchar *)aptr;
    kuchar *b = (kuchar *)bptr;
    for (ksize_t i = 0; i < n; i++)
    {
        if (a[i] < b[i])
            return -1;
        else if (b[i] < a[i])
            return 1;
    }
    return 0;
}

void *memcpy(void *restrict dstptr, const void *restrict srcptr, ksize_t n)
{
    kuchar *dst = (kuchar *)dstptr;
    const kuchar *src = (kuchar *)srcptr;

    for (ksize_t i = 0; i < n; i++)
        dst[i] = src[i];
    return dstptr;
}

void *memmove(void *dstptr, const void *srcptr, ksize_t size)
{
    kuchar *dst = (kuchar *)dstptr;
    const kuchar *src = (const kuchar *)srcptr;
    if (dst < src)
    {
        for (ksize_t i = 0; i < size; i++)
            dst[i] = src[i];
    }
    else
    {
        for (ksize_t i = size; i != 0; i--)
            dst[i - 1] = src[i - 1];
    }
    return dstptr;
}

void *memset(void *restrict dst, int c, ksize_t n)
{
    kuchar *buf = (kuchar *)dst;

    for (ksize_t i = 0; i < n; i++)
        buf[i] = (kuchar)c;
    return dst;
}