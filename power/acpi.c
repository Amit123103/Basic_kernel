#include "kernel.h"
#include "power/acpi.h"

void acpi_init(void)
{
    kprintf("ACPI power management initialized\n");
}

void acpi_reboot(void)
{
    kprintf("ACPI reboot request acknowledged\n");
}

void acpi_shutdown(void)
{
    kprintf("ACPI shutdown request acknowledged\n");
}
