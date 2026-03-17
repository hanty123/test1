/* **************************************************************************
 File Name	: 	isp_app_maf.c
 Description	:	Motorized AF Function
 Designer		:	Lee, Wanhee
 Date		:	17.11.07
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */
#include "dev.h"

BYTE gbUCCKeyOn=0, gbExUCCKeyOn=0, gbExtUCCKeyOn=0; // 160105 HTY
BYTE gbMAF_Tele =0,gbMAF_Wide =0, gbMAF_Near=0,gbMAF_Far=0;

#if (model_Lens==1)

#include "app_maf.h"
BYTE gbInitOff=3;
//=================================================================================================
//	Main function 
//=================================================================================================

void Motorized_AF(void)
{
			
//	Auto Focus Main Function (All Functions Flow Definition)
	static BYTE bInitFlag=1, bMAF_OutputMode_Buf=0xf;
	
	gbMAF_OutputMode = MP(MpOutFps);

	if(bMAF_OutputMode_Buf!=gbMAF_OutputMode){
#if (MAF_BOSD_DISP==1)

	#if (model_5M) // PCHAN 21.03.08 : Box position change
	
		gnBoxPosMAF_X[4] = gnBoxPosMAF_X[2] = (MP(MpOutFps)==MN_4M_720p_25_30) ? (0x03f404e3) : (MP(MpOutFps)==MN_4M_1080p_25_30) ? 0x05eb0751 : (MP(MpOutFps)==MN_4M_1440p_25_30) ? 0x07e009c0 : 0x07fb09e0; 
		gnBoxPosMAF_Y[4] = gnBoxPosMAF_Y[1] = (MP(MpOutFps)==MN_4M_720p_25_30) ? (0x1200bc) : (MP(MpOutFps)==MN_4M_1080p_25_30) ? 0x0021011d : (MP(MpOutFps)==MN_4M_1440p_25_30) ? 0x00300180 : 0x03001f6; 


	#elif (model_2M)
	
		gnBoxPosMAF_X[4] = gnBoxPosMAF_X[2] = (MP(MpOutFps)==MN_2M_720p_25_30 || MP(MpOutFps)==MN_2M_720p_50_60) ? (0x03fa04e9) : (MP(MpOutFps)==MN_2M_1080p_25_30 || MP(MpOutFps)==MN_2M_1080p_50_60) ? (0x058a072a) : (MP(MpOutFps)==MN_2M_1440p_25_30) ? (0x7600985) : (0x77809a7); 
		gnBoxPosMAF_Y[4] = gnBoxPosMAF_Y[1] = (MP(MpOutFps)==MN_2M_720p_25_30 || MP(MpOutFps)==MN_2M_720p_50_60) ? (0x1800be)   : (MP(MpOutFps)==MN_2M_1080p_25_30 || MP(MpOutFps)==MN_2M_1080p_50_60) ? (0x00300130) : (MP(MpOutFps)==MN_2M_1440p_25_30) ? (0x47019b)  : (0x42020f);

	#endif
        gwMAF_BoxSY = (WORD)((gnBoxPosMAF_Y[4]&0xFFFF0000)>>16); 
        gwMAF_BoxEY = (WORD)(gnBoxPosMAF_Y[4]&0x0000FFFF); 
        gwMAF_BoxSX = (WORD)((gnBoxPosMAF_X[4]&0xFFFF0000)>>16);
        gwMAF_BoxEX = (WORD)(gnBoxPosMAF_X[4]&0x0000FFFF);        
#endif 
		AF1_HSPw(MAF1_HSP);
		AF1_HEPw(MAF1_HEP);
	    AF1_VSPw(MAF1_VSP);
	    AF1_VEPw(MAF1_VEP);
	}

	bMAF_OutputMode_Buf=gbMAF_OutputMode;
    


	// Initialization
	if(bInitFlag) { MAF_EnvironmentSet(); bInitFlag=0; }
    
	MAF_CmdCheck();
	
	if(gbMAF_Excute) {

    	switch (gbAF_MainState) {
    		case 1 : { // Lens Initialization
    			if(!gbMAF_DevMode) Lens_Initialization();
    			else gbAF_MainState = 0;			
    			break;
    		}
    		case 2 : { // Trace Curve Auto Calibration
    			if(!gbMAF_DevMode) TraceCurve_Calibration();
    			else gbAF_MainState = 0; 			
    			break;
    		}
    		default : { // Normal Operation
    			// Motor Control
    			MAF_MnlMotorControl(!gbMenuState); // Control @Menu Off
    			MAF_AutoFocus();
    		    if(gbMAF_WrEEP){ MAF_Position_Save();gbMAF_WrEEP=0;}    // position save   
    		   
    		    #if MAF_INITIAL_OFF
    		    	if((gbInitOff==1)&&(!gbAutoFocus_Flag))    { UD(UdMaf_Cbp+30)=0xA8; gbInitOff=0; gbUsrDataSaveChk = 1; } 	
    		    #endif 	
    			break;
    		}
    	}

        MAF_Lens_StateDisp(); // State Display(Box/Font)		
    	MAF_DebugingDisp();   // State Display(Font/Grp)
    	MAF_Current_Mng();    // Motor Sleep Mode Managing
	}
}
//=================================================================================================
//	Position set
//=================================================================================================

void MAF_Position_Save(void) { // position save to eeprom.

#if (model_Lens==1)
	gbMAF_TwiTx_Z[0] = (BYTE)((Maf_Zmotor.nCurPos>>8)&0xFF); // Zoom MSB 8bit
	gbMAF_TwiTx_Z[1] = (BYTE)((Maf_Zmotor.nCurPos>>0)&0xFF); //   "  LSB 8bit
	gbMAF_TwiTx_F[0] = (BYTE)((Maf_Fmotor.nCurPos>>8)&0xFF); // Focs MSB 8bit
	gbMAF_TwiTx_F[1] = (BYTE)((Maf_Fmotor.nCurPos>>0)&0xFF); //   "  LSB 8bit


	UD(UdMaf+0) = gbMAF_TwiTx_Z[0]; 
	UD(UdMaf+1) = gbMAF_TwiTx_Z[1];
	UD(UdMaf+2) = gbMAF_TwiTx_F[0];
	UD(UdMaf+3) = gbMAF_TwiTx_F[1];
	gbUsrDataSaveChk = 1;
#endif	// end of #if (model_Lens==1)
}

void MAF_Position_Load(void) { // for initial

#if (model_Lens==1)

	gbMAF_TwiRx_Z[0] = UD(UdMaf+0);
	gbMAF_TwiRx_Z[1] = UD(UdMaf+1);
	gbMAF_TwiRx_F[0] = UD(UdMaf+2);
	gbMAF_TwiRx_F[1] = UD(UdMaf+3);

	gbUsrDataReadChk = 1;

    Maf_Zmotor.nTgtPos = (UINT)((UINT)(gbMAF_TwiRx_Z[0]<<8)|gbMAF_TwiRx_Z[1])&0x0000FFFF;
	Maf_Zmotor.nTgtPos = ((Maf_Zmotor.nTgtPos>gwMAF_Zpos_E)||(Maf_Zmotor.nTgtPos<gwMAF_Zpos_S))? gnMaf_TblPosition_Z[0] : Maf_Zmotor.nTgtPos;

	BYTE i=0;
	while(Maf_Zmotor.nTgtPos>gnMaf_TblPosition_Z[i]) i++;
	i+=(Maf_Zmotor.nTgtPos==gwMAF_Zpos_S);
	Maf_Fmotor.nTgtPos = (UINT)LibUtlInterp1D ((int)Maf_Zmotor.nTgtPos, (int)gnMaf_TblPosition_Z[i-1], (int)gnMaf_TblPosition_Z[i], (int)gnMaf_TblPosition_F[i-1], (int)gnMaf_TblPosition_F[i]);

#if MAF_DOM_INIT    // 181128 JJH
    gnFocusInitPosiBuf = Maf_Fmotor.nTgtPos;    
    Maf_Fmotor.nTgtPos=gwMAF_Frange_T-gnFocusInitPosiBuf;        
#endif
						   
#endif	// end of #if (model_Lens==1)
}

//=================================================================================================
//	Basic Environment Setting
//=================================================================================================
void MAF_EnvironmentSet(void)
{
	int i=0;

    for(i=0; i<MAF_TRACKING_TBL_STEP; i++) gnMaf_TblPosition_Z[i]=(gwMAF_Zpos_S+(gwMAF_Zpos_E-gwMAF_Zpos_S)*i/(MAF_TRACKING_TBL_STEP-1));
    
	gbMAF_MZrange_T = gwMAF_Zrange_T/MAF_RangeSTEP;
    gbMAF_MFrange_T = gwMAF_Frange_T/MAF_RangeSTEP;
    gbMAF_MZpos_S = gwMAF_Zpos_S/MAF_RangeSTEP;
    gbMAF_MZpos_E = gwMAF_Zpos_E/MAF_RangeSTEP;
    gbMAF_MFpos_S = gwMAF_Fpos_S/MAF_RangeSTEP;
    gbMAF_MFpos_E = gwMAF_Fpos_E/MAF_RangeSTEP;

  	gnMaf_FPosRange[0] = gbMAF_MFpos_S * MAF_RangeSTEP;
  	gnMaf_FPosRange[1] = gbMAF_MFpos_E * MAF_RangeSTEP;	


	giMaf_GainRange[0]=0;
	giMaf_GainRange[1]=Sens(AE_GAIN_TOTAL);

	gnMaf_LibCurPos_F  = &Maf_Fmotor.nCurPos;
	gnMaf_LibTgtPos_F  = &Maf_Fmotor.nTgtPos;
	gbMaf_LibTgtCtr_Go = &Maf_Fmotor.bPosGo;

	MP(MpMAF_MotorInit)=0;

    MAF_EnvironmentSet_Lib();
}

//=================================================================================================
//	Control Command check
//=================================================================================================
void MAF_CmdCheck(void)
{
    BYTE i;
    static BYTE bMAF_SetUpBuf=1,bMAF_DNbuf=0;

	if(MP(MpMAF_Filter)&&bMAF_DNbuf) { // 191202 PChan : Bug correction
		static BYTE bMAF_DnN_Cnt=0;              
               
		bMAF_DnN_Cnt = (gbDnN_Changed!=(BYTE)gnTdnChkOut) ? MAF_ONESHOT_FILTER_TIME : //(MAF_ONESHOT_TRG_TIME<<1);
		               (bMAF_DnN_Cnt>1) ? (bMAF_DnN_Cnt-1) : 0;


		if(bMAF_DnN_Cnt==1) gbAutoFocus_Flag = 1;
	}
	bMAF_DNbuf=1;
	gbDnN_Changed=(BYTE)gnTdnChkOut;
	
	gbAF_MainState = (MP(MpMAF_MotorInit)) ? 1 : (gbMAF_Calibration) ? 2 : gbAF_MainState;	

    if((!gbMenuState)&&(!gbAutoFocus_Flag)) {	// 190531 JJH Motor : Don't operate zoom during focusing

        if(MP(MpMAF_UccZoomHold)) gbExUCCKeyOn=0; // 181128 JJH

        static BYTE bExUCCKeyBuf=0;
        if(gbExUCCKeyOn)         bExUCCKeyBuf=PELCO_HOLD_CNT;    
        else if(bExUCCKeyBuf)    bExUCCKeyBuf--;
		else if((!gbUCCKeyOn)&&(!gbExUCCKeyOn)&&(!gbExtUCCKeyOn)){	// 171205 HTY
			gbMAF_Tele = (pKEY_U) ? 1 : 0; //Key_UP     MAF_TELE_Z
			gbMAF_Wide = (pKEY_D) ? 1 : 0; //Key_Down   MAF_WIDE_Z  
			gbMAF_Near = (pKEY_L) ? 1 : 0; //Key_Right  MAF_NEAR_F
			gbMAF_Far  = (pKEY_R) ? 1 : 0; //Key_Left   MAF_FAR_F
		}
	}
	else	gbMAF_Tele=gbMAF_Wide=gbMAF_Near=gbMAF_Far=0;	// 160105 HTY

	// Exception state
	static BYTE bExcuteFlag=0;

	if(MN_FPS_HI) 	bExcuteFlag = (bExcuteFlag==0);										// 190729 JHR : MAF bug correction
	else 			bExcuteFlag = 0;
		
	gbMAF_Excute = (!bExcuteFlag); 	  // WDR On & Short mode || FPS High		// 191202 PChan : bug correction

    if(gbMAF_Excute){
        if((UD(UdMaf_Cbp+2*MAF_TRACKING_TBL_STEP)==0x0A)&&(!gbMaf_Tccflag)){ // 180513 JJH calibration save 
            for(i=0; i<MAF_TRACKING_TBL_STEP; i++ )
            {
                gnMaf_TblPosition_F[i] = ((int)UD(UdMaf_Cbp+2*i)|(int)(UD(UdMaf_Cbp+2*i+1)<<8))&0x0000FFFF;                                
            }
            gbMaf_Tccflag = gbUsrDataReadChk = 1;
        }	

        if(gbMAF_SETUP){ // 180513 JJH Motor Setup
            if((bMAF_SetUpBuf!=gbMAF_SETUP)&&(!gbMenuState)) {
    		   OsdClearAll(); gbMnDebugFnc=2; ChangeMenuSize(); 
               bMAF_SetUpBuf = gbMAF_SETUP;
        	}
            for(i=0; i<MAF_TRACKING_TBL_STEP; i++) gnMaf_TblPosition_Z[i]=(gwMAF_Zpos_S+(gwMAF_Zpos_E-gwMAF_Zpos_S)*i/(MAF_TRACKING_TBL_STEP-1));
            gnMaf_FPosRange[0] = gwMAF_Fpos_S;
            gnMaf_FPosRange[1] = gwMAF_Fpos_E;
        }
        else{ 
        	bMAF_SetUpBuf=gbMAF_SETUP;
            gbMAF_DevMode=0; 
            bMAF_SetUpBuf = gbMAF_SETUP;
        }
    }
}

//=================================================================================================
//	Lens Initialization
//=================================================================================================
void Lens_Initialization(void)
{
	switch(gbMaf_InitState) {
		case 0 : { // Motor Move to Zero Point & Position Initialization
			#if MAF_INITIAL_OFF  
				if((UD(UdMaf_Cbp+30)==0xA8)&&(!MP(MpMAF_MotorInit)))
				{	
					MAF_Position_Load();
					Maf_Fmotor.nTgtPos = (UINT)((UINT)(gbMAF_TwiRx_F[0]<<8)|gbMAF_TwiRx_F[1])&0x0000FFFF; 
					Maf_Fmotor.nTgtPos = ((Maf_Fmotor.nTgtPos>gwMAF_Fpos_E)||(Maf_Fmotor.nTgtPos<gwMAF_Fpos_S))? gnMaf_TblPosition_F[0] : Maf_Fmotor.nTgtPos;   
					gbAF_MainState=gbMaf_InitState=0;
					Maf_Zmotor.nCurPos= Maf_Zmotor.nTgtPos;
					Maf_Fmotor.nCurPos=Maf_Fmotor.nTgtPos;
					break; 
				}
			#endif
			
			MP(MpMAF_MotorInit)=gbAutoFocus_Flag = gbMAF_OneTimeState = 0;
            Maf_Zmotor.nCurPos = gwMAF_Zrange_T;
            Maf_Fmotor.nCurPos = gwMAF_Frange_T;  
            
			Maf_Zmotor.nTgtPos = Maf_Fmotor.nTgtPos = 0;
			Maf_Zmotor.bPosGo = Maf_Fmotor.bPosGo = 1;
			gbMaf_InitState=1;
			break;
		}
		case 1 : {
			if((Maf_Zmotor.bPosGo==0)&&(Maf_Fmotor.bPosGo==0)) gbMaf_InitState++;
			break;
		}
		case 2 : { // Move to Margin
		    MAF_Position_Load();
			Maf_Zmotor.bPosGo = Maf_Fmotor.bPosGo = 1;
			gbMaf_InitState++;
			break;
		}
		case 3 : {
			if((Maf_Zmotor.bPosGo==0)&&(Maf_Fmotor.bPosGo==0)) gbMaf_InitState++;
			break;
		}
		default : { //case 4 :
		#if MAF_DOM_INIT    // 181128 JJH
            Maf_Fmotor.nTgtPos=Maf_Fmotor.nCurPos=gnFocusInitPosiBuf;		
        #endif  		
			gbAF_MainState=gbMaf_InitState=0;
			gbAutoFocus_Flag=1;	// 190531 JJH Motor : When Menu is On, Focusing 		
			break;
		}
	}	
}

//=================================================================================================
//	Trace Curve Auto Calibration
//=================================================================================================
void TraceCurve_Calibration(void)
{
	UINT i=0; // Dif Point
	static BYTE bInitState[2]={0,0};

	if(bInitState[0]==(sizeof(gnMaf_TblPosition_Z)/sizeof(gnMaf_TblPosition_Z[0]))) { // Finish
		gbAF_MainState=bInitState[1]=bInitState[0]=0;
		gbOnePushAfSel=MAF_OnePushAfSel;
		
		TxStrNoIRQ("Trace Curve Calibration Finish~!!", 0, 0);
		
		for(i=0; i<(sizeof(gnMaf_TblPosition_Z)/sizeof(gnMaf_TblPosition_Z[0])); i++) {

			if(i==(sizeof(gnMaf_TblPosition_Z)/sizeof(gnMaf_TblPosition_Z[0])-1)){ 
			#if(0)
			    TxStrDec("Focus position : ",gnMaf_TblPosition_F[i],5);
   			    TxStrDec("MAF_RANGE_Z : ",gbMAF_MZrange_T*MAF_RangeSTEP,5);
			    TxStrDec("MAF_START_Z : ",gbMAF_MZpos_S*MAF_RangeSTEP,5);
			    TxStrDec("MAF_END_Z   : ",gbMAF_MZpos_E*MAF_RangeSTEP,5);    			    
   			    TxStrDec("MAF_RANGE_F : ",gbMAF_MFrange_T*MAF_RangeSTEP,5);
			    TxStrDec("MAF_START_F : ",gbMAF_MFpos_S*MAF_RangeSTEP,5);
			    TxStrDec("MAF_END_F   : ",gbMAF_MFpos_E*MAF_RangeSTEP,5); 
			#else
				// 210727 PChan :  TxStrNoIRQ --> TxStrDecNoIRQ
				TxStrDecNoIRQ("Focus position : ",gnMaf_TblPosition_F[i],5);   
   			    TxStrDecNoIRQ("MAF_RANGE_Z : ",gbMAF_MZrange_T*MAF_RangeSTEP,5);
			    TxStrDecNoIRQ("MAF_START_Z : ",gbMAF_MZpos_S*MAF_RangeSTEP,5);
			    TxStrDecNoIRQ("MAF_END_Z   : ",gbMAF_MZpos_E*MAF_RangeSTEP,5);    			    
   			    TxStrDecNoIRQ("MAF_RANGE_F : ",gbMAF_MFrange_T*MAF_RangeSTEP,5);
			    TxStrDecNoIRQ("MAF_START_F : ",gbMAF_MFpos_S*MAF_RangeSTEP,5);
			    TxStrDecNoIRQ("MAF_END_F   : ",gbMAF_MFpos_E*MAF_RangeSTEP,5); 
			#endif
			    UD(UdMaf_Cbp+2*i  ) = gnMaf_TblPosition_F[i];
			    UD(UdMaf_Cbp+2*i+1) = gnMaf_TblPosition_F[i]>>8;
			    UD(UdMaf_Cbp+30)=0;
			    gbUsrDataSaveChk = 1;                  
			}
			else{		
//			    TxStrDec("Focus position : ",gnMaf_TblPosition_F[i],5);   			        			   			    
				TxStrDecNoIRQ("Focus position : ",gnMaf_TblPosition_F[i],5);  // 210727 PChan :  TxStrNoIRQ --> TxStrDecNoIRQ	
			    UD(UdMaf_Cbp+2*i) = gnMaf_TblPosition_F[i];
			    UD(UdMaf_Cbp+2*i+1) = gnMaf_TblPosition_F[i]>>8;    			    		   
			}    		
		}
        gbMaf_Tccflag = 0;
        UD(UdMaf_Cbp+2*i) = 0x0A;     		
	}
	else {
		if(bInitState[1]==0) { // Step 1 : Move to Target Zoom Position
			gbAutoFocus_Flag = gbMAF_OneTimeState = 0;
			// Dif Point
			Maf_Zmotor.nTgtPos= gnMaf_TblPosition_Z[bInitState[0]];
			if(bInitState[0]==0) {
				Maf_Fmotor.bPosGo=1;
				Maf_Fmotor.nTgtPos = gnMaf_TblPosition_F[bInitState[0]];
			}
			Maf_Zmotor.bPosGo = 1;
			bInitState[1]++;
		}
		else if(bInitState[1]==1) {
			if((Maf_Zmotor.bPosGo==0)&&(Maf_Fmotor.bPosGo==0)) bInitState[1]++;
		}
		else if(bInitState[1]==2) {
			gbAutoFocus_Flag=1;
			bInitState[1]++;
		}
		else {
			if(gbAutoFocus_Flag==0) { // Focusing Complete			
                gnMaf_TblPosition_F[bInitState[0]] = Maf_Fmotor.nCurPos;            
				bInitState[0]++;
				bInitState[1]=0;
			}
			else {
				gbOnePushAfSel=0;
                MAF_AutoFocus();
			}
		}
	}
}

//=================================================================================================
//	Motor Manual Control
//=================================================================================================
void MAF_MnlMotorControl(BYTE abExcute)
{	
	static BYTE bActBuf_Z=0, bActBuf_F=0;
		
	if(abExcute) { // Key Control @Menu off
		
		gbMAF_ZoomTrkEn = 0;

		if(gbMAF_DevMode==1) { // Development Mode
		
			Maf_Zmotor.nTgtPos = (gbMAF_Wide) ? ((Maf_Zmotor.nCurPos>MAF_MAX_STEP) ? (Maf_Zmotor.nCurPos-MAF_MAX_STEP) : 0) :
								 (gbMAF_Tele) ? (Maf_Zmotor.nCurPos+MAF_MAX_STEP) : Maf_Zmotor.nTgtPos;
		
			Maf_Fmotor.nTgtPos = (gbMAF_Near) ? ((Maf_Fmotor.nCurPos>MAF_MNL_STEP_F) ? (Maf_Fmotor.nCurPos-MAF_MNL_STEP_F) : 0) :
								 (gbMAF_Far ) ? (Maf_Fmotor.nCurPos+MAF_MNL_STEP_F) : Maf_Fmotor.nTgtPos;
								  
			Maf_Zmotor.bPosGo = (gbMAF_Wide|gbMAF_Tele) ? 1 : Maf_Zmotor.bPosGo;
			Maf_Fmotor.bPosGo = (gbMAF_Near|gbMAF_Far ) ? 1 : Maf_Fmotor.bPosGo;
			gbMaf_MnlSpeed=1;
		}
		else { // Normal Mode
		// Zoom Manual Control
			if(gbMAF_Wide|gbMAF_Tele) {			   
				MAF_ZoomTracking();
				gbAutoFocus_Flag = gbMAF_OneTimeState = gbMAF_TrgCnt = 0;
			}
			else if(bActBuf_Z!=(gbMAF_Wide|gbMAF_Tele)) {
				Maf_Zmotor.nTgtPos = Maf_Zmotor.nCurPos;
				Maf_Zmotor.bPosGo = 1;
				gbMAF_TrgCnt = (MP(MpMAF_mode)==0) ? MAF_ONESHOT_TRG_TIME :0; // 191202 PChan : Auto focus on oneshot mode 
			}
			bActBuf_Z=(gbMAF_Wide|gbMAF_Tele);

		 	if((gbMAF_TrgCnt==8)&&(!gbAutoFocus_Flag)) { 
		 		gbMAF_WrEEP=1; 
		 		#if MAF_INITIAL_OFF
		 			UD(UdMaf_Cbp+30)=0; gbUsrDataSaveChk = 1;
		 			gbInitOff=3;
		 		#endif
		 	}	
			else if(gbMAF_TrgCnt==1)  gbAutoFocus_Flag = (MP(MpMAF_mode)==0);  // AF Excution @Zoom Trigger
			gbMAF_TrgCnt = (gbMAF_TrgCnt>1) ? (gbMAF_TrgCnt-1) : 0;
	
		// Focus Manual Control
			if(gbMAF_Near|gbMAF_Far) {
            
             	Maf_Fmotor.nTgtPos = (gbMAF_Near) ? gwMAF_Fpos_S : gwMAF_Fpos_E; // 191202 PChan : Bug correction
                Maf_Fmotor.bPosGo = gbMaf_MnlSpeed = 1;
                gbMAF_OneTimeState = 0;
			}
			else if(bActBuf_F!=(gbMAF_Near|gbMAF_Far)) {
				Maf_Fmotor.nTgtPos = Maf_Fmotor.nCurPos;
				Maf_Fmotor.bPosGo = gbMaf_MnlSpeed = 1;
			}
			bActBuf_F=(gbMAF_Near|gbMAF_Far);	
		}
	}
}

//=================================================================================================
//	Zoom Tracking Function
//=================================================================================================
void MAF_ZoomTracking(void)
{
	UINT i=0;
	BYTE bTraceNo[2]={0,0};

	if(gbMAF_Wide) Maf_Zmotor.nTgtPos = ((WORD)Maf_Zmotor.nCurPos>(gwMAF_Zpos_S+MAF_MAX_STEP)) ? (Maf_Zmotor.nCurPos-MAF_MAX_STEP) : gwMAF_Zpos_S;
	else           Maf_Zmotor.nTgtPos = ((WORD)Maf_Zmotor.nCurPos<(gwMAF_Zpos_E-MAF_MAX_STEP)) ? (Maf_Zmotor.nCurPos+MAF_MAX_STEP) : gwMAF_Zpos_E;

	// Control Aception condition
	gbMAF_ZoomTrkEn = ((gbMAF_Wide&(Maf_Zmotor.nCurPos>gwMAF_Zpos_S))||(gbMAF_Tele&(Maf_Zmotor.nCurPos<gwMAF_Zpos_E)));
	
	if(Maf_Zmotor.nTgtPos==gwMAF_Zpos_S) { // Wide side Exception condition
		Maf_Fmotor.nTgtPos = gnMaf_TblPosition_F[0];	
		bTraceNo[0]=0;
		bTraceNo[1]=1;
	}
	else if(Maf_Zmotor.nTgtPos==gwMAF_Zpos_E) { // Tele side Exception condition
		Maf_Fmotor.nTgtPos = gnMaf_TblPosition_F[MAF_TRACKING_TBL_STEP-1];
		bTraceNo[0]=(MAF_TRACKING_TBL_STEP-2);
		bTraceNo[1]=(MAF_TRACKING_TBL_STEP-1);
	}
	else {

		for(i=0;i<MAF_TRACKING_TBL_STEP; i++) {
            if(gnMaf_TblPosition_Z[i]==Maf_Zmotor.nTgtPos) bTraceNo[0] = (gbMAF_Tele) ? (i-1) : i ;
			else if(gnMaf_TblPosition_Z[i]<Maf_Zmotor.nTgtPos) bTraceNo[0]=i;
		}
		
		for(i=(MAF_TRACKING_TBL_STEP-1);i>0; i--) {	    
            if(gnMaf_TblPosition_Z[i]==Maf_Zmotor.nTgtPos) bTraceNo[1] = (gbMAF_Wide) ? (i+1) : i;
			else if(gnMaf_TblPosition_Z[i]>Maf_Zmotor.nTgtPos) bTraceNo[1]=i;
		}
		Maf_Fmotor.nTgtPos = (UINT)LibUtlInterp1D ((int)Maf_Zmotor.nTgtPos, (int)gnMaf_TblPosition_Z[bTraceNo[0]], (int)gnMaf_TblPosition_Z[bTraceNo[1]], (int)gnMaf_TblPosition_F[bTraceNo[0]], (int)gnMaf_TblPosition_F[bTraceNo[1]]);			
	}

	if(ABS((int)Maf_Fmotor.nTgtPos-(int)Maf_Fmotor.nCurPos)>MAF_MAX_STEP) {
		if(Maf_Fmotor.nTgtPos<Maf_Fmotor.nCurPos) Maf_Fmotor.nTgtPos = ((WORD)Maf_Fmotor.nCurPos>(gwMAF_Fpos_S+MAF_MAX_STEP)) ? (Maf_Fmotor.nCurPos-MAF_MAX_STEP) : gwMAF_Fpos_S;
		else                                      Maf_Fmotor.nTgtPos = ((WORD)Maf_Fmotor.nCurPos<(gwMAF_Fpos_E-MAF_MAX_STEP)) ? (Maf_Fmotor.nCurPos+MAF_MAX_STEP) : gwMAF_Fpos_E;

		Maf_Zmotor.nTgtPos = (UINT)LibUtlInterp1D ((int)Maf_Fmotor.nTgtPos, (int)gnMaf_TblPosition_F[bTraceNo[0]], (int)gnMaf_TblPosition_F[bTraceNo[1]], (int)gnMaf_TblPosition_Z[bTraceNo[0]], (int)gnMaf_TblPosition_Z[bTraceNo[1]]);

        Maf_Zmotor.nTgtPos = (ABS((int)Maf_Zmotor.nTgtPos-(int)Maf_Zmotor.nCurPos)>MAF_MAX_STEP) ?  Maf_Zmotor.nCurPos : Maf_Zmotor.nTgtPos;                      

        Maf_Zmotor.nTgtPos = ((gbMAF_Wide==1)&&(Maf_Zmotor.nTgtPos>Maf_Zmotor.nCurPos)) ?   Maf_Zmotor.nCurPos : 
                             ((gbMAF_Tele==1)&&(Maf_Zmotor.nTgtPos<Maf_Zmotor.nCurPos)) ?   Maf_Zmotor.nCurPos : Maf_Zmotor.nTgtPos;        									 
	}
	Maf_Zmotor.bPosGo = Maf_Fmotor.bPosGo = gbMAF_ZoomTrkEn;
}

//=================================================================================================
//	Auto Focus (No LIB)
//=================================================================================================
void MAF_AutoFocus(void)	// Oneshot AF(.LIB)
{
	MAF_DataBuffering();
	MAF_PreProcessing();
	gnScanMargin=ScanMargin;

    // 190214
    static UINT nFocusingErrCnt=0;
    if(gbMAF_OneTimeState==1)   nFocusingErrCnt++;
    else                        nFocusingErrCnt=0;
              
    if(nFocusingErrCnt>(12*FPS)) 
    {
        gbMAF_OneTimeState=5; 
        nFocusingErrCnt=Maf_Fmotor.bPosGo=Maf_Fmotor.bActive=0;  // 191202 PChan : Set GPIO low after 2motor processing
        Maf_Fmotor.nTgtPos=Maf_Fmotor.nCurPos;
    }

	gbMotorSpeedStep[1]=SPEED_SEL ? MOTOR_SPEED_5M : MOTOR_SPEED1;  // 210527 HTY : 2-Motor speed control at 5M

	if(gbAutoFocus_Flag) 
	{
		MAF_OneTimeAF(); 
		if(gbInitOff==3) gbInitOff=1;
	} 
}

//=================================================================================================
//	Lens State Display
//=================================================================================================

void MAF_Lens_StateDisp(void)
{
#if (MAF_BOSD_DISP!=0)
	static BYTE bMAF_BoxCnt=0;

	if(Maf_Zmotor.bPosGo|Maf_Fmotor.bPosGo|gbMAF_SETUP) bMAF_BoxCnt = BAF_BOXOSD_TIME;
	else {
		bMAF_BoxCnt = (bMAF_BoxCnt>0) ? bMAF_BoxCnt-1 : 0;
	}

	if(gbMAF_SETUP||bMAF_BoxCnt) {
		gbMAFBoxFlag=1;
	    #if (MAF_BOSD_DISP==1) // State Display (Box OSD STYLE #1 / Coordinates)
	    
		if(bMAF_BoxCnt==BAF_BOXOSD_TIME) {
				// PCHAN 21.03.08 caculate box size
                gnBoxPosMAF_Y[3] = (((LibUtlInterp1D(gbMAF_MFpos_E, 0, gbMAF_MFrange_T, gwMAF_BoxEY, gwMAF_BoxSY)<<16)&0xFFFF0000) // Active Area 
                                    |(LibUtlInterp1D(gbMAF_MFpos_S, 0, gbMAF_MFrange_T, gwMAF_BoxEY, gwMAF_BoxSY)     &0x0000FFFF)); 
                gnBoxPosMAF_X[3] = (((LibUtlInterp1D(gbMAF_MZpos_S, 0, gbMAF_MZrange_T, gwMAF_BoxSX, gwMAF_BoxEX)<<16)&0xFFFF0000)
                                    |(LibUtlInterp1D(gbMAF_MZpos_E, 0, gbMAF_MZrange_T, gwMAF_BoxSX, gwMAF_BoxEX)     &0x0000FFFF));   

                gwMAF_Zrange_T = gbMAF_MZrange_T*MAF_RangeSTEP;
                gwMAF_Frange_T = gbMAF_MFrange_T*MAF_RangeSTEP;
                
                gwMAF_Zpos_S = gbMAF_MZpos_S*MAF_RangeSTEP;
                gwMAF_Zpos_E = gbMAF_MZpos_E*MAF_RangeSTEP;

                gwMAF_Fpos_S = gbMAF_MFpos_S*MAF_RangeSTEP;
                gwMAF_Fpos_E = gbMAF_MFpos_E*MAF_RangeSTEP;
        }       
            
        gnBoxPosMAF_Y[2] = LibUtlInterp1D (Maf_Fmotor.nCurPos, 0, gwMAF_Frange_T,gwMAF_BoxEY ,gwMAF_BoxSY ); // Focus Pos                                                                      
        gnBoxPosMAF_Y[2] = (((gnBoxPosMAF_Y[2]<<16)&0xFFFF0000)|(gnBoxPosMAF_Y[2]&0x0000FFFF));
        gnBoxPosMAF_X[1] = LibUtlInterp1D (Maf_Zmotor.nCurPos, 0, gwMAF_Zrange_T, gwMAF_BoxSX, gwMAF_BoxEX); // Zoom Pos                                                                         
        gnBoxPosMAF_X[1] = (((gnBoxPosMAF_X[1]<<16)&0xFFFF0000)|(gnBoxPosMAF_X[1]&0x0000FFFF));
        gnBoxPosMAF_Y[0] = gnBoxPosMAF_Y[2]; // Zoom & Focus Point
        gnBoxPosMAF_X[0] = gnBoxPosMAF_X[1];

        if(bMAF_BoxCnt==1) gnBoxOnMAF = 0;
        else               gnBoxOnMAF = MAF_BOX_BITMASK;   
 
		#endif
	}
	else gnBoxOnMAF = gbMAFBoxFlag = 0;
#endif

#if (MAF_FOSD_DISP==1) // State Display (Font OSD)
	static BYTE bMAF_Disp_Cnt=0;//, bMAF_FontBuf=0, gbMenuStatebuf=0xf;	
	BYTE bMAF_state_check=0; // PCHAN 21. 04 .01

	bMAF_Disp_Cnt = (bMAF_Disp_Cnt<40) ? bMAF_Disp_Cnt+1 : 0;

	// PCHAN 21. 04 .01
	
	bMAF_state_check = (MAF_LENS_INIT || MAF_AUTOFOCUS || MAF_ZTRACKING);

    if(bMAF_Disp_Cnt<30 ) { 
        if     (MAF_LENS_INIT) DispStr("LENS INITIALIZING...", MAF_FOSD_PosY, 0, 20);
        else if(MAF_AUTOFOCUS) DispStr("FOCUS SCANNING...", MAF_FOSD_PosY, 0, 17);
        else if(MAF_ZTRACKING) DispStr("ZOOM TRACKING...", MAF_FOSD_PosY, 0, 16 );
		else if(MP(MpCamTitleOn)==2){DispClr(MAF_FOSD_PosY, 0, 20); DispStr((const char*)&gbCamTitle(0), MAF_FOSD_PosY, 0, 0x8);}
		else DispClr(MAF_FOSD_PosY, 0, 20); // for erasing the last one. 
    }
	else (MP(MpCamTitleOn)==2 && !bMAF_state_check) ?( DispClr(MAF_FOSD_PosY, 0, 20) ,DispStr((const char*)&gbCamTitle(0), MAF_FOSD_PosY, 0, 0x8)) : DispClr(MAF_FOSD_PosY, 0, 20); // when erasing this, font just displays with erasing

	
	
#endif
}

//=================================================================================================
//	Fucntion Debuging Display (Font/Grp)
//=================================================================================================
void MAF_DebugingDisp(void)
{
	gbMAFDebugOn = (gbMnDebugFnc==2);
	
	if(gbMAFDebugOn) {
		#if 1 
			GRP0 = (UINT)gnMaf_TgtPeakVal_F; 
			GRP1 = (UINT)gnAF1_Normalization;
			GRP2 = (UINT)Maf_Zmotor.nCurPos;
			GRP3 = (UINT)Maf_Zmotor.nTgtPos;
			GRP4 = (UINT)Maf_Fmotor.nCurPos;
			GRP5 = (UINT)Maf_Fmotor.nTgtPos;
			TxGrpFnc();
		#endif
		OZONE_SELw(2);
	}

    if(gbMAF_SETUP){
    	DebugDisp(gbMAFDebugOn, Dec, "CurPos_Z", MAF_FOSD_PosY_Dbg   , 24, Maf_Zmotor.nCurPos);
    	DebugDisp(gbMAFDebugOn, Dec, "TgtPos_Z", MAF_FOSD_PosY_Dbg+1 , 24, Maf_Zmotor.nTgtPos);
    	DebugDisp(gbMAFDebugOn, Dec, "CurPos_F", MAF_FOSD_PosY_Dbg+2 , 24, Maf_Fmotor.nCurPos);
    	DebugDisp(gbMAFDebugOn, Dec, "TgtPos_F", MAF_FOSD_PosY_Dbg+3 , 24, Maf_Fmotor.nTgtPos);

        DebugDisp(gbMAFDebugOn, Dec, "Total_Z" , MAF_FOSD_PosY_Dbg+5 , 24, gwMAF_Zrange_T);
    	DebugDisp(gbMAFDebugOn, Dec, "Start_Z" , MAF_FOSD_PosY_Dbg+6 , 24, gwMAF_Zpos_S);
    	DebugDisp(gbMAFDebugOn, Dec, "End_Z"   , MAF_FOSD_PosY_Dbg+7 , 24, gwMAF_Zpos_E);
    	
    	DebugDisp(gbMAFDebugOn, Dec, "Total_F" , MAF_FOSD_PosY_Dbg+9 , 24, gwMAF_Frange_T);
    	DebugDisp(gbMAFDebugOn, Dec, "Start_F" , MAF_FOSD_PosY_Dbg+10, 24, gwMAF_Fpos_S);
    	DebugDisp(gbMAFDebugOn, Dec, "End_F"   , MAF_FOSD_PosY_Dbg+11, 24, gwMAF_Fpos_E);
    }
    else{
    	// AF Flag / Test & State
    	DebugDisp(gbMAFDebugOn, Hex, "MainState", MAF_FOSD_PosY_Dbg  , 24, gbAF_MainState);
    	DebugDisp(gbMAFDebugOn, Hex, "bAF_Flag", MAF_FOSD_PosY_Dbg+1 , 24, gbAutoFocus_Flag);
    	DebugDisp(gbMAFDebugOn, Hex, "AF_State", MAF_FOSD_PosY_Dbg+3 , 24, gbMAF_OneTimeState);

    	// Position Info
    	DebugDisp(gbMAFDebugOn, Dec, "PosCtr_Z", MAF_FOSD_PosY_Dbg+6 , 24, Maf_Zmotor.bPosGo);
    	DebugDisp(gbMAFDebugOn, Dec, "CurPos_Z", MAF_FOSD_PosY_Dbg+7 , 24, Maf_Zmotor.nCurPos);
    	DebugDisp(gbMAFDebugOn, Dec, "TgtPos_Z", MAF_FOSD_PosY_Dbg+8 , 24, Maf_Zmotor.nTgtPos);
    	
    	DebugDisp(gbMAFDebugOn, Dec, "PosCtr_F", MAF_FOSD_PosY_Dbg+11, 24, Maf_Fmotor.bPosGo);
    	DebugDisp(gbMAFDebugOn, Dec, "CurPos_F", MAF_FOSD_PosY_Dbg+12, 24, Maf_Fmotor.nCurPos);
    	DebugDisp(gbMAFDebugOn, Dec, "TgtPos_F", MAF_FOSD_PosY_Dbg+13, 24, Maf_Fmotor.nTgtPos);
    }
}

//=================================================================================================
//	Motor Current Managing
//=================================================================================================
void MAF_Current_Mng(void)
{
   	if(Maf_Zmotor.nCurPos==Maf_Zmotor.nTgtPos) MAF_HOLD_Z; // Motor Current Save (All Low)
   	if(((Maf_Fmotor.nCurPos==Maf_Fmotor.nTgtPos))&&(gbAutoFocus_Flag==0)) MAF_HOLD_F;
    	
   	gbMaf_TimerEn = (Maf_Zmotor.bPosGo|Maf_Fmotor.bPosGo|gbAutoFocus_Flag); // Timer Control Enable condition    
}

//=================================================================================================
//	GPIO Drive Handling (Timer IRQ Base)
//=================================================================================================
void MAF_MovingState(void) //PCHAN 21.03.08 : ISPM0 erase
{
	if(Maf_Zmotor.bPosGo) 
	{
		if(Z_SpdCtrOn) 
		{  
			Maf_Zmotor.bSpeedCnt=(Maf_Zmotor.bSpeedCnt==gbMotorSpeedStep[2*gbMaf_MnlSpeed]) ? 0 : Maf_Zmotor.bSpeedCnt+1;
			// Z-Active Condition
			if(!Maf_Zmotor.bSpeedCnt) { // Default
				if((gbAF_MainState==1)||(gbMAF_DevMode==1))    Maf_Zmotor.bActive = (Maf_Zmotor.nCurPos>Maf_Zmotor.nTgtPos) ? 1 : 2; // Debuging or Initialzation
				else { // Normal Operation (Area Limit)
					if(Maf_Zmotor.nCurPos>Maf_Zmotor.nTgtPos) { // Wide Direction
						Maf_Zmotor.bActive     = (Maf_Zmotor.nCurPos>gwMAF_Zpos_S) ? 1 : 0;
						Maf_Zmotor.bDirFlag    = (Maf_Zmotor.nCurPos>gwMAF_Zpos_S) ? 1 : Maf_Zmotor.bDirFlag;
						Maf_Zmotor.bReverseCnt = (Maf_Zmotor.bDirFlagBuf!=Maf_Zmotor.bDirFlag) ? MAF_REVERS_STEP_Z : Maf_Zmotor.bReverseCnt;
						Maf_Zmotor.bDirFlagBuf = Maf_Zmotor.bDirFlag;
					}
					else {                                        // Tele Direction
						Maf_Zmotor.bActive     = (Maf_Zmotor.nCurPos<gwMAF_Zpos_E) ? 2 : 0;
						Maf_Zmotor.bDirFlag    = (Maf_Zmotor.nCurPos<gwMAF_Zpos_E) ? 2 : Maf_Zmotor.bDirFlag;
						Maf_Zmotor.bReverseCnt = (Maf_Zmotor.bDirFlagBuf!=Maf_Zmotor.bDirFlag) ? MAF_REVERS_STEP_Z : Maf_Zmotor.bReverseCnt;
						Maf_Zmotor.bDirFlagBuf = Maf_Zmotor.bDirFlag;
					}
				}
			}
			else Maf_Zmotor.bActive=0;
		}
		else Maf_Zmotor.bPosGo=Maf_Zmotor.bActive=gbMaf_MnlSpeed=0;
	}
 //----------------------------------------------------------------------------------------------------------------------------------------------------------
	if(Maf_Fmotor.bPosGo) 
	{
		if(F_SpdCtrOn) 
		{	
			Maf_Fmotor.bSpeedCnt=(Maf_Fmotor.bSpeedCnt==(gbMotorSpeedStep[gbAutoFocus_Flag+2*gbMaf_MnlSpeed]+((Maf_Zmotor.nCurPos>MAF_LDOF_Z)&&gbAutoFocus_Flag))) ? 0 : Maf_Fmotor.bSpeedCnt+1;
			// F-Active Condition
			if(!Maf_Fmotor.bSpeedCnt) { // Default
				if((gbAF_MainState==1)||(gbMAF_DevMode==1))    Maf_Fmotor.bActive = (Maf_Fmotor.nCurPos>Maf_Fmotor.nTgtPos) ? 1 : 2; // Debuging or Initialzation
				else { // Normal Operation (Area Limit)
					if(Maf_Fmotor.nCurPos>Maf_Fmotor.nTgtPos) { // Wide Direction
						Maf_Fmotor.bActive     = (Maf_Fmotor.nCurPos>gwMAF_Fpos_S) ? 1 : 0;
						Maf_Fmotor.bDirFlag    = (Maf_Fmotor.nCurPos>gwMAF_Fpos_S) ? 1 : Maf_Fmotor.bDirFlag;
						Maf_Fmotor.bReverseCnt = (Maf_Fmotor.bDirFlagBuf!=Maf_Fmotor.bDirFlag) ? MAF_REVERS_STEP_F : Maf_Fmotor.bReverseCnt;
						Maf_Fmotor.bDirFlagBuf = Maf_Fmotor.bDirFlag;
					}
					else {                                        // Tele Direction
						Maf_Fmotor.bActive     = (Maf_Fmotor.nCurPos<gwMAF_Fpos_E) ? 2 : 0;
						Maf_Fmotor.bDirFlag    = (Maf_Fmotor.nCurPos<gwMAF_Fpos_E) ? 2 : Maf_Fmotor.bDirFlag;
						Maf_Fmotor.bReverseCnt = (Maf_Fmotor.bDirFlagBuf!=Maf_Fmotor.bDirFlag) ? MAF_REVERS_STEP_F : Maf_Fmotor.bReverseCnt;
						Maf_Fmotor.bDirFlagBuf = Maf_Fmotor.bDirFlag;
					}
				}
			}
			else Maf_Fmotor.bActive=0;
		}
		else Maf_Fmotor.bPosGo=Maf_Fmotor.bActive=gbMaf_MnlSpeed=0;
	}
}

void MAF_PhaseControl(void) // PCHAN 21.03.08 : ISPM0 erase
{
	MAF_MovingState(); // speed
	
	// Zoom Motor Control
	if(Maf_Zmotor.bActive) { // Active condition
		switch(Maf_Zmotor.bStateStep) { // Zoom Motor Driving Step
			case MAF_STEP1 : { MAF_H(MAF_AP_Z); MAF_H(MAF_BP_Z); MAF_L(MAF_AM_Z); MAF_L(MAF_BM_Z); break; } // 1 1 0 0 (step1)
			case MAF_STEP2 : { MAF_L(MAF_AP_Z); MAF_H(MAF_BP_Z); MAF_L(MAF_AM_Z); MAF_L(MAF_BM_Z); break; } // 0 1 0 0 (step2)
			case MAF_STEP3 : { MAF_L(MAF_AP_Z); MAF_H(MAF_BP_Z); MAF_H(MAF_AM_Z); MAF_L(MAF_BM_Z); break; } // 0 1 1 0 (step3)
			case MAF_STEP4 : { MAF_L(MAF_AP_Z); MAF_L(MAF_BP_Z); MAF_H(MAF_AM_Z); MAF_L(MAF_BM_Z); break; } // 0 0 1 0 (step4)
			case MAF_STEP5 : { MAF_L(MAF_AP_Z); MAF_L(MAF_BP_Z); MAF_H(MAF_AM_Z); MAF_H(MAF_BM_Z); break; } // 0 0 1 1 (step5)
			case MAF_STEP6 : { MAF_L(MAF_AP_Z); MAF_L(MAF_BP_Z); MAF_L(MAF_AM_Z); MAF_H(MAF_BM_Z); break; } // 0 0 0 1 (step6)
			case MAF_STEP7 : { MAF_H(MAF_AP_Z); MAF_L(MAF_BP_Z); MAF_L(MAF_AM_Z); MAF_H(MAF_BM_Z); break; } // 1 0 0 1 (step7)
			case MAF_STEP8 : { MAF_H(MAF_AP_Z); MAF_L(MAF_BP_Z); MAF_L(MAF_AM_Z); MAF_L(MAF_BM_Z); break; } // 1 0 0 0 (step8)
		}
		if     (Maf_Zmotor.bActive==1) Maf_Zmotor.bStateStep = (Maf_Zmotor.bStateStep<MAF_STEP8) ? (Maf_Zmotor.bStateStep+MAF_STEP1) : MAF_STEP1; // Wide Direction
		else if(Maf_Zmotor.bActive==2) Maf_Zmotor.bStateStep = (Maf_Zmotor.bStateStep>MAF_STEP1) ? (Maf_Zmotor.bStateStep-MAF_STEP1) : MAF_STEP8; // Tele Direction
		
		if(Maf_Zmotor.bReverseCnt) Maf_Zmotor.bReverseCnt--;
		else Maf_Zmotor.nCurPos = (Maf_Zmotor.bActive==1) ? ((Maf_Zmotor.nCurPos>0) ? (Maf_Zmotor.nCurPos-1) : Maf_Zmotor.nCurPos) : (Maf_Zmotor.nCurPos+1);
	}

	// Focus Motor Control	
	if(Maf_Fmotor.bActive) { // Active condition
        BYTE bFStateStep = ((gbAF_MainState==1)&&MAF_DOM_INIT) ? 9-Maf_Fmotor.bStateStep : Maf_Fmotor.bStateStep;
        switch(bFStateStep) { // Focus Motor Driving Step
			case MAF_STEP1 : { MAF_H(MAF_AP_F); MAF_H(MAF_BP_F); MAF_L(MAF_AM_F); MAF_L(MAF_BM_F); break; } // 1 1 0 0 (step1)
			case MAF_STEP2 : { MAF_L(MAF_AP_F); MAF_H(MAF_BP_F); MAF_L(MAF_AM_F); MAF_L(MAF_BM_F); break; } // 0 1 0 0 (step2)
			case MAF_STEP3 : { MAF_L(MAF_AP_F); MAF_H(MAF_BP_F); MAF_H(MAF_AM_F); MAF_L(MAF_BM_F); break; } // 0 1 1 0 (step3)
			case MAF_STEP4 : { MAF_L(MAF_AP_F); MAF_L(MAF_BP_F); MAF_H(MAF_AM_F); MAF_L(MAF_BM_F); break; } // 0 0 1 0 (step4)
			case MAF_STEP5 : { MAF_L(MAF_AP_F); MAF_L(MAF_BP_F); MAF_H(MAF_AM_F); MAF_H(MAF_BM_F); break; } // 0 0 1 1 (step5)
			case MAF_STEP6 : { MAF_L(MAF_AP_F); MAF_L(MAF_BP_F); MAF_L(MAF_AM_F); MAF_H(MAF_BM_F); break; } // 0 0 0 1 (step6)
			case MAF_STEP7 : { MAF_H(MAF_AP_F); MAF_L(MAF_BP_F); MAF_L(MAF_AM_F); MAF_H(MAF_BM_F); break; } // 1 0 0 1 (step7)
			case MAF_STEP8 : { MAF_H(MAF_AP_F); MAF_L(MAF_BP_F); MAF_L(MAF_AM_F); MAF_L(MAF_BM_F); break; } // 1 0 0 0 (step8)
		}
		if     (Maf_Fmotor.bActive==1) Maf_Fmotor.bStateStep = (Maf_Fmotor.bStateStep<MAF_STEP8) ? (Maf_Fmotor.bStateStep+MAF_STEP1) : MAF_STEP1; // Near Direction
		else if(Maf_Fmotor.bActive==2) Maf_Fmotor.bStateStep = (Maf_Fmotor.bStateStep>MAF_STEP1) ? (Maf_Fmotor.bStateStep-MAF_STEP1) : MAF_STEP8; // Far  Direction

		if(Maf_Fmotor.bReverseCnt) Maf_Fmotor.bReverseCnt--;
		else Maf_Fmotor.nCurPos = (Maf_Fmotor.bActive==1) ? ((Maf_Fmotor.nCurPos>0) ? (Maf_Fmotor.nCurPos-1) : Maf_Fmotor.nCurPos) : (Maf_Fmotor.nCurPos+1);
	}
}

#endif
/* EOF */
