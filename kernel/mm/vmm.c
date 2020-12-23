#include <stdint.h>
#include <stddef.h>
#include <libk/string.h>
#include <mm/vmm.h>


// Align tables to 4KB address
static page_directory * page_dir;


void init_vmm()
{
    // Boot code has already identity mapped last page
    // So we grab that and use the first 4KB for the PDE
    // TODO: we should probably grab this from kmalloc?
    // For now we hardcode the directory to the beggining of the last PDE
    page_dir = (page_directory *) VMM_PAGING_ADDR;
    memset(page_dir, 0, sizeof(page_directory));
    // TODO: free 4MB-1MB-4KB block back to kmalloc

    // Map in Higher half kernel at 3GB
    uint32_t kernel_offset = VMM_KERN_ADDR_START / VMM_PG_SZ_LARGE;
    page_dir->dir[kernel_offset] = \
        0x0 | PDE_PRESENT | PDE_RW_ACCESS | PDE_4MB_PAGE_SZ;

    // Map last 4MB used for paging initially
    uint32_t paging_offset = VMM_PAGING_ADDR / VMM_PG_SZ_LARGE;
    page_dir->dir[kernel_offset] = \
        (VMM_PAGING_ADDR & VMM_4MB_ALIGN_MASK) | PDE_PRESENT | PDE_RW_ACCESS | PDE_4MB_PAGE_SZ;

}

  