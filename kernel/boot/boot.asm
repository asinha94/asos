; Multiboot 2 version of https://wiki.osdev.org/Bare_Bones_with_NASM
; https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Example-boot-loader-code used for multiboot2


; Multiboot2 Header values
MBOOT2_MAGIC    equ 0xE85250D6
MBOOT2_ARCH     equ 0
MBOOT2_LEN      equ (multiboot_header_end-multiboot_header_start)
MBOOT2_CHECKSUM equ -(MBOOT2_MAGIC + MBOOT2_ARCH + MBOOT2_LEN)


; Declare the Header for the multiboot standard: https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Header-layout
section .multiboot
align 8
multiboot_header_start:
        dd MBOOT2_MAGIC
        dd MBOOT2_ARCH
        dd MBOOT2_LEN
        dd MBOOT2_CHECKSUM
multiboot_final_tag:
        dw 0
        dw 0
        dd 8
multiboot_header_end:


; Create Paging structures for loading kernel at higher-half
KERNEL_PG_VA_OFFSET equ 0xC0000000
KERNEL_PG_DIR_OFFSET equ 768 ; Number of pages before kernel page
section .data
align 4096
identity_page_directory:
        dd 0x00000083 ; Identity Map first 4MB. use single RW 4MB PDE
        times (KERNEL_PG_DIR_OFFSET - 1) dd 0 ; Unmap next ~767 PDEs
        dd 0x00000083 ; Map first 4MB to Kernel position i.e 786 * 4096 Bytes up
        times (1024 - KERNEL_PG_DIR_OFFSET - 2) dd 0 ; Unmap all but last entry
        dd 0x00400083 ; Map 2nd physical 4MB page to last PDE

section .text
global _start
_start:
        ; disable interrupts
        cli

        ; https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#I386-machine-state
        ; eax contains the multiboot magic number and ebx holds the addr. of multiboot structure
        ; which is passed to the kernel, so we can't use those values. Using ecx instead

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

        ; Multiboot2 magic value: 
        push eax
        ; Multiboot2 structure physical address, but we want virtual
        ; According to the docs, this can be anywhere, but we only map the first 4MB for the kernel
        ; Inside the kernel we have to figure out what page to map to access this
        add ebx, KERNEL_PG_VA_OFFSET
        push ebx

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