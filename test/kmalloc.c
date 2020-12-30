#include <stdint.h>
#include <stdlib.h>
//#include <stddef.h>
#include <stdio.h>

#define VMM_PG_SZ_SMALL 4096

typedef struct block_header{
    struct block_header * next_block;
    uint64_t block_size;
} block_header;



static char * __kernel_heap_start;
static char * __kernel_heap_end;
static size_t __heap_size;
static size_t __used_size;
static block_header __base;
static block_header * __last_used_block;

static void * __increase_heap_size_for_block(size_t block_size);
static void * __split_block(block_header * block, size_t block_size);


void init_kmalloc()
{
    __used_size = 0;
    __heap_size = 0;
    __last_used_block = &__base;
    __base.next_block = &__base;
    __base.block_size = 0;
    __kernel_heap_start = 0;
    __kernel_heap_end = __kernel_heap_start;
}


void * kmalloc(size_t size)
{    
    // block_size includes header as well
    size_t block_size = size + sizeof(block_header);

    // Iterate through the freelist till we get a suitable size block
    // O(N) algorithm, but this is only temporary
    block_header * prev = __last_used_block;
    block_header * p = prev->next_block;
    while (1) {
        // looped back to the head, return
        if (p == __last_used_block) {
            // allocate more memory if possible
            p = __increase_heap_size_for_block(block_size);
            if (p == NULL)
                return p;
            break;
        }

        // block large enough found
        if (p->block_size >= block_size) {
            // Split if necessary'
            block_header * orig_block = p;
            p = __split_block(p, block_size);
            if (p == orig_block) {
                // No split i.e we return the block as is
                // so we need to remove it from the free_list
                prev->next_block = p->next_block;
            }
            // noop if not split, otherwise
            break;
        }

        // incremement
        prev = p;
        p = p->next_block;
    }

    // Point __last_used_block at last block previous to one removed
    // doesn't really work if we increased heap size
    __last_used_block = prev;
    __used_size += p->block_size;

    void * block_addr = (char *) p + sizeof(block_header);
    return block_addr;
}


void kfree(void * addr)
{
    // addr is address memory, not whole block.
    // -1 to move back 1*sizeof(block_header) to start of header
    block_header * blk_addr = (block_header *) addr - 1;
    __used_size -= blk_addr->block_size;

    // We maintain the freelist by storing blocks in ascending order
    // in terms of address, so that adjacent blocks can be merged
    // the goals is to insert between prev and p so that prev < addr < p
    block_header * prev = __last_used_block;
    block_header * p = prev->next_block;
    while (1) {
        // list is empty or we looped around the whole list
        if (p == __last_used_block)
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
    __last_used_block = prev;

}


/*
    We return the block that meets the size requirement,
    whether or not we split i.e if block is too large, split
    and return the split block ptr otherwise return unchanged block.
    Caller will need to update references and bookkeeping.
    block->block_size has to be >= block_size
*/
void * __split_block(block_header * block, size_t block_size)
{
    // TODO: Maybe use an actual size instead of an estimate?
    block_header * split_ptr = block;
    size_t thresh = 2 * sizeof(block_header);
    // Found a block that slightly larger than required
    // split and return the tail end of the split
    if (block->block_size - block_size >= thresh) {
        block->block_size -= block_size;
        split_ptr = (block_header *)((char *)block + block->block_size);
        split_ptr->block_size = block_size;
    }
    return split_ptr;
}


void * __increase_heap_size_for_block(size_t block_size)
{
    // Increase kernel heap 1 page at a time, probably extrememly inefficient
    // TODO: I guess change this in future if we're allocating lots of large
    // objects. Will also need to update pmm to give us a range of pages instead
    block_header * new_block = malloc(VMM_PG_SZ_SMALL);
    __kernel_heap_end += VMM_PG_SZ_SMALL;
    __heap_size += VMM_PG_SZ_SMALL;

    // Split into 2 chunks, the chunk + remaining fragment
    new_block->block_size = VMM_PG_SZ_SMALL;
    block_header * p = __split_block(new_block, block_size);
    if (p != new_block) {
        // split occurred, need to 'free' the other block
        // kfree assumes memory was returned so it decrements
        // from used_size, so we need to prematurely add the size
        __used_size += new_block->block_size;
        // new_block+1 incremements pointer addr by sizeof(block_header)
        // which makes it point to the actual memory. kfree will decrement
        // again to get to the header
        kfree(new_block + 1);
    }

    return p;
}


void print_free_list()
{
    printf("Heap Size: %lu bytes, Size Used: %lu bytes\n", __heap_size, __used_size);
    block_header * p = __base.next_block;
    for (;p != &__base; p = p->next_block)
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