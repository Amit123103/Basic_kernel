#include "kernel.h"
#include "memory/vmm.h"

void vmm_init(void) {
    /* Page tables are initialized in the boot assembly. */
}

int vmm_map_page(uintptr_t virtual_address, uintptr_t physical_address) {
    (void)virtual_address;
    (void)physical_address;
    return 0;
}

int vmm_unmap_page(uintptr_t virtual_address) {
    (void)virtual_address;
    return 0;
}
