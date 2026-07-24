#include "kernel.h"
#include "logging/logging.h"

void log_init(void)
{
    kprintf("Logging subsystem initialized\n");
}

void log_info(const char *message)
{
    kprintf("INFO: ");
    kprintf(message);
    kprintf("\n");
}

void log_warn(const char *message)
{
    kprintf("WARN: ");
    kprintf(message);
    kprintf("\n");
}

void log_error(const char *message)
{
    kprintf("ERROR: ");
    kprintf(message);
    kprintf("\n");
}
