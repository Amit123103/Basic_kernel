global syscall_entry
extern syscall_dispatch

syscall_entry:
    ; Save the caller context in a minimal way for now.
    push rbp
    mov rbp, rsp

    ; syscall number in rax, args in rdi/rsi/rdx
    mov rax, rdi
    mov rsi, rdx
    mov rdx, rcx
    call syscall_dispatch

    pop rbp
    ret
