#ifndef __DATA_H
#define __DATA_H

#include "stdint.h"

#define FALSE  0
#define TRUE   1

#define LINEAR_SCALE    30
#define ANGULAR_SCALE   10

typedef struct CMD_VEL
{
	int16_t linearVel;
	int16_t angularVel;
}CmdVel;

typedef struct POS
{
	float x;
	float y;
	float angle;
}Posture;


int8_t Set_CmdVel(CmdVel *velData);
int8_t Get_CmdVel(CmdVel *velData);

int8_t Set_Pos(Posture *posData);
int8_t Get_Pos(Posture *posData);

void  SetInput(uint8_t input);
uint8_t GetInput(void);
void MotionCtrl(uint8_t cmd);
#endif
