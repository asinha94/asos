#include <stddef.h>
#include <cpu/idt.h>
#include <cpu/isr.h>
#include <display/tty.h>

#define IDT_SIZE 256

#define ADDR_UPPER_MASK 0xFFFF0000
#define ADDR_LOWER_MASK 0x0000FFFF

#define HANDLER_UPPER_ADDR(x) (((x) & ADDR_UPPER_MASK) >> 16)
#define HANDLER_LOWER_ADDR(x) ((x) & ADDR_LOWER_MASK)


#define CREATE_TYPE_ATTR(syscall) 0x80 | ((syscall) ? 0x6F : 0x0E)

extern void asm_unhandled_isr();
extern void asm_init_idt(uint32_t idt_address, uint16_t idt_table_size);

// IDT table to be loaded
idt_descriptor idt_entries[IDT_SIZE];


static void insert_idt_entry(
    uint8_t index,
    uint8_t is_syscall,
    uint32_t handler)
{
    idt_entries[index].offset_l = HANDLER_LOWER_ADDR(handler);

    // Selector tells the CPU what GDT segment, CPL etc... we want to be in
    // when we run this handler. The Answer is always the same...Kernel space
    // Look here for details https://wiki.osdev.org/Selector
    idt_entries[index].selector = 0x8; //0b 0000 0000 0000 1000
    idt_entries[index].zero = 0; // always zero

    // Type attribute tells us who/what is calling this routine
    // https://wiki.osdev.org/Interrupts_Descriptor_Table for more details
    idt_entries[index].type_attr = CREATE_TYPE_ATTR(is_syscall);
    idt_entries[index].offset_h = HANDLER_UPPER_ADDR(handler);
}

void init_idt()
{
    tty_writestring("Creating IDT entries\n");
    // Insert default handlers for all 256 interrupts
    for (size_t i = 0; i < IDT_SIZE; ++i) {
        insert_idt_entry(i, 0, (uint32_t) asm_unhandled_isr);
    }

    // Instantiate the handlers currently implemented

    // load the table, and re-enable interrupts
    // same deal as GDT, pass in table address and size(-1)
    asm_init_idt((uint32_t) &idt_entries, (uint16_t) sizeof(idt_entries)-1);
     
    tty_writestring("Interrupts enabled\n");
}