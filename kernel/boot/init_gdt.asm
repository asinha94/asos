global asm_init_gdt
asm_init_gdt:
    ; 4-byte gdt table address passed onto stack
    mov eax, [esp + 4] 
    lgdt [eax]

    ; CS is the only register we can't change with mov
    ; so we have to perform a far-jump to change it
    ; so the affects of the GDT take place
    ; The jump also clears the input prefetch queue
    jmp 0x08:.reload_segment_registers

.reload_segment_registers:
    ;; Set All segment register (except CS) to kernel data segment
    ;; https://stackoverflow.com/a/23979175
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret