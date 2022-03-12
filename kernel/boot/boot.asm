; Source: https://wiki.osdev.org/Bare_Bones_with_NASM
; The Global Constants used to signal to Multiboot to load this file
; This basically does all the hard bootloading for us

; The Multiboot magic number
MAGIC      equ 0x1BADB002
; Align modules at page boundaries
MB_ALIGN   equ 0x1
; Provide us with a memory map         
MB_MEMINFO equ 0x2
; Provide us with Graphics capabilites
MB_VGA     equ 0x4
; The Fields flag for multiboot
FLAGS      equ MB_ALIGN | MB_MEMINFO; | MB_VGA

; Checksum of above to prove to multiboot that this is actually a header
CHECKSUM   equ -(MAGIC + FLAGS)  

; Declare the Header for the multiboot standard
section .multiboot
align 4
multiboot_header:
        dd MAGIC
        dd FLAGS
        dd CHECKSUM

; Multiboot Memory Info Structure
        dd 0
        dd 0
        dd 0
        dd 0
        dd 0

; Multiboot Video Mode
        dd 0
        dd 640
        dd 480
        dd 32


; Create Paging structures for loading kernel at higher-half
KERNEL_PG_VA_OFFSET equ 0xC0000000 ; 3GB
KERNEL_PG_DIR_OFFSET equ 768 ; Number of pages before kernel page
section .data
align 4096
identity_page_directory:
        dd 0x00000083 ; Identity Map first 4MB. use single RW 4MB PDE
        times (KERNEL_PG_DIR_OFFSET - 1) dd 0 ; Unmap next ~767 PDEs
        dd 0x00000083 ; Map first 4MB to Kernel position i.e 786 * 4KB up
        times (1024 - KERNEL_PG_DIR_OFFSET - 2) dd 0 ; Unmap all but last entry
        dd 0x00400083 ; Map 2nd physical 4MB page to last PDE i.e 4MB from the end

section .text
global _start
_start:
        ; disable interrupts
        cli

        ; Enable A20 line. Unnecessary in Bochs, maybe QEMU
        ;in al, 0x92
        ;or al, 0x02
        ;out 0x92, al

        ; Load page-dir. The PIC addresses are used because
        ; the BIOS has loaded us in at 1MB, but we told the linker
        ; to use our VA offsets so the C code works with virtual addresses
        mov ecx, (identity_page_directory - KERNEL_PG_VA_OFFSET)
        mov cr3, ecx

        ; Enable 4MB pages
        mov ecx, cr4
        or ecx, 0x00000010
        mov cr4, ecx

        ; Enable Paging and Protected mode
        mov ecx, cr0
        or ecx, 0x80000001
        mov cr0, ecx

        ; Paging is enabled but the CPU still has physical addresses
        ; in its instruction cache, we need to long jump (similar to GDT jump)
        lea ecx, [_kernel_start]
        jmp ecx ; Need a virtual address to cement it


extern kernel_main
section .text
_kernel_start:
        ; Clear identity mapped entry from dir and tlb
        mov dword [identity_page_directory], 0
        invlpg [0]

        ; setup stack
        mov esp, stack_start

        ; Startup the C kernel
        ; Multiboot Magic Number
        push eax

        ; Convert ptr to Multiboot structure to virtual address 
        add ebx, KERNEL_PG_VA_OFFSET 

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