/* **************************************************************************
 File Name	:	EN772_SENS_GC2053.c
 Description	:	EN772 - GC2053 device driver
 Designer		:	Han Tian Yong
 Date		:	21. 01. 12
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#undef model_Sens
#include "../Src/dev.h"
#define model_Sens	SENS_GC2053
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

extern int	giAeLWdrGain;

#define AE_SHTMAX_OFST	0
#define AE_SHTMIN_OFST	1
#define AE_SHTMAX		(nMok-AE_SHTMAX_OFST)

#define AE_GAIN_UNIT_MAX		(96*3) /* ((113-5)*3) */
#define AE_GAIN_UNIT_EA			(1)																				// Sensor gain Unit EA
#define AE_GAIN_UNIT_OVR		(0)																			// Sensor gain extended step
#define AE_GAIN_UNIT_OVR2		(0)	    																		// ISP gain extended step
const int Sens(AE_GAIN_TOTAL) = (((AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR)*(0.125/0.1));
const int Sens(AE_GAIN_TOTAL2) = 0;

#define AE_GAIN_DENORMAL(val)	(ifdiv8(val*(int)(0.8f*256.f)))		// 171211 LH : int floating


#define AE_HSS_FLT_EA		(sizeof(gbAeHssFltTbl))
#define AE_SHT_TBL_EA		(sizeof(gnAeShtTbl)/8)

// -----------------------------------------------------------------------------------------
// initial
	// GC2053 MIPI
	// MIPI : Normal 2 -lane
	// INCK : 27MHz
	const BYTE gwTblSens0[][2] = {
						//ADDR	 Nor 2M30P	
								{0xfe,0x80},
								{0xfe,0x80},
								{0xfe,0x80},
								{0xfe,0x00},
								{0xf2,0x00},
								{0xf3,0x00},
								{0xf4,0x36},
								{0xf5,0xc0},
								{0xf6,0x44},
								{0xf7,0x01},
								{0xf8,0x2c},
								{0xf9,0x42},
								{0xfc,0x8e},
								
								/****CISCTL & ANALOG****/
								{0xfe,0x00},
								{0x87,0x18},
								{0xee,0x30},
								{0xd0,0xb7},
								{0x03,0x04},
								{0x04,0x60},
								{0x05,0x04},
								{0x06,0x4c},
								{0x07,0x00},
								{0x08,0x11},
								{0x09,0x00},
								{0x0a,0x02},
								{0x0b,0x00},
								{0x0c,0x02},
								{0x0d,0x04},
								{0x0e,0x40},
								{0x12,0xe2},
								{0x13,0x16},
								{0x19,0x0a},
								{0x21,0x1c},
								{0x28,0x0a},
								{0x29,0x24},
								{0x2b,0x04},
								{0x32,0xf8},
								{0x37,0x03},
								{0x39,0x15},
								{0x43,0x07},
								{0x44,0x40},
								{0x46,0x0b},
								{0x4b,0x20},
								{0x4e,0x08},
								{0x55,0x20},
								{0x66,0x05},
								{0x67,0x05},
								{0x77,0x01},
								{0x78,0x00},
								{0x7c,0x93},
								{0x8c,0x12},
								{0x8d,0x92},
								{0x90,0x00}, //01
								{0x41,0x04},
								{0x42,0x65}, //1125 frame length
								{0x9d,0x10},
								{0xce,0x7c},
								{0xd2,0x41},
								{0xd3,0xdc},
								{0xe6,0x50},
								
								/*gain*/
								{0xb6,0xc0},
//								{0xb0,0x70},
								{0xb0,0x60},

								{0xb1,0x01},
								{0xb2,0x00},
								{0xb3,0x00},
								{0xb4,0x00},
								{0xb8,0x01},
								{0xb9,0x00},
								
								/*blk*/
								{0x26,0x30},
								{0xfe,0x01},
								{0x40,0x23},
								{0x55,0x07},
								{0x60,0x40},
								{0xfe,0x04},
								{0x14,0x78},
								{0x15,0x78},
								{0x16,0x78},
								{0x17,0x78},
								
								/*window*/
								{0xfe,0x01},
								{0x92,0x00},
								{0x94,0x03},
								{0x95,0x04},
								{0x96,0x40},
								{0x97,0x07},
								{0x98,0x88},
								
								/*ISP*/
								{0xfe,0x01},
								{0x01,0x05},
								{0x02,0x89},
								{0x04,0x01},
								{0x07,0xa6},
								{0x08,0xa9},
								{0x09,0xa8},
								{0x0a,0xa7},
								{0x0b,0xff},
								{0x0c,0xff},
								{0x0f,0x00},
								{0x50,0x1c},
								{0x89,0x03},
								{0xfe,0x04},
								{0x28,0x86},
								{0x29,0x86},
								{0x2a,0x86},
								{0x2b,0x68},
								{0x2c,0x68},
								{0x2d,0x68},
								{0x2e,0x68},
								{0x2f,0x68},
								{0x30,0x4f},
								{0x31,0x68},
								{0x32,0x67},
								{0x33,0x66},
								{0x34,0x66},
								{0x35,0x66},
								{0x36,0x66},
								{0x37,0x66},
								{0x38,0x62},
								{0x39,0x62},
								{0x3a,0x62},
								{0x3b,0x62},
								{0x3c,0x62},
								{0x3d,0x62},
								{0x3e,0x62},
								{0x3f,0x62},
								
								/****DVP & MIPI****/
								{0xfe,0x01},
								{0x9a,0x06},
								{0xfe,0x00},
								{0x7b,0x2a},
								{0x23,0x2d},
								{0xfe,0x03},
								{0x01,0x27},
								{0x02,0x56},
								{0x03,0xb6},
								{0x12,0x80},
								{0x13,0x07},
								{0x15,0x12},
								{0xfe,0x00},
								{0x3e,0x91}
						  };
	
const UINT gTblSensEa		= numberof(gwTblSens0);

const BYTE gbRegValTable[][10] = {
		//0xb4	0xb3  0xb8	0xb9  0xb1	0xb2
		 {0x00, 0x00, 0x01, 0x00, 0x01, 0x00}, //	0
		 {0x00, 0x00, 0x01, 0x00, 0x01, 0x0C}, //	1
		 {0x00, 0x00, 0x01, 0x00, 0x01, 0x20}, //	2
		 {0x00, 0x10, 0x01, 0x0c, 0x01, 0x00}, //	3
		 {0x00, 0x10, 0x01, 0x0c, 0x01, 0x10}, //	4
		 {0x00, 0x10, 0x01, 0x0c, 0x01, 0x20}, //	5
		 {0x00, 0x10, 0x01, 0x0c, 0x01, 0x2C}, //	6
		 {0x00, 0x20, 0x01, 0x1b, 0x01, 0x04}, //	7
		 {0x00, 0x20, 0x01, 0x1b, 0x01, 0x10}, //	8
		 {0x00, 0x20, 0x01, 0x1b, 0x01, 0x18}, //	9
		 {0x00, 0x30, 0x01, 0x2c, 0x01, 0x00}, //	10
		 {0x00, 0x30, 0x01, 0x2c, 0x01, 0x08}, //	11
		 {0x00, 0x30, 0x01, 0x2c, 0x01, 0x14}, //	12
		 {0x00, 0x30, 0x01, 0x2c, 0x01, 0x20}, //	13
		 {0x00, 0x30, 0x01, 0x2c, 0x01, 0x28}, //	14
		 {0x00, 0x30, 0x01, 0x2c, 0x01, 0x30}, //	15
//		 {0x00, 0x40, 0x01, 0x3f, 0x01, 0x00}, //	16
		 {0x00, 0x40, 0x01, 0x3f, 0x01, 0x0C}, //	17
		 {0x00, 0x40, 0x01, 0x3f, 0x01, 0x20}, //	18
		 {0x00, 0x50, 0x02, 0x16, 0x01, 0x04}, //	19
		 {0x00, 0x50, 0x02, 0x16, 0x01, 0x10}, //	20
		 {0x00, 0x50, 0x02, 0x16, 0x01, 0x20}, //	21
		 {0x00, 0x50, 0x02, 0x16, 0x01, 0x2C}, //	22
		 {0x00, 0x60, 0x02, 0x35, 0x01, 0x04}, //	23
		 {0x00, 0x60, 0x02, 0x35, 0x01, 0x10}, //	24
		 {0x00, 0x60, 0x02, 0x35, 0x01, 0x20}, //	25
		 {0x00, 0x70, 0x03, 0x02, 0x01, 0x00}, //	26
		 {0x00, 0x70, 0x03, 0x02, 0x01, 0x0C}, //	27
		 {0x00, 0x70, 0x03, 0x02, 0x01, 0x14}, //	28
		 {0x00, 0x70, 0x03, 0x02, 0x01, 0x20}, //	29
		 {0x00, 0x70, 0x03, 0x02, 0x01, 0x28}, //	30
		 {0x00, 0x70, 0x03, 0x02, 0x01, 0x34}, //	31
		 {0x00, 0x70, 0x03, 0x02, 0x01, 0x40}, //	32
//		 {0x00, 0x80, 0x04, 0x02, 0x01, 0x04}, //	33
		 {0x00, 0x80, 0x04, 0x02, 0x01, 0x14}, //	34
		 {0x00, 0x90, 0x04, 0x31, 0x01, 0x00}, //	35
		 {0x00, 0x90, 0x04, 0x31, 0x01, 0x0C}, //	36
		 {0x00, 0x90, 0x04, 0x31, 0x01, 0x18}, //	37
		 {0x00, 0x90, 0x04, 0x31, 0x01, 0x28}, //	38
		 {0x00, 0xa0, 0x05, 0x32, 0x01, 0x00}, //	39
		 {0x00, 0xa0, 0x05, 0x32, 0x01, 0x0C}, //	40
		 {0x00, 0xa0, 0x05, 0x32, 0x01, 0x14}, //	41
		 {0x00, 0xb0, 0x06, 0x35, 0x01, 0x00}, //	42
		 {0x00, 0xb0, 0x06, 0x35, 0x01, 0x04}, //	43
		 {0x00, 0xb0, 0x06, 0x35, 0x01, 0x10}, //	44
		 {0x00, 0xb0, 0x06, 0x35, 0x01, 0x18}, //	45
		 {0x00, 0xb0, 0x06, 0x35, 0x01, 0x24}, //	46
		 {0x00, 0xb0, 0x06, 0x35, 0x01, 0x2C}, //	47
		 {0x00, 0xc0, 0x08, 0x04, 0x01, 0x00}, //	48
		 {0x00, 0xc0, 0x08, 0x04, 0x01, 0x10}, //	49
		 {0x00, 0xc0, 0x08, 0x04, 0x01, 0x20}, //	50
		 {0x00, 0x5a, 0x09, 0x19, 0x01, 0x04}, //	51
		 {0x00, 0x5a, 0x09, 0x19, 0x01, 0x14}, //	52
		 {0x00, 0x5a, 0x09, 0x19, 0x01, 0x24}, //	53
		 {0x00, 0x5a, 0x09, 0x19, 0x01, 0x30}, //	54
//		 {0x00, 0x83, 0x0b, 0x0f, 0x01, 0x00}, //	55
		 {0x00, 0x83, 0x0b, 0x0f, 0x01, 0x0C}, //	56
		 {0x00, 0x83, 0x0b, 0x0f, 0x01, 0x14}, //	57
		 {0x00, 0x93, 0x0d, 0x12, 0x01, 0x00}, //	58
		 {0x00, 0x93, 0x0d, 0x12, 0x01, 0x04}, //	59
		 {0x00, 0x93, 0x0d, 0x12, 0x01, 0x0C}, //	60
		 {0x00, 0x93, 0x0d, 0x12, 0x01, 0x18}, //	61
		 {0x00, 0x93, 0x0d, 0x12, 0x01, 0x20}, //	62
		 {0x00, 0x93, 0x0d, 0x12, 0x01, 0x2C}, //	63
		 {0x00, 0x93, 0x0d, 0x12, 0x01, 0x34}, //	64
		 {0x00, 0x84, 0x10, 0x00, 0x01, 0x08}, //	65
		 {0x00, 0x84, 0x10, 0x00, 0x01, 0x18}, //	66
		 {0x00, 0x94, 0x12, 0x3a, 0x01, 0x00}, //	67
		 {0x00, 0x94, 0x12, 0x3a, 0x01, 0x10}, //	68
		 {0x00, 0x94, 0x12, 0x3a, 0x01, 0x20}, //	69
		 {0x01, 0x2c, 0x1a, 0x02, 0x01, 0x00}, //	70
		 {0x01, 0x2c, 0x1a, 0x02, 0x01, 0x04}, //	71
		 {0x01, 0x2c, 0x1a, 0x02, 0x01, 0x10}, //	72
		 {0x01, 0x2c, 0x1a, 0x02, 0x01, 0x20}, //	73
		 {0x01, 0x3c, 0x1b, 0x20, 0x01, 0x00}, //	74
		 {0x01, 0x3c, 0x1b, 0x20, 0x01, 0x0C}, //	75
		 {0x01, 0x3c, 0x1b, 0x20, 0x01, 0x14}, //	76
		 {0x01, 0x3c, 0x1b, 0x20, 0x01, 0x20}, //	77
		 {0x01, 0x3c, 0x1b, 0x20, 0x01, 0x28}, //	78
		 {0x01, 0x3c, 0x1b, 0x20, 0x01, 0x34}, //	79
//		 {0x00, 0x8c, 0x20, 0x0f, 0x01, 0x00}, //	80
		 {0x00, 0x8c, 0x20, 0x0f, 0x01, 0x10}, //	81
		 {0x00, 0x9c, 0x26, 0x07, 0x01, 0x00}, //	82
		 {0x00, 0x9c, 0x26, 0x07, 0x01, 0x08}, //	83
		 {0x00, 0x9c, 0x26, 0x07, 0x01, 0x18}, //	84
		 {0x00, 0x9c, 0x26, 0x07, 0x01, 0x28}, //	85
		 {0x00, 0x9c, 0x26, 0x07, 0x01, 0x34}, //	86
		 {0x02, 0x64, 0x36, 0x21, 0x01, 0x04}, //	87
		 {0x02, 0x64, 0x36, 0x21, 0x01, 0x0C}, //	88
		 {0x02, 0x64, 0x36, 0x21, 0x01, 0x18}, //	89
		 {0x02, 0x74, 0x37, 0x3a, 0x01, 0x00}, //	90
		 {0x02, 0x74, 0x37, 0x3a, 0x01, 0x08}, //	91
		 {0x02, 0x74, 0x37, 0x3a, 0x01, 0x10}, //	92
		 {0x02, 0x74, 0x37, 0x3a, 0x01, 0x20}, //	93
		 {0x02, 0x74, 0x37, 0x3a, 0x01, 0x24}, //	94
		 {0x02, 0x74, 0x37, 0x3a, 0x01, 0x30}, //	95		 
//		 {0x00, 0xc6, 0x3d, 0x02, 0x01, 0x00}, //	96
		 {0x00, 0xc6, 0x3d, 0x02, 0x01, 0x0C}, //	97
		 {0x00, 0xc6, 0x3d, 0x02, 0x01, 0x20}, //	98
		 {0x00, 0xc6, 0x3d, 0x02, 0x01, 0x2C}, //	99
		 {0x00, 0xc6, 0x3d, 0x02, 0x01, 0x40}, //	100
//		 {0x00, 0xdc, 0x3f, 0x3f, 0x01, 0x04}, //	101
		/*
		 {0x02, 0x85, 0x3f, 0x3f, 0x01, 0x00}, //	102
		 {0x02, 0x85, 0x3f, 0x3f, 0x01, 0x0C}, //	103
		 {0x02, 0x85, 0x3f, 0x3f, 0x01, 0x18}, //	104
		 {0x02, 0x85, 0x3f, 0x3f, 0x01, 0x24}, //	105
		 {0x02, 0x85, 0x3f, 0x3f, 0x01, 0x30}, //	106
//		 {0x02, 0x95, 0x3f, 0x3f, 0x01, 0x00}, //	107
		 {0x00, 0xce, 0x3f, 0x3f, 0x01, 0x00}, //	108
		 {0x00, 0xce, 0x3f, 0x3f, 0x01, 0x08}, //	109
		 {0x00, 0xce, 0x3f, 0x3f, 0x01, 0x10}, //	110
		 {0x00, 0xce, 0x3f, 0x3f, 0x01, 0x18}, //	111
		 {0x00, 0xce, 0x3f, 0x3f, 0x01, 0x24}  //   112
		*/
                            };

const UINT gTblAgain_Ea		= numberof(gbRegValTable);

// -----------------------------------------------------------------------------------------
// AE
// -----------------------------------------------------------------------------------------
	const BYTE 	gbAeHssFltTbl[]   = {
									0 ,
									35,	// 57
									25,
									18,
									15,
									13,
									11,
									10,
									9 ,
									8 ,
									8 ,
									7 ,
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
									{980 , 10167401},
									{994 , 11945655},
									{1008, 14034920}
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
					(_10BIT),\
					/* 3210, 10, 0 */\
					(_10),\
					/* Word Count */\
					(0x96A),\
					/* MIPI Line information or Virtual channel mode */\
					(_MIPI_VC),\
					(aiWdrMode));
}

void LibInitSens(int aiMode, int aiOption)
{	// GC2053
	// aiMode   - 0 : Normal 30p, 1 : normal 60p
	// aiOption - 0 : OFF, 1 : DOL 2P

	UINT i;
	static BYTE bInitSet = 0x1;
	
	if(bInitSet){
		// Sensor H/W Reset
		GpioSetLo(GPIO_SRSTN);	WaitUs(10000);		GpioSetHi(GPIO_SRSTN);	WaitUs(10000);
		
		// I2C Check
		for(i=0; i<10; i++) {
			if(i2c_write(SENS_GLXCOR_DEV,1,0) == 0) {
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
	
	for (i=0; i<gTblSensEa; i++)	    { SetSens(gwTblSens0[i][0], gwTblSens0[i][1]);}
	
	WaitUs(500000);
	
	SetSens(0xfe,0x01);
	SetSens(0x60, 0x00); // Black Offset

	//Shutter Speed Max
	gnAeNorMax = gnInModeVtw-AE_SHTMAX_OFST;
	
}

void ISPM Sens(AE_SHTLw)(UINT val)
{	
	SetSens(0xfe,0x00);
	
	SetSens(0x03, val>>8&0xff);
	SetSens(0x04, val&0xff   );
}

void ISPM Sens(AE_AGCw)(UINT val)
{
	// Result of below val
	SetSens(0xfe,0x00);

	val = MINMAX(val, 0x0, (UINT)gTblAgain_Ea);
	
    SetSens(0x00b4,gbRegValTable[val][0]);
    SetSens(0x00b3,gbRegValTable[val][1]);
    SetSens(0x00b8,gbRegValTable[val][2]);
    SetSens(0x00b9,gbRegValTable[val][3]);

    SetSens(0x00b1,gbRegValTable[val][4]);
    SetSens(0x00b2,gbRegValTable[val][5]);
}

void ISPM Sens(AE_FREQw)(UINT val, UINT val1)
{	
	UNUSED_ARG(val);
	SetSens(0xfe,0x00);
	SetSens(0x05, (val1>>8)&0xff);
	SetSens(0x06, (val1>>0)&0xff);
	
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

// -----------------------------------------------------------
// AE Shutter Driver

WORD ISPM AeSHT(int aiVal, UINT anManual, UINT anManualVal)
{	// Shutter driver
//** Sensor Spec : Shutter 1 to 1123(VMAX-2)

	UINT	nMok = gnInModeVtw;
	UINT	nRem = 0;
	UINT	nShtMax = 0;
	static	UINT	gnShtFlt = 0;
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

	AE_SHTLw(nRem+AE_SHTMIN_OFST);
	
	DebugDisp(gbAeDebugOn, Dec, "SHT_int__d", 1, 24, nRem		)
	DebugDisp(gbAeDebugOn, Dec, "SHT_flt__d", 2, 24, gnShtFlt	)

	return ((WORD)nRem);
}

// -----------------------------------------------------------
// AE AGC Driver
void ISPM AeAGC(int aiVal)
{	// AGC driver
	static int	giAgc;
	const UINT nAGC_LMT = AE_GAIN_DENORMAL(AE_SENS_AGC_LMT_NOR); // 1000
	static UINT nLWdrGain;
	static UINT nDgc;
	
	UINT nDgcMok = 0;
	UINT nDgcMod = 0;
	
    giAgc = AE_GAIN_DENORMAL(aiVal);
	giAgc = MINMAX(giAgc, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR);
	
	if(giAgc <= (int)nAGC_LMT){											//AGC+HCG
		giAeLWdrGain = 0x0;
	}
	else{
		LibAeGainIntp0125((aiVal-AE_SENS_AGC_LMT_NOR), &nLWdrGain);			//Calculation 0.125dB
		giAeLWdrGain = (int)nLWdrGain;									
		giAgc = nAGC_LMT;												//AGC MAX
	}
	
	giAgc = MINMAX(giAgc, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA));

	nDgcMok = (giAgc/3);
	nDgcMod = (giAgc%3);
	
	nDgcMok = MINMAX(nDgcMok, 0x0, (UINT)gTblAgain_Ea);
	
	if (gnAeState!=0)	{
		if(giAgc <= 0)		nDgc = 0;
		else				LibAePrgainIntp0125(nDgcMod);

		LibAePrgain_L(MAX(nDgc, 0x100));
		AE_AGCw(nDgcMok);
	}
	
	DebugDisp(gbAeDebugOn, Hex, "AGC_____", 5, 24, giAgc )
	DebugDisp(gbAeDebugOn, Hex, "WDR_GAIN", 6, 24, (giAeLWdrGain))

}


// -----------------------------------------------------------------------------------------
// AWB
// -----------------------------------------------------------------------------------------

const s64 glMtxCf[9][6] =		{	// RT, Y 350
								{	      50304422536601LL,	        163419321307LL,	          9923716864LL,	           286075292LL,	           261092501LL,	           140609973LL},
								{	      85128713584717LL,	        293987741356LL,	        241952629218LL,	           439332458LL,	           283446134LL,	           151012133LL},
								{	      60257794627444LL,	        211382431960LL,	        215905487704LL,	           491238763LL,	           394517673LL,	           306416632LL},
								{	    -101517422927499LL,	       -339738621128LL,	       -253517293557LL,	          -535045758LL,	          -385982816LL,	          -203616496LL},
								{	     258918245160611LL,	        949293710553LL,	        650432751049LL,	          1506575553LL,	          1119610267LL,	           518732430LL},
								{	      -5547255265037LL,	       -177153431475LL,	        199952924091LL,	           112096755LL,	          -261632027LL,	           439208867LL},
								{	     -48657120283770LL,	       -146086719837LL,	       -145701611951LL,	          -217078590LL,	          -140684227LL,	          -113732866LL},
								{	      29541538780814LL,	        -13248861287LL,	        -37524597333LL,	          -246737761LL,	          -178818877LL,	          -206739673LL},
								{	     462384391477911LL,	       2169059459135LL,	       2051483657287LL,	          4918445902LL,	          3273954954LL,	          2835068590LL}
								};

// -----------------------------------------------------------------------------------------
// MIRROR & FLIP
// -----------------------------------------------------------------------------------------

BYTE gbMirrFlg=0;
void Sens(SENS_MIRw)(BYTE abOn){
	SetSens(0xfe,0x00);
	SetSens(0x17,((GetSens(0x17)&(~ValSft_L00(BitMask_01)))|ValSft_L00(abOn)));
	gbMirrFlg=abOn;
}

void Sens(SENS_FLPw)(BYTE abOn){
	SetSens(0xfe,0x00);
	SetSens(0x17,((gbMirrFlg&(~ValSft_L01(BitMask_01)))|ValSft_L01(abOn)));
//	SetSens(0x17,((GetSens(0x17)&(~ValSft_L01(BitMask_01)))|ValSft_L01(abOn)));
	
	static BYTE bBuf=0xf;
	static UINT nVLOCKL_POS;
	if(bBuf==0xf) {nVLOCKL_POS=VLOCKL_POSr;}
	
	if(bBuf!=abOn) {
		VLOCKL_POSw(nVLOCKL_POS+abOn);
		bBuf=abOn;
	}
}


