/* **************************************************************************
 File Name	:	app_awb_lib.c
 Description	:	EN772 - Auto White Balance function
 Designer		:	Lee, Hoon
 Modifier		:	Lee, Gyu Hong
 Date		:	13. 8. 4
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "../Src/dev.h"

extern void LibBrkCond(void);

extern int giCmat[3][3];

float32 gf32AwbMatGain;
void ISPM0 LibAwbCmatF32(int aiDb, int aiDr, float32 alMtxCf[9][6])
{

	LibBrkCond();

	UINT		i,j;

	float32		fDb, fDr, fDbDr, fDb2, fDr2;
	float32* 	p = (float32*)alMtxCf;
	float32		fBuf;

	fDb			= _itof(aiDb);
	fDr			= _itof(aiDr);
	fDbDr		= _fmul(fDb, fDr);
	fDb2 		= _fmul(fDb, fDb);
	fDr2 		= _fmul(fDr, fDr);


	for(j=0; j<3; j++) {
		for(i=0; i<3; i++) {
			fBuf = *p++;
			fBuf = _fadd(fBuf, _fmul(*p++, fDb	));
			fBuf = _fadd(fBuf, _fmul(*p++, fDr	));
			fBuf = _fadd(fBuf, _fmul(*p++, fDbDr));
			fBuf = _fadd(fBuf, _fmul(*p++, fDb2	));
			fBuf = _fadd(fBuf, _fmul(*p++, fDr2	));

			giCmat[j][i] = _ftoi(_fmul(fBuf, gf32AwbMatGain));
		}
	}

}


// WDR RGB clip ===============================================================
#define WDR_LCLIPRr				(ValSft_R16(_rd32(_REG_BASE_+(0x0154<<2)))&BitMask_16)
#define WDR_LCLIPRw(val)		_wr32(_REG_BASE_+(0x0154<<2),(UINT)((_rd32(_REG_BASE_+(0x0154<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define WDR_LCLIPGr				(ValSft_R00(_rd32(_REG_BASE_+(0x0154<<2)))&BitMask_16)
#define WDR_LCLIPGw(val)		_wr32(_REG_BASE_+(0x0154<<2),(UINT)((_rd32(_REG_BASE_+(0x0154<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define WDR_LCLIPBr				(ValSft_R16(_rd32(_REG_BASE_+(0x0155<<2)))&BitMask_16)
#define WDR_LCLIPBw(val)		_wr32(_REG_BASE_+(0x0155<<2),(UINT)((_rd32(_REG_BASE_+(0x0155<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define WDR_SCLIPRr				(ValSft_R00(_rd32(_REG_BASE_+(0x0155<<2)))&BitMask_12)
#define WDR_SCLIPRw(val)		_wr32(_REG_BASE_+(0x0155<<2),(UINT)((_rd32(_REG_BASE_+(0x0155<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define WDR_SCLIPGr				(ValSft_R16(_rd32(_REG_BASE_+(0x0156<<2)))&BitMask_12)
#define WDR_SCLIPGw(val)		_wr32(_REG_BASE_+(0x0156<<2),(UINT)((_rd32(_REG_BASE_+(0x0156<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_SCLIPBr				(ValSft_R00(_rd32(_REG_BASE_+(0x0156<<2)))&BitMask_12)
#define WDR_SCLIPBw(val)		_wr32(_REG_BASE_+(0x0156<<2),(UINT)((_rd32(_REG_BASE_+(0x0156<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

int RR_GAIN;
int RG_GAIN;
int RB_GAIN;
int GR_GAIN;
int GG_GAIN;
int GB_GAIN;
int BR_GAIN;
int BG_GAIN;
int BB_GAIN;

void ISPM LibAwbWdrRGB (int aiOn, int aiNight, int aiMon)
{
//	float 	fWdrClipR;
//	float 	fWdrClipG;
//	float 	fWdrClipB;

	hfloat 	fWdrClipR;		// 171207 LH : HW floating
	hfloat 	fWdrClipG;
	hfloat 	fWdrClipB;

//	s64 	fWdrClipR;		// 171211 LH : int floating -> size is too big !
//	s64 	fWdrClipG;
//	s64 	fWdrClipB;

	if (aiOn) {
		// inverse matrix
		const int DET = (RR_GAIN*GG_GAIN*BB_GAIN) + (GR_GAIN*BG_GAIN*RB_GAIN) + (BR_GAIN*RG_GAIN*GB_GAIN) - (RR_GAIN*BG_GAIN*GB_GAIN) - (BR_GAIN*GG_GAIN*RB_GAIN) - (GR_GAIN*RG_GAIN*BB_GAIN);
		const int RR_INV = (GG_GAIN*BB_GAIN)-(GB_GAIN*BG_GAIN);
		const int RG_INV = (RB_GAIN*BG_GAIN)-(RG_GAIN*BB_GAIN);
		const int RB_INV = (RG_GAIN*GB_GAIN)-(RB_GAIN*GG_GAIN);
		const int GR_INV = (GB_GAIN*BR_GAIN)-(GR_GAIN*BB_GAIN);
		const int GG_INV = (RR_GAIN*BB_GAIN)-(RB_GAIN*BR_GAIN);
		const int GB_INV = (RB_GAIN*GR_GAIN)-(RR_GAIN*GB_GAIN);
		const int BR_INV = (GR_GAIN*BG_GAIN)-(GG_GAIN*BR_GAIN);
		const int BG_INV = (RG_GAIN*BR_GAIN)-(RR_GAIN*BG_GAIN);
		const int BB_INV = (RR_GAIN*GG_GAIN)-(RG_GAIN*GR_GAIN);

//		fWdrClipR = (float)(RR_INV+RG_INV+RB_INV)/(float)DET;
//		fWdrClipG = (float)(GR_INV+GG_INV+GB_INV)/(float)DET;
//		fWdrClipB = (float)(BR_INV+BG_INV+BB_INV)/(float)DET;
//		// normalization to 1023
//		const float fWdrClipMax = MAX(MAX(fWdrClipR, fWdrClipG),fWdrClipB);
//		fWdrClipR = aiNight? 0x3ff : ((fWdrClipR/fWdrClipMax)*1023.f);
//		fWdrClipG = aiNight? 0x3ff : ((fWdrClipG/fWdrClipMax)*1023.f);
//		fWdrClipB = aiNight? 0x3ff : ((fWdrClipB/fWdrClipMax)*1023.f);
//
//		WDR_LCLIPRw((int)fWdrClipR);
//		WDR_LCLIPGw((int)fWdrClipG);
//		WDR_LCLIPBw((int)fWdrClipB);
//		WDR_SCLIPRw((int)fWdrClipR);
//		WDR_SCLIPGw((int)fWdrClipG);
//		WDR_SCLIPBw((int)fWdrClipB);

	// 171207 LH : HW floating -------------------------------------------------
		fWdrClipR = _fdiv(i_h(RR_INV+RG_INV+RB_INV), i_h(DET));
		fWdrClipG = _fdiv(i_h(GR_INV+GG_INV+GB_INV), i_h(DET));
		fWdrClipB = _fdiv(i_h(BR_INV+BG_INV+BB_INV), i_h(DET));

	#if(0)
		// normalization to 1023
		const hfloat fWdrClipMax = MAXh(MAXh(fWdrClipR, fWdrClipG),fWdrClipB);
		fWdrClipR = aiNight ? i_h(0x3ff) : _fmul(_fdiv(fWdrClipR,fWdrClipMax),i_h(1023));
		fWdrClipG = aiNight ? i_h(0x3ff) : _fmul(_fdiv(fWdrClipG,fWdrClipMax),i_h(1023));
		fWdrClipB = aiNight ? i_h(0x3ff) : _fmul(_fdiv(fWdrClipB,fWdrClipMax),i_h(1023));
	#else
		// normalization to 4095
		const hfloat fWdrClipMax = MAXh(MAXh(fWdrClipR, fWdrClipG),fWdrClipB);

		#if(1)
		fWdrClipR = aiNight ? i_h(0xfff) : _fmul(_fdiv(fWdrClipR,fWdrClipMax),i_h(4095));
		fWdrClipG = aiNight ? i_h(0xfff) : _fmul(_fdiv(fWdrClipG,fWdrClipMax),i_h(4095));
		fWdrClipB = aiNight ? i_h(0xfff) : _fmul(_fdiv(fWdrClipB,fWdrClipMax),i_h(4095));	
		#else 
		fWdrClipR = aiNight ? i_h(0xfff) : _fmul(_fdiv(fWdrClipR,fWdrClipMax),i_h(PAR02));
		fWdrClipG = aiNight ? i_h(0xfff) : _fmul(_fdiv(fWdrClipG,fWdrClipMax),i_h(PAR02));
		fWdrClipB = aiNight ? i_h(0xfff) : _fmul(_fdiv(fWdrClipB,fWdrClipMax),i_h(PAR02));	
		#endif
	#endif
	
		WDR_LCLIPRw(h_i(fWdrClipR));
		WDR_LCLIPGw(h_i(fWdrClipG));
		WDR_LCLIPBw(h_i(fWdrClipB));
		WDR_SCLIPRw(h_i(fWdrClipR));
		WDR_SCLIPGw(h_i(fWdrClipG));
		WDR_SCLIPBw(h_i(fWdrClipB));
	// ------------------------------------------------------------------------

//  // 171211 LH : int floating -> size is too big !
////		DebugDisp(aiMon,	Dec, "WdrClipR"	, 17, 24, (int)(RR_INV+RG_INV+RB_INV))
////		DebugDisp(aiMon,	Dec, "WdrClipG"	, 18, 24, (int)(GR_INV+GG_INV+GB_INV))
////		DebugDisp(aiMon,	Dec, "WdrClipB"	, 19, 24, (int)(BR_INV+BG_INV+BB_INV))
////		DebugDisp(aiMon,	Dec, "det_____"	, 20, 24, (int)DET)
//
//		fWdrClipR = ((s64)RR_INV+(s64)RG_INV+(s64)RB_INV)<<16/(s64)DET;
//		fWdrClipG = ((s64)GR_INV+(s64)GG_INV+(s64)GB_INV)<<16/(s64)DET;
//		fWdrClipB = ((s64)BR_INV+(s64)BG_INV+(s64)BB_INV)<<16/(s64)DET;
//		DebugDisp(aiMon,	Dec, "WdrClipR"	, 17, 24, (int)fWdrClipR)
//		DebugDisp(aiMon,	Dec, "WdrClipG"	, 18, 24, (int)fWdrClipG)
//		DebugDisp(aiMon,	Dec, "WdrClipB"	, 19, 24, (int)fWdrClipB)
//
//		// normalization to 1023
//		const s64 fWdrClipMax = MAX(MAX(fWdrClipR, fWdrClipG),fWdrClipB);
//		fWdrClipR = aiNight? 0x3ff : (ifmul8(fWdrClipR)/fWdrClipMax)*(s64)1023;
//		fWdrClipG = aiNight? 0x3ff : (ifmul8(fWdrClipG)/fWdrClipMax)*(s64)1023;
//		fWdrClipB = aiNight? 0x3ff : (ifmul8(fWdrClipB)/fWdrClipMax)*(s64)1023;
//
//		WDR_LCLIPRw((int)ifdiv8(fWdrClipR));
//		WDR_LCLIPGw((int)ifdiv8(fWdrClipG));
//		WDR_LCLIPBw((int)ifdiv8(fWdrClipB));
//		WDR_SCLIPRw((int)ifdiv8(fWdrClipR));
//		WDR_SCLIPGw((int)ifdiv8(fWdrClipG));
//		WDR_SCLIPBw((int)ifdiv8(fWdrClipB));
//	// --------------------------------------------------------------------------

		DebugDisp(aiMon,	Dec, "WdrClipR"	, 17, 24, (int)fWdrClipR)
		DebugDisp(aiMon,	Dec, "WdrClipG"	, 18, 24, (int)fWdrClipG)
		DebugDisp(aiMon,	Dec, "WdrClipB"	, 19, 24, (int)fWdrClipB)

	}

}


/* **************************************************************************
 File Name	: 	app_awb_odmcap.c
 Description:	AWB ODM capture module of EN773
 Designer	:	Lee Hoon
 Date		:	11. 9.5
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

void InitAwbOdmCap(void)
{	// Initial From PC command

	// ODM YC matrix	Y  = 0.33R + 0.33G + 0.33B,	Cb = B - Y,	 Cr = R - Y => Db, Dr output
	ODM_M1w(0x55);
	ODM_M2w(0x55);
	ODM_M3w(0x55);
	ODM_M4w(0x255);
	ODM_M5w(0x255);
	ODM_M6w(0xab );
	ODM_M7w(0xab );
	ODM_M8w(0x255);
	ODM_M9w(0x255);

	// Pre matrix => bypassed RGB output
	PRR_GAINw(0x100);
	PRG_GAINw(0x0)	;
	PRB_GAINw(0x0)	;
	PGR_GAINw(0x0)	;
	PGG_GAINw(0x100);
	PGB_GAINw(0x0)	;
	PBR_GAINw(0x0)	;
	PBG_GAINw(0x0)	;
	PBB_GAINw(0x100);

	OZONE_SELw(0x3)				;		// ODM OSD Selection Register

	AWB_WIN1_HWw (0x10 )		;
	AWB_WIN1_HSPw(0x80 )     	;
	AWB_WIN1_VWw (0x10 )     	;
	AWB_WIN1_VSPw(0x80 )     	;

	AWBL_CYSLICEw(0x0)			;		// Y slice
	AWBL_CYCLIPw (0x3ff)		;		// Y clip

//	AWBL_CLSL_ISELw(0)	;		// Clip/Slice apply position	(before/after matrix)

	// Color map setting (full scale)
	AWBL0_DBOFFSETw(0x0)		;
	AWBL0_DROFFSETw(0x0)		;
	AWBL_DBGAIN0w(0x8)			;
	AWBL_DRGAIN0w(0x8)			;

	AWBLCBCRO_SELw(0x0)	;		// 0: DbDr, 1: CbCr
	AWBL_HTAB_SELw(0x2)	;		// Size of detection block
	AWBLNOR_SELw(0x1)			;		// 1 : Always operate, 0 : Use color map

	AWBLYEDGE_THw(0x3ff)	;		// Y edge pseudo color remove
	AWBLOSD_ONw(0x1)       		;		// AWB OSD On/Off
	AWBL_OSD_SELw(0x73)      	;		// OSD Form
	AWB_LOCK_SELw(0x1)	;		// Awb data lock at VLOCK

	AWBL_CM_HSPw(0x15d)			;		// Color map OSD position
	AWBL_CM_VSPw(0x135)			;		// "

}

void AwbOdmCap(void)
{
static int	giOdmDbIIR,	giOdmDrIIR;
static UINT gnOdmRIIR, gnOdmGIIR, gnOdmBIIR;

	UINT	nTcnt;
	int		iDrSum,iDgSum,iDbSum;
	UINT	nRsum, nGsum, nBsum;

//--------------------------------------------
// ODM Data ready

	nTcnt	= AWBL_CCT_SUM_LOCKr	;														// Total block cnt
	iDrSum	= AWBL_CRDR_SUM_LOCKr	;     													// CR/DR(32b sign)
	iDgSum	= AWBL_CY_SUM_LOCKr		;														// CY	(31b)
	iDbSum	= AWBL_CBDB_SUM_LOCKr	;	     												// CB/DB(32b sign)
	nRsum 	= AWBL_CCR_SUM_LOCKr	;														// R from Pre ODM Mat
	nGsum 	= AWBL_CCG_SUM_LOCKr	;       												// G "
	nBsum 	= AWBL_CCB_SUM_LOCKr	;       												// B "

	if (nTcnt){
		iDrSum	= iDrSum / (int)nTcnt	;													// Pixel mean
		iDgSum	= iDgSum / (int)nTcnt	;													// "
		iDbSum	= iDbSum / (int)nTcnt	;													// "
		nRsum 	= nRsum  / (int)nTcnt	;													// "
		nGsum 	= nGsum  / (int)nTcnt	;													// "
		nBsum 	= nBsum  / (int)nTcnt	;													// "
	}
	else {
		iDbSum	= 0;
		iDrSum	= 0;
		iDgSum	= 0;
		nRsum	= 0;
		nGsum	= 0;
		nBsum	= 0;
	}

	gnOdmRIIR 	= ( (	  PAR00*gnOdmRIIR 	) + (     (0x100-PAR00)*(nRsum	<<4)) ) >> 8;	// speed
	gnOdmGIIR	= ( (	  PAR00*gnOdmGIIR	) + (     (0x100-PAR00)*(nGsum	<<4)) ) >> 8;	// "
	gnOdmBIIR	= ( (	  PAR00*gnOdmBIIR	) + (     (0x100-PAR00)*(nBsum	<<4)) ) >> 8;	// "
	giOdmDrIIR 	= ( ((int)PAR00*giOdmDrIIR	) + ((int)(0x100-PAR00)*(iDrSum	<<4)) ) >> 8;	// "
	giOdmDbIIR 	= ( ((int)PAR00*giOdmDbIIR	) + ((int)(0x100-PAR00)*(iDbSum	<<4)) ) >> 8;	// "


//--------------------------------------------
// Tx Graph

	GRP0		= gnOdmRIIR  >> 4;
	GRP1		= gnOdmGIIR	 >> 4;
	GRP2        = gnOdmBIIR	 >> 4;
	GRP3		= giOdmDrIIR >> 4;
	GRP4		= giOdmDbIIR >> 4;

	TxGrp();

//		DispDat("R_______"	,  8, 1, nRsum);
//		DispDat("G_______"	,  9, 1, nGsum);
//		DispDat("B_______"	, 10, 1, nBsum);
}


