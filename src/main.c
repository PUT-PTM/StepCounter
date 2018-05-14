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

float32_t re[64] = {0};
float32_t im[64] = {0};
float32_t im_mag[64] = {0};
int FFT_Flag = 0;
const int N = 64;
uint8_t results = 0;

arm_rfft_instance_f32 S;

TM_LIS302DL_LIS3DSH_t Axes_Data;
TM_LIS302DL_LIS3DSH_Device_t IMU_Type;



// przerwanie!
void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {

		TM_LIS302DL_LIS3DSH_ReadAxes(&Axes_Data);
		if (results < N)
			re[results++] = Axes_Data.Y;
		else
			FFT_Flag = 1;

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}




int main(void)
{
	initAccelerometr();

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 10000 - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 60 - 1;
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
			//fft
			/*
		    const arm_rfft_instance_f32 rfft_inst;
		    arm_rfft_init_f32();
		    arm_rfft_f32(&rfft_inst, re, im);
			//arm_rfft_f32(const arm_rfft_instance_f32 * S, re, im);
			 */

			FFT_Flag = 0;
			TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
		}
	}
}
