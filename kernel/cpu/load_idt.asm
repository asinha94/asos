idt dw 0 ; size of table - 1
    dd 0 ; address of table

global asm_unhandled_isr
asm_unhandled_isr:
    ; Default ISR which does nothing
    iret


global asm_init_idt
asm_init_idt:
    mov eax, [esp + 4] ;; copy 4 byte address
    mov [idt + 1], eax
    mov ax, [esp + 8] ;; copy 2 byte size
    mov [idt], ax
    lidt [idt]

    ; perfect time to re-enable all interrupts
    sti
    ret