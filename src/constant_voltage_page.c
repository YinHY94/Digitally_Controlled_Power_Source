#include "page.h"
#include "ina226.h"
#include "output_control.h"
#include "oled.h"
#include <stdio.h>
#include "pid_control.h"

page constant_votage_page;


void constant_votage_page_update_ui(){
OLED_Clearbuffer(&g_screen);
OLED_Set_Font(&g_screen,&Font_6x8);
char buf[50];
sprintf(buf,"Constant Votage Mode");
OLED_Draw_String(&g_screen,0,0,buf);
sprintf(buf,"Target Voltage:%.2fV",constant_votage_page.pid->Target);
OLED_Draw_String(&g_screen,0,8,buf);
sprintf(buf,"Current Vol:%.3fV",current_data.voltage);
OLED_Draw_String(&g_screen,0,24,buf);
if(current_data.current<=0.00f&&current_data.current>-0.001f){
    sprintf(buf,"Current Cur:0.000A");
}else
    sprintf(buf,"Current Cur:%.3fA",current_data.current);
OLED_Draw_String(&g_screen,0,32,buf);
if(current_data.power<=0.00f&&current_data.power>-0.001f){
    sprintf(buf,"Current Power:0.000W");
}else
    sprintf(buf,"Current Power:%.3fW",current_data.power);
OLED_Draw_String(&g_screen,0,40,buf);
if(output_state)
    OLED_Draw_String(&g_screen,0,48,"Output: ON");
else
    OLED_Draw_String(&g_screen,0,48,"Output: OFF");
OLED_Sendbuffer(&g_screen);
};


void constant_votage_page_init(){
    constant_votage_page.current_num=0;
    constant_votage_page.item=NULL;
    constant_votage_page.item_num=0;
    constant_votage_page.key_handlers[KEY_X3Y1].on_pressed=route_to_menu;
    constant_votage_page.key_handlers[KEY_X3Y3].on_pressed=Output_Start;
    constant_votage_page.key_handlers[KEY_X3Y2].on_pressed=Output_Stop;
    constant_votage_page.key_handlers[KEY_X3Y0].on_pressed=set_data;
    constant_votage_page.update_ui=constant_votage_page_update_ui;
    constant_votage_page.pid=&Voltage_PID;
}


