#pragma once

#include <stdint.h>
#include "gpio.h"

typedef enum key_code_t
{
//    KEY_OK ,
//    USER_KEY_1,
//    USER_KEY_2,
    KEY_X0Y0,
    KEY_X1Y0,
    KEY_X2Y0,
    KEY_X3Y0,
    KEY_X0Y1,
    KEY_X1Y1,
    KEY_X2Y1,
    KEY_X3Y1,
    KEY_X0Y2,
    KEY_X1Y2,
    KEY_X2Y2,
    KEY_X3Y2,
    KEY_X0Y3,
    KEY_X1Y3,
    KEY_X2Y3,
    KEY_X3Y3,
    KEY_COUNT,
}key_code_t;

typedef enum key_state
{
    released,
    pressed,
    long_pressed
}key_state;


typedef struct key_state_info_t
{
    key_state state;
    uint32_t at_last_changed;
    uint32_t at_last_pressed;
}key_state_info_t;


//typedef void (*key_handler_t)(key_state prev_state); 

typedef void (*key_handler_t)(); 

typedef struct key_handler_group_t
{
    key_handler_t on_pressed;
    key_handler_t on_released;
    key_handler_t on_long_pressed;
}key_handler_group_t;



void dispatch_for_keys(const key_handler_group_t handlers[KEY_COUNT]);


