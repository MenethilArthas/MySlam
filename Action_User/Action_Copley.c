#include "Action_Copley.h"
#include "can.h"

CANDATA_TRANS  CANData_Trans;				/*发送的数据*/
static int Car_L_Vel=0,Car_R_Vel=0;

void VelCfg_Action(uint32_t Motor_Num,uint32_t Acc_Vel,uint32_t Dec_Vel)
{
	
	
	
	uint8_t mbox;
	CanTxMsg TxMessage;

	TxMessage.StdId=Motor_Num;					 // standard identifier=0
	TxMessage.ExtId=Motor_Num;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			 // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			 // the type of frame for the message that will be transmitted
	TxMessage.DLC=5;						 //
	
	
	/****************Acc**************************/
	
	CANData_Trans.uint8[4]=VelCfgCmd+100;
	CANData_Trans.int32[0]=Acc_Vel;

	TxMessage.Data[0] =CANData_Trans.uint8[0];
	TxMessage.Data[1] =CANData_Trans.uint8[1];
	TxMessage.Data[2] =CANData_Trans.uint8[2];
	TxMessage.Data[3] =CANData_Trans.uint8[3];
	TxMessage.Data[4] =CANData_Trans.uint8[4];

		 
	mbox= CAN_Transmit(CAN1, &TxMessage);   
	while((CAN_TransmitStatus(CAN1, mbox)!= CAN_TxStatus_Ok)){};



	/****************Dec**************************/

	CANData_Trans.uint8[4]=VelCfgCmd+200;
	CANData_Trans.int32[0]=Dec_Vel;

	TxMessage.Data[0] =CANData_Trans.uint8[0];
	TxMessage.Data[1] =CANData_Trans.uint8[1];
	TxMessage.Data[2] =CANData_Trans.uint8[2];
	TxMessage.Data[3] =CANData_Trans.uint8[3];
	TxMessage.Data[4] =CANData_Trans.uint8[4];

       
	mbox= CAN_Transmit(CAN1, &TxMessage);   
	while((CAN_TransmitStatus(CAN1, mbox)!= CAN_TxStatus_Ok)){};


	return;
}

void VelCrl(uint32_t Motor_Num,int Speed_Vel)
{
	
	
	
	uint8_t mbox;
	CanTxMsg TxMessage;

	TxMessage.StdId=Motor_Num;					 // standard identifier=0
	TxMessage.ExtId=Motor_Num;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			 // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			 // the type of frame for the message that will be transmitted
	TxMessage.DLC=5;						 //
	
	
	/****************Acc**************************/
	
	CANData_Trans.uint8[4]=VelAdjCmd;
	CANData_Trans.int32[0]=Speed_Vel;

	TxMessage.Data[0] =CANData_Trans.uint8[0];
	TxMessage.Data[1] =CANData_Trans.uint8[1];
	TxMessage.Data[2] =CANData_Trans.uint8[2];
	TxMessage.Data[3] =CANData_Trans.uint8[3];
	TxMessage.Data[4] =CANData_Trans.uint8[4];

       
	mbox= CAN_Transmit(CAN1, &TxMessage);   
	while((CAN_TransmitStatus(CAN1, mbox)!= CAN_TxStatus_Ok)){};

	return;
}

int GetCar_L_V(void)
{
	return Car_L_Vel;
}
int GetCar_R_V(void)
{
	return Car_R_Vel;
}


void SetVel(uint16_t Sbus_Channel_Temp2 ,uint16_t Sbus_Channel_Temp3)
{
	Car_L_Vel=-250*(Sbus_Channel_Temp3-1024)-100*(Sbus_Channel_Temp2-1024);
	Car_R_Vel=+250*(Sbus_Channel_Temp3-1024)-100*(Sbus_Channel_Temp2-1024);
	/*记得加速度限制*/
	if(Car_L_Vel>200000)
	{
		Car_L_Vel=200000;
	}
		if(Car_L_Vel<-200000)
	{
		Car_L_Vel=-200000;
	}
		if(Car_R_Vel>200000)
	{
		Car_R_Vel=200000;
	}
	if(Car_R_Vel<-200000)
	{
		Car_R_Vel=-200000;
	}
}


