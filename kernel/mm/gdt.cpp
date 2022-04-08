#include <stdint.h>
#include <stddef.h>
#include <libk/kprintf.h>
#include <mm/gdt.h>

#define GDT_SIZE 5

static gdt_segment segments[GDT_SIZE];
static gdt_table gdt;

/* ASM function which loads the GDT for us */
extern "C" int asm_init_gdt(uint32_t gdt_address);

static void insert_gdt_entry(
    uint8_t index,
    uint32_t base,
    uint32_t limit,
    uint8_t type,
    uint8_t granularity)
{
    // Whats ironic is that all of these are 0
    segments[index].base_lower  = (uint16_t) ((base >> 00) & 0xFFFF); // Bottom 2 bytes
    segments[index].base_middle = (uint8_t)  ((base >> 16) & 0xFF); // Sandwich byte
    segments[index].base_upper  = (uint8_t)  ((base >> 24) & 0xFF); // MSB

    
    segments[index].limit_lower = (uint16_t) (limit & 0xFFFF);
    uint8_t lower_nibble_of_upper_word = ((limit >> 16) & 0x0F);
    segments[index].granularity = granularity | lower_nibble_of_upper_word;
    
    // Set type; Look here https://wiki.osdev.org/Global_Descriptor_Table for details
    segments[index].type = type;
    
}

void init_gdt()
{
    // // Null segment
    insert_gdt_entry(0, 0, 0x00000000, 0x00, 0x00); 
    // Create linear address space
    // handle memory isolation through paging
    insert_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xC0); // Kernel Code segment
    insert_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xC0); // Kernel Data segment
    insert_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xC0); // User Code segment
    insert_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xC0); // User Code segment

    // load GDT at table address
    // why is the size - 1?
    gdt.length = sizeof(segments) - 1;
    gdt.segments = (uint32_t) &segments;
    asm_init_gdt((uint32_t) &gdt);
    kprintf("GDT initialized\n");
}
