; Loads IDT
global asm_init_idt
asm_init_idt:
    mov eax, [esp + 4] ; copy 4 byte address
    lidt [eax]
    ret

;; ISR handler for Vect 0-31

global asm_handler_isr0
asm_handler_isr0:
    iret

global asm_handler_isr1
asm_handler_isr1:
    iret

global asm_handler_isr2
asm_handler_isr2:
    iret

global asm_handler_isr3
asm_handler_isr3:
    iret

global asm_handler_isr4
asm_handler_isr4:
    iret

global asm_handler_isr5
asm_handler_isr5:
    iret

global asm_handler_isr6
asm_handler_isr6:
    iret

global asm_handler_isr7
asm_handler_isr7:
    iret

global asm_handler_isr8
asm_handler_isr8:
    iret

global asm_handler_isr9
asm_handler_isr9:
    iret

global asm_handler_isr10
asm_handler_isr10:
    iret

global asm_handler_isr11
asm_handler_isr11:
    iret

global asm_handler_isr12
asm_handler_isr12:
    iret

global asm_handler_isr13
asm_handler_isr13:
    iret

global asm_handler_isr14
asm_handler_isr14:
    iret

global asm_handler_isr15
asm_handler_isr15:
    iret

global asm_handler_isr16
asm_handler_isr16:
    iret

global asm_handler_isr17
asm_handler_isr17:
    iret

global asm_handler_isr18
asm_handler_isr18:
    iret

global asm_handler_isr19
asm_handler_isr19:
    iret

global asm_handler_isr20
asm_handler_isr20:
    iret

global asm_handler_isr21
asm_handler_isr21:
    iret

global asm_handler_isr22
asm_handler_isr22:
    iret

global asm_handler_isr23
asm_handler_isr23:
    iret

global asm_handler_isr24
asm_handler_isr24:
    iret

global asm_handler_isr25
asm_handler_isr25:
    iret

global asm_handler_isr26
asm_handler_isr26:
    iret

global asm_handler_isr27
asm_handler_isr27:
    iret

global asm_handler_isr28
asm_handler_isr28:
    iret

global asm_handler_isr29
asm_handler_isr29:
    iret

global asm_handler_isr30
asm_handler_isr30:
    iret

global asm_handler_isr31
asm_handler_isr31:
    iret


;; ISR handler for Vect 32-47 (IRQ 0-15)

global asm_handler_irq0
asm_handler_irq0:
    iret

global asm_handler_irq1
asm_handler_irq1:
    iret

global asm_handler_irq2
asm_handler_irq2:
    iret

global asm_handler_irq3
asm_handler_irq3:
    iret

global asm_handler_irq4
asm_handler_irq4:
    iret

global asm_handler_irq5
asm_handler_irq5:
    iret

global asm_handler_irq6
asm_handler_irq6:
    iret

global asm_handler_irq7
asm_handler_irq7:
    iret

global asm_handler_irq8
asm_handler_irq8:
    iret

global asm_handler_irq9
asm_handler_irq9:
    iret

global asm_handler_irq10
asm_handler_irq10:
    iret

global asm_handler_irq11
asm_handler_irq11:
    iret

global asm_handler_irq12
asm_handler_irq12:
    iret

global asm_handler_irq13
asm_handler_irq13:
    iret

global asm_handler_irq14
asm_handler_irq14:
    iret

global asm_handler_irq15
asm_handler_irq15:
    iret


