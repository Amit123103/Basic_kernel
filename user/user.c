#include "kernel.h"
#include "user/user.h"

void user_mode_init(void) {
    /* TSS and ring-3 transition scaffolding will be expanded in a later stage. */
}

int user_load_elf(const char *path) {
    (void)path;
    return 0;
}
