/* **************************************************************************
 File Name	: 	app_ae_led.c
 Description	:	EN772 - AE-LED application
 Designer		:	Yu tae myung
 Date		:	19. 12. 18
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

//*******************************************************************************
// LED function variables
//*******************************************************************************
#if(Adaptive_led)
#if model_Led == 2 
		const UINT gnAE_LED_OFSMAX[10]	= { 1230000 ,  1230000	,  1230000	,	0,	 0,   0,   0,	0,	 0,   0};
		const UINT gnAE_LED_OFSMIN[10]	= { 3400	,  3000 	,  3000 	,	0,	 0,   0,   0,	0,	 0,   0};
		const UINT gnAE_LED_OFS[10] 	= { 2000	,  2000 	,  2000 	,	0,	 0,   0,   0,	0,	 0,   0};
		const BYTE gbAE_LED_DLY[10] 	= { 2		,  2		,  2		,	0,	 0,   0,   0,	0,	 0,   0};
		UINT gnAE_LED_HEP_Hz[10]		= { 0x44C	,  0x44C	,  0xFFF	,	0,	 0,   0,   0,	0,	 0,   0};				//210426 YTM
	#else
		const UINT gnAE_LED_OFSMAX[10]	= { 1230000 ,  1230000	,  1230000	,	0,	 0,   0,   0,	0,	 0,   0};
		const UINT gnAE_LED_OFSMIN[10]	= { 2000	,  23000	,  3000 	,	0,	 0,   0,   0,	0,	 0,   0};
		const UINT gnAE_LED_OFS[10] 	= { 1000	,  2000 	,  2000 	,	0,	 0,   0,   0,	0,	 0,   0};
		const BYTE gbAE_LED_DLY[10] 	= { 2		,  2		,  2		,	0,	 0,   0,   0,	0,	 0,   0};
		UINT gnAE_LED_HEP_Hz[10]		= { 0xFFF	,  0x44C	,  0xFFF	,	0,	 0,   0,   0,	0,	 0,   0};				//210426 YTM
	#endif

	const int giAE_AGC_LED_GAB=64;
		
	BYTE gbLedSel = 0;
	BYTE gbAE_LED_AePos_STOP = 0, gbAE_LED_TuningOn=0, gbAE_LED_TEST_RUN=0;
	WORD gwAE_LED_AGC=0, gwAE_LED_TEST_STEP=0, gwAE_LED_HEP_Hz=0;
	UINT gnAE_LED_LED = 0, gnAE_LED_TEST_MIN = 0, gnAE_LED_TEST_MAX = 0;
	UINT gnAE_LED_Avg=0, gnAE_LEDClip_Step=0xEA60;	 // 181130 JJH
	BYTE gbAE_LEDClip_Lv=50, gbAE_LED_Power=AE_LED_Power;
	BYTE gbLedDrvBuf = 0x0f, gbLedSwBuf = 0x0f;

	// 181017 JJH
	int giAE_LED_Pos_DIS_MIN=AE_LED_Pos_DIS_MIN, giAE_LED_Pos_DIS_MAX=AE_LED_Pos_DIS_MAX, giAE_LED_PosX=AE_LED_PosX , giAE_LED_PosY=AE_LED_PosY, giAE_LEDStart=AE_LEDStart; // 190610 JJH : LED start position
	const BYTE gbAE_AGC_DLY=AE_AGC_DLY;
		
	#define AE_LED_ON_TIME          5   // sec
		
	UINT gnTotalClkOfVLOCK = 0;

	UINT gnAesum1,gnAesum2,gnAeWin2Pxcnt,gnAe2ClipLvl;		//saturation control	


		// LED function  ---------------------------------------
void InitAeLed(void)
{
	
	AE5_SLICEw(0x0);			// led test window
	AE5_CLIPw(0x3ff);
	
	IRIS_ONw(0x1);
	IRIS_SWw(0x0);
	IRIS_MODw(0x1);
	IRIS_HSPw(0x0);
	IRIS_HEPw(1375);
	IRIS_VSPw(0x0);
	IRIS_VEPw(0xfff);
	
	IRIS_CLPLw(0x0);
	IRIS_CLPHw(0x0);			// Pulse Duty control : 1 ~ 1375 (full)
	
	IRIS_INVw(AE_LED_INVERT);
		
	gbLedSel = (model_Led==2);							//210112 YTM
	gnTotalClkOfVLOCK = 1237500;
		
	gnLedTotalclk = 74250000;													//210426 YTM : FPCK mode change

	extern void LibInitAeLed(const int, const BYTE, const BYTE); //181203
	LibInitAeLed(giAE_AGC_LED_GAB, gbAE_AGC_DLY, AE_LED_ON_TIME); //181203

}

void LedDriverChg(void)
{
    UINT nAE_LED_HEP_Hz = gnAE_LED_HEP_Hz[MP(MpLedDrv)];

    extern void LibLedDriverChg( UINT, const UINT, const UINT, const UINT, const BYTE);

    nAE_LED_HEP_Hz = nAE_LED_HEP_Hz;
    LibLedDriverChg(nAE_LED_HEP_Hz, gnAE_LED_OFSMAX[MP(MpLedDrv)], gnAE_LED_OFSMIN[MP(MpLedDrv)], gnAE_LED_OFS[MP(MpLedDrv)], gbAE_LED_DLY[MP(MpLedDrv)]);
}

#endif
//------------------------------------------------------------------------------------

int LEDSatuCtrl(UINT iAesum1, UINT iAesum2, UINT iAeWin2PxCnt, UINT nAe2ClipCnt, UINT nAe2ClipLvl, const int aiErrNow,const BYTE bWdrOn)
{
#if(0)
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
	AE2_HSPw(UP(UpAE2_HSP)+nAE2_HW_Gab);
	AE2_HEPw(UP(UpAE2_HEP)-nAE2_HW_Gab);
	AE2_VSPw(UP(UpAE2_VSP)+nAE2_VW_Gab);
	AE2_VEPw(UP(UpAE2_VEP)-nAE2_VW_Gab);
#endif

	#if(Adaptive_led)   //  180910 JJH Adaptive Lighting, model_Led == 0, PWM   190219 JJH		//210112 YTM						//210225 YTM
	    // JJH AL Update define->table
	    if(MP(MpLedSw)!=gbLedSwBuf)     IRIS_INVw(MP(MpLedSw));
	    if(MP(MpLedDrv)!=gbLedDrvBuf)   LedDriverChg();

	    gbLedSwBuf=MP(MpLedSw);
	    gbLedDrvBuf=MP(MpLedDrv);

	    gnAE_LED_Avg = ((iAesum1+iAesum2)/iAeWin2PxCnt);    // 181128 JJH

	    LibLedMenuChg();

		#if (model_Led == 2)																								//210112 YTM			//210225 YTM
			#define ALWAYS_FULL_COND	(MP(MpTdn)==MN_TDN_DAY)																							//210112 YTM
		#else																																			//210112 YTM
			#define ALWAYS_FULL_COND	(MP(MpTdn)==MN_TDN_NIGHT)																						//210112 YTM
		#endif																																			//210112 YTM
																																		
	    if(MP(MpAdaptive) != 1)   //  MpAdaptive adaptive : 1 full : 2
	    {
	        if(((gnTdnChkOut==TDN_NIT) || ALWAYS_FULL_COND) && (MP(MpTdn)!=MN_TDN_AUTO) && (MP(MpAdaptive)==2) ) {
	            LibLED_SET(gnAE_LED_OFSMAX[MP(MpLedDrv)],102);
	        }
	        else {
	            LibLED_SET(0,11);
	        }
	    }

	#else
		UNUSED_ARG(iAesum1);
		#if((model_Led==1))                 // 190514 JJH : model_LED Option			//FULL LED														//210225 YTM

		 	if (((MP(MpTdn)==MN_TDN_NIGHT)||(MP(MpTdn)==MN_TDN_EXTERN)) && MP(MpAdaptive) && (gnTdnChkOut==TDN_NIT) )   AE_LED_ON			//210112 YTM
			
		    else                                                                                                          AE_LED_OFF
		#endif
	#endif
	//210302 YTM 
	// Saturation detector
	gnAeLedWgtBit_Max 	= AE_LED_MAX_SHIFT_BIT;
	gnAeLedWgtBit_Min 	= AE_LED_MIN_SHIFT_BIT;
	gnAeLedTgt_Ofst 	= AE_LED_TGT_GAIN_FIX;
	gnAeLedErrLmt_flag 	= model_Iris_DC && ((MP(MpIris)==MN_LENS_DC)&&(MP(MpDcMode)==MN_DC_DEBLUR));
	gnAeLedDeblur_flag 	= AE_DEBLUR_COND;
	gbAeLedSatCtrl		= MP(MpLedSatCtrl);

	return LibAeLedErrChg(AE_LED_ASAT_COND, aiErrNow, iAesum2, nAe2ClipCnt, nAe2ClipLvl, iAeWin2PxCnt);// 210302 YTM
}

int ALAeLedCtrl(const int aiErrNow, int afAePosflt, const int aiOfs, const int aiAgcMax, int iAePosLmt)
{
	int iAePosLBuf;
	
	#if(Adaptive_led)	
		int aiAepos;
	
		AE5_WIN_CHw(0);									//ALAeWindowCtrl
		AE5_HSPw(UP(UpAE2_HSP)+0x100);					//ALAeWindowCtrl
		AE5_HEPw(UP(UpAE2_HEP)-0x100);					//ALAeWindowCtrl
		AE5_VSPw(UP(UpAE2_VSP)+100);					//ALAeWindowCtrl
		AE5_VEPw(UP(UpAE2_VEP)-0x100);					//ALAeWindowCtrl

		#if(model_5M)														//210426 YTM : FPCK mode change
			gnLedTotalclk = 148500000;										//210426 YTM : FPCK mode change
		#else																//210426 YTM : FPCK mode change
			gnLedTotalclk = (gbInModeRes) ? 148500000 : 74250000 ;			//210426 YTM : FPCK mode change
		#endif

		
		if(gnAeState != 1) {
			iAePosLBuf = LibAeLedCtrl(aiErrNow, afAePosflt, aiOfs, aiAgcMax, AE_ERR_MGN, UP(UpAE_SPEED));
			iAePosLBuf = MINMAX(iAePosLBuf, 0, ifmul8(iAePosLmt-1) );
			aiAepos = ifdiv8(iAePosLBuf);

			if(gbAE_LED_TuningOn&&(gbMnDebugFnc==7)){
            	GRP3 = (int)aiAepos;
            	GRP1 = (int)aiAepos - aiOfs;
        	}
		}
		else {
			
			LibLedIrisChg();
			iAePosLBuf = afAePosflt;
		}


		if(gbAE_LED_TuningOn&&(gbMnDebugFnc==7))	    		LibAeLedTest();
	
		DebugDisp((gbMnDebugFnc==7), Hex, "AGC_____", 0, 24, giCurAgc);
		DebugDisp((gbMnDebugFnc==7), Hex, "CDS_IN__", 1, 24, TDN_CDS_IN);
		DebugDisp((gbMnDebugFnc==7), Hex, "gnAeLed", 5, 24, gnAeLed);
		DebugDisp((gbMnDebugFnc==7), Hex, "State_____", 12, 24, gnAeState);
	#else
		UNUSED_ARG(aiErrNow);
		UNUSED_ARG(aiOfs);
		UNUSED_ARG(aiAgcMax);
		UNUSED_ARG(iAePosLmt);
		
		iAePosLBuf = afAePosflt;
	#endif

	return iAePosLBuf;
}
