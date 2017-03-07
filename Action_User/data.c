#include "data.h"
#include "stdio.h"
#include "math.h"


CmdVel cmdVel;
Posture pos;
uint8_t input;

int8_t Set_CmdVel(CmdVel *velData)
{
	if(velData==NULL)
		return FALSE;
	else
	{
		cmdVel.angularVel=velData->angularVel;
		cmdVel.linearVel=velData->linearVel;
		return TRUE;
	}

}

int8_t Get_CmdVel(CmdVel *velData)
{
		if(velData==NULL)
			return FALSE;
		else
		{
			velData->angularVel=cmdVel.angularVel;
			velData->linearVel=cmdVel.linearVel;
			return TRUE;
		}
}

int8_t Set_Pos(Posture *posData)
{
	
	if(posData==NULL)
		return FALSE;
	else
	{
		
		pos.y = posData->x ;
		pos.x = posData->y ;
		pos.angle = -posData->angle;
//				pos.y =posData->y;
//		pos.x = posData->x;
//		pos.angle = -posData->angle;
		return TRUE;
	}
}
int8_t Get_Pos(Posture *posData)
{
	if(posData==NULL)
		return FALSE;
	else
	{
		posData->x=pos.x;
		posData->y=pos.y;
		posData->angle=pos.angle;
		return TRUE;
	}
}

void  SetInput(uint8_t Input)
{
	input=Input;
}
uint8_t GetInput(void)
{
	return input;
}
