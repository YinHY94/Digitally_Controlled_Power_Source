#include "pid_control.h"
#include "output_control.h"
#include "hal_data.h"

uint32_t current_ccr;

//PID结构体
PID_Parameter Voltage_PID={
.Kp=25,
.Ki=5,
//.Kd=0,
.T=PID_T,
.Max=MAX_CCR,
.Min=0,
.Target=12.0f,
.Current=0,
.Errer_Threshold=0.01f,
};

PID_Parameter Current_PID={
.Kp=30,
.Ki=40,
//.Kd=0,
.T=PID_T,
.Max=MAX_CCR,
.Min=0,
.Target=1.0f,
.Current=0,
.Errer_Threshold=0.008f,
};

PID_Parameter Power_PID={
.Kp=10,
.Ki=0.5f,
//.Kd=0,
.T=PID_T,
.Max=MAX_CCR,
.Min=0,
.Target=10.0f,
.Current=0,
.Errer_Threshold=0.05f,
};



void PID_Control(PID_Parameter* pid){
	pid->Errer[1] = pid->Errer[0];
	pid->Errer[0] = pid->Target-(pid->Current) ;
	if(pid->Errer[0]>pid->Errer_Threshold || pid->Errer[0]<-pid->Errer_Threshold){
		pid->Integral+=pid->Errer[0];
		// PID 输出计算
		pid->Ret=pid->Kp*pid->Errer[0]+pid->Ki*pid->Integral;
		// PID限幅
		if (pid->Ret >pid->Max) {
			pid->Ret = pid->Max;
			pid->Integral=0;
		} else if (pid->Ret < pid->Min) {
			pid->Ret =pid->Min;
			pid->Integral=0;
		}
		R_GPT_DutyCycleSet(&output_timer_ctrl, (uint32_t)pid->Ret, GPT_IO_PIN_GTIOCA);
		current_ccr=(uint32_t)pid->Ret;
	}
}


