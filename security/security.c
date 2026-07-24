#include "kernel.h"
#include "security/security.h"

static uint32_t fnv1a_hash(const char *text)
{
    uint32_t hash = 2166136261u;
    const unsigned char *p = (const unsigned char *)text;

    while (*p != '\0') {
        hash ^= *p;
        hash *= 16777619u;
        p++;
    }

    return hash;
}

void security_init(void)
{
    kprintf("Security subsystem initialized\n");
}

uint32_t security_hash_string(const char *text)
{
    if (text == NULL) {
        return 0;
    }

    return fnv1a_hash(text);
}

int security_verify_integrity(const char *text)
{
    if (text == NULL || text[0] == '\0') {
        return 0;
    }

    return security_hash_string(text) != 0;
}
