#include "elc_hal.h"
#include "common_data.h"
#include "r_elc.h"

void elc_init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_ELC_Open(&g_elc_ctrl, &g_elc_cfg);
    assert(FSP_SUCCESS == err);
}

void elc_start(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_ELC_Enable(&g_elc_ctrl);
    assert(FSP_SUCCESS == err);
}
