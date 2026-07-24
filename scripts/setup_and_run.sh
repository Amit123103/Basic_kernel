#!/usr/bin/env bash
# MyKernel - Automated Download, Build & Run Helper Script

set -e

echo "=========================================="
echo "      MyKernel Setup & Run Utility        "
echo "=========================================="

# Check for required tools
echo "[1/3] Checking dependencies..."
if ! command -v make &> /dev/null; then
    echo "Error: 'make' is not installed."
    echo "Install via: sudo apt install build-essential"
    exit 1
fi

if ! command -v nasm &> /dev/null; then
    echo "Error: 'nasm' assembler is not installed."
    echo "Install via: sudo apt install nasm"
    exit 1
fi

if ! command -v qemu-system-x86_64 &> /dev/null; then
    echo "Error: 'qemu-system-x86_64' emulator is not installed."
    echo "Install via: sudo apt install qemu-system-x86"
    exit 1
fi

echo "[2/3] Building kernel binaries..."
if command -v x86_64-elf-gcc &> /dev/null; then
    make all
elif command -v x86_64-linux-gnu-gcc &> /dev/null; then
    make CC=x86_64-linux-gnu-gcc LD=x86_64-linux-gnu-ld all
else
    make CC=gcc LD=ld all
fi

echo "[3/3] Launching MyKernel in QEMU..."
make run
