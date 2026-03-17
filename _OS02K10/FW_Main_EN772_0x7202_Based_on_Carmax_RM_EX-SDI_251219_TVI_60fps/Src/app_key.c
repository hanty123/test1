/* **************************************************************************
 File Name	: 	app_key.c
 Description	:	EN772 - key scan module
 Designer		:	Kim, Sunghoon
 Date		:	14. 6. 17
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

//*************************************************************************************************
// Define & Variable
//-------------------------------------------------------------------------------------------------
// Key filtering (Chattering, Repeated key)
BYTE	gbUKeyVal = 0;				// Key UART(Input)
TKey	gtUKey = {0};				// Key UART(Chattering or Holding)

BYTE	gbPKeyVal = 0;				// Key UART(Input) - Pelco
TKey	gtPKey = {0};				// Key UART(Chattering or Holding)

BYTE	gbCKeyVal = 0;				// Key UCC(Input)
TKey	gtCKey = {0};				// Key UCC(Chattering or Holding)

BYTE	gbSKeyVal = 0;				// Key UART(Input)
TKey	gtSKey = {0};				// Key UART(Chattering or Holding)

BYTE	gbMKey = 0;					// Key MENU(Repeated)
BYTE	gbPKey = 0;					// Key MENU(Pushing)
BYTE	gbiKey = 0;					// Key MENU(VDi)	// 151214 HSH


//*************************************************************************************************
// Key
//-------------------------------------------------------------------------------------------------
// Chattering
void KeyCht(const BYTE abIn, TKey* aptKey, const BYTE abCHT_BIT)
{
	aptKey->v.bSft = (aptKey->v.bSft<<1) | (abIn!=0);
	aptKey->v.bOn = ((aptKey->v.bSft & abCHT_BIT) == abCHT_BIT) ? abIn : 0 ;
}

void KeyHld(const BYTE abIn, TKey* aptKey, const BYTE abHoldTime)
{
	if(abIn) {
		aptKey->v.bSft = abHoldTime;
		aptKey->v.bOn = abIn;
	}
	
	if(aptKey->v.bSft) aptKey->v.bSft--;
	else aptKey->v.bOn = 0;
}

void KeyPush(const BYTE abIn, TKey* aptKey, BYTE* apbMenuPushState, BYTE* apRepeatKEY, BYTE* apPushKEY)
{
	aptKey->v.bRpt = abIn;
	if(aptKey->v.bRpt) *apRepeatKEY = aptKey->v.bRpt;

	if(*apbMenuPushState == 1) {
		if(aptKey->b.Cr) aptKey->b.C = (!aptKey->b.C);
		else if(*apRepeatKEY || *apPushKEY) {
			if(aptKey->b.C)	*apbMenuPushState = 2;
			else			*apbMenuPushState = 0;
			aptKey->v.bOn = 0;
		}
	}
	else {
		aptKey->v.bOn = 0;
	}

	if(aptKey->v.bOn) *apPushKEY = aptKey->v.bOn;
}

//-------------------------------------------------------------------------------------------------
// Repeat key
void KeyRpt(TKey* aptKey, const BYTE abRptStart, const BYTE abRptTime)
{
	if(aptKey->v.bOn)
	{
		if(aptKey->v.bCnt == 0) {								// First
			aptKey->v.bCnt++;
			aptKey->v.bRpt = aptKey->v.bOn;
		}
		else if(aptKey->v.bCnt == abRptStart) {					// Second
			aptKey->v.bCnt++;
			aptKey->v.bRpt = aptKey->v.bOn;
		}
		else if(aptKey->v.bCnt >= (abRptStart + abRptTime)) {	// Every
			aptKey->v.bCnt = abRptStart;
			aptKey->v.bRpt = 0;
		}
		else{
			aptKey->v.bCnt++;
			aptKey->v.bRpt = 0;
		}
	}
	else {
		aptKey->v.bCnt = 0;
		aptKey->v.bRpt = 0;
	}
}

void ISPM2 KeyScan(void)		// 180104 LH
{
//	const UINT nADC_KEY = ADC_KEYr;
	DebugDisp((gbMnDebugFnc==MN_DBG_6), , "ADC_Key_", 2, 24, ADC_KEYr)

	DebugDisp((gbMnDebugFnc==MN_DBG_6), , "ADC0____", 5, 24, ADC_KEYr)
	DebugDisp((gbMnDebugFnc==MN_DBG_6), , "ADC1____", 6, 24, ADC_CDSr)

#if (model_Key==0)
	//----------------------------------------------------------------------------------------
	// ADC Key
		gbSKeyVal =	(ADC_KEYr<(((UINT)UP(UpADC_LEVEL_C)+(UINT)UP(UpADC_LEVEL_U))>>1)) ? KEY_VAL_C :		// Center
					(ADC_KEYr<(((UINT)UP(UpADC_LEVEL_U)+(UINT)UP(UpADC_LEVEL_D))>>1)) ? KEY_VAL_U :		// Up
					(ADC_KEYr<(((UINT)UP(UpADC_LEVEL_D)+(UINT)UP(UpADC_LEVEL_L))>>1)) ? KEY_VAL_D :		// Down
					(ADC_KEYr<(((UINT)UP(UpADC_LEVEL_L)+(UINT)UP(UpADC_LEVEL_R))>>1)) ? KEY_VAL_L : 		// Left
					(ADC_KEYr<(((UINT)UP(UpADC_LEVEL_R)+             0x000003FF)>>1)) ? KEY_VAL_R : 0;		// Right

	static BYTE bSKeyVal1d = 0;
	if(bSKeyVal1d != gbSKeyVal) {
		bSKeyVal1d = gbSKeyVal;
		gbSKeyVal = 0;
	}

	KeyCht(gbSKeyVal, &gtSKey, (1<<UP(UpAD_CHT_BIT))-1);
	KeyRpt(&gtSKey, AD_KEY_RPTF, AD_KEY_RPTT);
#endif

	//----------------------------------------------------------------------------------------
	// UART Key - ECM(PC)
	KeyHld(gbUKeyVal, &gtUKey, UART_HOLD_CNT);
	KeyRpt(&gtUKey, UART_KEY_RPTF, UART_KEY_RPTT);

	//----------------------------------------------------------------------------------------
	// UART Key - Pelco
	KeyHld(gbPKeyVal, &gtPKey, PELCO_HOLD_CNT);
	KeyRpt(&gtPKey, PELCO_KEY_RPTF, PELCO_KEY_RPTT);

	//----------------------------------------------------------------------------------------
	// Key MUX
	KEY =	(gtUKey.v.bRpt) ? gtUKey.v.bRpt : (gtPKey.v.bRpt) ? gtPKey.v.bRpt : gtSKey.v.bRpt;

	pKEY =	(gtUKey.v.bOn) ? gtUKey.v.bOn : (gtPKey.v.bOn) ? gtPKey.v.bOn : gtSKey.v.bOn;
	
	//----------------------------------------------------------------------------------------
	// COX Key
#if 0	// SRC_KEY -> gbCKeyVal ·Î »ç¿ë
	#define SRC_KEY	gtUKey
	static BYTE bKEY1d = 0;
	if(bKEY1d == 0 && SRC_KEY.v.bRpt) {
		gbCKeyVal = SRC_KEY.v.bRpt;
	}
	bKEY1d = SRC_KEY.v.bRpt;

	const TKey tSRC_KEY = SRC_KEY;
	SRC_KEY.nKey = 0;
	KEY =	(gtUKey.v.bRpt) ? gtUKey.v.bRpt : (gtPKey.v.bRpt) ? gtPKey.v.bRpt : gtSKey.v.bRpt;
	pKEY =	(gtUKey.v.bOn) ? gtUKey.v.bOn : (gtPKey.v.bOn) ? gtPKey.v.bOn : gtSKey.v.bOn;
	SRC_KEY = tSRC_KEY;
#endif

	KeyPush(gbCKeyVal, &gtCKey, &gbMenuPushState, &KEY, &pKEY);
	//KeyPush(gbUKeyVal, &gtUKey, &gbMenuPushState, &KEY, &pKEY);

	if(KEY!=0)
		iKEY = KEY;	// 151214 HSH

	//----------------------------------------------------------------------------------------
	// Debug
#if GRP_TI_UCC
	//GRP0 = gbCKeyVal;
	GRP1 = gtCKey.v.bRpt;
	GRP2 = gtCKey.v.bOn;
	//GRP3 = gbUKeyVal;
	//GRP4 = gtUKey.v.bRpt;
	//GRP5 = gtUKey.v.bOn;
	TxGrp();
#endif

#if 0
	GRP0 = gbUKeyVal;
	GRP1 = gbMenuPushState;
	GRP2 = pKEY;
	GRP4 = KEY;
	TxGrp();
#endif


	gbUKeyVal = 0;
	gbPKeyVal = 0;
}


void KeyAccLevel(int *aiKeyAdd)
{
	//KEY Accumulator Level
	#define KEY_ACC_LV0		1
	#define KEY_ACC_LV1		9
	#define KEY_ACC_LV2		14
	#define KEY_ACC_LV3		18
	#define KEY_ACC_LV4		22
	#define KEY_ACC_LV5		25
	#define KEY_ACC_LV6		28
	#define KEY_ACC_LV7		30
	
	//KEY Accumulator Level Count
	#define KEY_ACC_LV0_CNT	(FR/2)			// 30
	#define KEY_ACC_LV1_CNT	(FR/3)			// 15
	#define KEY_ACC_LV2_CNT	(FR/4)			// 10
	#define KEY_ACC_LV3_CNT	(FR/5)			// 7
	#define KEY_ACC_LV4_CNT	(FR/6)			// 6
	#define KEY_ACC_LV5_CNT	(FR/7)			// 5
	#define KEY_ACC_LV6_CNT	(FR/8)			// 4
	#define KEY_ACC_LV7_CNT	(FR/11)			// 3
	
	#define KEY_NONE_CNT	2

	static int iKeyAccLv = 0;
	static int iKeyAccLvCnt = 0;
	static int iKeyAccLvDn = 0;
	
	if(pKEY == 0 || KEY != pKEY) {
		iKeyAccLvDn++;
		if(iKeyAccLvDn == KEY_NONE_CNT) {
			iKeyAccLvDn = 0;
			iKeyAccLvCnt = 0;
			iKeyAccLv = 0;
		}
	}

//	if(pKEY) {
	if(pKEY||KEY) { // 161214 HTY
		iKeyAccLvDn = 0;
		iKeyAccLvCnt++;

		switch(iKeyAccLv) {
			case 0 : 
				if(iKeyAccLvCnt == KEY_ACC_LV0_CNT) { iKeyAccLvCnt = 0;	iKeyAccLv++; }		
				*aiKeyAdd = LibUtlInterp1D(iKeyAccLvCnt,0,KEY_ACC_LV0_CNT,KEY_ACC_LV0,KEY_ACC_LV1); break;
			case 1 : 
				if(iKeyAccLvCnt == KEY_ACC_LV1_CNT) { iKeyAccLvCnt = 0;	iKeyAccLv++; }		
				*aiKeyAdd = LibUtlInterp1D(iKeyAccLvCnt,0,KEY_ACC_LV1_CNT,KEY_ACC_LV1,KEY_ACC_LV2); break;
			case 2 : 
				if(iKeyAccLvCnt == KEY_ACC_LV2_CNT) { iKeyAccLvCnt = 0;	iKeyAccLv++; }		
				*aiKeyAdd = LibUtlInterp1D(iKeyAccLvCnt,0,KEY_ACC_LV2_CNT,KEY_ACC_LV2,KEY_ACC_LV3); break;
			case 3 : 
				if(iKeyAccLvCnt == KEY_ACC_LV3_CNT) { iKeyAccLvCnt = 0;	iKeyAccLv++; }		
				*aiKeyAdd = LibUtlInterp1D(iKeyAccLvCnt,0,KEY_ACC_LV3_CNT,KEY_ACC_LV3,KEY_ACC_LV4); break;
			case 4 : 
				if(iKeyAccLvCnt == KEY_ACC_LV4_CNT) { iKeyAccLvCnt = 0;	iKeyAccLv++; }		
				*aiKeyAdd = LibUtlInterp1D(iKeyAccLvCnt,0,KEY_ACC_LV4_CNT,KEY_ACC_LV4,KEY_ACC_LV5); break;
			case 5 : 
				if(iKeyAccLvCnt == KEY_ACC_LV5_CNT) { iKeyAccLvCnt = 0;	iKeyAccLv++; }		
				*aiKeyAdd = LibUtlInterp1D(iKeyAccLvCnt,0,KEY_ACC_LV5_CNT,KEY_ACC_LV5,KEY_ACC_LV6); break;
			case 6 : 
				if(iKeyAccLvCnt == KEY_ACC_LV6_CNT) { iKeyAccLvCnt = 0;	iKeyAccLv++; }		
				*aiKeyAdd = LibUtlInterp1D(iKeyAccLvCnt,0,KEY_ACC_LV6_CNT,KEY_ACC_LV6,KEY_ACC_LV7); break;
			default: 
				if(iKeyAccLvCnt == KEY_ACC_LV7_CNT) { iKeyAccLvCnt = KEY_ACC_LV7_CNT - 1; }	
				*aiKeyAdd = KEY_ACC_LV7; break;
		}
	}
	
}

