#include <stddef.h>
#include <graphics/vga.h>
#include <libk/kprintf.h>
#include <mm/vmm.h>

static void * fb_addr; 

void init_graphics(multiboot_info_t * mbi)
{
    if (mbi->flags & MULTIBOOT_INFO_FRAMEBUFFER_INFO) {

        fb_addr = (void *) mbi->framebuffer_addr;
        multiboot_uint8_t fb_type = mbi->framebuffer_type;
        kprintf("Framebuffer: addr=%x, Type=%u\n", fb_addr, fb_type);
        
        //multiboot_uint32_t fb_pitch = mbi->framebuffer_pitch;
        multiboot_uint32_t width = mbi->framebuffer_width;
        multiboot_uint32_t height = mbi->framebuffer_height;
        multiboot_uint8_t bpp = mbi->framebuffer_bpp;
        multiboot_uint32_t pitch = mbi->framebuffer_pitch;
        kprintf("VideoMode: %ux%u (BPP: %u bits, Pitch: %u bytes)\n", width, height, bpp, pitch);

        uint32_t vmem_pages = (height * pitch) / VMM_PG_SZ_SMALL;
        for (size_t i = 0; i < vmem_pages; ++i) {
            continue;
        }
    }
}