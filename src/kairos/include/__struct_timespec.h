#ifndef __kairos_libc__struct_timespec_h
#define __kairos_libc__struct_timespec_h

#include "__typedef_time_t.h"

struct timespec
{
    time_t tv_sec;
    long tv_nsec;
};

#endif // __kairos_libc__struct_timespec_h