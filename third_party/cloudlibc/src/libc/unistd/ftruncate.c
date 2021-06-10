// Copyright (c) 2015-2016 Nuxi, https://nuxi.nl/
//
// SPDX-License-Identifier: BSD-2-Clause

#include <cloudabi_syscalls.h>
#include <errno.h>
#include <unistd.h>

int ftruncate(int fildes, off_t length) {
  if (length < 0) {
    errno = EINVAL;
    return -1;
  }
  cloudabi_filestat_t fs = {
      .st_size = length,
  };
  cloudabi_errno_t error =
      cloudabi_sys_file_stat_fput(fildes, &fs, CLOUDABI_FILESTAT_SIZE);
  if (error != 0) {
    errno = error;
    return -1;
  }
  return 0;
}
