#ifndef DEBUG_H
#define DEBUG_H

#include <stdint.h>

void debug_init(void);
void debug_trace(const char *message);
void debug_dump_registers(void);

#endif
