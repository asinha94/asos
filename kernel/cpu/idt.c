#include <stddef.h>
#include <cpu/idt.h>
#include <cpu/isr.h>
#include <display/tty.h>

#define IDT_SIZE 256

extern void asm_unhandled_isr();
extern void asm_init_idt(uint32_t idt_address);

// IDT table to be loaded
idt_entries entries[IDT_SIZE];
idt_table idt;


static void insert_idt_entry(
    uint8_t index,
    uint8_t is_syscall,
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
    entries[index].type_attr = is_syscall ? 0xEF : 0x8E;
    
}

void init_idt()
{
    kernprintf("Creating IDT entries\n");
    // Insert default handlers for all 256 interrupts
    for (size_t i = 0; i < IDT_SIZE; ++i) {
        insert_idt_entry(i, 0, (uint32_t) asm_unhandled_isr);
    }

    // Instantiate the handlers currently implemented

    // load the table, and re-enable interrupts
    // same deal as GDT, pass in table address and size(-1)
    idt.length = (uint16_t) sizeof(entries) - 1;
    idt.entries_addr = (uint32_t) &entries;
    asm_init_idt((uint32_t) &idt);
     
    kernprintf("Interrupts enabled\n");
}