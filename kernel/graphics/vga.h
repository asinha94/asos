#ifndef ASOS_VGA_H
#define ASOS_VGA_H

#include <stdint.h>
#include <boot/multiboot.h>

#define COLOR_MAX 0xFF
#define COLOR_MIN 0x00

typedef uint32_t Pixel;

typedef struct FrameBuffer {
    Pixel * addr;
    uint16_t width;
    uint16_t height;
    uint32_t pitch;
    uint8_t bpp;
    uint8_t bytespp;
    uint8_t red_mask_size;
    uint8_t red_field_pos;
    uint8_t green_mask_size;
    uint8_t green_field_pos;
    uint8_t blue_mask_size;
    uint8_t blue_field_pos;
} FrameBuffer;


FrameBuffer * fb;
Pixel White;
Pixel Black;

void set_background_color(Pixel color);
Pixel create_pixel(uint8_t r, uint8_t g, uint8_t b);
void init_graphics(multiboot_info_t *);


#endif