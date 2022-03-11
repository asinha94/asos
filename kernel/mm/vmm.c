#include <stdint.h>
#include <stddef.h>
#include <mm/vmm.h>
#include <mm/pmm.h>
#include <libk/kmalloc.h>
#include <cpu/hal.h>


// Align tables to 4KB address
static uint32_t         __kernel_pdir_paddr;
static page_directory * __kernel_pdir_vaddr;


__attribute__((always_inline))
static inline void __update_page_directory(uint32_t pdir)
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
    // Mark first PDE as used i.e loaded Kernel + addresses < 1MB
    // TODO: Use memory map to see how much is actually used
    // Once we get a memory map, it will make sense to allocate the array
    // dynamically again, instead of a 128KB array which might be overkill
    pmm_set_range(0x0, VMM_PG_SZ_LARGE);
    // Map the second 4MB PDE to the end of memory and pass it to kmalloc
    pmm_set_range(VMM_PG_SZ_LARGE, VMM_PG_SZ_LARGE);

    // Use the page Directly lives in the last 4KB of the 2nd PDE
    __kernel_pdir_paddr = 2*VMM_PG_SZ_LARGE - VMM_PG_SZ_SMALL;
    __kernel_pdir_vaddr = (page_directory *) VMM_PGDIR_ADDR;

    // Map kernel (1st 4MB of physical memory ) to higher half i.e from 3GB onwards
    uint32_t flags = PDE_PRESENT | PDE_RW_ACCESS | PDE_4MB_PAGE_SZ;
    insert_kernel_pde(VMM_KERN_ADDR_START, 0x0, flags);
    // and next 4MB of physical memory to the last 4MB of virtual memory
    insert_kernel_pde(VMM_HEAP_START, VMM_PG_SZ_LARGE, flags);

    // load new page directory
    __update_page_directory(__kernel_pdir_paddr);

    // Seed kmalloc so it can operate. Last 4 KB is used for the page directory
    init_kmalloc(VMM_HEAP_START, VMM_PG_SZ_LARGE-VMM_PG_SZ_SMALL);
}


void insert_kernel_pde(uint32_t vaddr, uint32_t paddr, uint32_t flags)
{
    // Mask out addr[21:12] if its a 4MB Page. Not sure if its actually necessary
    uint32_t entry =  paddr & ((flags & PDE_4MB_PAGE_SZ) ? VMM_4MB_ALIGN_MASK : VMM_4KB_ALIGN_MASK);
    uint32_t idx = vaddr >> 22; // Divide by 4MB
    __kernel_pdir_vaddr->entries[idx] = entry | flags;
}


void insert_kernel_pte(uint32_t vaddr, uint32_t paddr, uint32_t flags)
{
    // WARNING: This function as is doesn't work, because we don't use page tables yet (only directories)
    return;

    uint32_t idx = vaddr >> 22; // Divide by 4MB
    uint32_t pd_addr = __kernel_pdir_vaddr->entries[idx] & VMM_4KB_ALIGN_MASK;

    // No page present, need to allocate one
    if (!pd_addr) {
        pd_addr = (uint32_t) pmm_page_alloc(); // TODO: Handle NULL
        __kernel_pdir_vaddr->entries[idx] = pd_addr | PDE_PRESENT | PDE_RW_ACCESS;
    }

    // bits [21:12] are what we want to find index in the page table
    // so we need to divide those 10 bits by 4KB (addr >> 12)
    idx = (vaddr >> 12) & 0x3FF;
    //page_table * pt = PG_P2V((void *)pd_addr);
    //pt->entries[idx] = paddr | flags;
}

int is_page_table_present(uint32_t paddr)
{
    __kernel_pdir_vaddr->entries[0];
}