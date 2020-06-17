;; This file lists contains the definitions for
;; the ISRs. These are just stubs which will 
;; call the real workers (in C)

extern isr_dispatcher
isr_common_handler:
    ;; All these routines use the interrupt gate
    ;; which automatically disables interrupts
    pushad
    push ds
    push es
    push fs
    push gs

    cld ; SysV ABI requires DF clear on function entry
    ; The dispatcher takes a pointer to the start of memory
    ; where all the data is stored i.e esp
    push esp 
    call isr_dispatcher
    add esp, 4
    ; Need to 'decrease' stack size so that everything we pushed
    ; is popped in the right place
    ; we could also pop esp but it means another memory access

    pop gs
    pop fs
    pop es
    pop ds
    popad
    ; clean up error codes we manually added
    add esp, 8
    iret

;; ISR handler for Vect 0-31

global asm_handler_isr0
asm_handler_isr0:
    push 0
    push 0
    jmp isr_common_handler

global asm_handler_isr1
asm_handler_isr1:
    push 1
    push 0
    jmp isr_common_handler

global asm_handler_isr2
asm_handler_isr2:
    push 2
    push 0
    jmp isr_common_handler

global asm_handler_isr3
asm_handler_isr3:
    push 3
    push 0
    jmp isr_common_handler

global asm_handler_isr4
asm_handler_isr4:
    push 4
    push 0
    jmp isr_common_handler

global asm_handler_isr5
asm_handler_isr5:
    push 5
    push 0
    jmp isr_common_handler

global asm_handler_isr6
asm_handler_isr6:
    push 6
    push 0
    jmp isr_common_handler

global asm_handler_isr7
asm_handler_isr7:
    push 7
    push 0
    jmp isr_common_handler

global asm_handler_isr8
asm_handler_isr8:
    push 8
    push 0
    jmp isr_common_handler

global asm_handler_isr9
asm_handler_isr9:
    push 9
    push 0
    jmp isr_common_handler

global asm_handler_isr10
asm_handler_isr10:
    push 10
    push 0
    jmp isr_common_handler

global asm_handler_isr11
asm_handler_isr11:
    push 11
    push 0
    jmp isr_common_handler

global asm_handler_isr12
asm_handler_isr12:
    push 12
    push 0
    jmp isr_common_handler

global asm_handler_isr13
asm_handler_isr13:
    push 13
    push 0
    jmp isr_common_handler

global asm_handler_isr14
asm_handler_isr14:
    push 14
    push 0
    jmp isr_common_handler

global asm_handler_isr15
asm_handler_isr15:
    push 15
    push 0
    jmp isr_common_handler

global asm_handler_isr16
asm_handler_isr16:
    push 16
    push 0
    jmp isr_common_handler

global asm_handler_isr17
asm_handler_isr17:
    push 17
    push 0
    jmp isr_common_handler

global asm_handler_isr18
asm_handler_isr18:
    push 18
    push 0
    jmp isr_common_handler

global asm_handler_isr19
asm_handler_isr19:
    push 19
    push 0
    jmp isr_common_handler

global asm_handler_isr20
asm_handler_isr20:
    push 20
    push 0
    jmp isr_common_handler

global asm_handler_isr21
asm_handler_isr21:
    push 21
    push 0
    jmp isr_common_handler

global asm_handler_isr22
asm_handler_isr22:
    push 22
    push 0
    jmp isr_common_handler

global asm_handler_isr23
asm_handler_isr23:
    push 23
    push 0
    jmp isr_common_handler

global asm_handler_isr24
asm_handler_isr24:
    push 24
    push 0
    jmp isr_common_handler

global asm_handler_isr25
asm_handler_isr25:
    push 25
    push 0
    jmp isr_common_handler

global asm_handler_isr26
asm_handler_isr26:
    push 26
    push 0
    jmp isr_common_handler

global asm_handler_isr27
asm_handler_isr27:
    push 27
    push 0
    jmp isr_common_handler

global asm_handler_isr28
asm_handler_isr28:
    push 28
    push 0
    jmp isr_common_handler

global asm_handler_isr29
asm_handler_isr29:
    push 29
    push 0
    jmp isr_common_handler

global asm_handler_isr30
asm_handler_isr30:
    push 30
    push 0
    jmp isr_common_handler

global asm_handler_isr31
asm_handler_isr31:
    push 31
    push 0
    jmp isr_common_handler


;; ISR handler for Vect 32-47 (IRQ 0-15)

global asm_handler_irq0
asm_handler_irq0:
    push 32
    push 0
    jmp isr_common_handler

global asm_handler_irq1
asm_handler_irq1:
    push 33
    push 0
    jmp isr_common_handler


    ;; we won't get here because of iret
    push eax
    ; get KBD data
    in al, 0x60
    mov byte [0xB8000], al
    ; eoi
    mov al, 0x20
    out 0x20, al
    
    ;; restore registers
    pop eax
    iret

global asm_handler_irq2
asm_handler_irq2:
    push 34
    push 0
    jmp isr_common_handler

global asm_handler_irq3
asm_handler_irq3:
    push 35
    push 0
    jmp isr_common_handler

global asm_handler_irq4
asm_handler_irq4:
    push 36
    push 0
    jmp isr_common_handler

global asm_handler_irq5
asm_handler_irq5:
    push 37
    push 0
    jmp isr_common_handler

global asm_handler_irq6
asm_handler_irq6:
    push 38
    push 0
    jmp isr_common_handler

global asm_handler_irq7
asm_handler_irq7:
    push 39
    push 0
    jmp isr_common_handler

global asm_handler_irq8
asm_handler_irq8:
    push 40
    push 0
    jmp isr_common_handler

global asm_handler_irq9
asm_handler_irq9:
    push 41
    push 0
    jmp isr_common_handler

global asm_handler_irq10
asm_handler_irq10:
    push 42
    push 0
    jmp isr_common_handler

global asm_handler_irq11
asm_handler_irq11:
    push 43
    push 0
    jmp isr_common_handler

global asm_handler_irq12
asm_handler_irq12:
    push 44
    push 0
    jmp isr_common_handler

global asm_handler_irq13
asm_handler_irq13:
    push 45
    push 0
    jmp isr_common_handler

global asm_handler_irq14
asm_handler_irq14:
    push 46
    push 0
    jmp isr_common_handler

global asm_handler_irq15
asm_handler_irq15:
    push 47
    push 0
    jmp isr_common_handler
