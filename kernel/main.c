#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <display/tty.h>
#include <cpu/interrupts/pic.h>
#include <cpu/interrupts/exception.h>
#include <cpu/interrupts/idt.h>
#include <cpu/hal.h>
#include <mm/gdt.h>


void kernel_main(void)
{
    // Init a TTY for us to log to
    init_tty();
    kprintf("%s is a t%dst; u: %u; %x\n", "this", 3, 42, 0xDEAD);
    kprintf("Initializing Kernel\n");
    
    // create linear address space for OS
    // includes Kernel and Userspace
    init_gdt();
    // init paging here

    // Install IDT and IRQ handlers
    init_irq();
    init_cpu_exceptions();
    init_idt();

    // Clear console
    tty_clear_tty();

    // Enables Interrupts
    enable_interrupts();

    // test software interrupt
    //asm("int $48");

    while (1) {
        asm("hlt");
    }
    
}


