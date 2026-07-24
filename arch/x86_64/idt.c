#include "kernel.h"
#include "arch/x86_64/idt.h"

static struct idt_entry g_idt[IDT_ENTRY_COUNT];
static struct idt_ptr g_idtp;

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);

static void install_isr(uint8_t vector, void (*handler)(void)) {
    uint64_t addr = (uint64_t)handler;
    g_idt[vector].offset_low = (uint16_t)(addr & 0xFFFF);
    g_idt[vector].selector = 0x08;
    g_idt[vector].ist = 0;
    g_idt[vector].flags = 0x8E;
    g_idt[vector].offset_mid = (uint16_t)((addr >> 16) & 0xFFFF);
    g_idt[vector].offset_high = (uint32_t)((addr >> 32) & 0xFFFFFFFF);
    g_idt[vector].reserved = 0;
}

void exception_handler(void) {
    kernel_panic("Unhandled exception");
}

void idt_init(void) {
    install_isr(0, isr0);
    install_isr(1, isr1);
    install_isr(2, isr2);
    install_isr(3, isr3);
    install_isr(4, isr4);
    install_isr(5, isr5);
    install_isr(6, isr6);
    install_isr(7, isr7);
    install_isr(8, isr8);
    install_isr(9, isr9);
    install_isr(10, isr10);
    install_isr(11, isr11);
    install_isr(12, isr12);
    install_isr(13, isr13);
    install_isr(14, isr14);
    install_isr(15, isr15);
    install_isr(16, isr16);
    install_isr(17, isr17);
    install_isr(18, isr18);
    install_isr(19, isr19);

    g_idtp.limit = sizeof(g_idt) - 1;
    g_idtp.base = (uint64_t)&g_idt;

    __asm__ volatile("lidt %0" : : "m"(g_idtp));
}
