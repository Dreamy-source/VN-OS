[bits 32]

extern kmain
extern irq0_handler_cpp
extern irq1_handler_cpp

global nothing_handler_pic
global nothing_handler_apic
global asm_irq0_handler
global asm_irq1_handler

_start:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000

    call kmain

    jmp $

nothing_handler_pic:
    pusha
    push ds
    push es

    ; Master EOI
    mov al, 0x20
    out 0x20, al

    ; Slave EOI
    mov al, 0x20
    out 0xA0, al

    pop es
    pop ds
    popa
    iret

nothing_handler_apic:
    pusha
    push ds
    push es

    ; LAPIC EOI
    mov ecx, 0xFEE000B0
    mov dword [ecx], 0

    pop es
    pop ds
    popa
    iret

asm_irq0_handler:
    pusha

    call irq0_handler_cpp

    popa
    iret

asm_irq1_handler:
    pusha

    call irq1_handler_cpp

    popa
    iret