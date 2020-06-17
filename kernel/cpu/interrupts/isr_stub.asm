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
    push 0
    push 1
    jmp isr_common_handler

global asm_handler_isr2
asm_handler_isr2:
    push 0
    push 2
    push 0
    jmp isr_common_handler

global asm_handler_isr3
asm_handler_isr3:
    push 0
    push 3
    jmp isr_common_handler

global asm_handler_isr4
asm_handler_isr4:
    push 0
    push 4
    jmp isr_common_handler

global asm_handler_isr5
asm_handler_isr5:
    push 0
    push 5
    push 0
    jmp isr_common_handler

global asm_handler_isr6
asm_handler_isr6:
    push 0
    push 6
    push 0
    jmp isr_common_handler

global asm_handler_isr7
asm_handler_isr7:
    push 0
    push 7
    push 0
    jmp isr_common_handler

global asm_handler_isr8
asm_handler_isr8:
    push 8
    jmp isr_common_handler

global asm_handler_isr9
asm_handler_isr9:
    push 0
    push 9
    push 0
    jmp isr_common_handler

global asm_handler_isr10
asm_handler_isr10:
    push 10
    jmp isr_common_handler

global asm_handler_isr11
asm_handler_isr11:
    push 0
    push 11
    push 0
    jmp isr_common_handler

global asm_handler_isr12
asm_handler_isr12:
    push 0
    push 12
    jmp isr_common_handler

global asm_handler_isr13
asm_handler_isr13:
    push 0
    push 13
    jmp isr_common_handler

global asm_handler_isr14
asm_handler_isr14:
    push 14
    jmp isr_common_handler

global asm_handler_isr15
asm_handler_isr15:
    push 0
    push 15
    jmp isr_common_handler

global asm_handler_isr16
asm_handler_isr16:
    push 0
    push 16
    jmp isr_common_handler

global asm_handler_isr17
asm_handler_isr17:
    push 0
    push 17
    jmp isr_common_handler

global asm_handler_isr18
asm_handler_isr18:
    push 0
    push 18
    jmp isr_common_handler

global asm_handler_isr19
asm_handler_isr19:
    push 0
    push 19
    jmp isr_common_handler

global asm_handler_isr20
asm_handler_isr20:
    push 0
    push 20
    jmp isr_common_handler

global asm_handler_isr21
asm_handler_isr21:
    push 0
    push 21
    jmp isr_common_handler

global asm_handler_isr22
asm_handler_isr22:
    push 0
    push 22
    jmp isr_common_handler

global asm_handler_isr23
asm_handler_isr23:
    push 0
    push 23
    jmp isr_common_handler

global asm_handler_isr24
asm_handler_isr24:
    push 0
    push 24
    jmp isr_common_handler

global asm_handler_isr25
asm_handler_isr25:
    push 0
    push 25
    jmp isr_common_handler

global asm_handler_isr26
asm_handler_isr26:
    push 0
    push 26
    jmp isr_common_handler

global asm_handler_isr27
asm_handler_isr27:
    push 0
    push 27
    jmp isr_common_handler

global asm_handler_isr28
asm_handler_isr28:
    push 0
    push 28
    jmp isr_common_handler

global asm_handler_isr29
asm_handler_isr29:
    push 0
    push 29
    jmp isr_common_handler

global asm_handler_isr30
asm_handler_isr30:
    push 0
    push 30
    jmp isr_common_handler

global asm_handler_isr31
asm_handler_isr31:
    push 0
    push 31
    jmp isr_common_handler


;; ISR handler for Vect 32-47 (IRQ 0-15)

global asm_handler_irq0
asm_handler_irq0:
    push 0
    push 32
    jmp isr_common_handler

global asm_handler_irq1
asm_handler_irq1:
    push 0
    push 33
    jmp isr_common_handler

global asm_handler_irq2
asm_handler_irq2:
    push 0
    push 34
    jmp isr_common_handler

global asm_handler_irq3
asm_handler_irq3:
    push 0
    push 35
    jmp isr_common_handler

global asm_handler_irq4
asm_handler_irq4:
    push 0
    push 36
    jmp isr_common_handler

global asm_handler_irq5
asm_handler_irq5:
    push 0
    push 37
    jmp isr_common_handler

global asm_handler_irq6
asm_handler_irq6:
    push 0
    push 38
    jmp isr_common_handler

global asm_handler_irq7
asm_handler_irq7:
    push 0
    push 39
    jmp isr_common_handler

global asm_handler_irq8
asm_handler_irq8:
    push 0
    push 40
    jmp isr_common_handler

global asm_handler_irq9
asm_handler_irq9:
    push 0
    push 41
    jmp isr_common_handler

global asm_handler_irq10
asm_handler_irq10:
    push 0
    push 42
    jmp isr_common_handler

global asm_handler_irq11
asm_handler_irq11:
    push 0
    push 43
    jmp isr_common_handler

global asm_handler_irq12
asm_handler_irq12:
    push 0
    push 44
    jmp isr_common_handler

global asm_handler_irq13
asm_handler_irq13:
    push 0
    push 45
    jmp isr_common_handler

global asm_handler_irq14
asm_handler_irq14:
    push 0
    push 46
    jmp isr_common_handler

global asm_handler_irq15
asm_handler_irq15:
    push 0
    push 47
    jmp isr_common_handler
