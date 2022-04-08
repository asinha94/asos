#include <stdint.h>
#include <cpu/hal.h>
#include <cpu/interrupts/idt.h>
#include <cpu/interrupts/pic.h>
#include <drivers/keyboard/keyboard.h>
#include <libk/kprintf.h>


// IRQ handlers in assembly
extern "C" void asm_handler_irq0();
extern "C" void asm_handler_irq1();
extern "C" void asm_handler_irq2();
extern "C" void asm_handler_irq3();
extern "C" void asm_handler_irq4();
extern "C" void asm_handler_irq5();
extern "C" void asm_handler_irq6();
extern "C" void asm_handler_irq7();
extern "C" void asm_handler_irq8();
extern "C" void asm_handler_irq9();
extern "C" void asm_handler_irq10();
extern "C" void asm_handler_irq11();
extern "C" void asm_handler_irq12();
extern "C" void asm_handler_irq13();
extern "C" void asm_handler_irq14();
extern "C" void asm_handler_irq15();

// Handlers in C
static void default_irq_handler(isr_data * data)
{
    kprintf("Entered ISR %u\n", data->int_no);
    irq_eoi(data->int_no);
}


void init_irq()
{
    // Start initialization sequence of both master and slave
    outport8(PIC_MASTER_CMD_PORT, ICW1_INIT | PIC_ICW1_ICW4);
    outport8(PIC_SLAVE_CMD_PORT,  ICW1_INIT | PIC_ICW1_ICW4);

    // Remap Vector offsets to non-reserved range
    outport8(PIC_MASTER_DATA_PORT, PIC_MASTER_VECTOR_OFFSET);
    outport8(PIC_SLAVE_DATA_PORT, PIC_SLAVE_VECTOR_OFFSET);

    // Init Cascade topology i.e slave IRQ2 wired to master
    outport8(PIC_MASTER_DATA_PORT, PIC_MASTER_CASCADE_IRQ);
    outport8(PIC_SLAVE_DATA_PORT, PIC_SLAVE_CASCADE_IRQ);

    // 8086 mode
    outport8(PIC_MASTER_DATA_PORT, ICW4_8086);
    outport8(PIC_SLAVE_DATA_PORT, ICW4_8086);

    // Disable all IRQs (high bit means disabled)
    outport8(PIC_MASTER_DATA_PORT, 0xFF);
    outport8(PIC_SLAVE_DATA_PORT, 0xFF);
    kprintf("PIC re-mapped\n");

    // Init all the PIC connected devices
    keyboard_init();

    //  Install IRQ handlers into IDT
    // Entries [32-47] are the IRQs we just re-mapped
    uint8_t idt_index = PIC_MASTER_VECTOR_OFFSET;
    insert_idt_entry(idt_index++, (uint32_t) asm_handler_irq0, default_irq_handler);
    insert_idt_entry(idt_index++, (uint32_t) asm_handler_irq1, keyboard_handler);
    insert_idt_entry(idt_index++, (uint32_t) asm_handler_irq2, default_irq_handler);
    insert_idt_entry(idt_index++, (uint32_t) asm_handler_irq3, default_irq_handler);
    insert_idt_entry(idt_index++, (uint32_t) asm_handler_irq4, default_irq_handler);
    insert_idt_entry(idt_index++, (uint32_t) asm_handler_irq5, default_irq_handler);
    insert_idt_entry(idt_index++, (uint32_t) asm_handler_irq6, default_irq_handler);
    insert_idt_entry(idt_index++, (uint32_t) asm_handler_irq7, default_irq_handler);
    insert_idt_entry(idt_index++, (uint32_t) asm_handler_irq8, default_irq_handler);
    insert_idt_entry(idt_index++, (uint32_t) asm_handler_irq9, default_irq_handler);
    insert_idt_entry(idt_index++, (uint32_t) asm_handler_irq10, default_irq_handler);
    insert_idt_entry(idt_index++, (uint32_t) asm_handler_irq11, default_irq_handler);
    insert_idt_entry(idt_index++, (uint32_t) asm_handler_irq12, default_irq_handler);
    insert_idt_entry(idt_index++, (uint32_t) asm_handler_irq13, default_irq_handler);
    insert_idt_entry(idt_index++, (uint32_t) asm_handler_irq14, default_irq_handler);
    insert_idt_entry(idt_index++, (uint32_t) asm_handler_irq15, default_irq_handler);
}


void irq_clear_mask(uint8_t irq_number)
{
    uint16_t port;
    uint8_t data;

    if (irq_number < 8) {
        // Master
        port = PIC_MASTER_DATA_PORT;
    } else {
        // Slave
        port = PIC_SLAVE_DATA_PORT;
        irq_number -= 8;
    }

    // Current mask
    data = inport8(port) & ~(1 << irq_number);
    // Flip bit corresponding to irq_number
    outport8(port, data);
}


void irq_set_mask(uint8_t irq_number)
{
    uint16_t port;
    uint8_t data;

    if (irq_number < 8) {
        // Master
        port = PIC_MASTER_DATA_PORT;
    } else {
        // Slave
        port = PIC_SLAVE_DATA_PORT;
        irq_number -= 8;
    }

    // Current mask
    data = inport8(port) | (1 << irq_number);
    outport8(port, data);
}

void irq_eoi(uint8_t interrupt_no)
{   
    uint8_t irq_no = interrupt_no - PIC_MASTER_VECTOR_OFFSET;
    if (irq_no > 7)
        outport8(PIC_SLAVE_CMD_PORT, PIC_EOI);
    outport8(PIC_MASTER_CMD_PORT, PIC_EOI);
}