#include <stddef.h>

// TODO: Optimize using assembly
__attribute__((always_inline))
static inline void * memset(void *dest, unsigned char ch, size_t n) {

    unsigned char *ptr = (unsigned char *) dest;
    while (n-- > 0) {
        *ptr++ = ch;
    }
    return dest;
}