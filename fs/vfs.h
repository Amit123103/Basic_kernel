#ifndef VFS_H
#define VFS_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    char name[32];
    uint32_t size;
    uint32_t flags;
} vfs_entry_t;

typedef struct {
    vfs_entry_t entries[16];
    uint32_t count;
} vfs_dir_t;

void vfs_init(void);
int vfs_open(const char *path);
int vfs_read(int fd, void *buffer, size_t size);
int vfs_write(int fd, const void *buffer, size_t size);
int vfs_list_dir(vfs_dir_t *out_dir);

#endif
