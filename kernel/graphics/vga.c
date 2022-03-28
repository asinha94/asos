#include <stddef.h>
#include <graphics/vga.h>
#include <libk/kprintf.h>
#include <mm/pmm.h>
#include <mm/vmm.h>

static void * fb_addr; 
static uint32_t fb_width;
static uint32_t fb_height;
static uint8_t fb_bpp;
static uint32_t fb_pitch;


void init_graphics(multiboot_info_t * mbi)
{
    if (mbi->flags & MULTIBOOT_INFO_FRAMEBUFFER_INFO) {

        fb_addr = (void *) mbi->framebuffer_addr;
        multiboot_uint8_t fb_type = mbi->framebuffer_type;
        kprintf("Framebuffer: addr=%x, Type=%u\n", fb_addr, fb_type);
        
        //multiboot_uint32_t fb_pitch = mbi->framebuffer_pitch;
        fb_width = mbi->framebuffer_width;
        fb_height = mbi->framebuffer_height;
        fb_bpp = mbi->framebuffer_bpp;
        fb_pitch = mbi->framebuffer_pitch;
        kprintf("VideoMode: %ux%u (BPP: %u bits, Pitch: %u bytes)\n", fb_width, fb_height, fb_bpp, fb_pitch);

        size_t vmem_pages = (fb_height * fb_pitch) / VMM_PG_SZ_SMALL;
        uint32_t base_addr = (uint32_t) fb_addr;
        for (size_t i = 0; i < vmem_pages; ++i) {
             uint32_t base_addr = (uint32_t) fb_addr + (i * VMM_PG_SZ_SMALL);
            vmm_map_page_to_vaddr(
                base_addr,
                base_addr, //  does a framebuffer actually exist in memory?
                PTE_RW_ACCESS | PTE_PRESENT
            );
        }
    }

    uint32_t color = ((1 << mbi->framebuffer_blue_mask_size) - 1) << mbi->framebuffer_blue_field_position;
    for (size_t i = 0; i < fb_height; ++i) {
        for (size_t j = 0; j < fb_width; ++j) {
            uint32_t * pixel = fb_addr + (i * fb_pitch) + (j * 4);
            *pixel = color;
        }
    }

}