#include <cpu/hal.h>
#include <cpu/interrupts/pic.h>
#include <cpu/interrupts/idt.h>
#include <drivers/keyboard/keyboard.h>
#include <display/tty.h>

const kbd_event * last_pressed;
uint8_t current_modifiers;

void keyboard_init()
{
    uint8_t data;
    uint8_t max_tries = 3;
    kprintf("Initializing Keyboard\n");

    // get/set scan code set 1 here
    // disalbe all LED
    // set type rate

    last_pressed = NULL;
    current_modifiers = 0;
    irq_clear_mask(0x1);
}

void keyboard_handler()
{
    uint8_t kbd_data = inport8(KBD_SCAN_CODE_PORT);
    uint8_t is_multiple = 0;
    // Check if we need more bytes to proceed
    if (kbd_data == KBD_SCAN_MORE_DATA) {
        kbd_data = inport8(KBD_SCAN_CODE_PORT);
        is_multiple = 0xFF;
    }
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