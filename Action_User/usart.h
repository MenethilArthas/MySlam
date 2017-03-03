#ifndef USART_H 
#define USART_H

#include "stm32f4xx_usart.h"

#define NUM_SIZE 8
#define Arr_SIZE 192


			

void PC_USART2_Init(uint32_t BaudRate);
void GYRO_USART3_Init(uint32_t BaudRate);
void DEBUG_UART4_Init(u32 BaudRate);

void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...);
char *itoa(int value, char *string, int radix);

#endif
