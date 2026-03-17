/* **************************************************************************
 File Name	  :	EN772_SENS_SC500AI.c
 Description  :	EN772_801 - SC500AI device driver
 Designer	  :	Han Tian Yong
 Date		  :	21. 03. 02
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */
#undef model_Sens
#include "../Src/dev.h"
#define model_Sens	SENS_SC500AI
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

#define AE_SHTMAX_OFST	10
#define AE_SHTMIN_OFST	3
#define AE_SHTMAX		(nMok-AE_SHTMAX_OFST)

#define AE_GAIN_UNIT_MAX		(606)															// Analog 27.63dB, Digtal 30.03dB  
#define AE_GAIN_UNIT_EA			(1)																// Sensor gain Unit EA
#define AE_GAIN_UNIT_OVR		(0)																// Sensor gain extended step
#define AE_GAIN_UNIT_OVR2		(0)	    
const int Sens(AE_GAIN_TOTAL) = (((AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR)*(0.1/0.1));
const int Sens(AE_GAIN_TOTAL2) = 0;

#define AE_GAIN_DENORMAL(val)	(ifdiv8(val*(int)(1.0f*256.f)))

#define AE_HSS_FLT_EA		(sizeof(gbAeHssFltTbl))
#define AE_SHT_TBL_EA		(sizeof(gnAeShtTbl)/8)

BYTE gbWdrOnFlgS;

// -----------------------------------------------------------------------------------------
// initial
	// Sensor Master
	// MIPI 4 Lane
	// INCK : 27MHz

	const WORD gwTblSens0[][2] = {	//ADDR	 Nor 4M30P	 Dol 4M30P	
									{0x0103,0x01},
									{0x0100,0x00},
									{0x36e9,0x80},
									{0x36f9,0x80},
									{0x301f,0x48},
									{0x3200,0x00},
									{0x3201,0x98},
									{0x3202,0x00},
									{0x3203,0x52},
									{0x3204,0x0a},
									{0x3205,0xaf},
									{0x3206,0x06},
									{0x3207,0x09},
									{0x3208,0x0a},
									{0x3209,0x10},
									{0x320a,0x05},
									{0x320b,0xb0},
									{0x320c,0x06},
									{0x320d,0x72},
									{0x320e,0x05},
									{0x320f,0xdc},
									{0x3210,0x00},
									{0x3211,0x04},
									{0x3212,0x00},
									{0x3213,0x04},
									{0x3253,0x0a},
									{0x3301,0x0a},
									{0x3302,0x18},
									{0x3303,0x10},
									{0x3304,0x60},
									{0x3306,0x60},
									{0x3308,0x10},
									{0x3309,0x70},
									{0x330a,0x00},
									{0x330b,0xf0},
									{0x330d,0x18},
									{0x330e,0x20},
									{0x330f,0x02},
									{0x3310,0x02},
									{0x331c,0x04},
									{0x331e,0x51},
									{0x331f,0x61},
									{0x3320,0x09},
									{0x3333,0x10},
									{0x334c,0x08},
									{0x3356,0x09},
									{0x3364,0x17},
									{0x336d,0x03},
									{0x3390,0x08},
									{0x3391,0x18},
									{0x3392,0x38},
									{0x3393,0x0a},
									{0x3394,0x20},
									{0x3395,0x20},
									{0x3396,0x08},
									{0x3397,0x18},
									{0x3398,0x38},
									{0x3399,0x0a},
									{0x339a,0x20},
									{0x339b,0x20},
									{0x339c,0x20},
									{0x33ac,0x10},
									{0x33ae,0x10},
									{0x33af,0x19},
									{0x360f,0x01},
									{0x3622,0x03},
									{0x363a,0x1f},
									{0x363c,0x40},
									{0x3651,0x7d},
									{0x3670,0x0a},
									{0x3671,0x07},
									{0x3672,0x17},
									{0x3673,0x1e},
									{0x3674,0x82},
									{0x3675,0x64},
									{0x3676,0x66},
									{0x367a,0x48},
									{0x367b,0x78},
									{0x367c,0x58},
									{0x367d,0x78},
									{0x3690,0x34},
									{0x3691,0x34},
									{0x3692,0x54},
									{0x369c,0x48},
									{0x369d,0x78},
									{0x36ea,0x35},
									{0x36eb,0x0c},
									{0x36ec,0x1a},
									{0x36ed,0x24},
									{0x36fa,0x35},
									{0x36fb,0x35},
									{0x36fc,0x10},
									{0x36fd,0x24},
									{0x3904,0x04},
									{0x3908,0x41},
									{0x391d,0x04},
									{0x39c2,0x30},
									{0x3e01,0xbb},
									{0x3e02,0x00},
									{0x3e16,0x00},
									{0x3e17,0x80},
									{0x4500,0x88},
									{0x4509,0x20},
									{0x4837,0x2b},
									{0x5799,0x00},
									{0x59e0,0x60},
									{0x59e1,0x08},
									{0x59e2,0x3f},
									{0x59e3,0x18},
									{0x59e4,0x18},
									{0x59e5,0x3f},
									{0x59e7,0x02},
									{0x59e8,0x38},
									{0x59e9,0x20},
									{0x59ea,0x0c},
									{0x59ec,0x08},
									{0x59ed,0x02},
									{0x59ee,0xa0},
									{0x59ef,0x08},
									{0x59f4,0x18},
									{0x59f5,0x10},
									{0x59f6,0x0c},
									{0x59f9,0x02},
									{0x59fa,0x18},
									{0x59fb,0x10},
									{0x59fc,0x0c},
									{0x59ff,0x02},
									{0x36e9,0x20},
									{0x36f9,0x53},
									{0x3907,0x00}, // Black Offset
								    {0x3908,0x00}, // Black Offset
									{0x0100,0x01}
								};
								
	const WORD gwTblSCWdr[][2] = { 
					        		{0x0103,0x01},
									{0x0100,0x00},
									{0x36e9,0x80},
									{0x36f9,0x80},
									{0x301f,0x4a},
									{0x3106,0x01},
									{0x3200,0x00},
									{0x3201,0x98},
									{0x3202,0x00},
									{0x3203,0x52},
									{0x3204,0x0a},
									{0x3205,0xaf},
									{0x3206,0x06},
									{0x3207,0x09},
									{0x3208,0x0a},
									{0x3209,0x10},
									{0x320a,0x05},
									{0x320b,0xb0},
									{0x320c,0x07},
									{0x320d,0xbc},
									{0x320e,0x0b},
									{0x320f,0xb8},
									{0x3210,0x00},
									{0x3211,0x04},
									{0x3212,0x00},
									{0x3213,0x04},
									{0x3220,0x53},
									{0x3250,0xff},
									{0x3253,0x0a},
									{0x3301,0x0b},
									{0x3302,0x20},
									{0x3303,0x10},
									{0x3304,0x70},
									{0x3306,0x50},
									{0x3308,0x18},
									{0x3309,0x80},
									{0x330a,0x00},
									{0x330b,0xe8},
									{0x330d,0x30},
									{0x330e,0x30},
									{0x330f,0x02},
									{0x3310,0x02},
									{0x331c,0x08},
									{0x331e,0x61},
									{0x331f,0x71},
									{0x3320,0x11},
									{0x3333,0x10},
									{0x334c,0x10},
									{0x3356,0x11},
									{0x3364,0x17},
									{0x336d,0x03},
									{0x3390,0x08},
									{0x3391,0x18},
									{0x3392,0x38},
									{0x3393,0x0a},
									{0x3394,0x0a},
									{0x3395,0x12},
									{0x3396,0x08},
									{0x3397,0x18},
									{0x3398,0x38},
									{0x3399,0x0a},
									{0x339a,0x0a},
									{0x339b,0x0a},
									{0x339c,0x12},
									{0x33ac,0x10},
									{0x33ae,0x20},
									{0x33af,0x21},
									{0x360f,0x01},
									{0x3621,0xe8},
									{0x3622,0x06},
									{0x3630,0x82},
									{0x3633,0x33},
									{0x3634,0x64},
									{0x3637,0x50},
									{0x363a,0x1f},
									{0x363c,0x40},
									{0x3651,0x7d},
									{0x3670,0x0a},
									{0x3671,0x06},
									{0x3672,0x16},
									{0x3673,0x17},
									{0x3674,0x82},
									{0x3675,0x62},
									{0x3676,0x44},
									{0x367a,0x48},
									{0x367b,0x78},
									{0x367c,0x48},
									{0x367d,0x58},
									{0x3690,0x34},
									{0x3691,0x34},
									{0x3692,0x54},
									{0x369c,0x48},
									{0x369d,0x78},
									{0x36ea,0x35},
									{0x36eb,0x04},
									{0x36ec,0x0a},
									{0x36ed,0x24},
									{0x36fa,0x35},
									{0x36fb,0x04},
									{0x36fc,0x00},
									{0x36fd,0x26},
									{0x3904,0x04},
									{0x3908,0x41},
									{0x391f,0x10},
									{0x39c2,0x30},
									{0x3e00,0x01},
									{0x3e01,0x5c},
									{0x3e02,0x00},
									{0x3e04,0x15},
									{0x3e05,0xc0},
									{0x3e23,0x00}, // Max Short Exposure
									{0x3e24,0x1d}, // Max Short Exposure
									{0x4500,0x88},
									{0x4509,0x20},
									{0x4800,0x04},
									{0x4837,0x15},
									{0x4853,0xfd},
									{0x36e9,0x20},
									{0x36f9,0x20},
									{0x3907,0x00}, // Black Offset
									{0x3908,0x00}, // Black Offset
									{0x0100,0x01}
				        		};

//----------------------------------------------------------------------------------------

const UINT gTblSensEa	  = numberof(gwTblSens0);
const UINT gTblSCWdrEa	  = numberof(gwTblSCWdr);

// -----------------------------------------------------------------------------------------
// AE
// -----------------------------------------------------------------------------------------

	const BYTE 	gbAeHssFltTbl[]   = {
					                 0,		// 0
									55,		// 1
									35,		// 2
									28,		// 3
									21,		// 4
									16,		// 5
									11,		// 6
									10,		// 7
									9 ,		// 8
									8 ,		// 9
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
									{0	 ,128      },
									{14  ,150      },
									{28  ,176      },
									{42  ,207      },
									{56  ,243      },
									{70  ,286      },
									{84  ,336      },
									{98  ,395      },
									{112 ,464      },
									{126 ,546      },
									{140 ,641      },
									{154 ,753      },
									{168 ,885      },
									{182 ,1040     },
									{196 ,1222     },
									{210 ,1436     },
									{224 ,1687     },
									{238 ,1982     },
									{252 ,2329     },
									{266 ,2736     },
									{280 ,3215     },
									{294 ,3777     },
									{308 ,4438     },
									{322 ,5214     },
									{336 ,6126     },
									{350 ,7197     },
									{364 ,8456     },
									{378 ,9935     },
									{392 ,11673    },
									{406 ,13715    },
									{420 ,16114    },
									{434 ,18932    },
									{448 ,22243    },
									{462 ,26134    },
									{476 ,30705    },
									{490 ,36075    },
									{504 ,42384    },
									{518 ,49797    },
									{532 ,58507    },
									{546 ,68740    },
									{560 ,80762    },
									{574 ,94887    },
									{588 ,111483   },
									{602 ,130981   },
									{616 ,153889   },
									{630 ,180804   },
									{644 ,212427   },
									{658 ,249580   },
									{672 ,293231   },
									{686 ,344516   },
									{700 ,404771   },
									{714 ,475565   },
									{728 ,558740   },
									{742 ,656462   },
									{756 ,771276   },
									{770 ,906170   },
									{784 ,1064657  },
									{798 ,1250863  },
									{812 ,1469636  },
									{826 ,1726672  },
									{840 ,2028663  },
									{854 ,2383471  },
									{868 ,2800334  },
									{882 ,3290106  },
									{896 ,3865538  },
									{910 ,4541611  },
									{924 ,5335928  },
									{938 ,6269168  },
									{952 ,7365631  },
									{966 ,8653862  },
									{980 ,10167401 },
									{994 ,11945655 },
									{1008,14034920 },
									{1022,16489594 }
									};

// -----------------------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------------------
void LibRdesIsp(int aiResMode, int aiWdrMode)
{	// MIPI RX Configuration
	LibISPtoSENS_Intf(\
					/* MIPI or LVDS */\
					MIPI,\
					/* 1, 2, 4 LANE */\
					(_4LANE),\
					/* 12BIT or 10BIT */\
					(_10BIT),\
					/* 3210, 10, 0 */\
					(_3210),\
					/* Word Count */\
					((aiWdrMode==MN_OFF) ?	((aiResMode==MD_4M_FPS_25_30)?(0xC94):(0xC94)):\
											((aiResMode==MD_4M_FPS_25_30)?(0xC94):(0xC94))),\
					/* MIPI Line information or Virtual channel mode */\
					_MIPI_VC,\
					aiWdrMode);
}

void LibInitSens(int aiMode, int aiOption)
{	// SC500AI, Sensor Master mode

	UINT i;
	static BYTE bInitSet = 0x1;

	if(bInitSet){
		// Sensor H/W Reset
		GpioSetLo(GPIO_SRSTN);	WaitUs(10000);	GpioSetHi(GPIO_SRSTN);	WaitUs(10000);

		for(i=0; i<10; i++) {
			if(i2c_write(SENS_SMARTS_DEV,1,0) == 0) {
				gbSensorOff = 0;
				TxStrNoIRQ("SI2C connected.", 0, 0);
				break;
			}
			WaitUs(1000);
		}
		if(gbSensorOff) TxStrNoIRQ("SI2C not connected.", 0, 0);

		bInitSet = 0x0;
	}
	
	LibRdesIsp(aiMode, aiOption);

	if(!aiOption)	{ for (i=0; i<gTblSensEa; i++)	{ SetSens(gwTblSens0[i][0], (BYTE)gwTblSens0[i][1]);} gbWdrOnFlgS=0; }
	else			{ for (i=0; i<gTblSCWdrEa; i++)	{ SetSens(gwTblSCWdr[i][0], (BYTE)gwTblSCWdr[i][1]);} gbWdrOnFlgS=1; }

	//Shutter Speed Max
	gnAeNorMax = gnInModeVtw-AE_SHTMAX_OFST;
	
	if (aiOption==1) {			// DOL 2P		
         // short_exp<vb,long_exp+short_ep<frame length
		gnAeLWdrMaxL0	= 1500*2-2*29-18;// 2*Frame_Length-2*ShortMax-18 
		gnAeLWdrMaxS1	= 29*2-14;       // 2*ShortMax-14

		gnAeLWdrMinL0	= 5;//
		gnAeLWdrMinS1	= 5;//
	}
}

void ISPM Sens(AE_SHTLw)(UINT val)
{
	SetSens(0x3e00, (val>>12)&0xff); // MSB [15:12]
	SetSens(0x3e01, (val>>4)&0xff);  // MSB [11: 4]
	SetSens(0x3e02, (val<<4)&0xf0);  // LSB [3 : 0]
}

void ISPM Sens(AE_SHTSw)(UINT val)
{
	SetSens(0x3e22, (val>>12)&0xff); // MSB [15:12]
	SetSens(0x3e04, (val>>4)&0xff);  // MSB [11: 4]
	SetSens(0x3e05, (val<<4)&0xf0);  // LSB [3 : 0]
}

void ISPM Sens(AE_AGCw)(UINT val)
{
	int iValAgc=0, iValDgc=0;
	UINT val1=val;
	
	if(val<0x21)		{ SetSens(0x3e08, 0x03); iValAgc=val;       }// AGC 
	else if(val<0x061)	{ SetSens(0x3e08, 0x23); iValAgc=val-0x021; } //  
	else if(val<0x0A1)	{ SetSens(0x3e08, 0x27); iValAgc=val-0x061; } //  
	else if(val<0x0E1)	{ SetSens(0x3e08, 0x2F); iValAgc=val-0x0A1; } //  
	else if(val<0x121)	{ SetSens(0x3e08, 0x3F); iValAgc=val-0x0E1; } //  

	SetSens(0x3e09, (val<0x121) ? ((iValAgc+0x40)&0xff) : 0x7f); // AGC Fine
	
	val=(val<0x121) ? 0 : 2*(val-0x121);
		
	if(val<0x7F)		{ SetSens(0x3e06, 0x00); iValDgc=val;       } // DGC 	
	else if(val<0xFE)	{ SetSens(0x3e06, 0x01); iValDgc=val-0x7F;  } //  	
	else if(val<0x17D)	{ SetSens(0x3e06, 0x03); iValDgc=val-0xFE;  } //  	
	else if(val<0x1FC)	{ SetSens(0x3e06, 0x07); iValDgc=val-0x17D; } //  	
	else if(val<0x27B)	{ SetSens(0x3e06, 0x0F); iValDgc=val-0x1FC; } //  	
	
	SetSens(0x3e07, (iValDgc+0x80)&0xff); // DGC Fine

	//Short Gain
	if(gbModeWdrOn_L){
		
	int iValAgc=0, iValDgc=0;
	
	if(val1<0x21)		{ SetSens(0x3e12, 0x03); iValAgc=val1; }// AGC 
	else if(val1<0x061)	{ SetSens(0x3e12, 0x23); iValAgc=val1-0x021; } // AGC 
	else if(val1<0x0A1)	{ SetSens(0x3e12, 0x27); iValAgc=val1-0x061; } // AGC 
	else if(val1<0x0E1)	{ SetSens(0x3e12, 0x2F); iValAgc=val1-0x0A1; } // AGC 
	else if(val1<0x121)	{ SetSens(0x3e12, 0x3F); iValAgc=val1-0x0E1; } // AGC 

	SetSens(0x3e13, (val1<0x121) ? ((iValAgc+0x40)&0xff) : 0x7f); // AGC Fine
	
	val1=(val1<0x121) ? 0 : 2*(val1-0x121);
	
	if(val1<0x7F)		{ SetSens(0x3e10, 0x00); iValDgc=val1;       } // DGC 	
	else if(val1<0xFE)	{ SetSens(0x3e10, 0x01); iValDgc=val1-0x7F;  } // DGC 	
	else if(val1<0x17D)	{ SetSens(0x3e10, 0x03); iValDgc=val1-0xFE;  } // DGC 	
	else if(val1<0x1FC)	{ SetSens(0x3e10, 0x07); iValDgc=val1-0x17D; } // DGC 	
	else if(val1<0x27B)	{ SetSens(0x3e10, 0x0F); iValDgc=val1-0x1FC; } // DGC 	
	
	SetSens(0x3e11, (iValDgc+0x80)&0xff); // DGC Fine
	
	}
}

void ISPM Sens(AE_FREQw)(UINT val, UINT val1)
{
	UNUSED_ARG(val);
	SetSens(0x320c, (val1>>8)&0xff);
	SetSens(0x320d, (val1>>0)&0xff);
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
    // shuter half line per 1step
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
//		gnShtFlt = AE_GAIN_DENORMAL(gnShtFlt);
		gnShtFlt = MIN(gnShtFlt,(UINT)(AE_GAIN_TOTAL));
		gnShtFlt = MAX(gnShtFlt,0);
 		AE_AGCw(gnShtFlt);				//Shutter Control State, AGC
	}
#endif

	if(anManual){
	  nMok 	= (UINT)(MAX(((int)anManualVal - AE_SHTMAX_OFST), (int)0))/gnInModeVtw;
	  nMok 	= ((nMok*gnInModeVtw)+gnInModeVtw);

	  nShtMax = AE_SHTMAX;
	  nRem = MINMAX(anManualVal, AE_SHTMIN_OFST, nShtMax);
	}
	//Shutter Control State
	else {
	  nMok 	= gnInModeVtw;
	  nShtMax = AE_SHTMAX;
	  nRem 	= MINMAX(nShtInt, AE_SHTMIN_OFST, nShtMax);
	}

	AE_SHTLw(nRem);

	DebugDisp(gbAeDebugOn, Dec, "SHT_int__d", 1, 24, nRem		)
	DebugDisp(gbAeDebugOn, Dec, "SHT_flt__d", 2, 24, gnShtFlt	)

	return ((WORD)(nRem));
}

void ISPM AeAGC(int aiVal)
{	// AGC driver
	static int	giAgc;
	const UINT nAGC_LMT = AE_GAIN_DENORMAL(AE_SENS_AGC_LMT_NOR);
	static UINT nLWdrGain;
	
	giAgc = AE_GAIN_DENORMAL(aiVal);
	giAgc = MINMAX(giAgc, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR);

	if(giAgc < (int)nAGC_LMT)   	giAeLWdrGain = 0x0; 
	else{
		LibAeGainIntp((aiVal-AE_SENS_AGC_LMT_NOR), &nLWdrGain);				//Calculation 0.1dB		
		giAeLWdrGain = (int)nLWdrGain;
		giAgc = (nAGC_LMT - AE_GAIN_UNIT_OVR);							//AGC MAX
	}
	
	if (gnAeState!=0)	AE_AGCw(aiVal);
	
	DebugDisp(gbAeDebugOn, Hex, "AGC_____", 5, 24, (giAgc<0x121) ? giAgc : 0x121);
//	DebugDisp(gbAeDebugOn, Hex, "DGC_____", 6, 24, (aiVal>0x121) ? aiVal-0x121:0);
	DebugDisp(gbAeDebugOn, Hex, "WDR_GAIN", 6, 24, (giAeLWdrGain))
}

// -------------------------------------------------------------------------------------
// LINE WDR

WORD ISPM AeSHT_LWDR(int aiMode, int aiVal, int aiVal1)
{	// Shutter driver for Line WDR
	// aiMode : 0 : off, 1: 2 page, 2: 3 page
	// aiVal  : Long
	// aiVal1 : short1
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
	gnAgc_L = LibAePrgainIntp(gnShtFlt_L);

	//Short
	LibAeShtIntp (aiVal1, AE_SHT_TBL_EA, AE_HSS_FLT_EA, &gnShtFlt_S, &nShtInt);
	tgt_S1 = (int)nShtInt;
	gnAgc_S1 = LibAePrgainIntp(gnShtFlt_S);
	
	gnSht_L		= tgt_L;	// Long   Exposure Shutter line
	gnSht_S1	= tgt_S1;   // Short1 Exposure Shutter line

	AE_SHTLw(tgt_L );
	AE_SHTSw(tgt_S1);

//	if(gnAeState==0)
//	{
//		AE_SHTLw(tgt_L );
//		AE_AGCw(gnShtFlt_L);
//
//		AE_SHTSw(tgt_S1);
//		AE_AGC_S(gnShtFlt_S);
//	}

	DebugDisp(gbAeDebugOn, Dec, "SHT0___d", 0, 24, gnSht_L 	)
	DebugDisp(gbAeDebugOn, Dec, "SHT1___d", 1, 24, gnSht_S1	)
	DebugDisp(gbAeDebugOn, Dec, "SHT_fltL_d", 2, 24, gnShtFlt_L	)
	
	return (0);		// LH TMP
}

void ISPM AeAGC_LWDR(int aiMode, int aiVal, int aiVal1)
{
	// aiVal : Long
	// aiVal1 : short1
	UNUSED_ARG(aiMode);
	UNUSED_ARG(aiVal1);
	
	static int	giAgcL;
	static UINT nLWdrGain;
	
	const UINT nLWDR_AGC_LMT = AE_GAIN_DENORMAL(AE_SENS_AGC_LMT_WDR);

	giAgcL = AE_GAIN_DENORMAL(aiVal);
	giAgcL = MINMAX(giAgcL, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR);
	
	if(giAgcL <= (int)nLWDR_AGC_LMT)   giAeLWdrGain = 0x0; 
	else{
		LibAeGainIntp((aiVal-AE_SENS_AGC_LMT_WDR), &nLWdrGain);						//Calculation 0.1dB
		giAeLWdrGain = (int)nLWdrGain;									
		giAgcL = (nLWDR_AGC_LMT - AE_GAIN_UNIT_OVR);							//AGC MAX
	}
	
	if (gnAeState!=0)	{
		LibAePrgain_L(0x100);
		LibAePrgain_S(0x100);
		
		AE_AGCw(giAgcL);
	}

	DebugDisp(gbAeDebugOn, Hex, "AGC_____", 5, 24, (giAgcL<0x121) ? giAgcL : 0x121);
//	DebugDisp(gbAeDebugOn, Hex, "DGC_____", 6, 24, (aiVal>0x121) ? aiVal-0x121:0);
	DebugDisp(gbAeDebugOn, Hex, "WDR_GAIN", 6, 24, (giAeLWdrGain))
}

// -----------------------------------------------------------------------------------------
// AWB
// -----------------------------------------------------------------------------------------
	//Designer 	: Jang, Jae Hoon
	//Date		: 18.04.05
	const s64 glMtxCf[9][6] =		{	// RT, Y 350
									{         37221652864054LL,        -143326653960LL,        -267730597607LL,           -316731530LL,           -141334521LL,            -74750098LL},
									{         35956976390509LL,         -19370254621LL,          39430316390LL,           -154663234LL,           -147976672LL,            -72535565LL},
									{         70204785253655LL,         337038710903LL,         204126828624LL,            645663437LL,            674882478LL,            347540728LL},
									{        -55536655688919LL,          35632443214LL,           7098510324LL,            206491738LL,            137863879LL,             92434327LL},
									{        192642622198312LL,         176905500592LL,         188845020901LL,            111934274LL,             13179457LL,             71708341LL},
									{        -40145894584436LL,        -163533056523LL,        -192405262239LL,           -763763281LL,           -162763771LL,           -301446768LL},
									{          4083609402405LL,         145442629649LL,         107487696771LL,            515337872LL,            296925559LL,            259571557LL},
									{        -10139669691116LL,        -363866453153LL,        -343404379160LL,          -1258376316LL,           -742248130LL,           -727109167LL},
									{        376456111388883LL,        1716361381869LL,        1849139140507LL,           4922080469LL,           3002233847LL,           3314551719LL}
									};


// -----------------------------------------------------------------------------------------
// MIRROR & FLIP
// -----------------------------------------------------------------------------------------

BYTE gbMirrFlgS=0;
void Sens(SENS_MIRw)(BYTE abOn){
	SetSens(0x3221,((GetSens(0x3221)&(~ValSft_L01(BitMask_02)))|ValSft_L01(abOn*3)));
	gbMirrFlgS=abOn*3;
}

void Sens(SENS_FLPw)(BYTE abOn){
	SetSens(0x3221,((ValSft_L01(gbMirrFlgS)&(~ValSft_L05(BitMask_02)))|ValSft_L05(abOn*3)));
	
	static BYTE bBuf=0xf,bBuf1=0xf;
	static UINT nVLOCKL_POS=0,nVLOCKS_POS=0;
	
	if((bBuf!=abOn)||(gbWdrOnFlgS!=bBuf1)) {
		if(gbWdrOnFlgS!=bBuf1) {nVLOCKL_POS=VLOCKL_POSr; nVLOCKS_POS=VLOCKS_POSr;}
		VLOCKL_POSw(nVLOCKL_POS+abOn*gbWdrOnFlgS);
		VLOCKS_POSw(nVLOCKS_POS+abOn*gbWdrOnFlgS);
		bBuf1=gbWdrOnFlgS; bBuf=abOn;
	}
}


