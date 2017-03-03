#include "flag.h"

//huiPai: 车挥拍时间指令是否有更新的标志
//         开电默认值  HuiPaiGengXin_NO
static uint8_t huiPai=HuiPaiGengXin_NO;
//此函数在接受场外摄像头或场内摄像头指令中更新车挥拍时间时调用
void SetHuiPai_FLAG(void)
{
	huiPai=HuiPaiGengXin_OK;
}
//此函数在倒计时挥拍时间的定时器中断中，当挥拍时间被更新后调用，
void ClearHuiPai_FLAG(void)
{
	huiPai=HuiPaiGengXin_NO;
}
//在倒计时挥拍时间定时器中断中每1ms查询一次挥拍时间是否有更新
uint8_t GetHuiPai_FLAG(void)
{
	return huiPai;
}


static int daqiutime=0;
void SetDaQiutime(int time)
{
	daqiutime=time;
}
 int GetDaQiutime(void)
 {
	 return daqiutime;
 }





//WaiCamera_EnOrDisable: 场外摄像头是否有效标志
//                       开电默认值  有效
static uint8_t WaiCamera_EnOrDisable=Enable;
//使能场外摄像头
void EnableWaiCamera(void)
{
	WaiCamera_EnOrDisable=Enable;
}
//失能场外摄像头
void DisableWaiCamera(void)
{
	WaiCamera_EnOrDisable=Disable;
}
//查询场外摄像头权利
uint8_t GetWaiCameraRight(void)
{
	return WaiCamera_EnOrDisable;
}




//Car_BuweiOrdaqiu 车是补位还是打球标志
static uint8_t Car_BuweiOrdaqiu=Buwei;
void SetCar_BuweiStation(void)
{
	Car_BuweiOrdaqiu=Buwei;
}

void SetCar_DaqiuStation(void)
{
	Car_BuweiOrdaqiu=Daqiu;
}

uint8_t GetCarTaskTodo(void)
{
	return Car_BuweiOrdaqiu;
}


//
static uint8_t SetCar_Station=Car_ZanTing;
void SetCarZanTingStation(void)
{
	SetCar_Station=Car_ZanTing;
}

void SetCarZhengchangtation(void)
{
	SetCar_Station=Car_Zhengchang;
}
uint8_t GetCarStation(void)
{
	return SetCar_Station;
}



static uint8_t HandData=0;
void SetHandData(uint8_t a)
{
	HandData=a;
}

uint8_t GethandData(void)
{
	return HandData;
}
void ClearHandData(void)
{
	HandData=0;
}



static uint8_t YaoGanGan_Flag=Yao_Over;
void Set_Yao_ing(void)
{
	YaoGanGan_Flag=Yao_ing;
}
void Set_Yao_Over(void)
{
	YaoGanGan_Flag=Yao_Over;
}
uint8_t Get_YaoGan(void)
{
	return YaoGanGan_Flag;
}


static double V_x_Handle=0.0,V_y_Handle=0.0;

void Set_Yao_Vel_X(double V_x)
{
	V_x_Handle=V_x;
}

void Set_Yao_Vel_Y(double V_y)
{
	V_y_Handle=V_y;
}


double get_V_x_Handle(void)
{
	return V_x_Handle;
}
double get_V_y_Handle(void)
{
	return V_y_Handle;
}




static uint8_t HuiPaiStEnFlag=HuiPaiEnd;
void HuiPai_Start(void)
{
	HuiPaiStEnFlag=HuiPaiStart;
}
void HuiPai_End(void)
{
	HuiPaiStEnFlag=HuiPaiEnd;
}
uint8_t GetHuiPaiStEnFlag(void)
{
	return HuiPaiStEnFlag;
}



static uint8_t HuiBiStEnFlag=HuiPaiEnd;
void HuiBi_Start(void)
{
	HuiBiStEnFlag=HuiBiStart;
}
void HuiBi_End(void)
{
	HuiBiStEnFlag=HuiBiEnd;
}
uint8_t GetHuiBiStEnFlag(void)
{
	return HuiBiStEnFlag;
}



static uint8_t Get_V_jiansu_Expt_Lock=unlock;
void Lock_Get_V_jiansu_Expt(void)
{
	Get_V_jiansu_Expt_Lock=lock;
}
void UnLock_Get_V_jiansu_Expt(void)
{
	Get_V_jiansu_Expt_Lock=unlock;
}
uint8_t Get_V_jiansu_Expt_LockState(void)
{
	return Get_V_jiansu_Expt_Lock;
}


static uint8_t huaxingflag=huaxingover;
void Sethuaxing(void)
{
	huaxingflag=huaxinging;
}

void Sethuaxingover(void)
{
	huaxingflag=huaxingover;
}

uint8_t Gethuaxingzhuangtan(void)
{
	return huaxingflag;
}

static uint8_t huipaishijian=0;
void SetHuiPaiShiJian(uint8_t t)
{
	huipaishijian=t;
}
uint8_t GetHuiPaiShiJian(void)
{
	return huipaishijian;
}


