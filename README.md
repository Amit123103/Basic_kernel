# 🚀 MyKernel: 64-Bit x86_64 Operating System Kernel

![Build and Release](https://github.com/Amit123103/Basic_kernel/actions/workflows/release.yml/badge.svg)
![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)
![Platform: x86_64](https://img.shields.io/badge/Platform-x86__64-orange.svg)
![OS Support: Windows | macOS | Linux](https://img.shields.io/badge/OS%20Support-Windows%20%7C%20macOS%20%7C%20Linux-green.svg)

**MyKernel** is a complete, educational, modular **64-bit operating system kernel** built from scratch in C and NASM assembly for the `x86_64` architecture. It features long-mode booting via Multiboot2, virtual memory paging, physical page allocation, kernel heap management, process scheduling, virtual filesystem (VFS) with FAT32 support, a complete network stack (Ethernet/ARP/IPv4/ICMP/UDP/TCP/DHCP), device drivers, IPC primitives, and an interactive kernel shell.

---

## 📋 Table of Contents

- [Features & Subsystem Architecture](#-features--subsystem-architecture)
- [Installation Guide](#-installation-guide)
  - [🪟 Windows Installation](#-windows-installation)
  - [🍎 macOS Installation](#-macos-installation)
  - [🐧 Linux Installation](#-linux-installation)
- [Quick Start: Download Prebuilt Releases](#-quick-start-download-prebuilt-releases)
- [Building from Source](#-building-from-source)
- [Kernel Subsystems Overview](#-kernel-subsystems-overview)
- [QEMU Command Reference](#-qemu-command-reference)
- [Troubleshooting](#-troubleshooting)
- [License](#-license)

---

## ✨ Features & Subsystem Architecture

| Subsystem | Key Capabilities & Features |
| :--- | :--- |
| **Bootloader** | **Multiboot2 Specification** compliant, GRUB2 bootable, long-mode (64-bit) trampoline |
| **CPU & Interrupts** | GDT, 64-bit IDT (Interrupt Descriptor Table), TSS (Task State Segment), Exception Gate Handlers |
| **Memory Management** | Bitmap Physical Page Allocator (PMM), Virtual Memory (VMM) 4-level Paging, Kernel Heap (`kmalloc`/`kfree`) |
| **Hardware Drivers** | VGA Text (80x25) & Graphics, Serial COM1 UART (`115200` baud), PS/2 Keyboard, PIT Timer (1193182 Hz), RTC, PC Speaker |
| **Processes & IPC** | Context Switching, Thread Scheduler, Spinlocks, Mutexes, Inter-Process Message Queues, Ring Buffer Pipes, Shared Memory |
| **Filesystem (VFS)** | Virtual File System abstraction, FAT32 partition reader/driver, Log-structured JournalFS |
| **Networking Stack** | Ethernet Frames, ARP Table, IPv4 Protocol, ICMP Ping, UDP Sockets, TCP State Machine, DHCP Client |
| **Power & Security** | ACPI Power Off & Reboot, Cryptographic Checksums (SHA256, MD5), Access Control Verifiers |
| **Kernel Utilities** | Interactive Kernel Shell CLI, Structured Logger (`kprintf`), Stack Trace Debugger, Freestanding C Standard Library |

---

## 📥 Installation Guide

Follow the installation instructions for your operating system below to set up **MyKernel** and its required emulators/compilers.

### 🪟 Windows Installation

1. **Install QEMU Emulator**:
   Open PowerShell as Administrator and run:
   ```powershell
   winget install SoftwareFreedomConservancy.QEMU
   ```
   *(Alternatively, download the Windows installer directly from [qemu.org](https://www.qemu.org/download/#windows)).*

2. **Clone the Repository**:
   ```powershell
   git clone https://github.com/Amit123103/Basic_kernel.git
   cd Basic_kernel
   ```

3. **Run Automated Setup Script**:
   ```powershell
   Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
   .\scripts\setup_and_run.ps1
   ```

---

### 🍎 macOS Installation (Apple Silicon M1/M2/M3/M4 & Intel)

1. **Install Homebrew** (if not already installed):
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```

2. **Install QEMU & Cross-Compiler Tools**:
   ```bash
   brew install qemu nasm make x86_64-elf-gcc x86_64-elf-binutils xorriso
   ```

3. **Clone the Repository & Run Setup**:
   ```bash
   git clone https://github.com/Amit123103/Basic_kernel.git
   cd Basic_kernel
   chmod +x scripts/setup_and_run_mac.sh
   ./scripts/setup_and_run_mac.sh
   ```

---

### 🐧 Linux Installation (Ubuntu / Debian / Fedora / Arch)

1. **Install Build Tools & QEMU**:

   - **Ubuntu / Debian / WSL2**:
     ```bash
     sudo apt-get update
     sudo apt-get install -y build-essential nasm qemu-system-x86 gcc-x86-64-linux-gnu xorriso grub-pc-bin mtools
     ```
   - **Fedora / RHEL**:
     ```bash
     sudo dnf install -y gcc make nasm qemu-system-x86 xorriso grub2-tools-extra
     ```
   - **Arch Linux**:
     ```bash
     sudo pacman -S --needed base-devel nasm qemu-desktop xorriso grub
     ```

2. **Clone the Repository & Run Setup**:
   ```bash
   git clone https://github.com/Amit123103/Basic_kernel.git
   cd Basic_kernel
   chmod +x scripts/setup_and_run.sh
   ./scripts/setup_and_run.sh
   ```

---

## ⚡ Quick Start: Download Prebuilt Releases

If you want to run **MyKernel** immediately without compiling from source:

1. Navigate to [**GitHub Releases**](https://github.com/Amit123103/Basic_kernel/releases/latest).
2. Download **`mykernel-v1.0.6.zip`** (or individual `mykernel.elf` / `mykernel.iso` binaries).
3. Extract the zip archive and run the launcher script for your platform:
   - **Windows**: Double-click `run-windows.bat` or run `.\scripts\run-windows.ps1`
   - **macOS**: Run `chmod +x scripts/run-macos.sh && ./scripts/run-macos.sh`
   - **Linux**: Run `chmod +x scripts/run-linux.sh && ./scripts/run-linux.sh`

---

## 🛠️ Building from Source

### Manual Compilation & ISO Creation

You can use standard `make` targets to build and package MyKernel:

#### Build Kernel ELF Executable (`build/mykernel.elf`):
```bash
make CC=x86_64-linux-gnu-gcc LD=x86_64-linux-gnu-ld all
```

#### Build Bootable ISO Image (`build/mykernel.iso`):
```bash
mkdir -p iso/boot/grub
cp build/mykernel.elf iso/boot/mykernel.elf
cp boot/grub.cfg iso/boot/grub/grub.cfg
grub-mkrescue -o build/mykernel.iso iso/
```

#### Execute in QEMU:
```bash
# Run raw 64-bit ELF image with serial console output
qemu-system-x86_64 -kernel build/mykernel.elf -serial stdio

# Boot full ISO image
qemu-system-x86_64 -cdrom build/mykernel.iso
```

#### Clean Build Artifacts:
```bash
make clean
```

---

## 💻 Kernel Subsystems Overview

### 1. Boot & Architecture (`boot/`, `arch/`)
- **Multiboot2 Protocol**: Complies with Multiboot2 specification, allowing GRUB2 to load the kernel, pass memory maps, and provide framebuffer details.
- **64-Bit Long Mode Transition**: Sets up 64-bit page tables, enables PAE and Long Mode flags in EFER MSR, and jumps into 64-bit code segment.
- **GDT & TSS**: Configures 64-bit Global Descriptor Table with Code/Data descriptors and Task State Segment for interrupt stacks.
- **IDT & ISRs**: Maps all 256 Interrupt Descriptor Table vectors, capturing CPU exceptions (Page Faults, GPF, Division by Zero) and hardware IRQs (Keyboard, PIT Timer, Serial).

### 2. Memory Subsystem (`memory/`)
- **PMM (Physical Memory Manager)**: Manages physical RAM frames using a fast bitmap allocator operating at 4 KiB frame granularity.
- **VMM (Virtual Memory Manager)**: Sets up 4-level paging (PML4, PDPT, PD, PT) with identity mapping for kernel space and virtual mapping for user space.
- **Kernel Heap (`heap.c`)**: Provides dynamic memory allocation primitives (`kmalloc`, `kfree`, `krealloc`) with block splitting and merging.

### 3. Drivers & I/O (`drivers/`)
- **VGA Driver**: Text-mode console supporting color attributes, scrolling, cursor positioning, and screen clearing.
- **Serial COM1 UART**: Serial port output mapped to host terminal (`stdio`) for logging and debugging.
- **PS/2 Keyboard**: Interrupt-driven scancode parser with modifier key handling (Shift, Control, Alt).
- **PIT Timer & RTC**: Programmable Interval Timer set to 100 Hz tick rate for process scheduling, combined with Real Time Clock CMOS readout.

### 4. Networking Stack (`network/`)
- Implements a complete zero-copy network layer hierarchy:
  $$\text{Ethernet} \longrightarrow \text{ARP / IPv4} \longrightarrow \text{ICMP / UDP / TCP} \longrightarrow \text{DHCP Client}$$
- Capable of responding to ICMP Echo Requests (Ping), opening UDP sockets, establishing TCP state transitions (SYN/ACK/ESTABLISHED), and requesting IP address leases via DHCP.

---

## 🖥️ QEMU Command Reference

### Recommended Running Command:
```bash
qemu-system-x86_64 \
  -kernel build/mykernel.elf \
  -serial stdio \
  -m 512M \
  -display default
```

### Useful QEMU Shortcut Keys:
- **`Ctrl + A` then `X`**: Quit QEMU when running in serial terminal mode.
- **`Ctrl + Alt + G`**: Release mouse/keyboard input focus from QEMU window.
- **`Ctrl + Alt + 2`**: Switch to QEMU Monitor console (type `info registers`, `info memory`).
- **`Ctrl + Alt + 1`**: Switch back to main kernel display.

---

## ❓ Troubleshooting

#### Q: QEMU shows `qemu-system-x86_64: command not found` on Windows.
- **Fix**: Run PowerShell script `.\scripts\run-windows.ps1` or install QEMU using:
  ```powershell
  winget install SoftwareFreedomConservancy.QEMU
  ```
  Ensure `C:\Program Files\qemu` is added to your environment `PATH`.

#### Q: `make: gcc-x86-64-linux-gnu: Command not found` on Linux/WSL.
- **Fix**: Install the x86_64 cross-compiler:
  ```bash
  sudo apt install gcc-x86-64-linux-gnu
  ```

#### Q: macOS shows `x86_64-elf-gcc: command not found`.
- **Fix**: Run `scripts/setup_and_run_mac.sh` or install cross compiler via Homebrew:
  ```bash
  brew install x86_64-elf-gcc x86_64-elf-binutils
  ```

---

## 📜 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for full details. Open source and free for educational and commercial use.
