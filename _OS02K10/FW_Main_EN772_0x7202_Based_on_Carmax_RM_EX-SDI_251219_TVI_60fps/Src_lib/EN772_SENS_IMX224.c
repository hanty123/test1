/* **************************************************************************
 File Name		:	EN772_SENS_IMX224.c
 Description	:	EN772 - IMX224 device driver
 Modifier		:	Lee, Gyu Hong
 Date			:	20. 04. 22
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#undef model_Sens
#include "../Src/dev.h"
#define model_Sens	SENS_IMX224
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

#define AE_SHTMAX_OFST	2
#define AE_SHTMIN_OFST	2
#define AE_SHTMAX		(nMok-AE_SHTMAX_OFST)

#define AE_GAIN_UNIT_MAX		(720)  															// Sensor gain step by Unit
#define AE_GAIN_UNIT_EA			(1)																// Sensor gain Unit EA
#define AE_GAIN_UNIT_OVR		(60)															// Sensor gain extended step
#define AE_GAIN_UNIT_OVR2		(0)    															// ISP gain extended step

const int Sens(AE_GAIN_TOTAL) = (((AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR)*(1));
const int Sens(AE_GAIN_TOTAL2) = 0;

#define AE_GAIN_DENORMAL(val)	(ifdiv8(val*(int)(1.f*256.f)))		// 171211 LH : int floating

#define AE_HSS_FLT_EA		(sizeof(gbAeHssFltTbl))
#define AE_SHT_TBL_EA		(sizeof(gnAeShtTbl)/8)
#define AE_LWDR_HSS_FLT_EA	(sizeof(gwAeHssFltTbl_Pgain)/2)


//190318 LGH
#define AE_LWDR_2P_RHS1			(   /*9*/25)
#define AE_LWDR_FSC				(gnInModeVtw*2)
#define AE_LWDR_PIC_SIZE_V		((735 + (AE_LWDR_2P_RHS1-1)/2)*2)				// IMX224_AppNote_DOL_E_Rev1.8.


#define AE_LWDR_2P_L0MIN_OFST	(	3)
#define AE_LWDR_2P_L0MAX_OFST	(	2)

#define AE_LWDR_2P_S1MIN_OFST	(	3)
#define AE_LWDR_2P_S1MAX_OFST	(	2)

#define AE_LWDR_2P_L0_MAX		(AE_LWDR_FSC - AE_LWDR_2P_L0MAX_OFST)			// L0 Max shutter line at DOL 2P		// Option 1
#define AE_LWDR_2P_L0_MIN		(AE_LWDR_2P_RHS1 + AE_LWDR_2P_L0MIN_OFST)		// L0 Max shutter line at DOL 2P

#define AE_LWDR_2P_S1_MAX		(AE_LWDR_2P_RHS1 - AE_LWDR_2P_S1MAX_OFST)		// S1 Max shutter line at DOL 2P
#define AE_LWDR_2P_S1_MIN		(AE_LWDR_2P_S1MIN_OFST)							// S1 Max shutter line at DOL 2P

//#define AE_SENS_AGC_LMT			(AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA+AE_GAIN_UNIT_OVR)	// LWDR Mode AGC Limit 
//#define AE_SENS_AGC_LMT			( 100)											// LWDR Mode AGC Limit (100 * 0.3 = 30dB)		//Option 2

// -----------------------------------------------------------------------------------------
// initial
	// IMX224 MIPI
	// MIPI : Normal 2 -lane / DOL 2M 60fps 4 -lane
	// Output bit : 12bit
	// INCK : 37.125MHz
	const WORD gwTblSens0[][5] = {	//ADDR	  	 Nor 1M30P	Dol 1M30P	Nor 1M60P	Dol 1M60P
									//ID2                        	
									{0x3002, 	  0x00,	   	0x00, 		0x00,		0x00},	// XMSTA
									{0x3005, 	  0x01,		0x00,		0x01,		0x00},	// ADBIT
									{0x3007, 	  0x10,		0x10,		0x10,		0x10},	// WINMODE, H/V Reverse
									{0x3009, 	  0x02,		0x01,		0x01,		0x00},	// FRSEL
									{0x300a,	  0x00,		0x00,		0x00,		0x00},  // BLKLEVEL_LSB
									{0x300b, 	  0x00,		0x00,		0x00,		0x00}, 	// BLKLEVEL_MSB
									{0x300c, 	  0x00,		0x11,		0x00,		0x11},	// DOL
									{0x300f, 	  0x00,		0x00,		0x00,		0x00},
									{0x3012, 	  0x2c,		0x2c,		0x2c,		0x2c},
									{0x3013, 	  0x01,		0x01,		0x01,		0x01},
									{0x3016, 	  0x09,		0x09,		0x09,		0x09},
									
//									{0x3018, 	  0xee,		0xee,		0xee,		0xee},	// VMAX
//									{0x3019, 	  0x02,		0x02,		0x02,		0x02},	// VMAX

//									{0x301b, 	  0xc8,		0xe4,		0xe4,		0x72},	// HMAX
//									{0x301c, 	  0x19,		0x0c,		0x0c,		0x06},	// HMAX

									{0x301d, 	  0xc2,		0xc2,		0xc2,		0xc2},
									{0x3043, 	  0x01,		0x05,		0x01,		0x05},	// DOL
									{0x3044, 	  0x01,		0x01,		0x01,		0x01},	// ODBIT, OPORTSEL
//									{0x3044, 	  0x01,		0x00,		0x01,		0x00},	// ODBIT, OPORTSEL			**

//                                    {0x3049,      0x0a,    	0x0a, 		0x0a,       0x0a}, 	// XVSOUTSEL, XHSOUTSEL
									{0x3054, 	  0x66,		0x66,		0x66,		0x66},	// CMOS, CSI-2 Fixed to 0x66
									{0x305c, 	  0x20,		0x20,		0x20,		0x20},  // INCKSEL1
									{0x305d, 	  0x00,		0x00,		0x00,		0x00},  // INCKSEL2
									{0x305e, 	  0x20,		0x20,		0x20,		0x20},  // INCKSEL3
									{0x305f, 	  0x00,		0x00,		0x00,		0x00},  // INCKSEL4
									{0x3070, 	  0x02,		0x02,		0x02,		0x02},
									{0x3071, 	  0x01,		0x01,		0x01,		0x01},
									{0x309e,	  0x22, 	0x22,		0x22,		0x22},
									{0x30a5, 	  0xfb,		0xfb,		0xfb,		0xfb},
									{0x30a6, 	  0x02,		0x02,		0x02,		0x02},
									{0x30b3, 	  0xff,		0xff,		0xff,		0xff},
									{0x30b4, 	  0x01,		0x01,		0x01,		0x01},
									{0x30b5, 	  0x42,		0x42,		0x42,		0x42},
									{0x30b8, 	  0x10,		0x10,		0x10,		0x10},
									{0x30c2, 	  0x01,		0x01,		0x01,		0x01},
                                                                		                
									//ID3                       		                
									{0x3108, 	  0x00,		0x11,		0x00,		0x11},	// DOL
									{0x3109, 	  0x00,		0x01,		0x00,		0x01},	// DOL
									{0x310f, 	  0x0f,		0x0f,		0x0f,		0x0f},
									{0x3110, 	  0x0e,		0x0e,		0x0e,		0x0e},
									{0x3111, 	  0xe7,		0xe7,		0xe7,		0xe7},
									{0x3112, 	  0x9c,		0x9c,		0x9c,		0x9c},
									{0x3113, 	  0x83,		0x83,		0x83,		0x83},
									{0x3114,	  0x10, 	0x10,		0x10,		0x10},
									{0x3115, 	  0x42,		0x42,		0x42,		0x42},
									{0x3128,	  0x1e, 	0x1e,		0x1e,		0x1e},
									{0x31ed,	  0x38, 	0x38,		0x38,		0x38},
                                                                		                
                                                                		                
									//ID4                       		                
									{0x320c,	  0xcf, 	0xcf,		0xcf,		0xcf},
									{0x324c,	  0x40, 	0x40,		0x40,		0x40},
									{0x324d,	  0x03, 	0x03,		0x03,		0x03},
									{0x3261,	  0xe0, 	0xe0,		0xe0,		0xe0},
									{0x3262,	  0x02, 	0x02,		0x02,		0x02},
									{0x326e,	  0x2f, 	0x2f,		0x2f,		0x2f},
									{0x326f,	  0x30, 	0x30,		0x30,		0x30},
									{0x3270,	  0x03, 	0x03,		0x03,		0x03},
									{0x3298,	  0x00, 	0x00,		0x00,		0x00},
									{0x329a,	  0x12, 	0x12,		0x12,		0x12},
									{0x329b,	  0xf1, 	0xf1,		0xf1,		0xf1},
									{0x329c,	  0x0c, 	0x0c,		0x0c,		0x0c},
									
									//ID5
									{0x3344,	  0x10, 	0x00,		0x00,		0x00},	//
									{0x3346,	  0x01, 	0x01,		0x01,		0x03},	//
									{0x3353,	  0x04, 	0x04,		0x04,		0x04},	//
									{0x3354,	  0x01, 	0x00,		0x01,		0x00},	//						**
									{0x3357,	  0xD9, 	0xD9,		0xD9,		0xD9},	//PIC_SIZE_V
									{0x3358,	  0x02, 	0x02,		0x02,		0x02},	//PIC_SIZE_V
									{0x336B,	  0x37, 	0x57,		0x57,		0x57},	//

									{0x337D,	  0x0C, 	0x0A,		0x0C,		0x0A},	//
									{0x337E,	  0x0C, 	0x0A,		0x0C,		0x0A},	//
									{0x337F,	  0x01, 	0x01,		0x01,		0x03},	//
									{0x3380,	  0x20, 	0x20,		0x20,		0x20},	//
									{0x3381,	  0x25, 	0x25,		0x25,		0x25},	//
									{0x3382,	  0x5F, 	0x6F,		0x6F,		0x6F},	//
									{0x3383,	  0x17, 	0x27,		0x27,		0x27},	//
									{0x3384,	  0x37, 	0x4F,		0x4F,		0x4F},	//
									{0x3385,	  0x17, 	0x2F,		0x2F,		0x2F},	//
									{0x3386,	  0x17, 	0x2F,		0x2F,		0x2F},	//
									{0x3387,	  0x17, 	0x2F,		0x2F,		0x2F},	//
									{0x3388,	  0x4F, 	0x9F,		0x9F,		0x9F},	//
									{0x3389,	  0x27, 	0x37,		0x37,		0x37},	//

									{0x338D,	  0xB4, 	0xB4,		0xB4,		0xB4},	//
									{0x338E,	  0x01, 	0x01,		0x01,		0x01}	//
								};


//----------------------------------------------------------------------------------------

const UINT gTblSensEa		= numberof(gwTblSens0);

// -----------------------------------------------------------------------------------------
// AE
// -----------------------------------------------------------------------------------------
	const BYTE 	gbAeHssFltTbl[]   = {
									0,
									0,
									60,
									35,
									25,
									19,
									16,
									13,
									11,
									10,
									9 ,
									8 ,
									7 ,
									7 ,
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
									{0	,	256    },
									{14 ,	300    },
									{28 ,	353    },
									{42 ,	415    },
									{56 ,	487    },
									{70 ,	573    },
									{84 ,	673    },
									{98 ,	791    },
									{112,	929    },
									{126,	1092   },
									{140,	1283   },
									{154,	1507   },
									{168,	1771   },
									{182,	2080   },
									{196,	2444   },
									{210,	2872   },
									{224,	3374   },
									{238,	3964   },
									{252,	4658   },
									{266,	5473   },
									{280,	6430   },
									{294,	7555   },
									{308,	8876   },
									{322,	10428  },
									{336,	12252  },
									{350,	14395  },
									{364,	16913  },
									{378,	19871  },
									{392,	23347  },
									{406,	27430  },
									{420,	32228  },
									{434,	37865  },
									{448,	44487  },
									{462,	52268  },
									{476,	61410  },
									{490,	72150  },
									{504,	84769  },
									{518,	99595  },
									{532,	117014 },
									{546,	137480 },
									{560,	161525 },
									{574,	189775 },
									{588,	222966 },
									{602,	261963 },
									{616,	307779 },
									{630,	361609 },
									{644,	424854 },
									{658,	499160 },
									{672,	586462 },
									{686,	689032 },
									{700,	809543 },
									{714,	951130 },
									{728,	1117480},
									{742,	1312925},
									{756,	1542552},
									{770,	1812341},
									{784,	2129315},
									{798,	2501727},
									{812,	2939273},
									{826,	3453344},
									{840,	4057326},
									{854,	4766943},
									{868,	5600669},
									{882,	6580213}
									};

	const WORD 	gwAeHssFltTbl_Pgain[]   = {
									0x200,	// 0
									0x181,	// 1
									0x157,	// 2
									0x143,	// 3
									0x136,	// 4
									0x12D,
									0x127,
									0x123,
									0x120,
									0x11D,
									0x11B,
									0x11A,
									0x118,
									0x117,
									0x116,
									0x115,
									0x114,
									0x114,
									0x114,
									0x113,
									0x112,
									0x111,
									0x111,
									0x111,
									0x110,
									0x10D,
									0x10A,
									0x107,
									0x106,
									0x102,
									0x101,
									0x101,
									0x100,
									0x100,
									0x100,
									0x100,
									0x100
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
					(((aiResMode==MD_1M_FPS_50_60)&&(aiWdrMode==MN_ON))?(_4LANE):(_2LANE)),\
					/* 12BIT or 10BIT */\
					((aiWdrMode==MN_OFF)?(_12BIT):(_10BIT)),\
					/* 3210, 10, 0 */\
					(((aiResMode==MD_2M_FPS_50_60)&&(aiWdrMode==MN_ON))?(_3210):(_10)),\
					/* Word Count */\
					((aiWdrMode==MN_OFF)?(0x7B0):(0x66D)),\
					/* MIPI Line information or Virtual channel mode */\
					(_MIPI_LI),\
					(aiWdrMode));
}


void LibInitSens(int aiMode, int aiOption)
{	// IMX224, Sensor Master mode
	// aiMode (Normal)  - 0 : 1M30P, 1 : 1M 60P
	// aiOption (DOL)	- 0 : OFF, 	 1 : ON (DOL2P)

	UINT i;
	static BYTE bInitSet = 0x1;
	static BYTE bModeIndx = 0x0;

	if(bInitSet){

	// Sensor H/W Reset
	GpioSetLo(GPIO_SRSTN);	WaitUs(10000);		GpioSetHi(GPIO_SRSTN);	WaitUs(10000);

	for(i=0; i<10; i++) {
		if(i2c_write(SENS_SONY_DEV,1,0) == 0) {
			gbSensorOff = 0;
			TxStrNoIRQ("SI2C connected.", 0, 0);
			break;
		}
		WaitUs(1000);
	}
	if(gbSensorOff) TxStrNoIRQ("SI2C not connected.", 0, 0);

		bInitSet = 0x0;
	}

	bModeIndx = ((aiMode==MD_CVBS)||(aiMode==MD_1M_FPS_50_60))?(1):(0);
	LibRdesIsp(bModeIndx, aiOption);
	
	SetSens(0x3000, 0x1);	WaitUs(1000);		// standby
	SetSens(0x3002, 0x1);	WaitUs(1000);		// xmaster stop
	SetSens(0x3001, 0x01);						// REG Hold
	SetSens(0x3003, 0x01);						// SW reset

	// 180503 LGH
//	for (i=0; i<gTblSensEa; i++)	{	SetSens(0, gwTblSens0[i][0], (BYTE)gwTblSens0[i][1+(aiMode*1)+aiOption]);} // No option
	for (i=0; i<gTblSensEa; i++)	{	SetSens(gwTblSens0[i][0], (BYTE)gwTblSens0[i][1+(aiMode*2)+aiOption]);}		//180321 LGH : If FWDR mode, sensor is 60p set.
	
	SetSens(0x3003, 0x00);						// SW reset OFF
	SetSens(0x3001, 0x00);						// REG Hold OFF
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
		SetSensBst(0x302C, (AE_LWDR_2P_RHS1&0xFFFFF), 3);

		//PIC_SIZE_V
		SetSensBst(0x3357, (AE_LWDR_PIC_SIZE_V&0x1FFF),2);
	}
}

void ISPM Sens(AE_SHTLw)(UINT val)
{
	SetSensBst(((!gbModeWdrOn_L)?(0x3020):(0x3023)), (val&0x3FFFF), 3);
}

void ISPM Sens(AE_SHTSw)(UINT val)
{
	SetSensBst(0x3020, (val&0x3FFFF), 3);
}

void ISPM Sens(AE_AGCw)(UINT val)
{
	SetSensBst(0x3014, (val&0x03FF), 2);
}

void ISPM Sens(AE_DGCw)(UINT val)
{
	UNUSED_ARG(val);
}

void ISPM Sens(AE_FREQw)(UINT val, UINT val1)
{
	UNUSED_ARG(val);
//	UNUSED_ARG(val1);
//	extern BYTE gbModeWdrOn_L;

//	if (gbModeWdrOn_L) val1 = val1/2;		// if DOL mode

	SetSensBst(0x3018, (val&0x1FFFF), 3);
	SetSensBst(0x301B, (val1&0x3FFF), 2);
}

//----------------------------------------------------------------------------------------

UINT ISPM LibAeShtLine(UINT anLine)	// Fixed
{
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

	for(i=1; i<anTblEa; i++) {
		if (aiVal<(int)gnAeShtTbl[i][0]) {
			nShtFlt = LibUtlInterp1D (aiVal, gnAeShtTbl[i-1][0], gnAeShtTbl[i][0], gnAeShtTbl[i-1][1], gnAeShtTbl[i][1]);
			nShtInt = nShtFlt>>7;

			if (nShtInt<anFltEa)		nShtFlt = LibUtlInterp1D (nShtFlt, (nShtInt<<7), (nShtInt<<7)+0x80, 0, gbAeHssFltTbl[nShtInt]);
			else 						nShtFlt = 0;
//			nShtFlt = MIN(nShtFlt, 0x80);
			break;
		}
	}
	*apnShtFlt = nShtFlt;
	*apnShtInt = nShtInt;
}

void ISPM LibAeShtIntp_LWDR(int aiVal, const UINT anTblEa, const UINT anFltEa, UINT* apnShtFlt, UINT* apnShtInt)	// Fixed
{
 	UINT	nShtFlt=0;
	UINT	nShtInt=0;
	UINT 	i;

	for(i=1; i<anTblEa; i++) {
		if (aiVal<(int)gnAeShtTbl[i][0]) {
			nShtFlt = LibUtlInterp1D (aiVal, gnAeShtTbl[i-1][0], gnAeShtTbl[i][0], gnAeShtTbl[i-1][1], gnAeShtTbl[i][1]);
			nShtInt = nShtFlt>>7;

			if (nShtInt<anFltEa)		nShtFlt = LibUtlInterp1D (nShtFlt, (nShtInt<<7), (nShtInt<<7)+0x80, 0x100, gwAeHssFltTbl_Pgain[nShtInt]);
			else 						nShtFlt = 0;
//			nShtFlt = MIN(nShtFlt, 0x80);
			break;
		}
	}

	*apnShtFlt = nShtFlt;
	*apnShtInt = nShtInt;
}

WORD ISPM AeSHT(int aiVal, UINT anManual, UINT anManualVal)
{	// Shutter driver

//** IMX225 HD 10bit : Shutter 2 to 748(VMAX-2)

	UINT 	nMok = gnInModeVtw;
	UINT	nRem = 0;
	UINT	nShtMax = 0;
	static 	UINT	gnShtFlt=0;
	UINT	nShtInt = 0;

	if (gnAeState==0){
		LibAePrgain_L(LibAePrgainIntp(gnShtFlt));
	}
	
	LibAeShtIntp (aiVal, AE_SHT_TBL_EA, AE_HSS_FLT_EA, &gnShtFlt, &nShtInt);

#if(0)
	if (gnAeState==0){
		gnShtFlt = AE_GAIN_DENORMAL(gnShtFlt);
		gnShtFlt = MINMAX(gnShtFlt, 0, (UINT)(AE_GAIN_UNIT_EA*AE_GAIN_UNIT_MAX));
 		AE_AGCw(gnShtFlt);				//Shutter Control State, AGC
	}
#endif

	if (anManual) {
		nMok 	= (UINT)(MAX(((int)anManualVal - AE_SHTMAX_OFST), (int)0))/gnInModeVtw;
		nMok	= ((nMok*gnInModeVtw) + gnInModeVtw);

		nShtMax = AE_SHTMAX;
		nRem = MINMAX(anManualVal,AE_SHTMIN_OFST, nShtMax);
	}
	//Shutter Control State
	else {
		nMok 	= gnInModeVtw;
		nShtMax = AE_SHTMAX;
		nRem 	= MIN(nShtInt, nShtMax);
	}

	AE_SHTLw((nShtMax-nRem+AE_SHTMIN_OFST));
	
	DebugDisp(gbAeDebugOn, Dec, "SHT_int__d", 1, 24, nRem		)
	DebugDisp(gbAeDebugOn, Dec, "SHT_flt__d", 2, 24, gnShtFlt	)

	return ((WORD)(nRem));

}

void ISPM AeAGC(int aiVal)
{	/// AGC driver
	static int	giAgc;
	static int  iChk;
	const UINT nAGC_LMT = AE_GAIN_DENORMAL(AE_SENS_AGC_LMT_NOR);
	static UINT nLWdrGain;
	
	SetSens(0x3009, ((0x3&GetSens(0x3009))|(iChk<<4)) );	//  FRSEL(fixed) + HCG	// 170621 LH

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

	static	UINT	gnShtFlt_L, gnShtFlt_S;
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
	// aiMode : 0: off, 1: 2 page, 2: 3 page
	// aiVal : Long
	// aiVal1 : short1
	// aiVal2 : short2

	UNUSED_ARG(aiMode);
	UNUSED_ARG(aiVal1);

	static int	giAgcL;
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

	if (gnAeState!=0)	{
		LibAePrgain_L(0x100);
		LibAePrgain_S(0x100);

		AE_AGCw(giAgcL);
	}

	DebugDisp(gbAeDebugOn, Hex, "AGC0____", 5, 24, (iChk<<16)|giAgcL)
	DebugDisp(gbAeDebugOn, Hex, "WDR_GAIN", 6, 24, (giAeLWdrGain))
}


// -----------------------------------------------------------------------------------------
// AWB
// -----------------------------------------------------------------------------------------

#if(0)
	const s64 glMtxCf[9][6] =		{	// Y 360
									{		  57727429718144LL, 		  -311863818LL, 	   -102767475387LL, 			53744260LL, 			57030016LL, 			80390159LL},
									{		 -14389951038236LL, 		-42832093920LL, 		-10692722222LL, 		  -108314486LL, 		   -90297864LL, 		   -52599469LL},
									{		  62333509339780LL, 		293999733746LL, 		125315760609LL, 		   446726124LL, 		   526164951LL, 		   178349433LL},
									{		 -14435509005806LL, 		-10622563333LL, 		-25162226327LL, 			32059482LL, 			21280943LL, 			23741172LL},
									{		  70234526969519LL, 		 97712577006LL, 		 92341100878LL, 		   149564368LL, 			59558681LL, 			71476925LL},
									{		  58400439109052LL, 		295731629131LL, 		135177339013LL, 		   336108741LL, 		   540310987LL, 		   214056512LL},
									{		  23563938592873LL, 		107113931406LL, 		102412103460LL, 		   420794886LL, 		   209107764LL, 		   238885936LL},
									{		 -72143363906940LL, 	   -359737465653LL, 	   -363977632960LL, 		 -1197404472LL, 		  -651036733LL, 		  -724049147LL},
									{		 352774067630654LL, 	   1762586012630LL, 	   1646813044353LL, 		  4978772519LL, 		  3157339345LL, 		  3183765256LL}
									};
#else
	const s64 glMtxCf[9][6] =		{	// Y 360
									{	      55556100699839LL,	         -4090024996LL,	       -139624728281LL,	            64768289LL,	            81653316LL,	            95582668LL},
									{	      29912118179250LL,	         12033381546LL,	         25980761148LL,	          -125491391LL,	           -84151587LL,	           -81644690LL},
									{	      41091732794301LL,	        108278125374LL,	        260258153939LL,	           721439464LL,	           328689132LL,	           592037403LL},
									{	     -50803652303650LL,	        -77636935218LL,	        -74657478624LL,	          -105962382LL,	           -68012471LL,	           -44411485LL},
									{	     184006318562067LL,	        388316158628LL,	        273417197088LL,	           589814600LL,	           421063714LL,	           224299473LL},
									{	     -49941988224235LL,	       -361560321511LL,	         47141969067LL,	          -232095047LL,	          -473535066LL,	           329598576LL},
									{	       7456331398956LL,	        101965606135LL,	         30175648342LL,	           296868808LL,	           222190672LL,	           122171500LL},
									{	      -7529358909416LL,	       -266281461646LL,	       -214045014995LL,	          -872438453LL,	          -581003553LL,	          -466514140LL},
									{	     299453823011479LL,	       1421873849280LL,	       1671794092170LL,	          4821989092LL,	          2710200712LL,	          3200614517LL}
									};
#endif

// -----------------------------------------------------------------------------------------
// MIRROR & FLIP
// -----------------------------------------------------------------------------------------

void Sens(SENS_MIRw)(BYTE abOn){
	SetSens(0x3007, ((GetSens(0x3007)&(~ValSft_L01(BitMask_01)))|ValSft_L01((abOn)&BitMask_01)));
}

void Sens(SENS_FLPw)(BYTE abOn){
	SetSens(0x3007, ((GetSens(0x3007)&(~ValSft_L00(BitMask_01)))|ValSft_L00((abOn)&BitMask_01)));
}


