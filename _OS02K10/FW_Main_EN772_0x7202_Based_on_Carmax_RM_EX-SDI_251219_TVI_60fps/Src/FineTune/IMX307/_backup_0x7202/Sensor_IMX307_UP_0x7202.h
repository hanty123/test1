/* **************************************************************************
 File Name	: 	Sensor_IMX307_UP.h
 Description	:	Image Fine-tune user parameter (open setting value)
 Designer		:	Lee, Gyu Hong
 Date		:	22. 04. 19
 Copyright ¨Ï DCOD  Co., Ltd. All Rights Reserved.
*************************************************************************** */

//******************************************************
// 1. AE (Auto Exposure)
//------------------------------------------------------
#define AE2_HSP						(0x50 )                             // Luma detection area X start
#define AE2_HEP						(0x3D0)                             // Luma detection area Y end
#define AE2_VSP						(0x30 )                             // Luma detection area Y start
#define AE2_VEP						(0x420)      						// Luma detection area Y end

//=====================================================
#define AE_SHT_SLICE_LINE			3
#define AE_OUTDOOR_THRS_VAL			3
                                	
#define AE_SHT_SLICE				(int)LibAeShtLine(UP(UpAE_SHT_SLICE_LINE))					// Shutter limit (line)
#define AE_OUTDOOR_THRS				(int)LibAeShtLine(gnInModeVtw>>UP(UpAE_OUTDOOR_THRS_VAL))	// shutter threshold (line)	// 1/240s
                                	
#define AE_DEBLUR_THRS_VAL			3
                                	
#if (AE_DEBLUR_FIX_ON==0)				// 170824 LH
	#define AE_DEBLUR_THRS			(int)LibAeShtLine(gnInModeVtw>>UP(UpAE_DEBLUR_THRS_VAL))	// shutter threshold (line)	// 1/240s
#else                           	
	#define AE_DEBLUR_MIN			(int)LibAeShtLine(2)
	#define AE_DEBLUR_MAX			(int)LibAeShtLine(gnInModeVtw>>3)
#endif

#define AE_SPEED_DC					1															// DC IRIS Speed : 0 ~ 3 (Low ~ Fast)

// Normal AE common -------------------------------------------
#define AE_ERR_MGN					(0x4)
                                	
#define	AE_TGT_GAIN					(0xA  )								// Normal Brightness target gain
#define	AE_TGT_OFST					(0x23 )								// Normal Brightness target offset
#define	AE_SLIC_OFST				(0x0  )								// Normal Brightness Slice level (- Target offset)
#define	AE_CLIP_OFST				(0x140)								// Normal Brightness Clip level (+ Target offset)	
                                	
#define	AE_SPEED					(0xA0)								// Tracking Speed : 0 ~ 128 ~ 255 (x0.25 ~ x1 ~ x4)
#define	AE_DEBLUR_GAIN				(100)								// Deblur shutter increasing gradient	 (line)	// 64 ~ 256 -> 0.5 ~ 2.0
                                	
// Target value decrease point  	
#define AE_TGT_DCRS_AGC_PT0			(0x0  )
#define AE_TGT_DCRS_AGC_PT1			(0x050)
#define AE_TGT_DCRS_AGC_PT2			(0x170)
                                	       
#define AE_TGT_DCRS_VAL_PT0			(0x0  )
#define AE_TGT_DCRS_VAL_PT1			(0x46 )
#define AE_TGT_DCRS_VAL_PT2			(0x5A )
                                	       
#define AE_BLK_LVL_AGC_PT0			(0x000)
#define AE_BLK_LVL_AGC_PT1			(0x0C0)
#define AE_BLK_LVL_AGC_PT2			(0x160)
                                	       
#define	AE_BLK_LVL_VAL_PT0			(0x5  )
#define	AE_BLK_LVL_VAL_PT1			(0x8  )
#define	AE_BLK_LVL_VAL_PT2			(0x8  )
                                	       
#define	AE_CLP_AGC_PT0				(0x000)
#define	AE_CLP_AGC_PT1				(0x040)
#define	AE_CLP_AGC_PT2				(0x080)
                                	       
#define	AE_CLP_VAL_PT0				(0x180)
#define	AE_CLP_VAL_PT1				(0x190)
#define	AE_CLP_VAL_PT2				(0x1a0)
                                	
#define	AE_SENS_AGC_LMT				(600)

// WDR common ---------------------------------------
//WDR-LONG
#define	AE_WDR_LTGT_GAIN			(0x3  )								// WDR Long Brightness target gain
#define	AE_WDR_LTGT_OFST			(0x25 )  							// WDR Long Brightness target offset
#define	AE_WDR_LSLIC_OFST			(0x0  )                             // WDR Long Brightness Slice level (- Target offset)		
#define	AE_WDR_LCLIP_OFST			(0x0  )                             // WDR Long Brightness Clip level (+ Target offset)				
                                	       
//WDR - SHORT                   	       
#define	AE_WDR_STGT_GAIN			(0x3  )								// WDR Short Brightness target gain
#define	AE_WDR_STGT_OFST			(0x15 )								// WDR Short Brightness target offset
#define	AE_WDR_SSLIC_OFST			(0x0  )                             // WDR Short Brightness Slice level (- Target offset)		
#define AE_WDR_SCLIP_OFST			(0x190) 							// WDR Short Brightness Clip level (+ Target offset) -SHORT


#define AE_WDR_LTGT_DCRS_AGC_PT0	(0x50 )
#define AE_WDR_LTGT_DCRS_AGC_PT1	(0xE0 )
#define AE_WDR_LTGT_DCRS_AGC_PT2	(0x1B0)
                                           
#define AE_WDR_LTGT_DCRS_VAL_PT0	(0x0  )
#define AE_WDR_LTGT_DCRS_VAL_PT1	(0x28 )
#define AE_WDR_LTGT_DCRS_VAL_PT2	(0x35 )
                                           
#define	AE_WDR_CLP_AGC_PT0			(0x000)
#define	AE_WDR_CLP_AGC_PT1			(0x040)
#define	AE_WDR_CLP_AGC_PT2			(0x080)
                                	       
#define	AE_WDR_CLP_VAL_PT0			(0x180)
#define	AE_WDR_CLP_VAL_PT1			(0x190)
#define	AE_WDR_CLP_VAL_PT2			(0x1A0)
                                	                                                         
#define AE_WDR_SATLV_AGC_PT0		(0x800)
#define AE_WDR_SATLV_AGC_PT1		(0x1000)
                                	                                                         
#define AE_WDR_SATLV_VAL_PT0		(0x0  )
#define AE_WDR_SATLV_VAL_PT1		(0x300)
                                           
#define AE_WDR_LS_WGT_AGC_PT0		(0x80 )
#define AE_WDR_LS_WGT_AGC_PT1		(0x100)
                                           
#define	AE_WDR_LS_WGT_VAL0			(0x200)
#define	AE_WDR_LS_WGT_VAL1			(0x200)

#define AE_WDR_LONG_TH_OFST1 		(0x150)
#define AE_WDR_LONG_TH_OFST2 		(0x40 )
																				
#define AE_WDR_LONG_MIN 			( 4)	
#define AE_WDR_SHORT_MIN1			( 2)
#define AE_WDR_SHORT_MIN2			(gnAeLWdrMaxS1)
                                	
#define	AE_SENS_WDR_AGC_LMT			(750)
#define AE_WDR_TMG_SEL				(2)
	
//******************************************************
// 2. AWB (Auto White Balance)
//------------------------------------------------------
#define AWB_HSP						(0x40 )										// AWB detection area X start
#define AWB_HW						(0x395)                                     // AWB detection area Y end
#define AWB_VSP						(0x20 )                                     // AWB detection area Y start
#define AWB_VW						(0x420)                        				// AWB detection area Y end
                            		
#define AWB_TCNT_LMT				(0x1000)									// White pixel cnt limit
                            		
#define AWB_AGC_MIN					(0x150)									  	// Chroma AGC position for maximum weight
#define AWB_AGC_MAX					(0x200)									  	// Chroma AGC position for minimum weight
                            		       									
#define AWB_WDR_AGC_MIN				(0x180)									  	// Chroma AGC position for maximum weight
#define AWB_WDR_AGC_MAX				(0x1A0)									  	// Chroma AGC position for minimum weight
                            		
#define AWB_AGC_WGT_MAX				(0x100)										// Chroma maximum weight (100% = 0x100)
#define AWB_AGC_WGT_MIN				(0xA0 )   									// Chroma minimum weight
                            		
#define	AWB_SPEED_MTRX				0xf8		       							// Matrix tracking speed (Low is high speed, max=0xff)
#define	AWB_SPEED_GAIN				UP(UpAWB_SPEED_MTRX)				       	// RGB gain tracking Speed (Low is high speed)
                            		
#define AWB_YSLICE					0x20										// White Y slice
#define AWB_YCLIP					0x100       								// White Y clip
                            		
#define	AWB_GAIN_DFLT				0x100										// RGB Gain default
#define AWB_GAIN_TIMES				3											// RGB Gain limit (X times)
                            		
#define AWB_GAIN_MIN				(AWB_GAIN_DFLT/UP(UpAWB_GAIN_TIMES))		// RGB Gain min
#define AWB_GAIN_MAX				(AWB_GAIN_DFLT*UP(UpAWB_GAIN_TIMES))		// RGB Gain max
                            		
#define AWB_GAIN_STEP_H				((AWB_GAIN_MAX-AWB_GAIN_DFLT)/10)			// 171211 LH
#define AWB_GAIN_STEP_L				((AWB_GAIN_DFLT-AWB_GAIN_MIN)/10)			// "
                            		
#define	AWB_TEMP_DR_L				(0x56F)
#define	AWB_TEMP_DR_M				(0x363)
#define AWB_TEMP_DR_H				(0x2D7)
                            		
#define AWB_TEMP_VAL_L				(2300)		// 2300K
#define AWB_TEMP_VAL_M				(4150)		// 4150K
#define AWB_TEMP_VAL_H				(6500)		// 6500K
                            		
#define	AWB_R_WGT					(0x100)
#define AWB_G_WGT					(0x100)
#define AWB_B_WGT					(0x100)
                            		
// Color Temp               		
#define CCM_TEMP_L					(AWB_TEMP_VAL_L)
#define CCM_TEMP_M					(AWB_TEMP_VAL_M)
#define CCM_TEMP_H					(AWB_TEMP_VAL_H)
                            		
// LOW_TEMP                 		
#define	CCM_RR_TEMP_L				(0x100)
#define CCM_RG_TEMP_L				(0x100)
#define CCM_RB_TEMP_L				(0x100)
#define	CCM_GR_TEMP_L				(0x100)
#define CCM_GG_TEMP_L				(0x100)
#define CCM_GB_TEMP_L				(0x100)
#define	CCM_BR_TEMP_L				(0x100)
#define CCM_BG_TEMP_L				(0x100)
#define CCM_BB_TEMP_L				(0x100)
                            		
// MID_TEMP                 		
#define	CCM_RR_TEMP_M				(0x100)
#define CCM_RG_TEMP_M				(0x100)
#define CCM_RB_TEMP_M				(0x100)
#define	CCM_GR_TEMP_M				(0x100)
#define CCM_GG_TEMP_M				(0x100)
#define CCM_GB_TEMP_M				(0x100)
#define	CCM_BR_TEMP_M				(0x100)
#define CCM_BG_TEMP_M				(0x100)
#define CCM_BB_TEMP_M				(0x100)
                            		
// HI_TEMP                  		
#define	CCM_RR_TEMP_H				(0x100)
#define CCM_RG_TEMP_H				(0x100)
#define CCM_RB_TEMP_H				(0x100)
#define	CCM_GR_TEMP_H				(0x100)
#define CCM_GG_TEMP_H				(0x100)
#define CCM_GB_TEMP_H				(0x100)
#define	CCM_BR_TEMP_H				(0x100)
#define CCM_BG_TEMP_H				(0x100)
#define CCM_BB_TEMP_H				(0x100)
                            		
#define AWB_5000K_AGC_TH			(0x1A0)
	
//******************************************************
// 3. AI-DNR
//------------------------------------------------------
// AI-DNR User Parameter
#define DNR_AGC_PT0					(0x040)
#define	DNR_AGC_PT1					(0x160)
#define DNR_AGC_PT2					(0x200)
                                	       
#define DNR_WDR_AGC_PT0				(0x040)
#define DNR_WDR_AGC_PT1				(0x160)
#define DNR_WDR_AGC_PT2				(0x200)
                                	       
#define DNR_AGC_HPF_PT0				(0x080)
#define DNR_AGC_HPF_PT1				(0x190)
#define DNR_AGC_HPF_PT2				(0x1C0)
                                	       
#define DNR_AGC_OFST_PVAL0			(0x000)
#define DNR_AGC_OFST_PVAL1			(0x000)
#define DNR_AGC_OFST_PVAL2			(0x000)
                                	       
#define DNR_AGC_OFST_MVAL0			(0x003)
#define DNR_AGC_OFST_MVAL1			(0x01e)
#define DNR_AGC_OFST_MVAL2			(0x04c)
                                	
#define	DNR_HPF_GAIN_LV0_PT0		(0x0)
#define DNR_HPF_GAIN_LV0_PT1		(0x1)
#define	DNR_HPF_GAIN_LV0_PT2		(0x0)
                                	    
#define	DNR_HPF_GAIN_LV1_PT0		(0x1)
#define DNR_HPF_GAIN_LV1_PT1		(0x2)
#define	DNR_HPF_GAIN_LV1_PT2		(0x0)
                                	    
#define	DNR_HPF_GAIN_LV2_PT0		(0x1)
#define DNR_HPF_GAIN_LV2_PT1		(0x2)
#define	DNR_HPF_GAIN_LV2_PT2		(0x0)

//******************************************************
// 4. SHARPNESS
//------------------------------------------------------
// Sharpness User Parameter
#define	SHARPNESS_GAIN				(0x5)
#define SHARPNESS_GAIN_CVBS			(0x10)
                                	
#define SHP_AGC_PT0					(0x000)
#define	SHP_AGC_PT1					(0x140)
#define SHP_AGC_PT2					(0x1C0)
                                	       
#define SHP_WDR_AGC_PT0				(0x000)	
#define SHP_WDR_AGC_PT1				(0x140)
#define SHP_WDR_AGC_PT2				(0x1C0)
                                	       
//APT_PT0                       	       
#define APT55_TH1_PT0				(0x30 )
#define APT55_TH2_PT0				(0x200)
#define APT55_TH3_PT0				(0x60 )
#define APT55_GAIN1N_PT0			(0x30 )	
#define APT55_GAIN2N_PT0			(0x20 )
#define APT55_GAIN1P_PT0			(0x90 )	
#define APT55_GAIN2P_PT0			(0x70 )
                                	       
#define APT33_SLIC_PT0				(0x4  )
#define APT33_CLIP_PT0				(0x80 )
#define APT33_GAIN_PT0				(0xB0 )
                                	       
//APT_PT1                       	       
#define APT55_TH1_PT1				(0x150)
#define APT55_TH2_PT1				(0x300)
#define APT55_TH3_PT1				(0x60 )
#define APT55_GAIN1N_PT1			(0x10 )
#define APT55_GAIN2N_PT1			(0x10 )
#define APT55_GAIN1P_PT1			(0x30 )
#define APT55_GAIN2P_PT1			(0x50 )
                                	       
#define APT33_SLIC_PT1				(0x30 )
#define APT33_CLIP_PT1				(0x80 )
#define APT33_GAIN_PT1				(0x80 )
                                	       
//APT_PT2                       	       
#define APT55_TH1_PT2				(0x400)
#define APT55_TH2_PT2				(0x500)
#define APT55_TH3_PT2				(0x60 )
#define APT55_GAIN1N_PT2			(0x05 )
#define APT55_GAIN2N_PT2			(0x05 )
#define APT55_GAIN1P_PT2			(0x10 )
#define APT55_GAIN2P_PT2			(0x20 )
                                	       
#define APT33_SLIC_PT2				(0x50 )  
#define APT33_CLIP_PT2				(0x40 )
#define APT33_GAIN_PT2				(0x60 )


//******************************************************
// 5. GAMMA
//------------------------------------------------------
#define YGMA_AGC_PT0				(0x0  )
#define	YGMA_AGC_PT1				(0x40 )
#define CGMA_AGC_PT0				(0x0  )
#define	CGMA_AGC_PT1				(0x200)
                                	       
#define YGMA_WDR_AGC_PT0			(0x50 )
#define	YGMA_WDR_AGC_PT1			(0xE0 )
#define CGMA_WDR_AGC_PT0			(0x0  )
#define	CGMA_WDR_AGC_PT1			(0x80 )
	
//******************************************************
// 6. DEFECT
//------------------------------------------------------
#define DEFECT_AGC_PT0				(0x040) 					// Max AGC arg.
#define DEFECT_AGC_PT1				(0x140) 					// Mid AGC arg.
#define DEFECT_AGC_PT2				(0x200)						// Min AGC arg.
                                            				
//******************************************************
// 8. ACE & DEFOG
//------------------------------------------------------
// ACE
#define ACE_IIR						(0x1f)						// ACE IIR coefficient (0x0 ~ 0x3f)
#define ACE_DTH						(0x3 )
#define ACE_WDR_DTH					(0x6 )
                                	
#define ACE_AGC_PT0					(0x000) 	
#define ACE_AGC_PT1					(0x090)
#define ACE_AGC_PT2					(0x100) 	
                                	       
#define ACE_WDR_AGC_PT0				(0x080)  	
#define ACE_WDR_AGC_PT1				(0x100) 
#define ACE_WDR_AGC_PT2				(0x150) 
                                	
// ACE - NORMAL                 	
#define ACE_TH1_LOW_VAL_PT0			(0x0C)						// ACE Dark Area Strength of WDR (0x0 ~ 0xff)
#define ACE_TH1_MID_VAL_PT0			(0x30)						// ACE Dark Area Strength of WDR (0x0 ~ 0xff)
#define ACE_TH1_HIGH_VAL_PT0		(0x50)						// ACE Dark Area Strength of WDR (0x0 ~ 0xff)
                                	      						
#define ACE_TH2_LOW_VAL_PT0			(0x0C)						// ACE Bright Area Strength of WDR (0x0 ~ 0xff)
#define ACE_TH2_MID_VAL_PT0			(0x18)						// ACE Bright Area Strength of WDR (0x0 ~ 0xff)
#define ACE_TH2_HIGH_VAL_PT0		(0x20)						// ACE Bright Area Strength of WDR (0x0 ~ 0xff)
                                	      						
#define ACE_TH1_LOW_VAL_PT1			(0x05)						// ACE Dark Area Strength of WDR (0x0 ~ 0xff)
#define ACE_TH1_MID_VAL_PT1			(0x30)						// ACE Dark Area Strength of WDR (0x0 ~ 0xff)
#define ACE_TH1_HIGH_VAL_PT1		(0x50)						// ACE Dark Area Strength of WDR (0x0 ~ 0xff)
                                	      						
#define ACE_TH2_LOW_VAL_PT1			(0x05)						// ACE Bright Area Strength of WDR (0x0 ~ 0xff)
#define ACE_TH2_MID_VAL_PT1			(0x18)						// ACE Bright Area Strength of WDR (0x0 ~ 0xff)
#define ACE_TH2_HIGH_VAL_PT1		(0x20)						// ACE Bright Area Strength of WDR (0x0 ~ 0xff)
                                	      						
#define ACE_TH1_VAL_PT2				(0x05)						// ACE Dark Area Strength of WDR (0x0 ~ 0xff)
#define ACE_TH2_VAL_PT2				(0x05)						// ACE Bright Area Strength of WDR (0x0 ~ 0xff)
                                	      						
#define	ACE_GMGN_VAL_PT0			(0x20)						// ACE Gamma gain 
#define	ACE_GMGN_VAL_PT1			(0x10)						// ACE Gamma gain 
#define	ACE_GMGN_VAL_PT2			(0x05)						// ACE Gamma gain 
                                	      						
// ACE - WDR                    	      						
#define ACE_WDR_TH1_VAL_PT0			(0xC )						// ACE Dark Area Strength minimum value of WDR (0x0 ~ 0xff)
#define ACE_WDR_TH1_VAL_PT1			(0x8 )						// ACE Dark Area Strength maximum value  of WDR (0x0 ~ 0xff)
#define ACE_WDR_TH1_VAL_PT2			(0x5 )						// ACE Dark Area Strength maximum value  of WDR (0x0 ~ 0xff)
                                	      						
#define ACE_WDR_TH2_VAL_PT0			(0x08)						// ACE Bright Area Strength minimum value  of WDR (0x0 ~ 0xff)
#define ACE_WDR_TH2_VAL_PT1			(0x08)						// ACE Bright Area Strength maximum value  of WDR (0x0 ~ 0xff)
#define ACE_WDR_TH2_VAL_PT2			(0x05)						// ACE Bright Area Strength maximum value  of WDR (0x0 ~ 0xff)
                                	      						
#define	ACE_WDR_GMGN_VAL_PT0		(0x10)						// ACE Gamma gain Max
#define	ACE_WDR_GMGN_VAL_PT1		(0x5 )						// ACE Gamma gain Min
#define	ACE_WDR_GMGN_VAL_PT2		(0x5 )						// ACE Gamma gain Min
                                	
// DEFOG                        	
#define DEFOG_TH_LOW				(0x100)						// Defog Maximum Strength for menu LOW (0x0 ~ 0xffff)
#define DEFOG_TH_MID				(0x200)						// Defog Maximum Strength for menu MIDDLE (LOW ~ 0xffff)
#define DEFOG_TH_HIGH				(0x500)						// Defog Maximum Strength for menu HIGH (MIDDLE ~ 0xffff)

//******************************************************
//10. ETC
//------------------------------------------------------
// LOW COLOR SUPRESSION        	
#define LSUP_GA_AGC_PT0				(0x000)
#define LSUP_GA_AGC_PT1				(0x100)
                                	
#define LSUP_GA_VAL_PT0 			(0x3F)
#define LSUP_GA_VAL_PT1 			(0x3F)

// COLOR SUPRESSION
#define CSUP_TH_AGC_PT0				(0x000)
#define CSUP_TH_AGC_PT1				(0x300)
                                	
#define CSUP_TH_VAL_PT0 			(0x95)
#define CSUP_TH_VAL_PT1 			(0x86)
                                	
// EDGE COLOR SUPRESSION        	
#define CES_TH_AGC_PT0				(0x000)
#define CES_TH_AGC_PT1				(0x200)
                                	
#define CES_TH_VAL_PT0 				(0x24)
#define CES_TH_VAL_PT1 				(0x24)

