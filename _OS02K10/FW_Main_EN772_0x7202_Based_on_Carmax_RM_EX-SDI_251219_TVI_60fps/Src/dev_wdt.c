/* **************************************************************************
 File Name	: 	dev_wdt.c
 Description:	EN772 - Watchdog timer device driver
 Designer	:	Jang, Young Kyu / Kim Sung-Hoon
 Date		:	14. 6. 18
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

void InitWdt(UINT sec)
{
	WDT_CNT_LMT = MCLK * sec;
}

void SystemReset(void)
{
	WDT_CNT_LMT = 500 * (MCLK/1000);	// 500ms
	WDT_CNT_EN = 1;
	WDT_CNT_RST = 1;
	while(1);
}

