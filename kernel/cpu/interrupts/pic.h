#ifndef ASOS_PIC_H
#define ASOS_PIC_H

#include <stdint.h>

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


void init_irq();
void irq_clear_mask(uint8_t irq_number);
void irq_set_mask(uint8_t irq_number);
void irq_eoi(uint8_t irq_number);

#endif