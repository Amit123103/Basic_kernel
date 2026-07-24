#ifndef NETWORK_H
#define NETWORK_H

#include "pci.h"
#include "ethernet.h"
#include "arp.h"
#include "ipv4.h"
#include "icmp.h"
#include "udp.h"
#include "tcp.h"
#include "dhcp.h"

void network_init(void);

#endif
