#ifndef JOURNALFS_H
#define JOURNALFS_H

#include <stdint.h>

void journalfs_init(void);
int journalfs_mount(void);
int journalfs_append_log(const char *entry);
int journalfs_recover(void);

#endif
