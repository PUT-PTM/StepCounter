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

//#define COMPLEX_NUMBER 128

double temp[128] = {0};
float32_t re[128] = {0};
float32_t im[256] = {0};
float32_t im_mag[128] = {0};
int FFT_Flag = 0;
const int N = 128;
uint8_t results = 0;
float32_t maxvalue;
uint32_t maxvalueindex;
arm_rfft_instance_f32 S;

TM_LIS302DL_LIS3DSH_t Axes_Data;
TM_LIS302DL_LIS3DSH_Device_t IMU_Type;



// przerwanie!
void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {

		TM_LIS302DL_LIS3DSH_ReadAxes(&Axes_Data);
		if (results < N){
			temp[results++] = Axes_Data.Y;
		}
		else
			FFT_Flag = 1;

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}




int main(void)
{
	initAccelerometr();
	initGPIODiodes();



	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 2624;
	TIM_TimeBaseStructure.TIM_Prescaler = 249; // 128 razy na sekunde
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up ;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM3, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);



	for (;;) {
		if (FFT_Flag) {
			TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);

			for(int i=0; i<N; i++){
				// rzutowanie double na float32
				re[i] = (float32_t) temp[i];
				im[i] = 0;
			}
			//----- FFT -----

			//tworzenie instancji struktury
			arm_rfft_instance_f32 S;
			arm_cfft_radix4_instance_f32 S_CFFT;
			arm_rfft_init_f32(&S, &S_CFFT, 128, 0, 1); //zainicjowanie jej

			//widmo fft
			// &S - wskaznik do struktury
			// re - bufor wejsciowy [128]
			// im - bufor wyjsciowy [256] (liczby zespolone)
			arm_rfft_f32(&S, re, im);
			GPIO_SetBits(GPIOD, GPIO_Pin_15);

			//wyliczanie modulu liczby zespolonej
			// im - bufor wejsciowy [256] (liczby zespolone)
			// im_mag - bufor wyjsciowy, zawierajacy moduly liczb [128]
			// 128 - ilosc liczb zespolonych
			arm_cmplx_mag_f32(im, im_mag, 128);

			//szukanie maksymalnej wartosci, zapisywanie jej indeksu
			// im_mag - bufor wejsciowy [128]
			// 128 - ilosc liczb zespolonych
			// maxvalue - najwieksza wartosc w buforze
			// maxvalueindex - indeks najwiekszej wartosci
			arm_max_f32(im_mag, 128, &maxvalue, &maxvalueindex);

			FFT_Flag = 0;
			TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
		}
	}
}
