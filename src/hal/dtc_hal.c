#include "dtc_hal.h"
#include "hal_data.h"
#include "r_dtc.h"

void dtc_init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_DTC_Open(&current_adc_transfer_ctrl, &current_adc_transfer_cfg);
    assert(FSP_SUCCESS == err);
    err = R_DTC_Open(&voltage_adc_transfer_ctrl, &voltage_adc_transfer_cfg);
    assert(FSP_SUCCESS == err);
}

void dtc_start(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_DTC_Enable(&current_adc_transfer_ctrl);
    assert(FSP_SUCCESS == err);
    err = R_DTC_Enable(&voltage_adc_transfer_ctrl);
    assert(FSP_SUCCESS == err);
}

// void dtc_stop(void)
// {
//     fsp_err_t err = FSP_SUCCESS;
//     err = R_DTC_Disable(&current_adc_transfer_ctrl);
//     assert(FSP_SUCCESS == err);
//     err = R_DTC_Disable(&voltage_adc_transfer_ctrl);
//     assert(FSP_SUCCESS == err);
// }
