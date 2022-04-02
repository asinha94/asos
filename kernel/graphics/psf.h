#ifndef ASOS_PSF_H
#define ASOS_PSF_H

#include <libk/kmalloc.h>
#include <stdint.h>

#define PXL_WIDTH  8
#define PXL_HEIGHT 16

void pxl_space(uint8_t * psf)
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
    psf[0xC] = 0b00000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

void pxl_0(uint8_t * psf)
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

void pxl_1(uint8_t * psf)
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

void pxl_2(uint8_t * psf)
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

void pxl_3(uint8_t * psf)
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

void pxl_4(uint8_t * psf)
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

void pxl_5(uint8_t * psf)
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

void pxl_6(uint8_t * psf)
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

void pxl_7(uint8_t * psf)
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

void pxl_8(uint8_t * psf)
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

void pxl_9(uint8_t * psf)
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

void pxl_A(uint8_t * psf)
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

void pxl_B(uint8_t * psf)
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


void pxl_C(uint8_t * psf)
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

void pxl_D(uint8_t * psf)
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

void pxl_E(uint8_t * psf)
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

void pxl_F(uint8_t * psf)
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

void pxl_G(uint8_t * psf)
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

void pxl_H(uint8_t * psf)
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

void pxl_I(uint8_t * psf)
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

void pxl_J(uint8_t * psf)
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

void pxl_K(uint8_t * psf)
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

void pxl_L(uint8_t * psf)
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

void pxl_M(uint8_t * psf)
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

void pxl_N(uint8_t * psf)
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

void pxl_O(uint8_t * psf)
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

void pxl_P(uint8_t * psf)
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

void pxl_Q(uint8_t * psf)
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

void pxl_R(uint8_t * psf)
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

void pxl_S(uint8_t * psf)
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

void pxl_T(uint8_t * psf)
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

void pxl_U(uint8_t * psf)
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

void pxl_V(uint8_t * psf)
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

void pxl_W(uint8_t * psf)
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

void pxl_X(uint8_t * psf)
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

void pxl_Y(uint8_t * psf)
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

void pxl_Z(uint8_t * psf)
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

void pxl_exclaim(uint8_t * psf)
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

void pxl_hash(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00001010;
    psf[0x5] = 0b00010100;
    psf[0x6] = 0b01111110;
    psf[0x7] = 0b00010100;
    psf[0x8] = 0b00101000;
    psf[0x9] = 0b01111110;
    psf[0xA] = 0b00101000;
    psf[0xB] = 0b01010000;
    psf[0xC] = 0b00000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

void pxl_dquote(uint8_t * psf)
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

void pxl_dollar(uint8_t * psf)
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

void pxl_percent(uint8_t * psf)
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

void pxl_ampersand(uint8_t * psf)
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

void pxl_squote(uint8_t * psf)
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

void pxl_openparen(uint8_t * psf)
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

void pxl_closeparen(uint8_t * psf)
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

void pxl_asterisk(uint8_t * psf)
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

void pxl_plus(uint8_t * psf)
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

void pxl_comma(uint8_t * psf)
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

void pxl_minus(uint8_t * psf)
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

void pxl_dot(uint8_t * psf)
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

void pxl_colon(uint8_t * psf)
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
    psf[0xB] = 0b00000000;
    psf[0xC] = 0b00000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

void pxl_semicolon(uint8_t * psf)
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

void pxl_lt(uint8_t * psf)
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

void pxl_gt(uint8_t * psf)
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

void pxl_eq(uint8_t * psf)
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

void pxl_qmark(uint8_t * psf)
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

void pxl_at(uint8_t * psf)
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

void pxl_openbrkt(uint8_t * psf)
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

void pxl_closebrkt(uint8_t * psf)
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

void pxl_fslash(uint8_t * psf)
{
    // 4 empty lines on top, 3 on the botom
    psf[0x0] = 0b00000000;
    psf[0x1] = 0b00000000;
    psf[0x2] = 0b00000000;
    psf[0x3] = 0b00000000;
    psf[0x4] = 0b00000100;
    psf[0x5] = 0b00001000;
    psf[0x6] = 0b00001000;
    psf[0x7] = 0b00010000;
    psf[0x8] = 0b00010000;
    psf[0x9] = 0b00100000;
    psf[0xA] = 0b00100000;
    psf[0xB] = 0b01000000;
    psf[0xC] = 0b01000000;
    psf[0xD] = 0b00000000;
    psf[0xE] = 0b00000000;
    psf[0xF] = 0b00000000;
    return psf;
}

void pxl_bslash(uint8_t * psf)
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

void pxl_caret(uint8_t * psf)
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

void pxl_underscore(uint8_t * psf)
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

void pxl_backtick(uint8_t * psf)
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

void pxl_opencurly(uint8_t * psf)
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

void pxl_closecurly(uint8_t * psf)
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

void pxl_pipe(uint8_t * psf)
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

void pxl_tilde(uint8_t * psf)
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

void pxl_box(uint8_t * psf)
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