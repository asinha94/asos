#include <stdint.h>
#include <stddef.h>
#include <mm/pmm.h>

static uint32_t *pmm_memory_map = 0;
static size_t next_free_page = 0;


void pmm_set_page(size_t pg_num)
{
    pmm_memory_map[pg_num / 32] |= (1 << (pg_num % 32));
}

void pmm_unset_page(size_t pg_num)
{
    pmm_memory_map[pg_num / 32] &= ~(1 << (pg_num % 32));
}

void pmm_clear_range(uint32_t addr, uint32_t len)
{
    uint32_t pg_num = addr / PMM_PG_SZ_SMALL;
    uint32_t pages = len / PMM_PG_SZ_SMALL;
    // Clear page if bytes bleed over boundary
    if (len % PMM_PG_SZ_SMALL) {
        ++pages;
    }
    for (size_t i = 0; i < pages; ++i) {
        pmm_unset_page(pg_num + i);
    }
}

void init_pmm()
{
    // TODO: Figure out actual memory size, don't assume 4GiB
    //       Get memory map from multiboot2 maybe?
    uint32_t bitmap_size_bytes = (PMM_RAM_SIZE / PMM_PG_SZ_SMALL);
    uint32_t bitmap_size = bitmap_size_bytes / 32;
    
    /* Place memory map at the end of kernel 4MiB page. */
    uint32_t kern_page_end = KERN_ADDR_START + PMM_PG_SZ_LARGE;
    pmm_memory_map = (uint32_t *)(kern_page_end - bitmap_size);

    /* Clear out all other pages */
    pmm_clear_range(0, KERN_ADDR_START);
    
}