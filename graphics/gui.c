#include "kernel.h"
#include "graphics/framebuffer.h"
#include "graphics/gui.h"

void gui_init(void) {
    framebuffer_init();
}

void gui_draw_window(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    framebuffer_draw_rect(x, y, width, height, 0x00FF00FF);
}
