#include "hal_data.h"

volatile uint8_t cur_cmp;
volatile uint8_t vol_cmp;
volatile uint8_t update_ui_state;
volatile uint8_t oled_spi_cmp;
volatile uint64_t system_tick;

void cur_adc_cmp_callback(adc_callback_args_t *p_args)
{
    if (p_args->event == ADC_EVENT_SCAN_COMPLETE)
    {
        cur_cmp = 1;
    }
}

void vol_adc_cmp_callback(adc_callback_args_t *p_args)
{
    if (p_args->event == ADC_EVENT_SCAN_COMPLETE)
    {
        vol_cmp = 1;
    }
}

void oled_timer_callback(timer_callback_args_t *p_args)
{
    if (p_args->event == TIMER_EVENT_CYCLE_END)
    {
        update_ui_state = 1;
    }
}

void oled_spi_callback(spi_callback_args_t *p_args)
{
    if (p_args->event == SPI_EVENT_TRANSFER_COMPLETE)
    {
        oled_spi_cmp = 1;
    }
}

void system_timer_callback(timer_callback_args_t *p_args)
{
    if (p_args->event == TIMER_EVENT_CYCLE_END)
    {
        system_tick++;
    }
}
