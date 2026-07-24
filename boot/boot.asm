global _start
extern kernel_main

section .text
bits 32

_start:
    cli
    mov esp, stack_top
    call setup_long_mode
    jmp 0x08:long_mode_entry

setup_long_mode:
    ; Map the first 2 MiB identity using a level 4 page table.
    mov eax, page_table_l4
    mov cr3, eax

    ; Clear the page tables.
    xor eax, eax
    mov ecx, 4096
    mov edi, page_table_l4
    rep stosb

    ; Build the level 4 entry.
    mov dword [page_table_l4], page_table_l3 + 0x03
    mov dword [page_table_l4 + 4], 0

    ; Build the level 3 entry.
    mov dword [page_table_l3], page_table_l2 + 0x03
    mov dword [page_table_l3 + 4], 0

    ; Build the level 2 entries.
    mov ecx, 512
    mov edi, page_table_l2
    mov eax, 0x83
.build_pd:
    mov dword [edi], eax
    mov dword [edi + 4], 0
    add edi, 8
    add eax, 0x200000
    loop .build_pd

    ; Enable PAE and long mode.
    mov eax, cr4
    or eax, 0x00000020
    mov cr4, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, 0x00000100
    wrmsr

    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    ret

bits 64
long_mode_entry:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    call kernel_main

    ; Safety stop if the kernel returns.
    cli
.halt:
    hlt
    jmp .halt

section .bss
align 4096
page_table_l4:
    resb 4096
page_table_l3:
    resb 4096
page_table_l2:
    resb 4096
stack_bottom:
    resb 4096
stack_top:

