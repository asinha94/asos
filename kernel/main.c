#include <cpu/interrupts/pic.h>
#include <cpu/interrupts/exception.h>
#include <cpu/interrupts/idt.h>
#include <cpu/hal.h>
#include <display/tty.h>
#include <drivers/keyboard/keyboard.h>
#include <mm/gdt.h>
#include <mm/pmm.h>
#include <libk/string.h>

extern char __kbd_buffer[80];
extern int __len;
extern int __newline;

int is_match(const char * s, const char * t, size_t n)
{
    return strncmp(s, t, n) == 0;
}

void temp_shell_execute()
{
    if (__newline) {
        if (is_match(__kbd_buffer, "help", __len)) {
            kprintf("This is the help!\n");
        } else {
            kprintf("%s: command not found\n", __kbd_buffer);
        }
    __newline = 0;
    __len = 0;
    kprintf("shell$> ");
    }
}

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
    kprintf("shell$> ");
    enable_interrupts();

    while (1) {
        halt();
        disable_interrupts();
        temp_shell_execute();
        enable_interrupts();
    }
    
}


