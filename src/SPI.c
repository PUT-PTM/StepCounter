#include "SPI.h"
#include "tm_stm32f4_lis302dl_lis3dsh.h"

void initAccelerometr(void)
{
	TM_LIS302DL_LIS3DSH_Init(TM_LIS3DSH_Sensitivity_2G, TM_LIS3DSH_Filter_800Hz);
}
