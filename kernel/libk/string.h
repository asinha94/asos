#ifndef ASOS_STRING_H
#define ASOS_STRING_H

#include <stddef.h>
#include <stdint.h>

int strncmp(const char * s1, const char * s2, size_t n);
size_t strlen(const char* str);
char * itoa(char * s, uint32_t x, uint32_t base);

// TODO: Optimize using inline assembly
__attribute__((always_inline))
static inline void * memset(void * dest, unsigned char ch, size_t n) {

    unsigned char *ptr = (unsigned char *) dest;
    while (n-- > 0) {
        *ptr++ = ch;
    }
    return dest;
}

#endif