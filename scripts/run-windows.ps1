# MyKernel - Windows PowerShell QEMU Launcher

Write-Host "==========================================" -ForegroundColor Cyan
Write-Host "   MyKernel - Windows QEMU Launcher       " -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan

# Add QEMU to PATH if present
if (Test-Path "C:\Program Files\qemu") {
    if ($env:Path -notlike "*C:\Program Files\qemu*") {
        $env:Path += ";C:\Program Files\qemu"
    }
}

$elfPath = if (Test-Path "build\mykernel.elf") { "build\mykernel.elf" } elseif (Test-Path "mykernel.elf") { "mykernel.elf" } else { $null }
$isoPath = if (Test-Path "build\mykernel.iso") { "build\mykernel.iso" } elseif (Test-Path "mykernel.iso") { "mykernel.iso" } else { $null }

$qemuExe = Get-Command qemu-system-x86_64 -ErrorAction SilentlyContinue

if ($qemuExe -or (Test-Path "C:\Program Files\qemu\qemu-system-x86_64.exe")) {
    $cmd = if ($qemuExe) { "qemu-system-x86_64" } else { "C:\Program Files\qemu\qemu-system-x86_64.exe" }
    
    if ($elfPath) {
        Write-Host "[+] Launching MyKernel ($elfPath) in QEMU..." -ForegroundColor Green
        & $cmd -kernel $elfPath -serial stdio
    } elseif ($isoPath) {
        Write-Host "[+] Booting MyKernel ISO ($isoPath) in QEMU..." -ForegroundColor Green
        & $cmd -cdrom $isoPath
    } else {
        Write-Host "[-] Error: mykernel.elf or mykernel.iso not found!" -ForegroundColor Red
    }
} else {
    Write-Host "[-] QEMU not found on system." -ForegroundColor Red
    Write-Host "[*] Install QEMU using winget:" -ForegroundColor Yellow
    Write-Host "    winget install SoftwareFreedomConservancy.QEMU" -ForegroundColor Yellow
}
