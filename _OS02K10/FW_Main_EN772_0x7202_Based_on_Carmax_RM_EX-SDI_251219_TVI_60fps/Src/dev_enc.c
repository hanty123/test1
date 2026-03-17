/* **************************************************************************
 File Name	: 	dev_enc.c
 Description:	EN772 - for MODE_T,C,A
 Designer	:	Jo Hong Rae
 Date		:	20. 12. 15
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

#if(model_IspO_ANL)

#define REF_DVR		1
//---------------------------------------------------------------------------
//***************************************************************************
// 0. UTC
//***************************************************************************

//---------------------------------------------------------------------------
// Step 0. Define Variable
//---------------------------------------------------------------------------
BYTE gbCkeyDir = 0;

#if model_UccA == 1

BYTE gbRX0 = 0;
BYTE gbRX1 = 0;
BYTE gbRX2 = 0;
BYTE gbRX3 = 0;
BYTE gbRX4 = 0;
BYTE gbRX5 = 0;
BYTE gbRX6 = 0;
BYTE gbRX7 = 0;
BYTE gbUccKeyBuf=0;
UINT gnRxBuf[2] = { 0, 0 };
BYTE bUccIrqFlg=0;

//*************************************************************************************************
// EMT BlackBox
//-------------------------------------------------------------------------------------------------

volatile BYTE gbUpstreamFlag = MN_OFF;
BYTE gbSaveFlag = MN_OFF;
BYTE gbReadFlag = MN_OFF;

UINT gnAckData = 0;
UINT gnTimAckData = 0;

BYTE gbBright = 0x6; 			// (Step Range 0x0 ~ 0xc (0~12), F: Read)

#if(CAR_BB_FRONT)
BYTE gbMFcond = 0; 			// 
#else
BYTE gbMFcond = 1; 			// (0: Nor, 1: M(default), 2: F, 3: M+F, F: Read)			// Rear Camera
#endif

BYTE gbLEDMode = LED_ON; 		// (0: On(default), 1: Off, 2: Blink (1sec), F: Read)
BYTE gbReset = MN_OFF; 			// (0: None, 1: Reset)
//BYTE gbFR = FPS_275; 		// (0: 30p, 1: 29.1, 3: 27.5, F: Read)
BYTE gbFR = FPS_30; 		// (0: 30p, 1: 29.1, 3: 27.5, F: Read)
BYTE gbNV = 1; 				// (0: On, 1: Off(default), F: Read)
BYTE gbHDR = 0; 			// (0: On, 1: Off, F: Read)
//UINT gnFW_Info = 0; 		// (F: Read, RearCam->EMT_RX)

#if(CAR_BB_FRONT)
BYTE gbModel_Info = 1; 		// (F: Read, Cam->EMT_RX, 1: Front, 2: Rear, 3: Incam)
#else
BYTE gbModel_Info = 2; 		// (F: Read, Cam->EMT_RX, 1: Front, 2: Rear, 3: Incam)
#endif

BYTE gbAeSum = 0;			// (0: Send AE Sum (Continuous, Default), 1: Stop AE Sum, 2: Request AE Sum(Single))
BYTE gbAeSum_sht_light = 0;	// (0 : light source, 1 : shutter)
BYTE gbGPSctrl = _GPS_QZSS; // Reserved
BYTE gbModelName = 0; 		// (F: Read Model Name)
BYTE gbAllSave = 0; 		// (1: Save All, F: Read)

//---------------------------------------------------------------------------
// Option. Use DownStream (EMT OMEGA)
//---------------------------------------------------------------------------
void ISPM Send_CTX_Data(UINT *CTX_Data)
{
	// Disable CTX (After 1Frame, Down Stream Off)
//	POWER_OFF_CTX

	CTX00w(CTX_Data[0]);
	CTX01w(CTX_Data[1]);
	CTX02w(CTX_Data[2]);

//	TxStrNoIRQ("CTX_Data[0]", CTX_Data[0],8); // Debug Text
//	TxStrNoIRQ("CTX_Data[1]", CTX_Data[1],8); // Debug Text
//	TxStrNoIRQ("CTX_Data[2]", CTX_Data[2],8); // Debug Text
	
	// Enable CTX (Down Stream)
//	POWER_ON_CTX
}

void ISPM CTX_Processing(UINT *anVal, BYTE abMode) // 220718
{
	UINT i;
	bool bFlag = 0;
	BYTE bRst[32] = {0,}; // 3bit * 32 = 96bit
	UINT Ctx_Dat[3] = {0,}; // 32bit * 3 = 96bit
	UINT nBuf = 0;
	
	if(abMode == MN_HD_A) // MODE_A, CVBS (CTX Data BYTE to Binary)
	{
		nBuf = *anVal;
		
		for(i=0; i<32; i++){	// Data Setup
			bFlag = ((*anVal&0x1) ? 1 : 0);
			
			if(bFlag==0)	bRst[32-(i+1)] = 4; // 100
			else			bRst[32-(i+1)] = 6; // 110
			*anVal >>= 1;
		}
		
		for(i = 0; i<11; i++) // Ctx_Dat[0]
		{
			if(i == 10)	Ctx_Dat[0] |= ((bRst[i]&0x7)>>1);			
			else		Ctx_Dat[0] |= (bRst[i]&0x7)<<(32-((i+1)*3));			
		}
//		TxStrNoIRQ("Ctx_Dat[0] : 0x",Ctx_Dat[0],8);
		
		for(i = 10; i<22; i++) // Ctx_Dat[1]
		{
			if(i == 10)			Ctx_Dat[1] |= (bRst[i]&0x1)<<31;
			else if(i == 21)	Ctx_Dat[1] |= (bRst[i]&0x4)>>2;
			else				Ctx_Dat[1] |= (bRst[i]&0x7)<<(31-((i-10)*3));
		}
//		TxStrNoIRQ("Ctx_Dat[1] : 0x",Ctx_Dat[1],8);
		
		for(i = 21; i<32; i++)	// Ctx_Dat[2]
		{
			if(i == 21)		Ctx_Dat[2] |= (bRst[i]&0x3)<<30;
			else			Ctx_Dat[2] |= (bRst[i]&0x7)<<(30-((i-21)*3));
		}
//		TxStrNoIRQ("Ctx_Dat[2] : 0x",Ctx_Dat[2],8);

		// (32bit * 3) CTX Data = CRX Data
		TxStrNoIRQ("Down Stream : 0x",nBuf,8); // Debug Text
	}
	
	else if(abMode == MN_HD_T) // MODE_T (Added Start Bit per Every CTX Line)
	{		
		BYTE S_BIT = 0xff/*0x2*/, Header = 0xE2, Dir = 0xC0, CMD, Data1, Data2, Data3, Checksum = 0;
		UINT Temp_Data1 = 0, Temp_Data2 = 0, Temp_Data3 = 0;

		CMD = ((*anVal>>24)&0xff);   //
		Data1 = ((*anVal>>16)&0xff); // 
		Data2 = ((*anVal>>8)&0xff);  // 
		Data3 = ((*anVal>>0)&0xff);  //
		Checksum = (Header+Dir+CMD+Data1+Data2+Data3) & 0xff;

		if(CMD != 0x0)
		{
			// (32bit * 2) CTX Data = (0xE2,C0,CMD,Dat1,Dat2,Dat3,CSUM,DUMMY)
			// LINE Data : START HEADER DIR CMD DATA1 / START DATA2 DAT3 CHECKSUM 0x00
			Temp_Data1 = (S_BIT<<24) | (Header<<16) | (Dir<<8) | (CMD<<0); // CTX00
			Temp_Data2 = (Data1<<24) | (S_BIT<<16)	| (0x00<<8)| (Data2<<0); 
			Temp_Data3 = (Data3<<24) | (Checksum<<16); 

			Ctx_Dat[0] = Temp_Data1;
			Ctx_Dat[1] = Temp_Data2;
			Ctx_Dat[2] = Temp_Data3;
		}
	}
	
	Send_CTX_Data(Ctx_Dat);
	
}

void ISPM0 CTX_Initial(UINT *DSdata) // 220718
{
	// Down Stream To Coax (CTX Data Setup & Send)
	if(MP(MpAnlForm)==MN_HD_A) 		CTX_Processing(DSdata, MN_HD_A);
	else if(MP(MpAnlForm)==MN_HD_T)	CTX_Processing(DSdata, MN_HD_T);
}

//---------------------------------------------------------------------------
// Option. UTC 10 Byte
//---------------------------------------------------------------------------
#if _10Byte_UccOn
const UINT gnTblUcc10Byte[][2]= {
								 {0x2a     , 0x28      },
								 {0x120015 , 0x120015  },
								 {0x0      , 0x0       },
								 {0x1451ffd, 0x1451ffd },
								 {0x0      , 0x0       },
								 {0x28003f , 0x28003d  }
							};

BYTE gbRX8,gbRX9;
// 170615 HTY
void ISPM0 TviUcc10ByteReadDat(void)
{	
	gbRX0 = (GetIsp(0x909)>>8);
	gbRX1 = (GetIsp(0x909)>>0);
	gbRX2 = (GetIsp(0x90a)>>24);
	gbRX3 = (GetIsp(0x90a)>>16);
	gbRX4 = (GetIsp(0x90a)>>8);
	gbRX5 = (GetIsp(0x90a)>>0);
	gbRX6 = (GetIsp(0x90b)>>24);
	gbRX7 = (GetIsp(0x90b)>>16);
	gbRX8 = (GetIsp(0x90b)>>8);
	gbRX9 = (GetIsp(0x90b)>>0);
}

// 170615 HTY
void TviUcc10Byte(void)
{	
	BYTE i;
	BYTE bChngMode = 0;

	CRX_AUTO_CATw(gnTblUcc10Byte[0][bChngMode]);		
 	
 	for(i=0; i<5; i++)
 	{
 		SetIsp(0x0733+i, gnTblUcc10Byte[i+1][bChngMode]);
	}
	
	if((gbRX7==0x24)&&(gbRX8==0x2C))	{gbCKeyVal = KEY_VAL_U; } 
	if((gbRX7==0x24)&&(gbRX8==0x34))	{gbCKeyVal = KEY_VAL_D; } 
	if((gbRX6==0x24)&&(gbRX8==0x26))	{gbCKeyVal = KEY_VAL_R; } 
	if((gbRX6==0x24)&&(gbRX8==0x28))	{gbCKeyVal = KEY_VAL_L; } 
	if((gbRX3==0x02)&&(gbRX8==0x02))	{gbCKeyVal = KEY_VAL_C; } 
	gbCkeyDir=0;
}
#endif

//---------------------------------------------------------------------------
// Step 1. Get UTC Data
//---------------------------------------------------------------------------
void ISPM0 GetUccData(void)
{	
	#define GET_RX	\
	gbRX0 = (GetIsp(0x90a)>>24);\
	gbRX1 = (GetIsp(0x90a)>>16);\
	gbRX2 = (GetIsp(0x90a)>>8 );\
	gbRX3 = (GetIsp(0x90a)>>0 );\
	gbRX4 = (GetIsp(0x90b)>>24);\
	gbRX5 = (GetIsp(0x90b)>>16);\
	gbRX6 = (GetIsp(0x90b)>>8 );\
	gbRX7 = (GetIsp(0x90b)>>0 );
	
	#define GET_C_RX	\
	gbRX0 = (GetIsp(0x904)>>24);\
	gbRX1 = (GetIsp(0x905)>>24);\
	gbRX2 = (GetIsp(0x906)>>24);\
	gbRX3 = (GetIsp(0x907)>>24);\
	gbRX4 = (GetIsp(0x908)>>24);\
	gbRX5 = (GetIsp(0x909)>>24);\
	gbRX6 = (GetIsp(0x90a)>>24);\
	gbRX7 = (GetIsp(0x90b)>>24);
	
	/* 170731 HTY */ 
	
	 if(!MODE_CVBS_ON) 
	 {
		 switch(MP(MpAnlForm))
		 {	
		 	case MN_HD_T :
		 		#if _10Byte_UccOn	// 170523 HTY
		 			TviUcc10ByteReadDat(); break; // 170615 HTY
		 		#else
		 			GET_RX; break;
		 		#endif

		 	case MN_HD_C :  		// 171013 HTY
				if(MODE_4M_ON) { GET_RX } else { GET_C_RX }  break;
		 	case MN_HD_A : bUccIrqFlg=1;	GET_RX;  break;
			case MN_CVBS : GET_RX;  break;
		 	default :  break;
	    }
	}
	else  { bUccIrqFlg=1; GET_RX }
}


//---------------------------------------------------------------------------
// Step 2. Analysis UTC Data
//---------------------------------------------------------------------------
void CRX_GET(const BYTE abData)
{
	if(abData != 0xff) {
		/* Default Byte Ordering is MSB(Most Significant Byte) */
		gnRxBuf[0] = ((gnRxBuf[0]<<8)&0xFFFFFF00) | ((gnRxBuf[1]>>24)&0xFF);
		gnRxBuf[1] = ((gnRxBuf[1]<<8)&0xFFFFFF00) | (abData&0xFF);

		if(MP(MpAnlForm)==MN_HD_C) // MODE_C
		{
			#define RxBUF(N)	(*(((BYTE*)gnRxBuf)+N))
			if(RxBUF(1) == 0xA5)
			{
				if((RxBUF(2) == 0x80) && (RxBUF(3) == 0x91) && (RxBUF(5) == 0x00) && (RxBUF(6) == 0x00))
				{ //Ignore second frame
					if(RxBUF(4) == 0x10 /*&& RxBUF(7) == 0xEC*/) gbCKeyVal = KEY_VAL_C;
					if(RxBUF(4) == 0x80 /*&& RxBUF(7) == 0x0C*/) gbCKeyVal = KEY_VAL_C; // 170831 HTY	
					if(RxBUF(4) == 0x20 /*&& RxBUF(7) == 0xCC*/) gbCKeyVal = KEY_VAL_U;
					if(RxBUF(4) == 0xA0 /*&& RxBUF(7) == 0x2C*/) gbCKeyVal = KEY_VAL_D;
					if(RxBUF(4) == 0x60 /*&& RxBUF(7) == 0xAC*/) gbCKeyVal = KEY_VAL_L;
					if(RxBUF(4) == 0xE0 /*&& RxBUF(7) == 0x6C*/) gbCKeyVal = KEY_VAL_R;
				}
//				else if((RxBUF(2)==0x80)&&((RxBUF(3)==0x06)||(RxBUF(3)==0x0A))&&((RxBUF(7)==0x6F)||(RxBUF(7)==0x60))) {
				else if((RxBUF(2)==0x80)&&((RxBUF(3)==0x06)||(RxBUF(3)==0x0A)||(RxBUF(3) == 0x91)))
				{	//Ignore second frame  // 180904 HTY
					gbCKeyVal = KEY_VAL_C;
				}
				else if((RxBUF(2) == 0x80))
				{
					if((RxBUF(3) == 0x10) /*&& (RxBUF(7) == 0xB2)*/) gbCKeyVal = KEY_VAL_U;
					if((RxBUF(3) == 0x20) /*&& (RxBUF(7) == 0x92)*/) gbCKeyVal = KEY_VAL_D;
					if((RxBUF(3) == 0x40) /*&& (RxBUF(7) == 0xE2)*/) gbCKeyVal = KEY_VAL_L;
					if((RxBUF(3) == 0x80) /*&& (RxBUF(7) == 0x62)*/) gbCKeyVal = KEY_VAL_R;

					// 160304 HTY
					gbUccKeyBuf=1;
					if((RxBUF(3) == 0x42) /*&& (RxBUF(7) == 0x17)*/) gbMAF_Wide = gbUCCKeyOn=1;
					if((RxBUF(3) == 0x82) /*&& (RxBUF(7) == 0xE7)*/) gbMAF_Tele = gbUCCKeyOn=1;
					if((RxBUF(3) == 0x12) /*&& (RxBUF(7) == 0x7C)*/) gbMAF_Far  = gbUCCKeyOn=1;
					if((RxBUF(3) == 0x22) /*&& (RxBUF(7) == 0x5C)*/) gbMAF_Near = gbUCCKeyOn=1;
					if((RxBUF(3) == 0x02)||(RxBUF(3) == 0x00))        gbCKeyVal = KEY_VAL_S;
				}
			}
		}
		else if(MP(MpAnlForm)==MN_HD_T) // MODE_T
		{
			#if(0)
			const BYTE gbStart = (gnRxBuf[0]>>24);

			if(gbStart == 0xb5)
			{
				const BYTE gbAddr = gnRxBuf[0]>>16;
				const BYTE gbComm = gnRxBuf[0]>>8;
				const BYTE gbPar1 = gnRxBuf[0];
				const BYTE gbPar2 = gnRxBuf[1]>>24;
				const BYTE gbPar3 = gnRxBuf[1]>>16;
				const BYTE gbDat4 = gnRxBuf[1]>>8;
				const BYTE gbCRC  = gbStart + gbAddr + gbComm + gbPar1 + gbPar2 + gbPar3 + gbDat4;

				if(gbCRC == (gnRxBuf[1]&0xFF)) 
				{
					if(gbComm == 0x17 || gbComm == 0x15||gbComm == 0x0F) gbCKeyVal = KEY_VAL_C;    // 170303 HTY
					if(gbComm == 0x06) {gbCKeyVal = KEY_VAL_U;}
					if(gbComm == 0x07) {gbCKeyVal = KEY_VAL_D;}
					if(gbComm == 0x09) {gbCKeyVal = KEY_VAL_L;}
					if(gbComm == 0x08) {gbCKeyVal = KEY_VAL_R;}
					if(gbComm == 0x14) {gbCKeyVal = KEY_VAL_S; gbUCCKeyOn=0;} // 160304 HTY

					if(gbComm == 0x12) gbMAF_Wide=gbUCCKeyOn=1;	// 160304 HTY
					if(gbComm == 0x13) gbMAF_Tele=gbUCCKeyOn=1;
					if(gbComm == 0x10) gbMAF_Far =gbUCCKeyOn=1;
					if(gbComm == 0x11) gbMAF_Near=gbUCCKeyOn=1;					
				}
			}

			if(gbStart == 0xE2) // EMT_Header
			{
				const BYTE gbDir  		= gnRxBuf[0]>>16;
				const BYTE gbCMD  		= gnRxBuf[0]>>8 ;
				const BYTE gbPar1 		= gnRxBuf[0]>>0 ;
				const BYTE gbPar2 		= gnRxBuf[1]>>24;
				const BYTE gbPar3 		= gnRxBuf[1]>>16;
				const BYTE gbCheckSum 	= gnRxBuf[1]>>8 ;
				const BYTE gbCRC  		= (gbStart + gbDir + gbCMD + gbPar1 + gbPar2 + gbPar3);

				// CheckSum
				if(gbCheckSum == (gbCRC & 0xFF))
				{
					// EMT_RX -> Rear Cam
					if(gbDir == 0xD0)
					{
						gbUpstreamFlag = MN_ON;
						gnAckData = ((gbCMD<<24) | (gbPar1<<16) | (gbPar2<<8) | (gbPar3<<0));

						if(gbPar1==0xF)			{gbReadFlag = MN_ON;	return;}		// Read flag
						else if(gbPar1 > 0xF)	{gbReadFlag = MN_OFF;	return;}		// Read Exception
						
						if(gbPar2==0x1)			{gbSaveFlag = MN_ON;		   }		// Save flag
						else if(gbPar2 > 0x1)	{gbSaveFlag = MN_OFF;	return;}		// Save Exception
						
						switch(gbCMD)
						{						
							case _BRIGHTNESS 	:	gbBright = gbPar1;		break;	// Brightness			
							case _MIRROR_FLIP 	: 	gbMFcond = gbPar1;		break;	// Mir / Flip
							case _LED_CTRL 		: 	gbLEDMode = gbPar1;		break;	// LED Control
							case _FACTORY_RST 	: 	gbReset = gbPar1;		break;	// Factory Reset
							case _FRAME_RATE 	: 	gbFR = gbPar1;			break;	// Frame Rate
							case _STARVIS_FUNC 	: 	gbNV = gbPar1;			break;	// Starvis(Night Vision)								
							case _HDR_FUNC 		: 	gbHDR = gbPar1;			break;	// HDR								
							case _INFORMATION 	: 	/*gnFW_Info = gbPar1;*/	break;	// F/W Information, Read Only								
							case _MODEL_INFO 	: 	/*gbModel_Info = gbPar1;*/	break;	// Model Information, Read Only								
							case _AE_SUM 		: 	gbAeSum = gbPar1;		
													gbAeSum_sht_light = gbPar2;	break;	// AE Sum (Rear Cam -> EMT_RX)								
							case _GPS_CTRL 		: 	gbGPSctrl = gbPar1;		break;	// GPS Control (Reserved)
						#if(0)
							case _MODEL_NAME : // Model Name, Read Only
								// ZDR-017 Rear Cam -> 17R (0x31, 0x37, 0x52)
								gbReadReq[Model_Name] = 1;
								gbModelName = gbPar1;
								break;
						#endif
						
							case _ALL_SAVE 		: 	gbAllSave = gbPar1;		break;	// All Save or Get Information
							default				:							break;
						};
					}
				}
			}
			#endif
		}
	}
}

BYTE gbStart = 0;
BYTE gbDir = 0;
BYTE gbCMD = 0;
BYTE gbPar1 = 0;
BYTE gbPar2 = 0;
BYTE gbPar3 = 0;
BYTE gbCheckSum = 0;
BYTE gbCRC = 0;

void EMT_Protocol(void)
{
	gbStart = ((gnRxBuf[0]>>24)&0xFF);

	if(gbStart == 0xE2) // EMT_Header
	{
		gbDir  		= ((gnRxBuf[0]>>16)&0xFF);
		gbCMD  		= ((gnRxBuf[0]>>8)&0xFF) ;
		gbPar1 		= ((gnRxBuf[0]>>0)&0xFF) ;
		gbPar2 		= ((gnRxBuf[1]>>24)&0xFF);
		gbPar3 		= ((gnRxBuf[1]>>16)&0xFF);
		gbCheckSum 	= ((gnRxBuf[1]>>8)&0xFF) ;
		gbCRC  		= (gbStart + gbDir + gbCMD + gbPar1 + gbPar2 + gbPar3);

		if((gbDir != 0xD0)||(gbCMD != _INFORMATION)||(gbPar1 != 0x0F)||(gbPar2 != 0x00)||(gbPar3 != 0x00)||(gbCheckSum != 0xD8)){
			DispDat("ERROR !!!!!", 19, 24, (gbCMD<<16 | gbPar1));
		}

		// CheckSum
		if(gbCheckSum == (gbCRC & 0xFF))
		{
			// EMT_RX -> Rear Cam
			if(gbDir == 0xD0)
			{
				gbUpstreamFlag = MN_ON;
				gnAckData = ((gbCMD<<24) | (gbPar1<<16) | (gbPar2<<8) | (gbPar3<<0));

				if(gbPar1==0xF)			{gbReadFlag = MN_ON;	return;}		// Read flag
				else if(gbPar1 > 0xF)	{gbReadFlag = MN_OFF;	return;}		// Read Exception
				
				if(gbPar2==0x1)			{gbSaveFlag = MN_ON;		   }		// Save flag
				else if(gbPar2 > 0x1)	{gbSaveFlag = MN_OFF;	return;}		// Save Exception
				
				switch(gbCMD)
				{						
					case _BRIGHTNESS 	:	gbBright = gbPar1;		break;	// Brightness			
					case _MIRROR_FLIP 	: 	gbMFcond = gbPar1;		break;	// Mir / Flip
					case _LED_CTRL 		: 	gbLEDMode = gbPar1;		break;	// LED Control
					case _FACTORY_RST 	: 	gbReset = gbPar1;		break;	// Factory Reset
					case _FRAME_RATE 	: 	gbFR = gbPar1;			break;	// Frame Rate
					case _STARVIS_FUNC 	: 	gbNV = gbPar1;			break;	// Starvis(Night Vision)								
					case _HDR_FUNC 		: 	gbHDR = gbPar1;			break;	// HDR								
					case _INFORMATION 	: 	/*gnFW_Info = gbPar1;*/	break;	// F/W Information, Read Only								
					case _MODEL_INFO 	: 	/*gbModel_Info = gbPar1;*/	break;	// Model Information, Read Only								
					case _AE_SUM 		: 	gbAeSum = gbPar1;		
											gbAeSum_sht_light = gbPar2;	break;	// AE Sum (Rear Cam -> EMT_RX)								
					case _GPS_CTRL 		: 	gbGPSctrl = gbPar1;		break;	// GPS Control (Reserved)
				#if(0)
					case _MODEL_NAME : // Model Name, Read Only
						// ZDR-017 Rear Cam -> 17R (0x31, 0x37, 0x52)
						gbReadReq[Model_Name] = 1;
						gbModelName = gbPar1;
						break;
				#endif
				
					case _ALL_SAVE 		: 	gbAllSave = gbPar1;		break;	// All Save or Get Information
					default				:							break;
				};
			}
		}
	}
}


void UccA(void)		
{	
	gbCKeyVal = 0;  // 170615 HTY

#if _10Byte_UccOn      // 170615 HTY
	if(MP(MpAnlForm)==MN_HD_T)	TviUcc10Byte(); 
#endif

	// Rx Data Get
	if(MP(MpAnlForm)==MN_HD_T){
		CRX_GET(gbRX0);
		CRX_GET(gbRX1);
	}
	else if(MP(MpAnlForm)==MN_HD_C)	CRX_GET(gbRX1);
	
	CRX_GET(gbRX2);
	CRX_GET(gbRX3);
	CRX_GET(gbRX4);
	CRX_GET(gbRX5);
	CRX_GET(gbRX6);
	CRX_GET(gbRX7);

    //-------------------------------------------------------------------------	
	if(MP(MpAnlForm)==MN_HD_T)
	{
		#if(1)
		EMT_Protocol();
		#endif
	}	
//------------------------------------------------------------------------------------------------------------------------------------------------
// Debug ------------------------------------
#if 1
	#define DEBUGCNT_ADD	3
	#define DISP_LINE		20
	#define RX_VAL(N)		gbRX##N
	
	// 210115 JHR : UTC Debug Display
	if(gbMnDebugFnc==MN_DBG_6) {
		DispDat("UTC_HPF",12,24,UTC_HPFr);
		DispDat("UTC_SCHM",13,24,UTC_SCHMr);
		if((GetIsp(0x90c)&0x3ff)<0x200) DispDat("rAuto_Cat",14,24,GetIsp(0x90c)&0x3ff);
		DispDat("wAuto_Cat",15,24,CRX_AUTO_CATr);
		DispDat("rPRE_READ",16,24,GetIsp(0x90e)>>24);
		DispDat("rBRATE_NEW",17,24,GetIsp(0x90e)&0x3fff);
		DispDat("rBRATE_SEL",18,24,GetIsp(0x90f)&0x3fff);

		#define DISP_CRX(N)	\
				/*if(bRX##N!=0 && bRX##N!=0xFF)*/ {\
					static BYTE debugcnt=0;\
					SETFONTATTR(DISP_LINE+N, debugcnt, MN_WHITE);	SETFONTATTR(DISP_LINE+N, debugcnt+1, MN_WHITE);\
					debugcnt+=DEBUGCNT_ADD;\
					if(debugcnt >= (ISP_FONT_EAX-DEBUGCNT_ADD-2)) {\
						debugcnt = 0;\
						/*DispClr(32, 0, (ISP_FONT_EAX-DEBUGCNT_ADD-2));*/\
					}\
					DispHex(DISP_LINE+N, debugcnt, RX_VAL(N), 2);	SETFONTID(DISP_LINE+N, debugcnt+2, ' ');\
					SETFONTATTR(DISP_LINE+N, debugcnt, MN_YELLOW);	SETFONTATTR(DISP_LINE+N, debugcnt+1, MN_YELLOW);\
				}

			// 160324 HTY
		#define CRX_VALID(N)	(RX_VAL(N)!=0 && RX_VAL(N)!=0xFF)
			if(CRX_VALID(0)||CRX_VALID(1)||CRX_VALID(2)||CRX_VALID(3)||
			   CRX_VALID(4)||CRX_VALID(5)||CRX_VALID(6)||CRX_VALID(7)) // 160324 HTY
			{
				DISP_CRX(0);
				DISP_CRX(1);
				DISP_CRX(2);
				DISP_CRX(3);
				DISP_CRX(4);
				DISP_CRX(5);
				DISP_CRX(6);
				DISP_CRX(7);

				#define DispI2cX	(ISP_FONT_EAX-24-1)
				DispHex(30, DispI2cX   , gnRxBuf[0], 8);
				DispHex(30, DispI2cX+8 , gnRxBuf[1], 8);
			}
	}
#endif

	// Rx Data Initial
	gbRX0=0;
	gbRX1=0;
	gbRX2=0;
	gbRX3=0;
	gbRX4=0;
	gbRX5=0;
	gbRX6=0;
	gbRX7=0;
}
#endif

//***************************************************************************
// 1. ENCODER
//***************************************************************************
// CVBS ---------------------------------------------------------------------------
// HD Analog Common Set
const UINT gnTblIspDefault[][2] =  {
								{0x0015,	0x00000000}, // ECKO_PD[27],ECK_PD[26],ECK_SEL[25]
//								{0x0005,	0xe3120001}, // External comp.
								{0x0005,	0xc3228001}, // UTC_PO[31], UTC_BYP[30],UTC_REF_PO[29:28],UTC_V[27:24],UTC_HPF[22:20],UTC_SCHM[18:16],UTC_SCHM_SEL[15],UTC_PHYSEL[0]	// 231013 LGH : Internal comp.
//								{0x0005,	0xa3130001}, // UTC_PO[31], UTC_BYP[30],UTC_REF_PO[29:28],UTC_V[27:24],UTC_HPF[22:20],UTC_SCHM[18:16],UTC_SCHM_SEL[15],UTC_PHYSEL[0]	// 230427 lGH : Fixed Ref
								{0x0601,	0x00000000}, // ENC_ON[1],ENC_TSEL[0] 			ENC_OFF -> At ANALOG ON 
								{0x0606,	0xc0080000}, // ESYNC_MODE[31:30],ENC_TIMG_SEL[25:24],FLDE_INV[23],FLDE_INV2[22],FLDE_INV3[21],ESYNC_UP[20],ESYNC_AUTO[19]
								{0x060a,	0x00000000}, // HLOCKE_POS[31:16]
								{0x060b,	0x00000000}, // VLOCKE_EV_POS[27:16],VLOCKE_OD_POS[11:0]
								{0x0633,	0x00000000}, // EFLD_INV[29],ESYNC_POL[27]
								{0x0638,	0x00000100}, // Y_MGAIN[11:0]
								{0x0639,	0x01000100}, // CB_MGAIN[27:16],CR_MGAIN[11:0]
								
								// UTC OD Field / CTX
								{0x0652,    0x80001000}, // CRX_AUTO[31:30]
								{0x0653,	0x49060c00}, // CTX_EN[31],CRX_EN[30],CRX_DEGLCHTAB[28:24],CRX_DEGLCHTH1[20:16],CRX_DEGLCHTH2[14:10]
								{0x0655,	0x001d0020}, // CRX_VPOSODS[28:16],CRX_VPOSODE[12:0]
								{0x0657,	0x00000000}, // CRX_HPOSODS[29:16],CRX_HPOSODE[13:0]
								{0x0659,	0x000e0017}, // CTX_VPOSEVS[28:16],CTX_VPOSEVE[12:0]
								{0x065a,	0x000d0016}, // CTX_VPOSODS[28:16],CTX_VPOSODE[12:0]
								{0x065b,	0x017a0884}, // CTX_HPOSEVS[29:16],CTX_HPOSEVE[13:0]
								{0x065c,	0x017a0884}, // CTX_HPOSODS[29:16],CTX_HPOSODE[13:0]
								{0x065d,	0x00000000}, // CXAL_WOP[31]
								{0x0661,	0xc0000000}, // INT_EN[31],INT_VALID[30],CTX_CONTINUE[29],CTX_LSBKEEP[28],CRX_INT_NEW[27],INT_BITCNT_NUM[23:16],INT_HSP[12:0]
								
								// CTX 0~7 Data
								{0x0665,	0xffffffff},
								{0x0666,	0x00000000},
								{0x0667,	0xcccccccc},
								{0x0668,	0xdddddddd},
								{0x0669,	0xeeeeeeee},
								{0x066a,	0xaaaaaaaa},
								{0x066b,	0x00000000},
								{0x066c,	0xaaaaaaaa},

								{0x0678,	0x00000007}, // Y_DLY_ADJ[3:0]
								{0x068c,	0x000003f0}, // CTX_LVL[9:0]
								{0x0691,    0x00007003},
								{0x06aa,	0x00000000}  // AY_OSEL[30:28],AY_IORDER[27],YC_LEVEL_TEST[9:0]
								};	
// Default Table EA
const UINT gnTblIspDefaultEa = sizeof(gnTblIspDefault)/sizeof(gnTblIspDefault[0]);

//---------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ISP - CVBS
	// Base CVBS Setting
	const UINT gnTblCvbsPre[][3] = {
								//ADDR		//PAL			//NTSC
								// DAC or Pre PLL Setting 
								{0x0003, 	0xb000033f, 	0xb000033f},
								
								// Pre Sync Phase Setting
								{0x0050, 	0x00020001,		0x00020001},
								{0x0051, 	0x00020000,		0x00020000},
								{0x0052, 	0x00010001,		0x00010001}
								};

	const UINT gnTblCvbsPost[][3] = {
								//ADDR		//PAL			//NTSC
								{0x005f, 	0xc800035f,		0xc800035f}, 	// POST_INTR
								{0x0012, 	0x00000002,		0x00000002}, 	// PPCK
                                      	           		               
								{0x005a, 	0x18be0270,		0x1892020c}, 	// HTWO,VTWO
								{0x005d, 	0x00010006,		0x0001000d},    // HSPO,VSPO
								{0x005e, 	0x00000000,		0x00000000},	// HLOCKO_POS, VLOCKO_POS

								{0x0096, 	0x00000000,		0x00000000},	//
								{0x0099, 	0x80000008,		0x800000e6},	//
								{0x009a, 	0x80557300,		0x80558b00}, 	// 210408 JHR : CVBS Output Correction
								};
	
	const UINT gnTblCvbsEnc[][3] =  {
								//ADDR		//PAL			//NTSC
								{0x0004,	0x00000000,		0x00000000},
								{0x0015,    0x02000000,		0x02000000},
								{0x0601,    0x00000002,		0x00000002},

								{0x0606,    0x00080000,		0x00180000},
								{0x0607,    0x06be0270,		0x06b2020c},
								{0x0608,    0x00fa0013,		0x00fa000e},
								{0x0609,    0x06d00128,		0x05d000f8}, // 210408 JHR : CVBS Output Correction
								{0x060a,    0x00000000,		0x00000000},
								{0x060b,    0x00000000,		0x00000000},
								{0x0621,    0x00000000,		0x00000008},
								{0x0631,    0x035f0270,		0x0359020c},
								{0x0632,    0x00b40012,		0x00b40012},
								{0x0633,    0x08000000,		0x08000000},
								{0x0678,    0x00000009,		0x00000009},
								{0x0635,    0x035b002c,		0x03590028}, // 210408 JHR : CVBS Output Correction


								{0x0636,    0x00010001,		0x00000000},
								{0x063a,    0x00000005,		0x00000006},
								{0x063b,    0x000a000c,		0x000c000c},
								{0x063c,    0x002d026c,		0x00220207},
								{0x063d,    0x026a026c,		0x02070207},
								{0x063e,    0x00000000,		0x00000000},
								{0x0641,    0x00000005,		0x00000006},
								{0x0642,    0x000a000b,		0x000c000d},
								{0x0643,    0x002d026c,		0x00220207},
								{0x0644,    0x0269026c,		0x02070207},
								{0x0645,    0x00000000,		0x00000000},
								{0x0646,	0x00900000, 	0x0085000e}, // 210408 JHR : CVBS Output Correction
								{0x0647,    0x02e40003,		0x02df0024}, // 210408 JHR : CVBS Output Correction
								{0x0648,    0x00410001,		0x003e0019}, // 210408 JHR : CVBS Output Correction
								{0x0649,    0x00810000,		0x00810019}, // 210408 JHR : CVBS Output Correction
								{0x064a,    0x003800a4,		0x003a00b8}, // 210408 JHR : CVBS Output Correction
								{0x064b,    0x0598010d,		0x059b0113}, // 210408 JHR : CVBS Output Correction

								{0x064c,    0x00000000,		0x00000000},
								{0x0637,    0x00b800e0,		0x00b900d9},
								{0x0682,    0x00002010,		0x00001010}, // 210408 JHR : CVBS Output Correction
								{0x0691,    0x00007003,		0x000070c3},
								{0x06aa,    0x00000000,		0x00000000},
								{0x0651,    0x4000ff00,		0x4000ff00},
								{0x0652,    0x40001000,		0x40001000}, // 210413 JHR : CVBS UTC
								{0x0653,    0x49060c00,		0x49060c00},
								{0x068c,    0x000003f0,		0x000003f0},
								{0x0654,    0x001c001f,		0x001c001f},
								{0x0655,    0x001d0020,		0x001d0020},
//								{0x0656,    0x015a06c0,		0x015a06c0}, // 210413 JHR : CVBS UTC
//								{0x0657,    0x015a06c0,		0x015a06c0}, // 210413 JHR : CVBS UTC 
								{0x0656,	0x010006c0, 	0x010006c0}, // 210521 HTY : CVBS UTC
								{0x0657,	0x010006c0, 	0x010006c0}, // 210521 HTY : CVBS UTC
								{0x0658,    0x10000500,		0x10000500}, // 210413 JHR : CVBS UTC
								{0x0659,    0x000e0017,		0x000e0017},
								{0x065a,    0x000d0016,		0x000d0016},
								{0x065b,    0x017a0884,		0x017a0884},
								{0x065c,    0x017a0884,		0x017a0884},
								{0x065e,    0x08080073,		0x08080073},
								{0x0661,    0xc0080000,		0xc0080000},
								{0x0662,    0x02000200,		0x02000200},
								{0x0663,    0x02020202,		0x02020202}, // 210413 JHR : CVBS UTC (IRQ_END_POS)
								{0x0695,    0x00080000,		0x00080000},
								{0x0665,    0xffffffff,		0xffffffff},
								{0x0666,    0x00000000,		0x00000000},
								{0x0667,    0xcccccccc,		0xcccccccc},
								{0x0668,    0xdddddddd,		0xdddddddd},
								{0x0669,    0xeeeeeeee,		0xeeeeeeee},
								{0x066a,    0xaaaaaaaa,		0xaaaaaaaa},
								{0x066b,    0x00000000,		0x00000000},
								{0x066c,    0xaaaaaaaa,		0xaaaaaaaa},
								{0x065d,    0x00000000,		0x00000000}
								};

	// CVBS categorized by mode
	const UINT gnTblModeCvbs[][5] =  {		//2M 59.94						//1M 59.94
								//ADDR		//PAL			//NTSC			//PAL			//NTSC
								//Pre 			
								{0x002a,	0x00000001, 	0x00000001,		0x00010001,		0x00010001},	//RDES_SYNC2 
								{0x0026,	0x0000079c, 	0x0000079c,		0x00000510,		0x00000510},	//RDES_HW           			
//								{0x0054,	0x07900448, 	0x07900448,		0x051002d8,		0x051002d8},	//HWI, VWI
//								{0x0050,	0x001c000d, 	0x001c000d,		0x001c0007,		0x001c0007},	//VLOCKL_POS
								{0x0054,	0x07900448, 	0x07900546, 	0x051002d8, 	0x051002d8},	//HWI, VWI
//								{0x0050,	0x001c000d, 	0x001c0001, 	0x001c0007, 	0x001c0007},	//VLOCKL_P
								                                                                        	                			
								//Post                                                                  	                			
								{0x009c,	0x05b00130,		0x05b00100,		0x05b005b0,		0x05b005b0},	//DS_HW, DS_VW      			
//								{0x005b,	0x05b00130,		0x05b00100,		0x05b005b0,		0x05b005b0},	//HWO, VWO
								{0x005b,	0x06d00130,		0x06d00100,		0x05b005b0,		0x05b005b0},	//HWO, VWO // 210408 JHR : CVBS Output Correction
								{0x005c,	0x05b00000,		0x05b00000,		0x05b00000,		0x05b00000},	//FONT_HWO          			
								                                                                        	                  			
								//Enc                                                                   	                  			
//								{0x0602,	0x00001000,		0x00001000,		0x00001000,		0x00001000} 	//HSC_K             			
								};
								
	const UINT gnTblCvbsPreEa = sizeof(gnTblCvbsPre)/sizeof(gnTblCvbsPre[0]);
	const UINT gnTblCvbsPostEa = sizeof(gnTblCvbsPost)/sizeof(gnTblCvbsPost[0]);
	const UINT gnTblCvbsEncEa = sizeof(gnTblCvbsEnc)/sizeof(gnTblCvbsEnc[0]);
	const UINT gnTblModeCvbsEa = sizeof(gnTblModeCvbs)/sizeof(gnTblModeCvbs[0]);

//*********************************************************************************************************************************************************
// MODE_CVBS
//---------------------------------------------------------------------------------------------------------------------------------------------------------
	const UINT gnEncModeCVBS_LV0[][2] = 	{		//PAL			//NTSC
								
							   	/*UpENC_RYGAINP*/ 	{0x40,			0x40},
							   	/*UpENC_RYGAINN*/ 	{0x40,			0x40},
							   	/*UpENC_BYGAINP*/ 	{0x40,			0x40},
							   	/*UpENC_BYGAINN*/ 	{0x40,			0x40},
                                                            	        
							   	/*UpENC_RYHUEP*/	{0x00,			0x00},
						    	/*UpENC_RYHUEN*/	{0x00,			0x00},
							    /*UpENC_BYHUEP*/	{0x00,			0x00},
							    /*UpENC_BYHUEN*/	{0x00,			0x00},                    	        	        	        	        	        	    	        	        	        	        	        	

							    /*UpWHITE_LV*/		{0x39b,			0x39b},
								/*UpBLANK_LV*/		{0x114,			0x114},
							    /*UpPEDESTAL_LV*/ 	{0x0,			0x0  },

								/*UpFSC_TGT*/		{0x541353ba,	0x43e0f837},
								
								/*UpY_MGAIN*/	   	{0x100,			0x100},
							    /*UpCB_MGAIN*/		{0x118,			0x118},
							    /*UpCR_MGAIN*/		{0x118,			0x118},
							                                	        
							    /*UpCB_BST*/		{0x1ae,			0x190},
							    /*UpCR_BST*/		{0x250,			0x200},
							    
							    /*UpHSC_K*/			{0x1000,		0xFF0}, // 210408 JHR : CVBS Output Correction

							    /*UpHLOCK_CAT*/	{0x31,			0x2B  }, // 210408 JHR : CVBS Output Correction
							    /*UpVLOCK_CAT_EV*/	{0x1,			0x0   },
							    /*UpVLOCK_CAT_OD*/	{0x1,			0x0   },
							    
							    /*UpCRX_AUTO_CAT*/	{0x00,			0x00  }, // 210413 JHR : CVBS UTC 
//								/*UpCRX_HPOSEVS*/	{0x15a,			0x15a }, // 210413 JHR : CVBS UTC 
								/*UpCRX_HPOSEVS*/	{0x100, 		0x100 }, // 210521 HTY : CVBS UTC
								/*UpCRX_HPOSEVE*/	{0x6c0,			0x6c0 }, // 210413 JHR : CVBS UTC 
								/*UpCTX_BITRATE*/	{0x500,			0x500 }  // 210413 JHR : CVBS UTC 
											};


//*********************************************************************************************************************************************************
// MODE_T
//---------------------------------------------------------------------------------------------------------------------------------------------------------
	
	const UINT gnEncModeT_LV0[][ANA_MODE_NUM] = 	{
													//720P											//1080P											//1440P					//1944P
																															//(TBD)		//(TBD)														//(TBD)
								//Name				//25		//30		//50		//60		//25		//30		//50		//60		//25		//30		//12.5		//20		//25
							   	/*UpENC_RYGAINP*/ 	{0x37,		0x37,		0x3d,		0x3c,		0x45,		0x45,		0x47,		0x47,		0x2b,		0x2b,		0x3a,		0x31,		0x00},
							   	/*UpENC_RYGAINN*/ 	{0x32,		0x3d,		0x3a,		0x3a,		0x40,		0x40,		0x60,		0x60,		0x29,		0x29,		0x40,		0x40,		0x00},
							   	/*UpENC_BYGAINP*/ 	{0x26,		0x2c,		0x2a,		0x2a,		0x30,		0x30,		0x60,		0x60,		0x24,		0x24,		0x2c,		0x20,		0x00},
							   	/*UpENC_BYGAINN*/ 	{0x29,		0x27,		0x2a,		0x2a,		0x30,		0x30,		0x60,		0x60,		0x21,		0x21,		0x2a,		0x2a,		0x00},
                                                            	        	        	        	        	        	    	        	        	        	        	        	
							   	/*UpENC_RYHUEP*/	{0xf8,		0xf6,		0xfe,		0xfe,		0xf5,		0xf5,		0x15,		0x15,		0x02,		0x02,		0x0,		0xfa,		0x00},
						    	/*UpENC_RYHUEN*/	{0x00,		0x06,		0xf3,		0xf3,		0xff,		0xff,		0x1d,		0x1d,		0x03,		0x03,		0xf1,		0xf1,		0x00},
							    /*UpENC_BYHUEP*/	{0xfc,		0xfc,		0xeb,		0xeb,		0x05,		0x05,		0xed,		0xed,		0xf1,		0xf1,		0x8,		0xf6,		0x00},
							    /*UpENC_BYHUEN*/	{0x00,		0xfe,		0xf8,		0xf8,		0x06,		0x06,		0xe0,		0xe0,		0xf7,		0xf7,		0xff,		0xf1,		0x00},                      	        	        	        	        	        	    	        	        	        	        	        	

							    /*UpWHITE_LV*/		{0x008,		0x008,		0x3bf,		0x3bf,		0x3e5,		0x3e5,		0x3c0,		0x3c0,		0x3e6,		0x3e6,		0x3db,		0x3db,		0x00},
								/*UpBLANK_LV*/		{0x119,		0x119,		0xfe,		0xfe,		0x107,		0x107,		0x108,		0x108,		0x10a,		0x10a,		0x10a,		0x10a,		0x00},
							    /*UpPEDESTAL_LV*/ 	{0x0,		0x0,		0x0,		0x0,		0x0  ,		0x0  ,		0x00,		0x0,		0x0,		0x0,		0x0,		0x0,		0x00},

								/*UpFSC_TGT*/		{0x48bb4bfd,0x48bb48fd,	0x91768cfa,	0x917691fa,	0x9173f4f0,	0x917401f0,	0xb73ff9e6,	0xb73df9e6,	0xae83e652,	0xae827938,	0x9176f2fa,	0xaef9ef45,	0x00},
								
								/*UpY_MGAIN*/	   	{0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x00},
							    /*UpCB_MGAIN*/		{0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x00},
							    /*UpCR_MGAIN*/		{0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x00},
							                                	        	        	        	        	        	     	         	        	        	        	        	
							    /*UpCB_BST*/		{0x189,		0x189,		0x189,		0x189,		0x189,		0x189,		0x168,		0x168,		0x1a8,		0x1aa,		0x189,		0x1a5,		0x00},
							    /*UpCR_BST*/		{0x200,		0x200,		0x200,		0x200,		0x200,		0x200,		0x200,		0x200,		0x200,		0x200,		0x200,		0x200,		0x00},
							    
												#if(model_2M)
													// H + L DVR
							    /*UpHSC_K*/			{0x400,		0x400,		0x7fc,		0x7fc,		0x800,		0x800 ,		0xc99,		0xc99,		0xbf2,		0xbf8,		0x818,		0xc1e,		0x00},
							    /*UpHLOCK_CAT*/		{0xb1a,		0x886,		0x59e,		0x454,		0x8b7,		0x6ff ,		0x2,		0x2,		0x76e,		0x5b5,		0x933,		0x6bd,		0x00},
//							    /*UpVLOCK_CAT_EV*/	{0x5d5,		0x5d5,		0x5db,		0x5db,		0x8af,		0x8af ,		0x8ac,		0x8ac,		0xb8b,		0xb91,		0xf55,		0xf59,		0x00},
								/*UpVLOCK_CAT_EV*/	{0x5d5, 	0x5d5,		0x5db,		0x5db,		0x8af,		0x8af , 	0x8ac,		0x8ac,		0xb8b,		0xb91,		0xf61,		0xf53,		0x00},		// 210426 LGH : 5M Active optimization

												#else
							    /*UpHSC_K*/			{0x400,		0x400,		0x7fc,		0x7fc,		0x800,		0x800 ,		0xCF9,		0xCF9,		0xbf2,		0xbf8,		0x818,		0xc1e,		0x00},
							    /*UpHLOCK_CAT*/		{0xb1a,		0x886,		0x59e,		0x454,		0x8b7,		0x6ff ,		0x00,		0x00,		0x76e,		0x5b5,		0x933,		0x6bd,		0x00},
							    /*UpVLOCK_CAT_EV*/	{0x5cb,		0x5cb,		0x5db,		0x5db,		0x8a3,		0x8a3 ,		0x8ac,		0x8ac,		0xb83,		0xb83,		0xf55,		0xf59,		0x00},
												#endif
												
							    /*UpVLOCK_CAT_OD*/	{0x1,		0x1,		0x1,		0x1,		0x1,		0x1 ,		0x1,		0x1,		0x1,		0x1,		0x1,		0x1,		0x00},
							    /*UpCRX_AUTO_CAT*/	{0xcf,		0xcf,		0x6a,		0x6a,		0x68  ,		0x68  ,		0xcf,		0xcf,		0x8b,		0x7c,		0x68,		0x8b,		0x00},
								/*UpCRX_HPOSEVS*/	{0x2e3,		0x2e3,		0x194,		0x194,		0x194 ,		0x194 ,		0x194,		0x194,		0x210,		0x210,		0x196,		0x20c,		0x00},
								/*UpCRX_HPOSEVE*/	{0x3f00,	0x3f00,		0x3f00,		0x3f00,		0x3F00,		0x3F00,		0x3f00, 	0x3f00,		0x3f00,		0x3f00,		0x3f00,		0x3f00,		0x00},  
								/*UpCTX_BITRATE*/	{0x67d,		0x67d,		0x33d,		0x33d,		0x33d ,		0x33d ,		0x1800, 	0x1800,		0x455,		0x454,		0x33d,		0x455,		0x00}
							   						};


	const UINT gnEncModeT_LV1[][ANA_MODE_NUM+1] = 	{
																//720P											//1080P											//1440P					//1944P
																																																				//(TBD)
													//Addr		//25		//30		//50		//60		//25		//30		//50		//60		//25		//30		//12.5		//20		//25	
													{0x063c,	0x003205d2, 0x003205d2, 0x003005d4, 0x003005d4, 0x005208c2, 0x005208c2, 0x005208c2, 0x005208c2, 0x006e0bae, 0x006e0bae, 0x00680f98, 0x003e0f6e,	0x00000000},
													{0x0643,	0x003005d4, 0x003205d2, 0x003005d4, 0x003205d2, 0x003008c2, 0x003008c2, 0x003008c2, 0x003008c2, 0x00300bb0, 0x00300bb0, 0x00300f98, 0x00300f70,	0x00000000},
													{0x064b,	0x141b04a5, 0x143004aa, 0x0a100257, 0x0a100257, 0x0f0901d8, 0x0f0701d8, 0x0f05015A, 0x0f05015A, 0x0ee9019a, 0x0ee5019a, 0x14d901d8, 0x10ff019a,	0x00000000},
													{0x0609,	0x1ebe02e4, 0x19a002e4, 0x0f4602e4, 0x0cb202e4, 0x146d045b, 0x10fe045b, 0x0d15045c, 0x0abd045c, 0x146e05d2, 0x10fe05d2, 0x170207c6, 0x135607b2,	0x00000000},
													{0x0695,	0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x661f77f0, 0x661f77f0, 0x503d2061, 0x503d2061, 0x4ca8a03f, 0x4ca8a03f, 0x6654b63f, 0x4cb604d7,	0x00000000},
							   						};

	// LV2 Table Index +1												
	const UINT gnEncModeT_LV2[][ANA_MODE_NUM+1] = 	{
																//720P											//1080P 											//1440P						//1944P
																																		 																		//(TBD)
													//Addr		//25		//30		//50		//60		//25		//30		//50		//60		//25		//30		//12.5		//20		//25	
													{0x0003,	0xb000022b, 0xb000022b, 0xb000022b, 0xb000022b, 0xb000022b, 0xb000022b, 0xb0000237, 0xb0000237, 0xb0000357, 0xb0000357, 0xb000022b, 0xb0000357,	0x00000000},
													{0x0607,	0x1eef02ed, 0x19c702ed, 0x0f7702ed, 0x0ce302ed, 0x149f0464, 0x112f0464, 0x0d1f0464, 0x0aef0464, 0x149f05db, 0x112f05db, 0x173307cf, 0x138707bb,	0x00000000},
													{0x0608,	0x00010005, 0x00010005, 0x00010006, 0x00010006, 0x00040005, 0x00040005, 0x01260005, 0x01260005, 0x00010001, 0x00010001, 0x00010001, 0x00010009,	0x00000000},
													{0x0621,	0x0000000e, 0x0000000e, 0x0000000e, 0x0000000e, 0x0000000e, 0x0000000e, 0x0000000c, 0x0000000c, 0x0000000e, 0x0000000e, 0x0000000e, 0x0000000e,	0x00000000},
													{0x0631,	0x0f7705db, 0x0ce305db, 0x07bb05db, 0x067105db, 0x0a4e08c9, 0x089708c9, 0x057708c9, 0x057708c9, 0x0a4f0bb7, 0x08970bb7, 0x0b990f9f, 0x09c30f77,	0x00000000},
													{0x0632,	0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b,	0x00000000},
													{0x0637,	0x028004af, 0x028004af, 0x01400257, 0x01400257, 0x01e001d7, 0x01e001d7, 0x012f0143, 0x012f0143, 0x01b20300, 0x01b20300, 0x02800257, 0x01b0031f,	0x00000000},
													{0x065e,	0x08080073, 0x08080073, 0x08080073, 0x08080073, 0x08080073, 0x08080073, 0x08080073, 0x08080073, 0x08080073, 0x08080073, 0x08080073, 0x08080073,	0x00000000},
													{0x06ab,	0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000,	0x00000000},
													{0x063a,	0x0000000a, 0x0000000a, 0x0000000a, 0x0000000a, 0x0000000a, 0x0000000a, 0x00000009, 0x00000009, 0x0000000a, 0x0000000a, 0x0000000a, 0x0000000a,	0x00000000},
													{0x063b,	0x000a000c, 0x000a000c, 0x000a000c, 0x000a000c, 0x000a000a, 0x000a000a, 0x000a000a, 0x000a000a, 0x000a000a, 0x000a000a, 0x000a000a, 0x000a000a,	0x00000000},
													{0x063d,	0x05d605d6, 0x05d605d6, 0x05d605d6, 0x05d605d6, 0x08c908c4, 0x08c908c4, 0x08c908ca, 0x08c908ca, 0x0bb70bb2, 0x0bb70bb2, 0x0f9f0f9a, 0x0f770f72,	0x00000000},
													{0x063e,	0x05d805da, 0x05d805da, 0x05d805da, 0x05d805da, 0x08c608c8, 0x08c608c8, 0x08c608c8, 0x08c608c8, 0x0bb40bb6, 0x0bb40bb6, 0x0f9c0f9e, 0x0f740f76,	0x00000000},
													{0x0641,	0x0000000a, 0x0000000a, 0x0000000a, 0x0000000a, 0x0000000a, 0x0000000a, 0x0000000a, 0x0000000a, 0x0000000a, 0x0000000a, 0x0000000a, 0x0000000a,	0x00000000},
													{0x0642,	0x000a000c, 0x000a000c, 0x000a000c, 0x000a000c, 0x000a000c, 0x000a000c, 0x000a000a, 0x000a000a, 0x000a000c, 0x000a000c, 0x000a000c, 0x000a000c,	0x00000000},
													{0x0644,	0x05d605d6, 0x05d605d6, 0x05d605d6, 0x05d605d6, 0x08c408c4, 0x08c408c4, 0x08c408c4, 0x08c408c4, 0x0bb20bb2, 0x0bb20bb2, 0x0f9a0f9a, 0x0f720f72,	0x00000000},
													{0x0645,	0x05d805da, 0x05d805da, 0x05d805da, 0x05d805da, 0x08c608c8, 0x08c608c8, 0x08c608c8, 0x08c608c8, 0x0bb40bb6, 0x0bb40bb6, 0x0f9c0f9e, 0x0f740f76,	0x00000000},
													{0x0651,	0x6000ff00, 0x6000ff00, 0x6000ff00, 0x6000ff00, 0x6000ff00, 0x6000ff00, 0x6000ff00, 0x6000ff00, 0x6000ff00, 0x6000ff00, 0x6000ff00, 0x6000ff00,	0x00000000},
													{0x0654,	0x00140017, 0x00140017, 0x00140017, 0x00140017, 0x00140017, 0x00140017, 0x00010005, 0x00010005, 0x0014001c, 0x0014001c, 0x00140017, 0x00140017,	0x00000000},
													{0x0656,	0x02e33f00, 0x02e33f00, 0x01943f00, 0x01943f00, 0x01943f00, 0x01943f00, 0x01943f00, 0x01943f00, 0x02103f00, 0x02103f00, 0x01963f00, 0x020c3f00,	0x00000000},													
													{0x0662,	0x04b004b0, 0x04b004b0, 0x04b004b0, 0x04b004b0, 0x05000500, 0x05000500, 0x05000500, 0x05000500, 0x09600960, 0x09600960, 0x0c800c80, 0x0c600c60,	0x00000000},
													{0x0663,	0x04b204b2, 0x04b204b2, 0x04b204b2, 0x04b204b2, 0x05020502, 0x05020502, 0x05020502, 0x05020502, 0x09620962, 0x09620962, 0x0c820c82, 0x0c620c62,	0x00000000},
													{0x066d,	0x81b50700, 0x81b50700, 0x81b50700, 0x81b50700, 0x81b50700, 0x81b50700, 0x81b50700, 0x81b50700, 0x81b50700, 0x81b50700, 0x81b50700, 0x81b50700,	0x00000000},
													{0x0613,	0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x40404040,	0x00000000},
													{0x0614,	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,	0x00000000},
													{0x0646,	0x01a90000, 0x01a90000, 0x01a90000, 0x01a90000, 0x01a90000, 0x01a90000, 0x010f0000, 0x010f0000, 0x01a90000, 0x01a90000, 0x01a90000, 0x01a90000,	0x00000000},
													{0x0647,	0x0e380000, 0x0ba40000, 0x071c0000, 0x05d20000, 0x097a0000, 0x07e80000, 0x0ad60148, 0x0CFF0148, 0x097a0000, 0x07c20000, 0x0afa0000, 0x08ee0000,	0x00000000},
													{0x0648,	0x00a00000, 0x00a00000, 0x00500000, 0x00500000, 0x00580000, 0x00580000, 0x00580000, 0x00580000, 0x006a0000, 0x006a0000, 0x00500000, 0x006a0000,	0x00000000},
													{0x0649,	0x01400000, 0x01400000, 0x00a00000, 0x00a00000, 0x00b00000, 0x00b10000, 0x00a00000, 0x00a00000, 0x00d50000, 0x00d60000, 0x00a00000, 0x00d50000,	0x00000000},
													{0x064a,	0x010a0180, 0x010a0180, 0x008c00bc, 0x008c00bc, 0x008300ce, 0x008000d1, 0x007c00c7, 0x007c00c7, 0x00a900ff, 0x00a80100, 0x008900ca, 0x00a700fe,	0x00000000},
													{0x064c,	0x1538047e, 0x1538047e, 0x0a9c023f, 0x0a9c023f, 0x0f080206, 0x0f070206, 0x09560181, 0x09560181, 0x0d550326, 0x0d530323, 0x14b0020a, 0x0d800318,	0x00000000},
													{0x0682,	0x0000e000, 0x0000e000, 0x0000e000, 0x0000e000, 0x0000e000, 0x0000e000, 0x0000e000, 0x0000e000, 0x0000e000, 0x0000e000, 0x0000e000, 0x0000e000,	0x00000000},
													{0x0683,	0x02160216, 0x02160216, 0x02160216, 0x02160216, 0x02200220, 0x02200220, 0x02000200, 0x02000200, 0x02200220, 0x02200220, 0x02200220, 0x02200220,	0x00000000},
													{0x0684,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300,	0x00000000},
													{0x0685,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300,	0x00000000},
													{0x0686,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300,	0x00000000},
													{0x0687,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300,	0x00000000},
													{0x0688,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300,	0x00000000},
													{0x0689,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300,	0x00000000},
													{0x068a,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300,	0x00000000},
													{0x0696,	0x00d600d6, 0x00d600d6, 0x00d600d6, 0x00d600d6, 0x01140114, 0x01140114, 0x01210121, 0x01210121, 0x01140114, 0x01140114, 0x01140114, 0x01140114,	0x00000000},
													{0x0697,	0x01000100, 0x01000100, 0x00d600d6, 0x00d600d6, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100,	0x00000000},
													{0x0698,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100,	0x00000000},
													{0x0699,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100,	0x00000000},
													{0x069a,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100,	0x00000000},
													{0x069b,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100,	0x00000000},
													{0x069c,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100,	0x00000000},
													{0x069d,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100,	0x00000000},
													{0x06a1,	0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200,	0x00000000},
													{0x06a2,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300,	0x00000000},
													{0x06a3,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300,	0x00000000},
													{0x06a4,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300,	0x00000000},
													{0x06a5,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300,	0x00000000},
													{0x06a6,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300,	0x00000000},
													{0x06a7,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300,	0x00000000},
													{0x06a8,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300,	0x00000000},
													{0x0622,	0x0fff0fff, 0x0fff0fff, 0x0fff0fff, 0x0fff0fff, 0x0fff0fff, 0x0fff0fff, 0x0fff0fff, 0x0fff0fff, 0x0fff0fff, 0x0fff0fff, 0x0fff0fff, 0x0fff0fff,	0x00000000},
													{0x0623,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100,	0x00000000},
													{0x0624,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100,	0x00000000},
													{0x0625,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100,	0x00000000},
													{0x0626,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100,	0x00000000},
													{0x0627,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100,	0x00000000},
													{0x0628,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100,	0x00000000},
													{0x0629,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100,	0x00000000},
													{0x0635,	0x0f770b1a, 0x0ce30886, 0x07bb059e, 0x06710454, 0x0a4f08b7, 0x089706ff, 0x0cbf0008, 0x0aa00008, 0x0a4f076e, 0x089705b5, 0x0b990933, 0x09c306bd,	0x00000000},
													{0x0658,	0x2000067d, 0x2000067d, 0x2000033d, 0x2000033d, 0x2000033d, 0x2000033d, 0x20001800, 0x20001800, 0x20000455, 0x20000454, 0x2000033d, 0x20000455,	0x00000000}
							   						};
//*********************************************************************************************************************************************************
// MODE_C
//---------------------------------------------------------------------------------------------------------------------------------------------------------

	const UINT gnEncModeC_LV0[][ANA_MODE_NUM] = 	{
													//720P											//1080P											//1440P					//1944P
																															//(TBD)		//(TBD)								//(TBD)					//(TBD)
								//Name				//25		//30		//50		//60		//25		//30		//50		//60		//25		//30		//12.5		//20		//25
							   	/*UpENC_RYGAINP*/ 	{0x54,		0x54,		0x56,		0x56,		0x55,		0x53,		0x00,		0x00,		0x58,		0x46,		0x00,		0x40,		0x00},
							   	/*UpENC_RYGAINN*/ 	{0x5a,		0x6a,		0x50,		0x50,		0x60,		0x4c,		0x00,		0x00,		0x53,		0x57,		0x00,		0x40,		0x00},
							   	/*UpENC_BYGAINP*/ 	{0x3c,		0x3c,		0x40,		0x40,		0x45,		0x3b,		0x00,		0x00,		0x41,		0x31,		0x00,		0x40,		0x00},
							   	/*UpENC_BYGAINN*/ 	{0x3e,		0x3e,		0x36,		0x36,		0x35,		0x38,		0x00,		0x00,		0x42,		0x3d,		0x00,		0x40,		0x00},
							                                	        	        	        	        	        	        	        	        	        	        	        	
							   	/*UpENC_RYHUEP*/	{0x07,		0x07,		0x0a,		0x0a,		0x0e,		0xe0,		0x00,		0x00,		0x18,		0x1c,		0x00,		0x0a,		0x00},
						    	/*UpENC_RYHUEN*/	{0x02,		0x02,		0x0e,		0x00,		0x0c,		0xe7,		0x00,		0x00,		0x03,		0xfa,		0x00,		0x00,		0x00},
							    /*UpENC_BYHUEP*/	{0x00,		0x00,		0x00,		0x00,		0x0f,		0x0d,		0x00,		0x00,		0x01,		0xf8,		0x00,		0x00,		0x00},
							    /*UpENC_BYHUEN*/	{0x00,		0x00,		0xff,		0xff,		0x04,		0x16,		0x00,		0x00,		0x07,		0xf8,		0x00,		0xe4,		0x00},          

							    /*UpWHITE_LV*/		{0x3b1,		0x3b1,		0x39d,		0x39d,		0x3bf,		0x3bf,		0x00,		0x00,		0x3ce,		0x3ce,		0x00,		0x3ff,		0x00},
								/*UpBLANK_LV*/		{0xe5,		0xe5,		0xde,		0xde,		0x102,		0x102,		0x00,		0x00,		0x100,		0x100,		0x00,		0x127,		0x00},								
							    /*UpPEDESTAL_LV*/ 	{0x0,		0x0,		0x0,		0x0,		0x0,		0x0,		0x00,		0x00,		0x0,		0x0,		0x00,		0x0,		0x00},

								/*UpFSC_TGT*/		{0x48676f31,0x48676f31,	0x83044f4c,	0x83044f4c,	0x83044f4c,	0x8302c84c,	0x00,		0x00,		0xafd6a052,	0xafd69f52,	0x00,		0xafd6a052,	0x00},
								
							    /*UpY_MGAIN*/	   	{0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x00,		0x00,		0x100,		0x100,		0x00,		0x100,		0x00},
							    /*UpCB_MGAIN*/		{0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x00,		0x00,		0x100,		0x100,		0x00,		0x100,		0x00},
							    /*UpCR_MGAIN*/		{0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x00,		0x00,		0x100,		0x100,		0x00,		0x100,		0x00},
								                            	        	        	        	        	        	        	        	        	        	        	        	
							    /*UpCB_BST*/		{0x1ab,		0x1ab,		0x1ab,		0x1ab,		0x1b0,		0x1b0,		0x00,		0x00,		0x1c0,		0x1c0,		0x00,		0x160,		0x00},
							    /*UpCR_BST*/		{0x254,		0x254,		0x254,		0x254,		0x250,		0x250,		0x00,		0x00,		0x240,		0x240,		0x00,		0x29f,		0x00},
							    
												#if(model_2M)
													// D + L DVR
   							    /*UpHSC_K*/			{0x343,		0x3ea,		0x686,		0x7d4,		0x751,		0x8c8,		0x00,		0x00,		0x9b0,		0xba4,		0x00,		0xc28,		0x00},
							    /*UpHLOCK_CAT*/		{0xa3e,		0x899,		0x530,		0x459,		0x6da,		0x5b8,		0x00,		0x00,		0x6df,		0x5bc,		0x00,		0x4a2,		0x00},
							    /*UpVLOCK_CAT_EV*/	{0x5cb,		0x5cb,		0x1,		0x1,		0x8ad,		0x8ad,		0x00,		0x00,		0xb9b,		0xb9b,		0x00,		0xf5a,		0x00},	
							    
							    				#else
   							    /*UpHSC_K*/			{0x343,		0x3ea,		0x686,		0x7d4,		0x751,		0x8c8,		0x00,		0x00,		0x9b0,		0xba4,		0x00,		0xc28,		0x00},
							    /*UpHLOCK_CAT*/		{0xa3e,		0x899,		0x530,		0x459,		0x6da,		0x5b8,		0x00,		0x00,		0x6df,		0x5bc,		0x00,		0x4a2,		0x00},
							    /*UpVLOCK_CAT_EV*/	{0x5cb,		0x5cb,		0x1,		0x1,		0x8a3,		0x8a3,		0x00,		0x00,		0xb95,		0xb95,		0x00,		0xf5a,		0x00},					    
												#endif
													
							    /*UpVLOCK_CAT_OD*/	{0x1,		0x1,		0x1,		0x1,		0x1,		0x1,		0x00,		0x00,		0x1,		0x1,		0x00,		0x1,		0x00},			                                	        	        	        	        	        	        	        	        	        	        	        	
							    /*UpCRX_AUTO_CAT*/	{0x6e,		0x6e,		0x6e,		0x6e,		0x6e,		0x6e,		0x00,		0x00,		0x11f,		0x118,		0x00,		0x90,		0x00},
								/*UpCRX_HPOSEVS*/	{0x466,		0x466,		0x466,		0x466,		0x31d,		0x344,		0x00,		0x00,		0x37a,		0x2db,		0x00,		0x282,		0x00},
								/*UpCRX_HPOSEVE*/	{0x3f00,	0x3f00,		0x3f00,		0x3f00,		0x3f00,		0x3f00,		0x00,		0x00,		0x3f00,		0x3f00,		0x00,		0x3f00,		0x00},
								/*UpCTX_BITRATE*/	{0x2bd,		0x2bd,		0x2bd,		0x2bd,		0x2bd,		0x2bd,		0x00,		0x00,		0x726,		0x6fd,		0x00,		0x220,		0x00}
							   						};


	const UINT gnEncModeC_LV1[][ANA_MODE_NUM+1] = 	{
																//720P											//1080P											//1440P					//1944P
																																		//(TBD)		//(TBD)														//(TBD)
													//Addr		//25		//30		//50		//60		//25		//30		//50		//60		//25		//30		//12.5		//20		//25	
													{0x063c,	0x003205d2, 0x003205d2, 0x003205d2, 0x003205d2, 0x005208c2, 0x005208c2, 0x00000000, 0x00000000, 0x005e0b9e, 0x005e0b9e, 0x00000000, 0x00450f69,	0x00000000},
													{0x0643,	0x003205d2, 0x003205d2, 0x003205d2, 0x003205d2, 0x005208c2, 0x003008c2, 0x00000000, 0x00000000, 0x00520bac, 0x00520bac, 0x00000000, 0x00520f90,	0x00000000},
													{0x064b,	0x18bf057e, 0x14a5048f, 0x0c6402bc, 0x0a550247, 0x108303a7, 0x0f0701d8, 0x00000000, 0x00000000, 0x108a03a6, 0x0dc8030a, 0x00000000, 0x0dc50524,	0x00000000},
													{0x0609,	0x1ebe02e8, 0x199602e4, 0x0f4602e4, 0x0cb202e4, 0x146d045b, 0x10fe045b, 0x00000000, 0x00000000, 0x146e05d2, 0x10fe05d2, 0x00000000, 0x135607b2,	0x00000000},
													{0x0695,	0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x00000000, 0x00000000, 0x80000000, 0x80000000, 0x00000000, 0x80000000,	0x00000000},
							   						};	
													
	// LV2 Table Index +1												
	const UINT gnEncModeC_LV2[][ANA_MODE_NUM+1] = 	{
																//720P											//1080P 											//1440P 					//1944P
																						//(TBD) 		//(TBD) 								//(TBD) 		//(TBD)														//(TBD) 							
													//Addr		//25		//30		//50		//60		//25		//30		//50		//60		//25		//30		//12.5		//20		//25
													{0x0003,	0xb000022b, 0xb000022b, 0xb000022b, 0xb000022b, 0xb000022b, 0xb000022b, 0x00000000, 0x00000000, 0xa0000357, 0xa0000357, 0xb000022b, 0xa0000357, 0x00000000},
													{0x0607,	0x1eef02ed, 0x19c702ed, 0x0f7702ed, 0x0ce302ed, 0x149f0464, 0x112f0464, 0x00000000, 0x00000000, 0x149f05db, 0x112f05db, 0x138707bb, 0x138707bb, 0x00000000},
													{0x0608,	0x00010001, 0x00010003, 0x00010008, 0x00010008, 0x00010001, 0x00010008, 0x00000000, 0x00000000, 0x00010001, 0x00010001, 0x00010009, 0x00010009, 0x00000000},
													{0x0621,	0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000000, 0x00000000, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000000},
													{0x0631,	0x0f7705db, 0x0ce305db, 0x07bb05db, 0x067105db, 0x0a4e08c9, 0x089708c9, 0x00000000, 0x00000000, 0x0a4f0bb7, 0x08970bb7, 0x09aa0f9f, 0x09aa0f9f, 0x00000000},
													{0x0632,	0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b, 0x00000000, 0x00000000, 0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b, 0x00000000},
													{0x0637,	0x03180560, 0x0294047d, 0x018a02a9, 0x014a0238, 0x0210039d, 0x01b80305, 0x00000000, 0x00000000, 0x02040395, 0x01b202f8, 0x01b804e9, 0x01b804e9, 0x00000000},
													{0x065e,	0x0802002b, 0x0802002b, 0x0802002b, 0x0802002b, 0x08080073, 0x08080073, 0x00000000, 0x00000000, 0x080803ff, 0x080803ff, 0x080803ff, 0x080803ff, 0x00000000},
													{0x06ab,	0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x00000000, 0x00000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x00000000},
													{0x063a,	0x05db0004, 0x05db0004, 0x05db0004, 0x05db0004, 0x08c90004, 0x08c90004, 0x00000000, 0x00000000, 0x0bb70004, 0x0bb70004, 0x00000005, 0x00000005, 0x00000000},
													{0x063b,	0x0008000c, 0x0008000c, 0x0008000c, 0x0008000c, 0x0008000c, 0x0008000c, 0x00000000, 0x00000000, 0x00080008, 0x00080008, 0x0009000d, 0x0009000d, 0x00000000},
													{0x063d,	0x05d605d6, 0x05d605d6, 0x05d605d6, 0x05d605d6, 0x08c408c4, 0x08c408c4, 0x00000000, 0x00000000, 0x0bb20bb2, 0x0bb20bb2, 0x0f720f73, 0x0f720f73, 0x00000000},
													{0x063e,	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
													{0x0641,	0x05db0004, 0x05db0004, 0x05db0004, 0x05db0004, 0x08c90004, 0x08c90004, 0x00000000, 0x00000000, 0x0bb70004, 0x0bb70004, 0x0f9f0004, 0x0f9f0004, 0x00000000},
													{0x0642,	0x0008000c, 0x0008000c, 0x0008000c, 0x0008000c, 0x0008000c, 0x0008000c, 0x00000000, 0x00000000, 0x0008000c, 0x0008000c, 0x0008000c, 0x0008000c, 0x00000000},
													{0x0644,	0x05d605d6, 0x05d605d6, 0x05d605d6, 0x05d605d6, 0x08c208c4, 0x08c208c4, 0x00000000, 0x00000000, 0x0bb00bb2, 0x0bb00bb2, 0x0f980f9a, 0x0f980f9a, 0x00000000},
													{0x0645,	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
													{0x0651,	0x6000ff00, 0x6000ff00, 0x6000ff00, 0x6000ff00, 0x6000ff00, 0x6000ff00, 0x00000000, 0x00000000, 0x6000ff00, 0x6000ff00, 0x6000ff00, 0x6000ff00, 0x00000000},
													{0x0654,	0x001e0029, 0x001e0029, 0x001e0029, 0x001e0029, 0x001e0029, 0x001e0029, 0x00000000, 0x00000000, 0x002a0039, 0x002a0039, 0x001f002a, 0x001f002a, 0x00000000},
													{0x0656,	0x04663f00, 0x04663f00, 0x04663f00, 0x04663f00, 0x031d3f00, 0x03443f00, 0x00000000, 0x00000000, 0x037a3f00, 0x02db3f00, 0x02823f00, 0x02823f00, 0x00000000},
													{0x0662,	0x04b004b0, 0x04b004b0, 0x04b004b0, 0x04b004b0, 0x03000300, 0x03000300, 0x00000000, 0x00000000, 0x09600960, 0x09600960, 0x0c600c60, 0x0c600c60, 0x00000000},
													{0x0663,	0x04b204b2, 0x04b204b2, 0x04b204b2, 0x04b204b2, 0x03020302, 0x03020302, 0x00000000, 0x00000000, 0x09620962, 0x09620962, 0x0c620c62, 0x0c620c62, 0x00000000},
													{0x066d,	0x81a50700, 0x81a50700, 0x81a50700, 0x81a50700, 0x81a50700, 0x81a50700, 0x00000000, 0x00000000, 0x81a50700, 0x81a50700, 0x81a50700, 0x81a50700, 0x00000000},
													{0x0613,	0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x00000000, 0x00000000, 0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x00000000},
													{0x0614,	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
													{0x0646,	0x01a90000, 0x01a90000, 0x01a90000, 0x01a90000, 0x01a90000, 0x01a90000, 0x00000000, 0x00000000, 0x01a90000, 0x01a90000, 0x01a90000, 0x01a90000, 0x00000000},
													{0x0647,	0x0d2d0000, 0x0b010000, 0x069a0000, 0x057f0000, 0x08ad0000, 0x073e0000, 0x00000000, 0x00000000, 0x08cd0000, 0x07550000, 0x084d0000, 0x084d0000, 0x00000000},
													{0x0648,	0x01240000, 0x00f10000, 0x00900000, 0x00790000, 0x00c00000, 0x00a10000, 0x00000000, 0x00000000, 0x00c10000, 0x00a10000, 0x00b30000, 0x00b30000, 0x00000000},
													{0x0649,	0x02490000, 0x01e70000, 0x01210000, 0x00f20000, 0x01830000, 0x01420000, 0x00000000, 0x00000000, 0x01820000, 0x01420000, 0x013d0000, 0x013d0000, 0x00000000},
													{0x064a,	0x00d702c3, 0x00b1024d, 0x006f015c, 0x005d0123, 0x009301cd, 0x00790181, 0x00000000, 0x00000000, 0x008c01db, 0x0075018b, 0x007b018b, 0x007b018b, 0x00000000},
													{0x064c,	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
													{0x0682,	0x0000f000, 0x0000f000, 0x0000f000, 0x0000f000, 0x0000f000, 0x0000f000, 0x00000000, 0x00000000, 0x0000f000, 0x0000f000, 0x0000f000, 0x0000f000, 0x00000000},
													{0x0683,	0x02160216, 0x02160216, 0x02160216, 0x02160216, 0x02200220, 0x02200220, 0x00000000, 0x00000000, 0x02200220, 0x02200220, 0x02200220, 0x02200220, 0x00000000},
													{0x0684,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000, 0x00000000, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000},
													{0x0685,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000, 0x00000000, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000},
													{0x0686,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000, 0x00000000, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000},
													{0x0687,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000, 0x00000000, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000},
													{0x0688,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000, 0x00000000, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000},
													{0x0689,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000, 0x00000000, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000},
													{0x068a,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000, 0x00000000, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000},
													{0x0696,	0x00d600d6, 0x00d600d6, 0x00d600d6, 0x00d600d6, 0x01140114, 0x01140114, 0x00000000, 0x00000000, 0x01140114, 0x01140114, 0x01140114, 0x01140114, 0x00000000},
													{0x0697,	0x01000100, 0x01000100, 0x00d600d6, 0x00d600d6, 0x01000100, 0x01000100, 0x00000000, 0x00000000, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000},
													{0x0698,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000, 0x00000000, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000},
													{0x0699,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000, 0x00000000, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000},
													{0x069a,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000, 0x00000000, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000},
													{0x069b,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000, 0x00000000, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000},
													{0x069c,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000, 0x00000000, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000},
													{0x069d,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000, 0x00000000, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000},
													{0x06a1,	0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000, 0x00000000, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000},
													{0x06a2,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000, 0x00000000, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000},
													{0x06a3,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000, 0x00000000, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000},
													{0x06a4,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000, 0x00000000, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000},
													{0x06a5,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000, 0x00000000, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000},
													{0x06a6,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000, 0x00000000, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000},
													{0x06a7,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000, 0x00000000, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000},
													{0x06a8,	0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000, 0x00000000, 0x03000300, 0x03000300, 0x03000300, 0x03000300, 0x00000000},
													{0x0622,	0x00a200ac, 0x0fff0fff, 0x0fff0fff, 0x0fff0fff, 0x0fff0fff, 0x0fff0fff, 0x00000000, 0x00000000, 0x0fff0fff, 0x0fff0fff, 0x0fff0fff, 0x0fff0fff, 0x00000000},
													{0x0623,	0x00ac00ac, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000, 0x00000000, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000},
													{0x0624,	0x00ac00ac, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000, 0x00000000, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000},
													{0x0625,	0x00ac00ac, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000, 0x00000000, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000},
													{0x0626,	0x00a804b3, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000, 0x00000000, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000},
													{0x0627,	0x00a200ac, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000, 0x00000000, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000},
													{0x0628,	0x00ac00eb, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000, 0x00000000, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000},
													{0x0629,	0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000, 0x00000000, 0x01000100, 0x01000100, 0x01000100, 0x01000100, 0x00000000},
													{0x0635,	0x0f770a3e, 0x0ce30899, 0x07bb0530, 0x06710459, 0x0a4e06da, 0x089705b8, 0x00000000, 0x00000000, 0x0a4f06df, 0x089705bc, 0x09c104a2, 0x09c104a2, 0x00000000},
													{0x0658,	0x200002bd, 0x200002bd, 0x200002bd, 0x200002bd, 0x200002bd, 0x200002bd, 0x00000000, 0x00000000, 0x08000726, 0x080006fd, 0x20000220, 0x20000220,	0x00000000}
													};


//*********************************************************************************************************************************************************
// MODE_A
//---------------------------------------------------------------------------------------------------------------------------------------------------------

	const UINT gnEncModeA_LV0[][ANA_MODE_NUM] = 	{
													//720P											//1080P											//1440P					//1944P
																			//(TBD) 		//(TBD) 								//(TBD) 		//(TBD) 														//(TBD)
								//Name				//25		//30		//50		//60		//25		//30		//50		//60		//25		//30		//12.5		//20		//25
							   	/*UpENC_RYGAINP*/ 	{0x3b,		0x37,		0x46,		0x46,		0x70,		0x70,		0x00,		0x00,		0x70,		0x70,		0x3a,		0x30,		0x00},
							   	/*UpENC_RYGAINN*/ 	{0x47,		0x43,		0x47,		0x47,		0x70,		0x70,		0x00,		0x00,		0x80,		0x80,		0x25,		0x2d,		0x00},	
							   	/*UpENC_BYGAINP*/ 	{0x2f,		0x28,		0x40,		0x40,		0x70,		0x70,		0x00,		0x00,		0x50,		0x50,		0x20,		0x19,		0x00},
							   	/*UpENC_BYGAINN*/ 	{0x2a,		0x2e,		0x35,		0x35,		0x70,		0x70,		0x00,		0x00,		0x70,		0x70,		0x25,		0x30,		0x00},
                                                            	        	        	        	        	        	        	        	        	        	        	        	
							   	/*UpENC_RYHUEP*/	{0xfe,		0xf3,		0xeb,		0xeb,		0x1D,		0x1D,		0x00,		0x00,		0x09,		0x09,		0x07,		0x0c,		0x00},
						    	/*UpENC_RYHUEN*/	{0xeb,		0xf6,		0xea,		0xea,		0xDB,		0xDB,		0x00,		0x00,		0xFE,		0xFE,		0xff,		0xea,		0x00},
							    /*UpENC_BYHUEP*/	{0x0e,		0x0e,		0x0e,		0xe,		0xC6,		0xC6,		0x00,		0x00,		0xFB,		0xFB,		0x03,		0x0a,		0x00},
							    /*UpENC_BYHUEN*/	{0x1d,		0x16,		0x24,		0x24,		0xEE,		0xEE,		0x00,		0x00,		0xEE,		0xEE,		0xf6,		0xf0,		0x00},

							    /*UpWHITE_LV*/		{0x35a,		0x35a,		0x386,		0x386,		0x390,		0x390,		0x00,		0x00,		0x373,		0x373,		0x35a,		0x35a,		0x00},
								/*UpBLANK_LV*/		{0x119,		0x119,		0x119,		0x119,		0x107,		0x107,		0x00,		0x00,		0x108,		0x108,		0x10c,		0x108,		0x00},
							    /*UpPEDESTAL_LV*/ 	{0x0,		0x0,		0x0,		0x0,		0x0,		0x0,		0x00,		0x00,		0x0,		0x0,		0x0,		0x0,		0x00},

//								/*UpFSC_TGT*/		{0x27871400,0x277213ff,	0x277b1400,	0x277213ff,	0x52c21cff,	0x52cb9d1d,	0x00,		0x00,		0x6ca6d01a,	0x6ca0b63d,	0x52d10984,	0x6cb3a380,	0x00},
								/*UpFSC_TGT*/		{0x27871400,0x277213ff, 0x277b1400, 0x277213ff, 0x52c21cff, 0x52cb9d1d, 0x00,		0x00,		0x6ca6cf87, 0x6ca001ea, 0x52d1047d, 0x6cb36d18, 0x00}, // 210914 JHR : Change FSC_TGT(4M, 5M)

							    /*UpY_MGAIN*/	   	{0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x00,		0x00,		0x100,		0x100,		0x100,		0x100,		0x00},
							    /*UpCB_MGAIN*/		{0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x00,		0x00,		0x100,		0x100,		0x100,		0x100,		0x00},
							    /*UpCR_MGAIN*/		{0x100,		0x100,		0x100,		0x100,		0x100,		0x100,		0x00,		0x00,		0x100,		0x100,		0x100,		0x100,		0x00},

							                                	        	        	        	        	        	        	        	        	        	        	        	
								/*UpCB_BST*/		{0x169, 	0x169,		0x169,		0x169,		0x17a,		0x17f,		0x00,		0x00,		0x182,		0x192,		0x187,		0x18a,		0x00},
							    /*UpCR_BST*/		{0x200,		0x200,		0x200,		0x200,		0x200,		0x200,		0x00,		0x00,		0x200,		0x200,		0x200,		0x200,		0x00},
							    
												#if(model_2M)
													// X + L DVR
							    /*UpHSC_K*/			{0x400,		0x400,		0x9c9,		0xbb2,		0x800,		0x800,		0x00,		0x00,		0xbfb,		0xbfb,		0x818,		0xc28,		0x00},
							    /*UpHLOCK_CAT*/		{0xb09,		0x87d,		0x5db,		0x440,		0x88b,		0x6d2,		0x00,		0x00,		0x335,		0x3b9,		0x790,		0x3b6,		0x00},
							    /*UpVLOCK_CAT_EV*/	{0x5cd,		0x5cd,		0x5cd,		0x5d1,		0x8ab,		0x8ab,		0x00,		0x00,		0xb97,		0xb97,		0xf5f,		0xf53,		0x00},
							    				#else
							    /*UpHSC_K*/			{0x400,		0x400,		0x9c9,		0xbb2,		0x800,		0x800,		0x00,		0x00,		0xbfb,		0xbfb,		0x818,		0xc28,		0x00},
							    /*UpHLOCK_CAT*/		{0xb09,		0x87d,		0x5db,		0x440,		0x88b,		0x6d2,		0x00,		0x00,		0x335,		0x3b9,		0x790,		0x3b6,		0x00},
							    /*UpVLOCK_CAT_EV*/	{0x5c7,		0x5c7,		0x5c7,		0x5c7,		0x89f,		0x89f,		0x00,		0x00,		0xb91,		0xb91,		0xf5f,		0xf5f,		0x00},
												#endif
													
							    /*UpVLOCK_CAT_OD*/	{0x1,		0x1,		0x1,		0x1,		0x1,		0x1,		0x00,		0x00,		0x1,		0x1,		0x1,		0x1,		0x00},
							    /*UpCRX_AUTO_CAT*/	{0x0,		0x0,		0x0,		0x0,		0x0,		0x0,		0x00,		0x00,		0x0,		0x0,		0x0,		0x0,		0x00},
								/*UpCRX_HPOSEVS*/	{0x4d4,		0x4d4,		0x4d4,		0x4d4,		0x384,		0x384,		0x00,		0x00,		0x34d,		0x343,		0x343,		0x359,		0x00},
								/*UpCRX_HPOSEVE*/	{0x3fff,	0x3fff,		0x3fff,		0x3fff,		0x3ff0,		0x3ff0,		0x00,		0x00,		0x3ff0,		0x3ff0,		0x3ff0,		0x3ff0,		0x00},  
								/*UpCTX_BITRATE*/	{0xe20,		0xe20,		0xe20,		0xe20,		0xe20,		0xe20,		0x00,		0x00,		0xd70,		0xd70,		0x1110,		0xd70,		0x00} 
							   						};


	const UINT gnEncModeA_LV1[][ANA_MODE_NUM+1] = 	{
																//720P											//1080P											//1440P					//1944P
																						//(TBD) 		//(TBD) 								//(TBD) 		//(TBD) 														//(TBD)
													//Addr		//25		//30		//50		//60		//25		//30		//50		//60		//25		//30		//12.5		//20		//25	
													{0x063c,	0x003605d4, 0x003605d4, 0x003005d4, 0x003005d4, 0x005408c4, 0x005408c4, 0x00000000, 0x00000000, 0x00640ba4, 0x00640ba4, 0x00380f68, 0x00380f68,	0x00000000},
													{0x0643,	0x003005d4, 0x003005d4, 0x003005d4, 0x003005d4, 0x003008c2, 0x003008c2, 0x00000000, 0x00000000, 0x00300bb0, 0x00300bb0, 0x00300f70, 0x00300f70,	0x00000000},
													{0x064b,	0x147a0453, 0x14d60453, 0x14d60453, 0x14d60453, 0x0f0a020a, 0x0f0c020a, 0x00000000, 0x00000000, 0x0d600379, 0x0d600370, 0x14900291, 0x0d730383,	0x00000000},
													{0x0609,	0x1ebe02e4, 0x199602e4, 0x0f4602e4, 0x0cb202e4, 0x146d045b, 0x10fe045b, 0x00000000, 0x00000000, 0x146e05d2, 0x10fe05d2, 0x175007ab, 0x137007b2,	0x00000000},
													{0x0695,	0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x52aa00f0, 0x52aa00f0, 0x00000000, 0x00000000, 0x6c9b16dc, 0x6c91f0bc, 0x52e9fcf0, 0x6c9b1cc9,	0x00000000},
							   						};

	
	// LV2 Table Index +1												
	const UINT gnEncModeA_LV2[][ANA_MODE_NUM+1] = 	{
																//720P											//1080P 											//1440P 					//1944P 								
																						//(TBD) 		//(TBD) 								//(TBD) 		//(TBD) 														//(TBD)
													//Addr		//25		//30		//50		//60		//25		//30		//50		//60		//25		//30		//12.5		//20		//25
													{0x0003,	0xb000022b, 0xb000022b, 0xb000022b, 0xb000022b, 0xb000022b, 0xb000022b, 0x00000000, 0x00000000, 0xb0000357, 0xb0000357, 0xb000022b, 0xb0000357, 0x00000000},
													{0x0607,	0x1eef02ed, 0x19c702ed, 0x0ce302ed, 0x0ce302ed, 0x149f0464, 0x112f0464, 0x00000000, 0x00000000, 0x149f05db, 0x112f05db, 0x176f07bb, 0x138707bb, 0x00000000},
													{0x0608,	0x00010003, 0x00010003, 0x00010001, 0x00010001, 0x00010008, 0x00010008, 0x00000000, 0x00000000, 0x00010001, 0x00010001, 0x00010001, 0x00010010, 0x00000000},
													{0x0621,	0x0000000c, 0x0000000c, 0x0000000c, 0x0000000c, 0x0000000c, 0x0000000c, 0x00000000, 0x00000000, 0x0000000c, 0x0000000c, 0x0000000c, 0x0000000c, 0x00000000},
													{0x0631,	0x0f7705db, 0x0ce305db, 0x067105db, 0x067105db, 0x0a4e08c9, 0x089708c9, 0x00000000, 0x00000000, 0x0a4f0bb7, 0x08970bb7, 0x0bb70f77, 0x09c30f77, 0x00000000},
													{0x0632,	0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b, 0x00000000, 0x00000000, 0x0001005b, 0x0001005b, 0x0001005b, 0x0001005b, 0x00000000},
													{0x0637,	0x0229044c, 0x027f04a0, 0x027f04a0, 0x00a0026d, 0x01e801d0, 0x01e000ea, 0x00000000, 0x00000000, 0x01b20300, 0x01b20300, 0x02810264, 0x01b4037d, 0x00000000},
													{0x065e,	0x0808003f, 0x0808003f, 0x0808003f, 0x0808003f, 0x0808003f, 0x0808003f, 0x00000000, 0x00000000, 0x080803ff, 0x080803ff, 0x080803ff, 0x080803ff, 0x00000000},
													{0x06ab,	0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x00000000, 0x00000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x00000000},
													{0x063a,	0x05db0004, 0x05db0004, 0x05db0004, 0x05db0004, 0x08c90004, 0x08c90004, 0x00000000, 0x00000000, 0x0000000a, 0x0000000a, 0x0000000a, 0x0000000a, 0x00000000},
													{0x063b,	0x0008000c, 0x0008000c, 0x0008000c, 0x0008000c, 0x00080008, 0x00080008, 0x00000000, 0x00000000, 0x0004000a, 0x000a000a, 0x0008000a, 0x0008000a, 0x00000000},
													{0x063d,	0x05d605d6, 0x05d605d6, 0x05d605d6, 0x05d605d6, 0x08c408c4, 0x08c408c4, 0x00000000, 0x00000000, 0x0bb70bb8, 0x0bb70bb8, 0x0f770f78, 0x0f770f78, 0x00000000},
													{0x063e,	0x00280030, 0x00280030, 0x00280030, 0x00280030, 0x002a0032, 0x002a0032, 0x00000000, 0x00000000, 0x002c0034, 0x002c0034, 0x002c0034, 0x002c0034, 0x00000000},
													{0x0641,	0x05db0004, 0x05db0004, 0x05db0004, 0x05db0004, 0x08c90004, 0x08c90004, 0x00000000, 0x00000000, 0x0bb70004, 0x0bb70004, 0x0f770004, 0x0f770004, 0x00000000},
													{0x0642,	0x0008000c, 0x0008000c, 0x0008000c, 0x0008000c, 0x0008000c, 0x0008000c, 0x00000000, 0x00000000, 0x0008000c, 0x0008000c, 0x0008000c, 0x0008000c, 0x00000000},
													{0x0644,	0x05d605d6, 0x05d605d6, 0x05d605d6, 0x05d605d6, 0x08c408c4, 0x08c408c4, 0x00000000, 0x00000000, 0x0bb20bb2, 0x0bb20bb2, 0x0f720f72, 0x0f720f72, 0x00000000},
													{0x0645,	0x05d805da, 0x05d805da, 0x05d805da, 0x05d805da, 0x08c608c8, 0x08c608c8, 0x00000000, 0x00000000, 0x0bb40bb6, 0x0bb40bb6, 0x0f740f76, 0x0f740f76, 0x00000000},
													{0x0651,	0x4000ff00, 0x4000ff00, 0x4000ff00, 0x4000ff00, 0x4000ff00, 0x4000ff00, 0x00000000, 0x00000000, 0x4000ff00, 0x4000ff00, 0x4000ff00, 0x4000ff00, 0x00000000},
													{0x0654,	0x001a001d, 0x001a001d, 0x001a001d, 0x00140017, 0x00190021, 0x00190021, 0x00000000, 0x00000000, 0x001c0023, 0x001c0023, 0x001c0023, 0x001c0023, 0x00000000},
													{0x0656,	0x04d43fff, 0x04d43fff, 0x04d43fff, 0x04d43fff, 0x03843ff0, 0x03843ff0, 0x00000000, 0x00000000, 0x034d3ff0, 0x034d3ff0, 0x03433ff0, 0x03593ff0, 0x00000000},
													{0x0662,	0x04b004b0, 0x04b004b0, 0x04b004b0, 0x04b004b0, 0x04200420, 0x04200420, 0x00000000, 0x00000000, 0x09600960, 0x09600960, 0x0c600c60, 0x0c600c60, 0x00000000},
													{0x0663,	0x04b204b2, 0x04b204b2, 0x04b204b2, 0x04b204b2, 0x04220422, 0x04220422, 0x00000000, 0x00000000, 0x09620962, 0x09620962, 0x0c620c62, 0x0c620c62, 0x00000000},
													{0x066d,	0x81b50700, 0x81b50700, 0x81b50700, 0x81b50700, 0x81b50700, 0x81b50700, 0x00000000, 0x00000000, 0x81b50700, 0x81b50700, 0x81b50700, 0x81b50700, 0x00000000},
													{0x0613,	0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x00000000, 0x00000000, 0x40404040, 0x40404040, 0x40404040, 0x40404040, 0x00000000},
													{0x0614,	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
													{0x0646,	0x01a90000, 0x01a90000, 0x01a90000, 0x01a90000, 0x01a90000, 0x01a90000, 0x00000000, 0x00000000, 0x01a90000, 0x01a90000, 0x01a90000, 0x01000000, 0x00000000},
													{0x0647,	0x09b00000, 0x0af80000, 0x05800000, 0x05800000, 0x06b50000, 0x076d0000, 0x00000000, 0x00000000, 0x0a5e0000, 0x08b60000, 0x0c200000, 0x09ea0000, 0x00000000},
													{0x0648,	0x00f40000, 0x00f50000, 0x00790000, 0x00790000, 0x00950000, 0x00950000, 0x00000000, 0x00000000, 0x00ce0000, 0x00ce0000, 0x00960000, 0x00c80000, 0x00000000},
													{0x0649,	0x01f60000, 0x01f40000, 0x00f20000, 0x01f40000, 0x012b0000, 0x012c0000, 0x00000000, 0x00000000, 0x01900007, 0x01900000, 0x012e0005, 0x01900000, 0x00000000},
													{0x064a,	0x01900274, 0x01930275, 0x00600128, 0x01930275, 0x00920167, 0x00960167, 0x00000000, 0x00000000, 0x010601ef, 0x010801e8, 0x00ce0177, 0x010901e3, 0x00000000},
													{0x064c,	0x0a59023f, 0x0a59023f, 0x0a59023f, 0x0a59023f, 0x0f03022e, 0x0f01022d, 0x00000000, 0x00000000, 0x0d4c0368, 0x0d3c0372, 0x14300291, 0x0d560378, 0x00000000},
													{0x0682,	0x0000e000, 0x0000e000, 0x0000e000, 0x0000e000, 0x0000e000, 0x0000e000, 0x00000000, 0x00000000, 0x0000e000, 0x0000e000, 0x0000e000, 0x0000e000, 0x00000000},
													{0x0683,	0x01410386, 0x01410386, 0x01410386, 0x01410386, 0x0103036c, 0x0103036c, 0x00000000, 0x00000000, 0x01150366, 0x011c0370, 0x011e0374, 0x01100361, 0x00000000},
													{0x0684,	0x032d02b9, 0x032d02b9, 0x032d02b9, 0x032d02b9, 0x036c02da, 0x036c02da, 0x00000000, 0x00000000, 0x033402bb, 0x033d02bb, 0x034002ce, 0x034202b9, 0x00000000},
													{0x0685,	0x027c0210, 0x027c0210, 0x027c0210, 0x027c0210, 0x028e021f, 0x028e021f, 0x00000000, 0x00000000, 0x02800231, 0x02800231, 0x02910225, 0x028c0225, 0x00000000},
													{0x0686,	0x01c30179, 0x01c30179, 0x01c30179, 0x01c30179, 0x01d2016d, 0x01d2016d, 0x00000000, 0x00000000, 0x01e70171, 0x01e70171, 0x01da0188, 0x01d70183, 0x00000000},
													{0x0687,	0x01400385, 0x01400385, 0x01400385, 0x01400385, 0x010d010f, 0x010d010f, 0x00000000, 0x00000000, 0x01110366, 0x0114036e, 0x011e0374, 0x01100360, 0x00000000},
													{0x0688,	0x01440384, 0x01440384, 0x01440384, 0x01440384, 0x036a010d, 0x036a010d, 0x00000000, 0x00000000, 0x01110366, 0x0117036f, 0x011e0374, 0x01100360, 0x00000000},
													{0x0689,	0x033b02d2, 0x033b02d2, 0x033b02d2, 0x033b02d2, 0x036f039d, 0x036f0352, 0x00000000, 0x00000000, 0x036902c7, 0x032202b4, 0x033b02d2, 0x034b02e0, 0x00000000},
													{0x068a,	0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02cc0111, 0x02cc0111, 0x00000000, 0x00000000, 0x02860200, 0x02860200, 0x02000200, 0x02000200, 0x00000000},
													{0x0696,	0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000, 0x00000000, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000},
													{0x0697,	0x03000340, 0x03000340, 0x03000340, 0x03000340, 0x03800340, 0x03500320, 0x00000000, 0x00000000, 0x031e030e, 0x034f0308, 0x03400340, 0x03200310, 0x00000000},
													{0x0698,	0x031c0310, 0x031c0310, 0x031c0310, 0x031c0310, 0x03300330, 0x03100310, 0x00000000, 0x00000000, 0x03200319, 0x03220321, 0x03300330, 0x031c0310, 0x00000000},
													{0x0699,	0x032002d0, 0x032002d0, 0x032002d0, 0x032002d0, 0x03200320, 0x03100310, 0x00000000, 0x00000000, 0x03140303, 0x031402f9, 0x03300330, 0x03200300, 0x00000000},
													{0x069a,	0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02780200, 0x02780200, 0x00000000, 0x00000000, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000},
													{0x069b,	0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000, 0x00000000, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000},
													{0x069c,	0x03000340, 0x03000340, 0x03000340, 0x03000340, 0x020003a0, 0x02000330, 0x00000000, 0x00000000, 0x03400310, 0x030d0319, 0x03000340, 0x03300340, 0x00000000},
													{0x069d,	0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x03400200, 0x03100200, 0x00000000, 0x00000000, 0x029a02e7, 0x02ec0200, 0x02000200, 0x02000200, 0x00000000},
													{0x06a1,	0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000, 0x00000000, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000},
													{0x06a2,	0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000, 0x00000000, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000},
													{0x06a3,	0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000, 0x00000000, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000},
													{0x06a4,	0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000, 0x00000000, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000},
													{0x06a5,	0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000, 0x00000000, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000},
													{0x06a6,	0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000, 0x00000000, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000},
													{0x06a7,	0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000, 0x00000000, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000},
													{0x06a8,	0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000, 0x00000000, 0x02000200, 0x02000200, 0x02000200, 0x02000200, 0x00000000},
													{0x0622,	0x00a200ac, 0x00a200ac, 0x00a200ac, 0x00a200ac, 0x00a2006b, 0x00a2006b, 0x00000000, 0x00000000, 0x00bb00b4, 0x00ab00b4, 0x01040108, 0x00a200ac, 0x00000000},
													{0x0623,	0x00ac00ac, 0x00ac00ac, 0x00a200ac, 0x00a200ac, 0x0056005f, 0x0056005f, 0x00000000, 0x00000000, 0x009c00ab, 0x009f00a9, 0x01000100, 0x00ac00ac, 0x00000000},
													{0x0624,	0x00ac00ac, 0x00ac00ac, 0x00a200ac, 0x00a200ac, 0x0058006f, 0x0058006f, 0x00000000, 0x00000000, 0x00a100b6, 0x00a600a6, 0x01000100, 0x00ac00ac, 0x00000000},
													{0x0625,	0x00ac00ac, 0x00ac00ac, 0x00a200ac, 0x00a200ac, 0x00530064, 0x00530064, 0x00000000, 0x00000000, 0x00a300ae, 0x00ae00b2, 0x01000100, 0x00ac009b, 0x00000000},
													{0x0626,	0x00a804b3, 0x00a804b3, 0x00a804b3, 0x00a804b3, 0x00140045, 0x00140045, 0x00000000, 0x00000000, 0x009f04a0, 0x009804a0, 0x01000709, 0x00a804af, 0x00000000},
													{0x0627,	0x00a200ac, 0x00a200ac, 0x00a200ac, 0x00a200ac, 0x052f007f, 0x052f007f, 0x00000000, 0x00000000, 0x00a800b7, 0x00a800b6, 0x01000110, 0x00aa00ac, 0x00000000},
													{0x0628,	0x00ac00eb, 0x00ac00eb, 0x00ac00eb, 0x00ac00eb, 0x00c500bf, 0x00c500bf, 0x00000000, 0x00000000, 0x009b00a7, 0x009b00a8, 0x010000f9, 0x00ac00a3, 0x00000000},
													{0x0629,	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00b80370, 0x00b80370, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
													{0x0635,	0x0f770b09, 0x0ce3087d, 0x07bb05db, 0x06710440, 0x0a4e088b, 0x089706d2, 0x00000000, 0x00000000, 0x0e2c0335, 0x0a4103b9, 0x0d4b0790, 0x0c7803b6, 0x00000000},
													{0x0658,	0x10000e20, 0x10000e20, 0x10000e20, 0x10000e20, 0x08000e20, 0x08000e20, 0x00000000, 0x00000000, 0x08000d70, 0x08000d70, 0x08001110, 0x08000d70,	0x00000000}
													};

const UINT gnEnc_LV1Ea = sizeof(gnEncModeT_LV1)/sizeof(gnEncModeT_LV1[0]);
const UINT gnEnc_LV2Ea = sizeof(gnEncModeT_LV2)/sizeof(gnEncModeT_LV2[0]);	


void ISPM2 ModeAnalog(UINT anMode)		// 180308 LGH
{	// ANALOG config (CAUTION ! call 1tyme when mode was changed, FIXED function)
	// anMode - 0 : Analog OFF, 1 : CVBS, 2 : HD-Analog
#if(model_Aout==2)
	UNUSED_ARG(anMode);
	POWER_OFF_HDANA	
	POWER_OFF_CVBS
#else
	UINT i;
	// Adapt Table (Default - LV2 - LV1 - LV0)

	// Encoder Default Table
	for(i=0; i<gnTblIspDefaultEa; i++) SetIsp(gnTblIspDefault[i][0], gnTblIspDefault[i][1]);
	
	// HD Analog
	if (anMode >= MN_HD_T) {
		// Matching Format
		gbEncModeIndex = GetENC_ModeIndex();
		
		// Encoder LV2 Register Write
		SetENCLv2_RegW();
		
		// Encoder LV1 Register Write
		SetENCLv1_RegW();

		// Encoder Exception Setting
		SetEncExcepRegW();
	}

	// CVBS Test Output ---------------------------------------------------------------------------------------------------
	else if (anMode==MN_CVBS)	
	{
//		TxStrNoIRQ("CVBS Init ! ", 0, 0);
		SetCVBS();
	}
	// Analog Off
	else if	(anMode==MN_ANL_OFF) {
		POWER_OFF_HDANA	
		POWER_OFF_CVBS
		return;
	}

	// Encoder LV0
	if(gbEncParInit){
//			TxStrNoIRQ("Encoder Parameter Init ! ", 0, 0);
		ParSet(UpENC_CSTM, 0x0);
//		ENCLv0_TBuftoUBuf();	// Run once on parameter reset
		gbEncParInit = 0;
	}
	
	ENCLv0_UBuftoTBuf();		// User parameter buffer to tuning buffer
	ENCLv0_TBuftoUBuf();		// Tuning buffer buffer to User parameter buffer
	
//	gbUsrParSaveChk = 1;
		
	POWER_OFF_HDANA	
	POWER_OFF_CVBS
	
//	Y_LPF_ONw(0x0);		// 201231 LGH : More strong MOIRE but, increase sharpness
	Y_LPF_ONw(0x1);		// 201231 LGH : More strong MOIRE but, increase sharpness
#endif

}

BYTE ISPM2 GetENC_ModeIndex(void)
{
	BYTE bAnaModeIndex = 0;

	switch(MP(MpOutFps)){
		
#if(model_1M)
	case MN_1M_720p_25_30	:	bAnaModeIndex = ((MP(MpSysFreq)==MN_SYSFREQ_50)?(ENC_OUT_720P_25):(ENC_OUT_720P_30));		break;
	case MN_1M_720p_50_60	:	bAnaModeIndex = ((MP(MpSysFreq)==MN_SYSFREQ_50)?(ENC_OUT_720P_50):(ENC_OUT_720P_60));		break;										
	
#elif(model_2M)
	case MN_2M_720p_25_30	:	bAnaModeIndex = ((MP(MpSysFreq)==MN_SYSFREQ_50)?(ENC_OUT_720P_25):(ENC_OUT_720P_30));		break;
	case MN_2M_720p_50_60	:	bAnaModeIndex = ((MP(MpSysFreq)==MN_SYSFREQ_50)?(ENC_OUT_720P_50):(ENC_OUT_720P_60));		break;
	case MN_2M_1080p_25_30	:	bAnaModeIndex = ((MP(MpSysFreq)==MN_SYSFREQ_50)?(ENC_OUT_1080P_25):(ENC_OUT_1080P_30));	break;
	case MN_2M_1080p_50_60	:	bAnaModeIndex = ((MP(MpSysFreq)==MN_SYSFREQ_50)?(ENC_OUT_1080P_50):(ENC_OUT_1080P_60));	break;
	case MN_2M_1440p_25_30	:	bAnaModeIndex = ((MP(MpSysFreq)==MN_SYSFREQ_50)?(ENC_OUT_1440P_25):(ENC_OUT_1440P_30));	break;
	case MN_2M_1944p_125	:	bAnaModeIndex = (ENC_OUT_1944P_125);														break;
	case MN_2M_1944p_20		:	bAnaModeIndex = (ENC_OUT_1944P_20);															break;
	case MN_2M_1080p_291	:	bAnaModeIndex = (ENC_OUT_1080P_30);														break;
	case MN_2M_1080p_275	:	bAnaModeIndex = (ENC_OUT_1080P_30);															break;	
	
#elif(model_5M)
	case MN_4M_720p_25_30	:	bAnaModeIndex = ((MP(MpSysFreq)==MN_SYSFREQ_50)?(ENC_OUT_720P_25):(ENC_OUT_720P_30));		break;
	case MN_4M_1080p_25_30	:	bAnaModeIndex = ((MP(MpSysFreq)==MN_SYSFREQ_50)?(ENC_OUT_1080P_25):(ENC_OUT_1080P_30));	break;
	case MN_4M_1440p_25_30	:	bAnaModeIndex = ((MP(MpSysFreq)==MN_SYSFREQ_50)?(ENC_OUT_1440P_25):(ENC_OUT_1440P_30));	break;
	case MN_5M_1944p_125	:	bAnaModeIndex = (ENC_OUT_1944P_125);														break;
	case MN_5M_1944p_20		:	bAnaModeIndex = (ENC_OUT_1944P_20);															break;
#else
#endif
	default 				: 	bAnaModeIndex = 0; 																			break;
	}
	return bAnaModeIndex;
}


//*******************************************************
// Function : Parameter LV0 
// Infor : Setting that depends on the type of DVR
//----------------------------------------
void ISPM2 SetENCLv0_RegW(void)
{
	// Encoder LV0 register write for user parameter control
	// Processing time : 37us
	static BYTE bEncCstmBuf = 0xee;

	if(bEncCstmBuf != UP(UpENC_CSTM))		ENCLv0_TBuftoUBuf();
	bEncCstmBuf = UP(UpENC_CSTM);
	
	// Register write function
	ENC_RYGAINPw(EGP(UpENC_RYGAINP)); 	
	ENC_RYGAINNw(EGP(UpENC_RYGAINN)); 	
	ENC_BYGAINPw(EGP(UpENC_BYGAINP)); 	
	ENC_BYGAINNw(EGP(UpENC_BYGAINN)); 	
                
	ENC_RYHUEPw (EGP(UpENC_RYHUEP));	
	ENC_RYHUENw (EGP(UpENC_RYHUEN));	
	ENC_BYHUEPw (EGP(UpENC_BYHUEP));	
	ENC_BYHUENw (EGP(UpENC_BYHUEN)); 	

	WHITE_LVw	(EGP(UpWHITE_LV));	
	BLANK_LVw	(EGP(UpBLANK_LV));		
//	PEDESTAL_LVw(EGP(UpPEDESTAL_LV));		//Apply register in AE function

	FSC_TGTw	(EGP(UpFSC_TGT));

	Y_MGAINw	(EGP(UpY_MGAIN));		
	CB_MGAINw	(EGP(UpCB_MGAIN));		
	CR_MGAINw	(EGP(UpCR_MGAIN));			
	
	CB_BSTw		(EGP(UpCB_BST));	
	CR_BSTw		(EGP(UpCR_BST));		
	
	HSC_Kw		(EGP(UpHSC_K));	
	HLOCK_CATw	(EGP(UpHLOCK_CAT));	
	VLOCK_CAT_EVw(EGP(UpVLOCK_CAT_EV));
	VLOCK_CAT_ODw(EGP(UpVLOCK_CAT_OD));

	CRX_AUTO_CATw(EGP(UpCRX_AUTO_CAT));
	CRX_HPOSEVSw(EGP(UpCRX_HPOSEVS));
	CRX_HPOSEVEw(EGP(UpCRX_HPOSEVE));

//	CRX_BITRATEw(EGP(UpCRX_BITRATE));
	// 210426 HTY : Update only when the value changes
	static WORD wCRX_BITRATE_Buf=0xffff;
	if((EGP(UpCRX_BITRATE))!=wCRX_BITRATE_Buf) CRX_BITRATEw(EGP(UpCRX_BITRATE));
	wCRX_BITRATE_Buf=EGP(UpCRX_BITRATE);
	
}

void ISPM2 ENCLv0_TBuftoUBuf(void)
{
	ESP(UpENC_RYGAINP, 	(BYTE)EST(ENC_RYGAINP));
	ESP(UpENC_RYGAINN, 	(BYTE)EST(ENC_RYGAINN));
	ESP(UpENC_BYGAINP, 	(BYTE)EST(ENC_BYGAINP));
	ESP(UpENC_BYGAINN, 	(BYTE)EST(ENC_BYGAINN));
                                         
	ESP(UpENC_RYHUEP,  	(BYTE)EST(ENC_RYHUEP));
	ESP(UpENC_RYHUEN,  	(BYTE)EST(ENC_RYHUEN));
	ESP(UpENC_BYHUEP,  	(BYTE)EST(ENC_BYHUEP));
	ESP(UpENC_BYHUEN,  	(BYTE)EST(ENC_BYHUEN));

	ESP(UpWHITE_LV, 	(WORD)EST(WHITE_LV));
	ESP(UpBLANK_LV, 	(WORD)EST(BLANK_LV));
	ESP(UpPEDESTAL_LV, 	(WORD)EST(PEDESTAL_LV));

	ESP(UpFSC_TGT, 	 	(UINT)EST(FSC_TGT));
	
	ESP(UpY_MGAIN, 	 	(WORD)EST(Y_MGAIN));
	ESP(UpCB_MGAIN, 	(WORD)EST(CB_MGAIN));
	ESP(UpCR_MGAIN, 	(WORD)EST(CR_MGAIN));
                                         
	ESP(UpCB_BST, 	 	(WORD)EST(CB_BST));
	ESP(UpCR_BST, 	 	(WORD)EST(CR_BST));
                                         
	ESP(UpHSC_K, 		(WORD)EST(HSC_K));
	ESP(UpHLOCK_CAT, 	(WORD)EST(HLOCK_CAT));
	ESP(UpVLOCK_CAT_EV,	(WORD)EST(VLOCK_CAT_EV));
	ESP(UpVLOCK_CAT_OD,	(WORD)EST(VLOCK_CAT_OD));
                                         
	ESP(UpCRX_AUTO_CAT,	(WORD)EST(CRX_AUTO_CAT));
	ESP(UpCRX_HPOSEVS, 	(WORD)EST(CRX_HPOSEVS));
	ESP(UpCRX_HPOSEVE, 	(WORD)EST(CRX_HPOSEVE));
	ESP(UpCRX_BITRATE, 	(WORD)EST(CRX_BITRATE));
}

void ISPM2 ENCLv0_UBuftoTBuf(void)
{
	ENC_LV0_MEMCPY(
		gAnEncLv0	,
		EGP(UpENC_RYGAINP ),
		EGP(UpENC_RYGAINN ),
		EGP(UpENC_BYGAINP ),
		EGP(UpENC_BYGAINN ),
		EGP(UpENC_RYHUEP  ),
		EGP(UpENC_RYHUEN  ),
		EGP(UpENC_BYHUEP  ),
		EGP(UpENC_BYHUEN  ),
		EGP(UpWHITE_LV    ),
		EGP(UpBLANK_LV    ),
		EGP(UpPEDESTAL_LV ),
		EGP(UpFSC_TGT     ),
		EGP(UpY_MGAIN     ), 
		EGP(UpCB_MGAIN    ),
		EGP(UpCR_MGAIN    ),	
		EGP(UpCB_BST      ),
		EGP(UpCR_BST      ),
		EGP(UpHSC_K       ),
		EGP(UpHLOCK_CAT   ),
		EGP(UpVLOCK_CAT_EV),
		EGP(UpVLOCK_CAT_OD),
		EGP(UpCRX_AUTO_CAT),
		EGP(UpCRX_HPOSEVS ),
		EGP(UpCRX_HPOSEVE ),
		EGP(UpCRX_BITRATE )
	);
}

//*******************************************************
// Function : Parameter LV1
// Infor : Setting that depends on the type of DVR
//----------------------------------------
void ISPM2 SetENCLv1_RegW(void)
{
	UINT i = 0;
	// Encoder LV1 Register Write
	for(i=0; i<gnEnc_LV1Ea; i++) SetIsp(gnEncModeT_LV1[i][0], EDT_LV1(i)); // Format Table	
}

//*******************************************************
// Function : Parameter LV2
// Infor : Setting that depends on the type of DVR
//----------------------------------------
void ISPM2 SetENCLv2_RegW(void)
{
	UINT i = 0;
	// Encoder LV2 Register Write
	for(i=0; i<gnEnc_LV2Ea; i++) SetIsp(gnEncModeT_LV2[i][0], EDT_LV2(i)); // Format Table
}

void ISPM2 SetEncExcepRegW(void)
{
	// setting for 2M to 5M Upscale
	#if(model_2M)

	// Set common
	if(MODE_5M_ON){
		HLOCKL_POSw((gbModeWdrOn_L)?(0x1A):(0x18));
		HLOCKS_POSw((gbModeWdrOn_L)?(0x1A):(0x0 ));
	}
	switch(MP(MpAnlForm))
	{
		case MN_HD_T :
			if(gbEncModeIndex == ENC_OUT_1944P_125){
				VLOCKL_POSw((gbModeWdrOn_L)?(0x0):(0xe));
				VLOCKS_POSw(0x0);
				VSPIw((gbModeWdrOn_L)?(0x1):(0x0)); 
				VWIw(0x3d8); 
				VLOCKO_POSw((gbModeWdrOn_L)?(0x16):(0x18)); 

				//Encoder
				VSPEw((gbModeWdrOn_L)?(0x18):(0x14));		//Top black Masking
				VWEw((gbModeWdrOn_L)?(0x78D):(0x7C6));		//Bottom black masking
			}
			
			else if(gbEncModeIndex == ENC_OUT_1944P_20){
				VLOCKL_POSw((gbModeWdrOn_L)?(0x0):(0x8));
				VLOCKS_POSw(0x0);
				VSPIw((gbModeWdrOn_L)?(0x1):(0x0)); 
				VWIw(0x3ce); 
				VLOCKO_POSw((gbModeWdrOn_L)?(0x16):(0x19)); 

				//Encoder
				VSPEw((gbModeWdrOn_L)?(0x19):(0x15));		//Top black Masking
				VWEw((gbModeWdrOn_L)?(0x779):(0x7B2));		//Bottom black masking
				 
				ACT_VEP_EVw(ACT_VEP_EVr-0x6);
			}
			break;
			
		case MN_HD_C :
			if(gbEncModeIndex == ENC_OUT_1944P_20) {
				VLOCKL_POSw((gbModeWdrOn_L)?(0x0):(0xe));
				VLOCKS_POSw(0x0);
				VSPIw((gbModeWdrOn_L)?(0x1):(0x0)); 
				VWIw(0x3ce); 
				VLOCKO_POSw((gbModeWdrOn_L)?(0x10):(0x14)); 

				//Encoder
				VSPEw((gbModeWdrOn_L)?(0x1D):(0x18));		//Top black Masking
				VWEw((gbModeWdrOn_L)?(0x77E):(0x7C6));		//Bottom black masking
			} 
			break;
			
		case MN_HD_A :
			if(gbEncModeIndex == ENC_OUT_1944P_125){
				VLOCKL_POSw((gbModeWdrOn_L)?(0x0):(0xe));
				VLOCKS_POSw(0x0);
				VSPIw((gbModeWdrOn_L)?(0x1):(0x0)); 
				VWIw(0x3d8); 
				VLOCKO_POSw((gbModeWdrOn_L)?(0xD):(0x12)); 

				//Encoder
				VSPEw((gbModeWdrOn_L)?(0x1E):(0x14));		//Top black Masking
				VWEw((gbModeWdrOn_L)?(0x77B):(0x7C6));		//Bottom black masking
				
			}
			else if(gbEncModeIndex == ENC_OUT_1944P_20) {
				VLOCKL_POSw((gbModeWdrOn_L)?(0x0 ):(0x8 ));
				VLOCKS_POSw(0x0);
				VSPIw((gbModeWdrOn_L)?(0x1):(0x0)); 
				VWIw(0x3ce); 
				VLOCKO_POSw((gbModeWdrOn_L)?(0x16):(0x19)); 

				//Encoder
				VSPEw((gbModeWdrOn_L)?(0x19):(0x15));		//Top black Masking
				VWEw((gbModeWdrOn_L)?(0x779):(0x7B2));		//Bottom black masking
				 
				ACT_VEP_EVw(ACT_VEP_EVr-0x6);
			} 
			break;

		default : 
			break;
	}
	#endif
}


//*******************************************************
// Function : Parameter Encoder (CVBS)
// Infor : Image tuning CVBS output
//----------------------------------------

void ISPM2 SetCVBS(void)
{	//Configuration CVBS output 
	//CVBS can't be output simultaneously with SDI.

	static WORD wVLOCKL_POS = 0x0;
	UINT i = 0;	
	
	for(i=0; i<gnTblCvbsPreEa; i++) 	SetIsp(gnTblCvbsPre[i][0], gnTblCvbsPre[i][1+MP(MpSysFreq)]);		// Pre
	for(i=0; i<gnTblCvbsPostEa; i++) 	SetIsp(gnTblCvbsPost[i][0], gnTblCvbsPost[i][1+MP(MpSysFreq)]);		// Post
	for(i=0; i<gnTblCvbsEncEa; i++) 	SetIsp(gnTblCvbsEnc[i][0], gnTblCvbsEnc[i][1+MP(MpSysFreq)]);		// Encoder
	for(i=0; i<gnTblModeCvbsEa; i++) 	SetIsp(gnTblModeCvbs[i][0], gnTblModeCvbs[i][1+MP(MpSysFreq)]);		// Encoder

	wVLOCKL_POS = VLOCKL_POSr;
	VLOCKL_POSw((gbModeWdrOn_L)?(wVLOCKL_POS-1):(wVLOCKL_POS));
	
	ParSet(UpDKX, UpDKX);
	ParSet(UpDKY, UpDKY);

	ParSet(UpDS_HOFF, UpDS_HOFF);
	ParSet(UpDS_VOFF, UpDS_VOFF);
}

void ISPM2 SetENC_CVBS_RegW(void)
{	
	DKXw(UP(UpDKX));
	DKYw(UP(UpDKY));

	DS_HOFFw(UP(UpDS_HOFF));
	DS_VOFFw(UP(UpDS_VOFF));

	// Analog burst-off option at BW mode ------------------------------------------
	if (gnTdnChkOut==TDN_NIT)	AY_OSELw(2);	// B&W
	else 						AY_OSELw(0);	// COLOR
}

void ISPM2 ModeCvbsMnConfig(void)
{	// Functions for remembering previous modes when switching to CVBS

	if(MP(MpAnlMode)==MN_CVBS_ON){
		// Save buffer before cvbs mode change
		gbModeBufBefore	= MP(MpOutFps);
		gbModeSdiBufBefore = MP(MpSdiForm);
		
		MP(MpOutFps)	= MODE_CVBS_OUT_FPS;
//		gbModeBufOutFps = MP(MpOutFps);
		gbModeBufOutFps = 0;

		MP(MpSdiForm)	= MN_SDI_OFF;
		gbModeBufSdiForm = MP(MpSdiForm);
	}
	
	else{
		if(gbModeChgHotKey){
			MP(MpOutFps)	= gbModeBufBefore;
			gbModeBufOutFps = MP(MpOutFps);
			
			MP(MpSdiForm)	= gbModeSdiBufBefore;
			gbModeBufSdiForm = MP(MpSdiForm);
		}
	}
}

#endif

