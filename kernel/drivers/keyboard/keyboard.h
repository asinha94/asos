#ifndef ASOS_KBD_H
#define ASOS_KBD_H

#include <stdint.h>
#include <cpu/interrupts/idt.h>


/* Ports */
#define KBD_CMD_PORT        0x60
#define KBD_DATA_PORT       0x64
#define KBD_STATUS_PORT     0x64

/* Status Codes */
#define KBD_SCAN_MORE_DATA  0xE0
#define KBD_ACK_BYTE        0xFA

/* Keyboard Status Register Masks */
#define KBD_STATUS_OUT_BUF  0x01
#define KBD_STATUS_IN_BUF   0x02
#define KBD_STATUS_SYSTEM   0x04
#define KBD_STATUS_CMD      0x08
#define KBD_STATUS_LOCKED   0x10
#define KBD_STATUS_DTYPE    0x20
#define KBD_STATUS_TIMEOUT  0x40
#define KBD_STATUS_PARITY   0x80

/* Modifier Bitmasks */
#define KBD_MASK_NONE       0x00 // 0b00000000
#define KBD_MASK_CAPSLOCK   0x01 // 0b00000001
#define KBD_MASK_SHIFT      0x02 // 0b00000010
#define KBD_MASK_CTRL       0x04 // 0b00000100
#define KBD_MASK_WINKEY     0x08 // 0b00001000
#define KBD_MASK_ALT        0x10 // 0b00010000
#define KBD_MASK_FN         0x20 // 0b00100000
#define KBD_MASK_NUMLOCK    0x40 // 0x01000000
#define KBD_MODIFIER        0x80 // 0b10000000

#define KBD_SCAN_CODES      256
#define KBD_INPUT_NONE      0x00


struct kbd_event_struct {
    uint8_t data;
    uint8_t data_mod;
    uint8_t modifier_mask;
//    uint8_t function; // add back in once things are stable
} __attribute__((packed));
typedef struct kbd_event_struct kbd_event;


void keyboard_init();
void keyboard_handler(asos::ISRData * data);


#endif