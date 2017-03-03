#include "cylinder.h"
#include "stm32f4xx_can.h"
#include "string.h"

#define Cylinder_ID 100

#define Cylinder_0_on  0x63
#define Cylinder_0_off 0x60

#define Cylinder_1_on  0x67
#define Cylinder_1_off 0x64

#define Cylinder_2_on  0x6B
#define Cylinder_2_off 0x68

#define Cylinder_3_on  0x6F
#define Cylinder_3_off 0x6C

#define Cylinder_4_on  0x73
#define Cylinder_4_off 0x70

#define Cylinder_5_on  0x77
#define Cylinder_5_off 0x74

#define Cylinder_6_on  0x7B
#define Cylinder_6_off 0x78

#define Cylinder_7_on  0x7F
#define Cylinder_7_off 0x7C









char array[8] = {0};

void Cylinder_Trans(char *CylinderMovement)
{


	uint8_t mbox_cylinder;
	CanTxMsg TxMessage_cylinder;
	
	TxMessage_cylinder.StdId=Cylinder_ID;					 // standard identifier=0
	TxMessage_cylinder.ExtId=Cylinder_ID;					 // extended identifier=StdId
	TxMessage_cylinder.IDE=CAN_Id_Standard ;			 // type of identifier for the message is Standard
	TxMessage_cylinder.RTR=CAN_RTR_Data  ;			 // the type of frame for the message that will be transmitted
	TxMessage_cylinder.DLC=8;						 // ·¢ËÍÁ½Ö¡ĞÅÏ¢
	
	TxMessage_cylinder.Data[0] = CylinderMovement[0];		   //Æø¸×³õÊ¼×´Ì¬
	TxMessage_cylinder.Data[1] = CylinderMovement[1];		   //Æø¸×³õÊ¼×´Ì¬
	TxMessage_cylinder.Data[2] = CylinderMovement[2];		   //Æø¸×³õÊ¼×´Ì¬
	TxMessage_cylinder.Data[3] = CylinderMovement[3];		   //Æø¸×³õÊ¼×´Ì¬
	TxMessage_cylinder.Data[4] = CylinderMovement[4];		   //Æø¸×³õÊ¼×´Ì¬
	TxMessage_cylinder.Data[5] = CylinderMovement[5];		   //Æø¸×³õÊ¼×´Ì¬
	TxMessage_cylinder.Data[6] = CylinderMovement[6];		   //Æø¸×³õÊ¼×´Ì¬
	TxMessage_cylinder.Data[7] = CylinderMovement[7];		   //Æø¸×³õÊ¼×´Ì¬

       
	mbox_cylinder= CAN_Transmit(CAN1, &TxMessage_cylinder);   

	while((CAN_TransmitStatus(CAN1, mbox_cylinder)!= CAN_TxStatus_Ok));
}

void push(void)  
{
		memset(array, 0, 8);
 		array[0] = Cylinder_0_on;
 		Cylinder_Trans(array);
}

void shou(void)  
{
		memset(array, 0, 8);
 		array[0] = Cylinder_0_off;
 		Cylinder_Trans(array);
}
void top_shou(void)
{
		memset(array, 0, 8);
 		array[0] = Cylinder_1_on;
 		Cylinder_Trans(array);
}
void top_fang(void)
{
		memset(array, 0, 8);
 		array[0] = Cylinder_1_off;
 		Cylinder_Trans(array);
}
void di_shou(void)
{
		memset(array, 0, 8);
 		array[0] = Cylinder_2_off;
 		Cylinder_Trans(array);
}
void di_fang(void)
{
		memset(array, 0, 8);
 		array[0] = Cylinder_2_on;
 		Cylinder_Trans(array);
}

void shu_shen(void)
{
	  memset(array, 0, 8);
 		array[0] = Cylinder_3_on;
 		Cylinder_Trans(array);
}

void shu_shou(void)
{
	  memset(array, 0, 8);
 		array[0] = Cylinder_3_off;
 		Cylinder_Trans(array);
}


