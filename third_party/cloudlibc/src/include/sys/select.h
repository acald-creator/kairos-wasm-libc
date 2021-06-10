// Copyright (c) 2015-2016 Nuxi, https://nuxi.nl/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

// <sys/select.h> - select types
//
// Extensions:
// - FD_COPY():
//   Present on most BSD-derived systems.
// - FD_ISSET():
//   Second argument marked const:
//   http://austingroupbugs.net/view.php?id=220
// - pselect():
//   Last parameter may be omitted entirely.

#ifndef _SYS_SELECT_H_
#define _SYS_SELECT_H_

#include <_/struct/timespec.h>  // IWYU pragma: export
#include <_/time_select.h>

#ifndef _SIGSET_T_DECLARED
typedef __sigset_t sigset_t;
#define _SIGSET_T_DECLARED
#endif

__BEGIN_DECLS
int pselect(int, fd_set *__restrict, fd_set *__restrict, fd_set *__restrict,
            const struct timespec *__restrict, ...);
__END_DECLS

#endif
