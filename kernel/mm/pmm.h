#ifndef ASOS_PMM_H
#define ASOS_PMM_H

#include <stdint.h>
#include <mm/vmm.h>

// TODO: Figure out actual memory size, don't assume 4GB Get memory map from multiboot2 maybe?
// All of this right now is hardcoded and will break as soon as things change.

// we store the Physical Memory usage in a large 1 MB Bitmap.
// 1 bit corresponds to 1 Small (4KB) Page. There is room for optimizations
// but lets try and get things working first :)
#define PMM_BITMAP_ENTRIES  0x00100000
#define PMM_BITMAP_LEN      (PMM_BITMAP_ENTRIES / 32)
#define PMM_BITMAP_SZ_BYTES (PMM_BITMAP_ENTRIES / 8)
#define PMM_BITMAP_ADDR     (VMM_KERN_ADDR_END - PMM_BITMAP_SZ_BYTES + 1)

void init_pmm();


#endif