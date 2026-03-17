/* **************************************************************************
 File Name		:	EN772_801_SENS_LFM_AR0233.c
 Description	:	EN772 - AR0233 device driver
 Designer		:	Gyu Hong, Lee
 Date			:	20. 08. 03
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#undef model_Sens
#include "../Src/dev.h"
#define model_Sens	SENS_AR0233
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

extern UINT gnInModeVtw;
extern BYTE gbAeDebugOn;

#define AE_SHTMAX_OFST	1
#define AE_SHTMIN_OFST	2
#define AE_SHTMAX		(nMok-AE_SHTMAX_OFST)

#define AE_GAIN_UNIT_MAX		(264)	    																	// Sensor gain step by Unit
#define AE_GAIN_UNIT_EA			(1)																				// Sensor gain Unit EA
#define AE_GAIN_UNIT_OVR		(171)																			// Sensor gain extended step
#define AE_GAIN_UNIT_OVR2		(0)	    																		// ISP gain extended step

const int Sens(AE_GAIN_TOTAL) = (((AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR)*(0.169/0.1));
const int Sens(AE_GAIN_TOTAL2) = 0;

#define AE_GAIN_DENORMAL(val)		(ifdiv8(val*(int)(0.595f*256.f)))

//#define AE_GAIN_DENORMAL(val)	(ifdiv8(val*(int)(0.34f*256.f)))		// 171211 LH : int floating

#define AE_HSS_FLT_EA		(sizeof(gbAeHssFltTbl))
#define AE_SHT_TBL_EA		(sizeof(gnAeShtTbl)/8)


//#define AE_LWDR_3P_L0_MAX		3349								// L0 Max shutter line at DOL 3P
//#define AE_LWDR_3P_S1_MAX		1137								// S1 Max shutter line at DOL 3P
//#define AE_LWDR_3P_S2_MAX		138									// S2 Max shutter line at DOL 3P
//
////#define AE_LWDR_2P_L0_MAX		2236								// L0 Max shutter line at DOL 2P (org)
////#define AE_LWDR_2P_S1_MAX		8									// S1 Max shutter line at DOL 2P (org)
//#define AE_LWDR_2P_L0_MAX		2210								// L0 Max shutter line at DOL 2P
//#define AE_LWDR_2P_S1_MAX		34									// S1 Max shutter line at DOL 2P
//
//
//extern UINT gnAeLWdrMaxL0;
//extern UINT gnAeLWdrMaxS1;

// -----------------------------------------------------------------------------------------
// initial

	// Chip ID 0x2
	const WORD gwTblSens0[][3] =    {			//2M30P		//2M60P 
								
									//[PLL_settings]
									{0x302A,	0x0006,		0x0004},
									{0x302C,	0x0702,		0x0701},
									{0x302E,	0x0003,		0x0002},
									{0x3030,	0x0063,		0x0025},
									{0x3036,	0x0006,		0x0006},
									{0x3038,	0x0002,		0x0002},
									{0x31DC,	0x1FB0,		0x1FB0},
									{0x30B0,	0x8800,		0x8800},
									//[MIPI Port Timing]   	      
									{0x31B0,	0x006B,		0x006B},
									{0x31B2,	0x004A,		0x004A},
									{0x31B4,	0x51C7,		0x51C7},
									{0x31B6,	0x3247,		0x3247},
									{0x31B8,	0x60C9,		0x60C9},
									{0x31BA,	0x028A,		0x028A},
									{0x31BC,	0x0B88,		0x0B88},
									{0x3342,	0x122C,		0x122C},
									{0x3344,	0x0011,		0x0011},
									{0x3346,	0x122C,		0x122C},
									{0x3348,	0x0011,		0x0011},
									{0x334A,	0x122C,		0x122C},
									{0x334C,	0x0011,		0x0011},
									{0x334E,	0x122C,		0x122C},
									{0x3350,	0x0011,		0x0011},
									{0x336E,	0x0147,		0x0147},
									//[Timing_settings]           
									{0x3004,	0x0042, 	0x0042},
									{0x3008,	0x07D1,     0x07D1},
									{0x3002,	0x0062,     0x0062},
									{0x3006,	0x049F,     0x049F},
									{0x30A2,	0x0001,     0x0001},
									{0x30A6,	0x0001,     0x0001},
									{0x3402,	0x0790,     0x0790},
									{0x3404,	0x0432,     0x0432},
									{0x3040,	0x8005,     0x8005},
									{0x3044,	0x0400,     0x0400},
									{0x3082,	0x0004,     0x0004},
									{0x30BA,	0x1121,     0x1121},
									{0x33E0,	0x0F80,     0x0F80},
									{0x3180,	0x1001,     0x1001},
									{0x31D0,	0x0001,     0x0001},
									{0x31AE,	0x0204,     0x0204},
									{0x31AC,	0x140C,     0x140C},
									{0x300A,	0x0465,     0x0465},
									{0x300C,	0x0898,     0x073A},
									{0x3012,	0x021C,     0x021C},
									{0x3212,	0x0043,     0x0043},
									{0x3216,	0x0004,     0x0004},
									{0x321A,	0x0001,     0x0001},
									{0x3238,	0x0443,     0x0443},
									{0x32EC,	0x72A0,     0x72A0},
									{0x31C6,	0x0000,     0x0000},
									{0x301A,	0x001C,     0x001C},
									{0x30B0,	0x8800,     0x8800},
									{0x3082,	0x0008,     0x0008},
									{0x3082,	0x0004,     0x0004},
									{0x301A,	0x0018,     0x0018},
									{0x301A,	0x001C,     0x001C},
									{0x301A,	0x0018,     0x0018},
    								};

const UINT gTblSensEa		= numberof(gwTblSens0);

// -----------------------------------------------------------------------------------------
// AE
// -----------------------------------------------------------------------------------------

	const BYTE 	gbAeHssFltTbl[]   = {
									0,	// dummy
									80,
									33,
									19,
									14,
									12,
									8 ,
									7 ,
									6 ,
									5 ,
									5 ,
									4 ,
									4 ,
									3 ,
									2 ,
									2 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1 ,
									1
									};

	const UINT	gnAeShtTbl[][2]   = {
									{0	 , 128     },
									{14  , 150     },
									{28  , 176     },
									{42  , 207     },
									{56  , 243     },
									{70  , 286     },
									{84  , 336     },
									{98  , 395     },
									{112 , 464     },
									{126 , 546     },
									{140 , 641     },
									{154 , 753     },
									{168 , 885     },
									{182 , 1040    },
									{196 , 1222    },
									{210 , 1436    },
									{224 , 1687    },
									{238 , 1982    },
									{252 , 2329    },
									{266 , 2736    },
									{280 , 3215    },
									{294 , 3777    },
									{308 , 4438    },
									{322 , 5214    },
									{336 , 6126    },
									{350 , 7197    },
									{364 , 8456    },
									{378 , 9935    },
									{392 , 11673   },
									{406 , 13715   },
									{420 , 16114   },
									{434 , 18932   },
									{448 , 22243   },
									{462 , 26134   },
									{476 , 30705   },
									{490 , 36075   },
									{504 , 42384   },
									{518 , 49797   },
									{532 , 58507   },
									{546 , 68740   },
									{560 , 80762   },
									{574 , 94887   },
									{588 , 111483  },
									{602 , 130981  },
									{616 , 153889  },
									{630 , 180804  },
									{644 , 212427  },
									{658 , 249580  },
									{672 , 293231  },
									{686 , 344516  },
									{700 , 404771  },
									{714 , 475565  },
									{728 , 558740  },
									{742 , 656462  },
									{756 , 771276  },
									{770 , 906170  },
									{784 , 1064657 },
									{798 , 1250863 },
									{812 , 1469636 },
									{826 , 1726672 },
									{840 , 2028663 },
									{854 , 2383471 },
									{868 , 2800334 },
									{882 , 3290106 },
									{896 , 3865538 },
									{910 , 4541611 },
									{924 , 5335928 },
									{938 , 6269168 },
									{952 , 7365631 },
									{966 , 8653862 },
									{980 , 10167401}
									};


// -----------------------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------------------

void LibInitSens(int aiMode, int aiOption)
{	// AR0233
	// aiMode   - 0 : Normal 30p, 1 : normal 60p
	// aiOption - 0 : OFF, 1 : DOL 2P

    UNUSED_ARG(aiOption);

	if(aiMode==0)	RDES_WCw(0xB58);					// AR0233 MIPI 2M30fps
	else			RDES_WCw(/*0xB40*/0xB4C);					// AR0233 MIPI 2M 60fps
	
	UINT i;

	GpioSetLo(GPIO_SRSTN);	WaitUs(10000);		GpioSetHi(GPIO_SRSTN);	WaitUs(10000);

	for(i=0; i<10; i++) {
		if(i2c_write(SENS_ONSEMI_DEV,1,0) == 0) {
			gbSensorOff = 0;
			TxStrNoIRQ("SI2C connected.", 0, 0);
			break;
		}
		WaitUs(1000);
	}
	if(gbSensorOff) TxStrNoIRQ("SI2C not connected.", 0, 0);

	for (i=0; i<gTblSensEa; i++)	{	SetSens(0, gwTblSens0[i][0], gwTblSens0[i][1+aiMode]);}
//	for (i=0; i<gTblSensEa; i++)	{	SetSens(0, gwTblSens0[i][0], gwTblSens0[i][1+(aiMode*2)+((aiOption)?(1):(0))]);}

	WaitUs(100);
	
    SetSens(0,0x3064, 0x0080);
	SetSens(0,0x301A, 0x001C);
	SetSens(0,0x301A, 0x0018);
	
	WaitUs(100);
	SetSens(0,0x306A, 0x0000);
	SetSens(0,0x301A, 0x001C);
	
	SetSens(0,0x301E, 0x8000);			//PEDESTAL LEVEL

// Knee point in LUT
	SetSens(0,0x34A2, 0x001D);
	SetSens(0,0x34A4, 0x003F);
	SetSens(0,0x34A0, 0x0040);
	SetSens(0,0x34A6, 0x004A);
	SetSens(0,0x3E00, 0x8000);
	SetSens(0,0x34BC, 0x0808);
	SetSens(0,0x3494, 0x0808);
	SetSens(0,0x3496, 0x5F00);
	SetSens(0,0x3474, 0x006F);
	SetSens(0,0x33EA, 0xDC98);
	SetSens(0,0x33EC, 0xEEAF);
	SetSens(0,0x3C08, 0x0104);
	SetSens(0,0x3C06, 0x0C3C);
	SetSens(0,0x3D28, 0xEA60);
	SetSens(0,0x3D2A, 0xEA60);
	SetSens(0,0x3290, 0xF80C);
	SetSens(0,0x3292, 0xF80C);
	SetSens(0,0x3294, 0xF80C);
	SetSens(0,0x3296, 0xF80C);
	SetSens(0,0x3298, 0xFFFF);
	SetSens(0,0x329A, 0xFFFF);
	SetSens(0,0x329C, 0xFFFF);
	SetSens(0,0x329E, 0xFFFF);
	SetSens(0,0x3110, 0x0011);
	SetSens(0,0x3362, 0x0001);
	SetSens(0,0x3238, 0x8443);
	SetSens(0,0x3012, 0x02A5);
	SetSens(0,0x3212, 0x0007);
	SetSens(0,0x3112, 0x71E7);
	SetSens(0,0x31AC, 0x180C);
	SetSens(0,0x31D0, 0x0001);
	SetSens(0,0x33DA, 0x0000);
	SetSens(0,0x33C0, 0x2000);
	SetSens(0,0x33C2, 0x3450);
	SetSens(0,0x33C4, 0x48A0);
	SetSens(0,0x33C6, 0x5CF0);
	SetSens(0,0x33C8, 0x7140);
	SetSens(0,0x33CA, 0x8590);
	SetSens(0,0x33CC, 0x99E0);
	SetSens(0,0x33CE, 0xAE30);
	SetSens(0,0x33D0, 0xC280);
	SetSens(0,0x33D2, 0xD6D0);
	SetSens(0,0x33D4, 0xEB20);
	SetSens(0,0x33D6, 0xFFF0);
	SetSens(0,0x33F4, 0xFFF0);
	SetSens(0,0x33F6, 0xFFF0);
	SetSens(0,0x33F8, 0xFFF0);
	SetSens(0,0x33FA, 0xFFF0);
	                          
	SetSens(0,0x562E, 0x0111);
	SetSens(0,0x3366, 0x1131);
	SetSens(0,0x336A, 0x00C0);
	SetSens(0,0x3E14, 0x003F);
	SetSens(0,0x3E02, 0x0F32);
	SetSens(0,0x562A, 0x03E8);
	SetSens(0,0x3E94, 0x3007);
	SetSens(0,0x3E6E, 0xE200);
	SetSens(0,0x3E98, 0x1000);
	SetSens(0,0x3F92, 0x4C00);
	SetSens(0,0x30B8, 0x000F);
	SetSens(0,0x30B8, 0x0007);
	SetSens(0,0x301A, 0x005C);
	SetSens(0,0x3040, 0x8005);
	
	WaitUs(150);
	     
	SetSens(0,0x3E3E, 0x0042);

	//Shutter Speed Max
	gnAeNorMax = gnInModeVtw-AE_SHTMAX_OFST;
}

void ISPM Sens(AE_SHTLw)(UINT val)
{
	#if(0)
    SetSens(0, 0x3012, (val>>0)&0xffff);
    #endif
}

void ISPM Sens(AE_AGCw)(UINT val)
{
	#if(0)
    SetSens(0,0x3366, gwAGC_T[val][0]);
    SetSens(0,0x3308, gwAGC_T[val][1]);
	#endif
}

void ISPM Sens(AE_FREQw)(UINT val, UINT val1)
{
	#if(0)
	UNUSED_ARG(val);
	UNUSED_ARG(val1);

    SetSens(0, 0x300C, (val1&0xffff));
    #endif
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
	#if(0)
	UINT	nMok = gnInModeVtw;
	UINT	nRem = 0;
	UINT	nShtMax = nMok-1;
	static 	UINT	gnShtFlt = 0;
	UINT	nShtInt = 0;

	#define AE_SHTMAX	(nMok-1)

	LibAeShtIntp (aiVal, AE_SHT_TBL_EA, AE_HSS_FLT_EA, &gnShtFlt, &nShtInt);

	gnShtFlt = MINMAX(gnShtFlt, 0, (UINT)(AE_GAIN_UNIT_EA*AE_GAIN_UNIT_MAX));

	if (gnAeState==0){
        SetSens(0,0x3022, 0x1);
        AE_AGCw(gnShtFlt);
        SetSens(0,0x3022, 0x0);
	}

	if(anManual){
		nMok 	= gnInModeVtw;

		nShtMax = AE_SHTMAX;
		nRem = MINMAX(anManualVal,1, nShtMax);
	}
	else if (gnAeState==3) {
	  nMok 	= nShtInt/gnInModeVtw;
	  nMok 	= ((nMok*gnInModeVtw)+gnInModeVtw);

	  nShtMax = AE_SHTMAX;
	  nRem 	= MIN(nShtInt, nShtMax);
	}
	else {
	  nMok 	= gnInModeVtw	 ;

	  nShtMax = AE_SHTMAX;
	  nRem 	= MIN(nShtInt, nShtMax);
	}

	AE_SHTLw(nRem);		        // 14.2.13

	giCurDss = MAX((int)(nMok/gnInModeVtw)-1, 0);

	DebugDisp(gbAeDebugOn, Dec, "SHT_dss__d", 0, 24, giCurDss	)
	DebugDisp(gbAeDebugOn, Dec, "SHT_int__d", 1, 24, nRem		)
	DebugDisp(gbAeDebugOn, Dec, "SHT_flt__d", 2, 24, gnShtFlt	)

	return ((WORD)nRem);
	#endif
}

void ISPM AeAGC(int aiVal)
{	// AGC driver
	#if(0)
// Analog Gain Reg  0x3366[5:0]
// Digital Gain Reg 0x3362[0]
// Sub Digital Gain Reg 0x3308
// 1DDC Reg 0x3F4C, 0x3F4E, 0x3F50

    static int giAgc=0, giGDgc=0, giGDgcBuf=0, giGDgcBuf1=0;
    static BYTE gbDgc=0, gb1DDCidx=0;

    if((aiVal>444)&&(giAgc>=0x107)){
        giGDgcBuf = AE_GAIN_DENORMAL(aiVal);
        if(giGDgcBuf1!=giGDgcBuf){
            if(giGDgcBuf<0x132){//305
                giGDgc = 0x80+(0x3*(giGDgcBuf-0x107));
            }
            else if(giGDgcBuf<0x15F){//351
                giGDgc = (0xfe +(0x06*(giGDgcBuf-0x131))); 
            }
            else if(giGDgcBuf<0x18B){//395
                giGDgc = 0x20C+(0xC*(giGDgcBuf-0x15E));           
            }
            else{
                giGDgc = 0x410+(0x18*(giGDgcBuf-0x18A));           
            }
        }
        giGDgcBuf1=giGDgcBuf;
    }
    else{
        giGDgc = 0x80;
    giAgc = AE_GAIN_DENORMAL(aiVal);		// 171211 LH
    }
    giAgc = MINMAX(giAgc, 0, 0x107);
    giGDgc = MINMAX(giGDgc, 0x80, 0x7E0); 

    gb1DDCidx = (giAgc<85) ? 0 : (giAgc<121) ? 1 : (giAgc<157) ? 2 : (giAgc<193) ? 3 : (giAgc<228) ? 4 : (giAgc<263) ? 5 : 6;
    gbDgc = (giAgc<85)? 0 : 1;

	if (gnAeState!=0){

	    SetSens(0,0x3022, 0x1);

	    AE_AGCw(giAgc);
        SetSens(0,0x305E, giGDgc);      
        // DCG
        SetSens(0,0x3362, gbDgc);
        // 1DDC
        SetSens(0,0x3F4C, gw1DDC_T[gb1DDCidx][0]);
        SetSens(0,0x3F4E, gw1DDC_T[gb1DDCidx][1]);
        SetSens(0,0x3F50, gw1DDC_T[gb1DDCidx][2]);

        SetSens(0,0x3022, 0x0);
	}

    DebugDisp(gbAeDebugOn, Hex, "AGC_____", 5, 24, (giAgc|(gbDgc<<16))) 
    DebugDisp(gbAeDebugOn, Hex, "DGC_____", 6, 24, giGDgc )
	#endif
}



// -------------------------------------------------------------------------------------
// lINE WDR

//WORD ISPM AeSHT_LWDR(int aiMode, int aiVal, int aiVal1)
//{	// Shutter driver for Line WDR
//	// aiMode : 0 : off, 1: 2 page, 2: 3 page
//	// aiVal  : Long
//	// aiVal1 : short1
//	// aiVal2 : short2
//
////	UINT	nRem = 0;
////	UINT	nShtMax = nMok-1;
//	static 	UINT	gnShtFlt = 0;
//	UINT	nShtInt = 0;
//
////	int iWdrGainS1 = 0x1000,  iWdrGainS2;
////	int iWdrGain   = 0x7fff;
////	int tgt_L = aiVal;
////	int tgt_S1 = aiVal1;
////	int tgt_S2 = aiVal2;
//	int tgt_L ;
//	int tgt_S1;
//	int tgt_S2;
//
////	#define AE_SHTMAX	(nMok-2)
////
//
//	LibAeShtIntp (aiVal, AE_SHT_TBL_EA, AE_HSS_FLT_EA, &gnShtFlt, &nShtInt);
//	tgt_L = (int)nShtInt;
//
//	if (aiMode==2) {				// 3 page
//	LibAeShtIntp (aiVal2, AE_SHT_TBL_EA, AE_HSS_FLT_EA, &gnShtFlt, &nShtInt);
//	tgt_S2 = (int)nShtInt;
////	tgt_S1 = MIN(((tgt_L+tgt_S2)/2), 1137);
//	tgt_S1 = MIN(((MAX((tgt_L-tgt_S2),0)*1/3)+tgt_S2), 1137);
//	//	tgt_S2 = 100;	// LH TMP
//	}
//	else if (aiMode==1) {			// 2 page
//	LibAeShtIntp (aiVal1, AE_SHT_TBL_EA, AE_HSS_FLT_EA, &gnShtFlt, &nShtInt);
//	tgt_S1 = (int)nShtInt;
//	tgt_S2 = 0;
//	}
//	else {
//	tgt_S1 = 0;
//	tgt_S2 = 0;
//	}
//
//
//
//////	gnShtFlt = (UINT)((float)gnShtFlt*AE_GAIN_DENORMAL);
////  gnShtFlt = AE_GAIN_DENORMAL(gnShtFlt);		// 171211 LH
////	gnShtFlt = MINMAX(gnShtFlt, 0, (UINT)(AE_GAIN_UNIT_EA*AE_GAIN_UNIT_MAX));
////
////	nMok = gnInModeVtw	 ;
////
////    nShtMax = AE_SHTMAX;
////	nRem = MIN(nShtInt, nShtMax);
//
//	gnSht_L		= tgt_L;	// Long   Exposure Shutter line
//	gnSht_S1	= tgt_S1;   // Short1 Exposure Shutter line
//
////	AE_SHTw((nShtMax-nRem));		// 14.2.13
//	if (aiMode==2) {				// 3 page
//
//////
//////		tgt_L  = 1000 + (MP(MpL)*100);
//////		tgt_S1 = 10 + (MP(MpS1)*40);
//////		tgt_S2 = 1+(MP(MpS2));
////
////		iWdrGainS1 = (tgt_L*256)/tgt_S1;			// WDR S1 gain = (Long * 256)/Short
////		iWdrGainS2 = (tgt_L*16)/tgt_S2;			// WDR S2 gain = (Short2 * 256)/Short1
//////		iWdrGain   = ((0x3fffff*256)/((0x3ff*tgt_L)/10));		// WDR last gain
////		iWdrGain   = ((0x3fffff*256)/((0x3ff*tgt_L)/tgt_S2));		// WDR last gain
//////		iWdrGain	= (iWdrGain * MP(MpBr)*2) / 10;
//
//	if (PAR0F==0x3530) {
//		DebugDisp(gbAeDebugOn, Dec, "SHT0___d", 0, 24, tgt_L  	)
//		DebugDisp(gbAeDebugOn, Dec, "SHT1___d", 1, 24, tgt_S1 	)
//		DebugDisp(gbAeDebugOn, Dec, "SHT2___d", 2, 24, tgt_S2   )
//	} else {
//		DebugDisp(gbAeDebugOn, Dec, "SHT0___d", 0, 24, aiVal  	)
//		DebugDisp(gbAeDebugOn, Dec, "SHT1___d", 1, 24, aiVal1 	)
//		DebugDisp(gbAeDebugOn, Dec, "SHT2___d", 2, 24, aiVal2   )
//	}
//
//	tgt_L  = 4500 - 1 - tgt_L;
//	tgt_S1 = 1006 - tgt_S1 - 1;
//	tgt_S2 = 1148 - 1 - tgt_S2;
//
//
//#if(0)
//		SetSens(SENS_SONY_ID2, 0x28, ((tgt_L&0xff)    ));			// SHS3
//		SetSens(SENS_SONY_ID2, 0x29, ((tgt_L>>8)&0xff ));			// "
//		SetSens(SENS_SONY_ID2, 0x2a, ((tgt_L>>16)&0xff));         	// "
//
//		SetSens(SENS_SONY_ID2, 0x24, ((tgt_S2&0xff)    ));			// SHS2
//		SetSens(SENS_SONY_ID2, 0x25, ((tgt_S2>>8)&0xff ));			// "
//		SetSens(SENS_SONY_ID2, 0x26, ((tgt_S2>>16)&0xff));         	// "
//
//		SetSens(SENS_SONY_ID2, 0x20, ((tgt_S1&0xff)    ));         // SHS1
//		SetSens(SENS_SONY_ID2, 0x21, ((tgt_S1>>8)&0xff ));         // "
//		SetSens(SENS_SONY_ID2, 0x22, ((tgt_S1>>16)&0xff));         // "
//#endif
//
//		SetSens(0, 0x3028, ((tgt_L&0xff)    ));			// SHS3
//		SetSens(0, 0x3029, ((tgt_L>>8)&0xff ));			// "
//		SetSens(0, 0x302a, ((tgt_L>>16)&0xff));         	// "
//
//		SetSens(0, 0x3024, ((tgt_S2&0xff)    ));			// SHS2
//		SetSens(0, 0x3025, ((tgt_S2>>8)&0xff ));			// "
//		SetSens(0, 0x3026, ((tgt_S2>>16)&0xff));         	// "
//
//		SetSens(0, 0x3020, ((tgt_S1&0xff)    ));         // SHS1
//		SetSens(0, 0x3021, ((tgt_S1>>8)&0xff ));         // "
//		SetSens(0, 0x3022, ((tgt_S1>>16)&0xff));         // "
//
//	}
//	else if (aiMode==1) {							// 2 page
//////		tgt_L  = 1000 + (MP(MpL)*40);
//////		tgt_S1 = MIN(MP(MpS1), 8);
////
////		iWdrGainS1 = (tgt_L*256)/tgt_S1;			// WDR S1 gain = (Long * 256)/Short
////		iWdrGainS2 = 0;								// WDR S2 gain = dummy
//////		iWdrGain   = ((0x3fffff*256)/((0x3ff*tgt_L)/10));		// WDR last gain
////		iWdrGain   = ((0x3fffff*256)/((0x3ff*tgt_L)/tgt_S1));		// WDR last gain
//
//
//		if (PAR0F==0x3530) {
//			DebugDisp(gbAeDebugOn, Dec, "SHT0___d", 0, 24, tgt_L  	)
//			DebugDisp(gbAeDebugOn, Dec, "SHT1___d", 1, 24, tgt_S1 	)
//		} else {
//			DebugDisp(gbAeDebugOn, Dec, "SHT0___d", 0, 24, aiVal  	)
//			DebugDisp(gbAeDebugOn, Dec, "SHT1___d", 1, 24, aiVal1 	)
//		}
//
//		tgt_L  = 2250 - 1 - tgt_L;	// ORG
////		tgt_S1 = 11 - 1 - tgt_S1;	// ORG
//		tgt_S1 = 37 - 1 - tgt_S1;
//
//#if(0)
//		SetSens(SENS_SONY_ID2, 0x28, ((tgt_L&0xff)    ));			// SHS2
//		SetSens(SENS_SONY_ID2, 0x29, ((tgt_L>>8)&0xff ));			// "
//		SetSens(SENS_SONY_ID2, 0x2a, ((tgt_L>>16)&0xff));         	// "
//
//		SetSens(SENS_SONY_ID2, 0x20, ((tgt_S1&0xff)    ));         // SHS1
//		SetSens(SENS_SONY_ID2, 0x21, ((tgt_S1>>8)&0xff ));         // "
//		SetSens(SENS_SONY_ID2, 0x22, ((tgt_S1>>16)&0xff));         // "
//#endif
//		SetSens(0, 0x3024, ((tgt_L&0xff)    ));			// SHS2
//		SetSens(0, 0x3025, ((tgt_L>>8)&0xff ));			// "
//		SetSens(0, 0x3026, ((tgt_L>>16)&0xff));         // "
//
//		SetSens(0, 0x3020, ((tgt_S1&0xff)    ));         // SHS1
//		SetSens(0, 0x3021, ((tgt_S1>>8)&0xff ));         // "
//		SetSens(0, 0x3022, ((tgt_S1>>16)&0xff));         // "
//	}
//
//	else {	// DOL OFF
//
//
//	}
////
////	WDR_LGAINw(0x1000);				// WDR_LGAIN  : 12b float offset
////	WDR_SGAINw(iWdrGainS1);         // WDR_SGAIN  :  8b "
////	WDR_SGAIN2w(iWdrGainS2);					// WDR_SGAIN2 :  4b "
////	WDR_GAINw(iWdrGain>>4);            // WDR_GAIN	  :  8b "	TMP
////	WDR_STEPw(4);						// TMP
////
////	WDR_SATVLw(0x3c6);
////	WDR_SATVWw(0x1);
////
//
////	return ((WORD)nRem);
//	return (0);		// LH TMP
//
//}

//void ISPM AeAGC_LWDR(int aiMode, int aiVal, int aiVal1, int aiVal2)
//{	// AGC driver for Line WDR
//	// aiMode : 0: off, 1: 2 page, 2: 3 page
//	// aiVal : Long
//	// aiVal1 : short1
//	// aiVal2 : short2
//
//// SPI
////	if (aiMode==2) {
////		SetSens(SENS_SONY_ID2, 0x14, (aiVal>>0)&0xff);		// L gain
////		SetSens(SENS_SONY_ID2, 0xf2, (aiVal1>>0)&0xff);		// S1 gain
////		SetSens(SENS_SONY_ID2, 0xf6, (aiVal2>>0)&0xff);		// S2 gain
////	}
////	else if (aiMode==1) {
////		SetSens(SENS_SONY_ID2, 0x14, (aiVal>>0)&0xff);		// L gain
////		SetSens(SENS_SONY_ID2, 0xf2, (aiVal1>>0)&0xff);		// S1 gain
////		SetSens(SENS_SONY_ID2, 0xf6, 0);					// S2 gain
////	}
//
//	static int	giAgcL, giAgcS1, giAgcS2;
////	static int  iChk;	// HCG on DOL ??
//
////	giAgcL  = (int)((float)aiVal*AE_GAIN_DENORMAL);
//	giAgcL = AE_GAIN_DENORMAL(aiVal);		// 171211 LH
//	giAgcL  = MINMAX(giAgcL, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA));
////	giAgcS1 = (int)((float)aiVal1*AE_GAIN_DENORMAL);
//	giAgcS1 = AE_GAIN_DENORMAL(aiVal1);		// 171211 LH
//	giAgcS1 = MINMAX(giAgcS1, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA));
////	giAgcS2 = (int)((float)aiVal2*AE_GAIN_DENORMAL);
//	giAgcS2 = AE_GAIN_DENORMAL(aiVal2);		// 171211 LH
//	giAgcS2 = MINMAX(giAgcS2, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA));
//
//	if (gnAeState!=0)	{
//		if (aiMode==2) {	// 3P
//			SetSens(0, 0x3014, (giAgcL >>0)&0xff);		// L gain
//			SetSens(0, 0x30f2, (giAgcS1>>0)&0xff);		// S1 gain
//			SetSens(0, 0x30f6, (giAgcS2>>0)&0xff);		// S2 gain
//		}
//		else if (aiMode==1) {	// 2P
//			SetSens(0, 0x3014, (giAgcL >>0)&0xff);		// L gain
//			SetSens(0, 0x30f2, (giAgcS1>>0)&0xff);		// S1 gain
//			SetSens(0, 0x30f6, 0);						// S2 gain
//		}
//		else {		// DOL OFF
//
//		}
//	}
//
//
////	DebugDisp(gbAeDebugOn, Dec, "AGC_L___", 5, 24, aiVal )
////	DebugDisp(gbAeDebugOn, Dec, "AGC_S1__", 6, 24, aiVal1 )
////	DebugDisp(gbAeDebugOn, Dec, "AGC_S2__", 7, 24, aiVal2 )
//	DebugDisp(gbAeDebugOn, Dec, "AGC0____", 5, 24, giAgcL  )
//	DebugDisp(gbAeDebugOn, Dec, "AGC1____", 6, 24, giAgcS1 )
//	DebugDisp(gbAeDebugOn, Dec, "AGC2____", 7, 24, giAgcS2 )
//
//}


// -----------------------------------------------------------------------------------------
// AWB
// -----------------------------------------------------------------------------------------

const s64 glMtxCf[9][6] =		{	// RT, Y 350
                                {         89943388351893LL,         -28880685132LL,        -200083792874LL,             -8570251LL,             32663400LL,             67461931LL},
                                {         43889672647229LL,          27068876199LL,         105797736796LL,            -31738401LL,           -105311182LL,              7823647LL},
                                {         96229952577565LL,         630944916181LL,         352277185980LL,           1352117950LL,           1180512637LL,            641965089LL},
                                {        -77065079092428LL,          -2221682150LL,         -18386074162LL,            166518888LL,            131589922LL,             36198659LL},
                                {        244115606285650LL,         269006495184LL,         317091268719LL,            402874401LL,             85547488LL,            264723072LL},
                                {         59213465171707LL,         604053950879LL,         397034868449LL,           1413378711LL,           1117225151LL,            886585528LL},
                                {         -1879386908066LL,          89838956433LL,          72052087219LL,            604069516LL,            298825595LL,            338951200LL},
                                {         30273606576429LL,        -220984328324LL,        -235948767189LL,          -1667283792LL,           -805184628LL,          -1175333675LL},
                                {        362490861744131LL,        2320894281559LL,        2245516572636LL,          10107977079LL,           5312594127LL,           7278981367LL}
								};
