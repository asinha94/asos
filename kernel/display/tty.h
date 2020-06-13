#ifndef ASOS_i386_TTY_H
#define ASOS_i386_TTY_H

#include <stddef.h>
#include <stdint.h>

extern const size_t VGA_WIDTH;
extern const size_t VGA_HEIGHT;
extern void tty_writestring(const char* data);
extern void tty_init(void);

#endif
