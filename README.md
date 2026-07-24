# MyKernel

MyKernel is a minimal educational 64-bit operating system kernel written in C and NASM assembly for x86_64 architecture.

## Features & Subsystems

- **Boot Protocol**: Multiboot2 compliant bootloader integration (GRUB2 compatible).
- **Core Architecture**: x86_64 Long Mode initialization, GDT, IDT, TSS, and Exception/Interrupt handlers.
- **Memory Management**: Physical Page Allocator (PMM), Virtual Memory (VMM) paging, and Kernel Heap (`kmalloc`/`kfree`).
- **Drivers**: VGA Text/Graphics, Serial COM1, Keyboard Scancode Decoder, PIT Timer, RTC, and PC Speaker.
- **IPC & Synchronization**: Spinlocks, Mutexes, Inter-Process Message Queues, Ring Buffer Pipes, and Shared Memory.
- **Filesystem & Storage**: Virtual File System (VFS), FAT32 reader, and JournalFS log structure.
- **Networking Stack**: Ethernet, ARP, IPv4, ICMP (Ping), UDP, TCP, and DHCP client protocol abstractions.
- **Power & Security**: ACPI Shutdown/Reboot, Crypto checksums, and Security hash verifiers.

---

## Download & Quick Start

### 1. Clone/Download the Repository

```bash
git clone https://github.com/Amit123103/Basic_kernel.git
cd Basic_kernel
```

### 2. Automated One-Command Setup & Run

#### On Linux / WSL (Debian/Ubuntu):
```bash
chmod +x scripts/setup_and_run.sh
./scripts/setup_and_run.sh
```

#### On Windows PowerShell:
```powershell
.\scripts\setup_and_run.ps1
```

---

## Manual Build & Execution

### Prerequisites

Install the build dependencies:

```bash
# Ubuntu / Debian / WSL
sudo apt-get update
sudo apt-get install -y build-essential nasm qemu-system-x86 gcc-x86-64-linux-gnu
```

### Build

```bash
make all
```

### Run with QEMU

```bash
make run
```

---

## Expected Output

```text
Welcome to MyKernel
Kernel Loaded Successfully
Phase 5: drivers ready
MyKernel serial driver initialized
Heap allocation test complete
```

---

## License

This project is open source and distributed under the terms of the MIT License.
