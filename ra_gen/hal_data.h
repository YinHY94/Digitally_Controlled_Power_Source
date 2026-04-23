/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_spi.h"
#include "r_dtc.h"
#include "r_transfer_api.h"
#include "r_adc.h"
#include "r_adc_api.h"
FSP_HEADER
/** Timer on GPT Instance. */
extern const timer_instance_t system_timer;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t system_timer_ctrl;
extern const timer_cfg_t system_timer_cfg;

#ifndef system_timer_callback
void system_timer_callback(timer_callback_args_t * p_args);
#endif
/** SPI on SPI Instance. */
extern const spi_instance_t oled_spi;

/** Access the SPI instance using these structures when calling API functions directly (::p_api is not used). */
extern spi_instance_ctrl_t oled_spi_ctrl;
extern const spi_cfg_t oled_spi_cfg;

/** Callback used by SPI Instance. */
#ifndef oled_spi_callback
void oled_spi_callback(spi_callback_args_t * p_args);
#endif


#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
    #define oled_spi_P_TRANSFER_TX (NULL)
#else
    #define oled_spi_P_TRANSFER_TX (&RA_NOT_DEFINED)
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
    #define oled_spi_P_TRANSFER_RX (NULL)
#else
    #define oled_spi_P_TRANSFER_RX (&RA_NOT_DEFINED)
#endif
#undef RA_NOT_DEFINED
/** Timer on GPT Instance. */
extern const timer_instance_t oled_timer;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t oled_timer_ctrl;
extern const timer_cfg_t oled_timer_cfg;

#ifndef oled_timer_callback
void oled_timer_callback(timer_callback_args_t * p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t output_timer;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t output_timer_ctrl;
extern const timer_cfg_t output_timer_cfg;

#ifndef NULL
void NULL(timer_callback_args_t * p_args);
#endif
/* Transfer on DTC Instance. */
extern const transfer_instance_t voltage_adc_transfer;

/** Access the DTC instance using these structures when calling API functions directly (::p_api is not used). */
extern dtc_instance_ctrl_t voltage_adc_transfer_ctrl;
extern const transfer_cfg_t voltage_adc_transfer_cfg;
/** ADC on ADC Instance. */
extern const adc_instance_t voltage_adc;

/** Access the ADC instance using these structures when calling API functions directly (::p_api is not used). */
extern adc_instance_ctrl_t voltage_adc_ctrl;
extern const adc_cfg_t voltage_adc_cfg;
extern const adc_channel_cfg_t voltage_adc_channel_cfg;

#ifndef vol_adc_cmp_callback
void vol_adc_cmp_callback(adc_callback_args_t * p_args);
#endif

#ifndef NULL
#define ADC_DMAC_CHANNELS_PER_BLOCK_NULL  0
#endif
/* Transfer on DTC Instance. */
extern const transfer_instance_t current_adc_transfer;

/** Access the DTC instance using these structures when calling API functions directly (::p_api is not used). */
extern dtc_instance_ctrl_t current_adc_transfer_ctrl;
extern const transfer_cfg_t current_adc_transfer_cfg;
/** ADC on ADC Instance. */
extern const adc_instance_t current_adc;

/** Access the ADC instance using these structures when calling API functions directly (::p_api is not used). */
extern adc_instance_ctrl_t current_adc_ctrl;
extern const adc_cfg_t current_adc_cfg;
extern const adc_channel_cfg_t current_adc_channel_cfg;

#ifndef cur_adc_cmp_callback
void cur_adc_cmp_callback(adc_callback_args_t * p_args);
#endif

#ifndef NULL
#define ADC_DMAC_CHANNELS_PER_BLOCK_NULL  0
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t adc_timer;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t adc_timer_ctrl;
extern const timer_cfg_t adc_timer_cfg;

#ifndef NULL
void NULL(timer_callback_args_t * p_args);
#endif
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
