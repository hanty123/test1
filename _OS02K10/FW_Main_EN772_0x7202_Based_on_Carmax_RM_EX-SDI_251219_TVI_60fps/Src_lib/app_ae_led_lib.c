/* **************************************************************************
 File Name	:	app_ae_led_lib.c
 Description:	Adaptive Lighting Control
 Designer	:	Kim Sung-hoon
 Date		:	18. 2. 8
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "../Src/dev.h"

#define ENABLE_EXTERN_MODE	1
//----------------------------------------------------------------------------------------

#define TotalClkOfVLOCK	gnTotalClkOfVLOCK
//----------------------------------------------------------------------------------------
// Common Macro
//----------------------------------------------------------------------------------------
// Variable

// 181017 JJH
int		giDbIIR=0, giDrIIR=0;

UINT	gnAeLed = 0x0;
#define gnTotalClkOfIRIS	gnAeLed

extern BYTE gbLedSel;

extern UINT gnAwbOdmCapOn;

//----------------------------------------------------------------------------------------

#define ErrStepMax_RATE	((int)10)		// 10% = 1/10  -> 10
#define ErrStepMin_RATE	((int)100)		// 1%  = 1/100 -> 100
#define ErrStepMax_MIN	((int)10)
#define ErrStepMin_MIN	((int)1)

#define ErrStepMax_Err_Sta	400																// LED_TUNING!
#define ErrStepMax_Err_End	100			// Min : 50											//		"
#define AE_LED_OFS_END		(gnLED_OFS<<1)

#define DIMMING_ON	((MP(MpAdaptive)==1)&&gnAeLed) // adaptive 1 full 2

int giSetLedThres_ON = 0;
int giSetLedThres_OFF = 0;

#define AE_AGC_LED_ON0			((int)giSetLedThres_ON * 22 + 96) // giSetLedThres_ON = 11  => 338
#define AE_AGC_LED_ON			((AE_AGC_LED_ON0 * aiAgcMax) / 536) // 
#define AE_AGC_LED_OFF_MIN		10
#define AE_AGC_LED_OFF			((((((int)giSetLedThres_OFF) * (AE_AGC_LED_ON0 - 96) + 10) / 20) * aiAgcMax) / 536 + AE_AGC_LED_OFF_MIN)

UINT gnLED_HEP_Hz = 0; //181203
UINT gnLedTotalclk_Buf = 0;
UINT gnLED_OFSMAX = 1237500;
UINT gnLED_OFSMIN = 1000;
UINT gnLED_OFS = 1000;
int	 giAGC_LED_GAB = 64;
BYTE gbLED_DLY = 2;
BYTE gbAGC_DLY = 1;
BYTE gbAE_LED_ON_TIME = 5;

int  giDimDelay = 0;
int  giLedFull = 60;
BYTE gbAE_LED_FPS = 30;

UINT gnAeOnCnt = 0;
BYTE gbLED_CHG_CNT = 0;	// 1:OFF AGC > LED, 11:ON AGC > LED, 21:OFF AGC < LED, 31:ON AGC < LED

BYTE gbLedDlyCnt = 0;
BYTE gbLedMenuChg = 0;

// 181017 JJH
extern int giAE_LED_Pos_DIS_MIN, giAE_LED_Pos_DIS_MAX, giAE_LED_PosX, giAE_LED_PosY, giAE_LEDStart; // 190610 JJH : LED start position
extern BYTE gbAE_LED_Power;

extern int ISPM LibAeSpeed (const int, const int, const int);

//----------------------------------------------------------------------------------------
// Function

void LibAe_IR_PWM_Ctrl_OFS(UINT anClkOfPeriodOfIRIS, UINT anTotalClkOfIRIS)
{
	const UINT nNumOfPeriodOfIRIS = TotalClkOfVLOCK / anClkOfPeriodOfIRIS;

	const UINT nClkOfIRIS = anTotalClkOfIRIS / nNumOfPeriodOfIRIS;

	IRIS_MODw(0x1);
	IRIS_HSPw(0x0);										// Setup Period
	IRIS_HEPw(anClkOfPeriodOfIRIS);						// Setup Period [15:0]
	IRIS_VSPw(0x0);										// Setup Period [15:0]
	IRIS_VEPw(nNumOfPeriodOfIRIS);						// Setup Period [15:0]
	IRIS_CLPHw(nClkOfIRIS);								// Setup Duty   [15:0]
	IRIS_CLPLw(anTotalClkOfIRIS % nNumOfPeriodOfIRIS);	// Setup Duty   [15:0]
}

UINT LibGetAeLedMax(void)
{
    if(gbAE_LED_TuningOn){
        return (gwAE_LED_HEP_Hz) ? ((TotalClkOfVLOCK/gwAE_LED_HEP_Hz)*gwAE_LED_HEP_Hz) : TotalClkOfVLOCK ;
    }
    else{
        return ((TotalClkOfVLOCK/gnLED_HEP_Hz)*gnLED_HEP_Hz) ; //181203
    }
}

void LibAe_IR_PWM_Ctrl(void)
{
	const UINT nTotalClkOfIRIS_Max = LibGetAeLedMax();

	if(gnTotalClkOfIRIS > nTotalClkOfIRIS_Max) gnTotalClkOfIRIS = nTotalClkOfIRIS_Max;
 
    if(gbAE_LED_TuningOn){
        if(gwAE_LED_HEP_Hz) {
        	LibAe_IR_PWM_Ctrl_OFS(gwAE_LED_HEP_Hz, gnTotalClkOfIRIS);
        }    
    }
    else{
    if(gnLED_HEP_Hz) {
    		LibAe_IR_PWM_Ctrl_OFS(gnLED_HEP_Hz, gnTotalClkOfIRIS);
    	}
	}	   
}

void LibLED_SET(const UINT anTotalClkOfIRIS, const UINT anTrace)
{

    if((MP(MpAdaptive)==2)&&(anTotalClkOfIRIS>0)){
        gnTotalClkOfIRIS = gnLED_OFSMIN+((anTotalClkOfIRIS-gnLED_OFSMIN)/gbAE_LED_Power)*MP(MpLedPower);
        gnTotalClkOfIRIS = MINMAX(gnTotalClkOfIRIS, gnLED_OFSMIN, gnLED_OFSMAX);        
    }
	else gnTotalClkOfIRIS = anTotalClkOfIRIS;

	LibAe_IR_PWM_Ctrl();

	if(gnTotalClkOfIRIS == 0) {
        giDbIIR = ((giAE_LED_PosX>>3)<<4); // 181017 JJH
        giDrIIR = ((giAE_LED_PosY>>3)<<4);
	}
	//------------------------------------------------------------------------------
	if((gbMnDebugFnc==MN_DBG_TDN)&&gbAE_LED_TuningOn) GRP5 = anTrace; // LED on/of trace 
}

void LibLedTdnChk(void)
{
	if(gnTdnChkOut==TDN_NIT || gnTdnChkOut==TDN_DAY) {
		if(gnAwbOdmCapOn==0) {
			AWBLNOR_SELw(gnTdnChkOut==TDN_NIT);
		}
	}
}
// 181017 JJH led range setting  -------------------------------------------------------------------------------------------------------

int LibAeLedOff(const BYTE abDbg)
{
	if((gnTdnChkOut==TDN_DAY) && ((MP(MpTdn)==MN_TDN_DAY)||(gbLedSel&&(MP(MpTdn)==MN_TDN_AUTO)))) return 1; 

	if(gnAeLed || abDbg) {

		const UINT nTcnt = AWBL_CCT_SUM_LOCKr;
		const int iDb = (nTcnt) ? (int)AWBL_CBDB_SUM_LOCKr / (int)nTcnt : 0;
		const int iDr = (nTcnt) ? (int)AWBL_CRDR_SUM_LOCKr / (int)nTcnt : 0;
		const int iStand_Db = (giAE_LED_PosX>>3), iStand_Dr = (giAE_LED_PosY>>3);

		if(iDb && iDr) {	
			if(gnAeLed && gnTdnChkOut==TDN_NIT) {
				#define IIR_SPEED	0xf8
				giDbIIR = ( ((int)IIR_SPEED*giDbIIR) + ((int)(0x100-IIR_SPEED)*(iDb<<4)) ) >> 8;
				giDrIIR = ( ((int)IIR_SPEED*giDrIIR) + ((int)(0x100-IIR_SPEED)*(iDr<<4)) ) >> 8;
			}

			const int iDb_Diff = iDb - (giAE_LED_PosX>>3);
			const int iDr_Diff = iDr - (giAE_LED_PosY>>3);

			const int iDis =  iDb_Diff * iDb_Diff + iDr_Diff * iDr_Diff ;

			const int iDbI_Diff = (giDbIIR>>4) - (giAE_LED_PosX>>3);
			const int iDrI_Diff = (giDrIIR>>4) - (giAE_LED_PosY>>3);
			const int iDisI =  iDbI_Diff * iDbI_Diff + iDrI_Diff * iDrI_Diff ;

			if((gbMnDebugFnc==MN_DBG_TDN)&&gbAE_LED_TuningOn) GRP4 = iDis; 

			DebugDisp((gbMnDebugFnc==MN_DBG_TDN), Dec, "PosY", 6, 24, iDr);
			DebugDisp((gbMnDebugFnc==MN_DBG_TDN), Dec, "PosX", 7, 24, iDb);

            if((iStand_Db>iDb)&&(iStand_Dr>iDr)){
    			if( ((iDis > (giAE_LED_Pos_DIS_MIN>>3)) && (iDisI > (giAE_LED_Pos_DIS_MIN>>3))) || ((giAE_LED_Pos_DIS_MIN>>3)==0) )			
			{
				return 1;
			}
		}
            else{  
				if( ((iDis > (giAE_LED_Pos_DIS_MAX>>3)) && (iDisI > (giAE_LED_Pos_DIS_MAX>>3))) || ((giAE_LED_Pos_DIS_MAX>>3)==0) )
				{
					return 1;
				}
			}

		}
	}

	return 0;
}
// -------------------------------------------------------------------------------------------------------------------------------------

int LibLED_OFF_COLOR(const BYTE abDbg)
{
	return (((MP(MpTdn)==MN_TDN_AUTO) && (MP(MpAdaptive) == 0)) ? 1 : LibAeLedOff(abDbg));
}

//----------------------------------------------------------------------------------------
//181203
void LibInitAeLed( const int aiAE_AGC_LED_GAB, const BYTE abAE_AGC_DLY, const BYTE abAE_LED_ON_TIME )
{
	giAGC_LED_GAB = aiAE_AGC_LED_GAB;
	gbAGC_DLY = abAE_AGC_DLY;
	gbAE_LED_ON_TIME = abAE_LED_ON_TIME;
	gnLedTotalclk_Buf = gnLedTotalclk;
    
}

void LibLedDriverChg(UINT  anAE_LED_HEP_Hz, const UINT anAE_LED_OFSMAX, const UINT anAE_LED_OFSMIN, const UINT anAE_LED_OFS, const BYTE abAE_LED_DLY)
{   
    gnLED_HEP_Hz = anAE_LED_HEP_Hz;
    gnLED_OFSMAX = anAE_LED_OFSMAX;
    gnLED_OFSMIN = anAE_LED_OFSMIN;
    gnLED_OFS = anAE_LED_OFS;
    gbLED_DLY = abAE_LED_DLY;
}

void LibLED_SET_DIMM(const UINT anTotalClkOfIRIS, const UINT anNoDly, const UINT anTrace)
{
	if(gbLedDlyCnt && (anNoDly==0)) { gbLedDlyCnt--; return; }

    if(MP(MpAdaptive) == 2) {
		if(anTotalClkOfIRIS==gnLED_OFSMAX) {
			giLedFull = FPS_VDI>>1;		//for AeLedCtrl() entrance after end of Full
		}
		
		if(anTotalClkOfIRIS==0) {
			giLedFull = 0;
		}
	}

	if(gnTotalClkOfIRIS==0 && anTotalClkOfIRIS==gnLED_OFSMIN) gnAeOnCnt = (gbAE_LED_FPS * gbAE_LED_ON_TIME);

	gbLedDlyCnt = gbLED_DLY;

	LibLED_SET(anTotalClkOfIRIS, anTrace);
}

void LibAeLedTest(void)
{
      TxGrp();
  
      GRP0=gnAeLed;
      GRP2=AE5_SUM1_LOCKr;
      
      static UINT gnAeLedBufExt[5]={0,};
  
	#define AeLedDlyOut		gnAeLedBufExt[0]

      if(gbAE_LED_TEST_RUN==2) {
		#define NUM1_LEN	7
		#define NUM2_LEN	3
          
          const UINT nAeWin5PxCnt = ((AE5_VEPr - AE5_VSPr)+1) * ((AE5_HEPr - AE5_HSPr)+1);
          const UINT nAeWin5Avg   = AE5_SUM1_LOCKr / nAeWin5PxCnt;
          static UINT nAeWin5AvgBuf = 0;
          
          UartTxByte(PC_STX);
          UartTxByte(PC_CMD_STR);
          UartTxByte(NUM1_LEN+1+NUM2_LEN+2+NUM2_LEN+2);
  
          int2str(gbStr, AeLedDlyOut/*gnAeLed*/, NUM1_LEN);
          UartTxStr(gbStr);
          UartTxByte('\t');
  
          int2str(gbStr, nAeWin5Avg/*AE4_SUM1_LOCKr*//*iAgcPos*/, NUM2_LEN);
          UartTxStr(gbStr);
          UartTxByte('\t');
  
          UartTxByte('=');
          int2str(gbStr, (int)nAeWin5Avg - (int)nAeWin5AvgBuf, NUM2_LEN);
          UartTxStr(gbStr);
          UartTxByte('\r');
          UartTxByte('\n');
  
          UartTxByte(PC_ETX);
  
          nAeWin5AvgBuf = nAeWin5Avg;
      }
  
      int i;
      for(i=0; i<gbAGC_DLY; i++)
      {
          gnAeLedBufExt[i] = gnAeLedBufExt[i+1];
      }
      gnAeLedBufExt[i] = gnAeLed;
  
      //----------------------------------------------------------------------------------------
      DebugDisp((gbMnDebugFnc==MN_DBG_TDN), Dec, "AWBLNOR_SEL", 8, 24, AWBLNOR_SELr);
  
}

//float ISPM LibAeLedCtrlTest(const int aiErrNow, float afAePosflt, const int aiOfs, const int aiAgcMax)  
int LibAeLedCtrlTest(const int aiErrNow, int afAePos, const int aiOfs, const int aiAgcMax)
{
      UNUSED_ARG(aiErrNow);
//      UNUSED_ARG(afAePosflt);
      UNUSED_ARG(afAePos);      
      UNUSED_ARG(aiOfs);
      UNUSED_ARG(aiAgcMax);
     
      //----------------------------------------------------------------------------------------
//      afAePosflt = MAX(afAePosflt, 0.f);
      afAePos = MAX(afAePos, 0);
      
      LibLED_OFF_COLOR(1);
  
      //----------------------------------------------------------------------------------------
//      static float fAePosfltTest = 0;
        static int iAePosfltTest = 0;   

        if(gbAE_LED_TEST_RUN == 1)
        {
          gnAeLed = gnAE_LED_TEST_MAX;

        #define AE_SUM_MAX	50000000

          if(AE5_SUM1_LOCKr < AE_SUM_MAX) {
              UINT nAePosfltStep = (AE_SUM_MAX - AE5_SUM1_LOCKr) / 5000000;
              nAePosfltStep = MINMAX(nAePosfltStep, 1, 10);
//              fAePosfltTest += nAePosfltStep;
              iAePosfltTest += nAePosfltStep;              
          }
          else {
              gbAE_LED_TEST_RUN=2;
              gnAeLed = gnAE_LED_TEST_MIN;
          }
        }
        else if(gbAE_LED_TEST_RUN == 2)
        {
          static UINT nTotalClkOfIRIS_D = 1;
          const UINT nTotalClkOfIRIS_Step = gwAE_LED_TEST_STEP; 

          const UINT nTotalClkOfIRIS_Max = LibGetAeLedMax();

          switch(nTotalClkOfIRIS_D) {
              case 1 :
                  gnAeLed += nTotalClkOfIRIS_Step;
                  if(gnAeLed >= nTotalClkOfIRIS_Max || gnAeLed >= (gnAE_LED_TEST_MAX)) {
                      nTotalClkOfIRIS_D = 2;
                  }
                  break;
              case 2 :
                  if(gnAeLed <= nTotalClkOfIRIS_Step || gnAeLed <= (gnAE_LED_TEST_MIN)) {
                      nTotalClkOfIRIS_D = 1;
                      gbAE_LED_TEST_RUN=0;

                  }
                  else {
                      gnAeLed -= nTotalClkOfIRIS_Step;
                  }
                  break;
          }
        }
        else {
          if(gnAE_LED_LED) gnAeLed = gnAE_LED_LED;

//          fAePosfltTest = (gwAE_LED_AGC) ? (float)(aiOfs + gwAE_LED_AGC) : afAePosflt;
          iAePosfltTest = (gwAE_LED_AGC) ? (aiOfs + gwAE_LED_AGC) : afAePos;          
        }
        //----------------------------------------------------------------------------------------
        LibAe_IR_PWM_Ctrl();

        //----------------------------------------------------------------------------------------
//      return fAePosfltTest;
      return iAePosfltTest;
}

//----------------------------------------------------------------------------------------
extern UINT gnGetTdnDly;

int LibLedTdnChg(UINT *apnDnChk, UINT *apnDnSeq, const int aiTdnMenuChg, const int aiLedMenuChg, _TdnThres* sTdnThres)
{
/*
 Determine on/off of LED in AE function, Therefore TDN status of Auto mode is determined  
 *apnDnChk              : F/W condition
 *apnDnSeq              : change delay
 aiTdnMenuChg           : device condition 
 _TdnThres* sTdnThres   : menu structure 
*/
	static  UINT gnAeLedBuf;

    // LED on/off threshold set
    if(MP(MpAdaptive)==1){
        giSetLedThres_ON	=   ((int)sTdnThres->bDNThres);// MP(MpTdnThrs) = 11  => 338
        giSetLedThres_OFF	=   ((int)sTdnThres->bNDThres);
	}
	
	if((MP(MpAdaptive)==1) && (MP(MpTdn)==MN_TDN_AUTO))	
	{
	    if(gbLedSel){
            if(aiLedMenuChg) *apnDnSeq=0;
            *apnDnChk=TDN_DAY;
		}
        else{
		    if ((gnAeLed>0)&&(gnAeLedBuf==0))		{*apnDnSeq=0; *apnDnChk=TDN_NIT;}	// Auto mode, Led is on
		    else if ((gnAeLed==0)&&(gnAeLedBuf>0))	{*apnDnSeq=0; *apnDnChk=TDN_DAY;}	// Auto mode, Led is off
		}
	}
	
	gnAeLedBuf = gnAeLed;

	if(!gbLedSel&&aiTdnMenuChg && MP(MpTdn)==MN_TDN_AUTO && gnAeLed && gnTdnChkOut==TDN_DAY) {	    
		*apnDnSeq=0; *apnDnChk=TDN_NIT;
    }

    return ((MP(MpAdaptive)!=1)|| MP(MpTdn)==MN_TDN_DAY || MP(MpTdn)==MN_TDN_NIGHT || MP(MpTdn)==MN_TDN_EXTERN);	    
}

void LibLedMenuChg(void)
{
/*
 gbLedMenuChg   : 1 at the time of D&N menu change
 giLedFull      : Activate AeLedCtrl() in Adaptive Lighting
*/
	if(giDimDelay) giDimDelay--;
    if(gbAE_LED_TuningOn&&(gbMnDebugFnc==MN_DBG_TDN))GRP6=giDimDelay;     
    
	//----------------------------------------------------------------------------------------
    
	if(gbLedMenuChg)  
	{
		static BYTE gbMnAdaptive1d = 1;

		gbLedMenuChg = 0;

		giLedFull = FPS_VDI>>1;

        if( ((MP(MpTdn)==MN_TDN_DAY) || (MP(MpTdn)==MN_TDN_NIGHT) || (((MP(MpTdn)==MN_TDN_EXTERN) || (MP(MpTdn)==MN_TDN_AUTO))&&(gnTdnChkOut==TDN_NIT)) )&& gbMnAdaptive1d != 1 && (MP(MpAdaptive)==1))
		{
			if(gnAeState==1) LibLED_SET_DIMM(gnLED_OFSMIN,1,106); // IRIS , menu change full->adaptive
		}

		gbMnAdaptive1d = MP(MpAdaptive);		
	}
	
	//----------------------------------------------------------------------------------------
	if(MP(MpAdaptive) == 1)	 
	{
		if(giLedFull) giLedFull--; // 15
	}

//    DispDatDec("gnLedTotalclk",  25, 24, gnLedTotalclk);

    if(gnLedTotalclk_Buf!=gnLedTotalclk){   // 148.5MHz <-> 74.25MHz
            
        gnLED_HEP_Hz = (gnLedTotalclk>gnLedTotalclk_Buf) ? (gnLED_HEP_Hz*2) : (gnLedTotalclk<gnLedTotalclk_Buf) ? (gnLED_HEP_Hz/2) : gnLED_HEP_Hz; //181203
    }	
	
    gnLedTotalclk_Buf=gnLedTotalclk;
	
}

void LibLedWdrChg(void)
{			

    static BYTE bLED_FPS_Buf = 0, bLED_FPS_Buf1 = 0, bWdrOn_L=0;
    
    	gbAE_LED_FPS = ((gbModeWdrOn_L) ? (FPS_VDI>>1) : FPS_VDI);	// WDR, on short

        bLED_FPS_Buf   = (gbModeWdrOn_L) ? 1 : 0;

        gbLED_DLY = (gbAE_LED_FPS<FPS_VDI) ? (gbLED_DLY>>1) : ((gbModeWdrOn_L) ||((bLED_FPS_Buf==0)&&(bLED_FPS_Buf1!=bLED_FPS_Buf)&&!bWdrOn_L)) ? (gbLED_DLY<<1) : gbLED_DLY ;     

        if(gbModeWdrOn_L){
            gbAGC_DLY = gbAGC_DLY; 
            bWdrOn_L = 1;
        }
   
        gbAGC_DLY = (gbAE_LED_FPS<FPS_VDI) ?  (gbAGC_DLY + 1) : ((bLED_FPS_Buf==0)&&(bLED_FPS_Buf1!=bLED_FPS_Buf)) ? (gbAGC_DLY-1) : gbAGC_DLY ;


//        gbAGC_DLY = (gbAE_LED_FPS<FPS_VDI) ? ((gbAGC_DLY-1)>>1) + 1 : ((bLED_FPS_Buf==0)&&(bLED_FPS_Buf1!=bLED_FPS_Buf)) ? ((gbAGC_DLY-1)<<1) + 1 : gbAGC_DLY ;
//
//        gbAGC_DLY = (gbAE_LED_FPS<FPS_VDI) ? (gbAGC_DLY + 1) : ((bLED_FPS_Buf==0)&&(bLED_FPS_Buf1!=bLED_FPS_Buf)) ? (gbAGC_DLY-1) : gbAGC_DLY ;

        gbAE_LED_FPS = (gbModeWdrOn_L) ? (gbAE_LED_FPS<<1) : gbAE_LED_FPS;        

        bLED_FPS_Buf1=bLED_FPS_Buf;    
   
}

void LibLedIrisChg(void)
{
    if((MP(MpAdaptive)==1) && gnAeLed && MP(MpTdn)!=MN_TDN_EXTERN)
	{
		if(LibLED_OFF_COLOR(0)) {
			if(giDimDelay == 0){
				giDimDelay = gnGetTdnDly;
				LibLED_SET_DIMM(0,1,5);
			}
		}
	}
}

//----------------------------------------------------------------------------------------
//float ISPM LibAeLedCtrl(const int aiErrNow, float afAePosflt, const int aiOfs, const int aiAgcMax, const int aiAE_ERR_MGN, const int aiUpAE_SPEED)
int LibAeLedCtrl(const int aiErrNow, int afAePosflt, const int aiOfs, const int aiAgcMax, const int aiAE_ERR_MGN, const int aiUpAE_SPEED)
{
/*
 Calculates error and determines LED on/off by AGC
 Control LED from minimum to max value
 aiErrNow       : iErr
 afAePosflt     : gfAePosL0 = ifmul8(giAePos) 
 aiOfs          : iHssLmt+iIrsLmt
 aiAgcMax       : iAgcLmt
 aiAE_ERR_MGN   : AE_ERR_MGN(0x8)
 aiUpAE_SPEED   : UP(UpAE_SPEED)(128) Tracking Speed : 0 ~ 128 ~ 255 (x0.25 ~ x1 ~ x4)
*/

    int afAePos = afAePosflt;
    // error calculation, ALF_ON == ((MP(MpAdaptive)==1)&&gnAeLed), (ALF_ON && !(IR && DAY)) ? aiAE_ERR_MGN + (aiAE_ERR_MGN>>1) : aiAE_ERR_MGN  -> Large error margin for LED
	const int iAE_ERR_MGN = (DIMMING_ON) ? ((!gbLedSel)&&(MP(MpTdn)==MN_TDN_DAY)) ? aiAE_ERR_MGN : aiAE_ERR_MGN + (aiAE_ERR_MGN>>1): aiAE_ERR_MGN; 
	
//	afAePosflt += LibAeSpeed(aiErrNow, iAE_ERR_MGN, aiUpAE_SPEED); 
	afAePos += LibAeSpeed(aiErrNow, iAE_ERR_MGN, aiUpAE_SPEED);
    afAePos =  ifdiv8(afAePos);
    
    if((!gbLedSel)&&(MP(MpTdn)==MN_TDN_DAY)){ // (IR LED && MP(DAY)) At IR LED menu change
        LibLED_SET_DIMM(0,1,5); // LED off		
		goto AeLedCtrl_End;
    }

    if(MP(MpAdaptive) != 1){ // when not adaptive light 
        if(gbMnDebugFnc==MN_DBG_TDN)	LibLED_OFF_COLOR(1);  // To check DB,DR position when not AL
//		return afAePosflt;
		return ifmul8(afAePos);		
	}

	const int iErrMgn = (aiErrNow>0)? MIN(aiErrNow, (int)0x80/*giAeErrLmt*/) : MAX(aiErrNow, -0x80/*giAeErrLmt*/);

	const int iErrOn = ABS(iErrMgn)>iAE_ERR_MGN || giLedFull;  

	//----------------------------------------------------------------------------------------

//	afAePosflt = MAX(afAePosflt, 0.f);  // Ae position
	afAePos = MAX(afAePos, 0);  // Ae position
//	const int iAgcPos = (int)afAePosflt - aiOfs;    //   AGC position, iHssLmt+iIrsLmt < (int)afAePosflt < iHssLmt+iIrsLmt+aiAgcMax -> iAgcPos > 0
	const int iAgcPos = afAePos - aiOfs;    //   AGC position, iHssLmt+iIrsLmt < (int)afAePosflt < iHssLmt+iIrsLmt+aiAgcMax -> iAgcPos > 0
/*
 The minimum AGC value at which the LED is turned on is 96
 Assume step 22 in AL
 Threshold step is 20
 AGC STEP of AL 22
 AGC MIN of AL  96
 AGC MAX of AL  536
 AGC MAX : 22*20+96 = 536
*/
	const int iAE_AGC_LED_ON = AE_AGC_LED_ON;   // LED ON
	const int iAE_AGC_LED_OFF = AE_AGC_LED_OFF; // LED off
	const int iAE_AGC_LED_GAB = (((giAGC_LED_GAB) * aiAgcMax) / 536); 

	const int iAE_LED_AGC = ((int)(iAE_AGC_LED_ON - iAE_AGC_LED_GAB)); // iAE_LED_AGC is the AGC value fixed at LED control

	DebugDisp((gbMnDebugFnc==MN_DBG_TDN)&&(MP(MpAdaptive)==1)&&MP(MpTdn)!=MN_TDN_EXTERN, Hex, "D>N Thrs", 3, 24, iAE_AGC_LED_ON);
	DebugDisp((gbMnDebugFnc==MN_DBG_TDN)&&(MP(MpAdaptive)==1)&&MP(MpTdn)!=MN_TDN_EXTERN, Hex, "N>D Thrs", 4, 24, iAE_AGC_LED_OFF);

	//----------------------------------------------------------------------------------------
//	static float fAePosfltHold;
	static int iAePosHold;	
	if(0<gbLED_CHG_CNT && gbLED_CHG_CNT<11) {	// 1:OFF AGC > LED
		if(gbLED_CHG_CNT==1) { gbLED_CHG_CNT = 0; LibLED_SET_DIMM(0,1,4);/*LED_OFF(3);*/ }
		else gbLED_CHG_CNT--;
//		return fAePosfltHold;
		return ifmul8(iAePosHold);
	}

	if(10<gbLED_CHG_CNT && gbLED_CHG_CNT<21) {	// 11:ON AGC > LED
		if(gbLED_CHG_CNT==11) { gbLED_CHG_CNT = 0; LibLED_SET_DIMM(giAE_LEDStart,1,101);/*LED_ON(101,gnLED_OFSMIN);*/ } // 190610 JJH : LED start position
		else gbLED_CHG_CNT--;
//      return fAePosfltHold;
        return ifmul8(iAePosHold);
	}

	if(20<gbLED_CHG_CNT && gbLED_CHG_CNT<31) {	// 21:OFF AGC < LED
		if(gbLED_CHG_CNT==21) {
			gbLED_CHG_CNT = 0;
//			if(iAgcPos > 0) fAePosfltHold = afAePosflt + (float)iAE_AGC_LED_GAB;				// LED OFF, Increase by GAB only in AGC mode
			if(iAgcPos > 0) iAePosHold = afAePos + iAE_AGC_LED_GAB;				// LED OFF, Increase by GAB only in AGC mode			
		}
		else gbLED_CHG_CNT--;
//      return fAePosfltHold;
        return ifmul8(iAePosHold);
	}

	if(30<gbLED_CHG_CNT && gbLED_CHG_CNT<41) {	// 31:ON AGC < LED
		if(gbLED_CHG_CNT==31) {
			gbLED_CHG_CNT = 0;
//			fAePosfltHold = (float)(aiOfs + iAE_LED_AGC);
			iAePosHold = aiOfs + iAE_LED_AGC;			
		}
		else gbLED_CHG_CNT--;
//      return fAePosfltHold;
        return ifmul8(iAePosHold);
	}

    if(gbAE_LED_TuningOn&&(gbMnDebugFnc==MN_DBG_TDN)){

//    	if(gbAE_LED_AePos_STOP)	afAePosflt = fAePosfltHold;
    	if(gbAE_LED_AePos_STOP)	afAePos = iAePosHold;    	

    	if(gnAE_LED_LED || gwAE_LED_AGC) {
//    		afAePosflt = LibAeLedCtrlTest(aiErrNow, afAePosflt, aiOfs, aiAgcMax);
    		afAePos = LibAeLedCtrlTest(aiErrNow, afAePos, aiOfs, aiAgcMax);    		
    		goto AeLedCtrl_End;
    	}

	}
	//----------------------------------------------------------------------------------------
	if(gnAeOnCnt) gnAeOnCnt--;

	const int iAeLedOff = LibLED_OFF_COLOR(0);  // LED off condition : iAeLedOff = 1, LibLED_OFF_COLOR(0) : (0) means that When Led is turned on, when gnLed is not 0 , will refer to Db, Dr when turn off the Led 

#if ENABLE_EXTERN_MODE == 1
	static BYTE gbMnTdn1d = 0;
	const int iExt2Auto = (gbMnTdn1d == MN_TDN_EXTERN) && (MP(MpTdn) != MN_TDN_EXTERN); // When changing from extern to another mode, iExt2Auto=1
	gbMnTdn1d = MP(MpTdn);
 
	if(MP(MpTdn) == MN_TDN_EXTERN) {
		if(((!gbLedSel)&&(gnTdnChkOut == TDN_DAY))||((gbLedSel)&&!gbTdnExtflag)) {		    
			if(gnAeLed) LibLED_SET_DIMM(0,1,2);
			goto AeLedCtrl_End;	//  don't LED_ON(101,...)
		}
		else {		    
			if((iAgcPos < iAE_LED_AGC && gnAeLed == gnLED_OFSMIN)||(iAgcPos > iAE_LED_AGC && gnAeLed == gnLED_OFSMAX))
			{
				goto AeLedCtrl_End;
			}
			else {
//				afAePosflt = (float)(aiOfs + iAE_LED_AGC);  // don't know ae position, Calculate on position, iAE_LED_AGC=((int)(iAE_AGC_LED_ON - iAE_AGC_LED_GAB))
				afAePos = aiOfs + iAE_LED_AGC;  // don't know ae position, Calculate on position, iAE_LED_AGC=((int)(iAE_AGC_LED_ON - iAE_AGC_LED_GAB))				
			}

            if(iErrOn) goto CtrlLED;
		}
	}	
#else
	#define iExt2Auto	0
#endif

    	//----------------------------------------------------------------------------------------
    	const int iDnDelay = gnGetTdnDly;
//    	if(!((((gbLedSel)&&(MP(MpTdn)==MN_TDN_DAY))||(MP(MpTdn)==MN_TDN_NIGHT))&&(MP(MpAdaptive)==1))){  // In AL and B&W mode, LED doesn't turn off and LED is fixed to minimum value
        	if((iAgcPos <= iAE_AGC_LED_OFF) && (gnAeLed <= gnLED_OFSMIN) && (gnAeLed > 0)&& (iAeLedOff || iExt2Auto))
        	{        	
        		if(gnAeOnCnt) {
        			if(iAgcPos > AE_AGC_LED_OFF_MIN)	goto AeLedCtrl_End;
//        			else								return fAePosfltHold;  
                    else                                return ifmul8(iAePosHold);;  
        		}
               
                if(giDimDelay == 0){
                    giDimDelay = iDnDelay; 
                
        			if(gbAGC_DLY > gbLED_DLY) {    			      
        				gbLED_CHG_CNT = gbAGC_DLY - gbLED_DLY;
        			}
        			else {    			    
        				LibLED_SET_DIMM(0,1,3);//LED_OFF(3);
        			}

        			if(gbAGC_DLY < gbLED_DLY) {
        				gbLED_CHG_CNT = 20 + gbLED_DLY - gbAGC_DLY;
        			}
        			else {
//        				if(iAgcPos > 0) afAePosflt += (float)iAE_AGC_LED_GAB;   // when LED OFF, Increase by GAB only in AGC mode afAePosflt = afAePosflt+(float)iAE_AGC_LED_GAB
        				if(iAgcPos > 0) afAePos += iAE_AGC_LED_GAB;   // when LED OFF, Increase by GAB only in AGC mode afAePosflt = afAePosflt+(float)iAE_AGC_LED_GAB        				
        			}    		     
        		}
        		goto AeLedCtrl_End;
        	}
//        }
        
    	if(iErrOn == 0) goto AeLedCtrl_End;
    	
    	//----------------------------------------------------------------------------------------
    	// AGC fix, LED control 
    	if( (iAgcPos > iAE_AGC_LED_ON && gnAeLed < gnLED_OFSMAX) ||(iAgcPos > iAE_LED_AGC && gnAeLed == gnLED_OFSMIN) ||	
            (iAgcPos < iAE_LED_AGC && gnAeLed == gnLED_OFSMAX) || (gnAeLed > gnLED_OFSMIN && gnAeLed < gnLED_OFSMAX))
    	{
    		if(gnAeLed == 0)
    		{
    			if(giDimDelay > 0)	{ // LED on / off to TDN delay

//    				fAePosfltHold = (float)(aiOfs + iAE_AGC_LED_ON + 1);	// LED ON Holding   
//    				return fAePosfltHold;
                    iAePosHold = (aiOfs + iAE_AGC_LED_ON + 1);    // LED ON Holding   
                    return ifmul8(iAePosHold);
    			}
    			else giDimDelay = iDnDelay;
    		}
 
//    		if(gnAeLed) afAePosflt = (float)(aiOfs + iAE_LED_AGC); // AfAePosflt when LED is OFF is processed by LED_ON (101, gnLED_OFSMIN)
    		if(gnAeLed) afAePos = aiOfs + iAE_LED_AGC; // AfAePosflt when LED is OFF is processed by LED_ON (101, gnLED_OFSMIN)    		
    	}
    	else {
    		goto AeLedCtrl_End;    		
    	}
        
    	//----------------------------------------------------------------------------------------
#if ENABLE_EXTERN_MODE == 1
CtrlLED :
#endif    
 {   
	//----------------------------------------------------------------------------------------
	
	const UINT nTotalClkOfIRIS0 = gnTotalClkOfIRIS + gnLED_OFS;
	const UINT nTotalClkOfIRIS  = (nTotalClkOfIRIS0 > gnLED_OFSMIN) ? nTotalClkOfIRIS0 - gnLED_OFSMIN : 0 ;

	int iErrStepMax = (int)nTotalClkOfIRIS / ErrStepMax_RATE;
	if(iErrStepMax < ErrStepMax_MIN) iErrStepMax = ErrStepMax_MIN;

	int iErrStepMin = (int)nTotalClkOfIRIS / ErrStepMin_RATE;
	if(iErrStepMin < ErrStepMin_MIN) iErrStepMin = ErrStepMin_MIN;

    const int iErrStepMax_Err = (nTotalClkOfIRIS > AE_LED_OFS_END) ? ErrStepMax_Err_End :
								(nTotalClkOfIRIS < gnLED_OFS) ? ErrStepMax_Err_Sta :
								LibUtlInterp1D(nTotalClkOfIRIS, gnLED_OFS, AE_LED_OFS_END, ErrStepMax_Err_Sta, ErrStepMax_Err_End) ;

	int iErrNow_Step = iErrStepMin + ((ABS(aiErrNow) * (iErrStepMax - iErrStepMin)) / iErrStepMax_Err);
	if(iErrNow_Step > iErrStepMax) iErrNow_Step = iErrStepMax;
    
    if(AE_LEDClip>AE_LEDClip_Lv){   // 181128 JJH
        if(iErrNow_Step < (int)AE_LEDClip_Step ) iErrNow_Step = AE_LEDClip_Step;
    }
    
	if(aiErrNow < 0) iErrNow_Step = -iErrNow_Step;
     
	//----------------------------------------------------------------------------------------
	if(gnAeLed == 0) {
		if(gbAGC_DLY > gbLED_DLY) {
			gbLED_CHG_CNT = 10 + gbAGC_DLY - gbLED_DLY;
		}
		else {
//			LibLED_SET_DIMM(gnLED_OFSMIN,1,101);//LED_ON(101,gnLED_OFSMIN);
			LibLED_SET_DIMM(giAE_LEDStart,1,101);//LED_ON(101,gnLED_OFSMIN);	// 190610 JJH : LED start position 		
		}

		if(gbAGC_DLY < gbLED_DLY) {
			gbLED_CHG_CNT = 30 + gbLED_DLY - gbAGC_DLY;
		}
		else {
//			afAePosflt = (float)(aiOfs + iAE_LED_AGC);
			afAePos = aiOfs + iAE_LED_AGC;
		}
		goto AeLedCtrl_End;
	}

	//----------------------------------------------------------------------------------------
	// Ctrl 'gnTotalClkOfIRIS'
	if(gbLedDlyCnt) {
		gbLedDlyCnt--;
	}
	else {
		if((int)gnTotalClkOfIRIS + iErrNow_Step < (int)gnLED_OFSMIN) {
			gnTotalClkOfIRIS = gnLED_OFSMIN;
		}
		else {
			gnTotalClkOfIRIS = (int)gnTotalClkOfIRIS + iErrNow_Step;
		}

		if(gnTotalClkOfIRIS > gnLED_OFSMAX) gnTotalClkOfIRIS = gnLED_OFSMAX;

		gbLedDlyCnt = gbLED_DLY;
	}
	
	//----------------------------------------------------------------------------------------
	// Ctrl IR_PWM
	LibAe_IR_PWM_Ctrl();
	//----------------------------------------------------------------------------------------
AeLedCtrl_End :
    
//	fAePosfltHold = afAePosflt;
//  return afAePosflt;
	iAePosHold = afAePos;
	return ifmul8(afAePos);
 }
}


