#include <stdint.h>
#include <stddef.h>
#include <mm/pmm.h>
#include <mm/vmm.h>
#include <libk/string.h>
#include <libk/math.h>

static void pmm_set_page(size_t pg_num);
static void pmm_unset_page(size_t pg_num);
static void pmm_set_range(uint32_t addr, uint32_t len);
static void pmm_unset_range(uint32_t addr, uint32_t len);


static uint32_t pmm_mmap[PMM_BITMAP_LEN];
static size_t used_pages = 0;


void init_pmm()
{
    // TODO: add utility function to mark large sections at the same time

    // TODO: replace with memset once optimized?
    for (int i = 0; i < PMM_BITMAP_LEN; ++i)
    {
        pmm_mmap[i] = 0x0; 
    }

    // Mark first Page dir entry i.e real-mode address and loaded Kernel
    // TODO: Use memory map to see how much is actually used
    pmm_set_range(0x0, VMM_PG_SZ_LARGE);
}


static void pmm_set_page(size_t pg_num)
{
    uint32_t word_num = pg_num / 32;
    uint32_t bit_num = pg_num % 32;
    pmm_mmap[word_num] |= (1 << (bit_num));
    used_pages++;
}

static void pmm_unset_page(size_t pg_num)
{
    uint32_t word_num = pg_num / 32;
    uint32_t bit_num = pg_num % 32;
    pmm_mmap[word_num] &= ~(1 << (bit_num));
    used_pages--;
}

static void pmm_set_range(uint32_t addr, uint32_t len)
{
    uint32_t pg_num = addr / VMM_PG_SZ_SMALL;
    // If len isn't multiple of 4K, clear next page
    uint32_t pages = div_ceil(len, VMM_PG_SZ_SMALL);

    for (size_t i = 0; i < pages; ++i) {
        pmm_set_page(pg_num + i);
    }
}

static void pmm_unset_range(uint32_t addr, uint32_t len)
{
    uint32_t pg_num = addr / VMM_PG_SZ_SMALL;
    uint32_t pages = len / VMM_PG_SZ_SMALL;
    // Clear page if bytes bleed over boundary
    if (len % VMM_PG_SZ_SMALL) {
        ++pages;
    }

    for (size_t i = 0; i < pages; ++i) {
        pmm_unset_page(pg_num + i);
    }
}

static void * get_page_in_range(uint32_t start_addr, uint32_t end_addr)
{
    if (used_pages >= PMM_BITMAP_VALUES) {
        return 0;
    }

    // Assume all addresses are 4K aligned
    uint32_t div = VMM_PG_SZ_SMALL * 32;
    size_t start_pgnum = start_addr / div;
    size_t end_pgnum = div_ceil(end_addr, div);
    for (size_t i = start_pgnum; i < end_pgnum; i++) {
        // Check if this set of 32 pages are free or not
        if (pmm_mmap[i] == 0xFFFFFFFF) {
            continue;
        }

        uint32_t dword = pmm_mmap[i];
        // At least 1 bit is free, grab it
        for (size_t j = 0; j < 32; j++){
            if ((dword >> j) & 0x1) {
                continue;
            }

            // Found the bit, set it and return the paddr
            uint32_t pg_num = i * 32 + j;
            pmm_set_page(pg_num);
            return (void *) (pg_num * VMM_PG_SZ_SMALL);
        }
    }

    return 0;
} 

void * pmm_get_page()
{
    return get_page_in_range(0x0, VMM_PAGING_ADDR);
}

void * pmm_page_alloc()
{
    uint32_t * paddr = get_page_in_range(VMM_PAGING_ADDR, VMM_KERN_ADDR_END);
    memset(paddr, 0, VMM_PG_SZ_SMALL);
    return paddr;
}

