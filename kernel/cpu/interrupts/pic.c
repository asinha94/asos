#include <stdint.h>
#include <cpu/interrupts/pic.h>
#include <cpu/hal.h>
#include <display/tty.h>


// Master PIC
#define PIC_MASTER_CMD_PORT      0x20
#define PIC_MASTER_DATA_PORT     (PIC_MASTER_CMD_PORT + 1)
#define PIC_MASTER_VECTOR_OFFSET 0x20
// Slace PIC
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


void remap_pic_irq()
{
    // Start initialization sequence of both master and slace
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
    outport8(PIC_MASTER_DATA_PORT, 0);
    outport8(PIC_SLAVE_DATA_PORT, 0);
    kernprintf("PIC re-mapped\n");
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
        outport8(PIC_SLAVE_DATA_PORT, PIC_EOI);
    }
    // Always send EOI to master
    outport8(PIC_MASTER_DATA_PORT, PIC_EOI);
}