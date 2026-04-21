/* generated vector source file - do not edit */
        #include "bsp_api.h"
        /* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
        #if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_NUM_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = gpt_counter_overflow_isr, /* GPT0 COUNTER OVERFLOW (Overflow) */
            [1] = gpt_counter_underflow_isr, /* GPT0 COUNTER UNDERFLOW (Underflow) */
            [2] = adc_scan_end_isr, /* ADC0 SCAN END (End of A/D scanning operation) */
            [3] = adc_scan_end_b_isr, /* ADC0 SCAN END B (A/D scan end interrupt for group B) */
            [4] = adc_scan_end_isr, /* ADC1 SCAN END (End of A/D scanning operation) */
            [5] = adc_scan_end_b_isr, /* ADC1 SCAN END B (A/D scan end interrupt for group B) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_NUM_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_GPT0_COUNTER_OVERFLOW,GROUP0), /* GPT0 COUNTER OVERFLOW (Overflow) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_GPT0_COUNTER_UNDERFLOW,GROUP1), /* GPT0 COUNTER UNDERFLOW (Underflow) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_ADC0_SCAN_END,GROUP2), /* ADC0 SCAN END (End of A/D scanning operation) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_ADC0_SCAN_END_B,GROUP3), /* ADC0 SCAN END B (A/D scan end interrupt for group B) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_ADC1_SCAN_END,GROUP4), /* ADC1 SCAN END (End of A/D scanning operation) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_ADC1_SCAN_END_B,GROUP5), /* ADC1 SCAN END B (A/D scan end interrupt for group B) */
        };
        #endif
        #endif