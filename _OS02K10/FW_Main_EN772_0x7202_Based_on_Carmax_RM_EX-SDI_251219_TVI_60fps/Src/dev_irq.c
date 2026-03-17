/* **************************************************************************
 File Name	: 	dev_irq.c
 Description:	Interrupt device driver
 Designer	:	Kim, Sunghoon
 Date		:	14. 6. 18
 Copyright ⓒ Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

//-------------------------------------------------------------------------------------------------
// Initialize routine
int IntInit(void)
{
	int i;

	//gbIntNum = 0;

	for(i = 0; i < MAX_INT_HANDLERS; i++) {
		tIntHandlers[i].handler = 0;
		//tIntHandlers[i].arg = 0;
		//gbIntVectors[i] = 0;
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------
// Add interrupt handler
int IntAdd(UINT anVec, void (* handler)(void), void *arg)
{
	UNUSED_ARG(arg);

	if(anVec >= MAX_INT_HANDLERS)	return -1;

	//gbIntVectors[gbIntNum] = anVec;

	tIntHandlers[/*gbIntNum*/anVec].handler = handler;
	//tIntHandlers[anVec].arg = arg;

	//gbIntNum++;

	return 0;
}


//*************************************************************************************************
// Isr
//-------------------------------------------------------------------------------------------------
void InitIrq(void)
{
	//TxStrNoIRQ("IRQ Init...", 0, 0);

	//----------------------------------------------------------------------------------------
	// ISP interrupt
//	extern void InitIspIrq(void);
//	InitIspIrq();

	VIRQI_ENw(1);		// VLOCKI, Sensor 입력 Sync 기준
	VIRQW_ENw(1);		// VLOCKI, Sensor 입력 Sync 기준 (WDR 기준 Sync)
	VIRQO_ENw(1);		// VLOCKO, ISP 출력 Sync 기준(Low Shutter 제외하고는 VLOKCI와 VLOCKO가 동일 함.)

	MANUAL_INT_ENw(1);	// Manual VLOCK, Based on register
	MANUAL_LWw((MCLK/MANUAL_SYNC_FPS)-1);

	VIRQF_EN0w(0); VIRQF_EN1w(0);		// User Interrupt I 0, 1 (VLOCKI 기준)
	VIRQP_EN0w(0); VIRQP_EN1w(0);		// User Interrupt O 0, 1 (VLOCKO 기준)
	
	//----------------------------------------------------------------------------------------
	// Interrupt handler initialize
	IntInit();

	//----------------------------------------------------------------------------------------
	// Isr registration
	IntAdd(IRQ_ISP  , (void*)IsrISP,   0);			// ISPx
	IntAdd(IRQ_UART	, (void*)IsrUart,  0);

	IntAdd(IRQ_TIMER, (void*)IsrTimer, 0);
	IntAdd(IRQ_GPIO	 ,(void*)IsrGpio,  0);

#if (model_I2C_ch1 == 1)
	IntAdd(IRQ_I2C	 ,(void*)IsrI2c,  0);
#endif

	//----------------------------------------------------------------------------------------
	// Irq enable
	IrqEnable(IRQ_ISP  );			// ISPx
	IrqEnable(IRQ_UART );

	IrqEnable(IRQ_TIMER);
	IrqEnable(IRQ_GPIO	);

#if (model_I2C_ch1 == 1)
	IrqEnable(IRQ_I2C	);
#endif

	//----------------------------------------------------------------------------------------
	// Global interrupt enable
	InitEnaIrq();
}


//----------------------------------------------------------------------------------------
volatile UINT gnIsrTickOn = 0;
volatile UINT gnIsrTick = 0;

void ISPM0 IsrTick(void)
{
	gnIsrTickOn++;
	gnIsrTick++;
}

#if 0
void ISPM0 WaitTt(UINT anUs)
{
	while(!gnIsrTickOn) WaitUs(anUs);
	gnIsrTickOn = 0;
}
#endif

