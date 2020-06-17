#include <stddef.h>
#include <cpu/idt.h>
#include <cpu/isr.h>
#include <cpu/pic.h>
#include <display/tty.h>

#define IDT_SIZE 256

// LIDT init function
extern void asm_init_idt(uint32_t idt_address);
// ISR Handler Stubs in asm
extern void asm_handler_isr0();
extern void asm_handler_isr1();
extern void asm_handler_isr2();
extern void asm_handler_isr3();
extern void asm_handler_isr4();
extern void asm_handler_isr5();
extern void asm_handler_isr6();
extern void asm_handler_isr7();
extern void asm_handler_isr8();
extern void asm_handler_isr9();
extern void asm_handler_isr10();
extern void asm_handler_isr11();
extern void asm_handler_isr12();
extern void asm_handler_isr13();
extern void asm_handler_isr14();
extern void asm_handler_isr15();
extern void asm_handler_isr16();
extern void asm_handler_isr17();
extern void asm_handler_isr18();
extern void asm_handler_isr19();
extern void asm_handler_isr20();
extern void asm_handler_isr21();
extern void asm_handler_isr22();
extern void asm_handler_isr23();
extern void asm_handler_isr24();
extern void asm_handler_isr25();
extern void asm_handler_isr26();
extern void asm_handler_isr27();
extern void asm_handler_isr28();
extern void asm_handler_isr29();
extern void asm_handler_isr30();
extern void asm_handler_isr31();
// IRQs
extern void asm_handler_irq0();
extern void asm_handler_irq1();
extern void asm_handler_irq2();
extern void asm_handler_irq3();
extern void asm_handler_irq4();
extern void asm_handler_irq5();
extern void asm_handler_irq6();
extern void asm_handler_irq7();
extern void asm_handler_irq8();
extern void asm_handler_irq9();
extern void asm_handler_irq10();
extern void asm_handler_irq11();
extern void asm_handler_irq12();
extern void asm_handler_irq13();
extern void asm_handler_irq14();
extern void asm_handler_irq15();

// Software Interrupt
extern void asm_handler_isr48();

// IDT table to be loaded
idt_entry entries[IDT_SIZE];
idt_table idt;


static void insert_idt_entry(
    uint8_t index,
    uint32_t handler)
{
    entries[index].offset_l = (handler >>  0) & 0xFFFF; // Lower 16 bits
    entries[index].offset_h = (handler >> 16) & 0xFFFF; // Upper 16 bits

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
    kernprintf("Creating IDT entries\n");
    // first 32 [0-31] are the Intel Reserved Exceptions
    insert_idt_entry(0, (uint32_t) asm_handler_isr0);
    insert_idt_entry(1, (uint32_t) asm_handler_isr1);
    insert_idt_entry(2, (uint32_t) asm_handler_isr2);
    insert_idt_entry(3, (uint32_t) asm_handler_isr3);
    insert_idt_entry(4, (uint32_t) asm_handler_isr4);
    insert_idt_entry(5, (uint32_t) asm_handler_isr5);
    insert_idt_entry(6, (uint32_t) asm_handler_isr6);
    insert_idt_entry(7, (uint32_t) asm_handler_isr7);
    insert_idt_entry(8, (uint32_t) asm_handler_isr8);
    insert_idt_entry(9, (uint32_t) asm_handler_isr9);
    insert_idt_entry(10, (uint32_t) asm_handler_isr10);
    insert_idt_entry(11, (uint32_t) asm_handler_isr11);
    insert_idt_entry(12, (uint32_t) asm_handler_isr12);
    insert_idt_entry(13, (uint32_t) asm_handler_isr13);
    insert_idt_entry(14, (uint32_t) asm_handler_isr14);
    insert_idt_entry(15, (uint32_t) asm_handler_isr15);
    insert_idt_entry(16, (uint32_t) asm_handler_isr16);
    insert_idt_entry(17, (uint32_t) asm_handler_isr17);
    insert_idt_entry(18, (uint32_t) asm_handler_isr18);
    insert_idt_entry(19, (uint32_t) asm_handler_isr19);
    insert_idt_entry(20, (uint32_t) asm_handler_isr20);
    insert_idt_entry(21, (uint32_t) asm_handler_isr21);
    insert_idt_entry(22, (uint32_t) asm_handler_isr22);
    insert_idt_entry(23, (uint32_t) asm_handler_isr23);
    insert_idt_entry(24, (uint32_t) asm_handler_isr24);
    insert_idt_entry(25, (uint32_t) asm_handler_isr25);
    insert_idt_entry(26, (uint32_t) asm_handler_isr26);
    insert_idt_entry(27, (uint32_t) asm_handler_isr27);
    insert_idt_entry(28, (uint32_t) asm_handler_isr28);
    insert_idt_entry(29, (uint32_t) asm_handler_isr29);
    insert_idt_entry(30, (uint32_t) asm_handler_isr30);
    insert_idt_entry(31, (uint32_t) asm_handler_isr31);

    // Next 16 [32-47] are the IRQs 
    insert_idt_entry(32, (uint32_t) asm_handler_irq0);
    insert_idt_entry(33, (uint32_t) asm_handler_irq1);
    insert_idt_entry(34, (uint32_t) asm_handler_irq2);
    insert_idt_entry(35, (uint32_t) asm_handler_irq3);
    insert_idt_entry(36, (uint32_t) asm_handler_irq4);
    insert_idt_entry(37, (uint32_t) asm_handler_irq5);
    insert_idt_entry(38, (uint32_t) asm_handler_irq6);
    insert_idt_entry(39, (uint32_t) asm_handler_irq7);
    insert_idt_entry(40, (uint32_t) asm_handler_irq8);
    insert_idt_entry(41, (uint32_t) asm_handler_irq9);
    insert_idt_entry(42, (uint32_t) asm_handler_irq10);
    insert_idt_entry(43, (uint32_t) asm_handler_irq11);
    insert_idt_entry(44, (uint32_t) asm_handler_irq12);
    insert_idt_entry(45, (uint32_t) asm_handler_irq13);
    insert_idt_entry(46, (uint32_t) asm_handler_irq14);
    insert_idt_entry(47, (uint32_t) asm_handler_irq15);

    // Software Interrupts
    insert_idt_entry(48, (uint32_t) asm_handler_isr48);

    // Still don't know why its 1 less byte than actual
    //(uint16_t) (sizeof(idt_entry) * 48) - 1;
    idt.length = (uint16_t) (sizeof(entries) - 1);
    idt.entries = (uint32_t) &entries;
    // load the IDT same way as the GDT
    asm_init_idt((uint32_t) &idt);
    kernprintf("IDT loaded\n");

    // Remap the PIC
    remap_pic_irq();
}