#include "network.h"
#include <stdint.h>

void pci_init(void)
{
    // Phase 12 stub: enumerate PCI devices.
}

uint16_t pci_read_config16(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset)
{
    (void)bus;
    (void)slot;
    (void)function;
    (void)offset;
    return 0;
}
