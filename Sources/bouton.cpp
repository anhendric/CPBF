
#include "peg.hpp"
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

ROMDATA UCHAR ucboutonBitmap[42] = {
0x00,0x00,0x00,0x3f,0xff,0x80,0x3f,0xff,0x80,0x20,0x00,0x80,0x2f,0xfe,0x80,0x20,
0x00,0x80,0x2f,0xfe,0x80,0x20,0x00,0x80,0x2e,0xa0,0x80,0x20,0x00,0x80,0x20,0x00,
0x80,0x3f,0xff,0x80,0x00,0x00,0x00,0x00,0x00,0x00,};
PegBitmap gbboutonBitmap = { 0x00, 1, 19, 14, 0x000000ff, (UCHAR *) ucboutonBitmap};

