#ifndef ASOS_KLOG_H
#define ASOS_KLOG_H

void init_klog(void (*putchar_fp)(unsigned char), void (*puts_fp)(const char*) );
void kprintf(const char * format, ...);

#endif