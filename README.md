# MyKernel

MyKernel is a minimal educational 64-bit operating system kernel written in C and NASM assembly.

## Phase 1 goals

- Boot via GRUB2 Multiboot2
- Enter long mode
- Initialize the stack and basic kernel entry point
- Clear the VGA text screen
- Print the boot banner
- Halt in a safe loop

## Build

On a machine with the required cross toolchain installed:

```sh
make
```

## Run with QEMU

```sh
qemu-system-x86_64 -kernel build/mykernel.elf -serial stdio
```

## Expected output

```text
Welcome to MyKernel
Kernel Loaded Successfully
```

## Notes

This repository is intentionally small and conservative so the first boot stage remains understandable.

