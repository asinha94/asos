#ifndef ASOS_IDT_H
#define ASOS_IDT_H

#include <stdint.h>

struct idt_struct {
   uint16_t offset_l; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t  zero;      // unused, set to 0
   uint8_t  type_attr; // type and attributes
   uint16_t offset_h; // offset bits 16..31
} __attribute__ ((packed));
typedef struct idt_struct idt_descriptor;

extern void init_idt();

#endif