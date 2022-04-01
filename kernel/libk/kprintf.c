#include <stdint.h>
#include <stdarg.h>
#include <drivers/serial/serial.h>
#include <libk/kprintf.h>
#include <libk/string.h>



void kprintf(const char * format, ...)
{
    // temp for conversions
    static char temp[12];
    // Only %d, %s, %u, %x supported
    uint32_t u;
    int32_t i;
    char *s;

    // variadic argument macro
    va_list arg; 
    va_start(arg, format); 

    const char * iter;
    for (iter = format; *iter != 0; ++iter) {
        if (*iter != '%') {
            serial_putchar(*iter);
            continue;
        }

        iter++;
        switch(*iter) {
            case 'c':
                i = va_arg(arg, int);
                serial_putchar((char) i);
                break;
            case 'd':
                i = va_arg(arg, int);
                if (i < 0) {
                    i = -i;
                    serial_putchar('-');
                }
                s = itoa(&temp[11], i, 10);
                serial_puts(s);
                break;
            case 'u':
                u = va_arg(arg, unsigned int);
                s = itoa(&temp[11], u, 10);
                serial_puts(s);
                break;
            case 's':
                s = va_arg(arg, char *);
                serial_puts(s);
                break;
            case 'x':
                u = va_arg(arg, unsigned int);
                s = itoa(&temp[11], u, 16);
                serial_puts("0x");
                serial_puts(s);
                break; 
        }

    }
    va_end(arg);
}
