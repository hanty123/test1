/* **************************************************************************
 File Name	: 	dev_uart.c
 Description	:	EN772 - UART device driver
 Designer		:	Jang, Young Kyu / Kim Sung-Hoon
 Date		:	14. 6. 18
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

void InitUart(void)
{
	UART0_CLKDIV = UB_INIT;	//BPS

	UartRstQue();

	UART0_TX_IRQ_EN = 0;
	UART1_TX_IRQ_EN = 0;

	while(!UART0_RX_EMPTY) {UNUSED_ARG(UART0_RX_DAT);}	// 151223	KSH
	UART0_RX_IRQ_EN = 1;

#if model_UccD == 1 || model_Uart2 == 1
	// 170602 HTY
	#if	(model_UccD == 1) || (model_Uart2 == 1)
		UART1_CLKDIV = UB_UCC_INIT;
	#endif

	Uart1RstRxQue();

	while(!UART1_RX_EMPTY) { UNUSED_ARG(UART1_RX_DAT); }	// 151223 KSH
	UART1_RX_IRQ_EN = 1;

	#if model_Uart2 == 1
		Uart1RstTxQue();
	#endif


#endif

}


// UART0 Transmitter & Receiver
void Uart_Tx(char dat)
{
	while(UART0_TX_FULL);
	UART0_TX_DAT = dat;
}

void Uart_Rx(char *dat)
{
	while(UART0_RX_EMPTY);
	*dat = UART0_RX_DAT;
}

//-------------------------------------------------------------------------------------------------
// Utility
void uart_str(const char *text)
{
	while(*text){
		//if(*text == '\n')		Uart_Tx('\r');
		Uart_Tx(*text++);
	}
}
void ISPM UartTxStr(const char *apcStr)
{	// String out (Guarantee Tx)
	while(*apcStr){													// Check 'NULL' character
		//if(*apcStr == '\n')		UartTxByte('\r');					// Move cursor to left
		UartTxByte(*apcStr++);										// Put 1 byte
	}
}

//*************************************************************************************************
// Isr
//-------------------------------------------------------------------------------------------------
//
TUartQue gtUartQue;
volatile int giTxOn = 0;

void UartRstRxQue(void)
{
	gtUartQue.wRxLen = 0;
	gtUartQue.pbRxHead = &gtUartQue.bRxQue[0];
	gtUartQue.pbRxTail = &gtUartQue.bRxQue[0];
}

void UartRstTxQue(void)
{
	gtUartQue.wTxLen = 0;
	gtUartQue.pbTxHead = &gtUartQue.bTxQue[0];
	gtUartQue.pbTxTail = &gtUartQue.bTxQue[0];
}

void UartRstQue(void)
{
	UartRstRxQue();
	UartRstTxQue();
}

void ISPM0 UartTxByte(BYTE abByte)
{
	while(gtUartQue.wTxLen >= UART_BUF_SIZE) {TxStrNoIRQ("Uart buffer size over !", 0, 0); NOP4 };		// Wait until the Tx operate. If DI() state, The result in an infinite loop.

	UART0_TX_IRQ_EN = 0;
	giTxOn = 1;
	*gtUartQue.pbTxHead++ = abByte;
	if( gtUartQue.pbTxHead == &gtUartQue.bTxQue[UART_BUF_SIZE-1]){
		gtUartQue.pbTxHead  = &gtUartQue.bTxQue[0];
	}
	gtUartQue.wTxLen++;
	giTxOn = 0;
	/*if(gtUartQue.wTxLen == 1)*/	UART0_TX_IRQ_EN = 1;
}

//-------------------------------------------------------------------------------------------------
// UART CH2 Rx

// UART1 Transmitter & Receiver
void Uart1_Tx(char dat)
{
	while(UART1_TX_FULL);
	UART1_TX_DAT = dat;
}

void Uart1_Rx(char *dat)
{
	while(UART1_RX_EMPTY);
	*dat = UART1_RX_DAT;
}


#if model_UccD == 1 || model_Uart2 == 1
TUartRxQue gtUart1RxQue;

void Uart1RstRxQue(void)
{
	gtUart1RxQue.wRxLen = 0;
	gtUart1RxQue.pbRxHead = &gtUart1RxQue.bRxQue[0];
	gtUart1RxQue.pbRxTail = &gtUart1RxQue.bRxQue[0];
}

void ISPM0 IsrUart1Rx(void)
{
	volatile BYTE bUART_RX_IRQ = UART1_RX_IRQ;

	while(bUART_RX_IRQ)
	{
		UART1_RX_IRQ_CLR = 1;

		do {
			if(UART1_RX_EMPTY) break;
			else {
				volatile BYTE bBuf = UART1_RX_DAT;
				
				if(gtUart1RxQue.wRxLen < (UART_BUF_SIZE-1)) {
					*gtUart1RxQue.pbRxHead++ = bBuf;
					if(gtUart1RxQue.pbRxHead == (gtUart1RxQue.bRxQue + UART_BUF_SIZE)) {
						gtUart1RxQue.pbRxHead = gtUart1RxQue.bRxQue;
					}
					gtUart1RxQue.wRxLen++;
				}
				else {
					//TxStr("UART1 RX FULL", bDat,4);
				}
			}

		} while ( 1/*UART1_RX_EMPTY == 0*/ );

		bUART_RX_IRQ = UART1_RX_IRQ;
	}
}

#else
	#define IsrUart1Rx()
#endif

//-------------------------------------------------------------------------------------------------
// UART CH2 Tx
#if model_Uart2 == 1
TUartTxQue gtUart1TxQue;

volatile int giTx1On = 0;

void Uart1RstTxQue(void)
{
	gtUart1TxQue.wTxLen = 0;
	gtUart1TxQue.pbTxHead = &gtUart1TxQue.bTxQue[0];
	gtUart1TxQue.pbTxTail = &gtUart1TxQue.bTxQue[0];
}

void ISPM0 Uart1TxByte(BYTE abByte)
{
#if 1
	while(gtUart1TxQue.wTxLen >= UART_BUF_SIZE) { NOP4 };		// Wait until the Tx operate. If DI() state, The result in an infinite loop.
#else
	if(gtUart1TxQue.wTxLen >= UART_BUF_SIZE) return;	// The Tx data is lost.
#endif

	UART1_TX_IRQ_EN = 0;
	giTx1On = 1;
	*gtUart1TxQue.pbTxHead++ = abByte;
	if( gtUart1TxQue.pbTxHead == &gtUart1TxQue.bTxQue[UART_BUF_SIZE-1]){
		gtUart1TxQue.pbTxHead  = &gtUart1TxQue.bTxQue[0];
	}
	gtUart1TxQue.wTxLen++;
	giTx1On = 0;
	/*if(gtUart1TxQue.wTxLen == 1)*/	UART1_TX_IRQ_EN = 1;
}

void ISPM Uart1TxStr(const char *apcStr)
{	// String out (Guarantee Tx)
	while(*apcStr){													// Check 'NULL' character
		//if(*apcStr == '\n')		Uart1TxByte('\r');					// Move cursor to left
		Uart1TxByte(*apcStr++);										// Put 1 byte
	}
}

void ISPM0 IsrUart1Tx(void)
{
	volatile BYTE bUART_TX_IRQ = UART1_TX_IRQ;

	while(bUART_TX_IRQ)
	{
		if(giTx1On) { UART1_TX_IRQ_EN = 0; break; }
		else {

			do {
				if(gtUart1TxQue.wTxLen == 0) {
					UART1_TX_IRQ_EN = 0;
					break;
				}
				else {
					UART1_TX_DAT = *gtUart1TxQue.pbTxTail++;

					if(	gtUart1TxQue.pbTxTail == &gtUart1TxQue.bTxQue[UART_BUF_SIZE-1]) {
						gtUart1TxQue.pbTxTail  = &gtUart1TxQue.bTxQue[0];
					}
					gtUart1TxQue.wTxLen--;
				}
			} while( UART1_TX_FULL == 0 );
		}

		bUART_TX_IRQ = UART1_TX_IRQ;
	}
}
#else
	#define IsrUart1Tx()
#endif

//-------------------------------------------------------------------------------------------------
// UART Isr

void ISPM0 IsrUart(void)		// CAUTION!!! - Isr stack size = 0x400, Do not use a lot of variables.
{
	IsrUart1Rx();
	IsrUart1Tx();

	volatile BYTE bUART_RX_IRQ = UART0_RX_IRQ;
	volatile BYTE bUART_TX_IRQ = UART0_TX_IRQ;

	//static BYTE bRx[2] = { 0, 0 };

	while(bUART_RX_IRQ)
	{
		UART0_RX_IRQ_CLR = 1;
		
		//volatile BYTE bBuf;

		do {
			if(UART0_RX_EMPTY) break;
			else {
				volatile BYTE bBuf = UART0_RX_DAT;

				if(gtUartQue.wRxLen < (UART_BUF_SIZE-1)) {

					*gtUartQue.pbRxHead++ = bBuf;
					if(gtUartQue.pbRxHead == (gtUartQue.bRxQue + UART_BUF_SIZE)) {
						gtUartQue.pbRxHead = gtUartQue.bRxQue;
					}
					gtUartQue.wRxLen++;
				}
				else {
					//TxStr("UART RX FULL", bDat,4);
				}
			}

		} while ( 1/*UART0_RX_EMPTY == 0*/ );

		bUART_RX_IRQ = UART0_RX_IRQ;
	}

	while(bUART_TX_IRQ)
	{
		if(giTxOn) { UART0_TX_IRQ_EN = 0; break; }
		else {

			do {
				if(gtUartQue.wTxLen == 0) {
					UART0_TX_IRQ_EN = 0;
					break;
				}
				else {
					UART0_TX_DAT = *gtUartQue.pbTxTail++;

					if(	gtUartQue.pbTxTail == &gtUartQue.bTxQue[UART_BUF_SIZE-1]) {
						gtUartQue.pbTxTail  = &gtUartQue.bTxQue[0];
					}
					gtUartQue.wTxLen--;
				}
			} while( UART0_TX_FULL == 0 );
		}

		bUART_TX_IRQ = UART0_TX_IRQ;
	}
}



