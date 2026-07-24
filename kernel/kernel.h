#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define VGA_MEMORY ((volatile uint16_t *)0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void vga_clear(void);
void vga_write_string(const char *text);
void vga_write_char(char c);
void vga_set_color(uint8_t fg, uint8_t bg);
void vga_set_cursor(uint8_t row, uint8_t col);
void kernel_main(void);
void kernel_panic(const char *message);
void gdt_init(void);
void idt_init(void);
void paging_init(void);
void cpu_halt(void);
void pmm_init(void);
void vmm_init(void);
void heap_init(void);
void *kmalloc(size_t size);
void kfree(void *ptr);
void serial_init(void);
void serial_write_string(const char *text);
uint8_t serial_read_byte(void);
void keyboard_init(void);
uint8_t keyboard_read_scancode(void);
void pit_init(uint32_t hz);
void pit_wait(uint32_t ticks);
void rtc_init(void);
uint8_t rtc_read_register(uint8_t reg);
void speaker_init(void);
void speaker_beep(uint32_t frequency);
void shell_init(void);
void shell_run(void);
void process_init(void);
uint32_t process_create(uint64_t entry_point);
void scheduler_yield(void);
void scheduler_sleep(uint32_t ticks);
void scheduler_init(void);
void scheduler_tick(void);
uint64_t syscall_dispatch(uint64_t number, uint64_t arg0, uint64_t arg1, uint64_t arg2);
void vfs_init(void);
int vfs_open(const char *path);
int vfs_read(int fd, void *buffer, size_t size);
int vfs_write(int fd, const void *buffer, size_t size);
int vfs_list_dir(void *out_dir);
void fat32_init(void);
int fat32_read_boot_sector(void);
void user_mode_init(void);
int user_load_elf(const char *path);
void tss_init(void);
void framebuffer_init(void);
void framebuffer_clear(uint32_t color);
void framebuffer_draw_pixel(uint32_t x, uint32_t y, uint32_t color);
void framebuffer_draw_rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color);
void gui_init(void);
void gui_draw_window(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void network_init(void);
void pci_init(void);
void ethernet_init(void);
void arp_init(void);
void ipv4_init(void);
void icmp_init(void);
void udp_init(void);
void tcp_init(void);
void dhcp_init(void);
void acpi_init(void);
void acpi_reboot(void);
void acpi_shutdown(void);
void security_init(void);
uint32_t security_hash_string(const char *text);
int security_verify_integrity(const char *text);
void audio_init(void);
void audio_beep(uint32_t frequency, uint32_t duration_ms);
void audio_play_melody(void);
void log_init(void);
void log_info(const char *message);
void log_warn(const char *message);
void log_error(const char *message);
void compression_init(void);
uint32_t compression_rle_encode(const char *input, char *output, uint32_t input_length);
uint32_t compression_rle_decode(const char *input, char *output, uint32_t input_length);
void firmware_init(void);
uint32_t firmware_detect_vendor(void);
uint32_t firmware_detect_revision(void);
void debug_init(void);
void debug_trace(const char *message);
void debug_dump_registers(void);

#endif
