/* **************************************************************************
 File Name	:	EN772_SENS_IMX662.c
 Description	:	EN772 - IMX662 device driver
 Designer		:	Lee, GyuHong
 Date		:	22. 06. 09.
 Copyright �� DCOD Co., Ltd. All Rights Reserved.
*************************************************************************** */

#undef model_Sens
#include "../Src/dev.h"
#define model_Sens	SENS_IMX662
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


#define AE_SHTMAX_OFST	4					//shutter full		
#define AE_SHTMIN_OFST	1					//shutter min
#define AE_SHTMAX		(nMok-AE_SHTMAX_OFST)

#if(0)
#define AE_GAIN_UNIT_MAX		(240)	    																	// Sensor gain step by Unit
#define AE_GAIN_UNIT_EA			(1)																				// Sensor gain Unit EA
#define AE_GAIN_UNIT_OVR		(50)																			// Sensor gain extended step
#define AE_GAIN_UNIT_OVR2		(0)	    																		// ISP gain extended step
#define AE_HCG_IN_TIMING		(0x22)

const int Sens(AE_GAIN_TOTAL) = (((AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR)*(0.3/0.1));
const int Sens(AE_GAIN_TOTAL2) = 0;

//#define AE_GAIN_DENORMAL		(0.34)
#define AE_GAIN_DENORMAL(val)	(ifdiv8(val*(int)(0.34f*256.f)))		// 171211 LH : int floating

#else
#define AE_GAIN_UNIT_MAX		(240*3)	    																	// Sensor gain step by Unit
#define AE_GAIN_UNIT_EA			(1)																				// Sensor gain Unit EA
#define AE_GAIN_UNIT_OVR		(52*3)																			// Sensor gain extended step
#define AE_GAIN_UNIT_OVR2		(0)	    																		// ISP gain extended step
#define AE_HCG_IN_TIMING		(0x22*3)

const int Sens(AE_GAIN_TOTAL) = (((AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR)*(0.1/0.1));
const int Sens(AE_GAIN_TOTAL2) = 0;

#define AE_GAIN_DENORMAL(val)	(ifdiv8(val*(int)(1.0f*256.f)))		// 171211 LH : int floating

#endif

#define AE_HSS_FLT_EA		(sizeof(gbAeHssFltTbl))
#define AE_SHT_TBL_EA		(sizeof(gnAeShtTbl)/8)


// -----------------------------------------------------------------------------------------
// LINE-WDR Configuration
// -----------------------------------------------------------------------------------------

//#define AE_LWDR_2P_RHS1			((gbInModeRes==MD_2M_FPS_125_20)?(19):(31))
#define AE_LWDR_2P_RHS1			(  39)

#define AE_LWDR_FSC				(gnInModeVtw*2)

#define AE_LWDR_2P_L0MIN_OFST	(	5)
#define AE_LWDR_2P_L0MAX_OFST	(	2)

#define AE_LWDR_2P_S1MIN_OFST	(	5)
#define AE_LWDR_2P_S1MAX_OFST	(	2)

#define AE_LWDR_2P_L0_MAX		(AE_LWDR_FSC - AE_LWDR_2P_L0MAX_OFST)			// L0 Max shutter line at DOL 2P
#define AE_LWDR_2P_L0_MIN		(AE_LWDR_2P_RHS1 + AE_LWDR_2P_L0MIN_OFST)		// L0 Max shutter line at DOL 2P

#define AE_LWDR_2P_S1_MAX		(AE_LWDR_2P_RHS1 - AE_LWDR_2P_S1MAX_OFST)		// S1 Max shutter line at DOL 2P
#define AE_LWDR_2P_S1_MIN		(AE_LWDR_2P_S1MIN_OFST)							// S1 Max shutter line at DOL 2P

//#define AE_SENS_AGC_LMT			(AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA+AE_GAIN_UNIT_OVR)	// LWDR Mode AGC Limit 
//#define AE_SENS_AGC_LMT_NOR		( 300)											// LWDR Mode AGC Limit 
//#define AE_SENS_AGC_LMT_WDR		( 600)											// LWDR Mode AGC Limit (Analog Gain : 300 * 0.1 = 30dB)

#if(0)
// -----------------------------------------------------------------------------------------
// Clear HDR Configuration
// -----------------------------------------------------------------------------------------
#define AE_CHDR_SHTMAX_OFST		(	8)					//shutter full		
#define AE_CHDR_SHTMIN_OFST		(	2)					//shutter min
#define AE_CHDR_SHTMAX			(nMok-AE_CHDR_SHTMAX_OFST)
#endif

// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------
// initial

	#define MODE_IMX662_594MBPS			1				// Changed 2Lane to 4Lane
	// Chip ID 0x2
	const WORD gwTblSens0[][4] = {
									//ADDR	 Nor 2M30P	DOL 2P	Nor 2M60P
									{0x3014,	0x01,	0x01,	0x01},	//INCK_SEL(0:74.25M,1:37.125M,2:72M,3:27M,4:24M)
								
								#if(MODE_IMX662_594MBPS)
									{0x3015,	0x07,	0x07,	0x07},	//DATARATE_SEL(4 : 1188Mbps, 7 : 594Mbps)
								#else
									{0x3015,	0x07,	0x04,	0x07},	//DATARATE_SEL(4 : 1188Mbps, 7 : 594Mbps)
								#endif

									{0x3018,	0x00,	0x00,	0x00},	//WINMODE(0:all-pixel)
									{0x301A,	0x00,	0x01,	0x00},	//WDMODE(HDR mode)
									{0x301B,	0x00,	0x00,	0x00},	//ADDMODE
									{0x301C,	0x00,	0x01,	0x00},	//THIN_V_EN(ONLY DOL)
									{0x301E,	0x01,	0x01,	0x01},	//VCMODE(ONLY DOL)
									{0x3020,	0x00,	0x00,	0x00},	//HREVERSE
									{0x3021,	0x00,	0x00,	0x00},	//VREVERSE
									{0x3022,	0x01,	0x01,	0x01},	//ADBIT
									{0x3023,	0x01,	0x01,	0x01},	//MDBIT
										                     	    
									{0x3028,	0xE2,	0xE2,	0xE2},	//VMAX	//model_VTW_1250
									{0x3029,	0x04,	0x04,	0x04},	//VMAX	//model_VTW_1250
									{0x302A,	0x00,	0x00,	0x00},	//VMAX	//model_VTW_1250		
									{0x302C,	0xBC,	0xDE,	0xDE},	//HMAX	//model_VTW_1250
									{0x302D,	0x07,	0x03,	0x03},	//HMAX	//model_VTW_1250
                                                             	    
								#if(0)                       	    
									{0x3028,	0x65,	0x65,	0xE2},	//VMAX	//1125
									{0x3029,	0x04,	0x04,	0x04},	//VMAX	//1125
									{0x302A,	0x00,	0x00,	0x00},	//VMAX	//1125
                                                             	    
									{0x302C,	0x98,	0x4c,	0xDE},	//HMAX	//1125
									{0x302D,	0x08,	0x04,	0x03},	//HMAX	//1125
								#endif                       	    
								                             	    
									{0x3030,	0x00,	0x00,	0x00},	//FDG_SEL(LCG,HCG)
									{0x3031,	0x00,	0x00,	0x00},	//FDG_SEL1
									{0x3032,	0x00,	0x00,	0x00},	//FDG_SEL2
									{0x303C,	0x00,	0x00,	0x00},	//PIX_HST(CROP MODE)
									{0x303D,	0x00,	0x00,	0x00},	//PIX_HST(CROP MODE)
									{0x303E,	0x90,	0x90,	0x90},	//PIX_HWIDTH(CROP MODE)
									{0x303F,	0x07,	0x07,	0x07},	//PIX_HWIDTH(CROP MODE)
							
								#if(MODE_IMX662_594MBPS)
									{0x3040,	0x03,	0x03,	0x03},	//LANEMODE				// 4lane
								#else
									{0x3040,	0x01,	0x01,	0x03},	//LANEMODE			// Normal : 2lane, WDR : 4lane
								#endif
								
									{0x3044,	0x00,	0x00,	0x00},	//PIX_VST
									{0x3045,	0x00,	0x00,	0x00},	//PIX_VST
									{0x3046,	0x4C,	0x4C,	0x4C},	//PIX_VWIDTH
									{0x3047,	0x04,	0x04,	0x04},	//PIX_VWIDTH
									{0x3050,	0x06,	0x06,	0x06},	//SHR0
									{0x3051,	0x00,	0x00,	0x00},	//SHR0
									{0x3052,	0x00,	0x00,	0x00},	//SHR0
									{0x3054,	0x0E,	0x0E,	0x0E},	//SHR1
									{0x3055,	0x00,	0x00,	0x00},	//SHR1
									{0x3056,	0x00,	0x00,	0x00},	//SHR1
									{0x3058,	0x8A,	0x8A,	0x8A},	//SHR2
									{0x3059,	0x01,	0x01,	0x01},	//SHR2
									{0x305A,	0x00,	0x00,	0x00},	//SHR2
									{0x3060,	0x16,	0x16,	0x16},	//RHS1
									{0x3061,	0x01,	0x01,	0x01},	//RHS1
									{0x3062,	0x00,	0x00,	0x00},	//RHS1
									{0x3064,	0xC4,	0xC4,	0xC4},	//RHS2
									{0x3065,	0x0C,	0x0C,	0x0C},	//RHS2
									{0x3066,	0x00,	0x00,	0x00},	//RHS2
									{0x3070,	0x00,	0x00,	0x00},	//GAIN
									{0x3071,	0x00,	0x00,	0x00},	//GAIN
									{0x3072,	0x00,	0x00,	0x00},	//GAIN_1
									{0x3073,	0x00,	0x00,	0x00},	//GAIN_1
									{0x3074,	0x00,	0x00,	0x00},	//GAIN_2
									{0x3075,	0x00,	0x00,	0x00},	//GAIN_2
									{0x3081,	0x00,	0x00,	0x00},	//EXP_GAIN(Clear HDR)
									{0x30A4,	0xAA,	0xAA,	0xAA},	//XVSOUTSEL, XHSOUTSEL
									{0x30A6,	0x00,	0x00,	0x00},	//XVS_DRV, XHS_DRV
									{0x30CC,	0x00,	0x00,	0x00},	//XVSLNG
									{0x30CD,	0x00,	0x00,	0x00},	//XHSLNG
									{0x30DC,	0x00,	0x00,	0x00},	//BLKLEVEL
									{0x30DD,	0x00,	0x00,	0x00},	//BLKLEVEL
									{0x3400,	0x01,	0x00,	0x01},	//GAIN_PGC_FIDMD
									{0x3444,	0xAC,	0xAC,	0xAC},	
                                                             	    
//									{0x3458,	0x00,	0x00,	0x00},
									{0x3460,	0x21,	0x21,	0x21},	
									{0x3492,	0x08,	0x08,	0x08},	
									{0x3A50,	0xFF,	0xFF,	0xFF},	//62h:AD10bit, FFh:AD12bit
									{0x3A51,	0x03,	0x03,	0x03},	//01h:AD10bit, 03h:AD12bit
									{0x3A52,	0x00,	0x00,	0x00},	//19h:AD10bit, 00h:AD12bit
									{0x3B00,	0x39,	0x39,	0x39},	
									{0x3B23,	0x2D,	0x2D,	0x2D},	
									{0x3B45,	0x04,	0x04,	0x04},	
									{0x3C0A,	0x1F,	0x1F,	0x1F},	
									{0x3C0B,	0x1E,	0x1E,	0x1E},	
									{0x3C38,	0x21,	0x21,	0x21},	
									{0x3C40,	0x06,	0x06,	0x06},	//06h:NOMAL mode, 05h:Clear HDR mode
									{0x3C44,	0x00,	0x00,	0x00},	
									{0x3CB6,	0xD8,	0xD8,	0xD8},	
									{0x3CC4,	0xDA,	0xDA,	0xDA},	
									{0x3E24,	0x79,	0x79,	0x79},	
									{0x3E2C,	0x15,	0x15,	0x15},	
									{0x3EDC,	0x2D,	0x2D,	0x2D},	
									{0x4498,	0x05,	0x05,	0x05},	
									{0x449C,	0x19,	0x19,	0x19},	
									{0x449D,	0x00,	0x00,	0x00},	
									{0x449E,	0x32,	0x32,	0x32},	
									{0x449F,	0x01,	0x01,	0x01},	
									{0x44A0,	0x92,	0x92,	0x92},	
									{0x44A2,	0x91,	0x91,	0x91},	
									{0x44A4,	0x8C,	0x8C,	0x8C},	
									{0x44A6,	0x87,	0x87,	0x87},	
									{0x44A8,	0x82,	0x82,	0x82},	
									{0x44AA,	0x78,	0x78,	0x78},	
									{0x44AC,	0x6E,	0x6E,	0x6E},	
									{0x44AE,	0x69,	0x69,	0x69},	
									{0x44B0,	0x92,	0x92,	0x92},	
									{0x44B2,	0x91,	0x91,	0x91},	
									{0x44B4,	0x8C,	0x8C,	0x8C},	
									{0x44B6,	0x87,	0x87,	0x87},	
									{0x44B8,	0x82,	0x82,	0x82},	
									{0x44BA,	0x78,	0x78,	0x78},	
									{0x44BC,	0x6E,	0x6E,	0x6E},	
									{0x44BE,	0x69,	0x69,	0x69},	
									{0x44C0,	0x7F,	0x7F,	0x7F},	
									{0x44C1,	0x01,	0x01,	0x01},	
									{0x44C2,	0x7F,	0x7F,	0x7F},	
									{0x44C3,	0x01,	0x01,	0x01},	
									{0x44C4,	0x7A,	0x7A,	0x7A},	
									{0x44C5,	0x01,	0x01,	0x01},	
									{0x44C6,	0x7A,	0x7A,	0x7A},	
									{0x44C7,	0x01,	0x01,	0x01},	
									{0x44C8,	0x70,	0x70,	0x70},	
									{0x44C9,	0x01,	0x01,	0x01},	
									{0x44CA,	0x6B,	0x6B,	0x6B},	
									{0x44CB,	0x01,	0x01,	0x01},	
									{0x44CC,	0x6B,	0x6B,	0x6B},	
									{0x44CD,	0x01,	0x01,	0x01},	
									{0x44CE,	0x5C,	0x5C,	0x5C},	
									{0x44CF,	0x01,	0x01,	0x01},	
									{0x44D0,	0x7F,	0x7F,	0x7F},	
									{0x44D1,	0x01,	0x01,	0x01},	
									{0x44D2,	0x7F,	0x7F,	0x7F},	
									{0x44D3,	0x01,	0x01,	0x01},	
									{0x44D4,	0x7A,	0x7A,	0x7A},	
									{0x44D5,	0x01,	0x01,	0x01},	
									{0x44D6,	0x7A,	0x7A,	0x7A},	
									{0x44D7,	0x01,	0x01,	0x01},	
									{0x44D8,	0x70,	0x70,	0x70},	
									{0x44D9,	0x01,	0x01,	0x01},	
									{0x44DA,	0x6B,	0x6B,	0x6B},	
									{0x44DB,	0x01,	0x01,	0x01},	
									{0x44DC,	0x6B,	0x6B,	0x6B},	
									{0x44DD,	0x01,	0x01,	0x01},	
									{0x44DE,	0x5C,	0x5C,	0x5C},	
									{0x44DF,	0x01,	0x01,	0x01},	
									{0x4534,	0x1C,	0x1C,	0x1C},	
									{0x4535,	0x03,	0x03,	0x03},	
									{0x4538,	0x1C,	0x1C,	0x1C},	
									{0x4539,	0x1C,	0x1C,	0x1C},	
									{0x453A,	0x1C,	0x1C,	0x1C},	
									{0x453B,	0x1C,	0x1C,	0x1C},	
									{0x453C,	0x1C,	0x1C,	0x1C},	
									{0x453D,	0x1C,	0x1C,	0x1C},	
									{0x453E,	0x1C,	0x1C,	0x1C},	
									{0x453F,	0x1C,	0x1C,	0x1C},	
									{0x4540,	0x1C,	0x1C,	0x1C},	
									{0x4541,	0x03,	0x03,	0x03},	
									{0x4542,	0x03,	0x03,	0x03},	
									{0x4543,	0x03,	0x03,	0x03},	
									{0x4544,	0x03,	0x03,	0x03},	
									{0x4545,	0x03,	0x03,	0x03},	
									{0x4546,	0x03,	0x03,	0x03},	
									{0x4547,	0x03,	0x03,	0x03},	
									{0x4548,	0x03,	0x03,	0x03},	
									{0x4549,	0x03,	0x03,	0x03}	
								};

const UINT gTblSensEa		= numberof(gwTblSens0);

// -----------------------------------------------------------------------------------------
// AE
// -----------------------------------------------------------------------------------------
	const BYTE 	gbAeHssFltTbl[]   = {
									0,		//0
									60,		//1
									35,		//2
									24,		//3
									19,		//4
									15,		
									13,
									11,
									10,
									9,
									8,
									7,
									6,
									6,
									5,
									5,
									5,
									4,
									4,
									4,
									4,
									4,
									3,
									3,
									3,
									3,
									3,
									3,
									3,
									2,
									2,
									2,
									2,
									2,
									2,
									2,
									2,
									2,
									2,
									2,
									2,
									2,
									2,
									1,
									1,
									1,
									1
									};
	
	const UINT	gnAeShtTbl[][2]   = {
									{0	,	128 	},
									{14	,	150 	},
									{28	,	176 	},
									{42	,	207 	},
									{56	,	243 	},
									{70	,	286 	},
									{84	,	336 	},
									{98	,	395 	},
									{112 ,	464 	},
									{126 ,	546 	},
									{140 ,	641 	},
									{154 ,	753 	},
									{168 ,	885 	},
									{182 ,	1040	},
									{196 ,	1222	},
									{210 ,	1436	},
									{224 ,	1687	},
									{238 ,	1982	},
									{252 ,	2329	},
									{266 ,	2736	},
									{280 ,	3215	},
									{294 ,	3777	},
									{308 ,	4438	},
									{322 ,	5214	},
									{336 ,	6126	},
									{350 ,	7197	},
									{364 ,	8456	},
									{378 ,	9935	},
									{392 ,	11673	},
									{406 ,	13715	},
									{420 ,	16114	},
									{434 ,	18932	},
									{448 ,	22243	},
									{462 ,	26134	},
									{476 ,	30705	},
									{490 ,	36075	},
									{504 ,	42384	},
									{518 ,	49797	},
									{532 ,	58507	},
									{546 ,	68740	},
									{560 ,	80762	},
									{574 ,	94887	},
									{588 ,	111483	},
									{602 ,	130981	},
									{616 ,	153889	},
									{630 ,	180804	},
									{644 ,	212427	},
									{658 ,	249580	},
									{672 ,	293231	},
									{686 ,	344516	},
									{700 ,	404771	},
									{714 ,	475565	},
									{728 ,	558740	},
									{742 ,	656462	},
									{756 ,	771276	},
									{770 ,	906170	},
									{784 ,	1064657 },
									{798 ,	1250863 },
									{812 ,	1469636 },
									{826 ,	1726672 },
									{840 ,	2028663 },
									{854 ,	2383471 },
									{868 ,	2800334 },
									{882 ,	3290106 },
									{896 ,	3865538 },
									{910 ,	4541611 },
									{924 ,	5335928 },
									{938 ,	6269168 },
									{952 ,	7365631 },
									{966 ,	8653862 },
									{980 ,	10167401},
									{994 ,	11945655}
									};

#if(0)
	const UINT 	gnClrHdrAgainTbl[]   = {
									0x0	 ,
									0x17 ,
									0x2F ,
									0x46 ,
									0x5C ,
									0x73 ,
									0x89 ,
									0x9F ,
									0xB4 ,
									0xCA ,
									0xDF ,
									0xF4 ,
									0x108,
									0x11D,
									0x131,
									0x145,
									0x159,
									0x16C,
									0x17F,
									0x192,
									0x1A5,
									0x1B8,
									0x1CA,
									0x1DC,
									0x1EE,
									0x200,
									0x212,
									0x223,
									0x234,
									0x245,
									0x256,
									0x267,
									0x277,
									0x287,
									0x297,
									0x2A7,
									0x2B7,
									0x2C6,
									0x2D6,
									0x2E5,
									0x2F4,
									0x303,
									0x311,
									0x320,
									0x32E,
									0x33C,
									0x34A,
									0x358,
									0x365,
									0x373,
									0x380,
									0x38E,
									0x39B,
									0x3A7,
									0x3B4,
									0x3C1,
									0x3CD,
									0x3D9,
									0x3E6,
									0x3F2,
									0x3FE,
									0x409,
									0x415,
									0x420,
									0x42C,
									0x437,
									0x442,
									0x44D,
									0x458,
									0x463,
									0x46D,
									0x478,
									0x482,
									0x48C,
									0x496,
									0x4A0,
									0x4AA,
									0x4B4,
									0x4BE,
									0x4C7,
									0x4D1,
									0x4DA,
									0x4E3,
									0x4EC,
									0x4F5,
									0x4FE,
									0x507,
									0x510,
									0x518,
									0x521,
									0x529,
									0x532,
									0x53A,
									0x542,
									0x54A,
									0x552,
									0x55A,
									0x562,
									0x569,
									0x571,
									0x578,
									0x580,
									0x587,
									0x58E,
									0x596,
									0x59D,
									0x5A4,
									0x5AB,
									0x5B1,
									0x5B8,
									0x5BF,
									0x5C5,
									0x5CC,
									0x5D2,
									0x5D9,
									0x5DF,
									0x5E5,
									0x5EB,
									0x5F2,
									0x5F8,
									0x5FE,
									0x603,
									0x609,
									0x60F,
									0x615,
									0x61A,
									0x620,
									0x625,
									0x62B,
									0x630,
									0x636,
									0x63B,
									0x640,
									0x645,
									0x64A,
									0x64F,
									0x654,
									0x659,
									0x65E,
									0x663,
									0x667,
									0x66C,
									0x671,
									0x675,
									0x67A,
									0x67E,
									0x683,
									0x687,
									0x68B,
									0x690,
									0x694,
									0x698,
									0x69C,
									0x6A0,
									0x6A4,
									0x6A8,
									0x6AC,
									0x6B0,
									0x6B4,
									0x6B8,
									0x6BB,
									0x6BF,
									0x6C3,
									0x6C6,
									0x6CA,
									0x6CE,
									0x6D1,
									0x6D5,
									0x6D8,
									0x6DB,
									0x6DF,
									0x6E2,
									0x6E5,
									0x6E9,
									0x6EC,
									0x6EF,
									0x6F2,
									0x6F5,
									0x6F8,
									0x6FB,
									0x6FE,
									0x701,
									0x704,
									0x707,
									0x70A,
									0x70D,
									0x70F,
									0x712,
									0x715,
									0x718,
									0x71A,
									0x71D,
									0x71F,
									0x722,
									0x725,
									0x727,
									0x72A,
									0x72C,
									0x72E,
									0x731,
									0x733,
									0x736,
									0x738,
									0x73A,
									0x73C,
									0x73F,
									0x741,
									0x743,
									0x745,
									0x747,
									0x749,
									0x74C,
									0x74E,
									0x750,
									0x752,
									0x754,
									0x756,
									0x758,
									0x75A,
									0x75B,
									0x75D,
									0x75F,
									0x761,
									0x763,
									0x765,
									0x766,
									0x768,
									0x76A,
									0x76C,
									0x76D,
									0x76F,
									0x771,
									0x772,
									0x774,
									0x776,
									0x777,
									0x779,
									0x77A,
									0x77C,
									0x77D,
									0x77F,
									0x780,
									0x782,
									0x783,
									0x785,
									0x786,
									0x787,
									0x789,
									0x78A,
									0x78B,
									0x78D,
									0x78E,
									0x78F,
									0x791,
									0x792,
									0x793,
									0x795,
									0x796,
									0x797,
									0x798,
									0x799,
									0x79B,
									0x79C,
									0x79D,
									0x79E,
									0x79F,
									0x7A0,
									0x7A1,
									0x7A2,
									0x7A3,
									0x7A5,
									0x7A6,
									0x7A7,
									0x7A8,
									0x7A9,
									0x7AA,
									0x7AB,
									0x7AC,
									0x7AD,
									0x7AE,
									0x7AE,
									0x7AF,
									0x7B0,
									0x7B1,
									0x7B2,
									0x7B3,
									0x7B4,
									0x7B5,
									0x7B6,
									0x7B6,
									0x7B7,
									0x7B8,
									0x7B9,
									0x7BA,
									0x7BB,
									0x7BB,
									0x7BC,
									0x7BD,
									0x7BE,
									0x7BE,
									0x7BF
									};

const UINT gTblHdrAgainEa		= numberof(gnClrHdrAgainTbl);
#endif

// -----------------------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------------------

void LibRdesIsp(int aiResMode, int aiWdrMode)
{	// MIPI RX Configuration

	UNUSED_ARG(aiResMode);

#if(MODE_IMX662_594MBPS)
	LibISPtoSENS_Intf(\
					/* MIPI or LVDS */\
					(MIPI),\
					/* 1, 2, 4 LANE */\
					(_4LANE),\
					/* 12BIT or 10BIT */\
					(_12BIT),\
					/* 3210, 10, 0 */\
					(_3210),\
					/* Word Count */\
					(((aiResMode==0)/*&&(aiWdrMode==MN_OFF)*/)?(0xB58):(0xB58)),\
					/* MIPI Line information or Virtual channel mode */\
					(_MIPI_VC),\
					(aiWdrMode));
#else
	LibISPtoSENS_Intf(\
					/* MIPI or LVDS */\
					(MIPI),\
					/* 1, 2, 4 LANE */\
					(((aiResMode==0)/*&&(aiWdrMode==MN_OFF)*/)?(_2LANE):(_4LANE)),\
					/* 12BIT or 10BIT */\
					(_12BIT),\
					/* 3210, 10, 0 */\
					(((aiResMode==0)/*&&(aiWdrMode==MN_OFF)*/)?(_10):(_3210)),\
					/* Word Count */\
					(((aiResMode==0)/*&&(aiWdrMode==MN_OFF)*/)?(0xB58):(0xB58)),\
					/* MIPI Line information or Virtual channel mode */\
					(_MIPI_VC),\
					(aiWdrMode));
#endif
	
}

void LibInitSens(int aiMode, int aiOption)
{	// IMX662
	// aiMode   - 0 : Normal 30p, 1 : normal 60p
	// aiOption - 0 : OFF, 1 : DOL 2P, 0x10 : Clear HDR

	UINT i;
	static BYTE bInitSet = 0x1;
	static BYTE bModeIndx = 0x0;

	if(bInitSet){		
		GpioSetLo(GPIO_SRSTN);	WaitUs(10000);		GpioSetHi(GPIO_SRSTN);	WaitUs(10000);
		
		for(i=0; i<10; i++) {
			
			if(i2c_write(SENS_SONY_DEV,1,0) == 0) {
				gbSensorOff = 0;
				TxStrNoIRQ("SI2C connected.", 0, 0);
				break;
			}
			
			WaitUs(1000);
		}
		if(gbSensorOff) {
			TxStrNoIRQ("SI2C not connected.", 0, 0);
		}
		bInitSet = 0x0;
	}

	bModeIndx = ((aiMode==MD_CVBS)||(aiMode==MD_2M_FPS_50_60))?(1):(0);
	LibRdesIsp(bModeIndx, aiOption);
	
	SetSens(0x3000, 0x1);	WaitUs(3000);		// standby
	SetSens(0x3002, 0x1);	WaitUs(3000);		// xmaster stop
	SetSens(0x3001, 0x1);						// REG Hold
	SetSens(0x3003, 0x1);						// SW reset

	for (i=0; i<gTblSensEa; i++)	{	SetSens(gwTblSens0[i][0], (BYTE)gwTblSens0[i][1+(bModeIndx*2)+((aiOption&0x1)?(1):(0))]);}

	// Clear HDR (Based Setting Normal Mode)
	if(aiOption==0x10){

	#if(MODE_IMX662_594MBPS)
		SetSens(0x3015, 0x07);				// DATARATE
	#else
		SetSens(0x3015, 0x04);				// DATARATE
	#endif
		SetSens(0x301A, 0x08);				// WDMODE
		SetSens(0x3030, 0x02);				// FDG_SEL0
		
	#if(MODE_IMX662_594MBPS)
		SetSens(0x3040, 0x03);				// LANEMODE : 4lane
	#else
		SetSens(0x3040, 0x01);				// LANEMODE : 2lane
	#endif

		SetSens(0x3460, 0x22);				//
		SetSens(0x3C40, 0x05);				// 

		SetSens(0x3069, 0x01);				//CHDR_GAIN_EN
	}
	else{
		SetSens(0x3069, 0x00);				//CHDR_GAIN_EN
	}
	
	SetSens(0x3003, 0x0);					// SW reset OFF
	SetSens(0x3001, 0x0);					// REG Hold OFF
	SetSens(0x3000, 0x0);	WaitUs(30000);	// standby cancel
	SetSens(0x3002, 0x0);	WaitUs(20000);	// xmaster

	gnAeNorMax = gnInModeVtw-AE_SHTMAX_OFST;

	if (aiOption==1) {			// DOL 2P		

		gnAeLWdrMaxL0	= (AE_LWDR_2P_L0_MAX - AE_LWDR_2P_RHS1)-AE_LWDR_2P_L0MIN_OFST;		
		gnAeLWdrMaxS1	= (AE_LWDR_2P_S1_MAX)-AE_LWDR_2P_S1MIN_OFST;		

		gnAeLWdrMinL0	= (AE_LWDR_2P_L0_MIN - AE_LWDR_2P_RHS1)-AE_LWDR_2P_L0MIN_OFST;		
		gnAeLWdrMinS1	= (AE_LWDR_2P_S1_MIN)-AE_LWDR_2P_S1MIN_OFST;		

		gbAeWdrComp		= 0x0;
		// RHS1
		SetSensBst(0x3060, (AE_LWDR_2P_RHS1&0xFFFFF), 3);
	}
	
}

void ISPM Sens(AE_SHTLw)(UINT val)
{
	SetSensBst(0x3050, (val&0xFFFFF), 3);
}

void ISPM Sens(AE_SHTSw)(UINT val)
{
	SetSensBst(0x3054, (val&0x1FFFF), 3);
}

void ISPM Sens(AE_AGCw)(UINT val)
{
	SetSensBst(0x3070, (val&0x07FF), 2);
	if(gbModeWdrOn_L)	SetSensBst(0x3072, (val&0x07FF), 2);
}

void ISPM Sens(AE_DGCw)(UINT val)
{
	UNUSED_ARG(val);
}

void ISPM Sens(AE_FREQw)(UINT val, UINT val1)
{
	UNUSED_ARG(val);

	SetSensBst(0x3028, (val&0xFFFFF), 3);
	SetSensBst(0x302C, (val1&0xFFFF), 2);
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
	
	// for DOL
	UINT	nShtFltbuf=0;
	UINT	nShtIntbuf=0;
	const BYTE bMultpl = 2;
	const BYTE bOfst = 1;
//	const BYTE bShtMinOfst = (gbModeWdrOn_L)?(AE_SHTMIN_OFST):(AE_CHDR_SHTMIN_OFST);
	const BYTE bShtMinOfst = AE_SHTMIN_OFST;
		
	for(i=1; i<anTblEa; i++) {
		if (aiVal<(int)gnAeShtTbl[i][0]) {
			nShtFlt = LibUtlInterp1D (aiVal, gnAeShtTbl[i-1][0], gnAeShtTbl[i][0], gnAeShtTbl[i-1][1], gnAeShtTbl[i][1]);
			nShtInt = nShtFlt>>7;

//		if(gbModeWdrOn_L || gbModeWdrOn_CLR){
		if(gbModeWdrOn_L /*|| gbModeWdrOn_CLR*/){
			nShtIntbuf = ((nShtInt-bShtMinOfst)/bMultpl)+bOfst;
			nShtFltbuf = ((nShtIntbuf-bOfst)*bMultpl)+bShtMinOfst;
			if (nShtInt<anFltEa)		nShtFlt = LibUtlInterp1D (nShtFlt, (nShtFltbuf<<7), ((nShtFltbuf+bMultpl)<<7), 0, gbAeHssFltTbl[nShtIntbuf]);
			else 						nShtFlt = 0;
		}
		else{
			if (nShtInt<anFltEa)		nShtFlt = LibUtlInterp1D (nShtFlt, (nShtInt<<7), (nShtInt<<7)+0x80, 0, gbAeHssFltTbl[nShtInt]);
			else 						nShtFlt = 0;
//			nShtFlt = MIN(nShtFlt, 0x80);
		}
			break;
		}
	}
	*apnShtFlt = nShtFlt;
	*apnShtInt = nShtInt;
}


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
		AE_AGCw(0x0);
	}
	
	LibAeShtIntp (aiVal, AE_SHT_TBL_EA, AE_HSS_FLT_EA, &gnShtFlt, &nShtInt);

#if(0)
	if (gnAeState==0)	{
		gnShtFlt = AE_GAIN_DENORMAL(gnShtFlt);
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

	AE_SHTLw(nShtMax-nRem+AE_SHTMAX_OFST);

	DebugDisp(gbAeDebugOn, Dec, "SHT_int__d", 1, 24, nRem		)
	DebugDisp(gbAeDebugOn, Dec, "SHT_flt__d", 2, 24, gnShtFlt	)

	return ((WORD)nRem);
}

void ISPM AeAGC(int aiVal)
{	// AGC driver
	static int	giAgc;
	static int  iChk;
	const UINT nAGC_LMT = AE_GAIN_DENORMAL(AE_SENS_AGC_LMT_NOR);
	static UINT nLWdrGain;
	static UINT nDgc;
	static UINT nDgcBuf;

	UINT nDgcMok = 0;	
	UINT nDgcMod = 0;

	giAgc = AE_GAIN_DENORMAL(aiVal);
	giAgc = MINMAX(giAgc, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR);

	if(giAgc <= (int)nAGC_LMT){											//AGC+HCG
		if ((giAgc-(AE_GAIN_UNIT_OVR+AE_HCG_IN_TIMING)) >= 0) {
			giAgc = giAgc - AE_GAIN_UNIT_OVR;
			iChk = 1;
		}
		else 	iChk = 0;

		giAeLWdrGain = 0x0;
	}

	else{
		if ((giAgc-(AE_GAIN_UNIT_OVR+AE_HCG_IN_TIMING)) >= 0) 		iChk = 1;
		
		LibAeGainIntp((aiVal-AE_SENS_AGC_LMT_NOR), &nLWdrGain);				//Calculation 0.1dB
		giAeLWdrGain = (int)nLWdrGain;									
		giAgc = (nAGC_LMT - AE_GAIN_UNIT_OVR);							//AGC MAX

	}

	giAgc = MINMAX(giAgc, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA));

	nDgcMok = (giAgc/3);	
	nDgcMod = (giAgc%3);
	
	if (gnAeState!=0){
		if(giAgc <= 0)		nDgc = 0;		
		else				nDgc = LibAePrgainIntp(nDgcMod);		

		LibAePrgain_L(MAX(nDgcBuf, 0x100));
		AE_AGCw((BYTE)nDgcMok);

		nDgcBuf = nDgc;
	}

	SetSens(0x3030, ((0xFC&GetSens(0x3030))|iChk));
	
	DebugDisp(gbAeDebugOn, Hex, "AGC_____", 5, 24, (iChk<<16)|nDgcMok )
	DebugDisp(gbAeDebugOn, Hex, "WDR_GAIN", 6, 24, (giAeLWdrGain))
}


// -------------------------------------------------------------------------------------
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
		AE_AGCw(0x0);
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


//	tgt_L  = (AE_LWDR_FSC - AE_LWDR_2P_L0MAX_OFST) - tgt_L + AE_LWDR_2P_L0MIN_OFST;
	tgt_L  = (AE_LWDR_FSC - AE_LWDR_2P_L0MAX_OFST) - tgt_L; 								// 191025 LGH : Shutter position offset
	tgt_L  = (tgt_L/2)*2;																	//must be controlled 2n
//	tgt_S1 = (AE_LWDR_2P_RHS1 - AE_LWDR_2P_S1MAX_OFST)- tgt_S1 + AE_LWDR_2P_S1MIN_OFST;
	tgt_S1 = (AE_LWDR_2P_RHS1 - AE_LWDR_2P_S1MAX_OFST)- tgt_S1; 							// 191025 LGH : Shutter position offset
	tgt_S1 = ((tgt_S1-1)/2)*2+1;															//must be controlled 2n+1


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
	static UINT nDgc;
	static UINT nDgcBuf;

	UINT nDgcMok = 0;	
	UINT nDgcMod = 0;

	const UINT nLWDR_AGC_LMT = AE_GAIN_DENORMAL(AE_SENS_AGC_LMT_WDR);
	
	giAgcL = AE_GAIN_DENORMAL(aiVal);
	giAgcL = MINMAX(giAgcL, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR);

	if(giAgcL <= (int)nLWDR_AGC_LMT){												//AGC+HCG
		if ((giAgcL-(AE_GAIN_UNIT_OVR+AE_HCG_IN_TIMING)) >= 0) {
			giAgcL = giAgcL - AE_GAIN_UNIT_OVR;
			iChk = 1;
		}
		else 	iChk = 0;

		giAeLWdrGain = 0x0;
	}

	else{
		if ((giAgcL-(AE_GAIN_UNIT_OVR+AE_HCG_IN_TIMING)) >= 0)		iChk = 1;
			
		LibAeGainIntp((aiVal-AE_SENS_AGC_LMT_WDR), &nLWdrGain);						//Calculation 0.1dB
		giAeLWdrGain = (int)nLWdrGain;									
		giAgcL = (nLWDR_AGC_LMT - AE_GAIN_UNIT_OVR);							//AGC MAX
	}
	
	giAgcL = MINMAX(giAgcL, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA));
	giAgcS1 = giAgcL;

	nDgcMok = (giAgcL/3);	
	nDgcMod = (giAgcL%3);
	
	if (gnAeState!=0){
		if(giAgcL <= 0)		nDgc = 0;		
		else				nDgc = LibAePrgainIntp(nDgcMod);		

		LibAePrgain_L(MAX(nDgcBuf, 0x100)); 	
		LibAePrgain_S(MAX(nDgcBuf, 0x100));
		
		AE_AGCw((BYTE)nDgcMok);

		nDgcBuf = nDgc;
	}

	SetSens(0x3030, ((0xFC&GetSens(0x3030))|iChk));
	SetSens(0x3031, ((0xFC&GetSens(0x3031))|iChk));
	
	DebugDisp(gbAeDebugOn, Hex, "AGC0____", 5, 24, (iChk<<16)|nDgcMok)
	DebugDisp(gbAeDebugOn, Hex, "WDR_GAIN", 6, 24, (giAeLWdrGain))
}

#if(0)
// -------------------------------------------------------------------------------------
// Clear HDR 

#define CHDR_AGIN_HG_MIN	0x587
#define	CHDR_AGIN_END		198

void ISPM CHDR_DGAIN0_HGw(UINT val)
{
	// 0x100 : x1
	// Digital Gain
	// Analog Gain >= x32 : 0x100h <= val <= FD9h
	UINT nDgain = 0x0;
	nDgain = MINMAX(val, 0x100, 0xFD9);
	
	SetSensBst(0x308C, (nDgain&0xFFFF), 2);	
}

void ISPM CHDR_AGAIN0_HGw(UINT val)
{
	// Analog Gain < x32 : 587h <= val <= 7BFh
	// Analog Gain >=x32 : 7BFh
	UINT nAgainHG = 0x0;
	nAgainHG = MINMAX(val, CHDR_AGIN_HG_MIN, 0x7BF);
	
	SetSensBst(0x309C, (nAgainHG&0xFFFF), 2);
}

void ISPM CHDR_AGAIN0_LGw(UINT val)
{
	// Analog Gain < x32 : 0h <= val <= 77Fh
	UINT nAgainLG = 0x0;
	nAgainLG = MINMAX(val, 0x0, 0x77F);
	
	SetSensBst(0x3094, (nAgainLG&0xFFFF), 2);
}



WORD ISPM AeSHT_CHDR(int aiVal)
{	// Shutter driver for Clear HDR
	// aiVal  : Long
	UINT	nMok = gnInModeVtw;
	UINT	nRem = 0;
	UINT	nShtMax = 0;
	static 	UINT	gnShtFlt = 0;
	UINT	nShtInt = 0;
	UINT	nShtL = 0;

	if (gnAeState==0){
		LibAePrgain_L(LibAePrgainIntp(gnShtFlt));
		LibAePrgain_S(LibAePrgainIntp(gnShtFlt));
		CHDR_AGAIN0_HGw(0x0);
		CHDR_AGAIN0_LGw(0x0);
	}
	
	LibAeShtIntp (aiVal, AE_SHT_TBL_EA, AE_HSS_FLT_EA, &gnShtFlt, &nShtInt);

    nMok 	= gnInModeVtw ;
	nShtMax = AE_CHDR_SHTMAX;
	nRem 	= MINMAX(nShtInt, AE_CHDR_SHTMIN_OFST, nShtMax);
	
	gnSht_L = nRem;
	gnSht_S1 = nRem;

	nShtL = nShtMax-nRem+AE_CHDR_SHTMAX_OFST;
	nShtL = ((nShtL-1)/2)*2+1;
		
	AE_SHTLw(nShtL);

	DebugDisp(gbAeDebugOn, Dec, "SHT_int__d", 1, 24, nRem		)
	DebugDisp(gbAeDebugOn, Dec, "SHT_flt__d", 2, 24, gnShtFlt	)

	return ((WORD)nRem);
}


#define	DR_FIX_MODE		1		// 0 : 
								//*1 : L/S Ratio Fixed

#if(0)
void ISPM AeAGC_CHDR(int aiVal)
{	// AGC driver
	static int	giAgc;
	static int  iChk = 1;
	const UINT nAGC_LMT = AE_GAIN_DENORMAL(AE_SENS_AGC_LMT_WDR);
	static UINT nLWdrGain;
	static UINT nDgc;
	static UINT nDgcBuf;

	UINT nDgcMok = 0;	
	UINT nDgcMod = 0;

	giAgc = AE_GAIN_DENORMAL(aiVal);
	giAgc = MINMAX(giAgc, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR);

	if(giAgc <= (int)nAGC_LMT){											//AGC
		giAeLWdrGain = 0x0;
	}

	else{
		LibAeGainIntp((aiVal-AE_SENS_AGC_LMT_NOR), &nLWdrGain);				//Calculation 0.1dB
		giAeLWdrGain = (int)nLWdrGain;									
		giAgc = (nAGC_LMT - AE_GAIN_UNIT_OVR);							//AGC MAX

	}

	giAgc = MINMAX(giAgc, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA));

	nDgcMok = (giAgc/3);	
	nDgcMod = (giAgc%3);
	
	if (gnAeState!=0){
		if(giAgc <= 0)		nDgc = 0;		
		else				nDgc = LibAePrgainIntp(nDgcMod);		

		LibAePrgain_L(MAX(nDgcBuf, 0x100));
		AE_AGCw((BYTE)nDgcMok);

		nDgcBuf = nDgc;
	}

	if(DR_FIX_MODE){
		const BYTE HCG = iChk*6;												// HCG 16dB = x6
		const BYTE EXP_GAIN = 2+1;											// EXP_GAIN 6dB = x2
		
		gnAgc_L = HCG*EXP_GAIN;												// HCG 16dB + EXP_GAIN 6dB
		gnAgc_S1 = 1;
			
		// Determined Dynamic Range (L/S Ratio)
		SetSens(0x3030, ((0xFC&GetSens(0x3030))|(iChk<<1)));				// Long Image - HCG ON 
		SetSens(0x3081, (EXP_GAIN/2));										// Long Image - EXP_GAIN (6dB)
	}
	
	DebugDisp(gbAeDebugOn, Hex, "AGC_____", 5, 24, (iChk<<16)|nDgcMok )
	DebugDisp(gbAeDebugOn, Hex, "WDR_GAIN", 6, 24, (giAeLWdrGain))
}

#else
// Clear HDR
// 4.1 Gain Direct Control Function
void ISPM AeAGC_CHDR(int aiVal)
{	// AGC driver
	static int	giAgc;
	static int  iChk = 1;
	static UINT nAgcHG;
	static UINT nAgcLG;
	static UINT nDgc;

	// 1step = 0.1dB
	giAgc = AE_GAIN_DENORMAL(aiVal);
	giAgc = MINMAX(giAgc, 1, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR);
	
	// Analog Gain Trigger Point x32
	// x32 = 30dB
	// 1step 0.1dB = 30/0.1 = 300step
	// 10.2dB = 102step
	
	if(giAgc < CHDR_AGIN_END){
		nAgcHG = gnClrHdrAgainTbl[(102+giAgc)];
		nAgcLG = gnClrHdrAgainTbl[giAgc];
		nDgc = 0x0;
	}
	else{
		nAgcHG = gnClrHdrAgainTbl[gTblHdrAgainEa-1];
		nAgcLG = gnClrHdrAgainTbl[CHDR_AGIN_END];
		nDgc = (giAgc-CHDR_AGIN_END);
	}
	
	nDgc = MAX(LibAePrgainIntp(nDgc), 0x100);
		
	if (gnAeState!=0){
		CHDR_AGAIN0_HGw(nAgcHG);
		CHDR_AGAIN0_LGw(nAgcLG);	
		
		CHDR_DGAIN0_HGw(nDgc);
	}

	if(DR_FIX_MODE){		
		
		float f_AGAIN_HG = 10.2f;
		float f_HCG = 15.3f;
		float f_EXP_GAIN = 6.0f;
		
		float32 fh_AGAIN_HG = TOFLOAT32(f_AGAIN_HG);				// Aanalog Gain : 10.2dB
		float32 fh_HCG = TOFLOAT32(f_HCG);					// HCG : 15.3dB
		float32 fh_EXP_GAIN = TOFLOAT32(f_EXP_GAIN);				// EXP Gain : 6dB
		
		gnAgc_L = (UINT)_ftoi(_fmul(_fmul(fh_AGAIN_HG,fh_HCG),fh_EXP_GAIN));	// AGC 10.2dB * HCG 15.3dB + EXP_GAIN 6dB
		gnAgc_S1 = /*MAX(PAR02,1);*/0x30;
			
		// Determined Dynamic Range (L/S Ratio)
		SetSens(0x3030, ((0xFC&GetSens(0x3030))|(iChk<<1)));				// Long Image - HCG ON 
		SetSens(0x3081, 0x1);												// Long Image - EXP_GAIN 0x1 : 6dB
	}
	
	DebugDisp(gbAeDebugOn, Hex, "AGC_HG__", 5, 24, nAgcHG )
	DebugDisp(gbAeDebugOn, Hex, "AGC_LG__", 6, 24, nAgcLG )
	DebugDisp(gbAeDebugOn, Hex, "DGC_____", 7, 24, nDgc )
}

#endif

#endif
// -----------------------------------------------------------------------------------------
// AWB
// -----------------------------------------------------------------------------------------

const s64 glMtxCf[9][6] =		{	// RT, Y 350
								{		  77789153573378LL, 		143198788617LL, 		 16018110560LL, 		   455533016LL, 		   285953583LL, 		   257511340LL},
								{		  39001661210694LL, 		 10938414072LL, 		 44010001521LL, 		  -122625505LL, 		   -97550618LL, 		   -75225239LL},
								{		  65784568001418LL, 		271648225004LL, 		277770402799LL, 		   784045392LL, 		   540042170LL, 		   575119022LL},
								{		 -61711801151792LL, 		-83187027365LL, 		-83905775924LL, 		   -75162975LL, 		   -46082292LL, 		   -22647559LL},
								{		 216713502550973LL, 		468501866012LL, 		403992769803LL, 		   761576340LL, 		   458523230LL, 		   310657481LL},
								{		 -32441428228565LL, 	   -185720548132LL, 		  5301143682LL, 		  -194405596LL, 		  -159044571LL, 		   253311895LL},
								{		  14113565714798LL, 		149740852435LL, 		 97756710782LL, 		   457300844LL, 		   282857740LL, 		   223090149LL},
								{		  -1402546190189LL, 	   -255516296194LL, 	   -211731724804LL, 		  -839893967LL, 		  -524591332LL, 		  -483553836LL},
								{		 399500168581251LL, 	   1922485067683LL, 	   2040315104372LL, 		  5491036804LL, 		  3194271876LL, 		  3675321505LL}
								};

// -----------------------------------------------------------------------------------------
// MIRROR & FLIP
// -----------------------------------------------------------------------------------------

void Sens(SENS_MIRw)(BYTE abOn) {
	SetSens(0x3020, ((GetSens(0x3020)&(~ValSft_L00(BitMask_01)))|ValSft_L00((abOn)&BitMask_01)));
}
void Sens(SENS_FLPw)(BYTE abOn) {
	SetSens(0x3021, ((GetSens(0x3021)&(~ValSft_L00(BitMask_01)))|ValSft_L00((abOn)&BitMask_01)));
}

