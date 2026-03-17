/* **************************************************************************
 File Name	: 	app_shd.c
 Description	:	Shading Detection&Correction Function
 Designer		:	Lee, Wanhee
 Date		:	15.08.27
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */
#include "dev.h" 
#include "app_shd_tbl.h"


//=================================================================================================
//	define
//=================================================================================================
#define	SHD_DEBUG 		0	// 1 : Debuging Info display to uart
#define SHD_DET_FRAME	30	// Minimum Value is 1 (1Frame)

//=================================================================================================
//	Main function 
//=================================================================================================
void InitShd(void)	// 2015827 - WHL
{
	WORD wKH = ((3840/(float)FR_HW)*64)/*+0.5f*/;	// 160224 HSH
	WORD wKV = ((2048/(float)FR_VW)*64)/*+0.5f*/;
	
	// Shading Register Initialization
	SHD_MODEw(1);	// 0 : PD, 1 : Off, 2 : Det mode, 3 : Cor Mode

	SHD_TESTw(0);	// 0 : Def, 1 : Block, 2 : Gain, 3 : Gain Block
	SHD_DETOSDw(1);	// It enable detection mode only!
	SHD_ECHKw(1);	// Shading Table Err Check at Detection Mode.

	// Shading Det Block Set for 2M Sensor
	SHD_KHw(wKH);	// Det Correction & Detection Ratio
	SHD_KVw(wKV);
	SHD_DHWw(FR_HW); // Det H/V-Width
	SHD_DVWw(FR_VW);
	
	SHD_DHOFFw(6);	// 180405 LH TMP	// Detection Ofs
	SHD_DVOFFw(6);	// 180405 LH TMP
	SHD_CHOFFw(0);	// Correction ofs for Optical Zoom (It's similiar with Gain)
	SHD_CVOFFw(0);

	SHD_GAINw(0x40); // 0x40 is x1

	SHD_BPw(0x2);	// (Fixed)

	static BYTE bInitFlag = 0x1;
	
	if(bInitFlag){
		bInitFlag = 0x0;
		
	//	Initial Shading Table Load
	#if (!model_Shade)
	//	#if model_Save
			Sf2Isp( FLASH_SECT_SHD_STT*FLASH_SECT_SIZE, ISP_BASE_SHADING, ISP_SHADING_EA, 2);	// from FLASH
	//	#else
	//		TwiEep2Isp(TWI_EEP_SHADE_STT, ISP_BASE_SHADING, ISP_SHADING_EA, 2);	// from EEPROM
	//	#endif
	#else																		// from fixed table
		UINT i;
	 	for (i=0; i<ISP_SHADING_EA; i++) 	SetIsp(ISP_BASE_SHADING+i, gwTblShading[i]);	
	#endif
	}
}

void ShadingDet(void)
{
	static BYTE bShdDetState=0;
	static WORD nShdTblBuf[ISP_SHADING_EA];
	
 	if(MP(MpShdDet)==MN_OFF) { bShdDetState=0; return; }
//	else if(bShdDetState==0) bShdDetState=1;
	else if(bShdDetState==0){
		InitShd();
		bShdDetState=1;
	}
	
	switch(bShdDetState) {
		case 1 : {	// Det Mode Set
			SHD_MODEw(2);	// Detection Mode
			SHD_TESTw(1);	// SHD Block View
			bShdDetState++;
			break;
		}
		case (SHD_DET_FRAME-2) : {
			SHD_MODEw(1);	// Normal Mode (R/W)
			SHD_TESTw(0);	// Def
			bShdDetState++;
			break;
		}
		case (SHD_DET_FRAME-1) : {
			UINT i,j;
			
			for(i=0; i<ISP_SHADING_EA; i++) {
				for(j=0; j<2; j++) nShdTblBuf[i] = (WORD)GetIsp(0x400+i);	// 201593 - WHL : Register Address Delay

//				nShdTblBuf[i] = ((WORD)((nShdTblBuf[i]<<8)&0xff00)|(WORD)((nShdTblBuf[i]>>8)&0x00ff));		// 200507 LGH : Shading funtion bug correction 

				if(SHD_DEBUG) {	// 2015826 - WHL : Debuging Info for Shading Table Check
//					TxStrNoIRQ("nShdTblAdr  : ", (0x400+i), 10);
					TxStrNoIRQ("nShdTblBuf : ", nShdTblBuf[i], 10);
				}
			}			
			bShdDetState++;
			break;
		}
		case (SHD_DET_FRAME) : {	// Det Complete
			MP(MpShdDet)=0;
			
	#if (!model_Shade)
//			#if model_Save
			SfWrite(FLASH_SECT_SHD_STT*FLASH_SECT_SIZE, (BYTE*)nShdTblBuf, ISP_SHADING_EA<<1);	// 12.12.28
//			#else 
//				TwiWrEep2(TWI_EEP_SHADE_STT, (BYTE*)nShdTblBuf, ISP_SHADING_EA<<1);				// 12.12.28
//			#endif
//			TxStrNoIRQ("Shd Table Write Done : ", (UINT)(ISP_SHADING_EA<<1), 10);	// 2015826 - WHL
	#endif
			break;
		}
		default : { bShdDetState++; break; }	// Wait for Detection
	}
}

//-------------------------------------------------------------------------------------------------

void ISPM2 Shading (void)		// 180104 LH
{	// Shading correction
	
	ShadingDet();						// Shading table detection mode (Hidden menu)
				
	if (MP(MpShading)==MN_ON)	SHD_MODEw(3);	// 2015827 - WHL
	else if(!MP(MpShdDet)) 		SHD_MODEw(1);

#if(model_Sens_LFM_HDR)
	if(gbModeWdrOn_LFM)		SHD_BPw(3);
	else					SHD_BPw(2);
#endif

#if(model_Sens_CLR_HDR)
	if(gbModeWdrOn_CLR)		SHD_BPw(3);
	else					SHD_BPw(2);
#endif

	UINT nWgt = MP(MpShdWeight);
//	nWgt = LibUtlInterp1D (MINMAX(giCurAgc, COMMON_AGC_PT0, COMMON_AGC_PT1), COMMON_AGC_PT0, COMMON_AGC_PT1, nWgt, 1 );
	nWgt = LibUtlInterp1D (MINMAX(giCurAgc, 0x0, COMMON_AGC_PT0), 0x0, COMMON_AGC_PT0, nWgt, 1 );
//	nWgt = (nWgt<<7)/100;
	nWgt = (nWgt<<6)/100;	// 2015827 - WHL : for 100% Gain
	
	SHD_GAINw(nWgt);
	DebugDisp((gbMnDebugFnc==MN_DBG_6), Hex, "SHAD_GAIN", 4, 24, nWgt | (MP(MpShading)<<31))
}


/* EOF */


