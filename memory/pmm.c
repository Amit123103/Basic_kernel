#include "kernel.h"
#include "memory/pmm.h"

static uint64_t g_frame_bitmap[1024];
static uint64_t g_next_frame = 0;

void pmm_init(void) {
    for (size_t i = 0; i < sizeof(g_frame_bitmap) / sizeof(g_frame_bitmap[0]); ++i) {
        g_frame_bitmap[i] = 0;
    }
}

uint64_t pmm_alloc_frame(void) {
    uint64_t frame = g_next_frame * PMM_FRAME_SIZE;
    g_next_frame++;
    return frame;
}

void pmm_free_frame(uint64_t frame_address) {
    (void)frame_address;
}
