#include <stdint.h>

#define NUM_PAGE_ENTRIES 1024

// Align tables to 4KiB address
uint32_t page_directory[NUM_PAGE_ENTRIES] __attribute__((aligned(4096)));
uint32_t page_table[NUM_PAGE_ENTRIES] __attribute__((aligned(4096)));


void init_paging()
{
    // clear page directory
    for (int i = 0; i < NUM_PAGE_ENTRIES; ++i) {
        // Setup page directories as read/write for supervisor only
        // page is set as not-present so access will lead to fault
        page_directory[i] = 0x00000002; 
    }

    // initialize our page table
    for (int i = 0; i < NUM_PAGE_ENTRIES; ++i) {
        // 0x1000 means the first 12 bits are zeroed i.e the non-address bits
        // 3 i.e first 2 bits means RW and present i.e can be read/written to
        // by kernel
        page_table[i] = (i * 0x1000) | 0x3;
        // The entire page table has been mapped which means 4MiB has been mapped
        // we could alternatively make a single 4MiB page entry, by setting the size bit
        // More info found here: https://wiki.osdev.org/Paging
    }

    // assign table as only entry in directory
    page_directory[0] = (uint32_t) page_table;

}

  