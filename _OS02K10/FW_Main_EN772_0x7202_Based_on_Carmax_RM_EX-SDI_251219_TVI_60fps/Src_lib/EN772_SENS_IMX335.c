/* **************************************************************************
 File Name	:	EN772_SENS_IMX335.c
 Description:	EN772 - IMX335 4M Sensor device driver
 Designer	:	Lee, Gyu Hong/ Lee, Hoon
 Date		:	17. 07. 13
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */
//180221 LGH : Sensor version ES

#undef model_Sens
#include "../Src/dev.h"
#define model_Sens	SENS_IMX335
#include "../Src/dev.h"
#include "SENS_Common.h"

// -----------------------------------------------------------------------------------------
// pre define & table
// -----------------------------------------------------------------------------------------

//#define gnTblIspModeSensor	Sens(gnTblIspModeSensor)

#define gwTblSens0			Sens(gwTblSens0)
#define gTblSensEa			Sens(gTblSensEa)

#define gbAeHssFltTbl		Sens(gbAeHssFltTbl)
#define gnAeShtTbl			Sens(gnAeShtTbl)

#define LibAeShtIntp		Sens(LibAeShtIntp)

extern BYTE gbInModeRes;

//#define AE_SHTMAX_OFST	1
//#define AE_SHTMIN_OFST	9
#define AE_SHTMAX_OFST	9
#define AE_SHTMIN_OFST	1

#define AE_SHTMAX		(nMok-AE_SHTMAX_OFST)

//#define AE_GAIN_UNIT_MAX		(240)  																		// Sensor gain step by Unit
#define AE_GAIN_UNIT_MAX		(720)  																		// Sensor gain step by Unit
#define AE_GAIN_UNIT_EA			(1)																			// Sensor gain Unit EA
#define AE_GAIN_UNIT_OVR		(0)																			// Sensor gain extended step
#define AE_GAIN_UNIT_OVR2		(0)    																		// ISP gain extended step

//const int Sens(AE_GAIN_TOTAL) = ((((AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR)+AE_GAIN_UNIT_OVR2)*3.0);
const int Sens(AE_GAIN_TOTAL) = ((((AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR)+AE_GAIN_UNIT_OVR2)*1.0);
const int Sens(AE_GAIN_TOTAL2) = 0;

//#define AE_GAIN_DENORMAL(val)	(ifdiv8(val*(int)(0.34f*256.f)))		// 171211 LH : int floating
#define AE_GAIN_DENORMAL(val)	(ifdiv8(val*(int)(1.0f*256.f)))		// 171211 LH : int floating

#define AE_HSS_FLT_EA		(sizeof(gbAeHssFltTbl))
#define AE_SHT_TBL_EA		(sizeof(gnAeShtTbl)/8)

// -----------------------------------------------------------------------------------------
// LINE-WDR Configuration
// -----------------------------------------------------------------------------------------

#define AE_LWDR_2P_RHS1		 	((gbInModeRes==0)?(90):(58))				// RHS1 (gbInModeRes==0 ? 4M30 : 5M)

#define AE_LWDR_FSC				(gnInModeVtw*2)

#define AE_LWDR_2P_L0MIN_OFST	(  18)
#define AE_LWDR_2P_L0MAX_OFST	(	4)

#define AE_LWDR_2P_S1MIN_OFST	(  18)
#define AE_LWDR_2P_S1MAX_OFST	(	4)

#define AE_LWDR_2P_L0_MAX		(AE_LWDR_FSC - AE_LWDR_2P_L0MAX_OFST)			// L0 Max shutter line at DOL 2P
#define AE_LWDR_2P_L0_MIN		(AE_LWDR_2P_RHS1 + AE_LWDR_2P_L0MIN_OFST)		// L0 Max shutter line at DOL 2P

#define AE_LWDR_2P_S1_MAX		(AE_LWDR_2P_RHS1 - AE_LWDR_2P_S1MAX_OFST)		// S1 Max shutter line at DOL 2P
#define AE_LWDR_2P_S1_MIN		(AE_LWDR_2P_S1MIN_OFST)							// S1 Max shutter line at DOL 2P

// -----------------------------------------------------------------------------------------
// initial

	// Sensor Master
	// MIPI 4 Lane
	// INCK : 27MHz

	const WORD gwTblSens0[][7] = {	//ADDR	 Nor 4M30P	Dol 4M30P	Nor 5M12.5P	Dol 5M12.5P	 Nor 5M20P	DOL 5M20P
									//0x30**
									{0x300c, 	0x42,	  0x42,		0x42,		0x42,		 0x42,		0x42},
									{0x300d, 	0x2e,	  0x2e,		0x2e,		0x2e,		 0x2e,		0x2e},
									{0x3018, 	0x04,	  0x04,		0x00,		0x00,		 0x00,		0x00},		// WINMODE : 4M-crop, others-all pixel
									
									{0x302c,	0x3e,	  0x3e, 	0x30,		0x30,		 0x30,		0x30},		// 190524 LGH : about Sensor Crop
									{0x302d,	0x00,	  0x00, 	0x00,		0x00,		 0x00,		0x00},		// 190524 LGH : about Sensor Crop
									{0x302e, 	0x20,	  0x20,		0x38,		0x38,		 0x38,		0x38},		// HNUM : cropping size H
									{0x302f, 	0x0a,	  0x0a,		0x0a,		0x0a,		 0x0a,		0x0a},

									{0x3048, 	0x00,	  0x01,		0x00,		0x01,		 0x00,		0x01},		// WDMODE : 1=DOL
									{0x3049, 	0x00,	  0x01,		0x00,		0x01,		 0x00,		0x01},		// WDSEL : 1=DOL2p
									{0x304a, 	0x03,	  0x04,		0x03,		0x04,		 0x03,		0x04},
									{0x304b, 	0x03,	  0x03,		0x03,		0x03,		 0x03,		0x03},
									{0x304c, 	0x14,	  0x13,		0x14,		0x13,		 0x14,		0x13},		// OPB_SIZE_V at DOL(VC mode)	// 180806 LH : DOL
									{0x304e, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x304f, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x3050, 	0x01,	  0x00,		0x01,		0x00,		 0x01,		0x00},		// ADBIT : 0=10b, 1=12b
									
//									{0x3056,	0x50,	  0xa8, 	0xac,		0xac,		 0xac,		0xac},		// Y_OUT_SIZE at DOL(VC mode)	// 180806 LH : DOL
//									{0x3057,	0x0b,	  0x05, 	0x07,		0x07,		 0x07,		0x07},		// "
									{0x3056,	0xa8,	  0xa8, 	0xac,		0xac,		 0xac,		0xac},		// Y_OUT_SIZE at DOL(VC mode)	// 180806 LH : DOL
									{0x3057,	0x05,	  0x05, 	0x07,		0x07,		 0x07,		0x07},		// "

									{0x3058, 	0x09,	  0x84,		0x09,		0x8c,		 0x09,		0x8c},		//  SHR0 : L 	// 180806 LH : DOL
									{0x3059, 	0x00,	  0x0b,		0x00,		0x0f,		 0x00,		0x0f},      //  "
									{0x305a, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},      //  "
									{0x305c, 	0x12,	  0xa6,		0x12,		0x12,		 0x12,		0x12},      //  SHR1 : S1
									{0x305d, 	0x00,	  0x0a,		0x00,		0x00,		 0x00,		0x00},      //  "
									{0x305e, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},      //  "
									{0x3060, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},      //  SHR2 : S2
									{0x3061, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},      //  "
									{0x3062, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},      //  "

//									{0x3068,	0xce,	  0x12, 	0xce,		0xa2,		 0xce,		0xa2},		//  RHS1
//									{0x3069,	0x00,	  0x03, 	0x00,		0x07,		 0x00,		0x07},		//  "
//									{0x306a,	0x00,	  0x00, 	0x00,		0x00,		 0x00,		0x00},		//  "

									{0x3072, 	0x28,	  0x28,		0x28,		0x28,		 0x28,		0x28},
									{0x3073, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
//									{0x3074, 	0xb0,	  0xb0,		0xb0,		0xb0,		 0xb0,		0xb0},
//									{0x3075, 	0x01,	  0x01,		0x00,		0x00,		 0x00,		0x00},
									{0x3074,	0xa8,	  0xa8, 	0xb0,		0xb0,		 0xb0,		0xb0},		// 190524 LGH : about Sensor Crop
									{0x3075,	0x02,	  0x02, 	0x00,		0x00,		 0x00,		0x00},		// 190524 LGH : about Sensor Crop
									{0x3076, 	0x50,	  0x50,		0x58,		0x58,		 0x58,		0x58},		// AREA3_WIDTH_1 : CROP V line= value/2		// 180806 LH : DOL
									{0x3077, 	0x0b,	  0x0b,		0x0f,		0x0f,		 0x0f,		0x0f},
									{0x30c6, 	0x12,	  0x12,		0x00,		0x00,		 0x00,		0x00},
									{0x30c7, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x30ce, 	0x64,	  0x64,		0x00,		0x00,		 0x00,		0x00},
									{0x30cf, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
//									{0x30d8, 	0xd0,	  0xd0,		0x4c,		0x4c,		 0x4c,		0x4c},
//									{0x30d9, 	0x0d,	  0x0d,		0x10,		0x10,		 0x10,		0x10},
									{0x30d8,	0xc8,	  0xc8, 	0x4c,		0x4c,		 0x4c,		0x4c},
									{0x30d9,	0x0e,	  0x0e, 	0x10,		0x10,		 0x10,		0x10},

									{0x30e8, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},		// L  GAIN
									{0x30e9, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},      // "
									{0x30ea, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},      // S1 GAIN
									{0x30eb, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},      // "
									{0x30ec, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},      // S2 GAIN
									{0x30ed, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},      // "

									//0x31**
									{0x314c, 	0x08,	  0xb0,		0x08,		0xb0,		 0x08,		0xb0},
									{0x314d, 	0x01,	  0x00,		0x01,		0x00,		 0x01,		0x00},
									{0x315a, 	0x06,	  0x02,		0x06,		0x02,		 0x06,		0x02},
									{0x3168, 	0x8f,	  0x8f,		0x8f,		0x8f,		 0x8f,		0x8f},
									{0x316a, 	0x7e,	  0x7e,		0x7e,		0x7e,		 0x7e,		0x7e},
									{0x3199, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
                                    {0x319d,    0x01,     0x00,     0x01,       0x00,        0x01,      0x00},      // MDBIT : 0=10b, 1=12b
									{0x319e, 	0x02,	  0x01,		0x02,		0x01,		 0x02,		0x01},
									{0x319f, 	0x01,	  0x01,		0x01,		0x01,		 0x01,		0x01},		// VCEN : 1=VCM mode
									{0x31a0, 	0x20,	  0x20,		0x20,		0x20,		 0x20,		0x20},		// XVS,XHS LOW Fixed
									{0x31a1, 	0x0F,	  0x0F,		0x0F,		0x0F,		 0x0F,		0x0F},		// XVS,XHS Slave mode (HiZ)
									{0x31d4, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x31d5, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x31d7, 	0x00,	  0x01,		0x00,		0x01,		 0x00,		0x01},		// XVSMSK

									//0x32**
//									{0x3200, 	0x01,	  0x01,		0x01,		0x01,		 0x01,		0x01},		// FGAINEN : each frame gain (0==valid)
                                    {0x3200,    0x01,     0x00,     0x01,       0x00,        0x01,      0x00},      // FGAINEN : each frame gain (0==valid)
									{0x3288, 	0x21,	  0x21,		0x21,		0x21,		 0x21,		0x21},
									{0x328a, 	0x02,	  0x02,		0x02,		0x02,		 0x02,		0x02},

									//0x33**
									{0x3300, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x3302, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x3303, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},

									//0x34**
									{0x3414, 	0x05,	  0x05,		0x05,		0x05,		 0x05,		0x05},
									{0x3416, 	0x18,	  0x18,		0x18,		0x18,		 0x18,		0x18},
                                    {0x341c, 	0x47,	  0xFF,		0x47,		0xFF,		 0x47,		0xFF},		// ADBIT1 (10bit : 0x1FF, 12bit : 0x047)
									{0x341d, 	0x00,	  0x01,		0x00,		0x01,		 0x00,		0x01},		// "
									
									//0x36**
									{0x3648, 	0x01,	  0x01,		0x01,		0x01,		 0x01,		0x01},		// Datasheet (Fixed)
									{0x364a, 	0x04,	  0x04,		0x04,		0x04,		 0x04,		0x04},		// "
									{0x364c, 	0x04,	  0x04,		0x04,		0x04,		 0x04,		0x04},		// "
									{0x3678, 	0x01,	  0x01,		0x01,		0x01,		 0x01,		0x01},		// "
									{0x367c, 	0x31,	  0x31,		0x31,		0x31,		 0x31,		0x31},		// "
									{0x367e, 	0x31,	  0x31,		0x31,		0x31,		 0x31,		0x31},		// "

									//0x37**
									{0x3706, 	0x10,	  0x10,		0x10,		0x10,		 0x10,		0x10},
									{0x3708, 	0x03,	  0x03,		0x03,		0x03,		 0x03,		0x03},
									{0x3714, 	0x02,	  0x02,		0x02,		0x02,		 0x02,		0x02},
									{0x3715, 	0x02,	  0x02,		0x02,		0x02,		 0x02,		0x02},
									{0x3716, 	0x01,	  0x01,		0x01,		0x01,		 0x01,		0x01},
									{0x3717, 	0x03,	  0x03,		0x03,		0x03,		 0x03,		0x03},
									{0x371c, 	0x3d,	  0x3d,		0x3d,		0x3d,		 0x3d,		0x3d},
									{0x371d, 	0x3f,	  0x3f,		0x3f,		0x3f,		 0x3f,		0x3f},
									{0x372c, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x372d, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x372e, 	0x46,	  0x46,		0x46,		0x46,		 0x46,		0x46},
									{0x372f, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x3730, 	0x89,	  0x89,		0x89,		0x89,		 0x89,		0x89},
									{0x3731, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x3732, 	0x08,	  0x08,		0x08,		0x08,		 0x08,		0x08},
									{0x3733, 	0x01,	  0x01,		0x01,		0x01,		 0x01,		0x01},
									{0x3734, 	0xfe,	  0xfe,		0xfe,		0xfe,		 0xfe,		0xfe},
									{0x3735, 	0x05,	  0x05,		0x05,		0x05,		 0x05,		0x05},
									{0x3740, 	0x02,	  0x02,		0x02,		0x02,		 0x02,		0x02},
									{0x375d, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x375e, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x375f, 	0x11,	  0x11,		0x11,		0x11,		 0x11,		0x11},
									{0x3760, 	0x01,	  0x01,		0x01,		0x01,		 0x01,		0x01},
									{0x3768, 	0x1b,	  0x1b,		0x1b,		0x1b,		 0x1b,		0x1b},
									{0x3769, 	0x1b,	  0x1b,		0x1b,		0x1b,		 0x1b,		0x1b},
									{0x376a, 	0x1b,	  0x1b,		0x1b,		0x1b,		 0x1b,		0x1b},
									{0x376b, 	0x1b,	  0x1b,		0x1b,		0x1b,		 0x1b,		0x1b},
									{0x376c, 	0x1a,	  0x1a,		0x1a,		0x1a,		 0x1a,		0x1a},
									{0x376d, 	0x17,	  0x17,		0x17,		0x17,		 0x17,		0x17},
									{0x376e, 	0x0f,	  0x0f,		0x0f,		0x0f,		 0x0f,		0x0f},
									{0x3776, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x3777, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x3778, 	0x46,	  0x46,		0x46,		0x46,		 0x46,		0x46},
									{0x3779, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x377a, 	0x89,	  0x89,		0x89,		0x89,		 0x89,		0x89},
									{0x377b, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x377c, 	0x08,	  0x08,		0x08,		0x08,		 0x08,		0x08},
									{0x377d, 	0x01,	  0x01,		0x01,		0x01,		 0x01,		0x01},
									{0x377e, 	0x23,	  0x23,		0x23,		0x23,		 0x23,		0x23},
									{0x377f, 	0x02,	  0x02,		0x02,		0x02,		 0x02,		0x02},
									{0x3780, 	0xd9,	  0xd9,		0xd9,		0xd9,		 0xd9,		0xd9},
									{0x3781, 	0x03,	  0x03,		0x03,		0x03,		 0x03,		0x03},
									{0x3782, 	0xf5,	  0xf5,		0xf5,		0xf5,		 0xf5,		0xf5},
									{0x3783, 	0x06,	  0x06,		0x06,		0x06,		 0x06,		0x06},
									{0x3784, 	0xa5,	  0xa5,		0xa5,		0xa5,		 0xa5,		0xa5},
									{0x3788, 	0x0f,	  0x0f,		0x0f,		0x0f,		 0x0f,		0x0f},
									{0x378a, 	0xd9,	  0xd9,		0xd9,		0xd9,		 0xd9,		0xd9},
									{0x378b, 	0x03,	  0x03,		0x03,		0x03,		 0x03,		0x03},
									{0x378c, 	0xeb,	  0xeb,		0xeb,		0xeb,		 0xeb,		0xeb},
									{0x378d, 	0x05,	  0x05,		0x05,		0x05,		 0x05,		0x05},
									{0x378e, 	0x87,	  0x87,		0x87,		0x87,		 0x87,		0x87},
									{0x378f, 	0x06,	  0x06,		0x06,		0x06,		 0x06,		0x06},
									{0x3790, 	0xf5,	  0xf5,		0xf5,		0xf5,		 0xf5,		0xf5},
									{0x3792, 	0x43,	  0x43,		0x43,		0x43,		 0x43,		0x43},
									{0x3794, 	0x7a,	  0x7a,		0x7a,		0x7a,		 0x7a,		0x7a},
									{0x3796, 	0xa1,	  0xa1,		0xa1,		0xa1,		 0xa1,		0xa1},
//									{0x37b0, 	0x36,	  0x36,		0x36,		0x36,		 0x36,		0x36},		//XMASTER PIN LOW : 0x36 (Sensor Master Mode)
									{0x37b0,	0x37,	  0x37, 	0x37,		0x37,		 0x37,		0x37},	//XMASTER PIN HIGH : 0x37 (Sensor Slave Mode)

									//0x3a**
									{0x3a01, 	0x03,	  0x03,		0x03,		0x03,		 0x03,		0x03},
									{0x3a18, 	0x7f,	  0x8f,		0x7f,		0x8f,		 0x7f,		0x8f},
									{0x3a19, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x3a1a, 	0x37,	  0x4f,		0x37,		0x4f,		 0x37,		0x4f},
									{0x3a1b, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x3a1c, 	0x37,	  0x47,		0x37,		0x47,		 0x37,		0x47},
									{0x3a1d, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x3a1e, 	0xf7,	  0x37,		0xf7,		0x37,		 0xf7,		0x37},
									{0x3a1f, 	0x00,	  0x01,		0x00,		0x01,		 0x00,		0x01},
									{0x3a20, 	0x3f,	  0x4f,		0x3f,		0x4f,		 0x3f,		0x4f},
									{0x3a21, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x3a22, 	0x6f,	  0x87,		0x6f,		0x87,		 0x6f,		0x87},
									{0x3a23, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x3a24, 	0x3f,	  0x4f,		0x3f,		0x4f,		 0x3f,		0x4f},
									{0x3a25, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x3a26, 	0x5f,	  0x7f,		0x5f,		0x7f,		 0x5f,		0x7f},
									{0x3a27, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00},
									{0x3a28, 	0x2f,	  0x3f,		0x2f,		0x3f,		 0x2f,		0x3f},
									{0x3a29, 	0x00,	  0x00,		0x00,		0x00,		 0x00,		0x00}
								};


//----------------------------------------------------------------------------------------

const UINT gTblSensEa		= numberof(gwTblSens0);

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
									{0    , 128     },
									{14   , 150     },
									{28   , 176     },
									{42   , 207     },
									{56   , 243     },
									{70   , 286     },
									{84   , 336     },
									{98   , 395     },
									{112  , 464     },
									{126  , 546     },
									{140  , 641     },
									{154  , 753     },
									{168  , 885     },
									{182  , 1040    },
									{196  , 1222    },
									{210  , 1436    },
									{224  , 1687    },
									{238  , 1982    },
									{252  , 2329    },
									{266  , 2736    },
									{280  , 3215    },
									{294  , 3777    },
									{308  , 4438    },
									{322  , 5214    },
									{336  , 6126    },
									{350  , 7197    },
									{364  , 8456    },
									{378  , 9935    },
									{392  , 11673   },
									{406  , 13715   },
									{420  , 16114   },
									{434  , 18932   },
									{448  , 22243   },
									{462  , 26134   },
									{476  , 30705   },
									{490  , 36075   },
									{504  , 42384   },
									{518  , 49797   },
									{532  , 58507   },
									{546  , 68740   },
									{560  , 80762   },
									{574  , 94887   },
									{588  , 111483  },
									{602  , 130981  },
									{616  , 153889  },
									{630  , 180804  },
									{644  , 212427  },
									{658  , 249580  },
									{672  , 293231  },
									{686  , 344516  },
									{700  , 404771  },
									{714  , 475565  },
									{728  , 558740  },
									{742  , 656462  },
									{756  , 771276  },
									{770  , 906170  },
									{784  , 1064657 },
									{798  , 1250863 },
									{812  , 1469636 },
									{826  , 1726672 },
									{840  , 2028663 },
									{854  , 2383471 },
									{868  , 2800334 },
									{882  , 3290106 },
									{896  , 3865538 },
									{910  , 4541611 },
									{924  , 5335928 },
									{938  , 6269168 },
									{952  , 7365631 },
									{966  , 8653862 },
									{980  , 10167401},
									{994  , 11945655},
									{1008 , 14034920},
									{1022 , 16489594},
									{1036 , 19373583},
									{1050 , 22761976},
									{1064 , 26742990},
									{1078 , 31420274},
									{1092 , 36915603},		//5M VMAX - 4950
									{1106 , 43372051},
									{1120 , 50957717}
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
					((aiWdrMode==MN_OFF)?(_12BIT):(_10BIT)),\
					/* 3210, 10, 0 */\
					(_3210),\
					/* Word Count */\
					((aiWdrMode==MN_OFF) ?	((aiResMode==MD_4M_FPS_25_30)?(0xF30):(0xF54)):\
											((aiResMode==MD_4M_FPS_25_30)?(0xCA8):(0xCC6))),\
					/* MIPI Line information or Virtual channel mode */\
					_MIPI_VC,\
					aiWdrMode);
	
	//ISP Master Mode Only
	SMCK_DIVw(0x1);	
	SS_WAVEw(((aiResMode==MD_5M_FPS_20)&&(aiWdrMode==MN_ON))?(0x1):(0x0));		// IMX335 5M 20fps DOL Only

	SS_HTWw(gnInModeHtw-2);
	SS_VTWw(gnInModeVtw-1);
}

void LibInitSens(int aiMode, int aiOption)
{	// IMX335, Sensor Master mode
	// aiMode (Normal)  - 0 : 4M30P, 1 : 5M12.5P, 2 : 5M20P
	// aiOption (DOL)	- 0 : OFF, 	 1 : ON (DOL2P)

	UINT i;

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

	LibRdesIsp(aiMode, aiOption);
	
	SetSens(0x3000, 0x1);	WaitUs(1000);		// standby
	SetSens(0x3002, 0x1);	WaitUs(1000);		// xmaster stop
	SetSens(0x3001, 0x01);						// REG Hold
	SetSens(0x3003, 0x01);						// SW reset

	// 180503 LGH
	for (i=0; i<gTblSensEa; i++)	{	SetSens(gwTblSens0[i][0], (BYTE)gwTblSens0[i][1+(aiMode*2)+aiOption]);}

	//Shutter Speed Max
	gnAeNorMax = gnInModeVtw-AE_SHTMAX_OFST;

	//	if ((aiOption==1)||(gbModeWdrOn_F)) {			// DOL 2P
	if (aiOption==1) {			// DOL 2P
		gnAeLWdrMaxL0	= (AE_LWDR_2P_L0_MAX - AE_LWDR_2P_RHS1)-AE_LWDR_2P_L0MIN_OFST;
		gnAeLWdrMaxS1	= (AE_LWDR_2P_S1_MAX)-AE_LWDR_2P_S1MIN_OFST;

		gnAeLWdrMinL0	= (AE_LWDR_2P_L0_MIN - AE_LWDR_2P_RHS1)-AE_LWDR_2P_L0MIN_OFST;
		gnAeLWdrMinS1	= (AE_LWDR_2P_S1_MIN)-AE_LWDR_2P_S1MIN_OFST;

		gbAeWdrComp		= 0x1;
		SetSensBst(0x3068, (AE_LWDR_2P_RHS1&0x0FFFFF), 3); 
	}
	
	SetSens(0x3003, 0x00);						// SW reset OFF
	SetSens(0x3001, 0x00);						// REG Hold OFF
	SetSens(0x3000, 0x0);	WaitUs(30000);		// standby cancel
	SetSens(0x3002, 0x0);	WaitUs(20000);		// xmaster	

}

void ISPM Sens(AE_SHTLw)(UINT val)
{
	SetSensBst(0x3058, (val&0x0FFFFF), 3); 
}

void ISPM Sens(AE_SHTSw)(UINT val)
{
	SetSensBst(0x305C, (val&0x0FFFFF), 3); 
}

void ISPM Sens(AE_AGCw)(UINT val)
{
	SetSensBst(0x30E8, (val&0x0FFF), 2);
}

void ISPM Sens(AE_DGCw)(UINT val)
{
//	UNUSED_ARG(val);
	LibAePrgainIntp(val);
}

void ISPM Sens(AE_FREQw)(UINT val, UINT val1)
{
	UNUSED_ARG(val);
	UNUSED_ARG(val1);
//Sensor Master Mode
//	SetSens(0, 0x3035, (val1>>8)&0xff);
//	SetSens(0, 0x3034, (val1>>0)&0xff);

//ISP Master Mode
//	SS_HTWw(val1-2);
//	SS_VTWw(val-1);
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
	
	// for DOL
	UINT	nShtFltbuf=0;
	UINT	nShtIntbuf=0;
	const BYTE bMultpl = 4;
	const BYTE bOfst = 2;

	for(i=1; i<anTblEa; i++) {
		if (aiVal<(int)gnAeShtTbl[i][0]) {
			nShtFlt = LibUtlInterp1D (aiVal, gnAeShtTbl[i-1][0], gnAeShtTbl[i][0], gnAeShtTbl[i-1][1], gnAeShtTbl[i][1]);
			nShtInt = nShtFlt>>7;

		if(gbModeWdrOn_L){
			nShtIntbuf = ((nShtInt-AE_SHTMIN_OFST)/bMultpl)+bOfst;
			nShtFltbuf = ((nShtIntbuf-bOfst)*bMultpl)+AE_SHTMIN_OFST;
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
//** Sensor Spec : Shutter 9 to 3299(VMAX-1)
//				1 to 3291
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
		gnShtFlt = AE_GAIN_DENORMAL(gnShtFlt);
		gnShtFlt = MIN(gnShtFlt,(UINT)(AE_GAIN_TOTAL));
		gnShtFlt = MAX(gnShtFlt,0);

 		AE_AGCw(gnShtFlt);				//Shutter Control State, AGC
	}

	LibAeShtIntp (aiVal, AE_SHT_TBL_EA, AE_HSS_FLT_EA, &gnShtFlt, &nShtInt);
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
	  nRem 	= MIN(nShtInt, nShtMax);
	}

	AE_SHTLw(nShtMax-nRem+AE_SHTMAX_OFST);

	DebugDisp(gbAeDebugOn, Dec, "SHT_int__d", 1, 24, nRem		)
	DebugDisp(gbAeDebugOn, Dec, "SHT_flt__d", 2, 24, gnShtFlt	)

	return ((WORD)(nRem));
}

void ISPM AeAGC(int aiVal)
{	// AGC driver
   	static int	giAgc;
	const UINT nAGC_LMT = AE_GAIN_DENORMAL(AE_SENS_AGC_LMT_NOR);
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
		LibAeGainIntp((aiVal-AE_SENS_AGC_LMT_NOR), &nLWdrGain);			//Calculation 0.1dB
		giAeLWdrGain = (int)nLWdrGain;									
		giAgc = (nAGC_LMT - AE_GAIN_UNIT_OVR);							//AGC MAX
	}

	giAgc = MINMAX(giAgc, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA));

	nDgcMok = (giAgc/3);
	nDgcMod = (giAgc%3);
	
	if (gnAeState!=0)	{
		if(giAgc <= 0)		nDgc = 0;
		else				nDgc = LibAePrgainIntp(nDgcMod);

		LibAePrgain_L(MAX(nDgc, 0x100));
		AE_AGCw((BYTE)nDgcMok);
	}

	DebugDisp(gbAeDebugOn, Hex, "AGC_____", 5, 24, giAgc )
	DebugDisp(gbAeDebugOn, Hex, "WDR_GAIN", 6, 24, giAeLWdrGain)
}


// -------------------------------------------------------------------------------------
// LINE WDR

WORD ISPM AeSHT_LWDR(int aiMode, int aiVal, int aiVal1)
{	// Shutter driver for Line WDR
	// aiMode : 0 : off, 1: 2 page
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
	gnSht_L		= tgt_L;	// Long   Exposure Shutter line
	gnAgc_L = LibAePrgainIntp(gnShtFlt_L);

	//Short
	LibAeShtIntp (aiVal1, AE_SHT_TBL_EA, AE_HSS_FLT_EA, &gnShtFlt_S, &nShtInt);
	tgt_S1 = (int)nShtInt;
	gnSht_S1	= tgt_S1;   // Short1 Exposure Shutter line
	gnAgc_S1 = LibAePrgainIntp(gnShtFlt_S);


//	tgt_L  = (AE_LWDR_FSC - AE_LWDR_2P_L0MAX_OFST) - tgt_L + AE_LWDR_2P_L0MIN_OFST;
	tgt_L  = (AE_LWDR_FSC - AE_LWDR_2P_L0MAX_OFST) - tgt_L;									// 191025 LGH : Shutter position offset
	tgt_L  = (tgt_L/4)*4;																	//must be controlled 4n
//	tgt_S1 = (AE_LWDR_2P_RHS1 - AE_LWDR_2P_S1MAX_OFST)- tgt_S1 + AE_LWDR_2P_S1MIN_OFST;
	tgt_S1 = (AE_LWDR_2P_RHS1 - AE_LWDR_2P_S1MAX_OFST)- tgt_S1;								// 191025 LGH : Shutter position offset
	tgt_S1 = ((tgt_S1-2)/4)*4+2;															//must be controlled 4n+2

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
{
	// AGC driver for Line WDR
	// aiMode : 0: off, 1: 2 page
	// aiVal : Long
	// aiVal1 : short1
	
	UNUSED_ARG(aiMode);
	UNUSED_ARG(aiVal1);
	
	static int	giAgcL, giAgcS1;
	static UINT nLWdrGain;
	static UINT nDgc;

	UINT nDgcMok = 0;
	UINT nDgcMod = 0;

	const UINT nLWDR_AGC_LMT = AE_GAIN_DENORMAL(AE_SENS_AGC_LMT_WDR);
	
	giAgcL = AE_GAIN_DENORMAL(aiVal);		// 171211 LH
	giAgcL  = MINMAX(giAgcL, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA));

	if(giAgcL <= (int)nLWDR_AGC_LMT){												//AGC+HCG
		giAeLWdrGain = 0x0;
	}
	else{
		LibAeGainIntp((aiVal-AE_SENS_AGC_LMT_WDR), &nLWdrGain);						//Calculation 0.1dB
		giAeLWdrGain = (int)nLWdrGain;									
		giAgcL = (nLWDR_AGC_LMT - AE_GAIN_UNIT_OVR);							//AGC MAX
	}

	giAgcL = MINMAX(giAgcL, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA));
	giAgcS1 = giAgcL;
		
	nDgcMok = (giAgcL/3);
	nDgcMod = (giAgcL%3);
	
	if (gnAeState!=0)	{
		if(giAgcL <= 0)		nDgc = 0;
		else				nDgc = LibAePrgainIntp(nDgcMod);

		LibAePrgain_L(MAX(nDgc, 0x100));
		LibAePrgain_S(MAX(nDgc, 0x100));
		
		SetSensBst(0x30e8, (nDgcMok&0x3FF), 2); 	// L  GAIN
		SetSensBst(0x30ea, (nDgcMok&0x3FF), 2); 	// S  GAIN
	}

	DebugDisp(gbAeDebugOn, Dec, "AGC0____", 5, 24, giAgcL  )
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

void Sens(SENS_MIRw)(BYTE abOn){
	SetSens(0x304E, ((GetSens(0x304E)&(~ValSft_L00(BitMask_01)))|ValSft_L00((abOn)&BitMask_01)));
}

void Sens(SENS_FLPw)(BYTE abOn){
	if(abOn){SetSens(0x304F, 0x01);\
	 if(MODE_5M_ON){SetSens(0x3074, 0x10); SetSens(0x3075, 0x10);}\
	 else		   {SetSens(0x3074, 0x18); SetSens(0x3075, 0x0E); SetSens(0x30C6, 0x00); SetSens(0x30CE, 0x00); SetSens(0x30D8, 0x4C); SetSens(0x30D9, 0x10);}\
	 SetSens(0x3081, 0xFE); SetSens(0x3083, 0xFE); SetSens(0x30B6, 0xFA); SetSens(0x30B7, 0x01); SetSens(0x3116, 0x02);}

	else{SetSens(0x304F, 0x00);\
	 if(MODE_5M_ON){SetSens(0x3074, 0xB0); SetSens(0x3075, 0x00);}\
	 else		   {SetSens(0x3074, 0xA8); SetSens(0x3075, 0x02); SetSens(0x30C6, 0x12); SetSens(0x30CE, 0x64); SetSens(0x30D8, 0xC8); SetSens(0x30D9, 0x0E);}\
	 SetSens(0x3081, 0x02); SetSens(0x3083, 0x02); SetSens(0x30B6, 0x00); SetSens(0x30B7, 0x00); SetSens(0x3116, 0x08);}
}


