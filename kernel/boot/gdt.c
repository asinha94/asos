#include <stdint.h>
#include <stddef.h>
#include <display/tty.h>
#include <boot/gdt.h>

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
#define GDT_BASE_MIDDLE(base) ((base & GDT_MASK_BASE_MIDDLE) >> GDT_BASE_MIDDLE_SHIFT)
#define GDT_BASE_UPPER(base)  (base & GDT_MASK_BASE_UPPPER) >> GDT_BASE_UPPER_SHIFT

#define GDT_LIMIT_LOWER(base) ((base & GDT_LIMIT_LOWER_SHIFT) >> GDT_LIMIT_LOWER_SHIFT)
#define GDT_LIMIT_UPPER(base) ((base & GDT_LIMIT_UPPER_SHIFT) >> GDT_LIMIT_UPPER_SHIFT)


gdt_segments segments[GDT_SIZE];
gdt_table gdt;


/* ASM function which loads the GDT for us */
extern int asm_init_gdt(uint32_t gdt_address);


static void insert_gdt_entry(
    size_t entry,
    uint32_t position,
    uint32_t length,
    uint8_t type,
    uint8_t granularity)
{
    if (entry >= GDT_SIZE) return;

    segments[entry].type = type;
    segments[entry].limit_lower = GDT_LIMIT_LOWER(length);
    segments[entry].granularity = GDT_LIMIT_UPPER(length) | granularity;
    segments[entry].base_lower  = GDT_BASE_LOWER(position);
    segments[entry].base_middle = GDT_BASE_MIDDLE(position);
    segments[entry].base_upper  = GDT_BASE_UPPER(position);
}

void init_gdt()
{
    // // Null segment
    insert_gdt_entry(0, 0, 0x00000000, 0x00, 0x00); 
    // You will notice that the bottom 4 entries look very similar
    // this is because segmentation is a lot of work
    // we prefer to handle memory management through paging
    insert_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel Code segment
    insert_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel Data segment
    insert_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User Code segment
    insert_gdt_entry(4, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User Code segment

    // load GDT at table address
    // why is the size - 1?
    gdt.length = sizeof(segments) - 1;
    gdt.segments_addr = (uint32_t) &segments;
    asm_init_gdt((uint32_t) &gdt);
    tty_writestring("GDT initialized\n");
}
