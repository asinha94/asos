#ifndef ASOS_KPRINTF_H
#define ASOS_KPRINTF_H

void init_kprintf(void (*putchar_fp)(unsigned char), void (*puts_fp)(const char*) );
void kprintf(const char * format, ...);

#endif