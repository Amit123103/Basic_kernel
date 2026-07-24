# 🚀 MyKernel: 64-Bit x86_64 Operating System Kernel

![Build and Release](https://github.com/Amit123103/Basic_kernel/actions/workflows/release.yml/badge.svg)
![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)
![Platform: x86_64](https://img.shields.io/badge/Platform-x86__64-orange.svg)
![OS Support: Windows | macOS | Linux](https://img.shields.io/badge/OS%20Support-Windows%20%7C%20macOS%20%7C%20Linux-green.svg)

**MyKernel** is a complete, educational, modular **64-bit operating system kernel** built from scratch in C and NASM assembly for the `x86_64` architecture. It features long-mode booting via Multiboot2, virtual memory paging, physical page allocation, kernel heap management, process scheduling, virtual filesystem (VFS) with FAT32 support, a complete network stack (Ethernet/ARP/IPv4/ICMP/UDP/TCP/DHCP), device drivers, IPC primitives, and an interactive kernel shell.

---

## 📋 Table of Contents

- [Features & Subsystem Architecture](#-features--subsystem-architecture)
- [Quick Start: Download Prebuilt Releases](#-quick-start-download-prebuilt-releases)
  - [🪟 Windows Setup & Run](#-windows-setup--run)
  - [🍎 macOS Setup & Run](#-macos-setup--run)
  - [🐧 Linux Setup & Run](#-linux-setup--run)
- [Building from Source](#-building-from-source)
  - [1. Prerequisites](#1-prerequisites)
  - [2. Automated Build Scripts](#2-automated-build-scripts)
  - [3. Manual Compilation & ISO Creation](#3-manual-compilation--iso-creation)
- [Architecture & Repository Structure](#-architecture--repository-structure)
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

## ⚡ Quick Start: Download Prebuilt Releases

If you want to run **MyKernel** immediately without installing compilers or building from source:

1. Navigate to [**GitHub Releases**](https://github.com/Amit123103/Basic_kernel/releases/latest).
2. Download **`mykernel-v1.0.6.zip`** (or individual `mykernel.elf` / `mykernel.iso` binaries).
3. Extract the archive and follow your operating system's launcher instructions below:

---

### 🪟 Windows Setup & Run

#### Option A: One-Click Batch Launcher
1. Open PowerShell as Administrator (once) to install QEMU if you don't have it:
   ```powershell
   winget install SoftwareFreedomConservancy.QEMU
   ```
2. Double-click **`run-windows.bat`** in the extracted release folder.

#### Option B: PowerShell Script
```powershell
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
.\scripts\run-windows.ps1
```

---

### 🍎 macOS Setup & Run (Apple Silicon M1/M2/M3/M4 & Intel)

1. Install QEMU using [Homebrew](https://brew.sh):
   ```bash
   brew install qemu
   ```
2. Run the automated macOS launcher:
   ```bash
   chmod +x scripts/run-macos.sh
   ./scripts/run-macos.sh
   ```

---

### 🐧 Linux Setup & Run (Ubuntu / Debian / Fedora / Arch)

1. Install QEMU for your distribution:
   ```bash
   # Ubuntu / Debian / WSL2
   sudo apt-get update && sudo apt-get install -y qemu-system-x86

   # Fedora / RHEL
   sudo dnf install qemu-system-x86

   # Arch Linux
   sudo pacman -S qemu-desktop
   ```
2. Run the Linux launcher:
   ```bash
   chmod +x scripts/run-linux.sh
   ./scripts/run-linux.sh
   ```

---

## 🛠️ Building from Source

### 1. Prerequisites

Ensure you have the required cross-compilation tools and emulators installed on your host system:

| Tool | Purpose | Ubuntu/Debian Command | macOS Command |
| :--- | :--- | :--- | :--- |
| `make` | Build Automation | `sudo apt install build-essential` | `brew install make` |
| `nasm` | x86_64 Assembler | `sudo apt install nasm` | `brew install nasm` |
| `gcc-x86-64-linux-gnu` | 64-bit C Cross Compiler | `sudo apt install gcc-x86-64-linux-gnu` | `brew install x86_64-elf-gcc` |
| `qemu-system-x86_64` | System Emulator | `sudo apt install qemu-system-x86` | `brew install qemu` |
| `xorriso` & `grub-pc-bin` | ISO Image Generation | `sudo apt install xorriso grub-pc-bin mtools` | `brew install xorriso` |

---

### 2. Automated Build Scripts

We provide automated setup and execution scripts for every platform:

```bash
# Clone the repository
git clone https://github.com/Amit123103/Basic_kernel.git
cd Basic_kernel
```

- **Windows (PowerShell)**:
  ```powershell
  .\scripts\setup_and_run.ps1
  ```
- **macOS**:
  ```bash
  chmod +x scripts/setup_and_run_mac.sh
  ./scripts/setup_and_run_mac.sh
  ```
- **Linux / WSL**:
  ```bash
  chmod +x scripts/setup_and_run.sh
  ./scripts/setup_and_run.sh
  ```

---

### 3. Manual Compilation & ISO Creation

You can also use standard `make` targets to build and package MyKernel:

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

## 📂 Architecture & Repository Structure

```text
My_Kernel/
├── .github/
│   └── workflows/
│       └── release.yml         # GitHub Actions multi-platform CI/CD release workflow
├── arch/                       # CPU Architecture (x86_64)
│   ├── gdt.c / gdt.h           # Global Descriptor Table & TSS
│   ├── idt.c / idt.h           # Interrupt Descriptor Table & Gates
│   └── isr.asm                 # Assembly Interrupt Service Routines & IRQ Handlers
├── boot/
│   ├── boot.asm                # Multiboot2 entry point & Long Mode switcher
│   └── grub.cfg                # GRUB2 Bootloader Configuration
├── drivers/                    # Hardware Drivers
│   ├── vga.c                   # VGA Text (80x25) & Graphics Driver
│   ├── serial.c                # Serial COM1 UART Driver
│   ├── keyboard.c              # PS/2 Keyboard Scancode Decoder
│   ├── pit.c                   # Programmable Interval Timer (1193182 Hz)
│   ├── rtc.c                   # Real Time Clock (CMOS)
│   └── speaker.c               # PC Speaker Frequency Generator
├── memory/                     # Memory Management
│   ├── pmm.c                   # Physical Memory Manager (Bitmap Page Allocator)
│   ├── vmm.c                   # Virtual Memory Manager (Paging & Page Tables)
│   └── heap.c                  # Kernel Heap Allocator (kmalloc / kfree)
├── fs/                         # Filesystem Layer
│   ├── vfs.c                   # Virtual File System Node Abstraction
│   └── fat32.c                 # FAT32 Partition Reader Driver
├── journalfs/                  # Journaling Filesystem (Log Safety)
├── network/                    # Full TCPIP Network Stack
│   ├── ethernet.c              # Layer 2 Ethernet Frame Parser
│   ├── arp.c                   # Address Resolution Protocol (ARP)
│   ├── ipv4.c                  # Layer 3 IPv4 Protocol Handling
│   ├── icmp.c                  # ICMP Protocol (Ping Echo/Reply)
│   ├── udp.c                   # User Datagram Protocol Sockets
│   ├── tcp.c                   # Transmission Control Protocol State Machine
│   └── dhcp.c                  # DHCP Client Dynamic IP Allocation
├── ipc/                        # Inter-Process Communication
│   ├── spinlock.c              # Hardware Atomic Spinlocks
│   ├── mutex.c                 # Sleeping Mutex Locks
│   ├── msg_queue.c             # IPC Message Queues
│   ├── pipe.c                  # Ring Buffer IPC Pipes
│   └── shm.c                   # Shared Memory Subsystem
├── process/                    # Process Management
│   ├── process.c               # Task Control Block (PCB) & Scheduler
│   └── context.asm             # Hardware Context Switching Assembly
├── syscall/                    # System Calls
│   └── syscall.c               # System Call Handler & Gate Dispatcher
├── graphics/                   # Graphical Display Utilities
├── audio/                      # Audio Drivers & Sound Interface
├── crypto/                     # Hashing (SHA256/MD5) & Checksums
├── security/                   # Access Control & Verification
├── power/                      # ACPI Power Management (Reboot / Shutdown)
├── time/                       # System Clocks & Delay Functions
├── shell/                      # Interactive Built-in Kernel CLI Shell
├── logging/                    # Structured Kernel Logger (kprintf)
├── debug/                      # Kernel Panic & Stack Trace Debugger
├── libc/                       # Freestanding C Standard Library
├── include/                    # Global Kernel Header Files
├── scripts/                    # Cross-Platform Launcher & Setup Scripts
│   ├── setup_and_run.sh        # Linux / WSL setup script
│   ├── setup_and_run_mac.sh    # macOS setup script
│   ├── setup_and_run.ps1       # Windows PowerShell setup script
│   ├── run-windows.bat         # Windows double-click launcher
│   ├── run-windows.ps1         # Windows PowerShell launcher
│   ├── run-macos.sh            # macOS launcher
│   └── run-linux.sh            # Linux launcher
├── linker.ld                   # 64-bit ELF Kernel Linker Script
├── Makefile                    # Modular Makefile
└── README.md                   # Project Documentation
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
