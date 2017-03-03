#include "exti.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"
#include "stm32f4xx_rcc.h"


/**
  * @brief  Configures EXTI Line0 (connected to PA0 pin) in interrupt mode
  * @param  None
  * @retval None
  */
void EXTI_Config(GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin_x )
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	uint8_t  EXTI_PortSourceGPIOx=0;
	uint8_t  EXTI_PinSourcex=0;
    uint32_t EXTI_Linex=0;
	                             
  /* Enable GPIOx clock */
	switch((uint32_t)GPIOx)
	{
		case GPIOA_BASE: 
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
			EXTI_PortSourceGPIOx=EXTI_PortSourceGPIOA;	
			break;
		}
		case GPIOB_BASE: 
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
			EXTI_PortSourceGPIOx=EXTI_PortSourceGPIOB;
			break;
		}
		case GPIOC_BASE: 
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
			EXTI_PortSourceGPIOx=EXTI_PortSourceGPIOC;
			break;
		}
		case GPIOD_BASE: 
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
			EXTI_PortSourceGPIOx=EXTI_PortSourceGPIOD;
			break;
		}
		case GPIOE_BASE: 
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
			EXTI_PortSourceGPIOx=EXTI_PortSourceGPIOE;
			break;
		}
		case GPIOF_BASE: 
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
			EXTI_PortSourceGPIOx=EXTI_PortSourceGPIOF;
			break;
		}
		case GPIOG_BASE: 
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
			EXTI_PortSourceGPIOx=EXTI_PortSourceGPIOG;
			break;
		}
		case GPIOH_BASE: 
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
			EXTI_PortSourceGPIOx=EXTI_PortSourceGPIOH;
			break;
		}
		case GPIOI_BASE: 
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
			EXTI_PortSourceGPIOx=EXTI_PortSourceGPIOH;
			break;
		}
		
		default: break;
	}
	
	switch(GPIO_Pin_x)
	{    
		case GPIO_Pin_0:
		{
			EXTI_PinSourcex=EXTI_PinSource0;
			EXTI_Linex=EXTI_Line0;
			NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
		   break;
		}
		case GPIO_Pin_1:
		{
		  EXTI_PinSourcex=EXTI_PinSource1;
			EXTI_Linex=EXTI_Line1;
			NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
		   break;
		}
		case GPIO_Pin_2:
		{
		  EXTI_PinSourcex=EXTI_PinSource2;
			EXTI_Linex=EXTI_Line2;
			NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
		   break;
		}
		case GPIO_Pin_3:
		{
           EXTI_PinSourcex=EXTI_PinSource3;
			EXTI_Linex=EXTI_Line3;
			NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
			break;
		}
        case GPIO_Pin_4:
		{
           EXTI_PinSourcex=EXTI_PinSource4;
			EXTI_Linex=EXTI_Line4;
			NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
			break;
		}
		case GPIO_Pin_5:
		{
           EXTI_PinSourcex=EXTI_PinSource5;
			EXTI_Linex=EXTI_Line5;
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
			break;
		}
		case GPIO_Pin_6:
		{
           EXTI_PinSourcex=EXTI_PinSource6;
			EXTI_Linex=EXTI_Line6;
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
		   break;
		}
		case GPIO_Pin_7:
		{
           EXTI_PinSourcex=EXTI_PinSource7;
			EXTI_Linex=EXTI_Line7;
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
		   break;
		}
		case GPIO_Pin_8:
		{
           EXTI_PinSourcex=EXTI_PinSource8;
			EXTI_Linex=EXTI_Line8;
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
		   break;
		}
		case GPIO_Pin_9:
		{
           EXTI_PinSourcex=EXTI_PinSource9;
			EXTI_Linex=EXTI_Line9;
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
			break;
		}
		case GPIO_Pin_10:
		{
           EXTI_PinSourcex=EXTI_PinSource10;
			EXTI_Linex=EXTI_Line10;
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	
			break;
		}
		case GPIO_Pin_11:
		{
           EXTI_PinSourcex=EXTI_PinSource11;
			EXTI_Linex=EXTI_Line11;
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	
		   break;
		}
		case GPIO_Pin_12:
		{
           EXTI_PinSourcex=EXTI_PinSource12;
			EXTI_Linex=EXTI_Line12;
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	
		   break;
		}
		case GPIO_Pin_13:
		{
           EXTI_PinSourcex=EXTI_PinSource13;
			EXTI_Linex=EXTI_Line13;
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	
		   break;
		}
		case GPIO_Pin_14:
		{
           EXTI_PinSourcex=EXTI_PinSource14;
			EXTI_Linex=EXTI_Line14;
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	
		   break;
		}
		case GPIO_Pin_15:
		{
           EXTI_PinSourcex=EXTI_PinSource15;
			EXTI_Linex=EXTI_Line15;
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	
		   break;
		}
		
		default: break;
	}
	/* Enable SYSCFG clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Configure PA0 pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
	GPIO_Init(GPIOx, &GPIO_InitStructure);
                                                   
	/* Connect EXTI Line0 to PA0 pin */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOx, EXTI_PinSourcex);

	/* Configure EXTI Linex */
	EXTI_InitStructure.EXTI_Line = EXTI_Linex;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
