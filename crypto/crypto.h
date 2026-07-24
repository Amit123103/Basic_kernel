#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdint.h>

void crypto_init(void);
uint32_t crypto_xor_hash(const char *text);
uint32_t crypto_crc32(const char *text);

#endif
