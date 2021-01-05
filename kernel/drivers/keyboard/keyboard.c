#include <cpu/hal.h>
#include <cpu/interrupts/pic.h>
#include <cpu/interrupts/idt.h>
#include <drivers/keyboard/keyboard.h>
#include <display/tty.h>

/*
    Implementation derived from these references
    - https://wiki.osdev.org/PS2_Keyboard
    - https://www.win.tue.nl/~aeb/linux/kbd/scancodes.html
*/


static const kbd_event * last_pressed;
static uint8_t current_modifiers;

void keyboard_init()
{
    kprintf("Initializing Keyboard\n");

    // TODO: 
    // disable all LEDs?
    // set type rate?

    last_pressed = NULL;
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
    return inport8(KBD_DATA_PORT);
}


void keyboard_handler(isr_data * data)
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
    // so we need to keep the highest bit
    uint8_t scancode = 0;
    if (is_multiple) {
        scancode = 0x80 | kbd_data;
    } else {
        scancode = 0x7F & kbd_data;
    }
 
    const kbd_event * evt = &scancode_set1[scancode];
    // Modifier bit indicate if it is the modifier key itself
    uint8_t is_modifier = KBD_MODIFIER & evt->modifier_mask;
    if (is_modifier && pressed) {
        // Modifier has been pressed
        // Set the appropriate bit in the modifier mask
        current_modifiers |= evt->modifier_mask;

    } else if (is_modifier) {
        // Key is a modifier but has been released flip modifier bits 
        // AND with from current_modifiers to remove bit
        current_modifiers &= ~(evt->modifier_mask);

    } else if (pressed) {
        // Key can't be a modifier and has been pressed down
        last_pressed = evt;

    } else if (last_pressed == evt) {
        // key can't be a modifier and has been released
        // If it happens to be the last thing we pressed down,
        // we stop inserting things, even if other keys are also
        // being pressed. Windows has the same behaviour
        last_pressed = NULL;
    }
    
    // Print char if anything pressed
    if (last_pressed) {
        uint8_t current_value = last_pressed->data;
        if (last_pressed->modifier_mask & current_modifiers) {
            current_value = last_pressed->data_mod;
        }

        // In future when we have userspace, this will be replaced
        // with a send and/or read with readline
        tty_putchar(current_value);        
    }
}