.section .text
.globl asm_init_gdt
.type asm_init_gdt, @function
asm_init_gdt:
    mov eax, [esp+4]
    lgdt [eax]

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret
    /* jmp flush, 0x08 */

.flush:
    ret
