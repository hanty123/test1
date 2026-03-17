/* **************************************************************************
 File Name	:	app_cont.c
 Description	:	EN772 - Gamma, ACE & Defog function (contrast)
 Designer		:	Lee, Gyu Hong
 Date		:	21. 04. 22
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"
#include "app_cont.h"

//*************************************************************************************************
// Variables
//-------------------------------------------------------------------------------------------------

//*************************************************************************************************
// Functions
//-------------------------------------------------------------------------------------------------
// Init
//-------------------------------------------------------------------------------------------------
// Gamma
void InitGamma(void)
{
	YGMA_ONw(1);
	CGMA_ONw(1);

	if(gbGammParInit){
//		TxStrNoIRQ("Gamma Data Init ! ", 0, 0);
		DfltGammaSave();
		gbGammParInit = 0;
	}
	else{
//		TxStrNoIRQ("Load Gamma Data from memory ! ", 0, 0);
		SftoISP_GmLoad();
	}
}

void ISPM2 Gamma(void)		// 180104 LHgnTblWdrC1Gma
{
	int i;

	static BYTE bLWdrOnBuf = 0xee;
	static BYTE bYGmaK = 0x0, bCGmaK = 0x0;
	static BYTE bGmaAutoModeBuf = 0xee;

	WORD wYAgcPt0, wYAgcPt1;
	WORD wCAgcPt0, wCAgcPt1;
	
	wYAgcPt0 = (MODE_WDR_ON)?(UP(UpYGMA_WDR_AGC_PT0)):(UP(UpYGMA_AGC_PT0));
	wYAgcPt1 = (MODE_WDR_ON)?(UP(UpYGMA_WDR_AGC_PT1)):(UP(UpYGMA_AGC_PT1));
	
	wCAgcPt0 = (MODE_WDR_ON)?(UP(UpCGMA_WDR_AGC_PT0)):(UP(UpCGMA_AGC_PT0));
	wCAgcPt1 = (MODE_WDR_ON)?(UP(UpCGMA_WDR_AGC_PT1)):(UP(UpCGMA_AGC_PT1));
	
	const BYTE bGmaAuto = (MP(MpGamma)==MN_GAMMA_AUTO);
		
	const UINT* pnY1GmmaTbl = (bGmaAuto)?((MODE_WDR_ON?(gnTblWdrY1GmaCstm):(gnTblY1GmaCstm))):(gnTblY1GmaBasic);
	const UINT* pnC1GmmaTbl = (bGmaAuto)?((MODE_WDR_ON?(gnTblWdrC1GmaCstm):(gnTblC1GmaCstm))):(gnTblC1GmaBasic);

	const UINT* pnY2GmmaTbl = (bGmaAuto)?((MODE_WDR_ON?(gnTblWdrY2GmaCstm):(gnTblY2GmaCstm))):(gnTblY2GmaBasic);
	const UINT* pnC2GmmaTbl = (bGmaAuto)?((MODE_WDR_ON?(gnTblWdrC2GmaCstm):(gnTblC2GmaCstm))):(gnTblC2GmaBasic);

#if(model_Sens_LFM_HDR)
	static BYTE gbLwdrLFMOnBuf;
#endif

#if(model_Sens_CLR_HDR)
	static BYTE gbLwdrCLROnBuf;
#endif

	YGMA_ONw(UP(UpGAMMA_Y_ON));					// 210513 LGH : Use parameter Gamma ON/OFF 
	CGMA_ONw(UP(UpGAMMA_C_ON));					// 210513 LGH : Use parameter Gamma ON/OFF 
	
	if ((gbDfltGammaChk) || (bLWdrOnBuf!=gbModeWdrOn_L) || (bGmaAutoModeBuf!=bGmaAuto)
	#if(model_Sens_CLR_HDR)
		||(gbLwdrCLROnBuf!=gbModeWdrOn_CLR)
	#endif
	){	// Gamma table exchange by WDR mode
		gbDfltGammaChk = 0;
	
	#if(1)
//		DfltGammaSave();
	#endif
	
		for (i=0; i<9; i++) 	SetIsp(YGAMMA_BASE1+i, *(pnY1GmmaTbl+i));		// Y1
		for (i=0; i<9; i++) 	SetIsp(CGAMMA_BASE1+i, *(pnC1GmmaTbl+i));		// C1
		
		for (i=0; i<9; i++) 	SetIsp(YGAMMA_BASE2+i, *(pnY2GmmaTbl+i));		// Y2
		for (i=0; i<9; i++) 	SetIsp(CGAMMA_BASE2+i, *(pnC2GmmaTbl+i));		// C2	
	}
	
	if ((gbModeWdrOn_L)
	#if(model_Sens_CLR_HDR)
		||(gbModeWdrOn_CLR)
	#endif
		){
			bYGmaK = LibUtlInterp1D(MINMAX(giCurAgc, UP(UpYGMA_WDR_AGC_PT0), UP(UpYGMA_WDR_AGC_PT1)), UP(UpYGMA_WDR_AGC_PT0), UP(UpYGMA_WDR_AGC_PT1), 0x0, 0x80);
			bCGmaK = LibUtlInterp1D(MINMAX(giCurAgc, UP(UpCGMA_WDR_AGC_PT0), UP(UpCGMA_WDR_AGC_PT1)), UP(UpCGMA_WDR_AGC_PT0), UP(UpCGMA_WDR_AGC_PT1), 0x0, 0x80);		
		}
	else{
		if(bGmaAuto){
			bYGmaK = LibUtlInterp1D(MINMAX(giCurAgc, UP(UpYGMA_AGC_PT0), UP(UpYGMA_AGC_PT1)), UP(UpYGMA_AGC_PT0), UP(UpYGMA_AGC_PT1), 0x0, 0x80);
			bCGmaK = LibUtlInterp1D(MINMAX(giCurAgc, UP(UpCGMA_AGC_PT0), UP(UpCGMA_AGC_PT1)), UP(UpCGMA_AGC_PT0), UP(UpCGMA_AGC_PT1), 0x0, 0x80);
		}
		else{
			bYGmaK = MIN((0x80*MP(MpGamma)/3),0x80);
			bCGmaK = MIN((0x80*MP(MpGamma)/3),0x80);
		}
	}
	
	YGMKw(bYGmaK);				// Manual
	CGMKw(bCGmaK);				// Manual

	bLWdrOnBuf = gbModeWdrOn_L;
	bGmaAutoModeBuf = bGmaAuto;
	
#if(model_Sens_CLR_HDR)
	gbLwdrCLROnBuf = gbModeWdrOn_CLR;
#endif

#if(model_Sens_LFM_HDR)
	gbLwdrLFMOnBuf = gbModeWdrOn_LFM;
#endif

	DebugDisp((gbMnDebugFnc==MN_DBG_5), , "AGC_____", 1, 24, giCurAgc	);
	DebugDisp((gbMnDebugFnc==MN_DBG_5), , "YGMA_K__", 3, 24, YGMKr);
	DebugDisp((gbMnDebugFnc==MN_DBG_5), , "YGMA_PT0_", 4, 24, wYAgcPt0);
	DebugDisp((gbMnDebugFnc==MN_DBG_5), , "YGMA_PT1_", 5, 24, wYAgcPt1);
	
	DebugDisp((gbMnDebugFnc==MN_DBG_5), , "CGMA_K___", 7, 24, CGMKr);
	DebugDisp((gbMnDebugFnc==MN_DBG_5), , "CGMA_PT0_", 8, 24, wCAgcPt0);
	DebugDisp((gbMnDebugFnc==MN_DBG_5), , "CGMA_PT1_", 9, 24, wCAgcPt1);
}

//-------------------------------------------------------------------------------------------------
//Default Gamma Set
void ISPM2 SetDefltGamma(BYTE abGammaNo, UINT* apnGammaTbl, const UINT* apnDfltGammaTbl)
{
	int i = 0;
	UINT nGammaBuf = 0x0;
	
	// Default Gamma buffer to Cstm Gamma buffer
	for(i = 0; i < 9; i++)	*(apnGammaTbl+i) = *(apnDfltGammaTbl+i);
	
	for (i = 0; i < 8; i++){
		nGammaBuf = *(apnGammaTbl+i);
			
		UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4)) 		= ((nGammaBuf>>24)&0x03);
		UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4)+1)	= ((nGammaBuf>>16)&0xFF);
		UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4)+2)	= ((nGammaBuf>> 8)&0x03);
		UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4)+3)	= ((nGammaBuf>> 0)&0xFF);
	}

	nGammaBuf = *(apnGammaTbl+i);
	
	UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4)) 			= ((nGammaBuf>>24)&0x03);
	UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4)+1)		= ((nGammaBuf>>16)&0xFF);
	
}

void ISPM2 DfltGammaSave(void)
{	
	SetDefltGamma(0, gnTblY1GmaCstm, gnTblY1Gma);
	SetDefltGamma(1, gnTblY2GmaCstm, gnTblY2Gma);
	SetDefltGamma(2, gnTblC1GmaCstm, gnTblC1Gma);
	SetDefltGamma(3, gnTblC2GmaCstm, gnTblC2Gma);

	SetDefltGamma(4, gnTblWdrY1GmaCstm, gnTblWdrY1Gma);
	SetDefltGamma(5, gnTblWdrY2GmaCstm, gnTblWdrY2Gma);
	SetDefltGamma(6, gnTblWdrC1GmaCstm, gnTblWdrC1Gma);
	SetDefltGamma(7, gnTblWdrC2GmaCstm, gnTblWdrC2Gma);

	// Save ROM
	if(gbGammParInit)	gbUsrDataSaveChk = 1;
}

//-------------------------------------------------------------------------------------------------
//Gamma Save
void ISPM2 GammaSave(WORD awAddr, BYTE abGammaNo)
{
	int i;
	UINT nGammaBuf = 0x0;

	for (i=0; i < 8; i++){
		nGammaBuf = GetIsp(awAddr+i);
			
		UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4)) 		= ((nGammaBuf>>24)&0x03);
		UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4)+1)	= ((nGammaBuf>>16)&0xFF);
		UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4)+2)	= ((nGammaBuf>> 8)&0x03);
		UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4)+3)	= ((nGammaBuf>> 0)&0xFF);
	}

	nGammaBuf = GetIsp(awAddr+i);
	
	UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4)) 			= ((nGammaBuf>>24)&0x03);
	UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4)+1)		= ((nGammaBuf>>16)&0xFF);

}

void ISPM2 ISPtoSf_GmSave(void)
{// Save Gamma from flash memory

	// Gamma Load
	if(!MODE_WDR_ON){
		GammaSave(YGAMMA_BASE1, 0);			//Y1
		GammaSave(YGAMMA_BASE2, 1);			//Y2
		GammaSave(CGAMMA_BASE1, 2);			//C1
		GammaSave(CGAMMA_BASE2, 3);			//C2
	}

	else{
		GammaSave(YGAMMA_BASE1, 4);			//Y1
		GammaSave(YGAMMA_BASE2, 5);			//Y2
		GammaSave(CGAMMA_BASE1, 6);			//C1
		GammaSave(CGAMMA_BASE2, 7);			//C2
	}
	
	// Save ROM
	gbUsrDataSaveChk = 1;
}

//-------------------------------------------------------------------------------------------------
//Gamma Load
void ISPM2 GammaLoad(BYTE abGammaNo, UINT* apnGammaTbl)
{
	int i;

	for (i=0; i < 8; i++){
		apnGammaTbl[i] = (	(UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4))<<24)|\
							(UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4)+1)<<16)|\
							(UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4)+2)<< 8)|\
							(UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4)+3)<< 0));
	}
		apnGammaTbl[i] = (	(UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4))<<24)|(UD(UdGamma+(abGammaNo*GMA_BYTE)+(i*4)+1)<<16));
}

void ISPM2 SftoISP_GmLoad(void)
{// Load Gamma from flash memory

	// Normal Gamma
	GammaLoad(0, gnTblY1GmaCstm);		//Y1
	GammaLoad(1, gnTblY2GmaCstm);		//Y2
	GammaLoad(2, gnTblC1GmaCstm);		//C1
	GammaLoad(3, gnTblC2GmaCstm);		//C2

	// WDR Gamma
	GammaLoad(4, gnTblWdrY1GmaCstm);	//Y1
	GammaLoad(5, gnTblWdrY2GmaCstm);	//Y2
	GammaLoad(6, gnTblWdrC1GmaCstm);	//C1
	GammaLoad(7, gnTblWdrC2GmaCstm);	//C2
}	

//-------------------------------------------------------------------------------------------------
// ACE & Defog
void InitContrast(void)
{
	TMG_ONw(0);
	
	//ACE setting
	ACE_HSPw(ACE_HSP);
	ACE_VSPw(ACE_VSP);
	
	//Defog setting
	gnDefog_HS = AE2_HSPr + DEFOG_X_OFF;								// Histogram detection area H start			// 160222 HSH
	gnDefog_HE = AE2_HEPr - DEFOG_X_OFF;								// "						H end
	gnDefog_VS = AE2_VSPr;												// "						V start
	gnDefog_VE = AE2_VEPr;												// "						V end

	UINT 	nHW = gnDefog_HE - gnDefog_HS + 1;
	UINT 	nVW = ((gnDefog_VE<<1)/3) - gnDefog_VS + 1;

	gnAe1Size = nHW * nVW;											// total size

	//171108 LGH
	HEQ_HWw(DEFOG_HW);											// Defog window setup
	HEQ_VWw(DEFOG_VW);											// "
	HEQ_HSPw(DEFOG_HSP);										// "
	HEQ_VSPw(DEFOG_VSP);                                        // " 

	// Histogram X domain read
	#define HISTO_MAX_VAL0	0x08101820
	#define HISTO_MAX_VAL1	0x28303840
	#define HISTO_MAX_VAL2	0x48505860
	#define HISTO_MAX_VAL3	0x68707800

	gnHistoM[15] = 0x7f;

	UINT nHistoMax = HISTO_MAX_VAL0;
	gnHistoM[3] = nHistoMax&0x7f;
	gnHistoM[2] = (nHistoMax>>8)&0x7f;
	gnHistoM[1] = (nHistoMax>>16)&0x7f;
	gnHistoM[0] = (nHistoMax>>24)&0x7f;

	nHistoMax = HISTO_MAX_VAL1;
	gnHistoM[7] = nHistoMax&0x7f;
	gnHistoM[6] = (nHistoMax>>8)&0x7f;
	gnHistoM[5] = (nHistoMax>>16)&0x7f;
	gnHistoM[4] = (nHistoMax>>24)&0x7f;

	nHistoMax = HISTO_MAX_VAL2;
	gnHistoM[11] = nHistoMax&0x7f;
	gnHistoM[10] = (nHistoMax>>8)&0x7f;
	gnHistoM[ 9] = (nHistoMax>>16)&0x7f;
	gnHistoM[ 8] = (nHistoMax>>24)&0x7f;

	nHistoMax = HISTO_MAX_VAL3;
	gnHistoM[14] = (nHistoMax>>8)&0x7f;
	gnHistoM[13] = (nHistoMax>>16)&0x7f;
	gnHistoM[12] = (nHistoMax>>24)&0x7f;

	gnDefogV = 0;
	gnDwdrV = 0;

	HEQ_IIRKw(0xd0);												// IIR Speed
	
  #if 0
	UINT i;
	char str[] = "HM\t0\t'";
	for(i=0; i<11/*numberof(gnHistoM)*/; i++)
	{
		str[2] = '0' + i;
		TxStr(str, gnHistoM[i], 3);
	}
  #endif 
}

void ISPM2 AceDefog(void)
{
	ACE_ON
	DEFOG_ON

	//ACE setting
	int 	iAceTh1=0, iAceTh2=0, iAceDth=3;
	BYTE 	bAceTblSel=0;
	BYTE	bAceGmgn = 0;
	WORD wAgcPt0, wAgcPt1, wAgcPt2;
	
	wAgcPt0 = (MODE_WDR_ON)?(UP(UpACE_WDR_AGC_PT0)):(UP(UpACE_AGC_PT0));
	wAgcPt1 = (MODE_WDR_ON)?(UP(UpACE_WDR_AGC_PT1)):(UP(UpACE_AGC_PT1));
	wAgcPt2 = (MODE_WDR_ON)?(UP(UpACE_WDR_AGC_PT2)):(UP(UpACE_AGC_PT2));

	ACE_HBw(ACE_HB);
	ACE_VBw(ACE_VB);
	
	ACE_HBSw(ACE_HBS);												// ACE block size
	ACE_VBSw(ACE_VBS);												// ACE block size

	//ACE setting
	ACE_HSPw(ACE_HSP);
	ACE_VSPw(ACE_VSP);
	
	ACE_IIRw(UP(UpACE_IIR)); 												// 161121 LGH	

	// ACE - WDR
	if ((MP(MpBackLight)==MN_BL_WDR)){	
		ACEBLOCK_ON

		bAceGmgn = IntpValAgcPos(giCurAgc, UP(UpACE_WDR_AGC_PT0), UP(UpACE_WDR_AGC_PT1), UP(UpACE_WDR_AGC_PT2), UP(UpACE_WDR_GMGN_VAL_PT0), UP(UpACE_WDR_GMGN_VAL_PT1), UP(UpACE_WDR_GMGN_VAL_PT2));
		
		iAceTh1 = IntpValAgcPos(giCurAgc, UP(UpACE_WDR_AGC_PT0), UP(UpACE_WDR_AGC_PT1), UP(UpACE_WDR_AGC_PT2), UP(UpACE_WDR_TH1_VAL_PT0), UP(UpACE_WDR_TH1_VAL_PT1), UP(UpACE_WDR_TH1_VAL_PT2));
		iAceTh2 = IntpValAgcPos(giCurAgc, UP(UpACE_WDR_AGC_PT0), UP(UpACE_WDR_AGC_PT1), UP(UpACE_WDR_AGC_PT2), UP(UpACE_WDR_TH2_VAL_PT0), UP(UpACE_WDR_TH2_VAL_PT1), UP(UpACE_WDR_TH2_VAL_PT2));
		
		iAceDth = UP(UpACE_WDR_DTH);
	}

	// ACE - Normal
	else {														
		if ((MP(MpDefog)==MN_ON) || (MP(MpAce) != MN_4sOFF)) {		// ACE, Defog condition
			ACEBLOCK_ON

			bAceGmgn 	= (MP(MpDefog)==MN_ON)?(0x0):(IntpValAgcPos(giCurAgc, UP(UpACE_AGC_PT0), UP(UpACE_AGC_PT1), UP(UpACE_AGC_PT2), UP(UpACE_GMGN_VAL_PT0), UP(UpACE_GMGN_VAL_PT1), UP(UpACE_GMGN_VAL_PT2)));
			bAceTblSel 	= (MP(MpDefog)==MN_ON)?(MN_4sMID):(MP(MpAce));
			
			switch (bAceTblSel) {
				case MN_4sLOW	:	iAceTh1 = IntpValAgcPos(giCurAgc, UP(UpACE_AGC_PT0), UP(UpACE_AGC_PT1), UP(UpACE_AGC_PT2), UP(UpACE_TH1_LOW_VAL_PT0), UP(UpACE_TH1_LOW_VAL_PT1), UP(UpACE_TH1_VAL_PT2));
									iAceTh2 = IntpValAgcPos(giCurAgc, UP(UpACE_AGC_PT0), UP(UpACE_AGC_PT1), UP(UpACE_AGC_PT2), UP(UpACE_TH2_LOW_VAL_PT0), UP(UpACE_TH2_LOW_VAL_PT1), UP(UpACE_TH2_VAL_PT2));  break;
									
				case MN_4sMID	:	iAceTh1 = IntpValAgcPos(giCurAgc, UP(UpACE_AGC_PT0), UP(UpACE_AGC_PT1), UP(UpACE_AGC_PT2), UP(UpACE_TH1_MID_VAL_PT0), UP(UpACE_TH1_MID_VAL_PT1), UP(UpACE_TH1_VAL_PT2));
									iAceTh2 = IntpValAgcPos(giCurAgc, UP(UpACE_AGC_PT0), UP(UpACE_AGC_PT1), UP(UpACE_AGC_PT2), UP(UpACE_TH2_MID_VAL_PT0), UP(UpACE_TH2_MID_VAL_PT1), UP(UpACE_TH2_VAL_PT2));  break;
									
				case MN_4sHI	:	iAceTh1 = IntpValAgcPos(giCurAgc, UP(UpACE_AGC_PT0), UP(UpACE_AGC_PT1), UP(UpACE_AGC_PT2), UP(UpACE_TH1_HIGH_VAL_PT0), UP(UpACE_TH1_HIGH_VAL_PT1), UP(UpACE_TH1_VAL_PT2));
									iAceTh2 = IntpValAgcPos(giCurAgc, UP(UpACE_AGC_PT0), UP(UpACE_AGC_PT1), UP(UpACE_AGC_PT2), UP(UpACE_TH2_HIGH_VAL_PT0), UP(UpACE_TH2_HIGH_VAL_PT1), UP(UpACE_TH2_VAL_PT2));  break;
									
				default			:	iAceTh1 = IntpValAgcPos(giCurAgc, UP(UpACE_AGC_PT0), UP(UpACE_AGC_PT1), UP(UpACE_AGC_PT2), UP(UpACE_TH1_LOW_VAL_PT0), UP(UpACE_TH1_LOW_VAL_PT1), UP(UpACE_TH1_VAL_PT2));
									iAceTh2 = IntpValAgcPos(giCurAgc, UP(UpACE_AGC_PT0), UP(UpACE_AGC_PT1), UP(UpACE_AGC_PT2), UP(UpACE_TH2_LOW_VAL_PT0), UP(UpACE_TH2_LOW_VAL_PT1), UP(UpACE_TH2_VAL_PT2));  break;
			}

			iAceDth = UP(UpACE_DTH);
		}
		
		else {														// all off condition
			ACEBLOCK_OFF
			bAceGmgn = 0x0;

			iAceDth = 0x0;
			iAceTh1 = 0x0;
			iAceTh2 = 0x0;
		}
	}

//	ACE_GMGNw(bAceGmgn);
	ACE_GMGNw(MINMAX(bAceGmgn+MP(MpContrast)-20, 0x0, 0xFF));
	
	ACE_DTHw(iAceDth);
//	ACE_TH1w(iAceTh1);
	ACE_TH1w(MINMAX(iAceTh1+MP(MpContrast)-20, 0x0, 0xFF));
	ACE_TH2w(iAceTh2);

	DebugDisp((gbMnDebugFnc==MN_DBG_5), , "ACE_TH1_", 11, 24, iAceTh1);
	DebugDisp((gbMnDebugFnc==MN_DBG_5), , "ACE_TH2_", 12, 24, iAceTh2);
	DebugDisp((gbMnDebugFnc==MN_DBG_5), , "ACE_GMGN", 13, 24, bAceGmgn);
	DebugDisp((gbMnDebugFnc==MN_DBG_5), , "ACE_PT0_", 15, 24, wAgcPt0);
	DebugDisp((gbMnDebugFnc==MN_DBG_5), , "ACE_PT1_", 16, 24, wAgcPt1);
	DebugDisp((gbMnDebugFnc==MN_DBG_5), , "ACE_PT2_", 17, 24, wAgcPt2);


	// Defog -------------------------------------------------------------------------------
	UINT	DefogTbl[3];	// Low, Middle, High
	//Defog Table UserParameter
	DefogTbl[0] = UP(UpDEFOG_TH_LOW);	
	DefogTbl[1] = MAX(DefogTbl[0],(UINT)UP(UpDEFOG_TH_MID));	
	DefogTbl[2] = MAX(DefogTbl[1],(UINT)UP(UpDEFOG_TH_HIGH));

 	UINT 	nDefogThres = 0;
	UINT 	nDefogWeight = 3;								//Defog off  (Weight 0 : Defog 0%, 1 : Defog 25%, 2 : Defog 50%, 3 : Defog 75%, else Defog 100% coverage)

	gbContrastMode 	= MP(MpDefog);							// menu parameter   OFF/ON
	gbDefogMode 	= MP(MpDefogMode);						// "				MANUAL/AUTO
	gbDefogLevel 	= MP(MpDefogLevel);						// "				STRENGTH LOW/MID/HIGH

	if (gbContrastMode==MN_ON) {	// Defog on

		gnDefog_HS = UP(UpAE2_HSP) + DEFOG_X_OFF;
		gnDefog_HE = UP(UpAE2_HEP) - DEFOG_X_OFF;
		gnDefog_VS = UP(UpAE2_VSP);
		gnDefog_VE = UP(UpAE2_VEP);

		HEQ_OSDw(DEFOG_OSDON);
		
		HEQ_HSPw(DEFOG_HSP); 	// Defog window setup
		HEQ_HWw(DEFOG_HW);		// "
		HEQ_VSPw(DEFOG_VSP);  	// "
		HEQ_VWw(DEFOG_VW);		// "

		UINT 	nHW = gnDefog_HE - gnDefog_HS + 1; 			// JYP
		UINT 	nVW = ((gnDefog_VE<<1)/3) - gnDefog_VS + 1;

		gnAe1Size = nHW*nVW;

		AE1_HSPw(gnDefog_HS);								// AE1 area H (Histogram window)
		AE1_HEPw(gnDefog_HE);								// "

		AE1_VSPw(gnDefog_VS);								// AE1 area V (Histogram window)
		AE1_VEPw((gnDefog_VE<<1)/3);				//

		//															0  1  2  3     4     5     6     7     8  9
		// HISTO10_MAX : 10203040 6080a0c0 0000e0ff				-> 10 20 30 40    60    80    a0    c0    e0 ff 100
		// HISTO15_MAX : 08101820 28303840 48505860 68707f00	->  8 10 18 20 28 30 38 40 48 50 58 60 68 70 7f  80
		//															0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
		gnHistoV[0] = HISTO0_LOCKr;
		gnHistoV[1] = HISTO1_LOCKr;
		gnHistoV[2] = HISTO2_LOCKr;
		gnHistoV[3] = HISTO3_LOCKr;
		gnHistoV[4] = HISTO4_LOCKr + HISTO5_LOCKr;
		gnHistoV[5] = HISTO6_LOCKr + HISTO7_LOCKr;
		gnHistoV[6] = HISTO8_LOCKr + HISTO9_LOCKr;
		gnHistoV[7] = HISTO10_LOCKr + HISTO11_LOCKr;	//	"TBD"	// 160222 HSH	// 180110 LGH : remove comment
		gnHistoV[8] = HISTO12_LOCKr + HISTO13_LOCKr;;
		gnHistoV[9] = HISTO14_LOCKr;

//		if (MP(MpBackLight)==MN_BL_WDR)		nDefogWeight = 1;									// 170804 LH : OFF when WDR
		if (MP(MpBackLight)==MN_BL_WDR) 	nDefogWeight = 0;									// 170804 LH : OFF when WDR
		else								LibDefog(&nDefogThres, &nDefogWeight, DefogTbl); 	// Defog library		
	}

	else{
		HEQ_OSDw(0x0);
		nDefogWeight = 0;												// Defog off
	}

	HEQ_THw(nDefogThres);												// apply to HEQ
	HEQ_WGw(MIN((nDefogWeight*0x100/4),0x100));							// EN781 Defog Intensity : 0x100 -> X1

	// Mon
//	DebugDisp(gbDebugOn, , "DFG_THRS", 7, 24, HEQ_THr 	);
//	DebugDisp(gbDebugOn, , "DFG_WG__", 8, 24, HEQ_WGr	);
	
}

