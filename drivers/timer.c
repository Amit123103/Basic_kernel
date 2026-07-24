#include "kernel.h"
#include "drivers/timer.h"

#define PIT_COMMAND_PORT 0x43
#define PIT_CHANNEL0_PORT 0x40

static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

void pit_init(uint32_t hz) {
    (void)hz;
    outb(PIT_COMMAND_PORT, 0x36);
    outb(PIT_CHANNEL0_PORT, 0x00);
    outb(PIT_CHANNEL0_PORT, 0x00);
}

void pit_wait(uint32_t ticks) {
    (void)ticks;
}
