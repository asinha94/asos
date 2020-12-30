#include <stdint.h>
#include <stdlib.h>
//#include <stddef.h>
#include <stdio.h>

#define ALLOC_SIZE 1000

typedef struct block_header{
    struct block_header * next_block;
    uint64_t block_size;
} block_header;

static size_t heap_size;
static size_t used_size;
static block_header base; // = {.next_block = &base, .block_size = 0};
static block_header * free_block_ptr;

void * kmalloc(size_t size);
void kfree(void * addr);
void init_kmalloc();
void * __increase_heap_size_for_block(size_t block_size);

void init_kmalloc()
{
    used_size = 0;
    heap_size = 0;
    free_block_ptr = &base;
    base.next_block = &base;
    base.block_size = 0;
}

void * kmalloc(size_t size)
{    
    // block_size includes header as well
    size_t block_size = size + sizeof(block_header);

    // Iterate through the freelist till we get a suitable size block
    // O(N) algorithm, but this is only temporary
    block_header * prev = free_block_ptr;
    block_header * p = prev->next_block;
    while (1) {
        // looped back to the head, return
        if (p == free_block_ptr) {
            // allocate more memory if possible
            p = __increase_heap_size_for_block(block_size);
            if (p == NULL)
                return p;
            break;
        }

        // block large enough found
        if (p->block_size >= block_size) {
            // Check if we can just return the block as-is
            size_t thresh = 2 * sizeof(block_header);
            if (p->block_size - block_size < thresh) {
                prev->next_block = p->next_block;
                break;
            }

            // Found a block that slightly larger, split apart and use
            if (p->block_size > block_size) {
                // split the blocks in 2
                p->block_size -= block_size;
                p = (block_header *)((char *)p + p->block_size);
                p->block_size = block_size;
                break;
            }
        }

        // incremement
        prev = p;
        p = p->next_block;
    }

    // Point free_block_ptr at last block previous to one removed
    // doesn't really work if we increased heap size
    free_block_ptr = prev;
    used_size += p->block_size;

    void * block_addr = (char *) p + sizeof(block_header);
    return block_addr;
}

void kfree(void * addr)
{
    // addr is address memory, not whole block.
    // -1 to move back 1*sizeof(block_header) to start of header
    block_header * blk_addr = (block_header *) addr - 1;
    used_size -= blk_addr->block_size;

    // We maintain the freelist by storing blocks in ascending order
    // in terms of address, so that adjacent blocks can be merged
    // the goals is to insert between prev and p so that prev < addr < p
    block_header * prev = free_block_ptr;
    block_header * p = prev->next_block;
    while (1) {
        // list is empty or we looped around the whole list
        if (p == free_block_ptr)
            break;

        // found the right position?
        if (prev < blk_addr && blk_addr < p)
            break;

        // increment
        prev = p;
        p = p->next_block;
    }

    // Can we merge with the block after?
    block_header * mergeable_blk_addr = (block_header *)((char *)blk_addr + blk_addr->block_size);
    if (mergeable_blk_addr == p) {
        blk_addr->next_block = p->next_block;
        blk_addr->block_size += p->block_size;
    } else {
        blk_addr->next_block = p;
    }

    // can we merge with the prev block?
    mergeable_blk_addr = (block_header *)((char *)prev + prev->block_size);
    if (mergeable_blk_addr == blk_addr) {
        prev->next_block = blk_addr->next_block;
        prev->block_size += blk_addr->block_size;
    } else {
        prev->next_block = blk_addr;
    }

    // Set pointer back 1 before where we just inserted
    free_block_ptr = prev;

}

void * __increase_heap_size_for_block(size_t block_size)
{
    // Get large contiguous chunk of mem
    // which is how v1 of kmalloc will work
    block_header * p = malloc(ALLOC_SIZE);
    heap_size += ALLOC_SIZE;

    // Split into 2 chunks, the chunk + remaining fragment
    // we use kfree on the unused part to insert into the freelist
    // TODO: use same heauristic here to determine if we fragment
    p->block_size = block_size;
    block_header * fragmented_blk = (block_header *)((char *) p + p->block_size);
    fragmented_blk->block_size = ALLOC_SIZE - block_size;

    // Use kfree to insert new chunks into free list
    used_size += fragmented_blk->block_size;
    void * fragmented_mem = (char *) fragmented_blk + sizeof(block_header);
    kfree(fragmented_mem);

    return p;
}


void print_free_list()
{
    printf("Heap Size: %lu bytes, Size Used: %lu bytes\n", heap_size, used_size);
    block_header * p = base.next_block;
    for (;p != &base; p = p->next_block)
        printf("addr: %p | block_size: %lu\n", p, p->block_size);
    printf("----------------------------------------------------------------\n");
        
}


int main()
{
    init_kmalloc();
    print_free_list();

    void * a = kmalloc(10);
    print_free_list();

    void * b = kmalloc(900);
    print_free_list();

    void * c = kmalloc(200);
    print_free_list();

    // return some memory
    printf("Using Addr(a): %p\n", a);
    kfree(a);
    print_free_list();
    kfree(b);
    print_free_list();
    kfree(c);
    print_free_list();

}