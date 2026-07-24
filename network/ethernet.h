#ifndef ETHERNET_H
#define ETHERNET_H

#include <stdint.h>

void ethernet_init(void);
int ethernet_send_frame(const void *frame, uint32_t length);

#endif
