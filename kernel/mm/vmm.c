#include <stdint.h>
#include <stddef.h>
#include <mm/vmm.h>


// Align tables to 4KiB address
static uint32_t * kernel_page_directory;
static uint32_t * kernel_page_table;


void init_vmm_structures()
{
}

  