#include <stdint.h>
#include <stddef.h>
#include <boot/multiboot.h>
#include <mm/pmm.h>
#include <mm/vmm.h>
#include <libk/string.h>
#include <libk/math.h>
#include <libk/kprintf.h>

static void pmm_set_page(size_t pg_num);
static void pmm_unset_page(size_t pg_num);


static uint32_t pmm_mmap[PMM_BITMAP_LEN];
static size_t used_pages = 0;


void init_pmm(multiboot_info_t * mbi)
{
    for (size_t i = 0; i < PMM_BITMAP_LEN; ++i)
    {
        pmm_mmap[i] = 0x0; 
    }

    // TODO: Configure the PMM Memory Map
    if (mbi->flags & MULTIBOOT_INFO_MEMORY) {
        kprintf("Mem lower: %x\nMem Upper: %x\n", mbi->mem_lower, mbi->mem_upper);
         // Not sure if this is the last byte or the upper bounds of memory
        uint32_t phys_memory_end = 0x100000 + mbi->mem_upper;
    }

    kprintf("Initialized PMM\n");
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

void pmm_set_range(uint32_t addr, uint32_t len)
{
    uint32_t pg_num = addr / VMM_PG_SZ_SMALL;
    // If len isn't multiple of 4K, clear next page
    uint32_t pages = div_ceil(len, VMM_PG_SZ_SMALL);

    for (size_t i = 0; i < pages; ++i) {
        pmm_set_page(pg_num + i);
    }
}

void pmm_unset_range(uint32_t addr, uint32_t len)
{
    uint32_t pg_num = addr / VMM_PG_SZ_SMALL;
    uint32_t pages = div_ceil(len, VMM_PG_SZ_SMALL);

    for (size_t i = 0; i < pages; ++i) {
        pmm_unset_page(pg_num + i);
    }
}

static uint32_t get_page_in_range(uint32_t start_addr, uint32_t end_addr)
{
    if (used_pages >= PMM_BITMAP_VALUES) {
        return NULL;
    }

    // Assume all addresses are 4K aligned
    uint32_t div = VMM_PG_SZ_SMALL * 32;
    // pg group being the 32 4K pages per array entry
    size_t start_pggroup = start_addr / div;
    size_t end_pggroup = div_ceil(end_addr, div);
    for (size_t i = start_pggroup; i < end_pggroup; i++) {
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
            return pg_num * VMM_PG_SZ_SMALL;
        }
    }

    return NULL;
} 

uint32_t pmm_page_alloc()
{
    // TODO: replace VMM_KERN_ADDR_END with the actual end of memory
    // when we get a memory map
    return get_page_in_range(PMM_PAGING_ADDR_END+1, VMM_KERN_ADDR_END);
}


