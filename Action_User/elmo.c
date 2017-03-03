#include "elmo.h"
#include "can.h"


void CAN1OPEN_elmo_Init(uint8_t CopleyNum)
{  

	
	uint8_t mbox;
	CanTxMsg TxMessage;
	TxMessage.StdId=0x600+CopleyNum;					 // standard identifier=0
	TxMessage.ExtId=0x600+CopleyNum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			 // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			 // the type of frame for the message that will be transmitted
	TxMessage.DLC=8;						 // 发送两帧信息

		 TxMessage.Data[0] = 0x2b;
	   TxMessage.Data[1] = 0x17;
	   TxMessage.Data[2] = 0x10;
	   TxMessage.Data[3] = 0x00;
	   TxMessage.Data[4] = 0xff;
	   TxMessage.Data[5] = 0x7f;
	   TxMessage.Data[6] = 0x00;
	   TxMessage.Data[7] = 0x00;
  
	mbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
	while((CAN_TransmitStatus(CAN1, mbox)!= CAN_TxStatus_Ok));//等待238us

		 TxMessage.Data[0] = 0x2b;
	   TxMessage.Data[1] = 0x40;
	   TxMessage.Data[2] = 0x60;
	   TxMessage.Data[3] = 0x00;
	   TxMessage.Data[4] = 0x0e;
	   TxMessage.Data[5] = 0x00;
	   TxMessage.Data[6] = 0x00;
	   TxMessage.Data[7] = 0x00;
  
	mbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
	while((CAN_TransmitStatus(CAN1, mbox)!= CAN_TxStatus_Ok));//等待238us
	

		 TxMessage.Data[0] = 0x2b;
	   TxMessage.Data[1] = 0x40;
	   TxMessage.Data[2] = 0x60;
	   TxMessage.Data[3] = 0x00;
	   TxMessage.Data[4] = 0x0f;
	   TxMessage.Data[5] = 0x00;
	   TxMessage.Data[6] = 0x00;
	   TxMessage.Data[7] = 0x00;
  
	mbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
	while((CAN_TransmitStatus(CAN1, mbox)!= CAN_TxStatus_Ok));//等待238us

		 TxMessage.Data[0] = 0x2b;
	   TxMessage.Data[1] = 0x40;
	   TxMessage.Data[2] = 0x60;
	   TxMessage.Data[3] = 0x00;
	   TxMessage.Data[4] = 0x0f;
	   TxMessage.Data[5] = 0x00;
	   TxMessage.Data[6] = 0x00;
	   TxMessage.Data[7] = 0x00;
  
	mbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
	while((CAN_TransmitStatus(CAN1, mbox)!= CAN_TxStatus_Ok));//等待238us



}


void VelCfg_elmo(uint8_t CopleyNum,uint32_t acc,uint32_t dec)
{
	 uint8_t mbox;
	uint16_t i=0;
	CanTxMsg TxMessage;

	
	 uint32_t data[3][2]=
	 {  
		 0x0060602F,0x00000003,	///Profile Velocity mode.   
		0x00608323,0,		  	//Profile acceleration
		0x00608423,0,  			//PROFILE deceleration
	 };
	 
	data[1][1]= acc ; 		
	data[2][1] = dec;
	TxMessage.StdId=0x600+CopleyNum;					 // standard identifier=0
	TxMessage.ExtId=0x600+CopleyNum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			 // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			 // the type of frame for the message that will be transmitted
	TxMessage.DLC=8;	
	
	 
		for(i=0;i<3;i++)
	  {	    
	    //msg[4].data=*(unsigned long long*)&data[i];	  	
		TxMessage.Data[0] = *(unsigned long*)&data[i][0]&0xff;
		TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>8)&0xff;
		TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>16)&0xff;
		TxMessage.Data[3] = (*(unsigned long*)&data[i][0]>>24)&0xff;
		TxMessage.Data[4] = *(unsigned long*)&data[i][1]&0xff;
		TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>8)&0xff;
		TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>16)&0xff;
		TxMessage.Data[7] = (*(unsigned long*)&data[i][1]>>24)&0xff;
			
		mbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
		while((CAN_TransmitStatus(CAN1, mbox)!= CAN_TxStatus_Ok));//等待238us

	  }

}
 

void VelMov_elmo( uint8_t CopleyNum,int32_t vel )   //耗时1.24ms
{

  uint8_t mbox;

	CanTxMsg TxMessage;
	
	uint32_t data[1][2]=
	{
		0x0060FF23,0 		    //target velocity	  
	};
	TxMessage.StdId=0x600+CopleyNum;					 // standard identifier=0
	TxMessage.ExtId=0x600+CopleyNum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			 // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			 // the type of frame for the message that will be transmitted
	TxMessage.DLC=8;	
	data[0][1]=vel;
		TxMessage.Data[0] = *(unsigned long*)&data[0][0]&0xff;
		TxMessage.Data[1] = (*(unsigned long*)&data[0][0]>>8)&0xff;
		TxMessage.Data[2] = (*(unsigned long*)&data[0][0]>>16)&0xff;
		TxMessage.Data[3] = (*(unsigned long*)&data[0][0]>>24)&0xff;
		TxMessage.Data[4] = *(unsigned long*)&data[0][1]&0xff;
		TxMessage.Data[5] = (*(unsigned long*)&data[0][1]>>8)&0xff;
		TxMessage.Data[6] = (*(unsigned long*)&data[0][1]>>16)&0xff;
		TxMessage.Data[7] = (*(unsigned long*)&data[0][1]>>24)&0xff;
			
		mbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
		while((CAN_TransmitStatus(CAN1, mbox)!= CAN_TxStatus_Ok));//等待238us

}



void Enable_elmo(uint8_t CopleyNum)
{
	 uint8_t mbox;
	CanTxMsg TxMessage;
	TxMessage.StdId=0x600+CopleyNum;					 // standard identifier=0
	TxMessage.ExtId=0x600+CopleyNum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			 // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			 // the type of frame for the message that will be transmitted
	TxMessage.DLC=8;	
		 TxMessage.Data[0] = 0x2b;
	   TxMessage.Data[1] = 0x40;
	   TxMessage.Data[2] = 0x60;
	   TxMessage.Data[3] = 0x00;
	   TxMessage.Data[4] = 0x0f;
	   TxMessage.Data[5] = 0x00;
	   TxMessage.Data[6] = 0x00;
	   TxMessage.Data[7] = 0x00;
  
	mbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
	while((CAN_TransmitStatus(CAN1, mbox)!= CAN_TxStatus_Ok));//等待238us
}
void Disable_elmo(uint8_t CopleyNum)
{
	 uint8_t mbox;
	CanTxMsg TxMessage;
	TxMessage.StdId=0x600+CopleyNum;					 // standard identifier=0
	TxMessage.ExtId=0x600+CopleyNum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			 // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			 // the type of frame for the message that will be transmitted
	TxMessage.DLC=8;	
		 TxMessage.Data[0] = 0x2b;
	   TxMessage.Data[1] = 0x40;
	   TxMessage.Data[2] = 0x60;
	   TxMessage.Data[3] = 0x00;
	   TxMessage.Data[4] = 0x07;
	   TxMessage.Data[5] = 0x00;
	   TxMessage.Data[6] = 0x00;
	   TxMessage.Data[7] = 0x00;
  
	mbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
	while((CAN_TransmitStatus(CAN1, mbox)!= CAN_TxStatus_Ok));//等待238us
}


void PosCfg_elmo(uint8_t CopleyNum,
			uint8_t TrapScurve,
			uint32_t vel,
			uint32_t acc,
			uint32_t dec)
{

    uint8_t i=0;
	uint32_t data[6][2]=
	{  
		0x0060602F,0x00000001,	//Profile Position mode. 
		
		0x00608123,0,	  		//Profile Velocity
		0x00608323,0,	  		//Profile Acceleration  
		0x00608423,0,	  		//Profile Deceleration   
		0x0060862B,0,	   	   	//motion profile type, Trapezoidal profile mode
    0x00212123,100			//Trajectory Jerk Limit   		
	};
	uint8_t mbox;
	CanTxMsg TxMessage;
	TxMessage.StdId=0x600+CopleyNum;					 // standard identifier=0
	TxMessage.ExtId=0x600+CopleyNum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			 // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			 // the type of frame for the message that will be transmitted
	TxMessage.DLC=8;	

	data[1][1] = dec; 
	data[2][1]=  vel; 		
	data[3][1] = acc;
	data[4][1] = TrapScurve;

	
	  for(i=0;i<6;i++)
	  {	    
	    //msg[4].data=*(unsigned long long*)&data[i];	  	
		TxMessage.Data[0] = *(unsigned long*)&data[i][0]&0xff;
		TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>8)&0xff;
		TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>16)&0xff;
		TxMessage.Data[3] = (*(unsigned long*)&data[i][0]>>24)&0xff;
		TxMessage.Data[4] = *(unsigned long*)&data[i][1]&0xff;
		TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>8)&0xff;
		TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>16)&0xff;
		TxMessage.Data[7] = (*(unsigned long*)&data[i][1]>>24)&0xff;
			
		mbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
		while((CAN_TransmitStatus(CAN1, mbox)!= CAN_TxStatus_Ok));//等待238us

	  }
		
		

}


void PosMov_elmo( uint8_t CopleyNum,uint8_t rel_abs,int32_t pos )
{
	uint8_t i=0;
	uint32_t data[4][2]=
	{           
		0x00607A23,0,	  		 //pos
		0x0060402B,0x0000001F,	 //Control word,Switch On,Enable Voltage,Quick Stop,Enable Operation
		0x0060412B,0x00004103,	
	  0x0060402B,0,	
	};
	
	uint8_t mbox;
	CanTxMsg TxMessage;
	TxMessage.StdId=0x600+CopleyNum;					 // standard identifier=0
	TxMessage.ExtId=0x600+CopleyNum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			 // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			 // the type of frame for the message that will be transmitted
	TxMessage.DLC=8;	

	data[0][1]=pos;
	
	
	if(rel_abs == POS_REL)
	{	
		data[3][1] = 0x006f;
	}
	else
	{	
		data[3][1] = 0x002f;
	}	
	
    for(i=0;i<4;i++)
	  {
				//msg[4].data=*(unsigned long long*)&data[i];	  	
			TxMessage.Data[0] = *(unsigned long*)&data[i][0]&0xff;
			TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>8)&0xff;
			TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>16)&0xff;
			TxMessage.Data[3] = (*(unsigned long*)&data[i][0]>>24)&0xff;
			TxMessage.Data[4] = *(unsigned long*)&data[i][1]&0xff;
			TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>8)&0xff;
			TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>16)&0xff;
			TxMessage.Data[7] = (*(unsigned long*)&data[i][1]>>24)&0xff;
				
			mbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
			while((CAN_TransmitStatus(CAN1, mbox)!= CAN_TxStatus_Ok));//等待238us

	  }
	
}

void HomeMode_elmo(uint8_t CopleyNum,int8_t home_method,uint32_t home_fast,uint32_t home_slow,uint32_t home_acc)
{ 
	uint8_t i=0;
	
 	uint32_t data[10][2]=
	{
		 0x0060602F,0x00000006,
	   0x0060402B,0x0000000F,	   //2b 40 60 00 0f 00 00 00   关闭home模式
	   0x01609923,		   0,	  //home_fast
	   0x02609923,	       0,	  //home_slow
	   0x00609A23,		   0,	  //home_acc
	   0x00607C23,         0,	  //offset	  // 26774
	   0x0060982F,         0,	  //home_method
	   0x0023512B,0x0000000a,     //delaytime  10             Units:milliseconds
	   0x0023502B,0x00000032,	  //homecurrent	  //  Units:0.01A
	   0x0060402B,0x0000001F, 	  //启动HOME模式	
	};
	
	uint8_t mbox;
	CanTxMsg TxMessage;
	TxMessage.StdId=0x600+CopleyNum;					 // standard identifier=0
	TxMessage.ExtId=0x600+CopleyNum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			 // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			 // the type of frame for the message that will be transmitted
	TxMessage.DLC=8;	
	

	
 	data[2][1] = home_fast;
	data[3][1] = home_slow ; 		
	data[4][1] = home_acc;
	data[6][1] = home_method;
	
    for(i=0;i<10;i++)
	  {	    
	    //msg[4].data=*(unsigned long long*)&data[i];	  	
			TxMessage.Data[0] = *(unsigned long*)&data[i][0]&0xff;
			TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>8)&0xff;
			TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>16)&0xff;
			TxMessage.Data[3] = (*(unsigned long*)&data[i][0]>>24)&0xff;
			TxMessage.Data[4] = *(unsigned long*)&data[i][1]&0xff;
			TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>8)&0xff;
			TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>16)&0xff;
			TxMessage.Data[7] = (*(unsigned long*)&data[i][1]>>24)&0xff;
				
			mbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
			while((CAN_TransmitStatus(CAN1, mbox)!= CAN_TxStatus_Ok));//等待238us

	  }
 
}




static int Position[10];
void SetActualPosition(uint8_t num,int pos)
{
	Position[num]=pos;
}
int GetActualPosition(uint8_t num)
{
   return 	Position[num];
}


 void ReadActualPosition(uint8_t CopleyNum)
 {
	 
		uint32_t data[1][2]={0x00606440,0x00000000};
		CAN_TxMsg(CAN1,0x600+CopleyNum,(uint8_t*)&data[0],8);
 }
 
 
 
 