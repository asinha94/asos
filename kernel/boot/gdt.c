#include <stdint.h>
#include <stddef.h>
#include <display/tty.h>
#include <boot/gdt.h>

#define GDT_SIZE 5

gdt_segment segments[GDT_SIZE];
gdt_table gdt;

/* ASM function which loads the GDT for us */
extern int asm_init_gdt(uint32_t gdt_address);

static void insert_gdt_entry(
    size_t entry,
    uint32_t base,
    uint32_t limit,
    uint8_t type,
    uint8_t granularity)
{
    if (entry >= GDT_SIZE) return;

    // Whats ironic is that all of these are 0
    segments[entry].base_lower  = (uint16_t) ((base >> 00) & 0xFFFF); // Bottom 2 bytes
    segments[entry].base_middle = (uint8_t)  ((base >> 16) & 0xFF); // Sandwich byte
    segments[entry].base_upper  = (uint8_t)  ((base >> 24) & 0xFF); // MSB

    
    segments[entry].limit_lower = (uint16_t) (limit & 0xFFFF);
    uint8_t lower_byte_of_upper_word = ((limit >> 16) & 0x0F);
    segments[entry].granularity = granularity | lower_byte_of_upper_word;
    
    // Set type; Look here https://wiki.osdev.org/Global_Descriptor_Table for details
    segments[entry].type = type;
    
}

void init_gdt()
{
    // // Null segment
    insert_gdt_entry(0, 0, 0x00000000, 0x00, 0x00); 
    // You will notice that the bottom 4 entries look very similar
    // this is because segmentation is a lot of work
    // we prefer to handle memory management through paging
    insert_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xC0); // Kernel Code segment
    insert_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xC0); // Kernel Data segment
    insert_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xC0); // User Code segment
    insert_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xC0); // User Code segment

    // load GDT at table address
    // why is the size - 1?
    gdt.length = sizeof(segments) - 1;
    gdt.segments = (uint32_t) &segments;
    asm_init_gdt((uint32_t) &gdt);
    kernprintf("GDT initialized\n");
}
