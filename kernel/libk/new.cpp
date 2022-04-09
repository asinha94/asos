#include <stddef.h>
#include <libk/kmalloc.h>

void * operator new(size_t size)
{
    return kmalloc(size);
}

void * operator new[](size_t size)
{
    return kmalloc(size);
}

void operator delete(void * p)
{
    kfree(p);
}

void operator delete(void * p, __attribute__ ((unused)) long unsigned int align)
{
    kfree(p);
}

void operator delete[](void * p)
{
    kfree(p);
}

void operator delete[](void * p, __attribute__ ((unused)) long unsigned int align)
{
    kfree(p);
}

