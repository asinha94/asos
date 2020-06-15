#ifndef ASOS_PIC_H
#define ASOS_PIC_H

#include <stdint.h>

void remap_pic_irq();
void irq_clear_mask(uint8_t irq_number);
void irq_set_mask(uint8_t irq_number);
void irq_eoi();

#endif