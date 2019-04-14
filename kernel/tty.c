#include <stdbool.h>

#include <arch/i686/vga.h>
#include <kernel/tty.h>

const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;

static size_t tty_row;
static size_t tty_column;
static uint8_t tty_color;
static uint16_t* tty_buffer;


size_t strlen(const char* str) {
    size_t len = 0;
    while (*str++)
        len++;
    return len;
}


static void tty_clear_from(uint8_t linum) {
    /* clear all lines from linum onwards */
    for (size_t y = linum; y < VGA_HEIGHT; y++) {
        const size_t line = y * VGA_WIDTH;
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = line + x;
            tty_buffer[index] = vga_entry(' ', tty_color);
        }
    }
    
}


static void tty_setcolor(uint8_t color) {
    tty_color = color;
}


static void tty_scroll_up_lines(uint8_t num_lines) {
    if (num_lines > VGA_HEIGHT)
        num_lines = VGA_HEIGHT;

    // we want to overrite the first num_lines number of rows
    // so start copying from num_lines till the total_height
    for (size_t y = num_lines; y < VGA_HEIGHT; y++) {
        size_t old_line = (y - num_lines) * VGA_WIDTH;
        size_t new_line = y * VGA_WIDTH;
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            size_t old_index = old_line + x;
            size_t new_index = new_line + x;
            tty_buffer[old_index] = tty_buffer[new_index];
        }
    }

    // clear off the remaining lines
    tty_clear_from(VGA_HEIGHT - num_lines);

}

static inline bool is_escape_char(char c) {
    return c == '\n' || c == '\r' || c == '\t';
}

static void handle_escape_char(char c) {
    switch (c) {
    case '\n':
        tty_column = 0;
        tty_row++;
        break;
    case '\r':
        tty_column = 0;
        tty_row++;
        break;
    case '\t':
        tty_writestring("    ");
    default:
        break;
    }
}

static void tty_putchar(char c) {
    if (is_escape_char(c)) {
        handle_escape_char(c);
        return;
    }
    
    /* Set char in position*/
    const size_t index = tty_row * VGA_WIDTH + tty_column;
    tty_buffer[index] = vga_entry(c, tty_color);
    if (++tty_column == VGA_WIDTH) {
        tty_column = 0;
        if (++tty_row == VGA_HEIGHT) {
            --tty_row;
            tty_scroll_up_lines(1);
        }
    }

}


static void tty_writechars(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++ ) {
        tty_putchar(data[i]);
    }

}


void tty_writestring(const char* data) {
    tty_writechars(data, strlen(data));
}


void tty_init(void) {
    tty_row = 0;
    tty_column = 0;
    tty_buffer = (uint16_t*) 0xB8000;
    tty_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    tty_clear_from(0);
}


