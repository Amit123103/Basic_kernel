@echo off
title MyKernel - Windows QEMU Launcher
echo ==========================================
echo    MyKernel - Windows QEMU Launcher
echo ==========================================

REM Add QEMU default install directory to path if present
if exist "C:\Program Files\qemu" set "PATH=%PATH%;C:\Program Files\qemu"

REM Check for kernel binary or ISO
set "KERNEL_ELF=build\mykernel.elf"
if not exist "%KERNEL_ELF%" set "KERNEL_ELF=mykernel.elf"

set "KERNEL_ISO=build\mykernel.iso"
if not exist "%KERNEL_ISO%" set "KERNEL_ISO=mykernel.iso"

where qemu-system-x86_64 >nul 2>nul
if %ERRORLEVEL% equ 0 (
    if exist "%KERNEL_ELF%" (
        echo [+] Launching MyKernel (%KERNEL_ELF%) in QEMU...
        qemu-system-x86_64 -kernel "%KERNEL_ELF%" -serial stdio
    ) else if exist "%KERNEL_ISO%" (
        echo [+] Launching MyKernel (%KERNEL_ISO%) in QEMU...
        qemu-system-x86_64 -cdrom "%KERNEL_ISO%"
    ) else (
        echo [-] Error: Could not find mykernel.elf or mykernel.iso.
        pause
    )
) else (
    echo [-] Error: QEMU is not installed or not in PATH.
    echo [*] Install QEMU on Windows via PowerShell: winget install SoftwareFreedomConservancy.QEMU
    pause
)
