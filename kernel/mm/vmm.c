#include <stdint.h>
#include <stddef.h>
#include <mm/vmm.h>
#include <mm/pmm.h>


// Align tables to 4KB address
static page_directory * kernel_pdir;


void init_vmm()
{
    // Boot code has already identity mapped last page
    // So we grab a 4KB chunk from that area. This area is limited to ~4MB
    // so we might need to grab something from kmalloc when it fails
    // TODO: use kmalloc if this fails
    kernel_pdir = pmm_page_alloc();

    // Map kernel to higher half i.e from 3GB onwards
    uint32_t flags = PDE_PRESENT | PDE_RW_ACCESS | PDE_4MB_PAGE_SZ;
    insert_pde_into_directory(kernel_pdir, VMM_KERN_ADDR_START, 0x0, flags);
    // Identity map last 4MB for paging
    insert_pde_into_directory(kernel_pdir, VMM_PAGING_ADDR, VMM_PAGING_ADDR, flags);

    // Map kernel heap location

}

void insert_pde_into_directory(page_directory * dir, uint32_t v_addr, uint32_t p_addr, uint32_t flags)
{
    // Mask out addr[10:21] if its a 4MB Page. Not sure if its actually necessary
    uint32_t entry =  p_addr & ((flags & PDE_4MB_PAGE_SZ) ? VMM_4MB_ALIGN_MASK : VMM_4KB_ALIGN_MASK);
    dir->entries[v_addr / VMM_PG_SZ_LARGE] = entry | flags;
}

/*
void insert_pte_into_directory(page_directory * tbl, uint32_t vaddr, uint32_t addr, uint32_t flags)
{

}
*/