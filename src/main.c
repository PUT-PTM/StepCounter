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
#include "TIM.h"
#include "GPIO.h"

#include "arm_math.h"

const int N = 128;
int FFT_Flag = 0;

q31_t sample[128] = {0};
q31_t samplefft[128] = {0};
q31_t comp[256] = {0};
q31_t comp_mag[128] = {0};

uint8_t results = 0;
q31_t maxvalue;
uint32_t maxvalueindex;
arm_rfft_instance_f32 S;

TM_LIS302DL_LIS3DSH_t Axes_Data;
TM_LIS302DL_LIS3DSH_Device_t IMU_Type;


// przerwanie!
void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {

		TM_LIS302DL_LIS3DSH_ReadAxes(&Axes_Data);
		if (results < N){

			sample[results++] = Axes_Data.Y;
		}
		else
			FFT_Flag = 1;

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}


int main(void)
{
	SystemInit();
	initAccelerometr();
	initGPIODiodes();
	InitTimer();

	for (;;) {
		if (FFT_Flag) {
			TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);

			//----- FFT -----

			//tworzenie instancji struktury
			arm_rfft_instance_q31 S;
			arm_cfft_radix4_instance_q31 S_CFFT;
			arm_rfft_init_q31(&S, &S_CFFT, N, 0, 1); //zainicjowanie jej

			//widmo fft
			// &S - wskaznik do struktury
			// sample - bufor wejsciowy [128]
			// comp - bufor wyjsciowy [256] (liczby zespolone)
			arm_rfft_q31(&S, sample, comp);

			for(int i=0;i<N;i++){
				//sprawdzamy jak wyglada tablica z probkami po wykonaniu fft
				samplefft[i] = sample[i];
			}

			//wyliczanie modulu liczby zespolonej
			// comp - bufor wejsciowy [256] (liczby zespolone)
			// comp_mag - bufor wyjsciowy, zawierajacy moduly liczb [128]
			// 128 - ilosc liczb zespolonych
			arm_cmplx_mag_q31(comp, comp_mag, N);

			//szukanie maksymalnej wartosci, zapisywanie jej indeksu
			// comp_mag - bufor wejsciowy [128]
			// 128 - ilosc liczb zespolonych
			// maxvalue - najwieksza wartosc w buforze
			// maxvalueindex - indeks najwiekszej wartosci
			arm_max_q31(comp_mag, 128, &maxvalue, &maxvalueindex);

			Clear();

			GPIO_SetBits(GPIOD, GPIO_Pin_15); //testowe zapalenie diody
			FFT_Flag = 0;
			TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
		}
	}
}


void Clear(){
	//czysci wszystkie tablice (wykonywana co sekunde)
	for(int i=0;i<N;i++){
		sample[i] = 0;
		comp[i] = 0;
		comp_mag[i] = 0;
		}
	results = 0;
}
