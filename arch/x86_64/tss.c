#include "kernel.h"
#include "arch/x86_64/tss.h"

void tss_init(void) {
    /* TSS initialization will be completed when the full ring-3 task switch path is introduced. */
}
