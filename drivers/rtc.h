#ifndef RTC_H
#define RTC_H

#include <stdint.h>

void rtc_init(void);
uint8_t rtc_read_register(uint8_t reg);

#endif
