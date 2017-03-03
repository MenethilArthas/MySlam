#include "Led_Beep.h"
#include "gpio.h"
#include "flag.h"
	  //  D6:PD4   D7:PD3   D8:PD1    D9:PD0  低电平亮  老板
		//  D6:PB1   D7:PB0   D8:PC5    D9:PC4  低电平亮  新板
void LED_Init(void)
{
#if	ZhuKbanWithOutFuJ
		GPIO_Init_Pins(GPIOD, GPIO_Pin_0,GPIO_Mode_OUT);
		GPIO_Init_Pins(GPIOD, GPIO_Pin_1,GPIO_Mode_OUT);
	  GPIO_Init_Pins(GPIOD, GPIO_Pin_3,GPIO_Mode_OUT);
		GPIO_Init_Pins(GPIOD, GPIO_Pin_4,GPIO_Mode_OUT);
#endif
	

#if	ZhuKbanWithFuJ
		GPIO_Init_Pins(GPIOB, GPIO_Pin_0,GPIO_Mode_OUT);
		GPIO_Init_Pins(GPIOB, GPIO_Pin_1,GPIO_Mode_OUT);
	  GPIO_Init_Pins(GPIOC, GPIO_Pin_4,GPIO_Mode_OUT);
		GPIO_Init_Pins(GPIOC, GPIO_Pin_5,GPIO_Mode_OUT);
#endif	

}

void Led6_ON(void)
{
#if	ZhuKbanWithOutFuJ
	GPIO_ResetBits(GPIOD,GPIO_Pin_4);
#endif

#if	ZhuKbanWithFuJ
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
#endif	
}

void Led7_ON(void)
{
#if	ZhuKbanWithOutFuJ	
	GPIO_ResetBits(GPIOD,GPIO_Pin_3);
#endif
	
#if	ZhuKbanWithFuJ
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
#endif		
}
void Led8_ON(void)
{
#if	ZhuKbanWithOutFuJ		
	GPIO_ResetBits(GPIOD,GPIO_Pin_1);
#endif	
#if	ZhuKbanWithFuJ
	GPIO_ResetBits(GPIOC,GPIO_Pin_5);
#endif
}
void Led9_ON(void)
{
#if	ZhuKbanWithOutFuJ		
	GPIO_ResetBits(GPIOD,GPIO_Pin_0);
#endif	
	
#if	ZhuKbanWithFuJ
	GPIO_ResetBits(GPIOC,GPIO_Pin_4);
#endif	
}



void Led6_OFF(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_4);
}
void Led7_OFF(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_3);
}
void Led8_OFF(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_1);
}
void Led9_OFF(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_0);
}


void QufaiLed6(void)
{
	static uint8_t flag=0;
	if(flag==0)
	{
		Led6_ON();
		flag=1;
	}
	else if(flag==1)
	{
		Led6_OFF();
		flag=0;
	}
}
void QufaiLed7(void)
{
	static uint8_t flag=0;
	if(flag==0)
	{
		Led7_ON();
		flag=1;
	}
	else if(flag==1)
	{
		Led7_OFF();
		flag=0;
	}
}
void QufaiLed8(void)
{
	static uint8_t flag=0;
	if(flag==0)
	{
		Led8_ON();
		flag=1;
	}
	else if(flag==1)
	{
		Led8_OFF();
		flag=0;
	}
}
void QufaiLed9(void)
{
	static uint8_t flag=0;
	if(flag==0)
	{
		Led9_ON();
		flag=1;
	}
	else if(flag==1)
	{
		Led9_OFF();
		flag=0;
	}
}


void Beep_Init(void)
{
//                   PE14  高电平响  老板
//                   PE8   高电平响  新板
#if	ZhuKbanWithOutFuJ
	GPIO_Init_Pins(GPIOE, GPIO_Pin_14,GPIO_Mode_OUT);
#endif
	

#if	ZhuKbanWithFuJ
	GPIO_Init_Pins(GPIOE, GPIO_Pin_8,GPIO_Mode_OUT);
#endif

	
}
void Beep_ON(void)
{
#if	ZhuKbanWithOutFuJ
	GPIO_SetBits(GPIOE,GPIO_Pin_14);	
#endif
	
#if	ZhuKbanWithFuJ
	GPIO_SetBits(GPIOE,GPIO_Pin_8);	
#endif
}

void Beep_OFF(void)
{
#if	ZhuKbanWithOutFuJ
	GPIO_ResetBits(GPIOE,GPIO_Pin_14);	
#endif
	
#if	ZhuKbanWithFuJ
	GPIO_ResetBits(GPIOE,GPIO_Pin_8);	
#endif	
}

