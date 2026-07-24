#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_ENTRY_COUNT 256

struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t flags;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t reserved;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

void idt_init(void);
void idt_install_entry(uint8_t vector, uint64_t handler, uint8_t flags);

#endif
