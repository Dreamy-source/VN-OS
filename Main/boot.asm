[org 0x7c00]
[bits 16]

%define kernel_address 0x9000
%define kernel_segment 0x0900

_start:
    mov [boot_drive], dl
    
    call hide_bios_cursor

    mov ah, 0x42
    mov dl, [boot_drive]
    mov si, dap
    int 0x13
    jc  disk_err

    in al, 0x92
    or al, 10b
    out 0x92, al

    cli

    lgdt [gdt_desc]

    mov eax, cr0
    or  eax, 1b
    mov cr0, eax

    jmp 0x08:kernel_address

hide_bios_cursor:
    mov ah, 0x01
    mov ch, 0x20
    mov cl, 0x00
    int 0x10
    ret

disk_err:
    mov  si, disk_err_msg
    call print
    cli
    hlt

gdt_start:

gdt_null:
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00

gdt_data:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

gdt_end:

gdt_desc:
    dw gdt_end - gdt_start - 1
    dd gdt_start

print:
    lodsb
    test al, al
    jz   .ret
    mov  ah, 0x0E
    int  0x10
    jmp  print
.ret: ret

dap:
    db 0x10
    db 0x00
    dw 0x0009
    dw 0x0000
    dw kernel_segment
    dq 0x0001

boot_drive: db 0x00

disk_err_msg: db "[fatal]: disk error", 0x0D, 0x0A, 0x00

times 510 - ($ - $$) db 0x00
dw 0xAA55