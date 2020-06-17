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

struct isr_data_struct {
    uint32_t eax;
};
typedef struct isr_data_struct isr_data;

// ivect is a pointer to void function which takes a pointer to isr_input
typedef void (*ivect)(isr_data * );

extern void insert_idt_entry(uint8_t index, uint32_t handler, ivect c_handler);
extern void init_idt();

#endif