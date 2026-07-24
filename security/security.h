#ifndef SECURITY_H
#define SECURITY_H

#include <stdint.h>

void security_init(void);
uint32_t security_hash_string(const char *text);
int security_verify_integrity(const char *text);

#endif
