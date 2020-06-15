#include <stddef.h>
#include <cpu/idt.h>
#include <cpu/isr.h>
#include <cpu/pic.h>
#include <display/tty.h>

#define IDT_SIZE 256

extern void asm_exception_handler();
extern void asm_irq_handler();
extern void asm_init_idt(uint32_t idt_address);

// IDT table to be loaded
idt_entry entries[IDT_SIZE];
idt_table idt;


static void insert_idt_entry(
    uint8_t index,
    uint32_t handler)
{
    entries[index].offset_h = (handler & 0xFFFF0000) >> 16; // Upper 16 bits, SHR
    entries[index].offset_l = handler & 0xFFFF; // Lower 16 bits

    // Selector tells the CPU what GDT segment, CPL etc... we want to be in
    // when we run this handler. The Answer is always the same...Kernel code segment
    // Look here for details https://wiki.osdev.org/Selector
    entries[index].selector = 0x8; //0b 0000 0000 0000 1000
    entries[index].zero = 0; // always zero

    // Type attribute tells us who/what is calling this routine
    // https://wiki.osdev.org/Interrupts_Descriptor_Table for more details
    entries[index].type_attr =  0x8E;
    // for syscalls we probably want 0xEF
    
}

void init_idt()
{
    kernprintf("Creating IDT entries\n");
    // first 32 [0-31] are the Intel Reserved Exceptions

    for (size_t i = 0; i < 32; ++i) {
        insert_idt_entry(i, (uint32_t) asm_exception_handler);
    }

    // Next 16 [32-47] are the IRQs, most of which are masked out
    uint8_t enabled_interrupts = 47 + 1;
    for (size_t i = 32; i < enabled_interrupts; ++i) {
        insert_idt_entry(i, (uint32_t) asm_irq_handler);
    }
    
    // Still don't know why its 1 less byte than actual
    idt.length = (uint16_t) (sizeof(idt_entry) * enabled_interrupts) - 1;
    idt.entries_addr = (uint32_t) &entries;
    // load the IDT same way as the GDT
    asm_init_idt((uint32_t) &idt);
    kernprintf("IDT loaded\n");

    // Remap the PIC and disable IRQs we don't handle
    remap_pic_irq();
}