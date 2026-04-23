#pragma once

#include <stdint.h>
#include "keyboard.h"
#include "pid_control.h"

#define ITEM_NUM 3

typedef void(*update_ui)();
typedef void(*route_to)();

struct page{
struct page* parent;
char** item;
uint8_t item_num;
uint8_t current_num;
update_ui update_ui;
key_handler_group_t key_handlers[KEY_COUNT];
PID_Parameter* pid;
};


typedef struct page page;


extern page main_menu_page;
extern page constant_votage_page;
extern page constant_current_page;
extern page constant_power_page;
extern page input_page;
extern page* current_page;


void page_init();
void route_to_menu();
void main_menu_page_init();
void constant_votage_page_init();
void constant_current_page_init();
void constant_power_page_init();
void input_page_init();
void set_data();
