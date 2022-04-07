#include <stddef.h>
#include <graphics/psf.h>
#include <graphics/vga.h>
#include <graphics/tty.h>
#include <libk/kmalloc.h>
#include <libk/kprintf.h>
#include <mm/pmm.h>
#include <mm/vmm.h>


FrameBuffer * fb;


void set_background_color(Pixel color)
{   
    Pixel * p = fb->addr;
    for (size_t i = 0; i < fb->height; ++i)
        for (size_t j = 0; j < fb->width; ++j)
            *p++ = color;
}

Pixel create_pixel(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t red = r << fb->red_field_pos;
    uint32_t green = g << fb->green_field_pos;
    uint32_t blue = b << fb->blue_field_pos;
    return red | green | blue;
}

void init_graphics(multiboot_info_t * mbi)
{
    // Allocate memory for framebuffer
    fb = (FrameBuffer *) kmalloc(sizeof(FrameBuffer));

    if (mbi->flags & MULTIBOOT_INFO_FRAMEBUFFER_INFO) {
        fb->addr = (Pixel *) mbi->framebuffer_addr;
        fb->width = mbi->framebuffer_width;
        fb->height = mbi->framebuffer_height;
        fb->pitch = mbi->framebuffer_pitch;
        fb->bpp = mbi->framebuffer_bpp;
        fb->bytespp = fb->bpp / 8;

        // Log the important stuff
        multiboot_uint8_t fb_type = mbi->framebuffer_type;
        kprintf("Framebuffer: addr=%x, Type=%u\n", fb->addr, fb_type);
        kprintf("VideoMode: %ux%u (BPP: %u bits, Pitch: %u bytes)\n", fb->width, fb->height, fb->bpp, fb->pitch);

        fb->red_mask_size = mbi->framebuffer_red_mask_size;
        fb->red_field_pos = mbi->framebuffer_red_field_position;
        fb->green_mask_size = mbi->framebuffer_green_mask_size;
        fb->green_field_pos = mbi->framebuffer_green_field_position;
        fb->blue_mask_size = mbi->framebuffer_blue_mask_size;
        fb->blue_field_pos = mbi->framebuffer_blue_field_position;

        // Set pmm pages for vmem, even though range is too high for our qemu emultation.
        // we use 128MB for qemu, and the address is usually in the 3GB range
        size_t vmem_pages = (fb->height * fb->pitch) / VMM_PG_SZ_SMALL;
        uint32_t base_addr = (uint32_t) fb->addr;
        pmm_set_range(base_addr, vmem_pages);

        for (size_t i = 0; i < vmem_pages; ++i) {
            vmm_map_page_to_vaddr(
                base_addr,
                base_addr, //  does a framebuffer actually exist in memory?
                PTE_RW_ACCESS | PTE_PRESENT
            );
            base_addr += VMM_PG_SZ_SMALL;
        }
    }

    //set_background_color(create_pixel(COLOR_MIN, COLOR_MIN, COLOR_MAX));
    init_tty();
}