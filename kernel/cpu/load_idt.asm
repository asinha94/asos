global asm_exception_handler
asm_exception_handler:
    ; Default ISR which does nothing
    iret


global asm_irq_handler
asm_irq_handler:
    ; Default ISR which does nothing
    iret


global asm_init_idt
asm_init_idt:
    mov eax, [esp + 4] ; copy 4 byte address
    lidt [eax]
    ret