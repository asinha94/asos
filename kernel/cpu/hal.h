#ifndef ASOS_HAL_H
#define ASOS_HAL_H

#include <stdint.h>

extern uint8_t inport8(uint16_t port);
extern void outport8(uint16_t port, uint8_t byte);
extern void disable_interrupts();
extern void enable_interrupts();

#endif