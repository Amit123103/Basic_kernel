#ifndef ICMP_H
#define ICMP_H

#include <stdint.h>

void icmp_init(void);
int icmp_echo_request(uint32_t destination_ip);

#endif
