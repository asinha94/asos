#include <libk/string.h>


int strncmp(const char * s1, const char * s2, size_t n)
{
    while (n && *s1 && *s2 && (*s1 == *s2)) {
        ++s1;
        ++s2;
        --n;
    }

    if (n == 0)
        return 0;

    unsigned char c1 = *(unsigned char *) s1;
    unsigned char c2 = *(unsigned char *) s2;
    return c1 - c2;
}
