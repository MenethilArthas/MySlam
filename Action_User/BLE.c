#include "BLE.h"
#include "usart.h"
void BLE_Init(void)
{
	UART1_SendString("AT2000000");
}
