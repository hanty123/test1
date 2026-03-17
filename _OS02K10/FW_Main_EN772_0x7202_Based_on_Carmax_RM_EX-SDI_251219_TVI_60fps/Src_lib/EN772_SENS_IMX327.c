/* **************************************************************************
 File Name	:	EN870_SENS_IMX327.c
 Description	:	EN870 - IMX327 device driver
 Designer		:	Lee, Hoon
 Modifier		:	Lee, Gyu Hong
 Date		:	19. 12. 18
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#undef model_Sens
#include "../Src/dev.h"
#define model_Sens	SENS_IMX327
#include "../Src/dev.h"
#include "SENS_Common.h"

// -----------------------------------------------------------------------------------------
// pre define & table
// -----------------------------------------------------------------------------------------
#define gwTblSens0			Sens(gwTblSens0)
#define gTblSensEa			Sens(gTblSensEa)


#define gbAeHssFltTbl		Sens(gbAeHssFltTbl)
#define gnAeShtTbl			Sens(gnAeShtTbl)

#define LibAeShtIntp		Sens(LibAeShtIntp)

#define AE_SHTMAX_OFST			(2)
#define AE_SHTMIN_OFST			(1)
#define AE_SHTMAX		(nMok-AE_SHTMAX_OFST)

#define AE_GAIN_UNIT_MAX		(238)	    																	// Sensor gain step by Unit  (IMX327:71.4dB)
#define AE_GAIN_UNIT_EA			(1)																				// Sensor gain Unit EA
#define AE_GAIN_UNIT_OVR		(27)//(81)																		// Sensor gain extended step (HCG)
#define AE_GAIN_UNIT_OVR2		(0)	    																		// ISP gain extended step
const int Sens(AE_GAIN_TOTAL) = (((AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR)*(0.3/0.1));
const int Sens(AE_GAIN_TOTAL2) = 0;

#define AE_GAIN_DENORMAL(val)	(ifdiv8(val*(int)(0.34f*256.f)))		// 171211 LH : int floating

#define AE_HSS_FLT_EA		(sizeof(gbAeHssFltTbl))
#define AE_SHT_TBL_EA		(sizeof(gnAeShtTbl)/8)

// -----------------------------------------------------------------------------------------
// LINE-WDR Configuration
// -----------------------------------------------------------------------------------------

#define AE_LWDR_2P_RHS1			((gbInModeRes==MD_2M_FPS_125_20)?(19):(31))
//#define AE_LWDR_2P_RHS1			(  19)

#define AE_LWDR_FSC				(gnInModeVtw*2)
#define AE_LWDR_Y_OUT_SIZE		((1109 + (AE_LWDR_2P_RHS1-1)/2)*2)				// IMX290_AppNote_DOL_E_Rev9.0.


#define AE_LWDR_2P_L0MIN_OFST	(	2)
#define AE_LWDR_2P_L0MAX_OFST	(	2)

#define AE_LWDR_2P_S1MIN_OFST	(	2)
#define AE_LWDR_2P_S1MAX_OFST	(	2)

#define AE_LWDR_2P_L0_MAX		(AE_LWDR_FSC - AE_LWDR_2P_L0MAX_OFST)			// L0 Max shutter line at DOL 2P
#define AE_LWDR_2P_L0_MIN		(AE_LWDR_2P_RHS1 + AE_LWDR_2P_L0MIN_OFST)		// L0 Max shutter line at DOL 2P

#define AE_LWDR_2P_S1_MAX		(AE_LWDR_2P_RHS1 - AE_LWDR_2P_S1MAX_OFST)		// S1 Max shutter line at DOL 2P
#define AE_LWDR_2P_S1_MIN		(AE_LWDR_2P_S1MIN_OFST)							// S1 Max shutter line at DOL 2P

// -----------------------------------------------------------------------------------------
// initial
	//IMX327 MIPI
	// MIPI : Normal 2 -lane / DOL 2 -lane
	// INCK : 37.125MHz
	
	// Chip ID 0x2
	const WORD gwTblSens0[][4] = {
								//ADDR	 Nor 2M30P	DOL 2P	Nor 2M60P
								/*ID2*/
								{0x3005, 	0x01, 	0x00,	0x01}, 	// ADBIT
								{0x3007, 	0x00, 	0x00,	0x00}, 	// WINMODE (1080p)
								{0x3009, 	0x02, 	0x01,	0x01}, 	// FRSEL *
								{0x300a, 	0x00, 	0x00,	0x00}, 	// BLKLEVEL (recommend : 0xf0 at 12b mode)
								{0x300b, 	0x00, 	0x00,	0x00}, 	// "
								{0x300c, 	0x00, 	0x11,	0x00},	// WDSEL/WDMODE (normal : 0x0, DOL2p : 0x11, DOL3p : 0x21)
								{0x3010, 	0x21, 	0x61,	0x21}, 	// FPGC : each frame gain of DOL 0x61, common gain of DOL 0x21 (normal, datasheet default is wrong)
								{0x3011, 	0x02, 	0x02,	0x02}, 	// (IMX327) fixed at DATASHEET 0.3
								
//								{0x3018, 	0x65, 	0x65,	0x65}, 	// VMAX
//								{0x3019, 	0x04, 	0x04,	0x04}, 	// "
//								{0x301a, 	0x00, 	0x00,	0x00}, 	// "
//
//								{0x301c, 	0x30, 	0x98,	0x98}, 	// HMAX *
//								{0x301d, 	0x11, 	0x08,	0x08}, 	// "

								{0x3020, 	0x02,	0x02,	0x02}, 	// SHS1
								{0x3021, 	0x00,	0x00,	0x00}, 	// "
								{0x3022, 	0x00,	0x00,	0x00},	// "

								{0x3024, 	0x00,	0x87,	0x00}, 	// SHS2
								{0x3025, 	0x00,	0x08,	0x00}, 	// "
								{0x3026, 	0x00,	0x00,	0x00},	// "

								{0x3030, 	0x00,	0x07,	0x00}, 	// RHS1
								{0x3031, 	0x00,	0x00,	0x00}, 	// "
								{0x3032, 	0x00,	0x00,	0x00},	// "
								
								{0x3045, 	0x01, 	0x05,	0x01},	// DOLSCDEN, DOLSYDINFOEN, HINFOEN
								{0x3046, 	0x01,	0x00,	0x01}, 	// OPORTSEL, ODBIT (normal, DOL)						//MIPI
//								{0x3048, 	0x10, 	0x10,	0x10}, 	// XVSLNG				(VSYNC Low pulse width)
//								{0x3049, 	0x0a, 	0x1a,	0x0a}, 	// XHSLNG				(HSYNC Low pulse width)
								{0x304b, 	0x0a, 	0x0a,	0x0a}, 	// XVSOUTSEL, XHSOUTSEL (V,H SYNC ON)
								{0x305c, 	0x18, 	0x18,	0x18}, 	// INCKSEL1
								{0x305d, 	0x03, 	0x03,	0x03}, 	// INCKSEL2
								{0x305e, 	0x20, 	0x20,	0x20}, 	// INCKSEL3
								{0x305f, 	0x01, 	0x01,	0x01}, 	// INCKSEL4
								{0x309e, 	0x4a, 	0x4a,	0x4a}, 	// (IMX327) fixed
								{0x309f, 	0x4a, 	0x4a,	0x4a}, 	// (IMX327) fixed
								{0x30d2, 	0x19, 	0x19,	0x19}, 	// (IMX327) fixed at DATASHEET 0.3
								{0x30d7, 	0x03, 	0x03,	0x03}, 	// (IMX327) fixed at DATASHEET 0.3
								{0x30f0, 	0xf0, 	0x64,	0xf0}, 	// (IMX327) FPGC_1 : each frame gain of DOL, 0x64 for S1
								{0x30f4, 	0xf0, 	0x64,	0xf0}, 	// (IMX327) FPGC_2 : each frame gain of DOL, 0x64 for S2

								/*ID3*/
								{0x3106, 	0x00, 	0x15,	0x00}, 	// XVS,HVS subsampling when DOL 2p master : 0x15 , 3p master : 0x3b)
								{0x3129, 	0x00, 	0x1D,	0x00}, 	// (IMX327) ADBIT1
								{0x313b, 	0x61, 	0x61,	0x61}, 	// (IMX327) fixed at DATASHEET 0.3
								{0x315e, 	0x1a, 	0x1a,	0x1a}, 	// INCKSEL5
								{0x3164, 	0x1a, 	0x1a,	0x1a}, 	// INCKSEL6
								{0x317c, 	0x00, 	0x12,	0x00}, 	// ADBIT2
								{0x31ec, 	0x0e, 	0x37,	0x0e},	// (IMX327) ADBIT3

								/*ID6 */
								{0x3405,	0x10,	0x00,	0x00},	// REPETITION			(0x20 : 222.75 /0x10 : 445.5 / 0x00 : 891Mbps/Lane)
								{0x3407,	0x01,	0x01,	0x01},	// PHYSICAL_LANE_NUM	(0x1 : 2 lane / 0x3 : 4 lane)
								{0x3414,	0x0A,	0x0A,	0x0A},	// OPB_SIZE_V
								{0x3415,	0x01,	0x00,	0x01},	// DOL : 0x00				
								{0x3418,	0x49,	0x9c,	0x49},	// Y_OUT_SIZ				(Full HD 1080p Normal : 0x449 / DOL2P : (1109 + (RHS1-1)/2) * 2))
								{0x3419,	0x04,	0x08,	0x04},	// "
								{0x3441,	0x0C,	0x0A,	0x0C},	// CSI_DT_FMT			(0x0C : 12bit, 0x0A : 10bit)
								{0x3442,	0x0C,	0x0A,	0x0C},	// CSI_DT_FMT			(0x0C : 12bit, 0x0A : 10bit)
								{0x3443,	0x01,	0x01,	0x01},	// CSI_LANE_MODE		(0x1 : 2 lane / 0x3 : 4 lane)
								{0x3444,	0x20,	0x20,	0x20},	// EXTCK_FREQ			(only MIPI)
								{0x3445,	0x25,	0x25,	0x25},	// EXTCK_FREQ			(only MIPI)
								
								// Global timing
								{0x3446, 	0x57,	0x77,	0x77},  // TCLKPOST				(only MIPI)
								{0x3447, 	0x00,	0x00,	0x00},  // TCLKPOST				(only MIPI)
								{0x3448, 	0x37,	0x67,	0x67},  // THSZERO				(only MIPI)
								{0x3449, 	0x00,	0x00,	0x00},  // THSZERO				(only MIPI)
								{0x344A, 	0x1F,	0x47,	0x47},  // THSPREPARE			(only MIPI)
								{0x344B, 	0x00,	0x00,	0x00},  // THSPREPARE			(only MIPI)
								{0x344C, 	0x1F,	0x37,	0x37},  // TCLKTRAIL				(only MIPI)
								{0x344D, 	0x00,	0x00,	0x00},  // TCLKTRAIL				(only MIPI)
								{0x344E, 	0x1F,	0x3F,	0x3F},  // THSTRAIL				(only MIPI)
								{0x344F, 	0x00,	0x00,	0x00},  // THSTRAIL				(only MIPI)
								{0x3450, 	0x77,	0xFF,	0xFF},  // TCLKZERO				(only MIPI)
								{0x3451, 	0x00,	0x00,	0x00},  // TCLKZERO				(only MIPI)
								{0x3452, 	0x1F,	0x3F,	0x3F},  // TCLKPREPARE			(only MIPI)
								{0x3453, 	0x00,	0x00,	0x00},  // TCLKPREPARE			(only MIPI)
								{0x3454, 	0x17,	0x37,	0x37},  // TLPX					(only MIPI)
								{0x3455, 	0x00,	0x00,	0x00},  // TLPX					(only MIPI)
                                         	
								{0x3472, 	0x9C,	0xA0,	0x9C},  // X_OUT_SIZE			(Full HD 1080p Normal : 0x79C / DOL : 0x7A0)
								{0x3473, 	0x07,	0x07,	0x07},  // X_OUT_SIZE			(Full HD 1080p Normal : 0x79C / DOL : 0x7A0)
								{0x347b, 	0x24,	0x23,	0x24},  // MIF_SYNC_TIM0			(only MIPI)
								{0x3480, 	0x49,	0x49,	0x49}   // INCKSEL7
								};

const UINT gTblSensEa		= numberof(gwTblSens0);

// -----------------------------------------------------------------------------------------
// AE
// -----------------------------------------------------------------------------------------
// shutter table value is same with IMX327

	const BYTE 	gbAeHssFltTbl[]   = {
									0 ,		// Dummy
									59,		// 0
									34,		// 1
									24,		// 2
									19,		// 3
									15,		// 4
									13,		// 5
									11,		// 6
									10,		// 7
									9 ,		// 8
									8 ,		// 9
									7 ,		// 10
									6 ,
									6 ,
									5 ,
									5 ,
									5 ,
									4 ,
									4 ,
									4 ,
									4 ,
									4 ,
									3 ,
									3 ,
									3 ,
									3 ,
									3 ,
									3 ,
									3 ,
									2 ,
									2 ,
									2 ,
									2 ,
									2 ,
									2 ,
									2 ,
									2 ,
									2 ,
									2 ,
									2 ,
									2 ,
									2 ,
									2 ,
									1 ,
									1 ,
									1
									};

	const UINT	gnAeShtTbl[][2]   = {
									{0	 , 128     },
									{14  , 144     },
									{28  , 164     },
									{42  , 187     },
									{56  , 214     },
									{70  , 246     },
									{84  , 284     },
									{98  , 328     },
									{112 , 380     },
									{126 , 441     },
									{140 , 513     },
									{154 , 597     },
									{168 , 696     },
									{182 , 812     },
									{196 , 948     },
									{210 , 1109    },
									{224 , 1297    },
									{238 , 1518    },
									{252 , 1778    },
									{266 , 2084    },
									{280 , 2443    },
									{294 , 2865    },
									{308 , 3360    },
									{322 , 3942    },
									{336 , 4626    },
									{350 , 5430    },
									{364 , 6374    },
									{378 , 7483    },
									{392 , 8787    },
									{406 , 10318   },
									{420 , 12117   },
									{434 , 14231   },
									{448 , 16714   },
									{462 , 19632   },
									{476 , 23060   },
									{490 , 27088   },
									{504 , 31820   },
									{518 , 37380   },
									{532 , 43912   },
									{546 , 51587   },
									{560 , 60603   },
									{574 , 71197   },
									{588 , 83644   },
									{602 , 98268   },
									{616 , 115449  },
									{630 , 135635  },
									{644 , 159352  },
									{658 , 187217  },
									{672 , 219955  },
									{686 , 258419  },
									{700 , 303610  },
									{714 , 356705  },
									{728 , 419087  },
									{742 , 492378  },
									{756 , 578489  },
									{770 , 679659  },
									{784 , 798525  },
									{798 , 938179  },
									{812 , 1102259 },
									{826 , 1295036 },
									{840 , 1521529 },
									{854 , 1787635 },
									{868 , 2100283 },
									{882 , 2467611 },
									{896 , 2899185 },
									{910 , 3406240 },
									{924 , 4001978 },
									{938 , 4701908 },
									{952 , 5524255 },
									{966 , 6490428 },
									{980 , 7625583 },
									{994 , 8959273 },
									{1008, 10526222}
									};

// -----------------------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------------------
void LibRdesIsp(int aiResMode, int aiWdrMode)
{	// MIPI RX Configuration
	UNUSED_ARG(aiResMode);
	LibISPtoSENS_Intf(\
					/* MIPI or LVDS */\
					(MIPI),\
					/* 1, 2, 4 LANE */\
					(_2LANE),\
					/* 12BIT or 10BIT */\
					((aiWdrMode==MN_OFF)?(_12BIT):(_10BIT)),\
					/* 3210, 10, 0 */\
					(_10),\
					/* Word Count */\
					((aiWdrMode==MN_OFF)?(0xB6A):(0x988)),\
					/* MIPI Line information or Virtual channel mode */\
					(_MIPI_LI),\
					(aiWdrMode));
}

void LibInitSens(int aiMode, int aiOption)
{	// IMX327
	// aiMode   - 	0 : Normal 30p (Based on data rate 445.5Mbps)
	//			1 : normal 60p (Based on data rate 891Mbps)
	//			0xff : CVBS Only (59.94fps)
	// aiOption - 0 : OFF, 1 : DOL 2P

	UINT i;
	static BYTE bInitSet = 0x1;
	static BYTE bModeIndx = 0x0;
	
	if(bInitSet){

		// Sensor H/W Reset
		GpioSetLo(GPIO_SRSTN);	WaitUs(10000);		GpioSetHi(GPIO_SRSTN);	WaitUs(10000);

		// I2C Check
		for(i=0; i<10; i++) {
		if(i2c_write(SENS_SONY_DEV,1,0) == 0) {
			gbSensorOff = 0;
			TxStrNoIRQ("SI2C connected.", 0, 0);
			break;
		}
		WaitUs(1000);
		}
		if(gbSensorOff) TxStrNoIRQ("SI2C not connected.", 0, 0);

		//Chip ID Check (IMX290 : 0x0 /IMX462 : 0x2 /IMX307 : 0x4 /IMX327 :  0x6)
		const BYTE bChipID = (GetSens(0x31DC)&0x06);
		if(bChipID==0x6)	{TxStrNoIRQ("Sensor correct matching. ", bChipID, 1);}
		else				{TxStrNoIRQ("Sensor incorrect matching. ", bChipID, 1); NEGA_ONw(0x1);}
		
		bInitSet = 0x0;
	}
	
	bModeIndx = ((aiMode==MD_CVBS)||(aiMode==MD_2M_FPS_50_60))?(1):(0);
	LibRdesIsp(bModeIndx, aiOption);
	
	SetSens(0x3000, 0x1);	WaitUs(1000);		// standby
	SetSens(0x3002, 0x1);	WaitUs(1000);		// xmaster stop
	SetSens(0x3001, 0x1);						// REG Hold
	SetSens(0x3003, 0x1);						// SW reset

	for (i=0; i<gTblSensEa; i++)	{	SetSens(gwTblSens0[i][0], (BYTE)gwTblSens0[i][1+(bModeIndx*2)+((aiOption)?(1):(0))]);}
//	for (i=0; i<gTblSensEa; i++)	{	SetSens(gwTblSens0[i][0], (BYTE)gwTblSens0[i][1+bModeIndx]);}

	SetSens(0x3003, 0x0);					// SW reset OFF
	SetSens(0x3001, 0x0);					// REG Hold OFF
	SetSens(0x3000, 0x0);	WaitUs(30000);		// standby cancel
	SetSens(0x3002, 0x0);	WaitUs(20000);		// xmaster

	//Shutter Speed Max
	gnAeNorMax = gnInModeVtw-AE_SHTMAX_OFST;

	if (aiOption==1) {			// DOL 2P

		gnAeLWdrMaxL0	= (AE_LWDR_2P_L0_MAX - AE_LWDR_2P_RHS1)-AE_LWDR_2P_L0MIN_OFST;		
		gnAeLWdrMaxS1	= (AE_LWDR_2P_S1_MAX)-AE_LWDR_2P_S1MIN_OFST;		

		gnAeLWdrMinL0	= (AE_LWDR_2P_L0_MIN - AE_LWDR_2P_RHS1)-AE_LWDR_2P_L0MIN_OFST;		
		gnAeLWdrMinS1	= (AE_LWDR_2P_S1_MIN)-AE_LWDR_2P_S1MIN_OFST;		

		gbAeWdrComp		= 0x0;
		// RHS1
		SetSensBst(0x3030, (AE_LWDR_2P_RHS1&0xFFFFF), 3);

		//Y_OUT_SIZE
		SetSensBst(0x3418, (AE_LWDR_Y_OUT_SIZE&0x1FFF),2);
	}
}


void ISPM Sens(AE_SHTLw)(UINT val)
{
	SetSensBst(((!gbModeWdrOn_L)?(0x3020):(0x3024)), (val&0x3FFFF), 3);
}

void ISPM Sens(AE_SHTSw)(UINT val)
{
	SetSensBst(0x3020, (val&0x3FFFF), 3);
}

void ISPM Sens(AE_AGCw)(UINT val)
{
	SetSens(0x3014, (val>>0)&0xff);
}

void ISPM Sens(AE_DGCw)(UINT val)
{
	UNUSED_ARG(val);
}

void ISPM Sens(AE_FREQw)(UINT val, UINT val1)
{
//	UNUSED_ARG(val);
	SetSensBst(0x3018, (val&0x3FFFF), 3);
	SetSensBst(0x301c, (val1&0xFFFF), 2);
}


//----------------------------------------------------------------------------------------

UINT ISPM LibAeShtLine(UINT anLine)	// Fixed
{	// convert line to db
	UINT i;
	UINT nShtDb = 0;
	const UINT nShtLine = anLine * 0x80;

	for(i=1; i<AE_SHT_TBL_EA; i++) {
		if (nShtLine<gnAeShtTbl[i][1]) {
			nShtDb = LibUtlInterp1D (nShtLine, gnAeShtTbl[i-1][1], gnAeShtTbl[i][1], gnAeShtTbl[i-1][0], gnAeShtTbl[i][0]);
			break;
		}
	}
	return nShtDb;
}

void ISPM LibAeShtIntp(int aiVal, const UINT anTblEa, const UINT anFltEa, UINT* apnShtFlt, UINT* apnShtInt)	// Fixed
{
 	UINT	nShtFlt=0;
	UINT	nShtInt=0;
	UINT 	i;
	const BYTE bLwdrOfst = (gbModeWdrOn_L)?(1):(0);
	
	for(i=1; i<anTblEa; i++) {
		if (aiVal<(int)gnAeShtTbl[i][0]) {
			nShtFlt = LibUtlInterp1D (aiVal, gnAeShtTbl[i-1][0], gnAeShtTbl[i][0], gnAeShtTbl[i-1][1], gnAeShtTbl[i][1]);
			nShtInt = nShtFlt>>7;

			if (nShtInt<anFltEa)		nShtFlt = LibUtlInterp1D (nShtFlt, (nShtInt<<7), (nShtInt<<7)+0x80, 0, gbAeHssFltTbl[nShtInt+bLwdrOfst]);
			else 						nShtFlt = 0;
//			nShtFlt = MIN(nShtFlt, 0x80);
			break;
		}
	}
	*apnShtFlt = nShtFlt;
	*apnShtInt = nShtInt;
}

// -----------------------------------------------------------
// AE Shutter Driver

WORD ISPM AeSHT(int aiVal, UINT anManual, UINT anManualVal)
{	// Shutter driver
//** Sensor Spec : Shutter 1 to 1123(VMAX-2)

	UINT	nMok = gnInModeVtw;
	UINT	nRem = 0;
	UINT	nShtMax = 0;
	static 	UINT	gnShtFlt = 0;
	UINT	nShtInt = 0;

	if (gnAeState==0){
		LibAePrgain_L(LibAePrgainIntp(gnShtFlt));
	}
	
	LibAeShtIntp (aiVal, AE_SHT_TBL_EA, AE_HSS_FLT_EA, &gnShtFlt, &nShtInt);

#if(0)
	if (gnAeState==0){
	  gnShtFlt = AE_GAIN_DENORMAL(gnShtFlt);		// 171211 LH
	  gnShtFlt = MINMAX(gnShtFlt, 0, (UINT)(AE_GAIN_UNIT_EA*AE_GAIN_UNIT_MAX));
	  AE_AGCw(gnShtFlt);
	}
#endif

	if(anManual){
	  nMok 	= (UINT)(MAX(((int)anManualVal - AE_SHTMAX_OFST), (int)0))/gnInModeVtw;
	  nMok 	= ((nMok*gnInModeVtw)+gnInModeVtw);

	  nShtMax = AE_SHTMAX;
	  nRem = MINMAX(anManualVal, AE_SHTMIN_OFST, nShtMax);
	}
	else {
	  nMok 	= gnInModeVtw ;
	  nShtMax = AE_SHTMAX;
	  nRem 	= MIN(nShtInt, nShtMax);
	}

	AE_SHTLw(nShtMax-nRem+AE_SHTMIN_OFST);

	DebugDisp(gbAeDebugOn, Dec, "SHT_int__d", 1, 24, nRem		)
	DebugDisp(gbAeDebugOn, Dec, "SHT_flt__d", 2, 24, gnShtFlt	)

	return ((WORD)nRem);

}

// -----------------------------------------------------------
// AE AGC Driver
void ISPM AeAGC(int aiVal)
{	// AGC driver

	static int	giAgc;
	static int  iChk;
	const UINT nAGC_LMT = AE_GAIN_DENORMAL(AE_SENS_AGC_LMT_NOR);
	static UINT nLWdrGain;
	
	SetSens(0x3009, ((0x3&GetSens(0x3009))|(iChk<<4)) );

	giAgc = AE_GAIN_DENORMAL(aiVal);
	giAgc = MINMAX(giAgc, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR);

	if(giAgc <= (int)nAGC_LMT){											//AGC+HCG
		if ((giAgc-AE_GAIN_UNIT_OVR) >= 0) {
			giAgc = giAgc - AE_GAIN_UNIT_OVR;
			iChk = 1;
		}
		else 	iChk = 0;

		giAeLWdrGain = 0x0;
	}

	else{
		if ((giAgc-AE_GAIN_UNIT_OVR) >= 0) 		iChk = 1;
		
		LibAeGainIntp((aiVal-AE_SENS_AGC_LMT_NOR), &nLWdrGain);				//Calculation 0.1dB
		giAeLWdrGain = (int)nLWdrGain;									
		giAgc = (nAGC_LMT - AE_GAIN_UNIT_OVR);							//AGC MAX
	}

//	if ((giAgc-AE_GAIN_UNIT_OVR) >= 0) {
//		giAgc = giAgc - AE_GAIN_UNIT_OVR;
//		iChk = 1;
//	}
//	else 	iChk = 0;

	giAgc = MINMAX(giAgc, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA));

	if (gnAeState!=0)	AE_AGCw((BYTE)giAgc);

	DebugDisp(gbAeDebugOn, Hex, "AGC_____", 5, 24, (iChk<<16)|giAgc )
	DebugDisp(gbAeDebugOn, Hex, "WDR_GAIN", 6, 24, (giAeLWdrGain))
}


// -------------------------------------------------------------------------------------
// LINE WDR

WORD ISPM AeSHT_LWDR(int aiMode, int aiVal, int aiVal1)
{	// Shutter driver for Line WDR
	// aiMode : 0 : off, 1: 2 page, 2: 3 page
	// aiVal  : Long
	// aiVal1 : short1
	// aiVal2 : short2
	UNUSED_ARG(aiMode);

	static	UINT	gnShtFlt_L, gnShtFlt_S = 0;
	UINT	nShtInt;
	int tgt_L ;
	int tgt_S1;

	if (gnAeState==0){
		LibAePrgain_L(MAX(gnAgc_L, 0x100));
		LibAePrgain_S(MAX(gnAgc_S1, 0x100));
	}
	
	//Long
	LibAeShtIntp (aiVal, AE_SHT_TBL_EA, AE_HSS_FLT_EA, &gnShtFlt_L, &nShtInt);
	tgt_L = (int)nShtInt;
	gnSht_L		= tgt_L;	// Long   Exposure Shutter line
	gnAgc_L = LibAePrgainIntp(gnShtFlt_L);

	
	//Short
	LibAeShtIntp (aiVal1, AE_SHT_TBL_EA, AE_HSS_FLT_EA, &gnShtFlt_S, &nShtInt);
	tgt_S1 = (int)nShtInt;
	gnSht_S1	= tgt_S1;   // Short1 Exposure Shutter line
	gnAgc_S1 = LibAePrgainIntp(gnShtFlt_S);


//		tgt_L  = (AE_LWDR_FSC - AE_LWDR_2P_L0MAX_OFST) - tgt_L + AE_LWDR_2P_L0MIN_OFST;
	tgt_L  = (AE_LWDR_FSC - AE_LWDR_2P_L0MAX_OFST) - tgt_L;

//		tgt_S1 = (AE_LWDR_2P_RHS1 - AE_LWDR_2P_S1MAX_OFST)- tgt_S1 + AE_LWDR_2P_S1MIN_OFST;
	tgt_S1 = (AE_LWDR_2P_RHS1 - AE_LWDR_2P_S1MAX_OFST)- tgt_S1;	

	AE_SHTLw(tgt_L );
	AE_SHTSw(tgt_S1);

	if (PAR0F==0x3530) {
		DebugDisp(gbAeDebugOn, Dec, "SHT0___d", 0, 24, tgt_L  	)
		DebugDisp(gbAeDebugOn, Dec, "SHT1___d", 1, 24, tgt_S1 	)
	} else {
		DebugDisp(gbAeDebugOn, Dec, "SHT0___d", 0, 24, gnSht_L 	)
		DebugDisp(gbAeDebugOn, Dec, "SHT1___d", 1, 24, gnSht_S1	)
	}

	DebugDisp(gbAeDebugOn, Dec, "SHT_fltL_d", 2, 24, gnShtFlt_L	)
	
	return (0);		// LH TMP

}

void ISPM AeAGC_LWDR(int aiMode, int aiVal, int aiVal1)
{	// AGC driver for Line WDR
	// aiMode : 0: off, 1: 2 page
	// aiVal : Long
	// aiVal1 : short1

	UNUSED_ARG(aiMode);
	UNUSED_ARG(aiVal1);

	static int	giAgcL, giAgcS1;
	static int  iChk;
	static UINT nLWdrGain;

	const UINT nLWDR_AGC_LMT = AE_GAIN_DENORMAL(AE_SENS_AGC_LMT_WDR);
	
	SetSens(0x3009, ((0x3&GetSens(0x3009))|(iChk<<4)) );	//  FRSEL(fixed) + HCG	// 171215 LH : HCG need to control continuously in also WDR Short

	giAgcL = AE_GAIN_DENORMAL(aiVal);
	giAgcL = MINMAX(giAgcL, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR);

	if(giAgcL <= (int)nLWDR_AGC_LMT){												//AGC+HCG
		if ((giAgcL-AE_GAIN_UNIT_OVR) >= 0) {
			giAgcL = giAgcL - AE_GAIN_UNIT_OVR;
			iChk = 1;
		}
		else 	iChk = 0;

		giAeLWdrGain = 0x0;
	}

	else{
		if ((giAgcL-AE_GAIN_UNIT_OVR) >= 0)		iChk = 1;
		
		LibAeGainIntp((aiVal-AE_SENS_AGC_LMT_WDR), &nLWdrGain);						//Calculation 0.1dB
		giAeLWdrGain = (int)nLWdrGain;									
		giAgcL = (nLWDR_AGC_LMT - AE_GAIN_UNIT_OVR);							//AGC MAX
	}
	
	giAgcL = MINMAX(giAgcL, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA));
	giAgcS1 = giAgcL;
	
	if (gnAeState!=0)	{
		LibAePrgain_L(0x100);
		LibAePrgain_S(0x100);
		
		SetSens(0x3014, (giAgcL >>0)&0xff);		// L gain
		SetSens(0x30f2, (giAgcS1>>0)&0xff);		// S1 gain
	}

	DebugDisp(gbAeDebugOn, Hex, "AGC0____", 5, 24, (iChk<<16)|giAgcL)
	DebugDisp(gbAeDebugOn, Hex, "WDR_GAIN", 6, 24, (giAeLWdrGain))
}



// -----------------------------------------------------------------------------------------
// AWB
// -----------------------------------------------------------------------------------------
//170913 PCB
const s64 glMtxCf[9][6] =		{	// RT, Y 350
									{	      97300108780293LL,	       -382335469335LL,	       -657327197288LL,	          -970854446LL,	          -417289512LL,	          -302948852LL},
									{	     -25610461631809LL,	        -83844350482LL,	          3074412947LL,	           -84467872LL,	          -172643182LL,	           -59928510LL},
									{	     100455795694691LL,	        596415001416LL,	        638846840119LL,	          1645069605LL,	           988588094LL,	          1263660471LL},
									{	     -84927297422427LL,	       -203233399711LL,	       -251468660294LL,	          -457136760LL,	          -186746040LL,	          -230653616LL},
									{	     239923228585736LL,	        199784174570LL,	        189022051213LL,	           238970871LL,	            51198144LL,	           108646683LL},
									{	      91378693540417LL,	        807722653076LL,	       1007610679352LL,	          2115959748LL,	          1039907685LL,	          1723648300LL},
									{	      28975171383173LL,	         15766565224LL,	        -89552909827LL,	            84743330LL,	           133061486LL,	            23940837LL},
									{	     -85036748617762LL,	       -562335545541LL,	       -488477555790LL,	         -1501553100LL,	         -1068165807LL,	          -900718286LL},
									{	     777088822166039LL,	       3924945873024LL,	       3894196879600LL,	         10135739041LL,	          6479661282LL,	          6882679484LL}
								};


// -----------------------------------------------------------------------------------------
// MIRROR & FLIP
// -----------------------------------------------------------------------------------------

void Sens(SENS_MIRw)(BYTE abOn){
	SetSens(0x3007, ((GetSens(0x3007)&(~ValSft_L01(BitMask_01)))|ValSft_L01((abOn)&BitMask_01)));
}

void Sens(SENS_FLPw)(BYTE abOn){
	SetSens(0x3007, ((GetSens(0x3007)&(~ValSft_L00(BitMask_01)))|ValSft_L00((abOn)&BitMask_01)));
}


