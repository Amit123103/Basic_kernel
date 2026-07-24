#include "kernel.h"
#include "process/process.h"
#include "process/scheduler.h"

void scheduler_init(void) {
    process_init();
}

void scheduler_tick(void) {
    scheduler_yield();
}
