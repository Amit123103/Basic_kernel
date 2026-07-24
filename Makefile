CC ?= x86_64-elf-gcc
LD ?= x86_64-elf-ld
ASM ?= nasm
QEMU ?= qemu-system-x86_64

CFLAGS := -ffreestanding -fno-stack-protector -fno-pic -mno-red-zone -Wall -Wextra -O2 -std=c11 -Iinclude -I.
LDFLAGS := -nostdlib -static -T linker.ld -z max-page-size=0x1000
ASMFLAGS := -f elf64

BUILD_DIR := build
OBJS := $(BUILD_DIR)/boot/boot.o \
	$(BUILD_DIR)/boot/multiboot.o \
	$(BUILD_DIR)/kernel/main.o \
	$(BUILD_DIR)/kernel/kernel.o \
	$(BUILD_DIR)/arch/x86_64/gdt.o \
	$(BUILD_DIR)/arch/x86_64/idt.o \
	$(BUILD_DIR)/arch/x86_64/cpu.o \
	$(BUILD_DIR)/arch/x86_64/paging.o \
	$(BUILD_DIR)/drivers/vga.o \
	$(BUILD_DIR)/kernel/panic.o \
	$(BUILD_DIR)/libc/string.o \
	$(BUILD_DIR)/network/network.o \
	$(BUILD_DIR)/network/pci.o \
	$(BUILD_DIR)/network/ethernet.o \
	$(BUILD_DIR)/network/arp.o \
	$(BUILD_DIR)/network/ipv4.o \
	$(BUILD_DIR)/network/icmp.o \
	$(BUILD_DIR)/network/udp.o \
	$(BUILD_DIR)/network/tcp.o \
	$(BUILD_DIR)/network/dhcp.o \
	$(BUILD_DIR)/power/acpi.o \
	$(BUILD_DIR)/security/security.o \
	$(BUILD_DIR)/audio/audio.o \
	$(BUILD_DIR)/logging/logging.o \
	$(BUILD_DIR)/compression/compression.o \
	$(BUILD_DIR)/firmware/firmware.o \
	$(BUILD_DIR)/debug/debug.o \
	$(BUILD_DIR)/crypto/crypto.o \
	$(BUILD_DIR)/journalfs/journalfs.o \
	$(BUILD_DIR)/time/time.o

.PHONY: all clean run

all: $(BUILD_DIR)/mykernel.elf

$(BUILD_DIR)/mykernel.elf: $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/boot/%.o: boot/%.asm
	@mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) -o $@ $<

$(BUILD_DIR)/kernel/%.o: kernel/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/arch/x86_64/%.o: arch/x86_64/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/drivers/%.o: drivers/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/libc/%.o: libc/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/network/%.o: network/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/power/%.o: power/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/security/%.o: security/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/audio/%.o: audio/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/logging/%.o: logging/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/compression/%.o: compression/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/firmware/%.o: firmware/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/debug/%.o: debug/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/crypto/%.o: crypto/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/journalfs/%.o: journalfs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/time/%.o: time/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BUILD_DIR)/mykernel.elf
	$(QEMU) -kernel $(BUILD_DIR)/mykernel.elf -serial stdio

clean:
	rm -rf $(BUILD_DIR)
