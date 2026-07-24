#include "kernel.h"
#include "crypto/crypto.h"

void crypto_init(void)
{
    kprintf("Crypto subsystem initialized\n");
}

uint32_t crypto_xor_hash(const char *text)
{
    uint32_t hash = 0;
    const unsigned char *p = (const unsigned char *)text;

    while (*p != '\0') {
        hash ^= *p;
        hash = (hash << 1) | (hash >> 31);
        p++;
    }

    return hash;
}

uint32_t crypto_crc32(const char *text)
{
    uint32_t crc = 0xFFFFFFFFu;
    const unsigned char *p = (const unsigned char *)text;

    while (*p != '\0') {
        crc ^= *p;
        for (unsigned int i = 0; i < 8; ++i) {
            if ((crc & 1u) != 0u) {
                crc = (crc >> 1u) ^ 0xEDB88320u;
            } else {
                crc >>= 1u;
            }
        }
        p++;
    }

    return ~crc;
}
