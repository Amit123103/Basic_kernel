#include "kernel.h"
#include "syscall/syscall.h"

uint64_t syscall_dispatch(uint64_t number, uint64_t arg0, uint64_t arg1, uint64_t arg2) {
    switch (number) {
        case SYSCALL_WRITE:
            return (uint64_t)0;
        case SYSCALL_READ:
            return (uint64_t)0;
        case SYSCALL_EXIT:
            return (uint64_t)0;
        case SYSCALL_FORK:
            return (uint64_t)1;
        case SYSCALL_EXEC:
            return (uint64_t)0;
        case SYSCALL_WAIT:
            return (uint64_t)0;
        case SYSCALL_GETPID:
            return (uint64_t)1;
        default:
            return (uint64_t)-1;
    }
}
