#ifndef __ELMO_H
#define __ELMO_H
#include "stm32f4xx.h"
#define   POS_REL  1    //相对位置方式POS_REL = 1 绝对位置方式POS_ABS = 0
#define   POS_ABS  0 


void CAN1OPEN_elmo_Init(uint8_t CopleyNum);
void VelCfg_elmo(uint8_t CopleyNum,uint32_t acc,uint32_t dec);
void VelMov_elmo( uint8_t CopleyNum,int32_t vel );
void Enable_elmo(uint8_t CopleyNum);
void Disable_elmo(uint8_t CopleyNum);
void PosCfg_elmo(uint8_t CopleyNum,
			uint8_t TrapScurve,
			uint32_t vel,
			uint32_t acc,
			uint32_t dec);

void PosMov_elmo( uint8_t CopleyNum,uint8_t rel_abs,int32_t pos );
void HomeMode_elmo(uint8_t CopleyNum,int8_t home_method,uint32_t home_fast,uint32_t home_slow,uint32_t home_acc);
void SetActualPosition(uint8_t num,int pos);
int GetActualPosition(uint8_t num);
 void ReadActualPosition(uint8_t CopleyNum);
#endif 


