[bits 32]

extern kmain
%define stack_size 0x90000

_start:
    mov ax, 0x10   ; GDT data
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, stack_size

    call kmain

    jmp $