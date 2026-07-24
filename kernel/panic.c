#include "kernel.h"

void kernel_panic(const char *message) {
    vga_clear();
    vga_write_string("KERNEL PANIC: ");
    vga_write_string(message);
    cpu_halt();
}
