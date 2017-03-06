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

union BLE_message    //�����ֱ����ݶ���
{
	uint8_t  BLEData[2];
	uint16_t BLEData1;
};

//////////////////�ⲿ������������///////////////////////
extern double ACTION_POSTION_X,ACTION_POSTION_Y;
double Aim_x=0.0,Aim_y=0.0;
extern __IO float Angle;
extern __IO float Angle_JiaoZheng;//�ǶȽ�������
extern float Angle_yuanshi;//�Ƕȱ���
#if DEBUG
extern uint32_t Real_Time;
#endif
//////////////////�ź���������///////////////////////
 OS_EVENT 		*PeriodSem;
 OS_EVENT 		*BeforePlayTaskSem;
 OS_EVENT 		*SysTickSem;
 OS_EVENT 		*GoHome_DealerrSem;
#if DEBUG
 OS_EVENT 		*DEBUGkSem;
#endif
  /////////////////���䶨����/////////////////////////
 OS_EVENT     *ChooseBat_Box;
 
void App_Task()
{
	CPU_INT08U  os_err;
	os_err = os_err; /* prevent warning... */
	
	/******************�����ź���***********************/
   PeriodSem				  =	OSSemCreate(0);
	 BeforePlayTaskSem	=	OSSemCreate(0);
   SysTickSem				  =	OSSemCreate(0);
	 GoHome_DealerrSem	=	OSSemCreate(0);
#if DEBUG
	 DEBUGkSem				  =	OSSemCreate(0);
#endif
	/******************��������*************************/
	ChooseBat_Box=OSMboxCreate((void*)0);
	
	
	
  /*****************��������**************************/	
	os_err = OSTaskCreate(	(void (*)(void *)) ConfigTask,					//��ʼ������
	                      	(void          * ) 0,							
							(OS_STK        * )&App_ConfigStk[Config_TASK_START_STK_SIZE-1],		
							(INT8U           ) Config_TASK_START_PRIO  );	

	os_err = OSTaskCreate(	(void (*)(void *)) WalkTask,					//��������
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
	
	//��ʱ3s���ȴ���λϵͳ����������ʼ��	
	TIM_Delayms(TIM5,10000);
	CAN_Config( CAN1, 500,GPIOB,GPIO_Pin_8, GPIO_Pin_9 );
	
	//10ms�ж�
	TIM_Init(TIM3, 1000-1, 840-1,2,2);
	
	//��pcͨ�Ŵ���
	PC_USART2_Init(115200);
	
	//�Ͷ�λϵͳͨ�Ŵ���
	GYRO_USART3_Init(115200);
	
	//���ô���
	DEBUG_UART4_Init(115200);


  
	ActionSetHeartbeatInterval(1, 100);
	ActionSetHeartbeatInterval(2, 100);
	ActionSetOperationalMode(1); // ��������ǰ����Ҫ���������� �ڿɲ���ģʽ
	ActionSetOperationalMode(2); // ��������ǰ����Ҫ���������� �ڿɲ���ģʽ
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



