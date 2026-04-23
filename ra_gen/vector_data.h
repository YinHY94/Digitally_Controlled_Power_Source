/* generated vector header file - do not edit */
        #ifndef VECTOR_DATA_H
        #define VECTOR_DATA_H
        #ifdef __cplusplus
        extern "C" {
        #endif
                /* Number of interrupts allocated */
        #ifndef VECTOR_DATA_IRQ_COUNT
        #define VECTOR_DATA_IRQ_COUNT    (6)
        #endif
        /* ISR prototypes */
        void gpt_counter_overflow_isr(void);
        void adc_scan_end_isr(void);
        void gpt_counter_underflow_isr(void);

        /* Vector table allocations */
        #define VECTOR_NUMBER_GPT0_COUNTER_OVERFLOW ((IRQn_Type) 0) /* GPT0 COUNTER OVERFLOW (Overflow) */
        #define GPT0_COUNTER_OVERFLOW_IRQn          ((IRQn_Type) 0) /* GPT0 COUNTER OVERFLOW (Overflow) */
        #define VECTOR_NUMBER_ADC0_SCAN_END ((IRQn_Type) 1) /* ADC0 SCAN END (End of A/D scanning operation) */
        #define ADC0_SCAN_END_IRQn          ((IRQn_Type) 1) /* ADC0 SCAN END (End of A/D scanning operation) */
        #define VECTOR_NUMBER_ADC1_SCAN_END ((IRQn_Type) 2) /* ADC1 SCAN END (End of A/D scanning operation) */
        #define ADC1_SCAN_END_IRQn          ((IRQn_Type) 2) /* ADC1 SCAN END (End of A/D scanning operation) */
        #define VECTOR_NUMBER_GPT1_COUNTER_OVERFLOW ((IRQn_Type) 3) /* GPT1 COUNTER OVERFLOW (Overflow) */
        #define GPT1_COUNTER_OVERFLOW_IRQn          ((IRQn_Type) 3) /* GPT1 COUNTER OVERFLOW (Overflow) */
        #define VECTOR_NUMBER_GPT1_COUNTER_UNDERFLOW ((IRQn_Type) 4) /* GPT1 COUNTER UNDERFLOW (Underflow) */
        #define GPT1_COUNTER_UNDERFLOW_IRQn          ((IRQn_Type) 4) /* GPT1 COUNTER UNDERFLOW (Underflow) */
        #define VECTOR_NUMBER_GPT2_COUNTER_OVERFLOW ((IRQn_Type) 5) /* GPT2 COUNTER OVERFLOW (Overflow) */
        #define GPT2_COUNTER_OVERFLOW_IRQn          ((IRQn_Type) 5) /* GPT2 COUNTER OVERFLOW (Overflow) */
        /* The number of entries required for the ICU vector table. */
        #define BSP_ICU_VECTOR_NUM_ENTRIES (6)

        #ifdef __cplusplus
        }
        #endif
        #endif /* VECTOR_DATA_H */