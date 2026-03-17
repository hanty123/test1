/* **************************************************************************
 File Name	: 	app_para.h
 Description:	EN772 - User Parameter
 Designer	:	Lee, Gyu Hong
 Date		:	20. 12. 15
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

//******************************************************
// User Parameter variable
//------------------------------------------------------
#define USR_PAR_EA				(1024)				// Byte total (max 4K-4)
#define UP_END					(USR_PAR_EA-1)

#if (model_Par == 1)
#define UP_DATA_ID				(gDataID)			// User Parameter Reset if Program is compiled new.
#endif

extern void UsrParReset(void); 
extern void UsrDataReset(void);
extern void UsrParSet(const int aiAddr, const int aiInit);
extern void UsrParSetChgVal(void);

extern BYTE gbUsrParSaveChk;
extern BYTE gbUsrParReadChk;
extern BYTE gbUsrParTbl[USR_PAR_EA];

extern BYTE gbEncParInit;

//******************************************************
// User Parameter Macro
//------------------------------------------------------
#ifndef __LIB__

#if (model_Par==0)
	#define		ParSet(N,D)
	#define		UP(N)			(N)
	
#else
	#define 	ParSet0(N,D)	{if(N##_SIZ==4) 	{ gbUsrParTbl[N##_IDX] = (BYTE)(D); gbUsrParTbl[N##_IDX+1] = (BYTE)((D)>>8); gbUsrParTbl[N##_IDX+2] = (BYTE)((D)>>16); gbUsrParTbl[N##_IDX+3] = (BYTE)((D)>>24); }\
								else if(N##_SIZ==3) { gbUsrParTbl[N##_IDX] = (BYTE)(D); gbUsrParTbl[N##_IDX+1] = (BYTE)((D)>>8); gbUsrParTbl[N##_IDX+2] = (BYTE)((D)>>16); }\
								else if(N##_SIZ==2) { gbUsrParTbl[N##_IDX] = (BYTE)(D); gbUsrParTbl[N##_IDX+1] = (BYTE)((D)>>8); }\
								else                { gbUsrParTbl[N##_IDX] = (BYTE)(D); } }

	#define		ParSet(N,D)		ParSet0(N##_,D)

	#define		UP0(N)			((N##_SIZ==4) ? gbUsrParTbl[N##_IDX] | (gbUsrParTbl[N##_IDX+1]<<8) | (gbUsrParTbl[N##_IDX+2]<<16) | (gbUsrParTbl[N##_IDX+3]<<24) :\
								 (N##_SIZ==3) ? gbUsrParTbl[N##_IDX] | (gbUsrParTbl[N##_IDX+1]<<8) | (gbUsrParTbl[N##_IDX+2]<<16) :\
								 (N##_SIZ==2) ? gbUsrParTbl[N##_IDX] | (gbUsrParTbl[N##_IDX+1]<<8) :\
								                gbUsrParTbl[N##_IDX] )

	#define		UP(N)			UP0(N##_)

	#define		UP_ADDR_S(N)	(N##_##_IDX)
	#define		UP_ADDR_E(N)	(N##_##_IDX+N##_##_SIZ-1)

#endif

	#define		xUP(N)			(N)

#endif//__LIB__


#if (model_Par==0)
#define USR_PAR_LIST
enum {
	UP_START=0,
	UP_END_REAL
};

#define	USR_PAR_READ_CHK_ALL

#else

#define PAR_LIST1(N,...)	N##_##_IDX __VA_ARGS__,
#define PAR_LIST2(N,...)	PAR_LIST1(N,__VA_ARGS__) N##_##1_IDX,
#define PAR_LIST3(N,...)	PAR_LIST2(N,__VA_ARGS__) N##_##2_IDX,
#define PAR_LIST4(N,...)	PAR_LIST3(N,__VA_ARGS__) N##_##3_IDX,

#define UP_SET(S,N,...)		PAR_LIST##S(N,__VA_ARGS__)

#include "app_para_tbl.h"
enum {
	UP_START=0,
	UP_FLAG,
	USR_PAR_LIST
	UP_END_REAL
};

#undef UP_SET
#define UP_SET(S,N,...)		enum { N##_##_SIZ = S };
#include "app_para_tbl.h"
USR_PAR_LIST

#define	USR_PAR_READ_CHK_ALL	{gbEncParInit = 1;}

#endif

//******************************************************
// User parameter define
//------------------------------------------------------
/* SYSTEM */
#define UpLVDS_CKDLY			(LVDS_CKDLYr)
#define UpLDIDLY0				(LDIDLY0r   )
#define UpLDIDLY1				(LDIDLY1r   )
#define UpLDIDLY2				(LDIDLY2r   )
#define UpLDIDLY3				(LDIDLY3r   )

/* KEY */
#define UpADC_LEVEL_C 			(ADC_LEVEL_C)		// AD value at Push
#define UpADC_LEVEL_U 			(ADC_LEVEL_U)		// "
#define UpADC_LEVEL_D 			(ADC_LEVEL_D)		// "
#define UpADC_LEVEL_L 			(ADC_LEVEL_L)		// "
#define UpADC_LEVEL_R 			(ADC_LEVEL_R)		// "
#define	UpAD_CHT_BIT			(AD_CHT_BIT )		// Chattering bit field

/* TDN */
#define UpTDN_EXTN_THRS_STEP	(51	)																											//210225 YTM

#define UpTDN_AUTO_THRS_STEP	(28			)		//TDN auto mode threshold menu step		(1~100 AGC)
#define UpTDN_DLY_LOW			(1		)		//TDN low delay time	(1000->1s, 2000->2s,....,20000->20s)									//210225 YTM
#define UpTDN_DLY_MIDDLE		(5		)		//TDN middle delay time	(1000->1s, 2000->2s,....,20000->20s)									//210225 YTM
#define UpTDN_DLY_HIGH			(20		)		//TDN high delay time	(1000->1s, 2000->2s,....,20000->20s)									//210225 YTM

/* AE */
#define UpAE2_HSP				(AE2_HSP)
#define UpAE2_HEP				(AE2_HEP)
#define UpAE2_VSP				(AE2_VSP)
#define UpAE2_VEP				(AE2_VEP)	

#define UpAE_SHT_SLICE_LINE		(AE_SHT_SLICE_LINE)	
#define UpAE_OUTDOOR_THRS_VAL	(AE_OUTDOOR_THRS_VAL)
#define UpAE_DEBLUR_THRS_VAL	(AE_DEBLUR_THRS_VAL)
#define UpAE_SPEED_DC			(AE_SPEED_DC)		// Speed : 0 ~ 3 (Low ~ Fast)

#define	UpAE_TGT_GAIN			(AE_TGT_GAIN )		// Normal Brightness target gain
#define	UpAE_TGT_OFST			(AE_TGT_OFST )		// Normal Brightness target offset
#define	UpAE_SLIC_OFST			(AE_SLIC_OFST)		// Normal Brightness Slice  level (- Target offset)
#define	UpAE_CLIP_OFST			(AE_CLIP_OFST)		// Normal Brightness Clip level (+ Target offset)

#define UpAE_TGT_DCRS_AGC_PT0	(AE_TGT_DCRS_AGC_PT0)
#define UpAE_TGT_DCRS_AGC_PT1	(AE_TGT_DCRS_AGC_PT1)
#define UpAE_TGT_DCRS_AGC_PT2	(AE_TGT_DCRS_AGC_PT2)

#define UpAE_TGT_DCRS_VAL_PT0	(AE_TGT_DCRS_VAL_PT0)
#define UpAE_TGT_DCRS_VAL_PT1	(AE_TGT_DCRS_VAL_PT1)
#define UpAE_TGT_DCRS_VAL_PT2	(AE_TGT_DCRS_VAL_PT2)

#define UpAE_CLP_AGC_PT0		(AE_CLP_AGC_PT0)
#define UpAE_CLP_AGC_PT1		(AE_CLP_AGC_PT1)
#define UpAE_CLP_AGC_PT2		(AE_CLP_AGC_PT2)

#define UpAE_CLP_VAL_PT0		(AE_CLP_VAL_PT0)
#define UpAE_CLP_VAL_PT1		(AE_CLP_VAL_PT1)
#define UpAE_CLP_VAL_PT2		(AE_CLP_VAL_PT2)

#define	UpAE_SPEED				(AE_SPEED	 )		// Tracking Speed : 0 ~ 128 ~ 255 (x0.25 ~ x1 ~ x4)
#define	UpAE_DEBLUR_GAIN		(AE_DEBLUR_GAIN)	// Deblur shutter increasing gradient	 (line)	// 64 ~ 256 -> 0.5 ~ 2.0

#define UpAE_BLK_LVL_AGC_PT0	(AE_BLK_LVL_AGC_PT0)
#define UpAE_BLK_LVL_AGC_PT1	(AE_BLK_LVL_AGC_PT1)
#define UpAE_BLK_LVL_AGC_PT2	(AE_BLK_LVL_AGC_PT2)

#define	UpAE_BLK_LVL_VAL_PT0	(AE_BLK_LVL_VAL_PT0)
#define	UpAE_BLK_LVL_VAL_PT1	(AE_BLK_LVL_VAL_PT1)
#define	UpAE_BLK_LVL_VAL_PT2	(AE_BLK_LVL_VAL_PT2)

#define UpAE_SENS_AGC_LMT		(AE_SENS_AGC_LMT)

// AE-WDR
#define	UpAE_WDR_LTGT_GAIN		(AE_WDR_LTGT_GAIN)
#define	UpAE_WDR_LTGT_OFST		(AE_WDR_LTGT_OFST)
#define UpAE_WDR_LSLIC_OFST		(AE_WDR_LSLIC_OFST)
#define UpAE_WDR_LCLIP_OFST		(AE_WDR_LCLIP_OFST)

#define	UpAE_WDR_STGT_GAIN		(AE_WDR_STGT_GAIN)
#define	UpAE_WDR_STGT_OFST		(AE_WDR_STGT_OFST)
#define UpAE_WDR_SSLIC_OFST		(AE_WDR_SSLIC_OFST)
#define UpAE_WDR_SCLIP_OFST		(AE_WDR_SCLIP_OFST)

#define UpAE_WDR_LTGT_DCRS_AGC_PT0	(AE_WDR_LTGT_DCRS_AGC_PT0)
#define UpAE_WDR_LTGT_DCRS_AGC_PT1	(AE_WDR_LTGT_DCRS_AGC_PT1)
#define UpAE_WDR_LTGT_DCRS_AGC_PT2	(AE_WDR_LTGT_DCRS_AGC_PT2)

#define UpAE_WDR_LTGT_DCRS_VAL_PT0	(AE_WDR_LTGT_DCRS_VAL_PT0)
#define UpAE_WDR_LTGT_DCRS_VAL_PT1	(AE_WDR_LTGT_DCRS_VAL_PT1)
#define UpAE_WDR_LTGT_DCRS_VAL_PT2	(AE_WDR_LTGT_DCRS_VAL_PT2)

#define UpAE_WDR_CLP_AGC_PT0	(AE_WDR_CLP_AGC_PT0)
#define UpAE_WDR_CLP_AGC_PT1	(AE_WDR_CLP_AGC_PT1)
#define UpAE_WDR_CLP_AGC_PT2	(AE_WDR_CLP_AGC_PT2)

#define UpAE_WDR_CLP_VAL_PT0	(AE_WDR_CLP_VAL_PT0)
#define UpAE_WDR_CLP_VAL_PT1	(AE_WDR_CLP_VAL_PT1)
#define UpAE_WDR_CLP_VAL_PT2	(AE_WDR_CLP_VAL_PT2)

#define UpAE_WDR_SATLV_AGC_PT0	(AE_WDR_SATLV_AGC_PT0)
#define UpAE_WDR_SATLV_AGC_PT1	(AE_WDR_SATLV_AGC_PT1)

#define UpAE_WDR_SATLV_VAL_PT0	(AE_WDR_SATLV_VAL_PT0)
#define UpAE_WDR_SATLV_VAL_PT1	(AE_WDR_SATLV_VAL_PT1)

#define UpAE_WDR_LS_WGT_AGC_PT0	(AE_WDR_LS_WGT_AGC_PT0)
#define UpAE_WDR_LS_WGT_AGC_PT1	(AE_WDR_LS_WGT_AGC_PT1)

#define UpAE_WDR_LS_WGT_VAL0	(AE_WDR_LS_WGT_VAL0)
#define UpAE_WDR_LS_WGT_VAL1	(AE_WDR_LS_WGT_VAL1)

#define UpAE_WDR_LONG_TH_OFST1	(AE_WDR_LONG_TH_OFST1)
#define UpAE_WDR_LONG_TH_OFST2	(AE_WDR_LONG_TH_OFST2)

#define UpAE_WDR_LONG_MIN 		(AE_WDR_LONG_MIN)	
#define UpAE_WDR_SHORT_MIN		(AE_WDR_SHORT_MIN1)

#define UpAE_WDR_SENS_AGC_LMT	(AE_SENS_WDR_AGC_LMT)
#define UpAE_WDR_TMG_SEL		(AE_WDR_TMG_SEL)

/* AWB */
#define UpAWB_HSP				(AWB_HSP	)
#define UpAWB_HW				(AWB_HW	    )
#define UpAWB_VSP				(AWB_VSP	)
#define UpAWB_VW				(AWB_VW	    )			

#define UpAWB_TCNT_LMT			(AWB_TCNT_LMT)

#define	UpAWB_DBOFFSET			(AWB_DBOFFSET)
#define	UpAWB_DROFFSET          (AWB_DROFFSET)

#define UpAWB_AGC_MIN			(AWB_AGC_MIN    )
#define UpAWB_AGC_MAX           (AWB_AGC_MAX    )
#define UpAWB_WDR_AGC_MIN		(AWB_WDR_AGC_MIN)
#define UpAWB_WDR_AGC_MAX       (AWB_WDR_AGC_MAX)
#define UpAWB_AGC_WGT_MIN       (AWB_AGC_WGT_MIN)
#define	UpAWB_SPEED_MTRX        (AWB_SPEED_MTRX )

#define UpAWB_YSLICE			(AWB_YSLICE)
#define UpAWB_YCLIP             (AWB_YCLIP )

#define UpAWB_GAIN_TIMES		(AWB_GAIN_TIMES)

#define UpAWB_TEMP_DR_L			(AWB_TEMP_DR_L)
#define UpAWB_TEMP_DR_M			(AWB_TEMP_DR_M)
#define UpAWB_TEMP_DR_H			(AWB_TEMP_DR_H)

#define UpAWB_TEMP_VAL_L		(AWB_TEMP_VAL_L)
#define UpAWB_TEMP_VAL_M		(AWB_TEMP_VAL_M)
#define UpAWB_TEMP_VAL_H		(AWB_TEMP_VAL_H)

#define	UpAWB_R_WGT				(0x100)
#define UpAWB_G_WGT				(0x100)
#define UpAWB_B_WGT				(0x100)

// Color Temp
#define UpCCM_TEMP_L			(CCM_TEMP_L)
#define UpCCM_TEMP_M			(CCM_TEMP_M)
#define UpCCM_TEMP_H			(CCM_TEMP_H )

// LOW_TEMP
#define	UpCCM_RR_TEMP_L			(CCM_RR_TEMP_L)
#define UpCCM_RG_TEMP_L			(CCM_RG_TEMP_L)
#define UpCCM_RB_TEMP_L			(CCM_RB_TEMP_L)
#define	UpCCM_GR_TEMP_L			(CCM_GR_TEMP_L)
#define UpCCM_GG_TEMP_L			(CCM_GG_TEMP_L)
#define UpCCM_GB_TEMP_L			(CCM_GB_TEMP_L)
#define	UpCCM_BR_TEMP_L			(CCM_BR_TEMP_L)
#define UpCCM_BG_TEMP_L			(CCM_BG_TEMP_L)
#define UpCCM_BB_TEMP_L			(CCM_BB_TEMP_L)

// MID_TEMP
#define	UpCCM_RR_TEMP_M			(CCM_RR_TEMP_M)
#define UpCCM_RG_TEMP_M			(CCM_RG_TEMP_M)
#define UpCCM_RB_TEMP_M			(CCM_RB_TEMP_M)
#define	UpCCM_GR_TEMP_M			(CCM_GR_TEMP_M)
#define UpCCM_GG_TEMP_M			(CCM_GG_TEMP_M)
#define UpCCM_GB_TEMP_M			(CCM_GB_TEMP_M)
#define	UpCCM_BR_TEMP_M			(CCM_BR_TEMP_M)
#define UpCCM_BG_TEMP_M			(CCM_BG_TEMP_M)
#define UpCCM_BB_TEMP_M			(CCM_BB_TEMP_M)

// HI_TEMP
#define	UpCCM_RR_TEMP_H			(CCM_RR_TEMP_H)
#define UpCCM_RG_TEMP_H			(CCM_RG_TEMP_H)
#define UpCCM_RB_TEMP_H			(CCM_RB_TEMP_H)
#define	UpCCM_GR_TEMP_H			(CCM_GR_TEMP_H)
#define UpCCM_GG_TEMP_H			(CCM_GG_TEMP_H)
#define UpCCM_GB_TEMP_H			(CCM_GB_TEMP_H)
#define	UpCCM_BR_TEMP_H			(CCM_BR_TEMP_H)
#define UpCCM_BG_TEMP_H			(CCM_BG_TEMP_H)
#define UpCCM_BB_TEMP_H			(CCM_BB_TEMP_H)

#define	UpAWB_5000K_AGC_TH		(AWB_5000K_AGC_TH)

#define UpAWB_SLIC_OFST_PT0		(AWB_SLIC_OFST_PT0 )
#define UpAWB_SLIC_OFST_PT1		(AWB_SLIC_OFST_PT1 )
#define UpAWB_SLIC_OFST_PT2		(AWB_SLIC_OFST_PT2 )
#define UpAWB_SLIC_OFST_VAL0	(AWB_SLIC_OFST_VAL0)
#define UpAWB_SLIC_OFST_VAL1	(AWB_SLIC_OFST_VAL1)
#define UpAWB_SLIC_OFST_VAL2	(AWB_SLIC_OFST_VAL2)

/* COLOR SUPPRESSION */
#define UpLSUP_ON				(0x0 ) //(0x0 )
//#define	UpLSUP_GA				(0x3F) //(0x80)
#define UpLSUP_GA_AGC_PT0		(LSUP_GA_AGC_PT0)
#define UpLSUP_GA_AGC_PT1       (LSUP_GA_AGC_PT1)
#define UpLSUP_GA_VAL_PT0       (LSUP_GA_VAL_PT0)
#define UpLSUP_GA_VAL_PT1       (LSUP_GA_VAL_PT1)
#define	UpLSUP_TH				(0x1 )
                    			
#define UpCSUP_ON				(0x1 )
#define	UpCSUP_GA				(0x10)
//#define UpCSUP_TH				(CSUP_TH)
#define UpCSUP_TH_AGC_PT0		(CSUP_TH_AGC_PT0)
#define UpCSUP_TH_AGC_PT1       (CSUP_TH_AGC_PT1)
#define UpCSUP_TH_VAL_PT0       (CSUP_TH_VAL_PT0)
#define UpCSUP_TH_VAL_PT1       (CSUP_TH_VAL_PT1)


#define UpCES_ON				(0x1 )
#define UpCES_GA				(0x10)
//#define UpCES_LCLIP				(0x14)
#define UpCES_TH_AGC_PT0		(CES_TH_AGC_PT0)
#define UpCES_TH_AGC_PT1        (CES_TH_AGC_PT1)
#define UpCES_TH_VAL_PT0        (CES_TH_VAL_PT0)
#define UpCES_TH_VAL_PT1        (CES_TH_VAL_PT1)


/* HUE & GAIN*/	
// Color Temp
#define UpHnG_TEMP_L			(HnG_TEMP_L)
#define UpHnG_TEMP_M			(HnG_TEMP_M)
#define UpHnG_TEMP_H			(HnG_TEMP_H)

// LOW_TEMP
#define UpBY_GAINN_TEMP_L		(BY_GAINN_TEMP_L)
#define UpBY_GAINP_TEMP_L     	(BY_GAINP_TEMP_L)
#define UpRY_GAINN_TEMP_L     	(RY_GAINN_TEMP_L)
#define UpRY_GAINP_TEMP_L     	(RY_GAINP_TEMP_L)
                        		
#define UpBY_HUEN_TEMP_L		(BY_HUEN_TEMP_L)
#define UpBY_HUEP_TEMP_L	    (BY_HUEP_TEMP_L)
#define UpRY_HUEN_TEMP_L	    (RY_HUEN_TEMP_L)
#define UpRY_HUEP_TEMP_L	    (RY_HUEP_TEMP_L)

// MID_TEMP
#define UpBY_GAINN_TEMP_M		(BY_GAINN_TEMP_M)
#define UpBY_GAINP_TEMP_M      	(BY_GAINP_TEMP_M)
#define UpRY_GAINN_TEMP_M   	(RY_GAINN_TEMP_M)
#define UpRY_GAINP_TEMP_M     	(RY_GAINP_TEMP_M)
                        		
#define UpBY_HUEN_TEMP_M		(BY_HUEN_TEMP_M)
#define UpBY_HUEP_TEMP_M   		(BY_HUEP_TEMP_M)
#define UpRY_HUEN_TEMP_M   		(RY_HUEN_TEMP_M)
#define UpRY_HUEP_TEMP_M   		(RY_HUEP_TEMP_M)

// HIGH_TEMP
#define UpBY_GAINN_TEMP_H		(BY_GAINN_TEMP_H)
#define UpBY_GAINP_TEMP_H      	(BY_GAINP_TEMP_H)
#define UpRY_GAINN_TEMP_H      	(RY_GAINN_TEMP_H)
#define UpRY_GAINP_TEMP_H      	(RY_GAINP_TEMP_H)
                        		
#define UpBY_HUEN_TEMP_H		(BY_HUEN_TEMP_H)
#define UpBY_HUEP_TEMP_H	    (BY_HUEP_TEMP_H)
#define UpRY_HUEN_TEMP_H	    (RY_HUEN_TEMP_H)
#define UpRY_HUEP_TEMP_H	    (RY_HUEP_TEMP_H)

/* GAMMA*/
#define UpGAMMA_Y_ON			(0x1)				//Y GAMMA on/off	(0: off, 1: on)
#define UpGAMMA_C_ON			(0x1)				//C GAMMA on/off	(0: off, 1: on)
#define UpYGMA_AGC_PT0			(YGMA_AGC_PT0)
#define UpYGMA_AGC_PT1			(YGMA_AGC_PT1)
#define UpCGMA_AGC_PT0			(CGMA_AGC_PT0)
#define UpCGMA_AGC_PT1			(CGMA_AGC_PT1)

#define UpYGMA_WDR_AGC_PT0		(YGMA_WDR_AGC_PT0)
#define UpYGMA_WDR_AGC_PT1		(YGMA_WDR_AGC_PT1)
#define UpCGMA_WDR_AGC_PT0		(CGMA_WDR_AGC_PT0)
#define UpCGMA_WDR_AGC_PT1		(CGMA_WDR_AGC_PT1)

/* DNR */
#define UpDNR_AGC_PT0			(DNR_AGC_PT0)
#define	UpDNR_AGC_PT1			(DNR_AGC_PT1)
#define UpDNR_AGC_PT2			(DNR_AGC_PT2)

#define UpDNR_WDR_AGC_PT0		(DNR_WDR_AGC_PT0)	
#define UpDNR_WDR_AGC_PT1		(DNR_WDR_AGC_PT1)
#define UpDNR_WDR_AGC_PT2		(DNR_WDR_AGC_PT2)

#define UpDNR_AGC_OFST_PVAL0	(DNR_AGC_OFST_PVAL0)	
#define UpDNR_AGC_OFST_PVAL1	(DNR_AGC_OFST_PVAL1)
#define UpDNR_AGC_OFST_PVAL2	(DNR_AGC_OFST_PVAL2)

#define UpDNR_AGC_OFST_MVAL0	(DNR_AGC_OFST_MVAL0)	
#define UpDNR_AGC_OFST_MVAL1	(DNR_AGC_OFST_MVAL1)
#define UpDNR_AGC_OFST_MVAL2	(DNR_AGC_OFST_MVAL2)

#define UpDNR_AGC_HPF_PT0		(DNR_AGC_HPF_PT0)
#define UpDNR_AGC_HPF_PT1		(DNR_AGC_HPF_PT1)
#define UpDNR_AGC_HPF_PT2		(DNR_AGC_HPF_PT2)

#define	UpDNR_HPF_GAIN_LV0_PT0	(DNR_HPF_GAIN_LV0_PT0)
#define	UpDNR_HPF_GAIN_LV0_PT1	(DNR_HPF_GAIN_LV0_PT1)
#define	UpDNR_HPF_GAIN_LV0_PT2	(DNR_HPF_GAIN_LV0_PT2)

#define	UpDNR_HPF_GAIN_LV1_PT0	(DNR_HPF_GAIN_LV1_PT0)
#define	UpDNR_HPF_GAIN_LV1_PT1	(DNR_HPF_GAIN_LV1_PT1)
#define	UpDNR_HPF_GAIN_LV1_PT2	(DNR_HPF_GAIN_LV1_PT2)

#define	UpDNR_HPF_GAIN_LV2_PT0	(DNR_HPF_GAIN_LV2_PT0)
#define	UpDNR_HPF_GAIN_LV2_PT1	(DNR_HPF_GAIN_LV2_PT1)
#define	UpDNR_HPF_GAIN_LV2_PT2	(DNR_HPF_GAIN_LV2_PT2)

/* SHARPNESS */
#define	UpSHARPNESS_GAIN		(SHARPNESS_GAIN)
#define	UpSHARPNESS_GAIN_CVBS	(SHARPNESS_GAIN_CVBS)

#define UpSHP_AGC_PT0			(SHP_AGC_PT0)
#define	UpSHP_AGC_PT1			(SHP_AGC_PT1)
#define UpSHP_AGC_PT2			(SHP_AGC_PT2)

#define UpSHP_WDR_AGC_PT0		(SHP_WDR_AGC_PT0)	
#define UpSHP_WDR_AGC_PT1		(SHP_WDR_AGC_PT1)
#define UpSHP_WDR_AGC_PT2		(SHP_WDR_AGC_PT2)

#define UpAPT55_TH1_PT0			(APT55_TH1_PT0	)
#define UpAPT55_TH2_PT0			(APT55_TH2_PT0	)
#define UpAPT55_TH3_PT0			(APT55_TH3_PT0	)
#define UpAPT55_GAIN1N_PT0		(APT55_GAIN1N_PT0)
#define UpAPT55_GAIN2N_PT0		(APT55_GAIN2N_PT0)
#define UpAPT55_GAIN1P_PT0		(APT55_GAIN1P_PT0)
#define UpAPT55_GAIN2P_PT0		(APT55_GAIN2P_PT0)

#define UpAPT33_SLIC_PT0		(APT33_SLIC_PT0	)
#define UpAPT33_CLIP_PT0		(APT33_CLIP_PT0	)
#define UpAPT33_GAIN_PT0		(APT33_GAIN_PT0	)

#define UpAPT55_TH1_PT1			(APT55_TH1_PT1	)
#define UpAPT55_TH2_PT1			(APT55_TH2_PT1	)
#define UpAPT55_TH3_PT1			(APT55_TH3_PT1	)
#define UpAPT55_GAIN1N_PT1		(APT55_GAIN1N_PT1)
#define UpAPT55_GAIN2N_PT1		(APT55_GAIN2N_PT1)
#define UpAPT55_GAIN1P_PT1		(APT55_GAIN1P_PT1)
#define UpAPT55_GAIN2P_PT1		(APT55_GAIN2P_PT1)
#define UpAPT33_SLIC_PT1		(APT33_SLIC_PT1	)
#define UpAPT33_CLIP_PT1		(APT33_CLIP_PT1	)
#define UpAPT33_GAIN_PT1		(APT33_GAIN_PT1	)

#define UpAPT55_TH1_PT2			(APT55_TH1_PT2	)                                                
#define UpAPT55_TH2_PT2			(APT55_TH2_PT2	)
#define UpAPT55_TH3_PT2			(APT55_TH3_PT2	)
#define UpAPT55_GAIN1N_PT2		(APT55_GAIN1N_PT2)
#define UpAPT55_GAIN2N_PT2		(APT55_GAIN2N_PT2)
#define UpAPT55_GAIN1P_PT2		(APT55_GAIN1P_PT2)
#define UpAPT55_GAIN2P_PT2		(APT55_GAIN2P_PT2)
#define UpAPT33_SLIC_PT2		(APT33_SLIC_PT2	)
#define UpAPT33_CLIP_PT2		(APT33_CLIP_PT2	)
#define UpAPT33_GAIN_PT2		(APT33_GAIN_PT2	)


/* DEFOG */
//DEFOG User Parameter
#define UpDEFOG_TH_LOW			(DEFOG_TH_LOW )			// Defog Maximum Strength for menu LOW (0x0 ~ 0xffff)
#define UpDEFOG_TH_MID			(DEFOG_TH_MID )			// Defog Maximum Strength for menu MIDDLE (LOW ~ 0xffff)
#define UpDEFOG_TH_HIGH			(DEFOG_TH_HIGH)			// Defog Maximum Strength for menu HIGH (MIDDLE ~ 0xffff)
                            	               		
/* ACE */
//ACE_Common
#define UpACE_IIR				(ACE_IIR	)			// ACE IIR coefficient (0x0 ~ 0x3f)
#define UpACE_AGC_PT0			(ACE_AGC_PT0)
#define UpACE_AGC_PT1			(ACE_AGC_PT1)
#define UpACE_AGC_PT2			(ACE_AGC_PT2)

#define UpACE_WDR_AGC_PT0		(ACE_WDR_AGC_PT0)
#define UpACE_WDR_AGC_PT1		(ACE_WDR_AGC_PT1)
#define UpACE_WDR_AGC_PT2		(ACE_WDR_AGC_PT2)

//ACE - Normal
#define UpACE_DTH				(ACE_DTH)
#define UpACE_TH1_LOW_VAL_PT0	(ACE_TH1_LOW_VAL_PT0)	// ACE Dark Area Strength of WDR (0x0 ~ 0xff)
#define UpACE_TH1_MID_VAL_PT0	(ACE_TH1_MID_VAL_PT0)	// ACE Dark Area Strength of WDR (0x0 ~ 0xff)
#define UpACE_TH1_HIGH_VAL_PT0	(ACE_TH1_HIGH_VAL_PT0)	// ACE Dark Area Strength of WDR (0x0 ~ 0xff)

#define UpACE_TH2_LOW_VAL_PT0	(ACE_TH2_LOW_VAL_PT0)	// ACE Bright Area Strength of WDR (0x0 ~ 0xff)
#define UpACE_TH2_MID_VAL_PT0	(ACE_TH2_MID_VAL_PT0)	// ACE Bright Area Strength of WDR (0x0 ~ 0xff)
#define UpACE_TH2_HIGH_VAL_PT0	(ACE_TH2_HIGH_VAL_PT0)	// ACE Bright Area Strength of WDR (0x0 ~ 0xff)

#define UpACE_TH1_LOW_VAL_PT1	(ACE_TH1_LOW_VAL_PT1)	// ACE Dark Area Strength of WDR (0x0 ~ 0xff)
#define UpACE_TH1_MID_VAL_PT1	(ACE_TH1_MID_VAL_PT1)	// ACE Dark Area Strength of WDR (0x0 ~ 0xff)
#define UpACE_TH1_HIGH_VAL_PT1	(ACE_TH1_HIGH_VAL_PT1)	// ACE Dark Area Strength of WDR (0x0 ~ 0xff)

#define UpACE_TH2_LOW_VAL_PT1	(ACE_TH2_LOW_VAL_PT1)	// ACE Bright Area Strength of WDR (0x0 ~ 0xff)
#define UpACE_TH2_MID_VAL_PT1	(ACE_TH2_MID_VAL_PT1)	// ACE Bright Area Strength of WDR (0x0 ~ 0xff)
#define UpACE_TH2_HIGH_VAL_PT1	(ACE_TH2_HIGH_VAL_PT1)	// ACE Bright Area Strength of WDR (0x0 ~ 0xff)

#define UpACE_TH1_VAL_PT2		(ACE_TH1_VAL_PT2)	// ACE Dark Area Strength of WDR (0x0 ~ 0xff)
#define UpACE_TH2_VAL_PT2		(ACE_TH2_VAL_PT2)	// ACE Bright Area Strength of WDR (0x0 ~ 0xff)

#define	UpACE_GMGN_VAL_PT0		(ACE_GMGN_VAL_PT0)	// ACE Gamma gain 
#define	UpACE_GMGN_VAL_PT1		(ACE_GMGN_VAL_PT1)	// ACE Gamma gain 
#define	UpACE_GMGN_VAL_PT2		(ACE_GMGN_VAL_PT2)	// ACE Gamma gain 

//ACE - WDR
#define UpACE_WDR_DTH			(ACE_WDR_DTH)

#define UpACE_WDR_TH1_VAL_PT0	(ACE_WDR_TH1_VAL_PT0)	// ACE Dark Area Strength of WDR (0x0 ~ 0xff)
#define UpACE_WDR_TH1_VAL_PT1	(ACE_WDR_TH1_VAL_PT1)	// ACE Dark Area Strength of WDR (0x0 ~ 0xff)
#define UpACE_WDR_TH1_VAL_PT2	(ACE_WDR_TH1_VAL_PT2)	// ACE Dark Area Strength of WDR (0x0 ~ 0xff)

#define UpACE_WDR_TH2_VAL_PT0	(ACE_WDR_TH2_VAL_PT0)	// ACE Bright Area Strength of WDR (0x0 ~ 0xff)
#define UpACE_WDR_TH2_VAL_PT1	(ACE_WDR_TH2_VAL_PT1)	// ACE Bright Area Strength of WDR (0x0 ~ 0xff)
#define UpACE_WDR_TH2_VAL_PT2	(ACE_WDR_TH2_VAL_PT2)	// ACE Bright Area Strength of WDR (0x0 ~ 0xff)

#define	UpACE_WDR_GMGN_VAL_PT0	(ACE_WDR_GMGN_VAL_PT0)	// ACE Gamma gain 
#define	UpACE_WDR_GMGN_VAL_PT1	(ACE_WDR_GMGN_VAL_PT1)	// ACE Gamma gain 
#define	UpACE_WDR_GMGN_VAL_PT2	(ACE_WDR_GMGN_VAL_PT2)	// ACE Gamma gain 

/* HIGH LIGHT MASK */
#define UpHLMASK_THRS_STEP		(7	)				//HLMASK threshold menu step	(0 ~ 0xA)
#define UpHLMASK_CY				(100)				//HLMASK CY of Color			(0 ~ 0xFF)
#define UpHLMASK_CB				(100)				//HLMASK CB of Color			(0 ~ 0xFF)
#define UpHLMASK_CR				(100)				//HLMASK CR of Color			(0 ~ 0xFF)

/* DEFECT */
#define UpDEFECT_AGC_PT0		(DEFECT_AGC_PT0)	//DEFECT AGC PT0	(0~500 AGC)
#define UpDEFECT_AGC_PT1		(DEFECT_AGC_PT1)	//DEFECT AGC PT1	(0~500 AGC)
#define UpDEFECT_AGC_PT2		(DEFECT_AGC_PT2)	//DEFECT AGC PT2	(0~500 AGC)
#define UpDEFECT_GA				(0x80)				//DEFECT GAIN
#define UpDEFECT_SPOT_GA		(0x80)				//DEFECT SPOT GAIN

#define UpDEFECT_TSEL			(0x0)				// Select test image in core for directional defect correction. (VLOCKI)  "0" : Normal operation  "1" : Difference values for isolated points  "2" : Image before correction  "3" : Complete correction image (100% correction image except weight).  "4" : Defect pattern detection value

/* ENCODER */
#define	UpENC_CSTM				(0x0)				//*0 : Default table
													// 1 : Cstm parameter
/* ENCODER_LV0_T */
#define UpENC_RYGAINP_T			(ENC_RYGAINPr)
#define UpENC_RYGAINN_T			(ENC_RYGAINNr)
#define UpENC_BYGAINP_T			(ENC_BYGAINPr)
#define UpENC_BYGAINN_T			(ENC_BYGAINNr)

#define UpENC_RYHUEP_T			(ENC_RYHUEPr )
#define UpENC_RYHUEN_T			(ENC_RYHUENr )
#define UpENC_BYHUEP_T			(ENC_BYHUEPr )
#define UpENC_BYHUEN_T			(ENC_BYHUENr )

#define	UpY_MGAIN_T				(Y_MGAINr    )
#define UpCB_MGAIN_T			(CB_MGAINr   )
#define UpCR_MGAIN_T			(CR_MGAINr   )

#define	UpWHITE_LV_T      		(WHITE_LVr	 )
#define	UpBLANK_LV_T     		(BLANK_LVr	 )
#define	UpPEDESTAL_LV_T   		(PEDESTAL_LVr)

#define	UpCB_BST_T        		(CB_BSTr	 )
#define	UpCR_BST_T        		(CR_BSTr	 )

#define	UpFSC_TGT_T				(FSC_TGTr	 )

#define	UpHSC_K_T				(HSC_Kr		 )
#define	UpHLOCK_CAT_T     		(HLOCK_CATr	 )
#define	UpVLOCK_CAT_EV_T		(VLOCK_CAT_EVr)
#define	UpVLOCK_CAT_OD_T		(VLOCK_CAT_ODr)

#define UpCRX_AUTO_CAT_T		(CRX_AUTO_CATr)
#define UpCRX_HPOSEVS_T			(CRX_HPOSEVSr)
#define UpCRX_HPOSEVE_T			(CRX_HPOSEVEr)
#define	UpCRX_BITRATE_T			(CRX_BITRATEr)

/* ENCODER_LV0_C */
#define UpENC_RYGAINP_C			(ENC_RYGAINPr)
#define UpENC_RYGAINN_C			(ENC_RYGAINNr)
#define UpENC_BYGAINP_C			(ENC_BYGAINPr)
#define UpENC_BYGAINN_C			(ENC_BYGAINNr)

#define UpENC_RYHUEP_C			(ENC_RYHUEPr )
#define UpENC_RYHUEN_C			(ENC_RYHUENr )
#define UpENC_BYHUEP_C			(ENC_BYHUEPr )
#define UpENC_BYHUEN_C			(ENC_BYHUENr )

#define	UpY_MGAIN_C				(Y_MGAINr    )
#define UpCB_MGAIN_C			(CB_MGAINr   )
#define UpCR_MGAIN_C			(CR_MGAINr   )

#define	UpWHITE_LV_C      		(WHITE_LVr	 )
#define	UpBLANK_LV_C     		(BLANK_LVr	 )
#define	UpPEDESTAL_LV_C   		(PEDESTAL_LVr)

#define	UpCB_BST_C        		(CB_BSTr	 )
#define	UpCR_BST_C        		(CR_BSTr	 )

#define	UpFSC_TGT_C				(FSC_TGTr	 )

#define	UpHSC_K_C				(HSC_Kr		 )
#define	UpHLOCK_CAT_C     		(HLOCK_CATr	 )
#define	UpVLOCK_CAT_EV_C		(VLOCK_CAT_EVr)
#define	UpVLOCK_CAT_OD_C		(VLOCK_CAT_ODr)

#define UpCRX_AUTO_CAT_C		(CRX_AUTO_CATr)
#define UpCRX_HPOSEVS_C			(CRX_HPOSEVSr)
#define UpCRX_HPOSEVE_C			(CRX_HPOSEVEr)
#define	UpCRX_BITRATE_C			(CRX_BITRATEr)

/* ENCODER_LV0_A */
#define UpENC_RYGAINP_A			(ENC_RYGAINPr)
#define UpENC_RYGAINN_A			(ENC_RYGAINNr)
#define UpENC_BYGAINP_A			(ENC_BYGAINPr)
#define UpENC_BYGAINN_A			(ENC_BYGAINNr)

#define UpENC_RYHUEP_A			(ENC_RYHUEPr )
#define UpENC_RYHUEN_A			(ENC_RYHUENr )
#define UpENC_BYHUEP_A			(ENC_BYHUEPr )
#define UpENC_BYHUEN_A			(ENC_BYHUENr )

#define	UpY_MGAIN_A				(Y_MGAINr    )
#define UpCB_MGAIN_A			(CB_MGAINr   )
#define UpCR_MGAIN_A			(CR_MGAINr   )

#define	UpWHITE_LV_A      		(WHITE_LVr	 )
#define	UpBLANK_LV_A     		(BLANK_LVr	 )
#define	UpPEDESTAL_LV_A   		(PEDESTAL_LVr)

#define	UpCB_BST_A        		(CB_BSTr	 )
#define	UpCR_BST_A        		(CR_BSTr	 )

#define	UpFSC_TGT_A				(FSC_TGTr	 )

#define	UpHSC_K_A				(HSC_Kr		 )
#define	UpHLOCK_CAT_A     		(HLOCK_CATr	  )
#define	UpVLOCK_CAT_EV_A		(VLOCK_CAT_EVr)
#define	UpVLOCK_CAT_OD_A		(VLOCK_CAT_ODr)

#define UpCRX_AUTO_CAT_A		(CRX_AUTO_CATr)
#define UpCRX_HPOSEVS_A			(CRX_HPOSEVSr)
#define UpCRX_HPOSEVE_A			(CRX_HPOSEVEr)
#define	UpCRX_BITRATE_A			(CRX_BITRATEr)

/* ENCODER_CVBS */
#define UpENC_RYGAINP_CVBS		(ENC_RYGAINPr)
#define UpENC_RYGAINN_CVBS		(ENC_RYGAINNr)
#define UpENC_BYGAINP_CVBS		(ENC_BYGAINPr)
#define UpENC_BYGAINN_CVBS		(ENC_BYGAINNr)

#define UpENC_RYHUEP_CVBS		(ENC_RYHUEPr )
#define UpENC_RYHUEN_CVBS		(ENC_RYHUENr )
#define UpENC_BYHUEP_CVBS		(ENC_BYHUEPr )
#define UpENC_BYHUEN_CVBS		(ENC_BYHUENr )

#define	UpY_MGAIN_CVBS			(Y_MGAINr    )
#define UpCB_MGAIN_CVBS			(CB_MGAINr   )
#define UpCR_MGAIN_CVBS			(CR_MGAINr   )

#define	UpWHITE_LV_CVBS      	(WHITE_LVr	 )
#define	UpBLANK_LV_CVBS     	(BLANK_LVr	 )
#define	UpPEDESTAL_LV_CVBS   	(PEDESTAL_LVr)

#define	UpCB_BST_CVBS        	(CB_BSTr	 )
#define	UpCR_BST_CVBS        	(CR_BSTr	 )

#define	UpFSC_TGT_CVBS			(FSC_TGTr	 )

#define	UpHSC_K_CVBS			(HSC_Kr		 )
#define	UpHLOCK_CAT_CVBS     	(HLOCK_CATr	  )
#define	UpVLOCK_CAT_EV_CVBS		(VLOCK_CAT_EVr)
#define	UpVLOCK_CAT_OD_CVBS		(VLOCK_CAT_ODr)

#define UpCRX_AUTO_CAT_CVBS		(CRX_AUTO_CATr)
#define UpCRX_HPOSEVS_CVBS		(CRX_HPOSEVSr )
#define UpCRX_HPOSEVE_CVBS		(CRX_HPOSEVEr )
#define	UpCRX_BITRATE_CVBS		(CRX_BITRATEr )

#define	UpDKX					(DKXr		 )
#define UpDKY					(DKYr		 )

#define UpDS_HOFF				(DS_HOFFr	 )
#define UpDS_VOFF				(DS_VOFFr	 )

/*---------------  AP-3DNR  ---------------*/
#define Up3DNR_AGC_PT0			(DNR3D_AGC_PT0)
#define Up3DNR_AGC_PT1			(DNR3D_AGC_PT1)
#define Up3DNR_AGC_PT2			(DNR3D_AGC_PT2)

#define Up3DNR_AGC_VAL0			(DNR3D_AGC_VAL0)
#define Up3DNR_AGC_VAL1			(DNR3D_AGC_VAL1)
#define Up3DNR_AGC_VAL2			(DNR3D_AGC_VAL2)

/* Adaptive Lighting */
#define UpAE_LED_TuningOn       (0x0 )

#define UpAE_LED_TEST_STEP      (1000)
#define UpAE_LED_TEST_MIN       (0x0 )
#define UpAE_LED_TEST_MAX       (0x0 )
#define UpAE_LED_TEST_RUN       (0x0 )

#define UpAE_LED_AePos_STOP     (0x0 )
#define UpAE_LED_LED            (0x0 )
#define UpAE_LED_AGC            (0x0 )

#define UpAE_LED_HEP_Hz         (0xfff)

/*---------------��H-V	REVERSE��---------------*/
#define	UpMirror				(0x0)
#define UpFlip					(0x0)

/*---------------  PAR-VER  ---------------*/\
#define UpUsrParVer				(0xFF)

#define UpPG_OFS_AGC_PT0        (PG_OFS_AGC_PT0)
#define UpPG_OFS_AGC_PT1        (PG_OFS_AGC_PT1)
#define UpPG_OFS_AGC_PT2        (PG_OFS_AGC_PT2)

#define	UpPG_OFS_VAL_PT0        (PG_OFS_VAL_PT0)
#define	UpPG_OFS_VAL_PT1        (PG_OFS_VAL_PT1)
#define	UpPG_OFS_VAL_PT2        (PG_OFS_VAL_PT2)

#define	UpVVD_FS_AGC_PT0        (VVD_FS_AGC_PT0)
#define	UpVVD_FS_AGC_PT1        (VVD_FS_AGC_PT1)
#define	UpVVD_FS_AGC_PT2        (VVD_FS_AGC_PT2)

#define	UpVVD_FS_VAL_PT0        (VVD_FS_VAL_PT0)
#define	UpVVD_FS_VAL_PT1        (VVD_FS_VAL_PT1)
#define	UpVVD_FS_VAL_PT2        (VVD_FS_VAL_PT2)

//******************************************************
// User Data
//------------------------------------------------------
#define UD_DATA_ID				gDataID/*model_ver*/		// User Data Reset if Program is compiled new.

#define USR_DATA_EA_AWBPRST		(16)
#define USR_DATA_EA_MAF			( 4)                // 180802 JJH position save
#define USR_DATA_EA_MAF_CBP		(31)                // 180802 JJH Calibration
#define	USR_DATA_TYPE_GAMMA		( 2)				// Gamma type Normal and WDR
#define USR_DATA_EA_GAMMA		(136)				// Gamma point  * 2byte * (Y1,Y2,C1,C2) = 17*2*4 = 136
#define USR_DATA_EA_COLORMAP	(512)				// Colormap point * 4byte = 128*4 = 512

#define USR_DATA_EA				(2+\
								USR_DATA_EA_AWBPRST+\
								USR_DATA_EA_MAF+\
								USR_DATA_EA_MAF_CBP+\
								(USR_DATA_EA_GAMMA*USR_DATA_TYPE_GAMMA)+\
								USR_DATA_EA_COLORMAP+\
								1)	// Byte total  (max 4K-4)
								
//#define USR_DATA_EA				(699+2)				// Byte total  (max 4K-4)  : START+(USR_DATA_EA_AWBPRST+USR_DATA_EA_MAF+USR_DATA_EA_MAF_CBP+USR_DATA_EA_GAMMA+USR_DATA_EA_COLORMAP)+END

#define GMA_BYTE				(34)

// User Data -------------------------------------------------------
extern BYTE gbUsrDataSaveChk;
extern BYTE gbUsrDataReadChk;
extern BYTE gbUsrDataTbl[USR_DATA_EA];

#define USR_DAT_READ_CHK_ALL	{gbGammParInit = 1;\
								 gbColorMapParInit = 1;}

enum {
	UD_START 	= 0,									// Head
	UD_FLAG,											// FLAG
	UdAwbPrst,											// 2			// AWB Preset Data
	UdMaf		= UdAwbPrst + USR_DATA_EA_AWBPRST,		// 18		// 2-Motor Current position Data
    UdMaf_Cbp   = UdMaf + USR_DATA_EA_MAF,			  	// 22		// 2-Motor Calibration Data
    UdGamma		= UdMaf_Cbp + USR_DATA_EA_MAF_CBP,		// 53		// Gamma
    UdColorMap	= UdGamma + (USR_DATA_EA_GAMMA*USR_DATA_TYPE_GAMMA),	// 325		// Gamma
    
	UD_END_REAL = UdColorMap + USR_DATA_EA_COLORMAP,	// 837		// ColorMap
};

#define UD_END 			(USR_DATA_EA-1)					// Tail
#define UD(I)			gbUsrDataTbl[I]

