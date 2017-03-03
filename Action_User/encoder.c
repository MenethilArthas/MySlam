/**
  ******************************************************************************
  * @file    encoder.c
  * @author  Calcus Lee
  * @version V1.0.1
  * @date    9-August-2013
  * @brief   functions of Using TIMx as encoder
  ******************************************************************************
  * @attention
  *
  * three are some IRQ handler functions in stm32f4xx_it.c
  *
  * How to use TIMx as encoder x: 
  * 	  1.Initialize TIMx using Encoder_Init() function.
  *     2.modify the value of ENCODER_ENABLE form encoder.h to encoder the SysTick_Handler
  *     3.add some integration code in SysTick_Handler() from stm32f4xx_it.h
  *     4.add TIMx interrupt handle funtion to stm32f4xx_it.h and clear the IRQ.
  *     5.using funcions in encoder.c to get the information of encoder x.
  ******************************************************************************
**/

#include "encoder.h"
#include "timer.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"
#include "stm32f4xx_rcc.h"

#define ENCODER_TIM_PERIOD (MAX_COUNT*4)    //比 每个定时周期内可能出现的计数最大值 还要大的值. 取值<=65535
#define MAX_COUNT          14436        //每个周期内的最大计数脉冲, 14436=350 r/s
#define COUNTER_RESET    0
#define ICx_FILTER         6

volatile int32_t Encoder_CurPos[4] ={0};
volatile int32_t Encoder_LastPos[4]={0};
volatile int32_t Encoder_dPos[4]   ={0};
volatile int8_t  Encoder_Dir[4]    ={0};

volatile int32_t deltaPos1=1000;
volatile int32_t PosOld1=0;
volatile int32_t PosNew1=0;
volatile int32_t PosCounter1=0;

volatile int32_t deltaPos=1000;
volatile int32_t PosOld=0;
volatile int32_t PosNew=0;
volatile int32_t PosCounter=0;
/**
  * @brief  Initialize the Systick for Encoder. Interrupt per 10ms.
  * @param  None
  * @retval None
  * @author Calcus Lee
**/


void Timer2_ConfigEncoder(void)
{
	TIM_Init(TIM2,999,83,0,0);
}

void Encoder_Init(TIM_TypeDef * EncoderTimer, 
          GPIO_TypeDef * GPIOx,
          uint16_t Encoder_PinA,
          uint16_t Encoder_PinB)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;    
  GPIO_InitTypeDef GPIO_InitStructure;  
  NVIC_InitTypeDef NVIC_InitStructure;
  uint8_t GPIO_PinSourceA=0;
  uint8_t GPIO_PinSourceB=0;
  uint8_t GPIO_AF_TIMx=0;
  //确定Encoder_PinA
  switch(Encoder_PinA)
	{    
		case GPIO_Pin_0:
		{
           GPIO_PinSourceA=GPIO_PinSource0;
		   break;
		}
		case GPIO_Pin_1:
		{
           GPIO_PinSourceA=GPIO_PinSource1;
		   break;
		}
		case GPIO_Pin_2:
		{
           GPIO_PinSourceA=GPIO_PinSource2;
		   break;
		}
		case GPIO_Pin_3:
		{
           GPIO_PinSourceA=GPIO_PinSource3;
		   break;
		}
        case GPIO_Pin_4:
		{
           GPIO_PinSourceA=GPIO_PinSource4;
		   break;
		}
		case GPIO_Pin_5:
		{
           GPIO_PinSourceA=GPIO_PinSource5;
		   break;
		}
		case GPIO_Pin_6:
		{
           GPIO_PinSourceA=GPIO_PinSource6;
		   break;
		}
		case GPIO_Pin_7:
		{
           GPIO_PinSourceA=GPIO_PinSource7;
		   break;
		}
		case GPIO_Pin_8:
		{
           GPIO_PinSourceA=GPIO_PinSource8;
		   break;
		}
		case GPIO_Pin_9:
		{
           GPIO_PinSourceA=GPIO_PinSource9;
		   break;
		}
		case GPIO_Pin_10:
		{
           GPIO_PinSourceA=GPIO_PinSource10;
		   break;
		}
		case GPIO_Pin_11:
		{
           GPIO_PinSourceA=GPIO_PinSource11;
		   break;
		}
		case GPIO_Pin_12:
		{
           GPIO_PinSourceA=GPIO_PinSource12;
		   break;
		}
		case GPIO_Pin_13:
		{
           GPIO_PinSourceA=GPIO_PinSource13;
		   break;
		}
		case GPIO_Pin_14:
		{
           GPIO_PinSourceA=GPIO_PinSource14;
		   break;
		}
		case GPIO_Pin_15:
		{
           GPIO_PinSourceA=GPIO_PinSource15;
		   break;
		}
		
		default: break;
	}
	//确定Encoder_PinB
	switch(Encoder_PinB)
	{    
		case GPIO_Pin_0:
		{
           GPIO_PinSourceB=GPIO_PinSource0;
		   break;
		}
		case GPIO_Pin_1:
		{
           GPIO_PinSourceB=GPIO_PinSource1;
		   break;
		}
		case GPIO_Pin_2:
		{
           GPIO_PinSourceB=GPIO_PinSource2;
		   break;
		}
		case GPIO_Pin_3:
		{
           GPIO_PinSourceB=GPIO_PinSource3;
		   break;
		}
        case GPIO_Pin_4:
		{
           GPIO_PinSourceB=GPIO_PinSource4;
		   break;
		}
		case GPIO_Pin_5:
		{
           GPIO_PinSourceB=GPIO_PinSource5;
		   break;
		}
		case GPIO_Pin_6:
		{
           GPIO_PinSourceB=GPIO_PinSource6;
		   break;
		}
		case GPIO_Pin_7:
		{
           GPIO_PinSourceB=GPIO_PinSource7;
		   break;
		}
		case GPIO_Pin_8:
		{
           GPIO_PinSourceB=GPIO_PinSource8;
		   break;
		}
		case GPIO_Pin_9:
		{
           GPIO_PinSourceB=GPIO_PinSource9;
		   break;
		}
		case GPIO_Pin_10:
		{
           GPIO_PinSourceB=GPIO_PinSource10;
		   break;
		}
		case GPIO_Pin_11:
		{
           GPIO_PinSourceB=GPIO_PinSource11;
		   break;
		}
		case GPIO_Pin_12:
		{
           GPIO_PinSourceB=GPIO_PinSource12;
		   break;
		}
		case GPIO_Pin_13:
		{
           GPIO_PinSourceB=GPIO_PinSource13;
		   break;
		}
		case GPIO_Pin_14:
		{
           GPIO_PinSourceB=GPIO_PinSource14;
		   break;
		}
		case GPIO_Pin_15:
		{
           GPIO_PinSourceB=GPIO_PinSource15;
		   break;
		}

		default: break;
	}
  /* Encoder unit connected to TIMx, 4X mode */
      
  /* TIMx clock source enable */ 
  switch((uint32_t)EncoderTimer)
  {
	//TIMs on APB2
    case TIM1_BASE: 
    {
	GPIO_AF_TIMx=GPIO_AF_TIM1;	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    break;
    }
	case TIM8_BASE: 
    {
	GPIO_AF_TIMx=GPIO_AF_TIM8;	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    break;
    }
	case TIM9_BASE: 
    {
	GPIO_AF_TIMx=GPIO_AF_TIM9;	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    break;
    }     
	//TIMs on APB1
	case TIM2_BASE: 
    {
	GPIO_AF_TIMx=GPIO_AF_TIM2;	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    break;
    }
	case TIM3_BASE: 
    {
	GPIO_AF_TIMx=GPIO_AF_TIM3;	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    break;
    }
	case TIM4_BASE: 
    {
	GPIO_AF_TIMx=GPIO_AF_TIM4;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    break;
    }
    case TIM5_BASE: 
    {
    GPIO_AF_TIMx=GPIO_AF_TIM5;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    break;
    }
	case TIM12_BASE: 
    {
	GPIO_AF_TIMx=GPIO_AF_TIM12;	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
    break;
    }
	
    default: break;
  }

  /* Enable GPIOx, clock */  
  switch((uint32_t)GPIOx)
  {
    case GPIOA_BASE: 
    {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    break;
    }
	case GPIOB_BASE: 
    {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    break;
    }
	case GPIOC_BASE: 
    {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    break;
    }
	case GPIOD_BASE: 
    {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    break;
    }
	case GPIOE_BASE: 
    {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    break;
    }
	case GPIOF_BASE: 
    {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    break;
    }
	case GPIOG_BASE: 
    {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
    break;
    }
	case GPIOH_BASE: 
    {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
    break;
    }
	case GPIOI_BASE: 
    {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
    break;
    }
	
	default: break;
  }
  
    
  GPIO_StructInit(&GPIO_InitStructure); 
  /* Configure encoder pinA and pinB */  
  GPIO_InitStructure.GPIO_Pin = Encoder_PinA | Encoder_PinB; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  
  GPIO_Init(GPIOx, &GPIO_InitStructure);    

  /* Connect TIM pins to AF1 */
    GPIO_PinAFConfig(GPIOx, GPIO_PinSourceA, GPIO_AF_TIMx);
    GPIO_PinAFConfig(GPIOx, GPIO_PinSourceB, GPIO_AF_TIMx);
  
  /* Enable the TIMx Update Interrupt */  
  switch((uint32_t)EncoderTimer)
  {
    case TIM1_BASE:
    {
      NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
      break;
    }
	case TIM2_BASE:
    {
      NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
      break;
    }
	case TIM3_BASE:
    {
      NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
      break;
    }
	case TIM4_BASE:
    {
      NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
      break;
    }
	case TIM5_BASE:
    {
      NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
      break;
    }
	case TIM8_BASE:
    {
      NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
      break;
    }
	case TIM9_BASE:
    {
      NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
      break;
    }
	case TIM12_BASE:
    {
      NVIC_InitStructure.NVIC_IRQChannel = TIM8_BRK_TIM12_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
      break;
    }

    default: break;
  }
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
  NVIC_Init(&NVIC_InitStructure); 
  
  /* Timer configuration in Encoder mode */ 
  TIM_DeInit(EncoderTimer);  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);    
  TIM_TimeBaseStructure.TIM_Prescaler = 0x00;  // No prescaling   
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD - 1;    
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
    
  TIM_TimeBaseInit(EncoderTimer, &TIM_TimeBaseStructure); 
  
  TIM_EncoderInterfaceConfig(EncoderTimer, TIM_EncoderMode_TI12,                              
                TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  
  TIM_ICStructInit(&TIM_ICInitStructure); 
  TIM_ICInitStructure.TIM_ICFilter = ICx_FILTER; 
  TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
  TIM_ICInit(EncoderTimer, &TIM_ICInitStructure);  
  
  TIM_ClearFlag(EncoderTimer, TIM_FLAG_Update);       // Clear all pending interrupts  
  TIM_ITConfig(EncoderTimer, TIM_IT_Update, ENABLE);  //enable TIM_IT_Update interrupt
  
  // Reset counter
  EncoderTimer->CNT = COUNTER_RESET;

  //  ENC_Clear_Speed_Buffer();    
  TIM_Cmd(EncoderTimer, ENABLE);
  
}       
/**
  * @brief  Get the courrent value of  Encoder Timer x.
  * @param  EncoderTimer: TIMx, where x can be 1,2,3,4,5,8,9,12
  * @retval dValue of Encoder Timer
  * @author Calcus Lee
**/
int16_t Encoder_GetStatus0(TIM_TypeDef * EncoderTimer)
{
  static  uint16_t   lastCount = 0;
  uint16_t  curCount = EncoderTimer->CNT;  
  int32_t dCount = curCount - lastCount;  

  if(dCount >= MAX_COUNT)
  {    
	dCount -= ENCODER_TIM_PERIOD;  
  }
  else if(dCount < -MAX_COUNT)
  {    
	dCount += ENCODER_TIM_PERIOD; 
  } 
  lastCount = curCount;
  
  return (int16_t)dCount; 
}

int16_t Encoder_GetStatus1(TIM_TypeDef * EncoderTimer)
{
  static  uint16_t   lastCount = 0;
  uint16_t  curCount = EncoderTimer->CNT;  
  int32_t dCount = curCount - lastCount;  

  if(dCount >= MAX_COUNT)
  {    
	dCount -= ENCODER_TIM_PERIOD;  
  }
  else if(dCount < -MAX_COUNT)
  {    
	dCount += ENCODER_TIM_PERIOD; 
  } 
  lastCount = curCount;
  
  return -(int16_t)dCount; 
}
int16_t Encoder_GetStatus2(TIM_TypeDef * EncoderTimer)
{
  static  uint16_t   lastCount = 0;
  uint16_t  curCount = EncoderTimer->CNT;  
  int32_t dCount = curCount - lastCount;  

  if(dCount >= MAX_COUNT)
  {    
	dCount -= ENCODER_TIM_PERIOD;  
  }
  else if(dCount < -MAX_COUNT)
  {    
	dCount += ENCODER_TIM_PERIOD; 
  } 
  lastCount = curCount;
  
  return (int16_t)dCount; 
}
int16_t Encoder_GetStatus3(TIM_TypeDef * EncoderTimer)
{
  static  uint16_t   lastCount = 0;
  uint16_t  curCount = EncoderTimer->CNT;  
  int32_t dCount = curCount - lastCount;  

  if(dCount >= MAX_COUNT)
  {    
	dCount -= ENCODER_TIM_PERIOD;  
  }
  else if(dCount < -MAX_COUNT)
  {    
	dCount += ENCODER_TIM_PERIOD; 
  } 
  lastCount = curCount;
  
  return (int16_t)dCount; 
}
//int16_t Encoder_GetStatus(TIM_TypeDef * EncoderTimer)
//{
//  return (int16_t)EncoderTimer->CNT;  
//}



/**
  * @brief  Get the courrent value of  Encoder x. 
  * @param  EncoderX: Encoder (in ACTION, that's QEI) 
  * @retval the Position value of QEIx. x range from 0 to 3 
  * @author Calcus Lee
**/
int32_t Encoder_GetPos(uint8_t EncoderX)
{
	return(Encoder_CurPos[EncoderX]);
}

/**
  * @brief  Get the courrent dirction of  Encoder x. 
  * @param  EncoderX: Encoder (in ACTION, that's QEI) 
  * @retval the dirction of QEIx. x range from 0 to 3 
  * @author Calcus Lee
**/
int8_t Encoder_GetDir(uint8_t EncoderX)
{
	return(Encoder_Dir[EncoderX]);
}

/**
  * @brief  Get the Speed of  Encoder x. pulse/s
  * @param  EncoderX: Encoder (in ACTION, that's QEI) 
  * @retval the speed of QEIx. x range from 0 to 3 
  * @author Calcus Lee
**/
int32_t Encoder_GetSpeed(uint8_t EncoderX)
{
	return(Encoder_dPos[EncoderX]*100);   //10ms a circle, use pulse/s as entity
}



