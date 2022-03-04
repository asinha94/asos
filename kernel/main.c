#include <cpu/interrupts/pic.h>
#include <cpu/interrupts/exception.h>
#include <cpu/interrupts/idt.h>
#include <cpu/hal.h>
#include <boot/multiboot2.h>
#include <display/tty.h>
#include <drivers/keyboard/keyboard.h>
#include <mm/gdt.h>
#include <mm/pmm.h>
#include <libk/string.h>

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
    kprintf("$> ");
    }
}

void kernel_main(uint32_t multiboot2_tag_paddr, uint32_t multiboot2_bootloader_magic)
{
    // Init a TTY for logging...and our shell till we get VBE support
    init_tty();
    kprintf("Initializing Kernel\n");

    if (MULTIBOOT2_BOOTLOADER_MAGIC != multiboot2_bootloader_magic) {
        return;
    }

    // Get MemoryMap from boot info structures
    // https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#kernel_002ec
    struct multiboot_tag * tag;
    struct multiboot_tag_mmap * boot_mmap;
    struct multiboot_tag_basic_meminfo * boot_meminfo;
    
    // skip header and align to tag pointer to 8 byte address
    for (tag = (struct multiboot_tag *) (multiboot2_tag_paddr + 8); 
         tag->type != MULTIBOOT_TAG_TYPE_END;
         tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag + ((tag->size + 7) & ~7)))
    {
        switch(tag->type)
        {
            case MULTIBOOT_TAG_TYPE_MMAP:
                boot_mmap = (struct multiboot_tag_mmap *) tag;
                break;
            case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
                boot_meminfo     = ( struct multiboot_tag_basic_meminfo *) tag;
                break;
            default:
                kprintf("Unknown Tag type in Multiboot struct: %u\n", tag->type);
        }
    }
    
    // descriptor tables and exception handlers
    init_gdt();
    init_irq();
    init_cpu_exceptions();
    init_idt();

    // Start Memory Management services.
    init_pmm(boot_meminfo, boot_mmap);
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


