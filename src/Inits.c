#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "tm_stm32f4_lis302dl_lis3dsh.h"
#include "stm32_tm1637.h"
#include "arm_math.h"
#include "Inits.h"
#include "StepCounter.h"


void InitStepCounter(){
	SystemInit();
	AccelerometrInit();
	GPIODiodesInit();
	TIM3Init();
	tm1637Init();
	tm1637DisplayInt(0);

	Work();
}


void AccelerometrInit(void){
	TM_LIS302DL_LIS3DSH_Init(TM_LIS3DSH_Sensitivity_2G, TM_LIS3DSH_Filter_800Hz);
}


void GPIODiodesInit(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef  str;
	str.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	str.GPIO_Mode = GPIO_Mode_OUT;
	str.GPIO_OType = GPIO_OType_PP;
	str.GPIO_Speed = GPIO_Speed_100MHz;
	str.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &str);
}


void TIM3Init(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 2624;
	TIM_TimeBaseStructure.TIM_Prescaler = 124;
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

}



