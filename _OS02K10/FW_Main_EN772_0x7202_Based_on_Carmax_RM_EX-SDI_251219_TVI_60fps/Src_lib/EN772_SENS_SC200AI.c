/* **************************************************************************
 File Name	  :	EN772_SENS_SC200AI.c
 Description  :	EN772 - SC200AI device driver
 Designer	  :	Han Tian Yong
 Date		  :	21. 03. 02
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */
#undef model_Sens
#include "../Src/dev.h"
#define model_Sens	SENS_SC200AI
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

#define AE_SHTMAX_OFST	8
#define AE_SHTMIN_OFST	1
#define AE_SHTMAX		(nMok-AE_SHTMAX_OFST)

#define AE_GAIN_UNIT_MAX		(682)															// Analog 34.64dB, Digtal 30.03dB  
#define AE_GAIN_UNIT_EA			(1)																// Sensor gain step by Unit
#define AE_GAIN_UNIT_OVR		(0)																// Sensor gain extended step
#define AE_GAIN_UNIT_OVR2		(0)	    
const int Sens(AE_GAIN_TOTAL) = (((AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR)*(0.1/0.1));
const int Sens(AE_GAIN_TOTAL2) = 0;

#define AE_GAIN_DENORMAL(val)	(ifdiv8(val*(int)(1.0f*256.f)))

#define AE_HSS_FLT_EA		(sizeof(gbAeHssFltTbl))
#define AE_SHT_TBL_EA		(sizeof(gnAeShtTbl)/8)

BYTE gbSC200AIWdrOnFlg;

// -----------------------------------------------------------------------------------------
// initial

	// Sensor Master
	// MIPI 4 Lane
	// INCK : 27MHz

	const WORD gwTblSens0[][2] = {	// 1080p30
									{0x0103,0x01},
									{0x0100,0x00},
									{0x36e9,0x80},
									{0x36f9,0x80},
									{0x301f,0x3f},
									{0x3200,0x00},
									{0x3201,0x00},
									{0x3202,0x00},
									{0x3203,0x00},
									{0x3204,0x07},
									{0x3205,0x8b},
									{0x3206,0x04},
									{0x3207,0x43},
									{0x3208,0x07},
									{0x3209,0x88},
									{0x320a,0x04},
									{0x320b,0x40},
									{0x3210,0x00},
									{0x3211,0x02},
									{0x3212,0x00},
									{0x3213,0x02},
									{0x3243,0x01},
									{0x3248,0x02},
									{0x3249,0x09},
									{0x3253,0x08},
									{0x3271,0x0a},
									{0x3301,0x20},
									{0x3304,0x40},
									{0x3306,0x32},
									{0x330b,0x88},
									{0x330f,0x02},
									{0x331e,0x39},
									{0x3333,0x10},
									{0x3621,0xe8},
									{0x3622,0x16},
									{0x3637,0x1b},
									{0x363a,0x1f},
									{0x363b,0xc6},
									{0x363c,0x0e},
									{0x3670,0x0a},
									{0x3674,0x82},
									{0x3675,0x76},
									{0x3676,0x78},
									{0x367c,0x48},
									{0x367d,0x58},
									{0x3690,0x34},
									{0x3691,0x33},
									{0x3692,0x44},
									{0x369c,0x40},
									{0x369d,0x48},
									{0x3901,0x02},
									{0x3904,0x04},
									{0x3908,0x41},
									{0x391d,0x14},
									{0x391f,0x18},
									{0x3e01,0x8c},
									{0x3e02,0x20},
									{0x3e16,0x00},
									{0x3e17,0x80},
									{0x3f09,0x48},
									{0x5787,0x10},
									{0x5788,0x06},
									{0x578a,0x10},
									{0x578b,0x06},
									{0x5790,0x10},
									{0x5791,0x10},
									{0x5792,0x00},
									{0x5793,0x10},
									{0x5794,0x10},
									{0x5795,0x00},
									{0x5799,0x00},
									{0x57c7,0x10},
									{0x57c8,0x06},
									{0x57ca,0x10},
									{0x57cb,0x06},
									{0x57d1,0x10},
									{0x57d4,0x10},
									{0x57d9,0x00},
									{0x59e0,0x60},
									{0x59e1,0x08},
									{0x59e2,0x3f},
									{0x59e3,0x18},
									{0x59e4,0x18},
									{0x59e5,0x3f},
									{0x59e6,0x06},
									{0x59e7,0x02},
									{0x59e8,0x38},
									{0x59e9,0x10},
									{0x59ea,0x0c},
									{0x59eb,0x10},
									{0x59ec,0x04},
									{0x59ed,0x02},
									{0x59ee,0xa0},
									{0x59ef,0x08},
									{0x59f4,0x18},
									{0x59f5,0x10},
									{0x59f6,0x0c},
									{0x59f7,0x10},
									{0x59f8,0x06},
									{0x59f9,0x02},
									{0x59fa,0x18},
									{0x59fb,0x10},
									{0x59fc,0x0c},
									{0x59fd,0x10},
									{0x59fe,0x04},
									{0x59ff,0x02},
									{0x36e9,0x20},
									{0x36f9,0x27},
									{0x0100,0x01}
								};
	
	const WORD gwTblSens2[][2] = {	// 1080p60
									{0x0103,0x01},
									{0x0100,0x00},
									{0x36e9,0x80},
									{0x36f9,0x80},
									{0x301f,0x41},
									{0x3200,0x00},
									{0x3201,0x00},
									{0x3202,0x00},
									{0x3203,0x00},
									{0x3204,0x07},
									{0x3205,0x8b},
									{0x3206,0x04},
									{0x3207,0x43},
									{0x3208,0x07},
									{0x3209,0x88},
									{0x320a,0x04},
									{0x320b,0x40},
									{0x3210,0x00},
									{0x3211,0x02},
									{0x3212,0x00},
									{0x3213,0x02},
									{0x3243,0x01},
									{0x3248,0x02},
									{0x3249,0x09},
									{0x3253,0x08},
									{0x3271,0x0a},
									{0x3301,0x06},
									{0x3302,0x0c},
									{0x3303,0x08},
									{0x3304,0x60},
									{0x3306,0x30},
									{0x3308,0x10},
									{0x3309,0x70},
									{0x330b,0x80},
									{0x330d,0x16},
									{0x330e,0x1c},
									{0x330f,0x02},
									{0x3310,0x02},
									{0x331c,0x04},
									{0x331e,0x51},
									{0x331f,0x61},
									{0x3320,0x07},
									{0x3333,0x10},
									{0x334c,0x08},
									{0x3356,0x09},
									{0x3364,0x17},
									{0x3390,0x08},
									{0x3391,0x18},
									{0x3392,0x38},
									{0x3393,0x06},
									{0x3394,0x06},
									{0x3395,0x06},
									{0x3396,0x08},
									{0x3397,0x18},
									{0x3398,0x38},
									{0x3399,0x06},
									{0x339a,0x0a},
									{0x339b,0x10},
									{0x339c,0x20},
									{0x33ac,0x08},
									{0x33ae,0x10},
									{0x33af,0x19},
									{0x3621,0xe8},
									{0x3622,0x16},
									{0x3630,0xa0},
									{0x3637,0x36},
									{0x363a,0x1f},
									{0x363b,0xc6},
									{0x363c,0x0e},
									{0x3670,0x0a},
									{0x3674,0x82},
									{0x3675,0x76},
									{0x3676,0x78},
									{0x367c,0x48},
									{0x367d,0x58},
									{0x3690,0x34},
									{0x3691,0x33},
									{0x3692,0x44},
									{0x369c,0x40},
									{0x369d,0x48},
									{0x36eb,0x0c},
									{0x36ec,0x0c},
									{0x36fd,0x14},
									{0x3901,0x02},
									{0x3904,0x04},
									{0x3908,0x41},
									{0x391f,0x10},
									{0x3e01,0x8c},
									{0x3e02,0x20},
									{0x3e16,0x00},
									{0x3e17,0x80},
									{0x3f09,0x48},
									{0x4819,0x09},
									{0x481b,0x05},
									{0x481d,0x14},
									{0x481f,0x04},
									{0x4821,0x0a},
									{0x4823,0x05},
									{0x4825,0x04},
									{0x4827,0x05},
									{0x4829,0x08},
									{0x5787,0x10},
									{0x5788,0x06},
									{0x578a,0x10},
									{0x578b,0x06},
									{0x5790,0x10},
									{0x5791,0x10},
									{0x5792,0x00},
									{0x5793,0x10},
									{0x5794,0x10},
									{0x5795,0x00},
									{0x5799,0x00},
									{0x57c7,0x10},
									{0x57c8,0x06},
									{0x57ca,0x10},
									{0x57cb,0x06},
									{0x57d1,0x10},
									{0x57d4,0x10},
									{0x57d9,0x00},
									{0x59e0,0x60},
									{0x59e1,0x08},
									{0x59e2,0x3f},
									{0x59e3,0x18},
									{0x59e4,0x18},
									{0x59e5,0x3f},
									{0x59e6,0x06},
									{0x59e7,0x02},
									{0x59e8,0x38},
									{0x59e9,0x10},
									{0x59ea,0x0c},
									{0x59eb,0x10},
									{0x59ec,0x04},
									{0x59ed,0x02},
									{0x59ee,0xa0},
									{0x59ef,0x08},
									{0x59f4,0x18},
									{0x59f5,0x10},
									{0x59f6,0x0c},
									{0x59f7,0x10},
									{0x59f8,0x06},
									{0x59f9,0x02},
									{0x59fa,0x18},
									{0x59fb,0x10},
									{0x59fc,0x0c},
									{0x59fd,0x10},
									{0x59fe,0x04},
			                        {0x59ff,0x02},
			                        {0x36e9,0x20},
			                        {0x36f9,0x24},
			                        {0x0100,0x01}
								};
								
	const WORD gwTblSC200AIWdr[][2] = { 
					        		{0x0103,0x01},
									{0x0100,0x00},
									{0x36e9,0x80},
									{0x36f9,0x80},
									{0x301f,0x43},
									{0x3200,0x00},
									{0x3201,0x00},
									{0x3202,0x00},
									{0x3203,0x00},
									{0x3204,0x07},
									{0x3205,0x8b},
									{0x3206,0x04},
									{0x3207,0x43},
									{0x3208,0x07},
									{0x3209,0x88},
									{0x320a,0x04},
									{0x320b,0x40},
									{0x320e,0x08},
									{0x320f,0xca},
									{0x3210,0x00},
									{0x3211,0x02},
									{0x3212,0x00},
									{0x3213,0x02},
									{0x3220,0x53},
									{0x3243,0x01},
									{0x3248,0x02},
									{0x3249,0x09},
									{0x3250,0x3f},
									{0x3253,0x08},
									{0x3271,0x0a},
									{0x3301,0x06},
									{0x3302,0x0c},
									{0x3303,0x08},
									{0x3304,0x60},
									{0x3306,0x30},
									{0x3308,0x10},
									{0x3309,0x70},
									{0x330b,0x80},
									{0x330d,0x16},
									{0x330e,0x1c},
									{0x330f,0x02},
									{0x3310,0x02},
									{0x331c,0x04},
									{0x331e,0x51},
									{0x331f,0x61},
									{0x3320,0x07},
									{0x3333,0x10},
									{0x334c,0x08},
									{0x3356,0x09},
									{0x3364,0x17},
									{0x3390,0x08},
									{0x3391,0x18},
									{0x3392,0x38},
									{0x3393,0x06},
									{0x3394,0x06},
									{0x3395,0x06},
									{0x3396,0x08},
									{0x3397,0x18},
									{0x3398,0x38},
									{0x3399,0x06},
									{0x339a,0x0a},
									{0x339b,0x10},
									{0x339c,0x20},
									{0x33ac,0x08},
									{0x33ae,0x10},
									{0x33af,0x19},
									{0x3621,0xe8},
									{0x3622,0x16},
									{0x3630,0xa0},
									{0x3637,0x36},
									{0x363a,0x1f},
									{0x363b,0xc6},
									{0x363c,0x0e},
									{0x3670,0x0a},
									{0x3674,0x82},
									{0x3675,0x76},
									{0x3676,0x78},
									{0x367c,0x48},
									{0x367d,0x58},
									{0x3690,0x34},
									{0x3691,0x33},
									{0x3692,0x44},
									{0x369c,0x40},
									{0x369d,0x48},
									{0x36eb,0x0c},
									{0x36ec,0x0c},
									{0x36fd,0x14},
									{0x3901,0x02},
									{0x3904,0x04},
									{0x3908,0x41},
									{0x391f,0x10},
									{0x3e00,0x01},
									{0x3e01,0x06},
									{0x3e02,0x00},
									{0x3e04,0x10},
									{0x3e05,0x60},
									{0x3e06,0x00},
									{0x3e07,0x80},
									{0x3e08,0x03},
									{0x3e09,0x40},
									{0x3e10,0x00},
									{0x3e11,0x80},
									{0x3e12,0x03},
									{0x3e13,0x40},
									{0x3e16,0x00},
									{0x3e17,0x80},
									{0x3e23,0x00}, // Max Short Exposure
									{0x3e24,0x26}, // Max Short Exposure
									{0x3f09,0x48},
									{0x4816,0xb1},
									{0x4819,0x09},
									{0x481b,0x05},
									{0x481d,0x14},
									{0x481f,0x04},
									{0x4821,0x0a},
									{0x4823,0x05},
									{0x4825,0x04},
									{0x4827,0x05},
									{0x4829,0x08},
									{0x5787,0x10},
									{0x5788,0x06},
									{0x578a,0x10},
									{0x578b,0x06},
									{0x5790,0x10},
									{0x5791,0x10},
									{0x5792,0x00},
									{0x5793,0x10},
									{0x5794,0x10},
									{0x5795,0x00},
									{0x5799,0x00},
									{0x57c7,0x10},
									{0x57c8,0x06},
									{0x57ca,0x10},
									{0x57cb,0x06},
									{0x57d1,0x10},
									{0x57d4,0x10},
									{0x57d9,0x00},
									{0x59e0,0x60},
									{0x59e1,0x08},
									{0x59e2,0x3f},
									{0x59e3,0x18},
									{0x59e4,0x18},
									{0x59e5,0x3f},
									{0x59e6,0x06},
									{0x59e7,0x02},
									{0x59e8,0x38},
									{0x59e9,0x10},
									{0x59ea,0x0c},
									{0x59eb,0x10},
									{0x59ec,0x04},
									{0x59ed,0x02},
									{0x59ee,0xa0},
									{0x59ef,0x08},
									{0x59f4,0x18},
									{0x59f5,0x10},
									{0x59f6,0x0c},
									{0x59f7,0x10},
									{0x59f8,0x06},
									{0x59f9,0x02},
									{0x59fa,0x18},
									{0x59fb,0x10},
									{0x59fc,0x0c},
									{0x59fd,0x10},
									{0x59fe,0x04},
									{0x59ff,0x02},
									{0x36e9,0x20},
									{0x36f9,0x24},
									{0x0100,0x01}
				        		};

//----------------------------------------------------------------------------------------

const UINT gTblSensEa	    = numberof(gwTblSens0);
const UINT gTblSens2Ea	    = numberof(gwTblSens2);
const UINT gTblSC200AIWdrEa	= numberof(gwTblSC200AIWdr);

// -----------------------------------------------------------------------------------------
// AE
// -----------------------------------------------------------------------------------------

	const BYTE 	gbAeHssFltTbl[]   = {
					                 0,		// 0
									53,		// 1
									31,		// 2
									23,		// 3
									20,		// 4
									14,		// 5
									12,		// 6
									11,		// 7
									8,		// 8
									7 ,	    // 9
									6 ,
									6 ,
									6 ,
									5 ,
									5 ,
									4 ,
									4 ,
									4 ,
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
									2 ,
									2 ,
									2 ,
									2 ,
									1 ,
									1 ,
									1 ,
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
	UNUSED_ARG(aiResMode);
	LibISPtoSENS_Intf(\
					/* MIPI or LVDS */\
					MIPI,\
					/* 1, 2, 4 LANE */\
					(_2LANE),\
					/* 12BIT or 10BIT */\
					(_10BIT),\
					/* 3210, 10, 0 */\
					(_3210),\
					/* Word Count */\
					((aiWdrMode==MN_OFF) ? (0x96a):(0x96a)),\
					/* MIPI Line information or Virtual channel mode */\
					_MIPI_VC,\
					aiWdrMode);
}

void LibInitSens(int aiMode, int aiOption)
{	// SC200AI, Sensor Master mode
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
	
	if(!aiOption)	
	{
		if(!aiMode)	
		{	
			for (i=0; i<gTblSensEa; i++)	{ SetSens(gwTblSens0[i][0], (BYTE)gwTblSens0[i][1]);} 
			SetSens(0x301f, (0x3f+(MP(MpSysFreq)==MN_SYSFREQ_50)));  // 
		}
		else		
		{ 
			for (i=0; i<gTblSens2Ea; i++)	{ SetSens(gwTblSens2[i][0], (BYTE)gwTblSens2[i][1]);}  
			SetSens(0x301f, (0x41+(MP(MpSysFreq)==MN_SYSFREQ_50)));
		}
		gbSC200AIWdrOnFlg=0; 		
	}
	else 
	{	
		for (i=0; i<gTblSC200AIWdrEa; i++)	{ SetSens(gwTblSC200AIWdr[i][0], (BYTE)gwTblSC200AIWdr[i][1]);} 
		SetSens(0x301f, (0x43+(MP(MpSysFreq)==MN_SYSFREQ_50)));  
		gbSC200AIWdrOnFlg=1;
	}
	
	SetSens(0x3907, 0x00); // Black Offset
	SetSens(0x3908, 0x00); // Black Offset

	//Shutter Speed Max
	gnAeNorMax = gnInModeVtw-AE_SHTMAX_OFST;

	if(aiOption==1) {			// DOL 2P		
         // short_exp<vb,long_exp+short_ep<frame lengthx
		gnAeLWdrMaxL0	= (1125*2-2*38-10);// 
		gnAeLWdrMaxS1	= (38*2-10);  // (38*2); 

		gnAeLWdrMinL0	= 1;//
		gnAeLWdrMinS1	= 1;//
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
	
	if(val<0x40)		{ SetSens(0x3e08, 0x03); iValAgc=val; }// AGC 
	else if(val<0x06D)	{ SetSens(0x3e08, 0x07); iValAgc=val-0x040; } // 
	else if(val<0x0AD)	{ SetSens(0x3e08, 0x23); iValAgc=val-0x06D; } // 
	else if(val<0x0ED)	{ SetSens(0x3e08, 0x27); iValAgc=val-0x0AD; } // 
	else if(val<0x12D)  { SetSens(0x3e08, 0x2F); iValAgc=val-0x0ED; } // 
	else if(val<0x16D)	{ SetSens(0x3e08, 0x3F); iValAgc=val-0x12D; } // 

	SetSens(0x3e09, (val<0x16D) ? ((iValAgc+0x40)&0xff) : 0x7f); // AGC Fine
	
	val=(val<0x16D) ? 0 : 2*(val-0x16D);
	
	if(val<0x7F)		{ SetSens(0x3e06, 0x00); iValDgc=val;       } //  DGC
	else if(val<0xFE)	{ SetSens(0x3e06, 0x01); iValDgc=val-0x7F ; } // 
	else if(val<0x17D)	{ SetSens(0x3e06, 0x03); iValDgc=val-0xFE ; } //
	else if(val<0x1FC)	{ SetSens(0x3e06, 0x07); iValDgc=val-0x17D; } //
	else if(val<0x27B)	{ SetSens(0x3e06, 0x0F); iValDgc=val-0x1FC; } //
	
	SetSens(0x3e07, (iValDgc+0x80)&0xff); // DGC Fine

	//Short Gain
	if(gbModeWdrOn_L){

	if(val1<0x40)		{ SetSens(0x3e12, 0x03); iValAgc=val1; }// AGC 
	else if(val1<0x06D)	{ SetSens(0x3e12, 0x07); iValAgc=val1-0x040; } // 
	else if(val1<0x0AD)	{ SetSens(0x3e12, 0x23); iValAgc=val1-0x06D; } // 
	else if(val1<0x0ED)	{ SetSens(0x3e12, 0x27); iValAgc=val1-0x0AD; } // 
	else if(val1<0x12D) { SetSens(0x3e12, 0x2F); iValAgc=val1-0x0ED; } // 
	else if(val1<0x16D)	{ SetSens(0x3e12, 0x3F); iValAgc=val1-0x12D; } // 

	SetSens(0x3e13, (val1<0x16D) ? ((iValAgc+0x40)&0xff) : 0x7f); // AGC Fine
	
	val1=(val1<0x16D) ? 0 : 2*(val1-0x16D);
	
	if(val1<0x7F)		{ SetSens(0x3e10, 0x00); iValDgc=val1;       } //  DGC
	else if(val1<0xFE)	{ SetSens(0x3e10, 0x01); iValDgc=val1-0x7F ; } // 
	else if(val1<0x17D)	{ SetSens(0x3e10, 0x03); iValDgc=val1-0xFE ; } //
	else if(val1<0x1FC)	{ SetSens(0x3e10, 0x07); iValDgc=val1-0x17D; } //
	else if(val1<0x27B)	{ SetSens(0x3e10, 0x0F); iValDgc=val1-0x1FC; } //
	
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
	
	DebugDisp(gbAeDebugOn, Hex, "AGC_____", 5, 24, (aiVal<0x16D) ? aiVal : 0x16D);
//	DebugDisp(gbAeDebugOn, Hex, "DGC_____", 6, 24, (aiVal>0x16D) ? aiVal-0x16D:0);
	DebugDisp(gbAeDebugOn, Hex, "WDR_GAIN", 6, 24, (giAeLWdrGain))
}

// -------------------------------------------------------------------------------------
// LINE WDR

WORD ISPM AeSHT_LWDR(int aiMode, int aiVal, int aiVal1)
{	// Shutter driver for Line WDR
//	 aiMode : 0 : off, 1: 2 page, 2: 3 page
//	 aiVal  : Long
//	 aiVal1 : short1
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
////
//		AE_SHTSw(tgt_S1);
////		AE_SC200AI_AGC_S(gnShtFlt_S);
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

	DebugDisp(gbAeDebugOn, Hex, "AGC_____", 5, 24, (aiVal<0x16D) ? aiVal : 0x16D);
	DebugDisp(gbAeDebugOn, Hex, "WDR_GAIN", 6, 24, (giAeLWdrGain))
//	DebugDisp(gbAeDebugOn, Hex, "DGC_____", 6, 24, (aiVal>0x16D) ? aiVal-0x16D:0);
}

// -----------------------------------------------------------------------------------------
// AWB
// -----------------------------------------------------------------------------------------
	//Designer 	: Yu, Tae Myeong
	//Date		: 21.04.13
	const s64 glMtxCf[9][6] =		{	// RT, Y 350
									{	      42367365814966LL,	         51787327989LL,	        -39655398535LL,	           291382031LL,	           183489642LL,	           182940673LL},
									{	      66739257559950LL,	        177881237359LL,	        136215443324LL,	           247130846LL,	           176040993LL,	            89781284LL},
									{	      24923549845504LL,	         23733718369LL,	         65639884508LL,	           187801006LL,	           177088862LL,	           276125470LL},
									{	     -52426945324586LL,	       -108233329717LL,	        -74557839860LL,	          -182107462LL,	          -127519113LL,	           -82084401LL},
									{	     190471460080696LL,	        527842210663LL,	        386019912396LL,	          1058415263LL,	           693968827LL,	           468808715LL},
									{	     -41717516390043LL,	       -310620772728LL,	       -117665650393LL,	          -575961030LL,	          -392098198LL,	            24602186LL},
									{	     -12648004802397LL,	         21117314327LL,	         16480481541LL,	           155139998LL,	            84041005LL,	            76082031LL},
									{	      47078176377552LL,	          2215135372LL,	        -25042167978LL,	          -257937214LL,	          -126223141LL,	          -177846621LL},
									{	     251226906829905LL,	       1375250892653LL,	       1379058429490LL,	          4506234799LL,	          2642023408LL,	          2886136723LL}
									};


// -----------------------------------------------------------------------------------------
// MIRROR & FLIP
// -----------------------------------------------------------------------------------------

BYTE gbSC200AIMirrFlg=0;
void Sens(SENS_MIRw)(BYTE abOn){
	SetSens(0x3221,((GetSens(0x3221)&(~ValSft_L01(BitMask_02)))|ValSft_L01(abOn*3)));
	gbSC200AIMirrFlg=abOn*3;
}

void Sens(SENS_FLPw)(BYTE abOn){
	SetSens(0x3221,((ValSft_L01(gbSC200AIMirrFlg)&(~ValSft_L05(BitMask_02)))|ValSft_L05(abOn*3)));
	
	static BYTE bBuf=0xf,bBuf1=0xf;
	static UINT nVLOCKL_POS=0,nVLOCKS_POS=0;
	
	if((bBuf!=abOn)||(gbSC200AIWdrOnFlg!=bBuf1)) {
		if(gbSC200AIWdrOnFlg!=bBuf1) {nVLOCKL_POS=VLOCKL_POSr; nVLOCKS_POS=VLOCKS_POSr;}
		VLOCKL_POSw(nVLOCKL_POS+((MP(MpOutFps)==MN_2M_1080p_50_60)?abOn:abOn*gbSC200AIWdrOnFlg));
		VLOCKS_POSw(nVLOCKS_POS+abOn*gbSC200AIWdrOnFlg);
		bBuf1=gbSC200AIWdrOnFlg; bBuf=abOn;
	}
	
	extern UINT gnOutputDelay;
	if(gnOutputDelay==1)	SetIsp(0x005d,0x9000f);  // bottom is cropped by 4 Line
}


