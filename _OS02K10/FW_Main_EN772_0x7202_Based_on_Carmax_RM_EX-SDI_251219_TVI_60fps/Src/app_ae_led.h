/* **************************************************************************
 File Name	: 	app_ae_led.h
 Description	:	EN772 - AE-LED application header file
 Designer		:	Yu tae myung
 Date		:	19. 12. 18
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

//******************************************************
// Extern function
//------------------------------------------------------
extern void InitAeLed(void);																			//210302 YTM
extern int  ISPM LibAeLedErrChg (const int, int, const UINT, const UINT, const UINT, const UINT);
extern int LEDSatuCtrl(UINT, UINT, UINT, UINT, UINT, const int,const BYTE);								//210302 YTM
extern int ALAeLedCtrl(const int, int, const int, const int, int);										//210302 YTM

//******************************************************
// Definition LED function
//------------------------------------------------------
// AE-LED Common -----------------------------------------------------------------------------------------
#define AE_LED_PWR(VAL)			IRIS_CLPHw(VAL);											// LED Power Strength (VAL : 1 ~ 1375)
#define AE_LED_TGT_GAIN_FIX		((int)0x10)

//-------------------------------------------------------------------------------------------------
// 180910 JJH Adaptive Lighting

extern BYTE gbTdnExtflag;

extern BYTE gbInModeRes;																	//210426 YTM : FPCK mode change
UINT gnLedTotalclk;																			//210426 YTM : FPCK mode change

extern UINT gnTotalClkOfVLOCK;

#define Adaptive_led	(model_Led==0 || model_Led==2)										//210303 YTM : only LPWM mode(IR,White) 

#if(Adaptive_led)
	extern void LibLED_SET(const UINT, const UINT);
	extern void LibLedMenuChg(void);
	//	extern void LibLedWdrChg(void);
	extern void LibLedIrisChg(void);
	extern int LibAeLedCtrl(const int, int, const int, const int, const int, const int);
	extern void LibAeLedTest(void);

	extern void LibLedTdnChk(void);
	extern int LibLED_OFF_COLOR(const BYTE );
	extern UINT gnAwbOdmCapOn;
    extern BYTE gbLedDlyCnt;
    extern BYTE gbLedMenuChg;
    extern UINT	gnAeLed;

    extern UINT gnAE_LED_Avg, gnAE_LEDClip_Step;  // 181128 JJH
    extern BYTE gbAE_LEDClip_Lv;

    #define AE_LEDClip         ((gnAE_LED_Avg*100)/1023)
    #define AE_LEDClip_Lv      gbAE_LEDClip_Lv
    #define AE_LEDClip_Step    gnAE_LEDClip_Step

    #define AE_LEDStart                 0x30D40             // 0x0 ~ 0xF4240                    // 190610 JJH : LED start position
    #define MN_LED_DRV                  0                   // 0: AP7350, 1: BP1360, 2: EUP2983

	
    // 0 : Apply AE ODM after 1 frame, 1 : Apply AE ODM after 2 frame, 2 : Apply AE ODM after 3 frame <-- Measured when the LibAeLedCtrl() function operates 30 times per second, When AGC is controlled by afAePosflt in LibAeLedCtrl(), 1 delay always occurs due to LibAeLedCtrl() position in Ae()
    #if model_Sens == SENS_IMX290
        #define AE_AGC_DLY  2
        #define AE_LED_Pos_DIS_MAX      ((int)200000)
        #define AE_LED_Pos_DIS_MIN      ((int)200000)
        #define AE_LED_PosX             ((int)216)
        #define AE_LED_PosY             ((int)240)
    #else																									//210426 YTM
        #define AE_AGC_DLY  2
        #define AE_LED_Pos_DIS_MAX      ((int)400000)														
        #define AE_LED_Pos_DIS_MIN      ((int)250000)
        #define AE_LED_PosX             ((int)216)
        #define AE_LED_PosY             ((int)240)
    #endif

    #define AE_LED_Power            10

    extern BYTE gbAE_LED_AePos_STOP, gbAE_LED_TuningOn, gbAE_LED_TEST_RUN;
    extern WORD gwAE_LED_AGC, gwAE_LED_HEP_Hz, gwAE_LED_TEST_STEP;
    extern UINT gnAE_LED_LED, gnAE_LED_TEST_MIN, gnAE_LED_TEST_MAX;

	#define AE_LED_ASAT_COND		((((gnTdnChkOut==TDN_NIT)||(((MP(MpTdn)==MN_TDN_AUTO)||(MP(MpTdn)==MN_TDN_DAY))&&(model_Led==3))||((MP(MpTdn)==MN_TDN_EXTERN) && gbTdnExtflag))&&(MP(MpAdaptive)!=0))&&(!bWdrOn)&&MP(MpLedSatCtrl))
	#define AE_LED_MAX_SHIFT_BIT 	6
	#define AE_LED_MIN_SHIFT_BIT 	4
	
#else
	#define AE_LED_ASAT_COND		((((gnTdnChkOut==TDN_NIT)||((MP(MpTdn)==MN_TDN_EXTERN) && gbTdnExtflag))&&(MP(MpTdn) != MN_TDN_AUTO)&&(MP(MpAdaptive)!=0))&&(!bWdrOn)&&MP(MpLedSatCtrl))
	#define AE_LED_MAX_SHIFT_BIT 	7
	#define AE_LED_MIN_SHIFT_BIT 	5
#endif


#if(model_Led==1)
    #if (AE_LED_INVERT==1)
        #define AE_LED_ON        {GpioSetLo(GPIO_LED_CTL);}      // IR-LED ON/OFF
        #define AE_LED_OFF       {GpioSetHi(GPIO_LED_CTL);}
    #else
        #define AE_LED_ON        {GpioSetHi(GPIO_LED_CTL);}      // IR-LED ON/OFF
        #define AE_LED_OFF       {GpioSetLo(GPIO_LED_CTL);}
    #endif

#elif (model_Led==2)
    #if (AE_LED_INVERT==1)
        #define AE_LED_ON        {IRIS_CLPHw(0);	  IRIS_HEPw(0);}
        #define AE_LED_OFF       {IRIS_CLPHw(1375);	  IRIS_HEPw(1375);}
    #else
        #define AE_LED_ON        {IRIS_CLPHw(1375);	  IRIS_HEPw(1375);}
        #define AE_LED_OFF       {IRIS_CLPHw(0);	  IRIS_HEPw(0);}
    #endif
#endif


//----------------------------------------------------------------------------------------

extern UINT gnAeLedWgtBit_Max;
extern UINT gnAeLedWgtBit_Min;
extern UINT gnAeLedTgt_Ofst;
extern UINT gnAeLedErrLmt_flag;
extern UINT gnAeLedDeblur_flag;
extern BYTE gbAeLedSatCtrl;

extern BYTE gbMnLensBuf;
extern BYTE gbWdrOnBuf;

//extern UINT gnAe2sum1,gnAe2sum2,gnAe2Win2Pxcnt,gnAe2ClipLvl;		//saturation control

