#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

#define SYSCALL_WRITE 1
#define SYSCALL_READ 2
#define SYSCALL_EXIT 3
#define SYSCALL_FORK 4
#define SYSCALL_EXEC 5
#define SYSCALL_WAIT 6
#define SYSCALL_GETPID 7

uint64_t syscall_dispatch(uint64_t number, uint64_t arg0, uint64_t arg1, uint64_t arg2);

#endif
