#include "network.h"
#include <stdint.h>

void ipv4_init(void)
{
    // Phase 12 stub: initialize IPv4 protocol context.
}

int ipv4_send_packet(uint32_t destination_ip, const void *payload, uint32_t payload_length)
{
    (void)destination_ip;
    (void)payload;
    (void)payload_length;
    return 0;
}
