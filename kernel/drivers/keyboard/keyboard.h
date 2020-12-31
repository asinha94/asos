#ifndef ASOS_KBD_H
#define ASOS_KBD_H

#include <stdint.h>
#include <cpu/interrupts/idt.h>

#define KBD_SCAN_CODES      0x100
#define KBD_SCAN_CODE_PORT  0x60
#define KBD_SCAN_MORE_DATA  0xE0
#define KBD_ACK_BYTE        0xFA

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


#define KBD_INPUT_NONE      0x00

struct kbd_event_struct {
    uint8_t data;
    uint8_t data_mod;
    uint8_t modifier_mask;
//    uint8_t function; // add back in once things are stable
} __attribute__((packed));
typedef struct kbd_event_struct kbd_event;


const kbd_event scancode_set1[KBD_SCAN_CODES];
void keyboard_init();
void keyboard_handler(isr_data * data);

#endif