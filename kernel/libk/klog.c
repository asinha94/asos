#include <stdint.h>
#include <stdarg.h>
#include <libk/klog.h>
#include <libk/string.h>

static void default_putchar(unsigned char c);
static void default_puts(unsigned char c);


static void (*putchar)(unsigned char c) = default_putchar;
static void (*puts)(const char * data) = default_puts;


static void default_putchar(unsigned char c)
{
    return;
}


static void default_puts(unsigned char c)
{
    return;
}

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
            putchar(*iter);
            continue;
        }

        iter++;
        switch(*iter) {
            case 'c':
                i = va_arg(arg, int);
                putchar((char) i);
                break;
            case 'd':
                i = va_arg(arg, int);
                if (i < 0) {
                    i = -i;
                    putchar('-');
                }
                s = itoa(&temp[11], i, 10);
                puts(s);
                break;
            case 'u':
                u = va_arg(arg, unsigned int);
                s = itoa(&temp[11], u, 10);
                puts(s);
                break;
            case 's':
                s = va_arg(arg, char *);
                puts(s);
                break;
            case 'x':
                u = va_arg(arg, unsigned int);
                s = itoa(&temp[11], u, 16);
                puts("0x");
                puts(s);
                break; 
        }

    }
    va_end(arg);
}


void init_klog(void (*putchar_fp)(unsigned char), void (*puts_fp)(const char*) )
{
    putchar = putchar_fp;
    puts = puts_fp;
}