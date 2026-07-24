#include "kernel.h"
#include "memory/allocator.h"
#include "memory/heap.h"

void allocator_init(void) {
    heap_init();
}

void *allocator_alloc(size_t size) {
    return kmalloc(size);
}

void allocator_free(void *ptr) {
    kfree(ptr);
}
