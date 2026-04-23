#include "keyboard.h"
#include "gpio.h"
#include "stdbool.h"

static void scan_column_in_matrix(GPIO_TypeDef *row_port, uint16_t row_pin, bool *states)
{
    row_port->BSRR = row_pin;

    // When executing too fast, the pin state may not be stable.
    // So we add some NOPs to wait for the pin state to be stable.
    // This is required in Release mode (with optimization enabled).
    __NOP();
    __NOP();
    __NOP();
    __NOP();

// #pragma clang diagnostic push
// #pragma ide diagnostic ignored "Simplify"
// #pragma ide diagnostic ignored "UnreachableCode"


    if (KEY_X0_GPIO_Port == KEY_X1_GPIO_Port && KEY_X1_GPIO_Port == KEY_X2_GPIO_Port &&
        KEY_X2_GPIO_Port == KEY_X3_GPIO_Port)
    {
        // all columns are in the same port
        // read all pins at once
        uint32_t pins_state = READ_REG(KEY_X0_GPIO_Port->IDR);
        states[0] = !!(pins_state & KEY_X0_Pin);
        states[1] = !!(pins_state & KEY_X1_Pin);
        states[2] = !!(pins_state & KEY_X2_Pin);
        states[3] = !!(pins_state & KEY_X3_Pin);
    }
    else
    {
     // read pins one by one
        states[0] = HAL_GPIO_ReadPin(KEY_X0_GPIO_Port, KEY_X0_Pin) == GPIO_PIN_SET;
        states[1] = HAL_GPIO_ReadPin(KEY_X1_GPIO_Port, KEY_X1_Pin) == GPIO_PIN_SET;
        states[2] = HAL_GPIO_ReadPin(KEY_X2_GPIO_Port, KEY_X2_Pin) == GPIO_PIN_SET;
        states[3] = HAL_GPIO_ReadPin(KEY_X3_GPIO_Port, KEY_X3_Pin) == GPIO_PIN_SET;
    }

//#pragma clang diagnostic pop

    row_port->BSRR = row_pin << 16u;
}

static void scan_matrix(bool *states)
{
    scan_column_in_matrix(KEY_Y0_GPIO_Port, KEY_Y0_Pin, &states[0]);
    scan_column_in_matrix(KEY_Y1_GPIO_Port, KEY_Y1_Pin, &states[4]);
    scan_column_in_matrix(KEY_Y2_GPIO_Port, KEY_Y2_Pin, &states[8]);
    scan_column_in_matrix(KEY_Y3_GPIO_Port, KEY_Y3_Pin, &states[12]);
}

// dispatcher

static key_state_info_t key_states[KEY_COUNT];

void dispatch_for_keys(const key_handler_group_t handlers[KEY_COUNT])
{
    bool raw_states[KEY_COUNT];
    scan_matrix(raw_states);
    for (int key_id = 0; key_id < KEY_COUNT; key_id++)
    {
        key_state_info_t *key = &key_states[key_id];
        bool raw_state = raw_states[key_id];
        uint32_t current_tick = HAL_GetTick();
        if (current_tick - key->at_last_changed < 50)
        {
            continue;
        }
        if (key->state == released && raw_state)
        {
            //  buzzer_beep();
            key->state = pressed;
            key->at_last_pressed = current_tick;
            key->at_last_changed = current_tick;
            if(handlers[key_id].on_pressed)
                //handlers[key_id].on_pressed(released);
                handlers[key_id].on_pressed();
        }
        else if (key->state != released && !raw_state)
        {
            //key_state before = key->state;
            key->state = released;
            key->at_last_changed = current_tick;
            if (handlers[key_id].on_released)
                //handlers[key_id].on_released(before);
                handlers[key_id].on_released();
        }
        else if (key->state == pressed && raw_state)
        {
            if (current_tick - key->at_last_pressed >= 2000)
            {
                // buzzer_beep();
                key->state = long_pressed;
                key->at_last_changed = current_tick;
                if (handlers[key_id].on_long_pressed)
                    //handlers[key_id].on_long_pressed(pressed);
                    handlers[key_id].on_long_pressed();
            }
        }
    }
}



