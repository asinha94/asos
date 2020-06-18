#ifndef ASOS_KBD_H
#define ASOS_KBD_H

#include <cpu/interrupts/idt.h>

void keyboard_init();
extern inline void keyboard_handler(isr_data * data);

#endif