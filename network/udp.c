#include "network.h"
#include <stdint.h>

void udp_init(void)
{
    // Phase 12 stub: initialize UDP port table.
}

int udp_send_packet(uint16_t port, const void *payload, uint32_t payload_length)
{
    (void)port;
    (void)payload;
    (void)payload_length;
    return 0;
}
