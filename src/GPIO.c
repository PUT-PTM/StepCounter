#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "GPIO.h"


void initGPIODiodes(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef  str;
	str.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	str.GPIO_Mode = GPIO_Mode_OUT;
	str.GPIO_OType = GPIO_OType_PP;
	str.GPIO_Speed = GPIO_Speed_100MHz;
	str.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &str);
}

