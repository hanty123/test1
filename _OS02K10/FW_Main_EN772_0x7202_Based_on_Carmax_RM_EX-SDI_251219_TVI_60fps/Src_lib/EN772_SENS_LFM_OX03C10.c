/* **************************************************************************
 File Name		:	EN772_SENS_LFM_OX03C10.c
 Description	:	EN772 - OX03C10 device driver
 Designer		:	Lee, Gyu Hong
 Date			:	20.10.20
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#undef model_Sens
#include "../Src/dev.h"
#define model_Sens	SENS_OX03C10
#include "../Src/dev.h"
#include "SENS_Common.h"

// -----------------------------------------------------------------------------------------
// pre define & table
// -----------------------------------------------------------------------------------------

#define gbAeHssFltTbl		Sens(gbAeHssFltTbl)
#define gnAeShtTbl			Sens(gnAeShtTbl)
#define LibAeShtIntp		Sens(LibAeShtIntp)

extern UINT gnInModeVtw;
extern BYTE gbAeDebugOn;
extern BYTE gbInModeRes;

extern int iVstAddr;
extern int iVendAddr;

extern WORD gwVsShtPos0, gwVsShtPos1;
extern WORD gwVsAgcPos0, gwVsAgcPos1;
extern BYTE gbVsShtLine0, gbVsShtLine1;

	
#define AE_RATIO_DCG_SPD		(1)																	// HDR Ratio DCG and SPD	x4
#define AE_RATIO_DCG_VS			(64)																// HDR Ratio DCG and VS	x64
#define AE_VS_SHT				(32)

#define AE_SHTMAX_OFST			(12+AE_VS_SHT)
#define AE_SHTMIN_OFST			(2)

#define AE_SHTMAX				(nMok-AE_SHTMAX_OFST)

#define AE_GAIN_UNIT_MAX		(479)	    														// Sensor gain step by Unit
#define AE_GAIN_UNIT_EA			(1)						    										// Sensor gain Unit EA
#define AE_GAIN_UNIT_OVR		(0)																	// Sensor gain extended step
#define AE_GAIN_UNIT_OVR2		(0)	    															// ISP gain extended step

const int Sens(AE_GAIN_TOTAL) = (((AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR)*1);			//Modified gain per step
const int Sens(AE_GAIN_TOTAL2) = 0;

#define AE_GAIN_DENORMAL(val)	(ifdiv8(val*(int)(1.0f*256.f)))										// 0.1dB

#define AE_HSS_FLT_EA		(sizeof(gbAeHssFltTbl))
#define AE_SHT_TBL_EA		(sizeof(gnAeShtTbl)/8)

// Limit condition 
// HDR 4 : Max (DCG_exp + VS_exp, SPD_exp) < VTS - 12
// VS_exp_max < 35  | VS 1 to 34 line = 1/37500s to 1/1100s

#define AGC_DBG_TXT				(0)

// -----------------------------------------------------------------------------------------
// initial								
	const WORD gwTblSens_Base[][2] = {
								//ADDR		//DATA
								{0x4d5a, 	0x1a},
								{0x4d09, 	0xff},
								{0x4d09, 	0xdf},
								{0x3208, 	0x04},
								{0x4620, 	0x04},
								{0x3208, 	0x14},
								{0x3208, 	0x05},
								{0x4620, 	0x04},
								{0x3208, 	0x15},
								{0x3208, 	0x02},
								{0x3507, 	0x00},
								{0x3208, 	0x12},
								{0x3208, 	0xa2},
								{0x0301, 	0xc8},
								{0x0303, 	0x01},
								{0x0304, 	0x01},
								{0x0305, 	0x08},
								{0x0306, 	0x04},
								{0x0307, 	0x01},
								{0x0316, 	0x00},
								{0x0317, 	0x00},
								{0x0318, 	0x00},
								{0x0323, 	0x04},
								{0x0324, 	0x00},
								{0x0325, 	0xc8},
								{0x0400, 	0xe0},
								{0x0401, 	0x80},
								{0x0403, 	0xde},
								{0x0404, 	0x34},
								{0x0405, 	0x3b},
								{0x0406, 	0xde},
								{0x0407, 	0x08},
								{0x0408, 	0xe0},
								{0x0409, 	0x7f},
								{0x040a, 	0xde},
								{0x040b, 	0x34},
								{0x040c, 	0x47},
								{0x040d, 	0xd8},
								{0x040e, 	0x08},
								{0x2803,	0xfe},
								{0x280b,	0x00},
								{0x280c,	0x79},
								{0x3001,	0x03},
								{0x3002,	0xf8},
								{0x3005,	0x80},
								{0x3007,	0x01},
								{0x3008,	0x80},
								{0x3012,	0x41},
								{0x3020,	0x05},
								{0x3700,	0x28},
								{0x3701,	0x15},
								{0x3702,	0x19},
								{0x3703,	0x23},
								{0x3704,	0x0a},
								{0x3705,	0x00},
								{0x3706,	0x3e},
								{0x3707,	0x0d},
								{0x3708,	0x50},
								{0x3709,	0x5a},
								{0x370a,	0x00},
								{0x370b,	0x96},
								{0x3711,	0x11},
								{0x3712,	0x13},
								{0x3717,	0x02},
								{0x3718,	0x73},
								{0x372c,	0x40},
								{0x3733,	0x01},
								{0x3738,	0x36},
								{0x3739,	0x36},
								{0x373a,	0x25},
								{0x373b,	0x25},
								{0x373f,	0x21},
								{0x3740,	0x21},
								{0x3741,	0x21},
								{0x3742,	0x21},
								{0x3747,	0x28},
								{0x3748,	0x28},
								{0x3749,	0x19},
								{0x3755,	0x1a},
								{0x3756,	0x0a},
								{0x3757,	0x1c},
								{0x3765,	0x19},
								{0x3766,	0x05},
								{0x3767,	0x05},
								{0x3768,	0x13},
								{0x376c,	0x07},
								{0x3778,	0x20},
								{0x377c,	0xc8},
								{0x3781,	0x02},
								{0x3783,	0x02},
								{0x379c,	0x58},
								{0x379e,	0x00},
								{0x379f,	0x00},
								{0x37a0,	0x00},
								{0x37bc,	0x22},
								{0x37c0,	0x01},
								{0x37c4,	0x3e},
								{0x37c5,	0x3e},
								{0x37c6,	0x2a},
								{0x37c7,	0x28},
								{0x37c8,	0x02},
								{0x37c9,	0x12},
								{0x37cb,	0x29},
								{0x37cd,	0x29},
								{0x37d2,	0x00},
								{0x37d3,	0x73},
								{0x37d6,	0x00},
								{0x37d7,	0x6b},
								{0x37dc,	0x00},
								{0x37df,	0x54},
								{0x37e2,	0x00},
								{0x37e3,	0x00},
								{0x37f8,	0x00},
								{0x37f9,	0x01},
								{0x37fa,	0x00},
								{0x37fb,	0x19},
								{0x3c03, 	0x01},
								{0x3c04, 	0x01},
								{0x3c06, 	0x21},
								{0x3c08, 	0x01},
								{0x3c09, 	0x01},
								{0x3c0a, 	0x01},
								{0x3c0b, 	0x21},
								{0x3c13, 	0x21},
								{0x3c14, 	0x82},
								{0x3c16, 	0x13},
								{0x3c21, 	0x00},
								{0x3c22, 	0xf3},
								{0x3c37, 	0x12},
								{0x3c38, 	0x31},
								{0x3c3c, 	0x00},
								{0x3c3d, 	0x03},
								{0x3c44, 	0x16},
								{0x3c5c, 	0x8a},
								{0x3c5f, 	0x03},
								{0x3c61, 	0x80},
								{0x3c6f, 	0x2b},
								{0x3c70, 	0x5f},
								{0x3c71, 	0x2c},
								{0x3c72, 	0x2c},
								{0x3c73, 	0x2c},
								{0x3c76, 	0x12},
								{0x3182,	0x12},								
								{0x320e,	0x00},
								{0x320f,	0x00},
								{0x3211,	0x61},
								{0x3215,	0xcd},
								{0x3219,	0x08},
								{0x3506, 	0x30},
								{0x350a, 	0x01},
								{0x350b, 	0x00},
								{0x350c, 	0x00},
								{0x3586, 	0x60},
								{0x358a, 	0x01},
								{0x358b, 	0x00},
								{0x358c, 	0x00},
								{0x3541, 	0x00},
								{0x3542, 	0x04},
								{0x3548, 	0x04},
								{0x3549, 	0x40},
								{0x354a, 	0x01},
								{0x354b, 	0x00},
								{0x354c, 	0x00},
								{0x35c1, 	0x00},
								{0x35c2, 	0x02},
								{0x35c6, 	0xa0},
						
						#if(1)
							//Exposure - DCG-HCG
								//Shutter speed
								{0x3501,	0x00},	// [7:0] - DCG [15:8]
								{0x3502,	0x08},	// [7:0] - DCG [ 7:0]

								//Real gain
								{0x3508,	0x01},	// [3:0] - Real gain[7:4]
								{0x3509,	0x00},	// [7:4] - Real gain[3:0]

								//Digital gain
								{0x350a,	0x01},	// [3:0] - Digital gain[13:10]
								{0x350b,	0x00},	// [7:0] - Digital gain[9:2]
								{0x350c,	0x00},	// [7:6] - Digital gain[1:0]

								{0x3581,	0x00},
								{0x3582,	0x40},

								// DCG - LCG	
								//Real gain
								{0x3588,	0x01},	// [3:0] - Real gain[7:4]
								{0x3589,	0x00},	// [7:4] - Real gain[3:0]

								//Digital gain
								{0x358a,	0x01},	// [3:0] - Digital gain[13:10]
								{0x358b,	0x00},	// [7:0] - Digital gain[9:2]
								{0x358c,	0x00},	// [7:6] - Digital gain[1:0]

							//Exposure - SPD
								//Shutter speed
								{0x3541,	0x00},	// [7:0] - SPD [15:8]
								{0x3542,	0x04},	// [7:0] - SPD [ 7:0]

								//Real gain
								{0x3548,	0x01},	// [3:0] - Real gain[7:4]
								{0x3549,	0x00},	// [7:4] - Real gain[3:0]

								//Digital gain
								{0x354a,	0x01},	// [3:0] - Digital gain[13:10]
								{0x354b,	0x00},	// [7:0] - Digital gain[9:2]
								{0x354c,	0x00},	// [7:6] - Digital gain[1:0]

							//Exposure - VS
								//Shutter speed
								{0x35c1,	0x00},	// [7:0] - VS [15:8]
								{0x35c2,	0x02},	// [7:0] - VS [ 7:0]
	
								{0x35c7,	0x00},	// ??

								//Real gain
								{0x35c8,	0x01},	// [3:0] - Real gain[7:4]
								{0x35c9,	0x00},	// [7:4] - Real gain[3:0]

								//Digital gain
								{0x35ca,	0x01},	// [3:0] - Digital gain[13:10]
								{0x35cb,	0x00},	// [7:0] - Digital gain[9:2]
								{0x35cc,	0x00},	// [7:6] - Digital gain[1:0]
						#endif
								{0x3600,	0x8f},
								{0x3605,	0x16},
								{0x3609,	0xf0},
								{0x360a,	0x01},
								{0x360e,	0x1d},
								{0x360f,	0x10},
								{0x3610,	0x70},
								{0x3611,	0x3a},
								{0x3612,	0x28},
								{0x361a,	0x29},
								{0x361b,	0x6c},
								{0x361c,	0x0b},
								{0x361d,	0x00},
								{0x361e,	0xfc},
								{0x362a,	0x00},
								{0x364d,	0x0f},
								{0x364e,	0x18},
								{0x364f,	0x12},
								{0x3653,	0x1c},
								{0x3654,	0x00},
								{0x3655,	0x1f},
								{0x3656,	0x1f},
								{0x3657,	0x0c},
								{0x3658,	0x0a},
								{0x3659,	0x14},
								{0x365a,	0x18},
								{0x365b,	0x14},
								{0x365c,	0x10},
								{0x365e,	0x12},
								{0x3674,	0x08},
								{0x3677,	0x3a},
								{0x3678,	0x3a},
								{0x3679,	0x19},

								{0x3802, 	0x00},
								{0x3803, 	0x64},
								{0x3804, 	0x07},
								{0x3805, 	0x9f},
								{0x3806, 	0x04},
								{0x3807, 	0xab},
								{0x3808, 	0x07},
								{0x3809, 	0x88},
								{0x380a, 	0x04},
								{0x380b, 	0x40},
//								{0x380c, 	0x04},
//								{0x380d, 	0x47},
//								{0x380e, 	0x02},
//								{0x380f, 	0xae},
								{0x3810, 	0x00},
								{0x3811, 	0x04},
								{0x3812, 	0x00},
								{0x3813, 	0x04},
								{0x3816, 	0x01},
								{0x3817, 	0x01},
								{0x381c, 	0x18},
								{0x381e, 	0x01},
								{0x381f, 	0x01},
								{0x3820, 	0x20},	//[5] : MIRROR Enable
													//[2] : FLIP Enable
								{0x3821, 	0x19},
								{0x3832, 	0x00},
								{0x3834, 	0x00},
//								{0x384c, 	0x02},
//								{0x384d, 	0x0d},
								{0x3850, 	0x00},
								{0x3851, 	0x42},
								{0x3852, 	0x00},
								{0x3853, 	0x40},
								{0x3858, 	0x04},
//								{0x388c, 	0x02},
//								{0x388d, 	0x2b},

								{0x3b40, 	0x05},
								{0x3b41, 	0x40},
								{0x3b42, 	0x00},
								{0x3b43, 	0x90},
								{0x3b44, 	0x00},
								{0x3b45, 	0x20},
								{0x3b46, 	0x00},
								{0x3b47, 	0x20},
								{0x3b48, 	0x19},
								{0x3b49, 	0x12},
								{0x3b4a, 	0x16},
								{0x3b4b, 	0x2e},
								{0x3b4c, 	0x00},
								{0x3b4d, 	0x00},
								{0x3b86, 	0x00},
								{0x3b87, 	0x34},
								{0x3b88, 	0x00},
								{0x3b89, 	0x08},
								{0x3b8a, 	0x05},
								{0x3b8b, 	0x00},
								{0x3b8c, 	0x07},
								{0x3b8d, 	0x80},
								{0x3b8e, 	0x00},
								{0x3b8f, 	0x00},
								{0x3b92, 	0x05},
								{0x3b93, 	0x00},
								{0x3b94, 	0x07},
								{0x3b95, 	0x80},
								{0x3b9e, 	0x09},
								{0x3d85, 	0x05},
								{0x3d8a, 	0x03},
								{0x3d8b, 	0xff},
								{0x3d99, 	0x00},
								{0x3d9a, 	0x9f},
								{0x3d9b, 	0x00},
								{0x3d9c, 	0xa0},
								{0x3da4, 	0x00},
								{0x3da7, 	0x50},
								{0x420e, 	0xff},
								{0x420f, 	0xff},
								{0x4210, 	0xff},
								{0x4211, 	0xff},
								{0x421e, 	0x02},
								{0x421f, 	0x45},
								{0x4220, 	0xe1},
								{0x4221, 	0x01},
								{0x4301, 	0xff},
								{0x4307, 	0x03},
								{0x4308, 	0x13},
								{0x430a, 	0x13},
								{0x430d, 	0x93},
								{0x430f, 	0x17},
								{0x4310, 	0x95},
								{0x4311, 	0x16},
								{0x4316, 	0x00},
								{0x4317, 	0x08},
								{0x4319, 	0x03},
								{0x431a, 	0x00},
								{0x431b, 	0x00},
								{0x431d, 	0x2a},
								{0x431e, 	0x11},
								{0x431f,	0x30},		// [5] : PWL Enable				*
														// [4:3] : PWL_MODE 0 - 12bit  
														//					1 - 14bit
														//					2 - 16bit	*
														//					3 - 20bit
								{0x4320, 	0x19},
								{0x4323, 	0x80},
								{0x4324, 	0x00},
								{0x4503, 	0x4e},
								{0x4505, 	0x00},
								{0x4509, 	0x00},
								{0x450a, 	0x00},
								{0x4580, 	0xf8},
								{0x4583, 	0x07},
								{0x4584, 	0x6a},
								{0x4585, 	0x08},
								{0x4586, 	0x05},
								{0x4587, 	0x04},
								{0x4588, 	0x73},
								{0x4589, 	0x05},
								{0x458a, 	0x1f},
								{0x458b, 	0x02},
								{0x458c, 	0xdc},
								{0x458d, 	0x03},
								{0x458e, 	0x02},
								{0x4597, 	0x07},
								{0x4598, 	0x40},
								{0x4599, 	0x0e},
								{0x459a, 	0x0e},
								{0x459b, 	0xfb},
								{0x459c, 	0xf3},
								{0x4602, 	0x00},
//								{0x4603, 	0x13},
								{0x4603, 	0x11},
								{0x4604, 	0x00},
								{0x4609, 	0x0a},
								{0x460a, 	0x30},
								{0x4610, 	0x00},
								{0x4611, 	0x70},
								{0x4612, 	0x01},
								{0x4613, 	0x00},
								{0x4614, 	0x00},
								{0x4615, 	0x70},
								{0x4616, 	0x01},
								{0x4617, 	0x00},
								{0x4800, 	0x04},
								{0x480a, 	0x22},
								{0x4813, 	0xe4},
								{0x4814, 	0x2a},
								{0x4837, 	0x0d},
								{0x484b, 	0x47},
								{0x484f, 	0x00},
								{0x4887, 	0x51},
								{0x4d00, 	0x4a},
								{0x4d01, 	0x18},
								{0x4d05, 	0xff},
								{0x4d06, 	0x88},
								{0x4d08, 	0x63},
								{0x4d09, 	0xdf},
								{0x4d15, 	0x7d},
								{0x4d1a, 	0x20},
								{0x4d30, 	0x0a},
								{0x4d31, 	0x00},
								{0x4d34, 	0x7d},
								{0x4d3c, 	0x7d},
								{0x4f00, 	0x00},
								{0x4f01, 	0x00},
								{0x4f02, 	0x00},
								{0x4f03, 	0x20},
								{0x4f04, 	0xe0},
								{0x6a00, 	0x00},
								{0x6a01, 	0x20},
								{0x6a02, 	0x00},
								{0x6a03, 	0x20},
								{0x6a04, 	0x02},
								{0x6a05, 	0x80},
								{0x6a06, 	0x01},
								{0x6a07, 	0xe0},
								{0x6a08, 	0xcf},
								{0x6a09, 	0x01},
								{0x6a0a, 	0x40},
								{0x6a20, 	0x00},
								{0x6a21, 	0x02},
								{0x6a22, 	0x00},
								{0x6a23, 	0x00},
								{0x6a24, 	0x00},
								{0x6a25, 	0x00},
								{0x6a26, 	0x00},
								{0x6a27, 	0x00},
								{0x6a28, 	0x00},
								{0x5000, 	0x8f},
								{0x5001, 	0x75},
								{0x5002, 	0x7f},
								{0x5004, 	0x3e},
								{0x5005, 	0x1e},
								{0x5006, 	0x1e},
								{0x5007, 	0x1e},
								{0x5008, 	0x00},
								{0x500c, 	0x00},
								{0x502c, 	0x00},
								{0x502e, 	0x00},
								{0x502f, 	0x00},
								{0x504b, 	0x00},
								{0x5053, 	0x00},
								{0x505b, 	0x00},
								{0x5063, 	0x00},
								{0x5070, 	0x00},
								{0x5074, 	0x04},
								{0x507a, 	0x04},
								{0x507b, 	0x09},
								{0x5500, 	0x02},
								{0x5700, 	0x02},
								{0x5900, 	0x02},
								{0x6007, 	0x04},
								{0x6008, 	0x05},
								{0x6009, 	0x02},
								{0x600b, 	0x08},
								{0x600c, 	0x07},
								{0x600d, 	0x88},
								{0x6016, 	0x00},
								{0x6027, 	0x04},
								{0x6028, 	0x05},
								{0x6029, 	0x02},
								{0x602b, 	0x08},
								{0x602c, 	0x07},
								{0x602d, 	0x88},
								{0x6047, 	0x04},
								{0x6048, 	0x05},
								{0x6049, 	0x02},
								{0x604b, 	0x08},
								{0x604c, 	0x07},
								{0x604d, 	0x88},
								{0x6067, 	0x04},
								{0x6068, 	0x05},
								{0x6069, 	0x02},
								{0x606b, 	0x08},
								{0x606c, 	0x07},
								{0x606d, 	0x88},
								{0x6087, 	0x04},
								{0x6088, 	0x05},
								{0x6089, 	0x02},
								{0x608b, 	0x08},
								{0x608c, 	0x07},
								{0x608d, 	0x88},
								{0x5e00, 	0x02},
								
								//PWL Point
							#if(1)
								{0x5e01,	0x08},		//dx_exp0 	
								{0x5e02,	0x09},		//dx_exp1 
								{0x5e03,	0x0a},		//dx_exp2 
								{0x5e04,	0x0b},		//dx_exp3 
								{0x5e05,	0x0c},		//dx_exp4 
								{0x5e06,	0x0c},		//dx_exp5 
								{0x5e07,	0x0c},		//dx_exp6 
								{0x5e08,	0x0c},		//dx_exp7 
								{0x5e09,	0x0c},		//dx_exp8 
								{0x5e0a,	0x0d},		//dx_exp9 
								{0x5e0b,	0x0d},		//dx_exp10
								{0x5e0c,	0x0d},		//dx_exp11
								{0x5e0d,	0x0d},		//dx_exp12  
								{0x5e0e,	0x0d},		//dx_exp13
								{0x5e0f,	0x0e},		//dx_exp14
								{0x5e10,	0x0e},		//dx_exp15
								{0x5e11,	0x0e},		//dx_exp16
								{0x5e12,	0x0e},		//dx_exp17
								{0x5e13,	0x0f},		//dx_exp18
								{0x5e14,	0x0f},		//dx_exp19
								{0x5e15,	0x10},		//dx_exp20
								{0x5e16,	0x11},		//dx_exp21
								{0x5e17,	0x11},		//dx_exp22
								{0x5e18,	0x12},		//dx_exp23
								{0x5e19,	0x12},		//dx_exp24
								{0x5e1a,	0x13},		//dx_exp25
								{0x5e1b,	0x13},		//dx_exp26
								{0x5e1c,	0x14},		//dx_exp27
								{0x5e1d,	0x14},		//dx_exp28
								{0x5e1e,	0x16},		//dx_exp29
								{0x5e1f,	0x16},		//dx_exp30
								{0x5e20,	0x16},		//dx_exp31
								{0x5e21,	0x08},		//dx_exp32
											  
								{0x5E22,	0x00},		//dy_val0
								{0x5E23,	0x01},		// "
								{0x5E24,	0x00},		// "
								{0x5E25,	0x00},		//dy_val1
								{0x5E26,	0x01},      // "     
								{0x5E27,	0x55},      // "     
								{0x5E28,	0x00},		//dy_val2
								{0x5E29,	0x02},      // "     
								{0x5E2A,	0xAA},      // "     
								{0x5E2B,	0x00},		//dy_val3
								{0x5E2C,	0x01},      // "     
								{0x5E2D,	0x55},      // "     
								{0x5E2E,	0x00},		//dy_val4
								{0x5E2F,	0x02},      // "     
								{0x5E30,	0xAA},      // "     
								{0x5E31,	0x00},		//dy_val5
								{0x5E32,	0x01},      // "     
								{0x5E33,	0xAA},      // "     
								{0x5E34,	0x00},		//dy_val6
								{0x5E35,	0x01},      // "     
								{0x5E36,	0xAA},      // "     
								{0x5E37,	0x00},		//dy_val7
								{0x5E38,	0x01},      // "     
								{0x5E39,	0xAA},      // "     
								{0x5E3A,	0x00},		//dy_val8
								{0x5E3B,	0x01},      // "     
								{0x5E3C,	0xAA},      // "     
								{0x5E3D,	0x00},		//dy_val9
								{0x5E3E,	0x03},      // "     
								{0x5E3F,	0x55},      // "    
								{0x5E40,	0x00},		//dy_val10
								{0x5E41,	0x02},      // "     
								{0x5E42,	0xAA},      // "     
								{0x5E43,	0x00},		//dy_val11
								{0x5E44,	0x02},      // "     
								{0x5E45,	0xAA},      // "     
								{0x5E46,	0x00},		//dy_val12
								{0x5E47,	0x02},      // "     
								{0x5E48,	0xAA},      // "     
								{0x5E49,	0x00},		//dy_val13
								{0x5E4A,	0x02},      // "     
								{0x5E4B,	0xAA},      // "     
								{0x5E4C,	0x00},		//dy_val14
								{0x5E4D,	0x05},      // "     
								{0x5E4E,	0x55},      // "     
								{0x5E4F,	0x00},		//dy_val15
								{0x5E50,	0x03},      // "     
								{0x5E51,	0x33},      // "     
								{0x5E52,	0x00},		//dy_val16
								{0x5E53,	0x03},      // "     
								{0x5E54,	0x33},      // "     
								{0x5E55,	0x00},		//dy_val17
								{0x5E56,	0x03},      // "     
								{0x5E57,	0x33},      // "     
								{0x5E58,	0x00},		//dy_val18
								{0x5E59,	0x06},      // "     
								{0x5E5A,	0x66},      // "     
								{0x5E5B,	0x00},		//dy_val19
								{0x5E5C,	0x04},      // "     
								{0x5E5D,	0x00},      // "     
								{0x5E5E,	0x00},		//dy_val20
								{0x5E5F,	0x08},      // "     
								{0x5E60,	0x00},      // "     
								{0x5E61,	0x00},		//dy_val21
								{0x5E62,	0x08},      // "     
								{0x5E63,	0x00},      // "     
								{0x5E64,	0x00},		//dy_val22
								{0x5E65,	0x08},      // "     
								{0x5E66,	0x00},      // "     
								{0x5E67,	0x00},		//dy_val23
								{0x5E68,	0x08},      // "     
								{0x5E69,	0x00},      // "     
								{0x5E6A,	0x00},		//dy_val24
								{0x5E6B,	0x08},      // "     
								{0x5E6C,	0x00},      // "     
								{0x5E6D,	0x00},		//dy_val25
								{0x5E6E,	0x10},      // "     
								{0x5E6F,	0x00},      // "     
								{0x5E70,	0x00},		//dy_val26
								{0x5E71,	0x10},      // "     
								{0x5E72,	0x00},      // "     
								{0x5E73,	0x00},		//dy_val27
								{0x5E74,	0x10},      // "     
								{0x5E75,	0x00},      // "     
								{0x5E76,	0x00},		//dy_val28
								{0x5E77,	0x10},      // "     
								{0x5E78,	0x00},      // "     
								{0x5E79,	0x00},		//dy_val29
								{0x5E7A,	0x20},      // "     
								{0x5E7B,	0x00},      // "     
								{0x5E7C,	0x00},		//dy_val30
								{0x5E7D,	0x20},      // "     
								{0x5E7E,	0x00},      // "     
								{0x5E7F,	0x00},		//dy_val31
								{0x5E80,	0x20},      // "     
								{0x5E81,	0x00},      // "     
								{0x5E82,	0x00},		//dy_val32
								{0x5E83,	0x00},      // "     
								{0x5E84,	0xFF},      // "     
							#endif
								
								{0x5f00, 	0x02},
								{0x5f01, 	0x08},
								{0x5f02, 	0x09},
								{0x5f03, 	0x0a},
								{0x5f04, 	0x0b},
								{0x5f05, 	0x0c},
								{0x5f06, 	0x0c},
								{0x5f07, 	0x0c},
								{0x5f08, 	0x0c},
								{0x5f09, 	0x0c},
								{0x5f0a, 	0x0d},
								{0x5f0b, 	0x0d},
								{0x5f0c, 	0x0d},
								{0x5f0d, 	0x0d},
								{0x5f0e, 	0x0d},
								{0x5f0f, 	0x0e},
								{0x5f10, 	0x0e},
								{0x5f11, 	0x0e},
								{0x5f12, 	0x0e},
								{0x5f13, 	0x0f},
								{0x5f14, 	0x0f},
								{0x5f15, 	0x10},
								{0x5f16, 	0x11},
								{0x5f17, 	0x11},
								{0x5f18, 	0x12},
								{0x5f19, 	0x12},
								{0x5f1a, 	0x13},
								{0x5f1b, 	0x13},
								{0x5f1c, 	0x14},
								{0x5f1d, 	0x14},
								{0x5f1e, 	0x16},
								{0x5f1f, 	0x16},
								{0x5f20, 	0x16},
								{0x5f21, 	0x08},
								{0x5f22, 	0x00},
								{0x5f23, 	0x01},
								{0x5f26, 	0x02},
								{0x5f27, 	0x00},
								{0x5f29, 	0x02},
								{0x5f2a, 	0x00},
								{0x5f2c, 	0x02},
								{0x5f2d, 	0x00},
								{0x5f2f, 	0x02},
								{0x5f30, 	0x00},
								{0x5f32, 	0x02},
								{0x5f33, 	0x00},
								{0x5f34, 	0x00},
								{0x5f35, 	0x02},
								{0x5f36, 	0x00},
								{0x5f37, 	0x00},
								{0x5f38, 	0x02},
								{0x5f39, 	0x00},
								{0x5f3a, 	0x00},
								{0x5f3b, 	0x02},
								{0x5f3c, 	0x00},
								{0x5f3d, 	0x00},
								{0x5f3e, 	0x02},
								{0x5f3f, 	0x00},
								{0x5f40, 	0x00},
								{0x5f41, 	0x02},
								{0x5f42, 	0x00},
								{0x5f43, 	0x00},
								{0x5f44, 	0x02},
								{0x5f45, 	0x00},
								{0x5f46, 	0x00},
								{0x5f47, 	0x04},
								{0x5f48, 	0x00},
								{0x5f49, 	0x00},
								{0x5f4a, 	0x04},
								{0x5f4b, 	0x00},
								{0x5f4c, 	0x00},
								{0x5f4d, 	0x04},
								{0x5f4e, 	0x00},
								{0x5f50, 	0x04},
								{0x5f51, 	0x00},
								{0x5f53, 	0x04},
								{0x5f54, 	0x00},
								{0x5f56, 	0x04},
								{0x5f57, 	0x00},
								{0x5f59, 	0x04},
								{0x5f5a, 	0x00},
								{0x5f5c, 	0x04},
								{0x5f5d, 	0x00},
								{0x5f5f, 	0x08},
								{0x5f60, 	0x00},
								{0x5f62, 	0x08},
								{0x5f63, 	0x00},
								{0x5f65, 	0x08},
								{0x5f66, 	0x00},
								{0x5f68, 	0x08},
								{0x5f69, 	0x00},
								{0x5f6b, 	0x08},
								{0x5f6c, 	0x00},
								{0x5f6e, 	0x10},
								{0x5f6f, 	0x00},
								{0x5f71, 	0x10},
								{0x5f72, 	0x00},
								{0x5f74, 	0x10},
								{0x5f75, 	0x00},
								{0x5f77, 	0x10},
								{0x5f78, 	0x00},
								{0x5f7a, 	0x20},
								{0x5f7b, 	0x00},
								{0x5f7d, 	0x20},
								{0x5f7e, 	0x00},
								{0x5f80, 	0x20},
								{0x5f81, 	0x00},
								{0x5f83, 	0x00},
								{0x5f84, 	0xff},
								{0x5240, 	0x0f},
								{0x5243, 	0x00},
								{0x5244, 	0x00},
								{0x5245, 	0x00},
								{0x5246, 	0x00},
								{0x5247, 	0x00},
								{0x5248, 	0x00},
								{0x5249, 	0x00},
								{0x5440, 	0x0f},
								{0x5443, 	0x00},
								{0x5445, 	0x00},
								{0x5447, 	0x00},
								{0x5448, 	0x00},
								{0x5449, 	0x00},
								{0x5640, 	0x0f},
								{0x5642, 	0x00},
								{0x5643, 	0x00},
								{0x5644, 	0x00},
								{0x5645, 	0x00},
								{0x5646, 	0x00},
								{0x5647, 	0x00},
								{0x5649, 	0x00},
								{0x5840, 	0x0f},
								{0x5842, 	0x00},
								{0x5843, 	0x00},
								{0x5845, 	0x00},
								{0x5846, 	0x00},
								{0x5847, 	0x00},
								{0x5848, 	0x00},
								{0x5849, 	0x00},
								{0x4001, 	0x2b},
								{0x4008, 	0x02},
								{0x4009, 	0x03},
								{0x4018, 	0x12},
								{0x4022, 	0x40},
								{0x4023, 	0x20},

								// Black Level (default : 0x40)
								{0x4026,	0x00},	//BLK_LVL_TARGET_HCG_H
								{0x4027,	0x00},	//BLK_LVL_TARGET_HCG_L	//40
								{0x4028,	0x00},  //BLK_LVL_TARGET_LCG_H      
								{0x4029,	0x00},	//BLK_LVL_TARGET_LCG_L	//40
								{0x402a,	0x00},  //BLK_LVL_TARGET_SPD_H      
								{0x402b,	0x00},	//BLK_LVL_TARGET_SPD_L	//40
								{0x402c,	0x00},  //BLK_LVL_TARGET_VS_H      
								{0x402d,	0x00},	//BLK_LVL_TARGET_VS_L	//40
								
								{0x405e, 	0x00},
								{0x405f, 	0x00},
								{0x4060, 	0x00},
								{0x4061, 	0x00},
								{0x4062, 	0x00},
								{0x4063, 	0x00},
								{0x4064, 	0x00},
								{0x4065, 	0x00},
								{0x4066, 	0x00},
								{0x4067, 	0x00},
								{0x4068, 	0x00},
								{0x4069, 	0x00},
								{0x406a, 	0x00},
								{0x406b, 	0x00},
								{0x406c, 	0x00},
								{0x406d, 	0x00},
								{0x406e, 	0x00},
								{0x406f, 	0x00},
								{0x4070, 	0x00},
								{0x4071, 	0x00},
								{0x4072, 	0x00},
								{0x4073, 	0x00},
								{0x4074, 	0x00},
								{0x4075, 	0x00},
								{0x4076, 	0x00},
								{0x4077, 	0x00},
								{0x4078, 	0x00},
								{0x4079, 	0x00},
								{0x407a, 	0x00},
								{0x407b, 	0x00},
								{0x407c, 	0x00},
								{0x407d, 	0x00},
								{0x407e, 	0xcc},
								{0x407f, 	0x18},
								{0x4080, 	0xff},
								{0x4081, 	0xff},
								{0x4082, 	0x01},
								{0x4083, 	0x53},
								{0x4084, 	0x01},
								{0x4085, 	0x2b},
								{0x4086, 	0x00},
								{0x4087, 	0xb3},
								{0x4640, 	0x40},
								{0x4641, 	0x11},
								{0x4642, 	0x0e},
								{0x4643, 	0xee},
								{0x4646, 	0x0f},
								{0x4648, 	0x00},
								{0x4649, 	0x03},
								{0x4f04, 	0xf8},
								{0x4d09, 	0xff},
								{0x4d09, 	0xdf},
								{0x5019, 	0x00},
								{0x501a, 	0xff},
								{0x501b, 	0xff},
								{0x501d, 	0x00},
								{0x501e, 	0x23},
								{0x501f, 	0x8e},
								{0x5021, 	0x00},
								{0x5022, 	0x00},
								{0x5023, 	0x50},
								{0x5025, 	0x00},
								{0x5026, 	0x23},
								{0x5027, 	0x8e},
								{0x5003, 	0xFA},			// [7] : awb_revs_en				*
															// [6] : LFM enable				*
															// [5] : Combine enable			*
															// [4] : Pre-Matrix enable			*
															// [3] : Combine sync buffer enable	*
															// [2] : LENC enable	
															// [1] : HDR sync buffer enable	*

								// HDR Combine Weight
								{0x5b80,	0x08},	// SPD-VS	,  Combine method 1: L/S                                                           
								{0x5c00,	0x08},  // LCG-SPD	, combine method 1: L/S                                                            
								{0x5c80,	0x00},  // HCG-LCG	, combine method 1: L/(S*ratio)                                                    
								{0x5bbe,	0x12},  // def=a                                                                                       
								{0x5c3e,	0x12},  // def=a                                                                                       
								{0x5cbe,	0x12},  // def=a               

								//SPD+VS Combine Weight
								{0x5b8a,	0x80},  // w00                                                                                         
								{0x5b8b,	0x80},  // w10                                                                                         
								{0x5b8c,	0x80},  // w20                                                                                         
								{0x5b8d,	0x80},  // w30                                                                                         
								{0x5b8e,	0x80},  // w40                                                                                         
								{0x5b8f,	0x40},  // w01                                                                                         
								{0x5b90,	0x80},  // w11                                                                                         
								{0x5b91,	0x80},  // w21                                                                                         
								{0x5b92,	0x80},  // w31                                                                                         
								{0x5b93,	0x60},  // w41                                                                                         
								{0x5b94,	0x00},  // w02                                                                                         
								{0x5b95,	0x00},  // w12                                                                                         
								{0x5b96,	0x40},  // w22                                                                                         
								{0x5b97,	0x80},  // w32                                                                                         
								{0x5b98,	0x10},  // w42                                                                                         
								{0x5b99,	0x00},  // w03                                                                                         
								{0x5b9a,	0x00},  // w13                                                                                         
								{0x5b9b,	0x00},  // w23                                                                                         
								{0x5b9c,	0x00},  // w33                                                                                         
								{0x5b9d,	0x00},  // w43                                                                                         
								{0x5b9e,	0x00},  // w04                                                                                         
								{0x5b9f,	0x00},  // w14                                                                                         
								{0x5ba0,	0x00},  // w24                                                                                         
								{0x5ba1,	0x00},  // w34                                                                                         
								{0x5ba2,	0x00},  // w44                                                                                         
								{0x5ba3,	0x00},  // w05                                                                                         
								{0x5ba4,	0x00},  // w15                                                                                         
								{0x5ba5,	0x00},  // w25                                                                                         
								{0x5ba6,	0x00},  // w35                                                                                         
								{0x5ba7,	0x00},  // w45           
											
								//Combine Threshold
								//SPD+VS
								{0x5ba8,	0x00},  //Com Thre L0                                                                                  
								{0x5ba9,	0xc0},                                                                                                 
								{0x5baa,	0x01},  //Com Thre L1                                                                                  
								{0x5bab,	0x40},                                                                                                 
								{0x5bac,	0x02},  //Com Thre L2                                                                                  
								{0x5bad,	0x40},                                                                                                 
								{0x5bae,	0x00},  //Com Thre S0                                                                                  
								{0x5baf,	0x50},                                                                                                 
								{0x5bb0,	0x00},  //Com Thre S1                                                                                  
								{0x5bb1,	0x60},                                                                                                 
								{0x5bb2,	0x00},  //Com Thre S2                                                                                  
								{0x5bb3,	0xc0},
							
								//LCG+SPDVS Combine Weight
								{0x5c0a,	0x80},                                                                                                 
								{0x5c0b,	0x80},                                                                                                 
								{0x5c0c,	0x80},                                                                                                 
								{0x5c0d,	0x80},                                                                                                 
								{0x5c0e,	0x60},                                                                                                 
								{0x5c0f,	0x80},                                                                                                 
								{0x5c10,	0x80},                                                                                                 
								{0x5c11,	0x80},                                                                                                 
								{0x5c12,	0x60},                                                                                                 
								{0x5c13,	0x20},                                                                                                 
								{0x5c14,	0x80},                                                                                                 
								{0x5c15,	0x80},                                                                                                 
								{0x5c16,	0x80},                                                                                                 
								{0x5c17,	0x20},                                                                                                 
								{0x5c18,	0x00},                                                                                                 
								{0x5c19,	0x80},                                                                                                 
								{0x5c1a,	0x40},                                                                                                 
								{0x5c1b,	0x20},                                                                                                 
								{0x5c1c,	0x00},                                                                                                 
								{0x5c1d,	0x00},                                                                                                 
								{0x5c1e,	0x80},                                                                                                 
								{0x5c1f,	0x00},                                                                                                 
								{0x5c20,	0x00},                                                                                                 
								{0x5c21,	0x00},                                                                                                 
								{0x5c22,	0x00},                                                                                                 
								{0x5c23,	0x00},                                                                                                 
								{0x5c24,	0x00},                                                                                                 
								{0x5c25,	0x00},                                                                                                 
								{0x5c26,	0x00},                                                                                                 
								{0x5c27,	0x00}, 

								//Combine Threshold
								//LCG+SPDVS
								{0x5c28,	0x02},                                                                                                 
								{0x5c29,	0x00},                                                                                                 
								{0x5c2a,	0x02},                                                                                                 
								{0x5c2b,	0x76},                                                                                                 
								{0x5c2c,	0x03},                                                                                                 
								{0x5c2d,	0x08},                                                                                                 
								{0x5c2e,	0x00},                                                                                                 
								{0x5c2f,	0x80},                                                                                                 
								{0x5c30,	0x01},                                                                                                 
								{0x5c31,	0x00},                                                                                                 
								{0x5c32,	0x02},                                                                                                 
								{0x5c33,	0x00},
									
								//HCG+LCGSPDVS Combine Weight
								{0x5c8a,	0x80},                                                                                                 
								{0x5c8b,	0x80},                                                                                                 
								{0x5c8c,	0x80},                                                                                                 
								{0x5c8d,	0x80},                                                                                                 
								{0x5c8e,	0x80},                                                                                                 
								{0x5c8f,	0x80},                                                                                                 
								{0x5c90,	0x80},                                                                                                 
								{0x5c91,	0x80},                                                                                                 
								{0x5c92,	0x80},                                                                                                 
								{0x5c93,	0x60},                                                                                                 
								{0x5c94,	0x80},                                                                                                 
								{0x5c95,	0x80},                                                                                                 
								{0x5c96,	0x80},                                                                                                 
								{0x5c97,	0x60},                                                                                                 
								{0x5c98,	0x40},                                                                                                 
								{0x5c99,	0x80},                                                                                                 
								{0x5c9a,	0x80},                                                                                                 
								{0x5c9b,	0x80},                                                                                                 
								{0x5c9c,	0x40},                                                                                                 
								{0x5c9d,	0x20},                                                                                                 
								{0x5c9e,	0x80},                                                                                                 
								{0x5c9f,	0x80},                                                                                                 
								{0x5ca0,	0x80},                                                                                                 
								{0x5ca1,	0x20},                                                                                                 
								{0x5ca2,	0x00},                                                                                                 
								{0x5ca3,	0x80},                                                                                                 
								{0x5ca4,	0x80},                                                                                                 
								{0x5ca5,	0x80},                                                                                                 
								{0x5ca6,	0x00},                                                                                                 
								{0x5ca7,	0x00},    

								//Combine Threshold
								//HCG+LCGSPDVS
								{0x5ca8,	0x01},                                                                                                 
								{0x5ca9,	0x00},                                                                                                 
								{0x5caa,	0x02},
								{0x5cab,	0x00},
								{0x5cac,	0x03},
								{0x5cad,	0x08},
								{0x5cae,	0x01},
								{0x5caf,	0x00},
								{0x5cb0,	0x02},
								{0x5cb1,	0x00},
								{0x5cb2,	0x03},
								{0x5cb3,	0x08},
									
								{0x5be7, 	0x80},
								{0x5bc9, 	0x80},
								{0x5bca, 	0x80},
								{0x5bcb, 	0x80},
								{0x5bcc, 	0x80},
								{0x5bcd, 	0x80},
								{0x5bce, 	0x80},
								{0x5bcf, 	0x80},
								{0x5bd0, 	0x80},
								{0x5bd1, 	0x80},
								{0x5bd2, 	0x20},
								{0x5bd3, 	0x80},
								{0x5bd4, 	0x40},
								{0x5bd5, 	0x20},
								{0x5bd6, 	0x00},
								{0x5bd7, 	0x00},
								{0x5bd8, 	0x00},
								{0x5bd9, 	0x00},
								{0x5bda, 	0x00},
								{0x5bdb, 	0x00},
								{0x5bdc, 	0x00},
								{0x5bdd, 	0x00},
								{0x5bde, 	0x00},
								{0x5bdf, 	0x00},
								{0x5be0, 	0x00},
								{0x5be1, 	0x00},
								{0x5be2, 	0x00},
								{0x5be3, 	0x00},
								{0x5be4, 	0x00},
								{0x5be5, 	0x00},
								{0x5be6, 	0x00},
								{0x5c49, 	0x80},
								{0x5c4a, 	0x80},
								{0x5c4b, 	0x80},
								{0x5c4c, 	0x80},
								{0x5c4d, 	0x40},
								{0x5c4e, 	0x80},
								{0x5c4f, 	0x80},
								{0x5c50, 	0x80},
								{0x5c51, 	0x60},
								{0x5c52, 	0x20},
								{0x5c53, 	0x80},
								{0x5c54, 	0x80},
								{0x5c55, 	0x80},
								{0x5c56, 	0x20},
								{0x5c57, 	0x00},
								{0x5c58, 	0x80},
								{0x5c59, 	0x40},
								{0x5c5a, 	0x20},
								{0x5c5b, 	0x00},
								{0x5c5c, 	0x00},
								{0x5c5d, 	0x80},
								{0x5c5e, 	0x00},
								{0x5c5f, 	0x00},
								{0x5c60, 	0x00},
								{0x5c61, 	0x00},
								{0x5c62, 	0x00},
								{0x5c63, 	0x00},
								{0x5c64, 	0x00},
								{0x5c65, 	0x00},
								{0x5c66, 	0x00},
								{0x5cc9, 	0x80},
								{0x5cca, 	0x80},
								{0x5ccb, 	0x80},
								{0x5ccc, 	0x80},
								{0x5ccd, 	0x80},
								{0x5cce, 	0x80},
								{0x5ccf, 	0x80},
								{0x5cd0, 	0x80},
								{0x5cd1, 	0x80},
								{0x5cd2, 	0x60},
								{0x5cd3, 	0x80},
								{0x5cd4, 	0x80},
								{0x5cd5, 	0x80},
								{0x5cd6, 	0x60},
								{0x5cd7, 	0x40},
								{0x5cd8, 	0x80},
								{0x5cd9, 	0x80},
								{0x5cda, 	0x80},
								{0x5cdb, 	0x40},
								{0x5cdc, 	0x20},
								{0x5cdd, 	0x80},
								{0x5cde, 	0x80},
								{0x5cdf, 	0x80},
								{0x5ce0, 	0x20},
								{0x5ce1, 	0x00},
								{0x5ce2, 	0x80},
								{0x5ce3, 	0x80},
								{0x5ce4, 	0x80},
								{0x5ce5, 	0x00},
								{0x5ce6, 	0x00},
								{0x5b84, 	0x02},
								{0x5b85, 	0xcc},
								{0x5bb4, 	0x05},
								{0x5bb5, 	0xc6},
								{0x5c04, 	0x02},
								{0x5c05, 	0xcc},
								{0x5c34, 	0x05},
								{0x5c35, 	0x33},
								{0x5c84, 	0x02},
								{0x5c85, 	0xcc},
								{0x5cb4, 	0x05},
								{0x5cb5, 	0x33},
								{0x5bbf, 	0x00},
								{0x5bc0, 	0x04},
								{0x5bc1, 	0x06},
								{0x5bc2, 	0xff},
								{0x5bc3, 	0x00},
								{0x5bc4, 	0x04},
								{0x5bc5, 	0x02},
								{0x5bc6, 	0xb8},
								{0x5c3f, 	0x00},
								{0x5c40, 	0x04},
								{0x5c41, 	0x07},
								{0x5c42, 	0xff},
								{0x5c43, 	0x00},
								{0x5c44, 	0x04},
								{0x5c45, 	0x03},
								{0x5c46, 	0xb8},
								{0x5cbf, 	0x00},
								{0x5cc0, 	0x20},
								{0x5cc1, 	0x07},
								{0x5cc2, 	0xff},
								{0x5cc3, 	0x00},
								{0x5cc4, 	0x20},
								{0x5cc5, 	0x03},
								{0x5cc6, 	0x00},
								{0x5b86, 	0x05},
								{0x5c06, 	0x05},
								{0x5c86, 	0x05},
								{0x5bb8, 	0x01},
								{0x5bb9, 	0x01},
								{0x5c38, 	0x01},
								{0x5c39, 	0x01},
								{0x5cb8, 	0x01},
								{0x5cb9, 	0x01},
								{0x5bc7, 	0x00},
								{0x5bc8, 	0x80},
								{0x5c47, 	0x00},
								{0x5c48, 	0x80},
								{0x5cc7, 	0x00},
								{0x5cc8, 	0x80},
								{0x5bba, 	0x01},
								{0x5bbb, 	0x00},
								{0x5c3a, 	0x01},
								{0x5c3b, 	0x00},
								{0x5cba, 	0x01},
								{0x5cbb, 	0x00},
								{0x5d74, 	0x01},
								{0x5d75, 	0x00},
								{0x5d1f, 	0x81},
								{0x5d11, 	0x00},
								{0x5d12, 	0x10},
								{0x5d13, 	0x10},
								{0x5d15, 	0x05},
								{0x5d16, 	0x05},
								{0x5d17, 	0x05},
								{0x5d08, 	0x03},
								{0x5d09, 	0x6b},
								{0x5d0a, 	0x03},
								{0x5d0b, 	0x6b},
								{0x5d18, 	0x03},
								{0x5d19, 	0x6b},
								{0x5b40, 	0x01},
								{0x5b41, 	0x00},
								{0x5b42, 	0x00},
								{0x5b43, 	0x00},
								{0x5b44, 	0x00},
								{0x5b45, 	0x00},
								{0x5b46, 	0x00},
								{0x5b47, 	0x00},
								{0x5b48, 	0x01},
								{0x5b49, 	0x00},
								{0x5b4a, 	0x00},
								{0x5b4b, 	0x00},
								{0x5b4c, 	0x00},
								{0x5b4d, 	0x00},
								{0x5b4e, 	0x00},
								{0x5b4f, 	0x00},
								{0x5b50, 	0x01},
								{0x5b51, 	0x00},
								{0x5b52, 	0x01},
								{0x5b53, 	0x00},
								{0x5b54, 	0x00},
								{0x5b55, 	0x00},
								{0x5b56, 	0x00},
								{0x5b57, 	0x00},
								{0x5b58, 	0x00},
								{0x5b59, 	0x00},
								{0x5b5a, 	0x01},
								{0x5b5b, 	0x00},
								{0x5b5c, 	0x00},
								{0x5b5d, 	0x00},
								{0x5b5e, 	0x00},
								{0x5b5f, 	0x00},
								{0x5b60, 	0x00},
								{0x5b61, 	0x00},
								{0x5b62, 	0x01},
								{0x5b63, 	0x00},
								{0x5b64, 	0x01},
								{0x5b65, 	0x00},
								{0x5b66, 	0x00},
								{0x5b67, 	0x00},
								{0x5b68, 	0x00},
								{0x5b69, 	0x00},
								{0x5b6a, 	0x00},
								{0x5b6b, 	0x00},
								{0x5b6c, 	0x01},
								{0x5b6d, 	0x00},
								{0x5b6e, 	0x00},
								{0x5b6f, 	0x00},
								{0x5b70, 	0x00},
								{0x5b71, 	0x00},
								{0x5b72, 	0x00},
								{0x5b73, 	0x00},
								{0x5b74, 	0x01},
								{0x5b75, 	0x00},
								{0x5b78, 	0x00},
								{0x5b79, 	0x4c},
								{0x5b7a, 	0x00},
								{0x5b7b, 	0xb9},
								{0x5b7c, 	0x01},
								{0x5b7d, 	0x38},
								{0x5b7e, 	0x01},
								{0x5280, 	0x04},
								{0x5281, 	0x00},
								{0x5282, 	0x04},
								{0x5283, 	0x00},
								{0x5284, 	0x04},
								{0x5285, 	0x00},
								{0x5286, 	0x04},
								{0x5287, 	0x00},
								{0x5480, 	0x04},
								{0x5481, 	0x00},
								{0x5482, 	0x04},
								{0x5483, 	0x00},
								{0x5484, 	0x04},
								{0x5485, 	0x00},
								{0x5486, 	0x04},
								{0x5487, 	0x00},
								{0x5680, 	0x04},
								{0x5681, 	0x00},
								{0x5682, 	0x04},
								{0x5683, 	0x00},
								{0x5684, 	0x04},
								{0x5685, 	0x00},
								{0x5686, 	0x04},
								{0x5687, 	0x00},
								{0x5880, 	0x04},
								{0x5881, 	0x00},
								{0x5882, 	0x04},
								{0x5883, 	0x00},
								{0x5884, 	0x04},
								{0x5885, 	0x00},
								{0x5886, 	0x04},
								{0x5887, 	0x00},
								{0x52c6, 	0x00},
								{0x52c7, 	0x12},
								{0x52c8, 	0x04},
								{0x52c9, 	0x02},
								{0x52ca, 	0x01},
								{0x52cb, 	0x01},
								{0x52cc, 	0x04},
								{0x52cd, 	0x02},
								{0x52ce, 	0x01},
								{0x52cf, 	0x01},
								{0x52d0, 	0x03},
								{0x52d1, 	0x08},
								{0x52d2, 	0x0c},
								{0x54c6, 	0x00},
								{0x54c7, 	0x12},
								{0x54c8, 	0x04},
								{0x54c9, 	0x02},
								{0x54ca, 	0x01},
								{0x54cb, 	0x01},
								{0x54cc, 	0x04},
								{0x54cd, 	0x02},
								{0x54ce, 	0x01},
								{0x54cf, 	0x01},
								{0x54d0, 	0x03},
								{0x54d1, 	0x08},
								{0x54d2, 	0x0c},
								{0x56c6, 	0x00},
								{0x56c7, 	0x12},
								{0x56c8, 	0x04},
								{0x56c9, 	0x02},
								{0x56ca, 	0x01},
								{0x56cb, 	0x01},
								{0x56cc, 	0x04},
								{0x56cd, 	0x02},
								{0x56ce, 	0x01},
								{0x56cf, 	0x01},
								{0x56d0, 	0x03},
								{0x56d1, 	0x08},
								{0x56d2, 	0x0c},
								{0x58c6, 	0x00},
								{0x58c7, 	0x12},
								{0x58c8, 	0x04},
								{0x58c9, 	0x02},
								{0x58ca, 	0x01},
								{0x58cb, 	0x01},
								{0x58cc, 	0x04},
								{0x58cd, 	0x02},
								{0x58ce, 	0x01},
								{0x58cf, 	0x01},
								{0x58d0, 	0x03},
								{0x58d1, 	0x08},
								{0x58d2, 	0x0c},
								{0x5004, 	0x1e},
								{0x610a, 	0x07},
								{0x610b, 	0x80},
								{0x610c, 	0x05},
								{0x610d, 	0x00},
								{0x6102, 	0x3f},
								{0x6120, 	0x75},
								{0x6121, 	0x75},
								{0x6122, 	0x75},
								{0x6123, 	0x75},
								{0x6124, 	0x75},
								{0x6125, 	0x75},
								{0x6126, 	0x75},
								{0x6127, 	0x75},
								{0x6128, 	0x75},
								{0x6129, 	0x75},
								{0x612a, 	0x75},
								{0x612b, 	0x75},
								{0x612c, 	0x75},
								{0x612d, 	0x75},
								{0x612e, 	0x75},
								{0x612f, 	0x75},
								{0x6130, 	0x75},
								{0x6131, 	0x75},
								{0x6132, 	0x75},
								{0x6133, 	0x75},
								{0x6134, 	0x75},
								{0x6135, 	0x75},
								{0x6136, 	0x75},
								{0x6137, 	0x75},
								{0x6138, 	0x75},
								{0x6139, 	0x75},
								{0x613a, 	0x75},
								{0x613b, 	0x75},
								{0x613c, 	0x75},
								{0x613d, 	0x75},
								{0x613e, 	0x75},
								{0x613f, 	0x75},
								{0x6140, 	0x75},
								{0x6141, 	0x75},
								{0x6142, 	0x75},
								{0x6143, 	0x75},
								{0x6144, 	0x75},
								{0x6145, 	0x75},
								{0x6146, 	0x75},
								{0x6147, 	0x75},
								{0x6148, 	0x75},
								{0x6149, 	0x75},
								{0x614a, 	0x75},
								{0x614b, 	0x75},
								{0x614c, 	0x75},
								{0x614d, 	0x75},
								{0x614e, 	0x75},
								{0x614f, 	0x75},
								{0x6150, 	0x75},
								{0x6151, 	0x75},
								{0x6152, 	0x75},
								{0x6153, 	0x75},
								{0x6154, 	0x75},
								{0x6155, 	0x75},
								{0x6156, 	0x75},
								{0x6157, 	0x75},
								{0x6158, 	0x75},
								{0x6159, 	0x75},
								{0x615a, 	0x75},
								{0x615b, 	0x75},
								{0x615c, 	0x75},
								{0x615d, 	0x75},
								{0x615e, 	0x75},
								{0x615f, 	0x75},
								{0x6160, 	0x75},
								{0x6161, 	0x75},
								{0x6162, 	0x75},
								{0x6163, 	0x75},
								{0x6164, 	0x75},
								{0x6165, 	0x75},
								{0x6166, 	0x75},
								{0x6167, 	0x75},
								{0x6168, 	0x75},
								{0x6169, 	0x75},
								{0x616a, 	0x75},
								{0x616b, 	0x75},
								{0x616c, 	0x75},
								{0x616d, 	0x75},
								{0x616e, 	0x75},
								{0x616f, 	0x75},
								{0x6170, 	0x75},
								{0x6171, 	0x75},
								{0x6172, 	0x75},
								{0x6173, 	0x75},
								{0x6174, 	0x75},
								{0x6175, 	0x75},
								{0x6176, 	0x75},
								{0x6177, 	0x75},
								{0x6178, 	0x75},
								{0x6179, 	0x75},
								{0x617a, 	0x75},
								{0x617b, 	0x75},
								{0x617c, 	0x75},
								{0x617d, 	0x75},
								{0x617e, 	0x75},
								{0x617f, 	0x75},
								{0x6180, 	0x75},
								{0x6181, 	0x75},
								{0x6182, 	0x75},
								{0x6183, 	0x75},
								{0x6184, 	0x75},
								{0x6185, 	0x75},
								{0x6186, 	0x75},
								{0x6187, 	0x75},
								{0x6188, 	0x75},
								{0x6189, 	0x75},
								{0x618a, 	0x75},
								{0x618b, 	0x75},
								{0x618c, 	0x75},
								{0x618d, 	0x75},
								{0x618e, 	0x75},
								{0x618f, 	0x75},
								{0x6190, 	0x75},
								{0x6191, 	0x75},
								{0x6192, 	0x75},
								{0x6193, 	0x75},
								{0x6194, 	0x75},
								{0x6195, 	0x75},
								{0x6196, 	0x75},
								{0x6197, 	0x75},
								{0x6198, 	0x75},
								{0x6199, 	0x75},
								{0x619a, 	0x75},
								{0x619b, 	0x75},
								{0x619c, 	0x75},
								{0x619d, 	0x75},
								{0x619e, 	0x75},
								{0x619f, 	0x75},
								{0x61a0, 	0x75},
								{0x61a1, 	0x75},
								{0x61a2, 	0x75},
								{0x61a3, 	0x75},
								{0x61a4, 	0x75},
								{0x61a5, 	0x75},
								{0x61a6, 	0x75},
								{0x61a7, 	0x75},
								{0x61a8, 	0x75},
								{0x61a9, 	0x75},
								{0x61aa, 	0x75},
								{0x61ab, 	0x75},
								{0x61ac, 	0x75},
								{0x61ad, 	0x75},
								{0x61ae, 	0x75},
								{0x61af, 	0x75},
								{0x5d62, 	0x07},
								{0x5d40, 	0x02},
								{0x5d41, 	0x01},
								{0x5d63, 	0x08},
								{0x5d64, 	0x01},
								{0x5d65, 	0xff},
								{0x5d56, 	0x00},
								{0x5d57, 	0x20},
								{0x5d58, 	0x00},
								{0x5d59, 	0x20},
								{0x5d5a, 	0x00},
								{0x5d5b, 	0x0c},
								{0x5d5c, 	0x02},
								{0x5d5d, 	0x40},
								{0x5d5e, 	0x02},
								{0x5d5f, 	0x40},
								{0x5d60, 	0x03},
								{0x5d61, 	0x40},
								{0x5d4a, 	0x02},
								{0x5d4b, 	0x40},
								{0x5d4c, 	0x02},
								{0x5d4d, 	0x40},
								{0x5d4e, 	0x02},
								{0x5d4f, 	0x40},
								{0x5d50, 	0x18},
								{0x5d51, 	0x80},
								{0x5d52, 	0x18},
								{0x5d53, 	0x80},
								{0x5d54, 	0x18},
								{0x5d55, 	0x80},
								{0x5d46, 	0x20},
								{0x5d47, 	0x00},
								{0x5d48, 	0x22},
								{0x5d49, 	0x00},
								{0x5d42, 	0x20},
								{0x5d43, 	0x00},
								{0x5d44, 	0x22},
								{0x5d45, 	0x00},
								{0x4221, 	0x03},
							
							#if(0)
								// VTS, HTS
								{0x380e, 	0x02},
								{0x380f, 	0x71},
								{0x380c, 	0x04},
								{0x380d, 	0xb0},
								{0x384c, 	0x02},
								{0x384d, 	0x58},
								{0x388c, 	0x02},
								{0x388d, 	0x58},
								
								// Exposure Time
								{0x3501, 	0x01},
								{0x3502, 	0xc8},
								{0x3541, 	0x01},
								{0x3542, 	0xc4},
							#endif
								{0x35c1, 	0x00},
								{0x35c2, 	0x20},
							
								{0x420e, 	0x54},
								{0x420f, 	0xa0},
								{0x4210, 	0xca},
								{0x4211, 	0xf2},
								{0x507a, 	0x5f},
								{0x507b, 	0x46},
								{0x4f00, 	0x00},
								{0x4f01, 	0x01},
								{0x4f02, 	0x80},
								{0x4f03, 	0x2c}
								};

	const WORD gwTblSens_Mode[][3] = {
								//ADDR		//NOR 2M30P		//NOR 2M60P
								{0x0307, 	0x03,			0x01},		//pll1_divm
								{0x380e, 	0x02,			0x02},		//VTS_H			(V-Total)
								{0x380f, 	0x71,			0x71},		//VTS_L			(V-Total)
								{0x380c, 	0x09,			0x04},		//HTS_DCG_H		(Dual Conversion Gain - Long)
								{0x380d, 	0x60,			0xb0},		//HTS_DCG_L		(Dual Conversion Gain - Long)
								{0x384c, 	0x04,			0x02},		//HTS_SPD_H		(Short Photo Diod - Short)
								{0x384d, 	0xb0,			0x58},		//HTS_SPD_L		(Short Photo Diod - Short)
								{0x388c, 	0x04,			0x02},		//HTS_VS_H		(Very Short)
								{0x388d, 	0xb0,			0x58},		//HTS_VS_L		(Very Short)
								};

const UINT gTblSensBaseEa	= numberof(gwTblSens_Base);
const UINT gTblSensModeEa	= numberof(gwTblSens_Mode);

// -----------------------------------------------------------------------------------------
// AE
// -----------------------------------------------------------------------------------------
	// Float Table
	const BYTE 	gbAeHssFltTbl[] = {
								0 ,
								0 ,
								0 ,
								0 ,
                                16,
                                13,
                                11,
                                10,
                                8 ,
                                8 ,
                                7 , 
                                6 ,
                                6 ,
                                6 , 
                                5 ,
                                5 ,
                                5 ,
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
                                2 ,
								1 ,
								1 ,
								1 ,
								1 
								};

	// Shutter Table
	const UINT	gnAeShtTbl[][2] = {
								{0	 , 256    },
								{14  , 300    },
								{28  , 353    },
								{42  , 415    },
								{56  , 487    },
								{70  , 573    },
								{84  , 673    },
								{98  , 791    },
								{112 , 929    },
								{126 , 1092   },
								{140 , 1283   },
								{154 , 1507   },
								{168 , 1771   },
								{182 , 2080   },
								{196 , 2444   },
								{210 , 2872   },
								{224 , 3374   },
								{238 , 3964   },
								{252 , 4658   },
								{266 , 5473   },
								{280 , 6430   },
								{294 , 7555   },
								{308 , 8876   },
								{322 , 10428  },
								{336 , 12252  },
								{350 , 14395  },
								{364 , 16913  },
								{378 , 19871  },
								{392 , 23347  },
								{406 , 27430  },
								{420 , 32228  },
								{434 , 37865  },
								{448 , 44487  },
								{462 , 52268  },
								{476 , 61410  },
								{490 , 72150  },
								{504 , 84769  },
								{518 , 99595  },
								{532 , 117014 },
								{546 , 137480 },
								{560 , 161525 },
								{574 , 189775 },
								{588 , 222966 },
								{602 , 261963 },
								{616 , 307779 },
								{630 , 361609 },
								{644 , 424854 },
								{658 , 499160 },
								{672 , 586462 },
								{686 , 689032 },
								{700 , 809543 },
								{714 , 951130 },
								{728 , 1117480},
								{742 , 1312925},
								{756 , 1542552},
								{770 , 1812341},
								{784 , 2129315},
								{798 , 2501727},
								{812 , 2939273},
								{826 , 3453344},
								{840 , 4057326},
								{854 , 4766943},
								{868 , 5600669},
								{882 , 6580213},
							    {896 , 7731076},
							    {910 , 9083222}
								};

	// 201126 PC : Gain table made by Park Chan
	const WORD wGain_table[][2] = {				
							  	{0x10,0x400},
								{0x10,0x40c},
								{0x10,0x418},
								{0x10,0x424},
								{0x10,0x431},
								{0x11,0x400},
								{0x11,0x40c},
								{0x11,0x418},
								{0x11,0x424},
								{0x11,0x431},
								{0x12,0x400},
								{0x12,0x40c},
								{0x12,0x418},
								{0x12,0x424},
								{0x12,0x431},
								{0x13,0x400},
								{0x13,0x40c},
								{0x13,0x418},
								{0x13,0x424},
								{0x14,0x400},
								{0x14,0x40c},
								{0x14,0x418},
								{0x14,0x424},
								{0x14,0x431},
								{0x15,0x400},
								{0x15,0x40c},
								{0x15,0x418},
								{0x15,0x424},
								{0x16,0x400},
								{0x16,0x40c},
								{0x16,0x418},
								{0x16,0x424},
								{0x17,0x400},
								{0x17,0x40c},
								{0x17,0x418},
								{0x18,0x400},
								{0x18,0x40c},
								{0x18,0x418},
								{0x18,0x424},
								{0x19,0x400},
								{0x19,0x40c},
								{0x19,0x418},
								{0x1a,0x400},
								{0x1a,0x40c},
								{0x1a,0x418},
								{0x1b,0x400},
								{0x1b,0x40c},
								{0x1b,0x418},
								{0x1b,0x424},
								{0x1c,0x400},
								{0x1c,0x40c},
								{0x1c,0x418},
								{0x1d,0x400},
								{0x1d,0x40c},
								{0x1d,0x418},
								{0x1e,0x400},
								{0x1e,0x40c},
								{0x1f,0x400},
								{0x1f,0x40c},
								{0x1f,0x418},
								{0x20,0x400},
								{0x20,0x40c},
								{0x20,0x418},
								{0x20,0x424},
								{0x20,0x430},
								{0x22,0x400},
								{0x22,0x40c},
								{0x22,0x418},
								{0x22,0x424},
								{0x22,0x431},
								{0x24,0x400},
								{0x24,0x40c},
								{0x24,0x418},
								{0x24,0x424},
								{0x24,0x431},
								{0x26,0x400},
								{0x26,0x40c},
								{0x26,0x418},
								{0x26,0x424},
								{0x26,0x431},
								{0x28,0x400},
								{0x28,0x40c},
								{0x28,0x418},
								{0x28,0x424},
								{0x2a,0x400},
								{0x2a,0x40c},
								{0x2a,0x418},
								{0x2a,0x424},	
								{0x2c,0x400},
								{0x2c,0x40c},
								{0x2c,0x418},
								{0x2c,0x424},
								{0x2e,0x400},
								{0x2e,0x40c},
								{0x2e,0x418},
								{0x30,0x400},
								{0x30,0x40c},
								{0x30,0x418},
								{0x30,0x424},
								{0x32,0x400},
								{0x32,0x40c},
								{0x32,0x418},
								{0x34,0x400},
								{0x34,0x40c},
								{0x34,0x418},
								{0x34,0x424},	
								{0x36,0x400},
								{0x36,0x40c},
								{0x36,0x418},
								{0x38,0x400},
								{0x38,0x40c},
								{0x38,0x418},
								{0x3a,0x400},
								{0x3a,0x40c},
								{0x3a,0x418},
								{0x3c,0x400},
								{0x3c,0x40c},
								{0x3c,0x418},
								{0x3e,0x400},
								{0x3e,0x40c},
								{0x40,0x400},
								{0x40,0x40c},
								{0x40,0x418},
								{0x40,0x424},
								{0x40,0x431},
								{0x40,0x43d},
								{0x44,0x400},
								{0x44,0x40c},
								{0x44,0x418},
								{0x44,0x424},
								{0x48,0x400},
								{0x48,0x40c},
								{0x48,0x418},
								{0x48,0x424},
								{0x48,0x431},
								{0x4c,0x400},
								{0x4c,0x40c},
								{0x4c,0x418},
								{0x4c,0x424},
								{0x4c,0x431},
								{0x50,0x400},
								{0x50,0x40c},
								{0x50,0x418},
								{0x50,0x424},
								{0x54,0x400},
								{0x54,0x40c},
								{0x54,0x418},
								{0x54,0x424},
								{0x58,0x400},
								{0x58,0x40c},
								{0x58,0x418},
								{0x58,0x424},
								{0x5c,0x400},
								{0x5c,0x40c},
								{0x5c,0x418},
								{0x5c,0x424},
								{0x60,0x400},
								{0x60,0x40c},
								{0x60,0x418},
								{0x60,0x424},
								{0x64,0x400},
								{0x64,0x40c},
								{0x64,0x418},
								{0x68,0x400},
								{0x68,0x40c},
								{0x68,0x418},
								{0x6c,0x400},
								{0x6c,0x40c},
								{0x6c,0x418},
								{0x70,0x400},
								{0x70,0x40c},
								{0x70,0x418},
								{0x74,0x400},
								{0x74,0x40c},
								{0x74,0x418},
								{0x78,0x400},
								{0x78,0x40c},
								{0x78,0x418},
								{0x7c,0x400},
								{0x7c,0x40c},
								{0x80,0x400},
								{0x80,0x40c},
								{0x80,0x418},
								{0x80,0x424},
								{0x80,0x431},
								{0x80,0x43d},	
								{0x88,0x400},
								{0x88,0x40c},
								{0x88,0x418},
								{0x88,0x424},
								{0x90,0x400},
								{0x90,0x40c},
								{0x90,0x418},
								{0x90,0x424},
								{0x90,0x431},
								{0x90,0x43d},
								{0x98,0x400},
								{0x98,0x40c},
								{0x98,0x418},
								{0x98,0x424},
								{0xa0,0x400},
								{0xa0,0x40c},
								{0xa0,0x418},
								{0xa0,0x424},
								{0xa8,0x400},
								{0xa8,0x40c},
								{0xa8,0x418},
								{0xa8,0x424},
								{0xb0,0x400},
								{0xb0,0x40c},
								{0xb0,0x418},
								{0xb0,0x424},
								{0xb8,0x400},
								{0xb8,0x40c},
								{0xb8,0x418},
								{0xb8,0x424},
								{0xc0,0x400},
								{0xc0,0x40c},
								{0xc0,0x418},
								{0xc0,0x424},
								{0xc8,0x400},
								{0xc8,0x40c},
								{0xc8,0x418},
								{0xd0,0x400},
								{0xd0,0x40c},
								{0xd0,0x418},
								{0xd8,0x400},
								{0xd8,0x40c},
								{0xd8,0x418},
								{0xd8,0x424},
								{0xe0,0x400},
								{0xe0,0x40c},
								{0xe8,0x400},
								{0xe8,0x40c},
								{0xe8,0x418},
								{0xf0,0x400},
								{0xf0,0x40c},
								{0xf0,0x418},
								{0xf8,0x400},   	
								{0xf8,0x40c}, //*******digital gain *******
								{0xf8,0x418},
								{0xf8,0x424},
								{0xf8,0x431},
								{0xf8,0x43d},
								{0xf8,0x44a},
								{0xf8,0x456},
								{0xf8,0x463},
								{0xf8,0x470},
								{0xf8,0x47d},
								{0xf8,0x48b},
								{0xf8,0x498},
								{0xf8,0x4a6},
								{0xf8,0x4b4},
								{0xf8,0x4c2},
								{0xf8,0x4d0},
								{0xf8,0x4de},
								{0xf8,0x4ec},
								{0xf8,0x4fb},
								{0xf8,0x50a},
								{0xf8,0x519},
								{0xf8,0x528},
								{0xf8,0x537},
								{0xf8,0x546},
								{0xf8,0x556},
								{0xf8,0x566},
								{0xf8,0x576},
								{0xf8,0x586},
								{0xf8,0x596},
								{0xf8,0x5a7},
								{0xf8,0x5b8},
								{0xf8,0x5c9},
								{0xf8,0x5da},
								{0xf8,0x5eb},
								{0xf8,0x5fd},
								{0xf8,0x60e},
								{0xf8,0x620},
								{0xf8,0x632},
								{0xf8,0x645},
								{0xf8,0x657},
								{0xf8,0x66a},
								{0xf8,0x67d},
								{0xf8,0x690},
								{0xf8,0x6a4},
								{0xf8,0x6b8},
								{0xf8,0x6cc},
								{0xf8,0x6e0},
								{0xf8,0x6f4},
								{0xf8,0x709},
								{0xf8,0x71d},
								{0xf8,0x733},
								{0xf8,0x748},
								{0xf8,0x75d},
								{0xf8,0x773},
								{0xf8,0x789},
								{0xf8,0x7a0},
								{0xf8,0x7b6},
								{0xf8,0x7cd},
								{0xf8,0x7e4},
								{0xf8,0x7fc},
								{0xf8,0x813},
								{0xf8,0x82b},
								{0xf8,0x843},
								{0xf8,0x85c},
								{0xf8,0x875},
								{0xf8,0x88e},
								{0xf8,0x8a7},
								{0xf8,0x8c1},
								{0xf8,0x8db},
								{0xf8,0x8f5},
								{0xf8,0x90f},
								{0xf8,0x92a},
								{0xf8,0x946},
								{0xf8,0x961},
								{0xf8,0x97d},
								{0xf8,0x999},
								{0xf8,0x9b5},
								{0xf8,0x9d2},
								{0xf8,0x9ef},
								{0xf8,0xa0d},
								{0xf8,0xa2a},
								{0xf8,0xa49},
								{0xf8,0xa67},
								{0xf8,0xa86},
								{0xf8,0xaa5},
								{0xf8,0xac5},
								{0xf8,0xae5},
								{0xf8,0xb05},
								{0xf8,0xb25},
								{0xf8,0xb47},
								{0xf8,0xb68},
								{0xf8,0xb8a},
								{0xf8,0xbac},
								{0xf8,0xbcf},
								{0xf8,0xbf2},
								{0xf8,0xc15},
								{0xf8,0xc39},
								{0xf8,0xc5d},
								{0xf8,0xc82},
								{0xf8,0xca7},
								{0xf8,0xccc},
								{0xf8,0xcf2},
								{0xf8,0xd18},
								{0xf8,0xd3f},
								{0xf8,0xd67},
								{0xf8,0xd8e},
								{0xf8,0xdb6},
								{0xf8,0xddf},
								{0xf8,0xe08},
								{0xf8,0xe32},
								{0xf8,0xe5c},
								{0xf8,0xe86},
								{0xf8,0xeb1},
								{0xf8,0xedd},
								{0xf8,0xf09},
								{0xf8,0xf36},
								{0xf8,0xf63},
								{0xf8,0xf90},
								{0xf8,0xfbe},
								{0xf8,0xfed},
								{0xf8,0x101c},
								{0xf8,0x104c},
								{0xf8,0x107c},
								{0xf8,0x10ad},
								{0xf8,0x10df},
								{0xf8,0x1111},
								{0xf8,0x1143},
								{0xf8,0x1176},
								{0xf8,0x11aa},
								{0xf8,0x11df},
								{0xf8,0x1214},
								{0xf8,0x1249},
								{0xf8,0x127f},
								{0xf8,0x12b6},
								{0xf8,0x12ee},
								{0xf8,0x1326},
								{0xf8,0x135e},
								{0xf8,0x1398},
								{0xf8,0x13d2},
								{0xf8,0x140d},
								{0xf8,0x1448},
								{0xf8,0x1484},
								{0xf8,0x14c1},
								{0xf8,0x14ff},
								{0xf8,0x153d},
								{0xf8,0x157c},
								{0xf8,0x15bb},
								{0xf8,0x15fc},
								{0xf8,0x163d},
								{0xf8,0x167f},
								{0xf8,0x16c2},
								{0xf8,0x1705},
								{0xf8,0x1749},
								{0xf8,0x178e},
								{0xf8,0x17d4},
								{0xf8,0x181b},
								{0xf8,0x1862},
								{0xf8,0x18aa},
								{0xf8,0x18f4},
								{0xf8,0x193e},
								{0xf8,0x1988},
								{0xf8,0x19d4},
								{0xf8,0x1a21},
								{0xf8,0x1a6e},
								{0xf8,0x1abc},
								{0xf8,0x1b0c},
								{0xf8,0x1b5c},
								{0xf8,0x1bad},
								{0xf8,0x1bff},
								{0xf8,0x1c52},
								{0xf8,0x1ca6},
								{0xf8,0x1cfb},
								{0xf8,0x1d51},
								{0xf8,0x1da8},
								{0xf8,0x1dff},
								{0xf8,0x1e58},
								{0xf8,0x1eb2},
								{0xf8,0x1f0d},
								{0xf8,0x1f69},
								{0xf8,0x1fc6},
								{0xf8,0x2025},
								{0xf8,0x2084},
								{0xf8,0x20e4},
								{0xf8,0x2146},
								{0xf8,0x21a8},
								{0xf8,0x220c},
								{0xf8,0x2271},
								{0xf8,0x22d7},
								{0xf8,0x233e},
								{0xf8,0x23a7},
								{0xf8,0x2411},
								{0xf8,0x247b},
								{0xf8,0x24e8},
								{0xf8,0x2555},
								{0xf8,0x25c4},
								{0xf8,0x2634},
								{0xf8,0x26a5},
								{0xf8,0x2717},
								{0xf8,0x278b},
								{0xf8,0x2800},
								{0xf8,0x2877},
								{0xf8,0x28ef},
								{0xf8,0x2968},
								{0xf8,0x29e3},
								{0xf8,0x2a5f},
								{0xf8,0x2add},
								{0xf8,0x2b5c},
								{0xf8,0x2bdc},
								{0xf8,0x2c5e},
								{0xf8,0x2ce2},
								{0xf8,0x2d67},
								{0xf8,0x2dee},
								{0xf8,0x2e76},
								{0xf8,0x2eff},
								{0xf8,0x2f8b},
								{0xf8,0x3018},
								{0xf8,0x30a6},
								{0xf8,0x3136},
								{0xf8,0x31c8},
								{0xf8,0x325c},
								{0xf8,0x32f1},
								{0xf8,0x3388},
								{0xf8,0x3421},
								{0xf8,0x34bb},
								{0xf8,0x3558},
								{0xf8,0x35f6},
								{0xf8,0x3696},
								{0xf8,0x3738},
								{0xf8,0x37d8},
								{0xf8,0x3881},
								{0xf8,0x3928},
								{0xf8,0x39d2},
								{0xf8,0x3a7d},
								{0xf8,0x3b2b},
								{0xf8,0x3bda},
								{0xf8,0x3c8b},
								{0xf8,0x3d3f},
								{0xf8,0x3df4},
								{0xf8,0x3eac},
								{0xf8,0x3f66}
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
					(_4LANE),\
					/* 12BIT or 10BIT */\
					(_16BIT),\
					/* 3210, 10, 0 */\
					(_3210),\
					/* Word Count */\
					(0xF10),\
					/* MIPI Line information or Virtual channel mode */\
					(_MIPI_VC),\
					(aiWdrMode));
}

void LibInitSens(int aiMode, int aiOption)
{
	// aiMode (Normal)	- 0 : 2M30P, 1 : 2M60P
	// aiOption (HDR)	- 0 : OFF,   1 : ON (HDR)

	UINT i;

	GpioSetLo(GPIO_SRSTN);	WaitUs(10000);		GpioSetHi(GPIO_SRSTN);	WaitUs(10000);

	for(i=0; i<10; i++) {
		if(i2c_write(SENS_OMNI_DEV,1,0) == 0) {
			gbSensorOff = 0;
			TxStrNoIRQ("SI2C connected.", 0, 0);
			break;
		}
	}
	if(gbSensorOff) TxStrNoIRQ("SI2C not connected.", 0, 0);

	LibRdesIsp(aiMode, aiOption);
	
	// Base Register Setting
	SetSens(0x0103, 0x01);
	SetSens(0x0107, 0x01);
	
	WaitUs(10000);
	
	for (i=0; i<gTblSensBaseEa; i++)	{	SetSens(gwTblSens_Base[i][0], (BYTE)gwTblSens_Base[i][1]);}
	
	// Mode Chage Register Setting
	SetSens(0x0100, 0x00);		
	for (i=0; i<gTblSensModeEa; i++)	{	SetSens(gwTblSens_Mode[i][0], (BYTE)gwTblSens_Mode[i][1+aiMode]);}
	SetSens(0x0100, 0x01);						

	//Sensor effective pixel width
	SetSensBst(0x3802, (0x64&0xFFFF), 2);		// Vertical Start address	
	SetSensBst(0x3806, (0x4F0&0xFFFF), 2);		// Vertical End address		
	SetSensBst(0x380A, (0x47E&0xFFFF), 2);		// Vertical Output Size					

	gwVsShtPos0 = 0x30;
	gwVsShtPos1 = 0x245;
	gwVsAgcPos0 = 0x30;
	gwVsAgcPos1 = 0x80;
	gbVsShtLine0 = 6;
	gbVsShtLine1 = 20;
	
	WaitUs(100);

	//Shutter Speed Max
	gnAeNorMax = gnInModeVtw-AE_SHTMAX_OFST;
	
}

void ISPM Sens(AE_SHTLw)(UINT val)
{
	UINT nDCG_SHT, nSPD_SHT, nVS_SHT;
//	static UINT nVS_SHT1d = 0x0;
	
	nDCG_SHT = val;
	nSPD_SHT = val/AE_RATIO_DCG_SPD;
	
//	nDCG_SHT = MAX(0xCE, nDCG_SHT);
	nSPD_SHT = MAX(0xCE, nSPD_SHT);			// 11ms
		
//	nVS_SHT = AE_VS_SHT;	
//	nVS_SHT = (nDCG_SHT/18);			// Ratio : x18
	
	if (gnAeState!=2){
//		nVS_SHT = LibUtlInterp1D (MINMAX(nDCG_SHT, 0x60, 0x245), 0x60, 0x245, 5, 15);
		nVS_SHT = LibUtlInterp1D (MINMAX(nDCG_SHT, gwVsShtPos0, gwVsShtPos1), gwVsShtPos0, gwVsShtPos1, gbVsShtLine0, gbVsShtLine1);
	}
	else{
//		nVS_SHT = LibUtlInterp1D (MINMAX(giCurAgc, 0x30, 0x80), 0x30, 0x80, 15, AE_VS_SHT);
		nVS_SHT = LibUtlInterp1D (MINMAX(giCurAgc, gwVsAgcPos0, gwVsAgcPos1), gwVsAgcPos0, gwVsAgcPos1, gbVsShtLine1, AE_VS_SHT);

	}
	
	nVS_SHT = MINMAX(nVS_SHT, gbVsShtLine0, AE_VS_SHT);

	iVstAddr = 0x64 - ((AE_VS_SHT-nVS_SHT)*2);
	iVendAddr = 0x4F0 - ((AE_VS_SHT-nVS_SHT)*2);
	
	//OX03C10 Exposure Control
	SetSensBst(0x3501, (nDCG_SHT&0xFFFF), 2);			// DCG(HCG, LCG)
	SetSensBst(0x3541, (nSPD_SHT&0xFFFF), 2);			// SPD
	
//	if(nVS_SHT1d != nVS_SHT){
	SetSensBst(0x35C1, (nVS_SHT&0xFFFF), 2);			// VS
//	}
//	nVS_SHT1d = nVS_SHT;
	
	DebugDisp(gbAeDebugOn, Hex, "DCG_SHT__", 24, 24, nDCG_SHT)
	DebugDisp(gbAeDebugOn, Hex, "SPD_SHT__", 25, 24, nSPD_SHT)
	DebugDisp(gbAeDebugOn, Hex, "VS__SHT__", 26, 24, nVS_SHT )
}

void ISPM Sens(AE_AGCw)(UINT val)
{
	// Minimum gain
	BYTE bHCG_Gain = 0x10;
	BYTE bLCG_Gain = 0x14;
	BYTE bSPD_Gain = 0x40;
	BYTE bVS_Gain  = 0x10;

	// Minimum gain
	bHCG_Gain = MAX(0x10, val);
	bLCG_Gain = MAX(0x14, val);
	bSPD_Gain = MAX(0x40, val);
	bVS_Gain  = MAX(0x10, val);

	SetSensBst(0x3508, ((((bHCG_Gain>>4)&0xF)<<8)|((bHCG_Gain&0xF)<<4)), 2);		// DCG(HCG) Real Gain
	SetSensBst(0x3588, ((((bLCG_Gain>>4)&0xF)<<8)|((bLCG_Gain&0xF)<<4)), 2);		// DCG(LCG) Real Gain
	SetSensBst(0x3548, ((((bSPD_Gain>>4)&0xF)<<8)|((bSPD_Gain&0xF)<<4)), 2);		// SPD Real Gain
	SetSensBst(0x35C8, ((((bVS_Gain >>4)&0xF)<<8)|((bVS_Gain &0xF)<<4)), 2);		// VS Real Gain
}

void ISPM Sens(AE_DGCw)(UINT val)
{
	SetSensBst(0x350A, ((((val>>10)&0xF)<<16)|(((val>>2)&0xFF)<<8)|((val&0x3)<<6)), 3);		// DCG(HCG) Digital Gain
	SetSensBst(0x358A, ((((val>>10)&0xF)<<16)|(((val>>2)&0xFF)<<8)|((val&0x3)<<6)), 3);		// DCG(LCG) Digital Gain
	SetSensBst(0x354A, ((((val>>10)&0xF)<<16)|(((val>>2)&0xFF)<<8)|((val&0x3)<<6)), 3);		// SPD Digital Gain
	SetSensBst(0x35CA, ((((val>>10)&0xF)<<16)|(((val>>2)&0xFF)<<8)|((val&0x3)<<6)), 3);		// VS Digital Gain
}

void ISPM Sens(AE_FREQw)(UINT val, UINT val1)
{
	SetSensBst(0x380C, (val1&0xFFFF), 2);		// DCG(HCG) HTS
	SetSensBst(0x384C, ((val1/2)&0xFFFF), 2);	// SPD HTS
	SetSensBst(0x388C, ((val1/2)&0xFFFF), 2);	// VS HTS

	SetSensBst(0x380E, (val&0xFFFF), 2);		// VTS
}

////----------------------------------------------------------------------------------------
//

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

	UINT	nMok = gnInModeVtw;
	UINT	nRem = 0;	
	UINT	nShtMax = 0;
	static 	UINT	gnShtFlt = 0;
	UINT	nShtInt = 0;

	if (gnAeState==0){
		LibAePrgain_L(LibAePrgainIntp(gnShtFlt));
	}
	
	LibAeShtIntp (aiVal, AE_SHT_TBL_EA, AE_HSS_FLT_EA, &gnShtFlt, &nShtInt);
	
	if(anManual){
	  nMok 	= (UINT)(MAX(((int)anManualVal - AE_SHTMAX_OFST), (int)0))/gnInModeVtw;
	  nMok 	= ((nMok*gnInModeVtw)+gnInModeVtw);

	  nShtMax = AE_SHTMAX;
	  nRem = MINMAX(anManualVal, AE_SHTMIN_OFST, nShtMax);
	}
	else {
	  nMok 	= gnInModeVtw;
	  nShtMax = AE_SHTMAX;
	  nRem 	= MIN(nShtInt, nShtMax);
	}
	
	AE_SHTLw(nRem);

//	giCurDss = MAX((int)(nMok/gnInModeVtw)-1, 0);
	
//	DebugDisp(gbAeDebugOn, Dec, "SHT_dss__d", 0, 24, giCurDss	)
	DebugDisp(gbAeDebugOn, Dec, "SHT_int__d", 1, 24, nRem		)
	DebugDisp(gbAeDebugOn, Dec, "SHT_flt__d", 2, 24, gnShtFlt	)

	return ((WORD)nRem);
}

void ISPM AeAGC(int aiVal)
{
	static UINT	gnAgc=0;
	
	gnAgc = AE_GAIN_DENORMAL(aiVal);
	gnAgc = MINMAX(gnAgc, 0, (AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA)+AE_GAIN_UNIT_OVR);

	if (gnAeState!=0){
		AE_AGCw(wGain_table[gnAgc][0]);
		AE_DGCw(wGain_table[gnAgc][1]);
	}
	else{
		AE_AGCw(0x10);		//	x1
		AE_DGCw(0x400);		//	"
	}

	#if(AGC_DBG_TXT)
	DebugDisp(gbAeDebugOn, Hex, "DCG_HG_RG", 28, 24, ((GetSens(0x3508)&0xF)<<8)|((GetSens(0x3509)&0xF0)) )
	DebugDisp(gbAeDebugOn, Hex, "DCG_LG_RG", 29, 24, ((GetSens(0x3588)&0xF)<<8)|((GetSens(0x3589)&0xF0)) )
	DebugDisp(gbAeDebugOn, Hex, "SPD_G__RG", 30, 24, ((GetSens(0x3548)&0xF)<<8)|((GetSens(0x3549)&0xF0)) )
	DebugDisp(gbAeDebugOn, Hex, "VS__G__RG", 31, 24, ((GetSens(0x35C8)&0xF)<<8)|((GetSens(0x35C9)&0xF0)) )

	DebugDisp(gbAeDebugOn, Hex, "DCG_HG_DG", 33, 24, ((GetSens(0x350A)&0xF)<<12)|((GetSens(0x350B)&0xFF)<<4)|((GetSens(0x350C)&0xC0)>>6))
	DebugDisp(gbAeDebugOn, Hex, "DCG_LG_DG", 34, 24, ((GetSens(0x358A)&0xF)<<12)|((GetSens(0x358B)&0xFF)<<4)|((GetSens(0x358C)&0xC0)>>6))
	DebugDisp(gbAeDebugOn, Hex, "SPD_G__DG", 35, 24, ((GetSens(0x354A)&0xF)<<12)|((GetSens(0x354B)&0xFF)<<4)|((GetSens(0x354C)&0xC0)>>6))
	DebugDisp(gbAeDebugOn, Hex, "VS__G__DG", 36, 24, ((GetSens(0x35CA)&0xF)<<12)|((GetSens(0x35CB)&0xFF)<<4)|((GetSens(0x35CC)&0xC0)>>6))
	#endif
}

void LPD_RGBGain(WORD awB, WORD awGb, WORD awGr, WORD awR)
{	
	SetSensBst(0x5280, ((awB<<16)|(awGb)) , 4);		//HCG B,Gb
	SetSensBst(0x5284, ((awGr<<16)|(awR)) , 4);		//HCG Gr, R

	SetSensBst(0x5480, ((awB<<16)|(awGb)) , 4);		//LCG B,Gb
	SetSensBst(0x5484, ((awGr<<16)|(awR)) , 4);		//LCG Gr, R

	SetSensBst(0x5880, ((awB<<16)|(awGb)) , 4);		//VS B,Gb
	SetSensBst(0x5884, ((awGr<<16)|(awR)) , 4);		//VS Gr, R
}

void SPD_RGBGain(WORD awB, WORD awGb, WORD awGr, WORD awR)
{
	SetSensBst(0x5680, ((awB<<16)|(awGb)) , 4);		//SPD B, Gb
	SetSensBst(0x5684, ((awGr<<16)|(awR)) , 4);		//SPD Gr, R
}

void LPD_InvRGBGain(WORD awB, WORD awGb, WORD awGr, WORD awR)
{
	SetSensBst(0x5DA0, ((awB<<16)|(awGb)) , 4);		//SPD B, Gb
	SetSensBst(0x5DA4, ((awGr<<16)|(awR)) , 4);		//SPD Gr, R
}

// -----------------------------------------------------------------------------------------
// Pre-CCM (Ref from omnivision)
// -----------------------------------------------------------------------------------------
const WORD gwSPDPreCCM_LT[3][3] = {									// A (2856K)
								{0x010F, 0x03F1, 0x0000},
								{0x03EB, 0x0104, 0x0011},
								{0x03C8, 0x03BD, 0x017B}
								};

const WORD gwSPDPreCCM_MT[3][3] = {									// CWF (4150K)
								{0x0111, 0x03F4, 0x03FB},
								{0x03F2, 0x0104, 0x000A},
								{0x03EA, 0x03C7, 0x014E}
								};

const WORD gwSPDPreCCM_HT[3][3] = {									// D65 (6500K)
								{0x0114, 0x03F1, 0x03FC},
								{0x03F0, 0x0102, 0x000E},
								{0x03F1, 0x03E4, 0x012B}
								};


void SPD_PreCCM(void)
{
#if(0)
	SetSensBst(0x5B40, ((awRR<<16)|(awRG)) , 4);		//RR, RG
	SetSensBst(0x5B44, ((awRB<<16)|(awGR)) , 4);		//RB, GR
	SetSensBst(0x5B48, ((awGG<<16)|(awGB)) , 4);		//GG, GB
	SetSensBst(0x5B4C, ((awBR<<16)|(awBG)) , 4);		//BR, BG
	SetSensBst(0x5B50, awBB, 2);	// BB
#endif

#if(0)
	// Matrix_D
	ExtWR_Reg(0x5B40, gwSPDPreCCM_HT[0][0], 2); // RR
	ExtWR_Reg(0x5B42, gwSPDPreCCM_HT[0][1], 2); // RG
	ExtWR_Reg(0x5B44, gwSPDPreCCM_HT[0][2], 2); // RB
                                  
	ExtWR_Reg(0x5B46, gwSPDPreCCM_HT[1][0], 2); // GR
	ExtWR_Reg(0x5B48, gwSPDPreCCM_HT[1][1], 2); // GG
	ExtWR_Reg(0x5B4A, gwSPDPreCCM_HT[1][2], 2); // GB
                                  
	ExtWR_Reg(0x5B4C, gwSPDPreCCM_HT[2][0], 2); // BR
	ExtWR_Reg(0x5B4E, gwSPDPreCCM_HT[2][1], 2); // BG
	ExtWR_Reg(0x5B50, gwSPDPreCCM_HT[2][2], 2); // BB
	
	// Matrix_C
	ExtWR_Reg(0x5B52, gwSPDPreCCM_MT[0][0], 2); // RR
	ExtWR_Reg(0x5B54, gwSPDPreCCM_MT[0][1], 2); // RG
	ExtWR_Reg(0x5B56, gwSPDPreCCM_MT[0][2], 2); // RB

	ExtWR_Reg(0x5B58, gwSPDPreCCM_MT[1][0], 2); // GR
	ExtWR_Reg(0x5B5A, gwSPDPreCCM_MT[1][1], 2); // GG
	ExtWR_Reg(0x5B5C, gwSPDPreCCM_MT[1][2], 2); // GB

	ExtWR_Reg(0x5B5E, gwSPDPreCCM_MT[2][0], 2); // BR
	ExtWR_Reg(0x5B60, gwSPDPreCCM_MT[2][1], 2); // BG
	ExtWR_Reg(0x5B62, gwSPDPreCCM_MT[2][2], 2); // BB
	
	// Matrix_A
	ExtWR_Reg(0x5B64, gwSPDPreCCM_LT[0][0], 2); // RR
	ExtWR_Reg(0x5B66, gwSPDPreCCM_LT[0][1], 2); // RG
	ExtWR_Reg(0x5B68, gwSPDPreCCM_LT[0][2], 2); // RB
                                   
	ExtWR_Reg(0x5B6A, gwSPDPreCCM_LT[1][0], 2); // GR
	ExtWR_Reg(0x5B6C, gwSPDPreCCM_LT[1][1], 2); // GG
	ExtWR_Reg(0x5B6E, gwSPDPreCCM_LT[1][2], 2); // GB
                                   
	ExtWR_Reg(0x5B70, gwSPDPreCCM_LT[2][0], 2); // BR
	ExtWR_Reg(0x5B72, gwSPDPreCCM_LT[2][1], 2); // BG
	ExtWR_Reg(0x5B74, gwSPDPreCCM_LT[2][2], 2); // BB
	
#else
	// Matrix_D
	ExtWR_Reg(0x5B40, 0x100, 2); // RR
	ExtWR_Reg(0x5B42, 0x000, 2); // RG
	ExtWR_Reg(0x5B44, 0x000, 2); // RB
                                  
	ExtWR_Reg(0x5B46, 0x000, 2); // GR
//	ExtWR_Reg(0x5B48, 0x100, 2); // GG
	ExtWR_Reg(0x5B48, 0x0D0, 2); // GG
	ExtWR_Reg(0x5B4A, 0x000, 2); // GB
                                  
	ExtWR_Reg(0x5B4C, 0x000, 2); // BR
	ExtWR_Reg(0x5B4E, 0x000, 2); // BG
	ExtWR_Reg(0x5B50, 0x100, 2); // BB

	// Matrix_C
	ExtWR_Reg(0x5B52, 0x100, 2); // RR
	ExtWR_Reg(0x5B54, 0x000, 2); // RG
	ExtWR_Reg(0x5B56, 0x000, 2); // RB

	ExtWR_Reg(0x5B58, 0x000, 2); // GR
	ExtWR_Reg(0x5B5A, 0x100, 2); // GG
	ExtWR_Reg(0x5B5C, 0x000, 2); // GB

	ExtWR_Reg(0x5B5E, 0x000, 2); // BR
	ExtWR_Reg(0x5B60, 0x000, 2); // BG
	ExtWR_Reg(0x5B62, 0x100, 2); // BB

	// Matrix_A
	ExtWR_Reg(0x5B64, 0x100, 2); // RR
	ExtWR_Reg(0x5B66, 0x000, 2); // RG
	ExtWR_Reg(0x5B68, 0x000, 2); // RB
                     
	ExtWR_Reg(0x5B6A, 0x000, 2); // GR
	ExtWR_Reg(0x5B6C, 0x100, 2); // GG
	ExtWR_Reg(0x5B6E, 0x000, 2); // GB
                     
	ExtWR_Reg(0x5B70, 0x000, 2); // BR
	ExtWR_Reg(0x5B72, 0x000, 2); // BG
	ExtWR_Reg(0x5B74, 0x100, 2); // BB
#endif
		
#if(1)
	// 1. AutoMatrixEnable => CurrentCT
	SetSens(0x5B7E, 0x01);			//[0] : 1 : Auto, 0 : Manual
									//[1] : 1 : ManualCT, 0 : CurrentCT 
#else
	#if(1)
	// 2. AutoMatrixEnable => ManualCT
	SetSens(0x5B7E, 0x03);			//[0] : 1 : Auto, 0 : Manual
									//[1] : 1 : ManualCT, 0 : CurrentCT 

//	ExtWR_Reg(0x5B78, UP(UpAWB_CTEMP_LOW), 2);	// CT0
//	ExtWR_Reg(0x5B7A, UP(UpAWB_CTEMP_MID), 2);	// CT1
//	ExtWR_Reg(0x5B7C, UP(UpAWB_CTEMP_HIGH), 2);	// CT2

	ExtWR_Reg(0x5B78, 0x100, 2);	// CT0
	ExtWR_Reg(0x5B7A, 0x200, 2);	// CT1
	ExtWR_Reg(0x5B7C, 0x300, 2); 	// CT2

	ExtWR_Reg(0x5B76, PAR02, 2);	// ManualCT
	#else
	// 3. AutoMatrixDisable => CustomMatrixSel
	SetSens(0x5B7E, 0x00);			//[0] : 1 : Auto, 0 : Manual
									//[1] : 1 : ManualCT, 0 : CurrentCT 

	SetSens(0x5B7F, 0x00);			//[1:0] : 	0 - Matrix A
									//		1 - Matrix C
									//		Other  - Matirx D
	#endif
#endif	
}


// -----------------------------------------------------------------------------------------
// AWB
// -----------------------------------------------------------------------------------------

    //Sensor "G" gain = 0x380 180308 PCB
	const s64 glMtxCf[9][6] =	{
                               	{	      45817990561053LL,	       -106098307828LL,	       -267221700453LL,	          -396221600LL,	           -72310753LL,	          -157203918LL},
								{	      66706010958776LL,	         62523394673LL,	        183311149628LL,	           341663136LL,	            57710355LL,	           189195380LL},
								{	     -98265488289969LL,	       -700686102702LL,	       -828773777231LL,	         -1945700347LL,	          -961979518LL,	         -1134847965LL},
								{	     -71298278851326LL,	       -180225807934LL,	       -221135910201LL,	          -507366707LL,	          -228884732LL,	          -305871425LL},
								{	     213985483185976LL,	        359316113581LL,	        399875070711LL,	           772580557LL,	           418642225LL,	           418556791LL},
								{	      15816061067672LL,	        -98563375474LL,	        183241259702LL,	           195335236LL,	          -359014273LL,	           434073522LL},
								{	       4047337413706LL,	         94267555749LL,	         56005459084LL,	           193881206LL,	           184694817LL,	            46518627LL},
								{	       2753311612625LL,	       -259730758037LL,	       -226696932329LL,	          -714087562LL,	          -436499792LL,	          -460088561LL},
								{	     471463143864336LL,	       1981421673320LL,	       2464328126473LL,	          6046334523LL,	          2994143252LL,	          4136074099LL}
								};

// -----------------------------------------------------------------------------------------
// MIRROR & FLIP
// -----------------------------------------------------------------------------------------

void Sens(SENS_MIRw)(BYTE abOn){
	UNUSED_ARG(abOn);
}

void Sens(SENS_FLPw)(BYTE abOn){
	UNUSED_ARG(abOn);
}

