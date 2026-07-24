#include "ipc.h"

static ipc_message_t msg_queue[MAX_IPC_MESSAGES];
static ipc_shm_region_t shm_regions[MAX_IPC_SHM_REGIONS];
static ipc_pipe_t pipes[MAX_IPC_PIPES];

void ipc_init(void) {
    for (int i = 0; i < MAX_IPC_MESSAGES; i++) {
        msg_queue[i].active = 0;
    }
    for (int i = 0; i < MAX_IPC_SHM_REGIONS; i++) {
        shm_regions[i].active = 0;
    }
    for (int i = 0; i < MAX_IPC_PIPES; i++) {
        pipes[i].active = 0;
        pipes[i].head = 0;
        pipes[i].tail = 0;
        pipes[i].count = 0;
    }
}

void spinlock_init(spinlock_t *lock) {
    if (!lock) return;
    lock->lock = 0;
}

void spinlock_lock(spinlock_t *lock) {
    if (!lock) return;
    while (__sync_lock_test_and_set(&lock->lock, 1)) {
        // Spin until lock is free
    }
}

void spinlock_unlock(spinlock_t *lock) {
    if (!lock) return;
    __sync_lock_release(&lock->lock);
}

void mutex_init(mutex_t *mutex) {
    if (!mutex) return;
    mutex->lock = 0;
    mutex->owner_pid = 0;
}

void mutex_lock(mutex_t *mutex, uint32_t pid) {
    if (!mutex) return;
    while (__sync_lock_test_and_set(&mutex->lock, 1)) {
        // Spin until acquired
    }
    mutex->owner_pid = pid;
}

void mutex_unlock(mutex_t *mutex) {
    if (!mutex) return;
    mutex->owner_pid = 0;
    __sync_lock_release(&mutex->lock);
}

int ipc_msg_send(uint32_t sender_pid, uint32_t receiver_pid, const char *data, uint32_t length) {
    if (!data || length == 0 || length > IPC_MSG_MAX_SIZE) return -1;

    for (int i = 0; i < MAX_IPC_MESSAGES; i++) {
        if (!msg_queue[i].active) {
            msg_queue[i].sender_pid = sender_pid;
            msg_queue[i].receiver_pid = receiver_pid;
            msg_queue[i].length = length;
            for (uint32_t j = 0; j < length; j++) {
                msg_queue[i].data[j] = data[j];
            }
            msg_queue[i].active = 1;
            return 0;
        }
    }
    return -1;
}

int ipc_msg_receive(uint32_t receiver_pid, uint32_t *sender_pid, char *buffer, uint32_t max_length) {
    if (!buffer || max_length == 0) return -1;

    for (int i = 0; i < MAX_IPC_MESSAGES; i++) {
        if (msg_queue[i].active && (msg_queue[i].receiver_pid == receiver_pid || msg_queue[i].receiver_pid == 0)) {
            uint32_t copy_len = msg_queue[i].length < max_length ? msg_queue[i].length : max_length;
            for (uint32_t j = 0; j < copy_len; j++) {
                buffer[j] = msg_queue[i].data[j];
            }
            if (sender_pid) {
                *sender_pid = msg_queue[i].sender_pid;
            }
            msg_queue[i].active = 0;
            return (int)copy_len;
        }
    }
    return -1;
}

int ipc_pipe_create(int pipefd[2]) {
    if (!pipefd) return -1;

    for (int i = 0; i < MAX_IPC_PIPES; i++) {
        if (!pipes[i].active) {
            pipes[i].active = 1;
            pipes[i].head = 0;
            pipes[i].tail = 0;
            pipes[i].count = 0;
            pipefd[0] = i * 2;
            pipefd[1] = i * 2 + 1;
            return 0;
        }
    }
    return -1;
}

int ipc_pipe_write(int fd, const char *buffer, uint32_t count) {
    if (!buffer || count == 0) return -1;
    int pipe_idx = fd / 2;
    if (pipe_idx < 0 || pipe_idx >= MAX_IPC_PIPES || !pipes[pipe_idx].active) return -1;

    ipc_pipe_t *p = &pipes[pipe_idx];
    uint32_t written = 0;
    while (written < count && p->count < PIPE_BUFFER_SIZE) {
        p->buffer[p->head] = buffer[written];
        p->head = (p->head + 1) % PIPE_BUFFER_SIZE;
        p->count++;
        written++;
    }
    return (int)written;
}

int ipc_pipe_read(int fd, char *buffer, uint32_t count) {
    if (!buffer || count == 0) return -1;
    int pipe_idx = fd / 2;
    if (pipe_idx < 0 || pipe_idx >= MAX_IPC_PIPES || !pipes[pipe_idx].active) return -1;

    ipc_pipe_t *p = &pipes[pipe_idx];
    uint32_t read_bytes = 0;
    while (read_bytes < count && p->count > 0) {
        buffer[read_bytes] = p->buffer[p->tail];
        p->tail = (p->tail + 1) % PIPE_BUFFER_SIZE;
        p->count--;
        read_bytes++;
    }
    return (int)read_bytes;
}

int ipc_shm_create(uint32_t key, size_t size) {
    for (int i = 0; i < MAX_IPC_SHM_REGIONS; i++) {
        if (shm_regions[i].active && shm_regions[i].key == key) {
            return i;
        }
    }

    for (int i = 0; i < MAX_IPC_SHM_REGIONS; i++) {
        if (!shm_regions[i].active) {
            shm_regions[i].key = key;
            shm_regions[i].size = size;
            shm_regions[i].phys_addr = 0x200000 + i * 0x1000;
            shm_regions[i].active = 1;
            return i;
        }
    }
    return -1;
}
