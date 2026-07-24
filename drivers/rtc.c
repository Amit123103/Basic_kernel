#include "kernel.h"
#include "drivers/rtc.h"

#define CMOS_PORT 0x70
#define CMOS_DATA_PORT 0x71

static inline uint8_t inb(uint16_t port) {
    uint8_t value;
    __asm__ volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

void rtc_init(void) {
    outb(CMOS_PORT, 0x80);
    (void)inb(CMOS_DATA_PORT);
}

uint8_t rtc_read_register(uint8_t reg) {
    outb(CMOS_PORT, reg);
    return inb(CMOS_DATA_PORT);
}
