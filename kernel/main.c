#include <boot/multiboot.h>
#include <cpu/hal.h>
#include <cpu/interrupts/pic.h>
#include <cpu/interrupts/exception.h>
#include <cpu/interrupts/idt.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/serial/serial.h>
#include <graphics/vga.h>
#include <libk/string.h>
#include <libk/kprintf.h>
#include <libk/kmalloc.h>
#include <mm/gdt.h>
#include <mm/pmm.h>


extern char __kbd_buffer[80];
extern int __len;
extern int __newline;


int is_match(const char * s)
{
    return strncmp(__kbd_buffer, s, __len) == 0;
}

void temp_shell_execute()
{
    if (__newline) {
        if (is_match("help")) {
            kprintf("This is the help!\n");
        } else {
            kprintf("%s: command not found\n", __kbd_buffer);
        }
    __newline = 0;
    __len = 0;
    kprintf("shell$> ");
    }
}

extern "C" void kernel_main(unsigned long magic, unsigned long mb_addr);

void kernel_main(unsigned long magic, unsigned long mb_addr)
{
    // Setup serial output for debugging
    init_serial();

    kprintf("Multiboot Magic Header 0x%x\n", magic);
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        kprintf("Invalid Multiboot Magic Number: 0x%x. Expected 0x%x\n", MULTIBOOT_BOOTLOADER_MAGIC);
        return;
    }

    kprintf("Initializing Kernel\n");
    // descriptor tables and exception handlers
    init_gdt();
    init_irq();
    init_cpu_exceptions();
    init_idt();

    multiboot_info_t *mbi = (multiboot_info_t *) (mb_addr + VMM_KERN_ADDR_START);

    // Memory Management
    init_pmm(mbi);
    init_vmm();

    // Setup graphics
    init_graphics(mbi);

    // Let loose the dogs of war
    enable_interrupts();

    while (1) {
        halt();
        disable_interrupts();
        temp_shell_execute();
        enable_interrupts();
    }
    
}


