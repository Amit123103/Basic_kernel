#ifndef UDP_H
#define UDP_H

#include <stdint.h>

void udp_init(void);
int udp_send_packet(uint16_t port, const void *payload, uint32_t payload_length);

#endif
