#include "kernel.h"
#include "debug/debug.h"

void debug_init(void)
{
    kprintf("Debug trace buffer initialized\n");
}

void debug_trace(const char *message)
{
    kprintf("TRACE: ");
    kprintf(message);
    kprintf("\n");
}

void debug_dump_registers(void)
{
    kprintf("Debug register dump placeholder\n");
}
