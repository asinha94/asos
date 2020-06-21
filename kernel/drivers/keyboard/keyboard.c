#include <cpu/hal.h>
#include <cpu/interrupts/pic.h>
#include <cpu/interrupts/idt.h>
#include <drivers/keyboard/keyboard.h>
#include <display/tty.h>

const kbd_event * last_pressed;
uint8_t current_modifiers;

void keyboard_init()
{
    last_pressed = &scancode_set1[0];
    current_modifiers = 0;
    irq_clear_mask(0x1);
}

void keyboard_handler()
{
    uint8_t kbd_data = inport8(KBD_SCAN_CODE_PORT);
    // Highest but just tells is if its pressed (0) or released (1)
    uint8_t pressed = 0x80 & ~kbd_data;
    uint8_t scancode = 0x7F & kbd_data;
    const kbd_event * evt = &scancode_set1[scancode];

    // Modifier bit indicate if it is the modifier key itself
    if (KBD_MODIFIER & evt->modifier_mask) {
        if (pressed) {
            // insert bit indicating modifier is currently pressed
            current_modifiers |= evt->modifier_mask;
        } else {
            // remove bit to indicate not pressed
            current_modifiers &= ~(evt->modifier_mask);
        }
    } else {
        if (pressed) {
            last_pressed = evt;
        } else {
            // If the last key pressed is depressed, insert nothing
            if (last_pressed == evt) {
                last_pressed = &scancode_set1[0];
            }
        }
    }

    // Print char if available not 0. 
    
    if (last_pressed->scancode_reg) {
        uint8_t current_value = last_pressed->scancode_reg;
        if (last_pressed->modifier_mask & current_modifiers) {
            current_value = last_pressed->scancode_mod;
        }

        // In future when we have userspace, this will be replaced
        // with a send and/or read with readline
        tty_putchar(current_value);        
    }
}