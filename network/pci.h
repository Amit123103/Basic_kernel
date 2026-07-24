#ifndef PCI_H
#define PCI_H

#include <stdint.h>

void pci_init(void);
uint16_t pci_read_config16(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset);

#endif
