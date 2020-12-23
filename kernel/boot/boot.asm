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
multiboot_header:
        dd MAGIC
        dd FLAGS
        dd CHECKSUM


; Create Paging structures for loading kernel at higher-half
KERNEL_PG_VA_OFFSET equ 0xC0000000
KERNEL_PG_DIR_OFFSET equ 768 ; Number of pages before kernel page
section .data
align 4096
identity_page_directory:
        dd 0x83 ; Identity Map first 4MB. use single RW 4MB PDE
        times (KERNEL_PG_DIR_OFFSET - 1) dd 0 ; Unmap next ~767 PDEs
        dd 0x83 ; Map first 4MB to Kernel position i.e 786 * 4096 Bytes up
        times (1024 - KERNEL_PG_DIR_OFFSET - 2) dd 0 ; Unmap all but last entry
        dd 0xFFC00083 ; Map last 4MB PDE for paging structures

section .text
global _start
_start:
        ; disable interrupts
        cli

        ; Load page-dir. The PIC addresses are used because
        ; the BIOS has loaded us in at 1MB, but we told the linker
        ; to use our VA offsets so the C code works with VA addresses
        mov eax, (identity_page_directory - KERNEL_PG_VA_OFFSET)
        mov cr3, eax

        ; Enable 4MB pages
        mov eax, cr4
        or eax, 0x00000010
        mov cr4, eax

        ; Enable Paging
        mov eax, cr0
        or eax, 0x80000000
        mov cr0, eax

        ; Paging is enabled but the CPU still has physical addresses
        ; in its instruction cache, we need to long jump (similar to GDT jump)
        lea eax, [_kernel_start]
        jmp eax ; Need a virtual address to cement it


extern kernel_main
section .text
_kernel_start:
        ; Clear identity mapped page entry
        mov dword [identity_page_directory], 0
        invlpg [0]

        ; setup stack
        mov esp, stack_start

        ; Startup the C kernel
        call kernel_main
        ; If somehow our kernel has exited then do nothing
        cli
        hlt

; 16 KB stack. SysV ABI requires a 16-byte aligned stack
section .bss
align 16  
stack_end:
        resb 16384 ; 16 KB
stack_start: