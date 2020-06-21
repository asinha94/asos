#include <cpu/hal.h>
#include <cpu/interrupts/pic.h>
#include <cpu/interrupts/idt.h>
#include <drivers/keyboard/keyboard.h>
#include <display/tty.h>

void keyboard_init()
{
    irq_clear_mask(0x1);
}

void keyboard_handler(isr_data * data)
{
    uint8_t kbd_data = inport8(KBD_SCAN_CODE_PORT);
    kprintf("Got %x from Keyboard\n", kbd_data);
}