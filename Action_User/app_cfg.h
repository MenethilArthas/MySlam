/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               app_cfg.h
** Descriptions:            ucosii configuration
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-9
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__
#include  <os_cpu.h>					  
#include "flag.h"
/*
*********************************************************************************************************
*                                       MODULE ENABLE / DISABLE
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                              TASKS NAMES
*********************************************************************************************************
*/
extern  void  App_Task(void);

static  void  App_TaskStart(void); 
static void ConfigTask(void);
static void BeforePlayTask(void);
static void PlayTask(void);
static void WalkTask(void);
static void GoHome_Dealerr(void);
#if DEBUG	
static void DEBUGTask(void);
#endif

/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_TASK_START_PRIO                               10u
#define  Config_TASK_START_PRIO                            11u
#define  BeforePlay_TASK_PRIO                              12u
#define  Play_TASK_PRIO                                    13u
#define  Walk_TASK_PRIO                                    14u
#define  GoHome_Dealerr_TASK_PRIO                          15u
#if DEBUG	
#define  DEBUG_TASK_PRIO                                   16u
#endif


/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/
#define  APP_TASK_START_STK_SIZE                          256u
#define  Config_TASK_START_STK_SIZE                       256u
#define  BeforePlay_TASK_STK_SIZE                         256u
#define  Play_TASK_STK_SIZE                               256u
#define  Walk_TASK_STK_SIZE                               256u
#define  GoHome_Dealerr_TASK_STK_SIZE                     256u

#if DEBUG	
#define  DEBUG_TASK_STK_SIZE                              256u
#endif

/*
*********************************************************************************************************
*                                            TASK STACK
*                             
*********************************************************************************************************
*/
static  OS_STK  App_TaskStartStk[APP_TASK_START_STK_SIZE];
static  OS_STK  App_ConfigStk[Config_TASK_START_STK_SIZE];
static  OS_STK  BeforePlayTaskStk[BeforePlay_TASK_STK_SIZE];
static  OS_STK  PlayTaskStk[Play_TASK_STK_SIZE];
static  OS_STK  WalkTaskStk[Walk_TASK_STK_SIZE];
static  OS_STK  GoHome_DealerrTaskStk[GoHome_Dealerr_TASK_STK_SIZE];
#if DEBUG
static  OS_STK  DEBUGTaskStk[DEBUG_TASK_STK_SIZE];
#endif

/*
*********************************************************************************************************
*                                                  LIB
*********************************************************************************************************
*/



#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

