#include "algorithm.h"
#include "math.h"
#include "copley.h"
#include "encoder.h"
#include "Led_Beep.h"
#include "usart.h"
#include "elmo.h"
#include "flag.h"


double ACTION_POSTION_X=CarAAAA_Start_XXPos,ACTION_POSTION_Y=CarAAAA_Start_YYPos; //车实际的坐标
double To_Camera_POSTION_X,To_Camera_POSTION_Y; //给摄像头的坐标
__IO float To_Camera_angle=0.0;//给摄像头的角度
extern __IO float Angle;





void GoStraight_gyro(int vel,double w)   //vel是速度，w是角度     姿态不变的闭环调节  5.4ms
{
		double v1=0,v2=0,v3=0,v4=0;
	  double vx,vy;
	  double v_w;
	  double v_P=1000.0;     //p调节参数
	  double v_i=15.0;
		static	  double ang_old=0;
		static    double ang_new=0;
	
	
	  ang_new=Angle;    //改过+18.2
	
	
	  vx=-vel*sin((w-45.0)/57.296);
	  vy=vel*cos((w-45.0)/57.296);
	  if(fabs(ang_new)<0.2)
		{v_w=0;}
    if(fabs(ang_new)>=0.2)
		{
			if(fabs(ang_new)>1.0)  {v_P=3000;}
			else {v_P=900;}
      v_w=v_P*(ang_new)+(ang_new-ang_old)*v_i;
    }
		v4=vx+v_w;
	  v2=-vx+v_w;
	  v1=vy+v_w;
	  v3=-vy+v_w;
    if(v1>240000) {v1=240000;}
    if(v2>240000) {v2=240000;}
	  if(v3>240000) {v3=240000;}
	  if(v4>240000) {v4=240000;}
		if(v1<-240000) {v1=-240000;}
    if(v2<-240000) {v2=-240000;}
		if(v3<-240000) {v3=-240000;}
	  if(v4<-240000) {v4=-240000;}
		
		
    VelMov_elmo(3,v3);
    VelMov_elmo(1,v1);
 	  VelMov_elmo(4,v4);
		VelMov_elmo(2,v2);
	  
    ang_old=ang_new;
}



void Handle_Walk(double vx,double vy)   //vel是速度，w是角度     姿态不变的闭环调节  5.4ms
{
		double v1=0,v2=0,v3=0,v4=0;

	  double v_w;
	  double v_P=1000.0;     //p调节参数
	  double v_i=15.0;
		static	  double ang_old=0;
		static    double ang_new=0;
	
	
		/*-------------------------场地边界限制-----------------------------*/

	
	if((ACTION_POSTION_Y<-70  )&&(vy<0))  {vy=0;}                         //场地边界值
	if((ACTION_POSTION_Y> 5600)&&(vy>0))  {vy=0;}                       //场地边界值
	 
	if((ACTION_POSTION_X>5730)&&(vx>0))   {vx=0;}                       //场地边界值
	if((ACTION_POSTION_X<335 )&&(vx<0))   {vx=0;}                         //场地边界值
	
	
	  ang_new=Angle;    //改过+18.2
	
	  if(fabs(ang_new)<0.2)
		{v_w=0;}
    if(fabs(ang_new)>=0.2)
		{
			if(fabs(ang_new)>1.0)  {v_P=3000;}
			else {v_P=900;}
      v_w=v_P*(ang_new)+(ang_new-ang_old)*v_i;
    }
		
		
		v3=-0.707*vx-0.707*vy+v_w;
	  v4= 0.707*vx-0.707*vy+v_w;
	  v1= 0.707*vx+0.707*vy+v_w;
	  v2=-0.707*vx+0.707*vy+v_w;
		
    if(v1>240000) {v1=240000;}
    if(v2>240000) {v2=240000;}
	  if(v3>240000) {v3=240000;}
	  if(v4>240000) {v4=240000;}
		if(v1<-240000) {v1=-240000;}
    if(v2<-240000) {v2=-240000;}
		if(v3<-240000) {v3=-240000;}
	  if(v4<-240000) {v4=-240000;}
		
		
    VelMov_elmo(3,v3);
    VelMov_elmo(1,v1);
 	  VelMov_elmo(4,v4);
		VelMov_elmo(2,v2);
	  
    ang_old=ang_new;
}



void GO_Point_TO_Point(int vel,double aim_x,double aim_y)   //vel是速度，w是角度     姿态不变的闭环调节
{
		double v1,v2,v3,v4;
	  double vx,vy;
	  double v_w;
	  double v_P=1000.0;     //p调节参数
	  double v_i=15.0;
	  double L=0.0;
		static	  double ang_old=0;
		static    double ang_new=0;
	
	
	  ang_new=Angle;
	  L=sqrt((aim_x-ACTION_POSTION_X)*(aim_x-ACTION_POSTION_X)+(aim_y-ACTION_POSTION_Y)*(aim_y-ACTION_POSTION_Y));
	
	  if(fabs(L)>250.0)
		{
			vx=vel*(aim_x-ACTION_POSTION_X)/L;
			vy=vel*(aim_y-ACTION_POSTION_Y)/L;
		}
		else
		{
			vx=50*(aim_x-ACTION_POSTION_X);
			vy=50*(aim_y-ACTION_POSTION_Y);
		}
	
	
	
	  if(fabs(ang_new)<0.2)
		{v_w=0;}
    if(fabs(ang_new)>=0.2)
		{
			if(fabs(ang_new)>1.0)  {v_P=3000;}
			else {v_P=700;}
      v_w=v_P*(ang_new)+(ang_new-ang_old)*v_i;
    }
		
		
		
		v3=-0.707*vx-0.707*vy+v_w;
	  v4= 0.707*vx-0.707*vy+v_w;
	  v1= 0.707*vx+0.707*vy+v_w;
	  v2=-0.707*vx+0.707*vy+v_w;
		
		
    if(v1>240000) {v1=240000;}
    if(v2>240000) {v2=240000;}
	  if(v3>240000) {v3=240000;}
	  if(v4>240000) {v4=240000;}
		if(v1<-240000) {v1=-240000;}
    if(v2<-240000) {v2=-240000;}
		if(v3<-240000) {v3=-240000;}
	  if(v4<-240000) {v4=-240000;}
		
		VelMov_elmo(1,v1);
    VelMov_elmo(3,v3);
    
 	  VelMov_elmo(4,v4);
		VelMov_elmo(2,v2);
	  
    ang_old=ang_new;
}

void HandStraight_gyro(int x,int y)
{
	  double v1,v2,v3,v4;
	  double vx,vy;
	  double v_w;
	  double v_P=1000.0;     //p调节参数
	  double v_i=15.0;
//	  double L=0.0;
		static	  double ang_old=0;
		static    double ang_new=0;
	
	
	  ang_new=Angle;


			vx=400*x;
			vy=400*y;

	
	
	
	  if(fabs(ang_new)<0.2)
		{v_w=0;}
    if(fabs(ang_new)>=0.2)
		{
			if(fabs(ang_new)>1.0)  {v_P=3000;}
			else {v_P=700;}
      v_w=v_P*(ang_new)+(ang_new-ang_old)*v_i;
    }
		
		
		
		v3=-0.707*vx-0.707*vy+v_w;
	  v4= 0.707*vx-0.707*vy+v_w;
	  v1= 0.707*vx+0.707*vy+v_w;
	  v2=-0.707*vx+0.707*vy+v_w;
		
		
    if(v1>240000) {v1=240000;}
    if(v2>240000) {v2=240000;}
	  if(v3>240000) {v3=240000;}
	  if(v4>240000) {v4=240000;}
		if(v1<-240000) {v1=-240000;}
    if(v2<-240000) {v2=-240000;}
		if(v3<-240000) {v3=-240000;}
	  if(v4<-240000) {v4=-240000;}
		
		VelMov_elmo(1,v1);
    VelMov_elmo(3,v3);
    
 	  VelMov_elmo(4,v4);
		VelMov_elmo(2,v2);
	  
    ang_old=ang_new;
}






#define ENCODER_TIM_PERIOD (MAX_COUNT*4)    //比 每个定时周期内可能出现的计数最大值 还要大的值. 取值<=65535
#define MAX_COUNT          14436        //每个周期内的最大计数脉冲, 14436=350 r/s
#define COUNTER_RESET    0
#define ICx_FILTER         6

extern volatile int32_t Encoder_CurPos[4];
static int32_t En_x=0,En_y=0;
static float DisX=0,DisY=0;
static float AccX=0,AccY=0;
float Get_DisX(void)
{
	return DisX;
}
float Get_DisY(void)
{
	return DisY;
}

float Get_AccX(void)
{
	return AccX;
}
float Get_AccY(void)
{
	return AccY;
}


static uint16_t lastCount_left=0,curCount_left=0,lastCount_right=0,curCount_right=0;
void ActPosCal(void)
{
	
  static float OldDisX=0,OldDisY=0;
	

	curCount_left=TIM4->CNT;                        //无符号16位
	En_x = curCount_left - lastCount_left;
	if(En_x >= MAX_COUNT)
  {    
	 En_x -= ENCODER_TIM_PERIOD;  
  }
  else if(En_x < -MAX_COUNT)
  {    
	 En_x += ENCODER_TIM_PERIOD; 
  } 
  lastCount_left = curCount_left;

	
	
	curCount_right=TIM3->CNT;                        //无符号16位
	En_y =-( curCount_right - lastCount_right);
	if(En_y >= MAX_COUNT)
  {    
	 En_y -= ENCODER_TIM_PERIOD;  
  }
  else if(En_y < -MAX_COUNT)
  {    
	 En_y += ENCODER_TIM_PERIOD; 
  } 
  lastCount_right = curCount_right;
	
	
	
	
	DisX=(En_x*cos((Angle+45.0+0.609)/57.29577951)-En_y*sin((Angle+45.0+0.609)/57.29577951));							
	DisY=(En_x*sin((Angle+45.0+0.609)/57.29577951)+En_y*cos((Angle+45.0+0.609)/57.29577951));
	
  AccX=DisX-OldDisX;//加速度
	AccY=DisY-OldDisY;//加速度
	
  OldDisX=DisX;
	OldDisY=DisY;
	
	
	ACTION_POSTION_X+=(DisX*0.019446);//理论0.01948  实际左0.019518   右0.0194664
	ACTION_POSTION_Y+=(DisY*0.019446);

	
	Encoder_CurPos[0]+=En_x;
	Encoder_CurPos[1]+=En_y;
	
}

void UpDataToCamera(void)
{
	static volatile double DataBuffer[2][14]={0};
	static __IO float DataBuffer_angle[14]={0};
	
	static uint8_t i=0;
	
	To_Camera_POSTION_X=DataBuffer[0][i];
	To_Camera_POSTION_Y=DataBuffer[1][i];
	To_Camera_angle    =DataBuffer_angle[i];
	
	DataBuffer[0][i]=ACTION_POSTION_X;
	DataBuffer[1][i]=ACTION_POSTION_Y;
	DataBuffer_angle[i]=(1000.0*Angle);
	i++;
	if(i>=13)
		i=0;
}

int32_t GetEn_x(void)
{
	return En_x;
}






#if DEBUG
uint32_t num=0;
uint32_t Sendnum=0;
double x_postion_debug[100]={0},y_postion_debug[100]={0};
double x_aimpostion_debug[100]={0},y_aimpostion_debug[100]={0};
float  L_actual_debug[100]={0};
float  V_Geiding_debug[100]={0};
float  L_theoryToStop_debug[100]={0};
float  V_actual2_debug[100]={0};

float  Vx_debug[100]={0};
float  Vy_debug[100]={0};

float  Vneedx_debug[100]={0};
float  Vneedy_debug[100]={0};
float  Vneed_debug[100]={0};

float  Vndelx_debug[100]={0};
float  Vndely_debug[100]={0};

float  CosQ_debug[100]={0};
float  acc_debug[100]={0};
int time_debug[100]={0};
#endif 




#define EncoderTomm_Zhu  0.0157839            //主动轮脉冲/s     转化为mm/s
#define EncoderTomm_Cong 1.94816              //从动轮脉冲/10ms  转化为mm/s
#define CongTo_Zhu  123.426                   //从动轮脉冲/10ms  转化为  主动轮脉冲/s  
#define De_Ae_EncoderTomm_Zhu  1.57839              //主动轮脉冲/10ms^2 转化为mm/s^2

void GO_Point_TO_Point_V2(float x,float y)
{
	static	float Vx_actual=0.0,Vy_actual=0.0,V_actual2=0.0;    //实际速度  编码器测得 mm/s
	static	float V_Geiding=0.0;  //给定速度  主动轮 脉冲/s
		
	static	float L_actual=0.0,L_theoryToStop=0.0;
	static	float V_max=0.0;
	static	float V_maxold=0.0;	
	
	static    double Acc_min=2500;//最大加减速度  m/s^2
	static    double Acc_act=0;
	static    double Acc_actold=0;
	
	static    double x_unit=0;
	static    double y_unit=0;
	static    double x_unitold=0;
	static    double y_unitold=0;
	
	
	static  double V_jiansu_Expect=0;				
  static  float cosQ=1.0;//实际速度与理想路线夹角
	static  float cosQold=1.0;//实际速度与理想路线夹角
	
	static  double Ver_err_sum=0;	
	static  double Ver_err_old=0;	
	static  double Ver_err_new=0;	
	
	static	  double vx,vy;
	static	  double ang_old=0;
	static    double ang_new=0;
	static    double ang_err_sum=0;
	double v_w;
	double v_P=1500.0;     //p调节参数
	
	double v1,v2,v3,v4;
	double v_i=150.0;
	
	
	static double V_need=0.0;
	static double V_x_need=0.0;
	static double V_y_need=0.0;
//	static double V_del=0.0;
	static double V_x_del=0.0;
	static double V_y_del=0.0;
	
	
	/*-------------------------场地边界限制-----------------------------*/
	
	if(y<-70)  {y=-70;}                         //场地边界值
	if(y>5600)  {y=5600;}                       //场地边界值
	 
	if(x>5730)  {x=5730;}                       //场地边界值
	if(x<335)  {x=335;}                         //场地边界值
	
	
	
	
	
	//计算实际距离
	L_actual=sqrt((ACTION_POSTION_X-x)*(ACTION_POSTION_X-x)+(ACTION_POSTION_Y-y)*(ACTION_POSTION_Y-y));
	
	Vx_actual=DisX*1.9518;
	Vy_actual=DisY*1.9466;
	
	
	V_actual2=sqrt(Vx_actual*Vx_actual+Vy_actual*Vy_actual);     // mm^2/s^2
   /*------------------------当落点离车较远时 加速度取大值 否则 取小值------------------------------*/
	if(L_actual>1000)
	{
		Acc_min=2500;
	}
	else
	{
		Acc_min=2500;
	}
	
	
	 /*-------------------------------------当走到位时-------------------------------------------*/
	if((L_actual<10)&&(V_actual2<300))
	{
		  cosQold=1;
			Ver_err_old=0;
			Ver_err_new=0;	
			Ver_err_sum=0;	
		  V_jiansu_Expect=0;
		  vx=0;
		  vy=0;
	}
	/*------------------------当走到位没有停下来或没有走到位时------------------------------------*/
	else
	{
					/*----------------------------计算实际的加速度和最大速度-------------------------------------*/
					if(L_actual>=10)
					{
						Acc_act=Acc_min+0.415*Acc_min*(fabs(fabs(ACTION_POSTION_X-x)-fabs(ACTION_POSTION_Y-y))/(fabs((ACTION_POSTION_X-x)+fabs(ACTION_POSTION_Y-y))));		
						V_max=(240000+70000*(fabs((ACTION_POSTION_X-x)-(ACTION_POSTION_Y-y))/fabs((ACTION_POSTION_X-x)+(ACTION_POSTION_Y-y))))*0.0157839;
						Acc_actold=Acc_act;
						V_maxold=V_max;
						
						x_unit=(x-ACTION_POSTION_X)/L_actual;
						y_unit=(y-ACTION_POSTION_Y)/L_actual;
						x_unitold=x_unit;
						y_unitold=y_unit;
					}
					else
					{
						 Acc_act=Acc_actold;  //根据历史记录给定值
																	//计算速度最大值（根据方向）       //脉冲/s
						 V_max=V_maxold;      //EncoderTomm_Zhu  0.0157839 
						 x_unit=x_unitold;
						 y_unit=y_unitold;
					}
					

					
		      /*-------------------------计算车速与车路线夹角--------------------------------------*/
					if((V_actual2>10)&&(L_actual>10))//计算夹角
					{
						cosQ=(Vx_actual*(x-ACTION_POSTION_X)+Vy_actual*(y-ACTION_POSTION_Y))/(V_actual2*L_actual);
						cosQold=cosQ;
					}
					else
					{
						cosQ=cosQold;
					}
					
					
					V_need=V_actual2*cosQ;           //在理想路线上投影速度
					V_x_need=V_need*x_unit;
					V_y_need=V_need*y_unit;
					
					V_x_del=Vx_actual-V_x_need;            //要消除的速度分量
					V_y_del=Vy_actual-V_y_need;						
									
		      /*-------------------------------当车走向目标点时-------------------------------------*/			
		      if(cosQ>=0)
					{
	
								
								/*------------计算当前有效速度和加速度值 稳当停车需要的距离------------*/ 
								L_theoryToStop=V_need*V_need*0.5/Acc_act;	
						    
						
						    /*车离目标点很远时 即要加速 或匀速时*/
						    if(L_actual>L_theoryToStop)
								{
										if(Get_V_jiansu_Expt_LockState()==unlock)
										{
											Lock_Get_V_jiansu_Expt();
											V_jiansu_Expect=V_need/0.0157839;
										}
										
										if((V_Geiding*0.0157839)>=V_max)   //匀速
										{
											V_jiansu_Expect=V_jiansu_Expect;
										}
										else                           //加速
										{
											V_jiansu_Expect=V_jiansu_Expect+Acc_act/1.57839;     //期望的速度(减速度阶段)										
										}
										
								}
								else
								{
								    V_jiansu_Expect=sqrt(L_actual*2.0*Acc_act)/0.0157839;
								}
								
								
								Ver_err_new=V_jiansu_Expect-V_need/0.0157839;
						    Ver_err_sum+=V_jiansu_Expect-V_need/0.0157839;
								
								V_Geiding=V_jiansu_Expect+6.0*(V_jiansu_Expect-V_need/0.0157839)+2.8*(Ver_err_new-Ver_err_old)+0.0015*Ver_err_sum;
								Ver_err_old=Ver_err_new;
								
								

								
						
					}
          /*-------------------------------当车走过目标点（即超调）时-------------------------------------*/					
					else
					{
						
						if(L_actual>40)  //当超调较多时
						{
							V_Geiding=50000+240.0*(L_actual);
						}
						else//当超调较少时
						{
							V_Geiding=50000;
						}	
						
            cosQold=1;	
						V_jiansu_Expect=0;
						Ver_err_old=0;
						Ver_err_new=0;	
						Ver_err_sum=0;	
						V_x_del=0;
						V_y_del=0;					
					}
					
					vx=V_Geiding*x_unit-2.0*V_x_del/0.0157839;
					vy=V_Geiding*y_unit-2.0*V_y_del/0.0157839;			
	}
	
	
	
	/*---------------------------角度闭环 要实时进行----------------------------*/
	
	  ang_new=Angle;
	  ang_err_sum+=ang_new;
	//角度闭环
		if(fabs(ang_new)<0.2)
		{v_w=0;}
    if(fabs(ang_new)>=0.2)
		{
			if(fabs(ang_new)>1.0)  {v_P=8000;}
			else {v_P=5000;}
      v_w=v_P*(ang_new)+(ang_new-ang_old)*v_i+0.4*ang_err_sum;
    }
		ang_old=ang_new;

		if(v_w>80000)
		{
			v_w=80000;
		}
		
		if(v_w<-80000)
		{
			v_w=-80000;
		}
	
		v3=-0.707*vx-0.707*vy+v_w;
	  v4= 0.707*vx-0.707*vy+v_w;
	  v1= 0.707*vx+0.707*vy+v_w;
	  v2=-0.707*vx+0.707*vy+v_w;
		
		
    if(v1>240000) {v1=240000;}
    if(v2>240000) {v2=240000;}
	  if(v3>240000) {v3=240000;}
	  if(v4>240000) {v4=240000;}
		if(v1<-240000) {v1=-240000;}
    if(v2<-240000) {v2=-240000;}
		if(v3<-240000) {v3=-240000;}
	  if(v4<-240000) {v4=-240000;}
		
		
		
		
		VelMov_elmo(1,v1);
		VelMov_elmo(2,v2);
    VelMov_elmo(3,v3);
    
 	  VelMov_elmo(4,v4);
		

		

//#if DEBUG		

//	  x_postion_debug[num%100]=ACTION_POSTION_X;
//		y_postion_debug[num%100]=ACTION_POSTION_Y;
//		x_aimpostion_debug[num%100]=x;
//		y_aimpostion_debug[num%100]=y;
//		L_actual_debug[num%100]=L_actual;
//    V_Geiding_debug[num%100]=V_Geiding;
//    L_theoryToStop_debug[num%100]=L_theoryToStop;
//		
//		V_actual2_debug[num%100]=V_actual2;
//		Vx_debug[num%100]=Vx_actual;
//		Vy_debug[num%100]=Vy_actual;
//		
//		Vneedx_debug[num%100]=V_x_need;
//		Vneedy_debug[num%100]=V_y_need;
//		Vneed_debug[num%100]=V_need;
//		
//		Vndelx_debug[num%100]=V_x_del;
//		Vndely_debug[num%100]=V_y_del;
//		
//		CosQ_debug[num%100]=1000*cosQ;
//		acc_debug[num%100]=Acc_act;
//		num++;
//#endif 
		
	
}

void GO_Point_TO_Point_V_daqiu(float x,float y)
{
	static	float Vx_actual=0.0,Vy_actual=0.0,V_actual2=0.0;    //实际速度  编码器测得 mm/s
	static	float V_Geiding=0.0;  //给定速度  主动轮 脉冲/s
		
	static	float L_actual=0.0,L_theoryToStop=0.0;
	static	float V_max=0.0;
	static	float V_maxold=0.0;	
	
	static    double Acc_min=2500;//最大加减速度  mm/s^2
	static    double Acc_act=0;
	static    double Acc_actold=0;

	static    double Acc_min1=2500;//最大加减速度  mm/s^2
	static    double Acc_act1=0;
	static    double Acc_actold1=0;

	
	static    double x_unit=0;
	static    double y_unit=0;
	static    double x_unitold=0;
	static    double y_unitold=0;
	
	
	static  double V_jiansu_Expect=0;				
  static  float cosQ=1.0;//实际速度与理想路线夹角
	static  float cosQold=1.0;//实际速度与理想路线夹角
	
	static  double Ver_err_sum=0;	
	static  double Ver_err_old=0;	
	static  double Ver_err_new=0;	
	
	static int timetogo=0;//车要走的时间
	static int timejiansu=0;//车减速的时间
	
	
	
	static	  double vx,vy;
	static	  double ang_old=0;
	static    double ang_new=0;
	static    double ang_err_sum=0;
	double v_w;
	double v_P=1500.0;     //p调节参数
	
	double v1,v2,v3,v4;
	double v_i=150.0;
	
	
	static double V_need=0.0;
	static double V_x_need=0.0;
	static double V_y_need=0.0;
//	static double V_del=0.0;
	static double V_x_del=0.0;
	static double V_y_del=0.0;
	
	
	/*-------------------------场地边界限制-----------------------------*/
	
	if(y<-70)  {y=-70;}                         //场地边界值
	if(y>5600)  {y=5600;}                       //场地边界值
	 
	if(x>5730)  {x=5730;}                       //场地边界值
	if(x<335)  {x=335;}                         //场地边界值
	
	
	
	
	
	//计算实际距离
	L_actual=sqrt((ACTION_POSTION_X-x)*(ACTION_POSTION_X-x)+(ACTION_POSTION_Y-y)*(ACTION_POSTION_Y-y));
	
	Vx_actual=DisX*1.9518;
	Vy_actual=DisY*1.9466;
	
	
	V_actual2=sqrt(Vx_actual*Vx_actual+Vy_actual*Vy_actual);     // mm^2/s^2
   /*------------------------当落点离车较远时 加速度取大值 否则 取小值------------------------------*/
	if(L_actual>1000)
	{
		Acc_min=2500;
	}
	else
	{
		Acc_min=2500;
	}
	
	
	 /*-------------------------------------当走到位时-------------------------------------------*/
	if((L_actual<10)&&(V_actual2<300))
	{
		  cosQold=1;
			Ver_err_old=0;
			Ver_err_new=0;	
			Ver_err_sum=0;	
		  V_jiansu_Expect=0;
		  vx=0;
		  vy=0;
		  Sethuaxing();
	}
	/*------------------------当走到位没有停下来或没有走到位时------------------------------------*/
	else
	{
					/*----------------------------计算实际的加速度和最大速度-------------------------------------*/
					if(L_actual>=10)
					{
						Acc_act=Acc_min+0.415*Acc_min*(fabs(fabs(ACTION_POSTION_X-x)-fabs(ACTION_POSTION_Y-y))/(fabs((ACTION_POSTION_X-x)+fabs(ACTION_POSTION_Y-y))));		
						Acc_act1=Acc_min1+0.415*Acc_min1*(fabs(fabs(ACTION_POSTION_X-x)-fabs(ACTION_POSTION_Y-y))/(fabs((ACTION_POSTION_X-x)+fabs(ACTION_POSTION_Y-y))));		
						V_max=(240000+70000*(fabs((ACTION_POSTION_X-x)-(ACTION_POSTION_Y-y))/fabs((ACTION_POSTION_X-x)+(ACTION_POSTION_Y-y))))*0.0157839;
						Acc_actold=Acc_act;
						Acc_actold1=Acc_act1;
						V_maxold=V_max;
						
						x_unit=(x-ACTION_POSTION_X)/L_actual;
						y_unit=(y-ACTION_POSTION_Y)/L_actual;
						x_unitold=x_unit;
						y_unitold=y_unit;
					}
					else
					{
						 Acc_act=Acc_actold;  //根据历史记录给定值
						 Acc_act1=Acc_actold1;
																	//计算速度最大值（根据方向）       //脉冲/s
						 V_max=V_maxold;      //EncoderTomm_Zhu  0.0157839 
						 x_unit=x_unitold;
						 y_unit=y_unitold;
					}
					

					
		      /*-------------------------计算车速与车路线夹角--------------------------------------*/
					if((V_actual2>10)&&(L_actual>10))//计算夹角
					{
						cosQ=(Vx_actual*(x-ACTION_POSTION_X)+Vy_actual*(y-ACTION_POSTION_Y))/(V_actual2*L_actual);
						cosQold=cosQ;
					}
					else
					{
						cosQ=cosQold;
					}
					
					
					V_need=V_actual2*cosQ;           //在理想路线上投影速度
					V_x_need=V_need*x_unit;
					V_y_need=V_need*y_unit;
					
					V_x_del=Vx_actual-V_x_need;            //要消除的速度分量
					V_y_del=Vy_actual-V_y_need;						
									
		      /*-------------------------------当车走向目标点时-------------------------------------*/			
		      if(cosQ>=0)
					{
	
								timetogo=GetDaQiutime();//得到车要走的时间！！！！！
						    timejiansu=1000*V_need/Acc_act;//车减速的时间  单位ms
						    if(timejiansu<timetogo)//给车走的时间很长！！！
								{
									timetogo=timejiansu;
								}
						
						
								if((timetogo<50)&&(L_actual>30))//如果没有走到
								{
									timetogo=50;
								}
								
									
								/*------------计算当前有效速度和加速度值 稳当停车需要的距离------------*/ 
								//L_theoryToStop=V_need*V_need*0.5/Acc_act;	
						    L_theoryToStop=V_need*(timetogo*0.001)-0.5*Acc_act*timetogo*timetogo*0.000001;//mm
								
						
						    /*车离目标点很远时 即要加速 或匀速时*/
						    if(L_actual>L_theoryToStop)
								{
										if(Get_V_jiansu_Expt_LockState()==unlock)
										{
											Lock_Get_V_jiansu_Expt();
											V_jiansu_Expect=V_need/0.0157839;
										}
										
										if((V_Geiding*0.0157839)>=V_max)   //匀速
										{
											V_jiansu_Expect=V_jiansu_Expect;
										}
										else                           //加速
										{
											V_jiansu_Expect=V_jiansu_Expect+Acc_act1/1.57839;     //期望的速度(减速度阶段)										
										}
										
								}
								else
								{
									
								  	V_jiansu_Expect=(L_actual/(timetogo*0.001)+0.5*Acc_act*timetogo*0.001)/0.0157839;	
							
								}
								
								
								Ver_err_new=V_jiansu_Expect-V_need/0.0157839;
						    Ver_err_sum+=V_jiansu_Expect-V_need/0.0157839;
								
								V_Geiding=V_jiansu_Expect+6.0*(V_jiansu_Expect-V_need/0.0157839)+2.8*(Ver_err_new-Ver_err_old)+0.0015*Ver_err_sum;
								Ver_err_old=Ver_err_new;
								
								

								
						
					}
          /*-------------------------------当车走过目标点（即超调）时-------------------------------------*/					
					else
					{
						
						if(L_actual>40)  //当超调较多时
						{
							V_Geiding=50000+240.0*(L_actual);
						}
						else//当超调较少时
						{
							V_Geiding=50000;
						}	
						
            cosQold=1;	
						V_jiansu_Expect=0;
						Ver_err_old=0;
						Ver_err_new=0;	
						Ver_err_sum=0;	
						V_x_del=0;
						V_y_del=0;					
					}
					
					if(timetogo>2)
					{
						vx=V_Geiding*x_unit-2.0*V_x_del/0.0157839;
						vy=V_Geiding*y_unit-2.0*V_y_del/0.0157839;	
					}	
					else
					{
						vx=0;
						vy=0;
					}	
	}
	
	
	
	/*---------------------------角度闭环 要实时进行----------------------------*/
	
	  ang_new=Angle;
	  ang_err_sum+=ang_new;
	//角度闭环
		if(fabs(ang_new)<0.2)
		{v_w=0;}
    if(fabs(ang_new)>=0.2)
		{
			if(fabs(ang_new)>1.0)  {v_P=8000;}
			else {v_P=5000;}
      v_w=v_P*(ang_new)+(ang_new-ang_old)*v_i+0.4*ang_err_sum;
    }
		ang_old=ang_new;

		if(v_w>80000)
		{
			v_w=80000;
		}
		
		if(v_w<-80000)
		{
			v_w=-80000;
		}
	
		v3=-0.707*vx-0.707*vy+v_w;
	  v4= 0.707*vx-0.707*vy+v_w;
	  v1= 0.707*vx+0.707*vy+v_w;
	  v2=-0.707*vx+0.707*vy+v_w;
		
		
    if(v1>240000) {v1=240000;}
    if(v2>240000) {v2=240000;}
	  if(v3>240000) {v3=240000;}
	  if(v4>240000) {v4=240000;}
		if(v1<-240000) {v1=-240000;}
    if(v2<-240000) {v2=-240000;}
		if(v3<-240000) {v3=-240000;}
	  if(v4<-240000) {v4=-240000;}
		
		
		
		
		VelMov_elmo(1,v1);
		VelMov_elmo(2,v2);
    VelMov_elmo(3,v3);
    
 	  VelMov_elmo(4,v4);
		

		

#if DEBUG		
		time_debug[num%100]=timetogo;
	  x_postion_debug[num%100]=ACTION_POSTION_X;
		y_postion_debug[num%100]=ACTION_POSTION_Y;
		x_aimpostion_debug[num%100]=x;
		y_aimpostion_debug[num%100]=y;
		L_actual_debug[num%100]=L_actual;
    V_Geiding_debug[num%100]=V_Geiding;
    L_theoryToStop_debug[num%100]=L_theoryToStop;
		
		V_actual2_debug[num%100]=V_actual2;
		Vx_debug[num%100]=Vx_actual;
		Vy_debug[num%100]=Vy_actual;
		
		Vneedx_debug[num%100]=V_x_need;
		Vneedy_debug[num%100]=V_y_need;
		Vneed_debug[num%100]=V_need;
		
		Vndelx_debug[num%100]=V_x_del;
		Vndely_debug[num%100]=V_y_del;
		
		CosQ_debug[num%100]=1000*cosQ;
		acc_debug[num%100]=Acc_act;
		num++;
#endif 
		
	
}

void Gohome(float x,float y)
{
	static	float Vx_actual=0.0,Vy_actual=0.0,V_actual2=0.0;    //实际速度  编码器测得 mm/s
	static	float V_Geiding=0.0;  //给定速度  主动轮 脉冲/s
		
	static	float L_actual=0.0,L_theoryToStop=0.0;
	static	float V_max=0.0;
	static	float V_maxold=0.0;	
	
	static    double Acc_min=1500;//最大加减速度  m/s^2
	static    double Acc_act=0;
	static    double Acc_actold=0;
	
	static    double x_unit=0;
	static    double y_unit=0;
	static    double x_unitold=0;
	static    double y_unitold=0;
	
	
	static  double V_jiansu_Expect=0;				
  static  float cosQ=1.0;//实际速度与理想路线夹角
	static  float cosQold=1.0;//实际速度与理想路线夹角
	
	static  double Ver_err_sum=0;	
	static  double Ver_err_old=0;	
	static  double Ver_err_new=0;	
	
	static	  double vx,vy;
	static	  double ang_old=0;
	static    double ang_new=0;
	static    double ang_err_sum=0;
	double v_w;
	double v_P=1500.0;     //p调节参数
	
	double v1,v2,v3,v4;
	double v_i=150.0;
	
	
	static double V_need=0.0;
	static double V_x_need=0.0;
	static double V_y_need=0.0;
//	static double V_del=0.0;
	static double V_x_del=0.0;
	static double V_y_del=0.0;
	
	
//	/*-------------------------场地边界限制-----------------------------*/
//	
//	if(y<-70)  {y=-70;}                         //场地边界值
//	if(y>5600)  {y=5600;}                       //场地边界值
//	 
//	if(x>5730)  {x=5730;}                       //场地边界值
//	if(x<335)  {x=335;}                         //场地边界值
	
	
	
	
	
	//计算实际距离
	L_actual=sqrt((ACTION_POSTION_X-x)*(ACTION_POSTION_X-x)+(ACTION_POSTION_Y-y)*(ACTION_POSTION_Y-y));
	
	Vx_actual=DisX*1.9518;
	Vy_actual=DisY*1.9466;
	
	
	V_actual2=sqrt(Vx_actual*Vx_actual+Vy_actual*Vy_actual);     // mm^2/s^2
   /*------------------------当落点离车较远时 加速度取大值 否则 取小值------------------------------*/
	if(L_actual>1000)
	{
		Acc_min=2500;
	}
	else
	{
		Acc_min=2500;
	}
	
	
	 /*-------------------------------------当走到位时-------------------------------------------*/
	if((L_actual<10)&&(V_actual2<300))
	{
		  cosQold=1;
			Ver_err_old=0;
			Ver_err_new=0;	
			Ver_err_sum=0;	
		  V_jiansu_Expect=0;
		  vx=0;
		  vy=0;
	}
	/*------------------------当走到位没有停下来或没有走到位时------------------------------------*/
	else
	{
					/*----------------------------计算实际的加速度和最大速度-------------------------------------*/
					if(L_actual>=10)
					{
						Acc_act=Acc_min+0.415*Acc_min*(fabs(fabs(ACTION_POSTION_X-x)-fabs(ACTION_POSTION_Y-y))/(fabs((ACTION_POSTION_X-x)+fabs(ACTION_POSTION_Y-y))));		
						V_max=(240000+70000*(fabs((ACTION_POSTION_X-x)-(ACTION_POSTION_Y-y))/fabs((ACTION_POSTION_X-x)+(ACTION_POSTION_Y-y))))*0.0157839;
						Acc_actold=Acc_act;
						V_maxold=V_max;
						
						x_unit=(x-ACTION_POSTION_X)/L_actual;
						y_unit=(y-ACTION_POSTION_Y)/L_actual;
						x_unitold=x_unit;
						y_unitold=y_unit;
					}
					else
					{
						 Acc_act=Acc_actold;  //根据历史记录给定值
																	//计算速度最大值（根据方向）       //脉冲/s
						 V_max=V_maxold;      //EncoderTomm_Zhu  0.0157839 
						 x_unit=x_unitold;
						 y_unit=y_unitold;
					}
					

					
		      /*-------------------------计算车速与车路线夹角--------------------------------------*/
					if((V_actual2>10)&&(L_actual>10))//计算夹角
					{
						cosQ=(Vx_actual*(x-ACTION_POSTION_X)+Vy_actual*(y-ACTION_POSTION_Y))/(V_actual2*L_actual);
						cosQold=cosQ;
					}
					else
					{
						cosQ=cosQold;
					}
					
					
					V_need=V_actual2*cosQ;           //在理想路线上投影速度
					V_x_need=V_need*x_unit;
					V_y_need=V_need*y_unit;
					
					V_x_del=Vx_actual-V_x_need;            //要消除的速度分量
					V_y_del=Vy_actual-V_y_need;						
									
		      /*-------------------------------当车走向目标点时-------------------------------------*/			
		      if(cosQ>=0)
					{
	
								
								/*------------计算当前有效速度和加速度值 稳当停车需要的距离------------*/ 
								L_theoryToStop=V_need*V_need*0.5/Acc_act;	
						    
						
						    /*车离目标点很远时 即要加速 或匀速时*/
						    if(L_actual>L_theoryToStop)
								{
										if(Get_V_jiansu_Expt_LockState()==unlock)
										{
											Lock_Get_V_jiansu_Expt();
											V_jiansu_Expect=V_need/0.0157839;
										}
										
										if((V_Geiding*0.0157839)>=V_max)   //匀速
										{
											V_jiansu_Expect=V_jiansu_Expect;
										}
										else                           //加速
										{
											V_jiansu_Expect=V_jiansu_Expect+Acc_act/1.57839;     //期望的速度(减速度阶段)										
										}
										
								}
								else
								{
								    V_jiansu_Expect=sqrt(L_actual*2.0*Acc_act)/0.0157839;
								}
								
								
								Ver_err_new=V_jiansu_Expect-V_need/0.0157839;
						    Ver_err_sum+=V_jiansu_Expect-V_need/0.0157839;
								
								V_Geiding=V_jiansu_Expect+6.0*(V_jiansu_Expect-V_need/0.0157839)+2.8*(Ver_err_new-Ver_err_old)+0.0015*Ver_err_sum;
								Ver_err_old=Ver_err_new;
								
								

								
						
					}
          /*-------------------------------当车走过目标点（即超调）时-------------------------------------*/					
					else
					{
						
						if(L_actual>40)  //当超调较多时
						{
							V_Geiding=50000+240.0*(L_actual);
						}
						else//当超调较少时
						{
							V_Geiding=50000;
						}	
						
            cosQold=1;	
						V_jiansu_Expect=0;
						Ver_err_old=0;
						Ver_err_new=0;	
						Ver_err_sum=0;	
						V_x_del=0;
						V_y_del=0;					
					}
					
					vx=V_Geiding*x_unit-2.0*V_x_del/0.0157839;
					vy=V_Geiding*y_unit-2.0*V_y_del/0.0157839;			
	}
	
	
	
	/*---------------------------角度闭环 要实时进行----------------------------*/
	
	  ang_new=Angle;
	  ang_err_sum+=ang_new;
	//角度闭环
		if(fabs(ang_new)<0.2)
		{v_w=0;}
    if(fabs(ang_new)>=0.2)
		{
			if(fabs(ang_new)>1.0)  {v_P=8000;}
			else {v_P=5000;}
      v_w=v_P*(ang_new)+(ang_new-ang_old)*v_i+0.4*ang_err_sum;
    }
		ang_old=ang_new;

		if(v_w>80000)
		{
			v_w=80000;
		}
		
		if(v_w<-80000)
		{
			v_w=-80000;
		}
	
		v3=-0.707*vx-0.707*vy+v_w;
	  v4= 0.707*vx-0.707*vy+v_w;
	  v1= 0.707*vx+0.707*vy+v_w;
	  v2=-0.707*vx+0.707*vy+v_w;
		
		
    if(v1>240000) {v1=240000;}
    if(v2>240000) {v2=240000;}
	  if(v3>240000) {v3=240000;}
	  if(v4>240000) {v4=240000;}
		if(v1<-240000) {v1=-240000;}
    if(v2<-240000) {v2=-240000;}
		if(v3<-240000) {v3=-240000;}
	  if(v4<-240000) {v4=-240000;}
		
		
		
		
		VelMov_elmo(1,v1);
		VelMov_elmo(2,v2);
    VelMov_elmo(3,v3);
    
 	  VelMov_elmo(4,v4);
		

		

//#if DEBUG		

//	  x_postion_debug[num%100]=ACTION_POSTION_X;
//		y_postion_debug[num%100]=ACTION_POSTION_Y;
//		x_aimpostion_debug[num%100]=x;
//		y_aimpostion_debug[num%100]=y;
//		L_actual_debug[num%100]=L_actual;
//    V_Geiding_debug[num%100]=V_Geiding;
//    L_theoryToStop_debug[num%100]=L_theoryToStop;
//		
//		V_actual2_debug[num%100]=V_actual2;
//		Vx_debug[num%100]=Vx_actual;
//		Vy_debug[num%100]=Vy_actual;
//		
//		Vneedx_debug[num%100]=V_x_need;
//		Vneedy_debug[num%100]=V_y_need;
//		Vneed_debug[num%100]=V_need;
//		
//		Vndelx_debug[num%100]=V_x_del;
//		Vndely_debug[num%100]=V_y_del;
//		
//		CosQ_debug[num%100]=1000*cosQ;
//		acc_debug[num%100]=Acc_act;
//		num++;
//#endif 
		
	
}


void GO_Point_TO_Point_V1(float x,float y)
{
//	static	float De_Aeceleration=0.0;          //加速度   mm/s^2
	static	float Vx_actual=0.0,Vy_actual=0.0,V_actual2=0.0;    //实际速度  编码器测得 mm/s
	static	float V_Geiding=0.0;  //给定速度  主动轮 脉冲/s
		
	static	float L_actual=0.0,L_theoryToStop=0.0;
	static	float V_max=0.0;
		
		
		
		
	static	double vx,vy;
	static	  double ang_old=0;

	static    double ang_new=0;
	static    double ang_err_sum=0;
	double v_w;
	double v_P=1500.0;     //p调节参数
	
	double v1,v2,v3,v4;
	double v_i=120.0;
	
	if(y<-70)  {y=-70;}                         //场地边界值
	if(y>4700)  {y=4700;}                       //场地边界值
	 
	if(x>5730)  {x=5730;}                       //场地边界值
	if(x<335)  {x=335;}                         //场地边界值
	
	
	ang_new=Angle;
	
	//计算实际距离
	L_actual=sqrt((ACTION_POSTION_X-x)*(ACTION_POSTION_X-x)+(ACTION_POSTION_Y-y)*(ACTION_POSTION_Y-y));
	
	if(L_actual>10)
	{
		V_max=(250000+70000*(fabs((ACTION_POSTION_X-x)-(ACTION_POSTION_Y-y))/fabs((ACTION_POSTION_X-x)+(ACTION_POSTION_Y-y))))*0.0157839;
	}else
	{
	
	//计算速度最大值（根据方向）       //脉冲/s
//	V_max=100000*EncoderTomm_Zhu;     //EncoderTomm_Zhu  0.0157839 
   V_max=250000*0.0157839;     //EncoderTomm_Zhu  0.0157839 
	}
	
	//调试加速度             //    车主动轮mm/s^2
//	De_Aeceleration=200*De_Ae_EncoderTomm_Zhu;   //De_Ae_EncoderTomm_Zhu  1.57839 
//	De_Aeceleration=3000.0*1.57839;   //De_Ae_EncoderTomm_Zhu  1.57839 
	
	
	
	//根据实际速度  加速度 计算减速距离    mm/s
//	Vx_actual=En_x*EncoderTomm_Cong;     //EncoderTomm_Cong 1.94816 
//	Vy_actual=En_y*EncoderTomm_Cong;
	Vx_actual=(float)En_x*1.94816;     //EncoderTomm_Cong 1.94816 
	Vy_actual=(float)En_y*1.94816;
	
	V_actual2=sqrt(Vx_actual*Vx_actual+Vy_actual*Vy_actual);     // mm^2/s^2
	
//	L_theoryToStop=V_actual2/(2*De_Aeceleration);    //脉冲与mm转化
   L_theoryToStop=(V_Geiding*0.0157839*V_Geiding*0.0157839)/(2500.0*1.57839);
	

	
	//判断加速  减速  匀速 
	if(L_actual>=L_theoryToStop)     //加速   或匀速
	{
		
		if(V_actual2>=V_max)   //匀速
		{
//			Beep_ON();
//			Beep_OFF();
			V_Geiding=V_Geiding;
		}
		else                           //加速
		{
//			Beep_ON();
//			Beep_OFF();
			V_Geiding=V_Geiding+3500;
		}
		
	}
	else                             //减速
	{
//		Beep_ON();
//		Beep_OFF();
		V_Geiding=V_Geiding-4000;
	}
	
	//分解速度

//	  L_actual=sqrt((ACTION_POSTION_X-x)*(ACTION_POSTION_X-x)+(ACTION_POSTION_Y-y)*(ACTION_POSTION_Y-y));
//	
//	

    if(L_actual<20)
		{
			L_theoryToStop=0;
			V_Geiding=0;
			vx=0;
			vy=0;
		} 
		else
		{
			vx=V_Geiding*(x-ACTION_POSTION_X)/L_actual;
			vy=V_Geiding*(y-ACTION_POSTION_Y)/L_actual;
		}
	
	  ang_err_sum+=ang_new;
	//角度闭环
	//角度闭环
		if(fabs(ang_new)<0.2)
		{v_w=0;}
    if(fabs(ang_new)>=0.2)
		{
			if(fabs(ang_new)>1.0)  {v_P=5000;}
			else {v_P=1000;}
      v_w=v_P*(ang_new)+(ang_new-ang_old)*v_i+0.4*ang_err_sum;
//			 v_w=v_P*(ang_new);
    }
		

		
		if(v_w>60000)
		{
			v_w=60000;
		}
		
		if(v_w<-60000)
		{
			v_w=-60000;
		}
	
		v3=-0.707*vx-0.707*vy+v_w;
	  v4= 0.707*vx-0.707*vy+v_w;
	  v1= 0.707*vx+0.707*vy+v_w;
	  v2=-0.707*vx+0.707*vy+v_w;
		
		
    if(v1>240000) {v1=240000;}
    if(v2>240000) {v2=240000;}
	  if(v3>240000) {v3=240000;}
	  if(v4>240000) {v4=240000;}
		if(v1<-240000) {v1=-240000;}
    if(v2<-240000) {v2=-240000;}
		if(v3<-240000) {v3=-240000;}
	  if(v4<-240000) {v4=-240000;}
		
		
		
		
    VelMov_elmo(3,v3);
    VelMov_elmo(1,v1);
 	  VelMov_elmo(4,v4);
		VelMov_elmo(2,v2);
		
    ang_old=ang_new;
		
//		USART_OUT(USART1, "\n%d  %d  %d   %d\n",(int)L_theoryToStop,(int)L_actual,(int)V_actual2,(int)V_Geiding);
		
	
}
uint8_t  Turnangle_v1(float ang)
{
	
	
  static	  double ang_old=0;

	static    double ang_new=0;
	static    double ang_err_sum=0;
	double  v_w;
	double  v_P=1500.0;     //p调节参数
	

	double  v_i=150.0;


	
		ang_new=Angle-ang;
	  ang_err_sum+=ang_new;
	//角度闭环
		if(fabs(ang_new)<0.2)
		{v_w=0;}
    if(fabs(ang_new)>=0.2)
		{
			if(fabs(ang_new)>1.0)  {v_P=8000;}
			else {v_P=5000;}
      v_w=v_P*(ang_new)+(ang_new-ang_old)*v_i+0.4*ang_err_sum;

    }
		
	
		if(v_w>60000)
		{
			v_w=60000;
		}	
		if(v_w<-60000)
		{
			v_w=-60000;
		}		
		VelMov_elmo(1,v_w);
		VelMov_elmo(2,v_w);
    VelMov_elmo(3,v_w);    
 	  VelMov_elmo(4,v_w);		
    ang_old=ang_new;
			
		return (uint8_t)ang_new;
}


uint8_t  Turnangle(int ratio,float ang)
{
	 int v;
   v=1000*(Angle-ang);

   if(fabs(Angle-ang)>1.0)
	 {
		 if(v>150000)
			{
				v=150000;
			}
			
     if(v<-150000)
			{
				v=-150000;
			}

			VelMov_elmo(1,v);
			VelMov_elmo(2,v);
			VelMov_elmo(3,v);
			VelMov_elmo(4,v);
			return 0;
	 }
	 else
	 {
			VelMov_elmo(1,0);
			VelMov_elmo(2,0);
			VelMov_elmo(3,0);
			VelMov_elmo(4,0);
			return 1;		 
	}
}





void WalkLine(int V_car,float angle_car,float Xstart,float Ystart,float distencePID_P)
{
	double vx,vy;
	float k,b;
	
	
  static	  double ang_old=0;
	static    double ang_new=0;
	static    double ang_err_sum=0;
	double v_w;
	double v_P=1500.0;     //p调节参数
	
	double v1,v2,v3,v4;
	double v_i=150.0;
	
	
	
	ang_new=Angle;
	if(fabs(cos((angle_car)*0.017453292))>0.707)
	{
		k=sin((angle_car)*0.017453292)/cos((angle_car)*0.017453292);
		b=Ystart-Xstart*k;
		
		vx=V_car*cos((angle_car)*0.017453292)+distencePID_P*(k*ACTION_POSTION_Y-k*k*ACTION_POSTION_X-k*b)/(k*k+1);
		vy=V_car*sin((angle_car)*0.017453292)+distencePID_P*(-ACTION_POSTION_Y+k*ACTION_POSTION_X+b)/(k*k+1);
	}
	else//斜率不存在时
	{
		k=cos((angle_car)*0.017453292)/sin((angle_car)*0.017453292);
		b=Xstart-Ystart*k;
		
		vx=V_car*cos((angle_car)*0.017453292)+distencePID_P*(k*ACTION_POSTION_Y-ACTION_POSTION_X+b)/(k*k+1);
		vy=V_car*sin((angle_car)*0.017453292)+distencePID_P*(-k*k*ACTION_POSTION_Y+k*ACTION_POSTION_X-k*b)/(k*k+1);
	}
	
	
	
	
	
	
	  ang_err_sum+=ang_new;
	//角度闭环
		if(fabs(ang_new)<0.2)
		{v_w=0;}
    if(fabs(ang_new)>=0.2)
		{
			if(fabs(ang_new)>1.0)  {v_P=8000;}
			else {v_P=5000;}
      v_w=v_P*(ang_new)+(ang_new-ang_old)*v_i+0.4*ang_err_sum;

    }
		

		
		if(v_w>60000)
		{
			v_w=60000;
		}
		
		if(v_w<-60000)
		{
			v_w=-60000;
		}
	
		v3=-0.707*vx-0.707*vy+v_w;
	  v4= 0.707*vx-0.707*vy+v_w;
	  v1= 0.707*vx+0.707*vy+v_w;
	  v2=-0.707*vx+0.707*vy+v_w;
		
		
    if(v1>240000) {v1=240000;}
    if(v2>240000) {v2=240000;}
	  if(v3>240000) {v3=240000;}
	  if(v4>240000) {v4=240000;}
		if(v1<-240000) {v1=-240000;}
    if(v2<-240000) {v2=-240000;}
		if(v3<-240000) {v3=-240000;}
	  if(v4<-240000) {v4=-240000;}
		
		
		
		
		VelMov_elmo(1,v1);
		VelMov_elmo(2,v2);
    VelMov_elmo(3,v3);
    
 	  VelMov_elmo(4,v4);
		
    ang_old=ang_new;
		
		
		
}

