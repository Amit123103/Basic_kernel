#ifndef USER_H
#define USER_H

#include <stdint.h>

#define USER_RING 3

void user_mode_init(void);
int user_load_elf(const char *path);

#endif
