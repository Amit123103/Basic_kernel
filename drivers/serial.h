#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

void serial_init(void);
void serial_write_byte(uint8_t byte);
void serial_write_string(const char *text);
uint8_t serial_read_byte(void);

#endif
