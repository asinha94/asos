#ifndef ASOS_PSF_H
#define ASOS_PSF_H

#include <libk/kmalloc.h>
#include <stdint.h>

void get_a(uint8_t * psf)
{
    psf[0]  = 0b00000000;
    psf[1]  = 0b00000000;
    psf[2]  = 0b00000000;
    psf[3]  = 0b00010000;
    psf[4]  = 0b00111000;
    psf[5]  = 0b01101100;
    psf[6]  = 0b11000110;
    psf[7]  = 0b11000110;
    psf[8]  = 0b11111110;
    psf[9]  = 0b11000110;
    psf[10] = 0b11000110;
    psf[11] = 0b11000110;
    psf[12] = 0b11000110;
    psf[13] = 0b00000000;
    psf[14] = 0b00000000;
    psf[15] = 0b00000000;
}

void get_a2(uint8_t * psf)
{
    psf[0]  = 0b00000000;
    psf[1]  = 0b00000000;
    psf[2]  = 0b00000000;
    psf[3]  = 0b00000000;
    psf[4]  = 0b00011000;
    psf[5]  = 0b00011000;
    psf[6]  = 0b00100100;
    psf[7]  = 0b00100100;
    psf[8]  = 0b00100100;
    psf[9]  = 0b00111100;
    psf[10] = 0b01000010;
    psf[11] = 0b01000010;
    psf[12] = 0b01000010;
    psf[13] = 0b00000000;
    psf[14] = 0b00000000;
    psf[15] = 0b00000000;
}

void get_b(uint8_t * psf)
{
    psf[0]  = 0b00000000;
    psf[1]  = 0b00000000;
    psf[2]  = 0b00000000;
    psf[3]  = 0b01111000;
    psf[4]  = 0b10000100;
    psf[5]  = 0b10000100;
    psf[6]  = 0b11111000;
    psf[7]  = 0b10000100;
    psf[8]  = 0b10000100;
    psf[9]  = 0b10000100;
    psf[10] = 0b01111000;
    psf[11] = 0b00000000;
    psf[12] = 0b00000000;
    psf[13] = 0b00000000;
    psf[14] = 0b00000000;
    psf[15] = 0b00000000;
}


#endif