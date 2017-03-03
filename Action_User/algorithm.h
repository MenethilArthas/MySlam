#ifndef __ALGORITHM__H
#define __ALGORITHM__H
#include "stm32f4xx.h"
#define CarAAAA_Start_XXPos -668+33
#define CarAAAA_Start_YYPos -965-60  //1070

void GO_Point_TO_Point(int vel,double aim_x,double aim_y);
void GoStraight_gyro(int vel,double w);
void ActPosCal(void);
int32_t GetEn_x(void);
void HandStraight_gyro(int x,int y);
void Gohome(float x,float y);
void GO_Point_TO_Point_V1(float x,float y);
void GO_Point_TO_Point_V2(float x,float y);
void GO_Point_TO_Point_V_daqiu(float x,float y);
void GO_Point_TO_Point_V3(float x,float y);
void GO_Point_TO_Point_Vnew(float x,float y);
uint8_t  Turnangle(int ratio,float ang);
uint8_t  Turnangle_v1(float ang);
void WalkLine(int V_car,float angle_car,float Xstart,float Ystart,float distencePID_P);
void UpDataToCamera(void);
void Handle_Walk(double vx,double vy);   //vel是速度，w是角度     姿态不变的闭环调节  5.4ms
float Get_DisX(void);
float Get_DisY(void);
float Get_AccX(void);
float Get_AccY(void);
#endif


