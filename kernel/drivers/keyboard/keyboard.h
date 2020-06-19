#ifndef ASOS_KBD_H
#define ASOS_KBD_H

#include <stdint.h>
#include <cpu/interrupts/idt.h>

/* */
#define KBD_SCAN_CODE_PORT 0x60
#define KBD_SCAN_CODES 128

/* Modifier Bitmasks */
#define KBD_MASK_NONE       0x00
#define KBD_MASK_CAPSLOCK   0x01 // 0b00000001
#define KBD_MASK_SHIFT      0x02 // 0b00000010
#define KBD_MASK_CTRL       0x04 // 0b00000100
#define KBD_MASK_WINKEY     0x08 // 0b00001000
#define KBD_MASK_ALT        0x10 // 0b00010000
#define KBD_MASK_FN         0x20 // 0b00100000
#define KBD_MASK_NUMLOCK    0x40 // 0x01000000
#define KBD_MODIFIER        0x80 // 0b10000000

/* Currently only 104-key US-QWERTY layout supported */
typedef enum {
    /* Function Keys */
    KEY_ESC,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    /* Navigation Keys */
    KEY_PRINT_SCREEN,
    KEY_SCROLL_LOCK,
    KEY_PAUSE_BREAK,
    KEY_INSERT,
    KEY_HOME,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    KEY_END,
    KEY_DELETE,
    KEY_ARROW_UP,
    KEY_ARROW_DOWN,
    KEY_ARROW_LEFT,
    KEY_ARROW_RIGHT,
    /* Control Modifiers & others */
    KEY_TAB,
    KEY_CAPS_LOCK,
    KEY_LSHIFT,
    KEY_LCTRL,
    KEY_WINKEY,
    KEY_LALT,
    KEY_SPACE,
    KEY_RALT,
    KEY_FN,
    KEY_MENUKEY,
    KEY_LCTRL,
    KEY_LSHIFT,
    KEY_ENTER,
    KEY_BACKSPACE,
    /* Number Row */
    KEY_TILDE,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,
    KEY_MINUS,
    KEY_EQUALS,
    /* Symbols */
    KEY_LBRACKET,
    KEY_RBRACKET,
    KEY_BACKSLASH,
    KEY_SEMICOLON,
    KEY_QUOTE,
    KEY_LT,
    KEY_GT,
    KEY_FORWARDSLASH,
    /* Letters*/
    KEY_Q,
    KEY_W,
    KEY_E,
    KEY_R,
    KEY_T,
    KEY_Y,
    KEY_U,
    KEY_I,
    KEY_O,
    KEY_P,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_Z,
    KEY_X,
    KEY_C,
    KEY_V,
    KEY_B,
    KEY_N,
    KEY_M,
    /* Numpad */
    KEY_NP_0,
    KEY_NP_1,
    KEY_NP_2,
    KEY_NP_3,
    KEY_NP_4,
    KEY_NP_5,
    KEY_NP_6,
    KEY_NP_7,
    KEY_NP_8,
    KEY_NP_9,
    KEY_NP_NUMLOCK,
    KEY_NP_FORWARDSLASH,
    KEY_NP_ASTERISK,
    KEY_NP_MINUS,
    KEY_NP_PLUS,
    KEY_NP_ENTER,
    KEY_NP_DEL,
} kdb_key;
// Letters



struct kbd_event_struct {
    uint8_t scancode_base;
    uint8_t scancode_modified;
    uint8_t modifier_bitmask;
} __attribute__ ((packed));
typedef struct kbd_event_struct kbd_event;


extern const kbd_event scancode_set2[KBD_SCAN_CODES];
void keyboard_init();
extern inline void keyboard_handler(isr_data * data);

#endif