/* **************************************************************************
 File Name	:	EN772_SENS_IMX225.c
 Description	:	EN772 - IMX225 device driver
  Modifier		:	Lee, Gyu Hong
 Date		:	19. 12. 18
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#undef model_Sens
#include "../Src/dev.h"
#define model_Sens	SENS_IMX225
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

// -----------------------------------------------------------------------------------------
// initial
	// IMX225 MIPI
	// MIPI : Normal 2 -lane
	// Output bit : 12bit
	// INCK : 37.125MHz
	
	const WORD gwTblSens0[][3] = {	//ADDR	  	 1M30P	   1M 60P
									//ID2
									{0x3005, 	  0x01,		0x01},	// ADBIT - 0x1 : 12bit / 0x0 : 10bit
									{0x3007, 	  0x10,		0x10},	// WINMODE, H/V Reverse
									{0x3009, 	  0x02,		0x01},	// FRSEL
									{0x300a,	  0x00,		0x00},  // BLKLEVEL_LSB
									{0x300b, 	  0x00,		0x00}, 	// BLKLEVEL_MSB
									{0x300f, 	  0x00,		0x00},
									{0x3012, 	  0x2c,		0x2c},
									{0x3013, 	  0x01,		0x01},
									{0x3016, 	  0x09,		0x09},
									
//									{0x3018, 	  0xee,		0xee},	// VMAX
//									{0x3019, 	  0x02,		0x02},	// VMAX

//									{0x301b, 	  0xc8,		0xe4},	// HMAX
//									{0x301c, 	  0x19,		0x0c},	// HMAX

									{0x301d, 	  0xc2,		0xc2},
//									{0x3044, 	  0xe0,		0xe0},	// ODBIT, OPORTSEL

//									{0x3046, 	  0x01,		0x01},	//DCK Synchronous Register1
//									{0x3047, 	  0x03,		0x01},	//DCK Synchronous Register2
//									{0x3048,   	  0xC0,		0x01},	//DCK Synchronous Register3

									{0x3044,      0x01,     0x01}, 	// ODBIT, OPORTSEL (MIPI : 0x1)
//                                  {0x3049,      0x0a,     0x0a}, 	// XVSOUTSEL, XHSOUTSEL
									{0x3054, 	  0x66,		0x66},	// CMOS, MIPI Fixed to 0x66
									{0x305c, 	  0x20,		0x20},  // INCKSEL1
									{0x305d, 	  0x00,		0x00},  // INCKSEL2
									{0x305e, 	  0x20,		0x20},  // INCKSEL3
									{0x305f, 	  0x00,		0x00},  // INCKSEL4
									{0x3070, 	  0x02,		0x02},
									{0x3071, 	  0x01,		0x01},
									{0x309e,	  0x22, 	0x22},
									{0x30a5, 	  0xfb,		0xfb},
									{0x30a6, 	  0x02,		0x02},
									{0x30b3, 	  0xff,		0xff},
									{0x30b4, 	  0x01,		0x01},
									{0x30b5, 	  0x42,		0x42},
									{0x30b8, 	  0x10,		0x10},
									{0x30c2, 	  0x01,		0x01},

									//ID3
									{0x310f, 	  0x0f,		0x0f},
									{0x3110, 	  0x0e,		0x0e},
									{0x3111, 	  0xe7,		0xe7},
									{0x3112, 	  0x9c,		0x9c},
									{0x3113, 	  0x83,		0x83},
									{0x3114,	  0x10, 	0x10},
									{0x3115, 	  0x42,		0x42},
									{0x3128,	  0x1e, 	0x1e},
									{0x31ed,	  0x38, 	0x38},


									//ID4
									{0x320c,	  0xcf, 	0xcf},
									{0x324c,	  0x40, 	0x40},
									{0x324d,	  0x03, 	0x03},
									{0x3261,	  0xe0, 	0xe0},
									{0x3262,	  0x02, 	0x02},
									{0x326e,	  0x2f, 	0x2f},
									{0x326f,	  0x30, 	0x30},
									{0x3270,	  0x03, 	0x03},
									{0x3298,	  0x00, 	0x00},
									{0x329a,	  0x12, 	0x12},
									{0x329b,	  0xf1, 	0xf1},
									{0x329c,	  0x0c, 	0x0c},
									
									//ID5
									{0x3344,	  0x10, 	0x00},
									{0x3346,	  0x01, 	0x01},
									{0x3353,	  0x04, 	0x04},
									{0x3357,	  0xd9, 	0xd9},
									{0x3358,	  0x02, 	0x02},
									{0x336b,	  0x2f, 	0x2f},
									{0x337f,	  0x01, 	0x01},
									{0x3380,	  0x20, 	0x20},
									{0x3381,	  0x25, 	0x25},
									{0x3382,	  0x5f, 	0x5f},
									{0x3383,	  0x17, 	0x17},
									{0x3384,	  0x37, 	0x37},
									{0x3385,	  0x17, 	0x17},
									{0x3386,	  0x17, 	0x17},
									{0x3387,	  0x17, 	0x17},
									{0x3388,	  0x4f, 	0x4f},
									{0x3389,	  0x22, 	0x22},
									{0x338d,	  0xb4, 	0xb4},
									{0x338e,	  0x01, 	0x01},
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
					(_12BIT),\
					/* 3210, 10, 0 */\
					(_10),\
					/* Word Count */\
					(0x7B0),\
					/* MIPI Line information or Virtual channel mode */\
					(_NOT_USED),\
					(aiWdrMode));
}

void LibInitSens(int aiMode, int aiOption)
{	// IMX225, Sensor Master mode
	// aiMode (Normal)  - 0 : 1M30P, 1 : 1M 60P, 2 : 1M 120P
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
	for (i=0; i<gTblSensEa; i++)	{	SetSens(gwTblSens0[i][0], (BYTE)gwTblSens0[i][1+(aiMode*1)+aiOption]);} // No option

	//Shutter Speed Max
	gnAeNorMax = gnInModeVtw-AE_SHTMAX_OFST;
	
	SetSens(0x3003, 0x00);						// SW reset OFF
	SetSens(0x3001, 0x00);						// REG Hold OFF
	SetSens(0x3000, 0x0);	WaitUs(30000);		// standby cancel
	SetSens(0x3002, 0x0);	WaitUs(20000);		// xmaster

}

void ISPM Sens(AE_SHTLw)(UINT val)
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



// -----------------------------------------------------------------------------------------
// AWB
// -----------------------------------------------------------------------------------------
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
										/*
										// Target matrix
										{	      48665575945434LL,	         10483255474LL,	        -88223343842LL,	           131117034LL,	            92340279LL,	           123691532LL},
										{	       7583596792440LL,	        -41284994273LL,	         -9375043305LL,	          -175898454LL,	          -134374269LL,	           -96168608LL},
										{	     116699836845678LL,	        565626245194LL,	        294804221763LL,	           958551163LL,	          1019652092LL,	           467372840LL},
										{	     -32210220130782LL,	        -17628217367LL,	        -29150144432LL,	            27163523LL,	            19394917LL,	            15223595LL},
										{	     119581013223621LL,	        185167468064LL,	        180750053038LL,	           352415379LL,	           154593662LL,	           187896531LL},
										{	      60150669213507LL,	        297296866075LL,	         30389029860LL,	           -13675301LL,	           551772616LL,	           -27714772LL},
										{	       7801695988077LL,	         80932294155LL,	         65934791321LL,	           352862335LL,	           180189508LL,	           200409105LL},
										{	      -8764849836201LL,	       -209930735807LL,	       -202228523642LL,	          -777950036LL,	          -449894233LL,	          -470302190LL},
										{	     302834185528574LL,	       1497172951021LL,	       1244152617397LL,	          3747488678LL,	          2693150023LL,	          2347044439LL}
										*/
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


