
#include <boot/multiboot.h>
#include <cpu/hal.h>
#include <cpu/interrupts/pic.h>
#include <cpu/interrupts/idt.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/serial/serial.h>
#include <graphics/vga.h>
#include <libk/string.h>
#include <libk/kprintf.h>
#include <libk/kmalloc.h>
#include <mm/gdt.h>
#include <mm/pmm.h>

//extern char __kbd_buffer[80];
//extern int __len;
//extern int __newline;

extern "C" void kernel_main(unsigned long magic, unsigned long mb_addr);
void kernel_main(unsigned long magic, unsigned long mb_addr)
{
    // Setup serial output for debugging
    asos::init_serial();
    kprintf("Multiboot Magic Header %x\n", magic);
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        kprintf("Invalid Multiboot Magic Number: %x. Expected %x\n", magic, MULTIBOOT_BOOTLOADER_MAGIC);
        return;
    }

    multiboot_info_t *mbi = (multiboot_info_t *) (mb_addr + VMM_KERN_ADDR_START);
    kprintf("Initializing Kernel\n");
    // Memory Management
    init_pmm(mbi);
    init_vmm();
    // descriptor tables and exception handlers
    asos::GDTTable::initGDT();
    asos::IDTHandler::initIDT();
    // Setup graphics
    init_graphics(mbi);
    // Let loose the dogs of war
    enable_interrupts();

    while (1) {
        halt();
        disable_interrupts();
        enable_interrupts();
    }
    
}


