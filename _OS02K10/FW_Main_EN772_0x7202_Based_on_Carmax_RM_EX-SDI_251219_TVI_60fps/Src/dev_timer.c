/* **************************************************************************
 File Name	: 	dev_timer.c
 Description:	EN772 - Timer device driver
 Designer	:	Jang, Young Kyu / Kim Sung-Hoon
 Date		:	14. 6. 18
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

volatile UINT gnIsrTimer0 = 0;
volatile UINT gnIsrTimer3 = 0;
volatile UINT gnIsrTimer4 = 0;
volatile UINT gnIsrTimer5 = 0;
volatile UINT gnIsrTimerX = 0;

// About GPS
#if(model_ModeLed==2)
BYTE gbLEDMode;
#endif

void InitTimer(void)
{
	// for IRIS
	TIM_CH0_DIV = 1;					// (MCLK/2) / (TIM_CH0_DIV+1) = counter/sec (�ʴ� counter ���� �ӵ�)
	PwmSetPrd(0x400);
	PwmSetDty(0/*0x400 - 1*/);
	PwmEna;
	TIM_CH0_PWM_EN = 1;
	TIM_CH0_IRQ_EN = 0;

#if (model_Lens == 1)
	// for TowMotor
	TIM_CH1_DIV = TIMER1_CLKDIV;		// (MCLK/2) / (TIM_CH0_DIV+1) = counter/sec
	TIM_CH1_LMT = TIMER1_LIMIT;
	TIM_CH1_TRIG = TIMER1_LIMIT - 1;

	TIM_CH1_EN = 1;
	TIM_CH1_PWM_EN = 0;
	TIM_CH1_IRQ_EN = 1;

#endif

	// for Timer
#if(0)
	TIM_CH3_DIV = TIMERx_CLKDIV;		// (MCLK/2) / (TIM_CH0_DIV+1) = counter/sec
	TIM_CH3_LMT = TIMERx_LIMIT;
	TIM_CH3_TRIG = TIMERx_LIMIT - 1;

	TIM_CH3_EN = 1;
	TIM_CH3_PWM_EN = 0;
	TIM_CH3_IRQ_EN = 1;
	
#else
	// 10ms
	TIM_CH2_DIV = 0xE;		
	TIM_CH2_LMT = 0xC15C;
	TIM_CH2_TRIG = 0xC15C - 1;

	TIM_CH2_EN = 1;
	TIM_CH2_PWM_EN = 0;
	TIM_CH2_IRQ_EN = 1;

	// 10ms
	TIM_CH3_DIV = 0xE;		
	TIM_CH3_LMT = 0xC15C;
	TIM_CH3_TRIG = 0xC15C - 1;

	TIM_CH3_EN = 1;
	TIM_CH3_PWM_EN = 0;
//	TIM_CH3_IRQ_EN = 1;
	TIM_CH3_IRQ_EN = 0;	

	// 10ms
	TIM_CH4_DIV = 0xE;		
	TIM_CH4_LMT = 0xC15C;
	TIM_CH4_TRIG = 0xC15C - 1;

	TIM_CH4_EN = 1;
	TIM_CH4_PWM_EN = 0;
//	TIM_CH4_IRQ_EN = 1;
	TIM_CH4_IRQ_EN = 0;	
	
#endif

}

void ISPM0 Tm0_Func(void)
{

}

void ISPM0 Tm1_Func(void)
{
#if (model_Lens==1)	// 180702 JJH
	if(gbMaf_TimerEn) MAF_PhaseControl();
#endif

}

void ISPM0 Tm2_Func(void)
{
#if(model_ModeLed==2) // Use LED (Blackbox)
	switch(MP(MpLedCtrl))
	{
		case LED_ON : // LED ON
			gnIsrTimer0 = 0;
			GpioSetHi(GPIO_MODE_LED);
			break;
			
		case LED_OFF : // LED OFF
			gnIsrTimer0 = 0;
			GpioSetLo(GPIO_MODE_LED);
			break;
			
		case LED_BLINKING : // LED BLINK (1Sec)
			gnIsrTimer0++;
			if(gnIsrTimer0 >= 100)
			{
				if(GpioGetPin(GPIO_MODE_LED))	GpioSetLo(GPIO_MODE_LED);
				else							GpioSetHi(GPIO_MODE_LED);				
				gnIsrTimer0 = 0;
			}
			break;

		default : break;
	}

#endif
}

void ISPM0 Tm3_Func(void)
{
	// for Send GPS Data using UART
	gnIsrTimer3++;
}

#define AE_SUM_TIMER_MS		50			//500ms (50x10ms)

void ISPM0 Tm4_Func(void)
{		
}

void ISPM0 Tm5_Func(void)
{
}

void ISPM0 IsrTimer(void)		// CAUTION!!! - Isr stack size = 0x400, Do not use a lot of variables.
{
#if 1
	UINT i;
	const BYTE bTIMER_IRQ = _rd8(TIMER_REG_BASE+3) & 0x3F;	// Default Byte Ordering is MSB(Most Significant Byte)

	for(i=0; i<TIMER_NUM; i++)
	{
		const BYTE bTimerBit = (0x1<<(TIMER_NUM-1-i));

		if( bTIMER_IRQ&bTimerBit ) {
			_rd8(TIMER_REG_BASE+2) |= bTimerBit;			// IRQ clear, Default Byte Ordering is MSB(Most Significant Byte)

			//if(i == 3)

			switch (i) {
				case 0 : Tm0_Func(); break;	// Timer0 Interrupt Function Call
				case 1 : Tm1_Func(); break;	// Timer1 Interrupt Function Call
				case 2 : Tm2_Func(); break;	// Timer2 Interrupt Function Call
				case 3 : Tm3_Func(); break;	// Timer3 Interrupt Function Call
				case 4 : Tm4_Func(); break;	// Timer3 Interrupt Function Call
				case 5 : Tm5_Func(); break;	// Timer3 Interrupt Function Call
			}

//		#if 0//model_VT_Test == 1	// Timer IRQ
//			if(i == 1) {
//				TIM_CH1_IRQ_EN = 0;
//				UART0_CLKDIV = UB9600;
//
//				BYTE nDat;
//				while(!UART0_RX_EMPTY) nDat = UART0_RX_DAT;
//				UART0_RX_IRQ_EN = 1;
//			}
//
//			if(i != 1)	// for gnIsrTimerX++;
//		#endif

			//if(i != 3 && gtUartQue.wTxLen < (UART_BUF_SIZE>>1)) TxStr("Timer IRQ ", i, 1);	// CAUTION!!! - If DI() & (gtUartQue.wTxLen >= UART_BUF_SIZE), Cause an infinite loop in UartTxByte()
			if(i != 3) gnIsrTimerX++;
		}
	}
#elif 0
		if(TIM_CH0_IRQ) { TIM_CH0_IRQ_CLR = 1; Tm0_Func(); }
		if(TIM_CH1_IRQ) { TIM_CH1_IRQ_CLR = 1; Tm1_Func(); }
		if(TIM_CH2_IRQ) { TIM_CH2_IRQ_CLR = 1; Tm2_Func(); }
		if(TIM_CH3_IRQ) { TIM_CH3_IRQ_CLR = 1; Tm3_Func(); }
		if(TIM_CH4_IRQ) { TIM_CH4_IRQ_CLR = 1; Tm4_Func(); }
		if(TIM_CH5_IRQ) { TIM_CH5_IRQ_CLR = 1; Tm5_Func(); }
#else
	if(TIM_CH0_IRQ) {
		TIM_CH0_IRQ_CLR = 1;

		gnIsrTimer0++;
	}
	else {
		//TIM_CH0_IRQ_CLR = 1;
		TIM_CH1_IRQ_CLR = 1;
		TIM_CH2_IRQ_CLR = 1;
		TIM_CH3_IRQ_CLR = 1;
		TIM_CH4_IRQ_CLR = 1;
		TIM_CH5_IRQ_CLR = 1;
		TxStr("Unknow Timer IRQ", 0, 0);
	}
#endif
}

