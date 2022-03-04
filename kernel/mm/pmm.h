#ifndef ASOS_PMM_H
#define ASOS_PMM_H

#include <stdint.h>
#include <boot/multiboot2.h>
#include <mm/vmm.h>

// TODO: Figure out actual memory size, don't assume 4GB Get memory map from multiboot2 maybe?
// All of this right now is hardcoded and will break as soon as things change.

// we store the Physical Memory usage in a 128 KB Bitmap (4GB/4KB == 0x00100000 bits)
// We always cover the full 4GB range even when actual memory might be much less
// This greatly simplifies the bootstrapping process, but might be removed in future
#define PMM_BITMAP_VALUES     0x00100000
#define PMM_BITMAP_LEN        (PMM_BITMAP_VALUES / 32)
#define PMM_PAGING_ADDR_START (VMM_PG_SZ_LARGE)
#define PMM_PAGING_ADDR_END   (PMM_PAGING_ADDR_START + VMM_PG_SZ_LARGE - 1)


void init_pmm(struct multiboot_tag_basic_meminfo * meminfo, struct multiboot_tag_mmap * mmap);
uint32_t pmm_get_page_addr();
void * pmm_page_alloc();

// Convert physical address to virtual for paging structures
static inline void * PG_P2V(void * paddr)
{
    uint32_t offset = (uint32_t) paddr - VMM_PG_SZ_LARGE;
    return (void *) (VMM_PAGING_ADDR_START + offset);
}

// convert virtual address to physical for paging structures
static inline void * PG_V2P(void * vaddr)
{
    uint32_t offset = (uint32_t) vaddr - VMM_PAGING_ADDR_START;
    return (void *) (VMM_PG_SZ_LARGE + offset);
}

#endif