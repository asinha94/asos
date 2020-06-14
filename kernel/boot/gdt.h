#ifndef ASOS_GDT_H
#define ASOS_GDT_H

#include <stdint.h>
#include <stddef.h>

struct gdt_struct {
    uint16_t limit_lower;
    uint16_t base_lower;
    uint8_t  base_middle;
    uint8_t  type;
    uint8_t  granularity;
    uint8_t  base_upper;
} __attribute__ ((packed));
typedef struct gdt_struct gdt_segments;

struct gdt_table_ptr {
    uint16_t length;
    uint32_t table_addr;
} __attribute__ ((packed));
typedef struct gdt_table_ptr gdt_ptr;


extern void init_gdt();

#endif
