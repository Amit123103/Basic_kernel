#include "kernel.h"
#include "graphics/framebuffer.h"

static uint32_t *g_framebuffer = (uint32_t *)0xB8000;

void framebuffer_init(void) {
    framebuffer_clear(0x00000000);
}

void framebuffer_clear(uint32_t color) {
    for (uint32_t i = 0; i < FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT; ++i) {
        g_framebuffer[i] = color;
    }
}

void framebuffer_draw_pixel(uint32_t x, uint32_t y, uint32_t color) {
    if (x < FRAMEBUFFER_WIDTH && y < FRAMEBUFFER_HEIGHT) {
        g_framebuffer[y * FRAMEBUFFER_WIDTH + x] = color;
    }
}

void framebuffer_draw_rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color) {
    for (uint32_t row = 0; row < height; ++row) {
        for (uint32_t col = 0; col < width; ++col) {
            framebuffer_draw_pixel(x + col, y + row, color);
        }
    }
}

void framebuffer_put_char(uint32_t x, uint32_t y, char c, uint32_t fg, uint32_t bg) {
    (void)x;
    (void)y;
    (void)c;
    (void)fg;
    (void)bg;
}

void framebuffer_put_string(uint32_t x, uint32_t y, const char *text, uint32_t fg, uint32_t bg) {
    (void)x;
    (void)y;
    (void)text;
    (void)fg;
    (void)bg;
}
