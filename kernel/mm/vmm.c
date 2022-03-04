#include <stdint.h>
#include <stddef.h>
#include <mm/vmm.h>
#include <mm/pmm.h>
#include <libk/kmalloc.h>
#include <cpu/hal.h>


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
    // Boot code has already mapped the 2nd 4MB PDE, grab a 4KB chunk
    // from that area. This area is limited to ~4MB so be wary
    void * pd_paddr = pmm_page_alloc();
    __kernel_pdir = PG_P2V(pd_paddr);

    // Map kernel to higher half i.e from 3GB onwards
    // and next 4MB og physical memory to the last 4MB of virtual memory (used for paging structures)
    uint32_t flags = PDE_PRESENT | PDE_RW_ACCESS | PDE_4MB_PAGE_SZ;
    insert_kernel_pde(VMM_KERN_ADDR_START, 0x0, flags);
    insert_kernel_pde(VMM_PAGING_ADDR_START, PMM_PAGING_ADDR_START, flags);

    init_kmalloc();
    // load new page directory
    __update_page_directory(pd_paddr);
    
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
    uint32_t pd_addr =  __kernel_pdir->entries[idx] & VMM_4KB_ALIGN_MASK;

    // No page present, need to allocate one
    if (!pd_addr) {
        pd_addr = (uint32_t) pmm_page_alloc(); // TODO: Handle NULL
        __kernel_pdir->entries[idx] = pd_addr | PDE_PRESENT | PDE_RW_ACCESS;
    }

    // bits [21:12] are what we want to find index in the page table
    // so we need to divide those 10 bits by 4KB (addr >> 12)
    idx = (vaddr >> 12) & 0x3FF;
    page_table * pt = PG_P2V((void *)pd_addr);
    pt->entries[idx] = paddr | flags;
}