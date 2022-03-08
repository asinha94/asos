#include <stdint.h>
#include <display/textmode.h>

const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;

static size_t tty_row;
static size_t tty_column;
static uint8_t tty_color;
static uint16_t* tty_buffer;

static void tty_clear_from(uint8_t linum);
static void tty_scroll_up_lines(uint8_t num_lines);



static void tty_clear_from(uint8_t linum)
{
    /* clear all lines from linum onwards */
    for (size_t y = linum; y < VGA_HEIGHT; y++) {
        const size_t line = y * VGA_WIDTH;
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = line + x;
            tty_buffer[index] = vga_entry(' ', tty_color);
        }
    }
    
}


static void tty_scroll_up_lines(uint8_t num_lines)
{
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

void tty_putchar(unsigned char c)
{
    // caclulate index in case we need it
    const size_t index = tty_row * VGA_WIDTH + tty_column;

    switch (c) {
    case '\0':
        return;
    case '\n':
        tty_column = 0;
        tty_row++;
        break;;
    case '\t':
        tty_puts("    ");
        return;
    default:
        tty_buffer[index] = vga_entry(c, tty_color);
        tty_column++;
        break;
    }

    // put on newline if need be
    if (tty_column == VGA_WIDTH) {
        tty_column = 0;
        tty_row++;
    }

    // strip the first line, print from bottom line
    if (tty_row == VGA_HEIGHT) {
        tty_row--;
        tty_scroll_up_lines(1);
    }
    

}


void tty_puts(const char* data)
{
    const char * s = data;
    // This can't go wrong
    while (*s) tty_putchar(*s++);

}


void init_tty()
{
    tty_row = 0;
    tty_column = 0;
    tty_buffer = (uint16_t*) 0xC00B8000; // 0xB8000 + Kernel Offset
    tty_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    tty_clear_from(0);
}


