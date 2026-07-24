#include "kernel.h"
#include "drivers/serial.h"

#define SERIAL_COM1 0x3F8
#define SERIAL_DATA_PORT (SERIAL_COM1 + 0)
#define SERIAL_INT_ENABLE (SERIAL_COM1 + 1)
#define SERIAL_FIFO_CTRL (SERIAL_COM1 + 2)
#define SERIAL_LINE_CTRL (SERIAL_COM1 + 3)
#define SERIAL_MODEM_CTRL (SERIAL_COM1 + 4)
#define SERIAL_LINE_STATUS (SERIAL_COM1 + 5)

static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t value;
    __asm__ volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

void serial_init(void) {
    outb(SERIAL_INT_ENABLE, 0x00);
    outb(SERIAL_LINE_CTRL, 0x80);
    outb(SERIAL_DATA_PORT, 0x03);
    outb(SERIAL_INT_ENABLE, 0x00);
    outb(SERIAL_LINE_CTRL, 0x03);
    outb(SERIAL_FIFO_CTRL, 0xC7);
    outb(SERIAL_MODEM_CTRL, 0x0B);
}

void serial_write_byte(uint8_t byte) {
    while ((inb(SERIAL_LINE_STATUS) & 0x20) == 0) {
    }
    outb(SERIAL_DATA_PORT, byte);
}

void serial_write_string(const char *text) {
    while (*text != '\0') {
        serial_write_byte((uint8_t)*text++);
    }
}

uint8_t serial_read_byte(void) {
    while ((inb(SERIAL_LINE_STATUS) & 0x01) == 0) {
    }
    return inb(SERIAL_DATA_PORT);
}
