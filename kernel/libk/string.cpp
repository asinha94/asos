#include <libk/string.h>
#include <stdint.h>


int strncmp(const char * s1, const char * s2, size_t n)
{
    while (n && *s1 && *s2 && (*s1 == *s2)) {
        ++s1;
        ++s2;
        --n;
    }

    if (n == 0)
        return 0;

    unsigned const char c1 = *(unsigned const char *) s1;
    unsigned const char c2 = *(unsigned const char *) s2;
    return c1 - c2;
}


size_t strlen(const char* str) {
    size_t len = 0;
    while (*str++)
        len++;
    return len;
}


char * itoa(char * s, uint32_t x, uint32_t base)
{
    // s is a pointer to the end of a buffer
    // 2**32 is the max representable value
    // and fits in 10 chars (negative sign inserted beforehand)
    // Buffer is larger than 10 so dont worry about space
    const char * digits = "0123456789ABCDEF";
    uint16_t i;

    // Its itoa's job to insert the null terminator
    *s = 0;
    do {
        i = x % base;
        *(--s) = digits[i];
        x /= base;
    } while (x);
    return s;
}