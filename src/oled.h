#ifndef _OLED_H_
#define _OLED_H_

#include <stdint.h> // for uint8_t
#include <stddef.h> // for size_t
#include "font.h"

#define OLED_LENTH (128)
#define OLED_WIDTH (64)

typedef struct{
uint8_t* Image;
int Lenth;
int Width;
uint8_t color; // 0: Black 1: White 2: Inverse
const ASCIIFont* font;
}Screen;

extern Screen g_screen;

void OLED_Init(void);
void OLED_Sendbuffer(Screen* screen);
void OLED_Clearbuffer(Screen* screen);
int OLED_Read_Pixel(Screen* screen,int x,int y);
void OLED_Draw_Pixel(Screen* screen,int x,int y);
void OLED_Copy_Block(Screen* screen,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);
void OLED_Draw_Line(Screen* screen,int x1,int y1,int x2,int y2);
void OLED_Draw_Filled_Rectangle(Screen* screen,int x1,int y1,int x2,int y2);
void OLED_Draw_Rectangle(Screen* screen,int x1,int y1,int x2,int y2);
void OLED_Draw_Triangle(Screen* screen,int x1,int y1,int x2,int y2,int x3,int y3);
void OLED_Draw_Filled_Triangle(Screen* screen,int x1,int y1,int x2,int y2,int x3,int y3);
void OLED_Draw_Circle(Screen* screen,int x,int y,int r);
void OLED_Draw_Filled_Circle(Screen* screen,int x,int y,int r);
void OLED_Draw_ASCII(Screen* screen,int x,int y,char c);
void OLED_Draw_String(Screen* screen,int x,int y,char* str);
void OLED_Set_Font(Screen* screen,const ASCIIFont* font);
void OLED_Set_Color(Screen* screen,uint8_t color);




#endif
	
