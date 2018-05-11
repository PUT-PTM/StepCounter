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

//z biblioteki DSP

int32_t X;
int32_t Y;
int32_t Z;

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

		TM_LIS302DL_LIS3DSH_ReadAxes(&Axes_Data);
		X = Axes_Data.X;
		Y = Axes_Data.Y;
		Z = Axes_Data.Z;


	}
}
