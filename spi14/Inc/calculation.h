#include "main.h"
#include "spi.h"
#include "gpio.h"

#ifndef __CALCULATION_H__
#define __CALCULATION_H__

extern int g_cntTim4;//TIM4��ʱ����

extern float g_accelXoutReceive;//x����ٶ�
extern float g_accelYoutReceive;//y����ٶ�
extern float g_accelZoutReceive;//z����ٶ�
extern float g_tempOutReceive;  //�¶�
extern float g_gypoXoutReceive; //x��Ǽ��ٶ�
extern float g_gypoYoutReceive; //y��Ǽ��ٶ�
extern float g_gypoZoutReceive; //z����ٶ�


void ICM_Value_Anverage(void);

#endif



