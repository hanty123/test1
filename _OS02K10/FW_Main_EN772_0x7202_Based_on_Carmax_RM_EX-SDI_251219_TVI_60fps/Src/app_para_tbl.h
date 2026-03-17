/* **************************************************************************
 File Name	: 	app_para_tbl.h
 Description:	EN772 - User Parameter table
 Designer	:	Lee, Gyu Hong
 Date		:	20. 12. 15
 Copyright    Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#define USR_PAR_LIST/* User Parameter List */\
/*---------------  SYSTEM  ---------------*/\
/*#MIPI_TIMING*/\
UP_SET(1, UpLVDS_CKDLY,=2)/* MIPI & LVDS Input Clock Delay Adjust (0x0 ~ 0xf) <Not be saved> */\
UP_SET(1, UpLDIDLY0)/* MIPI & LVDS Channel 0 Delay Adjust (0x0~0xf) <Not be saved> */\
UP_SET(1, UpLDIDLY1)/* MIPI & LVDS Channel 1 Delay Adjust (0x0~0xf) <Not be saved> */\
UP_SET(1, UpLDIDLY2)/* MIPI & LVDS Channel 2 Delay Adjust (0x0~0xf) <Not be saved> */\
UP_SET(1, UpLDIDLY3)/* MIPI & LVDS Channel 3 Delay Adjust (0x0~0xf) <Not be saved> */\
/*---------------  KEY  ---------------*/\
UP_SET(2, UpADC_LEVEL_C,=8)/* ADC Value of Center Key (0 ~ 0x3FF) */\
UP_SET(2, UpADC_LEVEL_U)/* ADC Value of Up Key (0 ~ 0x3FF) */\
UP_SET(2, UpADC_LEVEL_D)/* ADC Value of Down Key (0 ~ 0x3FF) */\
UP_SET(2, UpADC_LEVEL_L)/* ADC Value of Left Key (0 ~ 0x3FF) */\
UP_SET(2, UpADC_LEVEL_R)/* ADC Value of Right Key (0 ~ 0x3FF) */\
UP_SET(1, UpAD_CHT_BIT)/* Number of bit for Chattering ADC Value of Key (1 ~ 8) */\
/*---------------  TDN  ---------------*/\
UP_SET(1, UpTDN_EXTN_THRS_STEP,=30)/* ADC Value unit per one step of THRES in DAY&NIGHT-EXTERN Menu (1 ~ 0x64) */\
UP_SET(1, UpTDN_AUTO_THRS_STEP)/* AGC Value unit per one step of THRES in DAY&NIGHT-AUTO Menu (1 ~ 0x64) */\
UP_SET(2, UpTDN_DLY_LOW)/* TDN low delay time (1000->1s, 2000->2s, ..., 20000->20s) */\
UP_SET(2, UpTDN_DLY_MIDDLE)/* TDN middle delay time (1000->1s, 2000->2s, ..., 20000->20s) */\
UP_SET(2, UpTDN_DLY_HIGH)/* TDN high delay time (1000->1s, 2000->2s, ..., 20000->20s) */\
/*---------------  AE  ---------------*/\
/*#AE_WINDOW*/\
UP_SET(2, UpAE2_HSP,=50)/* Luma detection area X start (default +- value) */\
UP_SET(2, UpAE2_HEP)/* Luma detection area X end (default +- value) */\
UP_SET(2, UpAE2_VSP)/* Luma detection area Y start (default +- value) */\
UP_SET(2, UpAE2_VEP)/* Luma detection area Y end (default +- value) */\
/*#AE_PAR*/\
UP_SET(2, UpAE_SHT_SLICE_LINE)/* Limit of Shutter minimum value (line value : spec min ~ 1123) */\
UP_SET(1, UpAE_OUTDOOR_THRS_VAL)/* When OUTDOOR mode, Shutter threshold value (ex. 1125>>3 = 375 => 1/240s) */\
UP_SET(1, UpAE_DEBLUR_THRS_VAL)/* When DEBLUR mode, Shutter threshold value (ex. 1125>>3 = 375 => 1/240s) */\
UP_SET(1, UpAE_SPEED_DC)/* DC IRIS Speed ([Low]0 ~ [Fast]3) */\
UP_SET(2, UpAE_TGT_GAIN)/* Normal Brightness target gain [(UpAE_TGT_GAIN * BRIGHTNESS in Menu) + UpAE_TGT_OFST < 0x3FF] */\
UP_SET(2, UpAE_TGT_OFST)/* Normal Brightness target offset [(UpAE_TGT_GAIN * BRIGHTNESS in Menu) + UpAE_TGT_OFST < 0x3FF] */\
UP_SET(2, UpAE_SLIC_OFST)/* Normal Brightness Slice level (AE Target - UpAE_SLIC_OFST < Target) */\
UP_SET(2, UpAE_CLIP_OFST)/* Normal Brightness Clip level (AE Target + UpAE_CLIP_OFST < 0x3FF) */\
UP_SET(2, UpAE_TGT_DCRS_AGC_PT0)/* AGC interlocking point 0 for Target Value to be decreased */\
UP_SET(2, UpAE_TGT_DCRS_AGC_PT1)/* AGC interlocking point 1 for Target Value to be decreased */\
UP_SET(2, UpAE_TGT_DCRS_AGC_PT2)/* AGC interlocking point 2 for Target Value to be decreased */\
UP_SET(1, UpAE_TGT_DCRS_VAL_PT0)/* Target Value to be decreased interlocking point 0, [Target_Value = Target - DCRS_TargetVal(Calculate Target through AGC Interlocking) */\
UP_SET(1, UpAE_TGT_DCRS_VAL_PT1)/* Target Value to be decreased interlocking point 1, [Target_Value = Target - DCRS_TargetVal(Calculate Target through AGC Interlocking) */\
UP_SET(1, UpAE_TGT_DCRS_VAL_PT2)/* Target Value to be decreased interlocking point 2, [Target_Value = Target - DCRS_TargetVal(Calculate Target through AGC Interlocking) */\
UP_SET(1, UpAE_SPEED)/* Tracking Speed (0 ~ 0x80 ~ 0xFF ->  x0.25 ~ x1 ~ x4) */\
UP_SET(1, UpAE_DEBLUR_GAIN)/* Deblur shutter increasing gradient (0x40 ~ 0xFF -> x0.5 ~ x2.0) */\
UP_SET(2, UpAE_BLK_LVL_AGC_PT0)/* AGC interlocking point 0 for black level (0x0 ~ 0x300) */\
UP_SET(2, UpAE_BLK_LVL_AGC_PT1)/* AGC interlocking point 1 for black level (0x0 ~ 0x300) */\
UP_SET(2, UpAE_BLK_LVL_AGC_PT2)/* AGC interlocking point 2 for black level (0x0 ~ 0x300) */\
UP_SET(1, UpAE_BLK_LVL_VAL_PT0)/* Black level corresponding to interlocking point 0 */\
UP_SET(1, UpAE_BLK_LVL_VAL_PT1)/* Black level corresponding to interlocking point 1 */\
UP_SET(1, UpAE_BLK_LVL_VAL_PT2)/* Black level corresponding to interlocking point 2 */\
UP_SET(2, UpAE_CLP_AGC_PT0)/* AGC interlocking point 0 for CLIP_VALUE */\
UP_SET(2, UpAE_CLP_AGC_PT1)/* AGC interlocking point 1 for CLIP_VALUE */\
UP_SET(2, UpAE_CLP_AGC_PT2)/* AGC interlocking point 2 for CLIP_VALUE */\
UP_SET(2, UpAE_CLP_VAL_PT0)/* CLIP VALUE corresponding to interlocking point 0, (Clip_LEVEL = Target_Val + CLIP_VALUE) */\
UP_SET(2, UpAE_CLP_VAL_PT1)/* CLIP VALUE corresponding to interlocking point 1, (Clip_LEVEL = Target_Val + CLIP_VALUE) */\
UP_SET(2, UpAE_CLP_VAL_PT2)/* CLIP VALUE corresponding to interlocking point 2, (Clip_LEVEL = Target_Val + CLIP_VALUE) */\
UP_SET(2, UpAE_SENS_AGC_LMT)/* Limit the Analog Gain Value for each Sensor */\
/*#WDR_PAR*/\
UP_SET(2, UpAE_WDR_LTGT_GAIN)/* When WDR Mode, Long Brightness target gain (default +- value) */\
UP_SET(2, UpAE_WDR_LTGT_OFST)/* When WDR Mode, Long Brightness target offset (default +- value) */\
UP_SET(2, UpAE_WDR_LSLIC_OFST)/* When WDR Mode, Long Brightness Slice level (AE Long Target - UpAE_WDR_LSLIC_OFST < Target) */\
UP_SET(2, UpAE_WDR_LCLIP_OFST)/* When WDR Mode, Long Brightness Clip level (AE Long Target + UpAE_WDR_LCLIP_OFST < 0x3FF) */\
UP_SET(2, UpAE_WDR_STGT_GAIN)/* When WDR Mode, Short Brightness target gain (default +- value) */\
UP_SET(2, UpAE_WDR_STGT_OFST)/* When WDR Mode, Short Brightness target offset (default +- value) */\
UP_SET(2, UpAE_WDR_SSLIC_OFST)/* When WDR Mode, Short Brightness Slice level (AE Short Target - UpAE_WDR_SSLIC_OFST < Target) */\
UP_SET(2, UpAE_WDR_SCLIP_OFST)/* When WDR Mode, Short Brightness Clip level (AE Short Target + UpAE_WDR_SCLIP_OFST < 0x3FF) */\
UP_SET(2, UpAE_WDR_LTGT_DCRS_AGC_PT0)/* When WDR Mode, AGC interlocking point 0 for Target Value to be decreased */\
UP_SET(2, UpAE_WDR_LTGT_DCRS_AGC_PT1)/* When WDR Mode, AGC interlocking point 1 for Target Value to be decreased */\
UP_SET(2, UpAE_WDR_LTGT_DCRS_AGC_PT2)/* When WDR Mode, AGC interlocking point 2 for Target Value to be decreased */\
UP_SET(1, UpAE_WDR_LTGT_DCRS_VAL_PT0)/* When WDR Mode, Target Value to be decreased interlocking point 0, [Target_Value = Target - DCRS_TargetVal(Calculate Target through AGC Interlocking), (Must be DCRS_VAL < Target)] */\
UP_SET(1, UpAE_WDR_LTGT_DCRS_VAL_PT1)/* When WDR Mode, Target Value to be decreased interlocking point 1, [Target_Value = Target - DCRS_TargetVal(Calculate Target through AGC Interlocking), (Must be DCRS_VAL < Target)] */\
UP_SET(1, UpAE_WDR_LTGT_DCRS_VAL_PT2)/* When WDR Mode, Target Value to be decreased interlocking point 2, [Target_Value = Target - DCRS_TargetVal(Calculate Target through AGC Interlocking), (Must be DCRS_VAL < Target)] */\
UP_SET(2, UpAE_WDR_CLP_AGC_PT0)/* When WDR Mode, AGC interlocking point 0 for Long CLIP_VALUE */\
UP_SET(2, UpAE_WDR_CLP_AGC_PT1)/* When WDR Mode, AGC interlocking point 1 for Long CLIP_VALUE */\
UP_SET(2, UpAE_WDR_CLP_AGC_PT2)/* When WDR Mode, AGC interlocking point 2 for Long CLIP_VALUE */\
UP_SET(2, UpAE_WDR_CLP_VAL_PT0)/* When WDR Mode, Long CLIP VALUE corresponding to interlocking point 0 (CLIP_LV = UpAE_WDR_LCIP_OFST + CLIP_VALUE),(Range : iTgtL0 ~ 0x3ff) */\
UP_SET(2, UpAE_WDR_CLP_VAL_PT1)/* When WDR Mode, Long CLIP VALUE corresponding to interlocking point 1 (CLIP_LV = UpAE_WDR_LCIP_OFST + CLIP_VALUE),(Range : iTgtL0 ~ 0x3ff) */\
UP_SET(2, UpAE_WDR_CLP_VAL_PT2)/* When WDR Mode, Long CLIP VALUE corresponding to interlocking point 2 (CLIP_LV = UpAE_WDR_LCIP_OFST + CLIP_VALUE),(Range : iTgtL0 ~ 0x3ff) */\
UP_SET(2, UpAE_WDR_SATLV_AGC_PT0)/* When WDR Mode, AGC interlocking point 0 for Long SATURATION_LEVEL */\
UP_SET(2, UpAE_WDR_SATLV_AGC_PT1)/* When WDR Mode, AGC interlocking point 1 for Long SATURATION_LEVEL */\
UP_SET(2, UpAE_WDR_SATLV_VAL_PT0)/* When WDR Mode, Long SATURATION LEVEL VALUE corresponding to interlocking point 0 */\
UP_SET(2, UpAE_WDR_SATLV_VAL_PT1)/* When WDR Mode, Long SATURATION LEVEL VALUE corresponding to interlocking point 1 */\
UP_SET(2, UpAE_WDR_LS_WGT_AGC_PT0)/* When WDR Mode, As the corresponding value decreases ,the contrast of dark areas expressed from long exposure enhance */\
UP_SET(2, UpAE_WDR_LS_WGT_AGC_PT1)/* When WDR Mode, As the corresponding value decreases ,the contrast of dark areas expressed from long exposure enhance */\
UP_SET(2, UpAE_WDR_LS_WGT_VAL0)/* When WDR Mode, As the corresponding value decreases ,the contrast of dark areas expressed from long exposure enhance */\
UP_SET(2, UpAE_WDR_LS_WGT_VAL1)/* When WDR Mode, As the corresponding value decreases ,the contrast of dark areas expressed from long exposure enhance */\
UP_SET(2, UpAE_WDR_LONG_TH_OFST1)/* */\
UP_SET(2, UpAE_WDR_LONG_TH_OFST2)/* */\
UP_SET(1, UpAE_WDR_LONG_MIN)/* When WDR Mode, Minimum Value of Long Shutter */\
UP_SET(1, UpAE_WDR_SHORT_MIN)/* When WDR Mode, Minimum Value of Short Shutter */\
UP_SET(2, UpAE_WDR_SENS_AGC_LMT)/* When WDR Mode, Limit the Analog Gain Value for each Sensor */\
UP_SET(1, UpAE_WDR_TMG_SEL)/* */\
/*#G_OFS*/\
UP_SET(2, UpPG_OFS_AGC_PT0)/* */\
UP_SET(2, UpPG_OFS_AGC_PT1)/* */\
UP_SET(2, UpPG_OFS_AGC_PT2)/* */\
UP_SET(1, UpPG_OFS_VAL_PT0)/* */\
UP_SET(1, UpPG_OFS_VAL_PT1)/* */\
UP_SET(1, UpPG_OFS_VAL_PT2)/* */\
/*#VVD*/\
UP_SET(2, UpVVD_FS_AGC_PT0)/* */\
UP_SET(2, UpVVD_FS_AGC_PT1)/* */\
UP_SET(2, UpVVD_FS_AGC_PT2)/* */\
UP_SET(2, UpVVD_FS_VAL_PT0)/* */\
UP_SET(2, UpVVD_FS_VAL_PT1)/* */\
UP_SET(2, UpVVD_FS_VAL_PT2)/* */\
/*---------------  AWB  ---------------*/\
/*#AWB_WINDOW*/\
UP_SET(2, UpAWB_HSP,=200)/* AWB detection area X start (default +- value) */\
UP_SET(2, UpAWB_HW)/* AWB detection area Y end (default +- value) */\
UP_SET(2, UpAWB_VSP)/* AWB detection area Y start (default +- value) */\
UP_SET(2, UpAWB_VW)/* AWB detection area Y end (default +- value) */\
/*#AWB_PAR*/\
UP_SET(2, UpAWB_TCNT_LMT)/* White pixel cnt limit to minimum (under 0x10000) */\
UP_SET(2, UpAWB_DBOFFSET)/* Color map coordinate x offset (default +- value) */\
UP_SET(2, UpAWB_DROFFSET)/* Color map coordinate y offset (default +- value) */\
UP_SET(2, UpAWB_AGC_MIN)/* Chroma AGC position for maximum weight (default +- value) */\
UP_SET(2, UpAWB_AGC_MAX)/* Chroma AGC position for minimum weight (default +- value) */\
UP_SET(2, UpAWB_WDR_AGC_MIN)/* When WDR Mode, Chroma AGC position for maximum weight (default +- value) */\
UP_SET(2, UpAWB_WDR_AGC_MAX)/* When WDR Mode, Chroma AGC position for minimum weight (default +- value) */\
UP_SET(1, UpAWB_AGC_WGT_MIN)/* Chroma minimum weight (under 0x100(100%)) */\
UP_SET(1, UpAWB_SPEED_MTRX)/* Matrix tracking speed (Low is high speed, max=0xff) */\
UP_SET(2, UpAWB_YSLICE)/* White Y slice (under 0x3ff) */\
UP_SET(2, UpAWB_YCLIP)/* White Y clip (under 0x3ff, more than UpAWB_YSLICE) */\
UP_SET(1, UpAWB_GAIN_TIMES)/* RGB Gain limit (X times, under 4) */\
/*#C_TEMP_PAR*/\
UP_SET(2, UpAWB_TEMP_DR_L)/* */\
UP_SET(2, UpAWB_TEMP_DR_M)/* */\
UP_SET(2, UpAWB_TEMP_DR_H)/* */\
UP_SET(2, UpAWB_TEMP_VAL_L)/* */\
UP_SET(2, UpAWB_TEMP_VAL_M)/* */\
UP_SET(2, UpAWB_TEMP_VAL_H)/* */\
UP_SET(2, UpAWB_R_WGT)/* Red weight for AWB in Low temperature */\
UP_SET(2, UpAWB_G_WGT)/* Green weight for AWB in Low temperature */\
UP_SET(2, UpAWB_B_WGT)/* Blue weight for AWB in Low temperature */\
UP_SET(2, UpAWB_5000K_AGC_TH)/* */\
/*#AWB_POST_CCM*/\
UP_SET(2, UpCCM_TEMP_L)/* */\
UP_SET(2, UpCCM_TEMP_M)/* */\
UP_SET(2, UpCCM_TEMP_H)/* */\
UP_SET(2, UpCCM_RR_TEMP_L)/* */\
UP_SET(2, UpCCM_RG_TEMP_L)/* */\
UP_SET(2, UpCCM_RB_TEMP_L)/* */\
UP_SET(2, UpCCM_GR_TEMP_L)/* */\
UP_SET(2, UpCCM_GG_TEMP_L)/* */\
UP_SET(2, UpCCM_GB_TEMP_L)/* */\
UP_SET(2, UpCCM_BR_TEMP_L)/* */\
UP_SET(2, UpCCM_BG_TEMP_L)/* */\
UP_SET(2, UpCCM_BB_TEMP_L)/* */\
UP_SET(2, UpCCM_RR_TEMP_M)/* */\
UP_SET(2, UpCCM_RG_TEMP_M)/* */\
UP_SET(2, UpCCM_RB_TEMP_M)/* */\
UP_SET(2, UpCCM_GR_TEMP_M)/* */\
UP_SET(2, UpCCM_GG_TEMP_M)/* */\
UP_SET(2, UpCCM_GB_TEMP_M)/* */\
UP_SET(2, UpCCM_BR_TEMP_M)/* */\
UP_SET(2, UpCCM_BG_TEMP_M)/* */\
UP_SET(2, UpCCM_BB_TEMP_M)/* */\
UP_SET(2, UpCCM_RR_TEMP_H)/* */\
UP_SET(2, UpCCM_RG_TEMP_H)/* */\
UP_SET(2, UpCCM_RB_TEMP_H)/* */\
UP_SET(2, UpCCM_GR_TEMP_H)/* */\
UP_SET(2, UpCCM_GG_TEMP_H)/* */\
UP_SET(2, UpCCM_GB_TEMP_H)/* */\
UP_SET(2, UpCCM_BR_TEMP_H)/* */\
UP_SET(2, UpCCM_BG_TEMP_H)/* */\
UP_SET(2, UpCCM_BB_TEMP_H)/* */\
/*#AWB SLICE*/\
UP_SET(2, UpAWB_SLIC_OFST_PT0)/* */\
UP_SET(2, UpAWB_SLIC_OFST_PT1)/* */\
UP_SET(2, UpAWB_SLIC_OFST_PT2)/* */\
UP_SET(1, UpAWB_SLIC_OFST_VAL0)/* */\
UP_SET(1, UpAWB_SLIC_OFST_VAL1)/* */\
UP_SET(1, UpAWB_SLIC_OFST_VAL2)/* */\
/*---------------  COLOR  SUPPRESSION  ---------------*/\
/*#LSUP*/\
UP_SET(1, UpLSUP_ON,=340)/* Low Light color suppression on/off (0: off, 1: on) */\
UP_SET(2, UpLSUP_GA_AGC_PT0)/* Low Light color suppression threshold (Y domain control)  */\
UP_SET(2, UpLSUP_GA_AGC_PT1)/* Low Light color suppression threshold (Y domain control)  */\
UP_SET(1, UpLSUP_GA_VAL_PT0)/* Low Light color suppression threshold (Y domain control) (0 ~ 0xFF) */\
UP_SET(1, UpLSUP_GA_VAL_PT1)/* Low Light color suppression threshold (Y domain control) (0 ~ 0xFF) */\
UP_SET(1, UpLSUP_TH)/* Low Light color suppression threshold (0 ~ 0xFF) */\
/*#CSUP*/\
UP_SET(1, UpCSUP_ON)/* High Light color suppression on/off (Y domain control) (0: off, 1: on) */\
UP_SET(1, UpCSUP_GA)/* High Light color suppression gain (Y domain control) (0x40 = x0.5, 0x80 = x1, 0xC0 = x1.5, 0xff = x2) */\
UP_SET(2, UpCSUP_TH_AGC_PT0)/* High Light color suppression threshold (Y domain control)  */\
UP_SET(2, UpCSUP_TH_AGC_PT1)/* High Light color suppression threshold (Y domain control)  */\
UP_SET(1, UpCSUP_TH_VAL_PT0)/* High Light color suppression threshold (Y domain control) (0 ~ 0xFF) */\
UP_SET(1, UpCSUP_TH_VAL_PT1)/* High Light color suppression threshold (Y domain control) (0 ~ 0xFF) */\
/*#CESUP*/\
UP_SET(1, UpCES_ON)/* Color edge suppression on/off (0:Off, 1:On) */\
UP_SET(1, UpCES_GA)/* Color edge suppression gain (0x40 = x0.5, 0x80 = x1, 0xC0 = x1.5, 0xff = x2) */\
UP_SET(2, UpCES_TH_AGC_PT0)/* Color edge suppression clip */\
UP_SET(2, UpCES_TH_AGC_PT1)/* Color edge suppression clip */\
UP_SET(1, UpCES_TH_VAL_PT0)/* Color edge suppression clip */\
UP_SET(1, UpCES_TH_VAL_PT1)/* Color edge suppression clip */\
/*---------------  HUE  &  GAIN  ---------------*/\
/*#TEMP*/\
UP_SET(2, UpHnG_TEMP_L,=380)/* */\
UP_SET(2, UpHnG_TEMP_M)/* */\
UP_SET(2, UpHnG_TEMP_H)/* */\
/*#TEMP_LOW*/\
UP_SET(1, UpBY_GAINN_TEMP_L)/* B-Y Negative Gain Control (0 ~ 0xFF, Default:0x60) */\
UP_SET(1, UpBY_GAINP_TEMP_L)/* B-Y Positive Gain Control (0 ~ 0xFF, Default:0x60) */\
UP_SET(1, UpRY_GAINN_TEMP_L)/* R-Y Negative Gain Control (0 ~ 0xFF, Default:0x60) */\
UP_SET(1, UpRY_GAINP_TEMP_L)/* R-Y Positive Gain Control (0 ~ 0xFF, Default:0x60) */\
UP_SET(1, UpBY_HUEN_TEMP_L)/* B-Y Negative Hue Control (0x1:-90  , 0x80:0  , 0xFF:90  ) */\
UP_SET(1, UpBY_HUEP_TEMP_L)/* B-Y Positive Hue Control (0x1:-90  , 0x80:0  , 0xFF:90  ) */\
UP_SET(1, UpRY_HUEN_TEMP_L)/* R-Y Negative Hue Control (0x1:-90  , 0x80:0  , 0xFF:90  ) */\
UP_SET(1, UpRY_HUEP_TEMP_L)/* R-Y Positive Hue Control (0x1:-90  , 0x80:0  , 0xFF:90  ) */\
/*#TEMP_MID*/\
UP_SET(1, UpBY_GAINN_TEMP_M)/* B-Y Negative Gain Control (0 ~ 0xFF, Default:0x60) */\
UP_SET(1, UpBY_GAINP_TEMP_M)/* B-Y Positive Gain Control (0 ~ 0xFF, Default:0x60) */\
UP_SET(1, UpRY_GAINN_TEMP_M)/* R-Y Negative Gain Control (0 ~ 0xFF, Default:0x60) */\
UP_SET(1, UpRY_GAINP_TEMP_M)/* R-Y Positive Gain Control (0 ~ 0xFF, Default:0x60) */\
UP_SET(1, UpBY_HUEN_TEMP_M)/* B-Y Negative Hue Control (0x1:-90  , 0x80:0  , 0xFF:90  ) */\
UP_SET(1, UpBY_HUEP_TEMP_M)/* B-Y Positive Hue Control (0x1:-90  , 0x80:0  , 0xFF:90  ) */\
UP_SET(1, UpRY_HUEN_TEMP_M)/* R-Y Negative Hue Control (0x1:-90  , 0x80:0  , 0xFF:90  ) */\
UP_SET(1, UpRY_HUEP_TEMP_M)/* R-Y Positive Hue Control (0x1:-90  , 0x80:0  , 0xFF:90  ) */\
/*#TEMP_HI*/\
UP_SET(1, UpBY_GAINN_TEMP_H)/* B-Y Negative Gain Control (0 ~ 0xFF, Default:0x60) */\
UP_SET(1, UpBY_GAINP_TEMP_H)/* B-Y Positive Gain Control (0 ~ 0xFF, Default:0x60) */\
UP_SET(1, UpRY_GAINN_TEMP_H)/* R-Y Negative Gain Control (0 ~ 0xFF, Default:0x60) */\
UP_SET(1, UpRY_GAINP_TEMP_H)/* R-Y Positive Gain Control (0 ~ 0xFF, Default:0x60) */\
UP_SET(1, UpBY_HUEN_TEMP_H)/* B-Y Negative Hue Control (0x1:-90  , 0x80:0  , 0xFF:90  ) */\
UP_SET(1, UpBY_HUEP_TEMP_H)/* B-Y Positive Hue Control (0x1:-90  , 0x80:0  , 0xFF:90  ) */\
UP_SET(1, UpRY_HUEN_TEMP_H)/* R-Y Negative Hue Control (0x1:-90  , 0x80:0  , 0xFF:90  ) */\
UP_SET(1, UpRY_HUEP_TEMP_H)/* R-Y Positive Hue Control (0x1:-90  , 0x80:0  , 0xFF:90  ) */\
/*---------------  GAMMA  ---------------*/\
UP_SET(1, UpGAMMA_Y_ON,=420)/* Y GAMMA on/off (0: off, 1: on) */\
UP_SET(1, UpGAMMA_C_ON)/* C GAMMA on/off (0:off, 1:on) */\
UP_SET(2, UpYGMA_AGC_PT0)/* Apply Y Gamma1 interlocking point 0 */\
UP_SET(2, UpYGMA_AGC_PT1)/* Apply Y Gamma2 interlocking point 1 */\
UP_SET(2, UpCGMA_AGC_PT0)/* Apply C Gamma1 interlocking point 0 */\
UP_SET(2, UpCGMA_AGC_PT1)/* Apply C Gamma2 interlocking point 1 */\
UP_SET(2, UpYGMA_WDR_AGC_PT0)/* Apply Y Gamma1 interlocking point 0 */\
UP_SET(2, UpYGMA_WDR_AGC_PT1)/* Apply Y Gamma2 interlocking point 1 */\
UP_SET(2, UpCGMA_WDR_AGC_PT0)/* Apply C Gamma1 interlocking point 0 */\
UP_SET(2, UpCGMA_WDR_AGC_PT1)/* Apply C Gamma2 interlocking point 1 */\
/*---------------  DNR  ---------------*/\
/*#DNR_AGC_PT*/\
UP_SET(2, UpDNR_AGC_PT0,=460)/* AGC interlocking point 0 in DNR function (0x0 ~ UpDNR_AGC_PT1) */\
UP_SET(2, UpDNR_AGC_PT1)/* AGC interlocking point 1 in DNR function (0x0 ~ UpDNR_AGC_PT2) */\
UP_SET(2, UpDNR_AGC_PT2)/* AGC interlocking point 2 in DNR function (0x0 ~ AGC Max value) */\
UP_SET(2, UpDNR_WDR_AGC_PT0)/* AGC interlocking point 0 in DNR function of WDR (0x0 ~ UpDNR_WDR_AGC_PT1) */\
UP_SET(2, UpDNR_WDR_AGC_PT1)/* AGC interlocking point 1 in DNR function of WDR (0x0 ~ UpDNR_WDR_AGC_PT2) */\
UP_SET(2, UpDNR_WDR_AGC_PT2)/* AGC interlocking point 2 in DNR function of WDR (0x0 ~ AGC Max value) */\
/*#DNR_VAL_OFST*/\
UP_SET(1, UpDNR_AGC_OFST_PVAL0)/* DNR Q-table point 0 plus offset */\
UP_SET(1, UpDNR_AGC_OFST_PVAL1)/* DNR Q-table point 1 plus offset */\
UP_SET(1, UpDNR_AGC_OFST_PVAL2)/* DNR Q-table point 2 plus offset */\
UP_SET(1, UpDNR_AGC_OFST_MVAL0)/* DNR Q-table point 0 minus offset */\
UP_SET(1, UpDNR_AGC_OFST_MVAL1)/* DNR Q-table point 1 minus offset */\
UP_SET(1, UpDNR_AGC_OFST_MVAL2)/* DNR Q-table point 2 minus offset */\
/*#DNR_HPF_AGC_PT*/\
UP_SET(2, UpDNR_AGC_HPF_PT0)/* AGC interlocking point 0 in DNR function (0x0 ~ UpDNR_AGC_HPF_PT1) */\
UP_SET(2, UpDNR_AGC_HPF_PT1)/* AGC interlocking point 1 in DNR function (0x0 ~ UpDNR_AGC_HPF_PT2) */\
UP_SET(2, UpDNR_AGC_HPF_PT2)/* AGC interlocking point 2 in DNR function (0x0 ~ AGC Max value) */\
/*#DNR_HPF_GAIN*/\
UP_SET(1, UpDNR_HPF_GAIN_LV0_PT0)/* HPF gain LV0 (corresponding to AGC interlocking Point 0) (0x0 ~ 0x7) */\
UP_SET(1, UpDNR_HPF_GAIN_LV0_PT1)/* HPF gain LV0 (corresponding to AGC interlocking Point 1) (0x0 ~ 0x7) */\
UP_SET(1, UpDNR_HPF_GAIN_LV0_PT2)/* HPF gain LV0 (corresponding to AGC interlocking Point 2) (0x0 ~ 0x7) */\
UP_SET(1, UpDNR_HPF_GAIN_LV1_PT0)/* HPF gain interlocking point 0 in DNR function (0x0 ~ 0x7) */\
UP_SET(1, UpDNR_HPF_GAIN_LV1_PT1)/* HPF gain interlocking point 1 in DNR function (0x0 ~ 0x7) */\
UP_SET(1, UpDNR_HPF_GAIN_LV1_PT2)/* HPF gain interlocking point 2 in DNR function (0x0 ~ 0x7) */\
UP_SET(1, UpDNR_HPF_GAIN_LV2_PT0)/* HPF gain interlocking point 0 in DNR function (0x0 ~ 0x7) */\
UP_SET(1, UpDNR_HPF_GAIN_LV2_PT1)/* HPF gain interlocking point 1 in DNR function (0x0 ~ 0x7) */\
UP_SET(1, UpDNR_HPF_GAIN_LV2_PT2)/* HPF gain interlocking point 2 in DNR function (0x0 ~ 0x7) */\
/*---------------  SHARPNESS  ---------------*/\
UP_SET(1, UpSHARPNESS_GAIN,=500)/* Sharpness Gain (0=OFF, 1=x5, 2=x2.5, 3=x1.67, 4=1.25, 5=x1, 6=x0.83, 8=x0.625, 0xA=x0.5, 0x14=x0.25, 0x32=x0.1) */\
UP_SET(1, UpSHARPNESS_GAIN_CVBS)/* Sharpness Gain CVBS(0=OFF, 1=x5, 2=x2.5, 3=x1.67, 4=1.25, 5=x1, 6=x0.83, 8=x0.625, 0xA=x0.5, 0x14=x0.25, 0x32=x0.1) */\
/*#SHARPNESS_AGC_PT*/\
UP_SET(2, UpSHP_AGC_PT0)/* AGC interlocking point 0 in sharpness function (0x0 ~ UpSHP_AGC_PT1) */\
UP_SET(2, UpSHP_AGC_PT1)/* AGC interlocking point 1 in sharpness function (UpSHP_AGC_PT0 ~ UpSHP_AGC_PT1) */\
UP_SET(2, UpSHP_AGC_PT2)/* AGC interlocking point 2 in sharpness function (UpSHP_AGC_PT1 ~ AGC Max value) */\
UP_SET(2, UpSHP_WDR_AGC_PT0)/* AGC interlocking point 0 in sharpness function of WDR (0x0 ~ UpSHP_AGC_PT1) */\
UP_SET(2, UpSHP_WDR_AGC_PT1)/* AGC interlocking point 1 in sharpness function of WDR (UpSHP_AGC_PT0 ~ UpSHP_AGC_PT1) */\
UP_SET(2, UpSHP_WDR_AGC_PT2)/* AGC interlocking point 2 in sharpness function of WDR (UpSHP_AGC_PT1 ~ AGC Max value) */\
/*#SHARPNESS_PT0*/\
UP_SET(2, UpAPT55_TH1_PT0)/* Sharpness 5x5 threshold 1 (corresponding to Point 0) (0x0 ~ UpAPT55_TH2_PT0) */\
UP_SET(2, UpAPT55_TH2_PT0)/* Sharpness 5x5 threshold 2 (corresponding to Point 0) (0x0 ~ 0xFFF) */\
UP_SET(2, UpAPT55_TH3_PT0)/* Sharpness 5x5 threshold 3 (corresponding to Point 0) (0x0 ~ 0x3FF) */\
UP_SET(1, UpAPT55_GAIN1N_PT0)/* Sharpness 5x5 gain negative edge 1 (corresponding to Point 0) (0x0 ~ 0xFF) */\
UP_SET(1, UpAPT55_GAIN2N_PT0)/* Sharpness 5x5 gain negative edge 2 (corresponding to Point 0) (0x0 ~ 0xFF) */\
UP_SET(1, UpAPT55_GAIN1P_PT0)/* Sharpness 5x5 gain positive edge 1 (corresponding to Point 0) (0x0 ~ 0xFF) */\
UP_SET(1, UpAPT55_GAIN2P_PT0)/* Sharpness 5x5 gain positive edge 2 (corresponding to Point 0) (0x0 ~ 0xFF) */\
UP_SET(2, UpAPT33_SLIC_PT0)/* Sharpness 3x3 slice value (corresponding to Point 0) ((0x0 ~ 0x3FF) */\
UP_SET(2, UpAPT33_CLIP_PT0)/* Sharpness 3x3 clip value (corresponding to Point 0) (0x0 ~ 0x3FF) */\
UP_SET(1, UpAPT33_GAIN_PT0)/* Sharpness 3x3 gain (corresponding to Point 0) (0x0 ~ 0xFF) */\
/*#SHARPNESS_PT1*/\
UP_SET(2, UpAPT55_TH1_PT1)/* Sharpness 5x5 threshold 1 (corresponding to Point 1) (0x0 ~ UpAPT55_TH2_PT1) */\
UP_SET(2, UpAPT55_TH2_PT1)/* Sharpness 5x5 threshold 2 (corresponding to Point 1) (0x0 ~ 0xFFF) */\
UP_SET(2, UpAPT55_TH3_PT1)/* Sharpness 5x5 threshold 3 (corresponding to Point 1) (0x0 ~ 0x3FF) */\
UP_SET(1, UpAPT55_GAIN1N_PT1)/* Sharpness 5x5 negative gain 1 (corresponding to Point 1) (0x0 ~ 0xFF) */\
UP_SET(1, UpAPT55_GAIN2N_PT1)/* Sharpness 5x5 negative gain 2 (corresponding to Point 1) (0x0 ~ 0xFF) */\
UP_SET(1, UpAPT55_GAIN1P_PT1)/* Sharpness 5x5 positive gain 1 (corresponding to Point 1) (0x0 ~ 0xFF) */\
UP_SET(1, UpAPT55_GAIN2P_PT1)/* Sharpness 5x5 positive gain 2 (corresponding to Point 1) (0x0 ~ 0xFF) */\
UP_SET(2, UpAPT33_SLIC_PT1)/* Sharpness 3x3 slice value (corresponding to Point 1) (0x0 ~ 0x3FF) */\
UP_SET(2, UpAPT33_CLIP_PT1)/* Sharpness 3x3 clip value (corresponding to Point 1) (0x0 ~ 0x3FF) */\
UP_SET(1, UpAPT33_GAIN_PT1)/* Sharpness 3x3 gain (corresponding to Point 1) (0x0 ~ 0xFF) */\
/*#SHARPNESS_PT2*/\
UP_SET(2, UpAPT55_TH1_PT2)/* Sharpness 5x5 threshold 1 (corresponding to Point 2) (0x0 ~ UpAPT55_TH2_PT2) */\
UP_SET(2, UpAPT55_TH2_PT2)/* Sharpness 5x5 threshold 2 (corresponding to Point 2) (0x0 ~ 0xFFF) */\
UP_SET(2, UpAPT55_TH3_PT2)/* Sharpness 5x5 threshold 3 (corresponding to Point 2) (0x0 ~ 0x3FF) */\
UP_SET(1, UpAPT55_GAIN1N_PT2)/* Sharpness 5x5 negative gain 1 (corresponding to Point 2) (0x0 ~ 0xFF) */\
UP_SET(1, UpAPT55_GAIN2N_PT2)/* Sharpness 5x5 negative gain 2 (corresponding to Point 2) (0x0 ~ 0xFF) */\
UP_SET(1, UpAPT55_GAIN1P_PT2)/* Sharpness 5x5 positive gain 1 (corresponding to Point 2) (0x0 ~ 0xFF) */\
UP_SET(1, UpAPT55_GAIN2P_PT2)/* Sharpness 5x5 positive gain 2 (corresponding to Point 2) (0x0 ~ 0xFF) */\
UP_SET(2, UpAPT33_SLIC_PT2)/* Sharpness 3x3 slice value (corresponding to Point 2) (0x0 ~ 0x3FF) */\
UP_SET(2, UpAPT33_CLIP_PT2)/* Sharpness 3x3 clip value (corresponding to Point 2) (0x0 ~ 0x3FF) */\
UP_SET(1, UpAPT33_GAIN_PT2)/* Sharpness 3x3 gain (corresponding to Point 2) (0x0 ~ 0xFF) */\
/*---------------  DEFOG  ---------------*/\
/*#DEFOG*/\
UP_SET(2, UpDEFOG_TH_LOW,=570)/* Defog Maximum Strength for menu LOW (0x0 ~ 0xffff) */\
UP_SET(2, UpDEFOG_TH_MID)/* Defog Maximum Strength for menu MIDDLE (LOW ~ 0xffff) */\
UP_SET(2, UpDEFOG_TH_HIGH)/* Defog Maximum Strength for menu HIGH (MIDDLE ~ 0xffff) */\
/*---------------  ACE  ---------------*/\
/*#ACE_Common*/\
UP_SET(1, UpACE_IIR,=590)/* ACE IIR coefficient (0x0 ~ 0x3f) */\
UP_SET(1, UpACE_DTH)/* Threshold dividing histogram into 2 areas [Histogram Area smaller Than DTH Value means TH1[Dark Area],In the opposite, TH2[Bright Area] */\
UP_SET(1, UpACE_WDR_DTH)/* When WDR Mode, Threshold dividing histogram into 2 areas [Histogram Area Smaller Than DTH Value means TH1[Dark Area],In the opposite, TH2[Bright Area] */\
/*#ACE_AGC_PT*/\
UP_SET(2, UpACE_AGC_PT0)/* AGC interlocking point 0 in ACE function */\
UP_SET(2, UpACE_AGC_PT1)/* AGC interlocking point 1 in ACE function */\
UP_SET(2, UpACE_AGC_PT2)/* AGC interlocking point 2 in ACE function */\
UP_SET(2, UpACE_WDR_AGC_PT0)/* When WDR Mode, AGC interlocking point 0 in ACE function */\
UP_SET(2, UpACE_WDR_AGC_PT1)/* When WDR Mode, AGC interlocking point 1 in ACE function */\
UP_SET(2, UpACE_WDR_AGC_PT2)/* When WDR Mode, AGC interlocking point 2 in ACE function */\
/*#ACE_PT0*/\
UP_SET(1, UpACE_TH1_LOW_VAL_PT0)/* When ACE-LOW, Value to be applied to TH1 Area corresponding to interlocking point 0 (Apply to TH1[Dark Area]) */\
UP_SET(1, UpACE_TH1_MID_VAL_PT0)/* When ACE-MID, Value to be applied to TH1 Area corresponding to interlocking point 0 (Apply to TH1[Dark Area]) */\
UP_SET(1, UpACE_TH1_HIGH_VAL_PT0)/* When ACE-HIGH, Value to be applied to TH1 Area corresponding to interlocking point 0 (Apply to TH1[Dark Area]) */\
UP_SET(1, UpACE_TH2_LOW_VAL_PT0)/* When ACE-LOW, Value to be applied to TH2 Area corresponding to interlocking point 0 (Apply to TH2[Bright Area]) */\
UP_SET(1, UpACE_TH2_MID_VAL_PT0)/* When ACE-MID, Value to be applied to TH2 Area corresponding to interlocking point 0 (Apply to TH2[Bright Area]) */\
UP_SET(1, UpACE_TH2_HIGH_VAL_PT0)/* When ACE-HIGH, Value to be applied to TH2 Area corresponding to interlocking point 0 (Apply to TH2[Bright Area]) */\
/*#ACE_PT1*/\
UP_SET(1, UpACE_TH1_LOW_VAL_PT1)/* When ACE-LOW, Value to be applied to TH1 Area corresponding to interlocking point 1 (Apply to TH1[Dark Area]) */\
UP_SET(1, UpACE_TH1_MID_VAL_PT1)/* When ACE-MID, Value to be applied to TH1 Area corresponding to interlocking point 1 (Apply to TH1[Dark Area]) */\
UP_SET(1, UpACE_TH1_HIGH_VAL_PT1)/* When ACE-HIGH, Value to be applied to TH1 Area corresponding to interlocking point 1 (Apply to TH1[Dark Area]) */\
UP_SET(1, UpACE_TH2_LOW_VAL_PT1)/* When ACE-LOW, Value to be applied to TH2 Area corresponding to interlocking point 1 (Apply to TH2[Bright Area]) */\
UP_SET(1, UpACE_TH2_MID_VAL_PT1)/* When ACE-MID, Value to be applied to TH2 Area corresponding to interlocking point 1 (Apply to TH2[Bright Area]) */\
UP_SET(1, UpACE_TH2_HIGH_VAL_PT1)/* When ACE-HIGH, Value to be applied to TH2 Area corresponding to interlocking point 1 (Apply to TH2[Bright Area]) */\
/*#ACE_PT2*/\
UP_SET(1, UpACE_TH1_VAL_PT2)/* Value to be applied to TH1 Area corresponding to interlocking point 2 (Apply to TH1[Dark Area]) */\
UP_SET(1, UpACE_TH2_VAL_PT2)/* Value to be applied to TH2 Area corresponding to interlocking point 2 (Apply to TH2[Bright Area]) */\
/*#ACE_GMGN*/\
UP_SET(1, UpACE_GMGN_VAL_PT0)/* Gamma corresponding to interlocking point 0 */\
UP_SET(1, UpACE_GMGN_VAL_PT1)/* Gamma corresponding to interlocking point 1 */\
UP_SET(1, UpACE_GMGN_VAL_PT2)/* Gamma corresponding to interlocking point 2 */\
/*#ACE_WDR_PT*/\
UP_SET(1, UpACE_WDR_TH1_VAL_PT0)/* When WDR Mode, Value to be applied to TH1 Area corresponding to interlocking point 0 (Apply to TH1[Dark Area])(Range : 0x0 ~ 0xff) */\
UP_SET(1, UpACE_WDR_TH1_VAL_PT1)/* When WDR Mode, Value to be applied to TH1 Area corresponding to interlocking point 1 (Apply to TH1[Dark Area])(Range : 0x0 ~ 0xff) */\
UP_SET(1, UpACE_WDR_TH1_VAL_PT2)/* When WDR Mode, Value to be applied to TH1 Area corresponding to interlocking point 2 (Apply to TH1[Dark Area])(Range : 0x0 ~ 0xff) */\
UP_SET(1, UpACE_WDR_TH2_VAL_PT0)/* When WDR Mode, Value to be applied to TH2 Area corresponding to interlocking point 0 (Apply to TH2[Bright Area])(Range : 0x0 ~ 0xff) */\
UP_SET(1, UpACE_WDR_TH2_VAL_PT1)/* When WDR Mode, Value to be applied to TH2 Area corresponding to interlocking point 1 (Apply to TH2[Bright Area])(Range : 0x0 ~ 0xff) */\
UP_SET(1, UpACE_WDR_TH2_VAL_PT2)/* When WDR Mode, Value to be applied to TH2 Area corresponding to interlocking point 2 (Apply to TH2[Bright Area])(Range : 0x0 ~ 0xff) */\
/*#ACE_WDR_GMGN*/\
UP_SET(1, UpACE_WDR_GMGN_VAL_PT0)/* When WDR Mode, Gamma corresponding to interlocking point 0 */\
UP_SET(1, UpACE_WDR_GMGN_VAL_PT1)/* When WDR Mode, Gamma corresponding to interlocking point 1 */\
UP_SET(1, UpACE_WDR_GMGN_VAL_PT2)/* When WDR Mode, Gamma corresponding to interlocking point 2 */\
/*---------------  HIGH  LIGHT  MASK  ---------------*/\
UP_SET(1, UpHLMASK_THRS_STEP,=640)/* Menu Step of High Light masking level (0 ~ 0xA) */\
UP_SET(1, UpHLMASK_CY)/* HLMASK CY of Color for Customize Color Menu (0 ~ 0xFF) */\
UP_SET(1, UpHLMASK_CB)/* HLMASK CB of Color for Customize Color Menu (0 ~ 0xFF) */\
UP_SET(1, UpHLMASK_CR)/* HLMASK CR of Color for Customize Color Menu (0 ~ 0xFF) */\
/*---------------  DEFECT  ---------------*/\
UP_SET(2, UpDEFECT_AGC_PT0,=650)/* AGC value of Rather dark for control defect. (0 ~ 0x1F4 AGC value) */\
UP_SET(2, UpDEFECT_AGC_PT1)/* AGC value of Dark for control defect. (MIN ~ 0x1F4 AGC value) */\
UP_SET(2, UpDEFECT_AGC_PT2)/* AGC value of Very dark for control defect. (MIDDLE ~ 0x1F4 AGC value) */\
UP_SET(1, UpDEFECT_GA)/* Within the pattern, this parameter uses to detect directional defect. Difference gain for isolated point determination. (0x40 = x0.5, 0x80 = x1, 0xC0 = x1.5, 0xff = x2) */\
UP_SET(1, UpDEFECT_SPOT_GA)/* Spot pattern area gain. (0x40 = x0.5, 0x80 = x1, 0xC0 = x1.5, 0xff = x2) */\
UP_SET(1, UpDEFECT_TSEL)/* Select test image in core for directional defect correction. (VLOCKI)  "0" : Normal operation  "1" : Difference values for isolated points  "2" : Image before correction  "3" : Complete correction image (100% correction image except weight).  "4" : Defect pattern detection value */\
/*---------------  ENCODER  ---------------*/\
UP_SET(1, UpENC_CSTM,=680)/* 0 : Default table, 1 : Cstm parameter*/\
/*#MODE_T*/\
UP_SET(1, UpENC_RYGAINP_T)/* R-Y Positive Gain Control for HD-Analog (0 ~ 0xFF) <MODE_T> */\
UP_SET(1, UpENC_RYGAINN_T)/* R-Y Negative Gain Control for HD-Analog (0 ~ 0xFF) <MODE_T> */\
UP_SET(1, UpENC_BYGAINP_T)/* B-Y Positive Gain Control for HD-Analog (0 ~ 0xFF) <MODE_T> */\
UP_SET(1, UpENC_BYGAINN_T)/* B-Y Negative Gain Control for HD-Analog (0 ~ 0xFF) <MODE_T> */\
UP_SET(1, UpENC_RYHUEP_T)/* R-Y Positive Hue Control for HD-Analog <MODE_T> */\
UP_SET(1, UpENC_RYHUEN_T)/* R-Y Negative Hue Control for HD-Analog <MODE_T> */\
UP_SET(1, UpENC_BYHUEP_T)/* B-Y Positive Hue Control for HD-Analog <MODE_T> */\
UP_SET(1, UpENC_BYHUEN_T)/* B-Y Negative Hue Control for HD-Analog <MODE_T> */\
UP_SET(2, UpWHITE_LV_T)/* White level control parameter <MODE_T> */\
UP_SET(2, UpBLANK_LV_T)/* Blank level control parameter <MODE_T> */\
UP_SET(2, UpPEDESTAL_LV_T)/* Pedestal level control parameter <MODE_T> */\
UP_SET(4, UpFSC_TGT_T)/* Deciding Target for SubCarrier Frequency <MODE_T> */\
UP_SET(2, UpY_MGAIN_T)/* Gain to be Multiplied to Y Output Value <MODE_T> */\
UP_SET(2, UpCB_MGAIN_T)/* Gain to be Multiplied to Cb Value <MODE_T> */\
UP_SET(2, UpCR_MGAIN_T)/* Gain to be Multiplied to Cr Value <MODE_T> */\
UP_SET(2, UpCB_BST_T)/* Burst amplitude & phase select parameter(Cr) <MODE_T> */\
UP_SET(2, UpCR_BST_T)/* Burst amplitude & phase select parameter(Cb) <MODE_T> */\
UP_SET(2, UpHSC_K_T)/* Horizontal Scaler Ratio <MODE_T> */\
UP_SET(2, UpHLOCK_CAT_T)/* Video Encoder internal H sync delay parameter based on input H sync <MODE_T> */\
UP_SET(2, UpVLOCK_CAT_EV_T)/* Contolling Vertical Locking Catch Point(Even field) <MODE_T> */\
UP_SET(2, UpVLOCK_CAT_OD_T)/* Contolling Vertical Locking Catch Point(Odd field) <MODE_T> */\
UP_SET(2, UpCRX_AUTO_CAT_T)/* Delays the UTC data catching point of the corresponding parameter value from the first high signal, and the following datas are catched of the period of BITRATE (proceeded in the range of [UpCRX_HPOSEVS ~ UpCRX_HPOSEVE]) <MODE_T> */\
UP_SET(2, UpCRX_HPOSEVS_T)/* When UTC Communication, Start Position of Data Catching Point <MODE_T> */\
UP_SET(2, UpCRX_HPOSEVE_T)/* When UTC Communication, End Position of Data Catching Point <MODE_T> */\
UP_SET(2, UpCRX_BITRATE_T)/* Decides the Catching Period of UTC Data <MODE_T> */\
/*#MODE_C*/\
UP_SET(1, UpENC_RYGAINP_C)/* R-Y Positive Gain Control for HD-Analog(0 ~ 0xFF) <MODE_C> */\
UP_SET(1, UpENC_RYGAINN_C)/* R-Y Negative Gain Control for HD-Analog(0 ~ 0xFF) <MODE_C> */\
UP_SET(1, UpENC_BYGAINP_C)/* B-Y Positive Gain Control for HD-Analog(0 ~ 0xFF) <MODE_C> */\
UP_SET(1, UpENC_BYGAINN_C)/* B-Y Negative Gain Control for HD-Analog(0 ~ 0xFF) <MODE_C> */\
UP_SET(1, UpENC_RYHUEP_C)/* R-Y Positive Hue Control for HD-Analog <MODE_C> */\
UP_SET(1, UpENC_RYHUEN_C)/* R-Y Negative Hue Control for HD-Analog <MODE_C> */\
UP_SET(1, UpENC_BYHUEP_C)/* B-Y Positive Hue Control for HD-Analog <MODE_C> */\
UP_SET(1, UpENC_BYHUEN_C)/* B-Y Negative Hue Control for HD-Analog <MODE_C> */\
UP_SET(2, UpWHITE_LV_C)/* White level control parameter <MODE_C> */\
UP_SET(2, UpBLANK_LV_C)/* Blank level control parameter <MODE_C> */\
UP_SET(2, UpPEDESTAL_LV_C)/* Pedestal level control parameter <MODE_C> */\
UP_SET(4, UpFSC_TGT_C)/* Deciding Target for SubCarrier Frequency <MODE_C> */\
UP_SET(2, UpY_MGAIN_C)/* Gain to be Multiplied to Y Output Value <MODE_C> */\
UP_SET(2, UpCB_MGAIN_C)/* Gain to be Multiplied to Cb Value <MODE_C> */\
UP_SET(2, UpCR_MGAIN_C)/* Gain to be Multiplied to Cr Value <MODE_C> */\
UP_SET(2, UpCB_BST_C)/* Burst amplitude & phase select parameter(Cr) <MODE_C> */\
UP_SET(2, UpCR_BST_C)/* Burst amplitude & phase select parameter(Cb) <MODE_C> */\
UP_SET(2, UpHSC_K_C)/* Horizontal Scaler Ratio <MODE_C> */\
UP_SET(2, UpHLOCK_CAT_C)/* Video Encoder internal H sync delay parameter based on input H sync <MODE_C> */\
UP_SET(2, UpVLOCK_CAT_EV_C)/* Contolling Vertical Locking Catch Point(Even field) <MODE_C> */\
UP_SET(2, UpVLOCK_CAT_OD_C)/* Contolling Vertical Locking Catch Point(Odd field) <MODE_C> */\
UP_SET(2, UpCRX_AUTO_CAT_C)/* Delays the UTC data catching point of the corresponding parameter value from the first high signal, and the following datas are catched of the period of BITRATE (proceeded in the range of [UpCRX_HPOSEVS ~ UpCRX_HPOSEVE]) <MODE_C> */\
UP_SET(2, UpCRX_HPOSEVS_C)/* When UTC Communication, Start Position of Data Catching Point <MODE_C> */\
UP_SET(2, UpCRX_HPOSEVE_C)/* When UTC Communication, End Position of Data Catching Point <MODE_C> */\
UP_SET(2, UpCRX_BITRATE_C)/* Decides the Catching Period of UTC Data <MODE_C> */\
/*#MODE_A*/\
UP_SET(1, UpENC_RYGAINP_A)/* R-Y Positive Gain Control for HD-Analog(0 ~ 0xFF) <MODE_A> */\
UP_SET(1, UpENC_RYGAINN_A)/* R-Y Negative Gain Control for HD-Analog(0 ~ 0xFF) <MODE_A> */\
UP_SET(1, UpENC_BYGAINP_A)/* B-Y Positive Gain Control for HD-Analog(0 ~ 0xFF) <MODE_A> */\
UP_SET(1, UpENC_BYGAINN_A)/* B-Y Negative Gain Control for HD-Analog(0 ~ 0xFF) <MODE_A> */\
UP_SET(1, UpENC_RYHUEP_A)/* R-Y Positive Hue Control for HD-Analog <MODE_A> */\
UP_SET(1, UpENC_RYHUEN_A)/* R-Y Negative Hue Control for HD-Analog <MODE_A> */\
UP_SET(1, UpENC_BYHUEP_A)/* B-Y Positive Hue Control for HD-Analog <MODE_A> */\
UP_SET(1, UpENC_BYHUEN_A)/* B-Y Negative Hue Control for HD-Analog <MODE_A> */\ 
UP_SET(2, UpWHITE_LV_A)/* White level control parameter <MODE_A> */\
UP_SET(2, UpBLANK_LV_A)/* Blank level control parameter <MODE_A> */\
UP_SET(2, UpPEDESTAL_LV_A)/* Pedestal level control parameter <MODE_A> */\
UP_SET(4, UpFSC_TGT_A)/* Deciding Target for SubCarrier Frequency <MODE_A> */\
UP_SET(2, UpY_MGAIN_A)/* Gain to be Multiplied to Y Output Value <MODE_A> */\
UP_SET(2, UpCB_MGAIN_A)/* Gain to be Multiplied to Cb Value <MODE_A> */\
UP_SET(2, UpCR_MGAIN_A)/* Gain to be Multiplied to Cr Value <MODE_A> */\
UP_SET(2, UpCB_BST_A)/* Burst amplitude & phase select parameter(Cr) <MODE_A> */\
UP_SET(2, UpCR_BST_A)/* Burst amplitude & phase select parameter(Cb) <MODE_A> */\
UP_SET(2, UpHSC_K_A)/* Horizontal Scaler Ratio <MODE_A> */\
UP_SET(2, UpHLOCK_CAT_A)/* Video Encoder internal H sync delay parameter based on input H sync <MODE_A> */\
UP_SET(2, UpVLOCK_CAT_EV_A)/* Contolling Vertical Locking Catch Point(Even field) <MODE_A> */\
UP_SET(2, UpVLOCK_CAT_OD_A)/* Contolling Vertical Locking Catch Point(Odd field) <MODE_A> */\
UP_SET(2, UpCRX_AUTO_CAT_A)/* Delays the UTC data catching point of the corresponding parameter value from the first high signal, and the following datas are catched of the period of BITRATE (proceeded in the range of [UpCRX_HPOSEVS ~ UpCRX_HPOSEVE]) <MODE_A> */\
UP_SET(2, UpCRX_HPOSEVS_A)/* When UTC Communication, Start Position of Data Catching Point <MODE_A> */\
UP_SET(2, UpCRX_HPOSEVE_A)/* When UTC Communication, End Position of Data Catching Point <MODE_A> */\
UP_SET(2, UpCRX_BITRATE_A)/* Decides the Catching Period of UTC Data <MODE_A> */\
/*#MODE_CVBS*/\
UP_SET(1, UpENC_RYGAINP_CVBS)/* R-Y Positive Gain Control for HD-Analog(0 ~ 0xFF) <MODE_CVBS> */\
UP_SET(1, UpENC_RYGAINN_CVBS)/* R-Y Negative Gain Control for HD-Analog(0 ~ 0xFF) <MODE_CVBS> */\
UP_SET(1, UpENC_BYGAINP_CVBS)/* B-Y Positive Gain Control for HD-Analog(0 ~ 0xFF) <MODE_CVBS> */\
UP_SET(1, UpENC_BYGAINN_CVBS)/* B-Y Negative Gain Control for HD-Analog(0 ~ 0xFF) <MODE_CVBS> */\
UP_SET(1, UpENC_RYHUEP_CVBS)/* R-Y Positive Hue Control for HD-Analog <MODE_CVBS> */\
UP_SET(1, UpENC_RYHUEN_CVBS)/* R-Y Negative Hue Control for HD-Analog <MODE_CVBS> */\
UP_SET(1, UpENC_BYHUEP_CVBS)/* B-Y Positive Hue Control for HD-Analog <MODE_CVBS> */\
UP_SET(1, UpENC_BYHUEN_CVBS)/* B-Y Negative Hue Control for HD-Analog <MODE_CVBS> */\
UP_SET(2, UpWHITE_LV_CVBS)/* White level control parameter <MODE_CVBS> */\
UP_SET(2, UpBLANK_LV_CVBS)/* Blank level control parameter <MODE_CVBS> */\
UP_SET(2, UpPEDESTAL_LV_CVBS)/* Pedestal level control parameter <MODE_CVBS> */\
UP_SET(4, UpFSC_TGT_CVBS)/* Deciding Target for SubCarrier Frequency <MODE_CVBS> */\
UP_SET(2, UpY_MGAIN_CVBS)/* Gain to be Multiplied to Y Output Value <MODE_CVBS> */\
UP_SET(2, UpCB_MGAIN_CVBS)/* Gain to be Multiplied to Cb Value <MODE_CVBS> */\
UP_SET(2, UpCR_MGAIN_CVBS)/* Gain to be Multiplied to Cr Value <MODE_CVBS> */\
UP_SET(2, UpCB_BST_CVBS)/* Burst amplitude & phase select parameter(Cr) <MODE_CVBS> */\
UP_SET(2, UpCR_BST_CVBS)/* Burst amplitude & phase select parameter(Cb) <MODE_CVBS> */\
UP_SET(2, UpHSC_K_CVBS)/* Horizontal Scaler Ratio <MODE_CVBS> */\
UP_SET(2, UpHLOCK_CAT_CVBS)/* Video Encoder internal H sync delay parameter based on input H sync <MODE_CVBS> */\
UP_SET(2, UpVLOCK_CAT_EV_CVBS)/* Contolling Vertical Locking Catch Point(Even field) <MODE_CVBS> */\
UP_SET(2, UpVLOCK_CAT_OD_CVBS)/* Contolling Vertical Locking Catch Point(Odd field) <MODE_CVBS> */\
UP_SET(2, UpCRX_AUTO_CAT_CVBS)/* Delays the UTC data catching point of the corresponding parameter value from the first high signal, and the following datas are catched of the period of BITRATE (proceeded in the range of [UpCRX_HPOSEVS ~ UpCRX_HPOSEVE]) <MODE_CVBS> */\
UP_SET(2, UpCRX_HPOSEVS_CVBS)/* When UTC Communication, Start Position of Data Catching Point <MODE_CVBS> */\
UP_SET(2, UpCRX_HPOSEVE_CVBS)/* When UTC Communication, End Position of Data Catching Point <MODE_CVBS> */\
UP_SET(2, UpCRX_BITRATE_CVBS)/* Decides the Catching Period of UTC Data <MODE_CVBS> */\
UP_SET(1, UpDKX)/* Horizontal coefficient applied when DownScaler is used <MODE_CVBS> */\
UP_SET(1, UpDKY)/* Vertical coefficient applied when DownScaler is used <MODE_CVBS> */\
UP_SET(2, UpDS_HOFF)/* Horizontal offset applied when DownScaler is used <MODE_CVBS> */\
UP_SET(2, UpDS_VOFF)/* Vertical offset applied when DownScaler is used <MODE_CVBS> */\
/*---------------  AP-3DNR  ---------------*/\
UP_SET(2, Up3DNR_AGC_PT0,=880)/* AGC interlocking point 0 in DNR function */\
UP_SET(2, Up3DNR_AGC_PT1)/* AGC interlocking point 1 in DNR function */\
UP_SET(2, Up3DNR_AGC_PT2)/* AGC interlocking point 2 in DNR function */\
UP_SET(2, Up3DNR_AGC_VAL0)/* AGC interlocking point 0 in DNR function */\
UP_SET(2, Up3DNR_AGC_VAL1)/* AGC interlocking point 1 in DNR function */\
UP_SET(2, Up3DNR_AGC_VAL2)/* AGC interlocking point 2 in DNR function */\
/*---------------  ADAPTIVE-LIGHTING  ---------------*/\
UP_SET(1, UpAE_LED_TuningOn,=960)/* Tuning Mode Enable */\
UP_SET(2, UpAE_LED_TEST_STEP)/* LED_TEST_STEP (0x0 ~ 0xFFFF) */\
UP_SET(3, UpAE_LED_TEST_MIN)/* LED_TEST_MIN (0x0 ~ 0x12E1FC) */\
UP_SET(3, UpAE_LED_TEST_MAX)/* LED_TEST_MAX (0x0 ~ 0x12E1FC) */\
UP_SET(1, UpAE_LED_TEST_RUN)/* Start Test */\
UP_SET(1, UpAE_LED_AePos_STOP)/* Fix ae position to current position */\
UP_SET(3, UpAE_LED_LED)/* PWM duty control (0x0 ~ 0x12E1FC) */\
UP_SET(2, UpAE_LED_AGC)/* Apply AGC value manually (0x0 ~ 0xFFFF) */\
UP_SET(2, UpAE_LED_HEP_Hz)/* PWM frequency control (0x0 ~ 0xFFFF) */\
/*---------------  HV-REVERSE  ---------------*/\
UP_SET(1, UpMirror,=1000)/* Horizontal Reverse */\
UP_SET(1, UpFlip)/* Vertical Reverse */\
/*---------------  PAR-VER  ---------------*/\
UP_SET(2, UpUsrParVer,=1018)/* User Parameter Reset */\
/*---------------  ALL  (0x7202)---------------*/\

