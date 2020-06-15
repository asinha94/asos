global asm_unhandled_isr
asm_unhandled_isr:
    ; Default ISR which does nothing
    iret


global asm_init_idt
asm_init_idt:
    mov eax, [esp + 4] ; copy 4 byte address
    lidt [eax]
    ret