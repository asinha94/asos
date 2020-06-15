#ifndef ASOS_HAL_H
#define ASOS_HAL_H

#include <stdint.h>

extern uint8_t inportb(uint16_t port);
extern void outportb(uint16_t port, uint8_t byte);
extern void io_wait();
extern void disable_interrupts();
extern void enable_interrupts();

#endif