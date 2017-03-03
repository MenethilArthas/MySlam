#ifndef __GYRO_h
#define __GYRO_h
#include "stm32f4xx.h"

union Gyro
{
	uint8_t GyroData[4];
	float GyroAngle;
};

void SetGyro_Angle(float angle);
float GetGyro_Angle(void);
#endif

