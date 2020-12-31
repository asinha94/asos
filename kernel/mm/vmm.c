#include <stdint.h>
#include <stddef.h>
#include <mm/vmm.h>
#include <mm/pmm.h>
#include <libk/kmalloc.h>


// Align tables to 4KB address
static page_directory * __kernel_pdir;

__attribute__((always_inline))
static inline void __update_page_directory(page_directory * pdir)
{
    // put pointer to kernel_page in cr3
    asm volatile(
        "mov cr3, %0\n"
        :
        : "r"(pdir)
    );
}


void init_vmm()
{
    // Boot code has already identity mapped last page
    // So we grab a 4KB chunk from that area. This area is limited to ~4MB
    // so we might need to grab something from kmalloc when it fails
    // TODO: use kmalloc if this fails
    __kernel_pdir = pmm_page_alloc();

    // Map kernel to higher half i.e from 3GB onwards
    // and identity map last 4MB for paging structures
    uint32_t flags = PDE_PRESENT | PDE_RW_ACCESS | PDE_4MB_PAGE_SZ;
    insert_kernel_pde(VMM_KERN_ADDR_START, 0x0, flags);
    insert_kernel_pde(VMM_PAGING_ADDR, VMM_PAGING_ADDR, flags);

    init_kmalloc();
    // load new page directory
    __update_page_directory(__kernel_pdir);
    
}


void insert_kernel_pde(uint32_t vaddr, uint32_t paddr, uint32_t flags)
{
    // Mask out addr[21:12] if its a 4MB Page. Not sure if its actually necessary
    uint32_t entry =  paddr & ((flags & PDE_4MB_PAGE_SZ) ? VMM_4MB_ALIGN_MASK : VMM_4KB_ALIGN_MASK);
    uint32_t idx = vaddr >> 22; // Divide by 4MB
    __kernel_pdir->entries[idx] = entry | flags;
}


void insert_kernel_pte(uint32_t vaddr, uint32_t paddr, uint32_t flags)
{
    uint32_t idx = vaddr >> 22; // Divide by 4MB
    page_table * pt =  (page_table *) (__kernel_pdir->entries[idx] & VMM_4KB_ALIGN_MASK);

    // No page present, need to allocate one
    if (pt == NULL) {
        pt = pmm_page_alloc(); // TODO: Handle NULL
        uint32_t pde_flags = PDE_PRESENT | PDE_RW_ACCESS;
        __kernel_pdir->entries[idx] = (uint32_t) pt | pde_flags;
    }

    // bits [21:12] are what we want to find index in the page table
    // so we need to divide those 10 bits by 4KB (addr >> 12)
    idx = (vaddr >> 12) & 0x3FF;
    pt->entries[idx] = paddr | flags;
}