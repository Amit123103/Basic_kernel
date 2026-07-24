#include "kernel.h"
#include "drivers/speaker.h"

#define SPEAKER_PORT 0x61

static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

void speaker_init(void) {
    outb(SPEAKER_PORT, 0x00);
}

void speaker_beep(uint32_t frequency) {
    (void)frequency;
    outb(SPEAKER_PORT, 0x03);
}
