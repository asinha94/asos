#include <stdint.h>
#include <stddef.h>
#include <cpu/hal.h>
#include <mm/vmm.h>
#include <mm/pmm.h>
#include <libk/kmalloc.h>
#include <libk/kprintf.h>



// Align tables to 4KB address
static uint32_t     __kernel_pdir_paddr;
static page_table * __kernel_pdir_vaddr;


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

__attribute__((always_inline))
static inline void __invlpg(uint32_t addr) {
    asm volatile("invlpg [%0]\n"
                 :
                 :"r" (addr)
    );
}


void memset_page(page_table * table)
{
    for (size_t i = 0; i < VMM_PTABLE_LEN; ++i) {
        table->entries[i] = 0;
    }
}


void init_vmm()
{
    // TODO: Use memory map to see how much is actually used.
    // Once we get a memory map, it will make sense to allocate the array
    // dynamically again, instead of a 128KB array which might be overkill

    // VMM_KERN_ADDR_START is already mapped by the bootloader
    // Page Directory is in last 4KB of 2nd last page in virtual space
    __kernel_pdir_paddr = 2*VMM_PG_SZ_LARGE - VMM_PG_SZ_SMALL;
    __kernel_pdir_vaddr = (page_table *) (VMM_KERN_ADDR_END - VMM_PG_SZ_LARGE - VMM_PG_SZ_SMALL + 1);
    memset_page(__kernel_pdir_vaddr);

    // Mark first PDE as used and map to 3GB onwards i.e higher-half kernel
    pmm_set_range(0x0, VMM_PG_SZ_LARGE);
    insert_kernel_pde(VMM_KERN_ADDR_START, 0x0, PDE_RW_ACCESS | PDE_4MB_PAGE_SZ | PDE_PRESENT);

    // Map the second 4MB of physical memory to the 2nd last PDE in virtual space
    pmm_set_range(VMM_PG_SZ_LARGE, VMM_PG_SZ_LARGE);
    uint32_t vmm_heap_start = VMM_LAST_PDE_PAGE - VMM_PG_SZ_LARGE;
    insert_kernel_pde(vmm_heap_start, VMM_PG_SZ_LARGE, PDE_RW_ACCESS | PDE_4MB_PAGE_SZ | PDE_PRESENT);

    // The last Page directory entry is used for a recursive page. We can access a mapped page table using
    // this last entry in virtual space. It does mean we lose 4MB in all virtual address spaces, but its a small price
    insert_kernel_pde(VMM_LAST_PDE_PAGE, __kernel_pdir_paddr, PDE_RW_ACCESS | PDE_PRESENT);

    // load new page directory
    __update_page_directory(__kernel_pdir_paddr);

    // Seed kmalloc so it can operate. Last 4 KB is used for the page directory so avoid
    init_kmalloc(vmm_heap_start, VMM_PG_SZ_LARGE-VMM_PG_SZ_SMALL);
    kprintf("Initialized VMM\n");
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
    uint32_t new_page = pmm_page_alloc();
    if (!new_page) {
        return new_page;
    }

    // We already know the first and last 2 pages have been allocated so skip
    for (size_t i = VMM_PTABLE_LEN - 3; i > 0; --i) {
        uint32_t pde = __kernel_pdir_vaddr->entries[i];
        if (pde & PDE_4MB_PAGE_SZ) {
            continue;
        }
        
        // WARNING: vaddr doesn't work. Need a get_phys_addr(...) function
        // Last page is recursively mapped, so we use this to access the new page table
        page_table * new_page_table  = VMM_LAST_PDE_PAGE + (i * VMM_4KB_ALIGN_MASK);
        uint32_t vaddr = i * VMM_PG_SZ_LARGE;

        // Page table already present, lets search for an empty page entry
        if (pde & VMM_4KB_ALIGN_MASK) {
            for (size_t j = VMM_PTABLE_LEN-1; j >= 0; --j) {
                // Found an empty page entry, lets use it
                if (new_page_table->entries[j] == 0) {
                    new_page_table->entries[j] = new_page | PTE_RW_ACCESS | PTE_PRESENT;
                    // Memset the new page?
                    return vaddr + j * VMM_PG_SZ_SMALL;
                }
            }

            // Page table is full
            continue;
        }

        // Entry in directory is available. Lets use the recently allocated page for this table
        __kernel_pdir_vaddr->entries[i] = new_page | PDE_RW_ACCESS | PDE_PRESENT;
        memset_page(new_page_table);

        // Place a new page at the end of the table
        new_page = pmm_page_alloc();
        if (!new_page) {
            return new_page;
        }

        uint32_t idx = VMM_PTABLE_LEN - 1;
        new_page_table->entries[idx] = new_page | PTE_RW_ACCESS | PTE_PRESENT;
        return vaddr + idx * VMM_PG_SZ_SMALL;
    }

    return 0;
}

uint32_t allocate_page_at_vaddr(uint32_t vaddr)
{
    int offset = (vaddr & VMM_4KB_ALIGN_MASK) / VMM_PG_SZ_LARGE;
    uint32_t page_entry = __kernel_pdir_vaddr->entries[offset];

    // Insert page table entry if not present
    if (!(page_entry & PDE_PRESENT)) {
        uint32_t new_page = pmm_page_alloc();
        if (!new_page) {
            return new_page;
        }
    }

    uint32_t new_page = pmm_page_alloc();
    if (!new_page) {
        return new_page;
    }

    return 0;
}