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
#include "GPIO.h"

double temp=0;
int main(void)
{
	initGPIODiodes();
	initAccelerometr();

	typedef struct {
		int16_t X;
		int16_t Y;
		int16_t Z;
	} TM_LIS302DL_LIS3DSH_t;

	TM_LIS302DL_LIS3DSH_t Axes_Data;


	for (;;) {

		TM_LIS302DL_LIS3DSH_ReadAxes(&Axes_Data);
		temp = 2.3 / 127 * Axes_Data.Z * 10;
		if (temp<=-5) {
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
		} else {
			GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		}
		if (temp > -5 && temp <= 0) {
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
		} else {
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		}
		if (temp > 0 && temp < 5) {
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
		} else {
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		}
		if (temp >= 5) {
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
		} else {
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		}
	}
}
