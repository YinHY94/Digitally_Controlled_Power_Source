#include <oled.h>
#include <main.h>
#include <spi.h>
#include <string.h>

#define OLED_SPI hspi1

uint8_t buffer[1024];

Screen screen={
.Image=buffer,
.Lenth=OLED_LENTH,
.Width=OLED_WIDTH/8,	
.color=1,
.font=&Font_6x8,
};

static void OLED_Reset(void)
{
    HAL_GPIO_WritePin(OLED_RESET_GPIO_Port, OLED_RESET_Pin, GPIO_PIN_RESET);
    HAL_Delay(10-1);
    HAL_GPIO_WritePin(OLED_RESET_GPIO_Port, OLED_RESET_Pin, GPIO_PIN_SET);
    HAL_Delay(10-1);
}

static void OLED_Command(uint8_t byte)
{
    HAL_GPIO_WritePin(OLED_DATA_CMD_GPIO_Port, OLED_DATA_CMD_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&OLED_SPI, (uint8_t *)&byte, 1, HAL_MAX_DELAY);
}

static void OLED_Data(uint8_t *buffer, size_t buff_size)
{
    HAL_GPIO_WritePin(OLED_DATA_CMD_GPIO_Port, OLED_DATA_CMD_Pin, GPIO_PIN_SET);
    HAL_SPI_Transmit(&OLED_SPI, buffer, buff_size, HAL_MAX_DELAY);
}

int Get_Triangle_Area(int x1,int y1,int x2,int y2,int x3,int y3){
return x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2);
}

void OLED_Init(void)
{
    // Reset OLED
    OLED_Reset();

    // Wait for the screen to boot
    HAL_Delay(100);

    // Init OLED
    OLED_Command(0xAE); // Display off

    OLED_Command(0x20); // Set Memory Addressing Mode
    // 0b00: Horizontal Addressing Mode
    // 0b01: Vertical Addressing Mode
    // 0b10: Page Addressing Mode (RESET)
    // 0b11: Invalid
    OLED_Command(0x00);

    OLED_Command(0xC8); // Set COM Output Scan Direction

    OLED_Command(0x21); // Setup column start and end address
    OLED_Command(0);
    OLED_Command(127);

    OLED_Command(0x22); // Setup page start and end address
    OLED_Command(0);
    OLED_Command(7);

    OLED_Command(0x40); // Set start line address

    OLED_Command(0x81); // Set contrast
    OLED_Command(0xFF);

    OLED_Command(0xA1); // Set segment re-map 0 to 127

    // OLED_Command(0xA7); // Set inverse color
    OLED_Command(0xA6); // Set normal color

    OLED_Command(0xA8); // Set multiplex ratio.
    OLED_Command(0x3F);

    OLED_Command(0xA4); // 0xa4,Output follows RAM content

    OLED_Command(0xD3); // Set display offset
    OLED_Command(0x00); // --- not offset

    OLED_Command(0xD5); // Set display clock divide ratio/oscillator frequency
    OLED_Command(0xF0); // Set divide ratio

    OLED_Command(0xD9); // Set pre-charge period
    OLED_Command(0x22);

    OLED_Command(0xDA); // Set com pins hardware configuration
    OLED_Command(0x12);

    OLED_Command(0xDB); // Set vcomh
    OLED_Command(0x20); // 0x20,0.77xVcc

    OLED_Command(0x8D); // Set DC-DC enable
    OLED_Command(0x14);
    OLED_Command(0xAF); // Display on
}

void OLED_Sendbuffer(Screen* screen)
{	size_t Image_size=(size_t)(screen->Lenth*screen->Width);
    OLED_Command(0x21); // Setup column start and end address
    OLED_Command(0);
    OLED_Command(127);
    OLED_Command(0x22); // Setup page start and end address
    OLED_Command(0);
    OLED_Command(7);
    OLED_Data(screen->Image, Image_size);
}

void OLED_Clearbuffer(Screen* screen){
memset(screen->Image, 0, (size_t)(screen->Lenth*screen->Width));
}

void OLED_Draw_Pixel(Screen* screen, int x, int y){
if(x>=0&&x<screen->Lenth&&y>=0&&y<screen->Width*8){
  if(screen->color==1){
    x+=screen->Lenth*(y/8);
    screen->Image[x]=(1<<(y%8))|screen->Image[x];
  }else if(screen->color==0){
    x+=screen->Lenth*(y/8);
    screen->Image[x]=(0xff-(1<<(y%8)))&screen->Image[x];}
  else{
    x+=screen->Lenth*(y/8);
    screen->Image[x]=(1<<(y%8))^screen->Image[x];}
  }
}

int OLED_Read_Pixel(Screen* screen,int x,int y){
if(x>=0&&x<screen->Lenth&&y>=0&&y<screen->Width*8){
x+=screen->Lenth*(y/8);
return ((1<<(y%8))&screen->Image[x])!=0;}
else return -1;
}
/*void OLED_Draw_Line(Screen* screen, int x1, int y1, int x2, int y2){
int i,x,y,m,n,sign1,sign2;
m=y1>y2?(y1-y2):(y2-y1);
n=x1>x2?(x1-x2):(x2-x1);
if(m==0)
sign1=0;
else if(((int)y2-(int)y1)>0)
sign1=1;
else 
sign1=-1;
if(n==0)
sign2=0;
else if(((int)x2-(int)x1)>0)
sign2=1;
else 
sign2=-1;
if (m!=0||n!=0){
if(m>=n){
	for(i=0;i<=m;i++){
	x=x1+sign2*(int)(i*n*1.0/m+0.5);
	y=y1+sign1*i;
	OLED_Draw_Pixel(screen,x,y);
	}
}else{
	for(i=0;i<=n;i++){
	x=x1+sign2*i;
	y=y1+sign1*(int)(i*m*1.0/n+0.5);
	OLED_Draw_Pixel(screen,( int)x,( int)y);	
	}
}
}
}*/
void OLED_Draw_Line(Screen* screen, int x1, int y1, int x2, int y2){
 static uint8_t temp = 0;
  if (x1 == x2) {
    if (y1 > y2) {
      temp = y1;
      y1 = y2;
      y2 = temp;
    }
    for (uint8_t y = y1; y <= y2; y++) {
      OLED_Draw_Pixel(screen,x1,y);
    }
  } else if (y1 == y2) {
    if (x1 > x2) {
      temp = x1;
      x1 = x2;
      x2 = temp;
    }
    for (uint8_t x = x1; x <= x2; x++) {
      OLED_Draw_Pixel(screen,x,y1);
    }
  } else {
    // Bresenham直线算法
	int16_t dx =x2-x1;
    int16_t dy =y2-y1;
    int16_t ux = ((dx > 0) << 1) - 1;
    int16_t uy = ((dy > 0) << 1) - 1;
	dx =x1>x2?x1-x2:x2-x1;
	dy =y1>y2?y1-y2:y2-y1;
    int16_t x = x1, y = y1, eps = 0;
    if (dx > dy) {
      for (x = x1; x != x2; x += ux) {
        OLED_Draw_Pixel(screen,x,y);
        eps += dy;
        if ((eps << 1) >= dx) {
          y += uy;
          eps -= dx;
        }
      }
    } else {
      for (y = y1; y != y2; y += uy) {
        OLED_Draw_Pixel(screen,x,y);
        eps += dx;
        if ((eps << 1) >= dy) {
          x += ux;
          eps -= dy;
        }
      }
    }
  }
}



void OLED_Draw_Filled_Rectangle(Screen* screen, int x1, int y1, int x2, int y2){
int i,j;
for(i=x1;i<=x2;i++)
for(j=y1;j<=y2;j++)
OLED_Draw_Pixel(screen,i,j);
}

void OLED_Draw_Rectangle(Screen* screen, int x1, int y1, int x2, int y2){
OLED_Draw_Line(screen,x1,y1,x2,y1);
OLED_Draw_Line(screen,x1,y2,x2,y2);
OLED_Draw_Line(screen,x1,y1,x1,y2);
OLED_Draw_Line(screen,x2,y1,x2,y2);
}


void OLED_Draw_Triangle(Screen* screen, int x1, int y1, int x2, int y2, int x3, int y3){
OLED_Draw_Line(screen,x1,y1,x2,y2);
OLED_Draw_Line(screen,x3,y3,x2,y2);
OLED_Draw_Line(screen,x1,y1,x3,y3);
}

void OLED_Draw_Circle(Screen* screen, int x, int y, int r){
  int16_t a=0,b=r,di=3-(r<<1);
  while(a<=b){
    OLED_Draw_Pixel(screen,x-b,y-a);
    OLED_Draw_Pixel(screen,x+b,y-a);
    OLED_Draw_Pixel(screen,x-a,y+b);
    OLED_Draw_Pixel(screen,x-b,y-a);
    OLED_Draw_Pixel(screen,x-a,y-b);
    OLED_Draw_Pixel(screen,x+b,y+a);
    OLED_Draw_Pixel(screen,x+a,y-b);
    OLED_Draw_Pixel(screen,x+a,y+b);
    OLED_Draw_Pixel(screen,x-b,y+a);
    a++;
    if(di<0)
      di += 4*a+6;
    else{
      di+=10+4*(a - b);
      b--;
    }
    OLED_Draw_Pixel(screen,x+a,y+b);
  }
}

void OLED_Draw_Filled_Circle(Screen* screen, int x, int y, int r){
  int16_t a=0,b=r,di=3-(r<<1),i;
  while(a<=b){
    for (i=x-b;i<=x+b;i++){
      OLED_Draw_Pixel(screen,i,y+a);
      OLED_Draw_Pixel(screen,i,y-a);
    }
    for (i=x-a;i<=x+a;i++){
      OLED_Draw_Pixel(screen,i,y+b);
      OLED_Draw_Pixel(screen,i,y-b);
    }
    a++;
    if(di<0)
      di+=4*a+6;
    else{
      di+=10+4*(a-b);
      b--;
    }
  }
}

void OLED_Draw_ASCII(Screen* screen, int x, int y,char c){
int i,j;
uint8_t current_color=screen->color;
for(i=0;i<(screen->font->h+7)/8*screen->font->w;i++){
  char Byte=screen->font->chars[(c-32)*((screen->font->h+7)/8*screen->font->w)+i];
  for(j=0;j<8;j++){
    if(current_color==0||current_color==1){
      if(Byte&(1<<j)){
        screen->color=current_color;
	      OLED_Draw_Pixel(screen,x+i%screen->font->w,y+j+i/screen->font->w*8);
      }
      else{
        screen->color=1-current_color;
	      OLED_Draw_Pixel(screen,x+i%screen->font->w,y+j+i/screen->font->w*8);
      }
    }
    else{
      if(Byte&(1<<j)){
	      OLED_Draw_Pixel(screen,x+i%screen->font->w,y+j+i/screen->font->w*8);}
    }
  }
}
screen->color=current_color;
}

void OLED_Draw_String(Screen* screen, int x, int y,char* str){
int i=0;
while(str[i]){
OLED_Draw_ASCII(screen,x+i*screen->font->w,y,str[i]);
i++;}
}

void OLED_Copy_Block(Screen* screen,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){
int i,j,m=y2-y1,n=x2-x1;
uint8_t current_color=screen->color;
if(x2-x1==x4-x3&&y2-y1==y4-y3&&x1<x2&&x3<x4&&y1<y2&&y3<y4){
  for(i=0;i<n;i++)
    for(j=0;j<m;j++){
      screen->color=OLED_Read_Pixel(screen,x3+i,y3+j);
      OLED_Draw_Pixel(screen,x1+i,y1+j);
    }
}
screen->color=current_color;
}



// void OLED_Draw_Filled_Triangle(Screen* screen, int x1, int y1, int x2, int y2, int x3, int y3){
// int i,j,max_x,max_y,min_x,min_y;
// if(x1>x2){
// 	if(x1>x3) max_x=x1;
// 	else max_x=x3;
// 	if(x2<x3) min_x=x2;
// 	else min_x=x3;}
// else{
// 	if(x2>x3) max_x=x2;
// 	else max_x=x3;
// 	if(x1<x3) min_x=x1;
// 	else min_x=x3;}

// if(y1>y2){
// 	if(y1>y3) max_y=y1;
// 	else max_y=y3;
// 	if(y2<y3) min_y=y2;
// 	else min_y=y3;}
// else{
// 	if(y2>y3) max_y=y2;
// 	else max_y=y3;
// 	if(y1<y3) min_y=y1;
// 	else min_y=y3;}

// for(i=min_x;i<max_x;i++)
// for(j=min_y;j<max_y;j++){
// int s1=Get_Triangle_Area(x1,y1,x2,y2,i,j);
// int s2=Get_Triangle_Area(x2,y2,x3,y3,i,j);
// int s3=Get_Triangle_Area(x3,y3,x1,y1,i,j);
// if(s1==0||s2==0||s3==0)
// 	OLED_Draw_Pixel(screen,i,j);
// if((s1>0&&s2>0&&s3>0)||(s1<0&&s2<0&&s3<0))
// 	OLED_Draw_Pixel(screen,i,j);
// }
// OLED_Draw_Triangle(screen,x1,y1,x2,y2,x3,y3);
// }

void OLED_Draw_Filled_Triangle(Screen* screen,int x1,int y1,int x2,int y2,int x3,int y3){
    int max_x,max_y,min_x,min_y,s1,s2,s3;
    if(x1>x2){
        if(x1>x3) max_x=x1;
        else max_x=x3;
        if(x2<x3) min_x=x2;
        else min_x=x3;}
    else{
        if(x2>x3) max_x=x2;
        else max_x=x3;
        if(x1<x3) min_x=x1;
        else min_x=x3;}

    if(y1>y2){
        if(y1>y3) max_y=y1;
        else max_y=y3;
        if(y2<y3) min_y=y2;
        else min_y=y3;}
    else{
        if(y2>y3) max_y=y2;
        else max_y=y3;
        if(y1<y3) min_y=y1;
        else min_y=y3;}

    for(int16_t i = min_x;i<max_x;i++)
        for(int16_t j = min_y;j<max_y;j++){
             s1=Get_Triangle_Area(x1,y1,x2,y2,i,j);
             s2=Get_Triangle_Area(x2,y2,x3,y3,i,j);
             s3=Get_Triangle_Area(x3,y3,x1,y1,i,j);
            if(s1==0||s2==0||s3==0)
              OLED_Draw_Pixel(screen,i,j);
            if(s1+s2+s3<=Get_Triangle_Area(x1,y1,x2,y2,x3,y3))
              OLED_Draw_Pixel(screen,i,j);
        }
    OLED_Draw_Triangle(screen,x1,y1,x2,y2,x3,y3);
}

void OLED_Set_Font(Screen* screen, const ASCIIFont* font){
screen->font=font;
} 

void OLED_Set_Color(Screen* screen, uint8_t color){
screen->color=color;
}
