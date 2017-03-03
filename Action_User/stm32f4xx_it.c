/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Template/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    13-April-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "stm32f4xx.h"
#include  <ucos_ii.h>
/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/
#include "stm32f4xx_tim.h"
#include "encoder.h"
#include "stm32f4xx_usart.h"
#include "math.h"
#include "algorithm.h"
//#include "arm_math.h"
#include "usart.h"
#include "can.h"
#include "String.h"
#include "Deal_Data.h"
#include "Led_Beep.h"
#include "stm32f4xx_dma.h"
#include "flag.h"
#include "gpio.h"
#include "stm32f4xx_exti.h"
#include "ColorSensor.h"
#include "elmo.h"
#include "copley.h"
#include "PlayBadminton.h"
#include "action_driver.h"
#include "data.h"


u8 free_dma_buffer=1;
u8 motor_ready=0;
u8  flag=0;
void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg rx_message;	
	int32_t id = 0;
	static uint8_t Heart_Beat; 	
	if(CAN_GetITStatus(CAN1, CAN_IT_FMP0)!= RESET) 
	{
		CAN_Receive(CAN1, CAN_FIFO0, &rx_message);		
		id=rx_message.StdId;
		//fix me!!!
		if(id == 0x700 + 1)
		{
			motor_ready=1;			
			Heart_Beat=rx_message.Data[3];  // 7f-pre-operational 4-stop 5-operational						
		}

		if(Heart_Beat==0x05)
		{
			flag=1;		
		}

		/***************接收驱动器返回的错误信息*****************/	
		//fix me!!!
  	ActionCheckError(1, &rx_message);
		
		/***************接收驱动器返回的数据*********************/		
		ActionUpdateMotorInfo(2, &rx_message);
		
		CAN_ClearITPendingBit(CAN1, CAN_IT_FF0);
	}		
}

void CAN2_RX0_IRQHandler(void)
{
	OS_CPU_SR  cpu_sr;

	static uint8_t buffer[16];
	uint32_t StdId=0;
	OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();

	CAN_RxMsg(CAN2, &StdId,buffer,8);

	CAN_ClearFlag(CAN2,CAN_FLAG_EWG);
	CAN_ClearFlag(CAN2,CAN_FLAG_EPV);
	CAN_ClearFlag(CAN2,CAN_FLAG_BOF);
	CAN_ClearFlag(CAN2,CAN_FLAG_LEC);	
	CAN_ClearFlag(CAN2,CAN_FLAG_FMP0);
	CAN_ClearFlag(CAN2,CAN_FLAG_FF0);
	CAN_ClearFlag(CAN2,CAN_FLAG_FOV0);
	CAN_ClearFlag(CAN2,CAN_FLAG_FMP1);
	CAN_ClearFlag(CAN2,CAN_FLAG_FF1);
	CAN_ClearFlag(CAN2,CAN_FLAG_FOV1);
	OSIntExit();
}

//定时器1  左编码器中断
void TIM1_UP_TIM10_IRQHandler(void)
{
	OS_CPU_SR  cpu_sr;
	OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();
	if(TIM_GetITStatus(TIM1, TIM_IT_Update)==SET)    
	{                                                
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
	OSIntExit();
}

//定时器8  右编码器中断
void TIM8_UP_TIM13_IRQHandler(void)
{
	OS_CPU_SR  cpu_sr;
	OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();
	if(TIM_GetITStatus(TIM8, TIM_IT_Update)==SET)    
	{                                                
		TIM_ClearITPendingBit(TIM8, TIM_IT_Update);
	}
	OSIntExit();
}
//定时器3 向驱动器发送上传命令

extern  OS_EVENT 		*PeriodSem;
void TIM3_IRQHandler(void)
{
	OS_CPU_SR  cpu_sr;
	OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();

	if(TIM_GetITStatus(TIM3, TIM_IT_Update)==SET)    
	{             
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		OSSemPost(PeriodSem);
		
		
	}
	OSIntExit();
}
//定时器4  右编码器中断
void TIM4_IRQHandler(void)
{
	OS_CPU_SR  cpu_sr;
	OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();
	if(TIM_GetITStatus(TIM4, TIM_IT_Update)==SET)    
	{                                                
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
	OSIntExit();
}

void TIM5_IRQHandler(void)
{
	OS_CPU_SR  cpu_sr;
	OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();
	if(TIM_GetITStatus(TIM5, TIM_IT_Update)==SET)    
	{                                                
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
	OSIntExit();
}




void USART2_IRQHandler(void)                	//串口2中断服务程序
{
	u16 Res=0;
	
	static u8 count=0;
	
	OSIntEnter();    

	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		USART_ClearITPendingBit( USART2,USART_IT_RXNE);
		Res =USART_ReceiveData(USART2);//读取接收到的数据
		switch(count)
		{
			case 0:
				if(Res=='A')
					count++;
				else
					count=0;
				break;
			case 1:
				if(Res=='C')
					count++;
				else
					count=0;
				break;
			case 2:
				SetInput(Res);
//			case 2:
//				posture.data[0]=Res;
//			  count++;
//				break;
//			case 3:
//				posture.data[1]=Res;
//			  count++;
//				break;
//			case 4:
//				posture.data[2]=Res;
//			  count++;
//				break;
//			case 5:
//				posture.data[3]=Res;
//			  recCmdVel.linearVel=posture.vel[0];
//				recCmdVel.angularVel=posture.vel[1];
//			
//				Set_CmdVel(&recCmdVel);
			  count=0;
				break;
				
		}		 
  } 
	OSIntExit();  											 
} 



void USART3_IRQHandler(void)
{

	static uint8_t ch		 = 0;
	static uint8_t count = 0;
	static uint8_t i     = 0;
	Posture recPos;
	
	static union
  {
	    uint8_t data[24];
	    float   ActVal[6];
  }posture;
	
	OS_CPU_SR  cpu_sr;
	OS_ENTER_CRITICAL();/* Tell uC/OS-II that we are starting an ISR*/
	OSIntNesting++;
	OS_EXIT_CRITICAL();
	
 if(USART_GetITStatus(USART3, USART_IT_RXNE)==SET)   
 {
		USART_ClearITPendingBit( USART3,USART_IT_RXNE);
		ch=USART_ReceiveData(USART3);
		switch(count)
		{
			 case 0:
				 if(ch==0x0d)
					 count++;
				 else
					 count=0;
				 break;
				 
			 case 1:
				 if(ch==0x0a)
				 {
					 i=0;
					 count++;
				 }
				 else if(ch==0x0d);
				 else
					 count=0;
				 break;
				 
			 case 2:
				 posture.data[i]=ch;
				 i++;
				 if(i>=24)
				 {
							i=0;
							count++;
				 }
				 break;
				 
			 case 3:
				 if(ch==0x0a)
					 count++;
				 else
					 count=0;
				 break;
				 
			 case 4:
				 if(ch==0x0d)
				 {
					 recPos.angle=posture.ActVal[0];
					 
					 recPos.x=-posture.ActVal[3];
					 
					 recPos.y=-posture.ActVal[4];
					 Set_Pos(&recPos);
					
				 }
				 
				 count=0;
				 break;
			 
			 default:
				 count=0;
				 break;		 
		 }
	 }
	 OSIntExit();
}




/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
   while (1)
   {
   }
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{

  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{

  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
 
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
