#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <display/tty.h>
#include <cpu/interrupts/idt.h>
#include <cpu/hal.h>
#include <mm/gdt.h>


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

    // test software interrupt
    asm("int $48");

    while (1) {
        asm("hlt");
    }
    
}


