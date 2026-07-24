#!/usr/bin/env bash
# MyKernel - Linux QEMU Launcher

set -e

echo "=========================================="
echo "      MyKernel - Linux QEMU Launcher      "
echo "=========================================="

ELF_PATH=""
if [ -f "build/mykernel.elf" ]; then
    ELF_PATH="build/mykernel.elf"
elif [ -f "mykernel.elf" ]; then
    ELF_PATH="mykernel.elf"
fi

ISO_PATH=""
if [ -f "build/mykernel.iso" ]; then
    ISO_PATH="build/mykernel.iso"
elif [ -f "mykernel.iso" ]; then
    ISO_PATH="mykernel.iso"
fi

if ! command -v qemu-system-x86_64 &> /dev/null; then
    echo "[-] QEMU is not installed."
    echo "[*] Install on Ubuntu/Debian: sudo apt install qemu-system-x86"
    echo "[*] Install on Fedora/RHEL:   sudo dnf install qemu-system-x86"
    echo "[*] Install on Arch Linux:   sudo pacman -S qemu-desktop"
    exit 1
fi

if [ -n "$ELF_PATH" ]; then
    echo "[+] Launching MyKernel ($ELF_PATH) in QEMU..."
    qemu-system-x86_64 -kernel "$ELF_PATH" -serial stdio
elif [ -n "$ISO_PATH" ]; then
    echo "[+] Booting MyKernel ISO ($ISO_PATH) in QEMU..."
    qemu-system-x86_64 -cdrom "$ISO_PATH"
else
    echo "[-] Error: mykernel.elf or mykernel.iso not found."
    exit 1
fi
