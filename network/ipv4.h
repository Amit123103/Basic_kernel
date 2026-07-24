#ifndef IPV4_H
#define IPV4_H

#include <stdint.h>

void ipv4_init(void);
int ipv4_send_packet(uint32_t destination_ip, const void *payload, uint32_t payload_length);

#endif
