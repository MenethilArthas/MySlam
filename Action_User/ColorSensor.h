#ifndef __COLORSENSOR_H
#define __COLORSENSOR_H
#include "stm32f4xx.h"

	//色标A out PB0; S2 PB1; S3 PB2
	//色标B out PE7; S2 PE8; S3 PE9
	//色标C out PE11;S2 PC4; S3 PC5
	
	
#define S2_A_On();	GPIO_SetBits(GPIOB,GPIO_Pin_1);
#define S2_A_Off();	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
#define S3_A_On();  GPIO_SetBits(GPIOB,GPIO_Pin_2);
#define S3_A_Off(); GPIO_ResetBits(GPIOB,GPIO_Pin_2);


#define S2_B_On();  GPIO_SetBits(GPIOE,GPIO_Pin_8);               
#define S2_B_Off(); GPIO_ResetBits(GPIOE,GPIO_Pin_8);             
#define S3_B_On();  GPIO_SetBits(GPIOE,GPIO_Pin_9);
#define S3_B_Off(); GPIO_ResetBits(GPIOE,GPIO_Pin_9);

#define S2_C_On();  GPIO_SetBits(GPIOC,GPIO_Pin_4);               
#define S2_C_Off(); GPIO_ResetBits(GPIOC,GPIO_Pin_4);             
#define S3_C_On();  GPIO_SetBits(GPIOC,GPIO_Pin_5);
#define S3_C_Off(); GPIO_ResetBits(GPIOC,GPIO_Pin_5);

void ColorSensorInit_A(void);
void ColorSensorInit_B(void);
void ColorSensorInit_C(void);
void whitebalance_A(void);
void whitebalance_B(void);
void whitebalance_C(void);
void tcs3200_RED_Read_Begine(void);
void  tcs3200_RED_Read_Over(void);
void tcs3200_GREEN_Read_Begine(void);
void  tcs3200_GREEN_Read_Over(void);
void tcs3200_BLUE_Read_Begine(void);
void  tcs3200_BLUE_Read_Over(void);

void Add_Colour_num_A(void);
void Add_Colour_num_B(void);
void Add_Colour_num_C(void);

void Deal_ColorData(void);

float GET_COLOR_A(void);
float GET_COLOR_B(void);
float GET_COLOR_C(void);
#endif



