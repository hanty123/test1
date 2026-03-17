/* **************************************************************************
 File Name	: 	dev_extn.h
 Description:	EN772 - Extern function and variable
 Designer	:	Lee, Gyu Hong
 Date		:	20. 12. 01
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */
/*
 INDEX	:
		 1. System
		 2. GPIO
		 3. ADC
		 4. UART
		 5. I2C
		 6. TIMER
		 7. SPI
		 8. IRQ
		 9. FLASH
		10. WDT
		11. ISP
		12. SENSOR
		13. TEST
*/

//******************************************************
// Extern function and variable
//------------------------------------------------------


//******************************************************
// 1. System
//------------------------------------------------------



//******************************************************
// 2. GPIO
//------------------------------------------------------
extern void InitGpio(void);


//******************************************************
// 3. ADC (in ISP function)
//------------------------------------------------------
extern void InitAdc(void);

extern UINT gnADC_KEY;
extern UINT gnADC_CVBS;
extern UINT gnADC_CDS;


//******************************************************
// 4. UART
//------------------------------------------------------
extern void InitUart(void);

#define UART_BUF_SIZE		/*512*//*256*//*128*/192		// User buffer size

typedef /*volatile*/ struct _UART_QUE{		// Queue structure define
	volatile WORD	wRxLen;					// Number of characters in the Rx ring buffer
	volatile BYTE*	pbRxHead;				// Pointer to where next character will be inserted
	volatile BYTE*	pbRxTail;				// Pointer from where next character will be extracted
	volatile BYTE	bRxQue[UART_BUF_SIZE];	// Ring buffer character storage (Rx)

	volatile WORD	wTxLen;					// Number of characters in the Tx ring buffer
	volatile BYTE*	pbTxHead;				// Pointer to where next character will be inserted
	volatile BYTE*	pbTxTail;				// Pointer from where next character will be extracted
	volatile BYTE	bTxQue[UART_BUF_SIZE];	// Ring buffer character storage (Tx)

} TUartQue;

#if model_UccD == 1 || model_Uart2 == 1
	typedef /*volatile*/ struct _UART_RX_QUE{	// Queue structure define
		volatile WORD	wRxLen;					// Number of characters in the Rx ring buffer
		volatile BYTE*	pbRxHead;				// Pointer to where next character will be inserted
		volatile BYTE*	pbRxTail;				// Pointer from where next character will be extracted
		volatile BYTE	bRxQue[UART_BUF_SIZE];	// Ring buffer character storage (Rx)
	} TUartRxQue;
	extern TUartRxQue gtUart1RxQue;
	extern void Uart1RstRxQue(void);

	typedef /*volatile*/ struct _UART_TX_QUE{		// Queue structure define
		volatile WORD	wTxLen;					// Number of characters in the Tx ring buffer
		volatile BYTE*	pbTxHead;				// Pointer to where next character will be inserted
		volatile BYTE*	pbTxTail;				// Pointer from where next character will be extracted
		volatile BYTE	bTxQue[UART_BUF_SIZE];	// Ring buffer character storage (Tx)
	} TUartTxQue;
	extern TUartTxQue gtUart1TxQue;
	extern void Uart1RstTxQue(void);
	extern void Uart1TxByte(BYTE abByte);
	extern void Uart1TxStr(const char *apcStr);
	extern void TxStr1(const char* apbStr0, UINT anVal, UINT anValLen);
#endif

extern TUartQue gtUartQue;

extern void Uart_Tx(char dat);
extern void Uart_Rx(char *dat);
extern void uart_str(const char *text);

extern void UartRstQue(void);
extern void UartRstRxQue(void);

extern void UartTxByte(BYTE abByte);
extern void UartTxStr(const char *apcStr);

extern void Uart1_Tx(char dat);
extern void Uart1_Rx(char *dat);
extern void IsrUart1Tx(void);
extern void IsrUart1Rx(void);

//------------------------------------------------------------------------------
// Baudrate config.
extern void UartBaudRate(void);

//******************************************************
// 5. I2C
//------------------------------------------------------
extern void InitI2c(void);

// SI2C (dedicated channel for sensor control. 1.8v, Master only)
extern BYTE i2c1_write(BYTE dat, BYTE last, BYTE repeat);
extern BYTE i2c1_read(BYTE last, BYTE repeat);

extern void SetSensTwi_Sony(BYTE abDevaddr, WORD awAddr, BYTE abData);
extern BYTE GetSensTwi_Sony(BYTE abDevaddr, WORD awAddr);
extern void SetSensTwiBst_Sony(BYTE abDevaddr, WORD awAddr, UINT anData, UINT anNum);

extern void SetSensTwi_Onsemi(BYTE abDevaddr, WORD awAddr, WORD abData);
extern WORD GetSensTwi_Onsemi(BYTE abDevaddr, WORD awAddr);

extern void SetSensTwi_Omni(BYTE abDevaddr, WORD awAddr, BYTE abData);
extern BYTE GetSensTwi_Omni(BYTE abDevaddr, WORD awAddr);
extern void SetSensTwiBst_Omni(BYTE abDevaddr, WORD awAddr, UINT anData, UINT anNum);

extern void SetSensTwi_GC(BYTE abDevaddr, WORD awAddr, BYTE abData);
extern BYTE GetSensTwi_GC(BYTE abDevaddr, WORD awAddr);

extern void SetSensTwi_Pxpls(BYTE abDevaddr, BYTE abAddr, BYTE abData);
extern BYTE GetSensTwi_Pxpls(BYTE abDevaddr, BYTE abAddr);
extern void SetSensTwiBst_Pxpls(BYTE abDevaddr, BYTE abAddr, UINT anData, UINT anNum);

extern void SetSensTwi_SC(BYTE abDevaddr, WORD awAddr, BYTE abData);
extern BYTE GetSensTwi_SC(BYTE abDevaddr, WORD awAddr);

extern void SetSensTwi_Pana(BYTE abDevaddr, WORD awAddr, BYTE abData);
extern BYTE GetSensTwi_Pana(BYTE abDevaddr, WORD awAddr);

extern BYTE gbSensorOff;

extern BYTE i2c_write(BYTE dat, BYTE last, BYTE repeat);
extern BYTE i2c_read(BYTE last, BYTE repeat);

#if (model_I2C_ch1 == 2)
extern BYTE eep_write(UINT anAddr, BYTE abData);
extern BYTE eep_read(const WORD awAddr, BYTE* abData, const UINT anDataEa);
extern BYTE EepPageWrite(const WORD awWaddr, BYTE* apbBuf, const UINT anBufEa);
extern BYTE TwiWrEep2(const WORD awWaddr, BYTE* apbBuf, const UINT anBufEa);
extern void TwiWrEep( WORD awWaddr, BYTE* apbBuf, UINT anBufEa);
extern void TwiRdEep( WORD awWaddr,BYTE* apbBuf, UINT anBufEa);

#define	TwiWrEep2_continue	if(TwiWrEep2(0, 0, 0)) bTwiWrEep2Rdy = 1;
#define TwiRdEep	eep_read

extern BYTE gbEepromOff;
#endif



//******************************************************
// 6. TIMER
//------------------------------------------------------
extern void InitTimer(void);
extern void InitTickTimer(const UINT anCntPerSec);
	
	
//******************************************************
// 7. SPI
//------------------------------------------------------
extern void InitSpi(void);

extern void SPI0_LSB_WRITE(BYTE abData);
extern BYTE SPI0_LSB_READ(void);
extern void SPI_MSB_WRITE(BYTE abData);
extern BYTE SPI_MSB_READ(void);



//******************************************************
// 8. IRQ
//------------------------------------------------------
extern void InitIrq(void);

extern UINT ISPM0 GetSt(UINT *);
extern void ISPM0 SetStDisIrq(UINT);
extern void ISPM0 SetStEnaIrq(UINT);
extern void ISPM0 SetSt(const UINT, UINT *);
extern UINT ISPM0 GetTT(void);
extern UINT ISPM0 GetTTmax(void);

//extern int	IntInit(void);
//extern int	IntAdd(UINT anVec, void (* handler)(void *), void *arg);
//extern int	IrqDisable(UINT anVec);
//extern int	IrqEnable(UINT anVec);

extern void WaitTt(UINT anUs);

extern volatile UINT gnIsrTick;
extern volatile UINT gnIsrTickOn;

// Interrupt Vect
//-------------------------------------------------------------------------------------------------
extern int IrqDisable(UINT);
extern int IrqEnable(UINT);
extern void InitEnaIrq(void);

extern void ISPM0 ClrIrqTT(void);

extern void IsrGpio(void);
extern void IsrTimer(void);
extern void IsrUart(void);
extern void IsrISP(void);
extern void IsrI2c(void);

typedef struct _tIhnd{						// Handler entry
	void 	(*handler)(void);
	//void	*arg;
} tIhnd;

tIhnd tIntHandlers[MAX_INT_HANDLERS];		// Interrupt handlers table


//******************************************************
// 9. FLASH
//------------------------------------------------------
extern void InitFlash(void);

extern void sfls_init(void);
extern void sfls_write_en(void);
extern void sfls_erase_sect(int Adr);
extern void sfls_erase_all(void);
extern void sfls_write_reg(BYTE dat);
extern BYTE sfls_read_reg(void);
//extern void sfls_page_program(int Adr, BYTE* abData, const UINT anDataEa);

extern BYTE SfWrite(UINT anAddr,BYTE * apbData,UINT anNum);
extern BYTE SfRead(UINT anAddr,BYTE * apbData,UINT anNum);
extern BYTE SfWrite2(BYTE* apbData, UINT anNum, BYTE abMode);
extern BYTE SfRead2(BYTE* apbData, UINT anNum, BYTE abMode);
extern BYTE MenuSfWrite2(BYTE* apbData, UINT anNum, UINT anAddr, BYTE abData);
extern BYTE Sf2Isp(UINT anSfaddr,UINT anIspAddr,UINT anIspBufEa,BYTE abSizeByte);
extern BYTE Isp2Sf(UINT anSfaddr,UINT anIspAddr,UINT anIspBufEa,BYTE abSizeByte);

extern BYTE gbSF_Status;
extern BYTE gbSFLS_WB_RDCMD_IOM;



//******************************************************
// 10. WDT
//------------------------------------------------------
extern void SystemReset(void);
extern void InitWdt(UINT sec);


//******************************************************
// 11. ISP
//------------------------------------------------------
extern volatile BYTE gbVdiIrq;
extern volatile BYTE gbVdwIrq;
extern volatile BYTE gbVdoIrq;
extern volatile BYTE gbMnVdIrq;

extern void WaitVdi(void);
extern void WaitVdw(void);
extern void WaitVdo(void);
extern void InitWaitVd(const int);
extern void TestPatternOn(void);


// ISP initial table
extern const UINT gnTblIspCommon[][2];
extern const UINT gnTblIspCommonEa;

extern const UINT gnTblIspPre[][2];
extern const UINT gnTblIspPreEa;

#if (model_Sens_LWdr)
extern const UINT gnTblIspPreLWdr[][2];
extern const UINT gnTblIspPreEaLWdr;
#endif

#if(model_Sens_CLR_HDR)
extern const UINT gnTblIspPreClrWdr[][2];
extern const UINT gnTblIspPreEaClrWdr;
#endif

extern const UINT gnTblIspMode[][mode_size];
extern const UINT gnTblIspModeEa;

extern void SetFontAttrs(UINT anPosY, UINT anPosX, UINT anLen, UINT anAttr);
extern UINT DispStr(const char* cStr, UINT anPosY, UINT anPosX, UINT anLen);
extern void DispClr(UINT anPosY, UINT anPosX, UINT anLen);
extern void DispClrStr(const char* cStr, UINT anPosY, UINT anPosX, UINT anStrLen, UINT anClrLen);

#if model_CharMax == 1
extern void DispStrEx(const EXCH* cStr, UINT anPosY, UINT anPosX, UINT anLen);
extern void DispClrStrEx(const EXCH* cStr, UINT anPosY, UINT anPosX, UINT anStrLen, UINT anClrLen);
#endif

extern volatile UINT gnIsrISP0;
extern volatile UINT gnIsrISP1;
extern volatile UINT gnIsrISP2;



//******************************************************
// 12. SENSOR
//------------------------------------------------------
extern void LibInitSens(int aiMode, int aiOption);

#if (model_Sens_LWdr)
extern void InitSensWdr(int aiLWdrMode);
#endif

// Using EX-SDI UCC
#define EXUC_Brightness	0x00
#define EXUC_Sharpness	0x01
#define EXUC_TotalGain	0x02
#define EXUC_ColorGain	0x03
#define EXUC_Mirror		0x04
#define EXUC_Flip 		0x05
#define EXUC_FPS		0x06
#define EXUC_Resol		0x07
#define EXUC_ColorHue	0x08
#define EXUC_Contrast	0x09
#define EXUC_FWver 		0x0A
#define EXUC_Agc		0x0B
#define EXUC_ParVer 	0x0C

//******************************************************
// 13. TEST
//------------------------------------------------------




