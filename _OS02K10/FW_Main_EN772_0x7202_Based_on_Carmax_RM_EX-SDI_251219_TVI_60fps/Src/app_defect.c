/* ************************************************************************************************
File Name	: 	app_defect.c
Description 	:	EN772 - Defect Correction
Designer		:	Lee, Gyu Hong
Date			:	21-04-20
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
************************************************************************************************* */

#include "dev.h"

//*************************************************************************************************
// Top
//-------------------------------------------------------------------------------------------------
// Auto Defect
const int DefectDifGaTbl[3]  = {0x20, 0x30, 0x40};		// AUTO Defect gain table (Low Agc, Mid Agc, Hi Agc)
const int DefectSDifGaTbl[3] = {0x10, 0x08, 0x00};		// AUTO Defect spot gain table (Low Agc, Mid Agc, Hi Agc)

//const int DefectOfs_S[3] = {0x30, 0x90, 0xFF};
const int DefectOfs_S[3] = {0x30, 0x30, 0x60};
	
void ISPM2 Defect(void)		// 180104 LH
{	// Auto Defect correction
	
	BYTE bDifGain=0, bDfSGain = 0;

	#if(model_Sens_CLR_HDR)
		#if(model_Sens==SENS_OS02K10)
			DF_BITw(0x5);			// High PWL Curve
		#else
			DF_BITw(0x7);			// High PWL Curve
		#endif
	#endif

	bDifGain = IntpValAgcPos(giCurAgc, UP(UpDEFECT_AGC_PT0), UP(UpDEFECT_AGC_PT1), UP(UpDEFECT_AGC_PT2), DefectDifGaTbl[0], DefectDifGaTbl[1], DefectDifGaTbl[2]);
	bDifGain = MIN(((bDifGain * UP(UpDEFECT_GA))>>7), 0xFF);

	bDfSGain = IntpValAgcPos(giCurAgc, UP(UpDEFECT_AGC_PT0), UP(UpDEFECT_AGC_PT1), UP(UpDEFECT_AGC_PT2), DefectSDifGaTbl[0], DefectSDifGaTbl[1], DefectSDifGaTbl[2]);
	bDfSGain = MIN(((bDfSGain * UP(UpDEFECT_SPOT_GA))>>7), 0x3F);

	DF_DIFGA_Lw(bDifGain);
	DFS_DIFGA_Lw(bDfSGain);


	BYTE bDifOfs_S = 0x0;
	bDifOfs_S = IntpValAgcPos(giCurAgc, UP(UpDEFECT_AGC_PT0), UP(UpDEFECT_AGC_PT1), UP(UpDEFECT_AGC_PT2), DefectOfs_S[0], DefectOfs_S[1], DefectOfs_S[2]);
	
	if(gbModeWdrOn_L){
		DF_DIFGA_Sw(0x80);
//		DF_DIFOFS_Sw(0x30);
		DF_DIFOFS_Sw(bDifOfs_S);
	}

	DF_TSEL_Lw(UP(UpDEFECT_TSEL));
	DF_TSEL_Sw(UP(UpDEFECT_TSEL));
	
//	DispDat("DF_GAIN__", 16, 0, iGain);
//	DispDat("DFS_GAIN_", 17, 0, iSGain);
}

