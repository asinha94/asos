#include <stdint.h>
#include <stddef.h>
#include <cpu/hal.h>
#include <mm/vmm.h>
#include <mm/pmm.h>
#include <libk/kmalloc.h>
#include <libk/kprintf.h>



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
    memset_page((uint32_t) __kernel_pdir_vaddr);

    // Map kernel (1st 4MB of physical memory ) to higher half i.e from 3GB onwards
    uint32_t flags = PDE_RW_ACCESS | PDE_4MB_PAGE_SZ | PDE_PRESENT;
    insert_kernel_pde(VMM_KERN_ADDR_START, 0x0, flags);
    // and next 4MB of physical memory to the last 4MB of virtual memory
    insert_kernel_pde(VMM_HEAP_START, VMM_PG_SZ_LARGE, flags);

    // load new page directory
    __update_page_directory(__kernel_pdir_paddr);

    // Seed kmalloc so it can operate. Last 4 KB is used for the page directory
    init_kmalloc(VMM_HEAP_START, VMM_PG_SZ_LARGE-VMM_PG_SZ_SMALL);
    kprintf("Initialized VMM\n");
}


void memset_page(uint32_t table)
{
    for (uint32_t i=0; i<VMM_PDIR_LEN; ++i) {
        ((page_directory *) table)->entries[i] = 0;
    }
}


void insert_kernel_pde(uint32_t vaddr, uint32_t paddr, uint32_t flags)
{
    // Mask out addr[21:12] if its a 4MB Page. Not sure if its actually necessary
    uint32_t entry =  paddr & ((flags & PDE_4MB_PAGE_SZ) ? VMM_4MB_ALIGN_MASK : VMM_4KB_ALIGN_MASK);
    uint32_t idx = vaddr >> 22; // Divide by 4MB
    __kernel_pdir_vaddr->entries[idx] = entry | flags;
}


uint32_t get_virtual_page()
{
    uint32_t idx;
    uint32_t new_page = pmm_page_alloc();
    if (!new_page) {
        return new_page;
    }

    // We already know the first and last pages have  been allocated so skip
    for (uint32_t i = VMM_PDIR_LEN - 2; i > 0; --i) {
        uint32_t pde = __kernel_pdir_vaddr->entries[i];
        if (pde & PDE_4MB_PAGE_SZ) {
            continue;
        }

        // Page table already present, lets search for an empty page entry
        page_table * vaddr = (page_table *) (i * VMM_PG_SZ_LARGE);
        if (pde & VMM_4KB_ALIGN_MASK) {
            
            for (uint32_t j = 0; j < VMM_PTABLE_LEN; ++j) {
                idx = VMM_PTABLE_LEN - j - 1;
                // Found an empty page entry, lets use it
                if (vaddr->entries[idx] == 0) {
                    vaddr->entries[idx] = new_page | PTE_RW_ACCESS;
                    // Memset the new page?
                    return ((uint32_t) vaddr) + idx * VMM_PG_SZ_SMALL;
                }

            }
        }

        // Entry in directory is available. Lets use the recently allocated page for this table
        __kernel_pdir_vaddr->entries[i] = new_page | PTE_RW_ACCESS;
        memset_page((uint32_t) vaddr);

        // Place a new page at the end of the table
        new_page = pmm_page_alloc();
        if (!new_page) {
            return new_page;
        }

        idx = VMM_PTABLE_LEN-1;
        vaddr->entries[idx] = new_page | PTE_RW_ACCESS;
        return ((uint32_t) vaddr) + idx * VMM_PG_SZ_SMALL;
            
    }

    return NULL;
}