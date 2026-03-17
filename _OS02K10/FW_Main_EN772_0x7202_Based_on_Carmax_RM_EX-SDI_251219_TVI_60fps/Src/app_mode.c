/* **************************************************************************
 File Name	: 	app_mode.c
 Description	:	EN772 - Out mode function
 Designer		:	Lee, Gyu Hong
 Date		:	21. 04. 28
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"
//#include "app_mode.h"

extern void ISPM AE_FREQw(UINT val, UINT val1);

// ----------------------------------------------

UINT FPS_VDI = FPS_DEF;
UINT FPS_VDO = FPS_DEF;

BYTE gbModeWdrOn_L=0;
BYTE gbModeWdrOn_CLR=0;
BYTE gbModeWdrOn_LFM=0;
BYTE gbInModeChange=0;
UINT gnInModeVtw, gnInModeHtw;
BYTE gbInModeRes;

UINT gnOutputDelay;

BYTE gbOutModeChange=0;

BYTE gbCvbsAuto=0; 			                // 200130 PCB : CVBS Auto Detection
BYTE gbCvbsAuto_Flag=0;						// 200130 PCB : CVBS Auto Detection

BYTE gbModeFreq = 0;


WORD gwAesum_sht = 0;
BYTE gbAesum_agc = 0;
BYTE gbAwb_light = 0;						// 0x00 : D65, 0x01 : CWF, 0x02 : A, 0x03 : TL84

// ======================================================================================================================
// Sub function. CAUTION !!! sequence was fixed
// ======================================================================================================================

// 170602 HTY
#if (model_ModeLed==1)
void ModeLed (void)
{	// Mode status LED indicator

		static UINT gnModeLedFcnt;

		const UINT nModeLedFcntDiv = (gnModeLedFcnt/10);		// LED Speed	per 1/6s (60p)
		const UINT nModeLedFcntDiv2 = (gnModeLedFcnt/60);		// LED Speed	per 1s	 (60p)

		if (MODE_HDANL_ON) {		// HD-CVBS
			if ((nModeLedFcntDiv2%2)&&(nModeLedFcntDiv%2))		GpioSetLo(GPIO_MODE_LED);
			else	 											GpioSetHi(GPIO_MODE_LED);
		}
		else if (MODE_EXSDI_ON) {	// EX-SDI
			if ((nModeLedFcntDiv2%2)&&(nModeLedFcntDiv%2))		GpioSetHi(GPIO_MODE_LED);
			else	 											GpioSetLo(GPIO_MODE_LED);
		}
		else {						// HD-SDI
			if (nModeLedFcntDiv%2)		GpioSetHi(GPIO_MODE_LED);
			else 						GpioSetLo(GPIO_MODE_LED);
		}

		gnModeLedFcnt++;

}
#endif


void ISPM2 ModeScaler(void)
{	
	//Pre & Post active
	WORD wPRE_HW, wPRE_VW = 0x0;
	WORD wPOST_HW, wPOST_VW = 0x0;

	//Down Scaler config
	BYTE bDS_KX, bDS_KY = 0x0;
	BYTE bDS_INTR = 0x0;
	WORD wDS_VRS = 0xfff;

	//Up Scaler config
	BYTE bUS_KX, bUS_KY = 0x0;
	BYTE bUS_MSEL = 0x0, bUS_VRS = 0x0;
	BYTE bUDS_VSPO = 0x0;

	bDS_INTR = 0x0;
	wDS_VRS = 0xfff;

	bUDS_VSPO = 0x0;
	
#if(model_1M)	
	// 1M - 1280 x 720
	wPRE_HW = MODE_ACT_H_1M;	wPRE_VW = MODE_ACT_V_1M;

	#if(0)
	switch(MP(MpOutFps)){
		case MN_1M_1080p_25_30:
		case MN_1M_1080p_50_60: wPOST_HW = MODE_ACT_H_2M; wPOST_VW = MODE_ACT_V_2M;		
								bUS_MSEL = 0x4;  bUS_VRS = 0x2;	bUDS_VSPO = 0x1;		break;
								
		case MN_1M_1440p_25_30:	wPOST_HW = MODE_ACT_H_4M; wPOST_VW = MODE_ACT_V_4M;		
								bUS_MSEL = 0x3;  bUS_VRS = 0x3;	bUDS_VSPO = 0x1;		break;
								
		default :				wPOST_HW = MODE_ACT_H_2M; wPOST_VW = MODE_ACT_V_2M;		break;
	}
	#endif
	
#elif(model_2M)
	// 2M - 1920 x 1080
	wPRE_HW = MODE_ACT_H_2M; 	wPRE_VW = MODE_ACT_V_2M;

	switch(MP(MpOutFps)){
		case MN_2M_720p_25_30 :
		case MN_2M_720p_50_60 :	wPOST_HW = MODE_ACT_H_1M; wPOST_VW = MODE_ACT_V_1M;		
																bUDS_VSPO = 0xc;		break;
		case MN_2M_1440p_25_30:	wPOST_HW = MODE_ACT_H_4M; wPOST_VW = MODE_ACT_V_4M;		
								bUS_MSEL = 0x10; bUS_VRS = 0x3;	bUDS_VSPO = 0x4;		break;
	#if(model_Sens_US2Mto5M)
		case MN_2M_1944p_125  :
		case MN_2M_1944p_20	  :	wPOST_HW = MODE_ACT_H_5M; wPOST_VW = MODE_ACT_V_5M;		
								bUS_MSEL = 0x3;  bUS_VRS = 0x3;	bUDS_VSPO = 0x0;		break;
	#endif
		default :				wPOST_HW = MODE_ACT_H_2M; wPOST_VW = MODE_ACT_V_2M;		break;
	}
	
#elif(model_5M)
	// 4M - 2560 x 1440, 5M - 2592 x 1944
	wPRE_HW = (MODE_5M_ON)?(MODE_ACT_H_5M):(MODE_ACT_H_4M); 	wPRE_VW = (MODE_5M_ON)?(MODE_ACT_V_5M):(MODE_ACT_V_4M);

	switch(MP(MpOutFps)){
		case MN_4M_720p_25_30 :	wPOST_HW = MODE_ACT_H_1M; wPOST_VW = MODE_ACT_V_1M;		
																bUDS_VSPO = 0x8;		break;
		case MN_4M_1080p_25_30:	wPOST_HW = MODE_ACT_H_2M; wPOST_VW = MODE_ACT_V_2M;
												wDS_VRS = 0x3;  bUDS_VSPO = 0xd;		break;
		default :				wPOST_HW = MODE_ACT_H_4M; wPOST_VW = MODE_ACT_V_4M;		break;
	}	
#endif

#if(0)
	if(MODE_CVBS_ON){
		bDS_INTR = 0x1;
		wDS_VRS = (MP(MpSysFreq)==MN_SYSFREQ_60) ? (0xe):(0x8);
		
		wPOST_HW = (MP(MpSysFreq)==MN_SYSFREQ_60) ? (wPRE_HW):(720);
		wPOST_VW = (MP(MpSysFreq)==MN_SYSFREQ_60) ? (525):(625);
	}
#endif

	//Downscale Mode
	if(MODE_DS_ON){
		DS_ONw(0x1);
		US_HONw(0x0);	US_VONw(0x0);
		
		DS_INTRw(bDS_INTR);
		DS_VRSw(wDS_VRS);
		UDS_VSPOw(bUDS_VSPO);					//Common US,DS

		bDS_KX = (wPRE_HW * 64) / wPOST_HW;
		bDS_KY = (wPRE_VW * 64) / wPOST_VW;
		
		DKXw(bDS_KX);
		DKYw(bDS_KY);
	}

	//Upscale Mode
	else if(MODE_US_ON){	
		DS_ONw(0x0);
		US_HONw(0x1);	US_VONw(0x1);

		US_MSELw(bUS_MSEL);
		US_VRSw(bUS_VRS);
		UDS_VSPOw(bUDS_VSPO);					//Common US,DS

		bUS_KX = (wPRE_HW * 128) / wPOST_HW;
		bUS_KY = (wPRE_VW * 128) / wPOST_VW;
		
		UXKw(bUS_KX);
		UYKw(bUS_KY);
	}

	//1:1
	else{
		DS_ONw(0x0);
		DS_INTRw(0x0);
		US_HONw(0x0);	US_VONw(0x0);

		bUDS_VSPO = 0;
		UDS_VSPOw(bUDS_VSPO);					//Common US,DS
	}
}

// ======================================================================================================================
// Main function. CAUTION !!! sequence was fixed
// ======================================================================================================================

void ISPM2 InMode(void)
{	// Main input mode config
	// CAUTION !! Fixed sequence (Don't modify).

	static BYTE gbMpBackLightBuf=0xee, gbMnWdrModeBuf=0xee;
	static BYTE gbMnOutFpsBuf=0xee, gbMnSysFreqBufAe=0xee;
	static BYTE gbModeHdAnaBuf=0xee, gbModeAnaBuf=0xee, gbModeHdAnlOnBuf=0xee;	// 170123 LH
	
	UINT nInModeHw = 0, nInModeVw = 0;
	UINT nInModeHtwRdes = 0, nInModeVtwRdes = 0;

	// 190312 LH
	static BYTE gbMpShutterBuf=0xee;
	
	const BYTE bWdrChangeOn = ((MP(MpShutter)==MN_SHUT_AUTO)&&(MP(MpBackLight)!=gbMpBackLightBuf)&&((MP(MpBackLight)==MN_BL_WDR)||(gbMpBackLightBuf==MN_BL_WDR))) 	// WDR function change
							||(((gbModeWdrOn_L)||(gbModeWdrOn_LFM))&&(MP(MpWdrMode)!=gbMnWdrModeBuf))																	// WDR mode change
							||((MP(MpBackLight)==MN_BL_WDR)&&(MP(MpShutter)!=gbMpShutterBuf)&&((MP(MpShutter)==MN_SHUT_AUTO)||(gbMpShutterBuf==MN_SHUT_AUTO)));		// WDR shutter change


	if ((bWdrChangeOn) || (MP(MpOutFps)!=gbMnOutFpsBuf)||(MP(MpSysFreq)!=gbMnSysFreqBufAe)||(MP(MpAnlMode)!=gbModeHdAnaBuf)||(MP(MpAnlForm)!=gbModeAnaBuf)) {

		gbInModeChange = 1;
		
//		TxStr("InMode Change !", 0, 0);

	#if(model_IspO_ANL)
		if(MP(MpAnlMode)!=gbModeHdAnaBuf)		ModeCvbsMnConfig();	
	#endif
		
		// WDR ON/OFF status ----------------------------------------------
		if ((MP(MpBackLight)==MN_BL_WDR)&&(MP(MpShutter)==MN_SHUT_AUTO)) {		// WDR ON condition

			if(MODE_DISABLE_WDR){
				gbModeWdrOn_L = MN_OFF;
				gbModeWdrOn_LFM = MN_OFF;
				MP(MpBackLight) = MN_OFF;
			}
			else if ((model_Sens_LWdr)&&(MP(MpWdrMode)==MN_WDR_SENSF)) {		// Line WDR condition	//180228 LGH
				gbModeWdrOn_L = MN_ON;
				gbModeWdrOn_LFM = MN_OFF;
				gbModeWdrOn_CLR = MN_OFF;
			}
			else if((model_Sens_CLR_HDR)&&(MP(MpWdrMode)==MN_WDR_SENS_CLR)){
				gbModeWdrOn_L = MN_OFF;
				#if(model_Sens==SENS_OS02K10)
				gbModeWdrOn_CLR = MN_ON;
				#else
				gbModeWdrOn_CLR = MN_OFF;
				#endif
			}
			else {																// LFM WDR condition
				gbModeWdrOn_L = MN_OFF;
				gbModeWdrOn_LFM = MN_ON;
				gbModeWdrOn_CLR = MN_OFF;
			}
		}
		
		else {																	// WDR OFF
				gbModeWdrOn_L = MN_OFF;
				gbModeWdrOn_LFM = MN_OFF;
				gbModeWdrOn_CLR = MN_OFF;
		}

		// Init sensor and Pre block -------------------------------------
		UINT i;

		#if (model_Sens_LWdr)
			if (gbModeWdrOn_L)				{for(i=0; i<gnTblIspPreEaLWdr; i++)			{SetIsp(gnTblIspPreLWdr[i][0], gnTblIspPreLWdr[i][1]);}}
			#if(model_Sens_CLR_HDR)
			else if(gbModeWdrOn_CLR)		{for(i=0; i<gnTblIspPreEaClrWdr; i++)		{SetIsp(gnTblIspPreClrWdr[i][0], gnTblIspPreClrWdr[i][1]);}}
			#endif
			else 					   	   	{for(i=0; i<gnTblIspPreEa; i++) 	  		{SetIsp(gnTblIspPre[i][0], gnTblIspPre[i][1]);}}
		#else
										 		{for(i=0; i<gnTblIspPreEa; i++) 			{SetIsp(gnTblIspPre[i][0], gnTblIspPre[i][1]);}}
		#endif 

		#if(model_Sens == SENS_OS02K10)
		LWDR_POw(gbModeWdrOn_L);
		#else
		LWDR_POw(gbModeWdrOn_L||gbModeWdrOn_CLR);
		#endif

		FPCK_SELw(0x0);	
		FPCK_DIVw(((MODE_PRE_HIGH || MODE_CVBS_FULL) ? (0x1):(0x3)));

		// Frequency & FPS total of Pre block ----------------------------
		gbModeFreq = MP(MpSysFreq);

	#if(model_1M)

		switch(MP(MpOutFps)){
			case MN_1M_720p_25_30	:
			#if(model_Sens_LWdr)
				gnInModeHtw 	= (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_SS_HTW_1M_30_LWDR, MODE_SS_HTW_1M_25_LWDR))		: (MODE_SYSFREQ(MODE_SS_HTW_1M_30, MODE_SS_HTW_1M_25));
				gnInModeVtw 	= (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_SS_VTW_1M_30_LWDR, MODE_SS_VTW_1M_25_LWDR))		: (MODE_SYSFREQ(MODE_SS_VTW_1M_30, MODE_SS_VTW_1M_25));
				nInModeHtwRdes  = (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_RDES_HTW_1M_30_LWDR, MODE_RDES_HTW_1M_25_LWDR)) 	: (MODE_SYSFREQ(MODE_RDES_HTW_1M_30, MODE_RDES_HTW_1M_25));
				nInModeVtwRdes  = (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_RDES_VTW_1M_30_LWDR, MODE_RDES_VTW_1M_25_LWDR)) 	: (MODE_SYSFREQ(MODE_RDES_VTW_1M_30, MODE_RDES_VTW_1M_25));
			#else
				gnInModeHtw 	= MODE_SYSFREQ(MODE_SS_HTW_1M_30, MODE_SS_HTW_1M_25);
				gnInModeVtw 	= MODE_SYSFREQ(MODE_SS_VTW_1M_30, MODE_SS_VTW_1M_25);
				nInModeHtwRdes  = MODE_SYSFREQ(MODE_RDES_HTW_1M_30, MODE_RDES_HTW_1M_25);
				nInModeVtwRdes  = MODE_SYSFREQ(MODE_RDES_VTW_1M_30, MODE_RDES_VTW_1M_25);
			#endif
				gbInModeRes		= MD_1M_FPS_25_30;
				break;

			case MN_1M_720p_50_60	:
			#if(model_Sens_LWdr)
				gnInModeHtw 	= (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_SS_HTW_1M_60_LWDR, MODE_SS_HTW_1M_50_LWDR))		: (MODE_SYSFREQ(MODE_SS_HTW_1M_60, MODE_SS_HTW_1M_50));
				gnInModeVtw 	= (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_SS_VTW_1M_60_LWDR, MODE_SS_VTW_1M_50_LWDR))		: (MODE_SYSFREQ(MODE_SS_VTW_1M_60, MODE_SS_VTW_1M_50));
				nInModeHtwRdes  = (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_RDES_HTW_1M_60_LWDR, MODE_RDES_HTW_1M_50_LWDR)) 	: (MODE_SYSFREQ(MODE_RDES_HTW_1M_60, MODE_RDES_HTW_1M_50));
				nInModeVtwRdes  = (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_RDES_VTW_1M_60_LWDR, MODE_RDES_VTW_1M_50_LWDR)) 	: (MODE_SYSFREQ(MODE_RDES_VTW_1M_60, MODE_RDES_VTW_1M_50));
			#else
				gnInModeHtw 	= MODE_SYSFREQ(MODE_SS_HTW_1M_60, MODE_SS_HTW_1M_50);
				gnInModeVtw 	= MODE_SYSFREQ(MODE_SS_VTW_1M_60, MODE_SS_VTW_1M_50);
				nInModeHtwRdes  = MODE_SYSFREQ(MODE_RDES_HTW_1M_60, MODE_RDES_HTW_1M_50);
				nInModeVtwRdes  = MODE_SYSFREQ(MODE_RDES_VTW_1M_60, MODE_RDES_VTW_1M_50);
			#endif
				gbInModeRes		= MD_1M_FPS_50_60;
				break;
				
			default :
				break;
		}
			nInModeHw		= MODE_ACT_H_1M;
			nInModeVw		= MODE_ACT_V_1M;

	#elif(model_2M)

		switch(MP(MpOutFps)){
			case MN_2M_720p_25_30	:
			case MN_2M_1080p_25_30	:
			case MN_2M_1440p_25_30	:
			#if(model_Sens_LWdr)
				gnInModeHtw 	= (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_SS_HTW_2M_30_LWDR, MODE_SS_HTW_2M_25_LWDR))		: (MODE_SYSFREQ(MODE_SS_HTW_2M_30, MODE_SS_HTW_2M_25));
				gnInModeVtw 	= (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_SS_VTW_2M_30_LWDR, MODE_SS_VTW_2M_25_LWDR))		: (MODE_SYSFREQ(MODE_SS_VTW_2M_30, MODE_SS_VTW_2M_25));
				nInModeHtwRdes  = (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_RDES_HTW_2M_30_LWDR, MODE_RDES_HTW_2M_25_LWDR)) 	: (MODE_SYSFREQ(MODE_RDES_HTW_2M_30, MODE_RDES_HTW_2M_25));
				nInModeVtwRdes  = (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_RDES_VTW_2M_30_LWDR, MODE_RDES_VTW_2M_25_LWDR)) 	: (MODE_SYSFREQ(MODE_RDES_VTW_2M_30, MODE_RDES_VTW_2M_25));
			#else
				gnInModeHtw 	= MODE_SYSFREQ(MODE_SS_HTW_2M_30, MODE_SS_HTW_2M_25);
				gnInModeVtw 	= MODE_SYSFREQ(MODE_SS_VTW_2M_30, MODE_SS_VTW_2M_25);
				nInModeHtwRdes  = MODE_SYSFREQ(MODE_RDES_HTW_2M_30, MODE_RDES_HTW_2M_25);
				nInModeVtwRdes  = MODE_SYSFREQ(MODE_RDES_VTW_2M_30, MODE_RDES_VTW_2M_25);
			#endif
				gbInModeRes 	= MD_2M_FPS_25_30;
				break;

			case MN_2M_720p_50_60	:
			case MN_2M_1080p_50_60	:
			#if(model_Sens_LWdr)
				gnInModeHtw 	= (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_SS_HTW_2M_60_LWDR, MODE_SS_HTW_2M_50_LWDR))		: (MODE_SYSFREQ(MODE_SS_HTW_2M_60, MODE_SS_HTW_2M_50));
				gnInModeVtw 	= (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_SS_VTW_2M_60_LWDR, MODE_SS_VTW_2M_50_LWDR))		: (MODE_SYSFREQ(MODE_SS_VTW_2M_60, MODE_SS_VTW_2M_50));
				nInModeHtwRdes  = (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_RDES_HTW_2M_60_LWDR, MODE_RDES_HTW_2M_50_LWDR)) 	: (MODE_SYSFREQ(MODE_RDES_HTW_2M_60, MODE_RDES_HTW_2M_50));
				nInModeVtwRdes  = (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_RDES_VTW_2M_60_LWDR, MODE_RDES_VTW_2M_50_LWDR)) 	: (MODE_SYSFREQ(MODE_RDES_VTW_2M_60, MODE_RDES_VTW_2M_50));
			#else
				gnInModeHtw 	= MODE_SYSFREQ(MODE_SS_HTW_2M_60, MODE_SS_HTW_2M_50);
				gnInModeVtw 	= MODE_SYSFREQ(MODE_SS_VTW_2M_60, MODE_SS_VTW_2M_50);
				nInModeHtwRdes  = MODE_SYSFREQ(MODE_RDES_HTW_2M_60, MODE_RDES_HTW_2M_50);
				nInModeVtwRdes  = MODE_SYSFREQ(MODE_RDES_VTW_2M_60, MODE_RDES_VTW_2M_50);
			#endif
				gbInModeRes		= MD_2M_FPS_50_60;
				break;

			// case MN_2M_1080p_291	:
			// 	gnInModeHtw 	= (gbModeWdrOn_L) ? (MODE_SS_HTW_2M_291_LWDR) : (MODE_SS_HTW_2M_291);
			// 	gnInModeVtw 	= (gbModeWdrOn_L) ? (MODE_SS_VTW_2M_291_LWDR) : (MODE_SS_VTW_2M_291);
			// 	nInModeHtwRdes  = (gbModeWdrOn_L) ? (MODE_RDES_HTW_2M_291_LWDR) : (MODE_RDES_HTW_2M_291);
			// 	nInModeVtwRdes  = (gbModeWdrOn_L) ? (MODE_RDES_VTW_2M_291_LWDR) : (MODE_RDES_VTW_2M_291);
			// 	nInModeHw		= MODE_ACT_H_2M;
			// 	nInModeVw		= MODE_ACT_V_2M;
			// 	gbInModeRes		= MD_2M_FPS_291;
			// 	break;

			// case MN_2M_1080p_275	:
			// 	gnInModeHtw 	= (gbModeWdrOn_L) ? (MODE_SS_HTW_2M_275_LWDR) : (MODE_SS_HTW_2M_275);
			// 	gnInModeVtw 	= (gbModeWdrOn_L) ? (MODE_SS_VTW_2M_275_LWDR) : (MODE_SS_VTW_2M_275);
			// 	nInModeHtwRdes  = (gbModeWdrOn_L) ? (MODE_RDES_HTW_2M_275_LWDR) : (MODE_RDES_HTW_2M_275);
			// 	nInModeVtwRdes  = (gbModeWdrOn_L) ? (MODE_RDES_VTW_2M_275_LWDR) : (MODE_RDES_VTW_2M_275); 
			// 	nInModeHw		= MODE_ACT_H_2M;
			// 	nInModeVw		= MODE_ACT_V_2M;
			// 	gbInModeRes		= MD_2M_FPS_275;
			// 	break;
			#if(model_Sens_US2Mto5M)
			case MN_2M_1944p_125	:
			#if(model_Sens_LWdr)
				gnInModeHtw 	= (gbModeWdrOn_L) ? (MODE_SS_HTW_2Mto5M_125_LWDR)	: (MODE_SS_HTW_2Mto5M_125)	;
				gnInModeVtw 	= (gbModeWdrOn_L) ? (MODE_SS_VTW_2Mto5M_125_LWDR)	: (MODE_SS_VTW_2Mto5M_125)	;
				nInModeHtwRdes  = (gbModeWdrOn_L) ? (MODE_RDES_HTW_2Mto5M_125_LWDR) : (MODE_RDES_HTW_2Mto5M_125);
				nInModeVtwRdes  = (gbModeWdrOn_L) ? (MODE_RDES_VTW_2Mto5M_125_LWDR) : (MODE_RDES_VTW_2Mto5M_125);
			#else
				gnInModeHtw 	= (MODE_SS_HTW_2Mto5M_125)	;
				gnInModeVtw 	= (MODE_SS_VTW_2Mto5M_125)	;
				nInModeHtwRdes  = (MODE_RDES_HTW_2Mto5M_125);
				nInModeVtwRdes  = (MODE_RDES_VTW_2Mto5M_125);
			#endif
				gbInModeRes		= MD_2M_FPS_125_20;
				break;

			case MN_2M_1944p_20	:
			#if(model_Sens_LWdr)
				gnInModeHtw 	= (gbModeWdrOn_L) ? (MODE_SS_HTW_2Mto5M_20_LWDR)	: (MODE_SS_HTW_2Mto5M_20)  ;
				gnInModeVtw 	= (gbModeWdrOn_L) ? (MODE_SS_VTW_2Mto5M_20_LWDR)	: (MODE_SS_VTW_2Mto5M_20)  ;
				nInModeHtwRdes  = (gbModeWdrOn_L) ? (MODE_RDES_HTW_2Mto5M_20_LWDR)  : (MODE_RDES_HTW_2Mto5M_20);
				nInModeVtwRdes  = (gbModeWdrOn_L) ? (MODE_RDES_VTW_2Mto5M_20_LWDR)  : (MODE_RDES_VTW_2Mto5M_20);
			#else
				gnInModeHtw 	= (MODE_SS_HTW_2Mto5M_20)  ;
				gnInModeVtw 	= (MODE_SS_VTW_2Mto5M_20)  ;
				nInModeHtwRdes  = (MODE_RDES_HTW_2Mto5M_20);
				nInModeVtwRdes  = (MODE_RDES_VTW_2Mto5M_20);
			#endif
				gbInModeRes		= MD_2M_FPS_125_20;
				break;

			#endif

			default :
				break;
		}
			nInModeHw		= MODE_ACT_H_2M;
			nInModeVw		= MODE_ACT_V_2M;

	#elif(model_5M)

		switch(MP(MpOutFps)){
			case MN_4M_720p_25_30	:
			case MN_4M_1080p_25_30	:
			case MN_4M_1440p_25_30	:
			#if(model_Sens_LWdr)
				gnInModeHtw 	= (gbModeWdrOn_L) ?	(MODE_SYSFREQ(MODE_SS_HTW_4M_30_LWDR, MODE_SS_HTW_4M_25_LWDR))		: (MODE_SYSFREQ(MODE_SS_HTW_4M_30, MODE_SS_HTW_4M_25));
				gnInModeVtw 	= (gbModeWdrOn_L) ?	(MODE_SYSFREQ(MODE_SS_VTW_4M_30_LWDR, MODE_SS_VTW_4M_25_LWDR))		: (MODE_SYSFREQ(MODE_SS_VTW_4M_30, MODE_SS_VTW_4M_25));
				nInModeHtwRdes  = (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_RDES_HTW_4M_30_LWDR, MODE_RDES_HTW_4M_25_LWDR)) 	: (MODE_SYSFREQ(MODE_RDES_HTW_4M_30, MODE_RDES_HTW_4M_25));
				nInModeVtwRdes  = (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_RDES_VTW_4M_30_LWDR, MODE_RDES_VTW_4M_25_LWDR)) 	: (MODE_SYSFREQ(MODE_RDES_VTW_4M_30, MODE_RDES_VTW_4M_25));
			#else
				gnInModeHtw 	= MODE_SYSFREQ(MODE_SS_HTW_4M_30, MODE_SS_HTW_4M_25);
				gnInModeVtw 	= MODE_SYSFREQ(MODE_SS_VTW_4M_30, MODE_SS_VTW_4M_25);
				nInModeHtwRdes  = MODE_SYSFREQ(MODE_RDES_HTW_4M_30, MODE_RDES_HTW_4M_25);
				nInModeVtwRdes  = MODE_SYSFREQ(MODE_RDES_VTW_4M_30, MODE_RDES_VTW_4M_25);
			#endif
				nInModeHw		= MODE_ACT_H_4M;
				nInModeVw		= MODE_ACT_V_4M;
				gbInModeRes		= MD_4M_FPS_25_30;
				break;

			case MN_5M_1944p_125	:
			#if(model_Sens_LWdr)
				gnInModeHtw 	= (gbModeWdrOn_L) ? (MODE_SS_HTW_5M_125_LWDR) 	: (MODE_SS_HTW_5M_125);
				gnInModeVtw 	= (gbModeWdrOn_L) ? (MODE_SS_VTW_5M_125_LWDR) 	: (MODE_SS_VTW_5M_125);
				nInModeHtwRdes  = (gbModeWdrOn_L) ? (MODE_RDES_HTW_5M_125_LWDR) : (MODE_RDES_HTW_5M_125);
				nInModeVtwRdes  = (gbModeWdrOn_L) ? (MODE_RDES_VTW_5M_125_LWDR)	: (MODE_RDES_VTW_5M_125);
			#else
				gnInModeHtw 	= MODE_SS_HTW_5M_125;
				gnInModeVtw 	= MODE_SS_VTW_5M_125;
				nInModeHtwRdes  = MODE_RDES_HTW_5M_125;
				nInModeVtwRdes  = MODE_RDES_VTW_5M_125;
			#endif
				nInModeHw		= MODE_ACT_H_5M;
				nInModeVw		= MODE_ACT_V_5M;
				gbInModeRes		= MD_5M_FPS_125;
				break;

			case MN_5M_1944p_20		:
			#if(model_Sens_LWdr)
				gnInModeHtw 	= (gbModeWdrOn_L) ? (MODE_SS_HTW_5M_20_LWDR)	: (MODE_SS_HTW_5M_20);
				gnInModeVtw 	= (gbModeWdrOn_L) ? (MODE_SS_VTW_5M_20_LWDR)	: (MODE_SS_VTW_5M_20);
				nInModeHtwRdes  = (gbModeWdrOn_L) ? (MODE_RDES_HTW_5M_20_LWDR)  : (MODE_RDES_HTW_5M_20);
				nInModeVtwRdes  = (gbModeWdrOn_L) ? (MODE_RDES_VTW_5M_20_LWDR)  : (MODE_RDES_VTW_5M_20);
			#else
				gnInModeHtw 	= MODE_SS_HTW_5M_20;
				gnInModeVtw 	= MODE_SS_VTW_5M_20;
				nInModeHtwRdes  = MODE_RDES_HTW_5M_20;
				nInModeVtwRdes  = MODE_RDES_VTW_5M_20;
			#endif
				nInModeHw		= MODE_ACT_H_5M;
				nInModeVw		= MODE_ACT_V_5M;
				gbInModeRes		= MD_5M_FPS_20;
				break;
				
			default :
				break;
		}
		
	#else
	#endif

	#if(model_IspO_ANL)
		#if(model_Sens_CVBS)
		// CVBS Mode
		if(MP(MpAnlMode)==MN_CVBS_ON){
			#if(model_Sens_LWdr)
				gnInModeHtw 	= (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_SS_HTW_CVBS_NTSC_LWDR, MODE_SS_HTW_CVBS_PAL_LWDR))		: (MODE_SYSFREQ(MODE_SS_HTW_CVBS_NTSC, MODE_SS_HTW_CVBS_PAL));
				gnInModeVtw 	= (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_SS_VTW_CVBS_NTSC_LWDR, MODE_SS_VTW_CVBS_PAL_LWDR))		: (MODE_SYSFREQ(MODE_SS_VTW_CVBS_NTSC, MODE_SS_VTW_CVBS_PAL));
				nInModeHtwRdes  = (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_RDES_HTW_CVBS_NTSC_LWDR, MODE_RDES_HTW_CVBS_PAL_LWDR))  	: (MODE_SYSFREQ(MODE_RDES_HTW_CVBS_NTSC, MODE_RDES_HTW_CVBS_PAL));
				nInModeVtwRdes  = (gbModeWdrOn_L) ? (MODE_SYSFREQ(MODE_RDES_VTW_CVBS_NTSC_LWDR, MODE_RDES_VTW_CVBS_PAL_LWDR))  	: (MODE_SYSFREQ(MODE_RDES_VTW_CVBS_NTSC, MODE_RDES_VTW_CVBS_PAL));
			#else
				gnInModeHtw 	= (MODE_SYSFREQ(MODE_SS_HTW_CVBS_NTSC, MODE_SS_HTW_CVBS_PAL));    
				gnInModeVtw 	= (MODE_SYSFREQ(MODE_SS_VTW_CVBS_NTSC, MODE_SS_VTW_CVBS_PAL));
				nInModeHtwRdes  = (MODE_SYSFREQ(MODE_RDES_HTW_CVBS_NTSC, MODE_RDES_HTW_CVBS_PAL));
				nInModeVtwRdes  = (MODE_SYSFREQ(MODE_RDES_VTW_CVBS_NTSC, MODE_RDES_VTW_CVBS_PAL));
			#endif
				gbInModeRes 	= MD_CVBS;
		}
		#endif
	#endif

		 // fixed 27.5
		LibInitSens(gbInModeRes, ((gbModeWdrOn_L)|(gbModeWdrOn_CLR<<4)));
		InitRdesConfig(gbInModeRes, (gbModeWdrOn_L||gbModeWdrOn_CLR));
		
		AE_FREQw(gnInModeVtw, gnInModeHtw);

		// Saved MIPI Timing 
		LVDS_CKDLYw(UP(UpLVDS_CKDLY));	

		LDIDLY0w(UP(UpLDIDLY0));		
		LDIDLY1w(UP(UpLDIDLY1));		
		LDIDLY2w(UP(UpLDIDLY2));		
		LDIDLY3w(UP(UpLDIDLY3));	
		
		RDES_HTWw(nInModeHtwRdes-1);
		RDES_VTWw(nInModeVtwRdes-1);

		RDES_HWw(nInModeHw+28);			//HWI + add offset 24 pixel

	#if(0)
		const BYTE bPxlMgnH = (model_5M)?((nInModeHw%3)?(17):(18)):((model_Sens==SENS_OX03C10)?(16):(16));
		const BYTE bPxlMgnV = (model_5M)?(16):((model_Sens==SENS_OX03C10)?(72):(16));
	#else
		const BYTE bPxlMgnH = (LWDR_POr)?((gbAeWdrComp==0x1)?(15+(3-(nInModeHw%3))):(16+(nInModeHw%2))):(16);
		const BYTE bPxlMgnV = ((model_Sens==SENS_OX03C10)?(72):(16));
	#endif

		HWIw(nInModeHw+bPxlMgnH);		//HWI + add offset
		VWIw(nInModeVw+bPxlMgnV);		//VWI + add offset
		
		// SYNC UP -------------------------------------------------------------------------------------
		RSYNC_UPw(0x1);
		
	}

	else	gbInModeChange = 0;

	gbMpBackLightBuf 	= MP(MpBackLight);
	gbMnWdrModeBuf 		= MP(MpWdrMode);
	gbMnOutFpsBuf 		= MP(MpOutFps);
	gbMnSysFreqBufAe	= MP(MpSysFreq);
	gbMpShutterBuf      = MP(MpShutter);

	gbModeAnaBuf		= MP(MpAnlForm);
	gbModeHdAnaBuf		= MP(MpAnlMode);
	gbModeHdAnlOnBuf	= MODE_HDANL_ON;
}

// -----------------------------------------------------------------------------------------------------------------------------

void ISPM2 OutMode(void)
{	// Main output mode config
	// CAUTION !! Fixed sequence (Don't modify).

	static 	BYTE gbMnOutFpsBuf=0xee, gbMnSysFreqBuf=0xee;
	static 	BYTE gbModeSdiBuf=0xee, gbModeHdSdiBuf=0xee, gbModeHdAnaBuf=0xee, gbModeAnaBuf=0xee;
	static 	BYTE gbModeExSdiOnBuf=0xee, gbModeHdAnlOnBuf=0xee;
	static	BYTE gbModeOutputFuncBuf = 0xee;

	UINT nOutModeHtw = 0x0, nOutModeVtw = 0x0;
	UINT nOutModeHwo = 0x0, nOutModeVwo = 0x0;
	UINT i;

	if ((MP(MpOutFps)!=gbMnOutFpsBuf)||(MP(MpSysFreq)!=gbMnSysFreqBuf)||(MP(MpSdiMode)!=gbModeHdSdiBuf)||(MP(MpSdiForm)!=gbModeSdiBuf)||(MP(MpAnlMode)!=gbModeHdAnaBuf)||(MP(MpAnlForm)!=gbModeAnaBuf)||
		(gbModeExSdiOnBuf!=MODE_EXSDI_ON)||(gbModeHdAnlOnBuf!=MODE_HDANL_ON)||(gbModeOutputFuncBuf != ((MODE_OUTPUT_SET_FUNC)&&(gbModeWdrOn_L)))) {												// checking mode change

		gbOutModeChange = 1;

//		TxStr("OutMode Change !", 0, 0);

		const BYTE bSetModeIndex = (((MP(MpOutFps)==MN_2M_1080p_291)||(MP(MpOutFps)==MN_2M_1080p_275))?(MN_4M_1440p_25_30):(MP(MpOutFps)));

		// Digital config ---------------------------------------------------------------------------
//		for (i=0; i<gnTblIspModeEa; i++) 		{SetIsp(gnTblIspMode[i][0], gnTblIspMode[i][1+(MP(MpOutFps))]);}			// Digital
		for (i=0; i<gnTblIspModeEa; i++)		{SetIsp(gnTblIspMode[i][0], gnTblIspMode[i][1+bSetModeIndex]);} 		// Digital

		
	#if(model_1M)

		switch(MP(MpOutFps)){
			case MN_1M_720p_25_30	:
				nOutModeHtw		= (MODE_SYSFREQ(MODE_OUT_HTW_1M_60HZ, MODE_OUT_HTW_1M_50HZ)<<1);
				nOutModeVtw		= MODE_OUT_VTW_1M;
				nOutModeHwo		= MODE_ACT_H_1M;
				nOutModeVwo		= MODE_ACT_V_1M;
				break;

			case MN_1M_720p_50_60	:
				nOutModeHtw		= MODE_SYSFREQ(MODE_OUT_HTW_1M_60HZ, MODE_OUT_HTW_1M_50HZ);
				nOutModeVtw		= MODE_OUT_VTW_1M;
				nOutModeHwo		= MODE_ACT_H_1M;
				nOutModeVwo		= MODE_ACT_V_1M;
				break;
				
			default :
				break;
		}

	#elif(model_2M)

		switch(MP(MpOutFps)){
			case MN_2M_720p_25_30	:	//Downscale 1M
				nOutModeHtw		= (MODE_SYSFREQ(MODE_OUT_HTW_1M_60HZ, MODE_OUT_HTW_1M_50HZ)<<1);
				nOutModeVtw		= MODE_OUT_VTW_1M;
				nOutModeHwo		= MODE_ACT_H_1M;
				nOutModeVwo		= MODE_ACT_V_1M;
				break;

			case MN_2M_720p_50_60	:	//Downscale 1M
				nOutModeHtw		= MODE_SYSFREQ(MODE_OUT_HTW_1M_60HZ, MODE_OUT_HTW_1M_50HZ);
				nOutModeVtw		= MODE_OUT_VTW_1M;
				nOutModeHwo		= MODE_ACT_H_1M;
				nOutModeVwo		= MODE_ACT_V_1M;
				break;
				
			case MN_2M_1080p_25_30	:	// 2M
			case MN_2M_1080p_50_60	:
				nOutModeHtw		= MODE_SYSFREQ(MODE_OUT_HTW_2M_60HZ, MODE_OUT_HTW_2M_50HZ);
				nOutModeVtw		= MODE_OUT_VTW_2M;
				nOutModeHwo		= MODE_ACT_H_2M;
				nOutModeVwo		= MODE_ACT_V_2M;
				break;

			case MN_2M_1440p_25_30	:
				nOutModeHtw		= MODE_SYSFREQ(MODE_OUT_HTW_4M_60HZ, MODE_OUT_HTW_4M_50HZ);
				nOutModeVtw		= MODE_OUT_VTW_4M;
				nOutModeHwo		= MODE_ACT_H_4M;
				nOutModeVwo		= MODE_ACT_V_4M;
				break;

			case MN_2M_1080p_291	:
//				nOutModeHtw		= MODE_OUT_HTW_2M_291_60HZ;
			case MN_2M_1080p_275	:	
				nOutModeHtw		= MODE_OUT_HTW_2M_275_60HZ;
				nOutModeVtw		= MODE_OUT_VTW_2M;
				nOutModeHwo		= MODE_ACT_H_2M;
				nOutModeVwo		= MODE_ACT_V_2M;
				break;
		#if(model_Sens_US2Mto5M)
			case MN_2M_1944p_125	:	// 2M to 5M Upscale
				nOutModeHtw		= MODE_SYSFREQ(MODE_OUT_HTW_5M_12_5HZ, MODE_OUT_HTW_5M_12_5HZ);
				nOutModeVtw		= MODE_OUT_VTW_5M_12_5HZ;
				nOutModeHwo		= MODE_ACT_H_5M;
				nOutModeVwo		= MODE_ACT_V_5M;
				break;

			case MN_2M_1944p_20		:	// 2M to 5M Upscale
				nOutModeHtw		= MODE_SYSFREQ(MODE_OUT_HTW_5M_20HZ, MODE_OUT_HTW_5M_20HZ);
				nOutModeVtw		= MODE_OUT_VTW_5M_20HZ;
				nOutModeHwo		= MODE_ACT_H_5M;
				nOutModeVwo		= MODE_ACT_V_5M;
				break;
		#endif
			default :
				break;
		}

	#elif(model_5M)

		switch(MP(MpOutFps)){

			case MN_4M_720p_25_30	:	//Downscale 1M
				nOutModeHtw		= (MODE_SYSFREQ(MODE_OUT_HTW_1M_60HZ, MODE_OUT_HTW_1M_50HZ)<<1);
				nOutModeVtw		= MODE_OUT_VTW_1M;
				nOutModeHwo		= MODE_ACT_H_1M;
				nOutModeVwo		= MODE_ACT_V_1M;
				break;
				
			case MN_4M_1080p_25_30	:	//Downscale 2M
				nOutModeHtw		= MODE_SYSFREQ(MODE_OUT_HTW_2M_60HZ, MODE_OUT_HTW_2M_50HZ);
				nOutModeVtw		= MODE_OUT_VTW_2M;
				nOutModeHwo		= MODE_ACT_H_2M;
				nOutModeVwo		= MODE_ACT_V_2M;
				break;

			case MN_4M_1440p_25_30	:	// 4M
				nOutModeHtw		= MODE_SYSFREQ(MODE_OUT_HTW_4M_60HZ, MODE_OUT_HTW_4M_50HZ);
				nOutModeVtw		= MODE_OUT_VTW_4M;
				nOutModeHwo		= MODE_ACT_H_4M;
				nOutModeVwo		= MODE_ACT_V_4M;
				break;

			case MN_5M_1944p_125	:	// 5M
				nOutModeHtw		= MODE_SYSFREQ(MODE_OUT_HTW_5M_12_5HZ, MODE_OUT_HTW_5M_12_5HZ);
				nOutModeVtw		= MODE_OUT_VTW_5M_12_5HZ;
				nOutModeHwo		= MODE_ACT_H_5M;
				nOutModeVwo		= MODE_ACT_V_5M;
				break;

			case MN_5M_1944p_20		:	// 5M
				nOutModeHtw		= MODE_SYSFREQ(MODE_OUT_HTW_5M_20HZ, MODE_OUT_HTW_5M_20HZ);
				nOutModeVtw		= MODE_OUT_VTW_5M_20HZ;
				nOutModeHwo		= MODE_ACT_H_5M;
				nOutModeVwo		= MODE_ACT_V_5M;
				break;

			default	:
				break;
		}
		
	#endif

		HTWOw(nOutModeHtw-2);
		VTWOw(nOutModeVtw-1);

		HWOw(nOutModeHwo+16);			//HWO + add offset 16 pixel
		VWOw(nOutModeVwo+16);			//VWO + add offset 16 pixel

	#if(model_Sens==SENS_OX03C10)
		OSYNC_AUTOw(0x0);
		OSYNC_MODw(0x1);
	#else
		OSYNC_AUTOw(0x1);
	#endif
	
		// Up & Down Scale Mode
		ModeScaler();
		
		// SDI mode change ------------------------------------------------------------------------------
		UINT nSdiMode = (MP(MpSdiMode)==MN_EXSDI) ? (((MODE_EXSDI_3G_BASE)?(2):(MODE_EXSDI_1P5G_BASE))):((MODE_SDI_3G_BASE) ? (1) : (0));

		LibModeSdi(MODE_SDI_STATUS, nSdiMode);
		
		//Ancillary Data (EX-SDI Only)
//		ModeSdiAnc();

	#if(model_IspO_ANL)
		// Analog mode change ---------------------------------------------------------------------------
		ModeAnalog(MODE_ANL_STATUS);

		//*******************************************************
		// ANALOG_MODE SET (FPS Change)
		//*******************************************************
		// switch(MP(MpOutFps))
		// {
		// 	case MN_2M_1080p_25_30:
		// 	case MN_2M_1080p_291:
		// 		SetIsp(0x607, 0x112f0464); // HTWE[31:16],VTWE[11:0]
		// 		SetIsp(0x608, 0x00040005); // HSPE[31:16],VSPE[11:0]
		// 		SetIsp(0x635, 0x08970647); // ICNT_CLIP[28:16],HLOCK_CAT[12:0]
				
		// 		SetIsp(0x64a, 0x008000d1); // ACT_BURST_HW[29:16],ACT_BURST_HSP[13:0]
		// 		SetIsp(0x64b, 0x108601e1); // ACT_ACT_HW[29:16],ACT_ACT_HSP[13:0]			
		// 		SetIsp(0x64c, 0x0f070206); // LBURST_HW[29:16],LBURST_HSP[13:0]
		// 		SetIsp(0x683, 0x02200220); // LBURST_Y0[25:16],LBURST_Y1[9:0]0]
		// 		SetIsp(0x636, 0x08ab0001); // VLOCK_CAT_EV[28:16],VLOCK_CAT_OD[12:0]

		// 		SetIsp(0x662, 0x08700870); // INT_VSP_E[28:16],INT_VSP_O[12:0]
		// 		SetIsp(0x663, 0x08800880); // INT_BITCNT_EN[31],INT_VEP_E[28:16],INT_VEP_O[12:0]
		// 	break;

		// 	case MN_2M_1080p_275:
		// 		// Register
		// 		SetIsp(0x607, 0x12bf0464); // HTWE[31:16],VTWE[11:0]
		// 		SetIsp(0x608, 0x00040005); // HSPE[31:16],VSPE[11:0]
		// 		SetIsp(0x635, 0x095f0647); // ICNT_CLIP[28:16],HLOCK_CAT[12:0]
				
		// 		SetIsp(0x64a, 0x007f00d2); // ACT_BURST_HW[29:16],ACT_BURST_HSP[13:0]
		// 		SetIsp(0x64b, 0x0f0c0355); // ACT_ACT_HW[29:16],ACT_ACT_HSP[13:0]			
		// 		SetIsp(0x64c, 0x10920209); // LBURST_HW[29:16],LBURST_HSP[13:0]
		// 		SetIsp(0x683, 0x02500250); // LBURST_Y0[25:16],LBURST_Y1[9:0]0]
		// 		SetIsp(0x636, 0x08ab0001); // VLOCK_CAT_EV[28:16],VLOCK_CAT_OD[12:0]

		// 		SetIsp(0x662, 0x08700870); // INT_VSP_E[28:16],INT_VSP_O[12:0]
		// 		SetIsp(0x663, 0x08800880); // INT_BITCNT_EN[31],INT_VEP_E[28:16],INT_VEP_O[12:0]
		// 	break;
		// };

		

		// // 220718 MODE_T 2M (27.5, 29.1, 30)
		// // CTX Level, BIT NUM per Line, 1Bit Width
		// CTX_LVLw(0x3ff);	// CTX Level
		// CTX_LBITNUMw(0x20 + 0x8/*0x2*/); // BIT NUM Per Line = 32, Total 2 Line 64 bit + 2
		// //CTX_BITRATEw(0x34); // 1 Bit Width 350ns(033), 1Step Per (1/148.5M) = 6.73ns
		// CTX_BITRATEw(0x3f); // 1 Bit Width 430ns(040), 1Step Per (1/148.5M) = 6.73ns

		// // CTX Test Line Set
		// CTX_VPOSEVSw(0xc); // After 7 Lines based on Serration Wave
		// CTX_VPOSEVEw(0xf); // After 8 Lines based on Serration Wave
			
		// // CTX Horizontal Width Set
		// CTX_HPOSEVSw(0x1f4); // Sync to First High 2.6us
		// CTX_HPOSEVEw(0x1200);
	
	#else
		// MIPI  mode change ---------------------------------------------------------------------------
		ModeMipi(nOutModeHtw, nOutModeVtw, nOutModeHwo, nOutModeVwo);
	#endif

		gnOutputDelay = MODE_CHG_DLY;
		
		// Clock & Frame info (reserved, LGH TMP)
		FPS_VDI = ((MN_FPS_HI) ? MODE_SYSFREQ(60,50) : MODE_SYSFREQ(30,25));

		#if(model_1M)

			switch(MP(MpOutFps)){
				case MN_1M_720p_25_30		: FPS_VDO = MODE_SYSFREQ(30,25);	break;
				case MN_1M_720p_50_60		: FPS_VDO = MODE_SYSFREQ(60,50);	break;
				default :														break;
			}

		#elif(model_2M)

			switch(MP(MpOutFps)){
				case MN_2M_720p_25_30		: 
				case MN_2M_1080p_25_30		: 
				case MN_2M_1440p_25_30		: FPS_VDO = MODE_SYSFREQ(30,25);	break;
				case MN_2M_1080p_50_60		:
				case MN_2M_720p_50_60		: FPS_VDO = MODE_SYSFREQ(60,50);	break;
				case MN_2M_1080p_291		: FPS_VDO = 29;						break;
				case MN_2M_1080p_275		: FPS_VDO = 27;						break;
			#if(model_Sens_US2Mto5M)
				case MN_2M_1944p_125		: FPS_VDO = 13;						break;
				case MN_2M_1944p_20			: FPS_VDO = 20;						break;
			#endif
				default :														break;
			}

		#elif(model_5M)

			switch(MP(MpOutFps)){
				case MN_4M_720p_25_30		:
				case MN_4M_1080p_25_30		:
				case MN_4M_1440p_25_30		: FPS_VDO = MODE_SYSFREQ(30,25);	break;
				case MN_5M_1944p_125		: FPS_VDO = 13;						break;
				case MN_5M_1944p_20			: FPS_VDO = 20;						break;
				default	:														break;
			}
			
		#endif

		#if(model_IspO_ANL)
			if(MP(MpAnlForm)==MN_CVBS)		  FPS_VDO = MODE_SYSFREQ(60,50);
		#endif

		//Change font config according to resolution 
		MenuChangeRedraw();
		
		// mode Status String out -----------------------------------------------------------------------
		MODE_TXSTR
	}	// end of if (mode change condition)

	gbMnOutFpsBuf 		= MP(MpOutFps);
	gbMnSysFreqBuf 		= MP(MpSysFreq);
	gbModeSdiBuf		= MP(MpSdiForm);	//Mode change at EX-SDI
	gbModeHdSdiBuf		= MP(MpSdiMode);	//Mode change at HD-SDI
	gbModeAnaBuf		= MP(MpAnlForm);
	gbModeHdAnaBuf		= MP(MpAnlMode);

	gbModeExSdiOnBuf	= MODE_EXSDI_ON;
	gbModeHdAnlOnBuf	= MODE_HDANL_ON;
	gbModeOutputFuncBuf	= ((MODE_OUTPUT_SET_FUNC)&&(gbModeWdrOn_L));
}

// ----------------------------------------------------------------------------------------------------------------
void ISPM2 ModeChange (void)		// 180104 LH
{ // Mode change function

	// ============================================================================//
	// Fixed sequence (CAUTION !! Don't modify)                   					//

	InMode();		// call 1tyme When pre mode was changed        			//
	                                                          		
	OutMode();		// call 1tyme When post mode was changed       			//

	ModeSdiAnc();	// 

	// Sync allign, Should be located at last !!
	if ((gbInModeChange||gbOutModeChange)) {	// 170420 LH

		gbInModeChange = 0;	// pre  mode change flag reset
		gbOutModeChange= 0;	// post mode change flag reset

		WaitVdw();
		OSYNC_UPw(0x1);

		WaitVdw();
		WaitVdw();
		
		ESYNC_UPw(0x1);
		
	#if(model_Par==1)
		UsrParSetChgVal();
	#endif

	}

	// =========================================================== //
	// Analog Output Delay

#if(model_IspO_ANL)

	if(gnOutputDelay){
		
		gnOutputDelay--;
		
		if(gnOutputDelay == 0){
			if (MODE_ANL_STATUS==2)			POWER_ON_HDANA						// Power up HD Analog			
			else if (MODE_ANL_STATUS==1)	POWER_ON_CVBS				  		// Power up CVBS
			else{ 							POWER_OFF_HDANA	POWER_OFF_CVBS}		// Power down Analog
		}
	}
	
#endif
	
	// =========================================================== //
	// Analog burst-off option at BW mode ------------------------------------------
	if (gnTdnChkOut==TDN_NIT) 		AY_OSELw(2);	// BW
	else							AY_OSELw(0);	// Color
	
	// =========================================================== //
	// Encoder user parameter value monitoring 
	#if(model_Par==1)
		#if(model_IspO_ANL)
			SetENCLv0_RegW();
			if(MODE_CVBS_ON)	SetENC_CVBS_RegW();
		#endif
	#endif	
	
	#if(0)
		// condition for CVBS auto detection ------------------------------------------
		// 200130 PCB : CVBS Auto Detection
		#if (model_CvbsAdc==1)
			#define CVBS_AUTO_DET_LVL	0x500
			
            if(model_Aout!=4){
               if((ADC_CVBSr < CVBS_AUTO_DET_LVL)&&(!gbCvbsAuto_Flag))        {gbCvbsAuto=gbCvbsAuto_Flag=1; MP(MpAnlMode)=MN_CVBS_ON;}
               else if((ADC_CVBSr >= CVBS_AUTO_DET_LVL)&&(gbCvbsAuto_Flag))   {gbCvbsAuto=gbCvbsAuto_Flag=0;                          }
            }
		#endif
	#endif
}

WORD gwDNR3D_Val = 0;

void ModeSdiAnc(void)
{
	if(MODE_EXSDI_ON){
		EXE_ANC_SELw(0x1);				// 0x0 : ANC0,  0x1 : ANC1
		DS_ANC_ON_Aw(0x1);				// 0x0 : OFF, 0x1 : ON
		
		//0x720 ~ 0x727 (10bit x 16ea Register)
	
	// FW Ver, Sensor No, IQ Par
		REG_ANC0_D00w((gwFW_Ver			>>0)&0x3FF);
		REG_ANC0_D01w((model_Sens		>>0)&0x3FF);
		REG_ANC0_D02w((UP(UpUsrParVer )	>>0)&0x3FF);
		REG_ANC0_D03w((0x0				>>0)&0x3FF);			// Reserved

	// AP 3DNR Value
	#if(0)		//AGC
		REG_ANC0_D04w((giCurAgc>>0 )&0x3FF);
		REG_ANC0_D05w((giCurAgc>>10)&0x3FF);
	#else		//AP 3DNR
		WORD wDNR3D_Val = 0;

		wDNR3D_Val = IntpValAgcPos(giCurAgc, UP(Up3DNR_AGC_PT0), UP(Up3DNR_AGC_PT1), UP(Up3DNR_AGC_PT2),\
											 UP(Up3DNR_AGC_VAL0), UP(Up3DNR_AGC_VAL1), UP(Up3DNR_AGC_VAL2));
		
		gwDNR3D_Val = wDNR3D_Val;
		
	#if(0)
		REG_ANC0_D00w((wDNR3D_Val>>0)&0xFF);
		REG_ANC0_D01w((wDNR3D_Val>>8)&0xFF);
	#else
		REG_ANC0_D04w((wDNR3D_Val>>0 )&0x3FF);
		REG_ANC0_D05w((wDNR3D_Val>>10)&0x3FF);
	#endif
		GRP6 = wDNR3D_Val;

	#endif
		//0x728 ~ 0x72F (10bit x 16ea Register)
//		REG_ANC1_D00w(val0);
//		REG_ANC1_D01w(val1);
	}
	else	return;
}