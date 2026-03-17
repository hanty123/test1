/* **************************************************************************
 File Name	:	app_ae.c
 Description	:	EN772 - Auto Exposure function
 Designer		:	Lee, Hoon
 Modifier		:	Lee, Gyu Hong
 Date		:	19. 12. 18
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

// Lib link ---------------------------------------
extern int AE_GAIN_TOTAL;
extern int AE_GAIN_TOTAL2;

extern void ISPM AE_SHTLw(UINT val);		// Long Shutter
extern void ISPM AE_SHTSw(UINT val);		// Short Shutter

extern void ISPM AE_AGCw(UINT val);
extern void ISPM AE_DGCw(UINT val);

extern UINT	ISPM LibAeShtLine(UINT anLine);
extern WORD ISPM AeSHT(int aiVal, UINT anManual, UINT anManualVal);
extern void ISPM AeAGC(int aiVal); 
//extern void ISPM AeIRS(UINT nDTY, UINT anManual, UINT anManualVal);
BYTE gbEXUC_AgcFlag = 0;

#if (model_Sens_LWdr)
extern WORD ISPM AeSHT_LWDR(int aiMode, int aiVal, int aiVal1);
extern void ISPM AeAGC_LWDR(int aiMode, int aiVal, int aiVal1);
#endif

#if (model_Sens_CLR_HDR)   
extern WORD ISPM AeSHT_CHDR(int aiVal); 
extern void ISPM AeAGC_CHDR(int aiVal);    
#endif

extern UINT ISPM LibAeIrsIntp(UINT, UINT, UINT);
extern int ISPM LibAeSpeed_Irs(int, int, int);				
extern int ISPM LibAeSpeed(int, int, int);					
extern int ISPM LibAeSpeed_S1(int, int, int);	
extern int ISPM LibAeSpeedDc(int, int, int, int, int, int);

extern void ISPM LibAeWdr (int, int, UINT, UINT, UINT, UINT, UINT);	// 170213 LH

//*******************************************************************************
// Variables
//*******************************************************************************
UINT	gnAeState;		// 0:Shutter, 1:Iris, 2:AGC
UINT	gnAeStateS1;	// 0:Shutter, 1:Iris, 2:AGC				// 190319 LGH

int		giCurAgc;
int		giCurAePos;
int		giAePosLmt;
UINT 	gnAeHssTVal, gnAeIrsTVal, gnAeAgcTVal;
UINT 	gnAeHssTValS1, gnAeIrsTValS1, gnAeAgcTValS1;		// 190319 LGH

int		giShtValBuf, giAgcValBuf;
int		giShtValS1Buf, giAgcValS1Buf;

BYTE	gbWdrOnBuf=0;			// 190312 LH
int 	giErr1d,giErr2d;

UINT 	gnAeErr;
BYTE 	gbAeDebugOn;
int 	gnSht_L, gnSht_S1;
UINT 	gnAgc_L, gnAgc_S1;

UINT 	gnAeNorMax;
UINT 	gnAeLWdrMaxL0, gnAeLWdrMaxS1;
UINT 	gnAeLWdrMinL0, gnAeLWdrMinS1;

int		giAeLWdrGain;
WORD	gwAeWdrSatLv;
WORD	gwAeWdrWgt;
BYTE 	gbAeWdrComp = 0;

UINT 	gnIncrsBlkLv = 0;
BYTE 	PgOfs = 0;

WORD 	gwAeSensAgcLmtNor;
WORD 	gwAeSensAgcLmtWdr;

BYTE	gbAeWdrTm = 0;

UINT 	gnAe5Sum = 0x0;

#if (model_Iris_DC)
	int 	giIrsCent = /*0x1E5*/(AE_IRS_CLS_Max+AE_IRS_OPN_Max)<<(6-1);	// mean		Enx EV38 AR0230 = 0x1E5
	int 	giIrsPos = AE_IRS_STAT_Max/2;
	int		giIrsValBuf;
#else
	int 	giIrsCent = 0;
#endif

#if(model_Sens == SENS_OX03C10)
int iVstAddr = 0;
int iVendAddr = 0;

WORD gwVsShtPos0, gwVsShtPos1 = 0;
WORD gwVsAgcPos0, gwVsAgcPos1 = 0;
BYTE gbVsShtLine0, gbVsShtLine1 = 0;
#endif

//*******************************************************************************
// Sub Functions
//*******************************************************************************

void InitAe(void)
{
	AE_LOCK_SELw(1);
	AE_WIN_SELw(0x6);

	AE1_SLICEw(0x0);			// DEFOG
	AE1_CLIPw(0x3ff);			// "
	AE2_SLICEw(0x0);			// Main	/ Long
	AE2_CLIPw(0x3ff);			// "
	AE3_SLICEw(0x0);			// BLC  / WDR S1
	AE3_CLIPw(0x3ff);			// "

	TMG_ONw(0x0);

#if (model_5M)
	//The  AE2 window value originally set according to default mode
//	if(AE2_HSP == UP(UpAE2_HSP))	ParSet(N,D)
#endif

#if (Adaptive_led)								// 210302 YTM : Adaptive Lighting initializing
	InitAeLed();								// 210302 YTM : Adaptive Lighting initializing
#endif											// 210302 YTM : Adaptive Lighting initializing
}

// ---------------------------------------------------------

#if (model_Iris_DC)
void ISPM AeIRS(UINT nDTY, UINT anManual, UINT anManualVal)	// Fixed
{	// IRIS driver

	if (anManual)	PwmSetDty(anManualVal);
	else			PwmSetDty(nDTY);

//	DebugDisp(gbAeDebugOn, Hex, "IRS_CEN_", 3, 24, giIrsCent>>6	)
//	DebugDisp(gbAeDebugOn, Hex, "IRS_VAL_", 4, 24, nDTY			)
}
#endif

void AeSensTest(void)
{	// Sensor test
	// need to unset OutMode()

	const UINT 	nSum1    = AE2_SUM1_LOCKr  & 0xffffffff ;
	const UINT 	nSum2    = AE2_SUM2_LOCKr  & 0xffffffff ;
	const UINT  nSum	 = nSum1 + nSum2;

	AE2_SLICEw(0);
	AE_WIN_SELw(2);
	AE2_HSPw(UP(UpAE2_HSP)+200);
	AE2_HEPw(UP(UpAE2_HEP)-200);
	AE2_VSPw(UP(UpAE2_VSP)+200);
	AE2_VEPw(UP(UpAE2_VEP)-200);

	FONT_ONw(1);
	DebugDisp(gbAeDebugOn, Dec, "nAeSum__", 4, 24, nSum)
	if(gbAeDebugOn) OZONE_SELw(1);

	AE_SHTLw(PAR01);
	AE_AGCw(PAR02);
	AE_DGCw(PAR03);
}

void AeBlackOfst(void)
{
	// Decrease target value at low light
	gnIncrsBlkLv = IntpValAgcPos(giCurAgc, 	0x60, 0x80, 0xC0,\
											0x00, 0x01, 0x02);
	
	const BYTE bLastYoffs = IntpValAgcPos(giCurAgc, 	UP(UpAE_BLK_LVL_AGC_PT0), UP(UpAE_BLK_LVL_AGC_PT1), UP(UpAE_BLK_LVL_AGC_PT2),\
											UP(UpAE_BLK_LVL_VAL_PT0), UP(UpAE_BLK_LVL_VAL_PT1), UP(UpAE_BLK_LVL_VAL_PT2));
	
	PgOfs = IntpValAgcPos(giCurAgc, 	UP(UpPG_OFS_AGC_PT0), UP(UpPG_OFS_AGC_PT1), UP(UpPG_OFS_AGC_PT2),\
										UP(UpPG_OFS_VAL_PT0), UP(UpPG_OFS_VAL_PT1), UP(UpPG_OFS_VAL_PT2));
	PG_OFSw(PgOfs);
	
#if(0)
	CLAMP_GROFFSET_2w(0x3FF-((gnIncrsBlkLv*3)/2)+0x1);
	CLAMP_GBOFFSET_2w(0x3FF-((gnIncrsBlkLv*3)/2)+0x1);
	CLAMP_ROFFSET_2w(0x3FF- ((gnIncrsBlkLv*3)/2)+0x1);
	CLAMP_BOFFSET_2w(0x3FF- ((gnIncrsBlkLv*3)/2)+0x1);
#endif

	LAST_YOFFSw(OUTSCL_FULL_YOFST+bLastYoffs);
	
#if(model_IspO_ANL)
	PEDESTAL_LVw(EGP(UpPEDESTAL_LV)+bLastYoffs+0x400);
#endif
}

void AeOSD(void)
{	
	if(gbAeDebugOn||gbMnBlcOsdOn){
		OZONE_SELw(1);

//		AE_WIN_SELw((1<<1)|(1<<2));
		if(gbAeDebugOn&&gbMnBlcOsdOn)	AE_WIN_SELw((1<<1)|(1<<2));
		else if(gbAeDebugOn)			AE_WIN_SELw(1<<1);				// AE main window
		else							AE_WIN_SELw(1<<2);				// BLC window
	}
}

//*******************************************************************************
// Main Functions
//*******************************************************************************
void ISPM Ae(void)
{	// AE top

	gbAeDebugOn = (gbMnDebugFnc==MN_DBG_AE);	// Debug string on condition

	if (MP(MpShdDet))		return;				// Shading exception
	
// AE Sensor Test Only
#if (0)
	AeSensTest();								// Sensor test
	return;
#endif

#if(model_Sens == SENS_OX03C10)
	static UINT nPosCnt = 0x0;
	static int iVstAddr1d = 0x0;
	
	if(nPosCnt == 30){									// Stable Frame
		if(iVstAddr1d != iVstAddr){
			SetSensBst(0x3802, (iVstAddr&0xFFFF), 2);		// Vertical Start address	
			SetSensBst(0x3806, (iVendAddr&0xFFFF), 2);		// Vertical End address
		}
		iVstAddr1d = iVstAddr;
	}
	else{
		nPosCnt++;
	}
#endif
		
#if (model_Sony && (model_Lens!=2))
		WaitUs(300);							// delay for reg latch timing over 6H (Sony)
#endif

static 	UINT 	gnClipLvlBuf;
static 	int		giAePos=0, giAePosLmtBuf, giAeValBuf=600;
static 	int		giAePosS1=0, giAePosS1LmtBuf, giAeValS1Buf=600;

static 	int 	gfAePosL0, gfAePosS1;

		int		iAePosLmt=0;
		int		iAePosS1Lmt=0;

		int		iTgtL0=0, iCurL0=0, iErrL0=0, iShtValL0=0, iAgcValL0=0;	// Long / normal
		int		iTgtS1=0, iCurS1=0, iErrS1=0, iShtValS1=0, iAgcValS1=0;	// Short 1

		int 	iIrsVal = 0;
		int		iWdrSLmt=0;

static	BYTE	gbMnSysFreqBuf, gbMnLensBuf=-1;

		int		iHssLmt =0,	iIrsLmt =0,	iAgcLmt =0, iLssLmt =0;
		int		iHssLmtS1 =0, iAgcLmtS1 =0;								//190319 LGH


static int		gfIrsShtPos;                                // 171211 LH : int floating

#if(model_Iris==0)
	UNUSED_ARG(gfIrsShtPos);
#endif
		UINT 	nTgtDecrsVal = 0;
	
	// AE OSD ON
	AeOSD();

	// WDR status variable
	const BYTE 	bWdrOn 		 = (MODE_WDR_ON);

	// ODM Data variable
//	const UINT 	nAe2Sum0     = (AE2_SUM0_LOCKr  & 0xffffffff);
	const UINT 	nAe2Sum1     = (AE2_SUM1_LOCKr  & 0xffffffff);
	const UINT 	nAe2Sum2     = (AE2_SUM2_LOCKr  & 0xffffffff);

	const UINT 	nAe3Sum0     = (AE3_SUM0_LOCKr  & 0xffffffff);
	const UINT 	nAe3Sum1     = (AE3_SUM1_LOCKr  & 0xffffffff);
	const UINT 	nAe3Sum2     = (AE3_SUM2_LOCKr  & 0xffffffff);

//	const UINT 	nAe4Sum0     = (AE4_SUM0_LOCKr  & 0xffffffff);
	const UINT 	nAe4Sum1     = (AE4_SUM1_LOCKr  & 0xffffffff);
//	const UINT 	nAe4Sum2     = (AE4_SUM2_LOCKr  & 0xffffffff);
		
	const UINT 	nAe2ClipCnt  = (AE2_CLCNT_LOCKr & 0x003fffff);
	const UINT 	nAe2SlicCnt	 = (AE2_SLCNT_LOCKr & 0x003fffff);
	const UINT 	nAe3ClipCnt	 = (AE3_CLCNT_LOCKr & 0x003fffff);
	const UINT 	nAe3SlicCnt	 = (AE3_SLCNT_LOCKr & 0x003fffff);
	const UINT 	nAe4ClipCnt	 = (AE4_CLCNT_LOCKr & 0x003fffff);
	const UINT 	nAe4SlicCnt	 = (AE4_SLCNT_LOCKr & 0x003fffff);
	
	const UINT	nAeWin2PxCnt = ((AE2_VEPr - AE2_VSPr)+1) * ((AE2_HEPr - AE2_HSPr)+1);
	const UINT	nAeWin3PxCnt = ((AE3_VEPr - AE3_VSPr)+1) * ((AE3_HEPr - AE3_HSPr)+1);
	const UINT	nAeWin4PxCnt = ((AE4_VEPr - AE4_VSPr)+1) * ((AE4_HEPr - AE4_HSPr)+1);

	const UINT	nAe2ClipLvl	 = AE2_CLIPr;
	const UINT	nAe2SlicLvl	 = AE2_SLICEr;
	const UINT	nAe3ClipLvl	 = AE3_CLIPr;
	const UINT	nAe3SlicLvl	 = AE3_SLICEr;
	const UINT	nAe4ClipLvl	 = AE4_CLIPr;
	const UINT	nAe4SlicLvl	 = AE4_SLICEr;


	// AE5 Window
	const UINT 	nAe5SlicCnt	 = (AE5_SLCNT_LOCKr & 0x003fffff);

	const UINT	nAeWin5PxCnt = ((AE5_VEPr - AE5_VSPr)+1) * ((AE5_HEPr - AE5_HSPr)+1);


	UNUSED_ARG(nAe3Sum0);
	UNUSED_ARG(nAe3Sum2);
	// BLC variable 
//		   UINT	nBlcPosX=0, nBlcPosY=0, nBlcSizX=0, nBlcSizY=0;   
			int	iBlcPosX=0, iBlcPosY=0, iBlcSizX=0, iBlcSizY=0; 

	// Anti Saturation variable
	const UINT	nAE2_HW_Unit = (UP(UpAE2_HEP) - UP(UpAE2_HSP));
	const UINT	nAE2_VW_Unit = (UP(UpAE2_VEP) - UP(UpAE2_VSP));
		  UINT 	nAE2_HW_Gab=0, nAE2_VW_Gab=0;

	if(AE_LED_ASAT_COND) {
		nAE2_HW_Gab = (MP(MpLedSatCtrl) > 10) ? ((nAE2_HW_Unit>>2) + ((nAE2_HW_Unit/10) * (MP(MpLedSatCtrl) - 10) + 10) / 20) :	(((nAE2_HW_Unit>>1) * MP(MpLedSatCtrl) + 10) / 20);
		nAE2_VW_Gab = (MP(MpLedSatCtrl) > 10) ? ((nAE2_VW_Unit>>2) + ((nAE2_VW_Unit/10) * (MP(MpLedSatCtrl) - 10) + 10) / 20) :	(((nAE2_VW_Unit>>1) * MP(MpLedSatCtrl) + 10) / 20);
	}

	else{
		nAE2_HW_Gab = 0;
		nAE2_VW_Gab = 0;
	}
	
	// Set AE2 Window
	AE2_HSPw(MAX(0x0, UP(UpAE2_HSP))+nAE2_HW_Gab);
	AE2_HEPw(UP(UpAE2_HEP)-nAE2_HW_Gab);
	AE2_VSPw(MAX(0x0, UP(UpAE2_VSP))+nAE2_VW_Gab);
	AE2_VEPw(UP(UpAE2_VEP)-nAE2_VW_Gab);
	
	// Set AE window channel data path
	if(gbModeWdrOn_L){			// Line WDR Mode
	
	#if(model_Sens==SENS_OS02K10)
		AE_BITSELw(0x5/*0x6*/);
	#else
		AE_BITSELw(0x0);
	#endif
//		AE2_WIN_CHw(0x3);		// WDR ODM
		AE2_WIN_CHw(0x0);		// WDR ODM
		AE3_WIN_CHw(0x0);		// Short ref Long Image
		AE4_WIN_CHw(0x0);		// Image of Top Long
		AE5_WIN_CHw(0x0);		// Image of Top Long

		AE2_HSPw(MAX(0x0, UP(UpAE2_HSP)));
		AE2_HEPw(UP(UpAE2_HEP));
		AE2_VSPw(MAX(0x0, UP(UpAE2_VSP)));
		AE2_VEPw(UP(UpAE2_VEP));
		
		AE3_HSPw(MAX(0x0, UP(UpAE2_HSP)));
		AE3_HEPw(UP(UpAE2_HEP));
		AE3_VSPw(MAX(0x0, UP(UpAE2_VSP)));
		AE3_VEPw(UP(UpAE2_VEP));
		
		AE4_HSPw(MAX(0x0, UP(UpAE2_HSP)));
		AE4_HEPw(UP(UpAE2_HEP));
		AE4_VSPw(MAX(0x0, UP(UpAE2_VSP)));
		AE4_VEPw(0x200);

		AE5_HSPw(MAX(0x0, UP(UpAE2_HSP)));
		AE5_HEPw(UP(UpAE2_HEP));
		AE5_VSPw(MAX(0x0, UP(UpAE2_VSP)));
		AE5_VEPw(UP(UpAE2_VEP));
	}

#if(model_Sens_LFM_HDR)
   else if(gbModeWdrOn_LFM){	// LFM+HDR Mode
		AE_BITSELw(0x7);
//		AE_BITSELw(0x0);

		AE2_WIN_CHw(0x3);		// WDR Combine ODM
//		AE2_WIN_CHw(0x0);		// Long ODM
	}
#elif(model_Sens_CLR_HDR)
	else if(gbModeWdrOn_CLR){	// Clear HDR Mode
		#if(model_Sens==SENS_OS02K10)
		AE_BITSELw(0x5);
		#else
		AE_BITSELw(0x0);
		#endif
		AE2_WIN_CHw(0x0);
	}	
#endif

	else{						// Normal, BLC Mode
		AE_BITSELw(0x0);
		AE2_WIN_CHw(0x0);
		AE3_WIN_CHw(0x0);

		const BYTE bBLC_H_SIZE = AE_BLC_H_SIZE;
		const BYTE bBLC_V_SIZE = AE_BLC_V_SIZE;

		const int iBlcMinX = UP(UpAE2_HSP);
		const int iBlcMinY = UP(UpAE2_VSP);
		const int iBlcMaxX = UP(UpAE2_HEP);
		const int iBlcMaxY = UP(UpAE2_VEP);
		

		const int iBlcMirOfst = (MIRROR_ON)?(0x2):(0x0);
		const int iBlcFlpOfst = (FLIP_ON)?(0x12):(0x0);
	
		iBlcPosX = (MP(MpBlcPosX)*bBLC_H_SIZE)+iBlcMirOfst;
		iBlcPosY = (MP(MpBlcPosY)*bBLC_V_SIZE)+iBlcFlpOfst;
		iBlcSizX = iBlcPosX + (int)(MP(MpBlcSizX)*bBLC_H_SIZE);
		iBlcSizY = iBlcPosY + (int)(MP(MpBlcSizY)*bBLC_V_SIZE);

		iBlcPosX = MINMAX(iBlcPosX, iBlcMinX, iBlcMaxX);
		iBlcPosY = MINMAX(iBlcPosY,	iBlcMinY, iBlcMaxY);
		iBlcSizX = MINMAX(iBlcSizX, iBlcMinX, iBlcMaxX);
		iBlcSizY = MINMAX(iBlcSizY,	iBlcMinY, iBlcMaxY);
	
		AE3_HSPw(iBlcPosX);
		AE3_HEPw(iBlcSizX);
		AE3_VSPw(iBlcPosY);
		AE3_VEPw(iBlcSizY);
	}
	
// -------------------------------------------------------------------------------
// Status mode	
	//******************************************************************
	// Long position
	//******************************************************************
		
	gnAeHssTVal = (gbModeWdrOn_L) ? (LibAeShtLine(gnAeLWdrMaxL0)) : (LibAeShtLine(gnAeNorMax)+1);
	gnAeIrsTVal = (AE_IRS_STAT_Max);
	gnAeAgcTVal = (AE_GAIN_TOTAL + AE_GAIN_TOTAL2);

	// Set AE position limit
	iHssLmt 	= (MP(MpShutter)==MN_SHUT_MNL)				? (0):\
				  (MP(MpShutter)==MN_SHUT_FLICKER)			? (AE_SHT_FLK):\
				    (gbModeWdrOn_L)							? (AE_DEBLUR_COND) ? (AE_DEBLUR_THRS): (AE_LSHT_LMT_WDR):\
				  ((!AE_DEBLUR_COND))						? ((int)gnAeHssTVal) :	
		  															#if (AE_DEBLUR_FIX_ON==0)
																		AE_DEBLUR_THRS;
				  													#else
																		AE_DEBLUR_MAX;
				  													#endif

	iIrsLmt = ((MP(MpIris)==MN_LENS_MNL)||bWdrOn)			? 0 			:										// 190312 LH
			  (model_Iris_DC && AE_OUTDOOR_COND)			? gnAeIrsTVal + (gnAeHssTVal-AE_OUTDOOR_THRS) :
															  gnAeIrsTVal	;

	// For Focus
	iAgcLmt = (MP(MpAgc)>=20) ? (int)gnAeAgcTVal :
								(int)((((gnAeAgcTVal-AE_GAIN_TGT_OFST)*MP(MpAgc))/20)+AE_GAIN_TGT_OFST);

#if(1)
//	iLssLmt = 	(bWdrOn||(MP(MpShutter)==MN_SHUT_MNL)) 		? 0 :													// 190312 LH
	iLssLmt =	(MP(MpShutter)==MN_SHUT_MNL)		? 0 :													// 190312 LH
		#if (AE_DEBLUR_FIX_ON==1)			// 170824 LH
			AE_DEBLUR_COND									? 0 :
		#endif
			(gbModeWdrOn_L)									? 0 : 
	  		(MP(MpSysFreq)==MN_SYSFREQ_60) 					?
		  													(LibAeShtLine(gnAeNorMax)+1)-gnAeHssTVal + ( (MP(MpShutter)==MN_SHUT_FLICKER) ? (gnAeHssTVal-AE_SYS60_FLICKER) : 0 ) :
															(LibAeShtLine(gnAeNorMax)+1)-gnAeHssTVal + ( (MP(MpShutter)==MN_SHUT_FLICKER) ? (gnAeHssTVal-AE_SYS50_FLICKER) : 0 ) ;
#else
	iLssLmt = 0;
#endif
		
	//******************************************************************
	// Short1 position (Only Line WDR)
	//******************************************************************
	if(gbModeWdrOn_L){

	gnAeHssTValS1 = LibAeShtLine(gnAeLWdrMaxS1);
	gnAeAgcTValS1 = AE_GAIN_TOTAL + AE_GAIN_TOTAL2;

	iHssLmtS1	  = (int)gnAeHssTValS1;
	iAgcLmtS1 = 0;
	}

// -------------------------------------------------------------------------------
// Input condition adj

	if(bWdrOn){	// WDR mode --------------------------------------------------

		if(gbModeWdrOn_L) {
	
		//******************************************************************
		// Long Tgt proc
		//******************************************************************
		// WDR Image ODM
		iCurL0 = (int)((nAe2SlicCnt*nAe2SlicLvl) + nAe2Sum1 + (nAe2ClipCnt*nAe2ClipLvl)) / nAeWin2PxCnt;
		iTgtL0 = (UP(UpAE_WDR_LTGT_GAIN) * MP(MpBrightness)) + UP(UpAE_WDR_LTGT_OFST);

		// Decrease target value at low light
		nTgtDecrsVal = IntpValAgcPos(giCurAgc, 	UP(UpAE_WDR_LTGT_DCRS_AGC_PT0), UP(UpAE_WDR_LTGT_DCRS_AGC_PT1), UP(UpAE_WDR_LTGT_DCRS_AGC_PT2),\
												UP(UpAE_WDR_LTGT_DCRS_VAL_PT0), UP(UpAE_WDR_LTGT_DCRS_VAL_PT1), UP(UpAE_WDR_LTGT_DCRS_VAL_PT2));

		iTgtL0 = MAX((iTgtL0-nTgtDecrsVal), 0x0);
		iErrL0 = iTgtL0 - iCurL0;

		// AE2 SUM0
		#if(0)
		GRP3 = nAe2SlicLvl;	
		GRP4 = (nAe2Sum1 / (nAeWin2PxCnt - nAe2SlicCnt - nAe2ClipCnt));
		GRP5 = (nAe2Sum0 / nAe2SlicCnt);
		#endif
			//******************************************************************
			// Top of Image
			//******************************************************************
//			UINT nClipWgt = 0;
			int iCurT = 0;
			iCurT = (int)((nAe4SlicCnt*nAe4SlicLvl) + nAe4Sum1 + (nAe4ClipCnt*nAe4ClipLvl)) / nAeWin4PxCnt;
//			GRP6 = iCurT;

			AE4_SLICEw(0x0);
			AE4_CLIPw(0x3FF);	


			AE5_SLICEw(/*PAR02*/0x10);
			AE5_CLIPw(0x3FF);

//			gnAe5Sum = (int)((nAe5SlicCnt*nAe5SlicLvl) + nAe5Sum1 + (nAe5ClipCnt*nAe5ClipLvl)) / nAeWin5PxCnt;
			gnAe5Sum = (nAe5SlicCnt<<10)/nAeWin5PxCnt;
//			GRP6 = gnAe5Sum;

		#if(0)	
		const int iWdrClipLv  = IntpValAgcPos(giCurAgc, 	UP(UpAE_WDR_CLP_AGC_PT0), 	UP(UpAE_WDR_CLP_AGC_PT1), 	UP(UpAE_WDR_CLP_AGC_PT2),\
															UP(UpAE_WDR_CLP_VAL_PT0), 	UP(UpAE_WDR_CLP_VAL_PT1), 	UP(UpAE_WDR_CLP_VAL_PT2));
															
		#else
		
		const int iWdrClipLv  = IntpValAgcPos(iCurT, 		UP(UpAE_WDR_CLP_AGC_PT0), 	UP(UpAE_WDR_CLP_AGC_PT1), 	UP(UpAE_WDR_CLP_AGC_PT2),\
															UP(UpAE_WDR_CLP_VAL_PT0), 	UP(UpAE_WDR_CLP_VAL_PT1), 	UP(UpAE_WDR_CLP_VAL_PT2));
		
		int iWdrSliceLv  = IntpValAgcPos(iCurT, 		UP(UpAE_WDR_CLP_AGC_PT0), 	UP(UpAE_WDR_CLP_AGC_PT1), 	UP(UpAE_WDR_CLP_AGC_PT2),\
															0x0, 	0x20, 	0x20);
		//		iWdrSliceLv = MINMAX(iWdrSliceLv, 0x0, (iTgtL0>>1)-UP(UpAE_WDR_LSLIC_OFST));

		#endif

		AE2_SLICEw(MINMAX(((int)((iTgtL0>>1)-iWdrSliceLv)), 0x0, (iTgtL0>>1)));
		
//		AE2_CLIPw(MIN(0x3FF, (iTgtL0 + UP(UpAE_WDR_LCLIP_OFST) + iWdrClipLv)));			// next long
//		AE2_CLIPw(MINMAX(UP(UpAE_WDR_LCLIP_OFST)+iWdrClipLv, iTgtL0, 0x3FF));									// next long
		
		// For Focus
		AE2_CLIPw(MINMAX(iWdrClipLv, iTgtL0, 0x3FF));						// next long		
			
		//******************************************************************
		// Short1 Tgt proc
		//******************************************************************
		iCurS1 = (int)((nAe3SlicCnt*nAe3SlicLvl) + nAe3Sum1 + (nAe3ClipCnt*nAe3ClipLvl)) / nAeWin3PxCnt;
		iTgtS1 = (UP(UpAE_WDR_STGT_GAIN) * MP(MpBrightness)) + UP(UpAE_WDR_STGT_OFST);
		iErrS1 = iTgtS1 - iCurS1;

		AE3_SLICEw(MAX(0x0, (iTgtS1>>1)-UP(UpAE_WDR_SSLIC_OFST)));		
		AE3_CLIPw(MIN(0x3FF, iTgtS1+UP(UpAE_WDR_SCLIP_OFST)));
		

		}

	#if(model_Sens_CLR_HDR)
		else if(gbModeWdrOn_CLR){	// Clear HDR Mode
		//******************************************************************
		// Long Tgt proc
		//******************************************************************
		// WDR Image ODM
		iCurL0 = (int)((nAe2SlicCnt*nAe2SlicLvl) + nAe2Sum1 + (nAe2ClipCnt*nAe2ClipLvl)) / nAeWin2PxCnt;
		iTgtL0 = (UP(UpAE_WDR_LTGT_GAIN) * MP(MpBrightness)) + UP(UpAE_WDR_LTGT_OFST);

		// Decrease target value at low light
		nTgtDecrsVal = IntpValAgcPos(giCurAgc, 	UP(UpAE_WDR_LTGT_DCRS_AGC_PT0), UP(UpAE_WDR_LTGT_DCRS_AGC_PT1), UP(UpAE_WDR_LTGT_DCRS_AGC_PT2),\
												UP(UpAE_WDR_LTGT_DCRS_VAL_PT0), UP(UpAE_WDR_LTGT_DCRS_VAL_PT1), UP(UpAE_WDR_LTGT_DCRS_VAL_PT2));

		iTgtL0 = MAX((iTgtL0-nTgtDecrsVal), 0x0);
		iErrL0 = iTgtL0 - iCurL0;

	#if(0)
		const int iWdrClipLv  = IntpValAgcPos(giCurAgc, 	UP(UpAE_WDR_CLP_AGC_PT0), 	UP(UpAE_WDR_CLP_AGC_PT1), 	UP(UpAE_WDR_CLP_AGC_PT2),\
															UP(UpAE_WDR_CLP_VAL_PT0), 	UP(UpAE_WDR_CLP_VAL_PT1), 	UP(UpAE_WDR_CLP_VAL_PT2));
		
		AE2_SLICEw(MAX(0x0, (iTgtL0>>1)-UP(UpAE_WDR_LSLIC_OFST)));
//		AE2_CLIPw(MIN(0x3FF, (iTgtL0 + UP(UpAE_WDR_LCLIP_OFST) + iWdrClipLv)));			// next long
		AE2_CLIPw(MINMAX(UP(UpAE_WDR_LCLIP_OFST)+iWdrClipLv, iTgtL0, 0x3FF));									// next long

	#else
		// AE2 SUM0
		#if(0)
		GRP3 = nAe2SlicLvl;	
		GRP4 = (nAe2Sum1 / (nAeWin2PxCnt - nAe2SlicCnt - nAe2ClipCnt));
		GRP5 = (nAe2Sum0 / nAe2SlicCnt);
		#endif
			//******************************************************************
			// Top of Image
			//******************************************************************
//			UINT nClipWgt = 0;
			int iCurTClr = 0;
			iCurTClr = (int)((nAe4SlicCnt*nAe4SlicLvl) + nAe4Sum1 + (nAe4ClipCnt*nAe4ClipLvl)) / nAeWin4PxCnt;
//			GRP6 = iCurT;

			AE4_SLICEw(0x0);
			AE4_CLIPw(0x3FF);	


			AE5_SLICEw(/*PAR02*/0x10);
			AE5_CLIPw(0x3FF);

//			gnAe5Sum = (int)((nAe5SlicCnt*nAe5SlicLvl) + nAe5Sum1 + (nAe5ClipCnt*nAe5ClipLvl)) / nAeWin5PxCnt;
			gnAe5Sum = (nAe5SlicCnt<<10)/nAeWin5PxCnt;
//			GRP6 = gnAe5Sum;

		#if(0)	
		const int iWdrClipLv  = IntpValAgcPos(giCurAgc, 	UP(UpAE_WDR_CLP_AGC_PT0), 	UP(UpAE_WDR_CLP_AGC_PT1), 	UP(UpAE_WDR_CLP_AGC_PT2),\
															UP(UpAE_WDR_CLP_VAL_PT0), 	UP(UpAE_WDR_CLP_VAL_PT1), 	UP(UpAE_WDR_CLP_VAL_PT2));
															
		#else
		
		const int iWdrClipLvClr  = IntpValAgcPos(iCurTClr, 		UP(UpAE_WDR_CLP_AGC_PT0), 	UP(UpAE_WDR_CLP_AGC_PT1), 	UP(UpAE_WDR_CLP_AGC_PT2),\
															UP(UpAE_WDR_CLP_VAL_PT0), 	UP(UpAE_WDR_CLP_VAL_PT1), 	UP(UpAE_WDR_CLP_VAL_PT2));
		
		#if CAR_BB_FRONT
		int iWdrSliceLv  = IntpValAgcPos(iCurT, 		UP(UpAE_WDR_CLP_AGC_PT0), 	UP(UpAE_WDR_CLP_AGC_PT1), 	UP(UpAE_WDR_CLP_AGC_PT2),\
															0x0, 	0x10, 	0x10);
		#else
		int iWdrSliceLvClr  = IntpValAgcPos(iCurTClr, 		UP(UpAE_WDR_CLP_AGC_PT0), 	UP(UpAE_WDR_CLP_AGC_PT1), 	UP(UpAE_WDR_CLP_AGC_PT2),\
															0x0, 	0x20, 	0x20);
		//		iWdrSliceLv = MINMAX(iWdrSliceLv, 0x0, (iTgtL0>>1)-UP(UpAE_WDR_LSLIC_OFST));
		#endif

		#endif

		AE2_SLICEw(MINMAX(((int)((iTgtL0>>1)-iWdrSliceLvClr)), 0x0, (iTgtL0>>1)));
		
//		AE2_CLIPw(MIN(0x3FF, (iTgtL0 + UP(UpAE_WDR_LCLIP_OFST) + iWdrClipLv)));			// next long
//		AE2_CLIPw(MINMAX(UP(UpAE_WDR_LCLIP_OFST)+iWdrClipLv, iTgtL0, 0x3FF));									// next long
		
		// For Focus
		AE2_CLIPw(MINMAX(iWdrClipLvClr, iTgtL0, 0x3FF));						// next long		
	#endif
		}
	#endif	

	#if(model_Sens_LFM_HDR)
		else{
		iCurL0 = (int)((nAe2SlicCnt*nAe2SlicLvl) + nAe2Sum1 + (nAe2ClipCnt*nAe2ClipLvl)) / nAeWin2PxCnt;
		iTgtL0 = (AE_WDR_LTGT_GAIN * MP(MpBrightness)) + UP(UpAE_WDR_LTGT_OFST);

		// Decrease target value at low light
		nTgtDecrsVal = IntpValAgcPos(giCurAgc, 	UP(UpAE_WDR_LTGT_DCRS_AGC_PT0), UP(UpAE_WDR_LTGT_DCRS_AGC_PT1), UP(UpAE_WDR_LTGT_DCRS_AGC_PT2),\
												UP(UpAE_WDR_LTGT_DCRS_VAL_PT0), UP(UpAE_WDR_LTGT_DCRS_VAL_PT1), UP(UpAE_WDR_LTGT_DCRS_VAL_PT2));

		iTgtL0 = MAX((iTgtL0-nTgtDecrsVal), 0x0);
		iErrL0 = iTgtL0 - iCurL0;

		const int iWdrClipLv  = IntpValAgcPos(giCurAgc, 	UP(UpAE_WDR_CLP_AGC_PT0), 	UP(UpAE_WDR_CLP_AGC_PT1), 	UP(UpAE_WDR_CLP_AGC_PT2),\
															UP(UpAE_WDR_CLP_VAL_PT0), 	UP(UpAE_WDR_CLP_VAL_PT1), 	UP(UpAE_WDR_CLP_VAL_PT2));
		
		AE2_SLICEw(MAX(0x0, (iTgtL0>>1)-UP(UpAE_WDR_LSLIC_OFST)));
//		AE2_CLIPw(MIN(0x3FF, (iTgtL0 + UP(UpAE_WDR_LCLIP_OFST) + iWdrClipLv)));			// next long
		AE2_CLIPw(MINMAX(UP(UpAE_WDR_LCLIP_OFST)+iWdrClipLv, iTgtL0, 0x3FF));									// next long
		
		}
	#endif
		
	}
	else if (MP(MpBackLight)==MN_BL_BLC) {	// BLC Mode -------------------------------------

		iCurL0 = (nAe3Sum1 + (nAe3ClipCnt*nAe3ClipLvl)) / nAeWin3PxCnt;
//		iCur = (int)nSumMean1;
		iTgtL0 = (UP(UpAE_TGT_GAIN) * MP(MpBrightness)) + UP(UpAE_TGT_OFST);
		iErrL0 = iTgtL0 - iCurL0;

		/*#define iAE_CLIP_OFST UP(UpAE_CLIP_OFST)*/
		const int iAE_CLIP_OFST = AE_LED_ASAT_COND ?
									(MP(MpLedSatCtrl) > 10) ? (UP(UpAE_CLIP_OFST) * (40 - 3*(MP(MpLedSatCtrl)-10))) / 80 - 40 :
															(UP(UpAE_CLIP_OFST)>>1) : UP(UpAE_CLIP_OFST);

		AE3_CLIPw(iTgtL0 + iAE_CLIP_OFST);			//190121 LH : Bug correction
		AE3_SLICEw(0);		// 13.3.26

	}

	else {		// Normal Mode -------------------------------------------------------

		const int iAe2ClipCnt = LibUtlInterp1D(MP(MpHlMaskThrs)+8, 0, 28, 0, nAe2ClipCnt);
		if(MP(MpBackLight)==MN_BL_HLC)	iCurL0 = ((nAe2SlicCnt*nAe2SlicLvl) + nAe2Sum1 + (iAe2ClipCnt*nAe2ClipLvl)) / nAeWin2PxCnt;		//		"
		else							iCurL0 = ((nAe2SlicCnt*nAe2SlicLvl) + nAe2Sum1 + (nAe2ClipCnt*nAe2ClipLvl)) / nAeWin2PxCnt;		//		"


		iTgtL0 = (UP(UpAE_TGT_GAIN) * MP(MpBrightness)) + UP(UpAE_TGT_OFST);

		if(MP(MpBackLight)==MN_BL_HLC) 	iTgtL0 += (iTgtL0>>2);
		else{
			// Decrease target value at low light
			nTgtDecrsVal = IntpValAgcPos(giCurAgc, 	UP(UpAE_TGT_DCRS_AGC_PT0), 	UP(UpAE_TGT_DCRS_AGC_PT1), 	UP(UpAE_TGT_DCRS_AGC_PT2),\
													UP(UpAE_TGT_DCRS_VAL_PT0), 	UP(UpAE_TGT_DCRS_VAL_PT1), 	UP(UpAE_TGT_DCRS_VAL_PT2));
			iTgtL0 = MAX((iTgtL0-nTgtDecrsVal), 0x0);	
		}

		iErrL0 = iTgtL0 - iCurL0;

		const int iAE_CLIP_OFST = AE_LED_ASAT_COND ? (MP(MpLedSatCtrl) > 10) ? 	(UP(UpAE_CLIP_OFST) * (40 - 3*(MP(MpLedSatCtrl)-10))) / 80 - 40 :\
													 (UP(UpAE_CLIP_OFST)>>1) :\
													(((int)IntpValAgcPos(giCurAgc, 	UP(UpAE_CLP_AGC_PT0), 	UP(UpAE_CLP_AGC_PT1), 	UP(UpAE_CLP_AGC_PT2),\
																					UP(UpAE_CLP_VAL_PT0), 	UP(UpAE_CLP_VAL_PT1), 	UP(UpAE_CLP_VAL_PT2)))-iTgtL0);

		const int iSliceLv = AE_LED_ASAT_COND ? 0 : MAX(0x0, ((iTgtL0>>1)/*-(giCurAgc/3)*/-UP(UpAE_SLIC_OFST)));
//		const int iClipLv  = MIN(0x3FF, (iTgtL0 + iAE_CLIP_OFST));
		const int iClipLv  = MINMAX((iTgtL0 + iAE_CLIP_OFST) , iTgtL0, 0x3FF);

		AE2_SLICEw(iSliceLv);
		AE2_CLIPw(iClipLv);
	}

// ===================================================================================================================

// LED Control
	iErrL0 = LEDSatuCtrl(nAe2Sum1,nAe2Sum2,nAeWin2PxCnt, nAe2ClipCnt, nAe2ClipLvl, iErrL0, bWdrOn);		//210302 YTM


// Status manage ----------------------------------------------------------------------------------------------------------------------------

	//******************************************************************
	// Long position
	//******************************************************************
	iAePosLmt = MAX((iHssLmt + iIrsLmt + iAgcLmt + iLssLmt), 1);					// Total limit val

	if (gbWdrOnBuf!=bWdrOn) {// WDR change
		if (bWdrOn) 			 			 { giAePos = giShtValBuf;				gnAeState = 0;}
		else if (!bWdrOn)	{
			if (MP(MpIris)==MN_LENS_MNL) 	 { giAePos = MAX(iHssLmt-1,0);			gnAeState = 0;}
			else if (MP(MpIris)==MN_LENS_DC) { giAePos = MAX(iHssLmt+iIrsLmt-1, 0);	gnAeState = 1;}
		}
		gfAePosL0 = ifmul8(giAePos);	// 171211 LH : int floating
	}
	else if ((MP(MpIris)!=gbMnLensBuf)&&(!bWdrOn)) {// Lens change
		switch 	(gnAeState) {
			case 0 : giAePos = MAX(iHssLmt+iIrsLmt-1,0);	gnAeState = 1; 	break;
			case 1 : giAePos = MAX(iHssLmt-1,0);			gnAeState = 0;	break;
			case 2 : giAeValBuf = MIN(giAeValBuf, iAgcLmt); giAePos = iHssLmt + iIrsLmt + giAeValBuf; break;
			case 3 : giAeValBuf = MIN(giAeValBuf, iLssLmt+(int)gnAeHssTVal); giAePos = iIrsLmt + iAgcLmt + giAeValBuf; break;
		}
		gfAePosL0 = ifmul8(giAePos);	// 171211 LH : int floating
	}
	else if (iAePosLmt!=giAePosLmtBuf) {											// Limit val change
		switch 	(gnAeState) {
			case 0 : giAeValBuf = MIN(giAeValBuf, iHssLmt);					 giAePos = giAeValBuf; break;
			case 1 : giAeValBuf = MIN(giAeValBuf, iIrsLmt);					 giAePos = iHssLmt + giAeValBuf; break;
			case 2 : giAeValBuf = MIN(giAeValBuf, iAgcLmt);					 giAePos = iHssLmt + iIrsLmt + giAeValBuf; break;
			case 3 : giAeValBuf = MIN(giAeValBuf, iLssLmt+(int)gnAeHssTVal); giAePos = iIrsLmt + iAgcLmt + giAeValBuf; break;
		}
		gfAePosL0 = ifmul8(giAePos);	// 171211 LH : int floating
	}

	else if (gnAeState!=1) {
	//Error Equalizer
	#if(!Adaptive_led)														//210302 YTM
        // 171211 LH : int floating -----------------------------------------------
        gfAePosL0 += LibAeSpeed(iErrL0, AE_ERR_MGN, UP(UpAE_SPEED));		// 190527 PCB : New ae speed control function
        gfAePosL0  = MINMAX(gfAePosL0, 0, ifmul8(iAePosLmt-1) );
        giAePos    = ifdiv8(gfAePosL0);
        // -----------------------------------------------------------------------
    #endif
	}
	else {
        gfAePosL0 = ifmul8(giAePos);										// 171211 LH : int floating
	}


	gfAePosL0 = ALAeLedCtrl(iErrL0,gfAePosL0,iHssLmt+iIrsLmt,iAgcLmt,iAePosLmt);		// 210302 YTM
	if (gnAeState != 1)		giAePos = ifdiv8(gfAePosL0);								// 210302 YTM


// -------------------------------------------------------------
// 180910 JJH Adaptive Lighting
	//******************************************************************
	// Long state control
	//******************************************************************
#if (model_Iris_DC)
	if ((MP(MpShutter)!=MN_SHUT_MNL)&&((MP(MpIris)==MN_LENS_MNL)||(bWdrOn))&&(giAePos<iHssLmt)) {	//--// HSS status
#else
	if (((MP(MpShutter)!=MN_SHUT_MNL)||(bWdrOn))&&(giAePos<iHssLmt)) {
#endif
		// 171211 LH : int floating ------------------------------------
		gfAePosL0  = (MP(MpShutter)==MN_SHUT_FLICKER) ? ifmul8(AE_SHT_FLK) : 	// Shutter limit (Flicker)
						#if (AE_DEBLUR_FIX_ON==1)			// 170824 LH
						(AE_DEBLUR_COND&&(!bWdrOn)) ?	MAX(gfAePosL0, ifmul8(AE_DEBLUR_MIN)) :   	// 190312 LH
						#endif
						(gbModeWdrOn_L||gbModeWdrOn_CLR)	? (MAX(gfAePosL0, (int)(ifmul8(LibAeShtLine(gnAeLWdrMinL0)+LibAeShtLine(UP(UpAE_WDR_LONG_MIN)))))):
						(MAX(gfAePosL0, ifmul8(AE_SHT_SLICE)));	
						
		giAePos  	= ifdiv8(gfAePosL0);

		// ------------------------------------------------------------
		iShtValL0  	= giAePos;

		iIrsVal  	= (model_Iris_DC) ? 0 :	// full open
										0 ; // full close
		iAgcValL0  	= 0;

		giAeValBuf 	= iShtValL0;
		gnAeState  	= 0;
	}

#if (model_Iris_DC)
	else if ((MP(MpIris)==MN_LENS_DC)&&(!bWdrOn)&&(giAePos<(iHssLmt+iIrsLmt))) {	// 190312 LH	// -----------------// IRIS status

		if ((giAePos-iHssLmt) > (int)gnAeIrsTVal)	goto DoorMode;		// jump to shutter ctl range in Outdoor mode

		iIrsVal = LibAeSpeedDc(iErrL0, AE_ERR_MGN, AE_IRS_OPN_Max, AE_IRS_CLS_Max, UP(UpAE_SPEED_DC), 0);

		const int iErrOn   = ABS(iErrL0)>AE_ERR_MGN;
		const int iErrDif  = iErrL0-giErr2d;

		if (iErrOn) {
			// Position control (judge full open) -------------
			if (iErrL0>0) {
				if (iErrL0<=giErr2d)		giIrsPos += (9/*12*/ / ((iErrDif*iErrDif)+1))+1;		// open status
				else 					giIrsPos += 1;
			}
			else if (iErrL0<0) {
				if (iErrL0>=giErr2d)		giIrsPos -= (9/*12*/ / ((iErrDif*iErrDif)+1))+1;		// close status
				else 					giIrsPos -= 1;
			}
		}
		else {
			giIrsPos = ((giIrsPos * 240) + ((AE_IRS_STAT_Max/2) * (256-240))) >> 8;
		}

		giIrsPos = MINMAX(giIrsPos, 0, gnAeIrsTVal);
		giIrsValBuf = iIrsVal;


	DoorMode :
		if (!AE_OUTDOOR_COND) {

			gfIrsShtPos = 0;											// 171211 LH : int floating

			giAePos = MIN( iHssLmt + giIrsPos, (iHssLmt + iIrsLmt));
			giAeValBuf = giAePos - iHssLmt;

			iShtValL0 = iHssLmt;
		}
		else {

			// 171211 LH : int floating ------------------------------------
			if (giIrsPos >= (int)gnAeIrsTVal) {													// over full open
				gfIrsShtPos += LibAeSpeed_Irs(iErrL0, AE_ERR_MGN, UP(UpAE_SPEED)-42);			// 190822 PCB : IRIS speed control 
				gfIrsShtPos  = MINMAX(gfIrsShtPos, 0, (ifmul8(gnAeHssTVal-AE_OUTDOOR_THRS)));

				iIrsVal = MAX( (giIrsValBuf-(ifdiv8(gfIrsShtPos)<<1)), 0);							// increse open step
			}
			else gfIrsShtPos = 0;

			giAePos = MIN( iHssLmt + giIrsPos + ifdiv8(gfIrsShtPos), (iHssLmt + iIrsLmt));
			giAeValBuf = giAePos - iHssLmt;

			iShtValL0 = (int)AE_OUTDOOR_THRS + ifdiv8(gfIrsShtPos);
			iShtValL0 = MINMAX(iShtValL0, AE_OUTDOOR_THRS, (int)gnAeHssTVal);

			// -------------------------------------------------------------
		}

		iShtValL0 = (MP(MpShutter)==MN_SHUT_FLICKER) ? AE_SHT_FLK : iShtValL0;

		iIrsVal  = MINMAX(iIrsVal, 0, 0x3fe);
		iAgcValL0    = 0;

		gnAeState  = 1;
	}
#endif	// end of model_Iris_DC

	else if (giAePos<(iHssLmt+iIrsLmt+iAgcLmt)) {	// -----------------------------------------------------// AGC status
//	else {	// -----------------------------------------------------// AGC status

		iAgcValL0 = giAePos-(iHssLmt+iIrsLmt);
		iAgcValL0 = MAX(iAgcValL0, 0);

		#if (AE_DEBLUR_FIX_ON==0)			// 170824 LH
		
		#if(0)
		int iShtValOfst = (!AE_DEBLUR_COND) ? 0 :
						  (((((int)gnAeHssTVal-iHssLmt)<<8)/iAgcLmt) < ((UP(UpAE_DEBLUR_GAIN)<<8)/128)) ?		// compare gradient
						  ((iAgcValL0*UP(UpAE_DEBLUR_GAIN))/128) : ((iAgcValL0*((int)gnAeHssTVal-iHssLmt))/iAgcLmt);
		#else
		int iShtValOfst = ((!AE_DEBLUR_COND)&&(!gbModeWdrOn_L)) ? 0 :
						  (((((int)gnAeHssTVal-iHssLmt)<<8)/iAgcLmt) < ((UP(UpAE_DEBLUR_GAIN)<<8)/128)) ?		// compare gradient
						  ((iAgcValL0*UP(UpAE_DEBLUR_GAIN))/128) : ((iAgcValL0*((int)gnAeHssTVal-iHssLmt))/iAgcLmt);
		#endif
		
		
		#else
		int iShtValOfst = 0;
		#endif


		iShtValL0 = iHssLmt + iShtValOfst;
		iShtValL0 = MIN(iShtValL0,(int)gnAeHssTVal);
		iShtValL0 = (MP(MpShutter)==MN_SHUT_FLICKER) ? AE_SHT_FLK : iShtValL0;
			
		#if (model_Iris_DC)
			iIrsVal = ((MP(MpIris)==MN_LENS_DC) && (!AE_OUTDOOR_COND) && (!bWdrOn)) ? MAX( (giIrsValBuf-(iAgcValL0<<1)), 0) : 0;	// 190312 LH
		#endif

		giAeValBuf = iAgcValL0;
		gnAeState  = 2;
	}

#if(1)
	else {	// ---------------------------------------------------------------------------------------------// DSS status
		iShtValL0 = giAePos-(iIrsLmt+iAgcLmt);
		iShtValL0 = (MP(MpShutter)==MN_SHUT_FLICKER) ? MAX(iShtValL0, (int)iHssLmt) 	:	// 13.10.21
					  	(AE_DEBLUR_COND) 				 ?
					  									#if (AE_DEBLUR_FIX_ON==0)				// 170824 LH
					  									 MAX(iShtValL0, (int)gnAeHssTVal) 	:
					  									#else
					  									 MAX(iShtValL0, (int)iHssLmt) 		:
					  									#endif
					  									 MAX(iShtValL0, (int)iHssLmt)		;

		iIrsVal  	= (model_Iris_DC) ? 0 			: // full open
										gnAeIrsTVal ; // full open

		iAgcValL0 = iAgcLmt;

		giAeValBuf = iShtValL0;
		gnAeState  = 3;
	}
#else
	else{
		giAePos = MIN(giAePos, (iHssLmt+iIrsLmt+iAgcLmt));
		iShtValL0 = giAePos-(iIrsLmt+iAgcLmt);

		iAgcValL0 = iAgcLmt;
		giAeValBuf = iShtValL0;
	}
#endif
	
	// ----------------------------------------------------------------------------------------------------//

	if (gbModeWdrOn_L) {	// Short Tracking
	//******************************************************************
	// Short1 position
	//******************************************************************
	iAePosS1Lmt = MAX((iHssLmtS1 + iAgcLmtS1),1);								// S1 Total limit val

	if (gbWdrOnBuf!=bWdrOn) {													// WDR change
		if (bWdrOn) 			 			 {giAePosS1 = giShtValS1Buf;		gnAeStateS1 = 0;}
		gfAePosS1 = ifmul8(giAePosS1);
	}
	else if (iAePosS1Lmt!=giAePosS1LmtBuf) {									// Limit val change
		switch 	(gnAeStateS1) {
			case 0 : giAeValS1Buf = MIN(giAeValS1Buf, iHssLmtS1);				giAePosS1 = giAeValS1Buf; 				break;
			case 2 : giAeValS1Buf = MIN(giAeValS1Buf, iAgcLmtS1);				giAePosS1 = iHssLmtS1+ giAeValS1Buf; 	break;
		}
		gfAePosS1 = ifmul8(giAePosS1);
	}
      
		gfAePosS1 += LibAeSpeed(iErrS1, (AE_ERR_MGN), UP(UpAE_SPEED));
		gfAePosS1  = MINMAX(gfAePosS1, 0, ifmul8(iAePosS1Lmt-1) );
        giAePosS1  = ifdiv8(gfAePosS1);

	//******************************************************************
	// Short1 state control
	//******************************************************************
#if (model_Iris_DC)
	if ((MP(MpShutter)!=MN_SHUT_MNL)&&((MP(MpIris)==MN_LENS_MNL)||(bWdrOn))&&(giAePosS1<iHssLmtS1)) {	//--// HSS status
#else
	if (((MP(MpShutter)!=MN_SHUT_MNL)||(bWdrOn))&&(giAePosS1<iHssLmtS1)) {
#endif

//		iWdrSLmt	= LibUtlInterp1D ( MINMAX(giShtValBuf, (int)gnAeHssTVal-AE_WDR_LONG_TH_OFST, (int)gnAeHssTVal-1), (gnAeHssTVal-AE_WDR_LONG_TH_OFST), (gnAeHssTVal-1), (LibAeShtLine(gnAeLWdrMinS1)+AE_WDR_SHORT_MIN1), (LibAeShtLine(gnAeLWdrMinS1)+AE_WDR_SHORT_MIN2));	

		iWdrSLmt	= LibUtlInterp1D(MINMAX(giShtValBuf, 	(AE_LSHT_LMT_WDR-UP(UpAE_WDR_LONG_TH_OFST1)), (AE_LSHT_LMT_WDR-UP(UpAE_WDR_LONG_TH_OFST2))),\
									(AE_LSHT_LMT_WDR-UP(UpAE_WDR_LONG_TH_OFST1)), (AE_LSHT_LMT_WDR-UP(UpAE_WDR_LONG_TH_OFST2)),\
									(LibAeShtLine(gnAeLWdrMinS1)+LibAeShtLine(UP(UpAE_WDR_SHORT_MIN))), (LibAeShtLine(gnAeLWdrMinS1)+LibAeShtLine(AE_WDR_SHORT_MIN2)));

		gfAePosS1  = MAX(gfAePosS1, ifmul8(iWdrSLmt));																// 190214 LH	// over than short limit
		gfAePosS1  = MIN(gfAePosS1, (int)(ifmul8(LibAeShtLine(gnAeLWdrMaxS1))));
		giAePosS1  = ifdiv8(gfAePosS1);
		// ------------------------------------------------------------

		iShtValS1  	= giAePosS1;
		iAgcValS1  	= 0;

		giAeValS1Buf = iShtValS1;
		gnAeStateS1  = 0;
	}
	}

	//-------------------------------------------------------------------------------------
	// apply control val --------------
	gwAeSensAgcLmtNor = UP(UpAE_SENS_AGC_LMT);
	gwAeSensAgcLmtWdr = UP(UpAE_WDR_SENS_AGC_LMT);
	
	if (gbModeWdrOn_L) {
		
	#if (model_Sens_LWdr)
			AeSHT_LWDR(gbModeWdrOn_L, iShtValL0, iShtValS1);
			AeAGC_LWDR(gbModeWdrOn_L, iAgcValL0, iAgcValS1);
		#if model_Iris_DC
			AeIRS(0, 0, AE_IRS_CLS_Max);
		#endif

	#endif
	}
	#if (model_Sens_CLR_HDR)
		else if (gbModeWdrOn_CLR) {
			AeSHT_CHDR(iShtValL0);
			AeAGC_CHDR(iAgcValL0);
			#if model_Iris_DC
			AeIRS(0, 0, AE_IRS_CLS_Max);
			#endif
			
		}
	#endif
		
	else {
		gnSht_L 	= (UINT)AeSHT(iShtValL0, (MP(MpShutter)==MN_SHUT_MNL), (gnInModeVtw>>MP(MpShutSpd)));

		AeAGC(iAgcValL0);

		#if model_Iris_DC
			AeIRS(iIrsVal, 0, AE_IRS_CLS_Max);
		#endif
	}

// -------------------------------------------------------------------------------
// WDR control
	UINT nWDR_SGAIN = WDR_SGAINr;
	gbWdrOnBuf  = bWdrOn;
	
//	gwAeWdrSatLv = LibUtlInterp1D (MINMAX(giCurAgc, UP(UpAE_WDR_SATLV_AGC_PT0), UP(UpAE_WDR_SATLV_AGC_PT1)), UP(UpAE_WDR_SATLV_AGC_PT0), UP(UpAE_WDR_SATLV_AGC_PT1), UP(UpAE_WDR_SATLV_VAL_PT0), UP(UpAE_WDR_SATLV_VAL_PT1));
	gwAeWdrSatLv = LibUtlInterp1D (MINMAX((int)nWDR_SGAIN, UP(UpAE_WDR_SATLV_AGC_PT0), UP(UpAE_WDR_SATLV_AGC_PT1)), UP(UpAE_WDR_SATLV_AGC_PT0), UP(UpAE_WDR_SATLV_AGC_PT1), UP(UpAE_WDR_SATLV_VAL_PT0), UP(UpAE_WDR_SATLV_VAL_PT1));
	gwAeWdrWgt	 = LibUtlInterp1D (MINMAX(giCurAgc, UP(UpAE_WDR_LS_WGT_AGC_PT0), UP(UpAE_WDR_LS_WGT_AGC_PT1)), UP(UpAE_WDR_LS_WGT_AGC_PT0), UP(UpAE_WDR_LS_WGT_AGC_PT1), UP(UpAE_WDR_LS_WGT_VAL0), UP(UpAE_WDR_LS_WGT_VAL1));
	
	gbAeWdrTm	 = UP(UpAE_WDR_TMG_SEL);

	LibAeWdr (gbModeWdrOn_L, gbModeWdrOn_CLR, gnSht_L, gnSht_S1, gnAgc_L, gnAgc_S1, gwAeWdrWgt);

// -------------------------------------------------------------------------------

	gnAeErr = iErrL0;

	giErr2d = giErr1d;			
	giErr1d = iErrL0;

	giAePosLmtBuf = iAePosLmt;
	giShtValBuf = iShtValL0;
	giAgcValBuf = iAgcValL0;


	giAePosS1LmtBuf = iAePosS1Lmt;
	giShtValS1Buf = iShtValS1;
	giAgcValS1Buf = iAgcValS1;


	gnClipLvlBuf = nAe2ClipLvl;

	gbMnLensBuf	= MP(MpIris);
	gbMnSysFreqBuf = MP(MpSysFreq);

	giCurAgc = iAgcValL0;
	giCurAePos = giAePos;

//	if(gbEXUC_AgcFlag){
//		REG_ANC0_D04w(giCurAgc);
//	} 

	gwAesum_sht = iShtValL0;
	gbAesum_agc = MINMAX((0xFF - (giCurAgc*0xff/iAgcLmt)), 0x0, 0xFF);

// -------------------------------------------------------------------------------
// Black offset control
	//Used in function (Black Level offset)
	AeBlackOfst();
	
// -------------------------------------------------------------------------------
// Monitoring

#if(GRP_DEBUG_IMG_TUNE)
	GRP0 = iTgtL0;	
	GRP1 = iCurL0;	
	GRP2 = giCurAgc;
#endif
	
#if(model_Led==0)   //  180910 JJH Adaptive Lighting model_Led == 0
	DebugDisp((gbMnDebugFnc==7), Hex, "AGC_____", 0, 24, giCurAgc);
	DebugDisp((gbMnDebugFnc==7), Hex, "CDS_IN__", 1, 24, TDN_CDS_IN);
    DebugDisp((gbMnDebugFnc==7), Hex, "gnAeLed", 5, 24, gnAeLed);

    DebugDisp((gbMnDebugFnc==7), Hex, "target____", 10, 24, iTgtL0);
    DebugDisp((gbMnDebugFnc==7), Hex, "cur_______", 11, 24, iCurL0);
    DebugDisp((gbMnDebugFnc==7), Hex, "State_____", 12, 24, gnAeState);

    DebugDisp((gbMnDebugFnc==7), Hex, "POS_______", 16, 24, giAePos);
	
#endif

	DebugDisp(gbAeDebugOn, Hex, "target_L__",  8, 24, iTgtL0	  	)
	DebugDisp(gbAeDebugOn, Hex, "cur____L__",  9, 24, iCurL0 		)

	DebugDisp(gbAeDebugOn, Hex, "slice__L__", 10, 24, nAe2SlicLvl  	)
	DebugDisp(gbAeDebugOn, Hex, "clip___L__", 11, 24, nAe2ClipLvl  	)

	DebugDisp(gbAeDebugOn, Hex, "Pos_______", 13, 24, giAePos   	)
	DebugDisp(gbAeDebugOn, Hex, "PosLmt____", 14, 24, iAePosLmt 	)
	DebugDisp(gbAeDebugOn, Hex, "State_____", 15, 24, gnAeState   	)
	DebugDisp(gbAeDebugOn, Hex, "AePosSta__", 16, 24, giAeValBuf  	)
	DebugDisp(gbAeDebugOn, Hex, "CurAgc____", 17, 24, giCurAgc  	)

	DebugDisp(gbAeDebugOn, Hex, "Black_Lvl_", 19, 24, gnIncrsBlkLv	)
	DebugDisp(gbAeDebugOn, Hex, "PgOfs_____", 20, 24, PgOfs			)
		
	if(gbModeWdrOn_L||gbModeWdrOn_CLR){
	DebugDisp(gbAeDebugOn, Hex, "target_S__", 21, 24, iTgtS1	  	)
	DebugDisp(gbAeDebugOn, Hex, "cur____S__", 22, 24, iCurS1 		)

	DebugDisp(gbAeDebugOn, Hex, "slice__S__", 23, 24, nAe3SlicLvl  	)
	DebugDisp(gbAeDebugOn, Hex, "clip___S__", 24, 24, nAe3ClipLvl  	)
	
	DebugDisp(gbAeDebugOn, Hex, "WDR_SATLV_", 26, 24, (0xFFF+gwAeWdrSatLv))	
	DebugDisp(gbAeDebugOn, Hex, "WDR_SGAIN_", 27, 24, nWDR_SGAIN	)	
	DebugDisp(gbAeDebugOn, Hex, "WDR_LSWGT_", 28, 24, gwAeWdrWgt	)
	}
	
#if(model_Sens_LFM_HDR)
	DebugDisp(gbAeDebugOn, Hex, "giAePos___", 18, 24, giAePos		)
	DebugDisp(gbAeDebugOn, Hex, "SHT_SC_POS", 19, 24, AE_SHT_SLICE 	)
#endif

}


