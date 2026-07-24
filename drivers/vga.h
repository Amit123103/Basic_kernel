#ifndef VGA_H
#define VGA_H

#include <stdint.h>

#define VGA_COLOR_BLACK 0x00
#define VGA_COLOR_BLUE 0x01
#define VGA_COLOR_GREEN 0x02
#define VGA_COLOR_CYAN 0x03
#define VGA_COLOR_RED 0x04
#define VGA_COLOR_MAGENTA 0x05
#define VGA_COLOR_BROWN 0x06
#define VGA_COLOR_LIGHT_GREY 0x07
#define VGA_COLOR_DARK_GREY 0x08
#define VGA_COLOR_LIGHT_BLUE 0x09
#define VGA_COLOR_LIGHT_GREEN 0x0A
#define VGA_COLOR_LIGHT_CYAN 0x0B
#define VGA_COLOR_LIGHT_RED 0x0C
#define VGA_COLOR_LIGHT_MAGENTA 0x0D
#define VGA_COLOR_LIGHT_BROWN 0x0E
#define VGA_COLOR_WHITE 0x0F

void vga_clear(void);
void vga_write_string(const char *text);
void vga_write_char(char c);
void vga_set_color(uint8_t fg, uint8_t bg);
void vga_set_cursor(uint8_t row, uint8_t col);

#endif
