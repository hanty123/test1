/* **************************************************************************
 File Name	: 	app_util.h
 Description	:	EN772 - Utility header file
 Designer		:	Lee, Gyu Hong
 Date		:	20. 12. 17
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

//***********************************************************************************
// Hard Floating caculation Tool
//-----------------------------------------------------------------------------------
// 170609 KSH
#define hfloat      float32             // H/W float TYPE

#define i_h(i)      _itof(i)            // int -> hfloat
#define h_i(fh)     _ftoi(fh)           // hfloat -> int

extern hfloat f_h(float f);             // float -> hfloat
extern float h_f(hfloat h);             // hfloat -> float

extern hfloat hALU(hfloat h1, hfloat h2, const char* f);
extern bool hCLU(hfloat h1, hfloat h2, const char* f);

#define _h(a,f,b)       hALU(a, b, #f)  // hfloat1 f hfloat2	(171211 LH : increase code size than _fxxx( , ) )
#define _b(a,f,b)       hCLU(a, b, #f)  // hfloat1 f hfloat2	 "

#define addh(h1,h2)     _fadd(h1,h2)    // hfloat1 + hfloat2
#define subh(h1,h2)     _fsub(h1,h2)    // hfloat1 - hfloat2
#define mulh(h1,h2)     _fmul(h1,h2)    // hfloat1 * hfloat2
#define divh(h1,h2)     _fdiv(h1,h2)    // hfloat1 / hfloat2

#define eh(h1,h2)       _feq(h1,h2)     // hfloat1 == hfloat2
#define geh(h1,h2)      _fge(h1,h2)     // hfloat1 >= hfloat2
#define gh(h1,h2)       _fgt(h1,h2)     // hfloat1 >  hfloat2
#define leh(h1,h2)      _fle(h1,h2)     // hfloat1 <= hfloat2
#define lh(h1,h2)       _flt(h1,h2)     // hfloat1 <  hfloat2
#define nh(h1,h2)       _fne(h1,h2)     // hfloat1 != hfloat2

#define ABSh(h1)                ( geh((h1),f_h(0.f)) ? (h1) : mulh((h1),f_h(-1.f)) )
#define MINh(h1,h2)             (  lh((h1),(h2)) ? (h1) : (h2) )
#define MAXh(h1,h2)             (  gh((h1),(h2)) ? (h1) : (h2) )
#define MINMAXh(h1,hMin,hMax)   MINh(MAXh(h1, hMin), hMax)
#define ABSDIFFh(h1,h2)         (  gh((h1),(h2)) ? subh((h1),(h2)) : subh((h2),(h1)) )

// Integer offset define for Floating calculation -------------------------------
#define ifmul4(val)		((val)<< 4)		// 16  offset : 0.0625 step
#define ifmul6(val)		((val)<< 6)		// 64  offset : 0.0156 step
#define ifmul8(val)		((val)<< 8)		// 256 offset : 0.0039 step
#define ifdiv4(val)		((val)>> 4)		// 16  divide
#define ifdiv6(val)		((val)>> 6)		// 64  divide
#define ifdiv8(val)		((val)>> 8)		// 256 divide

// String ----------------------------------------------------------------------
extern UINT strlen(const char *apbStr);
extern void uchar2strb(char* apbStr, BYTE anVal, UINT anLen);
extern void uint2strh(char* apbStr, UINT anVal, UINT anLen);
extern void int2str(char* apbStr, int aiVal, UINT anLen);
extern void per2str(char* apbStr, const int aiVal, const int aiValMax, UINT anLen);
extern void flt2str(char* apbStr, const float afVal, const int aiValNum, UINT anLen);

// Etc ------------------------------------------------------------------------
extern void CheckByteOrdering(void);

extern void SetWaitTimeOffset(const UINT anMCLK, const UINT anCntPerSec);
extern void WaitUs(UINT anUs);
extern void WaitXus(UINT anUs);
extern void WaitXms(UINT anMs);
extern UINT IntpValAgcPos(UINT aiCurAgc, UINT anAgcPt0, UINT anAgcPt1, UINT anAgcPt2, UINT anValPt0, UINT anValPt1, UINT anValPt2);
extern UINT IntpValAePos(UINT anCurAePos, UINT anAePosPt0, UINT anAePosPt1, UINT anAePosPt2, UINT anValPt0, UINT anValPt1, UINT anValPt2);
extern UINT IntpValAgcPos4(UINT anCurAgc, UINT anAgcPt0, UINT anAgcPt1, UINT anAgcPt2, UINT anAgcPt3, UINT anValPt0, UINT anValPt1, UINT anValPt2, UINT anValPt3);
extern UINT IntpValAePos5(int aiCurAePos, WORD* awAePosPt, UINT* anValPt);
extern UINT IntpValCtempPos(int aiCurCtemp, int aiCtempPt0, int aiCtempPt1, int aiCtempPt2, UINT anCtempVal0, UINT anCtempVal1, UINT anCtempVal2);

extern int 	LibUtlInterp1D (int aiXCur, int aiXPos1, int aiXPos2, int aiYPos1, int aiYPos2);
extern int 	LibUtlInterp1D_MINUS (int aiXCur, int aiXPos1, int aiXPos2, int aiYPos1, int aiYPos2);
extern BYTE LibUtlKeyPass (const BYTE* abpPassKeys, BYTE abKeySize, BYTE* abpPassCnt);
extern float LibUtlInterp1F (int aiXCur, int aiXPos1, int aiXPos2, float aiYPos1, float aiYPos2);


#define NOP4 { asm volatile("l.nop"); asm volatile("l.nop"); asm volatile("l.nop"); asm volatile("l.nop"); }


//***********************************************************************************
// Debugging with UART COMM
//-----------------------------------------------------------------------------------
// Tx header
// Eyenix Protocol
#define	PC_STX		0x02			// STX
	//						gbRxStg :  0   1   CMD
	#define PC_CMD_REGW		0x10	// STX CMD ADH ADL DAH DA1 DA2 DAL ETX	: ISP Reg. Write
	#define PC_CMD_REGR		0x20	// STX CMD ADH ADL ETX					: ISP Reg. Read
	#define PC_CMD_KEY		0x30	// STX CMD KEY ETX						: KEY
	//#define PC_CMD_CHA		0x40	// STX CMD CHA ETX						: gbWinChar	- Not Used

	#define PC_CMD_PARW 	0x50 		// Cmd : Write parameter in F/W. 			2 addr, 1 data.
	#define PC_CMD_PARR 	0x58 		// Cmd : Read paramter in F/W. 				2 addr, 1 data.
	#define PC_CMD_EEPW 	0x60 		// Cmd : Write paramter from F/W to EEP.
	#define PC_CMD_EEPR 	0x61 		// Cmd : Read paramter from EEP to F/W.
	//#define PC_CMD_EEPD 	0x62 		// Cmd : Write / Read for EEPROM is done.
	#define PC_CMD_PARK		0x68		// Cmd : Enable Parameter					4 data

	#define	PC_CMD_PAR_ALL	0xB8		// Cmd : Parameter all transfer to PC
	
	//#define PC_CMD_SENW 	0x70 		// Cmd : Write register in Sensor. 			2 addr, 4 data
	//#define PC_CMD_SENR 	0x78 		// Cmd : Read register from Sensor.

	#define ISPF_CMD_CM_INIT	0xA2
	#define ISPF_CMD_CM_W		0xA6
	#define	ISPF_CMD_CM_R		0xA4
	
	#define	ISPF_CMD_GMA_INIT	0xB2
	#define ISPF_CMD_GMA_W		0xB6
	#define ISPF_CMD_GMA_R		0xB4
	
#if (model_I2C_ch1 == 1)
	#define I2C_CMD_MENUW 	0x70/*0x50*/	// STX CMD ADH ADL WDH WDL ETX : Menu parameter write
	#define I2C_CMD_MENUR	0x78/*0x60*/	// STX CMD ADH ADL RDH RDL ETX : Menu parameter read
	#define I2C_CMD_CLOCK	/*0x70*/	// Cmd : Internet Standard Time
#endif

	#define PD_STG			0x80	// xFF ADD CMD CMD DAT DAT CRC			: Pelco-D
	#define PP_STG			0x90	// xA0 ADD DAT DAT DAT DAT xAF CRC		: Pelco-P

	#define PC_CMD_AWBI 	0xaa	// STX CMD ETX							: InitAwbOdmCap()

	#define	PC_CMD_STR		0xb0	// TxStr()
	#define	PC_CMD_GRP		0xc0	// TxGrp()
	#define	PC_CMD_ERR		0xd0	// TxErr()

	#define	PC_CMD_INI		0xe0	// STX CMD ETX							: UartRstQue()	- ?
	#define	PC_CMD_ACK		0xf0	// STX CMD ETX							: TxAck()		- ?

	#define PC_CMD_DOWN		0xf8	// STX CMD ETX							: Uart Download request Rx

#define	PC_ETX		0x03			// ETX

// Pelco D Protocol
#define PD_STX		0xFF

// Pelco P Protocol
#define PP_STX		0xA0
#define PP_ETX		0xAF

//-------------------------------------------------------------------------------------------------
// Snatch logic address (Regulate with logic address .CAUTION)
#define	BASE_SENS			0x3000		// 0x300 ea 		sensor control
#define BASE_EXT_CHIP		0x4000
#define BASE_EEPROM			0x6000
#define BASE_MICOM_PAR		0x8000

//-------------------------------------------------------------------------------------------------
// Debug Graph channel

#if model_AwbCapOn
	#define GRP_NUMBER			5
#else
	#define GRP_NUMBER			8
#endif

union uFLOAT{
	float	m_float;
	UINT	m_UINT;
};

#define	GRP0			(gnTxGrp[0].m_UINT)
#define	GRP1			(gnTxGrp[1].m_UINT)
#define	GRP2			(gnTxGrp[2].m_UINT)
#define	GRP3			(gnTxGrp[3].m_UINT)
#define	GRP4			(gnTxGrp[4].m_UINT)
#define	GRP5			(gnTxGrp[5].m_UINT)
#define	GRP6			(gnTxGrp[6].m_UINT)
#define	GRP7			(gnTxGrp[7].m_UINT)

// Don't use as possible (because of floating proc time)
#define	GRP0F			(gnTxGrp[0].m_float)
#define	GRP1F			(gnTxGrp[1].m_float)
#define	GRP2F			(gnTxGrp[2].m_float)
#define	GRP3F			(gnTxGrp[3].m_float)
#define	GRP4F			(gnTxGrp[4].m_float)
#define	GRP5F			(gnTxGrp[5].m_float)
#define	GRP6F			(gnTxGrp[6].m_float)
#define	GRP7F			(gnTxGrp[7].m_float)

//-------------------------------------------------------------------------------------------------
// Debug Parameter channel
#define	PAR00			(gnRxPar[ 0])
#define	PAR01			(gnRxPar[ 1])
#define	PAR02			(gnRxPar[ 2])
#define	PAR03			(gnRxPar[ 3])
#define	PAR04			(gnRxPar[ 4])
#define	PAR05			(gnRxPar[ 5])
#define	PAR06			(gnRxPar[ 6])
#define	PAR07			(gnRxPar[ 7])
#define	PAR08			(gnRxPar[ 8])
#define	PAR09			(gnRxPar[ 9])
#define	PAR0A			(gnRxPar[10])
#define	PAR0B			(gnRxPar[11])
#define	PAR0C			(gnRxPar[12])
#define	PAR0D			(gnRxPar[13])
#define	PAR0E			(gnRxPar[14])
#define	PAR0F			(gnRxPar[15])		// 170304 LH : reserved to LH
#define	PAR10			(gnRxPar[16])
#define	PAR11			(gnRxPar[17])
#define	PAR12			(gnRxPar[18])
#define	PAR13			(gnRxPar[19])
#define	PAR14			(gnRxPar[20])
#define	PAR15			(gnRxPar[21])
#define	PAR16			(gnRxPar[22])
#define	PAR17			(gnRxPar[23])
#define	PAR18			(gnRxPar[24])
#define	PAR19			(gnRxPar[25])
#define	PAR1A			(gnRxPar[26])
#define	PAR1B			(gnRxPar[27])
#define	PAR1C			(gnRxPar[28])
#define	PAR1D			(gnRxPar[29])
#define	PAR1E			(gnRxPar[30])
#define	PAR1F			(gnRxPar[31])

//-------------------------------------------------------------------------------------------------
// Extern
extern void Comm(void);

#define TxGrp()		giTxGrpOn = 1
#define TxGrpRun()	if(giTxGrpOn == 1) { TxGrpFnc(); giTxGrpOn = 0; }
extern void TxGrpFnc(void);

extern void TxStr(const char* apbStr0, UINT anVal, UINT anValLen);
extern void TxStrDec(const char* apbStr0, UINT anVal, UINT anValLen);
extern void TxStrDec2(const char* apbStr0, UINT anVal0, UINT anValLen0, UINT anVal1, UINT anValLen1);
extern void TxStrNoIRQ(const char* apbStr0, UINT anVal, UINT anValLen);
extern void TxStrDecNoIRQ(const char* apbStr0, UINT anVal, UINT anValLen);

extern UINT	gnRxPar[32];
extern union uFLOAT gnTxGrp[8];
extern int  giTxGrpOn;


//***********************************************************************************
// Debugging OSD
//-----------------------------------------------------------------------------------

#define DispDbgX	24

//#define DispDbgYmin		15/*1*/
#define DispDbgYmin		0/*1*/
#define DispDbgStrLen	11

extern void DispDbgH(char* cStr, const int aiVal, const UINT anLen);
extern void DispDbgD(char* cStr, const int aiVal, const UINT anLen);
extern void DispDbgB(char* cStr, const int aiVal, const UINT anLen);
extern void DispDbgP(char* cStr, const int aiVal, const int aiValMax, const UINT anLen);

extern void DispHex(const UINT anDispY, const UINT anDispX, const UINT anVal, const UINT anLen);
extern void DispDec(const UINT anDispY, const UINT anDispX, const int aiVal, const UINT anLen);
extern void DispBin(const UINT anDispY, const UINT anDispX, const UINT anVal, const UINT anLen);
extern void DispPer(const UINT anDispY, const UINT anDispX, const int aiVal, const int aiValMax, const UINT anLen);
extern void DispFlt(const UINT anDispY, const UINT anDispX, const float afVal, const int aiValNum, const UINT anLen);


extern void DispDatHex(char* cStr, const UINT anDispY, const UINT anDispX, const UINT anVal);
extern void DispDatDec(char* cStr, const UINT anDispY, const UINT anDispX, const int aiVal);
extern void DispDatPer(char* cStr, const UINT anDispY, const UINT anDispX, const int aiVal, const int aiValMax);
extern void DispDatFlt(char* cStr, const UINT anDispY, const UINT anDispX, const float afVal);

#define DispDat		DispDatHex
#define DebugDisp(ON, TYPE, STR, Y, X, VAL)	{if(ON) DispDat##TYPE( STR, Y, X, VAL );}	// Debug display by Debug mode

//-------------------------------------------------------------------------------------------------
// Extern
extern void TxStrMemAddrInfo(void);
extern void TxStrCacheSize(void);


#if STR_PELCO_DATA == 1
extern void DispPelcoData(void);
extern BYTE gbPDcnt;
extern BYTE gbPDadr;
extern WORD gwFld;
extern WORD gwPDfld;
extern UINT gnPDdat;
#else
#define DispPelcoData()
#endif

extern void TxStrWaitTime(const UINT anUs);
extern void TestWaitTime(const UINT anUs);
extern void DispTime(UINT anSec);
extern void DispWdt(void);
extern void TestAppSavePar(void);
extern void TestSerialFlash(void);
extern void TestIRQ(void);
extern void DispIsrStatus(void);

extern UINT gnDispDbgY;

extern UINT gnWaitTimeOffset;
extern UINT gnWaitTimeUnit;

extern char gbStr[ISP_FONT_MAX_PATH+1+1];


extern void ExtWR_Reg(WORD awAddr, UINT anData, BYTE abLength);
