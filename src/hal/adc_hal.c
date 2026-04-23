#include "adc_hal.h"
#include "hal_data.h"
#include "r_adc.h"
#include <assert.h>

void adc_init(void){
    fsp_err_t err = FSP_SUCCESS;
    err = R_ADC_Open(&current_adc_ctrl, &current_adc_cfg);
    assert(FSP_SUCCESS == err);
    err = R_ADC_Open(&voltage_adc_ctrl, &voltage_adc_cfg);
    assert(FSP_SUCCESS == err);
}

void adc_start(void){
    fsp_err_t err = FSP_SUCCESS;
    err = R_ADC_ScanStart(&current_adc_ctrl);
    assert(FSP_SUCCESS == err);
    err = R_ADC_ScanStart(&voltage_adc_ctrl);
    assert(FSP_SUCCESS == err);
}

void adc_stop(void){
    fsp_err_t err = FSP_SUCCESS;
    err = R_ADC_ScanStop(&current_adc_ctrl);
    assert(FSP_SUCCESS == err);
    err = R_ADC_ScanStop(&voltage_adc_ctrl);
    assert(FSP_SUCCESS == err);
}


