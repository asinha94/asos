#include <stddef.h>
#include <cpu/interrupts/idt.h>
#include <display/tty.h>

#define IDT_LEN 256

// IDT table to be loaded
idt_table idt;
idt_entry entries[IDT_LEN];

// Pointers to C handler functions
ivect ivt[IDT_LEN];

// LIDT init function
extern void asm_init_idt(uint32_t idt_address);
// Software Interrupt
extern void asm_handler_isr48();

void insert_idt_entry(
    uint8_t index,
    uint32_t handler,
    ivect c_handler)
{
    if (index >= IDT_LEN) {
        // log when kprintf workd
        return;
    }
    // Insert the C handler
    ivt[index] = c_handler;

    entries[index].offset_l = (handler >>  0) & 0xFFFF;
    entries[index].offset_h = (handler >> 16) & 0xFFFF;
    // Selector tells the CPU what GDT segment, CPL etc... we want to be in
    // when we run this handler. The Answer is always the same...Kernel code segment
    // Look here for details https://wiki.osdev.org/Selector
    entries[index].selector = 0x8; //0b 0000 0000 0000 1000
    entries[index].zero = 0; // always zero
    // Type attribute tells us who/what is calling this routine
    // https://wiki.osdev.org/Interrupts_Descriptor_Table for more details
    entries[index].type_attr =  0x8E;
    // 0xEF for trap which doesn't disable interrupts
    
}

void init_idt()
{
    // Software Interrupts
    insert_idt_entry(48, (uint32_t) asm_handler_isr48, NULL);

    // Still don't know why its 1 less byte than actual
    //(uint16_t) (sizeof(idt_entry) * 48) - 1;
    idt.length = (uint16_t) (sizeof(entries) - 1);
    idt.entries = (uint32_t) &entries;
    // load the IDT same way as the GDT
    asm_init_idt((uint32_t) &idt);
    kprintf("IDT loaded\n");
}