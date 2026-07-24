#include "kernel.h"
#include "journalfs/journalfs.h"

void journalfs_init(void)
{
    kprintf("Journaled filesystem initialized\n");
}

int journalfs_mount(void)
{
    return 0;
}

int journalfs_append_log(const char *entry)
{
    (void)entry;
    return 0;
}

int journalfs_recover(void)
{
    return 0;
}
