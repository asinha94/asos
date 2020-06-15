#ifndef ASOS_CPU_H
#define ASOS_CPU_H

#include <stdint.h>

extern uint8_t inportb(uint16_t port);
extern void outportb(uint16_t port, uint8_t byte);
extern void io_wait();

#endif