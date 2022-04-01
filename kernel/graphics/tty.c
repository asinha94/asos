#include <stdint.h>
#include <graphics/vga.h>
#include <graphics/tty.h>

// TODO: Remove once we have a FS and we load TTF fonts
#include <graphics/psf.h>

static size_t tty_row;
static size_t tty_column;

Pixel * base_pixel;
Pixel * pixel_buffer;

void (*char_func[])(uint8_t *) = {
    pxl_space,
    pxl_exclaim,
    pxl_dquote,
    pxl_space, // hash?
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


static void draw_character(char c)
{
    void (*fp)(uint8_t*) = char_func[c-32];
    fp(pixel_buffer);
    draw_character_bmp(&base_pixel, pixel_buffer);
}

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

void tty_putchar(unsigned char c)
{
    // caclulate index in case we need it
    const size_t index = tty_row * fb->width + tty_column;

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
        draw_character(c);
        tty_column++;
        break;
    }

    // put on newline if need be
    if (tty_column == fb->width) {
        tty_column = 0;
        tty_row++;
    }

    // strip the first line, print from bottom line
    if (tty_row == fb->height) {
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
    tty_column = tty_row = 0;
    base_pixel = fb->addr;
    pixel_buffer = kmalloc(16);

    /* TODO:
        - semicolon too small
        - fslash random pixel
        - hash missing
        - add in lowercase chars
        - fix scrolling and line handling
    */
}


