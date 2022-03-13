#include <boot/multiboot.h>
#include <cpu/hal.h>
#include <cpu/interrupts/pic.h>
#include <cpu/interrupts/exception.h>
#include <cpu/interrupts/idt.h>
#include <display/textmode.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/serial/serial.h>
#include <mm/gdt.h>
#include <mm/pmm.h>
#include <libk/string.h>
#include <libk/kprintf.h>
#include <libk/kmalloc.h>


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

void init_kernel(unsigned long mb_addr)
{
    // Identity page has been removed, Only the higher-half page is installed right now
    multiboot_info_t *mbi = (multiboot_info_t *) (mb_addr + VMM_KERN_ADDR_START);

    // TODO: Configure the PMM Memory Map
    if (mbi->flags & MULTIBOOT_INFO_MEMORY) {
        kprintf("Mem lower: %x\nMem Upper: %x\n", mbi->mem_lower, mbi->mem_upper);
         // Not sure if this is the last byte or the upper bounds of memory
        uint32_t phys_memory_end = 0x100000 + mbi->mem_upper;
    }

    // Setup graphics
    if (mbi->flags & MULTIBOOT_INFO_FRAMEBUFFER_INFO) {

        void * fb_addr = (void *) mbi->framebuffer_addr;
        multiboot_uint8_t fb_type = mbi->framebuffer_type;
        kprintf("Type: %u\n", fb_type);
        
        //multiboot_uint32_t fb_pitch = mbi->framebuffer_pitch;
        //multiboot_uint32_t fb_width = mbi->framebuffer_width;
        //multiboot_uint32_t fb_height = mbi->framebuffer_height;
        //multiboot_uint8_t fb_bpp = mbi->framebuffer_bpp;   
    }
    
}

void kernel_main(unsigned long magic, unsigned long mb_addr)
{
    // Setup printf/serial output for debugging
    // Setup Text Mode
    //init_tty();
    //init_kprintf(tty_putchar, tty_puts);
    init_serial();
    init_kprintf(serial_putchar, serial_puts);

    kprintf("Multiboot Magic Header 0x%x\n", magic);
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        kprintf("Invalid Multiboot Magic Number: 0x%x. Expected 0x%x\n", MULTIBOOT_BOOTLOADER_MAGIC);
        return;
    }

    kprintf("Initializing Kernel\n");
    init_kernel(mb_addr);
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
        halt();
        disable_interrupts();
        temp_shell_execute();
        enable_interrupts();
    }
    
}


