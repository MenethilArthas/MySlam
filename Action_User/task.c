#include  <includes.h>
#include  <app_cfg.h>
#include "encoder.h"
#include "misc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "usart.h"
#include "can.h"
#include "copley.h"
#include "gpio.h"
#include "Led_Beep.h"
#include "timer.h"
#include "data.h"

#include "action_driver.h"
#include "stm32f4xx_dma.h"

union BLE_message    //场外手柄数据定义
{
	uint8_t  BLEData[2];
	uint16_t BLEData1;
};

//////////////////外部变量量定义区///////////////////////
extern double ACTION_POSTION_X,ACTION_POSTION_Y;
double Aim_x=0.0,Aim_y=0.0;
extern __IO float Angle;
extern __IO float Angle_JiaoZheng;//角度矫正变量
extern float Angle_yuanshi;//角度变量
#if DEBUG
extern uint32_t Real_Time;
#endif
//////////////////信号量定义区///////////////////////
 OS_EVENT 		*PeriodSem;
 OS_EVENT 		*BeforePlayTaskSem;
 OS_EVENT 		*SysTickSem;
 OS_EVENT 		*GoHome_DealerrSem;
#if DEBUG
 OS_EVENT 		*DEBUGkSem;
#endif
  /////////////////邮箱定义区/////////////////////////
 OS_EVENT     *ChooseBat_Box;
 
void App_Task()
{
	CPU_INT08U  os_err;
	os_err = os_err; /* prevent warning... */
	
	/******************创建信号量***********************/
   PeriodSem				  =	OSSemCreate(0);
	 BeforePlayTaskSem	=	OSSemCreate(0);
   SysTickSem				  =	OSSemCreate(0);
	 GoHome_DealerrSem	=	OSSemCreate(0);
#if DEBUG
	 DEBUGkSem				  =	OSSemCreate(0);
#endif
	/******************创建邮箱*************************/
	ChooseBat_Box=OSMboxCreate((void*)0);
	
	
	
  /*****************创建任务**************************/	
	os_err = OSTaskCreate(	(void (*)(void *)) ConfigTask,					//初始化任务
	                      	(void          * ) 0,							
							(OS_STK        * )&App_ConfigStk[Config_TASK_START_STK_SIZE-1],		
							(INT8U           ) Config_TASK_START_PRIO  );	

	os_err = OSTaskCreate(	(void (*)(void *)) WalkTask,					//走行任务
													(void          * ) 0,							
							(OS_STK        * )&WalkTaskStk[Walk_TASK_STK_SIZE-1],		
							(INT8U           ) Walk_TASK_PRIO  );									
												

													
}


extern u32 			DMA_Send_count;
extern int32_t speed_value,current_value,relative_position_value,absolute_position_value;


//#define ttl
void ConfigTask(void)
{
	
	CPU_INT08U  os_err;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//延时3s，等待定位系统和驱动器初始化	
	TIM_Delayms(TIM5,10000);
	CAN_Config( CAN1, 500,GPIOB,GPIO_Pin_8, GPIO_Pin_9 );
	
	//10ms中断
	TIM_Init(TIM3, 1000-1, 840-1,2,2);
	
	//和pc通信串口
	PC_USART2_Init(115200);
	
	//和定位系统通信串口
	GYRO_USART3_Init(115200);
	
	//备用串口
	DEBUG_UART4_Init(115200);


  
	ActionSetHeartbeatInterval(1, 100);
	ActionSetHeartbeatInterval(2, 100);
	ActionSetOperationalMode(1); // 发送命令前，需要控制驱动器 在可操作模式
	ActionSetOperationalMode(2); // 发送命令前，需要控制驱动器 在可操作模式
	ActionConfigTorque(1,1000);
	ActionConfigTorque(2,1000);


	ActionConfigVelocity(1,20000,20000);
	ActionConfigVelocity(2,20000,20000);


	OSSemSet(PeriodSem,0,&os_err);			

	 
}



void WalkTask(void)
{
	CPU_INT08U  os_err;
	Posture pos;
	uint8_t cmd      = 0;
	union 
	{
		uint8_t data[12];
		float coor[3];
	}txData;
	
	while(1)
	{
			OSSemPend(PeriodSem,0,&os_err);
		  
		  cmd=GetInput();
			Get_Pos(&pos);
			MotionCtrl(cmd);
			txData.coor[0]=pos.x;
			txData.coor[1]=pos.y;
			txData.coor[2]=pos.angle;
			#ifdef ttl
			USART_SendData(USART2,'A');
			USART_SendData(USART2,'C');
			#else
			USART_SendData(UART4,'A');
			USART_SendData(UART4,'C');
			#endif
			for(int i=0;i<12;i++)
			{
				#ifdef ttl
				USART_SendData(USART2,txData.data[i]);
				#else
				USART_SendData(UART4,txData.data[i]);
				#endif
			}
		

	}
}


void MotionCtrl(uint8_t cmd)
{
	int16_t initVel    =   3000;
	static float   velScale   =    1;
	switch(cmd)
	{
		case 'w':
			ActionSetVelocity(1,initVel*velScale);
			ActionSetVelocity(2,initVel*velScale);
			break;
		case 'd':
			ActionSetVelocity(1,0.4*initVel*velScale);
			ActionSetVelocity(2,0.4*(-initVel)*velScale);
			break;
		case 'a':
			ActionSetVelocity(1,0.4*(-initVel)*velScale);
			ActionSetVelocity(2,0.4*initVel*velScale);
			break;
		case 'x':
			ActionSetVelocity(1,-initVel*velScale);
			ActionSetVelocity(2,-initVel*velScale);
			break;
		case 's':
			ActionSetVelocity(1,0);
			ActionSetVelocity(2,0);
			break;
		case 'i':
			velScale+=0.03;
			if(velScale>=2.5)
				velScale=2.5;
			break;
		case 'k':
			velScale-=0.03;
			if(velScale<=1)
				velScale=1;
			break;
		default:
				break;
	}
}



