#ifndef ASOS_KMALLOC_H
#define ASOS_KMALLOC_H

#include <stddef.h>
#include <stdint.h>
#include <mm/vmm.h>
#include <mm/pmm.h>


typedef struct block_header {
    struct block_header * next_block;
    uint32_t block_size;
} block_header;


void init_kmalloc(uint32_t, size_t);
void * kmalloc(size_t size);
void * kcalloc(size_t num, size_t size);
void * krealloc(size_t size);
void kfree(void * addr);


#endif