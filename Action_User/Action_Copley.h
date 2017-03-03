#ifndef __ACTION_COPLEY_H
#define __ACTION_COPLEY_H
#include "stm32f4xx.h"

#define VelCfgCmd	 2		  	//速度参数设置	 加速度
#define VelAdjCmd	 3		  	//速度调节

typedef union 		   			//发数据公用体
{
	uint8_t  uint8[8];
	uint16_t uint16[4];
	uint32_t uint32[2];
	int		 int32[2];	  
}CANDATA_TRANS;

void ZeroPos_Set(uint8_t driverNum);
void VelCrl(uint32_t Motor_Num,int Speed_Vel);
void VelCfg_Action(uint32_t Motor_Num,uint32_t Acc_Vel,uint32_t Dec_Vel);
void SetCar_L_V(int V_L);
void SetCar_R_V(int V_R);
int GetCar_L_V(void);
int GetCar_R_V(void);
void SetVel(uint16_t Sbus_Channel_Temp2 ,uint16_t Sbus_Channel_Temp3);
#endif


