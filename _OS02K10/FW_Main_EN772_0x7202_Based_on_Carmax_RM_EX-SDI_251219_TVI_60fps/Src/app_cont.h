/* **************************************************************************
 File Name		: 	app_cont.h
 Description	:	EN772 - Gamma Table
 Designer		:	Lee, Gyu Hong
 Date			:	20. 12. 30
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

//*******************************************************************************
// reserved define & tables
//*******************************************************************************
#define HISTO_MAX_BIT	7
#define HISTO_MAX_NUM	15
#define HISTO_VAL_NUM	(HISTO_MAX_NUM+1)

#define HISTO_OUT_BIT	/*3*/2						// Histogram Width

#define HistoX	1200/*1000*/
#define HistoY	460/*400*/
#define HistoW	(1<<(HISTO_MAX_BIT+HISTO_OUT_BIT))
#define HistoH	400/*200*/							// Histogram Height

#define HistoFill	1
#define HistoTone	BOX_TONE_100

BYTE gbHistoM[HISTO_VAL_NUM];


#define ACEBLOCK_ON		ACE_BPw(0);						// Block bypass OFF(use)/ON
#define ACEBLOCK_OFF	ACE_BPw(1);

#define ACE_ON			ACE_ONw(1);						// ACE ON/OFF
#define ACE_OFF			ACE_ONw(0);

#define DEFOG_ON		HEQ_ONw(1);						// DEFOG ON/OFF
#define DEFOG_OFF		HEQ_ONw(0);

//*************************************************************************************************
// Gamma Table
//-------------------------------------------------------------------------------------------------
// Starvis Status
BYTE gbNV;

// -------------------------------------------------------------------------
// Gamma table New
BYTE gbGammParInit = 0;
BYTE gbDfltGammaChk = 0;

UINT gnTblY1GmaCstm[9];
UINT gnTblY2GmaCstm[9];
UINT gnTblC1GmaCstm[9];
UINT gnTblC2GmaCstm[9];

UINT gnTblWdrY1GmaCstm[9];
UINT gnTblWdrY2GmaCstm[9];
UINT gnTblWdrC1GmaCstm[9];
UINT gnTblWdrC2GmaCstm[9];

	//Reference Gamma
	// 0.45 ~ 0.75
	const UINT	gnTblY1GmaBasic[9] = 	{0x0000000f, 0x00350069, 0x00b100fc, 0x015201cd, 0x022d028c, 0x02d6031a, 0x038403d3, 0x03f403ff, 0x03ff0000};	// 0.45
	const UINT	gnTblY2GmaBasic[9] = 	{0x0000000a, 0x00130021, 0x00390062, 0x00a90126, 0x019a0208, 0x027102cb, 0x037703cc, 0x03e703f8, 0x03ff0000};	// 0.75
	
	const UINT	gnTblC1GmaBasic[9] = 	{0x00000011, 0x002d0060, 0x00bb0137, 0x01c8025e, 0x02c30312, 0x03560384, 0x03bb03d3, 0x03e703f2, 0x03ff0000};	// 0.45
	const UINT	gnTblC2GmaBasic[9] = 	{0x0000000d, 0x00190030, 0x00560096, 0x00f80192, 0x02120282, 0x02ea0330, 0x038f03c1, 0x03de03f2, 0x03ff0000};	// 0.75

	// Auto Gamma
//	const UINT	gnTblY1Gma[9] = 	{0x00000007, 0x00130025, 0x004a0083, 0x00d40173, 0x01f00262, 0x02c3030f, 0x037b03bf, 0x03e703fa, 0x03ff0000};	//Y Day
//	const UINT	gnTblY2Gma[9] = 	{0x00000008, 0x0011001d, 0x00350057, 0x00a10124, 0x019201fb, 0x025002aa, 0x03330391, 0x03cd03ec, 0x03ff0000};	//Y Night
	
	// Normal - for Focus
#if(model_ImgTune_Option==0)
	const UINT	gnTblY1Gma[9] = 	{0x00000006, 0x0012002b, 0x005c00b0, 0x012c01e9, 0x026902be, 0x02f50321, 0x037003a9, 0x03d303eb, 0x03ff0000};	//Y Day
	const UINT	gnTblY2Gma[9] = 	{0x00000006, 0x0012002b, 0x005c00b0, 0x012c01e9, 0x026902be, 0x02f50321, 0x037003a9, 0x03d303eb, 0x03ff0000};	//Y Night
	
	const UINT	gnTblC1Gma[9] = 	{0x00000019, 0x00380061, 0x009d00ec, 0x015401e7, 0x025502a6, 0x02f10323, 0x037b03b6, 0x03d703ef, 0x03ff0000};	//C Day
	const UINT	gnTblC2Gma[9] = 	{0x0000000b, 0x001b0031, 0x0055009c, 0x011601b4, 0x0227027e, 0x02c7030b, 0x037b03b6, 0x03d703ef, 0x03ff0000};	//C Night

	const UINT	gnTblWdrY1Gma[9] =	{0x00000008, 0x00100021, 0x003c006c, 0x00bf0147, 0x01b7020a, 0x0245026f, 0x02b302f5, 0x034003a0, 0x03ff0000}; 	//Y Day   (Ref)
	const UINT	gnTblWdrY2Gma[9] = 	{0x0000000b, 0x0016002b, 0x004c0082, 0x00d20144, 0x019801d8, 0x020e023f, 0x028e02d9, 0x0335039e, 0x03ff0000};  	//Y Night (Ref)

	const UINT	gnTblWdrC1Gma[9] =	{0x00000006, 0x000d001b, 0x004100b6, 0x015f01ff, 0x02590290, 0x02a802b8, 0x02e3030f, 0x0348038a, 0x03ff0000};  	//C Day
	const UINT	gnTblWdrC2Gma[9] =	{0x00000008, 0x0015002d, 0x0058009c, 0x011201c2, 0x022f0264, 0x028e02af, 0x02e8030f, 0x0348038d, 0x03ff0000};   //C Night
#else
	#include "FineTune/Sensor_FineTune_UD.h"
#endif		
//====================================================================================================================================
//====================================================================================================================================


