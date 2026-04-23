#pragma once
#include "hal_data.h"

void gpt_init(timer_ctrl_t *p_ctrl,timer_cfg_t const * const p_cfg);
void gpt_start(timer_ctrl_t *p_ctrl);
void gpt_stop(timer_ctrl_t *p_ctrl);
void gpt_set_duty_cycle(timer_ctrl_t *p_ctrl, uint32_t duty_cycle_counts);
