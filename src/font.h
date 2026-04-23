#ifndef __FONT_
#define __FONT_

#include "stdint.h"
#include "string.h"

typedef struct{
  uint8_t h;
  uint8_t w;
  uint8_t* chars;
}ASCIIFont;

extern const ASCIIFont Font_6x8;
extern const ASCIIFont Font_6x12;
extern const ASCIIFont Font_8x16;

#endif
