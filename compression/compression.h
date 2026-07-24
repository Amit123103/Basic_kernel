#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stdint.h>

void compression_init(void);
uint32_t compression_rle_encode(const char *input, char *output, uint32_t input_length);
uint32_t compression_rle_decode(const char *input, char *output, uint32_t input_length);

#endif
