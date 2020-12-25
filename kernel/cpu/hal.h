#ifndef ASOS_HAL_H
#define ASOS_HAL_H

#include <stdint.h>


__attribute__((always_inline))
static inline uint8_t inport8(uint16_t port)
{
    uint8_t byte;
    asm volatile(
        "inb %0, %1"
        : "=a"(byte)
        : "d"(port)
        );
    return byte;
}

//uint8_t inport8(uint16_t port);


__attribute__((always_inline))
static inline void outport8(uint16_t port, uint8_t byte)
{
    asm volatile(
        "outb %0, %1"
        :
        : "d"(port), "a"(byte)
        
        );

}


__attribute__((always_inline))
static inline void disable_interrupts()
{
    asm volatile("cli");
}


__attribute__((always_inline))
static inline void enable_interrupts()
{
    asm volatile("sti");
}

#endif