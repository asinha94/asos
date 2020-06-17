#ifndef ASOS_IDT_H
#define ASOS_IDT_H

#include <stdint.h>

struct idt_entry_struct {
   uint16_t offset_l; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t  zero;      // unused, set to 0
   uint8_t  type_attr; // type and attributes
   uint16_t offset_h; // offset bits 16..31
};
typedef struct idt_entry_struct idt_entry;

struct idt_table_struct {
   uint16_t length;
   uint32_t entries;
} __attribute__ ((packed));
typedef struct idt_table_struct idt_table;

extern void init_idt();

#endif