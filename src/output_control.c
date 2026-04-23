#include "output_control.h"
#include "page.h"
#include "tim.h"

volatile uint8_t output_state; // 0: off 1: on

void Output_Stop(){
    output_state=0;
    HAL_TIM_Base_Stop_IT(&htim2);
    //HAL_TIM_Base_Stop(&htim3);
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
    HAL_GPIO_WritePin(IR2104_EN_GPIO_Port, IR2104_EN_Pin, GPIO_PIN_RESET); // 关闭输出
	TIM1->CCR1=0;
    current_page->pid->Integral=0;
    current_page->pid->Errer[0]=0;
}

void Output_Start(){
    output_state=1;
    HAL_TIM_Base_Start_IT(&htim2);
    //HAL_TIM_Base_Start(&htim3);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_GPIO_WritePin(IR2104_EN_GPIO_Port, IR2104_EN_Pin, GPIO_PIN_SET);
}



