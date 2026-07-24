#include "kernel.h"

void kernel_main(void) {
    gdt_init();
    idt_init();
    paging_init();
    pmm_init();
    vmm_init();
    heap_init();
    serial_init();
    keyboard_init();
    pit_init(1000);
    rtc_init();
    speaker_init();

    vga_set_color(0x0F, 0x00);
    vga_clear();
    kprintf("Welcome to MyKernel\n");
    kprintf("Kernel Loaded Successfully\n");
    kprintf("Phase 5: drivers ready\n");

    serial_write_string("MyKernel serial driver initialized\n");

    void *ptr = kmalloc(64);
    kprintf("Heap allocation test complete\n");
    (void)ptr;

    shell_init();
    shell_run();
    scheduler_init();
    process_create((uint64_t)kernel_main);
    scheduler_tick();

    uint64_t result = syscall_dispatch(SYSCALL_GETPID, 0, 0, 0);
    (void)result;

    vfs_init();
    fat32_init();
    tss_init();
    user_mode_init();
    user_load_elf("/bin/hello");
    gui_init();
    gui_draw_window(10, 10, 200, 120);
    framebuffer_draw_pixel(20, 20, 0xFFFFFFFF);

    network_init();
    acpi_init();
    security_init();
    audio_init();
    log_init();
    compression_init();
    firmware_init();
    debug_init();
    crypto_init();
    journalfs_init();
    time_init();

    cpu_halt();
}
