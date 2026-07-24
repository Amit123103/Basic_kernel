#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

#define MAX_PROCESSES 16

typedef struct {
    uint32_t pid;
    uint32_t state;
    uint32_t priority;
    uint32_t wake_time;
    uint64_t rsp;
    uint64_t rip;
} process_t;

void process_init(void);
uint32_t process_create(uint64_t entry_point);
void scheduler_yield(void);
void scheduler_sleep(uint32_t ticks);

#endif
