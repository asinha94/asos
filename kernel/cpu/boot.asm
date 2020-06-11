; Source: https://wiki.osdev.org/Bare_Bones_with_NASM
; The Global Constants used to signal to Multiboot to load this file
; This basically does all the hard bootloading for us
MBALIGN  equ  1 << 0            ; Align modules at page boundaries
MEMINFO  equ  1 << 1            ; Provide us with a memory map
FLAGS    equ  MBALIGN | MEMINFO ; The Fields flag for multiboot
MAGIC    equ  0x1BADB002        ; The Bootloader magic number which lefts the bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; Checksum of above to prove to multiboot that this is actually a header

; Declare the Header for the multiboot standard
section .multiboot
align 4
        dd MAGIC
        dd FLAGS
        dd CHECKSUM

; Time to create our own small stack
; System V ABI requires a 16-bit aligned stack
section .bss
align 16  
stack_bottom:
        resb 16384 ; 16 KiB
stack_top:


section .text
global _start:function (_start.end - _start)
_start:
        ;; disable interrupts
        cli

        ; setup stack
        mov esp, stack_top
        
        ; If grub is removed, we need to setup 80x25 video mode ourselves
        ; this should be done here maybe?

        ; Set A20 so we can access >1 MB of memory
        ; This is unecceary atm because Grub has already done this
        in al, 0x92
        or al, 2
        out 0x92, al

        ; Set protected mode bit on CR0
        mov eax, cr0
        or eax, 0x1
        mov cr0, eax

        ; Startup the higher level kernel
        extern kernel_main
        call kernel_main

        ; If somehow our kernel has exited then we need to do nothing
        ; disable all interrupts, wait for interrupts which won't come
        ; Then if we somehow escape from that then jump back into waiting
        cli
.hang:  hlt
        jmp .hang

.end:
