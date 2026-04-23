#pragma once

#include <stdint.h>


extern volatile uint8_t output_state; // 0: off 1: on


void Output_Stop();
void Output_Start();



