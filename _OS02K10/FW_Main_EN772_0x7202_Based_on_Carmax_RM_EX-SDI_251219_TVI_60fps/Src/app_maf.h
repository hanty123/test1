/* **************************************************************************
 File Name	: 	isp_app_maf.h
 Description	:	Motorized AF Function Header file
 Designer		:	Lee, Wanhee
 Date		:	17.11.07
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */
	
#ifndef __MOTORIZED_AF_H__
#define __MOTORIZED_AF_H__

//=================================================================================================
//	Lib function
//=================================================================================================
extern void MAF_EnvironmentSet_Lib(void);
extern void MAF_WindowSet_Lib(void);
extern void MAF_DataBuffering(void);

//=================================================================================================
//	Main function
//=================================================================================================
void MAF_Position_Save(void);
void MAF_Position_Load(void);
void MAF_EnvironmentSet(void);
void Motorized_AF(void);

BYTE gbAF_MainState=1;
BYTE gbMAF_DevMode=0;
BYTE gbMaf_Tccflag=0;
BYTE gbMAF_Excute=0;

//Zoom/Focus Position save to EEPROM
BYTE gbMAF_TwiTx_Z[2]={0,};
BYTE gbMAF_TwiRx_Z[2]={0,};
BYTE gbMAF_TwiTx_F[2]={0,};
BYTE gbMAF_TwiRx_F[2]={0,};
BYTE gbMAF_WrEEP=0, gbMAF_RdEEP=1;

#if MAF_DOM_INIT // 181128 JJH
    UINT gnFocusInitPosiBuf=0;
#endif

#if (MAF_LENS_MODEL==0) // YT2812
#define MAF_RANGE_Z			5120 // 0x1400
#define MAF_START_Z			600  // 0x258
#define MAF_END_Z			4600 // 0x1200

#define MAF_RANGE_F			5400 // 0x1400
#define MAF_START_F			600  // 0x258
#define MAF_END_F			4800 // 0x12C0 YT2812 (@Holder 14mm)

#elif (MAF_LENS_MODEL==1) // YT3013
#define MAF_RANGE_Z			5120 // 0x1400
#define MAF_START_Z			600  // 0x258
#define MAF_END_Z			4608 // 0x1200

#define MAF_RANGE_F			6144 // 0x1800
#define MAF_START_F			600  // 0x258
#define MAF_END_F			5824 // 0x16C0

#elif (MAF_LENS_MODEL==2) // YT3017
#define MAF_RANGE_Z			5120 // 0x1400
#define MAF_START_Z			600  // 0x258
#define MAF_END_Z			4608 // 0x1200

#define MAF_RANGE_F			4864 // 0x1300
#define MAF_START_F			256  // 0x100
#define MAF_END_F			4608 // 0x1200

#elif (MAF_LENS_MODEL==3) // YT3017
#define MAF_RANGE_Z			4800 // 0x1300
#define MAF_START_Z			300  // 0x100
#define MAF_END_Z			4500 // 0x1200

#define MAF_RANGE_F			5100 // 0x1600
#define MAF_START_F			200  // 0x100
#define MAF_END_F			4900 // 0x1500

#endif

#define MAF_LDOF_Z			(MAF_RANGE_Z*2/3) // 0xC00 - Low DOF(Depth Of Focus) Point
#define MAF_REVERS_STEP_Z	0
#define MAF_REVERS_STEP_F	0x30

#define MAF_STEP_ADJ        ((MODE_5M_ON) ? 2 : 1)
#define MAF_STEP_INIT       ((MP(MpOutFps)==MN_5M_1944p_125)? 19 : (MP(MpOutFps)==MN_5M_1944p_20)? 12 : MP(MpSysFreq) ? 16 : 19)

#define MAF_MAX_STEP        (UINT)(MAF_STEP_INIT<<MAF_STEP_ADJ)
#define MAF_MNL_STEP_F		(10<<1)

#define MAF_RangeSTEP        40


// 180427 JJH Lens Range
WORD gwMAF_Zrange_T = MAF_RANGE_Z, gwMAF_Frange_T = MAF_RANGE_F, gwMAF_Fpos_S = MAF_START_F, gwMAF_Fpos_E = MAF_END_F, gwMAF_Zpos_S = MAF_START_Z, gwMAF_Zpos_E = MAF_END_Z; 

BYTE gbMAF_SETUP = 0, gbMAF_MZrange_T = 0, gbMAF_MFrange_T=0, gbMAF_MZpos_S=0, gbMAF_MZpos_E=0, gbMAF_MFpos_S=0, gbMAF_MFpos_E=0;

//=================================================================================================
//	Control Command check
//=================================================================================================
void MAF_CmdCheck(void);

BYTE gbMAF_TrgCnt=0, gbMAF_Calibration=0, gbDnN_Changed=0;

//=================================================================================================
//	Motor Manual Control
//=================================================================================================
void MAF_MnlMotorControl(BYTE abExcute);
void MAF_ZoomTracking(void);
void MAF_Current_Mng(void);

BYTE gbMAF_ZoomTrkEn=0, gbMaf_MnlSpeed=0;

typedef struct _MAF_MOTOR_STRUCTURE {
	UINT nCurPos;				/* Motor Current Position */
	UINT nTgtPos;				/* Motor Target Position */
	BYTE bPosGo;				/* Position Control Enable */
	BYTE bActive;				/* Active State */
	BYTE bDirFlag;				/* Control Direction Flag */
	BYTE bDirFlagBuf;			/* Control Direction Flag Buffer */
	BYTE bReverseCnt;			/* Reverse counter for position loss */
	BYTE bSpeedCnt;				/* Motor Speed Counter */
	BYTE bStateStep;			/* Motor Phase step */
	BYTE bStateStepBuf;			/* Motor Phase step Buffer */
} Maf_motor_structure;

Maf_motor_structure Maf_Zmotor={0,0,0,0,0,0,0,0,1,0};
Maf_motor_structure Maf_Fmotor={0,0,0,0,0,0,0,0,1,0};

extern volatile UINT *gnMaf_LibCurPos_F;
extern volatile UINT *gnMaf_LibTgtPos_F;
extern volatile BYTE *gbMaf_LibTgtCtr_Go;

//=================================================================================================
//	Auto Focus (No Library)
//=================================================================================================
void MAF_AutoFocus(void);

#define MAF_ONESHOT_TRG_TIME		40 // AF Enable delay time after Zoom move stop
#define MAF_ONESHOT_FILTER_TIME		(MAF_ONESHOT_TRG_TIME<<1) // AF Enable delay time after D&N Filter Change

#define MAF_TRY_MAX		5 // Max Retry Times @Not Peak Data when the focus point
#define MAF1_DIRV		4
#define MAF2_DIRV		2
#define MAF_YSCALE		0x0F
#define MAF_YALPHA_MIN	0x3E8
#define MAF_YALPHA_MAX	0x4B0
#define MAF_DAVG_OFS0	20
#define MAF_DAVG_OFS1	30

volatile int giMaf_AF_TryMax     = MAF_TRY_MAX; // Maximum AF Retry Times

volatile UINT gnMaf_FPosRange[2]; // Total Focus Range

// for Focus Direction Filter
volatile int giMaf_DirNo_P[2]    = { MAF1_DIRV, MAF2_DIRV};
volatile int giMaf_DirNo_M[2]    = {-MAF1_DIRV,-MAF2_DIRV};
volatile int giMaf_DAvg_Ofs[2]   = {MAF_DAVG_OFS0,MAF_DAVG_OFS1};

// for AF Data Normalization
volatile int giMaf_CurGain=0, giMaf_GainRange[2]={0,0};
volatile UINT gnMaf_AF_DATA[2]={0,0}, gnMaf_Y_DATA[2]={0,0};
volatile UINT gnMaf_AF_DATA_M[2]={0,0}, gnMaf_Y_DATA_M[2]={0,0};
volatile UINT gnMaf_AF_DATA_S[2]={0,0}, gnMaf_Y_DATA_S[2]={0,0};

volatile UINT gnMAF_YnmlAlpha[2] = {MAF_YALPHA_MIN,MAF_YALPHA_MAX};
volatile UINT gnMaf_Y_SCALE[2]   = {MAF_YSCALE,MAF_YSCALE};

// AF Complete Peak Data Success rate(Scanning Peak AF Data vs Finish AF Data)
volatile UINT gnMaf_TgtPeakMgn   = 50;//95; // % Matching Percentage

// from Library
extern const int Sens(AE_GAIN_TOTAL);
extern void MAF_PreProcessing(void);
extern void MAF_OneTimeAF(void);

extern BYTE gbMAF_OneTimeState;
extern BYTE gbAutoFocus_Flag;

extern UINT gnMaf_TgtPeakVal_F, giMAF1_DirCntBuf[15], gnAF1_Normalization;

//=================================================================================================
//	Lens State Display
//=================================================================================================
#define BAF_BOXOSD_TIME		15

void MAF_Lens_StateDisp(void);
void MAF_DebugingDisp(void);

BYTE gbMAFDebugOn=0, gbMAF_OutputMode=0; // 181128 JJH

#if (model_1M)
    #define MAF1_HSP    0x77
    #define MAF1_HEP    0x220
    #define MAF1_VSP    0x60
    #define MAF1_VEP    0x260
#if (MAF_FOSD_DISP==1)
    #define MAF_FOSD_PosY   16
#endif
    #define MAF_FOSD_PosY_Dbg   12

#if (MAF_BOSD_DISP!=0)
    UINT gnBoxPosMAF_Y[MAF_BOX_NUM] = {0x02500251, 0x021002c2, 0x02500251, 0x0021002c2, 0x021002c2};
    UINT gnBoxPosMAF_X[MAF_BOX_NUM] = {0x04000401, 0x040000401, 0x03ff04e0, 0x03ff04e0, 0x03ff04e0};
#endif	

#elif (model_2M) 	// 170913 HTY                  
    #define MAF1_HSP    0x8e
    #define MAF1_HEP    0x380
    #define MAF1_VSP    0x7c
    #define MAF1_VEP    0x3b0
#if (MAF_FOSD_DISP==1)
    #define MAF_FOSD_PosY   16
#endif
    #define MAF_FOSD_PosY_Dbg   14 // PCHAN 21.03.08 : position change 16->14

#if (MAF_BOSD_DISP!=0)
    UINT gnBoxPosMAF_Y[MAF_BOX_NUM] = {0x00300130, 0x00300130, 0x00300130, 0x00300130, 0x00300130};
    UINT gnBoxPosMAF_X[MAF_BOX_NUM] = {0x058a072a, 0x058a072a, 0x058a072a, 0x058a072a, 0x058a072a};

//			gnBoxPosMAF_X[4] = gnBoxPosMAF_X[2] = 0x05eb0751;
//				gnBoxPosMAF_Y[4] = gnBoxPosMAF_Y[1] = 0x0021011d;  
#endif	

#elif (model_5M)   // 170731 HTY                   
    #define MAF1_HSP    0xac
    #define MAF1_HEP    0x49f
    #define MAF1_VSP    (MODE_5M_ON) ? (0x100) : ( 0xc2) // PCHAN 21.03.08 : position change 0xc3->0xc2  
    #define MAF1_VEP    (MODE_5M_ON) ? (0x67a) : (0x4da)   
#if (MAF_FOSD_DISP==1)
    #define MAF_FOSD_PosY   16 // 210401 PCHAN : position change 17->16
#endif
    #define MAF_FOSD_PosY_Dbg   12 // PCHAN 21.03.08 : position change 22-> 12
	

#if (MAF_BOSD_DISP!=0)
    UINT gnBoxPosMAF_Y[MAF_BOX_NUM] = {0x00300180, 0x00300180, 0x00300180, 0x00300180, 0x00300180};
    UINT gnBoxPosMAF_X[MAF_BOX_NUM] = {0x07e009c0, 0x07e009c0, 0x07e009c0, 0x07e009c0, 0x07e009c0};
#endif

#else
#endif

#if (MAF_BOSD_DISP!=0)
//#define MAF_BOX_BITMASK		0xF8000000
#define MAF_BOX_BITMASK		0x1F

UINT gnBoxPltMAF[MAF_BOX_NUM]   = {0x004C54FF, 0x00fd13b0, 0x00fd13b0, 0x00df7f7f, 0x005f7f7f};

UINT gnBoxToneMAF = 0x2A400000;
UINT gnBoxFillMAF = 1;
UINT gnBoxOnMAF = 0;
BYTE gbMAFBoxFlag = 0;
WORD gwMAF_BoxSY=0, gwMAF_BoxSX=0, gwMAF_BoxEY=0, gwMAF_BoxEX=0;
#endif

#if(MAF_FOSD_DISP==1)
#define MAF_LENS_INIT	(gbAF_MainState==1)
#define MAF_AUTOFOCUS	(gbAutoFocus_Flag==1)
#define MAF_ZTRACKING	(gbMAF_ZoomTrkEn==1)
#define MAF_AGINGTEST	(MP(MpMAF_TestMode)==1)
#define MAF_PRESET_MV	(Maf_Zmotor.bPosGo|Maf_Fmotor.bPosGo)
#endif

#define Z_SpdCtrOn		(((!gbMenuState)||(gbAF_MainState==1)||gbMAF_SETUP)&&(Maf_Zmotor.nCurPos!=Maf_Zmotor.nTgtPos))
#define F_SpdCtrOn      (((!gbMenuState)||gbAutoFocus_Flag||(gbAF_MainState==1)||gbMAF_SETUP)&&(Maf_Fmotor.nCurPos!=Maf_Fmotor.nTgtPos))
//#define SPEED_SEL       ((model_5M&&((MP(MpOutFps)==MN_5M_1944p_20)||(MP(MpOutFps)==MN_5M_1944p_125)))||(model_2M&&((MP(MpOutFps)==MN_2M_1944p_20)||(MP(MpOutFps)==MN_2M_1944p_125)))) // 210527 HTY : 2-Motor speed control at 5M
#define SPEED_SEL       (MODE_5M_ON) // 210527 HTY : 2-Motor speed control at 5M

//==========================================================================================
// Motor Speed & Buffer Delay 
//==========================================================================================

#if(0)
#define MOTOR_SPEED0		1	// ZoomTracking Speed
#define MOTOR_SPEED1		2	// Auto Focusing Speed
#define MOTOR_SPEED2		2	// Manual Focusg&Zoom Speed
#define MOTOR_SPEED_5M      3   // Auto Focusing Speed in 5M // 210527 HTY : 2-Motor speed control at 5M
#else
// 210826 HTY : 2-motor speed according to MCU clock speed
#define MOTOR_SPEED0		0	// ZoomTracking Speed
#define MOTOR_SPEED1		1	// Auto Focusing Speed
#define MOTOR_SPEED2		1	// Manual Focusg&Zoom Speed
#define MOTOR_SPEED_5M      2   // Auto Focusing Speed in 5M // 210527 HTY : 2-Motor speed control at 5M

#endif

#define POSITION_DELAY      0	// Frame buffer delay

BYTE gbMAF_FrDly = POSITION_DELAY; // 
#define ScanMargin   (Maf_Zmotor.nCurPos<MAF_LDOF_Z ? 350 : 250)
UINT gnScanMargin=0;
BYTE gbOnePushAfSel=MAF_OnePushAfSel;   
//extern BYTE gbScanSel;

BYTE gbMotorSpeedStep[3] = {MOTOR_SPEED0, MOTOR_SPEED1, MOTOR_SPEED2};  

//=================================================================================================
//	GPIO Drive Handling (Timer IRQ Base)
//=================================================================================================
#define MAF_STEP1		1
#define MAF_STEP2		2
#define MAF_STEP3		3
#define MAF_STEP4		4
#define MAF_STEP5		5
#define MAF_STEP6		6
#define MAF_STEP7		7
#define MAF_STEP8		8

#define MAF_H		GpioSetHi
#define MAF_L		GpioSetLo

#define MAF_AP_Z    GPIO_MTR_ZOOM_AP
#define MAF_AM_Z    GPIO_MTR_ZOOM_AM
#define MAF_BP_Z    GPIO_MTR_ZOOM_BP
#define MAF_BM_Z    GPIO_MTR_ZOOM_BM
#define MAF_AP_F    GPIO_MTR_FCS_AP
#define MAF_AM_F    GPIO_MTR_FCS_AM
#define MAF_BP_F    GPIO_MTR_FCS_BP
#define MAF_BM_F    GPIO_MTR_FCS_BM

// Motor drive current save
#define MAF_HOLD_Z  { MAF_L(MAF_AP_Z); MAF_L(MAF_BP_Z); MAF_L(MAF_AM_Z); MAF_L(MAF_BM_Z); }
#define MAF_HOLD_F  { MAF_L(MAF_AP_F); MAF_L(MAF_BP_F); MAF_L(MAF_AM_F); MAF_L(MAF_BM_F); }

void MAF_MovingState(void);
void MAF_PhaseControl(void);

BYTE gbMaf_TimerEn=0;

//=================================================================================================
//	Lens Initialization
//=================================================================================================
void Lens_AgingTest(void);
void Lens_Initialization(void);
BYTE gbMaf_InitState=0;

//=================================================================================================
//	Trace Curve Auto Calibration
//=================================================================================================
void TraceCurve_Calibration(void);

#define MAF_TRACKING_TBL_STEP	11//20

UINT gnMaf_TblPosition_Z[MAF_TRACKING_TBL_STEP]; // It Calculated by Zoom Active area definition

#if (MAF_LENS_MODEL==0) // YT2812
    UINT gnMaf_TblPosition_F[MAF_TRACKING_TBL_STEP] = { 2077,2645,3163,3548,3849,4084,4235,4375,4486,4497,4541 }; // YT2812 (@Holder 15mm)
#elif (MAF_LENS_MODEL==1) // YT3013
	UINT gnMaf_TblPosition_F[MAF_TRACKING_TBL_STEP] = { 0x0871,0x0CF6,0x102F,0x1260,0x13EC,0x1504,0x15B9,0x1632,0x1657,0x167E,0x1657 }; // YT3013 (@Holder 14mm)
#elif (MAF_LENS_MODEL==2) // YT3017
	UINT gnMaf_TblPosition_F[MAF_TRACKING_TBL_STEP] = { 0x086c,0x0744,0x061c,0x04f4,0x03dc,0x02e5,0x0230,0x0215,0x02b9,0x04c8,0x0933 }; // YT3017 (@Holder 14mm)
#elif (MAF_LENS_MODEL==3) // YT3021
//	UINT gnMaf_TblPosition_F[MAF_TRACKING_TBL_STEP] = { 0x14cd,0x105f,0x0d0d,0x0a94,0x08b1,0x0742,0x0648,0x0581,0x04fc,0x0495,0x0476 }; // YT3021	
    UINT gnMaf_TblPosition_F[MAF_TRACKING_TBL_STEP] = { 2225,2847,3402,3824,4135,4357,4494,4645,4678,4763,4729}; // YT2812 (@Holder 15mm)
#endif

#endif // End of __MOTORIZED_AF_H__

/* EOF */


