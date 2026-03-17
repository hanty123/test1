/* **************************************************************************
 File Name	: 	app.h
 Description	:	EN772 - application common header
 Designer		:	Lee, Gyu Hong
 Date		:	21. 01. 08
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */
/*
 INDEX	:
		 0. APP
		 1. UTIL
		 2. INIT
		 3. KEY
		 4. COMM
		 5. MENU
		 6. MODE
		 7. AE
		 8. TDN
		 9. CONTRAST
		10. AWB
		11. DEFECT
		12. SHADING
		14. ETC
		15. FOCUS
		16. DBG
*/

//*************************************************************************************************
// 0. APP
//-------------------------------------------------------------------------------------------------
extern const char *gsBuildDate;
extern WORD gDataID;
extern void InitDataID(void);

#define MN_DATA_ID			gDataID/*model_ver*/		// Menu Parameter Reset if Program is compiled new.

extern void ISPM LibModelInfo(void);

// User Parameter --------------------------------------------------
#include "app_para.h"

// Common ----------------------------------------------------------
#if model_MenuDefSet == 1
	#define MENU_SET_PAR_READ_CHK	gbMnSetParReadChk = 1;
#else
	#define MENU_SET_PAR_READ_CHK
#endif

#define	APP_READ_CHK_ALL 			gbMnParReadChk = 1;		\
									gbUsrParReadChk = 1;	\
									gbUsrDataReadChk = 1;	\
									MENU_SET_PAR_READ_CHK

extern void AppSavePar(void);
extern void AppLoadPar(void);

//*************************************************************************************************
// 1. UTIL
//-------------------------------------------------------------------------------------------------
#include "app_util.h"


//*************************************************************************************************
// 2. INIT
//-------------------------------------------------------------------------------------------------
extern void InitFontChar(const UINT anFont[][12]);
extern void InitRdesConfig(int, int);
extern void Init(void);

BYTE gbModel_ISP;
BYTE gbModel_Sens;

//*************************************************************************************************
// 3. KEY
//-------------------------------------------------------------------------------------------------
// Key bit field

typedef	union{			// EN773 & EN779 & EN781 : Addr is the same, Bit is the opposite.
	UINT	nKey;
	struct {
		BYTE bSft;		// Addr 0, nKey[31:24]	- Shift buffer
		BYTE bOn;		// Addr 1, nKey[23:16]	- Key On/Off
		BYTE bCnt;		// Addr 2, nKey[15: 8]	- Repeat Counter
		BYTE bRpt;		// Addr 3, nKey[ 7: 0]	- Repeat Result (It is used in the OSD MENU)
	}v;	// Value
	struct {
		BYTE bSft : 8;	// Addr 0, nKey[31:24]	- bSft
		BYTE res0 : 2;	// Addr 1, nKey[23:22]	- bOn - for MENU PUSHING
		BYTE E    : 1;	// Addr 1, nKey[21]		-	"
		BYTE C    : 1;	// Addr 1, nKey[20]		-	"
		BYTE L    : 1;	// Addr 1, nKey[19]		-	"
		BYTE R    : 1;	// Addr 1, nKey[18]		-	"
		BYTE D    : 1;	// Addr 1, nKey[17]		-	"
		BYTE U    : 1;	// Addr 1, nKey[16]		-	"
		BYTE bCnt : 8;	// Addr 2, nKey[15:8]	- bCnt
		BYTE res1 : 2;	// Addr 3, nKey[7:6]	- bRpt - for MENU REPEAT
		BYTE Er   : 1;	// Addr 3, nKey[5]		-	"
		BYTE Cr   : 1;	// Addr 3, nKey[4]		-	"
		BYTE Lr   : 1;	// Addr 3, nKey[3]		-	"
		BYTE Rr   : 1;	// Addr 3, nKey[2]		-	"
		BYTE Dr   : 1;	// Addr 3, nKey[1]		-	"
		BYTE Ur   : 1;	// Addr 3, nKey[0]		-	"
	}b;	// Bit
} TKey;


//-------------------------------------------------------------------------------------------------
//
#ifndef __LIB__
#define ADC_LEVEL_C 	DFSEL_TgtBd(0x09D, 0x09B, 0x280)	// AD value at Push
#define ADC_LEVEL_U 	DFSEL_TgtBd(0x13D, 0x13D, 0x4C0)	// "
#define ADC_LEVEL_D 	DFSEL_TgtBd(0x1D4, 0x1D4, 0x73B)	// "
#define ADC_LEVEL_L 	DFSEL_TgtBd(0x26B, 0x26B, 0x9A0)	// "
#define ADC_LEVEL_R 	DFSEL_TgtBd(0x305, 0x305, 0xC0B)	// "


#define	AD_CHT_BIT		2/*0x3*//*0x07*/						// Chattering bit field
#define	AD_KEY_RPTF		(FPS_VDO>>2)						// First Repeat time
#define	AD_KEY_RPTT		(FPS_VDO>>3)						// Repeat time

#define	GPIO_CHT_BIT	4/*0x0f*/								// Chattering bit field
#define	GPIO_KEY_RPTF	(FPS_VDO>>2)						// First Repeat time
#define	GPIO_KEY_RPTT	(FPS_VDO>>3)						// Repeat time

#define	UART_HOLD_CNT	(2<<(FPS_VDO>30))					// Holding time
#define	UART_KEY_RPTF	(FPS_VDO>>2)						// First Repeat time
#define	UART_KEY_RPTT	(FPS_VDO>>3)						// Repeat time

#define PELCO_HOLD_CNT  3  //(FPS_VDO>>1)
#define PELCO_KEY_RPTF  (FPS_VDO>>1)
#define PELCO_KEY_RPTT  (FPS_VDO>>3)

#define	UCC_HOLD_CNT	GetBit(PAR1D,23,16)					// Holding time
#define	UCC_KEY_RPTF	GetBit(PAR1D, 7, 0)					// First Repeat time
#define	UCC_KEY_RPTT	GetBit(PAR1D,15, 8)					// Repeat time

#define PUSH_DELAY_NOT	1									// No Holding time
//	#define PUSH_DELAY_MIN	(FPS_VDO)		//(UCC_HOLD_CNT+1)	// Min Holding time
#define PUSH_DELAY_NOR	(gtCKey.b.C ? 1 : (FPS_VDO+1))		//(UCC_HOLD_CNT+4)	// Max Holding time

#endif//__LIB__

#define KEY_VAL_U	1
#define KEY_VAL_D	2
#define KEY_VAL_R	4
#define KEY_VAL_L	8
#define KEY_VAL_C	16
#define KEY_VAL_E	32
#define KEY_VAL_S	64

#define	KEY			gbMKey				// for MENU REPEAT
#define	KEY_U		((gbMKey   )&1)		//			"
#define	KEY_D		((gbMKey>>1)&1)		//			"
#define	KEY_R		((gbMKey>>2)&1)		//			"
#define	KEY_L		((gbMKey>>3)&1)		//			"
#define	KEY_C		((gbMKey>>4)&1)		//			"
#define	KEY_E		((gbMKey>>5)&1)		//			"

#define	pKEY		gbPKey				// for MENU PUSHING
#define	pKEY_U		((gbPKey   )&1)		//			"
#define	pKEY_D		((gbPKey>>1)&1)		//			"
#define	pKEY_R		((gbPKey>>2)&1)		//			"
#define	pKEY_L		((gbPKey>>3)&1)		//			"
#define	pKEY_C		((gbPKey>>4)&1)		//			"
#define	pKEY_E		((gbPKey>>5)&1)		//			"

#define	iKEY		gbiKey				// for MENU VDi	// 151214 HSH
#define	iKEY_U		((gbiKey   )&1)		//			"
#define	iKEY_D		((gbiKey>>1)&1)		//			"
#define	iKEY_R		((gbiKey>>2)&1)		//			"
#define	iKEY_L		((gbiKey>>3)&1)		//			"
#define	iKEY_C		((gbiKey>>4)&1)		//			"
#define	iKEY_E		((gbiKey>>5)&1)		//			"

//-------------------------------------------------------------------------------------------------
// Extern
extern void KeyScan(void);
extern void KeyAccLevel(int *aiKeyAdd);

extern BYTE gbSKeyVal;

extern BYTE gbUKeyVal;
extern TKey	gtUKey;

extern BYTE gbPKeyVal;
extern TKey	gtPKey;

extern BYTE gbCKeyVal;
extern TKey	gtCKey;

extern BYTE	gbMKey;
extern BYTE	gbPKey;
extern BYTE	gbiKey;	// 151214 HSH

#if model_UccA == 1
extern void UccA(void);
#else
#define UccA()
#endif

//*************************************************************************************************
// 5. MENU
//-------------------------------------------------------------------------------------------------
// Misc
#define MN_PAR_EA			512								// Menu parameter ea (user fix)
#define MN_LNG_EA			1								// Language max ea (1 ~ 12) (user fix)

#define	MN_TITLE			((MODE_CVBS_ON)?(0):(1))								// title y
#define	MN_YSTART			(MN_TITLE+((MODE_CVBS_ON)?(1):(2)))					//

extern BYTE MN_MXSP;

#define	MN_MXSP_DEF			14/*0x1*/	// 160330 KSH		// main osd x start position

#define	MN_SXSP				(MN_MXSP+12)					// sub osd x start position
#define MN_XBAR				(MN_SXSP+3)						// sub Bar osd start position
#define MN_BAR_SIZE			7								// Bar Size, 7 or 5

#define MN_XCENT        	(MN_MXSP+11)					// Osd center position
#define MN_XTITL			(MN_MXSP+5/*11*/)

#define MN_SUBSIZE      	11/*10*/			// Sub osd ea
#define MN_LINESIZE     	(MN_SXSP+MN_SUBSIZE-MN_MXSP)	// X ea

#define	MN_BLACK			0x0								// Attribute
#define	MN_WHITE			0x1								// "
#define MN_GRAY				0x2								// "
#define	MN_YELLOW			0x3								// "

#define FONT_LV0			(0xb48080 )			// Color plt MN_WHITE (Camtitle)
#define FONT_LV1			(0xb48080 ) 		// Color plt MN_WHITE
#define FONT_LV2			(0x708080 ) 		// Color plt
#define FONT_LV3			(0xa010a0 ) 		// Color plt MN_YELLOW


// Font configuration
#define MN_FONT_CONFIG(BD_ON, BD_MODE, OFY, OFX, VBLK, HBLK, VSIZ, HSIZ){\
	BOAD_ONw(BD_ON); 	BOAD_MODEw(BD_MODE);\
	FONT_OFYw(OFY); 	FONT_OFXw(OFX);   	\
	FONT_VBLKw(VBLK);	FONT_HBLKw(HBLK);	\
	FONT_VSIZw(VSIZ); 	FONT_HSIZw(HSIZ);	\
}

#define MN_FONT_1M		MN_FONT_CONFIG(0x1, 0x0, 0x58, 0xE0, 0x88, 0x84, 0x1, 0x1)
#define MN_FONT_2M		MN_FONT_CONFIG(0x1, 0x1, 0x65, 0xB0, 0x88, 0x84, 0x2, 0x2)
#define MN_FONT_4M		MN_FONT_CONFIG(0x1, 0x1, 0xC0, 0x1E6,0x88, 0x84, 0x2, 0x2)
#define MN_FONT_5M		MN_FONT_CONFIG(0x1, 0x1, 0xC0, 0x1E6,0x88, 0x84, 0x2, 0x2)
#define	MN_FONT_CVBS	MN_FONT_CONFIG(0x1, 0x1, (MP(MpSysFreq)==MN_SYSFREQ_60)?(0x13):(0x1b), 0x10 ,0x00, 0x00, 0x1, 0x2)

#define MN_FONT_DEBUG	MN_FONT_CONFIG(0x1, 0x0, 0x30, 0x50, 0x00, 0x00, 0x1, 0x1)
#define MN_FONT_DEBUG_H	MN_FONT_CONFIG(0x1, 0x0, 0x30, 0x50, 0x00, 0x00, 0x2, 0x2)

#define MENU_PK_SETUP		{KEY_VAL_L, KEY_VAL_L, KEY_VAL_R, KEY_VAL_R, KEY_VAL_C}		// Setup Menu pass Key sequence
#define MENU_PK_DEBUG 		{KEY_VAL_U, KEY_VAL_D, KEY_VAL_L, KEY_VAL_R, KEY_VAL_C}     // Debug Menu pass Key sequence
#define MENU_PK_EXSDI_ON	{KEY_VAL_L, KEY_VAL_L, KEY_VAL_L, KEY_VAL_C}				// EX-SDI pass Key sequence
#define MENU_PK_EXSDI_OFF	{KEY_VAL_R, KEY_VAL_R, KEY_VAL_R, KEY_VAL_C}				// EX-SDI pass Key sequence
#define MENU_PK_HDANL_ON	{KEY_VAL_U, KEY_VAL_U, KEY_VAL_U, KEY_VAL_C}
#define MENU_PK_CVBS_ON	{KEY_VAL_D, KEY_VAL_D, KEY_VAL_D, KEY_VAL_C}

#define	MN_AUTO_OFF			0						// Auto menu off
#define MN_OFF_TIME			60						// off after (sec)

//----------------------------------------------------------------------------------------
// FONT
//#define FONT_SEL0							  ((!MODE_CVBS_ON)?(gnFontChar0):(gnFontChar0_CVBS))
#define FONT_SEL0							  gnFontChar0
#define FONT_SEL1	MP(MpLanguageSel) == 1  ? gnFontChar1 : FONT_SEL0
#define FONT_SEL2	MP(MpLanguageSel) == 2  ? gnFontChar2 : FONT_SEL1
#define FONT_SEL3	MP(MpLanguageSel) == 3  ? gnFontChar3 : FONT_SEL2
#define FONT_SEL4	MP(MpLanguageSel) == 4  ? gnFontChar4 : FONT_SEL3
#define FONT_SEL5	MP(MpLanguageSel) == 5  ? gnFontChar5 : FONT_SEL4

#define EXTERN_FONT_CHAR0						extern const UINT gnFontChar0[][12]
#define EXTERN_FONT_CHAR1	EXTERN_FONT_CHAR0;	extern const UINT gnFontChar1[][12]
#define EXTERN_FONT_CHAR2	EXTERN_FONT_CHAR1;	extern const UINT gnFontChar2[][12]
#define EXTERN_FONT_CHAR3	EXTERN_FONT_CHAR2;	extern const UINT gnFontChar3[][12]
#define EXTERN_FONT_CHAR4	EXTERN_FONT_CHAR3;	extern const UINT gnFontChar4[][12]
#define EXTERN_FONT_CHAR5	EXTERN_FONT_CHAR4;	extern const UINT gnFontChar5[][12]

#if   MN_LNG_EA == 1
	#define SetFontChg() InitFontChar(FONT_SEL0);
	EXTERN_FONT_CHAR0;
#elif MN_LNG_EA == 2
	#define SetFontChg() InitFontChar(FONT_SEL1);
	EXTERN_FONT_CHAR1;
#elif MN_LNG_EA == 3
	#define SetFontChg() InitFontChar(FONT_SEL2);
	EXTERN_FONT_CHAR2;
#elif MN_LNG_EA == 4
	#define SetFontChg() InitFontChar(FONT_SEL3);
	EXTERN_FONT_CHAR3;
#elif MN_LNG_EA == 5
	#define SetFontChg() InitFontChar(FONT_SEL4);
	EXTERN_FONT_CHAR4;
#elif MN_LNG_EA == 6
	#define SetFontChg() InitFontChar(FONT_SEL5);
	EXTERN_FONT_CHAR5;
#endif


// -------------------------------------------------------------------------------------------------
// Menu parameter assign
#ifndef __LIB__
enum {
	MP_START,			// Head

	// System
	MpSysFreq,
	MpOutFps,
	MpSdiForm,
	MpSdiMode,		// 170530 LH
	MpAnlMode,
	MpAnlForm,

	MpOutScl,
	MpOutSclUser,
	MpCBar,
	MpCvbs,

	MpUccSel0,

	//MpReset,
	MpLanguageSel,
	MpOutFormat,
	MpCamID,
	MpBaudrate,
	MpCamTitleOn,
	MpCamTitleIdx,
	MpCamTitle = MpCamTitleIdx+8-1,

 	// AE
	MpBrightness,
	MpIris,
	MpIrisLvl,
	MpShutter,
	MpShutSpd,
	MpDcMode,
	MpShtMode,
	MpAgc,

	// Backlight
	MpBackLight,
	MpHlMaskThrs,
	MpHlMaskColor,
	MpBlcPosX,
	MpBlcPosY,
	MpBlcSizX,
	MpBlcSizY,
	MpWdrWgt,
	MpWdrMode,

	// TDN, LED
	MpTdn,
	MpTdnDly,
	MpAdaptive,
	MpLedPower,
    MpLedDrv,               // 190219 JJH
    MpLedSw,
	MpLedSatCtrl,
	MpTdnSw, 				// JYP
	MpTdnDNThres, 			// "
	MpTdnNDThres, 			// "
	MpTdnCfgIdx,
	MpTdnCfg = MpTdnCfgIdx+(2*2)-1, // 180910 JJH Tdn Threshold

	// ACE,Defog
	MpAce,
	MpDefog,
	MpDefogMode,
	MpDefogLevel,

	// AWB
	MpAwb,
	MpAwbPrst,
	MpAwbMnl,
	MpRgain,
	MpBgain,
	MpSaturation,
	MpColorTone,

	// ETC
	
	// DNR
	MpAdnr,
	
	// SHARPNESS
	MpSharpness,

	MpGamma,
	MpFlip,
	MpMirror,
	MpShading,
	MpShdWeight,

	// Privacy Box, Polygon
	MpPrivacy,
	MpPvcZone,
	MpPvcTrans,
	MpPvcYLevel,
	MpPvcCRLevel,
	MpPvcCBLevel,
	MpPvcCfgIdx,
	MpPvcCfg = MpPvcCfgIdx+(5*32)-1,

	// Hidden MENU
	MpShdDet,

#if(model_Lens==0) 	// Focus assist	// 170301 LH
	MpFaThrs,
	MpFaColor,
#endif

	MpColorSat,
	MpColorHue,
	MpContrast,

// TwoMoter
#if(model_Lens==1)	 // 180702 JJH
    MpMAF_mode,
    MpMAF_Filter,
    MpMAF_MotorInit,
    MpMAF_LensModel,
	MpMAF_TestMode,
    MpMAF_UccZoomHold,	// 181128 JJH
#endif

	MpExtDNR,

	
	MpLedCtrl,
	MpFrameRate,
	
	MpIQVer,
	
	MP_END_REAL
};

#define MP_END 	(MN_PAR_EA-1)	// Tail

#define gbMnPvcCfg(INDEX)		((_PRIVACY*)(gbMnParTbl + MpPvcCfgIdx +((INDEX))*5))

// 180910 JJH Tdn Threshold
#define gbMnTdnCfg(INDEX)		(( _TdnThres*)(gbMnParTbl + MpTdnCfgIdx +((INDEX))*2))

#define gbCamTitle(INDEX)		gbMnParTbl[MpCamTitleIdx+((INDEX))]

#define MP(I)					gbMnParTbl[I]
#define MP_LIB(I)				{ extern BYTE *gpb##I; gpb##I = &MP(I); }

#define MSP(I)					gbMnSetParTbl[I]

#else//__LIB__

	#define MP(I)	(*gpb##I)

	#ifdef LINK_MENU
		#define MP_LIB(I)	BYTE *gpb##I
	#else
		#define MP_LIB(I)	extern BYTE *gpb##I
	#endif

#endif//__LIB__

// 180910 JJH Adaptive Lighting
#define MP_LIB_LIST_LED	\
        MP_LIB(MpTdn);\
        MP_LIB(MpAdaptive);\
        MP_LIB(MpLedPower);\
        MP_LIB(MpTdnDly);\
        MP_LIB(MpLedSatCtrl);

#define MENU_LIB_LIST	\
        MP_LIB(MpSysFreq);\
        MP_LIB(MpOutFps);\
        MP_LIB(MpOutScl);\
        MP_LIB(MpOutSclUser);\
        MP_LIB_LIST_LED

#ifdef __LIB__
	MENU_LIB_LIST
#endif

// -------------------------------------------------------------------------------------------------
// Parameter status define
enum{	// common
   	MN_OFF,
	MN_ON
};

enum{	// common
   	MN_WDR_OFF,
	MN_WDR_ON
};

enum {	// common
	MN_3sLOW,
	MN_3sMID,
	MN_3sHI
};

enum {	// common
   	MN_4sOFF,
	MN_4sLOW,
	MN_4sMID,
	MN_4sHI
};

enum {	// MP(MpSysFreq)
	MN_SYSFREQ_50,
	MN_SYSFREQ_60
};

enum{	// MP(MpOutFps)
	MN_1M_720p_25_30,
	MN_1M_720p_50_60
};

enum{	// MP(MpOutFps)
	MN_2M_720p_25_30,
	MN_2M_720p_50_60,
	MN_2M_1080p_25_30,
	MN_2M_1080p_50_60,
	MN_2M_1440p_25_30,
	MN_2M_1944p_125,
	MN_2M_1944p_20,
	// EMT Format
	MN_2M_1080p_291,
	MN_2M_1080p_275
};

enum{	// MP(MpOutFps)
	MN_4M_720p_25_30,
	MN_4M_1080p_25_30,
	MN_4M_1440p_25_30,
	MN_5M_1944p_125,
	MN_5M_1944p_20
};

// When 1.3M, MN_FPS_LOW = 0
// When 1.3M, MP(MpOutFps) value is only 1.
#define MN_FPS_LOW  ((model_5M)||(model_2M&&((MP(MpOutFps)==MN_2M_720p_25_30)||(MP(MpOutFps)==MN_2M_1080p_25_30)||(MP(MpOutFps)==MN_2M_1440p_25_30)||(MP(MpOutFps)==MN_2M_1944p_125)||(MP(MpOutFps)==MN_2M_1944p_20)))||(model_1M&&(MP(MpOutFps)==MN_1M_720p_25_30)))		// 30P
#define MN_FPS_HI	(!MN_FPS_LOW)																																												// 60P

//enum {
//	MN_NTSC,
//	MN_PAL
//};


enum{
	MN_BR_2400,
	MN_BR_4800,
	MN_BR_9600,
	MN_BR_57600,
	MN_BR_115200
};

//MP(MpIris)
#define	MN_LENS_MNL		0
#define	MN_LENS_DC		1	// DC

enum {	//MP(MpShutter)
	MN_SHUT_AUTO,
	MN_SHUT_MNL,
	MN_SHUT_FLICKER
};

enum{	//MP(MpShutSpd)
	MN_MNL_SHUT_30,
	MN_MNL_SHUT_60,
	MN_MNL_SHUT_120,
	MN_MNL_SHUT_250,
	MN_MNL_SHUT_700,
	MN_MNL_SHUT_1000,
	MN_MNL_SHUT_1600,
	MN_MNL_SHUT_2500,
	MN_MNL_SHUT_5000,
	MN_MNL_SHUT_7000,
	MN_MNL_SHUT_10000,
	MN_MNL_SHUT_30000
};

enum{	//MP(MpDcMode)
	MN_DC_IN,
	MN_DC_OUT,
	MN_DC_DEBLUR
};

enum{	//MP(MpShtMode)
	MN_SHT_NORMAL,
	MN_SHT_DEBLUR
};

enum{	//MP(MpBackLight)
	MN_BL_OFF,
	MN_BL_HLC,
	MN_BL_BLC,
	MN_BL_WDR
};

enum {	//MP(MpWdrMode)
	MN_WDR_SENSF,
	MN_WDR_SENS_CLR
};

enum {	//MP(MpTdn)
	MN_TDN_AUTO,
	MN_TDN_DAY,
	MN_TDN_NIGHT,
	MN_TDN_EXTERN
};

enum{	//MP(MpDefogMode)
	MN_DEFOG_MANUAL,
	MN_DEFOG_AUTO
};

enum {	//MP(MpAwb)
	MN_AWB_AUTO,
	MN_AWB_AUTOEXT,
	MN_AWB_PRESET,
	MN_AWB_MNL
};

enum {	//MP(MpGamma)
	MN_GAMMA_045,
	MN_GAMMA_055,
	MN_GAMMA_065,
	MN_GAMMA_075,
	MN_GAMMA_AUTO
};

enum {	//MP(MpSdiMode)
	MN_EXSDI,
	MN_HDSDI
};

enum {	//MP(MpSdiForm) EX-SDI
	MN_SDI_OFF,
	MN_EXSDI_135MP,
	MN_EXSDI_270M,
	MN_EXSDI_270M_3G
};

enum {	//MP(MpSdiForm) HD-SDI
	MN_SDI_1P5G = 1
};

enum{	//MP(MpAnlMode)
	MN_CVBS_ON,
	MN_HDANALOG_ON
};

enum {	//MP(MpAnlForm)
	MN_ANL_OFF,
	MN_CVBS,
	MN_HD_T,
	MN_HD_C,
	MN_HD_A
};

enum {	//MP(MpCamTitleOn)
	MN_CT_OFF,
	MN_CT_RIGHT_UP,
	MN_CT_LEFT_DOWN
};

enum{
	MN_COOL_TONE,
	MN_WARM_TONE
};

// Fixed Menu parameter
enum{	//MP(MpOutFormat)	// Not used (HD-CbCr Fixed)
	MN_FRMT_SD,
	MN_FRMT_HD,
	MN_FRMT_UV
};

enum {	//MP(MpOutScl)		//Not used (FULL Fixed)
	MN_OUTSCL_FULL,
	MN_OUTSCL_COMP,
	MN_OUTSCL_USER
};

enum{	//gbMnDebugFnc
	MN_DBF_OFF,
	MN_DBG_AE,
	MN_DBG_AF,
	MN_DBG_AWB,
	MN_DBG_4,
	MN_DBG_5,
	MN_DBG_6,
	MN_DBG_TDN,
	MN_DBG_STATUS
};

//-------------------------------------------------------------------------------------------------
// Extern
extern void ChangeMenuSize(void);
extern void InitMenu(void);

extern void OsdClearAll(void);
extern void Menu(void);
extern void MenuReset(void);
extern void MenuResetFnc(void);
extern void MenuSave(UINT anSaveOn);

extern void menu_redraw(int iChg, int iGrayOnly);

extern void OsdCamTitle(void);
extern void MenuChangeRedraw(void);



// MODE 
enum{	// gbInModeRes
	MD_1M_FPS_25_30 = 0,
	MD_1M_FPS_50_60
};

enum{	// gbInModeRes
	MD_2M_FPS_25_30 = 0,
	MD_2M_FPS_50_60,
	MD_2M_FPS_125_20,
	MD_2M_FPS_291,
	MD_2M_FPS_275,
	MD_CVBS = 0xFF
};

enum{	// gbInModeRes
	MD_4M_FPS_25_30 = 0,
	MD_5M_FPS_125,
	MD_5M_FPS_20
};


//-------------------------------------------------------------------------------------------------
// Extern - Parameter & Global

	extern BYTE gbMnParSaveChk;
	extern BYTE gbMnParReadChk;
	extern BYTE gbMnParTbl[MN_PAR_EA];
	extern BYTE gbMnParTblOld[MN_PAR_EA];
		
#if model_MenuDefSet == 1
	extern BYTE gbMnSetParSaveChk;
	extern BYTE gbMnSetParReadChk;
	extern BYTE gbMnSetParTbl[MN_PAR_EA];

	extern void MenuResetSet(const int aiReset);
#endif

	extern BYTE gbMnBlcOsdOn;
	extern BYTE gbMnDebugFnc;
	extern BYTE gbMnDebugBypass;
	extern BYTE gbMnIrisCal;
	extern BYTE gbMenuState;
	extern BYTE gbMenuPushState;

#if (model_Lens==0)
	extern BYTE gbMnFaOn;
#endif

	extern BYTE gbModeBufSdiMode;
	extern BYTE gbModeBufOutFps;
	extern BYTE gbModeBufSysFreq;
	extern BYTE gbModeBufSdiForm;
	
	extern BYTE gbModeBufBefore;
	extern BYTE gbModeSdiBufBefore;

	extern BYTE gbModeChgHotKey;
	
#define _S(NAME)		s##NAME

#if MN_LNG_EA == 1
  #if model_CharMax == 1
	#define PEXCH		UINT//EXCH*
  #else
	#define PEXCH		EXCH
  #endif
#else
	#define PEXCH		UINT//EXCH*
#endif

#define MENU_TITLE			((const PEXCH*)gbMenuTitle)
#define MENU_NAME			((const PEXCH*)gbMenuList)
#define MENU_VAL			((const PEXCH*)gbMenuVal)

#define MENU_TITLE_IS(V)	(MENU_TITLE == _S(V))
#define MENU_NAME_IS(V)		(MENU_NAME == _S(V))
#define MENU_VAL_IS(V)		(MENU_VAL == _S(V))

extern PEXCH* gbMenuTitle;
extern PEXCH* gbMenuList;
extern PEXCH* gbMenuVal;

#define EXTERN_STR(STR)		extern const PEXCH _S(STR)[]

EXTERN_STR(NOT_USED);
EXTERN_STR(OFF);
EXTERN_STR(MENU);
//EXTERN_STR(MOTION);
//EXTERN_STR(BACKLIGHT);
//EXTERN_STR(SMART_IR);

//*************************************************************************************************
// 6. MODE (In /Out mode change management)
//-------------------------------------------------------------------------------------------------
#include "app_mode.h"

#define	OUTSCL_FULL_YCLIP	0xfe											// Final Output High Clip Value for FULL in IMAGE RANGE Menu (0x0 ~ 0xFF)
#define	OUTSCL_FULL_YOFST	0x01											// Final Output Offset Value for FULL in IMAGE RANGE Menu (0x0 ~ 0xFF)
#define	OUTSCL_FULL_YGAIN	0x80	// (((256-OUTSCL_FULL_YOFST)*0x80)/256)	// Final Y Output Gain for FULL in IMAGE RANGE Menu (0x0 ~ 0xFF)
#define	OUTSCL_FULL_CGAIN	0x80/*0x7F*/										// Final C Output Gain for FULL in IMAGE RANGE Menu (0x0 ~ 0xFF)
#define	OUTSCL_FULL_CCLIP	0xFF/*0x7F*/										// Final C High Clip Value for FULL in IMAGE RANGE Menu (0x0 ~ 0xFF)
#define	OUTSCL_FULL_YSLIC	0x01											// Final Output Low Clip Value for FULL in IMAGE RANGE Menu (0x0 ~ 0xFF)

#define	OUTSCL_COMP_YCLIP	0xf0											// Final Output High Clip Value for FULL in IMAGE RANGE Menu (0x0 ~ 0xFF)
#define	OUTSCL_COMP_YOFST	0x10											// Final Output Offset Value for FULL in IMAGE RANGE Menu (0x0 ~ 0xFF)
#define	OUTSCL_COMP_YGAIN	0x78	// (((256-OUTSCL_COMP_YOFST)*0x80)/256)	// Final Y Output Gain for FULL in IMAGE RANGE Menu (0x0 ~ 0xFF)
#define	OUTSCL_COMP_CGAIN	0x78/*0x71*/										// Final C Output Gain for FULL in IMAGE RANGE Menu (0x0 ~ 0xFF)
#define	OUTSCL_COMP_CCLIP	0xF0/*0x70*/										// Final C High Clip Value for FULL in IMAGE RANGE Menu (0x0 ~ 0xFF)
#define	OUTSCL_COMP_YSLIC	0x10											// Final Output Low Clip Value for FULL in IMAGE RANGE Menu (0x0 ~ 0xFF)

//#define	CVBS_FULL_PED		0x2a
//#define	CVBS_COMP_PED		0x0

#define CVBS_NTSC_H			720
#define CVBS_NTSC_V			480
#define CVBS_PAL_H			CVBS_NTSC_H
#define CVBS_PAL_V			576
//#define	CVBS_ACTBSTHW_BW	0x0
//#define	CVBS_ACTBSTHW_NTSC	0x44
//#define	CVBS_ACTBSTHW_PAL	0x3d

//#define	ADC_LEVEL_CVBS		0x80	// ON by under ADC value
////----------------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// extern
extern BYTE gbModeWdrOn_L;								// Line WDR on/off status
extern BYTE gbModeWdrOn_LFM;							// LFM+WDR on/ off status
extern BYTE gbModeWdrOn_CLR;							// Clear HDR on/ off status
extern UINT	gnInModeVtw, gnInModeHtw;					// Input mode Total H, V

extern void LibModeInit (void);
extern void LibModeSdi(UINT, UINT);
extern void ModeChange(void);
extern void ModeSdiAnc(void);


// 170602 HTY
#if (model_ModeLed==1)
	extern void ModeLed(void);
#else
	#define ModeLed()
#endif

//*************************************************************************************************
// EMT BlackBox
//-------------------------------------------------------------------------------------------------
#if(1)
extern BYTE gbBright; // (Step Range 0x0 ~ 0xc (0~12), F: Read)
extern BYTE gbMFcond; // (0: Nor, 1: M(default), 2: F, 3: M+F, F: Read)
extern BYTE gbLEDMode; // (0: On(default), 1: Off, 2: Blink (1sec), F: Read)
extern BYTE gbReset; // (0: None, 1: Reset)
extern BYTE gbFR; // (0: 30p, 1: 29.1, 3: 27.5, F: Read)
extern BYTE gbNV; // (0: On, 1: Off(default), F: Read)
extern BYTE gbHDR; // (0: On, 1: Off, F: Read)
//extern UINT gnFW_Info; // (F: Read, RearCam->EMT_RX)
extern BYTE gbModel_Info; // (F: Read, Cam->EMT_RX, 1: Front, 2: Rear, 3: Incam)
extern BYTE gbAeSum;	// (0: Send AE Sum (Continuous, Default), 1: Stop AE Sum, 2: Request AE Sum(Single))
extern BYTE gbAeSum_sht_light;	// (0 : light source, 1 : shutter)
extern BYTE gbGPSctrl; // Reserved
extern BYTE gbModelName; // (F: Read Model Name)
extern BYTE gbAllSave; // (1: Save All, F: Read)
#endif

//*************************************************************************************************
// 7. AE
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//Extern
extern int 	giCurAgc;						// AE AGC current value
	#define gnAgcLim	gnAeAgcTVal			// AE Max AGC value
extern UINT	gnAeAgcTVal;					// AE AGC Max value

extern UINT	gnAeErr;						// AE Tracking finish state
extern UINT	gnAeState;						// AE control state
extern UINT gnAeStateS1;

extern int  gnSht_L, gnSht_S1;				// Current shutter line
extern UINT gnAgc_L, gnAgc_S1;				// Current shutter line

extern BYTE gbAeWdrComp;

extern void InitAe(void);
extern void Ae(void);

extern void ISPM LibAeGainIntp(int aiVal, UINT* apnGain);
extern void ISPM LibAeGainIntp0125(int aiVal, UINT* apnGain);

// PreGain
extern UINT ISPM LibAePrgainIntp(int aiVal);
extern UINT ISPM LibAePrgainIntp0125(int aiVal);

extern void ISPM LibAePrgain_L (UINT anVal);
extern void ISPM LibAePrgain_S (UINT anVal);

// AE Common -----------------------------------------------------------------------------------------
// #define AE_GAIN_TGT_OFST		(0x80)									// Gain min offset
#define AE_GAIN_TGT_OFST		(0x3)									// Gain min offset


#define AE_SHT_FLK				((MP(MpSysFreq)==MN_SYSFREQ_60) ? AE_SYS60_FLICKER : AE_SYS50_FLICKER)

#if (model_1M)
	#define AE_SYS60_FLICKER 		(int)LibAeShtLine(450)					// 20m    / (60p 1H : 22.222u) / 2 = 450 line => 1/100s
	#define AE_SYS50_FLICKER 		(int)LibAeShtLine(313)					// 16.66m / (50p 1H : 26.666u) / 2 = 313 line => 1/120s

#elif (model_2M)
 #if(model_Sens==SENS_SC200AI)	// Sensor selection
	#define AE_SYS60_FLICKER 		(int)LibAeShtLine(675*2)				// 40m    / (30p 1H : 29.629u) / 2 = 675 line => 1/50s
	#define AE_SYS50_FLICKER 		(int)LibAeShtLine(469*2)				// 33.33m / (25p 1H : 35.555u) / 2 = 469 line => 1/60s
 #else
	#define AE_SYS60_FLICKER 		(int)LibAeShtLine(675)					// 40m    / (30p 1H : 29.629u) / 2 = 675 line => 1/50s
	#define AE_SYS50_FLICKER 		(int)LibAeShtLine(469)					// 33.33m / (25p 1H : 35.555u) / 2 = 469 line => 1/60s

 #endif

#elif (model_5M)															// 160909 LGH
	#if(model_Sens==SENS_IMX335)
	#define AE_SYS60_FLICKER		((MP(MpOutFps)==MN_5M_1944p_125) ? (int)LibAeShtLine(990) :\
										(MP(MpOutFps)==MN_5M_1944p_20)	? (int)LibAeShtLine(990) :\
																		  (int)LibAeShtLine(990))
																		 	// 1/100s => 1/12.5s : 4950line = 1/100s : x -> x = 990line
																		  	// 1/100s => 1/20s : 4950line = 1/100s : x -> x = 990line
																		  	// 1/100s => 1/30s : 3300line = 1/100s : x -> x = 990line
	#define AE_SYS50_FLICKER		((MP(MpOutFps)==MN_5M_1944p_125) ? (int)LibAeShtLine(990) :\
										(MP(MpOutFps)==MN_5M_1944p_20)	? (int)LibAeShtLine(990) :\
																		  (int)LibAeShtLine(1375))
																		  // 1/100s => 1/12.5s : 4950line = 1/100s : x -> x = 990line
																		  // 1/100s => 1/20s : 4950line = 1/100s : x -> x = 990line
																		  // 1/60s	=> 1/25s : 3300line = 1/60s : x -> x => 1375line
																		  
	#elif(model_Sens==SENS_SC500AI)		
    #define AE_SYS60_FLICKER		(int)LibAeShtLine(900*2)			 	 // 40m    / (30p 1H : 22.222u) / 2 = 900 line => 1/50s
	#define AE_SYS50_FLICKER		(int)LibAeShtLine(625*2)		 	  // 33.33m / (25p 1H : 26.666u) / 2 = 469 line => 1/60s																	  
	
	#else
	#define AE_SYS60_FLICKER		(int)LibAeShtLine(980)			 	 // 40m    / (30p 1H : 22.222u) / 2 = 900 line => 1/50s
	#define AE_SYS50_FLICKER		(int)LibAeShtLine(690)		 	  		// 33.33m / (25p 1H : 26.666u) / 2 = 469 line => 1/60s
	#endif
#endif


//#define	AE_LSHT_LMT_WDR				(int)LibAeShtLine(gnInModeVtw)			// 1/30s	=> 2250line = 1/60s : x -> x => 1125line
#define	AE_LSHT_LMT_WDR				(int)LibAeShtLine(gnAeLWdrMaxL0/*>>1*/)			// 1/30s	=> 2250line = 1/60s : x -> x => 1125line

#define AE_BLC_H_SIZE			(50)
#define AE_BLC_V_SIZE			(60)

#if (model_1M)
#define AE_BLC_WIN_MENU_H		(13)
#define AE_BLC_WIN_MENU_V		( 1)

#elif (model_2M)
//#define AE_BLC_WIN_MENU_H		(19)
//#define AE_BLC_WIN_MENU_V		(18)
#define AE_BLC_WIN_MENU_H		(HWIr/(AE_BLC_H_SIZE*2))
#define AE_BLC_WIN_MENU_V		(VWIr/AE_BLC_V_SIZE)

#elif (model_5M)
#define AE_BLC_WIN_MENU_H		(26)
#define AE_BLC_WIN_MENU_V		((!MODE_5M_ON)?(24):(32))
#else
#endif

#define model_Iris_DC			((model_Iris==1))
#define AE_DEBLUR_FIX_ON		0															// 0: Deblur normal (full shutter, default)

#if (model_Iris_DC)
	#define AE_OUTDOOR_COND		((MP(MpIris)==MN_LENS_DC)&&(MP(MpDcMode)==MN_DC_OUT))
	#define AE_DEBLUR_COND		(((MP(MpIris)==MN_LENS_MNL)&&(MP(MpShtMode)==MN_SHT_DEBLUR)) || ((MP(MpIris)==MN_LENS_DC)&&(MP(MpDcMode)==MN_DC_DEBLUR)))
#else
	#define	AE_OUTDOOR_COND		0
	#define AE_DEBLUR_COND		(MP(MpShtMode)==MN_SHT_DEBLUR)
#endif

#if (model_Iris==0)
	#define AE_IRS_OPN_Max		0x0
	#define AE_IRS_CLS_Max		0x0
	#define AE_IRS_STAT_Max		0
	
#elif (model_Iris==1) //-----------------------------------------------------------
	#define AE_IRS_OPN_Max		0x145/*0x1c5*//*0x180*/
	#define AE_IRS_CLS_Max		0x345/*0x2c5*//*0x380*/
	#define AE_IRS_STAT_Max		/*1800*/(1200/*<<(FPS_VDI>30)*/)	
#endif

// -------------------------------------------------------------------------------------------------------------------------------------
#include "app_ae_led.h"

#define AE_LED_INVERT                           0

#if (model_1M)
	#define COMMON_AGC_PT0		DFSEL_Sens(0x040, 0x040, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0)		// Min AGC arg.
	#define COMMON_AGC_PT1		DFSEL_Sens(0x180, 0x180, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0) 		// Mid AGC arg.
	#define COMMON_AGC_PT2		DFSEL_Sens(0x200, 0x200, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0) 		// Max AGC arg.

#elif (model_2M)
	#if(model_2M_L)
	#define COMMON_AGC_PT0		DFSEL_Sens(0x040, 0x040, 0x040, 0x040, 0x0, 0x040, 0x040, 0x040, 0x040, 0x040)	// Min AGC arg.
	#define COMMON_AGC_PT1		DFSEL_Sens(0x180, 0x180, 0x180, 0x180, 0x0, 0x180, 0x180, 0x180, 0x180, 0x180) 	// Mid AGC arg.
	#define COMMON_AGC_PT2		DFSEL_Sens(0x200, 0x200, 0x200, 0x200, 0x0, 0x200, 0x200, 0x200, 0x200, 0x200) 	// Max AGC arg.
	#else
	#define COMMON_AGC_PT0		DFSEL_Sens(0x040, 0x0, 0x0, 0x060, 0x0, 0x040, 0x040, 0x040, 0x0, 0x0)		// Min AGC arg.
	#define COMMON_AGC_PT1		DFSEL_Sens(0x180, 0x0, 0x0, 0x180, 0x0, 0x180, 0x180, 0x180, 0x0, 0x0) 		// Mid AGC arg.
	#define COMMON_AGC_PT2		DFSEL_Sens(0x200, 0x0, 0x0, 0x200, 0x0, 0x200, 0x200, 0x200, 0x0, 0x0) 		// Max AGC arg.
	#endif

#elif (model_5M)
	#define COMMON_AGC_PT0		DFSEL_Sens(0x040, 0x0, 0x0, 0x0, 0x0, 0x040, 0x0, 0x0, 0x0, 0x0)	// Min AGC arg.
	#define COMMON_AGC_PT1		DFSEL_Sens(0x180, 0x0, 0x0, 0x0, 0x0, 0x180, 0x0, 0x0, 0x0, 0x0) 	// Mid AGC arg.
	#define COMMON_AGC_PT2		DFSEL_Sens(0x200, 0x0, 0x0, 0x0, 0x0, 0x200, 0x0, 0x0, 0x0, 0x0) 	// Max AGC arg.
#endif

//*************************************************************************************************
// 8. TDN
//-------------------------------------------------------------------------------------------------

#if (model_Tdn==0)			// 1 Pin 2 state control
   #define TDN_MECH_HLD		{}
   #define TDN_MECH_NIT     {GpioOutDir(GPIO_TDN_1); GpioSetHi(GPIO_TDN_1);}
   #define TDN_MECH_DAY     {GpioOutDir(GPIO_TDN_1); GpioSetLo(GPIO_TDN_1);}
#elif (model_Tdn==1)		// 1 Pin 3 state control
   #define TDN_MECH_HLD		{GpioInDir(GPIO_TDN_1);}
   #define TDN_MECH_NIT     {GpioOutDir(GPIO_TDN_1); GpioSetHi(GPIO_TDN_1);}
   #define TDN_MECH_DAY     {GpioOutDir(GPIO_TDN_1); GpioSetLo(GPIO_TDN_1);}

#else						// 2 Pin control
	#if (model_TgtBd==0)
			#define TDN_MECH_HLD 	{GpioSetLo(GPIO_TDN_1); GpioSetLo(GPIO_TDN_2);}  		// Socket
 			#define TDN_MECH_DAY 	{GpioSetLo(GPIO_TDN_1); GpioSetHi(GPIO_TDN_2);}  		//
	   		#define TDN_MECH_NIT 	{GpioSetHi(GPIO_TDN_1); GpioSetLo(GPIO_TDN_2);}  		//
	   		
	#elif (model_TgtBd==1)
 	#if ((model_Lens==0)||(model_Lens==1))
			#define TDN_MECH_HLD 	{GpioSetLo(GPIO_TDN_1); GpioSetLo(GPIO_TDN_2);}  	// EVM
	      	#define TDN_MECH_DAY 	{GpioSetLo(GPIO_TDN_1); GpioSetHi(GPIO_TDN_2);}  	//
			#define TDN_MECH_NIT 	{GpioSetHi(GPIO_TDN_1); GpioSetLo(GPIO_TDN_2);}  	//
		#endif

	#else	// Customer area
			#define TDN_MECH_HLD 	{GpioSetLo(GPIO_TDN_1); GpioSetLo(GPIO_TDN_2);}  	// EVM
		    #define TDN_MECH_DAY 	{GpioSetHi(GPIO_TDN_1); GpioSetLo(GPIO_TDN_2);}  	//
	   		#define TDN_MECH_NIT 	{GpioSetLo(GPIO_TDN_1); GpioSetHi(GPIO_TDN_2);}  	//
	#endif
#endif

#if (model_Cds==1)
	#define TDN_CDS_IN		(GpioGetPin(GPIO_CDS_IN))	//(!GpioGetPin(GPIO_CDS_IN))	// assign CDS input (using GPIO)
#else
	#define TDN_CDS_IN		(ADC_CDSr)	 											// assign CDS input (using ADC)
#endif

#define TDN_DNTHRS          (((gbMnTdnCfg(0)->bDNThres)*UP(UpTDN_AUTO_THRS_STEP))+10)  // TDN D>N threshold level
#define TDN_NDTHRS          (((gbMnTdnCfg(0)->bNDThres)*UP(UpTDN_AUTO_THRS_STEP))+10)  // TDN N>D threshold level
//----------------------------------YTM--------------------------------------------
//#define TDN_DLY_1			(	UP(UpTDN_DLY_LOW)/FR_DUTY)		// 1s                  			 // 141121 LH : TDN Turn on delay time
//#define TDN_DLY_2			(UP(UpTDN_DLY_MIDDLE)/FR_DUTY)		// 5s                   			 // "
//#define TDN_DLY_3			(  UP(UpTDN_DLY_HIGH)/FR_DUTY)		// 20s                  			 // "

//FR_DUTY

#define TDN_DLY_1			(	UP(UpTDN_DLY_LOW) * FPS_VDO)		// 1s                  		//210112 YTM: TDN Turn on delay time 
#define TDN_DLY_2			(UP(UpTDN_DLY_MIDDLE) * FPS_VDO)		// 5s                   	//210112 YTM: TDN Turn on delay time	
#define TDN_DLY_3			(  UP(UpTDN_DLY_HIGH) * FPS_VDO)		// 20s                  	//210112 YTM: TDN Turn on delay time


enum {
	TDN_HLD = 0,
	TDN_DAY,
	TDN_NIT
};

typedef struct _tagTdnThres{    // 180910 JJH TDN Threshold
	BYTE	bDNThres;
	BYTE	bNDThres;
}_TdnThres;

//------------------------------------------------------------------------------
// extern
extern UINT gnTdnChkOut;		// Day & BW status
extern void TDN(void);

#if(model_Led == 0 || model_Led == 2)               // 180910 JJH TDN Threshold		//210112 YTM	//210225 YTM
extern int LibLedTdnChg(UINT *, UINT *, const int, const int, _TdnThres* );
#endif

//*************************************************************************************************
// 9. CONTRAST
//-------------------------------------------------------------------------------------------------
// ACE
#define	ACE_HSP				MODE_VAL(0x1, 0x1 , 0x1 , 0x1 , 0x0 )
#define ACE_VSP				MODE_VAL(0x0, 0x2a, 0x2a, 0x2a, 0x2a)

#define ACE_HBS				MODE_VAL(0x2, 0x2 , 0x2 , 0x3 , 0x3 )
#define ACE_VBS				MODE_VAL(0x0, 0x2 , 0x2 , 0x3 , 0x3 )

#define ACE_HB				MODE_VAL(0xb, 0xa , 0xf , 0xa , 0xa )
#define ACE_VB				MODE_VAL(0x7, 0x5 , 0x8 , 0x7 , 0x7 )

//DEFOG
#define DEFOG_OSDON			0x0		// Defog Area Set OSD On/Off Function (0x0 or 0x1)

#define DEFOG_HW			MODE_VAL(0xa  , 0xa , 0xa  , 0xb  , 0xb  )		// Defog Area Set Horizontal Width (0x0 ~ 0xf)
#define DEFOG_HSP			MODE_VAL(0x100, 0x90, 0x1c0, 0x100, 0x110)		// Defog Area Set Horizontal Start Position (0x0 ~ 0x790)
#define DEFOG_VW			MODE_VAL(0x7  , 0x9 , 0xa  , 0xa  , 0xa  )		// Defog Area Set Vertical Width (0x0 ~ 0xf)					
#define DEFOG_VSP			MODE_VAL(0x15 , 0x30, 0x30 , 0x30 , 0x30 )		// Defog Area Set Vertical Start Position (0x0 ~ 0x440)

#define DEFOG_X_OFF 		30

//------------------------------------------------------------------------------
// extern
extern BYTE gbHistoM[];

extern unsigned int 	gnDefog_HS;
extern unsigned int 	gnDefog_HE;
extern unsigned int 	gnDefog_VS;
extern unsigned int 	gnDefog_VE;
extern unsigned int 	gnAe1Size;
extern unsigned int 	gnHistoM[];
extern unsigned int 	gnDefogV;
extern unsigned int 	gnDwdrV;

extern unsigned char 	gbContrastMode;		// DEFOG OFF/ON
extern unsigned char 	gbDefogMode;        // "	 MODE MANUAL/AUTO
extern unsigned char 	gbDefogLevel;       // "	 STRENGTH LOW/MID/HIGH

extern unsigned int 	gnHistoV[];

extern void InitContrast(void);

extern BYTE gbGammParInit;
extern BYTE gbDfltGammaChk;

extern void InitGamma(void);
extern void Gamma(void);
extern void ISPM2 DfltGammaSave(void);
extern void ISPM2 ISPtoSf_GmSave(void);
extern void ISPM2 SftoISP_GmLoad(void);

extern void AceDefog(void);
extern void LibDefog(unsigned int * anDefogThres, unsigned int * anDefogWeight, unsigned int *anDefogTbl);

//*************************************************************************************************
// 10. AWB
//-------------------------------------------------------------------------------------------------
extern UINT	gnAwbErr;					// AWB tracking finish state
extern UINT	gnAwbOdmCapOn;

extern BYTE gbColorMapParInit;
extern BYTE gbDfltColorMapChk;

extern void Awb(void);
extern void InitAwb(void);
extern void ISPM2 DfltColorMapSave(void);
extern void ISPM2 ISPtoSf_CmSave(void);
extern void ISPM2 SftoISP_CmLoad(void);
extern void PostCCM_Wgt(int aiCT, int* apiRR, int* apiRG, int* apiRB, int* apiGR, int* apiGG, int* apiGB, int* apiBR, int* apiBG, int* apiBB);
extern void SetHueGain(int aiCT);

#if(model_Sens == SENS_OX03C10)
extern void OX3C_PreCCM(UINT anCtemp);
extern void OX3C_WBGain(UINT anCtemp);

extern void LPD_RGBGain(WORD awB, WORD awGb, WORD awGr, WORD awR);
extern void SPD_RGBGain(WORD awB, WORD awGb, WORD awGr, WORD awR);
extern void LPD_InvRGBGain(WORD awB, WORD awGb, WORD awGr, WORD awR);

extern void SPD_PreCCM(void);
#endif

#if model_AwbCapOn
	extern void InitAwbOdmCap(void);
	extern void AwbOdmCap(void);
#endif

#if(model_1M)
	#define	AWB_DBOFFSET		DFSEL_Sens((0x33 ), (0x33 ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x0  )) 	// Color map coordinate x offset
	#define	AWB_DROFFSET		DFSEL_Sens((0x10b),	(0x10b), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x0  )) 	// Color map coordinate y offset
	#define	AWB_DBGAIN  		DFSEL_Sens((0xf  ), (0xf  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ))   	// Color map coordinate X gain
	#define	AWB_DRGAIN  		DFSEL_Sens((0xd  ), (0xd  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ))   	// Color map coordinate y gain

	// LOW TEMP                                                                                     
	#define BY_GAINN_TEMP_L		DFSEL_Sens((0x60 ), (0x60 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 )) 
	#define BY_GAINP_TEMP_L		DFSEL_Sens((0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 )) 
	#define RY_GAINN_TEMP_L		DFSEL_Sens((0x60 ), (0x60 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 )) 
	#define RY_GAINP_TEMP_L		DFSEL_Sens((0x50 ), (0x50 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 )) 
                                                                                                                                     
	#define BY_HUEN_TEMP_L		DFSEL_Sens((0x81 ), (0x81 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 )) 
	#define BY_HUEP_TEMP_L		DFSEL_Sens((0x62 ), (0x62 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 )) 
	#define RY_HUEN_TEMP_L		DFSEL_Sens((0x47 ), (0x47 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 )) 
	#define RY_HUEP_TEMP_L		DFSEL_Sens((0x6e ), (0x6e ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ))    
	
	// MID TEMP
	#define BY_GAINN_TEMP_M		DFSEL_Sens((0x60 ), (0x60 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	#define BY_GAINP_TEMP_M		DFSEL_Sens((0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	#define RY_GAINN_TEMP_M		DFSEL_Sens((0x60 ), (0x60 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	#define RY_GAINP_TEMP_M		DFSEL_Sens((0x50 ), (0x50 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	                                                                                                                                
	#define BY_HUEN_TEMP_M		DFSEL_Sens((0x81 ), (0x81 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ))
	#define BY_HUEP_TEMP_M		DFSEL_Sens((0x62 ), (0x62 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ))
	#define RY_HUEN_TEMP_M		DFSEL_Sens((0x47 ), (0x47 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ))
	#define RY_HUEP_TEMP_M		DFSEL_Sens((0x6e ), (0x6e ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ))
                                                                                                                                   
	// HIGH TEMP                                                                                                                   
	#define BY_GAINN_TEMP_H		DFSEL_Sens((0x60 ), (0x60 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	#define BY_GAINP_TEMP_H		DFSEL_Sens((0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	#define RY_GAINN_TEMP_H		DFSEL_Sens((0x60 ), (0x60 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	#define RY_GAINP_TEMP_H		DFSEL_Sens((0x50 ), (0x50 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	                                                                                                                                
	#define BY_HUEN_TEMP_H		DFSEL_Sens((0x81 ), (0x81 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ))
	#define BY_HUEP_TEMP_H		DFSEL_Sens((0x62 ), (0x62 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ))
	#define RY_HUEN_TEMP_H		DFSEL_Sens((0x47 ), (0x47 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ))
	#define RY_HUEP_TEMP_H		DFSEL_Sens((0x6e ), (0x6e ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ), (0x80 ))
	
#elif(model_2M)
	#if(model_2M_L)																											//t
		#if(model_AWB_Matrix==0)
			// MP V1.0.0
			#if(0)
			#define	AWB_DBOFFSET		(0x56 )	// Color map coordinate x offset
			#define	AWB_DROFFSET		(0xde )	// Color map coordinate y offset
			#define	AWB_DBGAIN  		(0xf  )	// Color map coordinate X gain
			#define	AWB_DRGAIN  		(0xe  )	// Color map coordinate y gain
			#else
			#define	AWB_DBOFFSET		(0x68 )
			#define	AWB_DROFFSET		(0xf4 )
			#define	AWB_DBGAIN  		(0x10 )
			#define	AWB_DRGAIN  		(0xe  )
			#endif
		#else
			// MP V1.0.1
			#define	AWB_DBOFFSET		(0x47 )	// Color map coordinate x offset
			#define	AWB_DROFFSET		(0xed )	// Color map coordinate y offset
			#define	AWB_DBGAIN  		(0xf  )	// Color map coordinate X gain
			#define	AWB_DRGAIN  		(0xe  )	// Color map coordinate y gain
		#endif
                                                                                                       
	#define HnG_TEMP_L			(AWB_TEMP_VAL_L)
    #define HnG_TEMP_M			(AWB_TEMP_VAL_M)
    #define HnG_TEMP_H          (AWB_TEMP_VAL_H)
    
#if(model_ImgTune_Option==0)
    // LOW TEMP                                                                                     
	#define BY_GAINN_TEMP_L		DFSEL_Sens((0x55 ), (0x3A ), (0x58 ), (0x58 ), (0x40 ), (0x80 ), (0x95 ), (0x60 ), (0x6A ), (/*0x60*/0x58 ))
	#define BY_GAINP_TEMP_L		DFSEL_Sens((0x50 ), (0x25 ), (0x30 ), (0x20 ), (0x40 ), (0x70 ), (0x70 ), (0x40 ), (0x50 ), (/*0x25*/0x30 ))
	#define RY_GAINN_TEMP_L		DFSEL_Sens((0x50 ), (0x3A ), (0x5C ), (0x30 ), (0x40 ), (0x70 ), (0x90 ), (0x60 ), (0x60 ), (/*0x30*/0x5C ))
	#define RY_GAINP_TEMP_L		DFSEL_Sens((0x45 ), (0x2A ), (0x50 ), (0x50 ), (0x40 ), (0x70 ), (0x75 ), (0x50 ), (0x55 ), (/*0x70*/0x58 ))
                                                                                                                         /*    */    
	#define BY_HUEN_TEMP_L		DFSEL_Sens((0x60 ), (0x5D ), (0x50 ), (0x50 ), (0x80 ), (0x68 ), (0x61 ), (0x5F ), (0x48 ), (/*0x50*/0x50 ))
	#define BY_HUEP_TEMP_L		DFSEL_Sens((0x5D ), (0x62 ), (0x20 ), (0x20 ), (0x80 ), (0x3A ), (0x60 ), (0x51 ), (0x49 ), (/*0x20*/0x20 ))
	#define RY_HUEN_TEMP_L		DFSEL_Sens((0x66 ), (0x65 ), (0x70 ), (0x70 ), (0x80 ), (0xBA ), (0x6B ), (0x8C ), (0x75 ), (/*0xA0*/0x70 )) 
	#define RY_HUEP_TEMP_L		DFSEL_Sens((0x64 ), (0x72 ), (0x65 ), (0x65 ), (0x80 ), (0x84 ), (0x88 ), (0x65 ), (0x67 ), (/*0x40*/0x65 ))    
	                                                                                                                             
	// MID TEMP                                                                                                                  
	#define BY_GAINN_TEMP_M		DFSEL_Sens((0x55 ), (0x3A ), (0x58 ), (0x58 ), (0x40 ), (0x80 ), (0x95 ), (0x60 ), (0x6A ), (0x58 ))
	#define BY_GAINP_TEMP_M		DFSEL_Sens((0x50 ), (0x25 ), (0x45 ), (0x45 ), (0x40 ), (0x70 ), (0x70 ), (0x40 ), (0x50 ), (0x45 ))
	#define RY_GAINN_TEMP_M		DFSEL_Sens((0x50 ), (0x3A ), (0x5C ), (0x5C ), (0x40 ), (0x70 ), (0x90 ), (0x60 ), (0x60 ), (0x5C ))
	#define RY_GAINP_TEMP_M		DFSEL_Sens((0x45 ), (0x2A ), (0x48 ), (0x48 ), (0x40 ), (0x70 ), (0x75 ), (0x50 ), (0x55 ), (0x58 ))
	                                                                                                                                
	#define BY_HUEN_TEMP_M		DFSEL_Sens((0x60 ), (0x5D ), (0x70 ), (0x70 ), (0x80 ), (0x68 ), (0x61 ), (0x5F ), (0x48 ), (0x70 ))
	#define BY_HUEP_TEMP_M		DFSEL_Sens((0x5D ), (0x62 ), (0x30 ), (0x30 ), (0x80 ), (0x3A ), (0x60 ), (0x51 ), (0x49 ), (0x30 ))
	#define RY_HUEN_TEMP_M		DFSEL_Sens((0x66 ), (0x65 ), (0x70 ), (0x70 ), (0x80 ), (0xBA ), (0x6B ), (0x8C ), (0x75 ), (0x70 ))
	#define RY_HUEP_TEMP_M		DFSEL_Sens((0x64 ), (0x72 ), (0x65 ), (0x65 ), (0x80 ), (0x84 ), (0x88 ), (0x65 ), (0x67 ), (0x65 ))
                                                                                                                                 
	// HIGH TEMP                                                                                                                 
	#define BY_GAINN_TEMP_H		DFSEL_Sens((0x55 ), (0x3A ), (0x50 ), (0x50 ), (0x40 ), (0x80 ), (0x95 ), (0x60 ), (0x6A ), (0x50 ))
	#define BY_GAINP_TEMP_H		DFSEL_Sens((0x50 ), (0x25 ), (0x40 ), (0x40 ), (0x40 ), (0x70 ), (0x70 ), (0x40 ), (0x50 ), (0x40 ))
	#define RY_GAINN_TEMP_H		DFSEL_Sens((0x50 ), (0x3A ), (0x58 ), (0x58 ), (0x40 ), (0x70 ), (0x90 ), (0x60 ), (0x60 ), (0x58 ))
	#define RY_GAINP_TEMP_H		DFSEL_Sens((0x45 ), (0x2A ), (0x48 ), (0x48 ), (0x40 ), (0x70 ), (0x75 ), (0x50 ), (0x55 ), (0x58 ))
	                                                                                                                                
	#define BY_HUEN_TEMP_H		DFSEL_Sens((0x60 ), (0x5D ), (0x60 ), (0x60 ), (0x80 ), (0x68 ), (0x61 ), (0x5F ), (0x48 ), (0x60 ))
	#define BY_HUEP_TEMP_H		DFSEL_Sens((0x5D ), (0x62 ), (0x30 ), (0x30 ), (0x80 ), (0x3A ), (0x60 ), (0x51 ), (0x49 ), (0x30 ))
	#define RY_HUEN_TEMP_H		DFSEL_Sens((0x66 ), (0x65 ), (0x70 ), (0x70 ), (0x80 ), (0xBA ), (0x6B ), (0x8C ), (0x75 ), (0x70 ))
	#define RY_HUEP_TEMP_H		DFSEL_Sens((0x64 ), (0x72 ), (0x65 ), (0x65 ), (0x80 ), (0x84 ), (0x88 ), (0x65 ), (0x67 ), (0x65 ))
#endif

	#else
	#define	AWB_DBOFFSET		DFSEL_Sens((0x28 ), (0x0  ), (0x0  ), (0x56  ), (0x0  ), (0x25 ), (0x0  ), (0x0  ), (0x0  ), (0x0  ))	// Color map coordinate x offset
	#define	AWB_DROFFSET		DFSEL_Sens((0x109), (0x0  ), (0x0  ), (0xde  ), (0x0  ), (0xf7 ), (0x0  ), (0x0  ), (0x0  ), (0x0  ))	// Color map coordinate y offset
	#define	AWB_DBGAIN  		DFSEL_Sens((0xf  ), (0x0  ), (0x0  ), (0xf  ), (0x0  ), (0xe  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ))	// Color map coordinate X gain
	#define	AWB_DRGAIN  		DFSEL_Sens((0xd  ), (0x0  ), (0x0  ), (0xe  ), (0x0  ), (0xc  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ))	// Color map coordinate y gain

	#define HnG_TEMP_L			(AWB_TEMP_VAL_L)
    #define HnG_TEMP_M			(AWB_TEMP_VAL_M)
    #define HnG_TEMP_H          (AWB_TEMP_VAL_H)
	
	// LOW TEMP                                                                                     
	// #define BY_GAINN_TEMP_L		DFSEL_Sens((0x55 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x55 ), (0x40 ), (0x40 ), (0x40 ), (0x40 )) 
	// #define BY_GAINP_TEMP_L		DFSEL_Sens((0x50 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x55 ), (0x40 ), (0x40 ), (0x40 ), (0x40 )) 
	// #define RY_GAINN_TEMP_L		DFSEL_Sens((0x50 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x55 ), (0x40 ), (0x40 ), (0x40 ), (0x40 )) 
	// #define RY_GAINP_TEMP_L		DFSEL_Sens((0x45 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x55 ), (0x40 ), (0x40 ), (0x40 ), (0x40 )) 
                                                                                                                                     
	// #define BY_HUEN_TEMP_L		DFSEL_Sens((0xE0 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 )) 
	// #define BY_HUEP_TEMP_L		DFSEL_Sens((0xDD ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0xD0 ), (0x00 ), (0x00 ), (0x00 ), (0x00 )) 
	// #define RY_HUEN_TEMP_L		DFSEL_Sens((0xE6 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 )) 
	// #define RY_HUEP_TEMP_L		DFSEL_Sens((0xE4 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))    
	                                                                                                                      
	// MID TEMP                                                                                                           
	// #define BY_GAINN_TEMP_M		DFSEL_Sens((0x55 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x55 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	// #define BY_GAINP_TEMP_M		DFSEL_Sens((0x50 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x55 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	// #define RY_GAINN_TEMP_M		DFSEL_Sens((0x50 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x55 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	// #define RY_GAINP_TEMP_M		DFSEL_Sens((0x45 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x55 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	                                                                                                                                
	// #define BY_HUEN_TEMP_M		DFSEL_Sens((0xE0 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))
	// #define BY_HUEP_TEMP_M		DFSEL_Sens((0xDD ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0xD0 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))
	// #define RY_HUEN_TEMP_M		DFSEL_Sens((0xE6 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))
	// #define RY_HUEP_TEMP_M		DFSEL_Sens((0xE4 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))
                                                                                                                          
	// HIGH TEMP                                                                                                          
	// #define BY_GAINN_TEMP_H		DFSEL_Sens((0x55 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x55 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	// #define BY_GAINP_TEMP_H		DFSEL_Sens((0x50 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x55 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	// #define RY_GAINN_TEMP_H		DFSEL_Sens((0x50 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x55 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	// #define RY_GAINP_TEMP_H		DFSEL_Sens((0x45 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x55 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	                                                                                                                                
	// #define BY_HUEN_TEMP_H		DFSEL_Sens((0xE0 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))
	// #define BY_HUEP_TEMP_H		DFSEL_Sens((0xDD ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0xD0 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))
	// #define RY_HUEN_TEMP_H		DFSEL_Sens((0xE6 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))
	// #define RY_HUEP_TEMP_H		DFSEL_Sens((0xE4 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))
	#endif
	
#elif(model_5M)
	#if(model_AWB_Matrix==0)
			// MP V1.0.0
		#if(0)
			#define	AWB_DBOFFSET		(0x56 )	// Color map coordinate x offset
			#define	AWB_DROFFSET		(0xde )	// Color map coordinate y offset
			#define	AWB_DBGAIN  		(0xf  )	// Color map coordinate X gain
			#define	AWB_DRGAIN  		(0xe  )	// Color map coordinate y gain
			#else
			#define	AWB_DBOFFSET		(0x37 )
			#define	AWB_DROFFSET		(0xf1 )
			#define	AWB_DBGAIN  		(0x10 )
			#define	AWB_DRGAIN  		(0xe  )
			#endif
		#else
			#define	AWB_DBOFFSET		DFSEL_Sens((0x20 ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0x3d ), (0x0  ), (0x0  ), (0x0  ), (0x0  ))	// Color map coordinate x offset
			#define	AWB_DROFFSET		DFSEL_Sens((0x102), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0xe2 ), (0x0  ), (0x0  ), (0x0  ), (0x0  ))	// Color map coordinate y offset
			#define	AWB_DBGAIN  		DFSEL_Sens((0xf  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0xf  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ))  	// Color map coordinate X gain
			#define	AWB_DRGAIN  		DFSEL_Sens((0xd  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ), (0xd  ), (0x0  ), (0x0  ), (0x0  ), (0x0  ))  	// Color map coordinate y gain
		#endif

	#define HnG_TEMP_L			(AWB_TEMP_VAL_L)
    #define HnG_TEMP_M			(AWB_TEMP_VAL_M)
    #define HnG_TEMP_H          (AWB_TEMP_VAL_H)

#if(model_ImgTune_Option==0)
	// LOW TEMP                                                                                     
	#define BY_GAINN_TEMP_L		DFSEL_Sens((0x78 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 )) 
	#define BY_GAINP_TEMP_L		DFSEL_Sens((0x68 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 )) 
	#define RY_GAINN_TEMP_L		DFSEL_Sens((0x70 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 )) 
	#define RY_GAINP_TEMP_L		DFSEL_Sens((0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 )) 
                                                                                                                                     
	#define BY_HUEN_TEMP_L		DFSEL_Sens((0x30 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 )) 
	#define BY_HUEP_TEMP_L		DFSEL_Sens((0x2A ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 )) 
	#define RY_HUEN_TEMP_L		DFSEL_Sens((0x8D ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 )) 
	#define RY_HUEP_TEMP_L		DFSEL_Sens((0x60 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))    
	                                                                                                                      
	// MID TEMP                                                                                                           
	#define BY_GAINN_TEMP_M		DFSEL_Sens((0x78 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	#define BY_GAINP_TEMP_M		DFSEL_Sens((0x68 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	#define RY_GAINN_TEMP_M		DFSEL_Sens((0x70 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	#define RY_GAINP_TEMP_M		DFSEL_Sens((0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	                                                                                                                                
	#define BY_HUEN_TEMP_M		DFSEL_Sens((0x30 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))
	#define BY_HUEP_TEMP_M		DFSEL_Sens((0x2A ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))
	#define RY_HUEN_TEMP_M		DFSEL_Sens((0x8D ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))
	#define RY_HUEP_TEMP_M		DFSEL_Sens((0x60 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))
                                                                                                                          
	// HIGH TEMP                                                                                                          
	#define BY_GAINN_TEMP_H		DFSEL_Sens((0x78 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	#define BY_GAINP_TEMP_H		DFSEL_Sens((0x68 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	#define RY_GAINN_TEMP_H		DFSEL_Sens((0x70 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	#define RY_GAINP_TEMP_H		DFSEL_Sens((0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ), (0x40 ))
	                                                                                                                                
	#define BY_HUEN_TEMP_H		DFSEL_Sens((0x30 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))
	#define BY_HUEP_TEMP_H		DFSEL_Sens((0x2A ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))
	#define RY_HUEN_TEMP_H		DFSEL_Sens((0x8D ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))
	#define RY_HUEP_TEMP_H		DFSEL_Sens((0x60 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ), (0x00 ))
#endif

#endif

//*************************************************************************************************
// 11. DEFECT
//-------------------------------------------------------------------------------------------------
extern void Defect(void);

//*************************************************************************************************
// 12. SHADING
//-------------------------------------------------------------------------------------------------
extern void InitShd(void);
extern void Shading(void);

//*************************************************************************************************
// 14. ETC (ISP applications)
//-------------------------------------------------------------------------------------------------
// ADNR
extern void Adnr(void);

#define DNR_Q_TBL_NUM			32

extern WORD gwDNR3D_Val;

//------------------------------------------------------------------------------
// Sharpness
extern void Sharpness(void);

#define EXT_DNR(CN,DISCN)		((MP(MpExtDNR)==MN_EXT_DNR_CONN)?(CN):(DISCN))
//------------------------------------------------------------------------------
// Color Surpression
extern void CSup(void);

#if(0)
						//         0    1    2    3    4    5    6    7    8    9
#if (model_1M)
	#define CSUP_TH 	DFSEL_Sens(0x74,0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00)

#elif (model_2M)
	#if(model_2M_L)
	#define CSUP_TH 	DFSEL_Sens(0x74,0x74,0x74,0x74,0x00,0x74,0x74,0x74,0x74,0x00)
	#else	
	#define CSUP_TH 	DFSEL_Sens(0x69,0x00,0x00,0x00,0x00,0x6D,0x00,0x74,0x00,0x00)
	#endif

#elif (model_5M)
	#define CSUP_TH 	DFSEL_Sens(0x90,0x00,0x00,0x00,0x00,0x65,0x00,0x00,0x72,0x00)
#endif
#endif

//------------------------------------------------------------------------------
// Highlight Mask
extern void HlMask(void);

//------------------------------------------------------------------------------
// Mirro / Flip
extern void Sens(SENS_MIRw)(BYTE abOn);
extern void Sens(SENS_FLPw)(BYTE abOn);

extern void Mirror(void);
extern void Flip(void);

#define MIRROR_ON		((MP(MpMirror)==MN_ON)||(UP(UpMirror)==MN_ON))
#define	FLIP_ON			((MP(MpFlip)==MN_ON)||(UP(UpFlip)==MN_ON))

#define	MIR_ON			(SENS_MIRw(MN_ON ))
#define MIR_OFF			(SENS_MIRw(MN_OFF))

#define FLP_ON			(SENS_FLPw(MN_ON ))
#define FLP_OFF			(SENS_FLPw(MN_OFF))

//------------------------------------------------------------------------------
// Color bar
extern void ColorBar(void);

#if(model_1M)
	#define DCBAR_HW	0xA2
	#define DCBAR_ST	0x34
#elif(model_2M)
	#define DCBAR_HW	0xF3
	#define DCBAR_ST	0x5B
#elif(model_5M)
	#define DCBAR_HW	0x149
	#define DCBAR_ST	0x58
#endif

//------------------------------------------------------------------------------
// Color space
extern void ColorSpace(void);

//------------------------------------------------------------------------------
// Image Range
extern void ImageRange(void);


//------------------------------------------------------------------------------
// Privacy - BOX
extern void PrivacyBox(void);
extern void BoxLast(void);

UINT gnPixelStepH;
UINT gnPixelStepV;

#define BOX_TONE_100	3
#define BOX_TONE_50		2
#define BOX_TONE_25		1
#define BOX_TONE_0		0

#define BOX_ON(ID)		BOSD_ONw(BOSD_ONr | (1<<ID))
#define BOX_OFF(ID)		BOSD_ONw(BOSD_ONr & (~(1<<ID)))

#define BOX_COLOR(ID,Y,CB,CR)	{\
	BOX##ID##_PLTw( (((Y)&0xFF)<<16) | (((CB)&0xFF)<<8) | ((CR)&0xFF) );\
}

#define BOX_ATT(ID,FILL,TONE,Y,CB,CR) {\
	BFL_ON##ID##w(FILL);\
	BTONE##ID##w(TONE);\
	BOX_COLOR(ID,Y,CB,CR)\
}

#define BOX(ID,SX,SY,EX,EY)	{\
	B##ID##_HSPw(SX);\
	B##ID##_HEDw(EX);\
	B##ID##_VSPw(SY);\
	B##ID##_VEDw(EY);\
}

#define PVC_EA				(16)										// number of Privacy Box (max 32ea, CAUTION)

#if(1)

#define BOX_HSP				(MIRROR_ON)?(MODE_VAL(0xB4,0x60,0x6B,0x6E,0x54)):(MODE_VAL(0xB4,0x7B,0x73,0x6E,0x6F))
#define BOX_VSP				(MP(MpFlip  )==MN_ON)?(MODE_VAL(0x13,0x3,0x10,0x1E,0x14)):(MODE_VAL(0x13,0x1A,0x1A,0x1E,0x12))

#define BOX_MOVPIXEL		(0x20)
//#define BOX_XMAX			(MODE_2M_ON) ? (FR_HW/gnPixelStepH+1) : (FR_HW/gnPixelStepH)													//Menu Box Position Control X Max Value
//#define BOX_YMAX			(MODE_2M_ON) ? (FR_VW/gnPixelStepV+2) : (FR_VW/gnPixelStepV+1)
#define BOX_XMAX			((HWOr/gnPixelStepH)+1)													//Menu Box Position Control X Max Value
#define BOX_YMAX			((VWOr/gnPixelStepV)+1)

#define BOX_COLOR_STEP		(0x14)

#else
#if(model_1M)
	#define BOX_HSP			(MP(MpMirror))?(-0xA):(0x3)
	#define BOX_VSP			0x0
    #define BOX_FVSP        (-0x3)

#elif(model_2M)
	#define BOX_VSP			(0x1A)
	#define BOX_HSP			(0x73)

#elif(model_5M)
//	#define BOX_HSP			((MP(MpMirror)==MN_ON)?(0x62):(0x72))
	// 1M 25,30 TVI 0x68(MIR_OFF), 5M 20p Digital 0x65(MIR_ON)
	#define BOX_HSP			((MP(MpOutFps)==MN_5M_1944p_20) ? ((MP(MpMirror)==MN_ON)?(0x65):(0x74)) : ((MP(MpMirror)==MN_ON)?(0x5e):(0x6c)))/*(((MODE_1M_ON) ? (0x6d) : (0x71))))*/

//	#define BOX_VSP			((!MODE_5M_ON)?((MP(MpFlip)==MN_ON)?(0xB):(0x1C)):((MP(MpFlip)==MN_ON)?(0xB):(0x0)))
	#define BOX_VSP			((!MODE_5M_ON)?((MP(MpFlip)==MN_ON)?(0xB):(0x10)):((MP(MpFlip)==MN_ON)?(0x3):(0x6)))
#endif
#endif

#if(0)
#define BOX_REV_POS(YPOS,XPOS)	if(MP(MpFlip))		YPOS = ((VWOr - (YPOS & BitMask_16))<<16)|(VWOr - (ValSft_R16(YPOS)));\
								else				YPOS = YPOS;\
								if(MP(MpMirror))	XPOS = ((HWOr - (XPOS & BitMask_16))<<16)|(HWOr - (ValSft_R16(XPOS)));\
								else				XPOS = XPOS;
#endif


#ifndef __LIB__

typedef struct _tagPRIVACY{
	BYTE	bAction;
	BYTE	bPosX;
	BYTE	bPosY;
	BYTE	bSizX;
	BYTE	bSizY;
} _PRIVACY;


//------------------------------------------------------------------------------
// Last Box apply
extern UINT gnBoxPltPVC[PVC_EA];
extern UINT gnBoxTonePVC;
extern UINT gnBoxFillPVC;

extern UINT gnBoxPosPVC[PVC_EA*2];
extern UINT gnBoxOnPVC;


#endif//__LIB__

//*************************************************************************************************
// 15. FOCUS ( Focus Contorl Method )
//-------------------------------------------------------------------------------------------------                                     
// Focus Assist
#if (model_Lens==0)
	#define Focus		

// TwoMotor AF
#elif (model_Lens==1)	// 180802 JJH remove unused define, add define MAF_LENS_MODEL, MAF_FOSD_DISP

    #define Focus   {Motorized_AF();\
					extern BYTE gbAutoFocus_Flag;\
					if(gbAutoFocus_Flag /*&& (MP(MpBackLight)!=MN_BL_WDR)*/) 	{BoxLast();	continue;}}		// 191202 PChan : AE stop while processing 2-Motor

    #define	MAF_LENS_MODEL		3	 //*0 : YT2812
                                     // 1 : YT3013
                                     // 2 : YT3017
                                     // 3 : YT3021

    #define MAF_FOSD_DISP		1	 //*0 : No Font OSD Display
                                     // 1 : Font OSD Display (Control State)

    #define MAF_BOSD_DISP		1	 // 0 : No Box OSD Display
                                     //*1 : Box OSD Display Style #1 (Zoom&Focus / Coordinates)

    #define MAF_DOM_INIT        0    //*0 : defualt
                                     // 1 : dom

    #define MAF_INITIAL_OFF		0    // Initializing at booting
    								 // 0 : ON
    								 // 1 : Off
    #define MAF_OnePushAfSel    0    //  

	extern void Motorized_AF(void);
	extern void MAF_PhaseControl(void);
	extern BYTE gbOzone_Hold, gbMaf_TimerEn,gbMAF_Calibration,gbMAF_DevMode;

//    #define MAF_BOX_START   27 // Box No.29~31
 	#define MAF_BOX_START   16 // Box No.16~20
 	#define MAF_BOX_NUM		5

	extern UINT gnBoxPosMAF_Y[MAF_BOX_NUM];
	extern UINT gnBoxPosMAF_X[MAF_BOX_NUM];
	extern UINT gnBoxPltMAF[MAF_BOX_NUM];
	extern UINT gnBoxToneMAF;
	extern UINT gnBoxFillMAF;
	extern UINT gnBoxOnMAF;
	extern BYTE gbMAFBoxFlag;
	extern WORD gwMAF_Zrange_T, gwMAF_Frange_T, gwMAF_Fpos_S, gwMAF_Fpos_E, gwMAF_Zpos_S, gwMAF_Zpos_E; // 180427 JJH tuning

#endif	

/* EOF */
