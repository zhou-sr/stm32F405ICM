#include "main.h"
#include "spi.h"
#include "gpio.h"

#ifndef __CALCULATION_H__
#define __CALCULATION_H__

extern int g_cntTim4;//TIM4计时次数

extern float g_accelXoutReceive;//x轴加速度
extern float g_accelYoutReceive;//y轴加速度
extern float g_accelZoutReceive;//z轴加速度
extern float g_tempOutReceive;  //温度
extern float g_gypoXoutReceive; //x轴角加速度
extern float g_gypoYoutReceive; //y轴角加速度
extern float g_gypoZoutReceive; //z轴角速度


void ICM_Value_Anverage(void);

#endif



