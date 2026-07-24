#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void pit_init(uint32_t hz);
void pit_wait(uint32_t ticks);

#endif
