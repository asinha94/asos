gdtr dw 0 ; limit i.e table size (bytes)
     dd 0 ; base i.e table address

global asm_init_gdt
asm_init_gdt:
    ; SysV ABI - arguments are pushed onto stack right to left
    ; first argument is the 4-byte gdt table address
    mov eax, [esp + 4]  ; copy 4 bytes from 4 bytes above stack pointer
    mov [gdtr + 2], eax ; copy into gdtr 2 bytes from top
    ; second argument is the 2-byte gdb size, located 8 bytes from esp
    ; Only copy bottom 2 bytes
    mov ax, [esp + 8] ; ax used because we only copy bottom 2 bytes
    mov [gdtr], ax

    ;; Set All segment register (except CS) to kernel data segment
    ;; https://stackoverflow.com/a/23979175
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; CS is the only register we can't change with mov
    ; so we have to perform a far-jump to change it
    ; so the affects of the GDT take place
    ; also we need to clear the fetch queue
    jmp 0x08:.reload_cs

.reload_cs:
    ret