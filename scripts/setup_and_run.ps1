# MyKernel - Automated Download, Build & Run Helper Script for Windows PowerShell

Write-Host "==========================================" -ForegroundColor Cyan
Write-Host "      MyKernel Setup & Run Utility        " -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan

# Check if WSL or Docker or native build tools exist
if (Get-Command wsl -ErrorAction SilentlyContinue) {
    Write-Host "[+] Launching build environment in WSL..." -ForegroundColor Green
    wsl bash -c "sudo apt update && sudo apt install -y build-essential nasm qemu-system-x86 gcc-x86-64-linux-gnu && make CC=x86_64-linux-gnu-gcc LD=x86_64-linux-gnu-ld all && make run"
} else {
    Write-Host "[-] WSL not detected. Please install WSL (Windows Subsystem for Linux) or gcc/nasm cross toolchain to build MyKernel." -ForegroundColor Yellow
}
