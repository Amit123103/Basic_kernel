#include "kernel.h"
#include "memory/heap.h"

static uint8_t g_heap_memory[4096];
static size_t g_heap_used = 0;

void heap_init(void) {
    g_heap_used = 0;
}

void *kmalloc(size_t size) {
    if (g_heap_used + size > sizeof(g_heap_memory)) {
        return (void *)0;
    }

    void *ptr = &g_heap_memory[g_heap_used];
    g_heap_used += size;
    return ptr;
}

void kfree(void *ptr) {
    (void)ptr;
}
