#include <libk/kmalloc.h>


void * kmalloc(size_t size)
{
    return 0;
}

void * kcalloc(size_t num, size_t size)
{
    return 0;
}

void * krealloc(size_t size)
{
    return 0;
}

void free(void * ptr)
{

}


int main()
{
    uint32_t * ptr = kmalloc(10);
    free(ptr);
}