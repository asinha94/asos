#include <drivers/keyboard.h>
#include <cpu/interrupts/pic.h>
#include <cpu/interrupts/idt.h>
#include <display/tty.h>

#define KBD_SCAN_CODE            0x60

void keyboard_init()
{
    irq_clear_mask(1);
}

inline void keyboard_handler(isr_data * data)
{
    uint8_t kbd_data = inport8(KBD_SCAN_CODE);
    kprintf("Got %u from Keyboard\n", kbd_data);
}