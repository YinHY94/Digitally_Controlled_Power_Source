#include "page.h"
#include "oled.h"
#include <stdio.h>
#include "math.h"

page input_page;
char input_buffer[6];
uint8_t input_index=0;
uint8_t dot_index=255;

void input_page_update_ui(){   
    OLED_Set_Font(&screen,&Font_6x8); 
    if(input_page.parent==&constant_votage_page){
        OLED_Draw_Filled_Rectangle(&screen,90,8,119,15);
        OLED_Set_Color(&screen,0);
        OLED_Draw_String(&screen,90,8,input_buffer);
        OLED_Draw_ASCII(&screen,120,8,'V');
    }
    else if(input_page.parent==&constant_current_page){
        OLED_Draw_Filled_Rectangle(&screen,90,8,119,15);
        OLED_Set_Color(&screen,0);
        OLED_Draw_String(&screen,90,8,input_buffer);
        OLED_Draw_ASCII(&screen,120,8,'A');
    }
    else if(input_page.parent==&constant_power_page){
        OLED_Draw_Filled_Rectangle(&screen,78,8,108,15);
        OLED_Set_Color(&screen,0);
        OLED_Draw_String(&screen,78,8,input_buffer);
        OLED_Draw_ASCII(&screen,109,8,'W');
    }
    OLED_Set_Color(&screen,1);
    OLED_Sendbuffer(&screen);
}    

static void press_the_enter_key_event(){
    float value=0;
    sscanf(input_buffer,"%f",&value);
    if(value<0) 
        value=0;
    else if(input_page.parent==&constant_votage_page && value>29.0f)
        value=29.0f;
    else if(input_page.parent==&constant_current_page && value>5.0f) 
        value=5.0f;
    else if(input_page.parent==&constant_power_page && value>5.0f) 
        value=5.0f;
    input_page.parent->pid->Target=roundf(value*100)/100.0f;
    current_page=input_page.parent;
    input_index=0;
    memset(input_buffer,0,sizeof(input_buffer));
    dot_index=255;
} 

static void press_the_back_key_event(){
    current_page=current_page->parent;
    input_index=0;
    memset(input_buffer,0,sizeof(input_buffer));
    dot_index=255;
}


static void press_the_delete_key_event(){
    if(input_index>0){
        input_index--;
        input_buffer[input_index]='\0';
        if(input_index==dot_index){
            dot_index=255;
        }
    }
}

static void press_the_dot_key_event(){
    if(input_index<4&&input_index!=0&&dot_index==255){
        input_buffer[input_index]='.';
        dot_index=input_index;
        input_index++;
    }
}

static void press_the_zero_key_event(){
    if(input_index<5){
        input_buffer[input_index]='0';
        input_index++;
    }
}

static void press_the_one_key_event(){
    if(input_index<5){
        input_buffer[input_index]='1';
        input_index++;
    }
}
static void press_the_two_key_event(){
    if(input_index<5){
        input_buffer[input_index]='2';
        input_index++;
    }
}
void press_the_three_key_event(){
    if(input_index<5){
        input_buffer[input_index]='3';
        input_index++;
    }
}
static void press_the_four_key_event(){
    if(input_index<5){
        input_buffer[input_index]='4';
        input_index++;
    }
}
static void press_the_five_key_event(){
    if(input_index<5){
        input_buffer[input_index]='5';
        input_index++;
    }
}
static void press_the_six_key_event(){
    if(input_index<5){
        input_buffer[input_index]='6';
        input_index++;
    }
}
static void press_the_seven_key_event(){
    if(input_index<5){
        input_buffer[input_index]='7';
        input_index++;
    }
}
static void press_the_eight_key_event(){
    if(input_index<5){
        input_buffer[input_index]='8';
        input_index++;
    }
}
static void press_the_nine_key_event(){
    if(input_index<5){
        input_buffer[input_index]='9';
        input_index++;
    }
}

void input_page_init(){
    input_page.current_num=0;
    input_page.item=NULL;
    input_page.item_num=0;
    input_page.key_handlers[KEY_X0Y0].on_pressed=press_the_zero_key_event;
    input_page.key_handlers[KEY_X0Y1].on_pressed=press_the_one_key_event;
    input_page.key_handlers[KEY_X1Y1].on_pressed=press_the_two_key_event;
    input_page.key_handlers[KEY_X2Y1].on_pressed=press_the_three_key_event;
    input_page.key_handlers[KEY_X0Y2].on_pressed=press_the_four_key_event;
    input_page.key_handlers[KEY_X1Y2].on_pressed=press_the_five_key_event;
    input_page.key_handlers[KEY_X2Y2].on_pressed=press_the_six_key_event;
    input_page.key_handlers[KEY_X0Y3].on_pressed=press_the_seven_key_event;
    input_page.key_handlers[KEY_X1Y3].on_pressed=press_the_eight_key_event;
    input_page.key_handlers[KEY_X2Y3].on_pressed=press_the_nine_key_event;
    
    input_page.key_handlers[KEY_X1Y0].on_pressed=press_the_dot_key_event;
    input_page.key_handlers[KEY_X3Y1].on_pressed=press_the_back_key_event;
    input_page.key_handlers[KEY_X3Y0].on_pressed=press_the_enter_key_event;
    input_page.key_handlers[KEY_X2Y0].on_pressed=press_the_delete_key_event;
    input_page.update_ui=input_page_update_ui;
}


