#include <stdint.h>
#include <graphics/vga.h>
#include <graphics/tty.h>

// TODO: Remove once we have a FS and we load TTF fonts
#include <graphics/psf.h>

static TTYWidget * widget;
Pixel * pixel_buffer;

static void draw_character(char c);
static void tty_clear_from(uint8_t linum);
static void tty_scroll_up_lines(uint8_t num_lines);
static void increment_cursor();


void (*char_func[])(uint8_t *) = {
    pxl_space,
    pxl_exclaim,
    pxl_dquote,
    pxl_hash,
    pxl_dollar,
    pxl_percent,
    pxl_ampersand,
    pxl_squote,
    pxl_openparen,
    pxl_closeparen,
    pxl_asterisk,
    pxl_plus,
    pxl_comma,
    pxl_minus,
    pxl_dot,
    pxl_fslash,
    pxl_0,
    pxl_1,
    pxl_2,
    pxl_3,
    pxl_4,
    pxl_5,
    pxl_6,
    pxl_7,
    pxl_8,
    pxl_9,
    pxl_colon,
    pxl_semicolon,
    pxl_lt,
    pxl_eq,
    pxl_gt,
    pxl_qmark,
    pxl_at,
    pxl_A,
    pxl_B,
    pxl_C,
    pxl_D,
    pxl_E,
    pxl_F,
    pxl_G,
    pxl_H,
    pxl_I,
    pxl_J,
    pxl_K,
    pxl_L,
    pxl_M,
    pxl_N,
    pxl_O,
    pxl_P,
    pxl_Q,
    pxl_R,
    pxl_S,
    pxl_T,
    pxl_U,
    pxl_V,
    pxl_W,
    pxl_X,
    pxl_Y,
    pxl_Z,
    pxl_openbrkt,
    pxl_bslash,
    pxl_closebrkt,
    pxl_caret,
    pxl_underscore,
    pxl_backtick,
    pxl_A,
    pxl_B,
    pxl_C,
    pxl_D,
    pxl_E,
    pxl_F,
    pxl_G,
    pxl_H,
    pxl_I,
    pxl_J,
    pxl_K,
    pxl_L,
    pxl_M,
    pxl_N,
    pxl_O,
    pxl_P,
    pxl_Q,
    pxl_R,
    pxl_S,
    pxl_T,
    pxl_U,
    pxl_V,
    pxl_W,
    pxl_X,
    pxl_Y,
    pxl_Z,
    pxl_opencurly,
    pxl_pipe,
    pxl_closecurly,
    pxl_tilde,
    pxl_box
};


static void tty_clear_from(uint8_t linum)
{
    /* clear all lines from linum onwards */
    for (size_t y = linum; y < fb->height; y++) {
        const size_t line = y * fb->width;
        for (size_t x = 0; x < fb->width; x++) {
            const size_t index = line + x;
            draw_character(' ');
        }
    }
}


static void tty_scroll_up_lines(uint8_t num_lines)
{
    if (num_lines > fb->height)
        num_lines = fb->height;

    // we want to overrite the first num_lines number of rows
    // so start copying from num_lines till the total_height
    for (size_t y = num_lines; y < fb->height; y++) {
        size_t old_line = (y - num_lines) * fb->width;
        size_t new_line = y * fb->width;
        for (size_t x = 0; x < fb->width; x++) {
            size_t old_index = old_line + x;
            size_t new_index = new_line + x;
            //tty_buffer[old_index] = tty_buffer[new_index];
        }
    }

    // clear off the remaining lines
    tty_clear_from(fb->height - num_lines);

}


static void increment_cursor()
{
    
    // Are we on the same row?
    uint16_t col = widget->current_col + 1;
    if (col != widget->cols) {
        widget->current_col = col;
        widget->curr += PXL_WIDTH;
        return;
    }

    widget->current_col = 0;
    uint16_t row = widget->current_row + 1;

    // Are we above the bottom row?
    if (row != widget->rows) {
        widget->current_row = row;
        widget->curr += PXL_WIDTH + (PXL_HEIGHT - 1) * (PXL_WIDTH * widget->cols);
        return;
    }

    // We need to scroll up
}


static void draw_character(char c)
{
    void (*fp)(uint8_t*) = char_func[c-32];
    fp(pixel_buffer);
    draw_character_bmp(widget->curr, pixel_buffer);
    increment_cursor();
}



void tty_putchar(unsigned char c)
{
    switch (c) {
    case '\0':
        return;
    case '\n':
        widget->current_col = widget->cols - 1;
        increment_cursor();
        break;;
    case '\t':
        tty_puts("    ");
        return;
    default:
        draw_character(c);
        break;
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
    pixel_buffer = kmalloc(16);

    // Init TTY Window
    widget = kmalloc(sizeof(TTYWidget));
    widget->curr = fb->addr;
    widget->rows = fb->height / PXL_HEIGHT;
    widget->current_row = 0;
    widget->cols = fb->width / PXL_WIDTH;
    widget->current_row = 0;

    /* TODO:
        - add in lowercase chars
        - fix scrolling on end of buffer
    */
}


