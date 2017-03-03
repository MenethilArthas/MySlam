#ifndef __PLAYBADMINTON_H
#define __PLAYBADMINTON_H


#define MIDDLE_BAT 0
#define MIDDLE_START 1
#define MIDDLE_FLAT  2

float trans_ang(int pulse);
void Rotate_Middle(int vel,double arfa);
void Init_Rotate_Middle(void);
void LeftBat_S(void);
void RightBat_S(void);
void MiddleBat_S(void);
void FaGaoqiu(void);
void FaDiQianqiu(void);
void FaDiHouqiu(void);
void CarAAA_BiPai_Init(void);
#endif

