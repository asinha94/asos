#include <stdint.h>
#include <stddef.h>
#include <mm/vmm.h>
#include <mm/pmm.h>
#include <libk/kmalloc.h>


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
    // and identity map last 4MB for paging structures
    uint32_t flags = PDE_PRESENT | PDE_RW_ACCESS | PDE_4MB_PAGE_SZ;
    insert_kernel_pde_into_dir(VMM_KERN_ADDR_START, 0x0, flags);
    insert_kernel_pde_into_dir(VMM_PAGING_ADDR, VMM_PAGING_ADDR, flags);

    // Map kernel heap location
    // inline asm here for setting pde


    init_kmalloc();
}


/*
void insert_pde_into_dir(page_directory * dir, uint32_t v_addr, uint32_t p_addr, uint32_t flags)
{
    // Mask out addr[10:21] if its a 4MB Page. Not sure if its actually necessary
    uint32_t entry =  p_addr & ((flags & PDE_4MB_PAGE_SZ) ? VMM_4MB_ALIGN_MASK : VMM_4KB_ALIGN_MASK);
    dir->entries[v_addr / VMM_PG_SZ_LARGE] = entry | flags;
}
*/


void insert_kernel_pde_into_dir(uint32_t v_addr, uint32_t p_addr, uint32_t flags)
{
    // Mask out addr[10:21] if its a 4MB Page. Not sure if its actually necessary
    uint32_t entry =  p_addr & ((flags & PDE_4MB_PAGE_SZ) ? VMM_4MB_ALIGN_MASK : VMM_4KB_ALIGN_MASK);
    kernel_pdir->entries[v_addr / VMM_PG_SZ_LARGE] = entry | flags;
}


void insert_kernel_pte_into_dir(uint32_t v_addr, uint32_t p_addr, uint32_t flags)
{
    // Mask out addr[10:21] if its a 4MB Page. Not sure if its actually necessary
    uint32_t entry =  p_addr & ((flags & PDE_4MB_PAGE_SZ) ? VMM_4MB_ALIGN_MASK : VMM_4KB_ALIGN_MASK);
    kernel_pdir->entries[v_addr / VMM_PG_SZ_LARGE] = entry | flags;
}