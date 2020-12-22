#ifndef ASOS_VMM_H
#define ASOS_VMM_H

#define VMM_PG_ENTRIES_PER_TABLE 1024
#define VMM_KERN_ADDR_START      0xC0000000
#define VMM_KERN_ADDR_END        0xFFFFFFFF
#define VMM_PG_SZ_SMALL          4096
#define VMM_PG_SZ_LARGE          (4 * 1024 * 1024)
#define VMM_4KB_ALIGN_MASK      0xFFFFF000


enum VMM_PDE_FLAG
{
    PDE_4M_PG_SZ      = 0x001,
    PDE_RW_ACCESS     = 0x002,
    PDE_USER_ACCESS   = 0x004,
    PDE_WRITE_THRU    = 0x008,
    PDE_CACHE_DISABLE = 0x010,
    PDE_ACCESSED      = 0x020,
    PDE_4M_PAGE_SZ    = 0x080
};

void init_vmm();

#endif