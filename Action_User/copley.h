#include "can.h"

#define   POS_REL  1    //相对位置方式POS_REL = 1 绝对位置方式POS_ABS = 0
#define   POS_ABS  0 
#define   DIR_POS  1
#define   DIR_NEG  0
#define   TRAP     0
#define   SCURVE   3
#define   HOME_MODE         0
#define   REL_POS_MODE      1
#define   ABS_POS_MODE      2
#define   VEL_MODE          3
#define   MAX_COPLEY_NUM	6


void CANopen_Init(uint8_t CopleyNum);
void CAN_PDO_INIT(int First,int Last);
void HomeCfg(uint8_t CopleyNum,
			 uint8_t home_method,
			 uint32_t home_fast,
			 uint32_t home_slow,
			 uint32_t home_acc);
void HomeCfg_disenable(uint8_t CopleyNum,uint8_t home_method,uint32_t home_fast,uint32_t home_slow,uint32_t home_acc);
void VelCfg(uint8_t CopleyNum,uint32_t acc,uint32_t dec);
void VelMov( uint8_t CopleyNum,int32_t vel );
void PosCfg(uint8_t CopleyNum,
			uint8_t TrapScurve,
			uint32_t vel,
			uint32_t acc,
			uint32_t dec,
			uint32_t jerk);
void PosMov( uint8_t CopleyNum,uint8_t rel_abs,int32_t pos );
void Set_MaxVel(uint8_t CopleyNum,uint32_t vel);
void TorqCfg(uint8_t CopleyNum,uint32_t slo);
void TorMov(uint8_t CopleyNum,int16_t tor);
void VelCfgDual(uint32_t Acc_Dec);
long Get_Position(uint8_t CopleyNum);
void HomeMode(uint8_t CopleyNum,int8_t home_method,uint32_t home_fast,uint32_t home_slow,uint32_t home_acc);
