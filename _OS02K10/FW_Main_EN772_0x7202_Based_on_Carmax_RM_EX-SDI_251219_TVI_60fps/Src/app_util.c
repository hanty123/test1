/* **************************************************************************
 File Name	: 	app_util.c
 Description:	Utillity
 Designer	:	Kim, Sunghoon
 Date		:	14. 6. 18
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

//*************************************************************************************************
// Assembler call functions
//-------------------------------------------------------------------------------------------------
// .data section initilize
void _DataSectInit(void)
{
	UINT i;
#if 1
	UINT *pDst = (UINT*)_data_s;
	UINT *pSrc = (UINT*)_rom_data_s;
	const UINT nNum = (_data_e - _data_s)>>2;
	for(i=0; i<nNum; i++)
	{
		*(pDst++) = *(pSrc++);
	}

	BYTE *pbDst = (BYTE*)pDst;
	BYTE *pbSrc = (BYTE*)pSrc;
	const UINT nMod = (_data_e - _data_s) - (nNum<<2);
	for(i=0; i<nMod; i++)
	{
		*(pbDst++) = *(pbSrc++);
	}
#else
	BYTE *pDst = (BYTE*)_data_s;
	BYTE *pSrc = (BYTE*)_rom_data_s;
	const UINT nNum = _data_e - _data_s;
	for(i=0; i<nNum; i++)
	{
		*(pDst++) = *(pSrc++);
	}
#endif
}

//-------------------------------------------------------------------------------------------------
// .bss section initilize
void _BssSectInit(void)
{
	UINT i;
#if 1
	UINT *pDst = (UINT*)_bss_s;
	const UINT nNum = (_bss_e - _bss_s)>>2;
	for(i=0; i<nNum; i++)
	{
		*(pDst++) = 0;
	}

	BYTE *pbDst = (BYTE*)pDst;
	const UINT nMod = (_bss_e - _bss_s) - (nNum<<2);
	for(i=0; i<nMod; i++)
	{
		*(pbDst++) = 0;
	}
#else
	BYTE *pDst = (BYTE*)_bss_s;
	const UINT nNum = _bss_e - _bss_s;
	for(i=0; i<nNum; i++)
	{
		*(pDst++) = 0;
	}
#endif
}

void _ResetSectInit(void)
{
//	*((volatile unsigned int *)(0xf8000204)) = (UINT)(0x0c000000);			// Start DAC power down		//181004 LGH

	UINT i;

#if model_Ispm == 1
	UINT *pDst = (UINT*)(_ispm_text_s&0xFF000000)/*SRAM_BASE*/;
#else
	UINT *pDst = (UINT*)(_data_s&0xFF000000)/*SRAM_BASE*/;		// ISPM�� DSPM�� ���� �ִ� ��� ����
#endif
	UINT *pSrc = (UINT*)_reset_s/*FLS_BASE*/;
	/*const*/UINT nNum = 0xF00>>2;

	for(i=0; i<nNum; i++)
	{
		*(pDst++) = *(pSrc++);
	}

#if model_Ispm == 1
	pDst = (UINT*)_ispm_text_s;
	pSrc = (UINT*)_rom_ispm_text_s;
	nNum = (_ispm_text_e - _ispm_text_s)>>2;

	for(i=0; i<nNum; i++)
	{
		*(pDst++) = *(pSrc++);
	}
#endif
}

#if 0
void _IspmSectInit(void)
{
	UINT i;

	UINT *pDst = (UINT*)_ispm_text_s;
	UINT *pSrc = (UINT*)_rom_ispm_text_s;
	const UINT nNum = (_ispm_text_e - _ispm_text_s)>>2;

	for(i=0; i<nNum; i++)
	{
		*(pDst++) = *(pSrc++);
	}
}
#endif

//*************************************************************************************************
// HW Floating calculation 
//-------------------------------------------------------------------------------------------------
// 170609 KSH
hfloat ISPM0 f_h(float f)
{
    return TOFLOAT32(f);
}

float ISPM0 h_f(hfloat h)
{
    return (((tConv*)(&(h)))->f);
}

hfloat ISPM0 hALU(hfloat h1, hfloat h2, const char* f)
{
    return  (*f == '*') ? _fmul(h1,h2) :
            (*f == '/') ? _fdiv(h1,h2) :
            (*f == '+') ? _fadd(h1,h2) :
            (*f == '-') ? _fsub(h1,h2) : 0;
}

bool ISPM0 hCLU(hfloat h1, hfloat h2, const char* f)
{
    return  (*(f+1) == '=') ?   (*f == '=') ? _feq(h1,h2) :
                                (*f == '>') ? _fge(h1,h2) :
                                (*f == '<') ? _fle(h1,h2) :
                                (*f == '!') ? _fne(h1,h2) : 0 :
                                (*f == '>') ? _fgt(h1,h2) :
                                (*f == '<') ? _flt(h1,h2) : 0 ;
}


//*************************************************************************************************
// String
//-------------------------------------------------------------------------------------------------
// String
UINT ISPM strlen(const char *apbStr)
{	// String length
	UINT	nLen = 0;
    while(*apbStr++) nLen++;
	return nLen;
}

void ISPM uchar2strb(char* apbStr, BYTE anVal, UINT anLen)
{
	UINT	i;

	apbStr[anLen] = '\0';	// CAUTION!
	apbStr += anLen-1;
	for(i=0; i<anLen; i++){
		*apbStr-- = (anVal&0x1) ? '1' : '0' ;
		anVal >>= 1;
    }
}

void ISPM uint2strh(char* apbStr, UINT anVal, UINT anLen)
{	// Value -> String Hex
	UINT	i;

	apbStr[anLen] = '\0';	// CAUTION!
	apbStr += anLen-1;
	for(i=0; i<anLen; i++){
		const BYTE bBuf = anVal & 0xf;
		*apbStr-- = (bBuf >= 0xA) ? bBuf - 0xA + 'A' : bBuf + '0' ;
		anVal >>= 4;
    }
}

void ISPM int2str(char* apbStr, int aiVal, UINT anLen)
{	// Value -> String Dec
	UINT	i;
	UINT	nMod;

	apbStr[anLen] = '\0';	// CAUTION!

	int neg;

	if(aiVal < 0) {
		neg = 1;
		aiVal = -aiVal;
	}
	else {
		neg = 0;
	}

	for(i=0; i<anLen-neg; i++){
		if(aiVal >= 10) {
			nMod = aiVal / 10;
			apbStr[anLen-i-1] = '0' + (aiVal - (nMod * 10));
			aiVal = nMod;
		}
		else {
			break;
		}
	}

	if(i<anLen && aiVal > 0) {
		apbStr[anLen-i-1] = '0' + aiVal;
		i++;
	}

	if(i<anLen && neg) {
		apbStr[anLen-i-1] = '-';
		i++;
	}

	for(; i<anLen; i++) {
		apbStr[anLen-i-1] = '0';
	}
}

void ISPM per2str(char* apbStr, const int aiVal, const int aiValMax, UINT anLen)
{
	int2str(apbStr, (aiVal * 10000) / aiValMax, anLen-2);
	apbStr[anLen] = '\0';	// CAUTION!
	apbStr[anLen-1] = '%';
	apbStr[anLen-2] = apbStr[anLen-3];
	apbStr[anLen-3] = apbStr[anLen-4];
	apbStr[anLen-4] = '.';
}

void ISPM flt2str(char* apbStr, const float afVal, const int aiValNum, UINT anLen)
{	// 160104 KSH
	// aiValNum : floating no
	// anLen    : total character no
	int i, valmax=1;
	for(i=0; i<aiValNum; i++) valmax *= 10;

	int2str(apbStr, (int)(afVal * valmax), anLen-1);

	apbStr[anLen] = '\0';	// CAUTION!
	for(i=1; i<=aiValNum; i++) {
		apbStr[anLen-i] = apbStr[anLen-i-1];
	}
	apbStr[anLen-i] = '.';
}


void CheckByteOrdering(void)
{
	const UINT nTestVal = 0x98765432;
	char *pbTest = (char*)(&nTestVal);
	if(*(pbTest+1) == 0x76) TxStr("Byte Ordering : MSB ", 0,0);
	else if(*(pbTest+1) == 0x54) TxStr("Byte Ordering : LSB ", 0,0);
	else TxStr("Byte Ordering : Unknown ", 0,0);
}

//*************************************************************************************************
// Wait
//-------------------------------------------------------------------------------------------------
// Wait time
UINT gnWaitTimeOffset =  0;	// Clock
UINT gnWaitTimeUnit   = 13;	// Clock / [1 cycle of while{ } in WaitUs()], ISPM ON & I-Cache ON,

void ISPM0 WaitUs(UINT anUs)	// MAX = 1000000 / [anCntPerSec in InitTickTimer()], Guarantee 500000 (��)
{	// Wait X usec (Accuracy is high by Tick timer)
	const UINT nTargerClk = ((MCLK/10000) * anUs) / 100;	// = 74.25 * anUs,  MCLK/10000 = 7425,

	TICK_STA(1);

	do {
		TICK_END(1);
		if((nTick_1 + gnWaitTimeOffset) >= nTargerClk) break;
	} while(1/*(nTick_1 + gnWaitTimeOffset) < nTargerClk*/);	// It can not be used nTick_1. Because nTick_1 is a local variable.
}

void WaitXus(UINT anUs)
{	// Wait X usec (Accuracy is low, Approximated )
	volatile UINT	i, j;

	for(j=0; j<anUs; j++){
		for(i=0; i<2; i++){
			asm("l.nop" : :);
		}
	}
}

void WaitXms(UINT anMs)
{	// Wait X msec (Accuracy is low, Approximated )
	volatile UINT	i, j;

	for(j=0; j<anMs; j++){
		for(i=0; i<2000; i++){
			asm("l.nop" : :);
		}
	}
}


//*************************************************************************************************
// Interpolator Function
//-------------------------------------------------------------------------------------------------
#define STATE0	0
#define STATE1	1
#define STATE2	2
#define STATE3	3
#define STATE4	4
#define STATE5	5

UINT IntpValAgcPos(UINT anCurAgc, UINT anAgcPt0, UINT anAgcPt1, UINT anAgcPt2, UINT anValPt0, UINT anValPt1, UINT anValPt2)
{
	UINT nAgcPos = 0;
	UINT nVal = 0;
	
	nAgcPos = (anCurAgc < anAgcPt0) ? STATE0 :
			  (anCurAgc < anAgcPt1) ? STATE1 :
			  (anCurAgc < anAgcPt2) ? STATE2 : STATE3;

	switch (nAgcPos) {
		case STATE0 :	nVal = anValPt0;	break;
		case STATE1 :	nVal = LibUtlInterp1D (MINMAX(anCurAgc, anAgcPt0, anAgcPt1), anAgcPt0, anAgcPt1, anValPt0, 	anValPt1);	break;
		case STATE2 :	nVal = LibUtlInterp1D (MINMAX(anCurAgc, anAgcPt1, anAgcPt2), anAgcPt1, anAgcPt2, anValPt1, 	anValPt2);	break;			
		case STATE3 :	nVal = anValPt2;	break;
		
		default 	: 	nVal = anValPt0;	break;
	}

	return nVal;
}


UINT IntpValAgcPos4(UINT anCurAgc, UINT anAgcPt0, UINT anAgcPt1, UINT anAgcPt2, UINT anAgcPt3, UINT anValPt0, UINT anValPt1, UINT anValPt2, UINT anValPt3)
{
	UINT nAgcPos = 0;
	UINT nVal = 0;
	
	nAgcPos = (anCurAgc < anAgcPt0) ? STATE0 :
			  (anCurAgc < anAgcPt1) ? STATE1 :
			  (anCurAgc < anAgcPt2) ? STATE2 :
			  (anCurAgc < anAgcPt3) ? STATE3 : STATE4;

	switch (nAgcPos) {
		case STATE0 :	nVal = anValPt0;	break;
		case STATE1 :	nVal = LibUtlInterp1D (MINMAX(anCurAgc, anAgcPt0, anAgcPt1), anAgcPt0, anAgcPt1, anValPt0, 	anValPt1);	break;
		case STATE2 :	nVal = LibUtlInterp1D (MINMAX(anCurAgc, anAgcPt1, anAgcPt2), anAgcPt1, anAgcPt2, anValPt1, 	anValPt2);	break;			
		case STATE3 :	nVal = LibUtlInterp1D (MINMAX(anCurAgc, anAgcPt2, anAgcPt3), anAgcPt2, anAgcPt3, anValPt2, 	anValPt3);	break;			
		case STATE4 :	nVal = anValPt3;	break;
		
		default 	: 	nVal = anValPt0;	break;
	}

	return nVal;
}


UINT IntpValAePos(UINT anCurAePos, UINT anAePosPt0, UINT anAePosPt1, UINT anAePosPt2, UINT anValPt0, UINT anValPt1, UINT anValPt2)
{
	UINT nAgcPos = 0;
	UINT nVal = 0;
	
	nAgcPos = (anCurAePos < anAePosPt0) ? STATE0 :
			  (anCurAePos < anAePosPt1) ? STATE1 :
			  (anCurAePos < anAePosPt2) ? STATE2 : STATE3;

	switch (nAgcPos) {
		case STATE0 :	nVal = anValPt0;	break;
		case STATE1 :	nVal = LibUtlInterp1D (MINMAX(anCurAePos, anAePosPt0, anAePosPt1), anAePosPt0, anAePosPt1, anValPt0, 	anValPt1);	break;
		case STATE2 :	nVal = LibUtlInterp1D (MINMAX(anCurAePos, anAePosPt1, anAePosPt2), anAePosPt1, anAePosPt2, anValPt1, 	anValPt2);	break;			
		case STATE3 :	nVal = anValPt2;	break;
		
		default 	: 	nVal = anValPt0;	break;
	}

	return nVal;
}

UINT IntpValAePos5(int aiCurAePos, WORD* awAePosPt, UINT* anValPt)
{
	UINT nAePos = 0;
	UINT nVal = 0;
	
	nAePos  = (aiCurAePos < *(awAePosPt+0)) 			  		  ? STATE0 :
			  (aiCurAePos < MAX(*(awAePosPt+0), *(awAePosPt+1))) ? STATE1 :
			  (aiCurAePos < MAX(*(awAePosPt+1), *(awAePosPt+2))) ? STATE2 :
			  (aiCurAePos < MAX(*(awAePosPt+2), *(awAePosPt+3))) ? STATE3 :
			  (aiCurAePos < MAX(*(awAePosPt+3), *(awAePosPt+4))) ? STATE4 : STATE5;

	switch (nAePos) {
		case STATE0 :	nVal = *(anValPt+0);	break;
		case STATE1 :	nVal = LibUtlInterp1D (MINMAX(aiCurAePos, *(awAePosPt+0), *(awAePosPt+1)), *(awAePosPt+0), *(awAePosPt+1), *(anValPt+0), 	*(anValPt+1));	break;
		case STATE2 :	nVal = LibUtlInterp1D (MINMAX(aiCurAePos, *(awAePosPt+1), *(awAePosPt+2)), *(awAePosPt+1), *(awAePosPt+2), *(anValPt+1), 	*(anValPt+2));	break;			
		case STATE3 :	nVal = LibUtlInterp1D (MINMAX(aiCurAePos, *(awAePosPt+2), *(awAePosPt+3)), *(awAePosPt+2), *(awAePosPt+3), *(anValPt+2), 	*(anValPt+3));	break;		
		case STATE4 :	nVal = LibUtlInterp1D (MINMAX(aiCurAePos, *(awAePosPt+3), *(awAePosPt+4)), *(awAePosPt+3), *(awAePosPt+4), *(anValPt+3), 	*(anValPt+4));	break;		
		case STATE5 :	nVal = *(anValPt+4);	break;
		
		default 	: 	nVal = *(anValPt+0);	break;
	}

	return nVal;
}

UINT IntpValCtempPos(int aiCurCtemp, int aiCtempPt0, int aiCtempPt1, int aiCtempPt2, UINT anCtempVal0, UINT anCtempVal1, UINT anCtempVal2)
{
	int iCtempPos = 0;
	UINT nVal = 0;
	
	iCtempPos = (aiCurCtemp < aiCtempPt0) ? STATE0 :
			  	(aiCurCtemp < aiCtempPt1) ? STATE1 :
			  	(aiCurCtemp < aiCtempPt2) ? STATE2 : STATE3;

	switch (iCtempPos) {
		case STATE0 :	nVal = anCtempVal0;	break;
		case STATE1 :	nVal = LibUtlInterp1D (MINMAX(aiCurCtemp, aiCtempPt0, aiCtempPt1), aiCtempPt0, aiCtempPt1, anCtempVal0, anCtempVal1);	break;
		case STATE2 :	nVal = LibUtlInterp1D (MINMAX(aiCurCtemp, aiCtempPt1, aiCtempPt2), aiCtempPt1, aiCtempPt2, anCtempVal1, anCtempVal2);	break;			
		case STATE3 :	nVal = anCtempVal2;	break;
		
		default 	: 	nVal = anCtempVal0;	break;
	}

	return nVal;
}

void ExtWR_Reg(WORD awAddr, UINT anData, BYTE abLength)
{
	int i = 0;
	for(i=0; i < abLength; i++)		SetSens(awAddr+i, ((anData>>((abLength-i-1)*8))&0xFF));
}                     



