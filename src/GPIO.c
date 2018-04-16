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

void initExtBtns(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef  str;
	str.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4;
	str.GPIO_Mode = GPIO_Mode_IN;
	str.GPIO_OType = GPIO_OType_PP;
	str.GPIO_Speed = GPIO_Speed_50MHz;
	str.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &str);
}

/**
 * Stanem wysokim cyfry
 * Stanem niskim segmenty
 */
void initLedSegment(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef strSegments;
	strSegments.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3
					| GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6
					| GPIO_Pin_7;
	strSegments.GPIO_Mode = GPIO_Mode_OUT;
	strSegments.GPIO_OType = GPIO_OType_PP;
	strSegments.GPIO_Speed = GPIO_Speed_100MHz;
	strSegments.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &strSegments);

	GPIO_InitTypeDef  strNumbers;
	strNumbers.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14| GPIO_Pin_15;
	strNumbers.GPIO_Mode = GPIO_Mode_OUT;
	strNumbers.GPIO_OType = GPIO_OType_PP;
	strNumbers.GPIO_Speed = GPIO_Speed_100MHz;
	strNumbers.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &strNumbers);

GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3 | GPIO_Pin_4
					| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);

GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
}

void setLedSegment(int number)
{
	if(number == 1)
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
	else if(number == 2)
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
	else if(number == 3)
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
	else if(number == 4)
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
}

void resetLedSegment(int number)
{
	if(number == 1)
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	else if(number == 2)
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	else if(number == 3)
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	else if(number == 4)
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
}

void setLedSegmentAndResetOthers(int number)
{
	setLedSegment(number);

	if(number == 1)
	{
		resetLedSegment(2);
		resetLedSegment(3);
		resetLedSegment(4);
	}
	else if(number == 2)
	{
		resetLedSegment(1);
		resetLedSegment(3);
		resetLedSegment(4);
	}
	else if(number == 3)
	{
		resetLedSegment(1);
		resetLedSegment(2);
		resetLedSegment(4);
	}
	else if(number == 4)
	{
		resetLedSegment(1);
		resetLedSegment(2);
		resetLedSegment(3);
	}
}

void resetNumberOnSegment(void)
{
	GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3 | GPIO_Pin_4
						| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
}

void setNumberOnSegments(int number)
{
	switch(number)
	{
	case 0:
		setNumber0();
		break;
	case 1:
		setNumber1();
		break;
	case 2:
		setNumber2();
		break;
	case 3:
		setNumber3();
		break;
	case 4:
		setNumber4();
		break;
	case 5:
		setNumber5();
		break;
	case 6:
		setNumber6();
		break;
	case 7:
		setNumber7();
		break;
	case 8:
		setNumber8();
		break;
	case 9:
		setNumber9();
		break;
	case 10:
		setNumber0();
		break;
	case 11:
		setNumberDot();
		break;
	}
}

void setNumber0(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
				| GPIO_Pin_4 | GPIO_Pin_5);
}

void setNumber1(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_1 | GPIO_Pin_2);
}

void setNumber2(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_4
				| GPIO_Pin_3);
}

void setNumber3(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_2
					| GPIO_Pin_3);
}
void setNumber4(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_1 | GPIO_Pin_2);
}
void setNumber5(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_2
				| GPIO_Pin_3);
}
void setNumber6(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_2
					| GPIO_Pin_4 | GPIO_Pin_3);
}
void setNumber7(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
}
void setNumber8(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
				| GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
}
void setNumber9(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
					| GPIO_Pin_5 | GPIO_Pin_6);
}
void setNumberDot(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_7);
}


//ja dopisa³am (nadaj¹ siê do wiruj¹cego œwiat³a)
void resetNumber9(void)
{
	GPIO_SetBits(GPIOE, GPIO_Pin_6);
}

void resetNumber0(void)
{
	GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
}

void resetNumber1(void)
{
	GPIO_SetBits(GPIOE, GPIO_Pin_2 | GPIO_Pin_5);
}

void resetNumber2(void)
{
	GPIO_SetBits(GPIOE, GPIO_Pin_4 | GPIO_Pin_5);
}

void resetNumber3(void)
{
	GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4);
}

void resetNumber4(void)
{
	GPIO_SetBits(GPIOE, GPIO_Pin_1 | GPIO_Pin_4);
}

void resetNumber5(void)
{
	GPIO_SetBits(GPIOE, GPIO_Pin_1);
}

void resetNumber6(void)
{
	GPIO_SetBits(GPIOE, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
}

void resetNumber8(void)
{
		GPIO_SetBits(GPIOE, GPIO_Pin_4);
}
