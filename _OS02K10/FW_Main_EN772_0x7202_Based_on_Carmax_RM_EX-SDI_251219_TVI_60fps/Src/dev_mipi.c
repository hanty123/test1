/* **************************************************************************
 File Name	: 	dev_mipi.c
 Description	:	EN772 - for MIPI output
 Designer		:	Park chan bin
 Date		:	20. 12. 15
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

#if(model_IspO_MIPI)

void ISPM2 ModeMipi(UINT anHtwo, UINT anVtwo, UINT anHwo, UINT anVwo)
{
	BYTE bofst = 0x00;
//	BYTE hofst = (MODE_4M_ON) ? 0x02 : 0x00;

#if(model_USB_CX3)
	BYTE hofst = (MODE_4M_ON) ? 0x02 : (MODE_1M_ON) ? 0x04 : 0x00;
#else
	BYTE hofst = 0x00;
#endif

    UINT nMipi_VTWI = anVtwo-1;
    UINT nMipi_HWI  = MIPI_BYTE_CAL(anHwo+hofst);
    UINT nMipi_VWI  = anVwo+bofst;
    UINT nLane_HWI  = MIPI_BYTE_CAL(anHwo+hofst) << ((!MIPI_LANE)?1:0);
    
    UINT nVPOSW     = (MODE_1M_ON) ? 0x00 : (MODE_2M_ON) ? 0x07 : (MODE_4M_ON) ? 0x0f : 0x00;
    UINT nVPOSR     = (MODE_1M_ON) ? 0x10 : (MODE_2M_ON) ? 0x10 : (MODE_4M_ON) ? 0x0d : 0x10;
    BYTE bData_Type = (!MIPI_MOD) ? 0x2b : (MIPI_MOD==1) ? 0x2c : (MIPI_MOD==2) ? 0x1e : 0x1f;
    BYTE bMipi_En   = (!MIPI_LANE) ? 0x3 : 0xf;

   	//MIPI
	MTX_MSBw(0);
	MTX_PCw(0);
	MPLL_MCK_POw(0x1);
	MPLL_RSTNw(0x1);
	
	MTX_DATA_ONw(0x0);
	MTX_CLK_ONw(0x0);
	MPLL_POw(0x0);
	MTX_RSTNw(0x0);
	
	UINT nMipi_HTWI = (MIPI_BYTE_CAL(anHtwo)) - 1;

    BYTE bPOST_FREQ = (PPCK_DIVr==1) ? 1 : 0;
    BYTE bMODE      = (!MIPI_MOD) ? 10 : (MIPI_MOD==1||MIPI_MOD==2) ? 16 : 20;
    BYTE bLANE      = (!MIPI_LANE) ? 1 : 0;
    BYTE bMUL       = ((bMODE<<bPOST_FREQ)<<bLANE);
    // 0 : 594 / 2 : 1188 / 3 : 2376 / 4 : 742.5 / 6 : 1485 / 7 : 2970
    BYTE bMIPI_RATE = (bMUL<=16) ? 0 : (bMUL==20) ? 4 : (bMUL==32) ? 2 : (bMUL==40) ? 6 : (bMUL==64) ? 3 : 7;
    
    TxStrNoIRQ("MIPI PLL SETTING : ",bMIPI_RATE,3);
	MPLL_SELw(bMIPI_RATE);
	
    SetIsp(0x0014, ((!MIPI_LANE)?0x00000021:0x00000000)); // MBCK_SEL
    SetIsp(0x06b0, 0x00000000); // TEST PATTERN        
    SetIsp(0x06b1, 0x00001b1c);
    
	MTX_ENw((!MIPI_LANE) ? 3 : 15);
    MTX_MODw(MIPI_MOD);
    MTX_LANE_HWIw(nLane_HWI);
    MTX_LANEw((MIPI_LANE+1)<<1);
    MTX_DT_Lw(bData_Type);

    MTX_DT_VSw(0x0);
    MTX_DT_VEw(0x1);
    MTX_DT_HSw(0x2);
    MTX_DT_HEw(0x3);

    MTX_MEM_TOG_SELw(0x2);
    MTX_ENw(bMipi_En);
    MTX_SYNC_AUTOw(0x1);
    MTX_WC_Lw(nMipi_HWI<<2);
    MTX_HTWIw(nMipi_HTWI);
    MTX_VTWIw(nMipi_VTWI);
    MTX_READ_HWIw(nMipi_HWI);
    MTX_READ_VWIw(nMipi_VWI);
    MTX_WRITE_HWIw(anHwo+hofst);
    MTX_WRITE_VWIw(nMipi_VWI);
    MTX_FSYNC_ALNw(0x1);
    MTX_HSYNC_ALNw(0x1);
    MTX_HLOCKW_POSw(0x77);
    MTX_VLOCKW_POSw(nVPOSW);
    MTX_HLOCKR_POSw(0x00);
    MTX_VLOCKR_POSw(nVPOSR);
    MTX_CSI_READ_HPOSw(0x00);
    MTX_CSI_READ_VPOSw(0x05);
    MTX_CSI_WRITE_HPOSw(0x00);
    MTX_CSI_WRITE_VPOSw(0x12);

    MTX_CSI_READ_MASKw(0x0);
    MTX_CSI_READ_HSP_MASKw(0x00);
    MTX_CSI_READ_VSP_MASKw(0x0b);
    MTX_CSI_READ_HPOS_MASKw(anHwo+hofst);
    MTX_CSI_READ_VPOS_MASKw(nMipi_VWI);

    // 1xxx : 2LANE (MODE) / 0xxx: 4LANE (MODE)
    BYTE bDPHY_SET = (bLANE<<3) | (bMIPI_RATE);
    switch(bDPHY_SET&0xF){// SDR
        case 0b0000 : // 594-4
        { // 148.5Mbps / Lane
            MTX_SAP_TLPX_Dw(2);
            MTX_SAP_PRE_Dw(11);
            MTX_SAP_HS0_Dw(4);
            MTX_SAP_TRAIL_Dw(2);
            
            MTX_SAP_TLPX_Cw(2);
            MTX_SAP_PRE_Cw(11);
            MTX_SAP_HS0_Cw(6);
            MTX_SAP_TRAIL_Cw(2);   
            break;
        }
        case 0b0100 : // 742.5-4
        { // 185.625Mpbs / Lane
            MTX_SAP_TLPX_Dw(2);
            MTX_SAP_PRE_Dw(10);
            MTX_SAP_HS0_Dw(5);
            MTX_SAP_TRAIL_Dw(2);
            
            MTX_SAP_TLPX_Cw(2);
            MTX_SAP_PRE_Cw(10);
            MTX_SAP_HS0_Cw(7);
            MTX_SAP_TRAIL_Cw(3); 
            break;
        }
        case 0b1000 : // 594-2
        case 0b0010 : // 1188-4
        { // 297Mpbs / Lane
        #if(model_USB_CX3)
            MTX_SAP_TLPX_Dw(3);
            MTX_SAP_PRE_Dw(5);
            MTX_SAP_HS0_Dw(8);
            MTX_SAP_TRAIL_Dw(3);
        #else
			MTX_SAP_TLPX_Dw(3);
            MTX_SAP_PRE_Dw(7);
            MTX_SAP_HS0_Dw(7);
            MTX_SAP_TRAIL_Dw(3);
		#endif
		
            MTX_SAP_TLPX_Cw(4);
            MTX_SAP_PRE_Cw(7);
            MTX_SAP_HS0_Cw(14);
            MTX_SAP_TRAIL_Cw(4);   
            break;
        }
        case 0b1100 : // 742.5-2
        case 0b0110 : // 1485-4
        { // 371.25Mpbs / Lane
            MTX_SAP_TLPX_Dw(3);
            MTX_SAP_PRE_Dw(6);
            MTX_SAP_HS0_Dw(8);
            MTX_SAP_TRAIL_Dw(4);
            
            MTX_SAP_TLPX_Cw(4);
            MTX_SAP_PRE_Cw(6);
            MTX_SAP_HS0_Cw(14);
            MTX_SAP_TRAIL_Cw(4);  
            break;
        }
        case 0b1010 : // 1188-2
        case 0b0011 : // 2376-4
        { // 594Mpbs / Lane
            MTX_SAP_TLPX_Dw(5);
            MTX_SAP_PRE_Dw(4);
            MTX_SAP_HS0_Dw(12);
            MTX_SAP_TRAIL_Dw(6);
            
            MTX_SAP_TLPX_Cw(6);
            MTX_SAP_PRE_Cw(4);
            MTX_SAP_HS0_Cw(25);
            MTX_SAP_TRAIL_Cw(6);
            break;
        }
        case 0b1110 : // 1485-2
        case 0b0111 : // 2970-4
        { // 742.5Mpbs / Lane
            MTX_SAP_TLPX_Dw(6);
            MTX_SAP_PRE_Dw(3);
            MTX_SAP_HS0_Dw(13);
            MTX_SAP_TRAIL_Dw(7);
            
            MTX_SAP_TLPX_Cw(7);
            MTX_SAP_PRE_Cw(2);
            MTX_SAP_HS0_Cw(32);
            MTX_SAP_TRAIL_Cw(8); 
            break;
        }
        case 0b1011 : // 2376-2
        { // 1188Mpbs / Lane
            MTX_SAP_TLPX_Dw(9);
            MTX_SAP_PRE_Dw(17);
            MTX_SAP_HS0_Dw(21);
            MTX_SAP_TRAIL_Dw(11);
            
            MTX_SAP_TLPX_Cw(10);
            MTX_SAP_PRE_Cw(16);
            MTX_SAP_HS0_Cw(46);
            MTX_SAP_TRAIL_Cw(12); 
            break;
        }
        case 0b1111 : //2970-2
        { // 1485Mpbs / Lane
            MTX_SAP_TLPX_Dw(10);
            MTX_SAP_PRE_Dw(15);
            MTX_SAP_HS0_Dw(24);
            MTX_SAP_TRAIL_Dw(13);
            
            MTX_SAP_TLPX_Cw(11);
            MTX_SAP_PRE_Cw(14);
            MTX_SAP_HS0_Cw(53);
            MTX_SAP_TRAIL_Cw(12); 
            break;
        }
    }
	
    MTX_RSTNw(0x1);
	MPLL_POw(0x1);
    MTX_CLK_ONw(0x1);
    MTX_DATA_ONw(0x1);
}

#if(model_USB_CX3)
void USB_MenuCtrl_I2C(void)
{
	if(gAddr==0xf9) {
		TxStrNoIRQ("Address = ", gAddr, 8);
		TxStrNoIRQ("register = ", gData, 8);
	}
	else if(gAddr!=0xf1) SetIsp(gAddr, gData);
	else
	{
		if(gData==0x800)      	gbUKeyVal = 0x1;
		else if(gData==0x200) 	gbUKeyVal = 0x2;
		else if(gData==0x400) 	gbUKeyVal = 0x8;
		else if(gData==0x600) 	gbUKeyVal = 0x4;
		else if(gData==0x500) 	gbUKeyVal = 0x10;

		else if(gData==0x300) 	MP(MpSysFreq) =	MN_SYSFREQ_50;//select 50hz
		else if(gData==0x100) 	MP(MpSysFreq) =	MN_SYSFREQ_60;//select 60hz
		
		#if (model_2M)
		if(gData==0x10) 		{MP(MpOutFps) = MN_2M_720p_25_30;}
		else if(gData==0x11)	{MP(MpOutFps) = MN_2M_720p_50_60;}				
		else if(gData==0x20)	{MP(MpOutFps) = MN_2M_1080p_25_30;}
		else if(gData==0x21)	{MP(MpOutFps) = MN_2M_1080p_50_60;}
		else if(gData==0x40)	{MP(MpOutFps) = MN_2M_1440p_25_30;}
		else if(gData==0x50)	{MP(MpOutFps) = MN_2M_1944p_20;}
		
		#elif (model_5M)
		if(gData==0x10) 		{MP(MpOutFps) = MN_4M_720p_25_30;}
		else if(gData==0x20)	{MP(MpOutFps) = MN_4M_1080p_25_30;} 				
		else if(gData==0x40)	{MP(MpOutFps) = MN_4M_1440p_25_30;}
		else if(gData==0x50)	{MP(MpOutFps) = MN_5M_1944p_20;}
		#endif

		// Common
		gbModeBufOutFps = MP(MpOutFps);
		gbModeBufSysFreq = MP(MpSysFreq);

		//SDI Mode
		if(MP(MpOutFps) == MN_2M_1080p_50_60){
			MP(MpSdiForm)	= MN_EXSDI_270M_3G;
			MP(MpSdiMode)	= MN_EXSDI;
		}
		else{
			MP(MpSdiForm)	= MN_EXSDI_135MP;
			MP(MpSdiMode)	= MN_EXSDI;

//			MP(MpSdiForm)	= MN_SDI_1P5G;
//			MP(MpSdiMode)	= MN_HDSDI;
		}
		
//		TxStrNoIRQ("out mode = ", gData, 8);
	}
}
#endif
	
#endif
