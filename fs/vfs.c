#include "kernel.h"
#include "fs/vfs.h"

static vfs_dir_t g_root_dir;

void vfs_init(void) {
    g_root_dir.count = 1;
    g_root_dir.entries[0].size = 0;
    g_root_dir.entries[0].flags = 0x01;
    for (size_t i = 0; i < sizeof(g_root_dir.entries[0].name) - 1; ++i) {
        g_root_dir.entries[0].name[i] = '\0';
    }
    g_root_dir.entries[0].name[0] = '/';
}

int vfs_open(const char *path) {
    (void)path;
    return 0;
}

int vfs_read(int fd, void *buffer, size_t size) {
    (void)fd;
    (void)buffer;
    (void)size;
    return 0;
}

int vfs_write(int fd, const void *buffer, size_t size) {
    (void)fd;
    (void)buffer;
    (void)size;
    return 0;
}

int vfs_list_dir(vfs_dir_t *out_dir) {
    if (out_dir == (void *)0) {
        return -1;
    }
    *out_dir = g_root_dir;
    return 0;
}
