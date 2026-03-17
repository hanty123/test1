/* **************************************************************************
 File Name	: 	app_comm.c
 Description	:	Communication interface
 Designer		:	Kim, Sunghoon
 Date		:	14. 6. 18
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

//-------------------------------------------------------------------------------------------------
// Variables
BYTE	gbETX = 0;
BYTE	gbRxStg = 0;
WORD	gwRxAddr = 0;
UINT	gnRxData = 0;

//#if model_UccD == 1 || model_Uart2 == 1
	BYTE	gbETX1 = 0;
	BYTE	gbRxStg1 = 0;
	WORD	gwRxAddr1 = 0;
	UINT	gnRxData1 = 0;

	#define SetPnt(TYPE,NAME)	TYPE *p##NAME = (bCh == 1) ? &g##NAME##1 : &g##NAME
	#define P_ETX				(*pbETX)
	#define P_STG				(*pbRxStg)
	#define P_ADDR				(*pwRxAddr)
	#define P_DATA				(*pnRxData)

//#else
//	#define SetPnt(...)
//	#define P_ETX				gbETX
//	#define P_STG				gbRxStg
//	#define P_ADDR				gwRxAddr
//	#define P_DATA				gnRxData
//#endif

#define SetEnd() {\
		P_STG = 0;\
		P_ADDR = 0;\
		P_DATA = 0;\
		P_ETX = 0;\
	}

//BYTE gbWinChar = 0;													// Window character
union uFLOAT gnTxGrp[8] = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0} };	// Graphic data

UINT gnRxPar[32] = {
					0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	// Parameter data (Regulate with logic address .CAUTION)
					0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
					};

//UINT gnDownOn = 0;										// PC_CMD_DOWNLOAD

// 20171205 HTY
//extern BYTE gbSAF_Tele,gbSAF_Wide,gbSAF_Near,gbSAF_Far;	
extern BYTE gbMAF_Tele,gbMAF_Wide,gbMAF_Near,gbMAF_Far;	
extern BYTE gbUCCKeyOn, gbExUCCKeyOn;	               
BYTE  gbExUccKeyBuf=0;

//-------------------------------------------------------------------------------------------------
#if 0
int ISPM UartIsEmpty(void)
{
	int			iEmpty;

	DI();

	if(gtUartQue.wRxLen > 0)	iEmpty = 0;
	else						iEmpty = 1;

	EI();

	return (iEmpty);
}

BYTE ISPM UartGetByte(BYTE* apbErr)
{
	BYTE		bChar;

	DI();

	if(gtUartQue.wRxLen > 0){
		gtUartQue.wRxLen--;
		bChar = *gtUartQue.pbRxTail++;
		if( gtUartQue.pbRxTail == &gtUartQue.bRxQue[UART_BUF_SIZE-1]){
			gtUartQue.pbRxTail  = &gtUartQue.bRxQue[0];
		}
		*apbErr = UART_NO_QUE_ERR;
		//gtUartQue.wRxLen--;
	}
	else{
		bChar = 0;
		*apbErr = UART_RX_QUE_EMPTY;
	}

	EI();

	return (bChar);
}
#endif

void TxStrNoIRQ(const char* apbStr0, UINT anVal, UINT anValLen)
{
	//while(gtUartQue.wTxLen || UART0_TX_IRQ_EN) { NOP4 };
	if(gtUartQue.wTxLen || UART0_TX_IRQ_EN) {
		UINT nStNum;
		const UINT nSt = GetSt(&nStNum);
		SetStEnaIrq(nSt);
		while(gtUartQue.wTxLen || UART0_TX_IRQ_EN) { NOP4 };
		SetSt(nSt,&nStNum);
	}

	char bStr[9];
	const UINT nValLen = MIN(8,anValLen);
	const BYTE bLen = ((apbStr0) ? strlen(apbStr0) : 0) + nValLen + 2;

	if(nValLen) uint2strh(bStr, anVal, nValLen);

	Uart_Tx(PC_STX);
	Uart_Tx(PC_CMD_STR);
 	Uart_Tx(bLen);

	if(apbStr0) uart_str(apbStr0);
	if(nValLen) uart_str(bStr);

	Uart_Tx('\r');
	Uart_Tx('\n');

	Uart_Tx(PC_ETX);
}

void TxStrDecNoIRQ(const char* apbStr0, UINT anVal, UINT anValLen)
{
	//while(gtUartQue.wTxLen || UART0_TX_IRQ_EN) { NOP4 };
	if(gtUartQue.wTxLen || UART0_TX_IRQ_EN) {
		UINT nStNum;
		const UINT nSt = GetSt(&nStNum);
		SetStEnaIrq(nSt);
		while(gtUartQue.wTxLen || UART0_TX_IRQ_EN) { NOP4 };
		SetSt(nSt,&nStNum);
	}

	char bStr[11];
	const UINT nValLen = MIN(10,anValLen);
	const BYTE bLen = ((apbStr0) ? strlen(apbStr0) : 0) + nValLen + 2;

	if(nValLen) int2str(bStr, anVal, nValLen);

	Uart_Tx(PC_STX);
	Uart_Tx(PC_CMD_STR);
 	Uart_Tx(bLen);

	if(apbStr0) uart_str(apbStr0);
	if(nValLen) uart_str(bStr);

	Uart_Tx('\r');
	Uart_Tx('\n');

	Uart_Tx(PC_ETX);
}

void ISPM TxErr(void)
{
	UartTxByte(PC_STX);
	UartTxByte(PC_CMD_ERR);
	UartTxByte(PC_ETX);
}

void ISPM TxAck(void)
{
	UartTxByte(PC_STX);
	UartTxByte(PC_CMD_ACK);
	UartTxByte(PC_ETX);
}

void ISPM TxReg(UINT anAddr, UINT anData)
{
	UartTxByte(PC_STX);
	UartTxByte(PC_CMD_REGR);

	UartTxByte(anAddr>> 8);
	UartTxByte(anAddr>> 0);

	UartTxByte(anData>>24);
	UartTxByte(anData>>16);
	UartTxByte(anData>> 8);
	UartTxByte(anData>> 0);

	UartTxByte(PC_ETX);
}

int  giTxGrpOn = 0;

void ISPM TxGrpFnc(void)
{
	int		i;

	UartTxByte(PC_STX);
	UartTxByte(PC_CMD_GRP);

	for(i=0; i<GRP_NUMBER; i++){
		UartTxByte(gnTxGrp[i].m_UINT>>24);
		UartTxByte(gnTxGrp[i].m_UINT>>16);
		UartTxByte(gnTxGrp[i].m_UINT>> 8);
		UartTxByte(gnTxGrp[i].m_UINT>> 0);
	}

	UartTxByte(PC_ETX);
}

void ISPM TxStr(const char* apbStr0, UINT anVal, UINT anValLen)
{
	char bStr[9];
	const UINT nValLen = MIN(8,anValLen);
	const BYTE bLen = ((apbStr0) ? strlen(apbStr0) : 0) + nValLen + 2;

	if(nValLen) uint2strh(bStr, anVal, nValLen);

	UartTxByte(PC_STX);
	UartTxByte(PC_CMD_STR);
 	UartTxByte(bLen);

	if(apbStr0) UartTxStr(apbStr0);
	if(nValLen) UartTxStr(bStr);

	UartTxByte('\r');
	UartTxByte('\n');

	UartTxByte(PC_ETX);
}

void ISPM TxStrDec(const char* apbStr0, UINT anVal, UINT anValLen)
{
	char bStr[11];
	const UINT nValLen = MIN(10,anValLen);
	const BYTE bLen = ((apbStr0) ? strlen(apbStr0) : 0) + nValLen + 2;

	if(nValLen) int2str(bStr, anVal, nValLen);

	UartTxByte(PC_STX);
	UartTxByte(PC_CMD_STR);
 	UartTxByte(bLen);

	if(apbStr0) UartTxStr(apbStr0);
	if(nValLen) UartTxStr(bStr);

	UartTxByte('\r');
	UartTxByte('\n');

	UartTxByte(PC_ETX);
}

void ISPM TxPar(const UINT anAddr, BYTE abData)
{
	UartTxByte(PC_STX);
	UartTxByte(PC_CMD_PARR);					// Cmd

	UartTxByte(anAddr>> 8);						// Addr[15: 8]
	UartTxByte(anAddr>> 0);						// Addr[ 7: 0]

	UartTxByte(abData>> 0);						// Data[ 7: 0]

	UartTxByte(PC_ETX);							// ETX
}

#if (model_Par==1)

BYTE	gbParOn = 0x0;
BYTE 	gbParInitSeq = 0x0;

void ISPM RxPar(const int aiWrite)
{
	if(aiWrite && (gbParOn == 0xFF)) {
		if(UP_START < gwRxAddr && gwRxAddr < UP_END) {
			gbUsrParTbl[gwRxAddr] = gnRxData;
			UsrParSet(gwRxAddr, 0);
		}
	}

	if(gbParOn != 0xFF) {
		TxPar(0xFFFF, 0);
	}
	else if(gwRxAddr == 0xFFFF) {
		TxPar(UP_END, gbUsrParTbl[UP_END]);
	}
	else if(gwRxAddr < USR_PAR_EA){
		TxPar(gwRxAddr, gbUsrParTbl[gwRxAddr]);
	}
	else {
		TxPar(gwRxAddr, 0);
	}
}

void ISPM TxParK(const BYTE abVal)
{
	UartTxByte(PC_STX);
	UartTxByte(PC_CMD_PARK);					// Cmd
	UartTxByte(abVal);
	UartTxByte(PC_ETX);							// ETX
}

void ISPM RxParK(void)
{
	#define PW_CONTINUE		3

	if(gbParOn < PW_CONTINUE || gbParOn == 0xFF)
	{
		if(gnRxData == model_ParID) {
			gbParOn = 0xFF;
			TxParK(1);
			TxStr("Parameter Enable On ", 0, 0);

			gbParInitSeq = 0x1;
		}
		else {
			if(gbParOn == 0xFF) gbParOn = 0;
			gbParOn++;
			TxParK(0);
			TxStr("Parameter ID Error...", gbParOn, 1);
		}
	}

	if(gbParOn == PW_CONTINUE)
	{
		gbParOn++;

		gbUsrParTbl[UP_START]		= (BYTE)(((~UP_DATA_ID)>>8)&0xff);
		gbUsrParTbl[UP_END]			= (BYTE)(((~UP_DATA_ID))&0xff);
		gbUsrParSaveChk = 1;
		TxStr("Parameter Reset !!!", 0, 0);
	}
	else if(gbParOn > PW_CONTINUE && gbParOn != 0xFF)
	{
		TxParK(0);
	}
}

void UpReset(void)
{
	gbParOn = PW_CONTINUE;
	RxParK();
}

void ISPM TxEepDone(void)
{
	UartTxByte(PC_STX);
	UartTxByte(PC_CMD_EEPR);					// Cmd
	UartTxByte(PC_ETX);							// ETX
}

void ISPM TxParSave(void)
{
	gbUsrParSaveChk = 1;		// EN778
	TxEepDone();
}

void ISPM TxParRead(void)
{
	gbUsrParReadChk = 1;		// EN778
	TxEepDone();
}

void ISPM TxParInitAll(void)
{
	UINT i;
	static BYTE bTransState = 0x0;

	#define UP_DATA_TRANS_SIZE	100
	#define DATA_MOK	(UP_END_REAL / UP_DATA_TRANS_SIZE)
	#define DATA_MOD	(UP_END_REAL % UP_DATA_TRANS_SIZE)

	
	if(gbParInitSeq){
			
		if(bTransState==0x0){
			UartTxByte(PC_STX);				// STX
			UartTxByte(PC_CMD_PAR_ALL);		// Parameter All transfer to PC
			bTransState++;
		}
		else if(bTransState <= DATA_MOK){ 
			for(i = 0; i < UP_DATA_TRANS_SIZE; i++)		UartTxByte(gbUsrParTbl[(UP_DATA_TRANS_SIZE*(bTransState-1))+i]);
			bTransState++;
		}
		else{
			for(i = 0; i < DATA_MOD; i++)				UartTxByte(gbUsrParTbl[(DATA_MOK*UP_DATA_TRANS_SIZE)+i]);
			
			UartTxByte(PC_ETX);				// ETX
			gbParInitSeq = 0;
			bTransState = 0;
		}
	}
	else			return;
}

#else

void UpReset(void)
{
}

#endif

void ISPM RxAddr(const int aiWrite)
{
	const int iRxAddr = gwRxAddr;

	#define SET_ADDR(ADDR_START, ADDR_END, WRITE_CMD, READ_CMD, READ_DATA)	\
		if((int)(ADDR_START) <= iRxAddr && iRxAddr < (int)(ADDR_END)) {\
			const WORD wAddr = iRxAddr - (ADDR_START);\
			UNUSED_ARG(wAddr);\
			if(aiWrite) { WRITE_CMD; }\
			READ_CMD\
			TxReg(iRxAddr, (READ_DATA));}


	SET_ADDR(0x0, BASE_SENS,				// ISP : 0x0000 ~ 0x2fff
		// ISP Write Code
		SetIsp(wAddr, gnRxData);

		GRP3 = wAddr;
		GRP4 = gnRxData;
		GRP7 = GetIsp(wAddr);
		,
		// ISP Read Code
		,
		
		GetIsp(wAddr))
	SET_ADDR(BASE_SENS, BASE_EXT_CHIP,			// Sensor : 0x3000 ~ 0x4ffff
		// Sensor Write Code
		//TxStrNoIRQ("SetSens:", wAddr, 2);
		//TxStrNoIRQ("Data:", gnRxData, 8);

//	  	SetSens(0, wAddr, gnRxData);
//		SetSens(0, (BASE_SENS+wAddr), gnRxData);
	  #if((model_Onsemi)||(model_Glxcore))
		SetSens((wAddr+PAR00), gnRxData);
	  #elif(model_Omni)
	  	#if((model_Sens==SENS_OS02H10)||(model_Sens==SENS_OS02D20))
		SetSens(0xfd, PAR00); // Page Address
		SetSens((wAddr/*+PAR00*/), gnRxData);
		SetSens(0x1,  0x1); // Mirror, Flip, Gain, Shutter Update Enable
		#else
		SetSens((wAddr+PAR00), gnRxData);
		#endif
	  #elif(model_Pxpls)
//	  	SetSens(0x03, PAR00);			//Bank Address
		SetSens(wAddr, gnRxData);
	  #else
		SetSens((BASE_SENS+wAddr), gnRxData);
	  #endif
		,
		// Sensor Read Code
		//TxStrNoIRQ("GetSens:", wAddr, 8);
		//const UINT nBuf = GetSens(0,wAddr);
		BYTE bData = 0;
	#if model_Pxpls
	  	SetSens(0x03, PAR00);
	  	bData = GetSens(wAddr);
	#elif((model_Sens==SENS_OS02H10)||(model_Sens==SENS_OS02D20))
		SetSens(0xfd, PAR00); // Page Address
		bData = GetSens(wAddr);
	#else
		UNUSED_ARG(bData);
	#endif
		,
	  #if ((model_Pana)||(model_Onsemi)||(model_Glxcore))
		GetSens((wAddr+PAR00))
	  #elif(model_Omni)
	  	#if((model_Sens==SENS_OS02H10)||(model_Sens==SENS_OS02D20))
		bData
		#else
		GetSens((wAddr+PAR00))
		#endif
	  #elif model_Pxpls
	  	bData
	  #else
		GetSens((BASE_SENS+wAddr))
	  #endif
		/*nBuf*//*0x0*//* =Dummy */)

#if(model_I2C_ch1==2)
	SET_ADDR(BASE_EEPROM, BASE_MICOM_PAR,	// EEPROM : 0x6000 ~ 0x7fff
		// Sensor Write Code
		eep_write(wAddr, gnRxData);
		,
		// Sensor Read Code
		BYTE bBuf = 0;
		eep_read(wAddr, &bBuf, 1);
		,
		bBuf)
#endif

	SET_ADDR(BASE_MICOM_PAR, BASE_MICOM_PAR + numberof(gnRxPar),	// Micom Para : 0x8000 ~ 0x8020
		// Sensor Write Code
		gnRxPar[wAddr] = gnRxData;

		/*sfls_erase_sect(0x7E000);
		SfWrEn;
		sfw8(wAddr + (FLASH_SECT_USER_STT*FLASH_SECT_SIZE), gnRxData);
		SfWrDis;*/

		,
		// Sensor Read Code
		,
		gnRxPar[wAddr]
		//gbUsrParTbl[wAddr]
		//sfr8(0x7F000)
		//sfr8(wAddr + (FLASH_SECT_USER_STT*FLASH_SECT_SIZE))
		)
}

void ISPM RxMenuWrite(void)
{
	if(gwRxAddr < 0x280)
	{
		MP(gwRxAddr) = (BYTE)(gnRxData&0xff);

		if(gwRxAddr == 0x1D/*MpLanguageSel*/)	// 0x1D���� I2C Master�� ���� �����ؾ� ��
		{
#if 1
			SetFontChg();
#else
			gbMenuFlash[gwRxAddr] = (BYTE)(gnRxData&0xff);
			OsdClearAll();

			FONT_ONw(0x0);
			POREG_ENw(0x1);
			WaitVdi();

			SetFontChg();

			WaitVdi();
			FONT_ONw(0x1);

			gbChgMenuMode = gbMenuMode;
#endif
		}
	}
	else
	{
		switch(gwRxAddr)
		{
			//case 0x280 :	gbMnFaOn = (BYTE)(gnRxData&0xff);								break;	//FOCUS ADJ
			case 0x281 :	gbMnPvcCfg(MP(MpPvcZone))->bAction = (BYTE)(gnRxData&0xff);			break;	//ZONE DISP
			case 0x282 :	gbMnPvcCfg(MP(MpPvcZone))->bPosX = (BYTE)(gnRxData&0xff);			break;	//H-POS
			case 0x283 :	gbMnPvcCfg(MP(MpPvcZone))->bPosY = (BYTE)(gnRxData&0xff);			break;	//V-POS
			case 0x284 :	gbMnPvcCfg(MP(MpPvcZone))->bSizX = (BYTE)(gnRxData&0xff);			break;	//H-SIZE
			case 0x285 :	gbMnPvcCfg(MP(MpPvcZone))->bSizY = (BYTE)(gnRxData&0xff);			break;	//V-SIZE
			case 0x28B :	MenuReset(); MenuResetFnc();											break;	//RESET
#if 1
			default : break;
#else
			case 0x28C :	gbParSaveOn = 1;	ExitMenu();									break;	//MENU_EXIT
			case 0x28D :	//SHADING DET
				if(((BYTE)(gnRxData&0xff)) == 1)
				{
					gbMnShdDet = 1;
					gbMnShading = 0;
					gbMnOutFormat = MN_FOMT_1080;
					MenuOff();
				}
				break;
			case 0x28E :	//DEFECT DET
				if(((BYTE)(gnRxData&0xff)) == 1)
				{
					gbMnDefDet = 1;
					InitMenuSize();
				}
				break;
			case 0x28F :	//DEFETCT DET_DEFECT DET
				if(((BYTE)(gnRxData&0xff)) == 1)
				{
					gbDefCnt = 4;
				}
				break;
			case 0x290 :
				if(((BYTE)(gnRxData&0xff)) == 1)
				{
					for(i=1; i<FLASH_REG_EA; i++) {
						gbMenuDef[i] = gbMenuFlash[i];
					}

					#if model_Save
						SfWrite(FLASH_SECT_DEF_STT*FLASH_SECT_SIZE, gbMenuDef, FLASH_REG_EA);
			    	#else
						I2cWrEep(I2C_EEP_DEF_STT, gbMenuDef, FLASH_REG_EA);
					#endif
				}
				break;
			case 0x291 :	gbParSaveOn = 1;	ExitMenu(); 									break;	//SETUP_EXIT
#endif
		}
	}
}

#define Protocol_EXSDI 0

int ISPM RxPD(const BYTE bCh, const BYTE bIn)
{	
	UNUSED_ARG(bCh);
	BYTE bEX_UCC_DOWN=0;
	SetPnt(WORD, wRxAddr);
	SetPnt(UINT, nRxData);
	 
	#if(!Protocol_EXSDI)
	BYTE crc = 0;
	crc += (P_ADDR&0xFF);
	crc += ((P_DATA>>24)&0xFF);	// Command 1
	crc += ((P_DATA>>16)&0xFF);	// Command 2 (Zoom & Pan & Tilt)
	crc += ((P_DATA>>8)&0xFF);		// Pan Speed
	crc += ((P_DATA>>0)&0xFF);		// Tilt Speed
	if(crc != bIn) 	return 1;

	#else
	BYTE CAM_ID;
	BYTE Command_1;
	BYTE Command_2;
	BYTE Data_1;
	BYTE Data_2;

	CAM_ID = (P_ADDR&0xFF);
	Command_1 = ((P_DATA>>24)&0xFF);
	Command_2 = ((P_DATA>>16)&0xFF);
	Data_1 = ((P_DATA>>8)&0xFF);
	Data_2 = ((P_DATA>>0)&0xFF);

	BYTE crc = 0;
	crc = CAM_ID + Command_1 + Command_2 + Data_1 + Data_2;
	#endif
	
	if(crc != bIn){
		TxStrNoIRQ("bIn ",bIn,3);
		TxStrNoIRQ("crc ",crc,3);
	return 1;}

	if(P_ADDR != MP(MpCamID)) return 1;
    
#if STR_PELCO_DATA == 1
	gbPDcnt++;
	gwPDfld = gwFld;
	gbPDadr = P_ADDR;
	gnPDdat = P_DATA;
#endif

    switch(((P_DATA>>16)&0xFF)+((P_DATA>>24)&0x01)) {
        // 20171205 HTY
        case 2    : gbPKeyVal = KEY_VAL_R; gbExUCCKeyOn=1; break;             // RIGHT
        case 4    : gbPKeyVal = KEY_VAL_L; gbExUCCKeyOn=1; break;             // LEFT
        case 8    : gbPKeyVal = KEY_VAL_U; gbExUCCKeyOn=1; break;             // UP
        case 0x10 : gbPKeyVal = KEY_VAL_D; gbExUCCKeyOn=1; break;             // DOWN         
        // 180702 JJH   saf - > maf
        case 0x20 : gbMAF_Tele = 1; gbExUCCKeyOn = 1; break;                  // ZooM Tele	171204 JJH Pelco-d 2motor
        case 0x40 : gbMAF_Wide = 1; gbExUCCKeyOn = 1; break;                  // ZooM Wide
        case 0x80 : gbMAF_Far  = 1; gbExUCCKeyOn = 1; break;                  // Focus Far
        case 0x01 : gbMAF_Near = 1; gbExUCCKeyOn = 1; break;                  // Focus Near
        case 0xAA : bEX_UCC_DOWN = 1; break;								  // EX-SDI UCC DOWNLOAD
        
   #if model_UccD_Stop==1 
       	 case 0x00 : gbExUccKeyBuf=gbExUCCKeyOn= 0; break;                    // Stop
   #endif
        	
		default   : {
	#if model_UccD == 1	// 170407 KSH
			const WORD wCMD = (P_DATA>>16)&0xFFFF;

			if(bCh==0) {						// UART0
				if(wCMD) gbPKeyVal = KEY_VAL_C;
			}
			else {								// SDI UCC
//				if(wCMD!=0 && wCMD!=0xFFFF && wCMD!=0x88f8) gbPKeyVal = KEY_VAL_C; 				// CENTER (anything)
				if(wCMD==0x200 || wCMD==0x3 || wCMD==0x7 || wCMD==0x1E) {gbPKeyVal = KEY_VAL_C; gbExUCCKeyOn=1;}	// CENTER (reserved)
			}
	#else
			if((P_DATA>>16)&0xFFFF) gbPKeyVal = KEY_VAL_C;
	#endif
		}
	}
    
	//****************************************************************************************
	// Camera Control Protocol Using EX-SDI UCC 	
	//****************************************************************************************
	#if(Protocol_EXSDI)

	#define REQ_RdCmd 0x80
	#define REQ_WrCmd 0x00

	WORD Anc_D2=0;
	WORD Anc_D3=0;

	if(Command_1==0xA0){
	#if(0)
		TxStrNoIRQ("Command_1 : ",Command_1,3);
		TxStrNoIRQ("Command_2 : ",Command_2,3);
	#endif
	if(Command_2>=0x80){
		switch (Command_2&0x7F){
			case EXUC_Brightness:{Anc_D2=(EXUC_Brightness 	 &0x00FF);	Anc_D3=(MP(MpBrightness)&0x00FF);	break;}
			case EXUC_Sharpness	:{Anc_D2=(EXUC_Sharpness	 &0x00FF);	Anc_D3=(MP(MpSharpness)	&0x00FF);	break;}
			case EXUC_TotalGain	:{Anc_D2=(EXUC_TotalGain	 &0x00FF);	Anc_D3=(MP(MpAgc)		&0x00FF);	break;}
			case EXUC_Mirror	:{Anc_D2=(EXUC_Mirror	 	 &0x00FF);	Anc_D3=(MP(MpMirror)	&0x00FF);	break;}
			case EXUC_Flip		:{Anc_D2=(EXUC_Flip		 	 &0x00FF);	Anc_D3=(MP(MpFlip)		&0x00FF);	break;}
			case EXUC_FPS		:{Anc_D2=(EXUC_FPS		 	 &0x00FF);	Anc_D3=(MP(MpSysFreq)	&0x00FF);	break;}
			case EXUC_Resol		:{Anc_D2=(EXUC_Resol		 &0x00FF);	Anc_D3=(MP(MpOutFps)	&0x00FF);	break;}
			case EXUC_ColorGain	:{Anc_D2=(EXUC_ColorGain	 &0x00FF);	Anc_D3=(MP(MpColorSat)	&0x00FF);	break;}
			case EXUC_ColorHue	:{Anc_D2=(EXUC_ColorHue	 	 &0x00FF);	Anc_D3=(MP(MpColorHue)	&0x00FF);	break;}
			case EXUC_Contrast	:{Anc_D2=(EXUC_Contrast	 	 &0x00FF);	Anc_D3=(MP(MpContrast)	&0x00FF);	break;}
			case EXUC_FWver		:{Anc_D2=(EXUC_FWver		 &0x00FF);	Anc_D3=(gwFW_Ver		&0x03FF);	break;}
			case EXUC_Agc		:{Anc_D2=(EXUC_Agc			 &0x00FF);	Anc_D3=(gwDNR3D_Val		&0x03FF);	break;}
			case EXUC_ParVer	:{Anc_D2=(EXUC_ParVer		 &0x00FF);	Anc_D3=(UP(UpUsrParVer )&0x03FF);	break;}
			default				:{Anc_D2=0;	Anc_D3=0;		break;}
		}
		TxStrNoIRQ("ANC_REG_ANC0_D03w =  ", Anc_D3, 3 );
		SetIsp(0x721,(Anc_D2<<12)|(Anc_D3));		// REG_ANC0_D02w(Anc_D2);REG_ANC0_D03w(Anc_D3);
	}
	else{
		switch (Command_2){
			case EXUC_Brightness	:{MP(MpBrightness)	= Data_2;	TxStrNoIRQ("UccBrightness = ", MP(MpBrightness) , 3 );gbMnParSaveChk = 1;break;}
			case EXUC_Sharpness		:{MP(MpSharpness)	= Data_2;	TxStrNoIRQ("UccSharpness  = ", MP(MpSharpness ) , 3 );gbMnParSaveChk = 1;break;}
			case EXUC_TotalGain		:{MP(MpAgc)			= Data_2;	TxStrNoIRQ("UccTotalGain  = ", MP(MpAgc       ) , 3 );gbMnParSaveChk = 1;break;}
			case EXUC_Mirror		:{MP(MpMirror)		= Data_2;	TxStrNoIRQ("UccMirror     = ", MP(MpMirror    ) , 3 );gbMnParSaveChk = 1;break;}
			case EXUC_Flip			:{MP(MpFlip)		= Data_2;	TxStrNoIRQ("UccFlip       = ", MP(MpFlip      ) , 3 );gbMnParSaveChk = 1;break;}
			case EXUC_FPS			:{MP(MpSysFreq)		= Data_2;	TxStrNoIRQ("UccFPS        = ", MP(MpSysFreq   ) , 3 );gbMnParSaveChk = 1;break;}
			case EXUC_Agc			:{gbEXUC_AgcFlag	= Data_2;	TxStrNoIRQ("UccAgcFlag    = ", gbEXUC_AgcFlag   , 1 );					 break;}
			case EXUC_Resol			:{																										 break;}
			case EXUC_FWver			:{																										 break;}
			case EXUC_ParVer		:{ParSet(UpUsrParVer,Data_2);	TxStrNoIRQ("UccParVer     = ", UP(UpUsrParVer )	, 3 );gbUsrParSaveChk= 1;break;}
			case EXUC_ColorGain		:{MP(MpColorSat)    = Data_2;	TxStrNoIRQ("UccColorGain  = ", MP(MpColorSat)   , 3 );gbMnParSaveChk = 1;break;}
			case EXUC_ColorHue		:{MP(MpColorHue)    = Data_2;	TxStrNoIRQ("UccColorHue   = ", MP(MpColorHue)   , 3 );gbMnParSaveChk = 1;break;}
			case EXUC_Contrast		:{MP(MpContrast)    = Data_2;	TxStrNoIRQ("UccContrast   = ", MP(MpContrast)   , 3 );gbMnParSaveChk = 1;break;}
			default					:{																										 break;}
			}
	}
	
	}

	#endif
    #if model_UccD_Stop==1 
    	gbExUccKeyBuf=gbPKeyVal;
    #endif
    
    if(bEX_UCC_DOWN){//180329 PCB : EX-SDI UCC DOWNLOAD
        // Write Flag
		SfWrEn;
		sfls_erase_sect(_reset_s - 1);
		_wr8(_reset_s - 1, 0x40);

		// System Reset
		SystemReset();

		gbPKeyVal=0;
    }

	//TxStr("Pelco-D ", (P_DATA>>16)&0xFFFF,8);
	return 0;
	
}

int ISPM RxPP(const BYTE bCh, const BYTE bIn)
{
	//asm volatile("l.nop");

	UNUSED_ARG(bCh);
	SetPnt(BYTE, bETX);
	SetPnt(WORD, wRxAddr);
	SetPnt(UINT, nRxData);

	if(P_ETX != PP_ETX) return 1;

	BYTE crc = 0x0F;
	crc ^= (P_ADDR&0xFF);
	crc ^= ((P_DATA>>24)&0xFF);	// Command 1
	crc ^= ((P_DATA>>16)&0xFF);	// Command 2 (Zoom & Pan & Tilt)
	crc ^= ((P_DATA>>8)&0xFF);	// Pan Speed
	crc ^= ((P_DATA>>0)&0xFF);	// Tilt Speed
	if(crc != bIn) return 1;

	P_ADDR++;

	if(P_ADDR != MP(MpCamID)) return 1;


	switch((P_DATA>>16)&0xFF) {
		case 2    : gbPKeyVal = KEY_VAL_R; break;						// RIGHT
		case 4    : gbPKeyVal = KEY_VAL_L; break;						// LEFT
		case 8    : gbPKeyVal = KEY_VAL_U; break;						// UP
		case 0x10 : gbPKeyVal = KEY_VAL_D; break;						// DOWN
		default   : if((P_DATA>>16)&0xFFFF) gbPKeyVal = KEY_VAL_C;	// CENTER
	}
	//TxStr("Pelco-P ", (P_DATA>>16)&0xFFFF,8);

	return 0;
}

#if model_Uart2 == 1
void ISPM TxErr1(void)
{
	Uart1TxByte(PC_STX);
	Uart1TxByte(PC_CMD_ERR);
	Uart1TxByte(PC_ETX);
}

void ISPM TxAck1(void)
{
	Uart1TxByte(PC_STX);
	Uart1TxByte(PC_CMD_ACK);
	Uart1TxByte(PC_ETX);
}

void ISPM TxStr1(const char* apbStr0, UINT anVal, UINT anValLen)
{
	char bStr[9];
	const UINT nValLen = MIN(8,anValLen);
	const BYTE bLen = ((apbStr0) ? strlen(apbStr0) : 0) + nValLen + 2;

	if(nValLen) uint2strh(bStr, anVal, nValLen);

	Uart1TxByte(PC_STX);
	Uart1TxByte(PC_CMD_STR);
 	Uart1TxByte(bLen);

	if(apbStr0) Uart1TxStr(apbStr0);
	if(nValLen) Uart1TxStr(bStr);

	Uart1TxByte('\r');
	Uart1TxByte('\n');

	Uart1TxByte(PC_ETX);
}
#else
	#define TxErr1()
	#define TxAck1()
#endif

//-------------------------------------------------------------------------------------------------
#define Case1(CMD,VAL)\
	case (CMD) :\
		(VAL) = bIn;\
		P_STG++;\
		break

#define Case2(CMD,VAL)\
	case (CMD)   :\
	case (CMD)+1 :\
		(VAL) = ((VAL)<<8) | bIn;\
		P_STG++;\
		break

#define Case4(CMD,VAL)\
	case (CMD)   :\
	case (CMD)+1 :\
	Case2((CMD)+2,VAL)

#define SetCase0(C,E,EC,...)			case C : if(E) { EC DispLineUp(); } else goto err_proc; SetEnd(); break
#define SetCase1(C,E,EC,D0,D0n)			Case##D0n(C,D0);  SetCase0(C+D0n,E,EC)
#define SetCase2(C,E,EC,D0,D0n,...)		Case##D0n(C,D0);  SetCase1(C+D0n,E,EC,__VA_ARGS__)
#define SetCase3(C,E,EC,D0,D0n,...)		Case##D0n(C,D0);  SetCase2(C+D0n,E,EC,__VA_ARGS__)

#define SetCase(CMD,EndChk,EndCode,VAL_NUM,...)	SetCase##VAL_NUM(CMD,EndChk,EndCode,__VA_ARGS__)


#if 0//STR_QUE_DATA == 1
	BYTE gbDispLine = 0;
	BYTE gbDispLine1d = 11;
	BYTE gbDispPos = 0;

	void DispLineUp(void)
	{
		#define DispUartX	(ISP_FONT_EAX-24-1)/*0*//*DispDbgX*/

		SetFontAttrs( 6+gbDispLine1d, DispUartX, 24, MN_YELLOW);
		SetFontAttrs(17+gbDispLine1d, DispUartX, 24, MN_YELLOW);
		gbDispLine1d = gbDispLine;

		gbDispLine++;
		if(gbDispLine>11) gbDispLine = 0;

		DispClr( 6+gbDispLine, DispUartX, 24);
		DispClr(17+gbDispLine, DispUartX, 24);

		//SetFontAttrs( 6+gbDispLine, DispUartX, 24, MN_YELLOW);
		//SetFontAttrs(17+gbDispLine, DispUartX, 24, MN_YELLOW);
	}
#else
	#define DispLineUp()
#endif

//-------------------------------------------------------------------------------------------------
// UART CH2 Rx
#if model_UccD == 1 || model_Uart2 == 1
void ISPM RxCh2(void)
{
	BYTE *pbETX = &gbETX1;
	BYTE *pbRxStg = &gbRxStg1;
	WORD *pwRxAddr = &gwRxAddr1;
	UINT *pnRxData = &gnRxData1;
		
	#if model_UccD_Stop==1  // 20171205 HTY
		if(gbExUCCKeyOn)    gbPKeyVal=gbExUccKeyBuf;
	#else
		if(!pKEY) 			gbExUCCKeyOn=0;  // 
	#endif
		
	while(gtUart1RxQue.wRxLen > 0) {

		BYTE bIn = 0;

	  #if 0
		bIn = QueOut(gtUart1RxQue, UART_BUF_SIZE );
	  #else
		bIn = *gtUart1RxQue.pbRxTail++;
		if( gtUart1RxQue.pbRxTail == (gtUart1RxQue.bRxQue+UART_BUF_SIZE) ) {
			gtUart1RxQue.pbRxTail  = gtUart1RxQue.bRxQue;
		}
		gtUart1RxQue.wRxLen--;
	  #endif

	#if STR_QUE_DATA == 1
		gnQueUse2 = (gnQueUse2<<8) | ((gnQueUse1>>24)&0xFF);
		gnQueUse1 = (gnQueUse1<<8) | ((gnQueUse0>>24)&0xFF);
		gnQueUse0 = (gnQueUse0<<8) | bIn;
	#endif

		switch(gbRxStg1){
//...............................................
// Start -> Command
			case 0x00 :
				switch(bIn){
					case PC_STX : gbRxStg1++; break;
					case PD_STX : gbRxStg1 = PD_STG; break;
					case PP_STX : gbRxStg1 = PP_STG; break;
				}
				break;

			case 0x01 :
				switch(bIn){
					//case PC_CMD_REGW :
					//case PC_CMD_REGR :
					case PC_CMD_KEY  :
					//case PC_CMD_CHA  :
					//case PC_CMD_AWBI :

					case PC_CMD_INI  :
					case PC_CMD_ACK  :

					//case PC_CMD_PARW :
					//case PC_CMD_PARR :
					//case PC_CMD_EEPW :
					//case PC_CMD_EEPR :
					//case PC_CMD_PARK :

					//case PC_CMD_DOWN :
						gbRxStg1 = bIn;
						break;

					default	:
						goto err_proc;
						break;
				}
				break;
//...............................................
// Pelco D
			SetCase(PD_STG, RxPD(1,bIn)==0,
					, 2, gwRxAddr1,1, gnRxData1,4);

#if model_Uart2 == 1  // 170406 KSH : filtering for unstable value
//...............................................
// Pelco P
			SetCase(PP_STG, RxPP(1,bIn)==0,
					, 3, gwRxAddr1,1, gnRxData1,4, gbETX1,1);

//...............................................
// Key process : Key from PC
			SetCase(PC_CMD_KEY, bIn==PC_ETX, gbUKeyVal = gnRxData1; /*TxStr("UKeyVal ", gbUKeyVal,4);*/
					, 1, gnRxData1,1);

//...............................................
// Ini process : Uart que init
			SetCase(PC_CMD_INI, bIn==PC_ETX, Uart1RstRxQue();
					, 0);

//...............................................
// Ack process : Ack respond
			SetCase(PC_CMD_ACK, bIn==PC_ETX, TxAck1();
					, 0);

#endif
//...............................................
// Err process : Rx que clear, Error message send
			err_proc:
			default :
				Uart1RstRxQue();
				TxErr1();
				gbRxStg1 = 0;
				break;
		}
	}
}
#else
	#define RxCh2()
#endif

//-------------------------------------------------------------------------------------------------
void ISPM Comm(void)
{
//#if model_UccD == 1 || model_Uart2 == 1
		BYTE *pbETX = &gbETX;
		BYTE *pbRxStg = &gbRxStg;
		WORD *pwRxAddr = &gwRxAddr;
		UINT *pnRxData = &gnRxData;
//#endif

//#if model_LowUart
//		extern void ISPM0 UartStg(void);
//		UartStg();
//#endif

	DI();		// ���� ��� ECM���� CMD�� �и� �� ����
	
	RxCh2();

	while(gtUartQue.wRxLen > 0) {
#if 1
		BYTE bIn = 0;

		  #if 0
			bIn = QueOut(gtUartQue, UART_BUF_SIZE );
		  #else
			bIn = *gtUartQue.pbRxTail++;
			if( gtUartQue.pbRxTail == (gtUartQue.bRxQue+UART_BUF_SIZE) ) {
				gtUartQue.pbRxTail  = gtUartQue.bRxQue;
			}
			gtUartQue.wRxLen--;
			
		  #endif

		#if STR_QUE_DATA == 1
			gnQueUse2 = (gnQueUse2<<8) | ((gnQueUse1>>24)&0xFF);
			gnQueUse1 = (gnQueUse1<<8) | ((gnQueUse0>>24)&0xFF);
			gnQueUse0 = (gnQueUse0<<8) | bIn;

		  #if 0		// CAUTION !!! Comm() �Լ����� OSD ��� �� 'EEPROM WRITE ALL' �� ���ߴ� ��� �߻�
			#define DispUartX	(ISP_FONT_EAX-24-1)/*0*//*DispDbgX*/
			DispHex(29, DispUartX   , gnQueIn2, 8);
			DispHex(29, DispUartX+8 , gnQueIn1, 8);
			DispHex(29, DispUartX+16, gnQueIn0, 8);
			DispHex(30, DispUartX   , gnQueUse2, 8);
			DispHex(30, DispUartX+8 , gnQueUse1, 8);
			DispHex(30, DispUartX+16, gnQueUse0, 8);
			//SETFONTID(32, ISP_FONT_EAX-1, 0x1fe);
			//SETFONTID(31, ISP_FONT_EAX-1, 0x1fe);

			DispHex(28, DispUartX   , gnQueOut2, 8);
			DispHex(28, DispUartX+8 , gnQueOut1, 8);
			DispHex(28, DispUartX+16, gnQueOut0, 8);
		  #endif

		  #if 0
			if(gbDispPos>22) gbDispPos = 0;
			DispHex( 6+gbDispLine, DispUartX+gbDispPos, gnQueIn0, 2);	//  6~16
			DispHex(17+gbDispLine, DispUartX+gbDispPos,  gnQueUse0, 2);	// 17~27

			SetFontAttrs( 6+gbDispLine, DispUartX, 24, MN_WHITE);
			SetFontAttrs(17+gbDispLine, DispUartX, 24, MN_WHITE);

			gbDispPos+=2;
		  #endif
		#endif
		
#else
		gtUartQue.wRxLen--;
		const BYTE bIn = *gtUartQue.pbRxTail++;
		if( gtUartQue.pbRxTail == &gtUartQue.bRxQue[UART_BUF_SIZE-1]){
			gtUartQue.pbRxTail  = &gtUartQue.bRxQue[0];
		}
		//gtUartQue.wRxLen--;
#endif

		//TxStrNoIRQ("UART Data:", bIn, 16);

		switch(gbRxStg){
//...............................................
// Start -> Command
			case 0x00 :
				switch(bIn){
					case PC_STX : gbRxStg++; break;
					case PD_STX : gbRxStg = PD_STG; break;
					case PP_STX : gbRxStg = PP_STG; break;
				}
				break;

			case 0x01 :
				switch(bIn){
					case PC_CMD_REGW :
					case PC_CMD_REGR :
					case PC_CMD_KEY  :
					//case PC_CMD_CHA  :

#if (model_I2C_ch1 == 1)
					case I2C_CMD_MENUW :
					case I2C_CMD_MENUR :
//					case I2C_CMD_CLOCK :
#endif

					case PC_CMD_AWBI :

					case PC_CMD_INI  :
					case PC_CMD_ACK  :

					case PC_CMD_PARW :
					case PC_CMD_PARR :
					case PC_CMD_EEPW :
					case PC_CMD_EEPR :
					case PC_CMD_PARK :

					case ISPF_CMD_CM_INIT	:
					case ISPF_CMD_CM_W		:
					case ISPF_CMD_CM_R		:
						
					case ISPF_CMD_GMA_INIT	:
					case ISPF_CMD_GMA_W		:
					case ISPF_CMD_GMA_R		:
						
					case PC_CMD_DOWN :
						gbRxStg = bIn;
						break;

					default	:
						goto err_proc;
						break;
				}
				break;
//...............................................
// Pelco D
			SetCase(PD_STG, RxPD(0,bIn)==0,
					, 2, gwRxAddr,1, gnRxData,4);
//...............................................
// Pelco P
			SetCase(PP_STG, RxPP(0,bIn)==0,
					, 3, gwRxAddr,1, gnRxData,4, gbETX,1);
//...............................................
// Reg write process : ISP register set
			SetCase(PC_CMD_REGW, bIn==PC_ETX, RxAddr(1);
					, 2, gwRxAddr,2, gnRxData,4);
//...............................................
// Reg read process : ISP register get
			SetCase(PC_CMD_REGR, bIn==PC_ETX, RxAddr(0);
					, 1, gwRxAddr,2);

#if (model_Par==1)
//...............................................
// Paramter On process : Parameter set
			SetCase(PC_CMD_PARK, bIn==PC_ETX, RxParK();
					, 1, gnRxData,4);

//...............................................
// Paramter write process : Parameter set
			SetCase(PC_CMD_PARW, bIn==PC_ETX, RxPar(1);
					, 2, gwRxAddr,2, gnRxData,1);
//...............................................
// Paramter read process : Parameter get
			SetCase(PC_CMD_PARR, bIn==PC_ETX, RxPar(0);
					, 1, gwRxAddr,2);
//...............................................
// Paramter write process : Save parameter to EEPROM(or flash)
			SetCase(PC_CMD_EEPW, bIn==PC_ETX, TxParSave();
					, 0);

//...............................................
// Paramter read process : Read parameter from EEPROM(or flash)
			SetCase(PC_CMD_EEPR, bIn==PC_ETX, TxParRead();
					, 0);
#endif

//...............................................
// User Data - ColorMap  Init process : Init default ColorMap
			SetCase(ISPF_CMD_CM_INIT, bIn==PC_ETX, gbDfltColorMapChk = 1; DfltColorMapSave();
					, 0);
//...............................................
// User Data - ColorMap Write process : Save ColorMap user data to EEPROM(or flash)
			SetCase(ISPF_CMD_CM_W, bIn==PC_ETX, ISPtoSf_CmSave();
					, 0);
//...............................................
// User Data - ColorMap Read process : Read ColorMap user data from EEPROM(or flash)
			SetCase(ISPF_CMD_CM_R, bIn==PC_ETX, SftoISP_CmLoad();
					, 0);
					
//...............................................
// User Data - Gamma Init process : Init default Gamma
			SetCase(ISPF_CMD_GMA_INIT, bIn==PC_ETX, gbDfltGammaChk = 1; DfltGammaSave();
					, 0);
//...............................................
// User Data - Gamma Write process : Save Gamma user data to EEPROM(or flash)
			SetCase(ISPF_CMD_GMA_W, bIn==PC_ETX, ISPtoSf_GmSave();
					, 0);
//...............................................
// User Data - Gamma Read process : Read Gamma user data from EEPROM(or flash)
			SetCase(ISPF_CMD_GMA_R, bIn==PC_ETX, SftoISP_GmLoad();
					, 0);

//...............................................
// Key process : Key from PC
			SetCase(PC_CMD_KEY, bIn==PC_ETX, gbUKeyVal = gnRxData; /*TxStr("UKeyVal ", gbUKeyVal,4);*/
					, 1, gnRxData,1);

#if (model_I2C_ch1 == 1)
//...............................................
// Menu write process : Menu data set
			SetCase(I2C_CMD_MENUW, bIn==PC_ETX,
					TxStrDec2("MenuW ", gwRxAddr, 4, gnRxData, 4);
					//TxStr("MenuW ", gnRxData, 8);
					RxMenuWrite();
					, 2, gwRxAddr,2, gnRxData,2);
//...............................................
// Menu read process : Menu data get
			SetCase(I2C_CMD_MENUR, bIn==PC_ETX,
					TxStrDec2("MenuR ", gwRxAddr, 4, gnRxData, 4);
					, 2, gwRxAddr,2, gnRxData,2);
#endif

//...............................................
// Download process : Download from PC
			SetCase(PC_CMD_DOWN, bIn==PC_ETX,
					if(_reset_s&FLASH_ADDR_MASK) {
						/*gnDownOn = 1;*/ /*TxStr("DOWN ", 0,0);*/

						// UART IRQ Disable & Initialize
						UART0_TX_IRQ_EN = 0;
						UART0_RX_IRQ_EN = 0;
						gtUartQue.wTxLen = 0;
						gtUartQue.pbTxTail = gtUartQue.pbTxHead;

						// Write Flag
						SfWrEn;
						sfls_erase_sect(_reset_s - 1);
						_wr8(_reset_s - 1, 0x80);

						// System Reset
						SystemReset();
					}
					, 0);
//...............................................
// Ini process : Uart que init
			SetCase(PC_CMD_INI, bIn==PC_ETX, UartRstQue();
					, 0);
//...............................................
// Character process : Character from PC
			/*SetCase(PC_CMD_CHA,  bIn==PC_ETX, gbWinChar = gnRxData;
					, 1, gnRxData,1);*/
//...............................................
// Ack process : Ack respond
			SetCase(PC_CMD_ACK, bIn==PC_ETX, TxAck();
					, 0);
//...............................................
// AWB ODM process : AWB Odm Initializing
			SetCase(PC_CMD_AWBI, bIn==PC_ETX, gnAwbOdmCapOn=1; TxStr("AWB ODM ", 0,0);
					, 0);
//...............................................
// Err process : Rx que clear, Error message send
			err_proc:
			default :
				UartRstRxQue();
				TxErr();
				gbRxStg = 0;
				break;
		}
	}

	EI();		// ���� ��� ECM���� CMD�� �и� �� ����

//#if(!model_Par)
	TxParInitAll();
//#endif

}
