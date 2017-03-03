#include "action_driver.h"

SDO_ERROR sdo_error;

int Speed_Value=0;
int Current_Value=0;
int RelativePosition_Value=0;
int AbsolutePosition_Value=0;

void Set_Speed_Value(int tmp){
  Speed_Value=tmp;
}
int32_t Get_Speed_Value(void){
  return Speed_Value;
}

void Set_AbsolutePosition_Value(int tmp){
   AbsolutePosition_Value=tmp;
}
int32_t Get_AbsolutePosition_Value(void){
  return AbsolutePosition_Value;
}

void Set_RelativePosition_Value(int tmp){
   RelativePosition_Value=tmp;
}
int32_t Get_RelativePosition_Value(void){
  return RelativePosition_Value;
}


void Set_Current_Value(int tmp){
   Current_Value=tmp;
}
int32_t Get_Current_Value(void){
  return Current_Value;
}

/************************************************
�������ƣ�ActionSetHeartbeatInterval
�������ܣ�����������ʱ��
��ڲ�����nodeId-�������ڵ��.
          interval-������ʱ�䣬��λms��������65535
���ڲ�������
��ע����������ֻ����������״̬Ϊ pre-operational ʱ���á�
************************************************/
void ActionSetHeartbeatInterval(uint8_t nodeId,uint16_t interval)
{
	 uint8_t i=0; 
	 uint32_t data[1][2]={    				 
						   0x2b171000,0x64000000,		     //����������ʱ��
						 };
	
	//transmit_mailbox: the number of the mailbox that is used for transmission.
	uint8_t transmit_mailbox;	           		
	CanTxMsg TxMessage;
	// standard identifier
	TxMessage.StdId= SDOTX + nodeId;		
	// extended identifier=StdId						 
	TxMessage.ExtId= SDOTX + nodeId;	
	// type of identifier for the message is Standard						 
	TxMessage.IDE  = CAN_Id_Standard ;	
	// the type of frame for the message that will be transmitted						 
	TxMessage.RTR  = CAN_RTR_Data;			
	TxMessage.DLC  = DATA_LEN;

	data[0][1]=(((interval>>24)&0xff))+(((interval>>16)&0xff)<<8)+ (((interval>>8)&0xff)<<16)+((interval&0xff)<<24);	//��λ��ǰ							 
	
	TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
	TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
	TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
	TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;						 
	TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
	TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
	TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
	TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;

		
	transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         	
	while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));
}
/************************************************
�������ƣ�ActionSetOperationalMode
�������ܣ��л�����������״̬Ϊ operational
��ڲ�����nodeId-�������ڵ��
���ڲ�������
��ע��������״̬Ϊoperationalʱ�����ܽ���λ�á��ٶȵ����
************************************************/
void ActionSetOperationalMode(uint8_t nodeId)
{
	 uint8_t i=0; 
	 uint32_t data[1][2]={   		 
						   0x01000000,0x00000000,	 //��������������ģʽ
						 };
	//transmit_mailbox: the number of the mailbox that is used for transmission.
	uint8_t transmit_mailbox;	          
	CanTxMsg TxMessage;
	// standard identifier=0
	TxMessage.StdId=0x000;	
    // extended identifier=StdId						 
	TxMessage.ExtId=0x000;		
    // type of identifier for the message is Standard						 
	TxMessage.IDE=CAN_Id_Standard ;	
    // the type of frame for the message that will be transmitted						 
	TxMessage.RTR=CAN_RTR_Data;			   
	TxMessage.DLC=DATA_LEN;
  
	data[0][0]=0x01000000+((nodeId<<16)&0xffffffff); 
    	
	TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
	TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
	TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
	TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;						 
	TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
	TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
	TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
	TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;

		
	transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         
	while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));	

}
/************************************************
�������ƣ�ActionEnable
�������ܣ�ʹ�ܵ����ʹ�ܺ������ڱ���״̬
��ڲ�����nodeId-�������ڵ��
           status   -ENABLEʹ�ܵ����
                     DISABLE��ʹ�ܡ�
���ڲ�������
��ע����
************************************************/
void ActionEnable(uint8_t nodeId, int8_t status)
{
	 uint8_t i=0; 
	 uint32_t data[1][2]={   		 
		           0x2b406000,0x0f000000         
						 };
	//transmit_mailbox: the number of the mailbox that is used for transmission.
	uint8_t transmit_mailbox;	                
	CanTxMsg TxMessage;
	// standard identifier=0
	TxMessage.StdId=SDOTX + nodeId;	
	// extended identifier=StdId						 
	TxMessage.ExtId=SDOTX + nodeId;
	// type of identifier for the message is Standard
	TxMessage.IDE=CAN_Id_Standard ;
	// the type of frame for the message that will be transmitted						 
	TxMessage.RTR=CAN_RTR_Data;			         
	TxMessage.DLC=DATA_LEN;
    	
	if(status == 1)
	{
		data[0][1] = 0x0f000000;
	}
	else if(status == 0)
	{
		data[0][1] = 0x0d000000;
	}	
						 
		TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
		TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
		TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
		TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;						 
		TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
		TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
		TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
		TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;

		
	transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         
	while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));	
}
/************************************************
�������ƣ�ActionConfigTorque
�������ܣ�λ��ģʽ��ʼ��
��ڲ�����nodeId-�������ڵ��
          max_torque-���ת��
���ڲ�������
��ע:CANOpenЭ���ֽ�����LSB
************************************************/
void ActionConfigTorque(uint8_t nodeId, int16_t maxTorque)   	
{    
	 uint8_t i=0; 
	 uint32_t data[2][2]={
							//Index-6060(Mode of operation)		 
							0x2f606000,0x04000000,	
							//Index-6072(Max Torque)
							0x2b726000,0x00000000,   
						 };
	 
	//transmit_mailbox: the number of the mailbox that is used for transmission.
	uint8_t transmit_mailbox;	                 
	CanTxMsg TxMessage;
	//standard identifier=0
	TxMessage.StdId=SDOTX + nodeId;
	//extended identifier=StdId						 
	TxMessage.ExtId=SDOTX + nodeId;
	//type of identifier for the message is Standard						 
	TxMessage.IDE=CAN_Id_Standard ;	
	//the type of frame for the message that will be transmitted						 
	TxMessage.RTR=CAN_RTR_Data;			         
	TxMessage.DLC=DATA_LEN;
						 
	data[1][1]=(((maxTorque>>24)&0xff))+(((maxTorque>>16)&0xff)<<8)+ (((maxTorque>>8)&0xff)<<16)+((maxTorque&0xff)<<24);	
						 
	for(i=0; i<2; i++)
	{	      	
		TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
		TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
		TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
		TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;						 
		TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
		TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
		TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
		TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;

			
		transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         	
		while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));
	}
}
/************************************************
�������ƣ�ActionSetTorque
�������ܣ�������������
��ڲ�����nodeId-�������ڵ��
          torque- Ŀ������
                 - ��������������صĵ���δ2A���������3.2A����torque = 2000mA * 1000 /3200mA =625
                 - ����������� 62.5%
���ڲ�������
��ע:CANOpenЭ���ֽ�����LSB
************************************************/
void ActionSetTorque( uint8_t nodeId, int16_t torque)                 
{      
	 uint8_t i=0; 
	 uint32_t data[1][2]={    		
							//Index-6071(Target torque)		 
							0x2b716000,0x00000000,		
						 };
	//transmit_mailbox: the number of the mailbox that is used for transmission. 
	uint8_t transmit_mailbox;	                 
	CanTxMsg TxMessage;
	
	// standard identifier=0						 
	TxMessage.StdId=SDOTX+nodeId;
	//extended identifier=StdId						 
	TxMessage.ExtId=SDOTX+nodeId;
	//type of identifier for the message is Standard						 
	TxMessage.IDE=CAN_Id_Standard;	
	//the type of frame for the message that will be transmitted						 
	TxMessage.RTR=CAN_RTR_Data;			         
	TxMessage.DLC=DATA_LEN;
						 
	data[0][1]=(((torque>>24)&0xff))+(((torque>>16)&0xff)<<8)+ (((torque>>8)&0xff)<<16)+((torque&0xff)<<24);	
						 					 
	for(i=0;i<1;i++)
	{	     	
		TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
		TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
		TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
		TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;						 
		TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
		TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
		TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
		TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;

			
		transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         
		while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok)); 
	}
}
/************************************************
�������ƣ�ActionConfigVelocity
�������ܣ��ٶ�ģʽ��ʼ��
��ڲ�����nodeId-�������ڵ��
          acc-���ٶȣ���λ����/s2
          dec-���ٶȣ���λ����/s2
���ڲ�������
��ע:CANOpenЭ���ֽ�����LSB
************************************************/
void ActionConfigVelocity(uint8_t nodeId, uint32_t acc, uint32_t dec)            
{

	 uint8_t i=0; 
	 uint32_t data[3][2]={    			
							//Index-6060(Mode of operation) data-03(velocity mode)		 
							0x2f606000,0x03000000,  
							//Index-6083(Profile acceleration)		 
							0x23836000,0x00000000,
							//Index-6084(Profile deceleration)		 
							0x23846000,0x00000000     
						 };
	 
	//transmit_mailbox: the number of the mailbox that is used for transmission.
	uint8_t transmit_mailbox;	                 
	CanTxMsg TxMessage;
	//standard identifier=0
	TxMessage.StdId=SDOTX+nodeId;	
	//extended identifier=StdId						 
	TxMessage.ExtId=SDOTX+nodeId;
	//type of identifier for the message is Standard						 
	TxMessage.IDE=CAN_Id_Standard ;			       
	TxMessage.RTR=CAN_RTR_Data;	
	//the type of frame for the message that will be transmitted						 
	TxMessage.DLC=DATA_LEN;


	data[1][1]=(((acc>>24)&0xff))+(((acc>>16)&0xff)<<8)+ (((acc>>8)&0xff)<<16)+((acc&0xff)<<24);		
	data[2][1]=(((dec>>24)&0xff))+(((dec>>16)&0xff)<<8)+ (((dec>>8)&0xff)<<16)+((dec&0xff)<<24);								 
		 
							 
	for(i=0;i<3;i++)
	{	    
 	
		TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
		TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
		TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
		TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;						 
		TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
		TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
		TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
		TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;

			
		transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         
		while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));
	}
		
}
/************************************************
�������ƣ�ActionSetVelocity
�������ܣ������ٶ�����
��ڲ�����nodeId-�������ڵ��
          vel-�ٶȣ���λ����/s
���ڲ�������
��ע:CANOpenЭ���ֽ�����LSB
************************************************/
void ActionSetVelocity( uint8_t nodeId, int32_t vel)                 
{      
	 uint8_t i=0; 
	 uint32_t data[1][2]={ 
							//Index-60ff(Target velocity)		 
							0x23ff6000,0x00000000,		     
						 };
	//transmit_mailbox: the number of the mailbox that is used for transmission.
	uint8_t transmit_mailbox;	                 
	CanTxMsg TxMessage;
	
	//standard identifier=0						 
	TxMessage.StdId=SDOTX+nodeId;
	//extended identifier=StdId						 
	TxMessage.ExtId=SDOTX+nodeId;
	//type of identifier for the message is Standard						 
	TxMessage.IDE=CAN_Id_Standard ;	
	//the type of frame for the message that will be transmitted						 
	TxMessage.RTR=CAN_RTR_Data;			         
	TxMessage.DLC=DATA_LEN;


	data[0][1]=(((vel>>24)&0xff))+(((vel>>16)&0xff)<<8)+ (((vel>>8)&0xff)<<16)+((vel&0xff)<<24);	
						 
	for(i=0;i<1;i++)
	{	    
		TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
		TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
		TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
		TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;						 
		TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
		TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
		TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
		TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;

			
		transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         
		while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok)); 
	}
}
/************************************************
�������ƣ�ActionConfigPosition
�������ܣ�λ��ģʽ��ʼ��
��ڲ�����nodeId-�������ڵ��
		  vel-�ٶȣ���λ����/s
		  acc-���ٶȣ���λ����/s2
		  dec-���ٶȣ���λ����/s2
���ڲ�������
��ע:CANOpenЭ���ֽ�����LSB
************************************************/
void ActionConfigPosition(uint8_t nodeId, int32_t vel, uint32_t acc, uint32_t dec)   	
{    
	 uint8_t i=0; 
	 uint32_t data[5][2]={ 
							//Index-6060(Mode of operation)		 
							0x2f606000,0x01000000,	
							//Index-6086(Motion proflie type) data-0(trapezoidal profile mode)		 
							0x2b866000,0x00000000,
							//Index-6081(Proflie velocity)
							0x23816000,0x00000000,
							//Index-6083(Profile acceleration)		 
							0x23836000,0x00000000,
							//Index-6084(Profile deceleration)		 
							0x23846000,0x00000000,   
						 };
	//transmit_mailbox: the number of the mailbox that is used for transmission. 
	uint8_t transmit_mailbox;	                 
	CanTxMsg TxMessage;
	//standard identifier=0
	TxMessage.StdId=SDOTX+nodeId;					 
	TxMessage.ExtId=SDOTX+nodeId;
	//extended identifier=StdId						 
	TxMessage.IDE=CAN_Id_Standard ;
	//type of identifier for the message is Standard						 
	TxMessage.RTR=CAN_RTR_Data;
	//the type of frame for the message that will be transmitted						 
	TxMessage.DLC=DATA_LEN;
						 
	data[2][1]=(((vel>>24)&0xff))+(((vel>>16)&0xff)<<8)+ (((vel>>8)&0xff)<<16)+((vel&0xff)<<24);	
	data[3][1]=(((acc>>24)&0xff))+(((acc>>16)&0xff)<<8)+ (((acc>>8)&0xff)<<16)+((acc&0xff)<<24);		
	data[4][1]=(((dec>>24)&0xff))+(((dec>>16)&0xff)<<8)+ (((dec>>8)&0xff)<<16)+((dec&0xff)<<24);	
						 
	for(i=0;i<5;i++)
	{	      	
		TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
		TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
		TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
		TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;						 
		TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
		TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
		TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
		TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;
					
		transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);          	
		while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok)); 
	}
}
/************************************************
�������ƣ�ActionSetPosition
�������ܣ�����λ������
��ڲ�����nodeId-�������ڵ��
          mode-ABSOLUATE_POSITION_MODE,����λ��ģʽ��
                RELATIVE_POSITION_MODE,���λ��ģʽ
          pos-Ŀ��λ�ã���λ����
���ڲ�������
��ע:CANOpenЭ���ֽ�����LSB
************************************************/
void ActionSetPosition( uint8_t nodeId, uint8_t mode, int32_t pos)                 
{      
	 uint8_t i=0; 
	 uint32_t data[2][2]={  
							//Index-607a(Target position)		 
							0x237a6000,0x00000000,
							//Index-6040(Control word), 0x3f(absoluate position mode), 0x7f(relative  position mode)		 
							0x2b406000,0x00000000,                            
						 };
	//transmit_mailbox: the number of the mailbox that is used for transmission.
	uint8_t transmit_mailbox;	                
	CanTxMsg TxMessage;
	//standard identifier=0
	TxMessage.StdId=SDOTX+nodeId;
	//extended identifier=StdId						 
	TxMessage.ExtId=SDOTX+nodeId;
	//type of identifier for the message is Standard						 
	TxMessage.IDE=CAN_Id_Standard;
	//the type of frame for the message that will be transmitted						 
	TxMessage.RTR=CAN_RTR_Data;			         
	TxMessage.DLC=DATA_LEN;
						 
	data[0][1]=(((pos>>24)&0xff))+(((pos>>16)&0xff)<<8)+ (((pos>>8)&0xff)<<16)+((pos&0xff)<<24);	
						 
	if(mode == ABSOLUATE_POSITION_MODE)
	{
		data[1][1]= 0x3f000000; 
	}
	else if(mode == RELATIVE_POSITION_MODE)
	{
		data[1][1]= 0x7f000000;	 	
	}
				 
	for(i=0;i<3;i++)
	{	     	
		TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
		TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
		TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
		TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;							 
		TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
		TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
		TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
		TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;
				
		transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);          	
		while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok)); 
	}
}
/************************************************
�������ƣ�ActionSetHome
�������ܣ�������ã����ھ���λ��ģʽ��,�����õ�ǰ��Ϊ���
��ڲ�����nodeId-�������ڵ��
          pos-���λ��,����Ϊ0
���ڲ�������
��ע:CANOpenЭ���ֽ�����LSB
************************************************/
void ActionSetHome(uint8_t nodeId, int32_t pos)
{
	 uint8_t i=0; 
	 uint32_t data[3][2]={  
							//����6060(MODE OF OPERATION)��HOMEģʽ
							0x2f606000,0x06000000,
							//����607c(HOMING OFFSET)		 
							0x237c6000,0x00000000, 
							//����6089(HOMING METHOD) 0ΪHome is current position
							0x2f986000,0x00000000     
						 };
	//transmit_mailbox: the number of the mailbox that is used for transmission.
	uint8_t transmit_mailbox;	                 
	CanTxMsg TxMessage;
	//standard identifier=0
	TxMessage.StdId=SDOTX+nodeId;
	//extended identifier=StdId						 
	TxMessage.ExtId=SDOTX+nodeId;
	//type of identifier for the message is Standard						 
	TxMessage.IDE=CAN_Id_Standard;
	//the type of frame for the message that will be transmitted						 
	TxMessage.RTR=CAN_RTR_Data;			        
	TxMessage.DLC=DATA_LEN;
						 
	data[1][1]=(((pos>>24)&0xff))+(((pos>>16)&0xff)<<8)+ (((pos>>8)&0xff)<<16)+((pos&0xff)<<24);		
						 
	for(i=0;i<3;i++)
	{	    	
	TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
	TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
	TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
	TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;
						 
	TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
	TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
	TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
	TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;
		
			
		transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         
		while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));
	}
}
/************************************************
�������ƣ�ActionRequestMotorInfo
�������ܣ������������ͻ�ȡ��������Ϣ�������Ӧ��Ϣ��ͨ������ActionGetMotorInfo���
��ڲ�����nodeId-�������ڵ��
          infoType - CURRENT
                   - VELOCITY
                   - ABSOLUATE_POSITION
                   - RELATIVE_POSITION
���ڲ�������
��ע:CANOpenЭ���ֽ�����LSB
************************************************/
void ActionRequestMotorInfo(uint8_t nodeId, uint16_t infoType)
{
	 uint8_t i=0; 
	 uint32_t data[1][2]={  
							//Index-6078(Current actual value)
							//Index-6064(Position actual value-increments)
							//Index-6063(Position actual value)
							//Index-6069(Velocity snesor actual value)
							0x0000000,0x000000,		       
						 };                              
	                                           
	//transmit_mailbox: the number of the mailbox that is used for transmission.					                                 
	uint8_t transmit_mailbox;	                 
	CanTxMsg TxMessage;
	//standard identifier=0
	TxMessage.StdId=SDOTX+nodeId;
	//extended identifier=StdId						 
	TxMessage.ExtId=SDOTX+nodeId;
	//type of identifier for the message is Standard						 
	TxMessage.IDE=CAN_Id_Standard;	
	//the type of frame for the message that will be transmitted						 
	TxMessage.RTR=CAN_RTR_Data;			         
	TxMessage.DLC=DATA_LEN;
						 
	switch(infoType)
	{
		case CURRENT:
			data[0][0]=0x40786000;
			break;
		case VELOCITY:
			data[0][0]=0x40696000;			
			break;
		case RELATIVE_POSITION:
			data[0][0]=0x40636000;
			break;
		case ABSOLUATE_POSITION:
			data[0][0]=0x40646000;
			break;
	}		
	
	TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
	TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
	TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
	TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;						 
	TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
	TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
	TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
	TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;
		
	transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         	
	while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));
}

/************************************************
�������ƣ�ActionUpdateMotorInfo
�������ܣ������������ո���״̬�����ٶȡ�������λ�ã�
��ڲ�����nodeId-�������ڵ��
		  RxMessage-CAN���յ�һ֡����

���ڲ�������
��ע:CANOpenЭ���ֽ�����LSB
************************************************/
uint16_t ActionUpdateMotorInfo(uint8_t nodeId, CanRxMsg* RxMessage){
	//fix me, why static?
	static int32_t Speed_Value=0;
	static int32_t AbsolutePosition_Value=0;
	static int32_t RelativePosition_Value=0;	
	static int32_t Current_Value=0;	
	static uint16_t Index;
	static uint8_t  Subindex,SDO; 	
	
	SDO      = RxMessage->Data[0] & 0xff;
	Index    =(RxMessage->Data[2]<<8 &0xffff)  + (RxMessage->Data[1] &0xffff);
	Subindex = RxMessage->Data[3] & 0Xff;    	
	if((RxMessage->StdId - nodeId ) == 0x580)
	{	
		switch(SDO)
		{
			case SDO_LOAD_4:
				switch(Index)
				{
					case POSITION_ACTUAL_VALUE://����
						AbsolutePosition_Value = RxMessage->Data[4] + (RxMessage->Data[5] << 8 ) + (RxMessage->Data[6] <<16 ) + (RxMessage->Data[7] << 24 );
						Set_AbsolutePosition_Value(AbsolutePosition_Value); 								
						return POSITION_ACTUAL_VALUE;
						break;
					case ACTUAL_POSITION_INTERNAL_UNIT://���λ��
						RelativePosition_Value = RxMessage->Data[4] + (RxMessage->Data[5] << 8 ) + (RxMessage->Data[6] <<16 ) + (RxMessage->Data[7] << 24 );
						Set_RelativePosition_Value(RelativePosition_Value);  
						return ACTUAL_POSITION_INTERNAL_UNIT;					
						break;
					case VELOCITY_SENSOR_ACTUAL_VALUE://�ٶ�
						Speed_Value = RxMessage->Data[4] + (RxMessage->Data[5] << 8 ) + (RxMessage->Data[6] <<16 ) + (RxMessage->Data[7] << 24 );
						Set_Speed_Value(Speed_Value);	
						return 	VELOCITY_SENSOR_ACTUAL_VALUE;							
						break;
					case CURRENT_ACTUAL_VALUE://����
						Current_Value = RxMessage->Data[4] + (RxMessage->Data[5] << 8 ) + (RxMessage->Data[6] <<16 ) + (RxMessage->Data[7] << 24 );
						Set_Current_Value(Current_Value);	
						return 	CURRENT_ACTUAL_VALUE;							
						break;
					default:
						break;
				}
				break;	
			default:
				break;
		}
	}
	else return 0;	
}
/************************************************
�������ƣ�ActionCheckError
�������ܣ��������������صĴ�����Ϣ
��ڲ�����nodeId-����ڵ��
		  RxMessage-CAN���յ�һ֡����
           
���ڲ�����1-�д���
          0-û�д���
��ע:CANOpenЭ���ֽ�����LSB
************************************************/
uint8_t ActionCheckError(uint8_t nodeId, CanRxMsg* RxMessage){
	static uint16_t Index;
	static uint8_t  Subindex,SDO; 	
	
	SDO      = RxMessage->Data[0] & 0xff;
	Index    =(RxMessage->Data[2]<<8 &0xffff)  + (RxMessage->Data[1] &0xffff);
	Subindex = RxMessage->Data[3] & 0Xff;    	
	if((RxMessage->StdId - nodeId ) == 0x580 )
	{			
		switch(SDO)
		{
			case SDO_LOAD_1:
				 switch(Index)
				 {
					 case COMMAND_SPECIFIER_NOT_VALID:
						sdo_error.command_specifier_not_valid=1; //��������Ч
						return 1;
						break;
				 }		
				break;
			case SDO_LOAD_4:
				break;				
		}
	}
	else return 0;	
}

/************************************************
�������ƣ�Action_SendRemote
�������ܣ�����Զ��֡ 
��ڲ�����drivernum-����ڵ��.
          pdo-TPDOx
���ڲ�������
��ע����������TPDOx������յ���Ӧ�Ķ�TPDOx
************************************************/
void ActionSendRemote(uint8_t drivernum,uint16_t pdo)
{
	uint8_t i=0; 
  uint8_t transmit_mailbox;	                  //transmit_mailbox: the number of the mailbox that is used for transmission.
	CanTxMsg TxMessage;
	TxMessage.StdId= 0x180 + pdo - 0x1800 + drivernum;					 // standard identifier=0
	TxMessage.ExtId= 0;					 // extended identifier=StdId
	TxMessage.IDE  = CAN_Id_Standard ;			     // type of identifier for the message is Standard
	TxMessage.RTR  = CAN_RTR_Remote;			       // the type of frame for the message that will be transmitted
	TxMessage.DLC  = 0;

		
	transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
	while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));//�ȴ�238us
}

/************************************************
�������ƣ�ActionSetRPdo
��������: ����RPDO �� COB-ID
��ڲ�����drivernum-����ڵ��
          pdo - RPDOx
          enable - DISABLE\ENABLE
���ڲ�������
��ע����������ֻ����������״̬Ϊ pre-operational ʱ���á�
      ʹ�����λΪ0����ʹ�����λΪ0
************************************************/
void ActionSetRPdo(uint8_t drivernum,uint16_t pdo,uint8_t enable)
{
	 uint8_t i=0; 
	 uint32_t data[1][2]={    				 
						   0x23001401,0x00000000,		// Index-1400(RPDO1)
						 };
  uint8_t transmit_mailbox;	                 //transmit_mailbox: the number of the mailbox that is used for transmission.
	CanTxMsg TxMessage;
	TxMessage.StdId=SDOTX+drivernum;					 // standard identifier=0
	TxMessage.ExtId=SDOTX+drivernum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			       // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			         // the type of frame for the message that will be transmitted
	TxMessage.DLC=DATA_LEN;

	data[0][0] = data[0][0] |((pdo-0x1400)<<16) ;
	switch(enable)
	{
		case ENABLE:
      data[0][1] = ((( pdo - 0x1400 + 2 )<< 8 ) | 0x00000000 ) + drivernum ;			
			break;
		case DISABLE:
			data[0][1] = ((( pdo - 0x1400 + 2 )<< 8 ) | 0x80000000 ) + drivernum ;
			break;
	}								  
	data[0][1] = (((data[0][1]>>24)&0xff))+(((data[0][1]>>16)&0xff)<<8)+ (((data[0][1]>>8)&0xff)<<16)+((data[0][1]&0xff)<<24);		
						 
	TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
	TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
	TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
	TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;
						 
	TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
	TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
	TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
	TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;
		
	transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
	while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));//�ȴ�238us
}
/************************************************
�������ƣ�ActionSetTPdo
��������: ����TPDO �� COB-ID
��ڲ�����drivernum-����ڵ��
          pdo - TPDOx
          enable - ENABLE\DISABLE
���ڲ�������
��ע����������ֻ����������״̬Ϊ pre-operational ʱ���á�
      ʹ�����λΪ0����ʹ�����λΪ0
************************************************/
void ActionSetTPdo(uint8_t drivernum,uint16_t pdo,uint8_t enable)
{
	//����RPDO ��������COB-ID��ӳ��
	//����TPDO ��������COB-ID��ӳ�䣬ͨѶ��ʽ���¼���ʱ��
	//������ͬCOB-ID��Զ��֡�������߼��ɰ�PDO������������
	 uint8_t i=0; 
	 uint32_t data[1][2]={    				 
						   0x23001801,0x00000000,		// Index-1800(TPDO1)
						 };
  uint8_t transmit_mailbox;	                 //transmit_mailbox: the number of the mailbox that is used for transmission.
	CanTxMsg TxMessage;
	TxMessage.StdId=SDOTX+drivernum;					 // standard identifier=0
	TxMessage.ExtId=SDOTX+drivernum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			       // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			         // the type of frame for the message that will be transmitted
	TxMessage.DLC=DATA_LEN;

	data[0][0] = data[0][0] |((pdo-0x1800)<<16) ;
	switch(enable)
	{
		case ENABLE:
			data[0][1] = ((( pdo - 0x1800 + 1 )<< 8 ) | 0x00000080 ) + drivernum ;			
			break;
		case DISABLE:
			data[0][1] = ((( pdo - 0x1800 + 1 )<< 8 ) | 0x80000080 ) + drivernum ;
			break;
	}		
   
	data[0][1] = (((data[0][1]>>24)&0xff))+(((data[0][1]>>16)&0xff)<<8)+ (((data[0][1]>>8)&0xff)<<16)+((data[0][1]&0xff)<<24);							 
						 
    	
	TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
	TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
	TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
	TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;
						 
	TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
	TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
	TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
	TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;
		
	transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
	while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));//�ȴ�238us
}

/************************************************
�������ƣ�ActionSetTPdoComType
��������: ����TPDO �� �������
��ڲ�����drivernum-����ڵ��
          pdo - TPDOx
          type - 0~254
���ڲ�������
��ע����������ֻ����������״̬Ϊ pre-operational ʱ���á�
      ��TPDO�Ĵ�������Ϊ0 ʱ�����յ�ͬ��֡�����͸�PDO����ͬ����
      ��TPDO�Ĵ������Ϊ1~240ʱ�����յ���Ӧ������ͬ��֡�����͸�PDO
      ��TPDO�Ĵ������Ϊ254ʱ�� �������Զ����¼��� n*500us Ϊ���ڷ��͸�PDO���� ��
      ����������֧��TPDO 0,254
************************************************/
void ActionSetTPdoComType(uint8_t drivernum,uint16_t pdo,uint8_t type)
{
	//����RPDO ��������COB-ID��ӳ��
	 uint8_t i=0; 
	 uint32_t data[1][2]={    				 
						   0x2f001802,0x00000000,		// Index-1800(TPDO1)
						 };
  uint8_t transmit_mailbox;	                 //transmit_mailbox: the number of the mailbox that is used for transmission.
	CanTxMsg TxMessage;
	TxMessage.StdId=SDOTX+drivernum;					 // standard identifier=0
	TxMessage.ExtId=SDOTX+drivernum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			       // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			         // the type of frame for the message that will be transmitted
	TxMessage.DLC=DATA_LEN;

	data[0][0] = data[0][0] |((pdo-0x1800)<<16) ;
  data[0][1] = type; 
	data[0][1] = (((data[0][1]>>24)&0xff))+(((data[0][1]>>16)&0xff)<<8)+ (((data[0][1]>>8)&0xff)<<16)+((data[0][1]&0xff)<<24);							 
						 
    	
	TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
	TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
	TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
	TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;
						 
	TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
	TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
	TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
	TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;
		
	transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
	while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));//�ȴ�238us
}


/************************************************
�������ƣ�ActionSetRPdoComType
��������: ����RPDO�Ĵ������
��ڲ�����drivernum-����ڵ��
          pdo - TPDOx
          type - 0~254          
���ڲ�������
��ע����������ֻ����������״̬Ϊ pre-operational ʱ���á�
      ��RPDO�Ĵ������Ϊ0~240ʱ�� ���յ�һ��ͬ��֡�󣬽����ݸ��µ�Ӧ��
      ��RPDO�Ĵ������Ϊ254��255ʱ�����յ����ݼ����µ�Ӧ��
      ��֧��254
************************************************/
void ActionSetRPdoComType(uint8_t drivernum,uint16_t pdo,uint8_t type)
{
	 uint8_t i=0; 
	 uint32_t data[1][2]={    				 
						   0x2f001402,0x00000000,		// Index-1400(RPDO1)
						 };
  uint8_t transmit_mailbox;	                 //transmit_mailbox: the number of the mailbox that is used for transmission.
	CanTxMsg TxMessage;
	TxMessage.StdId=SDOTX+drivernum;					 // standard identifier=0
	TxMessage.ExtId=SDOTX+drivernum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			       // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			         // the type of frame for the message that will be transmitted
	TxMessage.DLC=DATA_LEN;

	data[0][0] = data[0][0] |((pdo-0x1400)<<16) ;
  data[0][1] = type; 
	data[0][1] = (((data[0][1]>>24)&0xff))+(((data[0][1]>>16)&0xff)<<8)+ (((data[0][1]>>8)&0xff)<<16)+((data[0][1]&0xff)<<24);							 
						 
    	
	TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
	TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
	TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
	TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;
						 
	TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
	TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
	TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
	TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;
		
	transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
	while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));//�ȴ�238us
}


/************************************************
�������ƣ�ActionSetTPdoBanTime
��������: ����TPDO ��ֹʱ��
��ڲ�����drivernum-����ڵ��
          pdo-TPDOx
          timt - ��λ100us
���ڲ�������
��ע����������ֻ����������״̬Ϊ pre-operational ʱ���á�
      ��ֹʱ�䣬��ΪTPDP����
      TPDO���ͼ������С�ڸ�ʱ�䣬��λ100us
************************************************/
void ActionSetTPdoBanTime(uint8_t drivernum,uint16_t pdo,uint8_t time)
{
	 uint8_t i=0; 
	 uint32_t data[1][2]={    				 
						   0x2f001803,0x00000000,		// Index-1800(TPDO1)
						 };
  uint8_t transmit_mailbox;	                 //transmit_mailbox: the number of the mailbox that is used for transmission.
	CanTxMsg TxMessage;
	TxMessage.StdId=SDOTX+drivernum;					 // standard identifier=0
	TxMessage.ExtId=SDOTX+drivernum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			       // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			         // the type of frame for the message that will be transmitted
	TxMessage.DLC=DATA_LEN;

	data[0][0] = data[0][0] |((pdo-0x1800)<<16) ;
  data[0][1] = time ; 
	data[0][1] = (((data[0][1]>>24)&0xff))+(((data[0][1]>>16)&0xff)<<8)+ (((data[0][1]>>8)&0xff)<<16)+((data[0][1]&0xff)<<24);							 
						 
    	
	TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
	TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
	TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
	TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;
						 
	TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
	TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
	TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
	TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;
		
	transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
	while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));//�ȴ�238us
}

/************************************************
�������ƣ�ActionSetTPdoEventCnt
��������: ����TPDO���¼���ʱ��
��ڲ�����drivernum-����ڵ��
          pdo-TPDOx
          event_cnt - ��500us * XΪ���ڷ����趨�õ�TPDOx 
���ڲ�������
��ע����������ֻ����������״̬Ϊ pre-operational ʱ���á�
      �¼�����������ΪTPDP����
      ��TPDO�������Ϊ254ʱ����event_cnt*500usΪ�����������߷���TPDO
************************************************/
void ActionSetTPdoEventCnt(uint8_t drivernum,uint16_t pdo,uint8_t event_cnt)
{
	 uint8_t i=0; 
	 uint32_t data[1][2]={    				 
						   0x2f001805,0x00000000,		// Index-1800(TPDO1)
						 };
  uint8_t transmit_mailbox;	                 //transmit_mailbox: the number of the mailbox that is used for transmission.
	CanTxMsg TxMessage;
	TxMessage.StdId=SDOTX+drivernum;					 // standard identifier=0
	TxMessage.ExtId=SDOTX+drivernum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			       // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			         // the type of frame for the message that will be transmitted
	TxMessage.DLC=DATA_LEN;

	data[0][0] = data[0][0] |((pdo-0x1800)<<16) ;
  data[0][1] = event_cnt ; 
	data[0][1] = (((data[0][1]>>24)&0xff))+(((data[0][1]>>16)&0xff)<<8)+ (((data[0][1]>>8)&0xff)<<16)+((data[0][1]&0xff)<<24);							 
						 
    	
	TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
	TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
	TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
	TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;
						 
	TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
	TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
	TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
	TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;
		
	transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
	while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));//�ȴ�238us
}


/************************************************
�������ƣ�ActionSetTPdoMap
��������: ����TPDO��ӳ�����
��ڲ�����drivernum-����ڵ��
          pdo-TPDOx
���ڲ�������
��ע����������ֻ����������״̬Ϊ pre-operational ʱ����
      ���ɶȺܸߣ�����������������ӳ��Ϊ��
************************************************/
void ActionSetTPdoMap(uint8_t drivernum,uint16_t pdo)
{
	 uint8_t i=0; 
	 uint32_t data[3][2]={    				 
						   0x2f001a00,0x00000002,		// ��������tpdo1��Ӧ����ӳ�䣨��Ч����Ϊ1~8��
						   0x23001a01,0x60780010,   //����
	             0x23001a02,0x60690020,   //�ٶ�
	             };
  uint8_t transmit_mailbox;	                 //transmit_mailbox: the number of the mailbox that is used for transmission.
	CanTxMsg TxMessage;
	TxMessage.StdId=SDOTX+drivernum;					 // standard identifier=0
	TxMessage.ExtId=SDOTX+drivernum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			       // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			         // the type of frame for the message that will be transmitted
	TxMessage.DLC=DATA_LEN;

	data[0][0] = data[0][0] |((pdo-0x1800)<<16) ;
	data[1][0] = data[1][0] |((pdo-0x1800)<<16) ;						 
	data[2][0] = data[2][0] |((pdo-0x1800)<<16) ;		
							 
	data[0][1] = (((data[0][1]>>24)&0xff))+(((data[0][1]>>16)&0xff)<<8)+ (((data[0][1]>>8)&0xff)<<16)+((data[0][1]&0xff)<<24);							 
	data[1][1] = (((data[1][1]>>24)&0xff))+(((data[1][1]>>16)&0xff)<<8)+ (((data[1][1]>>8)&0xff)<<16)+((data[1][1]&0xff)<<24);		
	data[2][1] = (((data[2][1]>>24)&0xff))+(((data[2][1]>>16)&0xff)<<8)+ (((data[2][1]>>8)&0xff)<<16)+((data[2][1]&0xff)<<24);						 
    	
	for(i = 0;i<3;i++)
	{
		TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
		TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
		TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
		TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;
							 
		TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
		TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
		TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
		TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;
				
		transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
		while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));//�ȴ�238us
	}
}

/************************************************
�������ƣ�ActionSetRPdoMap
��������: ����RPDOӳ��
          pdo-TPDOx
��ڲ�����drivernum-����ڵ��
���ڲ�������
��ע����������ֻ����������״̬Ϊ pre-operational ʱ����
      ���ɶȺܸߣ�����������������ӳ��Ϊ��
************************************************/
void ActionSetRPdoMap(uint8_t drivernum,uint16_t pdo)
{
	 uint8_t i=0; 
	 uint32_t data[3][2]={    				 
						   0x2f001600,0x00000002,		// ��������pdo1��Ӧ����ӳ�䣨��Ч����Ϊ1~8��
						   0x23001601,0x60830020,   //���ٶ�
	             0x23001602,0x60840020,   //���ٶ�
						 };
  uint8_t transmit_mailbox;	                 //transmit_mailbox: the number of the mailbox that is used for transmission.
	CanTxMsg TxMessage;
	TxMessage.StdId=SDOTX+drivernum;					 // standard identifier=0
	TxMessage.ExtId=SDOTX+drivernum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			       // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			         // the type of frame for the message that will be transmitted
	TxMessage.DLC=DATA_LEN;

	data[0][0] = data[0][0] |((pdo-0x1400)<<16) ;
	data[1][0] = data[1][0] |((pdo-0x1400)<<16) ;						 
	data[2][0] = data[2][0] |((pdo-0x1400)<<16) ;						 
						 
	data[0][1] = (((data[0][1]>>24)&0xff))+(((data[0][1]>>16)&0xff)<<8)+ (((data[0][1]>>8)&0xff)<<16)+((data[0][1]&0xff)<<24);							 
	data[1][1] = (((data[1][1]>>24)&0xff))+(((data[1][1]>>16)&0xff)<<8)+ (((data[1][1]>>8)&0xff)<<16)+((data[1][1]&0xff)<<24);		
	data[2][1] = (((data[2][1]>>24)&0xff))+(((data[2][1]>>16)&0xff)<<8)+ (((data[2][1]>>8)&0xff)<<16)+((data[2][1]&0xff)<<24);						 
    	
	for(i = 0;i<3;i++)
	{
		TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
		TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
		TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
		TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;
							 
		TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
		TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
		TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
		TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;
				
		transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
		while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));//�ȴ�238us
	}						 
}

/************************************************
�������ƣ�ActionPDOVelConfig
��������: ��PDO��ʽ���ü��ٶȣ����ٶȣ���PDOӳ������йأ�
��ڲ�����drivernum-����ڵ��
          pdo-TPDOx
          acc - ���ٶ�
          dec - ���ٶ�
���ڲ�������
��ע����������ֻ����������״̬Ϊ pre-operational ʱ���á�
      ��PDO��ʽ�����ٶ�ģʽ�µļ��ٶȺͼ��ٶ�
************************************************/
void ActionPDOVelConfig(uint8_t drivernum,uint16_t pdo,uint32_t acc,uint32_t dec)
{
	 uint8_t i=0; 
	 uint32_t data[1][2]={    				 
						   0x00000000,0x00000000,	 
						 };
  uint8_t transmit_mailbox;	                 //transmit_mailbox: the number of the mailbox that is used for transmission.
	CanTxMsg TxMessage;
	TxMessage.StdId=0x200 + pdo - RPDO1 + drivernum;					 // standard identifier=0
	TxMessage.ExtId=0;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			       // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Data  ;			         // the type of frame for the message that will be transmitted
	TxMessage.DLC=DATA_LEN;

	data[0][0] = acc;
	data[0][1] = dec;						 
						 
	data[0][1] = (((data[0][1]>>24)&0xff))+(((data[0][1]>>16)&0xff)<<8)+ (((data[0][1]>>8)&0xff)<<16)+((data[0][1]&0xff)<<24);							 
	data[0][0] = (((data[0][0]>>24)&0xff))+(((data[0][0]>>16)&0xff)<<8)+ (((data[0][0]>>8)&0xff)<<16)+((data[0][0]&0xff)<<24);		
    	

		TxMessage.Data[0] = (*(unsigned long*)&data[i][0]>>24)&0xff;
		TxMessage.Data[1] = (*(unsigned long*)&data[i][0]>>16)&0xff;
		TxMessage.Data[2] = (*(unsigned long*)&data[i][0]>>8)&0xff;
		TxMessage.Data[3] =  *(unsigned long*)&data[i][0]&0xff;
							 
		TxMessage.Data[4] = (*(unsigned long*)&data[i][1]>>24)&0xff;
		TxMessage.Data[5] = (*(unsigned long*)&data[i][1]>>16)&0xff;
		TxMessage.Data[6] = (*(unsigned long*)&data[i][1]>>8)&0xff;
		TxMessage.Data[7] = *(unsigned long*)&data[i][1]&0xff;
				
		transmit_mailbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us	
		while((CAN_TransmitStatus(CAN1, transmit_mailbox)!= CAN_TxStatus_Ok));//�ȴ�238us
							 
}
/************************************************
�������ƣ�ActionPDOReData
��������: �����TPDO���ص����ݣ� Ҫ��PDO������һ�£�˫��֪���������ݣ�
��ڲ�����drivernum-����ڵ��
          pod -TPDOx
���ڲ�������
��ע����������ֻ����������״̬Ϊ pre-operational ʱ���á�
      ������յ������ٶ�Ϊ��
************************************************/
uint8_t ActionPDOReData(CanRxMsg* RxMessage,uint8_t drivernum,uint16_t pdo)
{
	    static int32_t Speed_Value=0;
	    static int32_t AbsolutePosition_Value=0;
	    static int32_t RelativePosition_Value=0;	
     	static int32_t Current_Value=0;	
	    static uint16_t Index;
	    static uint8_t  Subindex,SDO; 	
	
			SDO      = RxMessage->Data[0] & 0xff;
			Index    =(RxMessage->Data[2]<<8 &0xffff)  + (RxMessage->Data[1] &0xffff);
		  Subindex = RxMessage->Data[3] & 0Xff;  
      Subindex = Subindex;	
			if((RxMessage->StdId - drivernum ) == (((pdo + 1 -TPDO1) << 8 )| 0x80) )
			{	
	
								 Current_Value        = RxMessage->Data[0] + (RxMessage->Data[1] << 8 );
								 Set_Current_Value(Current_Value);	
								 Speed_Value					= RxMessage->Data[2] + (RxMessage->Data[3] << 8 ) + (RxMessage->Data[4] <<16 ) + (RxMessage->Data[5] << 24 );	
    	}
	    else 
				return 0;	
     return 1;
							 
}