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


#endif
