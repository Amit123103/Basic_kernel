#include "kernel.h"
#include "time/time.h"

void time_init(void)
{
    kprintf("Time synchronization subsystem initialized\n");
}

uint64_t time_now(void)
{
    return 0;
}

void time_set(uint64_t epoch_seconds)
{
    (void)epoch_seconds;
}
