#ifndef FAT32_H
#define FAT32_H

#include <stdint.h>

void fat32_init(void);
int fat32_read_boot_sector(void);

#endif
