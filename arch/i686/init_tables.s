.section .text
.globl asm_init_gdt
.type asm_init_gdt, @function
asm_init_gdt:
    movl 4(%esp), %eax
    lgdt (%eax)

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    ljmp $0x08, $.flush

.flush:
    ret