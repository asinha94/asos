#include <stdint.h>
#include <stddef.h>
#include <mm/pmm.h>
#include <mm/vmm.h>

static uint32_t * pmm_memory_map;
static uint32_t pmm_map_len     = PMM_BITMAP_LEN;
static size_t next_free_page    = 0;


static void pmm_set_page(size_t pg_num);
static void pmm_unset_page(size_t pg_num);
static void pmm_set_range(uint32_t addr, uint32_t len);
static void pmm_unset_range(uint32_t addr, uint32_t len);


static void pmm_set_page(size_t pg_num)
{
    pmm_memory_map[pg_num / 32] |= (1 << (pg_num % 32));
}

static void pmm_unset_page(size_t pg_num)
{
    pmm_memory_map[pg_num / 32] &= ~(1 << (pg_num % 32));
}

static void pmm_set_range(uint32_t addr, uint32_t len)
{
    uint32_t pg_num = addr / VMM_PG_SZ_SMALL;
    uint32_t pages = len / VMM_PG_SZ_SMALL;
    // If len isn't multiple of 4K, clear next page
    if (len % VMM_PG_SZ_SMALL) {
        ++pages;
    }

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


void init_pmm()
{
    // TODO: add utility function to mark large sections at the same time

    // Place bitmap at the end of physical memory, in the last 1 MiB
    pmm_memory_map = (uint32_t *) PMM_BITMAP_ADDR;

    // Mark first Page dir entry i.e real-mode address and loaded Kernel
    pmm_set_range(0x0, VMM_PG_SZ_LARGE);

    // Set final 1 MiB  as used i.e the place where all our paging structures are held
    uint32_t last_page_addr = PMM_RAM_SIZE - PMM_BITMAP_SZ_BYTES;
    pmm_set_range(last_page_addr, PMM_BITMAP_SZ_BYTES);

    // Mark everything else as unused i.e [4 MB, 4GB-1MB]
    uint32_t ununsed_len = last_page_addr - VMM_PG_SZ_LARGE;
    pmm_unset_range(VMM_PG_SZ_LARGE, ununsed_len);
}