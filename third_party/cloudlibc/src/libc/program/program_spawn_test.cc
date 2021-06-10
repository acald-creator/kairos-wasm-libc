// Copyright (c) 2017 Nuxi, https://nuxi.nl/
//
// SPDX-License-Identifier: BSD-2-Clause

#ifdef __CloudABI__

#include <argdata.h>
#include <errno.h>
#include <fcntl.h>
#include <program.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include <uv.h>

#include "gtest/gtest.h"
#include "src/gtest_with_tmpdir/gtest_with_tmpdir.h"

static void unused_cb(uv_process_t *handle, int64_t exit_status,
                      int term_signal) {
  // This callback should not be invoked.
  ASSERT_TRUE(false);
}

TEST(program_spawn, eacces) {
  int fd_tmp = gtest_with_tmpdir::CreateTemporaryDirectory();

  uv_loop_t loop;
  ASSERT_EQ(0, uv_loop_init(&loop));

  // Attempt to execute a directory file descriptor.
  uv_process_t handle;
  ASSERT_EQ(EACCES,
            program_spawn(&loop, &handle, fd_tmp, &argdata_null, unused_cb));

  ASSERT_EQ(0, uv_loop_close(&loop));
}

TEST(program_spawn, ebadf1) {
  uv_loop_t loop;
  ASSERT_EQ(0, uv_loop_init(&loop));

  // Invalid file descriptor number.
  uv_process_t handle;
  ASSERT_EQ(EBADF, program_spawn(&loop, &handle, -1, &argdata_null, unused_cb));

  ASSERT_EQ(0, uv_loop_close(&loop));
}

TEST(program_spawn, ebadf2) {
  int fd_tmp = gtest_with_tmpdir::CreateTemporaryDirectory();

  int executable = openat(fd_tmp, "Hello", O_CREAT | O_WRONLY);
  ASSERT_LE(0, executable);
  uv_loop_t loop;
  ASSERT_EQ(0, uv_loop_init(&loop));

  // Executable is not open for executing.
  uv_process_t handle;
  ASSERT_EQ(EBADF, program_spawn(&loop, &handle, executable, &argdata_null,
                                 unused_cb));
  ASSERT_EQ(0, close(executable));

  ASSERT_EQ(0, uv_loop_close(&loop));
}

TEST(program_spawn, enoexec) {
  int fd_tmp = gtest_with_tmpdir::CreateTemporaryDirectory();

  // Create an empty file.
  int executable = openat(fd_tmp, "Hello", O_CREAT | O_WRONLY);
  ASSERT_LE(0, executable);
  ASSERT_EQ(0, close(executable));

  executable = openat(fd_tmp, "Hello", O_EXEC);
  ASSERT_LE(0, executable);
  uv_loop_t loop;
  ASSERT_EQ(0, uv_loop_init(&loop));

  // Unsupported file format.
  uv_process_t handle;
  ASSERT_EQ(ENOEXEC, program_spawn(&loop, &handle, executable, &argdata_null,
                                   unused_cb));
  ASSERT_EQ(0, close(executable));

  ASSERT_EQ(0, uv_loop_close(&loop));
}

#ifdef __x86_64__

// An executable that crashes on purpose with SIGFPE. Generated with:
//
//     $ cat tiny.asm
//     BITS 64
//     GLOBAL _start
//     SECTION .text
//     _start:
//       xor rax, rax
//       div rax
//     $ nasm -f elf64 tiny.asm
//     $ ld -pie -o tiny tiny.o
//     $ strip -s tiny
//     $ brandelf -f 17 tiny
//     $ xxd --include tiny
//
static const unsigned char sigfpe_binary[] = {
    0x7f, 0x45, 0x4c, 0x46, 0x02, 0x01, 0x01, 0x11, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x3e, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x38, 0x00, 0x01, 0x00, 0x40, 0x00,
    0x03, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x31, 0xc0, 0x48,
    0xf7, 0xf0, 0x00, 0x2e, 0x73, 0x68, 0x73, 0x74, 0x72, 0x74, 0x61, 0x62,
    0x00, 0x2e, 0x74, 0x65, 0x78, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0b, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static void crash_result(uv_process_t *handle, int64_t exit_status,
                         int term_signal) {
  ASSERT_EQ(0, exit_status);
  ASSERT_EQ(SIGFPE, term_signal);
  ASSERT_FALSE(*(bool *)handle->data);
  *(bool *)handle->data = true;
}

static void close_cb(uv_handle_t *handle) {
  ASSERT_FALSE(*(bool *)handle->data);
  *(bool *)handle->data = true;
}

TEST(program_spawn, sigfpe) {
  int fd_tmp = gtest_with_tmpdir::CreateTemporaryDirectory();

  // Create our faulty executable.
  int executable = openat(fd_tmp, "Crash", O_CREAT | O_WRONLY);
  ASSERT_LE(0, executable);
  ASSERT_EQ(sizeof(sigfpe_binary),
            write(executable, sigfpe_binary, sizeof(sigfpe_binary)));
  ASSERT_EQ(0, close(executable));

  executable = openat(fd_tmp, "Crash", O_EXEC);
  ASSERT_LE(0, executable);
  uv_loop_t loop;
  ASSERT_EQ(0, uv_loop_init(&loop));

  // Execution should succeed.
  uv_process_t handle;
  ASSERT_EQ(0, program_spawn(&loop, &handle, executable, &argdata_null,
                             crash_result));
  ASSERT_EQ(0, close(executable));

  // Let the process run until termination.
  bool terminated = false;
  handle.data = &terminated;
  ASSERT_EQ(0, uv_run(&loop, UV_RUN_DEFAULT));
  ASSERT_TRUE(terminated);

  bool closed = false;
  handle.data = &closed;
  uv_close((uv_handle_t *)&handle, close_cb);
  ASSERT_EQ(0, uv_run(&loop, UV_RUN_DEFAULT));
  ASSERT_TRUE(closed);

  ASSERT_EQ(0, uv_loop_close(&loop));
}

// TODO(ed): Any way we can test processes that exit?

#endif

#endif
