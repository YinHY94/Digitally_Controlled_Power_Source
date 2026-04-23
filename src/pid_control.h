#ifndef __PID_CONTROL_H__
#define __PID_CONTROL_H__

#include <stdint.h>

#define MAX_CCR  	1000-1
#define MIN_CCR  	0
#define PID_T  		0.001f

typedef struct{
float Kp;
float Ki;
//float Kd;
float T;
uint16_t Max;
uint16_t Min;
float Target;
float Current;
float Integral; 		
float Errer[2]; 		
float Ret;
float Errer_Threshold;	
}PID_Parameter;



extern PID_Parameter Voltage_PID;
extern PID_Parameter Current_PID;
extern PID_Parameter Power_PID;

void PID_Control(PID_Parameter* pid);



#endif
