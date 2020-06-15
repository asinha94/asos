#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <display/tty.h>
#include <boot/gdt.h>
#include <cpu/idt.h>
#include <cpu/hal.h>


void kernel_main(void)
{
    // Init a TTY for us to log to
    init_tty();
    kernprintf("Initializing Kernel\n");

    // create linear address space for OS
    // includes Kernel and Userspace
    init_gdt();

    // Install IDT and IRQ handlers
    init_idt();

    // Enables Interrupts
    enable_interrupts();

    volatile int i = 1;
    while (i) {
        
    }
    
}


