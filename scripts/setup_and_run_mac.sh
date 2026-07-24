#!/usr/bin/env bash
# MyKernel - macOS Setup, Build & Run Helper Script

set -e

echo "=========================================="
echo "    MyKernel macOS Setup & Run Utility    "
echo "=========================================="

# Check for Homebrew
if ! command -v brew &> /dev/null; then
    echo "[!] Homebrew is not installed. Installing Homebrew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi

echo "[1/3] Checking dependencies..."
if ! command -v make &> /dev/null || ! command -v nasm &> /dev/null || ! command -v qemu-system-x86_64 &> /dev/null; then
    echo "[*] Installing build tools and QEMU via Homebrew..."
    brew install make nasm qemu x86_64-elf-gcc x86_64-elf-binutils || brew install nasm qemu
fi

echo "[2/3] Building kernel binaries..."
if command -v x86_64-elf-gcc &> /dev/null; then
    make CC=x86_64-elf-gcc LD=x86_64-elf-ld all
elif command -v x86_64-linux-gnu-gcc &> /dev/null; then
    make CC=x86_64-linux-gnu-gcc LD=x86_64-linux-gnu-ld all
else
    make CC=gcc LD=ld all
fi

echo "[3/3] Launching MyKernel in QEMU..."
if command -v qemu-system-x86_64 &> /dev/null; then
    qemu-system-x86_64 -kernel build/mykernel.elf -serial stdio
else
    echo "[-] qemu-system-x86_64 not found. Please install via: brew install qemu"
    exit 1
fi
