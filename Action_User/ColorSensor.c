#include "ColorSensor.h"
#include "gpio.h"
#include "timer.h"
#include "stm32f4xx_exti.h"
#include "math.h"

 u32 Colour_num_A=0;								  // 用于颜色传感器脉冲计数
 u16 Rgena_A,Ggena_A,Bgena_A;
 u16 Ramount_A,Gamount_A,Bamount_A;


 u32 Colour_num_B=0;	
 u16 Rgena_B,Ggena_B,Bgena_B;
 u16 Ramount_B,Gamount_B,Bamount_B;

 u32 Colour_num_C=0;	
 u16 Rgena_C,Ggena_C,Bgena_C;
 u16 Ramount_C,Gamount_C,Bamount_C;

 u16 R_A=0x00,G_A=0x00,B_A=0x00;
 u16 R_B=0x00,G_B=0x00,B_B=0x00;
 u16 R_C=0x00,G_C=0x00,B_C=0x00;



void ColorSensorInit_A(void)
{
  //色标A out PB0; S2 PB1; S3 PB2
  GPIO_Init_Pins(GPIOB, GPIO_Pin_1,GPIO_Mode_OUT);   //S2 PB1;
	GPIO_Init_Pins(GPIOB, GPIO_Pin_2,GPIO_Mode_OUT);   //S3 PB2;
	GPIO_Init_Pins(GPIOB, GPIO_Pin_0,GPIO_Mode_IN);    //out PB0;
}

void ColorSensorInit_B(void)
{
  //色标B out PE7; S2 PE8; S3 PE9
  GPIO_Init_Pins(GPIOE, GPIO_Pin_8,GPIO_Mode_OUT);   //S2 PE8;
	GPIO_Init_Pins(GPIOE, GPIO_Pin_9,GPIO_Mode_OUT);   //S3 PE9;
	GPIO_Init_Pins(GPIOE, GPIO_Pin_7,GPIO_Mode_IN);    //out PE7;
}

void ColorSensorInit_C(void)
{
  //色标C out PE11;S2 PC4; S3 PC5
  GPIO_Init_Pins(GPIOC, GPIO_Pin_4,GPIO_Mode_OUT);   //S2 PC4;
	GPIO_Init_Pins(GPIOC, GPIO_Pin_5,GPIO_Mode_OUT);   //S3 PC5;
	GPIO_Init_Pins(GPIOE, GPIO_Pin_11,GPIO_Mode_IN);    //out PE11;
}








/*******************************************
*
*		  白平衡
*
*******************************************/
void whitebalance_A(void)
{

	S2_A_Off();S3_A_Off();  		//红色通道0
  Colour_num_A=0;			  		//开始计数
	TIM_Delayms(TIM5,1);
	Rgena_A = Colour_num_A; 		//求出红色因子      

//----------------------------------
	S2_A_On();S3_A_On();       	//绿色通道
  Colour_num_A=0;
	TIM_Delayms(TIM5,1);
	Ggena_A = Colour_num_A;   	//求出绿色因子

//----------------------------------
	S2_A_Off();S3_A_On();			  //蓝色通道
 	Colour_num_A=0;
	TIM_Delayms(TIM5,1);
	Bgena_A = Colour_num_A;	  	//求出蓝色因子
  S2_A_On();S3_A_Off();				//关闭通道  	  
}
void whitebalance_B(void)
{

	S2_B_Off();S3_B_Off();  		//红色通道0
  Colour_num_B=0;			  		//开始计数
	TIM_Delayms(TIM5,1);
	Rgena_B = Colour_num_B; 		//求出红色因子       

//----------------------------------
	S2_B_On();S3_B_On();       	//绿色通道
  Colour_num_B=0;
	TIM_Delayms(TIM5,1);
	Ggena_B = Colour_num_B;   	//求出绿色因子

//----------------------------------
	S2_B_Off();S3_B_On();			  //蓝色通道
 	Colour_num_B=0;
	TIM_Delayms(TIM5,1);
	Bgena_B = Colour_num_B;	  	//求出蓝色因子
  S2_B_On();S3_B_Off();				//关闭通道  	  
}

void whitebalance_C(void)
{

	S2_C_Off();S3_C_Off();  		//红色通道0
  Colour_num_C=0;			  		//开始计数
	TIM_Delayms(TIM5,1);
	Rgena_C = Colour_num_C; 		//求出红色因子      

//----------------------------------
	S2_C_On();S3_C_On();       	//绿色通道
  Colour_num_C=0;
	TIM_Delayms(TIM5,1);
	Ggena_C = Colour_num_C;   	//求出绿色因子

//----------------------------------
	S2_C_Off();S3_C_On();			  //蓝色通道
 	Colour_num_C=0;
	TIM_Delayms(TIM5,1);
	Bgena_C = Colour_num_C;	  	//求出蓝色因子
  S2_C_On();S3_C_Off();				//关闭通道  	  
}


void tcs3200_RED_Read_Begine(void)
{
	S2_A_Off();S3_A_Off();
 	Colour_num_A=0;
	S2_B_Off();S3_B_Off();
 	Colour_num_B=0;
	S2_C_Off();S3_C_Off();
 	Colour_num_C=0;
}

void  tcs3200_RED_Read_Over(void)
{
	Ramount_A=(u32) Colour_num_A*255/Rgena_A;	 //取R值
	if(Ramount_A>255) Ramount_A = 255;
	R_A=Ramount_A;
	
	Ramount_B=(u32) Colour_num_B*255/Rgena_B;	 //取R值
	if(Ramount_B>255) Ramount_B = 255;
	R_B=Ramount_B;
	
	Ramount_C=(u32) Colour_num_C*255/Rgena_C;	 //取R值
	if(Ramount_C>255) Ramount_C = 255;
	R_C=Ramount_C;	
}




void tcs3200_GREEN_Read_Begine(void)
{
	S2_A_On();S3_A_On();
 	Colour_num_A=0;
	S2_B_On();S3_B_On();
 	Colour_num_B=0;
	S2_C_On();S3_C_On();
 	Colour_num_C=0;
}

void  tcs3200_GREEN_Read_Over(void)
{
	Gamount_A=(u32) Colour_num_A*255/Ggena_A;	 //取G值
	if(Gamount_A>255) Gamount_A = 255;
	G_A=Gamount_A;
	
	Gamount_B=(u32) Colour_num_B*255/Ggena_B;	 //取G值
	if(Gamount_B>255) Gamount_B = 255;
	G_B=Gamount_B;
	
	Gamount_C=(u32) Colour_num_C*255/Ggena_C;	 //取G值
	if(Gamount_C>255) Gamount_C = 255;
	G_C=Gamount_C;	
}


void tcs3200_BLUE_Read_Begine(void)
{
	S2_A_Off();S3_A_On();
 	Colour_num_A=0;
	S2_B_Off();S3_B_On();
 	Colour_num_B=0;
	S2_C_Off();S3_C_On();
 	Colour_num_C=0;
}

void  tcs3200_BLUE_Read_Over(void)
{
	Bamount_A=(u32) Colour_num_A*255/Bgena_A;	 //取B值
	if(Bamount_A>255) Bamount_A = 255;
	B_A=Bamount_A;
	
	Bamount_B=(u32) Colour_num_B*255/Bgena_B;	 //取B值
	if(Bamount_B>255) Bamount_B = 255;
	B_B=Bamount_B;
	
	Bamount_C=(u32) Colour_num_C*255/Bgena_C;	 //取B值
	if(Bamount_C>255) Bamount_C = 255;
	B_C=Bamount_C;	

}

 static	float H_A=0;
 static float H_B=0;
 static	float H_C=0;
void Deal_ColorData(void)
{
	/*****************************AAAAAAAAAAAAAAAAAAAAAAAA*************************/
    if((R_A<G_A)&&(B_A<G_A)) 
		{
			if(G_A<=150)   H_A=140; 
			if((G_A>150)&&((G_A-R_A)>30)&&((G_A-B_A)>30))  H_A=140;         
		}
	  else if((R_A>=190)&&(G_A>=190)&&(B_A>=190)&&(fabs(R_A-G_A)<30)&&(fabs(R_A-B_A)<30))      H_A=240;        //白色
    else if(((R_A>=220)&&(G_A>=220)&&(B_A<=200)) ||((R_A-B_A)>30&&((G_A-B_A)>30)&&(fabs((G_A-R_A))<((R_A-B_A)))))   H_A=60; 
   /*****************************BBBBBBBBBBBBBBBBBBBBBBBBBBB*************************/
		 if((R_B<G_B)&&(B_B<G_B)) 
		{
			if(G_B<=150)   H_B=140; 
			if((G_B>150)&&((G_B-R_B)>30)&&((G_B-B_B)>30))  H_B=140;         
		}
	  else if((R_B>=190)&&(G_B>=190)&&(B_B>=190)&&(fabs(R_B-G_B)<30)&&(fabs(R_B-B_B)<30))      H_B=240;        //白色
    else if(((R_B>=220)&&(G_B>=220)&&(B_B<=200)) ||((R_B-B_B)>30&&((G_B-B_B)>30)&&(fabs((G_B-R_B))<((R_B-B_B)))))   H_B=60; 
		/*****************************CCCCCCCCCCCCCCCCCCCCCCCCCCC*************************/
     if((R_C<G_C)&&(B_C<G_C)) 
		{
			if(G_C<=150)   H_C=140; 
			if((G_C>150)&&((G_C-R_C)>30)&&((G_C-B_C)>30))  H_C=140;         
		}
	  else if((R_C>=190)&&(G_C>=190)&&(B_C>=190)&&(fabs(R_C-G_C)<30)&&(fabs(R_C-B_C)<30))      H_C=240;        //白色
    else if(((R_C>=220)&&(G_C>=220)&&(B_C<=200)) ||((R_C-B_C)>30&&((G_C-B_C)>30)&&(fabs((G_C-R_C))<((R_C-B_C)))))   H_C=60; 
}

void Add_Colour_num_A(void)
{
	Colour_num_A++;
}

void Add_Colour_num_B(void)
{
	Colour_num_B++;
}

void Add_Colour_num_C(void)
{
	Colour_num_C++;
}
float GET_COLOR_A(void)
{
	return H_A;
}

float GET_COLOR_B(void)
{
	return H_B;
}

float GET_COLOR_C(void)
{
	return H_C;
}



