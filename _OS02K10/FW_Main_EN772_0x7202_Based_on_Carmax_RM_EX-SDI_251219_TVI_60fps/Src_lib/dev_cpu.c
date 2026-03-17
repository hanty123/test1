/* **************************************************************************
 File Name	: 	dev_cpu.c
 Description:	OR - CPU
 Designer	:	Kim, Sunghoon
 Date		:	15. 5. 9
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "spr_defs.h"
#include "../Src/dev.h"


//*************************************************************************************************
// Or1200
//-------------------------------------------------------------------------------------------------
// SPR R/W
void ISPM0 mtspr(UINT anSpr, UINT anVal)
{
	asm volatile ("l.mtspr\t\t%0,%1,0": : "r" (anSpr), "r" (anVal));
}

UINT ISPM0 mfspr(UINT anSpr)
{
	UINT anVal;

	asm volatile ("l.mfspr\t\t%0,%1,0" : "=r" (anVal) : "r" (anSpr));
	return anVal;
}

//*************************************************************************************************
// Unused exception
//-------------------------------------------------------------------------------------------------
#define ExceptionMsg	TxStrNoIRQ
//	#define ExceptionMsg(...)

void XsrBusErr(void)
{
	ExceptionMsg("bus error exception occured 0 : ", 0, 0);
	while(1);
}

void XsrAlign(void)
{
	ExceptionMsg("align error exception occured 0 : ", 0, 0);
	ExceptionMsg("SPR_EPCR_BASE 0 is : ", mfspr(SPR_EPCR_BASE), 0);
	ExceptionMsg("SPR_ESR_BASE 0 is : ", mfspr(SPR_ESR_BASE), 0);
	while(1);
}

void XsrIllInsn(void)
{
	ExceptionMsg("invalid instruction exception occured 0 : ", 0, 0);
	ExceptionMsg("SPR_EPCR_BASE 0 is : ", mfspr(SPR_EPCR_BASE), 0);
	ExceptionMsg("SPR_ESR_BASE 0 is : ", mfspr(SPR_ESR_BASE), 0);
	while(1);
}

void XsrFloatPoint(void)
{
	ExceptionMsg("range exception occured 0 : ", 0, 0);
	while(1);
}

void XsrSyscall(void)
{
	ExceptionMsg("system call exception occured 0 : ", 0, 0);
	while(1);
}

void XsrBreak(void)
{
	ExceptionMsg("break exception occured 0 : ", 0, 0);
	while(1);
}

void XsrTrap(void)
{
	ExceptionMsg("trap exception occured 0 : ", 0, 0);
	while(1);
}

void XsrDpFault(void)
{
	ExceptionMsg("data page fault exception occured 0 : ", 0, 0);
	while(1);
}

void XsrIpFault(void)
{
	ExceptionMsg("instruction page fault exception occured 0 : ", 0, 0);
	while(1);
}

void XsrDtlbMiss(void)
{
	ExceptionMsg("data TLB miss exception occured 0 : ", 0, 0);
	while(1);
}

void XsrItlbMiss(void)
{
	ExceptionMsg("instruction TLB miss exception occured 0 : ", 0, 0);
	while(1);
}

//-------------------------------------------------------------------------------------------------
// Disable or Enable interrupt
int IrqDisable(UINT anVec)
{
	if(anVec >= MAX_INT_HANDLERS)	return -1;

	mtspr(SPR_PICMR, mfspr(SPR_PICMR) & ~(0x00000001L << anVec));

	return 0;
}

int IrqEnable(UINT anVec)
{
	if(anVec >= MAX_INT_HANDLERS)	return -1;

	mtspr(SPR_PICMR, mfspr(SPR_PICMR) | (0x00000001L << anVec));

	return 0;
}

void InitEnaIrq(void)
{
	//TxStr("Intterup Setting 1", 0, 0);
	//TxStr("SPR : ", mfspr(SPR_SR), 8);

	mtspr(SPR_SR, mfspr(SPR_SR) | SPR_SR_IEE);

	//mtspr(SPR_SR,0x8005);
	//TxStr("SPR : ", mfspr(SPR_SR), 8);
}

//----------------------------------------------------------------------------------------

void TxStrMemAddrInfo(void)
{
	TxStr("reset_s ",_reset_s,8);

#if model_Ispm == 1
	TxStr("rom_ispm_text_s ",_rom_ispm_text_s,8);
	TxStr("ispm_text_s ",_ispm_text_s,8);
	TxStr("ispm_text_e ",_ispm_text_e,8);
#endif

#if 1
	TxStr("rom_data_s ",_rom_data_s,8);
//	TxStr("rom_data_e ",_rom_data_e,8);
	TxStr("data_s ",_data_s,8);
	TxStr("data_e ",_data_e,8);
	TxStr("bss_s ",_bss_s,8);
	TxStr("bss_e ",_bss_e,8);
	TxStr("stack ",_stack,8);
#endif

#if model_Ispm == 1
	TxStr("ROM  VAL: ", _rd32(_rom_ispm_text_s + 0xa0),8);
	TxStr("ISPM VAL: ", _rd32(_ispm_text_s + 0xa0),8);

	//extern int RxPP(BYTE bIn);
	//TxStr("RxPP: ", (UINT)((void*)RxPP),8);
#endif
}


void TxStrCacheSize(void)
{
	extern UINT mfspr0(UINT anSpr);

	const unsigned long iccfgr = mfspr0(SPR_ICCFGR);
	const unsigned long icache_ways = 1 << (iccfgr & SPR_ICCFGR_NCW);
	const unsigned long icache_set_size = 1 << ((iccfgr & SPR_ICCFGR_NCS) >> 3);
	const unsigned long icache_block_size = (iccfgr & SPR_ICCFGR_CBS) ? 32 : 16;

	const unsigned long dccfgr = mfspr0(SPR_DCCFGR);
	const unsigned long dcache_ways = 1 << (dccfgr & SPR_DCCFGR_NCW);
	const unsigned long dcache_set_size = 1 << ((dccfgr & SPR_DCCFGR_NCS) >> 3);
	const unsigned long dcache_block_size = (dccfgr & SPR_DCCFGR_CBS) ? 32 : 16;

	TxStrDec("icache_ways ",icache_ways,8);
	TxStrDec("icache_set_size ",icache_set_size,8);
	TxStrDec("icache_block_size ",icache_block_size,8);
	TxStrDec("icache_total ",icache_set_size * icache_ways * icache_block_size,8);

	TxStrDec("dcache_ways ",dcache_ways,8);
	TxStrDec("dcache_set_size ",dcache_set_size,8);
	TxStrDec("dcache_block_size ",dcache_block_size,8);
	TxStrDec("dcache_total ",dcache_set_size * dcache_ways * dcache_block_size,8);
}

//----------------------------------------------------------------------------------------
#if 1//model_FPU == 1	// float32 to String(Dec or Hex)

char gNumcode[] = "0123456789ABCDEF";

char* ISPM strrev(char* str)
{
	char *s = str, *d = str + strlen(str)-1;
	while(d>s) {
		char ch=*d; *d--=*s; *s++=ch;
	}
	return str;
}

int ISPM uitoan(uint value, char* str, int base, int width, char fill_val)
{
	char* wstr = str;
	int i;

	// check base
	if(base<2||base>16) { *str = '\0'; return 0; }

	// reversed conversion
	do {
		*wstr++=gNumcode[value%base];
	} while(value/=base);

	for(i=wstr-str; i<width; i++)	*wstr++ = fill_val;
	*wstr='\0';

	// reverse string
	strrev(str);
	return (wstr-str);
}

int ISPM ftoan(float32 f, char* str, int width, char fill_val, int prec)		// $CMT-ygkim-151118: if the value is not correct, print and check with '%q'
{
	const float32 f10 = 0x41200000;
	char* wstr = str;

	// signed to unsigned, and add leading a sign '-'
	if(f&0x80000000) {
		f &= ~0x80000000;
		*wstr++ = '-';
		width--;
	}

	// fixed part conversion
    int fixpart = _ftoi(f);
	int fixlen = width-1-prec;	// 1 for '.'
	fixlen = uitoan(fixpart, wstr, 10, fixlen, fill_val);		// max 10 digits @ 32bits
	wstr += fixlen;
	*wstr++ = '.';

	// fraction part conversion
	do {
		//f = (f-float(fixpart))*10.0f;
		f = _fsub(f, _itof(fixpart));
		f = _fmul(f, f10);
		fixpart = _ftoi(f);

		/*if(fixpart < 0 && wstr > str) {
			*wstr = ((*(wstr-1) - '0') * 10) + fixpart + '0';
			*(wstr-1) = '0';
			wstr++;
		}
		else*/
		*wstr++ =/* (fixpart < 0) ? '!' :*/ '0' + fixpart;

		prec--;
	} while(prec>0 && f);

	// trailing 0
	if(prec>0) while(prec--) *wstr++ = '0';
	*wstr = '\0';

	return (wstr-str);	// fix + '.' + frac
}

int ISPM ftox(float32 f, char* str)
{
	char* wstr = str;
	int sgn = f&0x80000000;
	int exp = (f>>23)&0xFF;
	int frac = f&0x7FFFFF;
	int frac_msb = frac&0x800000;

    *wstr++ = sgn ? '-' : '+';
    int len = uitoan(exp, wstr, 16, 2, '0');
    wstr += len;
	*wstr++ = '.';

    len = uitoan(frac, wstr, 16, 6, '0');
    wstr += len;
	*wstr = '\0';

	// special numbers
    if(exp==0 && frac) 	{
    		*wstr++ = '('; *wstr++ = 'D'; *wstr++ = 'N'; *wstr++ = ')';
    }
    if(exp==0xff) {
    	if(!frac) {
    		*wstr++ = '('; *wstr++ = 'I'; *wstr++ = 'N'; *wstr++ = 'F'; *wstr++ = ')';
		} else if(frac_msb) {
    		*wstr++ = '('; *wstr++ = 'q'; *wstr++ = 'N'; *wstr++ = 'a'; *wstr++ = 'N'; *wstr++ = ')';
    	} else {
    		*wstr++ = '('; *wstr++ = 's'; *wstr++ = 'N'; *wstr++ = 'a'; *wstr++ = 'N'; *wstr++ = ')';
    	}
    }

	return (wstr-str);	// sign + exp + '.' + frac
}

#endif

//----------------------------------------------------------------------------------------

UINT gnMCLK = 0;

UINT ISPM0 GetWaitUsTick(const UINT anUs)
{
	// When an interrupt occurs, then the time increases.
	TICK_STA(1);
	WaitUs(anUs);
	TICK_END(1);
	return nTick_1;
}

UINT CorrWaitTime(const UINT anUs)
{
	UINT nTick_1 = GetWaitUsTick(anUs);

	const UINT nNs = anUs * 1000;
	const UINT nTick_ns = (nTick_1*4000) / (gnMCLK/250000);

	if(nTick_ns < nNs && gnWaitTimeOffset) {
		gnWaitTimeOffset--;
		return 1;
	}
	else {
		return 0;
	}
}

void SetWaitTimeOffset(const UINT anMCLK, const UINT anCntPerSec)
{
	gnMCLK = anMCLK;

	mtspr(SPR_TTMR,	SPR_TTMR_RT /*| SPR_TTMR_IE*/);		// Restart mode, Interrupt enable
    mtspr(SPR_TTMR,	mfspr(SPR_TTMR) | (SPR_TTMR_TP&((gnMCLK/anCntPerSec)-1)) );	// Set period
    //mtspr(SPR_SR  , mfspr(SPR_SR) | SPR_SR_TEE );

	#define WAIT_TIME_TEST_US	10	// CAUTION!!! - If LOW MCLK & NO ISPM & NO I-CACHE, The value must be larger.

	UINT nTick_1 = GetWaitUsTick(WAIT_TIME_TEST_US);

	const UINT nTargerClk = ((gnMCLK/10000) * WAIT_TIME_TEST_US) / 100;
	gnWaitTimeOffset = nTick_1 - nTargerClk;

	//#define OffsetCorr 14	// Used TestWaitTime()
	//if(gnWaitTimeOffset >= OffsetCorr) gnWaitTimeOffset -= OffsetCorr;
	while( CorrWaitTime(WAIT_TIME_TEST_US) );
}

void InitTickTimer(const UINT anCntPerSec)
{
#if 1
	// Restart mode, Interrupt enable, Set period
	mtspr(SPR_TTMR,	SPR_TTMR_RT | SPR_TTMR_IE | (SPR_TTMR_TP&((gnMCLK/anCntPerSec)-1)) );	// Set period
	mtspr(SPR_SR  , mfspr(SPR_SR) | SPR_SR_TEE );
#else
	mtspr(SPR_TTMR,	SPR_TTMR_RT | SPR_TTMR_IE);		// Restart mode, Interrupt enable
    mtspr(SPR_TTMR,	mfspr(SPR_TTMR) | (SPR_TTMR_TP&((MCLK/anCntPerSec)-1)) );	// Set period
    mtspr(SPR_SR  , mfspr(SPR_SR) | SPR_SR_TEE );
	//TxStrNoIRQ("444", 0, 0);
#endif
}

//----------------------------------------------------------------------------------------
#define SPR_SR_BUF	10
UINT gnSPR_SR[SPR_SR_BUF];
UINT gnSPR_SRi = 0;

UINT gnActCnt = 0;
UINT gnActCntMax = 0;


UINT ISPM0 GetSt(UINT *apNum)
{
	gnActCnt++;
	if(apNum) *apNum = gnActCnt;

	gnSPR_SRi++;
	if(gnSPR_SRi == SPR_SR_BUF) gnSPR_SRi = 0;

	gnSPR_SR[gnSPR_SRi] = mfspr(SPR_SR);

	return gnSPR_SRi;
}

void ISPM0 SetSt(const UINT anSPR_SRi, UINT *apNum)
{
	if(apNum) {
		if(*apNum > gnActCnt)	*apNum = (0xFFFFFFFF - (*apNum)) + gnActCnt + 1;	// A->B & A>B = (0x100+B-A) = (0xFF-A)+B+1
		else					*apNum = gnActCnt - (*apNum);						// A->B & A<B = B - A

		if(gnActCntMax < *apNum) gnActCntMax = *apNum;
	}

	mtspr(SPR_SR, gnSPR_SR[anSPR_SRi]);
}

void ISPM0 SetStDisIrq(UINT anSPR_SRi)
{
	mtspr(SPR_SR, gnSPR_SR[anSPR_SRi] & ~(SPR_SR_IEE | SPR_SR_TEE));
}

void ISPM0 SetStEnaIrq(UINT anSPR_SRi)
{
	mtspr(SPR_SR, gnSPR_SR[anSPR_SRi] | SPR_SR_IEE);
}

/*void ISPM0 ClrIrqTT(void)
{
	mtspr(SPR_TTMR,	mfspr(SPR_TTMR) & (~SPR_TTMR_IP)); 		// Interrupt clear
}*/

UINT ISPM0 GetTT(void)
{
	return mfspr(SPR_TTCR);
}

UINT ISPM0 GetTTmax(void)
{
	return mfspr(SPR_TTMR)&0x0fffffff;
}


//*************************************************************************************************
// Xsr
//-------------------------------------------------------------------------------------------------
void ISPM0 XsrTick(void)
{
	//const UINT nStXsrTick = mfspr(SPR_SR);
	//mtspr(SPR_SR, nStXsrTick & ~(SPR_SR_IEE | SPR_SR_TEE));

	extern void ISPM0 IsrTick(void);
	IsrTick();

	mtspr(SPR_TTMR,	mfspr(SPR_TTMR) & (~SPR_TTMR_IP));		// 160809 ksh

	//mtspr(SPR_SR, nStXsrTick);
}

//----------------------------------------------------------------------------------------
//typedef struct _tIhnd{						// Handler entry
//	void 	(*handler)(void);
//	//void	*arg;
//} tIhnd;

extern tIhnd tIntHandlers[MAX_INT_HANDLERS];

void ISPM0 XsrInt(void)
{
	UINT picsr;
	UINT i;
	UINT xi=0;
	UINT vi=0;
	UINT vo=0;

	//DI();		// Int
	//const UINT nStXsrInt = mfspr(SPR_SR);
	//mtspr(SPR_SR, nStXsrInt & ~(SPR_SR_IEE | SPR_SR_TEE));


//	#define SECRET_CODE_TIME	0
extern void LibBrkCond(void);

#if 1
	while((picsr = mfspr(SPR_PICSR))) {
		for(i=0; i</*gbIntNum*/MAX_INT_HANDLERS; i++) {
			if((picsr & (0x00000001L << /*gbIntVectors[i]*/i)) && (tIntHandlers[i].handler != 0)) {

				if(i == IRQ_ISP)
				{
					if(EXRISC_IRQr&(0x1<<ISP_IRQ_USERI0)) xi = 1;
//					if(EXRISC_IRQr&(0x1<<ISP_IRQ_VLOCKI)) vi = 1;
					if(EXRISC_IRQr&(0x1<<ISP_IRQ_VLOCKL)) vi = 1;
					if(EXRISC_IRQr&(0x1<<ISP_IRQ_VLOCKO)) vo = 1;

					(*tIntHandlers[i].handler)(/*tIntHandlers[i].arg*/);
					
					if (vi)	LibBrkCond();	// 161220 LH
						
//					if(xi) {
//					  #if SECRET_CODE_TIME
//						TICK_STA(1);
//					  #endif
//
//					  #if SECRET_CODE_TIME
//						TICK_END(1);
//
//						#ifndef MCLK
//							#define MCLK	gnMCLK
//							DispDec(17, DispDbgX, tick2ns(1), 10);
//						#endif
//					  #endif
//					}


				}
				else {
					(*tIntHandlers[i].handler)(/*tIntHandlers[i].arg*/);
				}

				mtspr(SPR_PICSR, mfspr(SPR_PICSR) & ~(0x00000001L << /*gbIntVectors[i]*/i));		// IRQ clear masking
			}
		}

		/*
		if(picsr&(0x00000001L<<IRQ_ISP))	{ IsrISP();		mtspr(SPR_PICSR, mfspr(SPR_PICSR) & ~(0x00000001L<<IRQ_ISP)); }
		if(picsr&(0x00000001L<<IRQ_UART))	{ IsrUart();	mtspr(SPR_PICSR, mfspr(SPR_PICSR) & ~(0x00000001L<<IRQ_UART)); }
		if(picsr&(0x00000001L<<IRQ_TIMER))	{ IsrTimer();	mtspr(SPR_PICSR, mfspr(SPR_PICSR) & ~(0x00000001L<<IRQ_TIMER)); }
		if(picsr&(0x00000001L<<IRQ_GPIO))	{ IsrGpio();	mtspr(SPR_PICSR, mfspr(SPR_PICSR) & ~(0x00000001L<<IRQ_GPIO)); }
		if(picsr&(0x00000001L<<IRQ_I2C))	{ IsrI2c();		mtspr(SPR_PICSR, mfspr(SPR_PICSR) & ~(0x00000001L<<IRQ_I2C)); }
		*/
	}
#else
	IsrUart(&i);

	//extern UINT gnIsrUartRxF;
	//gnIsrUartRxF++;
	//do { i = U0RB; } while( U0LS_DRDY );

	mtspr(SPR_PICSR, 0);
#endif

    //EI();
	//mtspr(SPR_SR, nStXsrInt);

    //TxStr("DONE", 0, 0);
}

