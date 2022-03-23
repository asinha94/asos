#ifndef ASOS_VMM_H
#define ASOS_VMM_H

#define VMM_KERN_ADDR_START      0xC0000000
#define VMM_KERN_ADDR_END        0xFFFFFFFF
#define VMM_PGDIR_ADDR           0xFFFFF000 // 4GB-4KB
#define VMM_HEAP_START           0xFFC00000 // 4GB-4MB
#define VMM_PG_SZ_SMALL          (4 * 1024)
#define VMM_PG_SZ_LARGE          (4 * 1024 * 1024)
#define VMM_PDIR_LEN             1024
#define VMM_PTABLE_LEN           1024

// Masks
#define VMM_4KB_ALIGN_MASK      0xFFFFF000 // Top 20 bits
#define VMM_4MB_ALIGN_MASK      0xFFC00000 // Top 10 Bits
#define VMM_ACCESS_MASK         0x00000FFF

enum VMM_PDE_FLAG
{
    PDE_PRESENT       = 0x001,
    PDE_RW_ACCESS     = 0x002,
    PDE_USER_ACCESS   = 0x004,
    PDE_WRITE_THRU    = 0x008,
    PDE_CACHE_DISABLE = 0x010,
    PDE_ACCESSED      = 0x020,
    PDE_4MB_PAGE_SZ   = 0x080
};

enum VMM_PTE_FLAG
{
    PTE_PRESENT       = 0x001,
    PTE_RW_ACCESS     = 0x002,
    PTE_USER_ACCESS   = 0x004,
    PTE_WRITE_THRU    = 0x008,
    PTE_CACHE_DISABLE = 0x010,
    PTE_ACCESSED      = 0x020,
    PTE_DIRTY         = 0x040,
    PTE_GLOBAL_ENABLE = 0x100
};

typedef struct
{
    uint32_t entries[VMM_PDIR_LEN];
} page_directory;

typedef struct
{
    uint32_t entries[VMM_PTABLE_LEN];
} page_table;


void init_vmm();
void memset_page(uint32_t table);
void insert_kernel_pde(uint32_t vaddr, uint32_t paddr, uint32_t flags);
uint32_t get_virtual_page();
void allocate_page_at_vaddr(uint32_t vaddr);

#endif