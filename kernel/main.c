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
    // descriptor tables and exception handlers
    init_gdt();
    init_irq();
    init_cpu_exceptions();
    init_idt();
    // Memory Management
    init_pmm();
    init_vmm();

    // Let loose the dogs of war
    enable_interrupts();

    while (1) {
        asm("hlt");
    }
    
}


