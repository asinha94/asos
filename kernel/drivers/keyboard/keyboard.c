#include <cpu/hal.h>
#include <cpu/interrupts/pic.h>
#include <cpu/interrupts/idt.h>
#include <drivers/keyboard/keyboard.h>
#include <display/tty.h>

/*
    Implementation derived from these references
    - https://wiki.osdev.org/PS2_Keyboard
    - https://www.win.tue.nl/~aeb/linux/kbd/scancodes.html
    - http://www.brokenthorn.com/Resources/OSDev19.html
*/


static uint8_t current_modifiers;

void keyboard_init()
{
    kprintf("Initializing Keyboard\n");

    // TODO: 
    // disable all LEDs?
    // set type rate?
    // character device? need vfs first

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
    // so always keep the highest bit even its been pressed
    // this is due to the way keys are stored in the lookup table
    // i.e if the bit isn't set it conflicts with other keys
    uint8_t scancode = scancode = 0x7F & kbd_data;
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
        uint8_t current_value = evt->data;
        if (evt->modifier_mask & current_modifiers)
            current_value = evt->data_mod;
        // TODO: handle capslock/numlock/scrolllock
        // In future when we have userspace, this will be replaced
        // with a write/send to character device
        tty_putchar(current_value);  
    }
}