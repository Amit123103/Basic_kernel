#ifndef VMM_H
#define VMM_H

#include <stdint.h>

#define PAGE_SIZE 4096U

void vmm_init(void);
int vmm_map_page(uintptr_t virtual_address, uintptr_t physical_address);
int vmm_unmap_page(uintptr_t virtual_address);

#endif
