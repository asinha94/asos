#include <cpu/interrupts/pic.h>
#include <cpu/interrupts/exception.h>
#include <cpu/interrupts/idt.h>
#include <cpu/hal.h>
#include <display/textmode.h>
#include <drivers/keyboard/keyboard.h>
#include <mm/gdt.h>
#include <mm/pmm.h>
#include <libk/string.h>
#include <libk/klog.h>
#include <boot/multiboot.h>

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
            klogf("This is the help!\n");
        } else {
            klogf("%s: command not found\n", __kbd_buffer);
        }
    __newline = 0;
    __len = 0;
    klogf("shell$> ");
    }
}

void kernel_main(unsigned long magic, unsigned long mb_addr)
{

    // Init a serial/tty connections for us to log to
    //init_tty(); -- Uncomment to clear textmode screen, should do it when we check the graphics mode
    //init_klog(tty_putchar, tty_puts); 

    klogf("Multiboot Magic Header %u\n", magic);
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        klogf("Invalid Multiboot Magic Number: 0x%x. Expected 0x%x\n", MULTIBOOT_BOOTLOADER_MAGIC);
        return;
    }

    //multiboot_info_t *mbi = (multiboot_info_t *) mb_addr;
    // TODO: check flags
    //void * fb_addr = (void *) mbi->framebuffer_addr; 
    //multiboot_uint32_t fb_pitch = mbi->framebuffer_pitch;
    //multiboot_uint32_t fb_width = mbi->framebuffer_width;
    //multiboot_uint32_t fb_height = mbi->framebuffer_height;
    //multiboot_uint8_t fb_bpp = mbi->framebuffer_bpp;
    //multiboot_uint8_t fb_type = mbi->framebuffer_type;
    
    klogf("Initializing Kernel\n");
    // descriptor tables and exception handlers
    init_gdt();
    init_irq();
    init_cpu_exceptions();
    init_idt();
    // Memory Management
    init_pmm();
    init_vmm();

    // Let loose the dogs of war
    klogf("shell$> ");
    enable_interrupts();

    while (1) {
        halt();
        disable_interrupts();
        temp_shell_execute();
        enable_interrupts();
    }
    
}


