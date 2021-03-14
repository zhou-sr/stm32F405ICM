/**
  ******************************************************************************
  * @file    spi.h
  * @brief   This file contains all the function prototypes for
  *          the spi.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN Private defines */

#define PI 3.14159265358979846264338327950

//接收陀螺仪寄存器地址//
#define ACCEL_XOUT_H 0x3b
#define ACCEL_XOUT_L 0x3c
#define ACCEL_YOUT_H 0x3d
#define ACCEL_YOUT_L 0x3e
#define ACCEL_ZOUT_H 0x3f
#define ACCEL_ZOUT_L 0x40
#define TEMP_OUT_H   0x41
#define TEMP_OUT_L   0x42
#define GYRO_XOUT_H  0x43
#define GYRO_XOUT_L  0x44
#define GYRO_YOUT_H  0x45
#define GYRO_YOUT_L  0x46
#define GYRO_ZOUT_H  0x47
#define GYRO_ZOUT_L  0x48

//写入寄存器地址及内容//
#define SMPLRT_DIV        0x19  //0x00 读取频率为1khz
#define CONFIG            0x1a  //0x01 读取频率为1khz
#define GYRO_CONFIG       0x1b  //0x00 读取角速度范围为+-250dps
#define ACCEL_CONFIG      0x1c  //0x00 读取加速度范围为+-2g
#define ACCEL_CONFIG2     0x1d  //0x00
#define LP_MODE_CFG       0x1e  //0x00 不进入低功耗模式
#define ACCEL_WOM_X_THR   0x20  //0x00 不使用中断
#define ACCEL_WOM_Y_THR   0x21  //0x00 不使用中断
#define ACCEL_WOM_Z_THR   0x22  //0x00 不使用中断
#define FIFO_EN           0x23  //0x00 不使能FIFO
#define INT_PIN_CFG       0x37  //0x00 不使用中断
#define INT_ENABLE        0x38  //0x00 不使用中断
#define SIGNAL_PATH_RESET 0x68  //0x00
#define ACCEL_INTEL_CTRL  0x69  //0x02
#define USER_CTRL         0x6a  //0x00
#define PWR_MGMT_1        0x6b  //0x00
#define PWR_MGMT_2        0x6c  //0x00

extern float g_accelXoutReceive;//x轴加速度
extern float g_accelYoutReceive;//y轴加速度
extern float g_accelZoutReceive;//z轴加速度
extern float g_tempOutReceive;  //温度
extern float g_gypoXoutReceive; //x轴角速度
extern float g_gypoYoutReceive; //y轴角速度
extern float g_gypoZoutReceive; //z轴角速度

extern int g_angleXoutOn;//x轴角度计算开关 1开0关
extern float g_angleXout;//x轴角度
extern int g_angleYoutOn;//y轴角度计算开关 1开0关
extern float g_angleYout;//y轴角度
extern int g_angleZoutOn;//z轴角度计算开关 1开0关
extern float g_angleZout;//z轴角度

extern float g_accelXoutAverage;
extern float g_accelYoutAverage;
extern float g_accelZoutAverage;
extern float g_tempOutAverage;
extern float g_gypoXoutAverage;
extern float g_gypoYoutAverage;
extern float g_gypoZoutAverage;

extern float dataTable[500][7];
/* USER CODE END Private defines */

void MX_SPI1_Init(void);

/* USER CODE BEGIN Prototypes */
void SPI_MultiRead(SPI_HandleTypeDef *hspi,
	                 GPIO_TypeDef* GPIOx,
                   uint16_t GPIO_Pin_X,
                   uint8_t addressStart,
                   uint8_t* spiRecieveData,
                   uint32_t len);

void SPI_MultiWrite(SPI_HandleTypeDef *hspi,
	                  GPIO_TypeDef* GPIOx,
                    uint16_t GPIO_Pin_X,
                    uint8_t addressStart,
                    uint8_t* spiSendData,
                    uint32_t len);

float *ICM_Value_Read(int clock,               //定时器选择
	                    int time,                //全部采样间隔时间
	                    SPI_HandleTypeDef *hspi,
	                    GPIO_TypeDef* GPIOx,     //对应片选
                      uint16_t GPIO_Pin_X,     //对应片选
                      uint8_t rxSheet[14],     //用于存储接受到来自icm的未处理数据
                      float dataSheetFloat[7]);//用于存储接受到来自icm的已处理数据
	                    

void ICM_Command_Write(SPI_HandleTypeDef *hspi,
	                     GPIO_TypeDef* GPIOx,    //对应片选
                       uint16_t GPIO_Pin_X);   //对应片选
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
