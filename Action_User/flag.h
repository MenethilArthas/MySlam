#ifndef __FLAG__H
#define __FLAG__H
#include "stm32f4xx.h"


#define DEBUG 1


#define Elmo    1
#define Copley  0


#define ZhuKbanWithFuJ     1
#define ZhuKbanWithOutFuJ  0



#define HuiPaiGengXin_OK 1
#define HuiPaiGengXin_NO 0
#define Enable 1
#define Disable 0
#define Buwei 0
#define Daqiu 1
#define Car_ZanTing 0
#define Car_Zhengchang 1

#define Yao_ing 1
#define Yao_Over 0

#define HuiPaiStart 1
#define HuiPaiEnd 0

#define HuiBiStart 1
#define HuiBiEnd 0

#define unlock 1
#define lock 0

#define huaxinging 0
#define huaxingover 1

void    SetHuiPai_FLAG(void);
void    ClearHuiPai_FLAG(void);
uint8_t GetHuiPai_FLAG(void);


void EnableWaiCamera(void);
void DisableWaiCamera(void);
uint8_t GetWaiCameraRight(void);

void SetCar_BuweiStation(void);
void SetCar_DaqiuStation(void);
uint8_t GetCarTaskTodo(void);

void SetCarZanTingStation(void);
void SetCarZhengchangtation(void);
uint8_t GetCarStation(void);


void SetHandData(uint8_t a);
uint8_t Get_bit_HandData(uint8_t bit);
uint8_t GethandData(void);
void ClearHandData(void);


void Set_Yao_Vel_X(double V_x);
void Set_Yao_Vel_Y(double V_y);
double get_V_x_Handle(void);
double get_V_y_Handle(void);

void Set_Yao_ing(void);
void Set_Yao_Over(void);
uint8_t Get_YaoGan(void);

void HuiPai_Start(void);
void HuiPai_End(void);
uint8_t GetHuiPaiStEnFlag(void);

void HuiBi_Start(void);
void HuiBi_End(void);
uint8_t GetHuiBiStEnFlag(void);

void Lock_Get_V_jiansu_Expt(void);
void UnLock_Get_V_jiansu_Expt(void);
uint8_t Get_V_jiansu_Expt_LockState(void);


void SetDaQiutime(int time);
 int GetDaQiutime(void);
 
 
 void Sethuaxing(void);
 void Sethuaxingover(void);
 uint8_t Gethuaxingzhuangtan(void);
 
 void SetHuiPaiShiJian(uint8_t t);
 uint8_t GetHuiPaiShiJian(void);
#endif

