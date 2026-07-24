#ifndef IPC_H
#define IPC_H

#include <stdint.h>
#include <stddef.h>

#define MAX_IPC_MESSAGES 32
#define IPC_MSG_MAX_SIZE 128
#define MAX_IPC_SHM_REGIONS 8
#define MAX_IPC_PIPES 8
#define PIPE_BUFFER_SIZE 256

typedef struct {
    uint32_t lock;
} spinlock_t;

typedef struct {
    uint32_t lock;
    uint32_t owner_pid;
} mutex_t;

typedef struct {
    uint32_t sender_pid;
    uint32_t receiver_pid;
    uint32_t length;
    char data[IPC_MSG_MAX_SIZE];
    uint32_t active;
} ipc_message_t;

typedef struct {
    uint32_t key;
    uint64_t phys_addr;
    size_t size;
    uint32_t active;
} ipc_shm_region_t;

typedef struct {
    char buffer[PIPE_BUFFER_SIZE];
    uint32_t head;
    uint32_t tail;
    uint32_t count;
    uint32_t active;
} ipc_pipe_t;

void ipc_init(void);

void spinlock_init(spinlock_t *lock);
void spinlock_lock(spinlock_t *lock);
void spinlock_unlock(spinlock_t *lock);

void mutex_init(mutex_t *mutex);
void mutex_lock(mutex_t *mutex, uint32_t pid);
void mutex_unlock(mutex_t *mutex);

int ipc_msg_send(uint32_t sender_pid, uint32_t receiver_pid, const char *data, uint32_t length);
int ipc_msg_receive(uint32_t receiver_pid, uint32_t *sender_pid, char *buffer, uint32_t max_length);

int ipc_pipe_create(int pipefd[2]);
int ipc_pipe_read(int fd, char *buffer, uint32_t count);
int ipc_pipe_write(int fd, const char *buffer, uint32_t count);

int ipc_shm_create(uint32_t key, size_t size);

#endif
