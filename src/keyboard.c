#include "keyboard.h"
#include "hal_data.h"

/* 假设在 FSP Configurator 中已将引脚命名为 KEY_X0, KEY_Y0 等 */
static const bsp_io_port_pin_t X_PINS[] = { KEY_X0, KEY_X1, KEY_X2, KEY_X3 };
static const bsp_io_port_pin_t Y_PINS[] = { KEY_Y0, KEY_Y1, KEY_Y2, KEY_Y3 };

static key_state_info_t key_states[KEY_COUNT];

extern volatile uint8_t system_tick;

uint64_t R_BSP_TickGet(void)
{
    return system_tick;
}


/**
 * 扫描矩阵的一行
 * @param row_pin 瑞萨引脚定义
 * @param states  存储该行4个列按键的结果
 */
static void scan_row_in_matrix(bsp_io_port_pin_t row_pin, bool *states)
{
    // 拉低当前行 (假设是低电平有效)
    R_IOPORT_PinWrite(&g_ioport_ctrl, row_pin, BSP_IO_LEVEL_LOW);

    // 瑞萨内核频率通常较高，增加延时保证电平稳定
    for (volatile int d = 0; d < 150; d++) {
        __NOP();
    }

    // 读取 4 个列引脚的状态
    for (int i = 0; i < 4; i++) {
        bsp_io_level_t level;
        R_IOPORT_PinRead(&g_ioport_ctrl, X_PINS[i], &level);
        // 如果读取到低电平，说明按键按下
        states[i] = (level == BSP_IO_LEVEL_LOW);
    }

    // 恢复行电平为高
    R_IOPORT_PinWrite(&g_ioport_ctrl, row_pin, BSP_IO_LEVEL_HIGH);
}

static void scan_matrix(bool *states)
{
    // 依次扫描 Y0 - Y3 四行
    scan_row_in_matrix(Y_PINS[0], &states[0]);
    scan_row_in_matrix(Y_PINS[1], &states[4]);
    scan_row_in_matrix(Y_PINS[2], &states[8]);
    scan_row_in_matrix(Y_PINS[3], &states[12]);
}

void dispatch_for_keys(const key_handler_group_t handlers[KEY_COUNT])
{
    bool raw_states[KEY_COUNT];
    scan_matrix(raw_states);

    // 获取瑞萨 BSP 系统滴答 (通常 1 tick = 1 ms)
    uint64_t current_tick = R_BSP_TickGet();
    for (int key_id = 0; key_id < KEY_COUNT; key_id++)
    {
        key_state_info_t *key = &key_states[key_id];
        bool raw_state = raw_states[key_id];

        // 消抖处理：50ms 内不重复触发状态改变
        if (current_tick - key->at_last_changed < 50)
        {
            continue;
        }

        if (key->state == KEY_STATE_RELEASED && raw_state)
        {
            // 状态：从未按下 -> 按下
            key->state = KEY_STATE_PRESSED;
            key->at_last_pressed = current_tick;
            key->at_last_changed = current_tick;
            if(handlers[key_id].on_pressed)
                handlers[key_id].on_pressed();
        }
        else if (key->state != KEY_STATE_RELEASED && !raw_state)
        {
            // 状态：任何按下状态 -> 松开
            key->state = KEY_STATE_RELEASED;
            key->at_last_changed = current_tick;
            if (handlers[key_id].on_released)
                handlers[key_id].on_released();
        }
        else if (key->state == KEY_STATE_PRESSED && raw_state)
        {
            // 状态：持续按下 -> 判定长按 (2000ms)
            if (current_tick - key->at_last_pressed >= 2000)
            {
                key->state = KEY_STATE_LONG_PRESSED;
                key->at_last_changed = current_tick;
                if (handlers[key_id].on_long_pressed)
                    handlers[key_id].on_long_pressed();
            }
        }
    }
}
