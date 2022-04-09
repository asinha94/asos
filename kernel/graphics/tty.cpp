#include <stdint.h>
#include <graphics/vga.h>
#include <graphics/tty.h>

// TODO: Remove once we have a FS and we load TTF fonts
#include <graphics/psf.h>

static TTYWidget * widget;
uint8_t * pixel_buffer;
extern FrameBuffer * fb;

static void draw_character(char c);
static void tty_clear_from(size_t linum);
static void tty_scroll_up_lines(size_t num_lines);
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
    pxl_a,
    pxl_b,
    pxl_c,
    pxl_d,
    pxl_e,
    pxl_f,
    pxl_g,
    pxl_h,
    pxl_i,
    pxl_j,
    pxl_k,
    pxl_l,
    pxl_m,
    pxl_n,
    pxl_o,
    pxl_p,
    pxl_q,
    pxl_r,
    pxl_s,
    pxl_t,
    pxl_u,
    pxl_v,
    pxl_w,
    pxl_x,
    pxl_y,
    pxl_z,
    pxl_opencurly,
    pxl_pipe,
    pxl_closecurly,
    pxl_tilde,
    pxl_box
};


void tty_draw_character_bmp(Pixel * point, uint8_t * c)
{
    Pixel Black = create_pixel(COLOR_MAX, COLOR_MAX, COLOR_MAX);
    Pixel White = create_pixel(COLOR_MIN, COLOR_MIN, COLOR_MIN);
    
    for (size_t k = 0; k < PXL_HEIGHT; ++k) {
        Pixel * p = point + (k * PXL_WIDTH * widget->cols);
        for (size_t l = 0; l < PXL_WIDTH; ++l) {
            Pixel color = ((c[k] >> (PXL_WIDTH - l - 1)) & 0x1) ? Black : White;
            *(p+l) = color;
        }
    }
}


static void tty_clear_from(size_t linum)
{
    pxl_space(pixel_buffer);
    /* clear all lines from linum onwards */
    
    for (size_t i = linum; i < widget->rows; ++i) {
        Pixel * dst = fb->addr + i * (PXL_HEIGHT * (PXL_WIDTH * widget->cols));
        for (size_t j = 0; j < widget->cols; ++j) {
            tty_draw_character_bmp(dst+(j*PXL_WIDTH), pixel_buffer);
        } 
    }
}


static void tty_scroll_up_num_rows(size_t num_rows)
{
    if (num_rows == 0)
        return;

    if (num_rows >= widget->rows) {
        num_rows = widget->rows - 1;
    }

    // we want to scroll up num_rows. This means everything below #num_rows needs to be copied up
    // so start copying from num_lines till the total_height
    size_t pitch = PXL_WIDTH * widget->cols;
    size_t character_pitch = PXL_HEIGHT * pitch;

    for (size_t i = num_rows; i < widget->rows; ++i) {
        for (size_t j = 0; j < PXL_HEIGHT; ++j) {
            
            Pixel * dst = fb->addr + ((i-num_rows) * character_pitch) + (j * pitch);
            Pixel * src = dst + (num_rows * character_pitch);
            for (size_t k = 0; k < pitch; ++k) {
                dst[k] = src[k];
            }
        }
    }

    // clear off the remaining lines
    tty_clear_from(widget->rows - num_rows);

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
    tty_scroll_up_num_rows(widget->rows - 1);
    widget->curr = fb->addr + (widget->rows - 1) * (PXL_HEIGHT * PXL_WIDTH * widget->cols);
}


static void draw_character(char c)
{
    void (*fp)(uint8_t*) = char_func[c-32];
    fp(pixel_buffer);
    tty_draw_character_bmp(widget->curr, pixel_buffer);
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
        break;
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
    pixel_buffer = (uint8_t *) kmalloc(16);

    // Init TTY Window
    widget = (TTYWidget *) kmalloc(sizeof(TTYWidget));
    widget->curr = fb->addr;
    widget->rows = 32 / PXL_HEIGHT;
    widget->current_row = 0;
    widget->cols = fb->width / PXL_WIDTH;
    widget->current_row = 0;

    /* TODO:
        - add in lowercase chars
        - abstract away pitch vs character calculation because its leading to lots of errors
    */
}


