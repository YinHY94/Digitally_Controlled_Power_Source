#include <stddef.h>
#include "oled.h"
#include "page.h"


char* item[]={
"Constant Votage",
"Constant Current",
"Constant Power",
};

page main_menu_page;

void main_menu_page_update_ui(){
OLED_Clearbuffer(&g_screen);
OLED_Set_Font(&g_screen,&Font_8x16);
OLED_Draw_String(&g_screen,0,0,main_menu_page.item[0]);
OLED_Draw_String(&g_screen,0,16,main_menu_page.item[1]);
OLED_Draw_String(&g_screen,0,32,main_menu_page.item[2]);
OLED_Set_Color(&g_screen,2);
OLED_Draw_Filled_Rectangle(&g_screen,0,main_menu_page.current_num*16,g_screen.Lenth-1,main_menu_page.current_num*16+15);
OLED_Set_Color(&g_screen,1);
OLED_Sendbuffer(&g_screen);
}




//void route_to_item(key_state prev_state){
    //(void)prev_state;
void route_to_item(){
    switch (main_menu_page.current_num) {
    case 0:
        current_page=&constant_votage_page;
        break;
    case 1:
        current_page=&constant_current_page;
        break;
    case 2:
        current_page=&constant_power_page;
        break;
    default:
        break;
    }
}



// void main_menu_page_num_increase(key_state prev_state){
//     (void)prev_state;
void main_menu_page_num_increase(){
    if(main_menu_page.current_num<main_menu_page.item_num-1){
        main_menu_page.current_num++;
    }
}

// void main_menu_page_num_decrease(key_state prev_state){
//     (void)prev_state;
void main_menu_page_num_decrease(){
    if(main_menu_page.current_num>0){
        main_menu_page.current_num--;
    }
}

void main_menu_page_init(){
    main_menu_page.current_num=0;
    main_menu_page.item=item;
    main_menu_page.item_num=ITEM_NUM;
    main_menu_page.key_handlers[KEY_X3Y0].on_pressed=route_to_item;
    main_menu_page.key_handlers[KEY_X3Y3].on_pressed=main_menu_page_num_decrease;
    main_menu_page.key_handlers[KEY_X3Y2].on_pressed=main_menu_page_num_increase;
    main_menu_page.update_ui=main_menu_page_update_ui;
    main_menu_page.pid=NULL;
}

