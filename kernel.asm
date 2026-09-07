[bits 32]

global _start

extern kmain
extern irq0_handler
extern irq1_handler

global asm_irq0
global asm_irq1

%macro catch_return_from_interrupt 0
    jmp $
%endmacro

_start:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x200000

    call clear_screen
    
    call pit_init
    call kmain

    catch_return_from_interrupt

clear_screen:
    mov edi, 0xB8000
    mov ecx, 80 * 25
    mov eax, 0x0F20
    rep stosw
    ret

pit_init:
    mov al, 00110110b         ; channel 0, lobyte/hibyte, square wave, 16-bit binary
    out 0x43, al              ; data

    mov eax, 1193181 / 1000
    out 0x40, al              ; channel 0
    mov al, ah
    out 0x40, al
    
    ret

asm_irq0:
    pusha

    call irq0_handler

    popa
    iret

asm_irq1:
    pusha

    call irq1_handler
    
    popa
    iret