#ifndef __kairos_libc_sys_types_h
#define __kairos_libc_sys_types_h

#define __need_size_t
#include <stddef.h>

#include <__typedef_blksize_t.h>
#include <__typedef_nlink_t.h>
#include <__typedef_off_t.h>
#include <__typedef_ksize_t.h>
#include <__typedef_suseconds_t.h>

/**
 *  Defining types for the libc
 **/

typedef long long blksize_t;
typedef long long nlink_t;
typedef long long off_t;
typedef unsigned long ksize_t;
typedef unsigned short kushort;
typedef unsigned short kuchar;
typedef ksize_t pde_t;

#endif // __kairos_libc_sys_types_h