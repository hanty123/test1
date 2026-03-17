/* **************************************************************************
 File Name	: 	dev_enc.h
 Description:	EN772 - for MODE_T,C,A
 Designer	:	Jo Hong Rae
 Date		:	20. 12. 15
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#if(model_IspO_ANL)
//****************************************************************************
// Extern function
//------------------------------------------------------
extern void ISPM2 ModeAnalog(UINT anMode);

extern void ISPM2 SetENCLv0_RegW(void);
extern void ISPM2 ENCLv0_TBuftoUBuf(void);
extern void ISPM2 ENCLv0_UBuftoTBuf(void);

extern void ISPM2 SetENCLv1_RegW(void);
extern void ISPM2 SetENCLv2_RegW(void);
extern void ISPM2 SetEncExcepRegW(void);

extern BYTE ISPM2 GetENC_ModeIndex(void);
extern void ISPM2 SetENC_CVBS_RegW(void);
extern void ISPM2 SetCVBS(void);
extern void ISPM2 ModeCvbsMnConfig(void);

extern void ISPM2 CTX_Initial(UINT* DSdata);
extern void ISPM CTX_Processing(UINT *anVal, BYTE abMode); // 220718

//****************************************************************************
// Extern variable
//------------------------------------------------------
extern const UINT gnTblCvbsEnc[][3];
extern const UINT gnTblCvbsEncEa;

// 20171205 HTY
extern BYTE gbMAF_Tele,gbMAF_Wide,gbMAF_Near,gbMAF_Far;	
extern BYTE gbUCCKeyOn, gbExUCCKeyOn;

BYTE gbEncParInit;

// 170523 HTY -----------------------------------------------
#define _10Byte_UccOn 	0  // 0: Normal 8BYTE 1: Use speco 10BYTE

//****************************************************************************
// Encoder Configuration
//------------------------------------------------------
#define ANA_MODE_NUM		13
#define	ANA_LV0_NUM			25

// Mode Index
#define ENC_OUT_720P_25		0
#define ENC_OUT_720P_30		1
#define ENC_OUT_720P_50		2
#define ENC_OUT_720P_60		3
#define ENC_OUT_1080P_25	4
#define ENC_OUT_1080P_30	5
#define ENC_OUT_1080P_50	6
#define ENC_OUT_1080P_60	7
#define ENC_OUT_1440P_25	8
#define ENC_OUT_1440P_30	9
#define ENC_OUT_1944P_125	10
#define ENC_OUT_1944P_20	11
#define ENC_OUT_1944P_25	12

// Customizing Structure
typedef struct _tagANALOG_LV0{
	// Encoder Gain
	BYTE ENC_RYGAINP;
	BYTE ENC_RYGAINN;
	BYTE ENC_BYGAINP;
	BYTE ENC_BYGAINN;

	// Encoder Hue
	BYTE ENC_RYHUEP;
	BYTE ENC_RYHUEN;
	BYTE ENC_BYHUEP;
	BYTE ENC_BYHUEN;

	WORD WHITE_LV;
	WORD BLANK_LV;
	WORD PEDESTAL_LV;

	// Burst Frequency
	UINT FSC_TGT;
	
	// Y, Cb, Cr Gain
	WORD Y_MGAIN;
	WORD CB_MGAIN;
	WORD CR_MGAIN;

	WORD CB_BST;
	WORD CR_BST;

	WORD HSC_K;
	WORD HLOCK_CAT;
	WORD VLOCK_CAT_EV;
	WORD VLOCK_CAT_OD;

	// UTC
	WORD CRX_AUTO_CAT;
	WORD CRX_HPOSEVS;
	WORD CRX_HPOSEVE;
	WORD CRX_BITRATE;	
}_ANALOG_LV0;

_ANALOG_LV0 gAnEncLv0;

//enum Encoder LV0 Index
enum{
	ENC_RYGAINP = 0,
	ENC_RYGAINN,
	ENC_BYGAINP,
	ENC_BYGAINN,

	ENC_RYHUEP,
	ENC_RYHUEN,
	ENC_BYHUEP,
	ENC_BYHUEN,

	WHITE_LV,
	BLANK_LV,
	PEDESTAL_LV,

	FSC_TGT,		//11
	
	Y_MGAIN,
	CB_MGAIN,
	CR_MGAIN,

	CB_BST,
	CR_BST,

	HSC_K,
	HLOCK_CAT,
	VLOCK_CAT_EV,
	VLOCK_CAT_OD,

	CRX_AUTO_CAT,
	CRX_HPOSEVS,
	CRX_HPOSEVE,
	CRX_BITRATE,	
};

BYTE gbEncModeIndex;

//****************************************************************************
// Implement 
//------------------------------------------------------
//Encoder Parameter Set & Get Macro
#define	EncPS(N)		((MP(MpAnlForm) == MN_CVBS)?(N##_CVBS__SIZ):(MP(MpAnlForm) == MN_HD_T)?(N##_T__SIZ):(MP(MpAnlForm) == MN_HD_C)?(N##_C__SIZ):(N##_A__SIZ))
#define	EncPI(N)		((MP(MpAnlForm) == MN_CVBS)?(N##_CVBS__IDX):(MP(MpAnlForm) == MN_HD_T)?(N##_T__IDX):(MP(MpAnlForm) == MN_HD_C)?(N##_C__IDX):(N##_A__IDX))

#define	ESP(N,D) 		{if(EncPS(N)==4) 		{gbUsrParTbl[EncPI(N)] = (BYTE)(D); gbUsrParTbl[EncPI(N)+1] = (BYTE)((D)>>8); gbUsrParTbl[EncPI(N)+2] = (BYTE)((D)>>16); gbUsrParTbl[EncPI(N)+3] = (BYTE)((D)>>24); }\
						 else if(EncPS(N)==3) 	{gbUsrParTbl[EncPI(N)] = (BYTE)(D); gbUsrParTbl[EncPI(N)+1] = (BYTE)((D)>>8); gbUsrParTbl[EncPI(N)+2] = (BYTE)((D)>>16); }\
						 else if(EncPS(N)==2) 	{gbUsrParTbl[EncPI(N)] = (BYTE)(D); gbUsrParTbl[EncPI(N)+1] = (BYTE)((D)>>8); }\
						 else           		{gbUsrParTbl[EncPI(N)] = (BYTE)(D); }}

#define EGP(N)			((EncPS(N)==4)	? 		gbUsrParTbl[EncPI(N)]|(gbUsrParTbl[EncPI(N)+1]<<8)|(gbUsrParTbl[EncPI(N)+2]<<16)|(gbUsrParTbl[EncPI(N)+3]<<24):\
						 (EncPS(N)==3)	? 		gbUsrParTbl[EncPI(N)]|(gbUsrParTbl[EncPI(N)+1]<<8)|(gbUsrParTbl[EncPI(N)+2]<<16):\
						 (EncPS(N)==2)	? 		gbUsrParTbl[EncPI(N)]|(gbUsrParTbl[EncPI(N)+1]<<8):\
							          			gbUsrParTbl[EncPI(N)])

//Encoder Default Table								          		
#define EDT(A)			((MP(MpAnlForm) == MN_CVBS)?(gnEncModeCVBS_LV0[A][MP(MpSysFreq)]):(MP(MpAnlForm) == MN_HD_T)?(gnEncModeT_LV0[A][gbEncModeIndex]):(MP(MpAnlForm) == MN_HD_C)?(gnEncModeC_LV0[A][gbEncModeIndex]):(gnEncModeA_LV0[A][gbEncModeIndex]))
#define ETT(A)			(gAnEncLv0.A)

#define EDT_LV1(A)		((MP(MpAnlForm) == MN_HD_T)?(gnEncModeT_LV1[A][gbEncModeIndex+1]):(MP(MpAnlForm) == MN_HD_C)?(gnEncModeC_LV1[A][gbEncModeIndex+1]):(gnEncModeA_LV1[A][gbEncModeIndex+1]))
#define EDT_LV2(A)		((MP(MpAnlForm) == MN_HD_T)?(gnEncModeT_LV2[A][gbEncModeIndex+1]):(MP(MpAnlForm) == MN_HD_C)?(gnEncModeC_LV2[A][gbEncModeIndex+1]):(gnEncModeA_LV2[A][gbEncModeIndex+1]))

//Encoder Select Table
#define EST(D)			((UP(UpENC_CSTM)==MN_ON)?(ETT(D)):(EDT(D)))

#define	ENC_LV0_MEMCPY(ARRY, RYGP, RYGN, BYGP, BYGN, RYHP, RYHN, BYHP, BYHN, WHTLV, BLKLV, PEDLV, FSC, YMG, CBMG, CRMG, CBBST, CRBST, HSC, HLOC, VLOCEV, VLOCOD, CRXAC, CRXHEVS, CRXHEVE, CRXBTR){\
	ARRY.ENC_RYGAINP = RYGP;	ARRY.ENC_RYGAINN = RYGN;	ARRY.ENC_BYGAINP = BYGP;	ARRY.ENC_BYGAINN = BYGN;\
	ARRY.ENC_RYHUEP = RYHP;		ARRY.ENC_RYHUEN = RYHN;		ARRY.ENC_BYHUEP = BYHP;		ARRY.ENC_BYHUEN = BYHN;\
	ARRY.WHITE_LV = WHTLV;		ARRY.BLANK_LV = BLKLV;		ARRY.PEDESTAL_LV = PEDLV;\
	ARRY.FSC_TGT = FSC;\
	ARRY.Y_MGAIN = YMG;			ARRY.CB_MGAIN = CBMG;		ARRY.CR_MGAIN = CRMG;\
	ARRY.CB_BST = CBBST;		ARRY.CR_BST = CRBST;\
	ARRY.HSC_K = HSC;			ARRY.HLOCK_CAT = HLOC;		ARRY.VLOCK_CAT_EV = VLOCEV;	ARRY.VLOCK_CAT_OD = VLOCOD;\
	ARRY.CRX_AUTO_CAT = CRXAC;	ARRY.CRX_HPOSEVS = CRXHEVS;	ARRY.CRX_HPOSEVE = CRXHEVE;	ARRY.CRX_BITRATE = CRXBTR;\
}



// EMT M3 Protocol 

#define	_CTRL_NUM		13

#define	_BRIGHTNESS		0x10
#define	_MIRROR_FLIP	0x11
#define	_LED_CTRL		0x12
#define	_FACTORY_RST	0x13
#define	_FRAME_RATE		0x14
#define	_STARVIS_FUNC	0x15
#define	_HDR_FUNC		0x16
#define	_INFORMATION	0x17
#define	_MODEL_INFO		0x18
#define	_AE_SUM			0x19
#define	_GPS_CTRL		0x1A
#define	_MODEL_NAME		0x1B

#define	_ALL_SAVE		0x50


enum{
	Bright = 0, // 0
	MirFlip,    // 1
	LED,        // 2
	Reset,      // 3
	FrameRate,  // 4
	Starvis,    // 5
	HDR,        // 6
	FW_Info,    // 7
	Model_Info, // 8
	AE_Sum,     // 9
	GPS,        // 10
	Model_Name, // 11
	All_Save    // 12
};

// enum{		// gbFR
// 	FPS_30 = 0,
// 	FPS_291,
// 	FPS_275 = 3
// };

enum{		// gbLEDMode
	LED_ON,			// 0
	LED_OFF,		// 1
	LED_BLINKING	// 2
};


// HDR FUNC - Front and Rear
#define	_HDR_FRONT		0x1
#define	_HDR_REAR		0x2

// GPS - 
#define	_GPS_COLD		0x0
#define	_GPS_WARM		0x1
#define	_GPS_HOT		0x2
#define	_GPS_QZSS		0x3
#define	_GPS_HW_INFO	0x4
#define	_GPS_READ		0xF

#define _GPS_PKT_NUM		9
#define	_GPS_INIT_PKT_NUM	10
#define	_GPS_ENA_PKT_NUM	12

#endif


	
