# MyKernel - Windows Automated Setup & Run Script

Write-Host "==========================================" -ForegroundColor Cyan
Write-Host "   MyKernel - Windows Setup & Run Utility " -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan

# Add QEMU to PATH if present
if (Test-Path "C:\Program Files\qemu") {
    if ($env:Path -notlike "*C:\Program Files\qemu*") {
        $env:Path += ";C:\Program Files\qemu"
    }
}

# Ensure build directory exists
if (-not (Test-Path "build")) {
    New-Item -ItemType Directory -Force -Path "build" | Out-Null
}

# Try downloading prebuilt binary if missing locally
if (-not (Test-Path "build\mykernel.elf") -or ((Get-Item "build\mykernel.elf").Length -lt 100)) {
    Write-Host "[*] Fetching prebuilt kernel binary from GitHub Releases..." -ForegroundColor Yellow
    curl.exe -sSL "https://github.com/Amit123103/Basic_kernel/releases/latest/download/mykernel.elf" -o "build/mykernel.elf"
}

# Launch QEMU natively
$qemuExe = "C:\Program Files\qemu\qemu-system-x86_64.exe"
if (Test-Path $qemuExe) {
    Write-Host "[+] Launching MyKernel in QEMU..." -ForegroundColor Green
    & $qemuExe -kernel build/mykernel.elf -serial stdio
} elseif (Get-Command qemu-system-x86_64 -ErrorAction SilentlyContinue) {
    Write-Host "[+] Launching MyKernel in QEMU..." -ForegroundColor Green
    qemu-system-x86_64 -kernel build/mykernel.elf -serial stdio
} else {
    Write-Host "[-] QEMU executable not found. Please install QEMU via winget install SoftwareFreedomConservancy.QEMU" -ForegroundColor Red
}
