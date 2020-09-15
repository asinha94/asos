#include <stdint.h>

#define PMM_RAM_SIZE      0xFFFFFFFF
#define KERN_ADDR_START   0xC0000000
#define PMM_PG_SZ_SMALL   4096
#define PMM_PG_SZ_LARGE   4*1024*1024


void init_pmm();
