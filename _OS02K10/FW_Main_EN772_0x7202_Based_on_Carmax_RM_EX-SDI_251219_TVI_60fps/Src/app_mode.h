/* **************************************************************************
 File Name	: app_mode.h
 Description	: Mode define header file
 Designer		: Lee, Gyu-Hong
 Date		: 18-03-02
 Copyright �� DCOD Co., Ltd. All Rights Reserved.
*************************************************************************** */

// ======================================================================================================================
// InMode
// ======================================================================================================================
#if(model_1M)
#define MODE_SS_HTW_1M_30			DFSEL_Sens(6600,6600,3000,1650, 0,	0, 0, 0, 0, 0)
#define MODE_SS_VTW_1M_30			DFSEL_Sens( 750, 750, 825, 750, 0,	0, 0, 0, 0, 0)

#define MODE_SS_HTW_1M_25			DFSEL_Sens(7920,7920,3600,1980, 0,	0, 0, 0, 0, 0)
#define MODE_SS_VTW_1M_25			DFSEL_Sens( 750, 750, 825, 750, 0,	0, 0, 0, 0, 0)
                                                                                   
#define MODE_SS_HTW_1M_60			DFSEL_Sens(3300,3300,1500,1650, 0,	0, 0, 0, 0, 0)
#define MODE_SS_VTW_1M_60			DFSEL_Sens( 750, 750, 825, 750, 0,	0, 0, 0, 0, 0)
                                                                                   
#define MODE_SS_HTW_1M_50			DFSEL_Sens(3960,3960,1800,1980, 0,	0, 0, 0, 0, 0)
#define MODE_SS_VTW_1M_50			DFSEL_Sens( 750, 750, 825, 750, 0,	0, 0, 0, 0, 0)                                                                              
                                                                                   
#define MODE_RDES_HTW_1M_30			DFSEL_Sens(3300,3300,3000,3300, 0,	0, 0, 0, 0, 0)
#define MODE_RDES_VTW_1M_30			DFSEL_Sens( 750, 750, 825, 750, 0,	0, 0, 0, 0, 0)
                                                                                   
#define MODE_RDES_HTW_1M_25			DFSEL_Sens(3960,3960,3600,3960, 0,	0, 0, 0, 0, 0)
#define MODE_RDES_VTW_1M_25			DFSEL_Sens( 750, 750, 825, 750, 0,	0, 0, 0, 0, 0)
                                                                                   
#define MODE_RDES_HTW_1M_60			DFSEL_Sens(1650,1650,1500,1650, 0,	0, 0, 0, 0, 0)
#define MODE_RDES_VTW_1M_60			DFSEL_Sens( 750, 750, 825, 750, 0,	0, 0, 0, 0, 0)
                                                                                   
#define MODE_RDES_HTW_1M_50			DFSEL_Sens(1980,1980,1800,1980, 0,	0, 0, 0, 0, 0)
#define MODE_RDES_VTW_1M_50			DFSEL_Sens( 750, 750, 825, 750, 0,	0, 0, 0, 0, 0)
                                                                               
#if(model_Sens_LWdr)
#define MODE_SS_HTW_1M_30_LWDR		DFSEL_Sens(0,3300, 0,1650, 0, 0,	0, 0, 0, 0)	
#define MODE_SS_VTW_1M_30_LWDR		DFSEL_Sens(0, 750, 0, 750, 0, 0,	0, 0, 0, 0)	
                                                                            
#define MODE_SS_HTW_1M_25_LWDR		DFSEL_Sens(0,3960, 0,1980, 0, 0,	0, 0, 0, 0)	
#define MODE_SS_VTW_1M_25_LWDR		DFSEL_Sens(0, 750, 0, 750, 0, 0,	0, 0, 0, 0)	
                                                                            
#define MODE_SS_HTW_1M_60_LWDR		DFSEL_Sens(0,1650, 0,1650, 0, 0,	0, 0, 0, 0)
#define MODE_SS_VTW_1M_60_LWDR		DFSEL_Sens(0, 750, 0, 750, 0, 0,	0, 0, 0, 0)
                                                                            
#define MODE_SS_HTW_1M_50_LWDR		DFSEL_Sens(0,1980, 0,1980, 0, 0,	0, 0, 0, 0)
#define MODE_SS_VTW_1M_50_LWDR		DFSEL_Sens(0, 750, 0, 750, 0, 0,	0, 0, 0, 0)
                                                                           
#define MODE_RDES_HTW_1M_30_LWDR	DFSEL_Sens(0,3300, 0,3300, 0, 0,	0, 0, 0, 0)	
#define MODE_RDES_VTW_1M_30_LWDR	DFSEL_Sens(0, 750, 0, 750, 0, 0,	0, 0, 0, 0)	
                                                                            
#define MODE_RDES_HTW_1M_25_LWDR	DFSEL_Sens(0,3960, 0,3960, 0, 0,	0, 0, 0, 0)	
#define MODE_RDES_VTW_1M_25_LWDR	DFSEL_Sens(0, 750, 0, 750, 0, 0,	0, 0, 0, 0)	
                                                                            
#define MODE_RDES_HTW_1M_60_LWDR	DFSEL_Sens(0,1650, 0,1650, 0, 0,	0, 0, 0, 0)
#define MODE_RDES_VTW_1M_60_LWDR	DFSEL_Sens(0, 750, 0, 750, 0, 0,	0, 0, 0, 0)
                                                                            
#define MODE_RDES_HTW_1M_50_LWDR	DFSEL_Sens(0,1980, 0,1980, 0, 0,	0, 0, 0, 0)
#define MODE_RDES_VTW_1M_50_LWDR	DFSEL_Sens(0, 750, 0, 750, 0, 0,	0, 0, 0, 0)
#endif

#elif(model_2M)
// 2M START===============================================================================================
// 2M_L
#if(model_2M_L)
#define MODE_SS_HTW_2M_30			DFSEL_Sens(4400,4400,4400,4400,2200,1100,1100,1100,2200,1250)
#define MODE_SS_VTW_2M_30			DFSEL_Sens(1125,1125,1125,1125,1125,1125,1125,2250,1125,1125)
                                                                                                
#define MODE_SS_HTW_2M_25			DFSEL_Sens(5280,5280,5280,5280,2640,1320,1320,1320,2640,1220)
#define MODE_SS_VTW_2M_25			DFSEL_Sens(1125,1125,1125,1125,1125,1125,1125,2250,1125,1125)
                                                                                                
#define MODE_SS_HTW_2M_60			DFSEL_Sens(2200,2200,2200,2200,1100,675 ,675 ,1100,2200,1280)
#define MODE_SS_VTW_2M_60			DFSEL_Sens(1125,1125,1125,1125,1125,1125,1125,2250,1125,1125)
                                                                                                
#define MODE_SS_HTW_2M_50			DFSEL_Sens(2640,2640,2640,2640,1320,810 ,810 ,1320,2640,1248)
#define MODE_SS_VTW_2M_50			DFSEL_Sens(1125,1125,1125,1125,1125,1125,1125,2250,1125,1125) 
                                                                       
#define MODE_RDES_HTW_2M_30			DFSEL_Sens(2200,2200,2200,2200,2200,2200,2200,2200,2200,2200)
#define MODE_RDES_VTW_2M_30			DFSEL_Sens(1125,1125,1125,1125,1125,1125,1125,1125,1125,1125)
                                                                                           
#define MODE_RDES_HTW_2M_25			DFSEL_Sens(2640,2640,2640,2640,2640,2640,2640,2640,2640,2640)
#define MODE_RDES_VTW_2M_25			DFSEL_Sens(1125,1125,1125,1125,1125,1125,1125,1125,1125,1125)
                                                                                                
#define MODE_RDES_HTW_2M_60			DFSEL_Sens(2200,2200,2200,2200,2200,2200,2200,2200,2200,2200)
#define MODE_RDES_VTW_2M_60			DFSEL_Sens(1125,1125,1125,1125,1125,1125,1125,1125,1125,1125)
                                                                                                
#define MODE_RDES_HTW_2M_50			DFSEL_Sens(2640,2640,2640,2640,2640,2640,2640,2640,2640,2640)
#define MODE_RDES_VTW_2M_50			DFSEL_Sens(1125,1125,1125,1125,1125,1125,1125,1125,1125,1125)

// ------------------------------------------
// 2M to 5M Upscale
// ------------------------------------------
#if(model_Sens_US2Mto5M)
#define	MODE_SS_HTW_2Mto5M_125		DFSEL_Sens(MODE_HDT_125(11880,12000),MODE_HDT_125(11880,12000),MODE_HDT_125(11880,12000),MODE_HDT_125(11880,12000),0,0,0,0,0,0)
#define MODE_SS_VTW_2Mto5M_125		DFSEL_Sens(MODE_HDT_125( 1000,  990),MODE_HDT_125( 1000,  990),MODE_HDT_125( 1000,  990),MODE_HDT_125( 1000,  990),0,0,0,0,0,0)
                                                                   
#define	MODE_SS_HTW_2Mto5M_20		DFSEL_Sens(7500,7500,7500,7500,0,0,0,0,0,0)
#define MODE_SS_VTW_2Mto5M_20		DFSEL_Sens( 990, 990, 990, 990,0,0,0,0,0,0)

#define	MODE_RDES_HTW_2Mto5M_125	DFSEL_Sens(MODE_HDT_125(5940, 6000),MODE_HDT_125(5940, 6000),MODE_HDT_125(5940, 6000),MODE_HDT_125(5940, 6000),0,0,0,0,0,0)
#define MODE_RDES_VTW_2Mto5M_125	DFSEL_Sens(MODE_HDT_125(1000,  990),MODE_HDT_125(1000,  990),MODE_HDT_125(1000,  990),MODE_HDT_125(1000,  990),0,0,0,0,0,0)
                                                                   
#define	MODE_RDES_HTW_2Mto5M_20		DFSEL_Sens(3750,3750,3750,3750,0,0,0,0,0,0)
#define MODE_RDES_VTW_2Mto5M_20		DFSEL_Sens( 990, 990, 990, 990,0,0,0,0,0,0)
#endif

// ------------------------------------------
// CVBS Mode
// ------------------------------------------
#if(model_IspO_ANL)
#define	MODE_SS_HTW_CVBS_NTSC		DFSEL_Sens(2100,2100,2100,2100,0,0,0,0,0,0)
#define MODE_SS_VTW_CVBS_NTSC		DFSEL_Sens(1144,1144,1144,1144,0,0,0,0,0,0)

#define	MODE_SS_HTW_CVBS_PAL		DFSEL_Sens(2640,2640,2640,2640,0,0,0,0,0,0)
#define MODE_SS_VTW_CVBS_PAL		DFSEL_Sens(1125,1125,1125,1125,0,0,0,0,0,0)

#define	MODE_RDES_HTW_CVBS_NTSC		DFSEL_Sens(2100,2100,2100,2100,0,0,0,0,0,0)
#define MODE_RDES_VTW_CVBS_NTSC		DFSEL_Sens(1144,1144,1144,1144,0,0,0,0,0,0)

#define	MODE_RDES_HTW_CVBS_PAL		DFSEL_Sens(2640,2640,2640,2640,0,0,0,0,0,0)
#define MODE_RDES_VTW_CVBS_PAL		DFSEL_Sens(1125,1125,1125,1125,0,0,0,0,0,0)
#endif


#if(model_Sens_LWdr)
#define MODE_SS_HTW_2M_30_LWDR		DFSEL_Sens(2200,2200,2200,2200,1100,	0,	675 ,1100,	 0,1248)	
#define MODE_SS_VTW_2M_30_LWDR		DFSEL_Sens(1125,1125,1125,1125,1125,	0,	1125,2250,	 0,1125)	
                                                                                                   
#define MODE_SS_HTW_2M_25_LWDR		DFSEL_Sens(2640,2640,2640,2640,1320,	0,	810 ,1320,	 0,1248)	
#define MODE_SS_VTW_2M_25_LWDR		DFSEL_Sens(1125,1125,1125,1125,1125,	0,	1125,2250,	 0,1125)	
                                                                                                   
#define MODE_SS_HTW_2M_60_LWDR		DFSEL_Sens(1100,1100,1100,1100,   0,	0,	   0,	0,	 0,1100)
#define MODE_SS_VTW_2M_60_LWDR		DFSEL_Sens(1125,1125,1125,1125,   0,	0,	   0,	0,	 0,1125)
                                                                                                   
#define MODE_SS_HTW_2M_50_LWDR		DFSEL_Sens(1320,1320,1320,1320,   0,	0,	   0,	0,	 0,1320)
#define MODE_SS_VTW_2M_50_LWDR		DFSEL_Sens(1125,1125,1125,1125,   0,	0,	   0,	0,	 0,1125)
                                                                       
#define MODE_RDES_HTW_2M_30_LWDR	DFSEL_Sens(2200,2200,2200,2200,2200,	2200, 2200,	2200,	 0,2200)	
#define MODE_RDES_VTW_2M_30_LWDR	DFSEL_Sens(1125,1125,1125,1125,1125,	1125, 1125,	1125,	 0,1125)	
                                                                                    
#define MODE_RDES_HTW_2M_25_LWDR	DFSEL_Sens(2640,2640,2640,2640,2640,	2640, 2640,	2640,	 0,2640)	
#define MODE_RDES_VTW_2M_25_LWDR	DFSEL_Sens(1125,1125,1125,1125,1125,	1125, 1125,	1125,	 0,1125)	
                                                                                    
#define MODE_RDES_HTW_2M_60_LWDR	DFSEL_Sens(2200,2200,2200,2200,   0,	2200, 2200,	0,	 0,2200)
#define MODE_RDES_VTW_2M_60_LWDR	DFSEL_Sens(1125,1125,1125,1125,   0,	1125, 1125,	0,	 0,1125)
                                                                                    
#define MODE_RDES_HTW_2M_50_LWDR	DFSEL_Sens(2640,2640,2640,2640,   0,	2640, 2640,	0,	 0,2640)
#define MODE_RDES_VTW_2M_50_LWDR	DFSEL_Sens(1125,1125,1125,1125,   0,	1125, 1125,	0,	 0,1125)

#if(model_Sens_US2Mto5M)
#define	MODE_SS_HTW_2Mto5M_125_LWDR	DFSEL_Sens(MODE_HDT_125(5940, 6000),MODE_HDT_125(5940, 6000),MODE_HDT_125(5940, 6000),MODE_HDT_125(5940, 6000),0,0,0,0,0,0)
#define MODE_SS_VTW_2Mto5M_125_LWDR	DFSEL_Sens(MODE_HDT_125(1000,  990),MODE_HDT_125(1000,  990),MODE_HDT_125(1000,  990),MODE_HDT_125(1000,  990),0,0,0,0,0,0)
                                                                   
#define	MODE_SS_HTW_2Mto5M_20_LWDR	DFSEL_Sens(3750,3750,3750,3750,0,0,0,0,0,0)
#define MODE_SS_VTW_2Mto5M_20_LWDR	DFSEL_Sens( 990, 990, 990, 990,0,0,0,0,0,0)

#define	MODE_RDES_HTW_2Mto5M_125_LWDR	DFSEL_Sens(MODE_HDT_125(5940, 6000),MODE_HDT_125(5940, 6000),MODE_HDT_125(5940, 6000),MODE_HDT_125(5940, 6000),0,0,0,0,0,0)
#define MODE_RDES_VTW_2Mto5M_125_LWDR	DFSEL_Sens(MODE_HDT_125(1000,  990),MODE_HDT_125(1000,  990),MODE_HDT_125(1000,  990),MODE_HDT_125(1000,  990),0,0,0,0,0,0)
                                                                   
#define	MODE_RDES_HTW_2Mto5M_20_LWDR	DFSEL_Sens(3750,3750,3750,3750,0,0,0,0,0,0)
#define MODE_RDES_VTW_2Mto5M_20_LWDR	DFSEL_Sens( 990, 990, 990, 990,0,0,0,0,0,0)
#endif

// ------------------------------------------
// CVBS Mode
// ------------------------------------------
#if(model_IspO_ANL)
#define	MODE_SS_HTW_CVBS_NTSC_LWDR	DFSEL_Sens(1050,0,0,1050,0,0,0,0,0,0)
#define MODE_SS_VTW_CVBS_NTSC_LWDR	DFSEL_Sens(1144,0,0,1144,0,0,0,0,0,0)

#define	MODE_SS_HTW_CVBS_PAL_LWDR	DFSEL_Sens(1320,0,0,1320,0,0,0,0,0,0)
#define MODE_SS_VTW_CVBS_PAL_LWDR	DFSEL_Sens(1125,0,0,1125,0,0,0,0,0,0)

#define	MODE_RDES_HTW_CVBS_NTSC_LWDR DFSEL_Sens(2100,0,0,2100,0,0,0,0,0,0)
#define MODE_RDES_VTW_CVBS_NTSC_LWDR DFSEL_Sens(1144,0,0,1144,0,0,0,0,0,0)

#define	MODE_RDES_HTW_CVBS_PAL_LWDR	DFSEL_Sens(2640,0,0,2640,0,0,0,0,0,0)
#define MODE_RDES_VTW_CVBS_PAL_LWDR	DFSEL_Sens(1125,0,0,1125,0,0,0,0,0,0)
#endif

#endif

//********************************************************************************************************

// 2M_H
#else

#if(model_fps_2904)
#define MODE_SS_HTW_2M_30			DFSEL_Sens(1980,0,0,3200,1250,2400,2200,1980,0,0)
#define MODE_SS_VTW_2M_30			DFSEL_Sens(1250,0,0,1162,1125, 625,1120,1250,0,0)
#else
#define MODE_SS_HTW_2M_30			DFSEL_Sens(1980,0,0,3200,1250,2400,2200,1980,0,0)
#define MODE_SS_VTW_2M_30			DFSEL_Sens(1250,0,0,1125,1125, 625,1120,1250,0,0)
#endif

#define MODE_SS_HTW_2M_25			DFSEL_Sens(2376,0,0,3840,1220,2880,2640,0,0,0)
#define MODE_SS_VTW_2M_25			DFSEL_Sens(1250,0,0,1125,1125, 625,1120,0,0,0)

#define MODE_SS_HTW_2M_60			DFSEL_Sens(1980,0,0,1600,1280,1200,1100,0,0,0)
#define MODE_SS_VTW_2M_60			DFSEL_Sens(1250,0,0,1125,1125, 625,1120,0,0,0)

#define MODE_SS_HTW_2M_50			DFSEL_Sens(2376,0,0,1920,1248,1440,1320,0,0,0)
#define MODE_SS_VTW_2M_50			DFSEL_Sens(1250,0,0,1125,1125, 625,1120,0,0,0)

#if(model_fps_2904)
#define MODE_RDES_HTW_2M_30			DFSEL_Sens(1980,0,0,2200,2200,1980,2200,1980,0,0)
#define MODE_RDES_VTW_2M_30			DFSEL_Sens(1250,0,0,1162,1125,1250,1125,1250,0,0)
#else
#define MODE_RDES_HTW_2M_30			DFSEL_Sens(1980,0,0,2200,2200,1980,2200,1980,0,0)
#define MODE_RDES_VTW_2M_30			DFSEL_Sens(1250,0,0,1125,1125,1250,1125,1250,0,0)
#endif

#define MODE_RDES_HTW_2M_25			DFSEL_Sens(2376,0,0,2640,2640,2376,2640,0,0,0)
#define MODE_RDES_VTW_2M_25			DFSEL_Sens(1250,0,0,1125,1125,1250,1125,0,0,0)

#define MODE_RDES_HTW_2M_60			DFSEL_Sens(1980,0,0,2200,2200,1980,2200,2200,0,0)
#define MODE_RDES_VTW_2M_60			DFSEL_Sens(1250,0,0,1125,1125,1250,1125,1125,0,0)

#define MODE_RDES_HTW_2M_50			DFSEL_Sens(2376,0,0,2640,2640,2376,2640,2376,0,0)
#define MODE_RDES_VTW_2M_50			DFSEL_Sens(1250,0,0,1125,1125,1250,1125,1250,0,0)

// ------------------------------------------
// CVBS Mode
// ------------------------------------------
#if(model_IspO_ANL)
#define	MODE_SS_HTW_CVBS_NTSC		DFSEL_Sens(0,0,2080,0,0,0,0,0,0,0)
#define MODE_SS_VTW_CVBS_NTSC		DFSEL_Sens(0,0,1155,0,0,0,0,0,0,0)

#define	MODE_SS_HTW_CVBS_PAL		DFSEL_Sens(0,0,2640,0,0,0,0,0,0,0)
#define MODE_SS_VTW_CVBS_PAL		DFSEL_Sens(0,0,1125,0,0,0,0,0,0,0)

#define	MODE_RDES_HTW_CVBS_NTSC		DFSEL_Sens(0,0,2080,0,0,0,0,0,0,0)
#define MODE_RDES_VTW_CVBS_NTSC		DFSEL_Sens(0,0,1155,0,0,0,0,0,0,0)

#define	MODE_RDES_HTW_CVBS_PAL		DFSEL_Sens(0,0,2640,0,0,0,0,0,0,0)
#define MODE_RDES_VTW_CVBS_PAL		DFSEL_Sens(0,0,1125,0,0,0,0,0,0,0)
#endif


#if(model_Sens_LWdr)
#if(model_fps_2904)
#define MODE_SS_HTW_2M_30_LWDR		DFSEL_Sens(0,0,0,2132,1248,0,0,0,0,0)
#define MODE_SS_VTW_2M_30_LWDR		DFSEL_Sens(0,0,0,1162,1125,0,0,0,0,0)
#else
#define MODE_SS_HTW_2M_30_LWDR		DFSEL_Sens(0,0,0,2132,1248,0,0,0,0,0)
#define MODE_SS_VTW_2M_30_LWDR		DFSEL_Sens(0,0,0,1125,1125,0,0,0,0,0)
#endif
#define MODE_SS_HTW_2M_25_LWDR		DFSEL_Sens(0,0,0,2560,1248,0,0,0,0,0)	
#define MODE_SS_VTW_2M_25_LWDR		DFSEL_Sens(0,0,0,1125,1125,0,0,0,0,0)	

#define MODE_SS_HTW_2M_60_LWDR		DFSEL_Sens(0,0,0,1600,1100,0,0,0,0,0)
#define MODE_SS_VTW_2M_60_LWDR		DFSEL_Sens(0,0,0,1125,1125,0,0,0,0,0)

#define MODE_SS_HTW_2M_50_LWDR		DFSEL_Sens(0,0,0,1920,1320,0,0,0,0,0)
#define MODE_SS_VTW_2M_50_LWDR		DFSEL_Sens(0,0,0,1125,1125,0,0,0,0,0)

#if(model_fps_2904)
#define MODE_RDES_HTW_2M_30_LWDR	DFSEL_Sens(0,0,0,2200,2200,0,0,0,0,0)	
#define MODE_RDES_VTW_2M_30_LWDR	DFSEL_Sens(0,0,0,1162,1125,0,0,0,0,0)
#else
#define MODE_RDES_HTW_2M_30_LWDR	DFSEL_Sens(0,0,0,2200,2200,0,0,0,0,0)	
#define MODE_RDES_VTW_2M_30_LWDR	DFSEL_Sens(0,0,0,1125,1125,0,0,0,0,0)	
#endif

#define MODE_RDES_HTW_2M_25_LWDR	DFSEL_Sens(0,0,0,2640,2640,0,0,0,0,0)	
#define MODE_RDES_VTW_2M_25_LWDR	DFSEL_Sens(0,0,0,1125,1125,0,0,0,0,0)	

#define MODE_RDES_HTW_2M_60_LWDR	DFSEL_Sens(0,0,0,2200,2200,0,0,0,0,0)
#define MODE_RDES_VTW_2M_60_LWDR	DFSEL_Sens(0,0,0,1125,1125,0,0,0,0,0)

#define MODE_RDES_HTW_2M_50_LWDR	DFSEL_Sens(0,0,0,2640,2640,0,0,0,0,0)
#define MODE_RDES_VTW_2M_50_LWDR	DFSEL_Sens(0,0,0,1125,1125,0,0,0,0,0)
#endif
//********************************************************************************************************
#endif

//2M END=====================================================================================================

#elif(model_5M)
// 4M,5M START===============================================================================================
#define MODE_SS_HTW_4M_30			DFSEL_Sens((model_Sens_335_805)?( 750):(1650),	(1650),	(1500),	(1500),	0,	1600,	0,	0,	1650,	(2250))
#define MODE_SS_VTW_4M_30			DFSEL_Sens((model_Sens_335_805)?(3300):(3000),	(1500),	(1650),	(1650),	0,	1500,	0,	0,	3000,	(1500))
                                                                                         
#define MODE_SS_HTW_4M_25			DFSEL_Sens((model_Sens_335_805)?( 900):(1980),	(1980),	0,	0,	0,	0,	0,	0,	1980,	(2700))
#define MODE_SS_VTW_4M_25			DFSEL_Sens((model_Sens_335_805)?(3300):(3000),	(1500),	0,	0,	0,	0,	0,	0,	3000,	(1500))
                                                                                         
#define MODE_SS_HTW_5M_20			DFSEL_Sens((model_Sens_335_805)?( 990):(1875),	(1875),	0,	0,	0,	0,	0,	0,	1650,	0)
#define MODE_SS_VTW_5M_20			DFSEL_Sens((model_Sens_335_805)?(3750):(3960),	(1980),	0,	0,	0,	0,	0,	0,	3000,	0)
                                                         
#define MODE_SS_HTW_5M_125			DFSEL_Sens((model_Sens_335_805)?(1500):(MODE_HDT_125(2970,3000)),	(MODE_HDT_125(2970,3000)),	0,	0,	0,	1188,	0,	0,	0,	0)
#define MODE_SS_VTW_5M_125			DFSEL_Sens((model_Sens_335_805)?(3960):(MODE_HDT_125(4000,3960)),	(MODE_HDT_125(2000,1980)),	0,	0,	0,	2000,	0,	0,	0,	0)

#define MODE_SS_HTW_5M_25			DFSEL_Sens((model_Sens_335_805)?( 750):(1500),	(1500),	0,	0,	0,	0,	0,	0,	1650,	0)
#define MODE_SS_VTW_5M_25			DFSEL_Sens((model_Sens_335_805)?(3960):(3960),	(1980),	0,	0,	0,	0,	0,	0,	3000,	0)

#define MODE_RDES_HTW_4M_30			DFSEL_Sens((model_Sens_335_805)?(3000):(3300),	(3300),	(3000),	(3000),	0,	3300,	0,	0,	3300,	(3300))
#define MODE_RDES_VTW_4M_30			DFSEL_Sens((model_Sens_335_805)?(1650):(1500),	(1500),	(1650),	(1650),	0,	1500,	0,	0,	1500,	(1500))
                                                                                         
#define MODE_RDES_HTW_4M_25			DFSEL_Sens((model_Sens_335_805)?(3600):(3960),	(3960),	0,	0,	0,	0,	0,	0,	3960,	(3960))
#define MODE_RDES_VTW_4M_25			DFSEL_Sens((model_Sens_335_805)?(1650):(1500),	(1500),	0,	0,	0,	0,	0,	0,	1500,	(1500))
                                                                         
#define MODE_RDES_HTW_5M_20			DFSEL_Sens((model_Sens_335_805)?(3960):(3750),	(3750),	0,	0,	0,	0,	0,	0,	0,	0)
#define MODE_RDES_VTW_5M_20			DFSEL_Sens((model_Sens_335_805)?(1875):(1980),	(1980),	0,	0,	0,	0,	0,	0,	0,	0)
                                                         
#define MODE_RDES_HTW_5M_125		DFSEL_Sens((model_Sens_335_805)?(3000):(MODE_HDT_125(2970,3000)),	(MODE_HDT_125(2970,3000)),	0,	0,	0,	0,	0,	0,	0,	0)
#define MODE_RDES_VTW_5M_125		DFSEL_Sens((model_Sens_335_805)?(1980):(MODE_HDT_125(2000,1980)),	(MODE_HDT_125(2000,1980)),	0,	0,	0,	0,	0,	0,	0,	0)

#define MODE_RDES_HTW_5M_25			DFSEL_Sens((model_Sens_335_805)?(3000):(3000),	(3000),	0,	0,	0,	0,	0,	0,	0,	0)
#define MODE_RDES_VTW_5M_25			DFSEL_Sens((model_Sens_335_805)?(1980):(1980),	(1980),	0,	0,	0,	0,	0,	0,	0,	0)

// ------------------------------------------
// CVBS Mode
// ------------------------------------------
#if(model_IspO_ANL)
#define	MODE_SS_HTW_CVBS_NTSC		DFSEL_Sens(0,0,2080,0,0,0,0,0,0,0)
#define MODE_SS_VTW_CVBS_NTSC		DFSEL_Sens(0,0,1155,0,0,0,0,0,0,0)

#define	MODE_SS_HTW_CVBS_PAL		DFSEL_Sens(0,0,2640,0,0,0,0,0,0,0)
#define MODE_SS_VTW_CVBS_PAL		DFSEL_Sens(0,0,1125,0,0,0,0,0,0,0)

#define	MODE_RDES_HTW_CVBS_NTSC		DFSEL_Sens(0,0,2080,0,0,0,0,0,0,0)
#define MODE_RDES_VTW_CVBS_NTSC		DFSEL_Sens(0,0,1155,0,0,0,0,0,0,0)

#define	MODE_RDES_HTW_CVBS_PAL		DFSEL_Sens(0,0,2640,0,0,0,0,0,0,0)
#define MODE_RDES_VTW_CVBS_PAL		DFSEL_Sens(0,0,1125,0,0,0,0,0,0,0)
#endif

#if(model_Sens_LWdr)                                     
#define MODE_SS_HTW_4M_30_LWDR		DFSEL_Sens((model_Sens_335_805)?( 375):( 825),	( 825),	( 750),	0,	0,	1475,	0,	0,	1650,	(1200))
#define MODE_SS_VTW_4M_30_LWDR		DFSEL_Sens((model_Sens_335_805)?(3300):(3000),	(1500),	(1650),	0,	0,	1500,	0,	0,	3000,	(1500))
                                                                                         
#define MODE_SS_HTW_4M_25_LWDR		DFSEL_Sens((model_Sens_335_805)?( 450):( 990),	( 990),	0,	0,	0,	0,	0,	0,	1980,	(1440))
#define MODE_SS_VTW_4M_25_LWDR		DFSEL_Sens((model_Sens_335_805)?(3300):(3000),	(1500),	0,	0,	0,	0,	0,	0,	3000,	(1500))
                                                                         
#define MODE_SS_HTW_5M_20_LWDR		DFSEL_Sens((model_Sens_335_805)?( 495):( 937),	( 937),	0,	0,	0,	0,	0,	0,	0,	0)
#define MODE_SS_VTW_5M_20_LWDR		DFSEL_Sens((model_Sens_335_805)?(3750):(3960),	(1980),	0,	0,	0,	0,	0,	0,	0,	0)
                                                         
#define MODE_SS_HTW_5M_125_LWDR		DFSEL_Sens((model_Sens_335_805)?( 750):(MODE_HDT_125(1485,1500)),	0,	0,	0,	0,	1188,	0,	0,	0,	0)
#define MODE_SS_VTW_5M_125_LWDR		DFSEL_Sens((model_Sens_335_805)?(3960):(MODE_HDT_125(4000,3960)),	0,	0,	0,	0,	1980,	0,	0,	0,	0)

#define MODE_SS_HTW_5M_25_LWDR		DFSEL_Sens((model_Sens_335_805)?( 375):( 750),	( 750),	0,	0,	0,	0,	0,	0,	0,	0)
#define MODE_SS_VTW_5M_25_LWDR		DFSEL_Sens((model_Sens_335_805)?(3960):(3960),	(1980),	0,	0,	0,	0,	0,	0,	0,	0)

#define MODE_RDES_HTW_4M_30_LWDR	DFSEL_Sens((model_Sens_335_805)?(3000):(3300),	(3300),	(3000),	0,	0,	3300,	0,	0,	3300,	(3300))
#define MODE_RDES_VTW_4M_30_LWDR	DFSEL_Sens((model_Sens_335_805)?(1650):(1500),	(1500),	(1650),	0,	0,	1500,	0,	0,	1500,	(1500))
                                                                                         
#define MODE_RDES_HTW_4M_25_LWDR	DFSEL_Sens((model_Sens_335_805)?(3600):(3960),	(3960),	0,	0,	0,	0,	0,	0,	3960,	(3960))
#define MODE_RDES_VTW_4M_25_LWDR	DFSEL_Sens((model_Sens_335_805)?(1650):(1500),	(1500),	0,	0,	0,	0,	0,	0,	1500,	(1500))
                                                                         
#define MODE_RDES_HTW_5M_20_LWDR	DFSEL_Sens((model_Sens_335_805)?(3960):(3750),	(3750),	0,	0,	0,	0,	0,	0,	0,	0)
#define MODE_RDES_VTW_5M_20_LWDR	DFSEL_Sens((model_Sens_335_805)?(1875):(1980),	(1980),	0,	0,	0,	0,	0,	0,	0,	0)
                                                         
#define MODE_RDES_HTW_5M_125_LWDR	DFSEL_Sens((model_Sens_335_805)?(3000):(MODE_HDT_125(2970,3000)),	0,	0,	0,	0,	0,	0,	0,	0,	0)
#define MODE_RDES_VTW_5M_125_LWDR	DFSEL_Sens((model_Sens_335_805)?(1980):(MODE_HDT_125(2000,1980)),	0,	0,	0,	0,	0,	0,	0,	0,	0)

#define MODE_RDES_HTW_5M_25_LWDR	DFSEL_Sens((model_Sens_335_805)?(3000):(3000),	(3000),	0,	0,	0,	0,	0,	0,	0,	0)
#define MODE_RDES_VTW_5M_25_LWDR	DFSEL_Sens((model_Sens_335_805)?(1980):(1980),	(1980),	0,	0,	0,	0,	0,	0,	0,	0)

#endif
//4M,5M END==================================================================================================
#endif

//ACTIVE WIDTH
#define	MODE_ACT_H_1M				(1280)
#define MODE_ACT_V_1M				( 720)

#define MODE_ACT_H_2M				(1920)		//0x790
#define MODE_ACT_V_2M				(1080)		//0x440

#define MODE_ACT_H_4M				(2560)		//0xa10
#define MODE_ACT_V_4M				(1440)		//0x5b0

#define MODE_ACT_H_5M				((MODE_5M_25_ON)?(2560):(2592))		//0xa30
#define MODE_ACT_V_5M				((MODE_5M_25_ON)?(1920):(1944))		//0x7a8

// ======================================================================================================================
// OutMode
// ======================================================================================================================

#define   model_Stndrd_Output  1

#define MODE_OUT_HTW_1M_60HZ		((model_Stndrd_Output)?(1650):(1500))
#define MODE_OUT_HTW_1M_50HZ		((model_Stndrd_Output)?(1980):(1800))
#define	MODE_OUT_VTW_1M				((model_Stndrd_Output)?( 750):( 825))


#define MODE_OUT_HTW_2M_60HZ		((model_Stndrd_Output)?(2200):(1980))
#define MODE_OUT_HTW_2M_50HZ		((model_Stndrd_Output)?(2640):(2376))

#define MODE_OUT_HTW_2M_275_60HZ	2400

#if(model_fps_2904)
#define	MODE_OUT_VTW_2M				((model_Stndrd_Output)?(1162):(1250))
#else
#define	MODE_OUT_VTW_2M				((model_Stndrd_Output)?(1125):(1250))
#endif
      

#define MODE_OUT_HTW_4M_60HZ		((model_Stndrd_Output)?(3300):(3000))
#define MODE_OUT_HTW_4M_50HZ		((model_Stndrd_Output)?(3960):(3600))
#define MODE_OUT_VTW_4M				((model_Stndrd_Output)?(1500):(1650))
                                                                        
#define MODE_OUT_HTW_5M_20HZ		((model_Stndrd_Output)?(3750):(3960))
#define MODE_OUT_VTW_5M_20HZ		((model_Stndrd_Output)?(1980):(1875))
                                                                        
#define MODE_OUT_HTW_5M_12_5HZ		((model_Stndrd_Output)?(MODE_HDT_125(2970,3000)):(3000))
#define MODE_OUT_VTW_5M_12_5HZ		((model_Stndrd_Output)?(MODE_HDT_125(2000,1980)):(1980))

#define MODE_OUT_HTW_5M_25HZ		(3000)
#define MODE_OUT_VTW_5M_25HZ		(1980)

// ======================================================================================================================
// Mode Macro
// ======================================================================================================================

#define MODE_SYSFREQ(A,B)			((MP(MpSysFreq)==MN_SYSFREQ_60)?(A):(B))
#define MODE_HDT_125(T,CA)			((MODE_T_5M125P_ON)?(T):(CA))
#define MODE_LWDR(A,B)				((gbModeWdrOn_L)?(B):(A))

	
//*********************
//EX-SDI
//*********************
	#define MODE_EXSDI_COND 		((!model_Dout))

	//for confirm mode
	#define MODE_EXSDI_COND_CF 		((!model_Dout))

#if (model_ExSdiSel==0)
	#define MODE_EXSDI_ON			0																								// no use EX-SDI
#elif (model_ExSdiSel==1)
	#define MODE_EXSDI_ON			(MODE_EXSDI_COND&&(MP(MpSdiForm)!=MN_SDI_OFF)&&(!GpioGetPin(GPIO_EXSDI_SEL)))					// EX-SDI selection by physical Switch
#elif (model_ExSdiSel==2)
	#define MODE_EXSDI_ON			(MODE_EXSDI_COND&&(MP(MpSdiForm)!=MN_SDI_OFF)&&(MP(MpSdiMode)==MN_EXSDI))						// EX-SDI selection by sequencial Menu key
#endif

	//for mode change
	#define MODE_EXSDI_1P5G_BASE	((MP(MpSdiForm)==MN_EXSDI_270M) ? 0 : 1)														// 1.5G BASE 270M or 135M+
	#define MODE_EXSDI_3G_BASE		((model_2M&&((MP(MpOutFps)==MN_2M_1080p_50_60)||(MP(MpOutFps)==MN_2M_1440p_25_30)||(MP(MpOutFps)==MN_2M_1944p_125)||(MP(MpOutFps)==MN_2M_1944p_20)))||\
									 (model_5M&&((MP(MpOutFps)==MN_4M_1440p_25_30)||(MP(MpOutFps)==MN_5M_1944p_125)||(MP(MpOutFps)==MN_5M_1944p_20))))		// 3G BASE 270M
	
//*********************
//HD-SDI
//*********************
	#define MODE_HDSDI_COND			((!model_Dout)&&\
									(!(model_2M&&((MP(MpOutFps)==MN_2M_1440p_25_30)||(MP(MpOutFps)==MN_2M_1944p_125)||(MP(MpOutFps)==MN_2M_1944p_20))))&&\
									(!(model_5M&&((MP(MpOutFps)==MN_4M_1440p_25_30)||(MP(MpOutFps)==MN_5M_1944p_125)||(MP(MpOutFps)==MN_5M_1944p_20)))))


	//for confirm mode
	#define MODE_HDSDI_COND_CF		((!model_Dout)&&\
									(!(model_2M&&((gbModeBufOutFps==MN_2M_1440p_25_30)||(gbModeBufOutFps==MN_2M_1944p_125)||(gbModeBufOutFps==MN_2M_1944p_20))))&&\
									(!(model_5M&&((gbModeBufOutFps==MN_4M_1440p_25_30)||(gbModeBufOutFps==MN_5M_1944p_125)||(gbModeBufOutFps==MN_5M_1944p_20)))))

#if (model_ExSdiSel==0)
	#define MODE_HDSDI_ON			0
#elif (model_ExSdiSel==1)
	#define MODE_HDSDI_ON			(MODE_HDSDI_COND&&(MP(MpSdiForm)!=MN_SDI_OFF)&&(GpioGetPin(GPIO_EXSDI_SEL)))
#elif (model_ExSdiSel==2)
	#define MODE_HDSDI_ON			(MODE_HDSDI_COND&&(MP(MpSdiForm)!=MN_SDI_OFF)&&(MP(MpSdiMode)==MN_HDSDI))
#endif

	#define MODE_SDI_3G_BASE		((model_2M)&&(MP(MpOutFps)==MN_2M_1080p_50_60))
	#define MODE_SDI_OFF			((!MODE_EXSDI_ON)&&(!MODE_HDSDI_ON))
	#define MODE_SDI_STATUS			(MODE_EXSDI_ON ? 2 : MODE_HDSDI_ON ? 1 : 0)			// 0 : SDI OFF, 1 : HDSDI, 2 : EXSDI

	//for Menu
	#define MODE_3G_BASE_MENU		(((model_2M)&&((gbModeBufOutFps==MN_2M_1080p_50_60)||(gbModeBufOutFps==MN_2M_1440p_25_30)||(gbModeBufOutFps==MN_2M_1944p_125)||(gbModeBufOutFps==MN_2M_1944p_20)))||\
									 ((model_5M)&&((gbModeBufOutFps==MN_4M_1440p_25_30)||(gbModeBufOutFps==MN_5M_1944p_125)||(gbModeBufOutFps==MN_5M_1944p_20))))		// 3G BASE 270M


	//*********************
	//--HD-Analog --
	//*********************
	#define MODE_HDANL_COND			((model_Aout==1)&&(MP(MpAnlMode)==MN_HDANALOG_ON)&&((MP(MpAnlForm)==MN_HD_T)||(MP(MpAnlForm)==MN_HD_C)||(MP(MpAnlForm)==MN_HD_A)))

#if (model_HdAnSel==0)
	#define MODE_HDANL_ON			0
#elif (model_HdAnSel==1)
	#define MODE_HDANL_ON			(MODE_HDANL_COND/*&&(!GpioGetPin(GPIO_HDAN_SEL)*/)
#elif (model_HdAnSel==2)
	#define MODE_HDANL_ON			(MODE_HDANL_COND&&(MP(MpAnlMode)==MN_HDANALOG_ON))
#endif

	#define MODE_5M_125_ON_MENU		((MODE_HDANL_ON)&&(((model_2M)&&(gbModeBufOutFps==MN_2M_1944p_125))||((model_5M)&&(gbModeBufOutFps==MN_5M_1944p_125))))							   
	#define MODE_5M_125_ON			((MODE_HDANL_ON)&&(((model_2M)&&(MP(MpOutFps)==MN_2M_1944p_125))||((model_5M)&&(MP(MpOutFps)==MN_5M_1944p_125))))
	#define MODE_A_5M125P_ON 		((MODE_5M_125_ON)&&(MP(MpAnlForm)==MN_HD_A))
	#define MODE_T_5M125P_ON 		((MODE_5M_125_ON)&&(MP(MpAnlForm)==MN_HD_T))

	#define MODE_5M_20_ON_MENU		((MODE_HDANL_ON)&&(((model_2M)&&(gbModeBufOutFps==MN_2M_1944p_20))||((model_5M)&&(gbModeBufOutFps==MN_5M_1944p_20))))
	#define MODE_5M_20_ON			((MODE_HDANL_ON)&&(((model_2M)&&(MP(MpOutFps)==MN_2M_1944p_20))||((model_5M)&&(MP(MpOutFps)==MN_5M_1944p_20))))

	// #define MODE_5M_25_ON_MENU		((model_5M)&&(gbModeBufOutFps==MN_5M_1920p_25))
	// #define MODE_5M_25_ON			((model_5M)&&(MP(MpOutFps)==MN_5M_1920p_25))
	
	#define	MODE_C_MENU				((MODE_HDANL_ON)&&(gbModeBufAnlForm==MN_HD_C))
	//*********************
	//--CVBS --
	//*********************
	
#if (model_CvbsAdc==1)
	extern  BYTE  gbCvbsAuto;		// 200130 PCB : CVBS Auto Detection	
	#define MODE_CVBS_ON			((!MODE_HDANL_ON)&&(model_Aout!=2)&&(MP(MpAnlForm)!=MN_ANL_OFF)&&gbCvbsAuto)   // "						// CVBS ON by ADC
#else
	#define MODE_CVBS_ON			((!MODE_HDANL_ON)&&(model_Aout!=2)&&(MP(MpAnlForm)!=MN_ANL_OFF))										// 180823 LGH
#endif
	// CVBS
	#define	MODE_DISABLE_CVBS		((model_2M)&&(model_Sens_LWdr_Low && gbModeWdrOn_L))
	#define MODE_MENU_CVBS_OFF		(!(gbModeBufAnlForm==MN_CVBS))
	#define	MODE_CVBS_FULL			((MODE_CVBS_ON)&&((model_Sens==SENS_IMX290)||(model_Sens==SENS_IMX327)||(model_Sens==SENS_IMX307)||(model_Sens==SENS_IMX462)))				// CVBS PAL : Full downscale mode

	#define MODE_ANL_OFF			((!MODE_HDANL_ON)&&(!MODE_CVBS_ON))
	#define MODE_ANL_STATUS			(MODE_HDANL_ON ? 2 : MODE_CVBS_ON ? 1 : 0)				// 0 : Analog OFF, 1 : CVBS, 2 : HD-Analog
	#define	MODE_CHG_DLY			(1)

	#define MODE_CVBS_OUT_FPS		((model_2M)?(MN_2M_1080p_50_60):(MN_1M_720p_50_60))
	//*********************
	//-- Scale Mode --
	//*********************
	#define MODE_DS_ON				(((model_2M)&&((MP(MpOutFps)==MN_2M_720p_25_30)||(MP(MpOutFps)==MN_2M_720p_50_60)))||\
									((model_5M)&&((MP(MpOutFps)==MN_4M_720p_25_30)||(MP(MpOutFps)==MN_4M_1080p_25_30))))			//Downscale Mode ON

	#define MODE_US_ON				((model_2M)&&((MP(MpOutFps)==MN_2M_1440p_25_30)||(MP(MpOutFps)==MN_2M_1944p_125)||(MP(MpOutFps)==MN_2M_1944p_20)))		//Upscale Mode ON


	#define MODE_1M_ON				(((model_1M)&&((MP(MpOutFps)==MN_1M_720p_25_30)||(MP(MpOutFps)==MN_1M_720p_50_60)))||\
									((model_2M)&&((MP(MpOutFps)==MN_2M_720p_25_30)||(MP(MpOutFps)==MN_2M_720p_50_60)))||\
									((model_5M)&&(MP(MpOutFps)==MN_4M_720p_25_30)))
									
	#define MODE_2M_ON				(((model_2M)&&((MP(MpOutFps)==MN_2M_1080p_25_30)||(MP(MpOutFps)==MN_2M_1080p_50_60)))||\
									((model_5M)&&(MP(MpOutFps)==MN_4M_1080p_25_30)))
									
	#define MODE_4M_ON				(((model_2M)&&(MP(MpOutFps)==MN_2M_1440p_25_30))||\
									((model_5M)&&(MP(MpOutFps)==MN_4M_1440p_25_30)))
									
	#define MODE_5M_ON				(((model_2M)&&((MP(MpOutFps)==MN_2M_1944p_125)||(MP(MpOutFps)==MN_2M_1944p_20)))||\
									 ((model_5M)&&((MP(MpOutFps)==MN_5M_1944p_125)||(MP(MpOutFps)==MN_5M_1944p_20))))

	#define	MODE_VAL(CVBS,_1M,_2M,_4M,_5M)	((MODE_CVBS_ON)?(CVBS):(MODE_1M_ON)?(_1M):(MODE_2M_ON)?(_2M):(MODE_4M_ON)?(_4M):(_5M))
	
	// Mode Pre side 148.5MHz -----------------------------------------
	#define	MODE_PRE_HIGH			(((model_2M)&&((MP(MpOutFps)==MN_2M_720p_50_60)||(MP(MpOutFps)==MN_2M_1080p_50_60)))||\
									((model_5M)&&((MP(MpOutFps)==MN_4M_720p_25_30)||(MP(MpOutFps)==MN_4M_1080p_25_30)||(MP(MpOutFps)==MN_4M_1440p_25_30)||(MP(MpOutFps)==MN_5M_1944p_20))))

	// Mode WDR	 -----------------------------------------
	// WDR 
	#define MODE_WDR_ON				((gbModeWdrOn_L)||(gbModeWdrOn_CLR))
//	#define	MODE_DISABLE_WDR		((MODE_CVBS_ON)&&((model_Sens_NonWdr)||((model_Sens_LWdr_Low)&&((model_2M)&&((MP(MpOutFps)==MN_2M_720p_50_60)||(MP(MpOutFps)==MN_2M_1080p_50_60))))))
	#define MODE_DISABLE_WDR		((model_Sens_NonWdr)||((model_Sens_LWdr_Low)&&(((model_2M)&&((MP(MpOutFps)==MN_2M_720p_50_60)/*||(MP(MpOutFps)==MN_2M_1080p_50_60)*/))||(MODE_CVBS_ON))))

	#define MODE_OUTPUT_SET_FUNC	((MODE_CVBS_ON)||((model_2M)&&(MODE_5M_ON)))
	
	// Mode status tx string
	#define MODE_TXSTR				TxStr("Mode Change_",\
									((MODE_SDI_STATUS<<28)|(((MODE_EXSDI_ON)?MP(MpSdiForm):MP(MpSdiMode))<<24)|\
									(MODE_ANL_STATUS<<20)|(MP(MpAnlForm)<<16)|\
									(MP(MpSysFreq)<<8)|MP(MpOutFps)),  8);

//*********************
// MIPI
//*********************
	#define MIPI_FN_INC				((model_Isp_pkg56)&&(model_Mipiout==1)&&(MIPI_FN_INC_MODE))

	#define POWER_ON_HDANA    	{ECK_PDw(0); ENC_ONw(1); DAC_PD_INw(0); DPLL_Sw(1);}
	#define POWER_OFF_HDANA    	{ECK_PDw(1); ENC_ONw(0); DAC_PD_INw(1); DPLL_Sw(0);}


	#define POWER_ON_CVBS      	{ECK_PDw(0); ENC_ONw(1); DAC_PD_INw(0); DPLL_Sw(1);\
								SMCKO_SELw((MP(MpSysFreq)==MN_SYSFREQ_60)?(0x1):(0x0));\
								FPCK_SELw((MP(MpSysFreq)==MN_SYSFREQ_60)?(0x1):(0x0));}

	#define POWER_OFF_CVBS      {ECK_PDw(1); ENC_ONw(0); DAC_PD_INw(1); DPLL_Sw(0);}

extern void ISPM2 ModeChangeACP(void);

enum{
	NIGHT_NOR_CLEAR_OFF,	// 0
	NIGHT_HDR_CLEAR_OFF,	// 1
	NIGHT_NOR_CLEAR_ON ,		// 2
	NIGHT_HDR_CLEAR_ON ,		// 3
};

enum{
	HDR_OFF,
	HDR_ON
};

enum{
	FRONT_CAM,
	REAR_CAM
};

enum{
	FPS_30,
	FPS_60
};

#define	MODEL_NORMAL		((gbNightMode==NIGHT_NOR_CLEAR_OFF)&&(gbHDRMode==HDR_OFF))
#define	MODEL_NC			((gbNightMode==NIGHT_NOR_CLEAR_ON )&&(gbHDRMode==HDR_OFF))
#define	MODEL_HDR			((gbNightMode==NIGHT_HDR_CLEAR_OFF)&&(gbHDRMode==HDR_ON ))
#define	MODEL_HDRNC			((gbNightMode==NIGHT_HDR_CLEAR_ON )&&(gbHDRMode==HDR_ON ))

#define MODE_IQ_VAL(N, HDR, NC, HDR_NC)	((MODEL_NORMAL)?(N):\
										 (MODEL_HDR   )?(HDR):\
										 (MODEL_NC    )?(NC):(HDR_NC))

