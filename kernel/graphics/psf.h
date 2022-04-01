#ifndef ASOS_PSF_H
#define ASOS_PSF_H

#include <libk/kmalloc.h>
#include <stdint.h>

uint8_t * pxl_0(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00111000;
    psf[0x5] = 0b01000100;
    psf[0x6] = 0b01000100;
    psf[0x7] = 0b01010100;
    psf[0x8] = 0b01010100;
    psf[0x9] = 0b01010100;
    psf[0xA] = 0b01000100;
    psf[0xB] = 0b01000100;
    psf[0xC] = 0b00111000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_1(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00010000;
    psf[0x5] = 0b01110000;
    psf[0x6] = 0b00010000;
    psf[0x7] = 0b00010000;
    psf[0x8] = 0b00010000;
    psf[0x9] = 0b00010000;
    psf[0xA] = 0b00010000;
    psf[0xB] = 0b00010000;
    psf[0xC] = 0b01111100;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_2(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00111000;
    psf[0x5] = 0b01000100;
    psf[0x6] = 0b00000100;
    psf[0x7] = 0b00001000;
    psf[0x8] = 0b00001000;
    psf[0x9] = 0b00010000;
    psf[0xA] = 0b00100000;
    psf[0xB] = 0b01000000;
    psf[0xC] = 0b01111100;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_3(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01111100;
    psf[0x5] = 0b00000100;
    psf[0x6] = 0b00000100;
    psf[0x7] = 0b00000100;
    psf[0x8] = 0b00111000;
    psf[0x9] = 0b00000100;
    psf[0xA] = 0b00000100;
    psf[0xB] = 0b00000100;
    psf[0xC] = 0b01111000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_4(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00001100;
    psf[0x5] = 0b00001100;
    psf[0x6] = 0b00010100;
    psf[0x7] = 0b00100100;
    psf[0x8] = 0b01000100;
    psf[0x9] = 0b01111110;
    psf[0xA] = 0b00000100;
    psf[0xB] = 0b00000100;
    psf[0xC] = 0b00000100;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_5(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01111100;
    psf[0x5] = 0b01000000;
    psf[0x6] = 0b01000000;
    psf[0x7] = 0b01111000;
    psf[0x8] = 0b00000100;
    psf[0x9] = 0b00000100;
    psf[0xA] = 0b00000100;
    psf[0xB] = 0b00000100;
    psf[0xC] = 0b01111000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_6(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00001100;
    psf[0x5] = 0b00010000;
    psf[0x6] = 0b00100000;
    psf[0x7] = 0b01000000;
    psf[0x8] = 0b01111100;
    psf[0x9] = 0b01000010;
    psf[0xA] = 0b01000010;
    psf[0xB] = 0b00100100;
    psf[0xC] = 0b00011000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_7(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01111100;
    psf[0x5] = 0b00000100;
    psf[0x6] = 0b00000100;
    psf[0x7] = 0b00001000;
    psf[0x8] = 0b00001000;
    psf[0x9] = 0b00010000;
    psf[0xA] = 0b00010000;
    psf[0xB] = 0b00100000;
    psf[0xC] = 0b00100000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_8(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00111100;
    psf[0x5] = 0b01000010;
    psf[0x6] = 0b01000010;
    psf[0x7] = 0b01000010;
    psf[0x8] = 0b00111100;
    psf[0x9] = 0b01000010;
    psf[0xA] = 0b01000010;
    psf[0xB] = 0b01000010;
    psf[0xC] = 0b00111100;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_9(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00111000;
    psf[0x5] = 0b01000100;
    psf[0x6] = 0b01000100;
    psf[0x7] = 0b01000100;
    psf[0x8] = 0b00111100;
    psf[0x9] = 0b00000100;
    psf[0xA] = 0b00000100;
    psf[0xB] = 0b00001000;
    psf[0xC] = 0b01110000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_A(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00011000;
    psf[0x5] = 0b00011000;
    psf[0x6] = 0b00100100;
    psf[0x7] = 0b00100100;
    psf[0x8] = 0b00100100;
    psf[0x9] = 0b00111100;
    psf[0xA] = 0b01000010;
    psf[0xB] = 0b01000010;
    psf[0xC] = 0b01000010;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_B(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00111100;
    psf[0x5] = 0b01000010;
    psf[0x6] = 0b01000010;
    psf[0x7] = 0b01000010;
    psf[0x8] = 0b01111100;
    psf[0x9] = 0b01000010;
    psf[0xA] = 0b01000010;
    psf[0xB] = 0b01000010;
    psf[0xC] = 0b00111100;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}


uint8_t * pxl_C(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00011110;
    psf[0x5] = 0b00100000;
    psf[0x6] = 0b01000000;
    psf[0x7] = 0b01000000;
    psf[0x8] = 0b01000000;
    psf[0x9] = 0b01000000;
    psf[0xA] = 0b01000000;
    psf[0xB] = 0b00100000;
    psf[0xC] = 0b00011110;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_D(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01111000;
    psf[0x5] = 0b01000100;
    psf[0x6] = 0b01000010;
    psf[0x7] = 0b01000010;
    psf[0x8] = 0b01000010;
    psf[0x9] = 0b01000010;
    psf[0xA] = 0b01000010;
    psf[0xB] = 0b01000100;
    psf[0xC] = 0b00111000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_E(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01111100;
    psf[0x5] = 0b01000000;
    psf[0x6] = 0b01000000;
    psf[0x7] = 0b01000000;
    psf[0x8] = 0b01111000;
    psf[0x9] = 0b01000000;
    psf[0xA] = 0b01000000;
    psf[0xB] = 0b01000000;
    psf[0xC] = 0b01111100;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_F(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01111100;
    psf[0x5] = 0b01000000;
    psf[0x6] = 0b01000000;
    psf[0x7] = 0b01000000;
    psf[0x8] = 0b01111100;
    psf[0x9] = 0b01000000;
    psf[0xA] = 0b01000000;
    psf[0xB] = 0b01000000;
    psf[0xC] = 0b01000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_G(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00011100;
    psf[0x5] = 0b00100010;
    psf[0x6] = 0b01000000;
    psf[0x7] = 0b01000000;
    psf[0x8] = 0b01000000;
    psf[0x9] = 0b01000010;
    psf[0xA] = 0b01000010;
    psf[0xB] = 0b00100010;
    psf[0xC] = 0b00011110;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_H(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01000010;
    psf[0x5] = 0b01000010;
    psf[0x6] = 0b01000010;
    psf[0x7] = 0b01000010;
    psf[0x8] = 0b01111110;
    psf[0x9] = 0b01000010;
    psf[0xA] = 0b01000010;
    psf[0xB] = 0b01000010;
    psf[0xC] = 0b01000010;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_I(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01111100;
    psf[0x5] = 0b00010000;
    psf[0x6] = 0b00010000;
    psf[0x7] = 0b00010000;
    psf[0x8] = 0b00010000;
    psf[0x9] = 0b00010000;
    psf[0xA] = 0b00010000;
    psf[0xB] = 0b00010000;
    psf[0xC] = 0b01111100;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_J(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00111100;
    psf[0x5] = 0b00000100;
    psf[0x6] = 0b00000100;
    psf[0x7] = 0b00000100;
    psf[0x8] = 0b00000100;
    psf[0x9] = 0b00000100;
    psf[0xA] = 0b00000100;
    psf[0xB] = 0b01000100;
    psf[0xC] = 0b00111000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_K(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01000100;
    psf[0x5] = 0b01001000;
    psf[0x6] = 0b01010000;
    psf[0x7] = 0b01100000;
    psf[0x8] = 0b01100000;
    psf[0x9] = 0b01010000;
    psf[0xA] = 0b01001000;
    psf[0xB] = 0b01000100;
    psf[0xC] = 0b01000010;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_L(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01000000;
    psf[0x5] = 0b01000000;
    psf[0x6] = 0b01000000;
    psf[0x7] = 0b01000000;
    psf[0x8] = 0b01000000;
    psf[0x9] = 0b01000000;
    psf[0xA] = 0b01000000;
    psf[0xB] = 0b01000000;
    psf[0xC] = 0b01111110;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_M(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00100100;
    psf[0x5] = 0b01100110;
    psf[0x6] = 0b01011010;
    psf[0x7] = 0b01011010;
    psf[0x8] = 0b01011010;
    psf[0x9] = 0b01000010;
    psf[0xA] = 0b01000010;
    psf[0xB] = 0b01000010;
    psf[0xC] = 0b01000010;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_N(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01000010;
    psf[0x5] = 0b01100010;
    psf[0x6] = 0b01100010;
    psf[0x7] = 0b01010010;
    psf[0x8] = 0b01001010;
    psf[0x9] = 0b01001010;
    psf[0xA] = 0b01000110;
    psf[0xB] = 0b01000110;
    psf[0xC] = 0b01000010;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_O(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00111100;
    psf[0x5] = 0b01000010;
    psf[0x6] = 0b01000010;
    psf[0x7] = 0b01000010;
    psf[0x8] = 0b01000010;
    psf[0x9] = 0b01000010;
    psf[0xA] = 0b01000010;
    psf[0xB] = 0b01000010;
    psf[0xC] = 0b00111100;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_P(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01111100;
    psf[0x5] = 0b01000010;
    psf[0x6] = 0b01000010;
    psf[0x7] = 0b01000010;
    psf[0x8] = 0b01111100;
    psf[0x9] = 0b01000000;
    psf[0xA] = 0b01000000;
    psf[0xB] = 0b01000000;
    psf[0xC] = 0b01000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_Q(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00111100;
    psf[0x5] = 0b01000010;
    psf[0x6] = 0b01000010;
    psf[0x7] = 0b01000010;
    psf[0x8] = 0b01000010;
    psf[0x9] = 0b01000010;
    psf[0xA] = 0b00111100;
    psf[0xB] = 0b00001000;
    psf[0xC] = 0b00000110;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_R(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01111100;
    psf[0x5] = 0b01000010;
    psf[0x6] = 0b01000010;
    psf[0x7] = 0b01000010;
    psf[0x8] = 0b01111100;
    psf[0x9] = 0b01000100;
    psf[0xA] = 0b01000100;
    psf[0xB] = 0b01000010;
    psf[0xC] = 0b01000010;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_S(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00111110;
    psf[0x5] = 0b01000000;
    psf[0x6] = 0b01000000;
    psf[0x7] = 0b01000000;
    psf[0x8] = 0b00111100;
    psf[0x9] = 0b00000010;
    psf[0xA] = 0b00000010;
    psf[0xB] = 0b00000010;
    psf[0xC] = 0b01111100;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_T(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b11111110;
    psf[0x5] = 0b00010000;
    psf[0x6] = 0b00010000;
    psf[0x7] = 0b00010000;
    psf[0x8] = 0b00010000;
    psf[0x9] = 0b00010000;
    psf[0xA] = 0b00010000;
    psf[0xB] = 0b00010000;
    psf[0xC] = 0b00010000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_U(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01000010;
    psf[0x5] = 0b01000010;
    psf[0x6] = 0b01000010;
    psf[0x7] = 0b01000010;
    psf[0x8] = 0b01000010;
    psf[0x9] = 0b01000010;
    psf[0xA] = 0b01000010;
    psf[0xB] = 0b01000010;
    psf[0xC] = 0b00111100;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_V(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01000010;
    psf[0x5] = 0b01000010;
    psf[0x6] = 0b01000010;
    psf[0x7] = 0b00100100;
    psf[0x8] = 0b00100100;
    psf[0x9] = 0b00100100;
    psf[0xA] = 0b00011000;
    psf[0xB] = 0b00011000;
    psf[0xC] = 0b00011000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_W(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01000010;
    psf[0x5] = 0b01000010;
    psf[0x6] = 0b01000010;
    psf[0x7] = 0b01000010;
    psf[0x8] = 0b01011010;
    psf[0x9] = 0b01101010;
    psf[0xA] = 0b01100110;
    psf[0xB] = 0b01000010;
    psf[0xC] = 0b01000010;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_X(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01000010;
    psf[0x5] = 0b00100100;
    psf[0x6] = 0b00100100;
    psf[0x7] = 0b00011000;
    psf[0x8] = 0b00011000;
    psf[0x9] = 0b00100100;
    psf[0xA] = 0b00100100;
    psf[0xB] = 0b01000010;
    psf[0xC] = 0b01000010;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_Y(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b10000010;
    psf[0x5] = 0b01000100;
    psf[0x6] = 0b01000100;
    psf[0x7] = 0b00101000;
    psf[0x8] = 0b00010000;
    psf[0x9] = 0b00010000;
    psf[0xA] = 0b00010000;
    psf[0xB] = 0b00010000;
    psf[0xC] = 0b00010000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_Z(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01111110;
    psf[0x5] = 0b00000100;
    psf[0x6] = 0b00001000;
    psf[0x7] = 0b00001000;
    psf[0x8] = 0b00010000;
    psf[0x9] = 0b00010000;
    psf[0xA] = 0b00100000;
    psf[0xB] = 0b00100000;
    psf[0xC] = 0b01111110;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_exclaim(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00010000;
    psf[0x5] = 0b00010000;
    psf[0x6] = 0b00010000;
    psf[0x7] = 0b00010000;
    psf[0x8] = 0b00010000;
    psf[0x9] = 0b00000000;
    psf[0xA] = 0b00000000;
    psf[0xB] = 0b00000000;
    psf[0xC] = 0b00010000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_dquote(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00101000;
    psf[0x5] = 0b00101000;
    psf[0x6] = 0b00101000;
    psf[0x7] = 0b00000000;
    psf[0x8] = 0b00000000;
    psf[0x9] = 0b00000000;
    psf[0xA] = 0b00000000;
    psf[0xB] = 0b00000000;
    psf[0xC] = 0b00000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_dollar(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00001000;
    psf[0x4] = 0b00111110;
    psf[0x5] = 0b01000000;
    psf[0x6] = 0b01000000;
    psf[0x7] = 0b01000000;
    psf[0x8] = 0b00111100;
    psf[0x9] = 0b00000010;
    psf[0xA] = 0b00000010;
    psf[0xB] = 0b00000010;
    psf[0xC] = 0b01111100;
    psf[0xD] = 0b00010000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_percent(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01110010;
    psf[0x5] = 0b01010100;
    psf[0x6] = 0b01011000;
    psf[0x7] = 0b01111000;
    psf[0x8] = 0b00011000;
    psf[0x9] = 0b00011110;
    psf[0xA] = 0b00011010;
    psf[0xB] = 0b00101010;
    psf[0xC] = 0b01001110;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_ampersand(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00011000;
    psf[0x5] = 0b00100100;
    psf[0x6] = 0b00100100;
    psf[0x7] = 0b00111000;
    psf[0x8] = 0b00111010;
    psf[0x9] = 0b01001100;
    psf[0xA] = 0b01000100;
    psf[0xB] = 0b01000100;
    psf[0xC] = 0b00111010;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_squote(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00010000;
    psf[0x5] = 0b00010000;
    psf[0x6] = 0b00010000;
    psf[0x7] = 0b00000000;
    psf[0x8] = 0b00000000;
    psf[0x9] = 0b00000000;
    psf[0xA] = 0b00000000;
    psf[0xB] = 0b00000000;
    psf[0xC] = 0b00000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_openparen(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00001000;
    psf[0x5] = 0b00010000;
    psf[0x6] = 0b00100000;
    psf[0x7] = 0b01000000;
    psf[0x8] = 0b01000000;
    psf[0x9] = 0b01000000;
    psf[0xA] = 0b00100000;
    psf[0xB] = 0b00010000;
    psf[0xC] = 0b00001000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_closeparen(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00010000;
    psf[0x5] = 0b00001000;
    psf[0x6] = 0b00000100;
    psf[0x7] = 0b00000010;
    psf[0x8] = 0b00000010;
    psf[0x9] = 0b00000010;
    psf[0xA] = 0b00000100;
    psf[0xB] = 0b00001000;
    psf[0xC] = 0b00010000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_asterisk(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00010000;
    psf[0x5] = 0b01111100;
    psf[0x6] = 0b00010000;
    psf[0x7] = 0b00101000;
    psf[0x8] = 0b00101000;
    psf[0x9] = 0b00000000;
    psf[0xA] = 0b00000000;
    psf[0xB] = 0b00000000;
    psf[0xC] = 0b00000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_plus(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00000000;
    psf[0x5] = 0b00000000;
    psf[0x6] = 0b00010000;
    psf[0x7] = 0b00010000;
    psf[0x8] = 0b01111100;
    psf[0x9] = 0b00010000;
    psf[0xA] = 0b00010000;
    psf[0xB] = 0b00000000;
    psf[0xC] = 0b00000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_comma(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00000000;
    psf[0x5] = 0b00000000;
    psf[0x6] = 0b00000000;
    psf[0x7] = 0b00000000;
    psf[0x8] = 0b00000000;
    psf[0x9] = 0b00000000;
    psf[0xA] = 0b00010000;
    psf[0xB] = 0b00010000;
    psf[0xC] = 0b00100000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_minus(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00000000;
    psf[0x5] = 0b00000000;
    psf[0x6] = 0b00000000;
    psf[0x7] = 0b00111100;
    psf[0x8] = 0b00000000;
    psf[0x9] = 0b00000000;
    psf[0xA] = 0b00000000;
    psf[0xB] = 0b00000000;
    psf[0xC] = 0b00000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_dot(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00000000;
    psf[0x5] = 0b00000000;
    psf[0x6] = 0b00000000;
    psf[0x7] = 0b00000000;
    psf[0x8] = 0b00000000;
    psf[0x9] = 0b00000000;
    psf[0xA] = 0b00000000;
    psf[0xB] = 0b00000000;
    psf[0xC] = 0b00010000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_colon(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00000000;
    psf[0x5] = 0b00000000;
    psf[0x6] = 0b00000000;
    psf[0x7] = 0b00000000;
    psf[0x8] = 0b00010000;
    psf[0x9] = 0b00000000;
    psf[0xA] = 0b00010000;
    psf[0xB] = 0b00000000;
    psf[0xC] = 0b00000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_semicolon(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00000000;
    psf[0x5] = 0b00000000;
    psf[0x6] = 0b00000000;
    psf[0x7] = 0b00010000;
    psf[0x8] = 0b00000000;
    psf[0x9] = 0b00000000;
    psf[0xA] = 0b00010000;
    psf[0xB] = 0b00010000;
    psf[0xC] = 0b00100000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_lt(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00000100;
    psf[0x5] = 0b00001000;
    psf[0x6] = 0b00010000;
    psf[0x7] = 0b00100000;
    psf[0x8] = 0b01000000;
    psf[0x9] = 0b00100000;
    psf[0xA] = 0b00010000;
    psf[0xB] = 0b00001000;
    psf[0xC] = 0b00000100;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_gt(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01000000;
    psf[0x5] = 0b00100000;
    psf[0x6] = 0b00010000;
    psf[0x7] = 0b00001000;
    psf[0x8] = 0b00000100;
    psf[0x9] = 0b00001000;
    psf[0xA] = 0b00010000;
    psf[0xB] = 0b00100000;
    psf[0xC] = 0b01000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_eq(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00000000;
    psf[0x5] = 0b00000000;
    psf[0x6] = 0b00000000;
    psf[0x7] = 0b01111100;
    psf[0x8] = 0b00000000;
    psf[0x9] = 0b00000000;
    psf[0xA] = 0b01111100;
    psf[0xB] = 0b00000000;
    psf[0xC] = 0b00000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_qmark(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01110000;
    psf[0x5] = 0b00001000;
    psf[0x6] = 0b00000100;
    psf[0x7] = 0b00001000;
    psf[0x8] = 0b00010000;
    psf[0x9] = 0b00100000;
    psf[0xA] = 0b00000000;
    psf[0xB] = 0b00000000;
    psf[0xC] = 0b00100000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_at(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00011100;
    psf[0x5] = 0b00100010;
    psf[0x6] = 0b01000110;
    psf[0x7] = 0b01001010;
    psf[0x8] = 0b01001010;
    psf[0x9] = 0b01001010;
    psf[0xA] = 0b01000110;
    psf[0xB] = 0b00100000;
    psf[0xC] = 0b00011000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_openbrkt(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01111000;
    psf[0x5] = 0b01000000;
    psf[0x6] = 0b01000000;
    psf[0x7] = 0b01000000;
    psf[0x8] = 0b01000000;
    psf[0x9] = 0b01000000;
    psf[0xA] = 0b01000000;
    psf[0xB] = 0b01000000;
    psf[0xC] = 0b01111000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_closebrkt(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01111000;
    psf[0x5] = 0b00001000;
    psf[0x6] = 0b00001000;
    psf[0x7] = 0b00001000;
    psf[0x8] = 0b00001000;
    psf[0x9] = 0b00001000;
    psf[0xA] = 0b00001000;
    psf[0xB] = 0b00001000;
    psf[0xC] = 0b01111000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_fslash(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x3] = 0b00000100;
    psf[0x4] = 0b00001000;
    psf[0x5] = 0b00001000;
    psf[0x6] = 0b00010000;
    psf[0x7] = 0b00010000;
    psf[0x8] = 0b00100000;
    psf[0x9] = 0b00100000;
    psf[0xA] = 0b01000000;
    psf[0xB] = 0b01000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_bslash(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01000000;
    psf[0x5] = 0b00100000;
    psf[0x6] = 0b00100000;
    psf[0x7] = 0b00010000;
    psf[0x8] = 0b00010000;
    psf[0x9] = 0b00001000;
    psf[0xA] = 0b00001000;
    psf[0xB] = 0b00000100;
    psf[0xC] = 0b00000100;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_caret(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00010000;
    psf[0x5] = 0b00101000;
    psf[0x6] = 0b00101000;
    psf[0x7] = 0b01000100;
    psf[0x8] = 0b00000000;
    psf[0x9] = 0b00000000;
    psf[0xA] = 0b00000000;
    psf[0xB] = 0b00000000;
    psf[0xC] = 0b00000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_underscore(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00000000;
    psf[0x5] = 0b00000000;
    psf[0x6] = 0b00000000;
    psf[0x7] = 0b00000000;
    psf[0x8] = 0b00000000;
    psf[0x9] = 0b00000000;
    psf[0xA] = 0b00000000;
    psf[0xB] = 0b00000000;
    psf[0xC] = 0b01111110;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_backtick(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01000000;
    psf[0x5] = 0b00100000;
    psf[0x6] = 0b00000000;
    psf[0x7] = 0b00000000;
    psf[0x8] = 0b00000000;
    psf[0x9] = 0b00000000;
    psf[0xA] = 0b00000000;
    psf[0xB] = 0b00000000;
    psf[0xC] = 0b00000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_opencurly(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00011000;
    psf[0x5] = 0b00100000;
    psf[0x6] = 0b00100000;
    psf[0x7] = 0b00100000;
    psf[0x8] = 0b01000000;
    psf[0x9] = 0b00100000;
    psf[0xA] = 0b00100000;
    psf[0xB] = 0b00100000;
    psf[0xC] = 0b00011000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_closecurly(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b01100000;
    psf[0x5] = 0b00010000;
    psf[0x6] = 0b00010000;
    psf[0x7] = 0b00010000;
    psf[0x8] = 0b00001000;
    psf[0x9] = 0b00010000;
    psf[0xA] = 0b00010000;
    psf[0xB] = 0b00010000;
    psf[0xC] = 0b01100000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_pipe(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00010000;
    psf[0x5] = 0b00010000;
    psf[0x6] = 0b00010000;
    psf[0x7] = 0b00010000;
    psf[0x8] = 0b00010000;
    psf[0x9] = 0b00010000;
    psf[0xA] = 0b00010000;
    psf[0xB] = 0b00010000;
    psf[0xC] = 0b00010000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_tilde(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00000000;
    psf[0x5] = 0b00000000;
    psf[0x6] = 0b00000000;
    psf[0x7] = 0b00000000;
    psf[0x8] = 0b00110010;
    psf[0x9] = 0b01001100;
    psf[0xA] = 0b00000000;
    psf[0xB] = 0b00000000;
    psf[0xC] = 0b00000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

uint8_t * pxl_box(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00111100;
    psf[0x5] = 0b00100100;
    psf[0x6] = 0b00100100;
    psf[0x7] = 0b00100100;
    psf[0x8] = 0b00100100;
    psf[0x9] = 0b00100100;
    psf[0xA] = 0b00100100;
    psf[0xB] = 0b00100100;
    psf[0xC] = 0b00111100;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

#endif