/* The Global Constants used to signal to Multiboot to load this file */
.set ALIGN,     1<<0            /* Align modules at page boundaries */
.set MEMINFO,   1<<1            /* Provide us with a memory map */
.set FLAGS,     ALIGN | MEMINFO /* The Fields flag for multiboot */
.set MAGIC,     0x1BADB002      /* The Magic Bootloader number which lefts the bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* Checksum of above to prove to multiboot that this is actually a header */

/* Declare the Header */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Time to create our own small stack */
.section .bss
.align 16 /* System V ABI required a 16-bit aligned stack*/
stack_bottom:
        .skip 16384 # 16 KiB
stack_top:
        .section .text
        .global _start
        .type _start, @function
_start:
        mov esp, stack_top

        /* If I were to perform CPU initilization, it would be done here */

        /* Startup the higher level kernel */
        call kernel_main

        /* If somehow our kernel has exited then we need to do nothing
           disable all interrupts, wait for interrupts which won't come
           Then if we somehow escape from that then jump back into waiting
        */
        cli
1:      hlt
        jmp 1b

        .size _start, . -_start
