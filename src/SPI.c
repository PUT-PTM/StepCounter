#include "SPI.h"
#include "tm_stm32f4_lis302dl_lis3dsh.h"

void initAccelerometr(void)
{
	TM_LIS302DL_LIS3DSH_Init(TM_LIS3DSH_Sensitivity_2G, TM_LIS3DSH_Filter_800Hz);
}


//TM_LIS302DL_LIS3DSH_t Axes_Data;
//const float divider = 16384.0;
//int x = 0;
//int y = 0;
//int z = 0;
//float rx = 0;
//float ry = 0;
//float rz = 0;
//
//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)
//	{
//		TM_LIS302DL_LIS3DSH_ReadAxes(&Axes_Data);
//
//		x = Axes_Data.X;
//		y = Axes_Data.Y;
//		z = Axes_Data.Z;
//
//		rx = (float)x/divider;
//		ry = (float)y/divider;
//		rz = (float)z/divider;
//
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	}
//}
