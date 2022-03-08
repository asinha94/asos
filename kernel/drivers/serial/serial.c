#include <cpu/hal.h>
#include <drivers/serial/serial.h>

// Code mostly taken from https://wiki.osdev.org/Serial_Ports
// ...except I removed all the test code...lord help me if I ever run this on real hardware

#define PORT 0x3F8 // COM1

void serial_puts(const char *s)
{
    while ((inport8(PORT + 5) & 0x20) == 0);
    while (*s) {
        outport8(PORT, *s++);
    }
}

void serial_putchar(unsigned char a) {
    // Wait till nothing is being transmitted
    while ((inport8(PORT + 5) & 0x20) == 0); 
    outport8(PORT, a);
}

void init_serial()
{
    // Straight up copied off the osdev page
    outport8(PORT + 1, 0x00);    // Disable all interrupts
    outport8(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outport8(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outport8(PORT + 1, 0x00);    //                  (hi byte)
    outport8(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
    outport8(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outport8(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}