#include "network.h"

void network_init(void)
{
    pci_init();
    ethernet_init();
    arp_init();
    ipv4_init();
    icmp_init();
    udp_init();
    tcp_init();
    dhcp_init();
}
