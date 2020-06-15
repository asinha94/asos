#include <stdint.h>
#include <cpu/pic.h>
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
    // save masks
    uint8_t imr1 = inportb(PIC_MASTER_DATA_PORT);
    uint8_t imr2 = inportb(PIC_SLAVE_DATA_PORT);

    // Start initialization sequence of both master and slace
    outportb(PIC_MASTER_CMD_PORT, ICW1_INIT | PIC_ICW1_ICW4);
    io_wait();
    outportb(PIC_SLAVE_CMD_PORT, ICW1_INIT | PIC_ICW1_ICW4);
    io_wait();

    // Remap Vector offsets to non-reserved range
    outportb(PIC_MASTER_DATA_PORT, PIC_MASTER_VECTOR_OFFSET);
    io_wait();
    outportb(PIC_SLAVE_DATA_PORT, PIC_SLAVE_VECTOR_OFFSET);
    io_wait();

    // Init Cascade topology i.e slace IRQ2 wired to master
    outportb(PIC_MASTER_DATA_PORT, PIC_MASTER_CASCADE_IRQ);
    io_wait();
    outportb(PIC_SLAVE_DATA_PORT, PIC_SLAVE_CASCADE_IRQ);
    io_wait();

    // 8086 mode
    outportb(PIC_MASTER_DATA_PORT, ICW4_8086);
    io_wait();
    outportb(PIC_SLAVE_DATA_PORT, ICW4_8086);
    io_wait();

    // restore the saved masks
    outportb(PIC_MASTER_DATA_PORT, imr1);
    outportb(PIC_SLAVE_DATA_PORT, imr2);
    kernprintf("PIC intialized\n");
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
    data = inportb(port) & ~(1 << irq_number);
    // Flip bit corresponding to irq_number
    outportb(port, data);
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
    data = inportb(port) | (1 << irq_number);
    outportb(port, data);
}

void irq_eoi()
{
    return;
}