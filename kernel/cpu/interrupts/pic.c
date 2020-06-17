#include <stdint.h>
#include <cpu/interrupts/idt.h>
#include <cpu/interrupts/pic.h>
#include <cpu/hal.h>
#include <display/tty.h>


// Master PIC
#define PIC_MASTER_CMD_PORT      0x20
#define PIC_MASTER_DATA_PORT     (PIC_MASTER_CMD_PORT + 1)
#define PIC_MASTER_VECTOR_OFFSET 0x20
// Slave PIC
#define PIC_SLAVE_CMD_PORT       0xA0
#define PIC_SLAVE_DATA_PORT      (PIC_SLAVE_CMD_PORT + 1)
#define PIC_SLAVE_VECTOR_OFFSET  (PIC_MASTER_VECTOR_OFFSET + 8)
// Common Commands
#define PIC_EOI                  0x20 // End of Instruction
#define ICW1_INIT	             0x10
#define PIC_ICW1_ICW4            0x01 // ICW4 not needed
#define ICW4_8086	             0x01
// Cascading
#define PIC_MASTER_CASCADE_IRQ   0x04
#define PIC_SLAVE_CASCADE_IRQ    0x02
// IRQ Specific
#define KBD_SCAN_CODE            0x60


// IRQ handlers in assembly
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

// Handlers in C
static void handler_irq0(isr_data * data)
{
    kprintf("Entered IRQ 0\n");
    irq_eoi(0);
}

static void handler_irq1(isr_data * data)
{
    uint8_t kbd_data = inport8(KBD_SCAN_CODE);
    kprintf("Got %u from Keyboard\n", kbd_data);
    irq_eoi(1);
}

static void handler_irq2(isr_data * data)
{
    irq_eoi(2);
}

static void handler_irq3(isr_data * data)
{
    irq_eoi(3);
}

static void handler_irq4(isr_data * data)
{
    irq_eoi(4);
}

static void handler_irq5(isr_data * data)
{
    irq_eoi(5);
}

static void handler_irq6(isr_data * data)
{
    irq_eoi(6);
}

static void handler_irq7(isr_data * data)
{
    irq_eoi(7);
}

static void handler_irq8(isr_data * data)
{
    irq_eoi(8);
}

static void handler_irq9(isr_data * data)
{
    irq_eoi(9);
}

static void handler_irq10(isr_data * data)
{
    irq_eoi(10);
}

static void handler_irq11(isr_data * data)
{
    irq_eoi(11);
}

static void handler_irq12(isr_data * data)
{
    irq_eoi(12);
}

static void handler_irq13(isr_data * data)
{
    irq_eoi(13);
}

static void handler_irq14(isr_data * data)
{
    irq_eoi(14);
}

static void handler_irq15(isr_data * data)
{
    irq_eoi(15);
}


void init_irq()
{
    // Start initialization sequence of both master and slave
    outport8(PIC_MASTER_CMD_PORT, ICW1_INIT | PIC_ICW1_ICW4);
    outport8(PIC_SLAVE_CMD_PORT,  ICW1_INIT | PIC_ICW1_ICW4);

    // Remap Vector offsets to non-reserved range
    outport8(PIC_MASTER_DATA_PORT, PIC_MASTER_VECTOR_OFFSET);
    outport8(PIC_SLAVE_DATA_PORT, PIC_SLAVE_VECTOR_OFFSET);

    // Init Cascade topology i.e slace IRQ2 wired to master
    outport8(PIC_MASTER_DATA_PORT, PIC_MASTER_CASCADE_IRQ);
    outport8(PIC_SLAVE_DATA_PORT, PIC_SLAVE_CASCADE_IRQ);

    // 8086 mode
    outport8(PIC_MASTER_DATA_PORT, ICW4_8086);
    outport8(PIC_SLAVE_DATA_PORT, ICW4_8086);

    // Enable all IRQs
    outport8(PIC_MASTER_DATA_PORT, 1);
    outport8(PIC_SLAVE_DATA_PORT, 0);
    kprintf("PIC re-mapped\n");

    //  Install IRQ handlers into IDT
    // Entries [32-47] are the IRQs we just re-mapped
    uint8_t idt_entry = PIC_MASTER_VECTOR_OFFSET;
    insert_idt_entry(idt_entry++, (uint32_t) asm_handler_irq0, handler_irq0);
    insert_idt_entry(idt_entry++, (uint32_t) asm_handler_irq1, handler_irq1);
    insert_idt_entry(idt_entry++, (uint32_t) asm_handler_irq2, handler_irq2);
    insert_idt_entry(idt_entry++, (uint32_t) asm_handler_irq3, handler_irq3);
    insert_idt_entry(idt_entry++, (uint32_t) asm_handler_irq4, handler_irq4);
    insert_idt_entry(idt_entry++, (uint32_t) asm_handler_irq5, handler_irq5);
    insert_idt_entry(idt_entry++, (uint32_t) asm_handler_irq6, handler_irq6);
    insert_idt_entry(idt_entry++, (uint32_t) asm_handler_irq7, handler_irq7);
    insert_idt_entry(idt_entry++, (uint32_t) asm_handler_irq8, handler_irq8);
    insert_idt_entry(idt_entry++, (uint32_t) asm_handler_irq9, handler_irq9);
    insert_idt_entry(idt_entry++, (uint32_t) asm_handler_irq10, handler_irq10);
    insert_idt_entry(idt_entry++, (uint32_t) asm_handler_irq11, handler_irq11);
    insert_idt_entry(idt_entry++, (uint32_t) asm_handler_irq12, handler_irq12);
    insert_idt_entry(idt_entry++, (uint32_t) asm_handler_irq13, handler_irq13);
    insert_idt_entry(idt_entry++, (uint32_t) asm_handler_irq14, handler_irq14);
    insert_idt_entry(idt_entry++, (uint32_t) asm_handler_irq15, handler_irq15);
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

void irq_eoi(uint8_t irq_number)
{
    if (irq_number > 7) {
        outport8(PIC_SLAVE_CMD_PORT, PIC_EOI);
    }
    // Always send EOI to master
    outport8(PIC_MASTER_CMD_PORT, PIC_EOI);
}