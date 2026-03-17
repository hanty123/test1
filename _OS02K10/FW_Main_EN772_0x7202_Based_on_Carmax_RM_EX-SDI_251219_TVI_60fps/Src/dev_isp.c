/* **************************************************************************
 File Name	: 	dev_isp.c
 Description:	EN772 - ISP device driver
 Designer	:	Sung, Min-Je / Kim, Sung-Hoon
 Date		:	14. 6. 18
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

UINT gnFontdummy;

volatile BYTE gbVdiIrq = 0;
volatile BYTE gbVdwIrq = 0;
volatile BYTE gbVdoIrq = 0;
volatile BYTE gbMnVdIrq = 0;

volatile BYTE gbVdiIrqOn = 0;
volatile BYTE gbVdwIrqOn = 0;
volatile BYTE gbVdoIrqOn = 0;

void InitWaitVd(const int aiTestPatternOn)
{
	if(gbVdiIrqOn == 0 && gbVdwIrqOn == 0) {
		TxStrDecNoIRQ("Wait Vd Init...", aiTestPatternOn, 1);
		WaitUs(33333);
	}

	if(gbVdiIrqOn == 0) {
		if(gbVdiIrq) {
			gbVdiIrqOn = 1;
			TxStrDecNoIRQ("  >>VDI OK...", 0, 0);
		}
		else {
			TxStrDecNoIRQ("  >>NO VDI...", 0, 0);
		}
	}

	if(gbVdwIrqOn == 0) {
		if(gbVdwIrq) {
			gbVdwIrqOn = 1;
			TxStrDecNoIRQ("  >>VDW OK...", 0, 0);
		}
		else {
			TxStrDecNoIRQ("  >>NO VDW...", 0, 0);
		}
	}

	#if(0)
	if(gbVdoIrqOn == 0) {
		if(gbVdoIrq) {
			gbVdoIrqOn = 1;
			TxStrDecNoIRQ("  >>VDO OK...", 0, 0);
		}
		else {
			TxStrDecNoIRQ("  >>NO VDO...", 0, 0);
		}
	}
	#endif
	
	if(!gbVdiIrqOn && aiTestPatternOn) {
		TestPatternOn();
	}
}

void ISPM0 WaitVdi(void)
{	// Wait VDI interrupt
	if(gbVdiIrqOn) {
		while(!gbVdiIrq);
		gbVdiIrq = 0;
	}
	else {
		WaitUs(33333);
	}
}

void ISPM0 WaitVdw(void)
{	// Wait VDW interrupt
	if(gbVdwIrqOn) {
		while(!gbVdwIrq);
		gbVdwIrq = 0;
	}
	else {
		WaitUs(33333);
	}
}

#if(0)
void ISPM0 WaitVdo(void)
{	// Wait VDO interrupt
	if(gbVdoIrqOn) {
		while(!gbVdoIrq);
		gbVdoIrq = 0;
	}
	else {
		WaitUs(33333);
	}
}
#endif

volatile UINT gnIsrISP0 = 0;
volatile UINT gnIsrISP1 = 0;
volatile UINT gnIsrISP2 = 0;

BYTE gnIsrStatus[7];
BYTE gnIsrStatusPos = 0;

void ISPM0 IsrISP(void)		// CAUTION!!! - Isr stack size = 0x400, Do not use a lot of variables.
{
	while(1) {
		//#define IsrStatus RISC_IRQr
		/*const*/ WORD IsrStatus = EXRISC_IRQr;
		
		if(IsrStatus == 0) break;

		if(gnIsrStatusPos < numberof(gnIsrStatus)) {
			gnIsrStatus[gnIsrStatusPos++] = IsrStatus;
		}

		//if(gtUartQue.wTxLen < (UART_BUF_SIZE>>1)) TxStr("IsrISP:", IsrStatus, 1);

		/*0	*/if(IsrStatus&(0x1<<ISP_IRQ_VLOCKL	)) 		{ CLI_VLOCKLw(1); gbVdiIrq = 1; gnIsrISP0++; }
		/*1	*/if(IsrStatus&(0x1<<ISP_IRQ_VLOCKW	)) 		{ CLI_VLOCKWw(1); gbVdwIrq = 1; gnIsrISP1++; }
		/*4  	*/if(IsrStatus&(0x1<<ISP_IRQ_VLOCKO	)) 		{ CLI_VLOCKOw(1); gbVdoIrq = 1; gnIsrISP2++; CTX00w(0x0);	CTX01w(0x0);	CTX02w(0x0);}
		/*8	*/if(IsrStatus&(0x1<<ISP_IRQ_USERI0 	)) 		{ CLI_UIRQF0w(1);  }					// VDI ����
		/*16	*/if(IsrStatus&(0x1<<ISP_IRQ_USERI1 	)) 		{ CLI_UIRQF1w(1);  }					// VDI ����
		/*32	*/if(IsrStatus&(0x1<<ISP_IRQ_USERO0 	)) 		{ CLI_UIRQP0w(1);  }					// VDO ����
		/*64	*/if(IsrStatus&(0x1<<ISP_IRQ_USERO1 	)) 		{ CLI_UIRQP1w(1);  }					// VDO ����
		/*128 */if(IsrStatus&(0x1<<ISP_IRQ_COAX  )) 	{  
				#if(model_UccA)
					extern void GetUccData(void);
					GetUccData();	// HD analog UCC interrupt  // 200819 HTY
				#endif
					CLI_CXALw(1);
				}
		/*256 */if(IsrStatus&(0x1<<ISP_IRQ_ADC   	)) 	{ CLI_ADCw(1);}
		/*512*/if(IsrStatus&(0x1<<ISP_IRQ_VLOCKM		))	{ CLI_MANUALw(1); gbMnVdIrq = 1;}
		//if(IsrStatus&(0x1<<ISP_IRQ_UPST  )) { CLI_USIRQw(1); }
	}
}


//----------------------------------------------------------------------------------------
#if 0
void ISPM0 _wr8_fnc(const UINT anAddr, const BYTE abData)
{
	(*((volatile BYTE *)(anAddr)) = (abData));
}

void ISPM0 _wr32_fnc(const UINT anAddr, const UINT anData)
{
	(*((volatile UINT *)(anAddr)) = (anData));
}
#endif

//*************************************************************************************************
// Utillity
//-------------------------------------------------------------------------------------------------
// Font
void ISPM SetFontAttrs(UINT anPosY, UINT anPosX, UINT anLen, UINT anAttr)
{	// Font attributes setting
	UINT i;

	for(i=0; i<anLen; i++) {SETFONTATTR(anPosY, anPosX+i, anAttr);}
}

UINT ISPM DispStr(const char* cStr, UINT anPosY, UINT anPosX, UINT anLen)
{
	UINT i;

	for(i=0; i<anLen && (*(cStr+i)); i++) {SETFONTID(anPosY, anPosX+i, (BYTE)cStr[i]);}
	
	return i;
}

void ISPM DispClr(UINT anPosY, UINT anPosX, UINT anLen)
{
    UINT i;

	for(i=0; i<anLen; i++) {SETFONTID(anPosY, anPosX+i, SPACE_CHAR_ID);}
}

void ISPM DispClrStr(const char* cStr, UINT anPosY, UINT anPosX, UINT anStrLen, UINT anClrLen)
{
	UINT i;

	for(i=0; i<anStrLen && (*(cStr+i)); i++){SETFONTID(anPosY, anPosX+i, (BYTE)cStr[i]);}
	for(; i<anClrLen; i++) 					 {SETFONTID(anPosY, anPosX+i, SPACE_CHAR_ID);}
}

#if model_CharMax == 1
void ISPM DispStrEx(const EXCH* cStr, UINT anPosY, UINT anPosX, UINT anLen)
{
	UINT i;
	for(i=0; i<anLen && (*(cStr+i)); i++) {
		SETFONTID(anPosY, anPosX+i, (EXCH)(*(cStr+i)));
	}
}

void ISPM DispClrStrEx(const EXCH* cStr, UINT anPosY, UINT anPosX, UINT anStrLen, UINT anClrLen)
{
	UINT i;

	for(i=0; i<anStrLen && (*(cStr+i)); i++) {
		SETFONTID(anPosY, anPosX+i, (EXCH)(*(cStr+i)));
	}

	for(; i<anClrLen; i++) {
		SETFONTID(anPosY, anPosX+i, 0/*' '*/);
	}
}
#endif


