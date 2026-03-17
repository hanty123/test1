/* **************************************************************************
 File Name	: 	app_etc.c
 Description	:	EN772 - etc. Functions
 Designer		:	Lee, Gyu Hong
 Date		:	21. 03. 10
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */
#include "dev.h"
#include "app_etc_tbl.h"

//*************************************************************************************************
// Variables
//-------------------------------------------------------------------------------------------------

//*************************************************************************************************
// Functions
//-------------------------------------------------------------------------------------------------

void ISPM2 Adnr(void)			// 180104 LH
{	// Digital noise reduction

	//DNR
	UINT i = 0;
	int iAgcPos_Q, iAgcPos_G;
	UINT nQtbl_ev, nQtbl_od = 0;
	WORD wAgcPt0, wAgcPt1, wAgcPt2;
	BYTE bDNR_LV0_Gain = 0, bDNR_LV1_Gain = 0, bDNR_LV2_Gain = 0;

	DNR2D_ONw((MP(MpAdnr)!=MN_OFF));

	wAgcPt1 = (MODE_WDR_ON)?(UP(UpDNR_WDR_AGC_PT1)):(UP(UpDNR_AGC_PT1));
	wAgcPt2 = (MODE_WDR_ON)?(UP(UpDNR_WDR_AGC_PT2)):(UP(UpDNR_AGC_PT2));
	wAgcPt0 = (MODE_WDR_ON)?(UP(UpDNR_WDR_AGC_PT0)):(UP(UpDNR_AGC_PT0));
	
	//Q Table Write
	iAgcPos_Q = (giCurAgc<=wAgcPt0) ? 0 :
			  	(giCurAgc<=wAgcPt1) ? 1 :
			  	(giCurAgc<=wAgcPt2) ? 2 : 3;

	for(i=0; i < DNR_Q_TBL_NUM; i++)	{
		
		switch(iAgcPos_Q){
			case 0	: 	nQtbl_ev = (Adnr2D_Tbl_Q1[i] >> 16) + UP(UpDNR_AGC_OFST_PVAL0) - UP(UpDNR_AGC_OFST_MVAL0);	
						nQtbl_od = ((Adnr2D_Tbl_Q1[i] & 0x1FFF) + UP(UpDNR_AGC_OFST_PVAL0) - UP(UpDNR_AGC_OFST_MVAL0));
						break;
						
			case 1	:	nQtbl_ev = LibUtlInterp1D (giCurAgc, wAgcPt0, wAgcPt1, ((Adnr2D_Tbl_Q1[i] >> 16) + UP(UpDNR_AGC_OFST_PVAL0) - UP(UpDNR_AGC_OFST_MVAL0)), 		((Adnr2D_Tbl_Q5[i] >> 16) + UP(UpDNR_AGC_OFST_PVAL1) - UP(UpDNR_AGC_OFST_MVAL1)));
						nQtbl_od = LibUtlInterp1D (giCurAgc, wAgcPt0, wAgcPt1, ((Adnr2D_Tbl_Q1[i] & 0x1FFF) + UP(UpDNR_AGC_OFST_PVAL0) - UP(UpDNR_AGC_OFST_MVAL0)), 	((Adnr2D_Tbl_Q5[i] & 0x1FFF)+ UP(UpDNR_AGC_OFST_PVAL1) - UP(UpDNR_AGC_OFST_MVAL1)));
						break;

			case 2	:	nQtbl_ev = LibUtlInterp1D (giCurAgc, wAgcPt1, wAgcPt2, ((Adnr2D_Tbl_Q5[i] >> 16) + UP(UpDNR_AGC_OFST_PVAL1) - UP(UpDNR_AGC_OFST_MVAL1)), 		((Adnr2D_Tbl_Q10[i] >> 16) + UP(UpDNR_AGC_OFST_PVAL2) - UP(UpDNR_AGC_OFST_MVAL2)));
						nQtbl_od = LibUtlInterp1D (giCurAgc, wAgcPt1, wAgcPt2, ((Adnr2D_Tbl_Q5[i] & 0x1FFF) + UP(UpDNR_AGC_OFST_PVAL1) - UP(UpDNR_AGC_OFST_MVAL1)), 	((Adnr2D_Tbl_Q10[i] & 0x1FFF) + UP(UpDNR_AGC_OFST_PVAL2) - UP(UpDNR_AGC_OFST_MVAL2)));
						break;

			case 3	: 	nQtbl_ev = (Adnr2D_Tbl_Q10[i] >> 16) + UP(UpDNR_AGC_OFST_PVAL2) - UP(UpDNR_AGC_OFST_MVAL2);	
						nQtbl_od = ((Adnr2D_Tbl_Q10[i] & 0x1FFF) + UP(UpDNR_AGC_OFST_PVAL2) - UP(UpDNR_AGC_OFST_MVAL2));
						break;
						
			default : 	nQtbl_ev = (Adnr2D_Tbl_Q1[i] >> 16) + UP(UpDNR_AGC_OFST_PVAL0) - UP(UpDNR_AGC_OFST_MVAL0);	
						nQtbl_od = ((Adnr2D_Tbl_Q1[i] & 0x1FFF) + UP(UpDNR_AGC_OFST_PVAL0) - UP(UpDNR_AGC_OFST_MVAL0));
						break;
		}

		nQtbl_ev = MAX(nQtbl_ev, 1);
		nQtbl_od = MAX(nQtbl_od, 1);

		//MENU Control
		SetIsp((0x192+i), (nQtbl_ev<<16)|nQtbl_od);
	}

	// DNR LV1 GAIN
	iAgcPos_G = (giCurAgc<=UP(UpDNR_AGC_HPF_PT0)) ? 0 :
			  	(giCurAgc<=UP(UpDNR_AGC_HPF_PT1)) ? 1 :
			  	(giCurAgc<=UP(UpDNR_AGC_HPF_PT2)) ? 2 : 3;
		
	switch(iAgcPos_G){
		case 0	: 	bDNR_LV0_Gain = UP(UpDNR_HPF_GAIN_LV0_PT0);
					bDNR_LV1_Gain = UP(UpDNR_HPF_GAIN_LV1_PT0);
					bDNR_LV2_Gain = UP(UpDNR_HPF_GAIN_LV2_PT0);																														
					break;
					
		case 1	:	bDNR_LV0_Gain = LibUtlInterp1D (giCurAgc, UP(UpDNR_AGC_HPF_PT0), UP(UpDNR_AGC_HPF_PT1), UP(UpDNR_HPF_GAIN_LV0_PT0), UP(UpDNR_HPF_GAIN_LV0_PT1));
					bDNR_LV1_Gain = LibUtlInterp1D (giCurAgc, UP(UpDNR_AGC_HPF_PT0), UP(UpDNR_AGC_HPF_PT1), UP(UpDNR_HPF_GAIN_LV1_PT0), UP(UpDNR_HPF_GAIN_LV1_PT1));	
					bDNR_LV2_Gain = LibUtlInterp1D (giCurAgc, UP(UpDNR_AGC_HPF_PT0), UP(UpDNR_AGC_HPF_PT1), UP(UpDNR_HPF_GAIN_LV2_PT0), UP(UpDNR_HPF_GAIN_LV2_PT1));	
					break;
					
		case 2	:	bDNR_LV0_Gain = LibUtlInterp1D (giCurAgc, UP(UpDNR_AGC_HPF_PT1), UP(UpDNR_AGC_HPF_PT2), UP(UpDNR_HPF_GAIN_LV0_PT1), UP(UpDNR_HPF_GAIN_LV0_PT2));
					bDNR_LV1_Gain = LibUtlInterp1D (giCurAgc, UP(UpDNR_AGC_HPF_PT1), UP(UpDNR_AGC_HPF_PT2), UP(UpDNR_HPF_GAIN_LV1_PT1), UP(UpDNR_HPF_GAIN_LV1_PT2));
					bDNR_LV2_Gain = LibUtlInterp1D (giCurAgc, UP(UpDNR_AGC_HPF_PT1), UP(UpDNR_AGC_HPF_PT2), UP(UpDNR_HPF_GAIN_LV2_PT1), UP(UpDNR_HPF_GAIN_LV2_PT2));	
					break;
					
		case 3	: 	bDNR_LV0_Gain = UP(UpDNR_HPF_GAIN_LV0_PT2);
					bDNR_LV1_Gain = UP(UpDNR_HPF_GAIN_LV1_PT2);																					
					bDNR_LV2_Gain = UP(UpDNR_HPF_GAIN_LV2_PT2);
					break;
					
		default : 	bDNR_LV0_Gain = 0x0;
					bDNR_LV1_Gain = 0x0;																					
					bDNR_LV2_Gain = 0x0;																														
					break;
	}
	
	DNR2D_LVL0_GAINw(bDNR_LV0_Gain);
	DNR2D_LVL1_GAINw(bDNR_LV1_Gain);
	DNR2D_LVL2_GAINw(bDNR_LV2_Gain);

	ModeSdiAnc();	// AP-3DNR

	//for debugging
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "AGC_____",  0, 24, giCurAgc 	);

//	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "DNR_Q00_", 	8, 24, ((GetIsp(0x192)>>16)&0x1FFF));
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "DNR_Q00_", 2, 24, (GetIsp(0x192)&0x1FFF));
	
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "DNR_POS_",  4, 24, (iAgcPos_Q<<16)|(iAgcPos_G));
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "DNR_PT0_",  5, 24,  wAgcPt0);
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "DNR_PT1_",  6, 24,  wAgcPt1);
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "DNR_PT2_",  7, 24,  wAgcPt2);
	
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "DNR_LV0_",  9, 24, 	bDNR_LV0_Gain);
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "DNR_LV1_", 10, 24, 	bDNR_LV1_Gain);
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "DNR_LV2_", 11, 24, 	bDNR_LV2_Gain);
}


//-------------------------------------------------------------------------------------------------

void ISPM2 Sharpness(void)
{	
	// Aperture
	int i55Th1, i55Th2, i55Th3;
	int i55Gain1N, i55Gain2N, i55Gain1P, i55Gain2P, i33Slic, i33Clip, i33Gain;
	WORD wAgcPt0, wAgcPt1, wAgcPt2;
	BYTE bSharpness = MP(MpSharpness);
	BYTE bShpGain = 0;

	bShpGain = ((!MODE_CVBS_ON)?(UP(UpSHARPNESS_GAIN)):(UP(UpSHARPNESS_GAIN_CVBS)));
	bShpGain = MAX(1, bShpGain);

	APT_ONw(1);
	APT_GAIN_ONw(1);

	wAgcPt0 = (MODE_WDR_ON)?(UP(UpSHP_WDR_AGC_PT0)):(UP(UpSHP_AGC_PT0));
	wAgcPt1 = (MODE_WDR_ON)?(UP(UpSHP_WDR_AGC_PT1)):(UP(UpSHP_AGC_PT1));
	wAgcPt2 = (MODE_WDR_ON)?(UP(UpSHP_WDR_AGC_PT2)):(UP(UpSHP_AGC_PT2));

	// SHARPNESS
	i55Th1 = IntpValAgcPos(giCurAgc, wAgcPt0, wAgcPt1, wAgcPt2, UP(UpAPT55_TH1_PT0), UP(UpAPT55_TH1_PT1), UP(UpAPT55_TH1_PT2));
	i55Th2 = IntpValAgcPos(giCurAgc, wAgcPt0, wAgcPt1, wAgcPt2, UP(UpAPT55_TH2_PT0), UP(UpAPT55_TH2_PT1), UP(UpAPT55_TH2_PT2));
	i55Th3 = IntpValAgcPos(giCurAgc, wAgcPt0, wAgcPt1, wAgcPt2, UP(UpAPT55_TH3_PT0), UP(UpAPT55_TH3_PT1), UP(UpAPT55_TH3_PT2));

	i55Gain1N = IntpValAgcPos(giCurAgc, wAgcPt0, wAgcPt1, wAgcPt2, UP(UpAPT55_GAIN1N_PT0), UP(UpAPT55_GAIN1N_PT1), UP(UpAPT55_GAIN1N_PT2));
	i55Gain2N = IntpValAgcPos(giCurAgc, wAgcPt0, wAgcPt1, wAgcPt2, UP(UpAPT55_GAIN2N_PT0), UP(UpAPT55_GAIN2N_PT1), UP(UpAPT55_GAIN2N_PT2));
	i55Gain1P = IntpValAgcPos(giCurAgc, wAgcPt0, wAgcPt1, wAgcPt2, UP(UpAPT55_GAIN1P_PT0), UP(UpAPT55_GAIN1P_PT1), UP(UpAPT55_GAIN1P_PT2));
	i55Gain2P = IntpValAgcPos(giCurAgc, wAgcPt0, wAgcPt1, wAgcPt2, UP(UpAPT55_GAIN2P_PT0), UP(UpAPT55_GAIN2P_PT1), UP(UpAPT55_GAIN2P_PT2));
	
	i33Slic = IntpValAgcPos(giCurAgc, wAgcPt0, wAgcPt1, wAgcPt2, UP(UpAPT33_SLIC_PT0), UP(UpAPT33_SLIC_PT1), UP(UpAPT33_SLIC_PT2));
	i33Clip = IntpValAgcPos(giCurAgc, wAgcPt0, wAgcPt1, wAgcPt2, UP(UpAPT33_CLIP_PT0), UP(UpAPT33_CLIP_PT1), UP(UpAPT33_CLIP_PT2));

	i33Gain = IntpValAgcPos(giCurAgc, wAgcPt0, wAgcPt1, wAgcPt2, UP(UpAPT33_GAIN_PT0), UP(UpAPT33_GAIN_PT1), UP(UpAPT33_GAIN_PT2));


	// Calculation SHARPNESS GAIN
	i55Gain1N = i55Gain1N * bSharpness / bShpGain;
	i55Gain1N = MIN(i55Gain1N, 0xff);

	i55Gain2N = i55Gain2N * bSharpness / bShpGain;
	i55Gain2N = MIN(i55Gain2N, 0xff);

	i55Gain1P = i55Gain1P * bSharpness / bShpGain;
	i55Gain1P = MIN(i55Gain1P, 0xff);

	i55Gain2P = i55Gain2P * bSharpness / bShpGain;
	i55Gain2P = MIN(i55Gain2P, 0xff);
	
	i33Gain = i33Gain * bSharpness / bShpGain;
	i33Gain = MIN(i33Gain, 0xff);

	// Write Register
//	APT_TH1w((i55Th1*0x10));
//	APT_TH2w((i55Th2*0x10));
	APT_TH1w(i55Th1);
	APT_TH2w(i55Th2);
	APT_TH3w(i55Th3);

	APT_GAIN1_POSw(i55Gain1P);
	APT_GAIN1_NEGw(i55Gain1N);

	APT_GAIN2_POSw(i55Gain2P);
	APT_GAIN2_NEGw(i55Gain2N);
	
//	APT_SLIC3w((i33Slic*0x10));
	APT_SLIC3w(i33Slic);
	APT_CLIP3w(i33Clip);
	APT_GAIN3w(i33Gain);

	// LPF Filter 
	APT_LPFKw(0xF0);
	APT_LPFGAw(0x80);
	APT_LPFTHw(0x8);

	//for debugging
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "SHP_PT0_", 14, 24, wAgcPt0);
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "SHP_PT1_", 15, 24, wAgcPt1);
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "SHP_PT2_", 16, 24, wAgcPt2);

	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "5x5_GAP1", 18, 24, i55Gain1P );
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "5x5_GAN1", 19, 24, i55Gain1N	);
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "5x5_GAP2", 20, 24, i55Gain2P );
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "5x5_GAN2", 21, 24, i55Gain2N	);
	
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "5x5_TH1_", 22, 24, i55Th1	);
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "5x5_TH2_", 23, 24, i55Th2	);
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "5x5_TH3_", 24, 24, i55Th3	);
	
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "3x3_GAIN", 26, 24, i33Gain 	);
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "3x3_SLIC", 27, 24, i33Slic   );
	DebugDisp((gbMnDebugFnc==MN_DBG_4), , "3x3_CLIP", 28, 24, i33Clip 	);
}

//-------------------------------------------------------------------------------------------------
void ISPM2 CSup(void)			// 180104 LH
{
	// Low light color suppression ----------------------------
	#if (0)
		int iGain=0;
		int iAgcPos;

		iAgcPos = (giCurAgc<=COMMON_AGC_PT0) ? 0 :
				  (giCurAgc<=COMMON_AGC_PT1) ? 1 :
				  (giCurAgc<=COMMON_AGC_PT2) ? 2 : 3;

		switch (iAgcPos) {
			case 0 :	iGain 	= LowCSupGaTbl[0];	break;
			case 1 :	iGain 	= LibUtlInterp1D (giCurAgc, COMMON_AGC_PT0, COMMON_AGC_PT1, LowCSupGaTbl[0], LowCSupGaTbl[1]); break;
			case 2 :	iGain 	= LibUtlInterp1D (giCurAgc, COMMON_AGC_PT1, COMMON_AGC_PT2, LowCSupGaTbl[1], LowCSupGaTbl[2]); break;
			case 3 :	iGain 	= LowCSupGaTbl[2];	break;
		}

		iGain = MIN((iGain * UP(UpLSUP_GA))>>7, 0x3F);	// 15.06.13 KSH

		LSUP_ONw(UP(UpLSUP_ON));
		LSUP_GAw(iGain);
		LSUP_THw(UP(UpLSUP_TH));						//HTY 20150613
	//	DispDat("LSUP_GAw"	,  9, 0, iGain);
	#else
		int iLSupGa = 0;
	
		iLSupGa = LibUtlInterp1D (MINMAX(giCurAgc, UP(UpLSUP_GA_AGC_PT0), UP(UpLSUP_GA_AGC_PT1)), UP(UpLSUP_GA_AGC_PT0), UP(UpLSUP_GA_AGC_PT1), UP(UpLSUP_GA_VAL_PT0), UP(UpLSUP_GA_VAL_PT1));
	
		LSUP_ONw(UP(UpLSUP_ON));
		LSUP_GAw(iLSupGa);
		LSUP_THw(UP(UpLSUP_TH));
		
	#endif

	#if(0)
	// High light color suppression ----------------------------
	CSUP_ONw(UP(UpCSUP_ON));						//HTY 20150613
	iGain = MIN((UP(UpCSUP_GA) * UP(UpLSUP_GA))>>7, 0x3F);// 15.06.13 KSH
	CSUP_GAw(iGain);								// 15.06.13 KSH
	CSUP_THw(UP(UpCSUP_TH));

	// Edge color suppression -------------------------------
	CES_ONw(UP(UpCES_ON));
	
	CES_GAINw(UP(UpCES_GA));
	CES_LCLIPw(UP(UpCES_LCLIP));
	#else
	// High light color suppression ----------------------------
	int iCSupTh = 0;
	
	iCSupTh = LibUtlInterp1D (MINMAX(giCurAgc, UP(UpCSUP_TH_AGC_PT0), UP(UpCSUP_TH_AGC_PT1)), UP(UpCSUP_TH_AGC_PT0), UP(UpCSUP_TH_AGC_PT1), UP(UpCSUP_TH_VAL_PT0), UP(UpCSUP_TH_VAL_PT1));
	
	CSUP_ONw(UP(UpCSUP_ON));						//HTY 20150613
	CSUP_GAw(MIN(UP(UpCSUP_GA), 0x3F));
	CSUP_THw(iCSupTh);

	// Edge color suppression -------------------------------
	int iCESupTh = 0;
	
	iCESupTh = LibUtlInterp1D (MINMAX(giCurAgc, UP(UpCES_TH_AGC_PT0), UP(UpCES_TH_AGC_PT1)), UP(UpCES_TH_AGC_PT0), UP(UpCES_TH_AGC_PT1), UP(UpCES_TH_VAL_PT0), UP(UpCES_TH_VAL_PT1));
	
	CES_ONw(UP(UpCES_ON));
	CES_GAINw(UP(UpCES_GA));
	CES_LCLIPw(iCESupTh);
	#endif
}

//-------------------------------------------------------------------------------------------------
void ISPM2 HlMask(void)
{	// High Light Mask	
	
	UINT nPRVC_CY=0, nPRVC_CB=0, nPRVC_CR=0;

	if (MP(MpBackLight)==MN_BL_HLC) {
		HLMASK_ONw(1);
		HLMASK_THw(50+(MP(MpHlMaskThrs)*UP(UpHLMASK_THRS_STEP)));
		switch (MP(MpHlMaskColor)) {
			case 0x0	: nPRVC_CY = 235;            	// WHT
						  nPRVC_CB = 128;
						  nPRVC_CR = 128;	break;
			case 0x1	: nPRVC_CY = 218;				// YEL
						  nPRVC_CB =   8;
						  nPRVC_CR = 139;	break;
			case 0x2	: nPRVC_CY = 185;				// CYN
						  nPRVC_CB = 155;
						  nPRVC_CR =   8;	break;
			case 0x3	: nPRVC_CY = 168;				// GRN
						  nPRVC_CB =  35;
						  nPRVC_CR =  19;	break;
			case 0x4	: nPRVC_CY =  67;				// MAG
						  nPRVC_CB = 221;
						  nPRVC_CR = 237;	break;
			case 0x5	: nPRVC_CY =  50;				// RED
						  nPRVC_CB = 101;
						  nPRVC_CR = 248;	break;
			case 0x6	: nPRVC_CY =  17;				// BLU
						  nPRVC_CB = 248;
						  nPRVC_CR = 117;	break;
			case 0x7	: nPRVC_CY =   0;				// BLK
						  nPRVC_CB = 128;
						  nPRVC_CR = 128;	break;
			default		: nPRVC_CY = UP(UpHLMASK_CY);	// CUSTOMIZE
						  nPRVC_CB = UP(UpHLMASK_CB);
						  nPRVC_CR = UP(UpHLMASK_CR);
						  					break;
		}
		HLMASK_YLVw(nPRVC_CY);
		HLMASK_RLVw(nPRVC_CR);
		HLMASK_BLVw(nPRVC_CB);
	}
	else HLMASK_ONw(0);


}

//-------------------------------------------------------------------------------------------------
void ISPM2 Mirror(void)
{	// Mirror
	if (MIRROR_ON)	MIR_ON;
	else			MIR_OFF;
}

//-------------------------------------------------------------------------------------------------
void ISPM2 Flip(void)
{	// Flip
	if (FLIP_ON)	FLP_ON;
	else			FLP_OFF;
}


//-------------------------------------------------------------------------------------------------
void ISPM2 ColorBar(void)
{	// Color bar display
	if (MP(MpCBar)==1) {
		// Digital Output
		DCBAR_ONw(1);
		DCBAR_HWw(DCBAR_HW);
		DCBAR_STw(DCBAR_ST);

		// Analog Output
		TEST_ONw(1);
	}
	else {
		DCBAR_ONw(0);

		// Analog Output
		TEST_ONw(0);
	}
}

//-------------------------------------------------------------------------------------------------
void ISPM2 ColorSpace(void)
{ 	// Color space setup
	switch(MP(MpOutFormat)) {
		case MN_FRMT_UV :	RMYRw(0x276);RMYGw(0x20F);RMYBw(0x66);BMYRw(0x97);BMYGw(0x128);BMYBw(0x1BE); break;
		case MN_FRMT_SD :	RMYRw(0x20B);RMYGw(0x1B6);RMYBw(0x55);BMYRw(0xB0);BMYGw(0x15B);BMYBw(0x20B); break;
		case MN_FRMT_HD :	RMYRw(0x20B);RMYGw(0x1DB);RMYBw(0x30);BMYRw(0x78);BMYGw(0x193);BMYBw(0x20B); break;
	}
}

//-------------------------------------------------------------------------------------------------
void ISPM2 ImageRange(void)
{ 	// Image Range
	// Output scale ----------------------------------------------------------------
		#define PEDESTAL_LV_MAX 0x50

		BYTE bLAST_YGAIN, bLAST_YOFFS, bLAST_YCLIP, bLAST_YSLIC, bLAST_CGAIN, bLAST_CCLIP;
		WORD wPEDESTAL_LV;

		if (MP(MpOutScl)==MN_OUTSCL_FULL) {									// 100% data
			bLAST_YGAIN = MIN(OUTSCL_FULL_YGAIN, 0xff);
			bLAST_YOFFS = OUTSCL_FULL_YOFST;
			bLAST_YCLIP = OUTSCL_FULL_YCLIP;
			bLAST_YSLIC = OUTSCL_FULL_YSLIC;
			bLAST_CGAIN = MIN(OUTSCL_FULL_CGAIN, 0xff);
	        bLAST_CCLIP = OUTSCL_FULL_CCLIP;

			wPEDESTAL_LV = 0;
		}

		else if (MP(MpOutScl)==MN_OUTSCL_COMP) {							// 75% data ?
			bLAST_YGAIN = MIN(OUTSCL_COMP_YGAIN, 0xff);
			bLAST_YOFFS = OUTSCL_COMP_YOFST;
			bLAST_YCLIP = OUTSCL_COMP_YCLIP;
	   		bLAST_YSLIC = OUTSCL_COMP_YSLIC;
			bLAST_CGAIN = MIN(OUTSCL_COMP_CGAIN, 0xff);
	        bLAST_CCLIP = OUTSCL_COMP_CCLIP;


			wPEDESTAL_LV = PEDESTAL_LV_MAX>>1;
		}
		else {
			bLAST_YGAIN = MIN(((128 - (MP(MpOutSclUser)>>1))), 0xff);
			bLAST_YOFFS = MP(MpOutSclUser);
			bLAST_YCLIP = OUTSCL_FULL_YCLIP;
	   		bLAST_YSLIC = OUTSCL_FULL_YSLIC;
			bLAST_CGAIN = MIN(((128 - (MP(MpOutSclUser)>>2))), 0xff);
	        bLAST_CCLIP = OUTSCL_FULL_CCLIP;

			wPEDESTAL_LV = (PEDESTAL_LV_MAX * MP(MpOutSclUser))>>5;
		}
		
			LAST_YGAINw(bLAST_YGAIN);
			LAST_YOFFSw(bLAST_YOFFS);
			LAST_YCLIPw(bLAST_YCLIP);
			LAST_YSLICw(bLAST_YSLIC);
			
			LAST_CBGAINw(bLAST_CGAIN);
			LAST_CRGAINw(bLAST_CGAIN);
	        LAST_CCLIPw(bLAST_CCLIP);

			PEDESTAL_LVw(wPEDESTAL_LV);
}


//-------------------------------------------------------------------------------------------------
void UartBaudRate(void)
{ // UART Baudrate
	//TxStrDecNoIRQ("UART Baudrate ", MP(MpBaudrate), 3);

//#if model_LowUart
//	extern BYTE gbIsrGpioStg;
//	if(gbIsrGpioStg == 0 || gbIsrGpioStg == 1) return;
//#endif

	switch(MP(MpBaudrate)){
		case MN_BR_2400		: UART0_CLKDIV = UB2400;	break;
		case MN_BR_4800		: UART0_CLKDIV = UB4800;	break;
		case MN_BR_9600		: UART0_CLKDIV = UB9600;	break;
		case MN_BR_57600	: UART0_CLKDIV = UB57600;	break;
		case MN_BR_115200	: UART0_CLKDIV = UB115200;	break;
		default				: UART0_CLKDIV = UB_INIT;	break;
	}
}

//-------------------------------------------------------------------------------------------------
// BOX00 ~ BOX15 (PVC_EA : 16)
UINT gnBoxPltPVC[PVC_EA];
UINT gnBoxTonePVC;
UINT gnBoxFillPVC;

UINT gnBoxPosPVC[PVC_EA*2];
UINT gnBoxOnPVC;



void ISPM PrivacyBox(void)
{	// Box Privacy 32ea
	
	UINT i;
	UINT nPRVC_CY, nPRVC_CB, nPRVC_CR;

	int iPosX,iPosY,iSizX,iSizY;

	int iXOffSet=0x0, iYOffSet=0x0;							//Between Menual and Auto Position Offset

	float32 fRatioH = 0, fRatioV = 0;
	
	fRatioH = _fdiv(_itof(HWOr),_itof(HWIr));
	fRatioV = _fdiv(_itof(VWOr),_itof(VWIr));
	
	const BYTE nColorStep = BOX_COLOR_STEP;

	gnPixelStepH = _ftoi(_fmul(_itof(BOX_MOVPIXEL),fRatioH));
	gnPixelStepV = _ftoi(_fmul(_itof(BOX_MOVPIXEL),fRatioV));
	
	gnBoxTonePVC = 0;
	gnBoxOnPVC = 0;

	if (MP(MpPrivacy)==MN_ON) {

		nPRVC_CY = MP(MpPvcYLevel)  * 255 / nColorStep;
		nPRVC_CB = MAX((MP(MpPvcCBLevel) * 255 / nColorStep),1);
		nPRVC_CR = MAX((MP(MpPvcCRLevel) * 255 / nColorStep),1);

		#define	PRVC_POS_H	(gbMnPvcCfg(i)->bPosX)
		#define	PRVC_POS_V	(gbMnPvcCfg(i)->bPosY)
		#define	PRVC_SIZ_H	(gbMnPvcCfg(i)->bSizX)
		#define	PRVC_SIZ_V	(gbMnPvcCfg(i)->bSizY)


		for (i=0; i<PVC_EA; i++) {

			//(LGH) 1 Step Box Position Calculation

			iPosX = PRVC_POS_H*gnPixelStepH;
			iSizX = PRVC_SIZ_H*gnPixelStepH;

			iPosY = PRVC_POS_V*gnPixelStepV;
			iSizY = PRVC_SIZ_V*gnPixelStepV;

			if(MP(MpFlip)==MN_OFF)		{iYOffSet = 0x0; iPosY = iPosY + iYOffSet;}								//Left Bottom Axis
			else						{iYOffSet = 0x0; iPosY = VWOr - iPosY - iSizY + iYOffSet;}

			if(MP(MpMirror)==MN_OFF)	{iXOffSet = 0x0; iPosX = iPosX + iXOffSet;}								//   "
			else						{iXOffSet = 0x0; iPosX = HWOr - iPosX - iSizX + iXOffSet;}
			
			gnBoxPosPVC[(i*2)]	 = (MINMAX((iPosY+iSizY),0x0,0xfff) | (MINMAX(iPosY,0x0,0xfff)<<16));
			gnBoxPosPVC[(i*2)+1] = (MINMAX((iPosX+iSizX),0x0,0xfff) | (MINMAX(iPosX,0x0,0xfff)<<16));
			gnBoxPltPVC[i]		 = (nPRVC_CY<<16)|(nPRVC_CB<<8)|(nPRVC_CR);										// box attr

			gnBoxTonePVC |= MP(MpPvcTrans)<<(i*2);	
			gnBoxFillPVC |= 0x1<<i;

			gnBoxOnPVC |= ((gbMnPvcCfg(i)->bAction)&0x1)<<i;
		}

	}
}


//-------------------------------------------------------------------------------------------------
void ISPM BoxLast(void)
{	// Last Box apply (priority, sharing control)
	BOX_HSPw(BOX_HSP);
	BOX_VSPw(BOX_VSP);

	//----------------------------------------------------------------------------------------
	int i;

	for (i=0; i<ISP_BOX_EA; i++) {
		if (i < PVC_EA) {				// Privacy - BOX (BOX0 ~ BOX15)
			SetIsp(BOXPOS_BASE+(i*2)  	, gnBoxPosPVC[(i*2)]);				// box y
			SetIsp(BOXPOS_BASE+(i*2+1)	, gnBoxPosPVC[(i*2)+1]);			// box x
			SetIsp(BOXPLT_BASE+i      	, gnBoxPltPVC[i]);					// box attr
		}
		
#if ((model_Lens==1)&&(MAF_BOSD_DISP!=0)) // 180702 JJH 2motor box
		else if((gbMAFBoxFlag)&&(i < (MAF_BOX_START+MAF_BOX_NUM))){
			SetIsp(BOXPOS_BASE+(i*2)  	, gnBoxPosMAF_Y[(i-MAF_BOX_START)]);// box y
			SetIsp(BOXPOS_BASE+(i*2+1)	, gnBoxPosMAF_X[(i-MAF_BOX_START)]);// box x
			SetIsp(BOXPLT_BASE+i      	, gnBoxPltMAF[(i-MAF_BOX_START)]);	// box attr		
		}
#endif
	}

#if ((model_Lens==1)&&(MAF_BOSD_DISP!=0)) 					// 180702 JJH 2motor box
	const UINT nBoxToneLSB = (gnBoxTonePVC);
	const UINT nBoxToneMSB = (gnBoxToneMAF&0x3FF);
	const UINT nBoxFill = ((gnBoxFillPVC&0xFFFF)|((gnBoxFillMAF<<MAF_BOX_START)&0x1F0000));

	const UINT nBoxOn = ((gnBoxOnPVC&0xFFFF)|((gnBoxOnMAF<<MAF_BOX_START)&0x1F0000));
	
#else
	const UINT nBoxToneLSB = (gnBoxTonePVC);
	const UINT nBoxToneMSB = 0;
	const UINT nBoxFill = (gnBoxFillPVC&0xFFFF);

	const UINT nBoxOn = ((gnBoxOnPVC&0xFFFF));

#endif
	
	SetIsp(BOXTON_BASE  , nBoxToneMSB);		// box tone msb
    SetIsp(BOXTON_BASE+1, nBoxToneLSB);		// box tone lsb
    SetIsp(BOXFIL_BASE  , nBoxFill);		// box fill tone

	BOSD_ONw(nBoxOn);						// box on/off
	
}

