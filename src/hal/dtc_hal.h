#pragma once


#include <sys/types.h>
typedef struct
{
   uint16_t voltage[2];
   uint16_t current[2];
} adc_data;

void dtc_init(void);
void dtc_start(void);
// void dtc_stop(void);