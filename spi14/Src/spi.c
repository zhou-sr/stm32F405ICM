/**
  ******************************************************************************
  * @file    spi.c
  * @brief   This file provides code for the configuration
  *          of the SPI instances.
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

/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

SPI_HandleTypeDef hspi1;

/* SPI1 init function */
void MX_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/******************************************************
��������ֵ��ȡ����
**********************************************************/
/* USER CODE BEGIN 1 */
void SPI_MultiRead(SPI_HandleTypeDef *hspi,
	                 GPIO_TypeDef* GPIOx,    //��ӦƬѡ
                   uint16_t GPIO_Pin_X,    //��ӦƬѡ
                   uint8_t addressStart,   //��ʼ��ַ
                   uint8_t* spiRecieveData,//������ֵ
                   uint32_t len)           //��ַ������ȡ����
{
  uint8_t spiTransform = 0;//���Ϳհ���������ַ
	uint8_t temp[6] = {0xff};//���������������������ռĴ�������ֵ
	addressStart = addressStart | 0x80;//����ַתΪ��״̬
	
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin_X, GPIO_PIN_RESET);//����Ƭѡ
	HAL_SPI_TransmitReceive(hspi, &addressStart, &spiTransform, 1, 10);//����ַ
	HAL_SPI_TransmitReceive(hspi, temp, spiRecieveData, len, 10);//������
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin_X, GPIO_PIN_SET);//����Ƭѡ������ȡ
}
/******************************************************
��������ֵд�뺯��
**********************************************************/
void SPI_MultiWrite(SPI_HandleTypeDef *hspi,
	                  GPIO_TypeDef* GPIOx,    //��ӦƬѡ
                    uint16_t GPIO_Pin_X,    //��ӦƬѡ
                    uint8_t addressStart,   //��ʼ��ַ
                    uint8_t* spiSendData,   //������ֵ
                    uint32_t len)           //��ַ����д�볤��
{
  uint8_t spiTransform = 0;//���Ϳհ���������ַ
	uint8_t temp[6] = {0xff};//������������ռĴ�����ԭ��ֵ
	addressStart = (addressStart) & (~(1<<7));//����ַתΪд״̬
	
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin_X, GPIO_PIN_RESET);//����Ƭѡ
	HAL_SPI_TransmitReceive(hspi, &addressStart, &spiTransform, 1, 10);//����ַ
	HAL_SPI_TransmitReceive(hspi, spiSendData, temp, len, 10);//д����
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin_X, GPIO_PIN_SET);//����Ƭѡ����д��
}




/******************************************************
��ȡ�����ǼĴ�����������ֵ����
���ش�����ֵ������ָ��
**********************************************************/
float *ICM_Value_Read(int clock,              //��ʱ��ѡ��
	                    int time,               //ȫ���������ʱ��
	                    SPI_HandleTypeDef *hspi,
	                    GPIO_TypeDef* GPIOx,    //��ӦƬѡ
                      uint16_t GPIO_Pin_X,    //��ӦƬѡ
                      uint8_t rxSheet[14],    //���ڴ洢���ܵ�����icm��δ��������
                      float dataSheetFloat[7])//���ڴ洢���ܵ�����icm���Ѵ�������
{
  switch(clock %time)
			{
				
				case 0:
					SPI_MultiRead(hspi, GPIOx, GPIO_Pin_X, ACCEL_XOUT_H, rxSheet, 14);//����������ȡ
				
				  //ƴ�ӵõ��������ݺ��չ�ʽ���д���//
					g_accelXoutReceive = (float)(int16_t)((rxSheet[0] << 8) | rxSheet[1]) / 32768 * 2 * 9.8035;//��ֵΪ+-2g������һ�˼���
				  dataSheetFloat[0] = g_accelXoutReceive;                                                    //���������ݴ�������
					g_accelYoutReceive = (float)(int16_t)((rxSheet[2] << 8) | rxSheet[3]) / 32768 * 2 * 9.8035;
				  dataSheetFloat[1] = g_accelYoutReceive;
					g_accelZoutReceive = (float)(int16_t)((rxSheet[4] << 8) | rxSheet[5]) / 32768 * 2 * 9.8035;
				  dataSheetFloat[2] = g_accelZoutReceive;
				  g_tempOutReceive = (float)(int16_t)((rxSheet[6] << 8) | rxSheet[7]) / 326.8 + 25;
				  dataSheetFloat[3] = g_tempOutReceive;
					g_gypoXoutReceive = (float)(int16_t)((rxSheet[8] << 8) | rxSheet[9]) / 32768 * 250;//��ֵΪ+-250dps������һ�˼���
				  dataSheetFloat[4] = g_gypoXoutReceive;                                             //���������ݴ�������
				  if(g_angleXoutOn == 1)
					{
						if(g_angleXout >= 360)
						{
						  g_angleXout = g_angleXout - 360;
						}
						if(g_angleXout < 0)
						{
						  g_angleXout = g_angleXout + 360;
						}
						
					  g_angleXout = g_angleXout + (((float)time * (dataSheetFloat[4] - g_gypoXoutAverage))/1000)/PI * 180;
					}
					if(g_angleXoutOn == 0)
					{
					  g_angleXout = 0;
					}
					g_gypoYoutReceive = (float)(int16_t)((rxSheet[10] << 8) | rxSheet[11]) / 32768 * 250;
				  dataSheetFloat[5] = g_gypoYoutReceive;
					if(g_angleYoutOn == 1)
					{
						if(g_angleYout >= 360)
						{
						  g_angleYout = g_angleYout - 360;
						}
						if(g_angleYout < 0)
						{
						  g_angleYout = g_angleYout + 360;
						}
					  g_angleYout = g_angleYout + (((float)time * (dataSheetFloat[5] - g_gypoYoutAverage))/1000)/PI * 180;
					}
					if(g_angleYoutOn == 0)
					{
					  g_angleYout = 0;
					}
					g_gypoZoutReceive = (float)(int16_t)((rxSheet[12] << 8) | rxSheet[13]) / 32768 * 250;
					dataSheetFloat[6] = g_gypoZoutReceive;
					if(g_angleZoutOn == 1)
					{
						if(g_angleZout >= 360)
						{
						  g_angleZout = g_angleZout - 360;
						}
						if(g_angleZout < 0)
						{
						  g_angleZout = g_angleZout + 360;
						}
					  g_angleZout = g_angleZout + (((float)time * (dataSheetFloat[6] - g_gypoZoutAverage))/1000 )/PI * 180;
					}
					if(g_angleZoutOn == 0)
					{
					  g_angleZout = 0;
					}
					break;
			}
			
		
    float *dataReturn = dataSheetFloat;
		
		return dataReturn;
}

//���͵�ַ������//
uint8_t commandAdress[17] = {0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x20, 0x21, 0x22, 0x23, 0x37, 0x38, 0x68, 0x69, 0x6a, 0x6b, 0x6c};
uint8_t commandSend[17] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
/******************************************************
�������ǼĴ�����д���ʼ����ֵ����
**********************************************************/	
void ICM_Command_Write(SPI_HandleTypeDef *hspi,
	                     GPIO_TypeDef* GPIOx,    //��ӦƬѡ
                       uint16_t GPIO_Pin_X)    //��ӦƬѡ
	                    
{
	for(int i = 0; i < 18; i++)
	{
		SPI_MultiWrite(&hspi1, GPIOA, GPIO_PIN_4, commandAdress[i], &commandSend[i], 1);
	}
}
//1ms

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
