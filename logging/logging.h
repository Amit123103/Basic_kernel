#ifndef LOGGING_H
#define LOGGING_H

#include <stdint.h>

void log_init(void);
void log_info(const char *message);
void log_warn(const char *message);
void log_error(const char *message);

#endif
