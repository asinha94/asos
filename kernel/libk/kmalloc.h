#ifndef ASOS_KMALLOC_H
#define ASOS_KMALLOC_H

#include <stddef.h>
#include <stdint.h>
#include <mm/vmm.h>
#include <mm/pmm.h>

void * kmalloc(size_t size);
void * kcalloc(size_t num, size_t size);
void * krealloc(size_t size);
void free(void * ptr);



#endif