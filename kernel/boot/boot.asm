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
; System V ABI requires a 16-byte aligned stack
section .bss
align 16  
stack_bottom:
        resb 16384 ; 16 KiB
stack_top:

; Create Paging structures for loading kernel at higher-half
KERNEL_PG_VA_OFFSET equ 0xC0000000
KERNEL_PG_DIR_OFFSET equ 768 ; Number of pages before kernel page
section .data
align 4096
identity_page_directory:
        dd 0x83 ; Identity Map first 4MiB. use single RW 4MiB Page
        times (KERNEL_PG_DIR_OFFSET - 1) dd 0
        dd 0x83 ; Kernel 4MiB RW Page
        times (1024 - KERNEL_PG_DIR_OFFSET - 1) dd 0 ; Remaining Pages


section .text
global _start
_start:
        ; disable interrupts
        cli

        ; Load page-dir. The PIC addresses are used because
        ; the BIOS has loaded us in at 1MiB, but we told the linker
        ; to use our VA offsets
        mov eax, (identity_page_directory - KERNEL_PG_VA_OFFSET)
        mov cr3, eax

        ; Enable 4MiB pages
        mov eax, cr4
        or eax, 0x00000010

        ; Enable Paging (and protected mode which)
        mov eax, cr0
        or eax, 0x80000000

        ; Paging is enabled but the CPU still has physical addresses
        ; in its instruction cache, we need to long jump (similar to GDT jump)
        lea eax, [_kernel_start]
        jmp eax ; Need a virtual address to cement it


extern kernel_main
section .text
_kernel_start:
        ; setup stack
        mov esp, stack_top

        ; Startup the C kernel
        call kernel_main
        ; If somehow our kernel has exited then we need to do nothing
        ; disable all interrupts, wait for interrupts which won't come
        ; Then if we somehow escape from that then jump back into waiting
        cli
        hlt
;.end:
