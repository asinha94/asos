#ifndef ASOS_SERIAL_H
#define ASOS_SERIAL_H

namespace asos {
    static constexpr int serial_port = 0x3F8;
    void init_serial();
    void serial_puts(const char *);
    void serial_putchar(unsigned char);
}
#endif