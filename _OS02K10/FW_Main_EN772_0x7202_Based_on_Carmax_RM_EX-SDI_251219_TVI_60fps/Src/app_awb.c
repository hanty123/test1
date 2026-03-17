/* **************************************************************************
 File Name	: 	app_awb.c
 Description	:	EN772 - Auto White Balance module
 Designer		:	Lee, Hoon
 Modifier		:	Lee, Gyu Hong
 Date		:	14. 12. 05
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"
#include "app_awb_tbl.h"

//*******************************************************************************
// Reserved define & Variables
//*******************************************************************************

#define TestMnl	0

extern const s64 glMtxCf[9][6];
extern const s64 glMtxCf_cstm[9][6];
int giCmat[3][3];

UINT 	gnAwbRGainIIR, gnAwbBGainIIR;
int  	giAwbDbIIR, giAwbDrIIR;
int		giDrSum = 0;
int		giDbSum = 0;

UINT 	gnAwbErr;
BYTE 	gbAwbDebugOn;
UINT	gnAwbOdmCapOn = 0;
int 	giAwbPrstTbl[4] = { 0, 0, 0x100<<2, 0x100<<2};		// Preset save

float32 gf32MtxCf[9][6];
extern void LibAwbCmatF32 (int, int, float32 [9][6]);

BYTE 	gbColorMapParInit = 0;
BYTE 	gbDfltColorMapChk = 0;

extern UINT gnAe5Sum;

//*************************************************************************************************
// Sub Functions
//*************************************************************************************************

void ISPM AwbCmapSet(BYTE abMapSel, UINT* apnMapTbl)
{
	int i;
	const BYTE bAddrofst = (abMapSel) ? 2 : 1;
	
	apnMapTbl = abMapSel ? apnMapTbl+1 : apnMapTbl;

	for (i=0; i<128; i++) {
		SetIsp(AWBL_CM_BASE+i, 	*apnMapTbl);
		apnMapTbl += bAddrofst;			
	}
}

void InitAwb(void)
{	// Initial AWB

//	ICSELw(0x1);		// matching with OCSEL
//	OZONE_SELw(0x3)				;		// ODM OSD Selection Register

	// ���� X
	// ODM YC matrix	Y  = 0.33R + 0.33G + 0.33B,	Cb = B - Y,	 Cr = R - Y
	ODM_M1w(0x55);
	ODM_M2w(0x55);
	ODM_M3w(0x55);
	ODM_M4w(0x255);
	ODM_M5w(0x255);
	ODM_M6w(0xab);
	ODM_M7w(0xab);
	ODM_M8w(0x255);
	ODM_M9w(0x255);

	AWBLCBCRO_SELw(0x0);	// 0: DbDr, 1: CbCr  OutPut
	AWBL_HTAB_SELw(0x2);	// Size of detection block
	AWB_LOCK_SELw(0x1);		// Awb data lock at VLOCK
	AWBLYEDGE_THw(0x3ff);	// Y edge pseudo color remove

	AWB_WIN1_HSPw(UP(UpAWB_HSP));
	AWB_WIN1_HWw(UP(UpAWB_HW));
	AWB_WIN1_VSPw(UP(UpAWB_VSP));
	AWB_WIN1_VWw(UP(UpAWB_VW));

	// init Hue
	BYGAINNw(UP(UpBY_GAINN_TEMP_M));
	BYGAINPw(UP(UpBY_GAINP_TEMP_M));
	RYGAINNw(UP(UpRY_GAINN_TEMP_M));
	RYGAINPw(UP(UpRY_GAINP_TEMP_M));

	BYHUENw (UP(UpBY_HUEN_TEMP_M));
	BYHUEPw (UP(UpBY_HUEP_TEMP_M));
	RYHUENw (UP(UpRY_HUEN_TEMP_M));
	RYHUEPw (UP(UpRY_HUEP_TEMP_M));


	AWBLNOR_SELw(0x0)			;		// 1 : Always operate, 0 : Use color map

	AWBLOSD_ONw(0x0)       		;		// AWB OSD On/Off
	AWBL_OSD_SELw(0x7b)      	;		// OSD Form

	AWBL_CM_HSPw(0x1f8)			;		// Color map OSD position	//150422 HSH
	AWBL_CM_VSPw(0x138)			;		// "

	AWBL_CYSLICEw(UP(UpAWB_YSLICE))	;		// Y slice
	AWBL_CYCLIPw(UP(UpAWB_YCLIP))		;		// Y clip

	AWBL0_DBOFFSETw(UP(UpAWB_DBOFFSET));
	AWBL0_DROFFSETw(UP(UpAWB_DROFFSET));
	AWBL_DBGAIN0w  (AWB_DBGAIN);
	AWBL_DRGAIN0w  (AWB_DRGAIN);

	giAwbDbIIR = giDbDrMnl[1][0]<<4;
	giAwbDrIIR = giDbDrMnl[1][1]<<4;
	gnAwbRGainIIR = AWB_GAIN_DFLT<<4;
	gnAwbBGainIIR = AWB_GAIN_DFLT<<4;
	
	UINT i;
	for (i=0; i<4; i++) giAwbPrstTbl[i] = (UD(UdAwbPrst+(i*4)+3)<<24) | (UD(UdAwbPrst+(i*4)+2)<<16) | (UD(UdAwbPrst+(i*4)+1)<<8) | (UD(UdAwbPrst+(i*4)+0)<<0);

	if(gbColorMapParInit){
//		TxStrNoIRQ("ColorMap Data Init ! ", 0, 0);
		DfltColorMapSave();
		gbColorMapParInit = 0;
	}
	
	else{
//		TxStrNoIRQ("Load ColorMap Data from memory ! ", 0, 0);
		SftoISP_CmLoad();
	}

	if (MP(MpAwb)==MN_AWB_AUTOEXT)	AwbCmapSet(1, (UINT*)gnCmap);
	else							AwbCmapSet(0, gnCmapCstm);

	
//#if (model_Save==0)		// EEPROM only
//	TwiRdEep(TWI_EEP_AWBPRST_STT , (BYTE*)giAwbPrstTbl, 16);
//#else
//
//#endif

	UINT j;
	for(j=0; j<9; j++) {
		for(i=0; i<6; i++) {
//			const float a = (float)glMtxCf[j][i];
			const float a = (float)glMtxCf_cstm[j][i];
			gf32MtxCf[j][i] = TOFLOAT32(a);
		}
	}

	//extern float gfAwbMatGain2;
	const float gfAwbMatGain2 = (double)AWB_MTRX_GAIN * 256. / 100000000000000.;

	extern float32 gf32AwbMatGain;
	gf32AwbMatGain = TOFLOAT32(gfAwbMatGain2);

#if(model_Sens == SENS_OX03C10)
	SPD_PreCCM();
#endif
}


void ISPM AwbTest(void)
{
	//CMatrix Setting
//	AwbCmapSet(0, (UINT*)gnCmap);
	
#if(0)
	//Main Window
	
	AWB_WIN1_HSPw(PAR01);
	AWB_WIN1_HWw(PAR02);
	AWB_WIN1_VSPw(PAR03);
	AWB_WIN1_VWw(PAR04);

	AWB_CHSELw(PAR05);
	
	//Sub Window
	AWB_SUBWIN_SPCw(PAR06);
	AWB_SUBWIN_HSPw(PAR07);
	AWB_SUBWIN_VSPw(PAR08);
	
	static UINT nCCT_SUM, nDB_SUM, nDR_SUM = 0x0;

	if(PAR00==0x1){
		nCCT_SUM = AWBL_CCT_SUM0_LOCKr; 
		nDB_SUM = AWBL_DB_SUM0_LOCKr;
		nDR_SUM = AWBL_DR_SUM0_LOCKr; 
	}
	else if(PAR00==0x2){
		nCCT_SUM = AWBL_CCT_SUM1_LOCKr; 
		nDB_SUM = AWBL_DB_SUM1_LOCKr;
		nDR_SUM = AWBL_DR_SUM1_LOCKr; 
	}
	else if(PAR00==0x3){
		nCCT_SUM = AWBL_CCT_SUM2_LOCKr; 
		nDB_SUM = AWBL_DB_SUM2_LOCKr;
		nDR_SUM = AWBL_DR_SUM2_LOCKr; 
	}
	else if(PAR00==0x4){
		nCCT_SUM = AWBL_CCT_SUM3_LOCKr; 
		nDB_SUM = AWBL_DB_SUM3_LOCKr;
		nDR_SUM = AWBL_DR_SUM3_LOCKr; 
	}
	else if(PAR00==0x5){
		nCCT_SUM = AWBL_CCT_SUM4_LOCKr; 
		nDB_SUM = AWBL_DB_SUM4_LOCKr;
		nDR_SUM = AWBL_DR_SUM4_LOCKr; 
	}
	else if(PAR00==0x6){
		nCCT_SUM = AWBL_CCT_SUM5_LOCKr; 
		nDB_SUM = AWBL_DB_SUM5_LOCKr;
		nDR_SUM = AWBL_DR_SUM5_LOCKr; 
	}
	else if(PAR00==0x7){
		nCCT_SUM = AWBL_CCT_SUM6_LOCKr; 
		nDB_SUM = AWBL_DB_SUM6_LOCKr;
		nDR_SUM = AWBL_DR_SUM6_LOCKr; 
	}
	else if(PAR00==0x8){
		nCCT_SUM = AWBL_CCT_SUM7_LOCKr; 
		nDB_SUM = AWBL_DB_SUM7_LOCKr;
		nDR_SUM = AWBL_DR_SUM7_LOCKr; 
	}

	AWBLOSD_ONw(0x1);
	OZONE_SELw(0x3);
	AWBL_OSD_SELw(0xfb);

	DebugDisp(1, Dec, "CCR_SUM", 0, 0, AWBL_CCR_SUM_LOCKr)
	DebugDisp(1, Dec, "CCG_SUM", 1, 0, AWBL_CCG_SUM_LOCKr)
	DebugDisp(1, Dec, "CCB_SUM", 2, 0, AWBL_CCB_SUM_LOCKr)
	DebugDisp(1, Dec, "CCT_SUM", 3, 0, AWBL_CCT_SUM_LOCKr)
	
	DebugDisp(1, Dec, "R_CL_CNT", 5, 0, AWBL_R_CLCNT_LOCKr)
	DebugDisp(1, Dec, "G_CL_CNT", 6, 0, AWBL_G_CLCNT_LOCKr)
	DebugDisp(1, Dec, "B_CL_CNT", 7, 0, AWBL_B_CLCNT_LOCKr)

	DebugDisp(1, Dec, "R_SL_CNT", 9, 0, AWBL_R_SLCNT_LOCKr)
	DebugDisp(1, Dec, "G_SL_CNT", 10, 0, AWBL_G_SLCNT_LOCKr)
	DebugDisp(1, Dec, "B_SL_CNT", 11, 0, AWBL_B_SLCNT_LOCKr)
	
	DebugDisp(1, Dec, "CCT_SUM", 12, 0, nCCT_SUM)
	DebugDisp(1, Dec, "DB_SUM_", 13, 0, nDB_SUM)
	DebugDisp(1, Dec, "DR_SUM_", 14, 0, nDR_SUM)

#endif	

}

//*************************************************************************************************
// Main Functions
//*************************************************************************************************

void ISPM Awb(void)
{	
	int		iDrSum=0, iDgSum=0, iDbSum=0;
	UINT	nTcnt=0, nHold=0;

	UINT	nRsum,  nGsum,  nBsum,  nRGain, nBGain, nAwbRgain, nAwbGgain, nAwbBgain;

	int		iRcm0=0x100,iRcm1=0x0,iRcm2=0x0,iGcm0=0x0,iGcm1=0x100,iGcm2=0x0,iBcm0=0x0,iBcm1=0x0,iBcm2=0x100;
	UINT	nRcm0,nRcm1,nRcm2,nGcm0,nGcm1,nGcm2,nBcm0,nBcm1,nBcm2;

//	double	oIntpRgain=1,oIntpBgain=1;
	int 	iRWgt, iGWgt, iBWgt;

	int 	iAgcPos,iWgt;
	static BYTE	gbMnAwbBuf;
	WORD 	wAwbAgcMin, wAwbAgcMax;
	UINT	nCtempCur=0;
	int 	iDrSumCal = 0x0;

	gbAwbDebugOn = (gbMnDebugFnc==MN_DBG_AWB);

#if(0)
	AwbTest();
	return;
#endif

//--------------------------------------------------------------------------------------------------
// Exception
#if model_AwbCapOn
	if (gnAwbOdmCapOn) {
		if (gnAwbOdmCapOn==1) 	{ InitAwbOdmCap();	gnAwbOdmCapOn++;}
		else 					{ AwbOdmCap();
			#if(model_Sens == SENS_OX03C10)
			const UINT nCTemp = PAR01;
			OX3C_WBGain(nCTemp);
			#endif	
		}
		return;
	}
#endif

	if(gbModeWdrOn_L){
//		AWB_CHSELw(0x3);
		AWB_CHSELw(0x0);
		AWB_BITSELw(0x0);
	}
	else if(gbModeWdrOn_LFM){
		AWB_CHSELw(0x3);
		AWB_BITSELw(0x7);
	}
#if(model_Sens_CLR_HDR)
	else if(gbModeWdrOn_CLR){
			AWB_CHSELw(0x0);
			AWB_BITSELw(0x5);
	}
#endif
	else{
		AWB_CHSELw(0x0);
		AWB_BITSELw(0x0);
	}

// -------------------------------------------------------------------------------
// AWB Window
	AWB_WIN1_HSPw(UP(UpAWB_HSP));
	AWB_WIN1_HWw(UP(UpAWB_HW));
	AWB_WIN1_VSPw(UP(UpAWB_VSP));
	AWB_WIN1_VWw(UP(UpAWB_VW));

// -------------------------------------------------------------------------------
// AWB Y Slice, Clip, DbDr Offset

	BYTE bSliceOffset = 0x0;
	BYTE bSliceMin = 0xff;

#if(model_AWB_Matrix==0)
	// MP V1.0.0
//	bSliceOffset = LibUtlInterp1D (MINMAX(giCurAgc, 0x110, 0x130), 0x110, 0x130, 0x0, 0x1D);
	bSliceOffset = IntpValAgcPos(gnAe5Sum, 	UP(UpAWB_SLIC_OFST_PT0),  UP(UpAWB_SLIC_OFST_PT1),  UP(UpAWB_SLIC_OFST_PT2),\
											UP(UpAWB_SLIC_OFST_VAL0), UP(UpAWB_SLIC_OFST_VAL1), UP(UpAWB_SLIC_OFST_VAL2));

	bSliceMin	 = LibUtlInterp1D (MINMAX(giCurAgc, 0x110, 0x130), 0x110, 0x130, 0x0, 0x1D);
	bSliceOffset = MAX(bSliceOffset, bSliceMin);

#else
	// MP V1.0.1
	bSliceOffset = LibUtlInterp1D (MINMAX(giCurAgc, 0xD0, 0x130), 0x110, 0x130, 0x0, /*0x20*/0x2D);
#endif

	AWBL_CYSLICEw(MAX((UP(UpAWB_YSLICE)-bSliceOffset), 0x0));		// Y slice
	AWBL_CYCLIPw(UP(UpAWB_YCLIP));			// Y clip

	AWBL0_DBOFFSETw(UP(UpAWB_DBOFFSET));
	AWBL0_DROFFSETw(UP(UpAWB_DROFFSET));

// -------------------------------------------------------------------------------
// ODM Area

	if(gbAwbDebugOn&&(!gbMnBlcOsdOn)) {
		AWBLOSD_ONw(1);
		OZONE_SELw (3);
		/*ODM_OSD_ONw(1);*/
	}
	else {
		AWBLOSD_ONw(0);

		AWB_WIN1_HSPw(UP(UpAWB_HSP));
		AWB_WIN1_HWw(UP(UpAWB_HW));
		AWB_WIN1_VSPw(UP(UpAWB_VSP));
	    AWB_WIN1_VWw(UP(UpAWB_VW));
	}

#if (model_Lens==0)
	if ((!((gbMnDebugFnc>=1)&&(gbMnDebugFnc<=3)))&&(gbMnBlcOsdOn==0)&&(MP(MpShdDet)!=1)/*&&(gbOzone_Hold!=1)*/){OZONE_SELw(0); /*ODM_OSD_ONw(0);*/}		// final OSD Off condition // 150325 WHL
#else
	if ((!((gbMnDebugFnc>=1)&&(gbMnDebugFnc<=3)))&&(gbMnBlcOsdOn==0)&&(MP(MpShdDet)!=1)){OZONE_SELw(0); /*ODM_OSD_ONw(0);*/}		// final OSD Off condition
#endif
//
//--------------------------------------------------------------------------------------------------
// ColorMap Set
	if ((gbDfltColorMapChk)||(MP(MpAwb)!=gbMnAwbBuf)) {
		switch (MP(MpAwb)) {
			case MN_AWB_AUTO 	: 	AwbCmapSet(0, gnCmapCstm);		break;
			case MN_AWB_AUTOEXT : 	AwbCmapSet(1, (UINT*)gnCmap); 	break;
			default				: 	  								break;
		}
		gbDfltColorMapChk = 0;
	}
	gbMnAwbBuf = MP(MpAwb);

//--------------------------------------------------------------------------------------------------
// Color Matrix control
	nTcnt		= AWBL_CCT_SUM_LOCKr ;					// Total block cnt
	iDrSum		= AWBL_CRDR_SUM_LOCKr;     				// CR/DR(32b sign)
	iDgSum		= AWBL_CY_SUM_LOCKr  ;					// CY	(31b)
	iDbSum		= AWBL_CBDB_SUM_LOCKr;	     			// CB/DB(32b sign)

	nHold = (nTcnt<(UINT)UP(UpAWB_TCNT_LMT))? 1 : 0;											// AWB Hold flag by block cnt.

	if (MP(MpAwb)==MN_AWB_MNL){														// Manual Matrix
		switch (MP(MpAwbMnl)) {
			case MN_3sLOW :	iDbSum	= giDbDrMnl[MN_3sLOW][0];		iDrSum  = giDbDrMnl[MN_3sLOW][1];	break;
			case MN_3sMID :	iDbSum	= giDbDrMnl[MN_3sMID][0];		iDrSum	= giDbDrMnl[MN_3sMID][1];	break;
			case MN_3sHI  :	iDbSum	= giDbDrMnl[MN_3sHI][0] ;		iDrSum	= giDbDrMnl[MN_3sHI][1];	break;
			default 			: 	break;
		}
	}
	// AGC MAX & Hold : Low light
	else if((giCurAgc > UP(UpAWB_5000K_AGC_TH))&&(nHold&0x1)){
		iDbSum	= giDbDrMnl[MN_3sMID][0];		
		iDrSum	= giDbDrMnl[MN_3sMID][1];
	}
	
	else if ( ((MP(MpAwb)==MN_AWB_PRESET)&&(MP(MpAwbPrst)==MN_OFF)) || (nHold&0x1) ) {	// Hold Matrix
		if (MP(MpAwb)==MN_AWB_PRESET) {
			iDbSum = giAwbPrstTbl[0]>>4;
			iDrSum = giAwbPrstTbl[1]>>4;
		}
		else {
			iDbSum	= giAwbDbIIR >> 4;
			iDrSum	= giAwbDrIIR >> 4;
			nHold  += 0x10;
		}
	}
	else if (MP(MpAwb)==MN_AWB_AUTOEXT) {
		iDbSum	= giDbDrMnl[MN_3sMID][0];
		iDrSum	= giDbDrMnl[MN_3sMID][1];
	}
	else{
	#if(0)
		iDbSum	= iDbSum / (int)nTcnt;												// Pixel mean
		iDrSum	= iDrSum / (int)nTcnt;												// "
	#else
		nTcnt	= MAX(nTcnt, 0x1);
		
		iDrSumCal = iDrSum / (int)nTcnt;

		iDbSum	= giDbDrMnl[MN_3sMID][0];
		iDrSum	= giDbDrMnl[MN_3sMID][1];
	#endif
		iDgSum	= iDgSum / (int)nTcnt;												// "
	}
	
	iDrSumCal	= MIN(iDrSumCal,AWB_DR_MAX);
	iDrSumCal	= MAX(iDrSumCal,AWB_DR_MIN);

	iDbSum 		= MIN(iDbSum,AWB_DB_MAX);											// ODM data limitaion
	iDbSum 		= MAX(iDbSum,AWB_DB_MIN);											// "
	iDrSum 		= MIN(iDrSum,AWB_DR_MAX);           								// "
	iDrSum 		= MAX(iDrSum,AWB_DR_MIN);           								// " max limit

	giDbSum = iDbSum;
	giDrSum = iDrSum;

	giAwbDbIIR 	= ( ((int)UP(UpAWB_SPEED_MTRX)*giAwbDbIIR) + ((int)(0x100-UP(UpAWB_SPEED_MTRX))*(iDbSum<<4)) ) >> 8;
	giAwbDrIIR 	= ( ((int)UP(UpAWB_SPEED_MTRX)*giAwbDrIIR) + ((int)(0x100-UP(UpAWB_SPEED_MTRX))*(iDrSum<<4)) ) >> 8;

	gnAwbErr	= MAX((UINT)ABS((giAwbDbIIR>>4) - iDbSum), (UINT)ABS((giAwbDrIIR>>4) - iDrSum));

	xFUNC_TIME_OSD("AwbCmat", 21, DispDbgX,
		LibAwbCmatF32 ((giAwbDbIIR>>4), (giAwbDrIIR>>4), gf32MtxCf);

		/*if(PAR1A)	LibAwbCmat ((giAwbDbIIR>>4), (giAwbDrIIR>>4), glMtxCf);
		else		LibAwbCmatF32 ((giAwbDbIIR>>4), (giAwbDrIIR>>4), gf32MtxCf);*/
	)

	// Color Temp Calculation
	const UINT nCtempUnitOfst = 1000;
	nCtempCur =  IntpValCtempPos((/*iDrSum*/iDrSumCal+nCtempUnitOfst), UP(UpAWB_TEMP_DR_H), UP(UpAWB_TEMP_DR_M), UP(UpAWB_TEMP_DR_L), UP(UpAWB_TEMP_VAL_H), UP(UpAWB_TEMP_VAL_M), UP(UpAWB_TEMP_VAL_L));

	gbAwb_light = IntpValCtempPos(nCtempCur, UP(UpAWB_TEMP_VAL_H), UP(UpAWB_TEMP_VAL_M), UP(UpAWB_TEMP_VAL_L), 0x0, 0x1, 0x2);
		
#if(model_Sens == SENS_OX03C10)
	OX3C_WBGain(nCtempCur);
#endif

// ------------------------------------------------------------------
// Apply Pre ODM Matrix  (Sign[11], Integer[10:8], Float[7:0])
//
	if (!TestMnl) {
		iRcm0 =  MIN(giCmat[0][0],2047);	iRcm0 =  MAX(iRcm0,0    );
		iRcm1 =  MIN(giCmat[0][1],2047);	iRcm1 =  MAX(iRcm1,-2047);
		iRcm2 =  MIN(giCmat[0][2],2047);	iRcm2 =  MAX(iRcm2,-2047);
		iGcm0 =  MIN(giCmat[1][0],2047);	iGcm0 =  MAX(iGcm0,-2047);
		iGcm1 =  MIN(giCmat[1][1],2047);	iGcm1 =  MAX(iGcm1,0	);
		iGcm2 =  MIN(giCmat[1][2],2047);	iGcm2 =  MAX(iGcm2,-2047);
		iBcm0 =  MIN(giCmat[2][0],2047);	iBcm0 =  MAX(iBcm0,-2047);
		iBcm1 =  MIN(giCmat[2][1],2047);	iBcm1 =  MAX(iBcm1,-2047);
		iBcm2 =  MIN(giCmat[2][2],2047);	iBcm2 =  MAX(iBcm2,0    );
	}
	else {	// Manual control (affect to Post Matrix)
		iRcm0 = ((PRR_GAINr)>>11) ? -(PRR_GAINr&BitMask_11) : (PRR_GAINr&BitMask_11);
		iRcm1 = ((PRG_GAINr)>>11) ? -(PRG_GAINr&BitMask_11) : (PRG_GAINr&BitMask_11);
		iRcm2 = ((PRB_GAINr)>>11) ? -(PRB_GAINr&BitMask_11) : (PRB_GAINr&BitMask_11);
		iGcm0 = ((PGR_GAINr)>>11) ? -(PGR_GAINr&BitMask_11) : (PGR_GAINr&BitMask_11);
		iGcm1 = ((PGG_GAINr)>>11) ? -(PGG_GAINr&BitMask_11) : (PGG_GAINr&BitMask_11);
		iGcm2 = ((PGB_GAINr)>>11) ? -(PGB_GAINr&BitMask_11) : (PGB_GAINr&BitMask_11);
		iBcm0 = ((PBR_GAINr)>>11) ? -(PBR_GAINr&BitMask_11) : (PBR_GAINr&BitMask_11);
		iBcm1 = ((PBG_GAINr)>>11) ? -(PBG_GAINr&BitMask_11) : (PBG_GAINr&BitMask_11);
		iBcm2 = ((PBB_GAINr)>>11) ? -(PBB_GAINr&BitMask_11) : (PBB_GAINr&BitMask_11);
	}

	nRcm0 = ABS(iRcm0);					nRcm0 =  						    nRcm0;
	nRcm1 = ABS(iRcm1);     			nRcm1 = (iRcm1<0) ? (1<<11)|nRcm1 : nRcm1;
	nRcm2 = ABS(iRcm2);     			nRcm2 = (iRcm2<0) ? (1<<11)|nRcm2 : nRcm2;
	nGcm0 = ABS(iGcm0);     			nGcm0 = (iGcm0<0) ? (1<<11)|nGcm0 : nGcm0;
	nGcm1 = ABS(iGcm1);     			nGcm1 =  							nGcm1;
	nGcm2 = ABS(iGcm2);     			nGcm2 = (iGcm2<0) ? (1<<11)|nGcm2 : nGcm2;
	nBcm0 = ABS(iBcm0);     			nBcm0 = (iBcm0<0) ? (1<<11)|nBcm0 : nBcm0;
	nBcm1 = ABS(iBcm1);     			nBcm1 = (iBcm1<0) ? (1<<11)|nBcm1 : nBcm1;
	nBcm2 = ABS(iBcm2);     			nBcm2 =  							nBcm2;

	// Pre mat (temp)
	PRR_GAINw(nRcm0);
	PRG_GAINw(nRcm1);
	PRB_GAINw(nRcm2);
	PGR_GAINw(nGcm0);
	PGG_GAINw(nGcm1);
	PGB_GAINw(nGcm2);
	PBR_GAINw(nBcm0);
	PBG_GAINw(nBcm1);
	PBB_GAINw(nBcm2);

//-------------------------------------------------------------------------------------------------
// RGB gain control
	nRsum 	= AWBL_CCR_SUM_LOCKr;					// R from Pre ODM Mat
	nGsum 	= AWBL_CCG_SUM_LOCKr;   				// G "
	nBsum 	= AWBL_CCB_SUM_LOCKr; 					// B "

	if (MP(MpAwb)==MN_AWB_MNL){													// Manual Gain
		nRsum 	= 0;
		nGsum 	= 0;
		nBsum 	= 0;

		// 171211 LH
		nRGain  = (((int)MP(MpRgain)-10)>=0) ? (UINT)((MP(MpRgain)-10)*AWB_GAIN_STEP_H)+AWB_GAIN_DFLT :
											   (UINT)((MP(MpRgain)   )*AWB_GAIN_STEP_L)+AWB_GAIN_MIN  ;
		nBGain  = (((int)MP(MpBgain)-10)>=0) ? (UINT)((MP(MpBgain)-10)*AWB_GAIN_STEP_H)+AWB_GAIN_DFLT :
											   (UINT)((MP(MpBgain)   )*AWB_GAIN_STEP_L)+AWB_GAIN_MIN  ;

	}
	// AGC MAX & Hold : Low light
	else if((giCurAgc > UP(UpAWB_5000K_AGC_TH))&&(nHold&0x1)){
		nRsum 	= 0;
		nGsum 	= 0;
		nBsum 	= 0;

		nRGain  = (((int)MP(MpRgain)-10)>=0) ? (UINT)((MP(MpRgain)-10)*AWB_GAIN_STEP_H)+AWB_GAIN_DFLT :
											   (UINT)((MP(MpRgain)   )*AWB_GAIN_STEP_L)+AWB_GAIN_MIN  ;
		nBGain  = (((int)MP(MpBgain)-10)>=0) ? (UINT)((MP(MpBgain)-10)*AWB_GAIN_STEP_H)+AWB_GAIN_DFLT :
											   (UINT)((MP(MpBgain)   )*AWB_GAIN_STEP_L)+AWB_GAIN_MIN  ;
	}
	
	else if ( ((MP(MpAwb)==MN_AWB_PRESET)&&(MP(MpAwbPrst)==MN_OFF)) || (nHold&0x1) ) {	// Hold Gain
		if (MP(MpAwb)==MN_AWB_PRESET) {					// Preset save example
			nRGain = giAwbPrstTbl[2]>>4;
			nBGain = giAwbPrstTbl[3]>>4;
		}
		else {
			nRGain  = gnAwbRGainIIR >> 4;
			nBGain  = gnAwbBGainIIR >> 4;
			nHold  += 0x100;
		}
		nRsum 	= 0;
		nGsum 	= 0;
		nBsum 	= 0;
	}
	else {																		// Auto Gain
		nTcnt 	= MAX(nTcnt, 1);

		nRsum 	= nRsum / nTcnt;
		nGsum 	= nGsum / nTcnt;
		nBsum 	= nBsum / nTcnt;

		nRsum 	= MAX(nRsum, 1);
		nGsum 	= MAX(nGsum, 1);
		nBsum 	= MAX(nBsum, 1);

//		nRGain  = (nGsum*AWB_GAIN_DFLT) / ((nRsum*AWB_GAIN_DFLT)/(gnAwbRGainIIR>>4));				// gain with default offset		// new
//		nBGain  = (nGsum*AWB_GAIN_DFLT) / ((nBsum*AWB_GAIN_DFLT)/(gnAwbBGainIIR>>4));				// "							// new

		nRGain = (nGsum*AWB_GAIN_DFLT)/nRsum;								// gain with default offset
		nBGain = (nGsum*AWB_GAIN_DFLT)/nBsum;
	}

	nRGain		= MAX(AWB_GAIN_MIN, nRGain);									// Gain limitation
	nRGain		= MIN(AWB_GAIN_MAX, nRGain);              						//	"
	nBGain		= MAX(AWB_GAIN_MIN, nBGain);      	    						//	"
	nBGain		= MIN(AWB_GAIN_MAX, nBGain);    	        					//	"

	gnAwbRGainIIR 	= ( (AWB_SPEED_GAIN*gnAwbRGainIIR) + ((0x100-AWB_SPEED_GAIN)*(nRGain<<4)) ) >> 8;
	gnAwbBGainIIR 	= ( (AWB_SPEED_GAIN*gnAwbBGainIIR) + ((0x100-AWB_SPEED_GAIN)*(nBGain<<4)) ) >> 8;

	gnAwbErr	= MAX(gnAwbErr, (UINT)ABS((int)(gnAwbRGainIIR>>4) - (int)nRGain));
	gnAwbErr	= MAX(gnAwbErr, (UINT)ABS((int)(gnAwbBGainIIR>>4) - (int)nBGain));

//-------------------------------------------------------------------------------------------------
// Final Gain with weights		
	if (!TestMnl) {
		
		wAwbAgcMin = (gbModeWdrOn_L)?UP(UpAWB_WDR_AGC_MIN):UP(UpAWB_AGC_MIN);
		wAwbAgcMax = (gbModeWdrOn_L)?UP(UpAWB_WDR_AGC_MAX):UP(UpAWB_AGC_MAX);
		
		iAgcPos = (giCurAgc<=wAwbAgcMin) ? 0 :
				  (giCurAgc<=wAwbAgcMax) ? 1 : 2;

		switch (iAgcPos) {
			case 0 :	iWgt 	= AWB_AGC_WGT_MAX;	break;
			case 1 :	iWgt 	= LibUtlInterp1D (giCurAgc, wAwbAgcMin, wAwbAgcMax, AWB_AGC_WGT_MAX, UP(UpAWB_AGC_WGT_MIN)); break;
			case 2 :	iWgt 	= UP(UpAWB_AGC_WGT_MIN);	break;
		}

		iWgt = (gnTdnChkOut==TDN_DAY)? iWgt : 0;			// Day or B&W

	#if(0)
		// ---------------------
		int iDrCur = iDrSum, iWgt2;
		iDrCur = MAX(iDrCur, giDbDrMnl[1][1]);
		iDrCur = MIN(iDrCur, AWB_DR_MAX);
		iWgt2  = LibUtlInterp1D (iDrCur, giDbDrMnl[1][1], AWB_DR_MAX, AWB_AGC_WGT_MAX, (((AWB_AGC_WGT_MAX-UP(UpAWB_AGC_WGT_MIN))<<3)>>4)+UP(UpAWB_AGC_WGT_MIN));
//		DispDat("WGT2____"	, 13, 24, iWgt2);

		iWgt   = MIN(iWgt, iWgt2);
	#else
		// Only Low temp		
		#if(0)
		iRWgt  = LibUtlInterp1D (MINMAX(iDbSum, -UP(UpAWB_LOW_TEMP_DB_MIN), -UP(UpAWB_LOW_TEMP_DB_MAX)), -UP(UpAWB_LOW_TEMP_DB_MIN), -UP(UpAWB_LOW_TEMP_DB_MAX), UP(UpAWB_R_WGT), AWB_AGC_WGT_MAX);					
		iGWgt  = LibUtlInterp1D (MINMAX(iDbSum, -UP(UpAWB_LOW_TEMP_DB_MIN), -UP(UpAWB_LOW_TEMP_DB_MAX)), -UP(UpAWB_LOW_TEMP_DB_MIN), -UP(UpAWB_LOW_TEMP_DB_MAX), UP(UpAWB_G_WGT), AWB_AGC_WGT_MAX);					
		iBWgt  = LibUtlInterp1D (MINMAX(iDbSum, -UP(UpAWB_LOW_TEMP_DB_MIN), -UP(UpAWB_LOW_TEMP_DB_MAX)), -UP(UpAWB_LOW_TEMP_DB_MIN), -UP(UpAWB_LOW_TEMP_DB_MAX), UP(UpAWB_B_WGT), AWB_AGC_WGT_MAX);									
		#endif
		
		iRWgt  = 0x100;
		iGWgt  = 0x100;
		iBWgt  = 0x100;

		iRWgt  = MIN(iWgt, iRWgt);	
		iGWgt  = MIN(iWgt, iGWgt);
		iBWgt  = MIN(iWgt, iBWgt);
		
	#endif
		// ---------------------

		#if(0)
		if(MP(MpColorTone)==MN_COOL_TONE){	
			nAwbRgain	= ifdiv8(ifdiv8(((gnAwbRGainIIR>>4) * ((int)(0.5f*256)+(int)(MP(MpSaturation)*(0.05f*256)))) * iWgt));		// iwgt offset 8b, saturation offset 6b
			nAwbGgain	= ifdiv8(ifdiv8( (AWB_GAIN_DFLT 	* ((int)(0.5f*256)+(int)(MP(MpSaturation)*(0.05f*256)))) * iWgt));
			nAwbBgain	= ifdiv8(ifdiv8(((gnAwbBGainIIR>>4) * ((int)(0.5f*256)+(int)(MP(MpSaturation)*(0.05f*256)))) * iWgt));
		}
		else{
			nAwbRgain	= ifdiv8(ifdiv8(((gnAwbRGainIIR>>4) * ((int)(0.5f*256)+(int)(MP(MpSaturation)*(0.067f*256)))) * iWgt));		// iwgt offset 8b, saturation offset 6b
			nAwbGgain	= ifdiv8(ifdiv8( (AWB_GAIN_DFLT 	* ((int)(0.5f*256)+(int)(MP(MpSaturation)*(0.064f*256)))) * iWgt));
			nAwbBgain	= ifdiv8(ifdiv8(((gnAwbBGainIIR>>4) * ((int)(0.5f*256)+(int)(MP(MpSaturation)*(0.067f*256)))) * iWgt));
		}
		#else
		
		if(MP(MpColorTone)==MN_COOL_TONE){	
			nAwbRgain	= ifdiv8(ifdiv8(((gnAwbRGainIIR>>4) * ((int)(0.5f*256)+(int)(MP(MpSaturation)*(0.05f*256)))) * iRWgt));		// iwgt offset 8b, saturation offset 6b
			nAwbGgain	= ifdiv8(ifdiv8( (AWB_GAIN_DFLT 	* ((int)(0.5f*256)+(int)(MP(MpSaturation)*(0.05f*256)))) * iGWgt));
			nAwbBgain	= ifdiv8(ifdiv8(((gnAwbBGainIIR>>4) * ((int)(0.5f*256)+(int)(MP(MpSaturation)*(0.05f*256)))) * iBWgt));
		}
		else{
			nAwbRgain	= ifdiv8(ifdiv8(((gnAwbRGainIIR>>4) * ((int)(0.5f*256)+(int)(MP(MpSaturation)*(0.067f*256)))) * iRWgt));		// iwgt offset 8b, saturation offset 6b
			nAwbGgain	= ifdiv8(ifdiv8( (AWB_GAIN_DFLT 	* ((int)(0.5f*256)+(int)(MP(MpSaturation)*(0.064f*256)))) * iGWgt));
			nAwbBgain	= ifdiv8(ifdiv8(((gnAwbBGainIIR>>4) * ((int)(0.5f*256)+(int)(MP(MpSaturation)*(0.067f*256)))) * iBWgt));
		}

		#endif
	}
	
	else {
		nAwbRgain 	= AWB_GAIN_DFLT;
		nAwbGgain 	= AWB_GAIN_DFLT;
		nAwbBgain 	= AWB_GAIN_DFLT;
	}
	
////-------------------------------------------------------------------------------------------------
//// Post Matrix (final with R,B Gain)(Sign[12], Integer[10:8], Float[7:0])
//


	iRcm0 = (iRcm0 * (int)nAwbRgain) >> 8;				// divide by Gain scale
	iRcm1 = (iRcm1 * (int)nAwbRgain) >> 8;
	iRcm2 = (iRcm2 * (int)nAwbRgain) >> 8;
	iGcm0 = (iGcm0 * (int)nAwbGgain) >> 8;
	iGcm1 = (iGcm1 * (int)nAwbGgain) >> 8;
	iGcm2 = (iGcm2 * (int)nAwbGgain) >> 8;
	iBcm0 = (iBcm0 * (int)nAwbBgain) >> 8;
	iBcm1 = (iBcm1 * (int)nAwbBgain) >> 8;
	iBcm2 = (iBcm2 * (int)nAwbBgain) >> 8;

	PostCCM_Wgt(nCtempCur, &iRcm0, &iRcm1, &iRcm2, &iGcm0, &iGcm1, &iGcm2, &iBcm0, &iBcm1, &iBcm2);

	nRcm0 = ABS(iRcm0);					nRcm0 =  						    nRcm0;
	nRcm1 = ABS(iRcm1);     			nRcm1 = (iRcm1<0) ? (1<<12)|nRcm1 : nRcm1;
	nRcm2 = ABS(iRcm2);     			nRcm2 = (iRcm2<0) ? (1<<12)|nRcm2 : nRcm2;
	nGcm0 = ABS(iGcm0);     			nGcm0 = (iGcm0<0) ? (1<<12)|nGcm0 : nGcm0;
	nGcm1 = ABS(iGcm1);     			nGcm1 =  							nGcm1;
	nGcm2 = ABS(iGcm2);     			nGcm2 = (iGcm2<0) ? (1<<12)|nGcm2 : nGcm2;
	nBcm0 = ABS(iBcm0);     			nBcm0 = (iBcm0<0) ? (1<<12)|nBcm0 : nBcm0;
	nBcm1 = ABS(iBcm1);     			nBcm1 = (iBcm1<0) ? (1<<12)|nBcm1 : nBcm1;
	nBcm2 = ABS(iBcm2);     			nBcm2 =  							nBcm2;
	
	WPRR_GAINw(nRcm0);
	WPRG_GAINw(nRcm1);
	WPRB_GAINw(nRcm2);
	WPGR_GAINw(nGcm0);
	WPGG_GAINw(nGcm1);
	WPGB_GAINw(nGcm2);
	WPBR_GAINw(nBcm0);
	WPBG_GAINw(nBcm1);
	WPBB_GAINw(nBcm2);

//-------------------------------------------------------------------------------------------------
// Preset save example	13.2.22
	static UINT	gnAwbPrstCnt,gnAwbPrstDone=0;

	if((MP(MpAwb)==MN_AWB_PRESET)&&(MP(MpAwbPrst)==MN_ON)) {	// preset key push

		if ((gnAwbPrstCnt>=0x40)&&(gnAwbErr<0x18)&&(!gnAwbPrstDone)) {		// save on condition
			gnAwbPrstCnt = 0;
			giAwbPrstTbl[0] = giAwbDbIIR;
			giAwbPrstTbl[1] = giAwbDrIIR;
			giAwbPrstTbl[2] = (int)gnAwbRGainIIR;
			giAwbPrstTbl[3] = (int)gnAwbBGainIIR;

//			#if (model_Save==0)
//				TwiWrEep(TWI_EEP_AWBPRST_STT , (BYTE*)giAwbPrstTbl, 16);		// save to eep
//			#else
//
//			#endif

			gnAwbPrstDone = 1;

			UINT i;
			for (i=0; i<4; i++)	 UD(UdAwbPrst+ 0+i)	= (giAwbPrstTbl[0]>>(i*8)) & 0xff;
			for (i=0; i<4; i++)	 UD(UdAwbPrst+ 4+i)	= (giAwbPrstTbl[1]>>(i*8)) & 0xff;
            for (i=0; i<4; i++)	 UD(UdAwbPrst+ 8+i)	= (giAwbPrstTbl[2]>>(i*8)) & 0xff;
            for (i=0; i<4; i++)	 UD(UdAwbPrst+12+i)	= (giAwbPrstTbl[3]>>(i*8)) & 0xff;
            gbUsrDataSaveChk = 1;

//			DebugDisp(1, Hex, "Verify", 17, 24, giAwbPrstTbl[0])
//			DebugDisp(1, Hex, "Verify", 18, 24, giAwbPrstTbl[1])
//			DebugDisp(1, Hex, "Verify", 19, 24, giAwbPrstTbl[2])
//			DebugDisp(1, Hex, "Verify", 20, 24, giAwbPrstTbl[3])

		}
		else gnAwbPrstCnt ++;

		gnAwbPrstCnt = MIN(gnAwbPrstCnt, 0x100);

	}
	else {
		gnAwbPrstCnt = 0;
		gnAwbPrstDone = 0;
	}

//	DispDat("prstDB__"	, 16, 24, giAwbPrstTbl[0]);
//	DispDat("prstDR__"	, 17, 24, giAwbPrstTbl[1]);
//	DispDat("prstRG__"	, 18, 24, giAwbPrstTbl[2]);
//	DispDat("prstBG__"	, 19, 24, giAwbPrstTbl[3]);
//	DispDat("prstCNT_"	, 20, 24, gnAwbPrstCnt);
//	DispDat("err_____"	, 21, 24, gnAwbErr);

// -------------------------------------------------------------------------------
// Hue & Gain
	SetHueGain(nCtempCur);

	const WORD wVVD_Fs = IntpValAgcPos(giCurAgc, 	UP(UpVVD_FS_AGC_PT0), UP(UpVVD_FS_AGC_PT1), UP(UpVVD_FS_AGC_PT2),\
													UP(UpVVD_FS_VAL_PT0), UP(UpVVD_FS_VAL_PT1), UP(UpVVD_FS_VAL_PT2));

//	const BYTE bVVD_CW_G = LibUtlInterp1D (giCurAgc, UP(UpVVD_FS_AGC_PT0), UP(UpVVD_FS_AGC_PT1), 0x80, 0x40);
//	const BYTE bVVD_CW_B = LibUtlInterp1D (giCurAgc, UP(UpVVD_FS_AGC_PT0), UP(UpVVD_FS_AGC_PT1), 0x80, 0x40);

	VVD_FSw(wVVD_Fs);
//	VVD_CW_Rw(0x80);
//	VVD_CW_Gw(bVVD_CW_G);
//	VVD_CW_Bw(bVVD_CW_B);
	
//-------------------------------------------------------------------------------------------------
// Interpolator gain
double	oIntpRgain=1,oIntpBgain=1;
oIntpRgain = (double)(iRcm0+iRcm1+iRcm2)/ (double)(iGcm0+iGcm1+iGcm2) ;
oIntpBgain = (double)(iBcm0+iBcm1+iBcm2)/ (double)(iGcm0+iGcm1+iGcm2) ;

oIntpRgain = (oIntpRgain<=0)? 0 : (oIntpRgain * 64.);
oIntpBgain = (oIntpBgain<=0)? 0 : (oIntpBgain * 64.);

//INTP_RGAINw((UINT)((oIntpRgain<=0)? 0 : (oIntpRgain * 64.)));	// x4 under
//INTP_BGAINw((UINT)((oIntpBgain<=0)? 0 : (oIntpBgain * 64.)));

extern int RR_GAIN;
extern int RG_GAIN;
extern int RB_GAIN;
extern int GR_GAIN;
extern int GG_GAIN;
extern int GB_GAIN;
extern int BR_GAIN;
extern int BG_GAIN;
extern int BB_GAIN;
extern  void LibAwbWdrRGB (int, int, int);

RR_GAIN = iRcm0;
RG_GAIN = iRcm1;
RB_GAIN = iRcm2;
GR_GAIN = iGcm0;
GG_GAIN = iGcm1;
GB_GAIN = iGcm2;
BR_GAIN = iBcm0;
BG_GAIN = iBcm1;
BB_GAIN = iBcm2;

LibAwbWdrRGB (1, (gnTdnChkOut==TDN_NIT), 0);

//-------------------------------------------------------------------------------------------------
// Monitoring

#if(GRP_DEBUG_IMG_TUNE)
	GRP3 = nAwbRgain;	
	GRP4 = nAwbBgain;
	GRP5 = nCtempCur;
//	GRP6 = AWBL_CYCLIPr;
//	GRP7 = AWBL_CYSLICEr;
#endif
	
//	DebugDisp(1,Dec ,"AWB_Db_MAX", 32,10, AWB_DB_MAX);
//	DebugDisp(1,Dec ,"AWB_Db_MIN", 33,10, AWB_DB_MIN);
//
//	DebugDisp(1,Dec ,"AWB_Dr_MAX", 34,10, AWB_DR_MAX);
//	DebugDisp(1,Dec ,"AWB_Dr_MIN", 35,10, AWB_DR_MIN);
	
	DebugDisp(gbAwbDebugOn, Dec, "TCNT___d"	,  1, 24, nTcnt 	)
	DebugDisp(gbAwbDebugOn, Dec, "CRDR___d"	,  2, 24, iDrSum	)
	DebugDisp(gbAwbDebugOn, Dec, "CY_____d"	,  3, 24, iDgSum	)
	DebugDisp(gbAwbDebugOn, Dec, "CBDB___d"	,  4, 24, iDbSum	)
	DebugDisp(gbAwbDebugOn, Dec, "R______d"	,  6, 24, nRsum		)
	DebugDisp(gbAwbDebugOn, Dec, "G______d"	,  7, 24, nGsum		)
	DebugDisp(gbAwbDebugOn, Dec, "B______d"	,  8, 24, nBsum		)
	DebugDisp(gbAwbDebugOn,    , "R_Gain__"	, 10, 24, nAwbRgain	)
	DebugDisp(gbAwbDebugOn,    , "B_Gain__"	, 11, 24, nAwbBgain	)
	DebugDisp(gbAwbDebugOn,    , "WGT_____"	, 12, 24, iWgt		)
	DebugDisp(gbAwbDebugOn,    , "Hold____"	, 14, 24, nHold		)
	DebugDisp(gbAwbDebugOn,    , "Done____"	, 15, 24, gnAwbErr	)
//	DebugDisp(gbAwbDebugOn,    , "nRGain"	, 15, 24, nRGain	)
//	DebugDisp(gbAwbDebugOn,    , "nBGain"	, 16, 24, nBGain	)

	DebugDisp(gbAwbDebugOn,    , "DR_VAL__"	, 17, 24, iDrSumCal+nCtempUnitOfst)
	DebugDisp(gbAwbDebugOn, Dec, "C_TEMP_d"	, 18, 24, nCtempCur )
	
	DebugDisp(gbAwbDebugOn,    , "WGT_____"	, 20, 24, iWgt	)		
	DebugDisp(gbAwbDebugOn,    , "R_Wgt___"	, 21, 24, iRWgt	)		
	DebugDisp(gbAwbDebugOn,    , "G_Wgt___"	, 22, 24, iGWgt	)		
	DebugDisp(gbAwbDebugOn,    , "B_Wgt___"	, 23, 24, iBWgt	)	

}	// end of AWB


//-------------------------------------------------------------------------------------------------
//Default Gamma Set
void ISPM2 SetDefltColorMap(UINT* apnColorMapTbl, UINT* apnDfltColorMapTbl)
{
	int i;
	UINT nColorMapBuf = 0x0;
	
	for(i = 0; i < 128; i++)	*(apnColorMapTbl+i) = *(apnDfltColorMapTbl+(i*2));

	//Default Gamma Save
	for(i = 0; i < 128; i++){
		nColorMapBuf = *(apnColorMapTbl+i);
		UD(UdColorMap+(i*4)+0) = (nColorMapBuf>>24)&0xFF;
		UD(UdColorMap+(i*4)+1) = (nColorMapBuf>>16)&0xFF;
		UD(UdColorMap+(i*4)+2) = (nColorMapBuf>> 8)&0xFF;
		UD(UdColorMap+(i*4)+3) = (nColorMapBuf>> 0)&0xFF;
	}
}

void ISPM2 DfltColorMapSave(void)
{
	SetDefltColorMap(gnCmapCstm, (UINT*)gnCmap);	

	if(gbColorMapParInit)	gbUsrDataSaveChk = 1;
}

//-------------------------------------------------------------------------------------------------
//ColorMap Save
void ISPM2 ColorMapSave(void)
{
	int i;
	UINT nColorMapBuf = 0x0;

	for(i = 0; i < 128; i++){
		nColorMapBuf = GetIsp(AWBL_CM_BASE+i);
		UD(UdColorMap+(i*4)+0) = (nColorMapBuf>>24)&0xFF;
		UD(UdColorMap+(i*4)+1) = (nColorMapBuf>>16)&0xFF;
		UD(UdColorMap+(i*4)+2) = (nColorMapBuf>> 8)&0xFF;
		UD(UdColorMap+(i*4)+3) = (nColorMapBuf>> 0)&0xFF;
	}
}

void ISPM2 ISPtoSf_CmSave(void)
{// Save ColorMap from flash memory
	ColorMapSave();
	
	// Save ROM
	gbUsrDataSaveChk = 1;
}

//-------------------------------------------------------------------------------------------------
//ColorMap Load
void ISPM2 ColorMapLoad(UINT* apnMapTbl)
{
	int i;
	for(i = 0; i < 128; i++){
		apnMapTbl[i] = ((UD(UdColorMap+(i*4)+0)<<24)|(UD(UdColorMap+(i*4)+1)<<16)|(UD(UdColorMap+(i*4)+2)<<8)|UD(UdColorMap+(i*4)+3));
	}
}

void ISPM2 SftoISP_CmLoad(void)
{// Load ColorMap from flash memory

	ColorMapLoad(gnCmapCstm);
}	

void SetHueGain(int aiCT)
{
	BYTE BYGAINN, BYGAINP, RYGAINN, RYGAINP;
	BYTE BYHUEN , BYHUEP , RYHUEN , RYHUEP;
	BYTE RYGAINP_MINUS;
	BYTE RYGAINN_MINUS;
	BYTE BYGAINP_MINUS;
	BYTE BYGAINN_MINUS;
	
	BYGAINN = IntpValAgcPos(aiCT, UP(UpHnG_TEMP_L), UP(UpHnG_TEMP_M), UP(UpHnG_TEMP_H), UP(UpBY_GAINN_TEMP_L), UP(UpBY_GAINN_TEMP_M), UP(UpBY_GAINN_TEMP_H));
	BYGAINP = IntpValAgcPos(aiCT, UP(UpHnG_TEMP_L), UP(UpHnG_TEMP_M), UP(UpHnG_TEMP_H), UP(UpBY_GAINP_TEMP_L), UP(UpBY_GAINP_TEMP_M), UP(UpBY_GAINP_TEMP_H));
	RYGAINN = IntpValAgcPos(aiCT, UP(UpHnG_TEMP_L), UP(UpHnG_TEMP_M), UP(UpHnG_TEMP_H), UP(UpRY_GAINN_TEMP_L), UP(UpRY_GAINN_TEMP_M), UP(UpRY_GAINN_TEMP_H));
	RYGAINP = IntpValAgcPos(aiCT, UP(UpHnG_TEMP_L), UP(UpHnG_TEMP_M), UP(UpHnG_TEMP_H), UP(UpRY_GAINP_TEMP_L), UP(UpRY_GAINP_TEMP_M), UP(UpRY_GAINP_TEMP_H));
	
	BYHUEN  = IntpValAgcPos(aiCT, UP(UpHnG_TEMP_L), UP(UpHnG_TEMP_M), UP(UpHnG_TEMP_H), UP(UpBY_HUEN_TEMP_L), UP(UpBY_HUEN_TEMP_M), UP(UpBY_HUEN_TEMP_H));
	BYHUEP  = IntpValAgcPos(aiCT, UP(UpHnG_TEMP_L), UP(UpHnG_TEMP_M), UP(UpHnG_TEMP_H), UP(UpBY_HUEP_TEMP_L), UP(UpBY_HUEP_TEMP_M), UP(UpBY_HUEP_TEMP_H));
	RYHUEN  = IntpValAgcPos(aiCT, UP(UpHnG_TEMP_L), UP(UpHnG_TEMP_M), UP(UpHnG_TEMP_H), UP(UpRY_HUEN_TEMP_L), UP(UpRY_HUEN_TEMP_M), UP(UpRY_HUEN_TEMP_H));
	RYHUEP  = IntpValAgcPos(aiCT, UP(UpHnG_TEMP_L), UP(UpHnG_TEMP_M), UP(UpHnG_TEMP_H), UP(UpRY_HUEP_TEMP_L), UP(UpRY_HUEP_TEMP_M), UP(UpRY_HUEP_TEMP_H));

	// Exception
	BYHUEN = (MINMAX(BYHUEN, 0x1, 0xFF)+0x80);
	BYHUEP = (MINMAX(BYHUEP, 0x1, 0xFF)+0x80);
	RYHUEN = (MINMAX(RYHUEN, 0x1, 0xFF)+0x80);
	RYHUEP = (MINMAX(RYHUEP, 0x1, 0xFF)+0x80);

	RYGAINP_MINUS = LibUtlInterp1D (MINMAX(giCurAgc, 0x80, 0x100), 0x80, 0x100, RYGAINP, RYGAINP/*-0x15*/-0x8 );
	RYGAINN_MINUS = LibUtlInterp1D (MINMAX(giCurAgc, 0x80, 0x100), 0x80, 0x100, RYGAINN, RYGAINN/*-0x10*/ );
	BYGAINP_MINUS = LibUtlInterp1D (MINMAX(giCurAgc, 0x80, 0x100), 0x80, 0x100, BYGAINP, BYGAINP/*-0x8 */ );
	BYGAINN_MINUS = LibUtlInterp1D (MINMAX(giCurAgc, 0x80, 0x100), 0x80, 0x100, BYGAINN, BYGAINN-0x8  );

	// Register Write
	BYGAINNw(/*BYGAINN*/BYGAINN_MINUS);
	BYGAINPw(/*BYGAINP*/BYGAINP_MINUS);
	RYGAINNw(/*RYGAINN*/RYGAINN_MINUS);
	RYGAINPw(/*RYGAINP*/RYGAINP_MINUS);

	BYHUENw (BYHUEN );
	BYHUEPw (BYHUEP );
	RYHUENw (RYHUEN );
	RYHUEPw (RYHUEP );

	// NBYGAINNw(MP(MpColorSat));
	// NBYGAINPw(MP(MpColorSat));
	// NRYGAINNw(MP(MpColorSat));
	// NRYGAINPw(MP(MpColorSat));

	// NBYHUENw ((MINMAX(MP(MpColorHue), 0x1, 0xFF)+0x80)&0xFF);
	// NBYHUEPw ((MINMAX(MP(MpColorHue), 0x1, 0xFF)+0x80)&0xFF);
	// NRYHUENw ((MINMAX(MP(MpColorHue), 0x1, 0xFF)+0x80)&0xFF);
	// NRYHUEPw ((MINMAX(MP(MpColorHue), 0x1, 0xFF)+0x80)&0xFF);
}

void PostCCM_Wgt(int aiCT, int* apiRR, int* apiRG, int* apiRB, int* apiGR, int* apiGG, int* apiGB, int* apiBR, int* apiBG, int* apiBB)
{
	UINT nPRR, nPRG, nPRB;
	UINT nPGR, nPGG, nPGB;
	UINT nPBR, nPBG, nPBB; 

	// 0x100 : x1
	nPRR = IntpValAgcPos(aiCT, UP(UpCCM_TEMP_L), UP(UpCCM_TEMP_M), UP(UpCCM_TEMP_H), UP(UpCCM_RR_TEMP_L), UP(UpCCM_RR_TEMP_M), UP(UpCCM_RR_TEMP_H));
	nPRG = IntpValAgcPos(aiCT, UP(UpCCM_TEMP_L), UP(UpCCM_TEMP_M), UP(UpCCM_TEMP_H), UP(UpCCM_RG_TEMP_L), UP(UpCCM_RG_TEMP_M), UP(UpCCM_RG_TEMP_H));
	nPRB = IntpValAgcPos(aiCT, UP(UpCCM_TEMP_L), UP(UpCCM_TEMP_M), UP(UpCCM_TEMP_H), UP(UpCCM_RB_TEMP_L), UP(UpCCM_RB_TEMP_M), UP(UpCCM_RB_TEMP_H));
	nPGR = IntpValAgcPos(aiCT, UP(UpCCM_TEMP_L), UP(UpCCM_TEMP_M), UP(UpCCM_TEMP_H), UP(UpCCM_GR_TEMP_L), UP(UpCCM_GR_TEMP_M), UP(UpCCM_GR_TEMP_H));	
	nPGG = IntpValAgcPos(aiCT, UP(UpCCM_TEMP_L), UP(UpCCM_TEMP_M), UP(UpCCM_TEMP_H), UP(UpCCM_GG_TEMP_L), UP(UpCCM_GG_TEMP_M), UP(UpCCM_GG_TEMP_H));	
	nPGB = IntpValAgcPos(aiCT, UP(UpCCM_TEMP_L), UP(UpCCM_TEMP_M), UP(UpCCM_TEMP_H), UP(UpCCM_GB_TEMP_L), UP(UpCCM_GB_TEMP_M), UP(UpCCM_GB_TEMP_H));
	nPBR = IntpValAgcPos(aiCT, UP(UpCCM_TEMP_L), UP(UpCCM_TEMP_M), UP(UpCCM_TEMP_H), UP(UpCCM_BR_TEMP_L), UP(UpCCM_BR_TEMP_M), UP(UpCCM_BR_TEMP_H));	
	nPBG = IntpValAgcPos(aiCT, UP(UpCCM_TEMP_L), UP(UpCCM_TEMP_M), UP(UpCCM_TEMP_H), UP(UpCCM_BG_TEMP_L), UP(UpCCM_BG_TEMP_M), UP(UpCCM_BG_TEMP_H));	
	nPBB = IntpValAgcPos(aiCT, UP(UpCCM_TEMP_L), UP(UpCCM_TEMP_M), UP(UpCCM_TEMP_H), UP(UpCCM_BB_TEMP_L), UP(UpCCM_BB_TEMP_M), UP(UpCCM_BB_TEMP_H));

	*apiRR = (*apiRR * (int)nPRR) >> 8;				// divide by Gain scale
	*apiRG = (*apiRG * (int)nPRG) >> 8;
	*apiRB = (*apiRB * (int)nPRB) >> 8;
	*apiGR = (*apiGR * (int)nPGR) >> 8;
	*apiGG = (*apiGG * (int)nPGG) >> 8;
	*apiGB = (*apiGB * (int)nPGB) >> 8;
	*apiBR = (*apiBR * (int)nPBR) >> 8;
	*apiBG = (*apiBG * (int)nPBG) >> 8;
	*apiBB = (*apiBB * (int)nPBB) >> 8;
}

#if(model_Sens == SENS_OX03C10)
void OX3C_WBGain(UINT anCtemp)
{
	UINT i = 0;
	
	WORD wRGB_LPD[4] = {0,};
	WORD wRGB_SPD[4] = {0,};
	WORD wRGB_Inv[4] = {0,};
	

	for(i = 0; i < 4; i++)	{
		wRGB_LPD[i] = IntpValAgcPos(anCtemp, UP(UpCCM_TEMP_L), UP(UpCCM_TEMP_M), UP(UpCCM_TEMP_H), gwLPDWbGain[0][i], gwLPDWbGain[1][i], gwLPDWbGain[2][i]);	//LPD : B, Gb, Gr, R
		wRGB_SPD[i] = IntpValAgcPos(anCtemp, UP(UpCCM_TEMP_L), UP(UpCCM_TEMP_M), UP(UpCCM_TEMP_H), gwSPDWbGain[0][i], gwSPDWbGain[1][i], gwSPDWbGain[2][i]);	//SPD : B, Gb, Gr, R
		wRGB_Inv[i] = IntpValAgcPos(anCtemp, UP(UpCCM_TEMP_L), UP(UpCCM_TEMP_M), UP(UpCCM_TEMP_H), gwLPDWbRvsGain[0][i], gwLPDWbRvsGain[1][i], gwLPDWbRvsGain[2][i]);	//LPD Inverse : B, Gb, Gr, R
	}

	LPD_RGBGain(*(wRGB_LPD+0), *(wRGB_LPD+1), *(wRGB_LPD+2), *(wRGB_LPD+3));
	SPD_RGBGain(*(wRGB_SPD+0), *(wRGB_SPD+1), *(wRGB_SPD+2), *(wRGB_SPD+3));

	LPD_InvRGBGain(*(wRGB_Inv+0), *(wRGB_Inv+1), *(wRGB_Inv+2), *(wRGB_Inv+3));
}
#endif

