/* **************************************************************************
 File Name	:	lib_app_maf.c
 Description:	EN772 - Motorized Auto Focus function
 Designer	:	Danny, Lee
 Date		:	17. 12. 14
 Copyright ⓒ Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "../Src/dev.h"

//=================================================================================================
//	AF Data Filter / Position Buffering
//=================================================================================================
#define MAF_BufClear(A,B)		{ int DataBuf_i; for(DataBuf_i=0; DataBuf_i<A; DataBuf_i++) B[DataBuf_i] = 0; }
#define MAF_DataBuf(A,B,C)		{ int DataBuf_i; for(DataBuf_i=(A-1); DataBuf_i>0; DataBuf_i--) B[DataBuf_i] = B[DataBuf_i-1]; B[0] = C; }

extern BYTE gbMAF_FrDly;
#define MAF_Frame_Delay gbMAF_FrDly // 180427 JJH frame delay

UINT gnAF1_Normalization=0, gnAF2_Normalization=0;
UINT gnAF1_Normalization_M=0, gnAF2_Normalization_M=0;
UINT gnAF1_Normalization_S=0, gnAF2_Normalization_S=0;

void MAF_DataNormalization(void);

int Lib_AFTAB1_DT(int *apiDT_Buf);
int Lib_AFTAB1_DE(int *apiDE_Buf);
int Lib_AFTAB2_DT(int *apiDT_Buf);
int Lib_AFTAB2_DE(int *apiDE_Buf);

void MAF_Data_Filtering(void);	
void MAF_Buffer_Clear(void);
void MAF_Data_n_Pos_Buffering(void);		
void MAF_PreProcessing(void);


int giMAF1_DirCnt=0, giMAF2_DirCnt=0, giMAF1_DirCntBuf[15], giMAF2_DirCntBuf[15];
int giMAF_TAB1DT=0, giMAF_TAB1DE=0, giMAF_TAB2DT=0, giMAF_TAB2DE=0;
BYTE gbDirState=0, gbMaf_Flag=1;

//=================================================================================================
//	Auto Focus (Library)
//=================================================================================================
BYTE MAF_DirScanning(void);
BYTE MAF_OverCorrection(void);
void MAF_OneTimeAF(void);

void MAF_EnvironmentSet_Lib(void);
void MAF_DataBuffering(void);

BYTE gbMAF_OneTimeState=0;
BYTE gbAutoFocus_Flag=0;

UINT gnMAF1_Data[15], gnMAF2_Data[15], gnMAF_Position_F[15];
	
volatile UINT *gnMaf_LibCurPos_F;  // Maf_Fmotor.nCurPos
volatile UINT *gnMaf_LibTgtPos_F;  // Maf_Fmotor.nTgtPos
volatile BYTE *gbMaf_LibTgtCtr_Go; // Maf_Fmotor.bPosGo

extern volatile int giMaf_CurGain, giMaf_GainRange[2], giMaf_DAvg_Ofs[2];
extern volatile int giMaf_DirNo_P[2], giMaf_DirNo_M[2], giMaf_AF_TryMax;
extern volatile UINT gnMaf_FPosRange[2], gnMAF_YnmlAlpha[2];
extern volatile UINT gnMaf_AF_DATA[2], gnMaf_Y_DATA[2], gnMaf_Y_SCALE[2], gnMaf_TgtPeakMgn;
extern volatile UINT gnMaf_AF_DATA_M[2], gnMaf_Y_DATA_M[2],gnMaf_AF_DATA_S[2], gnMaf_Y_DATA_S[2];

//=================================================================================================
//	Init AF Register Set (LIB)
//=================================================================================================
void MAF_EnvironmentSet_Lib(void)
{
//	ISP AF ODM Environment Setting
    AF_CHSELw(0);
	AF_YLPFw(0);
	// AF_BITSELw(0);

	AF_PDw(0);	
	AF_CLIPw(0x3c0);
	AF_SLICEw(0);
	AF_CLIP_ONw(0);

	AF1_HTABw(2);
	AF2_HTABw(5);
	AF_WIN_SELw(3);
	AF_LOCK_SELw(0);	
}

void MAF_DataBuffering(void)
{
    gnMaf_AF_DATA[0]=AF1_SUM1_LOCKr; // 64Tabs
//  gnMaf_AF_DATA[1]=AF2_SUM1_LOCKr; // 16Tabs
	gnMaf_Y_DATA[0]=AF1_YSUM1_LOCKr;
//	gnMaf_Y_DATA[1]=AF2_YSUM1_LOCKr;

	giMaf_CurGain=giCurAgc;
}

//=================================================================================================
//	AF Data Filter / Position, Data Buffering (LIB)
//=================================================================================================

void MAF_DataNormalization(void)
{
	UINT nAlpha = LibUtlInterp1D (giMaf_CurGain, giMaf_GainRange[0], giMaf_GainRange[1], gnMAF_YnmlAlpha[0], gnMAF_YnmlAlpha[1]);

	gnAF1_Normalization = (gnMaf_AF_DATA[0]/(gnMaf_Y_DATA[0]>>gnMaf_Y_SCALE[0]))*nAlpha;
	gnAF2_Normalization = (gnMaf_AF_DATA[1]/(gnMaf_Y_DATA[1]>>gnMaf_Y_SCALE[1]))*nAlpha;
}

int Lib_AFTAB1_DT(int *apiDT_Buf)
{
	int iBuf = (apiDT_Buf[0]-apiDT_Buf[3])+(apiDT_Buf[1]-apiDT_Buf[3])+(apiDT_Buf[2]-apiDT_Buf[3])
		      +(apiDT_Buf[3]-apiDT_Buf[4])+(apiDT_Buf[3]-apiDT_Buf[5])+(apiDT_Buf[3]-apiDT_Buf[6]);

	return iBuf;
}

int Lib_AFTAB1_DE(int *apiDE_Buf)
{
	int iBuf = ABS(apiDE_Buf[6]-apiDE_Buf[5])+ABS(apiDE_Buf[5]-apiDE_Buf[4])+ABS(apiDE_Buf[4]-apiDE_Buf[3])
		      +ABS(apiDE_Buf[3]-apiDE_Buf[2])+ABS(apiDE_Buf[2]-apiDE_Buf[1])+ABS(apiDE_Buf[1]-apiDE_Buf[0]);

	return (iBuf+(iBuf>>1)+giMaf_DAvg_Ofs[0]);
}

int Lib_AFTAB2_DT(int *apiDT_Buf)
{
	int iBuf = (apiDT_Buf[0]-apiDT_Buf[2])+(apiDT_Buf[0]-apiDT_Buf[4])+(apiDT_Buf[0]-apiDT_Buf[6]);

	return iBuf;
}

int Lib_AFTAB2_DE(int *apiDE_Buf)
{
	int iBuf = ABS(apiDE_Buf[0]-apiDE_Buf[2])+ABS(apiDE_Buf[2]-apiDE_Buf[4])+ABS(apiDE_Buf[4]-apiDE_Buf[6]);

	return (iBuf+(iBuf>>1)+giMaf_DAvg_Ofs[1]);
}

void MAF_Data_Filtering(void)
{
	// AF Data Tab1,2 Differencial Total & Each Increment
	giMAF_TAB1DT = Lib_AFTAB1_DT((int *)gnMAF1_Data); // Long(64) Tab
	giMAF_TAB1DE = Lib_AFTAB1_DE((int *)gnMAF1_Data);
	
	giMAF_TAB2DT = Lib_AFTAB2_DT((int *)gnMAF2_Data); // Short(16) Tab
	giMAF_TAB2DE = Lib_AFTAB2_DE((int *)gnMAF2_Data);

	// AF Tab1 Dir-Counter
	if(ABS(giMAF_TAB1DT)>giMAF_TAB1DE) // Response
	{
		if(giMAF_TAB1DT>0) { // + Direction
			giMAF1_DirCnt = (giMAF1_DirCnt>=giMaf_DirNo_P[0]) ? giMaf_DirNo_P[0] : giMAF1_DirCnt+1;
		}
		else {				  // - Direction
			giMAF1_DirCnt = (giMAF1_DirCnt<=giMaf_DirNo_M[0]) ? giMaf_DirNo_M[0] :
			                (giMAF1_DirCnt>               0 ) ?                0 : giMAF1_DirCnt-1;
		}
	}
	else giMAF1_DirCnt=0; // No Response

	// AF Tab2 Dir-Counter
	if(ABS(giMAF_TAB2DT)>giMAF_TAB2DE) // Response
	{
		if(giMAF_TAB2DT>0) { // + Direction
			giMAF2_DirCnt = (giMAF2_DirCnt>=giMaf_DirNo_P[1]) ? giMaf_DirNo_P[1] : giMAF2_DirCnt+1;
		}
		else {				  // - Direction
			giMAF2_DirCnt = (giMAF2_DirCnt<=giMaf_DirNo_M[1]) ? giMaf_DirNo_M[1] :
			                (giMAF2_DirCnt>               0 ) ?                0 : giMAF2_DirCnt-1;
		}
	}
	else giMAF2_DirCnt=0; // No Response
}
		
void MAF_Buffer_Clear(void)
{
	MAF_BufClear(15, giMAF1_DirCntBuf)
	MAF_BufClear(15, giMAF2_DirCntBuf)
	MAF_BufClear(15, gnMAF1_Data)
	MAF_BufClear(15, gnMAF2_Data)
}
		
void MAF_Data_n_Pos_Buffering(void)
{
	MAF_DataBuf(15, gnMAF_Position_F, *gnMaf_LibCurPos_F)
	MAF_DataBuf(15, giMAF1_DirCntBuf, giMAF1_DirCnt)
	MAF_DataBuf(15, giMAF2_DirCntBuf, giMAF2_DirCnt)
	MAF_DataBuf(15, gnMAF1_Data, gnAF1_Normalization)
	MAF_DataBuf(15, gnMAF2_Data, gnAF2_Normalization)
}
		
void MAF_PreProcessing(void)
{	
//    if(gbMaf_Flag){
        MAF_DataNormalization();

        MAF_Data_n_Pos_Buffering();

        MAF_Data_Filtering();
//	}
}

//=================================================================================================
//	Auto Focus (LIB)
//=================================================================================================
BYTE gbDirStateBuf=0;
UINT gnMaf_TgtPosition_F=0, gnMaf_TgtPeakVal_F=0;
BYTE MAF_DirScanning(void)
{
	BYTE ReturnVal=0;
	
	*gnMaf_LibTgtPos_F = (gbDirState==0) ? gnMaf_FPosRange[0] : gnMaf_FPosRange[1];
	*gbMaf_LibTgtCtr_Go = 1;
	
	if((giMAF1_DirCntBuf[giMaf_DirNo_P[0]]==giMaf_DirNo_P[0])&&(giMAF1_DirCntBuf[1]==giMaf_DirNo_P[0])&&(giMAF1_DirCntBuf[0]==0)) {	// Mountain Over Correction
//		*gnMaf_LibTgtPos_F = gnMAF_Position_F[giMaf_DirNo_P[0]+2];
		*gnMaf_LibTgtPos_F = gnMAF_Position_F[giMaf_DirNo_P[0]+2+MAF_Frame_Delay];		
		*gbMaf_LibTgtCtr_Go = 1;
		
//		gnMaf_TgtPosition_F[0] = gnMAF_Position_F[giMaf_DirNo_P[0]];
		gnMaf_TgtPosition_F = gnMAF_Position_F[giMaf_DirNo_P[0]+MAF_Frame_Delay];		// 673(ODM을 pre단에서 처리) 대비 frc 때문에 1frame delay - 771(ODM을 post단에서 처리) 
		gnMaf_TgtPeakVal_F = gnMAF1_Data[giMaf_DirNo_P[0]-1];
		ReturnVal = 1;
	}
	else if((giMAF1_DirCntBuf[0]==giMaf_DirNo_M[0])&&(giMAF1_DirCntBuf[giMaf_DirNo_P[0]]==giMaf_DirNo_M[0])) { // Continuously Decrease AF Data
		gbDirState = (gbDirState==0) ? 1 : 0; // Direction Change Condition
	}
	else { // Exception Processing #Limitation Area
		if     ((gbDirState==0)&&(*gnMaf_LibCurPos_F==gnMaf_FPosRange[0])) gbDirState=1;
		else if((gbDirState==1)&&(*gnMaf_LibCurPos_F==gnMaf_FPosRange[1])) gbDirState=0;
	}
	return ReturnVal;
}

BYTE MAF_OverCorrection(void)
{
	static BYTE bProc_Cnt=0, bRetry_Cnt=0;
	BYTE ReturnVal=0;

	if((bProc_Cnt==0)&&(*gbMaf_LibTgtCtr_Go==0)) { // Move to Focus Target Position
		*gnMaf_LibTgtPos_F = gnMaf_TgtPosition_F;
		*gbMaf_LibTgtCtr_Go = 1;
		bProc_Cnt++;
	}
	else if((bProc_Cnt<5)&&(*gbMaf_LibTgtCtr_Go==0)) {
		bProc_Cnt++;
	}
	else if (bProc_Cnt==5) {
		if(gnAF1_Normalization>(gnMaf_TgtPeakVal_F/100*gnMaf_TgtPeakMgn)) { // AF Finish Condition Check
			bProc_Cnt = bRetry_Cnt = 0;
			ReturnVal = 1;
		}
		else {
			if(bRetry_Cnt<giMaf_AF_TryMax) { // Retry Condition
				bRetry_Cnt++;
				bProc_Cnt = gbMAF_OneTimeState = 0;
			}
			else { // Forced finish condition
				bProc_Cnt = bRetry_Cnt = 0;
				ReturnVal = 1;
			}
		}
	}
	return ReturnVal;
}

extern UINT gnScanMargin;
extern BYTE gbOnePushAfSel;
BYTE gbScanSel=0;
void MAF_LocalScanning(void)
{ 
	static UINT nAF1_NormalizationDataBuf=0, nFocusPosDataBuf[8]={0,};
	static BYTE i,bMovingState=0;
	
	if(*gnMaf_LibTgtPos_F==*gnMaf_LibCurPos_F)
	{	
		bMovingState++;
		*gnMaf_LibTgtPos_F=(bMovingState==1) ?  *gnMaf_LibTgtPos_F+gnScanMargin : 
						   (bMovingState==2) ?  *gnMaf_LibTgtPos_F-2*gnScanMargin :
						   (bMovingState==3) ?   nFocusPosDataBuf[MAF_Frame_Delay]+gnScanMargin/2 :
						   (bMovingState==4) ?   nFocusPosDataBuf[MAF_Frame_Delay]-gnScanMargin/2 :
			               (bMovingState==5) ?   nFocusPosDataBuf[MAF_Frame_Delay]:
			                                      *gnMaf_LibTgtPos_F; 
		
		if(bMovingState==3) bMovingState+=(!gbScanSel);
		 // DispDat("bMovingState",10,10,bMovingState)	;      
		*gnMaf_LibTgtPos_F=	(*gnMaf_LibTgtPos_F<gnMaf_FPosRange[0]) ? gnMaf_FPosRange[0] :
					        (*gnMaf_LibTgtPos_F>gnMaf_FPosRange[1]) ? gnMaf_FPosRange[1] : *gnMaf_LibTgtPos_F ;                                
	}
	
	switch(bMovingState)
	{
		case 1: 
			nFocusPosDataBuf[2]=nFocusPosDataBuf[1];
			nFocusPosDataBuf[1]=nFocusPosDataBuf[0];
			nFocusPosDataBuf[0]=*gnMaf_LibCurPos_F; 
			break;
		case 2: 
		case 3: 
			if(nAF1_NormalizationDataBuf<gnAF1_Normalization)	
{
				for(i=7;i>0;i--)
				{
					nFocusPosDataBuf[i]=nFocusPosDataBuf[i-1];
				}
				
				nAF1_NormalizationDataBuf=gnAF1_Normalization;
				nFocusPosDataBuf[0]=*gnMaf_LibCurPos_F;
			}
			break;
		case 6: gbAutoFocus_Flag=*gbMaf_LibTgtCtr_Go=bMovingState=nAF1_NormalizationDataBuf=0;	
		default: break;		
	}

	*gbMaf_LibTgtCtr_Go =(*gnMaf_LibTgtPos_F!=*gnMaf_LibCurPos_F);	                	
}

void MAF_OneTimeAF(void)
{
	if(gbOnePushAfSel)	MAF_LocalScanning();
	else{
	switch(gbMAF_OneTimeState) {
		case 0 : { // Data & Dir-Counter Initialization
			MAF_Buffer_Clear();
			gbMAF_OneTimeState=1;
			break;
		}
		case 1 : { // Direction Searching / Mountain Climbing
			// Direction & Speed Set
			if(MAF_DirScanning()){
			    gbMAF_OneTimeState++;
//			    gbMaf_Flag = 0;
			}
			break;
		}
		case 2 : { // Move to Target #1
			if(*gbMaf_LibTgtCtr_Go==0) gbMAF_OneTimeState++;
			break;
		}
		case 3 : { // Over correction #1
			if(MAF_OverCorrection()){ 
			    gbMAF_OneTimeState++;
//			    gbMaf_Flag = 1;
			    
			}
			break;
		}
		case 4 : { // Move to Target #2
			if(*gbMaf_LibTgtCtr_Go==0) gbMAF_OneTimeState++;
			break;
		}
		default : { // OneTime AF Complete
			gbAutoFocus_Flag=gbMAF_OneTimeState=0;
			break;
		}
	}
	}
	if(gbDirStateBuf!=gbDirState) MAF_Buffer_Clear();	
	gbDirStateBuf = gbDirState;
}


/* EOF */
