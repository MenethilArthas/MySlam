/**
  ******************************************************************************
  * @file    copley.c
  * @author  Calcus Lee
  * @version V1.0.1
  * @date    13-August-2013
  * @brief   functions of Using Copley Accelnet Micro Panel
  ******************************************************************************
  * @attention
  *
  * 1.there is a time delay between the time VelCfg() is run over and 
  *   the time you can use VelMov() the set Vel.
  * 2. @ref CANopenProgrammersManual.pdf and Copley驱动器内部资料V1203beta.pdf 
  *    for the specific means of parametrs
  * 3.the velocity loop's acceleration and  deceleration and  the motor's 
  *   position loop's acceleration and  deceleration have mutual effect to each other, 
  *   and the motor will move at the latter instruction.
  * 4.there are some multiplication and division ( *10, /10, /100) to unify units.
  * 5.All OF THESE FUNCION will use CAN1 to communicate with Copley Accelnet Micro Panel,
  *   so you should intialize CAN1, before you use any of these functions.
  ******************************************************************************
**/


#include "copley.h"

uint32_t Motor_Status;
int32_t Motor_Actual_Position;

uint8_t Position_Update_Flag;


uint8_t Position_Flag[MAX_COPLEY_NUM];

/**
  * @brief  initialize CANopen to communicate with Copley Accelnet Micro Panel
  * @param  None 
  * @retval None
  * @authonr Calcus Lee
  */
void CANopen_Init(uint8_t CopleyNum)
{

    uint8_t CANopen_Msg1[8]={0x01,0x00,0x00,0x00,
							 0x00,0x00,0x00,0x00};
    uint8_t CANopen_Msg2[8]={0x2B,0x17,0x10,0x00,
							 0xFF,0x7F,0x00,0x00};
	uint8_t CANopen_Msg3[8]={0x2B,0x40,0x60,0x00,
							 0x0f,0x00,0x00,0x00};							
							 
    CAN_TxMsg(CAN1, 0, CANopen_Msg1,2); 
	

	  CAN_TxMsg(CAN1,0x600+CopleyNum,CANopen_Msg2,8);
      CAN_TxMsg(CAN1,0x600+CopleyNum,CANopen_Msg3,8);


}


void CAN_PDO_INIT(int First,int Last)
{
	unsigned char i,j;
  	uint32_t data[4][2]={
  	0x0214022f,0x000000ff,		
  	0x0214032f,0x000000ff,
  	0x0218022f,0x000000fd,
  	0x0218032f,0x000000fd
  	};
	uint32_t data2[3][2]={
  	0x0016032f,0x00000000,		
  	0x01160323,0x60ff0020,
  	0x0016032f,0x00000001
  	};


   for(i=First;i<Last+1;i++)
	{
	  for(j=0;j<4;j++)
	  {	    
      CAN_TxMsg(CAN1,0x600+i,(uint8_t*) & data[j],8);
	  }
	}
//**********************************************************************************//

   for(i=First;i<Last+1;i++)
	{
	  for(j=0;j<3;j++)
	  {	    
      CAN_TxMsg(CAN1,0x600+i,(uint8_t*) & data2[j],8);
	  }

	}
		Motor_Actual_Position= 0;
		Position_Update_Flag= 0;	
}




/**
  * @brief  setup a motor's Homing mode.Homing is the method by which a drive seeks the home position 
  *			(also called the datum, reference point, or zero point).
  * @param  CopleyNum: (usually 3,4,5,6)the number you set for Copley Accelnet Micro Panel in CME2 software.
  * @param  home_method: (usually 0) The method for finding the motor home position in homing mode.
  *         @ref CANopenProgrammersManual.pdf p183 for more informatin.
  * @param  home_fast: (usually 100000) The fast speed is used to find the home switch.
  *			@ref CANopenProgrammersManual.pdf p184 for more informatin.
  *         Units : counts/sec       Range : 0 – 50,000,000 
  * @param  home_slow: (usually 100000)the slow speed is used to find the index pulse.
  *			@ref CANopenProgrammersManual.pdf p184 for more informatin.
  *         Units : counts/sec       Range : 0 – 50,000,000 
  * @param  home_acc:  ((usually 9000))This value defines the acceleration used for all homing moves. 
  *			The same acceleration value is used at the beginning and ending of moves 
  *			(i.e. there is no separate deceleration value). 
  *         Units : counts/sec^2       Range : 0 – 2,000,000,000  
  *			@note  in homing, it is not possible to program a separate deceleration rate. 
  * @retval None
  * @authonr Calcus Lee
**/
void HomeCfg(uint8_t CopleyNum,
			 uint8_t home_method,
			 uint32_t home_fast,
			 uint32_t home_slow,
			 uint32_t home_acc)
{ 
	uint8_t i=0;
	
 	uint32_t data[8][2]=
	{
		0x0060602F,0x00000006,    //switch to HOME Mode
		0x0060402B,0x0000000F,	  //2b 40 60 00 0f 00 00 00
		0x01609923,		   0,	  //home_fast
		0x02609923,	       0,	  //home_slow
		0x00609A23,		   0,	  //home_acc
		0x00607C23,		   0,	  //offset
		0x0060982F,        0,	  //home_method
		0x0060402B,0x0000001F, 	  //启动HOME模式	,Switch On,Enable Voltage,Quick Stop,Enable Operation
	};

 	data[2][1] = home_fast * 10;
	data[3][1] = home_slow * 10; 		
	data[4][1] = home_acc/ 10;
	data[6][1] = home_method;
	
	for(i=0;i<8;i++)
	{
		CAN_TxMsg(CAN1,0x600+CopleyNum,(uint8_t*) & data[i],8);     // pay attention to this bit arithmetic!!
	}
 
}
 
 
void HomeCfg_disenable(uint8_t CopleyNum,uint8_t home_method,uint32_t home_fast,uint32_t home_slow,uint32_t home_acc)
{  
	
	unsigned char i;
	
 	uint32_t data[8][2]=
	{  
		 0x0060602F,0x00000006,
	   0x0060402B,0x0000000D,	   //2b 40 60 00 0f 00 00 00
	   0x01609923,		   0,	  //home_fast
	   0x02609923,	       0,	  //home_slow
	   0x00609A23,		   0,	  //home_acc
	   0x00607C23,		   0,	  //offset
	   0x0060982F,         0,	  //home_method
	   0x0060402B,0x0000001D, 	  //启动HOME模式	
	};
	
 	data[2][1] = home_fast * 10;
	data[3][1] = home_slow * 10; 		
	data[4][1] = home_acc/ 10;
	data[6][1] = home_method;
	
	
	for(i=0;i<8;i++)
	{
		CAN_TxMsg(CAN1,0x600+CopleyNum,(uint8_t*) & data[i],8);     // pay attention to this bit arithmetic!!
	}
 
 }
 
 
/**
  * @brief  setup a motor's Velocity mode.
  * @param  CopleyNum: (usually 3,4,5,6)the number you set for Copley Accelnet Micro Panel in CME2 software.
  * @param  acc: In profile position mode, this value is the acceleration that the trajectory 
  *			generator attempts to achieve. For S-curve moves, this value is also used to 
  *			decelerate at the end of the move.
  *			Units : counts/sec^2     	Range : 0 - 2,000,000,000
  *         @ref CANopenProgrammersManual.pdf p203 for more informatin.
  * @param  dec: Deceleration that the trajectory generator uses at the end of a trapezoidal 
  *			profile when running in position profile mode. 
  *         Units : counts/sec^2       Range : 0 – 2,000,000,000 
  *			@ref CANopenProgrammersManual.pdf p184 for more informatin. 
  * @retval None
  * @authonr Calcus Lee
**/
void VelCfg(uint8_t CopleyNum,uint32_t acc,uint32_t dec)
{
	 uint8_t i=0;
	 uint32_t data[3][2]=
	 {  0x0060602F,0x00000003,	///Profile Velocity mode.   
		0x00608323,0,		  	//Profile acceleration
		0x00608423,0,  			//PROFILE deceleration
	 };
	data[1][1]= acc / 10; 		
	data[2][1] = dec / 10;
	for(i=0;i<3;i++)
	{
		CAN_TxMsg(CAN1, 0x600+CopleyNum, (uint8_t*)&data[i], 8);
	}

}

/**
  * @brief  setup a motor's Velocity mode.
  * @param  CopleyNum: (usually 3,4,5,6)the number you set for Copley Accelnet Micro Panel in CME2 software.
  * @param  Acc_Dec 省赛车的加减速度.
  *			@ref CANopenProgrammersManual.pdf p184 for more informatin. 
  * @retval None
  * @authonr Calcus Lee
**/
void VelCfgDual(uint32_t Acc_Dec)
{
	VelCfg(1,Acc_Dec,Acc_Dec);
	VelCfg(2,Acc_Dec,Acc_Dec);
}
/**
  * @brief  specify a motor's target velocity
  * @param  CopleyNum: (usually 3,4,5,6)the number you set for Copley Accelnet Micro Panel in CME2 software.
  * @param  vel:  target velocity
  *         Units : counts/sec        Range : -50,000,000 - 50,000,000
  * @retval None
  * @authonr Calcus Lee
**/
void VelMov( uint8_t CopleyNum,int32_t vel )   //耗时1.24ms
{

	uint8_t i=0;
	uint32_t data[3][2]=
	{  
		0x0060402B,0x0000000F,	//CONTROL WORD, Switch On,Enable Voltage,Quick Stop,Enable Operation
		0x0060602F,0x00000003,  //Profile Velocity mode. 	 
		0x0060FF23,0, 		    //target velocity	  
	};

	data[2][1]=vel*10;
	for(i=0;i<3;i++)
	{
		CAN_TxMsg(CAN1,0x600+CopleyNum,(uint8_t*)&data[i],8);
	}
}

/**
  * @brief  setups a motor's Position mode.
  * @param  CopleyNum: (usually 3,4,5,6)the number you set for Copley Accelnet Micro Panel in CME2 software.
  * @param  TrapScurve:  motion profile type. The supported values for this object are:
  *         0:  Trapezoidal profile mode; 3:  S-curve profile mode (Jerk limited); -1:  Velocity mode.   
  * @param  vel:  Profile Velocity
  *         Units : counts/sec        Range : -50,000,000 - 50,000,000
  * @param  acc:  Profile Acceleration
  *         Units : counts/sec^2       Range : 0 - 2,000,000,000 
  * @param  dec:  Profile Deceleration  
  *         Units : counts/sec^2       Range : 0 - 2,000,000,000 
  * @param  jerk:  This object defines the maximum jerk (rate of change of acceleration) for use 
  *			with S-curve profile moves. Other profile types do not use the jerk limit. 
  *         Units : counts / sec^3       Range : 0 – 10,000,000,000 
  * 		@note the max value of a uint32_t number is 4,294,967,296, so you actually cant get set a 
  *               value bigger than 4,294,967,296 to jerk. if you really need to get a bigger 
  *               Trajectory Jerk Limit value, you can change the equation data[5][1] = jerk / 100 to
  *               data[5][1] = jerk, so that the units of jerk become 100 counts/sec^3, and you get a 
  *               bigger value range of jerk.
  * @retval None
  * @authonr Calcus Lee
**/
void PosCfg(uint8_t CopleyNum,
			uint8_t TrapScurve,
			uint32_t vel,
			uint32_t acc,
			uint32_t dec,
			uint32_t jerk)
{

    uint8_t i=0;
	uint32_t data[6][2]=
	{  
		0x0060602F,0x00000001,	//Profile Position mode. 
		0x0060862B,0,	   	   	//motion profile type, Trapezoidal profile mode
		0x00608123,0,	  		//Profile Velocity
		0x00608323,0,	  		//Profile Acceleration  
		0x00608423,0,	  		//Profile Deceleration  
		0x00212123,0			//Trajectory Jerk Limit   		
	};

	data[1][1] = TrapScurve; 
	data[2][1]=  vel * 10; 		
	data[3][1] = acc / 10;
	data[4][1] = dec / 10;
	data[5][1] = jerk / 100;
	
	for(i=0;i<6;i++)
	{
		CAN_TxMsg(CAN1,0x600+CopleyNum,(uint8_t*) & data[i],8);
	}

}

/**
  * @brief  specify a motor's target postion
  * @param  CopleyNum: (usually 3,4,5,6)the number you set for Copley Accelnet Micro Panel in CME2 software.
  * @param  rel_abs:  
  *         relative location mode rel_abs = 1, absolute position mode rel_abs=0(others except 1)
  * @param  pos:  target position
  *         Units : counts        Range : Integer 32 
  * @retval None
  * @authonr Calcus Lee
**/
void PosMov( uint8_t CopleyNum,uint8_t rel_abs,int32_t pos )
{
	uint8_t i=0;
	uint32_t data[3][2]=
	{           
		0x00607A23,0,	  		 //pos
		0x0060402B,0x0000000F,	 //Control word,Switch On,Enable Voltage,Quick Stop,Enable Operation
		0x0060402B,0	  
   		
	};
	data[0][1]=pos;
	
	if(rel_abs == POS_REL)
	{
		data[2][1] = 0x007f;
	}
	else
	{
		data[2][1] = 0x003f;
	}	
	
	for(i=0;i<3;i++)
	{
		CAN_TxMsg(CAN1,0x600+CopleyNum,(uint8_t*)&data[i],8);
	}
	
}

/**
  * @brief  Limit velocity loop velocity 
  * @param  CopleyNum: (usually 3,4,5,6)the number you set for Copley Accelnet Micro Panel in CME2 software.
  * @param  vel:  This velocity value is a limit on the commanded velocity used by the velocity loop.
			Units : counts        Range : 0 – 50,000,000 
  * @retval None
  * @authonr Calcus Lee
**/
void Set_MaxVel(uint8_t CopleyNum,uint32_t vel)
{
	uint32_t data[1][2]=
	{ 	 
		0x00210323,0	  //vel   		
	};
	data[0][1]=  vel * 10; 
	CAN_TxMsg(CAN1,0x600+CopleyNum,(uint8_t*)&data[0],8);
} 

/**
  * @brief  setup a motor's Torque mode 
  * @param  CopleyNum: (usually 3,4,5,6)the number you set for Copley Accelnet Micro Panel in CME2 software.
  * @param  slo:  Torque slope.Torque acceleration or deceleration. 
  *         Units: (rated torque)/1000/second    Range: (Positive integer values)/1000 
  * @retval None
  * @authonr Calcus Lee
**/
void TorqCfg(uint8_t CopleyNum,uint32_t slo)
{
	uint8_t i=0;
	uint32_t data[3][2]=
	{
		0x0060602F,0x00000004, //Mode of operation, Profile Torque mode. 
		0x00608723,0,          //Torque slope
		0x00608823,0           //Type of torque profile used to perform a torque change.
							   //Set to zero to select trapezoidal profile. 
	};
	data[1][1] = slo * 1000/181 ;
	for(i=0;i<3;i++)
	{
		CAN_TxMsg(CAN1,0x600+CopleyNum,(uint8_t*)&data[i],8);
	}
}

/**
  * @brief  specify a motor's target torque
  * @param  CopleyNum: (usually 3,4,5,6)the number you set for Copley Accelnet Micro Panel in CME2 software.
  * @retval tor: motor's target torque
  * @authonr Calcus Lee
**/
void TorMov(uint8_t CopleyNum,int16_t tor)
{
	uint8_t i=0;
	 uint32_t data[2][2]=
	{          
		0x00607123,0,	   //tor
		0x0060402B,0x0000000F	  	   		
	};
	data[0][1]=tor * 1000;
	for(i=0;i<2;i++)
	{
		CAN_TxMsg(CAN1,0x600+CopleyNum,(uint8_t*)&data[i],8);
	}
}


long Get_Position(uint8_t CopleyNum)        //共耗时460us（包括等待的238us）
{
	
	
	
	uint8_t mbox;

	
	CanTxMsg TxMessage;
	TxMessage.StdId=0x380+CopleyNum;					 // standard identifier=0
	TxMessage.ExtId=0x380+CopleyNum;					 // extended identifier=StdId
	TxMessage.IDE=CAN_Id_Standard ;			 // type of identifier for the message is Standard
	TxMessage.RTR=CAN_RTR_Remote  ;			 // the type of frame for the message that will be transmitted
	TxMessage.DLC=2;						 // 发送两帧信息

	mbox= CAN_Transmit(CAN1, &TxMessage);         //1.4us		

	while((CAN_TransmitStatus(CAN1, mbox)!= CAN_TxStatus_Ok));//等待238us


	while(Position_Update_Flag == 0);              
		Position_Update_Flag = 0;
		
		
	return Motor_Actual_Position;
	
	
}

void HomeMode(uint8_t CopleyNum,int8_t home_method,uint32_t home_fast,uint32_t home_slow,uint32_t home_acc)
{ 
	uint8_t i=0;
	
 	uint32_t data[10][2]=
	{
		 0x0060602F,0x00000006,
	   0x0060402B,0x0000000F,	   //2b 40 60 00 0f 00 00 00
	   0x01609923,		   0,	  //home_fast
	   0x02609923,	       0,	  //home_slow
	   0x00609A23,		   0,	  //home_acc
	   0x00607C23,         0,	  //offset	  // 26774
	   0x0060982F,         0,	  //home_method
	   0x0023512B,0x0000000a,     //delaytime  10             Units:milliseconds
	   0x0023502B,0x00000032,	  //homecurrent	  //  Units:0.01A
	   0x0060402B,0x0000001F, 	  //启动HOME模式	
	};
	

	
 	data[2][1] = home_fast * 10;
	data[3][1] = home_slow * 10; 		
	data[4][1] = home_acc/ 10;
	data[6][1] = home_method;
	
	for(i=0;i<10;i++)
	{
		CAN_TxMsg(CAN1,0x600+CopleyNum,(uint8_t*) & data[i],8);     // pay attention to this bit arithmetic!!
	}
 
}
 

