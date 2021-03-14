#include "calculation.h"

extern float g_accelXoutAverage;
extern float g_accelYoutAverage;
extern float g_accelZoutAverage;
extern float g_tempOutAverage;
extern float g_gypoXoutAverage;
extern float g_gypoYoutAverage;
extern float g_gypoZoutAverage;

extern float dataTable[500][7];

void ICM_Value_Anverage(void)
{
  
	uint8_t rxSheet_0[14];
  float dataSheetFloat_0[7];
	
	float accelXoutSum = 0;
	float accelYoutSum = 0;
	float accelZoutSum = 0;
	float tempOutSum = 0;
	float gypoXoutSum = 0; 
	float gypoYoutSum = 0;
	float gypoZoutSum = 0;
					
	for(int i = 0; i < 500; i++)
	{
		for(int a = 0; a < 7; a++)
		{
			ICM_Value_Read(g_cntTim4, 1, &hspi1, GPIOA, GPIO_PIN_4, rxSheet_0, dataSheetFloat_0);
			dataTable[i][a] = dataSheetFloat_0[a];
		}
	}
	
	for(int i = 0; i < 500; i++)
	{
		accelXoutSum = dataTable[i][0] + accelXoutSum;
		accelYoutSum = dataTable[i][1] + accelYoutSum;
		accelZoutSum = dataTable[i][2] + accelZoutSum;
		tempOutSum = dataTable[i][3] + tempOutSum;
		gypoXoutSum = dataTable[i][4] + gypoXoutSum;
		gypoYoutSum = dataTable[i][5] + gypoYoutSum;
		gypoZoutSum = dataTable[i][6] + gypoZoutSum;
	}
	
	g_accelXoutAverage = accelXoutSum / 500;
	g_accelYoutAverage = accelYoutSum / 500;
	g_accelZoutAverage = accelZoutSum / 500;
	g_tempOutAverage = tempOutSum / 500;
	g_gypoXoutAverage = gypoXoutSum / 500;
	g_gypoYoutAverage = gypoYoutSum / 500;
	g_gypoZoutAverage = gypoZoutSum / 500;
}



