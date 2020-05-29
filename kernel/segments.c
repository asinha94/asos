#include <stdint.h>
#include <stddef.h>
#include "segments.h"

//--------------------------------------------------------------------------------------------------------------
// Macros
//--------------------------------------------------------------------------------------------------------------
#define GDT_SIZE 5

// GDT Masks
#define GDT_MASK_BASE_LOWER  0x0000FFFF
#define GDT_MASK_BASE_MIDDLE 0x00FF0000
#define GDT_MASK_BASE_UPPPER 0xFF000000

#define GDT_MASK_LIMIT_LOWER 0x0FFFF000
#define GDT_MASK_LIMIT_UPPER 0xF0000000

// GDT Shifts
#define GDT_BASE_MIDDLE_SHIFT 16
#define GDT_BASE_UPPER_SHIFT  24

#define GDT_LIMIT_LOWER_SHIFT 12
#define GDT_LIMIT_UPPER_SHIFT 28

// GDT Macros
#define GDT_BASE_LOWER(base)  (base & GDT_MASK_BASE_LOWER)
#define GDT_BASE_MIDDLE(base) (base & GDT_MASK_BASE_MIDDLE) >> GDT_BASE_MIDDLE_SHIFT
#define GDT_BASE_UPPER(base)  (base & GDT_MASK_BASE_UPPPER) >> GDT_BASE_UPPER_SHIFT

#define GDT_LIMIT_LOWER(base) (base & GDT_LIMIT_LOWER_SHIFT) >> GDT_LIMIT_LOWER_SHIFT
#define GDT_LIMIT_UPPER(base) (base & GDT_LIMIT_UPPER_SHIFT) >> GDT_LIMIT_UPPER_SHIFT


//--------------------------------------------------------------------------------------------------------------
// Global local variables
//--------------------------------------------------------------------------------------------------------------
gdt_segments segments[GDT_SIZE];
gdt_ptr table;

//--------------------------------------------------------------------------------------------------------------
// Declarations
//-------------------------------------------------------------------------------------------------------------
extern int asm_init_gdt(uint32_t gdt_address);

//--------------------------------------------------------------------------------------------------------------
// Function definitions
//--------------------------------------------------------------------------------------------------------------
void insert_gdt_entry(size_t entry, uint32_t position, uint32_t length, uint8_t type, uint8_t granularity) {
    if (entry >= GDT_SIZE) return;

    segments[entry].type = type;
    segments[entry].limit_lower = GDT_LIMIT_LOWER(length);
    segments[entry].granularity = GDT_LIMIT_UPPER(length) | granularity;
    segments[entry].base_lower  = GDT_BASE_LOWER(position);
    segments[entry].base_middle = GDT_BASE_MIDDLE(position);
    segments[entry].base_upper  = GDT_BASE_UPPER(position);
}

void load_gdt_table() {
    insert_gdt_entry(0, 0, 0x00000000, 0x00, 0x00); // Null segment
    insert_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel Code segment
    insert_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel Data segment
    insert_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User Code segment
    insert_gdt_entry(4, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User Code segment

    // pass table address to CPU
    table.length = (sizeof(gdt_segments) * GDT_SIZE) - 1;
    table.base = (uint32_t) &segments;

    // LGDT table
    // asm_init_gdt((uint32_t) &table);
}
