#include "PlayBadminton.h"
#include "copley.h"
#include "elmo.h"
#include "stm32f4xx_gpio.h"
#include "cylinder.h"
#include "timer.h"
#include "flag.h"
#include "usart.h"



//角度脉冲转换
int32_t AngToPulse(double Angle)
{
	return (int32_t)((Angle-158.0)*83.33);               //83.33=15*2000/360
}

//中间球拍转动

void Rotate_Middle(int vel,double arfa)      //vel是速度，arfa是目标角度
{
	PosCfg(6,0,vel,2100000,2100000,10000);
	PosMov(6,POS_ABS,AngToPulse(arfa));
}


//顺时针为正
void LeftBat_S()
{
	PosCfg(5,0,180000,200000,200000,20000);  //机械臂准备
	PosMov(5,POS_ABS,500*91*2.5/6);  
	Rotate_Middle(50000,270);             //手臂准备
}
void RightBat_S()
{
	PosCfg(5,0,180000,200000,200000,20000);  //机械臂准备
	PosMov(5,POS_ABS,1500*91*2.5/6); 
  Rotate_Middle(50000,210);  
}
void MiddleBat_S()
{
	PosCfg(5,0,180000,200000,200000,20000);  //机械臂准备
	PosMov(5,POS_ABS,1000*91*2.5/6); 
  Rotate_Middle(20000,270);  
}

void FaGaoqiu(void)
{
	  uint8_t i=0;
		Rotate_Middle(100000,135.0);
	  shu_shen();
	  di_fang(); //球和夹球气缸一起伸出
	
	
	  SetCar_DaqiuStation();
	  for(i=0;i<20;i++)
	  {
			Usart_Send_XY();
		  TIM_Delayms(TIM5,50);
	  }
		SetCar_BuweiStation();
		
		
		top_shou();//夹球气缸收回 即：将球丢下
		TIM_Delayms(TIM5,20);
		di_shou(); //丢球后将夹球气缸收回
		TIM_Delayms(TIM5,140);
		Rotate_Middle(240000,450.0);  //di:130000    gao: 200000
		TIM_Delayms(TIM5,1000);	
		top_fang();//夹球气缸伸出 为下次夹球做准备！！！！
		Rotate_Middle(100000,270.0);  // di: 255  gao:135
	  shu_shou();
}

void FaDiQianqiu(void)
{
	    uint8_t i=0;
			Rotate_Middle(100000,135.0);  // 
			shu_shou();
			di_fang();	//球和夹球气缸一起伸出	
	
	
	  SetCar_DaqiuStation();
	  for(i=0;i<20;i++)
	  {
			Usart_Send_XY();
		  TIM_Delayms(TIM5,50);
	  }
		SetCar_BuweiStation();
		
		
			top_shou();//夹球气缸收回 即：将球丢下
			TIM_Delayms(TIM5,20);
			di_shou(); //丢球后将夹球气缸收回
			TIM_Delayms(TIM5,170);
			Rotate_Middle(150000,450.0); 
			TIM_Delayms(TIM5,1000);
			top_fang();//夹球气缸伸出 为下次夹球做准备！！！！
			Rotate_Middle(100000,270.0);  // di: 255  gao:135
	    shu_shou();
}
void FaDiHouqiu(void)
{
	    uint8_t i=0;
			Rotate_Middle(100000,135.0);  // 
			shu_shou();
			di_fang();	//球和夹球气缸一起伸出	
	
				SetCar_DaqiuStation();
				for(i=0;i<20;i++)
				{
					Usart_Send_XY();
					TIM_Delayms(TIM5,50);
				}	
		   SetCar_BuweiStation();
				
				
			top_shou();//夹球气缸收回 即：将球丢下
			TIM_Delayms(TIM5,20);
			di_shou(); //丢球后将夹球气缸收回
			TIM_Delayms(TIM5,190);
			Rotate_Middle(160000,450.0); 
			TIM_Delayms(TIM5,1000);
			top_fang();//夹球气缸伸出 为下次夹球做准备！！！！
			Rotate_Middle(100000,270.0);  // di: 255  gao:135
	    shu_shou();
}
void CarAAA_BiPai_Init(void)
{
	
#if  Copley
{
    HomeMode(5,-2,5000,5000,5000);//机械臂home模式    新车逆时针-1     老车顺时针 -2
}
#endif	

		TIM_Delayms(TIM5,2000);
		HomeMode(6,-1,5000,5000,5000);//球拍home模式
    TIM_Delayms(TIM5,500);
		
		
		
		PosCfg(6,0,10000,20000,20000,10000);  //球拍抬一点
		PosMov(6,POS_ABS,-83.33*23.33);    
		TIM_Delayms(TIM5,1000);
	
#if  Copley
{
		PosCfg(5,0,100000,20000,20000,2000);  //机械臂准备
		PosMov(5,POS_ABS,1000*91*2.5/6);      // 新车- 老车+
}
#endif

#if  Elmo
{
		 PosCfg_elmo(5,0,20000,300000,300000);
		 PosMov_elmo(5,POS_ABS,1000*91*2.5/6);
}
#endif		
 
		TIM_Delayms(TIM5,2000);
		PosMov(6,POS_ABS,9332);
		TIM_Delayms(TIM5,2000);
}

