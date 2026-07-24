#ifndef ARP_H
#define ARP_H

#include <stdint.h>

void arp_init(void);
int arp_resolve(uint32_t ip_address);

#endif
