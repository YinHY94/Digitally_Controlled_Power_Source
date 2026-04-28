#include "gpt_hal.h"
#include "fsp_common_api.h"


void gpt_init(timer_ctrl_t *p_ctrl,timer_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_GPT_Open(p_ctrl, p_cfg);
    assert(FSP_SUCCESS == err);
}

void gpt_start(timer_ctrl_t *p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_GPT_Start(p_ctrl);
    assert(FSP_SUCCESS == err);
}

void gpt_stop(timer_ctrl_t *p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_GPT_Stop(p_ctrl);
    assert(FSP_SUCCESS == err);
}

void gpt_set_duty_cycle(timer_ctrl_t *p_ctrl, uint32_t duty_cycle_counts)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_GPT_DutyCycleSet(p_ctrl, duty_cycle_counts, GPT_IO_PIN_GTIOCA);
    assert(FSP_SUCCESS == err);
}

void gpt_reset(timer_ctrl_t *p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_GPT_Reset(p_ctrl);
    assert(FSP_SUCCESS == err);
}

