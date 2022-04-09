#include <stdint.h>
#include <stddef.h>
#include <libk/kprintf.h>
#include <libk/kmalloc.h>
#include <mm/gdt.h>

#define GDT_SIZE 5


/* ASM function which loads the GDT for us */
extern "C" int asm_init_gdt(uint32_t gdt_address);

namespace asos {
    
    GDTSegment::GDTSegment(uint32_t base, uint32_t limit, uint8_t type, uint8_t granularity)
    {
        // The irony is that all of these are 0 when we favor paging over segmentation
        this->m_base_lower  = (uint16_t) ((base >> 00) & 0xFFFF);
        this->m_base_middle = (uint8_t) ((base >> 16) & 0xFF);
        this->m_base_upper  = (uint8_t) ((base >> 24) & 0xFF);

        this->m_limit_lower = (uint16_t) (limit & 0xFFFF);
        this->m_granularity = granularity | ((limit >> 16) & 0x0F);
        // Set type; Look here https://wiki.osdev.org/Global_Descriptor_Table for details
        this->m_type = type;
    }

    void GDTTable::initGDT()
    {
        GDTSegment * __segments = (GDTSegment *) kmalloc(GDTTable::table_size * sizeof(GDTSegment));
        // Create linear address space, handle memory isolation through paging
        __segments[0] = GDTSegment(0, 0x00000000, 0x00, 0x00); // Null segment
        __segments[1] = GDTSegment(0, 0xFFFFFFFF, 0x9A, 0xC0); // Kernel Code segment
        __segments[2] = GDTSegment(0, 0xFFFFFFFF, 0x92, 0xC0); // Kernel Data segment
        __segments[3] = GDTSegment(0, 0xFFFFFFFF, 0xFA, 0xC0); // User Code segment
        __segments[4] = GDTSegment(0, 0xFFFFFFFF, 0xF2, 0xC0); // User Code segment

        GDTTable * __gdt_table = (GDTTable *) kmalloc(sizeof(GDTTable));
        __gdt_table->m_length = (GDTTable::table_size * sizeof(GDTSegment)) - 1;
        __gdt_table->m_segments = (uint32_t) __segments;
        asm_init_gdt((uint32_t) __gdt_table);
        kprintf("GDT initialized\n");
    }
}


