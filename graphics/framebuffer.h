#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

#define FRAMEBUFFER_WIDTH 1024
#define FRAMEBUFFER_HEIGHT 768
#define FRAMEBUFFER_BPP 4

void framebuffer_init(void);
void framebuffer_clear(uint32_t color);
void framebuffer_draw_pixel(uint32_t x, uint32_t y, uint32_t color);
void framebuffer_draw_rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color);
void framebuffer_put_char(uint32_t x, uint32_t y, char c, uint32_t fg, uint32_t bg);
void framebuffer_put_string(uint32_t x, uint32_t y, const char *text, uint32_t fg, uint32_t bg);

#endif
