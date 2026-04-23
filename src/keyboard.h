#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

// 对应瑞萨的引脚名称（需在 FSP Configurator 中定义引脚符号，如 KEY_X0 等）
// 如果没有定义符号，可以使用 BSP_IO_PORT_00_PIN_00 这种格式

typedef enum {
    KEY_X0Y0 = 0, KEY_X1Y0, KEY_X2Y0, KEY_X3Y0,
    KEY_X0Y1, KEY_X1Y1, KEY_X2Y1, KEY_X3Y1,
    KEY_X0Y2, KEY_X1Y2, KEY_X2Y2, KEY_X3Y2,
    KEY_X0Y3, KEY_X1Y3, KEY_X2Y3, KEY_X3Y3,
    KEY_COUNT
} key_code_t;

typedef enum {
    KEY_STATE_RELEASED = 0,
    KEY_STATE_PRESSED,
    KEY_STATE_LONG_PRESSED
} key_state_t;

typedef struct {
    key_state_t state;
    uint64_t    at_last_changed;
    uint64_t    at_last_pressed;
} key_state_info_t;

typedef void (*key_handler_t)(void); 

typedef struct {
    key_handler_t on_pressed;
    key_handler_t on_released;
    key_handler_t on_long_pressed;
} key_handler_group_t;

void dispatch_for_keys(const key_handler_group_t handlers[KEY_COUNT]);

#endif // KEYBOARD_H
