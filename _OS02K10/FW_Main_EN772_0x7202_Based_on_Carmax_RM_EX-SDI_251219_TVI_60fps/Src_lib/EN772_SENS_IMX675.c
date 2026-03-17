/* **************************************************************************
 File Name	:	EN772_SENS_IMX675.c
 Description:	EN775 - IMX675 device driver
 Designer	:	Lee, GyuHong
 Date		:	22. 07. 07
 Copyright �� DCOD Co., Ltd. All Rights Reserved.
*************************************************************************** */

#undef model_Sens
#include "../Src/dev.h"
#define model_Sens	SENS_IMX675
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
#define AE_GAIN_UNIT_OVR		(27*3)																			// Sensor gain extended step
#define AE_GAIN_UNIT_OVR2		(0)	    																		// ISP gain extended step
#define AE_HCG_IN_TIMING		(0x1E*3)

const int Sens(AE_GAIN_TOTAL) = (((AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR)*(0.1/0.1));
const int Sens(AE_GAIN_TOTAL2) = 0;

#define AE_GAIN_DENORMAL(val)	(ifdiv8(val*(int)(1.0f*256.f)))		// 171211 LH : int floating

#endif

#define AE_HSS_FLT_EA		(sizeof(gbAeHssFltTbl))
#define AE_SHT_TBL_EA		(sizeof(gnAeShtTbl)/8)


// -----------------------------------------------------------------------------------------
// LINE-WDR Configuration
// -----------------------------------------------------------------------------------------

//#define AE_LWDR_2P_RHS1			(  15)
#define AE_LWDR_2P_RHS1		 	((gbInModeRes==0)?(45):(29))				// RHS1 (gbInModeRes==0 ? 4M30 : 5M)

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

	#define MODE_IMX675_891MBPS			1
	// Ver1.0
	// Chip ID 0x2
	const WORD gwTblSens0[][5] = {
									//ADDR	 Nor 4M30P	DOL 4M30P	Nor 5M	DOL 5M 12.5P,20,25
									{0x3014,	0x03,	0x03,		0x03,	0x03},	//INCK_SEL(0:74.25M,1:37.125M,2:72M,3:27M,4:24M)
									
								#if(MODE_IMX675_891MBPS)
									{0x3015,	0x05,	0x05,		0x05,	0x05},	//DATARATE_SEL(4 : 1188Mbps, 6 : 720Mbps, 7 : 594Mbps)
								#else
									{0x3015,	0x04,	0x04,		0x04,	0x04},	//DATARATE_SEL(4 : 1188Mbps, 6 : 720Mbps, 7 : 594Mbps)
								#endif
								
									{0x3018,	0x04,	0x04,		0x04,	0x04},	//WINMODE(0:all-pixel)
									{0x301A,	0x00,	0x01,		0x00,	0x01},	//WDMODE(HDR mode)
									{0x301B,	0x00,	0x00,		0x00,	0x00},	//ADDMODE
									{0x301C,	0x00,	0x01,		0x00,	0x01},	//THIN_V_EN(ONLY DOL)
									{0x301E,	0x01,	0x01,		0x01,	0x01},	//VCMODE(ONLY DOL)
									{0x3020,	0x00,	0x00,		0x00,	0x00},	//HREVERSE
									{0x3021,	0x00,	0x00,		0x00,	0x00},	//VREVERSE
									{0x3022,	0x01,	0x00,		0x01,	0x00},	//ADBIT
									{0x3023,	0x01,	0x00,		0x01,	0x00},	//MDBIT                   	
								                             		            
									{0x3030,	0x00,	0x00,		0x00,	0x00},	//FDG_SEL(LCG,HCG)
									{0x3031,	0x00,	0x00,		0x00,	0x00},	//FDG_SEL1
									{0x3032,	0x00,	0x00,		0x00,	0x00},	//FDG_SEL2
									{0x303C,	0x00,	0x00,		0x00,	0x00},	//PIX_HST(CROP MODE)
									{0x303D,	0x00,	0x00,		0x00,	0x00},	//PIX_HST(CROP MODE)
									{0x303E,	0x30,	0x10,		0x30,	0x30},	//PIX_HWIDTH(CROP MODE)		// 0x30 is No Guaranty
									{0x303F,	0x0A,	0x0A,		0x0A,	0x0A},	//PIX_HWIDTH(CROP MODE)
									{0x3040,	0x03,	0x03,		0x03,	0x03},	//LANEMODE				// 4lane
									{0x3044,	0xFC,	0xFC,		0x00,	0x00},	//PIX_VST
									{0x3045,	0x00,	0x00,		0x00,	0x00},	//PIX_VST
//									{0x3046,	0xB4,	0xB4,		0xAC,	0xAC},	//PIX_VWIDTH
									{0x3046,	0xB4,	0xB4,		0xA0,	0xA0},	//PIX_VWIDTH
									{0x3047,	0x05,	0x05,		0x07,	0x07},	//PIX_VWIDTH
								                               	            
									{0x30A4,	0xAA,	0xAA,		0xAA,	0xAA},	//XVSOUTSEL, XHSOUTSEL
//									{0x30A6,	0x00,	0x00,		0x00,	0x00},	//XVS_DRV, XHS_DRV
									{0x30A6,	0x0F,	0x0F,		0x0F,	0x0F},	//XVS_DRV, XHS_DRV				// Sensor Slave Mode

									{0x30CC,	0x00,	0x00,		0x00,	0x00},	//XVSLNG
									{0x30CD,	0x00,	0x00,		0x00,	0x00},	//XHSLNG
									{0x30CE,	0x02,	0x02,		0x02,	0x02},	//
									{0x30DC,	0x00,	0x00,		0x00,	0x00},	//BLKLEVEL
									{0x30DD,	0x00,	0x00,		0x00,	0x00},	//BLKLEVEL
									{0x3148,	0x00,	0x00,		0x00,	0x00},	//
									                           	            
									{0x3400,	0x01,	0x01,		0x01,	0x01},	//GAIN_PGC_FIDMD
									{0x3460,	0x22,	0x22,		0x22,	0x22},	
									{0x3492,	0x08,	0x08,		0x08,	0x08},	
									{0x3B1D,	0x17,	0x17,		0x17,	0x17},	
									{0x3B44,	0x3F,	0x3F,		0x3F,	0x3F},	
									{0x3B60,	0x03,	0x03,		0x03,	0x03},	    
									{0x3C03,	0x04,	0x04,		0x04,	0x04},
									{0x3C04,	0x04,	0x04,		0x04,	0x04},
									                           	            
									                           	            
									{0x3C0A,	0x1F,	0x03,		0x1F,	0x03},	
									{0x3C0B,	0x1F,	0x03,		0x1F,	0x03},	
									{0x3C0C,	0x1F,	0x03,		0x1F,	0x03},	
									{0x3C0D,	0x1F,	0x03,		0x1F,	0x03},	
									{0x3C0E,	0x1F,	0x03,		0x1F,	0x03},	
									{0x3C0F,	0x1F,	0x03,		0x1F,	0x03},	

									{0x3C30,	0x73,	0x73,		0x73,	0x73},	
									{0x3C3C,	0x20,	0x20,		0x20,	0x20},	
									{0x3C7C,	0xB9,	0xB9,		0xB9,	0xB9},	
									{0x3C7D,	0x01,	0x01,		0x01,	0x01},	
									{0x3C7E,	0xB7,	0xB7,		0xB7,	0xB7},	
									{0x3C7F,	0x01,	0x01,		0x01,	0x01},	//06h:NOMAL mode, 05h:Clear HDR mode
									{0x3CB0,	0x00,	0x00,		0x00,	0x00},	
									{0x3CB2,	0xFF,	0xFF,		0xFF,	0xFF},	
									{0x3CB3,	0x03,	0x03,		0x03,	0x03},	
									{0x3CB4,	0xFF,	0xFF,		0xFF,	0xFF},	
									{0x3CB5,	0x03,	0x03,		0x03,	0x03},	
									{0x3CBA,	0xFF,	0xFF,		0xFF,	0xFF},	
									{0x3CBB,	0x03,	0x03,		0x03,	0x03},	
									{0x3CC0,	0xFF,	0xFF,		0xFF,	0xFF},	
									{0x3CC1,	0x03,	0x03,		0x03,	0x03},	
									{0x3CC2,	0x00,	0x00,		0x00,	0x00},	
									{0x3CC6,	0xFF,	0xFF,		0xFF,	0xFF},	
									{0x3CC7,	0x03,	0x03,		0x03,	0x03},	
									{0x3CC8,	0xFF,	0xFF,		0xFF,	0xFF},	
									{0x3CC9,	0x03,	0x03,		0x03,	0x03},	
									{0x3E00,	0x1E,	0x1E,		0x1E,	0x1E},	
									{0x3E02,	0x04,	0x04,		0x04,	0x04},	
									{0x3E03,	0x00,	0x00,		0x00,	0x00},	
									{0x3E20,	0x04,	0x04,		0x04,	0x04},	
									{0x3E21,	0x00,	0x00,		0x00,	0x00},	
									{0x3E22,	0x1E,	0x1E,		0x1E,	0x1E},	
									{0x3E24,	0xBA,	0xBA,		0xBA,	0xBA},	
									{0x3E72,	0x85,	0x85,		0x85,	0x85},	
									{0x3E76,	0x0C,	0x0C,		0x0C,	0x0C},	
									{0x3E77,	0x01,	0x01,		0x01,	0x01},	
									{0x3E7A,	0x85,	0x85,		0x85,	0x85},	
									{0x3E7E,	0x1F,	0x1F,		0x1F,	0x1F},	
									{0x3E82,	0xA6,	0xA6,		0xA6,	0xA6},	
									{0x3E86,	0x2D,	0x2D,		0x2D,	0x2D},	
									{0x3EE2,	0x33,	0x33,		0x33,	0x33},	
									{0x3EE3,	0x03,	0x03,		0x03,	0x03},	
									{0x4490,	0x07,	0x07,		0x07,	0x07},	
									{0x4494,	0x19,	0x19,		0x19,	0x19},	
									{0x4495,	0x00,	0x00,		0x00,	0x00},	
									{0x4496,	0xBB,	0xBB,		0xBB,	0xBB},	
									{0x4497,	0x00,	0x00,		0x00,	0x00},	
									{0x4498,	0x55,	0x55,		0x55,	0x55},	
									{0x449A,	0x50,	0x50,		0x50,	0x50},	
									{0x449C,	0x50,	0x50,		0x50,	0x50},	
									{0x449E,	0x50,	0x50,		0x50,	0x50},	
									{0x44A0,	0x3C,	0x3C,		0x3C,	0x3C},	
									{0x44A2,	0x19,	0x19,		0x19,	0x19},	
									{0x44A4,	0x19,	0x19,		0x19,	0x19},	
									{0x44A6,	0x19,	0x19,		0x19,	0x19},	
									{0x44A8,	0x4B,	0x4B,		0x4B,	0x4B},	
									{0x44AA,	0x4B,	0x4B,		0x4B,	0x4B},	
									{0x44AC,	0x4B,	0x4B,		0x4B,	0x4B},	
									{0x44AE,	0x4B,	0x4B,		0x4B,	0x4B},	
									{0x44B0,	0x3C,	0x3C,		0x3C,	0x3C},	
									{0x44B2,	0x19,	0x19,		0x19,	0x19},	
									{0x44B4,	0x19,	0x19,		0x19,	0x19},	
									{0x44B6,	0x19,	0x19,		0x19,	0x19},	
									{0x44B8,	0x4B,	0x4B,		0x4B,	0x4B},	
									{0x44BA,	0x4B,	0x4B,		0x4B,	0x4B},	
									{0x44BC,	0x4B,	0x4B,		0x4B,	0x4B},	
									{0x44BE,	0x4B,	0x4B,		0x4B,	0x4B},	
									{0x44C0,	0x3C,	0x3C,		0x3C,	0x3C},	
									{0x44C2,	0x19,	0x19,		0x19,	0x19},	
									{0x44C4,	0x19,	0x19,		0x19,	0x19},	
									{0x44C6,	0x19,	0x19,		0x19,	0x19},	
									{0x44C8,	0xF0,	0xF0,		0xF0,	0xF0},	
									{0x44CA,	0xEB,	0xEB,		0xEB,	0xEB},	
									{0x44CC,	0xEB,	0xEB,		0xEB,	0xEB},	
									{0x44CE,	0xE6,	0xE6,		0xE6,	0xE6},	
									{0x44D0,	0xE6,	0xE6,		0xE6,	0xE6},	
									{0x44D2,	0xBB,	0xBB,		0xBB,	0xBB},	
									{0x44D4,	0xBB,	0xBB,		0xBB,	0xBB},	
									{0x44D6,	0xBB,	0xBB,		0xBB,	0xBB},	
									{0x44D8,	0xE6,	0xE6,		0xE6,	0xE6},	
									{0x44DA,	0xE6,	0xE6,		0xE6,	0xE6},	
									{0x44DC,	0xE6,	0xE6,		0xE6,	0xE6},	
									{0x44DE,	0xE6,	0xE6,		0xE6,	0xE6},	
									{0x44E0,	0xE6,	0xE6,		0xE6,	0xE6},
									{0x44E2,    0xBB,   0xBB,  		0xBB,   0xBB},
									{0x44E4,    0xBB,   0xBB,  		0xBB,   0xBB},
									{0x44E6,    0xBB,   0xBB,  		0xBB,   0xBB},
									{0x44E8,    0xE6,   0xE6,  		0xE6,   0xE6},
									{0x44EA,    0xE6,   0xE6,  		0xE6,   0xE6},
									{0x44EC,    0xE6,   0xE6,  		0xE6,   0xE6},
									{0x44EE,    0xE6,   0xE6,  		0xE6,   0xE6},
									{0x44F0,    0xE6,   0xE6,  		0xE6,   0xE6},
									{0x44F2,    0xBB,   0xBB,  		0xBB,   0xBB},
									{0x44F4,    0xBB,   0xBB,  		0xBB,   0xBB},
									{0x44F6,    0xBB,   0xBB,  		0xBB,   0xBB},
									{0x4538,    0x15,   0x15,  		0x15,   0x15},
									{0x4539,    0x15,   0x15,  		0x15,   0x15},
									{0x453A,    0x15,   0x15,  		0x15,   0x15},
									{0x4544,    0x15,   0x15,  		0x15,   0x15},
									{0x4545,    0x15,   0x15,  		0x15,   0x15},
									{0x4546,    0x15,   0x15,  		0x15,   0x15},
									{0x4550,    0x10,   0x10,  		0x10,   0x10},
									{0x4551,    0x10,   0x10,  		0x10,   0x10},
									{0x4552,    0x10,   0x10,  		0x10,   0x10},
									{0x4553,    0x10,   0x10,  		0x10,   0x10},
									{0x4554,    0x10,   0x10,  		0x10,   0x10},
									{0x4555,    0x10,   0x10,  		0x10,   0x10},
									{0x4556,    0x10,   0x10,  		0x10,   0x10},
									{0x4557,    0x10,   0x10,  		0x10,   0x10},
									{0x4558,    0x10,   0x10,  		0x10,   0x10},
									{0x455C,    0x10,   0x10,  		0x10,   0x10},
									{0x455D,    0x10,   0x10,  		0x10,   0x10},
									{0x455E,    0x10,   0x10,  		0x10,   0x10},
									{0x455F,    0x10,   0x10,  		0x10,   0x10},
									{0x4560,    0x10,   0x10,  		0x10,   0x10},
									{0x4561,    0x10,   0x10,  		0x10,   0x10},
									{0x4562,    0x10,   0x10,  		0x10,   0x10},
									{0x4563,    0x10,   0x10,  		0x10,   0x10},
									{0x4564,    0x10,   0x10,  		0x10,   0x10},
									{0x4569,    0x01,   0x01,  		0x01,   0x01},
									{0x456A,    0x01,   0x01,  		0x01,   0x01},
									{0x456B,    0x06,   0x06,  		0x06,   0x06},
									{0x456C,    0x06,   0x06,  		0x06,   0x06},
									{0x456D,    0x06,   0x06,  		0x06,   0x06},
									{0x456E,    0x06,   0x06,  		0x06,   0x06},
									{0x456F,    0x06,   0x06,  		0x06,   0x06},
									{0x4570,    0x06,   0x06,  		0x06,   0x06}
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
					((aiWdrMode==_NORMAL)?(_12BIT):(_10BIT)),\
					/* 3210, 10, 0 */\
					(_3210),\
					/* Word Count */\
					(	(aiWdrMode==_NORMAL)?	((aiResMode==MD_4M_FPS_25_30)?(0xF48):(0xF48)):\
						(aiWdrMode==_HDR_LINE)?	((aiResMode==MD_4M_FPS_25_30)?(0xC94):(0xCBC)):\
												(/*(aiResMode==MD_4M_FPS_25_30)?(0xCBC):(0xCC6)*/0xCBC)),\
					/* MIPI Line information or Virtual channel mode */\
					_MIPI_VC,\
					aiWdrMode);

	//ISP Master Mode Only
	if(SENS_MST){
	}
	else{
		SMCK_DIVw(0x3);	
		SS_WAVEw(((gbInModeRes==MD_5M_FPS_20)&&((aiWdrMode==_HDR_LINE)||(aiWdrMode==_HDR_CLR)))?(0x1):(0x0));		// IMX675 5M 20fps DOL Only

		SS_HTWw(gnInModeHtw-2);
		SS_VTWw(gnInModeVtw-1);
	}
	
}

void LibInitSens(int aiMode, int aiOption)
{	// IMX675
	// aiMode (Normal)  - 0 : 4M30P, 1 : 5M12.5P, 2 : 5M20P, 3 : 5M25P
	// aiOption (DOL)	- 0 : OFF, 	 1 : ON (DOL2P), 0x10 : Clear HDR
	LibBrkCond();
	
	UINT i;
	static BYTE bModeIndx = 0x0;

	SENS_MST = /*((gbModel_ISP==LIB_ISP_EN805)||(gbModel_ISP==LIB_ISP_EN805M))*/1;

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

	bModeIndx = ((aiMode==MD_5M_FPS_125)||(aiMode==MD_5M_FPS_20)/*||(aiMode==MD_5M_FPS_25)*/)?(1):(0);
	LibRdesIsp(bModeIndx, aiOption);

	if(SENS_MST)	SetSens(0x30A6, 0x00);
	else			SetSens(0x30A6, 0x0F);
	
	SetSens(0x3000, 0x1);	WaitUs(3000);		// standby
	SetSens(0x3002, 0x1);	WaitUs(3000);		// xmaster stop
	SetSens(0x3001, 0x1);						// REG Hold
	SetSens(0x3003, 0x1);						// SW reset

	for (i=0; i<gTblSensEa; i++)	{	SetSens(gwTblSens0[i][0], (BYTE)gwTblSens0[i][1+(bModeIndx*2)+((aiOption&0x1)?(1):(0))]);}

	gnAeNorMax = gnInModeVtw-AE_SHTMAX_OFST;

	// Clear HDR (Based Setting Normal Mode)
	if(aiOption==0x10){
		// 10bit Mode
	#if(MODE_IMX675_891MBPS)
		SetSens(0x3015, 0x05);				// DATARATE 	(891Mbps)
	#else
		SetSens(0x3015, 0x04);				// DATARATE 	(1188Mbps)
	#endif
		SetSens(0x301A, 0x08);				// WDMODE		(Clear HDR)
	
	#if(0)
		SetSens(0x3022, 0x01);				// ADBIT		(0 : 10bit, 1 : 12bit)
		SetSens(0x3023, 0x01);				// MDBIT		(0 : 10bit, 1 : 12bit)
	#else
		SetSens(0x3022, 0x00);				// ADBIT		(0 : 10bit, 1 : 12bit)
		SetSens(0x3023, 0x00);				// MDBIT		(0 : 10bit, 1 : 12bit)
	#endif

		SetSens(0x3030, 0x02);				// FDG_SEL0
		SetSens(0x3040, 0x03);				// LANEMODE : 4lane

	#if(0)
		SetSens(0x3C0A, 0x1F);				// 			(0x3 : 10bit, 0x1F : 12bit)
		SetSens(0x3C0B, 0x1F);				// 
		SetSens(0x3C0C, 0x1F);				// 
		SetSens(0x3C0D, 0x1F);				// 
		SetSens(0x3C0E, 0x1F);				// 
		SetSens(0x3C0F, 0x1F);				// 
	#else
		SetSens(0x3C0A, 0x03);				// 			(0x3 : 10bit, 0x1F : 12bit)
		SetSens(0x3C0B, 0x03);				// 
		SetSens(0x3C0C, 0x03);				// 
		SetSens(0x3C0D, 0x03);				// 
		SetSens(0x3C0E, 0x03);				// 
		SetSens(0x3C0F, 0x03);				// 
	#endif

		SetSens(0x4498, 0x5A);				// 			(Clear HDR)
		
		SetSens(0x44A8, 0x50);				// 			(Clear HDR)
		SetSens(0x44AA, 0x50);				// 			(Clear HDR)
		SetSens(0x44AC, 0x50);				// 			(Clear HDR)
		SetSens(0x44AE, 0x46);				// 			(Clear HDR)
		SetSens(0x44B0, 0x46);				// 			(Clear HDR)
		
		SetSens(0x44B8, 0x50);				// 			(Clear HDR)
		SetSens(0x44BA, 0x50);				// 			(Clear HDR)
		SetSens(0x44BC, 0x50);				// 			(Clear HDR)
		SetSens(0x44BE, 0x46);				// 			(Clear HDR)
		SetSens(0x44C0, 0x46);				// 			(Clear HDR)
		
		SetSens(0x4569, 0x00);				// 			(Clear HDR)
		SetSens(0x456A, 0x00);				// 			(Clear HDR)
		SetSens(0x456B, 0x04);				// 			(Clear HDR)
		SetSens(0x456C, 0x04);				// 			(Clear HDR)
		SetSens(0x456D, 0x04);				// 			(Clear HDR)
		SetSens(0x456E, 0x04);				// 			(Clear HDR)
		SetSens(0x456F, 0x04);				// 			(Clear HDR)
		SetSens(0x4570, 0x04);				// 			(Clear HDR)	

		gbAeWdrComp		= 0x0;
	}
	
	if (aiOption==1) {			// DOL 2P		

		gnAeLWdrMaxL0	= (AE_LWDR_2P_L0_MAX - AE_LWDR_2P_RHS1)-AE_LWDR_2P_L0MIN_OFST;		
		gnAeLWdrMaxS1	= (AE_LWDR_2P_S1_MAX)-AE_LWDR_2P_S1MIN_OFST;		

		gnAeLWdrMinL0	= (AE_LWDR_2P_L0_MIN - AE_LWDR_2P_RHS1)-AE_LWDR_2P_L0MIN_OFST;		
		gnAeLWdrMinS1	= (AE_LWDR_2P_S1_MIN)-AE_LWDR_2P_S1MIN_OFST;		

		gbAeWdrComp		= 0x1;
		// RHS1
		SetSensBst(0x3060, (AE_LWDR_2P_RHS1&0xFFFFF), 3);
	}

	SetSens(0x3003, 0x0);					// SW reset OFF
	SetSens(0x3001, 0x0);					// REG Hold OFF
	SetSens(0x3000, 0x0);	WaitUs(30000);	// standby cancel
	SetSens(0x3002, 0x0);	WaitUs(20000);	// xmaster	
	
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
}

void ISPM Sens(AE_DGCw)(UINT val)
{
	UNUSED_ARG(val);
}

void ISPM Sens(AE_FREQw)(UINT val, UINT val1)
{
	UNUSED_ARG(val);

	if(SENS_MST){
		//Sensor Master Mode
		SetSensBst(0x3028, (val&0xFFFFF), 3);
		SetSensBst(0x302C, (val1&0xFFFF), 2);
	}
	else{
		//ISP Master Mode
		//	SS_HTWw(val1-2);
		//	SS_VTWw(val-1);
	}
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
	const BYTE bShtMinOfst = (AE_SHTMIN_OFST);
	const BYTE bLwdrOfst = (gbModeWdrOn_L)?(1):(0);

	for(i=1; i<anTblEa; i++) {
		if (aiVal<(int)gnAeShtTbl[i][0]) {
			nShtFlt = LibUtlInterp1D (aiVal, gnAeShtTbl[i-1][0], gnAeShtTbl[i][0], gnAeShtTbl[i-1][1], gnAeShtTbl[i][1]);
			nShtInt = nShtFlt>>7;

//		if(gbModeWdrOn_L || gbModeWdrOn_CLR){
		if(gbModeWdrOn_L /*|| gbModeWdrOn_CLR*/){
			nShtIntbuf = ((nShtInt-bShtMinOfst)/bMultpl)+bOfst;
			nShtFltbuf = ((nShtIntbuf-bOfst)*bMultpl)+bShtMinOfst;
			if (nShtInt<anFltEa)		nShtFlt = LibUtlInterp1D (nShtFlt, (nShtFltbuf<<7), ((nShtFltbuf+bMultpl)<<7), 0, gbAeHssFltTbl[nShtIntbuf+bLwdrOfst]);
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
#define CHDR_AGIN_LG_MIN	0x0
#define CHDR_AGIN_LG_MAX	0x50

#define CHDR_AGIN_HG_MIN	0x1E
#define CHDR_AGIN_HG_MAX	0xB4

#define	CHDR_AGIN_END		(180*3)				// Max. 54dB

void ISPM AE_AGC_LGw(UINT val)
{
	// Control Range : 0x0 ~ 0x50
	UINT nAgainLG = 0x0;
	nAgainLG = MINMAX(val, CHDR_AGIN_LG_MIN, CHDR_AGIN_LG_MAX);

	SetSensBst(0x3070, (nAgainLG&0x07FF), 2);
}

void ISPM AE_AGC_HGw(UINT val)
{
	// Control Range : 0x30 ~ 0xB4
	UINT nAgainHG = 0x0;
	nAgainHG = MINMAX(val, CHDR_AGIN_HG_MIN, CHDR_AGIN_HG_MAX);

	SetSensBst(0x304C, (nAgainHG&0x07FF), 2);
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
		AE_AGC_LGw(0x0);
		AE_AGC_HGw(0x0);
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

void ISPM AeAGC_CHDR(int aiVal)
{	// AGC driver
	static int	giAgc;
	static int  iChk = 1;
	static UINT nDgc;
	static UINT nDgcBuf;

	UINT nDgcMok = 0;	
	UINT nDgcMod = 0;

	giAgc = AE_GAIN_DENORMAL(aiVal);
	giAgc = MINMAX(giAgc, 0, CHDR_AGIN_END);

	nDgcMok = (giAgc/3);	
	nDgcMod = (giAgc%3);
	
	if (gnAeState!=0){
		if(giAgc <= 0)		nDgc = 0;		
		else				nDgc = LibAePrgainIntp(nDgcMod);		

		LibAePrgain_L(MAX(nDgcBuf, 0x100));
		LibAePrgain_S(MAX(nDgcBuf, 0x100));

		AE_AGC_LGw((BYTE)nDgcMok);
		AE_AGC_HGw((BYTE)nDgcMok);

		nDgcBuf = nDgc;
	}

	if(DR_FIX_MODE){
		float f_AGAIN_HG = 9.0f;
		float f_HCG = 12.0f;
		
		float32 fh_AGAIN_HG = TOFLOAT32(f_AGAIN_HG);				// Aanalog Gain : 10.2dB
		float32 fh_HCG = TOFLOAT32(f_HCG);							// HCG : 15.3dB
		
		gnAgc_L = (UINT)_ftoi(_fmul(fh_AGAIN_HG,fh_HCG));	// AGC 9.0dB * HCG 15.3dB
		gnAgc_S1 = /*MAX(PAR02,1);*/0x10;
			
		// Determined Dynamic Range (L/S Ratio)
		SetSens(0x3030, ((0xFC&GetSens(0x3030))|(iChk<<1)));				// Long Image - HCG ON 
	}
	
	DebugDisp(gbAeDebugOn, Hex, "AGC_____", 5, 24, (iChk<<16)|nDgcMok )
	DebugDisp(gbAeDebugOn, Hex, "DGC_____", 6, 24, (nDgcBuf))
}
#endif

// -----------------------------------------------------------------------------------------
// AWB
// -----------------------------------------------------------------------------------------

const s64 glMtxCf[9][6] =		{	// RT, Y 350
								{		  73203998720212LL, 		148533282734LL, 		-30707198081LL, 		   445942830LL, 		   325386744LL, 		   214102389LL},
								{		  24888888005710LL, 		-12523542761LL, 	   -137124784910LL, 		  -566176556LL, 		  -160472802LL, 		  -375153888LL},
								{		 303679546929103LL, 	   1672193634912LL, 	   1676388097219LL, 		  4577739941LL, 		  2608851099LL, 		  2666998067LL},
								{		-174921265833992LL, 	   -662094176162LL, 	   -279524607849LL, 		  -664025873LL, 		  -851503238LL, 		  -204775568LL},
								{		 473743932270042LL, 	   1901387446677LL, 		898810665399LL, 		  2374852550LL, 		  2451627195LL, 		   614052118LL},
								{		-211689665626970LL, 	  -1095329937358LL, 		315703280301LL, 		   281969073LL, 		 -1413282465LL, 		  1508958644LL},
								{		   2744237475863LL, 		 85314798423LL, 		 44484374156LL, 		   360553106LL, 		   186192857LL, 			13709632LL},
								{		-283092505264028LL, 	  -1815783847263LL, 	  -1491505051855LL, 		 -4300852038LL, 		 -2787061510LL, 		 -2059152816LL},
								{		1732161801332960LL, 	   9614784138614LL, 	   8046186512256LL, 		 21945768746LL, 		 14193569217LL, 		 11450259544LL}
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

