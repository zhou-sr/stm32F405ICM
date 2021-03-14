/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
int YouXiaoWei;
/* USER CODE END 0 */

UART_HandleTypeDef huart6;

/* USART6 init function */

void MX_USART6_UART_Init(void)
{

  huart6.Instance = USART6;
  huart6.Init.BaudRate = 9600;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspInit 0 */

  /* USER CODE END USART6_MspInit 0 */
    /* USART6 clock enable */
    __HAL_RCC_USART6_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**USART6 GPIO Configuration
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* USART6 interrupt Init */
    HAL_NVIC_SetPriority(USART6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART6_IRQn);
  /* USER CODE BEGIN USART6_MspInit 1 */

  /* USER CODE END USART6_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspDeInit 0 */

  /* USER CODE END USART6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART6_CLK_DISABLE();

    /**USART6 GPIO Configuration
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7);

    /* USART6 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART6_IRQn);
  /* USER CODE BEGIN USART6_MspDeInit 1 */

  /* USER CODE END USART6_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/******************************************************
��������ת�ַ�������
char *itoa(int value, char *string, int radix)
radix=10 ��ʾ��10����	��ʮ���ƣ�ת�����Ϊ0;  

����d=-379;
ִ��	itoa(d, buf, 10); ��

buf="-379"							   			  
**********************************************************/
char *itoa_10(int value, char *string)
{
	int     i, d;
	int     flag = 0;
	char    *ptr = string;

	/* This implementation only works for decimal numbers. */
	if (!value)
	{
		*ptr++ = 0x30;
		*ptr = 0;
		return string;
	}

	/* if this is a negative value insert the minus sign. */
	if (value < 0)
	{
		*ptr++ = '-';
		/* Make the value positive. */
		value *= -1;
	}

	for (i = 10000; i > 0; i /= 10)
	{
		d = value / i;
		if (d || flag)
		{
			*ptr++ = (char)(d + 0x30);
			value -= (d * i);
			flag = 1;
		}
}

/* Null terminate the string. */
*ptr = 0;

return string;
} 

/******************************************************
���봮�ڽ����жϻص�����						   			  
**********************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART6)
  {
    //�жϴ����ж���USART6��������ж���
		//HAL_UART_Receive_IT(&huart6, &Rx_dat, 1);
  }
}
/******************************************************
���봮�ڷ����жϻص�����						   			  
**********************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART6)
	{
	  //HAL_UART_Receive_IT(&huart6, &Rx_dat, 1);
	}
}
/******************************************************
����������ת�ַ���������ת�� ������С�������λ

����d=-3.79;
ִ�� Float_To_Char(d, buf); ��

buf="-3.7900
"
**********************************************************/
void Float_To_Char(float data,        //��Ҫת������
                  int msb ,          //Ԥ����Ҫ�ռ�
									char dateSend[msb])//�õ��������ַ���
{	
	char dataChar[5];    //�����ַ���
	char dataCharRest[4];//С���ַ���
	int zhengShuWei = 0; //������Чλ
	int xiaoShuWei = 0;  //С����Чλ
  int fuHao;           //0+ 1- 20  
  int flg = 0;
	
	//�ж���������//
	if(data < 0)
	{
	  fuHao = 1;
	}
	if(data > 0)
	{
	  fuHao = 0;
	}
	if(data == 0)//������
	{
	  fuHao = 2;
	}
	
	//����������С�����ִ���//
	if(fuHao == 0)
	{
	  itoa_10((int)data, dataChar);//תΪ�ַ���
	  float dateRest = data - (float)((int)data);//ȡС��
	  int dateRestInt = (int)(dateRest * 10000);//����С�������λ
	  itoa_10((int)dateRestInt, dataCharRest);//תΪ�ַ���
	}
	
	if(fuHao == 1)
	{
	  itoa_10(-(int)data, dataChar);//תΪ���ַ���
	  float dateRest = -data + (float)((int)data);//ȥ��С��
	  int dateRestInt = (int)(dateRest * 10000);//����С�������λ
	  itoa_10((int)dateRestInt, dataCharRest);//תΪ�ַ���
	}
	
	for(int i = 0;i < 5; i++)//����������Чλ
	{
	  if(dataChar[i] == 0)
		{
		  zhengShuWei = i;
			break;
		}
	}
	
	for(int i = 0;i < 5; i++)//����С����Чλ
	{
	  if(dataCharRest[i] == 0)
		{
		  xiaoShuWei = i;
			break;
		}
	}
	
	switch(fuHao)
	{
	  case 0:
			//�����ݽ�������//
			for(int i = 0; i < zhengShuWei; i++)//��������
		  {
			  dateSend[i] = dataChar[i];
			}
			
			dateSend[zhengShuWei] = '.';
			
			for(int i = 0; 4 - xiaoShuWei - i > 0; i++)//С�����㲿��
		  {
				dateSend[zhengShuWei + i + 1] = '0';			 
			}
			
			for(int i = xiaoShuWei; i > 0; i--)//С����Ч����
		  {
				dateSend[4 + zhengShuWei + (i - xiaoShuWei)] = dataCharRest[i - 1];
			}
			
			dateSend[4 + zhengShuWei + 1] = '\t';
		  break;
		
		case 1:
			//�����ݽ�������//
		  dateSend[0] = '-';	
		
		  for(int i = 0; i < zhengShuWei; i++)//��������
		  {
			  dateSend[i + 1] = dataChar[i];
			}
			
			dateSend[zhengShuWei + 1] = '.';
			
			for(int i = 0; 4 - xiaoShuWei - i > 0; i++)//С�����㲿��
		  {
				dateSend[2 + zhengShuWei + i] = '0';			 
			}
			
			for(int i = xiaoShuWei; i > 0; i--)//С����Ч����
		  {
				dateSend[4 + zhengShuWei + 1 + (i - xiaoShuWei)] = dataCharRest[i - 1];
			}
			dateSend[4 + zhengShuWei + 2] = '\t';
		case 2:
		  //������//
		  break;		
	}
	
	zhengShuWei = 0;
	xiaoShuWei = 0;
}

/******************************************************
����������ת�з��͵�����
����ʱ������λ�Ե�ǰ��ʱ��Ϊ׼
Ԫ����󳤶�Ϊ20
����ȫ������
**********************************************************/
void Transfer_Sending(UART_HandleTypeDef *huart,//���ʹ���
                     	int time,                 //���ͼ��ʱ��
											int clock,                //��ǰʹ��ʱ��
										  int msb,                  //���鳤��
											float dateSend[msb],      //��Ҫ��������
											char dateSendCharAll[150]) //��������
{
	char dateSendChar[20];
	int supWei = 0;
	int wei = 0;
	
	for(int r = 0; r < msb; r++)
	{	
		wei = 0;
		Float_To_Char(dateSend[r], 20 ,dateSendChar);
		
		for(int i = 0;i < 12; i++)//����������Чλ
		{
			if(dateSendChar[i] == 0)
			{
				wei = i;
				break;
			}
		}
		
		for(int i = 0; i < wei; i++)
		{
			dateSendCharAll[i + supWei] = dateSendChar[i];
		}
		
		supWei = supWei + wei;
	}
	
	dateSendCharAll[supWei] = '\r';
	dateSendCharAll[supWei + 1] = '\n';
	
	switch(clock %time)
		{
			case 0:
				
			  HAL_UART_Transmit_IT(huart, (uint8_t*)dateSendCharAll, supWei + 2);//���ͽ��			
				break;
		}
}											
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/













