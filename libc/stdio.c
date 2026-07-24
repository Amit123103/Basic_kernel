#include "kernel.h"
#include <stdio.h>

static void print_number(unsigned long value, int base) {
    char buffer[32];
    int i = 0;

    if (value == 0) {
        vga_write_char('0');
        return;
    }

    while (value > 0) {
        unsigned long rem = value % base;
        buffer[i++] = (rem < 10) ? ('0' + rem) : ('a' + (rem - 10));
        value /= base;
    }

    while (i-- > 0) {
        vga_write_char(buffer[i]);
    }
}

int kprintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    while (*fmt != '\0') {
        if (*fmt == '%') {
            fmt++;
            if (*fmt == '\0') {
                break;
            }
            if (*fmt == 'd' || *fmt == 'i') {
                long value = va_arg(args, long);
                if (value < 0) {
                    vga_write_char('-');
                    value = -value;
                }
                print_number((unsigned long)value, 10);
            } else if (*fmt == 'u') {
                unsigned long value = va_arg(args, unsigned long);
                print_number(value, 10);
            } else if (*fmt == 'x' || *fmt == 'X') {
                unsigned long value = va_arg(args, unsigned long);
                print_number(value, 16);
            } else if (*fmt == 's') {
                const char *value = va_arg(args, const char *);
                vga_write_string(value);
            } else if (*fmt == 'c') {
                char value = (char)va_arg(args, int);
                vga_write_char(value);
            } else {
                vga_write_char(*fmt);
            }
        } else {
            vga_write_char(*fmt);
        }
        fmt++;
    }

    va_end(args);
    return 0;
}
