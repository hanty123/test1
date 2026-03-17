/* **************************************************************************
 File Name	: 	app_dbg.c
 Description	:	Debugging & Testing functions
 Designer		:	Jang, Young Kyu / Kim Sung-Hoon
 Date		:	14. 6. 18
 Copyright ⓒ Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

#define		model_TestOSD			1		// 0 : normal operation

//*************************************************************************************************
// Debugging & Testing functions
//-------------------------------------------------------------------------------------------------
extern volatile UINT gnIsrGpio;
extern volatile UINT gnIsrTimer0;
extern volatile UINT gnIsrTimerX;


#define UART_STR(STR)		TxStr(STR, 0, 0)/*uart_str(MSG)*/
#define UART_VAL(STR,VAL)	TxStr(STR, VAL, 8)

UINT gnDispDbgY = DispDbgYmin;
char gbStr[ISP_FONT_MAX_PATH+1+1];

//*************************************************************************************************
// Debugging & Testing functions
//-------------------------------------------------------------------------------------------------
void DispDbgH(char* cStr, const int aiVal, const UINT anLen)
{
	const UINT nLen = DispStr(cStr, gnDispDbgY, DispDbgX, DispDbgStrLen);
	DispHex(gnDispDbgY++, DispDbgX+nLen, aiVal, anLen);
}

void DispDbgD(char* cStr, const int aiVal, const UINT anLen)
{
	const UINT nLen = DispStr(cStr, gnDispDbgY, DispDbgX, DispDbgStrLen);
	DispDec(gnDispDbgY++, DispDbgX+nLen, aiVal, anLen);
}

void DispDbgB(char* cStr, const int aiVal, const UINT anLen)
{
	const UINT nLen = DispStr(cStr, gnDispDbgY, DispDbgX, DispDbgStrLen);
	DispBin(gnDispDbgY++, DispDbgX+nLen, aiVal, anLen);
}

void DispDbgP(char* cStr, const int aiVal, const int aiValMax, const UINT anLen)
{
	const UINT nLen = DispStr(cStr, gnDispDbgY, DispDbgX, DispDbgStrLen);
	DispPer(gnDispDbgY++, DispDbgX+nLen, aiVal, aiValMax, anLen);
}


#if 0
void UART_TEST(void)
{
	char/*BYTE*/ temp[3];
	UART_STR("2. UART LOOPBACK TEST - ");
	while(1)
	{
		UART_STR("Type 'ABC'   ");
		Uart_Rx(&temp[0]);
		Uart_Tx(temp[0]);
		Uart_Rx(&temp[1]);
		Uart_Tx(temp[1]);
		Uart_Rx(&temp[2]);
		Uart_Tx(temp[2]);
		if(temp[0]=='A' && temp[1]=='B' &&temp[2]=='C')
		{
			UART_STR("... OK");
			return;
		}
		else UART_STR("... FAIL");
	}
	return;
}

void GPIO_TEST(void)
{
	volatile int i, j;
	GPIO_OE = 0xffff;
	GPIO_O = 0x0001;
	UART_STR("3. GPIO TEST");
	for(i=0;i<16;i++)
	{
		GPIO_O = GPIO_O<<1;
		for(j=0;j<10000;j++);
	}
	return;
}

void TIMER_TEST(void)
{
	timer_init();
	return;
}
#endif


#if STR_PELCO_DATA == 1
BYTE gbPDcnt = 0;
BYTE gbPDadr = 0;
WORD gwFld = 0;
WORD gwPDfld = 0;
UINT gnPDdat = 0;

void ISPMt DispPelcoData(void)
{
	gwFld++;

	#define DispPelcoX	(ISP_FONT_EAX-24-1)/*0*//*DispDbgX*/
	#define DispPelcoY	(model_1M?18:20)

	const UINT nDispPelcoY = DispPelcoY + (gbPDcnt%8);

	DispStr("Pelco:", nDispPelcoY, DispPelcoX, 6);
	DispDec(nDispPelcoY, DispPelcoX+6, gwPDfld, 4);
	DispHex(nDispPelcoY, DispPelcoX+6+5, ((gbPDadr&0xFF)<<16) | ((gnPDdat>>16)&0xFFFF), 6);

	//DispDatHex("gbPDcnt", 25, DispPelcoX, gbPDcnt);
	//DispDatHex("gbPDadr", 26, DispPelcoX, gbPDadr);
	//DispDatHex("gnPDdat", 27, DispPelcoX, gnPDdat);
	//DispDatHex("ID NO", 24, DispPelcoX, gbPDadr != MP(MpCamID));
}
#endif

void DispTime(UINT anSec)
{
	const UINT nHour = anSec / 3600;
	anSec -= nHour * 3600;
	const UINT nMin  = anSec / 60;
	anSec -= nMin * 60;

	int2str(gbStr  , nHour, 3);	gbStr[3] = ':';
	int2str(gbStr+4, nMin , 2);	gbStr[6] = ':';
	int2str(gbStr+7, anSec, 2);	gbStr[9] = ' ';
	gbStr[10] = 0;

	DispStr((const char*)gbStr, gnDispDbgY++, DispDbgX, 9);			// ISPx
	//uart_str(gbStr);
	//TxStr("TIME: ", anSec, 8);
	//TxStr(gbStr, gtUartQue.wTxLen, 8);
	//TxStr(gbStr, TIM_CH0_PWM_EN/*GPIO_MUX*/, 8);
}

void ISPM TxStrDec2(const char* apbStr0, UINT anVal0, UINT anValLen0, UINT anVal1, UINT anValLen1)
{
	char bStr[11];
	const UINT nValLen0 = MIN(10,anValLen0);
	const UINT nValLen1 = MIN(10,anValLen1);
	const BYTE bLen = ((apbStr0) ? strlen(apbStr0) : 0) + nValLen0 + 1 + nValLen1 + 2;

	UartTxByte(PC_STX);
	UartTxByte(PC_CMD_STR);
 	UartTxByte(bLen);

	if(apbStr0) UartTxStr(apbStr0);

	if(nValLen0) {
		int2str(bStr, anVal0, nValLen0);
		UartTxStr(bStr);
	}

	UartTxByte('-');

	if(nValLen1) {
		int2str(bStr, anVal1, nValLen1);
		UartTxStr(bStr);
	}

	UartTxByte('\r');
	UartTxByte('\n');

	UartTxByte(PC_ETX);
}

void TxStrWaitTime(const UINT anUs)
{
	#define WANT_WAIT_TIMEx2	(MCLK/(1000000/(anUs<<1)))//(MCLK/(1000/2))

	//TxStrDecNoIRQ("WaitTimeUnit ", gnWaitTimeUnit,10);
	TxStrDecNoIRQ("WaitTimeOffset ", gnWaitTimeOffset,10);

	//TxStrNoIRQ("WaitUs 1ms", ((MCLK/1000) - gnWaitTimeOffset) / gnWaitTimeUnit ,10);
	//TxStrNoIRQ("WaitUs 1ms", ((WANT_WAIT_TIMEx2 - (gnWaitTimeOffset<<1)) / gnWaitTimeUnit + 1)>>1,10);
#if 0
	Uart_Tx(PC_STX);
	Uart_Tx(PC_CMD_STR);
 	Uart_Tx(8+4+4+5);
	int2str(gbStr, anUs, 8);
	uart_str(gbStr);		// 8
	uart_str("㎲: ");		// 4
	int2str(gbStr, ((WANT_WAIT_TIMEx2 - (gnWaitTimeOffset<<1)) / gnWaitTimeUnit + 1)>>1, 4);
	uart_str(gbStr);		// 4
	uart_str(" WT\r\n");	// 5
	Uart_Tx(PC_ETX);
#else
	UNUSED_ARG(anUs);
#endif
}

void ISPMt TestWaitTime(const UINT anUs)
{
	FUNC_TIME_OUT_ID(_DI, 1, "WaitUs", DispDbgD, WaitUs(anUs); )	// use DI()
}

void TestSerialFlash(void)
{
	//UINT i;
	//for(i=0x70000; i<=0x7ffff; i += 0x1000)
	//{
	//	sfls_erase_sect(i);
	//	TxStr("SF Sect Erase",  i, 8);
	//}

	//SfWrEn;
	//for(i=0x70000; i<=0x7ffff; i++)
	//{
	//	sfw8(i, /*0x7F*/0x88);
	//}
	//SfWrDis;

	//UINT j = 0;
	//for(i=0x70000; i<=0x7ffff; i++)
	//{
	//	const BYTE bFlsData = sfr8(i);
	//	if(bFlsData != 0x7F/*0x88*/) {
	//		//uint2strh(gbStr, FLS_BASE | i, 8);
	//		//gbStr[8] = ' ';
	//		//gbStr[9] = 0;
	//		//TxStr(gbStr, bFlsData, 2);
	//		j++;
	//	}
	//}
	//TxStr("hhhh",  j, 8);

#if 0
	//SFLS_BP_SET(0,0,0,0);
	sfls_erase_sect(0x70000);
	//sfls_erase_sect(0x7f000);


	SfWrEn;
	sfw8(0x70000, 0x74);
	//sfw8(0x7ffff, 0x88);
	SfWrDis;
	//SFLS_BP_SET(1,0,1,1);

	sfls_erase_sect(0x70000);
	TxStr("SFLS_DATA ", /*sfr32(0x7fffc)*/(sfr8(0x70000)<<16) | (sfr8(0x7ffff)<<0), 8);
#endif

#if 0
	sfls_erase_sect(0x70000);

	SfWrEn;
	sfw8(0x70000, 0x74);
	SfWrDis;
	//sfls_erase_sect(0x70000);
	TxStr("SFLS_DATA0", /*sfr32(0x7fffc)*/(sfr8(0x70000)<<16) | (sfr8(0x7ffff)<<0), 8);

	SfWrEn;
	sfw8(0x70000, 0x74);
	SfWrDis;
	//sfls_erase_sect(0x70000);
	TxStr("SFLS_DATA1", /*sfr32(0x7fffc)*/(sfr8(0x70000)<<16) | (sfr8(0x7ffff)<<0), 8);
#endif

#if 0
	SfWrEn;
	sfls_erase_sect(0x6E000);
	BYTE bTW[4] = { 0x34, 0x56, 0x78, 0x92 };
	sfls_page_program(0x6E000, bTW, 4);
	SfWrDis;

	TxStr("PP Test: ", sfr32(0x6E000), 8);
#endif



	SfWrEn;
	const BYTE bResetCnt = sfr8(FLASH_SECT_TEST_STT*FLASH_SECT_SIZE);
	sfls_erase_sect(FLASH_SECT_TEST_STT*FLASH_SECT_SIZE);
	sfw8(FLASH_SECT_TEST_STT*FLASH_SECT_SIZE, bResetCnt+1);
	SfWrDis;

	TxStrDec("SF  Reset Cnt: ", sfr8(FLASH_SECT_TEST_STT*FLASH_SECT_SIZE), 4);


	//TxStrDec("datalen     : ", sfr32(0x70000), 10);
	//TxStrDec("addr_fsize  : ", sfr32(0x70004), 10);
	//TxStrDec("START_SECTOR: ", sfr32(0x70008), 10);
	//TxStrDec("SECTOR_NUM  : ", sfr32(0x7000c), 10);


#if 0
	SfWrEn;
	sfw8(0x70000, 0x74);
	SfWrDis;
	sfls_erase_sect(0x70000);
	TxStr("SFLS_DATA1", /*sfr32(0x7fffc)*/(sfr8(0x70000)<<16) | (sfr8(0x7ffff)<<0), 8);
#endif
}

void ISPMt TestIRQ(void)
{
	const UINT nTimer1Sec = TIMERtoSEC(gnIsrTimer0);

#if 0
  #if model_I2C_ch1 == 1
	DispDbgD("IsrI2c   :", gnIsrI2c, 8);
  #endif
	//DispDbgD("IsrGpio  :", gnIsrGpio, 8);
	DispDbgD("IsrTick  :", gnIsrTick, 8);	// ISPx
	DispDbgD("IsrTimer0:", gnIsrTimer0, 8);
	DispDbgD("Timer1Sec:", nTimer1Sec, 8);
#else
	//DispDbgD("IsrISP0  :", gnIsrISP0, 8);	// ISPx
	//DispDbgD("IsrISP1  :", gnIsrISP1, 8);	// ISPx
	//DispDbgD("IsrISP2  :", gnIsrISP2, 8);	// ISPx
	//DispDbgD("IsrISP3  :", gnIsrISP8, 8);	// ISPx
	//DispDbgD("IsrISP4  :", gnIsrISP10, 8);	// ISPx

	#if LOW_UART_DBG == 0
//	DispDbgD("IsrGpio  :", gnIsrGpio, 8);

	//TIM_CH3_EN = 0;
	//TIM_CH3_EN = 1;
	//const UINT nTIM_CH3_CNT = TIM_CH3_CNT;
//	DispDbgD("Timer X  :", /*TIM_CH1_TRIG*//*nTIM_CH3_CNT*/gnIsrTimerX, 8);
	#endif
#endif
	//static BYTE bDiffOn = 0;
	//static UINT nDiffSec = 0;
	//DispDbgD("nDiffSec  :",  nDiffSec, 8);

//	extern UINT gnActCntMax;
//	DispStr("Act_Max :", gnDispDbgY, DispDbgX, 10);	DispDec(gnDispDbgY++, DispDbgX+10, gnActCntMax, 10);


#if model_TestOSD == 1
	if( EWV(gnIsrTickOn, (gnIsrTick%FPS_DEF) == 0) )
	{
		EWV(gnIsrTickOn = 0; ,)

		const UINT nTick1Sec = EWV(gnIsrTick, gnIsrTick/FPS_DEF );

		if(gbMnDebugFnc==MN_DBG_STATUS){
			DispStr("(VLOCKI)", gnDispDbgY, DispDbgX+10, 10);	DispTime(gnIsrISP0/FPS_VDI);
			DispStr("(VLOCKW)", gnDispDbgY, DispDbgX+10, 10);	DispTime(gnIsrISP1/FPS_VDI);
			DispStr("(VLOCKO)", gnDispDbgY, DispDbgX+10, 10);	DispTime(gnIsrISP2/FPS_VDO);
			DispStr("(TIMER)" , gnDispDbgY, DispDbgX+10, 10);	DispTime(nTimer1Sec);
			DispStr("(TICK)"  , gnDispDbgY, DispDbgX+10, 10);	DispTime(nTick1Sec);

			DispStr("FPS_VDI :", gnDispDbgY, DispDbgX, 10);	DispDec(gnDispDbgY++, DispDbgX+10, FPS_VDI, 3);
			DispStr("FPS_VDO :", gnDispDbgY, DispDbgX, 10);	DispDec(gnDispDbgY++, DispDbgX+10, FPS_VDO, 3);
		}
		//TxStr1("Time", nTick1Sec, 8);

		//TxStrDec2(gbStr, 987, 3, 345, 3);

		/*if( bDiffOn == 0 && ABSDIFF(nTimer1Sec, nTick1Sec) >= 2 )
		{
			bDiffOn = 1;
			nDiffSec = nTick1Sec;
		}*/
	}
	else gnDispDbgY += 7;	// 위의 gnDispDbgY 증가 개수와 같아야 함!!!
#else
	UNUSED_ARG(nTimer1Sec);
#endif

}

void ISPMt DispIsrStatus(void)
{
	extern BYTE gnIsrStatus[7];
	extern BYTE gnIsrStatusPos;
	if(gnIsrStatusPos)
	{
		UINT i;
		for(i=0; i<gnIsrStatusPos; i++) {
			DispDec(gnDispDbgY, DispDbgX+(i*3), gnIsrStatus[i], 2);
			gnIsrStatus[i] = 0;
		}
		gnIsrStatusPos = 0;

		for(; i<numberof(gnIsrStatus); i++) {
			SETFONTID(gnDispDbgY, DispDbgX+(i*3)  , '0');
			SETFONTID(gnDispDbgY, DispDbgX+(i*3)+1, '0');
		}
	}
	gnDispDbgY++;
}

void TestAppSavePar(void)
{
	if(gnIsrISP2 == 60) {
		TxStrDec("gnIsrISP2", gnIsrISP2, 10);
		gbUsrParSaveChk = 1;
	}

	if(gnIsrISP2 == 65) {
		TxStrDec("gnIsrISP2", gnIsrISP2, 10);
		gbMnParSaveChk = 1;
	}

	if(gnIsrISP2 == 70) {
		TxStrDec("gnIsrISP2", gnIsrISP2, 10);
		gbUsrDataSaveChk = 1;
	}
}

#if 0//model_FPU == 1	// float32 Test
void hfloat_test(void)
{
    //bool func_arg = TRUE;
    //int func_idx = 0;
    //int rnd_prec = 0;
    //int rnd_mode = -1;

	// test print float
	int i=0/*, j=0*//*, k=0*/;
	for(i=0; i<15; i++) {
	    float a = ((float)i*5)+0.1f;
	    float b = ((float)i*5)+0.1234567890123456789f;
	    float32 fa = TOFLOAT32(a);												// $CMT-ygkim-151117: only casting but the same value
	    float32 fb = TOFLOAT32(b);												// $CMT-ygkim-151117: DO NOT CARE ABOUT THE WARNING MSG.

	    char bf[32];
    	//for(j=RND_TONEAR; j<=RND_DNWARD; j++) {
	    	//set_fp_round_mode(j<<1);
		    float c = a*b;
			float32 fc = _fmul(fa, fb);

			#define FLOAT_STR_WIDTH		10

			ftoan(fc, bf, FLOAT_STR_WIDTH, '0', 5);
			DispStr(bf, i, DispDbgX, FLOAT_STR_WIDTH);

			ftoan(TOFLOAT32(c), bf, FLOAT_STR_WIDTH, '0', 5);
			DispStr(bf, i, FLOAT_STR_WIDTH+1+DispDbgX, FLOAT_STR_WIDTH);

			//DispDec(i, 10+1+DispDbgX, c*100000, 10);

		    //puthex32f(fa); puts(" * "); puthex32f(fb); puts(" = "); puthex32f(fc); puts("\r\n");
		    //printf("%f : 0x%08x * %f : 0x%08x = %f : 0x%08x \r\n",fa, fa, fb, fb, TOFLOAT32(c), fc);
		    /*for(k=0; k<10; k++) {
		    	sprintf(format, "%%d.%df * %%d.%df = %%d.%df\r\n", 20,k, 20,k, 20,k);
				printf(format, fa, fb, fc);
			}*/


		//}
	}
}
#endif

#if 0//model_FPU == 1	// float32 Test
void hfloat_test(void)
{
    //bool func_arg = TRUE;
    //int func_idx = 0;
    //int rnd_prec = 0;
    //int rnd_mode = -1;

	// test print float
	int i=0/*, j=0*//*, k=0*/;
	for(i=0; i<10; i++) {
	    float a = ((float)i*5)+0.1f;
	    float b = ((float)i*5)+0.1234567890123456789f;
	    float32 fa = TOFLOAT32(a);												// $CMT-ygkim-151117: only casting but the same value
	    float32 fb = TOFLOAT32(b);												// $CMT-ygkim-151117: DO NOT CARE ABOUT THE WARNING MSG.

	    char bf[32];
    	//for(j=RND_TONEAR; j<=RND_DNWARD; j++) {
	    	//set_fp_round_mode(j<<1);
		    float c = a*b;
			float32 fc = _fmul(fa, fb);

			#define FLOAT_STR_WIDTH		10

			ftoan(fc, bf, FLOAT_STR_WIDTH, '0', 5);
			DispStr(bf, i, DispDbgX, FLOAT_STR_WIDTH);

			ftoan(TOFLOAT32(c), bf, FLOAT_STR_WIDTH, '0', 5);
			DispStr(bf, i, FLOAT_STR_WIDTH+1+DispDbgX, FLOAT_STR_WIDTH);

			//DispDec(i, 10+1+DispDbgX, c*100000, 10);

		    //puthex32f(fa); puts(" * "); puthex32f(fb); puts(" = "); puthex32f(fc); puts("\r\n");
		    //printf("%f : 0x%08x * %f : 0x%08x = %f : 0x%08x \r\n",fa, fa, fb, fb, TOFLOAT32(c), fc);
		    /*for(k=0; k<10; k++) {
		    	sprintf(format, "%%d.%df * %%d.%df = %%d.%df\r\n", 20,k, 20,k, 20,k);
				printf(format, fa, fb, fc);
			}*/


		//}
	}
}
#endif

