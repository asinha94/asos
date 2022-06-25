#include <libk/math.h>

uint32_t div_ceil(uint32_t num, uint32_t denom)
{
    uint32_t div = num / denom;
    return div + ((num % denom) ? 1 : 0);
}