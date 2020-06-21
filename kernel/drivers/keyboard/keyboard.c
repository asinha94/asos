#include <cpu/hal.h>
#include <cpu/interrupts/pic.h>
#include <cpu/interrupts/idt.h>
#include <drivers/keyboard/keyboard.h>
#include <display/tty.h>

uint8_t current_value;
uint8_t current_modifiers;

void keyboard_init()
{
    current_value = 0;
    current_modifiers = 0;
    irq_clear_mask(0x1);
}

void keyboard_handler(isr_data * data)
{
    uint8_t kbd_data = inport8(KBD_SCAN_CODE_PORT);
    // Highest but just tells is if its pressed (0) or released (1)
    uint8_t pressed = 0x80 ^ kbd_data;
    uint8_t scancode = 0x7F & kbd_data;
    kbd_event * evt = &scancode_set1[scancode];

    // Logic below I think can be cleaned up and consolidated
    // Mask has hightest bit set to indicate it is the modifier key itself
    uint8_t is_modifier = 0x80 & evt->modifier_mask;
    if (is_modifier) {
        if (pressed) {
            current_modifiers |=  evt->modifier_mask;
        } else {
            // remove all high bits in modifier_mask
            current_modifiers &= ~(evt->modifier_mask);
        }
    } else {
        current_value = 0;
        if (pressed) {
            current_value = evt->scancode_reg;
            if (evt->modifier_mask & current_modifiers) {
                current_value = evt->scancode_mod;
            }
        }
    }
    
    if (current_value) kprintf("Got %c from Keyboard\n", current_value);
}