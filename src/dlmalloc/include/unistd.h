#include <stdint.h>

#define sysconf(name) 0x10000
#define _SC_PAGESIZE

void *sbrk(intptr_t increment);