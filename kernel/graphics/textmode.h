#ifndef ASOS_TEXTMODE_H
#define ASOS_TEXTMODE_H

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

enum ega_color {
    EGA_COLOUR_BLACK         = 0,
    EGA_COLOUR_BLUE          = 1,
    EGA_COLOUR_GREEN         = 2,
    EGA_COLOUR_CYAN          = 3,
    EGA_COLOUR_RED           = 4,
    EGA_COLOUR_MAGENTA       = 5,
    EGA_COLOUR_BROWN         = 6,
    EGA_COLOUR_LIGHT_GREY    = 7,
    EGA_COLOUR_DARK_GREY     = 8,
    EGA_COLOUR_LIGHT_BLUE    = 9,
    EGA_COLOUR_LIGHT_GREEN   = 10,
    EGA_COLOUR_LIGHT_CYAN    = 11,
    EGA_COLOUR_LIGHT_RED     = 12,
    EGA_COLOUR_LIGHT_MAGENTA = 13,
    EGA_COLOUR_LIGHT_BROWN   = 14,
    EGA_COLOUR_WHITE         = 15
};

static inline uint8_t ega_entry_colour(enum ega_color fg, enum ega_color bg)
{
    return fg | bg << 4;
}

static inline uint16_t ega_entry(unsigned char uc, uint8_t color)
{
    return (((uint16_t) color) << 8) | ((uint16_t) uc);
}

void tty_puts(const char* data);
void tty_putchar(unsigned char c);

void init_tty();

#endif
