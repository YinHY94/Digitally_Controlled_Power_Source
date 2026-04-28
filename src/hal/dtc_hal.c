#include "dtc_hal.h"
#include "hal_data.h"
#include "pid_control.h"
#include "r_dtc.h"

void dtc_init(void)
{
    fsp_err_t err = FSP_SUCCESS;

    err = R_DTC_Open(&current_adc_transfer_ctrl, &current_adc_transfer_cfg);
    assert(FSP_SUCCESS == err);
    err = R_DTC_Open(&voltage_adc_transfer_ctrl, &voltage_adc_transfer_cfg);
    assert(FSP_SUCCESS == err);

    current_adc_transfer_cfg.p_info->p_dest= &Current_PID.Current;
    current_adc_transfer_cfg.p_info->p_src = (void const*) &R_ADC0->ADDR[0u];
    err = R_DTC_Reconfigure(&current_adc_transfer_ctrl, current_adc_transfer_cfg.p_info);
    assert(FSP_SUCCESS == err);
    
    voltage_adc_transfer_cfg.p_info->p_dest= &Current_PID.Current;
    voltage_adc_transfer_cfg.p_info->p_src = (void const*) &R_ADC1->ADDR[1u];
    err = R_DTC_Reconfigure(&voltage_adc_transfer_ctrl, voltage_adc_transfer_cfg.p_info);
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
