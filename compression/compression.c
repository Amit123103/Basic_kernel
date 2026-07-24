#include "kernel.h"
#include "compression/compression.h"

void compression_init(void)
{
    kprintf("Compression subsystem initialized\n");
}

uint32_t compression_rle_encode(const char *input, char *output, uint32_t input_length)
{
    (void)input;
    (void)output;
    (void)input_length;
    return 0;
}

uint32_t compression_rle_decode(const char *input, char *output, uint32_t input_length)
{
    (void)input;
    (void)output;
    (void)input_length;
    return 0;
}
