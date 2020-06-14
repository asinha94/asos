#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <display/tty.h>
#include <boot/gdt.h>
#include <cpu/idt.h>


void kernel_main(void)
{
    // Init all of the Protected Mode Services
    init_tty();
    kernprintf("Initializing Kernel\n");
    init_gdt();
    init_idt();

    while (1) {
        
    }
    
}


