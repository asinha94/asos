#ifndef ASOS_STRINGH
#define ASOS_STRINGH

#include <stddef.h>

int strncmp(const char * s1, const char * s2, size_t n);

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