#ifndef TCP_H
#define TCP_H

#include <stdint.h>

void tcp_init(void);
int tcp_connect(uint32_t destination_ip, uint16_t port);

#endif
