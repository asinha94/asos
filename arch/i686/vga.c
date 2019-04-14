#include <include/arch/i686/vga.h>

#ifndef ASOS_i386_VGA_DRIVER_H
#define ASOS_i386_VGA_DRIVER_H

inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

#endif
