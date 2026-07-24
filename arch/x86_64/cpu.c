#include "kernel.h"

void cpu_halt(void) {
    __asm__ volatile("cli; hlt; 1: jmp 1b");
}
