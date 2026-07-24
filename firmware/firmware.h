#ifndef FIRMWARE_H
#define FIRMWARE_H

#include <stdint.h>

void firmware_init(void);
uint32_t firmware_detect_vendor(void);
uint32_t firmware_detect_revision(void);

#endif
