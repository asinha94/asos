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
    kprintf("Initializing Kernel\n");
    
    // create linear address space for OS
    // includes Kernel and Userspace
    init_gdt();
    // init paging here

    // Install IDT and IRQ handlers
    init_irq();
    init_cpu_exceptions();
    init_idt();

    kprintf("The\n");
    kprintf("quick\n");
    kprintf("brown\n");
    kprintf("fox\n");
    kprintf("jumps\n");
    kprintf("over\n");
    kprintf("the\n");
    kprintf("lazy\n");
    kprintf("dog\n");
    kprintf("who\n");
    kprintf("sleeps\n");
    kprintf("all\n");
    kprintf("day\n");
    kprintf("and\n");
    kprintf("doesnt\n");
    kprintf("event\n");
    kprintf("pay\n");
    kprintf("rent\n");
    kprintf("but\n");
    kprintf("is\n");
    kprintf("still\n");
    kprintf("a\n");
    kprintf("well\n");

    // Enables Interrupts
    enable_interrupts();

    // test software interrupt
    //asm("int $48");

    while (1) {
        asm("hlt");
    }
    
}


