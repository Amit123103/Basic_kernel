#ifndef TIME_H
#define TIME_H

#include <stdint.h>

void time_init(void);
uint64_t time_now(void);
void time_set(uint64_t epoch_seconds);

#endif
