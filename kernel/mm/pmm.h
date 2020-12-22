#include <stdint.h>
#include <mm/vmm.h>

// TODO: Figure out actual memory size, don't assume 4GiB Get memory map from multiboot2 maybe?
// All of this right now is hardcoded and will break as soon as things change.


// we store the Physical Memory usage in a large 1 MiB Bitmap.
// 1 bit corresponds to 1 Small (4KiB) Page. There is room for optimizations
// but lets try and get things working first :)
#define PMM_RAM_SIZE        (4 * 1024 * 1024 * 1024) // 4 GB
#define PMM_BITMAP_ENTRIES  (PMM_RAM_SIZE / VMM_PG_SZ_SMALL)
#define PMM_BITMAP_LEN      (PMM_BITMAP_ENTRIES / 32)
#define PMM_BITMAP_SZ_BYTES (PMM_BITMAP_ENTRIES / 8)
#define PMM_BITMAP_ADDR     (PMM_RAM_SIZE - PMM_BITMAP_SZ_BYTES)

void init_pmm();
