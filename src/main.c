/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "tm_stm32f4_lis302dl_lis3dsh.h"
#include "SPI.h"

#include "arm_math.h"

//z biblioteki DSP

int32_t X;
int32_t Y;
int32_t Z;

double re[64];
const int N = 64;
uint8_t sample = 0;


int main(void)
{
	initAccelerometr();

	typedef struct {
		int32_t X;
		int32_t Y;
		int32_t Z;
	} TM_LIS302DL_LIS3DSH_t;

	TM_LIS302DL_LIS3DSH_t Axes_Data;


	for (;;) {

		// konieczne bedzie przerwanie obslugujace zliczanie wartosci akcelerometru
		TM_LIS302DL_LIS3DSH_ReadAxes(&Axes_Data);
		if (sample < N)
			re[sample++] = Axes_Data.Y;
		//else
			// ustawienie flagi FFT_Flag = 1;


	}
}
