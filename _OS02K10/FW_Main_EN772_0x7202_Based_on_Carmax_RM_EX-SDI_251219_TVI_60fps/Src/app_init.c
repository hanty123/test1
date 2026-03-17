/* **************************************************************************
 File Name	: 	app_init.c
 Description:	initialize functions
 Designer	:	Lee, Gyu Hong
 Date		:	20. 06. 04
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

extern void UsrParReset(void);
extern void InitPar(void);

//*************************************************************************************************
// Device Init Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//
void InitFontChar(const UINT anFont[][12])
{
	FONT_MUTEw(1);				// EN778

	UINT i, j;

	//TxStrNoIRQ("InitFontChar Start", 0, 0);

	for(j=0; j<ISP_FONT_CHAR_EA; j++){
		for(i=0; i<12; i++){
			SetFontChar( (j*12)+i, ((UINT)(anFont[j][i])));
			//_wr32(ISP_BASE+((ISP_BASE_FONT_CHAR +(UINT)( (j*12)+i ))<<2),  (UINT)( anFont[j][i] ));
		}
	}

	//TxStrNoIRQ("InitFontChar End", 0, 0);

	FONT_MUTEw(0);				// EN778
}

void TestPatternOn(void)
{
	TxStrDecNoIRQ("    = INSEL : ", INSELr, 1);
	TxStrDecNoIRQ("    = INSEL : ", INSELr, 1);
	TxStrDecNoIRQ("    = FPCK_SEL : ", FPCK_SELr, 1);
	RDES_HALNw(0x1); 	RDES_VALNw(0x1);	INSELw(6); // master, internal sync, test pattern
}

void InitSens(void)
{
	LibInitSens(0, 0);
	//TxStrNoIRQ("Sensor Initalize End", 0, 0);
}


void ISPM2 InitRdesConfig(int aiResMode, int aiWdrMode)		// 180221 LGH
{
	BYTE bMIPI_CLK_DLY = 0x0;
	WORD wMIPI_DAYA_DLY = 0x0;
	
	#if (model_TgtBd==0)	// Enx Socket

	switch(aiWdrMode)
	{
		#if (model_Sens==SENS_IMX225)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_1M_FPS_25_30) ? (0x9) : (0x9);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_1M_FPS_25_30) ? (0x0022) : (0x0022);		// WDR-OFF MIPI Data Delay
								break;

		#elif (model_Sens==SENS_IMX224)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_1M_FPS_25_30) ? (0x9) : (0x9);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_1M_FPS_25_30) ? (0x0022) : (0x0022);		// WDR-OFF MIPI Data Delay
								break;

			case MN_WDR_ON :	bMIPI_CLK_DLY	= (aiResMode==MD_1M_FPS_25_30) ? (0x4) : (0x4);				// WDR-ON MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_1M_FPS_25_30) ? (0x0022) : (0x2222);		// WDR-ON MIPI Data Delay
								break;
								
		#elif ((model_Sens==SENS_IMX290)||(model_Sens==SENS_IMX462))
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x9) : (0x9);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x2222) : (0x2222);		// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x9) 	  : (0x9);			// WDR-ON MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x2222) : (0x2222);		// WDR-ON MIPI Data Delay
								break;

		#elif ((model_Sens==SENS_IMX307)||(model_Sens==SENS_IMX327))
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x9) : (0x9);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0022) : (0x0022);		// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0x9);													// WDR-ON MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x0022);													// WDR-ON MIPI Data Delay
								break;
		
		#elif (model_Sens==SENS_IMX662)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x5) : (0x5);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x2222) : (0x2222);		// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0x5);													// WDR-ON MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x2222);													// WDR-ON MIPI Data Delay
								break;

		#elif ((model_Sens==SENS_GC2053)||(model_Sens==SENS_GC2093)) // 210114 HTY
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x5) : (0x5);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0033) : (0x0033);		// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0x5);													// WDR-ON MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x0033);													// WDR-ON MIPI Data Delay
								break;

		#elif (model_Sens==SENS_SC200AI) 
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0xf) : (0x0);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0033) : (0x0033);		// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0xf);													// WDR-ON MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x0033);													// WDR-ON MIPI Data Delay
								break;
								
		#elif (model_Sens==SENS_PS6210K)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x7) : (0x7);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0022) : (0x0022);		// WDR-OFF MIPI Data Delay
								break;
			
		#elif (model_Sens==SENS_OS02H10)
			case MN_WDR_OFF:	
								if(MP(MpOutFps) == MN_2M_1080p_275){
									bMIPI_CLK_DLY	= (0x8);													// WDR-OFF MIPI Clock Delay (0x2 ~ 0xd, 0x4~0xf)
									wMIPI_DAYA_DLY	= (0x0022); 												// WDR-OFF MIPI Data Delay
								}
								else{
									bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? MODE_SYSFREQ(0x3,0x3) : (0x3);	// WDR-OFF MIPI Clock Delay (0x2 ~ 0xd, 0x4~0xf)
									wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0033) : (0x0033);		// WDR-OFF MIPI Data Delay
								}
								break;
			case MN_WDR_ON :	
								if(MP(MpOutFps) == MN_2M_1080p_275){
									bMIPI_CLK_DLY	= (0x6);													// WDR-ON MIPI Clock Delay
									wMIPI_DAYA_DLY	= (0x0055); 												// WDR-ON MIPI Data Delay
								}
								else{
									bMIPI_CLK_DLY	= MODE_SYSFREQ(0x3, 0x3);									// WDR-ON MIPI Clock Delay
									wMIPI_DAYA_DLY	= (0x0033);													// WDR-ON MIPI Data Delay
								}
								break;
		
		#elif (model_Sens==SENS_OS02K10)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? MODE_SYSFREQ(0x2,0x2) : (0x2);	// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0055) : (0x0055);		// WDR-OFF MIPI Data Delay
								break;
		
			#if(0)
			case MN_WDR_ON :	bMIPI_CLK_DLY	= MODE_SYSFREQ(0x7, 0x7);									// WDR-ON MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x0022);													// WDR-ON MIPI Data Delay
								RDES_LOCKPOSLw((MP(MpSysFreq)==MN_SYSFREQ_50)?(0x310):(0x2D0));
								break;
			#else
			// MP
			case MN_WDR_ON :	bMIPI_CLK_DLY	= MODE_SYSFREQ(0x2, 0x2);									// WDR-ON MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x0055);													// WDR-ON MIPI Data Delay
								RDES_LOCKPOSLw((MP(MpSysFreq)==MN_SYSFREQ_50)?(0x310):(0x2D0));
								break;
			#endif

		#elif (model_Sens==SENS_IMX390)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0x6);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x4444);				// WDR-OFF MIPI Data Delay
								break;
			
		#elif (model_Sens==SENS_AR0233)
           	case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0x7);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x4444);				// WDR-OFF MIPI Data Delay
								break;

		#elif (model_Sens==SENS_OX03C10)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0x0);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x0000);				// WDR-OFF MIPI Data Delay
								break;
								
		#elif (model_Sens==SENS_IMX335)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0xB);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x4444);				// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0x7);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x4444);				// WDR-OFF MIPI Data Delay
								break;
			UNUSED_ARG(aiResMode);
		
		#elif (model_Sens==SENS_IMX675)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0x4);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x2222);				// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0x4);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x2222);				// WDR-OFF MIPI Data Delay
								break;
			UNUSED_ARG(aiResMode);

		#elif (model_Sens==SENS_SC500AI)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0xB);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x4444);				// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0x1);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x2222);				// WDR-OFF MIPI Data Delay
								break;
																
			UNUSED_ARG(aiResMode);
	
		#elif (model_Sens==SENS_OS04C10)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0x4);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x3333);				// WDR-OFF MIPI Data Delay
								break;

			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0x4);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x3333);				// WDR-OFF MIPI Data Delay
								break;

			UNUSED_ARG(aiResMode);

		#else
			#define LVDS_CLK_DLY 	(LVDS_CKDLYr)
			#define LVDS_LDO_SEL 	(GetIsp(0x33))
			#define LVDS_DATA_DLY	(GetIsp(0x34))
		#endif
	}
	
	#elif (model_TgtBd==1)	// Enx EVM

	switch(aiWdrMode)
	{
		#if (model_Sens==SENS_IMX225)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_1M_FPS_25_30) ? (0x9) : (0x9);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_1M_FPS_25_30) ? (0x0022) : (0x0022);		// WDR-OFF MIPI Data Delay
								break;

		#elif (model_Sens==SENS_IMX224)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_1M_FPS_25_30) ? (0x9) : (0x9);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_1M_FPS_25_30) ? (0x0022) : (0x0022);		// WDR-OFF MIPI Data Delay
								break;

		#elif ((model_Sens==SENS_IMX290)||(model_Sens==SENS_IMX462))
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x9) : (0x9);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0022) : (0x0022);		// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x9) : (0x7);				// WDR-ON MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0022) : (0x2222);		// WDR-ON MIPI Data Delay
								break;

		#elif ((model_Sens==SENS_IMX307)||(model_Sens==SENS_IMX327))
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x9) : (0x9);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0022) : (0x0022);		// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0x9);													// WDR-ON MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x0022);													// WDR-ON MIPI Data Delay
								break;

		#elif ((model_Sens==SENS_GC2053)||(model_Sens==SENS_GC2093)) // 210114 HTY
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x5) : (0x5);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0033) : (0x0033);		// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0x5);													// WDR-ON MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x0033);													// WDR-ON MIPI Data Delay
								break;

		#elif (model_Sens==SENS_SC200AI) 
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0xf) : (0x0);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0033) : (0x0033);		// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0xf);													// WDR-ON MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x0033);													// WDR-ON MIPI Data Delay
								break;
								
		#elif (model_Sens==SENS_PS6210K)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x7) : (0x7);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0022) : (0x0022);		// WDR-OFF MIPI Data Delay
								break;

		#elif (model_Sens==SENS_OS02H10)
			case MN_WDR_OFF:	
								if(MP(MpOutFps) == MN_2M_1080p_275){
									bMIPI_CLK_DLY	= (0x8);													// WDR-OFF MIPI Clock Delay (0x2 ~ 0xd, 0x4~0xf)
									wMIPI_DAYA_DLY	= (0x0022); 												// WDR-OFF MIPI Data Delay
								}
								else{
									bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? MODE_SYSFREQ(0x7,0x9) : (0x7);	// WDR-OFF MIPI Clock Delay (0x2 ~ 0xd, 0x4~0xf)
									wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0022) : (0x0022);		// WDR-OFF MIPI Data Delay
								}
								break;
			case MN_WDR_ON :	
								if(MP(MpOutFps) = MN_2M_1080p_275){
									bMIPI_CLK_DLY	= (0x6);													// WDR-ON MIPI Clock Delay
									wMIPI_DAYA_DLY	= (0x0055); 												// WDR-ON MIPI Data Delay
								}
								else{
									bMIPI_CLK_DLY	= MODE_SYSFREQ(0x2, 0x6);									// WDR-ON MIPI Clock Delay
									wMIPI_DAYA_DLY	= (0x0055);													// WDR-ON MIPI Data Delay
								}
								break;		
		#elif (model_Sens==SENS_IMX390)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0x6);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x4444);				// WDR-OFF MIPI Data Delay
								break;
			
		#elif (model_Sens==SENS_AR0233)
           	case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0x7);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x4444);				// WDR-OFF MIPI Data Delay
								break;

		#elif (model_Sens==SENS_OX03C10)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0x0);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x0000);				// WDR-OFF MIPI Data Delay
								break;
								
		#elif (model_Sens==SENS_IMX335)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0xB);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x4444);				// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0x7);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x4444);				// WDR-OFF MIPI Data Delay
								break;
			UNUSED_ARG(aiResMode);
			
		#elif (model_Sens==SENS_SC500AI)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0xB);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x4444);				// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0x1);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x2222);				// WDR-OFF MIPI Data Delay
								break;
																
			UNUSED_ARG(aiResMode);
	
		#else
			#define LVDS_CLK_DLY 	(LVDS_CKDLYr)
			#define LVDS_LDO_SEL 	(GetIsp(0x33))
			#define LVDS_DATA_DLY	(GetIsp(0x34))
		#endif
	}

	#else
		// Customer config. ====================================================
		
	switch(aiWdrMode)
	{
		#if (model_Sens==SENS_IMX225)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_1M_FPS_25_30) ? (0x9) : (0x9);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_1M_FPS_25_30) ? (0x0022) : (0x0022);		// WDR-OFF MIPI Data Delay
								break;

		#elif (model_Sens==SENS_IMX224)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_1M_FPS_25_30) ? (0x9) : (0x9);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_1M_FPS_25_30) ? (0x0022) : (0x0022);		// WDR-OFF MIPI Data Delay
								break;

		#elif ((model_Sens==SENS_IMX290)||(model_Sens==SENS_IMX462))
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x9) : (0x9);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0022) : (0x0022);		// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x9) : (0x7);				// WDR-ON MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0022) : (0x2222);		// WDR-ON MIPI Data Delay
								break;

		#elif ((model_Sens==SENS_IMX307)||(model_Sens==SENS_IMX327))
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x9) : (0x9);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0022) : (0x0022);		// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0x9);													// WDR-ON MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x0022);													// WDR-ON MIPI Data Delay
								break;

		#elif ((model_Sens==SENS_GC2053)||(model_Sens==SENS_GC2093)) // 210114 HTY
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x5) : (0x5);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0033) : (0x0033);		// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0x5);													// WDR-ON MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x0033);													// WDR-ON MIPI Data Delay
								break;

		#elif (model_Sens==SENS_SC200AI) 
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0xf) : (0x0);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0033) : (0x0033);		// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0xf);													// WDR-ON MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x0033);													// WDR-ON MIPI Data Delay
								break;
								
		#elif (model_Sens==SENS_PS6210K)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x7) : (0x7);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0022) : (0x0022);		// WDR-OFF MIPI Data Delay
								break;

		#elif (model_Sens==SENS_OS02H10)
			case MN_WDR_OFF:	
								if(MP(MpOutFps) == MN_2M_1080p_275){
									bMIPI_CLK_DLY	= (0x8);													// WDR-OFF MIPI Clock Delay (0x2 ~ 0xd, 0x4~0xf)
									wMIPI_DAYA_DLY	= (0x0022); 												// WDR-OFF MIPI Data Delay
								}
								else{
									bMIPI_CLK_DLY	= (aiResMode==MD_2M_FPS_25_30) ? MODE_SYSFREQ(0x7,0x9) : (0x7);	// WDR-OFF MIPI Clock Delay (0x2 ~ 0xd, 0x4~0xf)
									wMIPI_DAYA_DLY	= (aiResMode==MD_2M_FPS_25_30) ? (0x0022) : (0x0022);		// WDR-OFF MIPI Data Delay
								}
								break;
			case MN_WDR_ON :	
								if(MP(MpOutFps) = MN_2M_1080p_275){
									bMIPI_CLK_DLY	= (0x6);													// WDR-ON MIPI Clock Delay
									wMIPI_DAYA_DLY	= (0x0055); 												// WDR-ON MIPI Data Delay
								}
								else{
									bMIPI_CLK_DLY	= MODE_SYSFREQ(0x2, 0x6);									// WDR-ON MIPI Clock Delay
									wMIPI_DAYA_DLY	= (0x0055);													// WDR-ON MIPI Data Delay
								}
								break;
		#elif (model_Sens==SENS_IMX390)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0x6);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x4444);				// WDR-OFF MIPI Data Delay
								break;
			
		#elif (model_Sens==SENS_AR0233)
           	case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0x7);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x4444);				// WDR-OFF MIPI Data Delay
								break;

		#elif (model_Sens==SENS_OX03C10)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0x0);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x0000);				// WDR-OFF MIPI Data Delay
								break;
								
		#elif (model_Sens==SENS_IMX335)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0xB);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x4444);				// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0x7);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x4444);				// WDR-OFF MIPI Data Delay
								break;
			UNUSED_ARG(aiResMode);
			
		#elif (model_Sens==SENS_SC500AI)
			case MN_WDR_OFF:	bMIPI_CLK_DLY	= (0xB);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x4444);				// WDR-OFF MIPI Data Delay
								break;
					
			case MN_WDR_ON :	bMIPI_CLK_DLY	= (0x1);				// WDR-OFF MIPI Clock Delay
								wMIPI_DAYA_DLY	= (0x2222);				// WDR-OFF MIPI Data Delay
								break;
																
			UNUSED_ARG(aiResMode);
	
		#else
			#define LVDS_CLK_DLY 	(LVDS_CKDLYr)
			#define LVDS_LDO_SEL 	(GetIsp(0x33))
			#define LVDS_DATA_DLY	(GetIsp(0x34))
		#endif
	}

		// =====================================================================
	#endif

// Register Write =============================================================================
	LVDS_CKDLYw(  bMIPI_CLK_DLY);	// MIPI Clock delay
	SetIsp(0x24, wMIPI_DAYA_DLY);	// MIPI Data delay
	
//=============================================================================================
}

void InitIsp(void)
{	//ISP Init
	gbModel_ISP = (model_Isp);
	gbModel_Sens = (model_Sens);
	//----------------------------------------------------------------------------------------	
	UINT i;

	// Init ISP - ISP Common
	for(i=0; i<gnTblIspCommonEa; i++)		{SetIsp(gnTblIspCommon[i][0], gnTblIspCommon[i][1]);} 
	
	// Init ISP - Pre
	for(i=0; i<gnTblIspPreEa; i++) 			{SetIsp(gnTblIspPre[i][0], gnTblIspPre[i][1]);}

	LibModeInit();		// fixed

	//----------------------------------------------------------------------------------------
	// Default Mode Init : 1080 30P
	#define DEFAULT_OUT_MODE		((model_1M) ? (MN_1M_720p_25_30) : (model_2M) ? (MN_2M_1080p_25_30) : (model_5M) ? (MN_4M_1080p_25_30) : (MN_2M_1080p_50_60)) /*MP(MpOutFps)*/

	// init ISP - Post
	for (i=0; i<gnTblIspModeEa; i++) 		{SetIsp(gnTblIspMode[i][0], gnTblIspMode[i][1+(DEFAULT_OUT_MODE)+0]);}		// Digital

	InitRdesConfig(0, 0);					// LVDS Timing config.
	
}

//*************************************************************************************************
// Init Top
//-------------------------------------------------------------------------------------------------
void Init(void)
{	// Init Top
//----------------------------------------------------------------------------------------
// Init ISP
	InitIsp();														// for ISPx
	
//----------------------------------------------------------------------------------------
// Init CPU
	InitDataID();
	SetWaitTimeOffset(MCLK, 1);										// It must be run prior to InitTickTimer()

	InitGpio(); 													// GPIO and Function PIN MUX
	InitUart();														// UART(interrupt)

	/*if((_reset_s&FLASH_ADDR_MASK) == 0)*/ TxStrNoIRQ(0, 0, 0);	// for sync with the ECM
	TxStrNoIRQ("\t\t\t\t\t", 0, 0);
	TxStrNoIRQ("----- ISP Init. -----", 0/*HDSDI_POr*/, 0/*1*/);

	InitFlash();													// Serial Flash

	InitI2c();														// I2C
	InitSpi();														// SPI

	InitTimer();													// Timer(interrupt) or PWM
	InitWdt(WDT_TIME);												// Watchdog

	InitAdc();														// ADC

	InitIrq();														// for IRQ
	InitTickTimer(EWV(1, FPS_DEF));									// for Tick timer(interrupt)

//-------------------------------------------------------------------------------------------------
// Init Sensor

	TxStrDecNoIRQ("Sensor Init Start-", model_Sens, 4);
//	FUNC_TIME_TX_NoIRQ("Sensor Init Time", InitSens(); )			// Time checking for sensor initial
	InitSens();

//-------------------------------------------------------------------------------------------------
// Init Function
	APP_READ_CHK_ALL
	AppLoadPar();													// load parameter from memory

#if (model_Par==1)
	InitPar();														// LVDS timing, KEY, User Custom Paremeter, Etc.
#endif

	InitMenu();
	
	ModeChange();
	
	InitAe();														// AE init

	InitWaitVd(0);													// Pre operation check <- InitIrq()�� ���� �ؾ���

	InitContrast();

	InitGamma();
	
//	TDN_MECH_DAY	WaitUs(100000);	TDN_MECH_HLD					// TDN reset

	InitAwb();

	InitShd();

	//Output range, color space Initial
	ColorSpace();										// Color space selelction
	ImageRange();										// Image Range
	
//----------------------------------------------------------------------------------------
// Init Tail
	WdtEna;												// Enable Watchdog
	POST_MASKw(0);										// Mask off

//----------------------------------------------------------------------------------------
// Tx Info.
	TxStrNoIRQ("****************************************************", 0, 0);	
	TxStrNoIRQ("<< FW Information >>", 0, 0);	
	TxStrNoIRQ("FW Ver. : ", model_ver, 4);
	TxStrNoIRQ(gsBuildDate, 0, 8);
	TxStrNoIRQ("Compile	 : ", gDataID, 4);
	TxStrNoIRQ("Engineer : HANTY ", 0, 0);
	TxStrNoIRQ("Customer : Yuanchang ", 0, 0);
	TxStrNoIRQ("IQ Ver   : v1.0.0 ", 0, 0);
	TxStrNoIRQ("Date   	 : 26-01-15 ", 0, 0);
	TxStrNoIRQ("PAR Ver  : 7203_Custom_ver ", 0, 0);
	// TxStrNoIRQ("Contents : Saved MIPI Timing, Saved IQ Ver, New Matrix ", 0, 0);
	TxStrNoIRQ("****************************************************", 0, 0);	

	LibModelInfo();

	gwFW_Ver = 0x01;
//	gwIQ_Ver = 0x00;

	TxStrNoIRQ("F/W Release Version : ",gwFW_Ver,3);
	TxStrNoIRQ("Par Release Version : ",UP(UpUsrParVer),3);

#if 0
	CheckByteOrdering();								// TxStr() ���

	TxStrDec("WaitTimeOffset ", gnWaitTimeOffset,10);	// TxStr() ���

	TxStrMemAddrInfo();									// TxStr() ���

	TxStrCacheSize();									// TxStr() ���
#endif

#if(1)
	LINE0_ONw(0x0);
	LINE1_ONw(0x0);
#endif

}

