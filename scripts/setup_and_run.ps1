# MyKernel - Windows Automated Setup & Run Script

Write-Host "==========================================" -ForegroundColor Cyan
Write-Host "   MyKernel - Windows Setup & Run Utility " -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan

# Step 1: Check if QEMU is installed natively on Windows
$qemuPath = Get-Command qemu-system-x86_64 -ErrorAction SilentlyContinue

if (-not $qemuPath) {
    # Check default QEMU installation paths on Windows
    if (Test-Path "C:\Program Files\qemu\qemu-system-x86_64.exe") {
        $env:Path += ";C:\Program Files\qemu"
        $qemuPath = "C:\Program Files\qemu\qemu-system-x86_64.exe"
    }
}

if (-not $qemuPath) {
    Write-Host "[!] QEMU is not detected on your system." -ForegroundColor Yellow
    Write-Host "[*] Installing QEMU via Winget (or WSL)..." -ForegroundColor Green
    
    if (Get-Command winget -ErrorAction SilentlyContinue) {
        Write-Host "[+] Running: winget install SoftwareFreedomConservancy.QEMU" -ForegroundColor Cyan
        winget install SoftwareFreedomConservancy.QEMU --accept-source-agreements --accept-package-agreements
        $env:Path += ";C:\Program Files\qemu"
    }
}

# Step 2: Run in WSL if WSL is available
if (Get-Command wsl -ErrorAction SilentlyContinue) {
    Write-Host "[+] Building and launching MyKernel via WSL..." -ForegroundColor Green
    wsl bash -c "sudo apt-get update && sudo apt-get install -y build-essential nasm qemu-system-x86 gcc-x86-64-linux-gnu && make CC=x86_64-linux-gnu-gcc LD=x86_64-linux-gnu-ld all && qemu-system-x86_64 -kernel build/mykernel.elf -serial stdio"
} else {
    if (Test-Path "C:\Program Files\qemu\qemu-system-x86_64.exe") {
        & "C:\Program Files\qemu\qemu-system-x86_64.exe" -kernel build/mykernel.elf -serial stdio
    } else {
        Write-Host "[-] Please restart your terminal after QEMU installation and rerun this script." -ForegroundColor Yellow
    }
}
