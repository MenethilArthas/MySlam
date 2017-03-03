#include "stm32f4xx_tim.h"

#define ENCODER_ENABLE 1

void Timer2_ConfigEncoder(void);
void Encoder_Init(TIM_TypeDef * EncoderTimer, 
          GPIO_TypeDef * GPIOx,
          uint16_t Encoder_PinA,
          uint16_t Encoder_PinB);
			  
int16_t Encoder_GetStatus0(TIM_TypeDef * EncoderTimer);
int16_t Encoder_GetStatus1(TIM_TypeDef * EncoderTimer);
int16_t Encoder_GetStatus2(TIM_TypeDef * EncoderTimer);
int16_t Encoder_GetStatus3(TIM_TypeDef * EncoderTimer);
int32_t Encoder_GetPos(uint8_t EncoderX);

int8_t Encoder_GetDir(uint8_t EncoderX);

int32_t Encoder_GetSpeed(uint8_t EncoderX);
