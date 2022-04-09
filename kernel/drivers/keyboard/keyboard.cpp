#include <cpu/hal.h>
#include <cpu/interrupts/pic.h>
#include <cpu/interrupts/idt.h>
#include <drivers/keyboard/keyboard.h>
#include <libk/ascii.h>
#include <libk/kprintf.h>
#include <libk/kmalloc.h>
#include <graphics/tty.h>

/*
    Implementation derived from these references
    - https://wiki.osdev.org/PS2_Keyboard
    - https://www.win.tue.nl/~aeb/linux/kbd/scancodes.html
    - http://www.brokenthorn.com/Resources/OSDev19.html
*/


static uint8_t current_modifiers;

// TODO: Remove once done with temp shell
int __len = 0;
int __newline = 0;
//char __kbd_buffer[80];


kbd_event * scancode_set1;
    

static void init_kdb_struct(uint8_t idx, uint8_t data, uint8_t data_mod, uint8_t modifier_mask)
{
    scancode_set1[idx].data = data;
    scancode_set1[idx].data_mod = data_mod;
    scancode_set1[idx].modifier_mask = modifier_mask;
}

void keyboard_init()
{
    kprintf("Initializing Keyboard\n");
    scancode_set1 = (kbd_event *) kmalloc(KBD_SCAN_CODES * sizeof(kbd_event));
    // TODO: 
    // disable all LEDs?
    // set type rate?
    // character device? need vfs first

    init_kdb_struct(0x00, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_INPUT_NONE); // NULL
    init_kdb_struct(0x01, ASCII_ESCAPE, ASCII_ESCAPE, KBD_MASK_NONE ); // ESC - Replace with ctrl msg
    init_kdb_struct(0x02, ASCII_ONE, ASCII_EXCLAMATION_MARK, KBD_MASK_SHIFT );
    init_kdb_struct(0x03, ASCII_TWO, ASCII_AT_SIGN, KBD_MASK_SHIFT );
    init_kdb_struct(0x04, ASCII_THREE, ASCII_NUMBER_SIGN, KBD_MASK_SHIFT );
    init_kdb_struct(0x05, ASCII_FOUR, ASCII_DOLLAR_SIGN, KBD_MASK_SHIFT );
    init_kdb_struct(0x06, ASCII_FIVE, ASCII_PERCENT, KBD_MASK_SHIFT );
    init_kdb_struct(0x07, ASCII_SIX, ASCII_CARET, KBD_MASK_SHIFT );
    init_kdb_struct(0x08, ASCII_SEVEN, ASCII_AMPERSAND, KBD_MASK_SHIFT );
    init_kdb_struct(0x09, ASCII_EIGHT, ASCII_ASTERISK, KBD_MASK_SHIFT );
    init_kdb_struct(0x0A, ASCII_NINE, ASCII_LEFT_PAREN, KBD_MASK_SHIFT );
    init_kdb_struct(0x0B, ASCII_ZERO, ASCII_RIGHT_PAREN, KBD_MASK_SHIFT );
    init_kdb_struct(0x0C, ASCII_MINUS, ASCII_UNDERSCORE, KBD_MASK_SHIFT );
    init_kdb_struct(0x0D, ASCII_EQUAL, ASCII_PLUS, KBD_MASK_SHIFT );
    init_kdb_struct(0x0E, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_NONE ); // Backspace - Replace with ctrl msg?
    init_kdb_struct(0x0F, ASCII_H_TAB, ASCII_H_TAB, KBD_MASK_NONE );
    init_kdb_struct(0x10, ASCII_LOWER_Q, ASCII_UPPER_Q, KBD_MASK_SHIFT );
    init_kdb_struct(0x11, ASCII_LOWER_W, ASCII_UPPER_W, KBD_MASK_SHIFT );
    init_kdb_struct(0x12, ASCII_LOWER_E, ASCII_UPPER_E, KBD_MASK_SHIFT );
    init_kdb_struct(0x13, ASCII_LOWER_R, ASCII_UPPER_R, KBD_MASK_SHIFT );
    init_kdb_struct(0x14, ASCII_LOWER_T, ASCII_UPPER_T, KBD_MASK_SHIFT );
    init_kdb_struct(0x15, ASCII_LOWER_Y, ASCII_UPPER_Y, KBD_MASK_SHIFT );
    init_kdb_struct(0x16, ASCII_LOWER_U, ASCII_UPPER_U, KBD_MASK_SHIFT );
    init_kdb_struct(0x17, ASCII_LOWER_I, ASCII_UPPER_I, KBD_MASK_SHIFT );
    init_kdb_struct(0x18, ASCII_LOWER_O, ASCII_UPPER_O, KBD_MASK_SHIFT );
    init_kdb_struct(0x19, ASCII_LOWER_P, ASCII_UPPER_P, KBD_MASK_SHIFT );
    init_kdb_struct(0x1A, ASCII_L_SQR_BRKT, ASCII_L_CURLY_BRKT, KBD_MASK_SHIFT );
    init_kdb_struct(0x1B, ASCII_R_SQR_BRKT, ASCII_R_CURLY_BRKT, KBD_MASK_SHIFT );
    init_kdb_struct(0x1C, ASCII_LINE_FEED, ASCII_LINE_FEED, KBD_MASK_NONE ); // ENTER replace with ctrl msg?
    init_kdb_struct(0x1D, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MODIFIER | KBD_MASK_CTRL ); //LCTRL
    init_kdb_struct(0x1E, ASCII_LOWER_A, ASCII_UPPER_A, KBD_MASK_SHIFT );
    init_kdb_struct(0x1F, ASCII_LOWER_S, ASCII_UPPER_S, KBD_MASK_SHIFT );
    init_kdb_struct(0x20, ASCII_LOWER_D, ASCII_UPPER_D, KBD_MASK_SHIFT );
    init_kdb_struct(0x21, ASCII_LOWER_F, ASCII_UPPER_F, KBD_MASK_SHIFT );
    init_kdb_struct(0x22, ASCII_LOWER_G, ASCII_UPPER_G, KBD_MASK_SHIFT );
    init_kdb_struct(0x23, ASCII_LOWER_H, ASCII_UPPER_H, KBD_MASK_SHIFT );
    init_kdb_struct(0x24, ASCII_LOWER_J, ASCII_UPPER_J, KBD_MASK_SHIFT );
    init_kdb_struct(0x25, ASCII_LOWER_K, ASCII_UPPER_K, KBD_MASK_SHIFT );
    init_kdb_struct(0x26, ASCII_LOWER_L, ASCII_UPPER_L, KBD_MASK_SHIFT );
    init_kdb_struct(0x27, ASCII_SEMICOLON, ASCII_COLON, KBD_MASK_SHIFT );
    init_kdb_struct(0x28, ASCII_SINGLE_QUOTE, ASCII_DOUBLE_QOUTE, KBD_MASK_SHIFT );
    init_kdb_struct(0x29, ASCII_BACKTICK, ASCII_TILDE, KBD_MASK_SHIFT );
    init_kdb_struct(0x2A, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MODIFIER | KBD_MASK_SHIFT ); //LSHIFT
    init_kdb_struct(0x2B, ASCII_BACKSLASH, ASCII_VERT_BAR, KBD_MASK_SHIFT );
    init_kdb_struct(0x2C, ASCII_LOWER_Z, ASCII_UPPER_Z, KBD_MASK_SHIFT );
    init_kdb_struct(0x2D, ASCII_LOWER_X, ASCII_UPPER_X, KBD_MASK_SHIFT );
    init_kdb_struct(0x2E, ASCII_LOWER_C, ASCII_UPPER_C, KBD_MASK_SHIFT );
    init_kdb_struct(0x2F, ASCII_LOWER_V, ASCII_UPPER_V, KBD_MASK_SHIFT );
    init_kdb_struct(0x30, ASCII_LOWER_B, ASCII_UPPER_B, KBD_MASK_SHIFT );
    init_kdb_struct(0x31, ASCII_LOWER_N, ASCII_UPPER_N, KBD_MASK_SHIFT );
    init_kdb_struct(0x32, ASCII_LOWER_M, ASCII_UPPER_M, KBD_MASK_SHIFT );
    init_kdb_struct(0x33, ASCII_COMMA, ASCII_LESS_THAN, KBD_MASK_SHIFT );
    init_kdb_struct(0x34, ASCII_PERIOD, ASCII_GREATER_THAN, KBD_MASK_SHIFT );
    init_kdb_struct(0x35, ASCII_SLASH, ASCII_QUESTION_MARK, KBD_MASK_SHIFT );
    init_kdb_struct(0x36, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MODIFIER | KBD_MASK_SHIFT ); //RSHIFT
    init_kdb_struct(0x37, ASCII_ASTERISK, ASCII_ASTERISK, KBD_MASK_NONE );
    init_kdb_struct(0x38, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MODIFIER | KBD_MASK_ALT ); //LALT
    init_kdb_struct(0x39, ASCII_SPACE, ASCII_SPACE, KBD_MASK_NONE );
    init_kdb_struct(0x3A, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MODIFIER | KBD_MASK_CAPSLOCK ); //CAPSLOCK
    init_kdb_struct(0x3B, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_FN ); // F1
    init_kdb_struct(0x3C, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_FN ); // F2
    init_kdb_struct(0x3D, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_FN ); // F3
    init_kdb_struct(0x3E, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_FN ); // F4
    init_kdb_struct(0x3F, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_FN ); // F5
    init_kdb_struct(0x40, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_FN ); // F6
    init_kdb_struct(0x41, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_FN ); // F7 
    init_kdb_struct(0x42, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_FN ); // F8 
    init_kdb_struct(0x43, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_FN ); // F9 
    init_kdb_struct(0x44, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_FN ); // F10
    init_kdb_struct(0x45, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MODIFIER | KBD_MASK_NUMLOCK ); // NUMLOCK
    init_kdb_struct(0x46, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_NONE ); // SCROLLLOCK
    init_kdb_struct(0x47, KBD_INPUT_NONE, ASCII_SEVEN, KBD_MASK_NUMLOCK ); // Home
    init_kdb_struct(0x48, KBD_INPUT_NONE, ASCII_EIGHT, KBD_MASK_NUMLOCK ); // UP
    init_kdb_struct(0x49, KBD_INPUT_NONE, ASCII_NINE, KBD_MASK_NUMLOCK ); // PGUP
    init_kdb_struct(0x4A, ASCII_MINUS, ASCII_MINUS, KBD_MASK_NONE );
    init_kdb_struct(0x4B, KBD_INPUT_NONE, ASCII_FOUR, KBD_MASK_NUMLOCK ); // LEFT
    init_kdb_struct(0x4C, KBD_INPUT_NONE, ASCII_FIVE, KBD_MASK_NUMLOCK ); 
    init_kdb_struct(0x4D, KBD_INPUT_NONE, ASCII_SIX, KBD_MASK_NUMLOCK ); // RIGHT
    init_kdb_struct(0x4E, ASCII_PLUS, ASCII_PLUS, KBD_MASK_NONE );
    init_kdb_struct(0x4F, KBD_INPUT_NONE, ASCII_ONE, KBD_MASK_NUMLOCK ); // END
    init_kdb_struct(0x50, KBD_INPUT_NONE, ASCII_TWO, KBD_MASK_NUMLOCK ); // DOWN
    init_kdb_struct(0x51, KBD_INPUT_NONE, ASCII_THREE, KBD_MASK_NUMLOCK ); // PGDOWN
    init_kdb_struct(0x52, KBD_INPUT_NONE, ASCII_ZERO, KBD_MASK_NUMLOCK ); // INS
    init_kdb_struct(0x53, KBD_INPUT_NONE, ASCII_PERIOD, KBD_MASK_NUMLOCK ); // DEL key
    init_kdb_struct(0x57, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_FN ); // F11
    init_kdb_struct(0x58, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_FN ); // F12
    /* Release scan-codes are identical, so re-use the index for the duplicate keys */
    init_kdb_struct(0x9C, ASCII_LINE_FEED, ASCII_LINE_FEED, KBD_MASK_NONE );
    init_kdb_struct(0x9D, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MODIFIER | KBD_MASK_CTRL ); //LCTRL
    init_kdb_struct(0xB5, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MODIFIER | KBD_MASK_CTRL );
    init_kdb_struct(0xC7, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_NONE ); // Home
    init_kdb_struct(0xC8, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_NONE ); // Up
    init_kdb_struct(0xC9, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_NONE ); // PgUp
    init_kdb_struct(0xCB, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_NONE ); // Left
    init_kdb_struct(0xCD, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_NONE ); // Right
    init_kdb_struct(0xCF, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_NONE ); // End
    init_kdb_struct(0xD0, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_NONE ); // Down
    init_kdb_struct(0xD1, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_NONE ); // PgDown
    init_kdb_struct(0xD2, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_NONE ); // Insert
    init_kdb_struct(0xD3, KBD_INPUT_NONE, KBD_INPUT_NONE, KBD_MASK_NONE ); // Delete

    current_modifiers = 0;
    irq_clear_mask(0x1);
}


static uint8_t kbd_get_status()
{
    return inport8(KBD_STATUS_PORT);
}


static void kbd_send_data(uint8_t data)
{
    while(kbd_get_status() & KBD_STATUS_IN_BUF);
    outport8(KBD_CMD_PORT, data);
}


static uint8_t kbd_read_data()
{
    return inport8(KBD_CMD_PORT);
}


void keyboard_handler(asos::ISRData * data)
{
    // If we got an interrupt and the data isn't ready it's
    // already been read and we can just ignore this I guess?
    if ((kbd_get_status() & KBD_STATUS_OUT_BUF) == 0) {
        irq_eoi(data->int_no);
        return;
    }

    uint8_t kbd_data = kbd_read_data();
    uint8_t is_multiple = 0;
    // Check if we need more bytes to proceed
    if (kbd_data == KBD_SCAN_MORE_DATA) {
        kbd_data = kbd_read_data();
        is_multiple = 0xFF;
    }

    irq_eoi(data->int_no);

    // Highest but just tells is if its pressed (0) or released (1)
    uint8_t pressed = 0x80 & ~kbd_data;

    // Some scan codes are sent over 2 bytes (in another interrupt)
    // so always keep the highest bit even its been pressed
    // this is due to the way keys are stored in the lookup table
    // i.e if the bit isn't set it conflicts with other keys
    uint8_t scancode = 0x7F & kbd_data;
    if (is_multiple)
        scancode = 0x80 | kbd_data;

    const kbd_event * evt = &scancode_set1[scancode];

    // Modifier bit indicate if it is the modifier key itself
    uint8_t is_modifier = KBD_MODIFIER & evt->modifier_mask;
    if (is_modifier) {
        if (pressed)
            current_modifiers |= evt->modifier_mask;
        else
            current_modifiers &= ~(evt->modifier_mask);
        return;
    } 
    
    // If a non-modifier key was pressed
    if (pressed) {
        // TODO: handle capslock/numlock/scrolllock
        uint8_t c = (evt->modifier_mask & current_modifiers) ? evt->data_mod : evt->data;
        tty_putchar(c);
        
        // In future when we have userspace, this will be replaced
        // with a write/send to character device
        if (__len >= 80)
            __len = 0;
        if (c == '\n') {
            c = 0;
            __newline = 1;
        }
        //__kbd_buffer[__len++] = c;

    }
}