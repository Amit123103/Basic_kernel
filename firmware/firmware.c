#include "kernel.h"
#include "firmware/firmware.h"

void firmware_init(void)
{
    kprintf("Firmware discovery initialized\n");
}

uint32_t firmware_detect_vendor(void)
{
    return 0;
}

uint32_t firmware_detect_revision(void)
{
    return 0;
}
