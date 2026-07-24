#include "kernel.h"
#include "drivers/keyboard.h"

#define KEYBOARD_DATA_PORT 0x60

static inline uint8_t inb(uint16_t port) {
    uint8_t value;
    __asm__ volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

void keyboard_init(void) {
    /* Keyboard controller is not yet fully initialized for the educational Phase 5 path. */
}

uint8_t keyboard_read_scancode(void) {
    return inb(KEYBOARD_DATA_PORT);
}
