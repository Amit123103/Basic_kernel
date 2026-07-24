#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

void allocator_init(void);
void *allocator_alloc(size_t size);
void allocator_free(void *ptr);

#endif
