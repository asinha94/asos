#ifndef ASOS_PMM_H
#define ASOS_PMM_H

#include <stdint.h>
#include <mm/vmm.h>

// TODO: Figure out actual memory size, don't assume 4GB Get memory map from multiboot2 maybe?
// All of this right now is hardcoded and will break as soon as things change.

// we store the Physical Memory usage in a 128 KB Bitmap (4GB/4KB == 0x00100000 bits)
// There is room for optimizations but lets try and get things working first :)
#define PMM_BITMAP_VALUES     0x00100000
#define PMM_BITMAP_LEN        (PMM_BITMAP_VALUES / 32)
#define PMM_PAGING_ADDR_START (VMM_PG_SZ_LARGE)
#define PMM_PAGING_ADDR_END   (PMM_PAGING_ADDR_START + VMM_PG_SZ_LARGE - 1)


void init_pmm();
void pmm_unset_range(uint32_t addr, uint32_t len);
void pmm_set_range(uint32_t addr, uint32_t len); // TODO: Make a more user-friendly version of this
uint32_t pmm_get_page_addr();
uint32_t pmm_page_alloc();

#endif