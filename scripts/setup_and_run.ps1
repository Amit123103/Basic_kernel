# MyKernel - Windows Automated Setup & Run Script

Write-Host "==========================================" -ForegroundColor Cyan
Write-Host "   MyKernel - Windows Setup & Run Utility " -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan

# Add QEMU to PATH if present in standard installation folder
if (Test-Path "C:\Program Files\qemu") {
    if ($env:Path -notlike "*C:\Program Files\qemu*") {
        $env:Path += ";C:\Program Files\qemu"
    }
}

# Step 1: Ensure kernel ELF is built
if (-not (Test-Path "build\mykernel.elf")) {
    if (Get-Command wsl -ErrorAction SilentlyContinue) {
        Write-Host "[+] Building kernel via WSL..." -ForegroundColor Green
        wsl bash -c "make CC=x86_64-linux-gnu-gcc LD=x86_64-linux-gnu-ld all || make all"
    }
}

# Step 2: Launch QEMU natively
$qemuExe = "C:\Program Files\qemu\qemu-system-x86_64.exe"
if (Test-Path $qemuExe) {
    Write-Host "[+] Launching MyKernel in QEMU..." -ForegroundColor Green
    & $qemuExe -kernel build/mykernel.elf -serial stdio
} elseif (Get-Command qemu-system-x86_64 -ErrorAction SilentlyContinue) {
    Write-Host "[+] Launching MyKernel in QEMU..." -ForegroundColor Green
    qemu-system-x86_64 -kernel build/mykernel.elf -serial stdio
} else {
    Write-Host "[-] QEMU executable not found." -ForegroundColor Red
}
