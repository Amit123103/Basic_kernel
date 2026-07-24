#include "kernel.h"
#include "process/process.h"

static process_t g_processes[MAX_PROCESSES];
static uint32_t g_current_pid = 0;

void process_init(void) {
    for (size_t i = 0; i < MAX_PROCESSES; ++i) {
        g_processes[i].pid = 0;
        g_processes[i].state = 0;
        g_processes[i].priority = 0;
        g_processes[i].wake_time = 0;
        g_processes[i].rsp = 0;
        g_processes[i].rip = 0;
    }
}

uint32_t process_create(uint64_t entry_point) {
    for (size_t i = 0; i < MAX_PROCESSES; ++i) {
        if (g_processes[i].pid == 0) {
            g_processes[i].pid = (uint32_t)i + 1;
            g_processes[i].state = 1;
            g_processes[i].priority = 1;
            g_processes[i].wake_time = 0;
            g_processes[i].rip = entry_point;
            return g_processes[i].pid;
        }
    }
    return 0;
}

void scheduler_yield(void) {
    g_current_pid = (g_current_pid + 1) % MAX_PROCESSES;
}

void scheduler_sleep(uint32_t ticks) {
    (void)ticks;
}
