section .multiboot_header
align 8

multiboot2_header:
    dd 0xe85250d6
    dd 0
    dd header_end - multiboot2_header
    dd -(0xe85250d6 + 0 + (header_end - multiboot2_header))

    ; End tag
    dw 0
    dw 0
    dd 8
header_end:
