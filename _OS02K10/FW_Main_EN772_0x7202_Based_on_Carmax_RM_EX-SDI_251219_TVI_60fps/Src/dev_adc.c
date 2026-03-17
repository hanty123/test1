/* **************************************************************************
 File Name	: 	dev_adc.c
 Description	:	EN772 - ADC Setting
 Designer		:	Lee Gyu Hong	
 Date		:	18.07.04
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

UINT gnADC_KEY;
UINT gnADC_CVBS;
UINT gnADC_CDS;

void InitAdc(void)
{
#if((ISP_EN801)||(ISP_EN801M))
	POWER_OFF_ADC;
#else
	POWER_ON_ADC;

	ADC_INT_ENw(1);					
	ADC_MODEw(0);					
	ADC_CHANNEL0w(1);				
	ADC_CHANNEL1w(2);				
	ADC_CYCLEw(0x67);				
	
	ADC_CH_UPDATE_POINTw(0x10);		// 201231 LBG
	
#endif
}

