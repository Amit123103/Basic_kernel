#include "kernel.h"

static uint16_t *const vga_buffer = VGA_MEMORY;
static uint8_t g_cursor_row = 0;
static uint8_t g_cursor_col = 0;
static uint8_t g_foreground_color = 0x0F;
static uint8_t g_background_color = 0x00;

static void vga_scroll(void) {
    for (uint8_t row = 1; row < VGA_HEIGHT; ++row) {
        for (uint8_t col = 0; col < VGA_WIDTH; ++col) {
            uint16_t cell = vga_buffer[row * VGA_WIDTH + col];
            vga_buffer[(row - 1) * VGA_WIDTH + col] = cell;
        }
    }

    for (uint8_t col = 0; col < VGA_WIDTH; ++col) {
        vga_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + col] = (uint16_t)(((g_foreground_color | (g_background_color << 4)) << 8) | ' ');
    }
}

void vga_set_color(uint8_t fg, uint8_t bg) {
    g_foreground_color = fg & 0x0F;
    g_background_color = bg & 0x0F;
}

void vga_set_cursor(uint8_t row, uint8_t col) {
    g_cursor_row = row;
    g_cursor_col = col;
}

void vga_clear(void) {
    for (uint16_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i) {
        vga_buffer[i] = (uint16_t)(((g_foreground_color | (g_background_color << 4)) << 8) | ' ');
    }
    g_cursor_row = 0;
    g_cursor_col = 0;
}

void vga_write_char(char c) {
    uint8_t attr = (uint8_t)((g_foreground_color | (g_background_color << 4)));

    if (c == '\n') {
        g_cursor_row++;
        g_cursor_col = 0;
    } else if (c == '\r') {
        g_cursor_col = 0;
    } else if (c == '\b') {
        if (g_cursor_col > 0) {
            g_cursor_col--;
            vga_buffer[g_cursor_row * VGA_WIDTH + g_cursor_col] = (uint16_t)(attr << 8) | ' ';
        }
    } else {
        if (g_cursor_row >= VGA_HEIGHT) {
            vga_scroll();
            g_cursor_row = VGA_HEIGHT - 1;
        }

        vga_buffer[g_cursor_row * VGA_WIDTH + g_cursor_col] = (uint16_t)(attr << 8) | (unsigned char)c;
        g_cursor_col++;

        if (g_cursor_col >= VGA_WIDTH) {
            g_cursor_col = 0;
            g_cursor_row++;
        }
    }

    if (g_cursor_row >= VGA_HEIGHT) {
        vga_scroll();
        g_cursor_row = VGA_HEIGHT - 1;
    }
}

void vga_write_string(const char *text) {
    while (*text != '\0') {
        vga_write_char(*text++);
    }
}
