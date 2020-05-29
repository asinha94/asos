.section .text
.global asm_init_gdt
.type asm_init_gdt, @function

asm_init_gdt:
    /* Load GDT */
    mov eax, [esp+4]
    lgdt [eax]

    /* Enable line20 */
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    /* update segment registers */
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    /* Jumping to clear the CPU Prefetch Queue
    /* and enable 32-bit protected mode
    */
    jmp flush

flush:
    ret
