#include <display/tty.h>
#include <cpu/interrupts/pic.h>
#include <cpu/interrupts/exception.h>
#include <cpu/interrupts/idt.h>
#include <cpu/hal.h>
#include <mm/gdt.h>
#include <mm/pmm.h>


void kernel_main(void)
{
    // Init a TTY for us to log to
    init_tty();
    kprintf("Initializing Kernel\n");
    
    // create linear address space for OS
    // includes Kernel and Userspace
    kprintf("Initializing MM\n");
    init_gdt();
    init_pmm();
    init_vmm();

    // Install IDT and IRQ handlers
    kprintf("Initializing CPU exception handlers\n");
    init_irq();
    init_cpu_exceptions();
    init_idt();
    

    // Enables Interrupts
    enable_interrupts();

    while (1) {
        asm("hlt");
    }
    
}


