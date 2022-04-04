#ifndef ASOS_TEXTMODE_H
#define ASOS_TEXTMODE_H

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include <graphics/vga.h>


typedef struct TTYWidget {
    Pixel *  curr;
    uint16_t rows;
    uint16_t cols;
    uint16_t current_row;
    uint16_t current_col;
} TTYWidget;

void init_tty();
void tty_putchar(unsigned char c);
void tty_puts(const char* data);
void tty_draw_character_bmp(Pixel * point, uint8_t * c);

#endif
