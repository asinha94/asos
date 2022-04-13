#ifndef ASOS_VGA_H
#define ASOS_VGA_H

#include <stdint.h>
#include <boot/multiboot.h>

void init_graphics(multiboot_info_t * mbi);

namespace asos {

    using Pixel = uint32_t;
    using PixelSize = uint32_t;

    static constexpr uint8_t ColorMax = 0xFF;
    static constexpr uint8_t ColorMin = 0x00;

    class VGAFrameBuffer {
    public:
        static void initVGAFramebuffer(multiboot_info_t *);
        static VGAFrameBuffer * GetFrameBuffer();
        Pixel CreatePixel(uint8_t, uint8_t, uint8_t) const;
    //private:
        
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
    private:
        VGAFrameBuffer() {}
    };
}



#endif