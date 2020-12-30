#include <stdint.h>
#include <libk/kmalloc.h>
#include <mm/vmm.h>
#include <mm/pmm.h>

static uint32_t __kernel_heap_start;
static uint32_t __kernel_heap_end;
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
    __kernel_heap_start = 0xC8000000;
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

        // large enough block found
        if (p->block_size >= block_size) {
            // Split if necessary, p points to new block if split
            block_header * orig_block = p;
            p = __split_block(p, block_size);
            // no split, remove whole block from free_list
            if (p == orig_block)
                prev->next_block = p->next_block;
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

    // could also return p + 1 due to pointer arithmetic
    void * block_addr = (char *) p + sizeof(block_header);
    return block_addr;
}


void kfree(void * addr)
{
    // addr is address memory, not block (header).
    // -1 to move back by 1*sizeof(block_header) to start of header
    block_header * blk_addr = (block_header *) addr - 1;
    __used_size -= blk_addr->block_size;

    // We store block in freelist by address in ascending order
    // so adjacent blocks can be merged easily.
    // The goals is to insert between prev and p so that prev < addr < p
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
    whether or not we split. If block is much larger, split
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
    uint32_t phys_page_addr = (uint32_t) pmm_get_page();
    if (!phys_page_addr)
        return (void *) phys_page_addr;

    // Map new page for kernel heap at __kernel_heap_end
    uint32_t flags = PTE_PRESENT | PTE_RW_ACCESS;
    insert_kernel_pde_into_dir(__kernel_heap_end, phys_page_addr, flags);

    block_header * new_block = (block_header *)__kernel_heap_end;
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
