#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "You are not using a cross-compiler"
#endif

#if !defined(__i386__)
#error "You need the i386-elf compiler"
#endif

enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) {
    size_t len = 0;
    while (*str++)
        len++;
    return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void clear_from(uint8_t linnum) {
    if (linnum >= VGA_HEIGHT) return;
    /* clear all lines from linnum onwards */
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);    
    for (size_t y = linnum; y < VGA_HEIGHT; y++) {
        const size_t line = y * VGA_WIDTH;
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = line + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }

}

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_buffer = (uint16_t*) 0xB8000;
    clear_from(terminal_row);
    
}


void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}



void scroll_up_lines(uint8_t num_lines) {
    if (num_lines > VGA_HEIGHT)
        num_lines = VGA_HEIGHT;

    // we want to overrite the first num_lines number of rows
    // so start copying from num_lines till the total_height
    for (uint8_t y = 0; y < num_lines; y++) {
        uint8_t old_offset = y * VGA_WIDTH;
        uint8_t offset = num_lines == VGA_HEIGHT ? num_lines - 1 : num_lines;
        uint8_t new_offset = old_offset + (num_lines == offset * VGA_WIDTH);
        for (uint8_t x = 0; x < VGA_WIDTH; x++) {
            uint8_t old_index = old_offset + x;
            uint8_t new_index = new_offset + x;
            terminal_buffer[old_index] = terminal_buffer[new_index];
        }
            
        // clear off the remaining lines
        clear_from(VGA_HEIGHT - num_lines);

    }
    
}

void terminal_putchar(char c) {

    if (c == '\n') {
        terminal_column = 0;
        terminal_row++;
        return;
    }
    /* Set char in position*/
    const size_t index = terminal_row * VGA_WIDTH + terminal_column;
    terminal_buffer[index] = vga_entry(c, terminal_color);
    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            --terminal_row;
            scroll_up_lines(1);
        }
    }
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++ ) {
        terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}

void kernel_main(void) {
    terminal_initialize();

    terminal_writestring("Hello World\n\nMr. Sinha");
}
