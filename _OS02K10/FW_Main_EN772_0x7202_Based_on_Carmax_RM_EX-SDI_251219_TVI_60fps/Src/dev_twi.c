/* **************************************************************************
 File Name	: 	dev_twi.c
 Description:	EN772 - I2C device driver
 Designer	:	Jang, Young Kyu / Kim Sung-Hoon / Lee, hoon / Lee, Gyu Hong
 Date		:	20. 12. 01
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

volatile UINT gnI2cPacket[2] = { 0, 0 };	// IRQ Stack�� ���̱� ���� Global�� ����

void InitI2c(void)
{
	TxStrNoIRQ("I2C Init.", 0, 0);

	// I2C CH0 : Sensor control only
	I2C0_SYNC = 0;
	I2C0_CLK_DIV = I2C0_CLKDIV_MASTER;
	
	I2C0_MODE = 0;						//I2C Master ModeW
	I2C0_IRQ_EN = 0;					// I2C Irq disable

	// I2C CH1
#if (model_I2C_ch1==1)
	// Slave Mode
	I2C1_CLK_DIV = I2C1_CLKDIV_SLAVE;

	R_I2C1_ONw(0x1);
	DUCC_MUXw(0x0);
	
	I2C1_MODE = 1;						// I2C Slave Mode
	I2C1_IRQ_EN = 1;					// I2C Irq enable
	
	I2C1_SLV_ADR = (SLAVE_DEVICE>>1);	// I2C Slave device address
	
#elif(model_I2C_ch1==2)
	// Master Mode
	I2C1_CLK_DIV = I2C1_CLKDIV_MASTER;
	I2C1_MODE = 0;
	I2C1_IRQ_EN = 0;
	
	if(I2C1_ACT) {												// master check
		TxStrNoIRQ("  >>Another master is working...", 0, 0);
		while(I2C1_ACT);
	}
	
	#if (model_Save==0)											// eeprom check
	UINT i;
	for(i=0; i<10; i++) {
		if(i2c1_write(EEPROM_DEVICE,1,0) == 0) {
			gbEepromOff = 0;
			TxStrNoIRQ("  >>EEPROM Connected...", 0, 0);
			break;
		}
		WaitUs(100);
	}
	
	if(gbEepromOff) TxStrNoIRQ("  >>EEPROM Not Connected...", 0, 0);
	#endif
	
#endif

}

#if (model_I2C_ch1 == 1)

void ISPM0 IsrI2c(void)		// CAUTION!!! - Isr stack size = 0x400, Do not use a lot of variables.
{
	/*
	Interrupt Process Time = 6us @ 81MHz

	Master Mode IRQ
		1. when a byte transfer action(R/W) was finished.

	Slave Mode IRQ
		1. when a byte was written by Master.
		2. when a Read command is arrived.
		3. when a byte was read by Master.
	*/

	BYTE gbAdr_Flag1  = I2C1_ADR_FLAG ;
	BYTE gbLast_Flag1 = I2C1_LAST_FLAG;
	UINT i = 0;
	static IDATA snDataBuf = 0;
	static BYTE sbDataPos = 0;

	I2C1_IRQ_CLR = 1;

		switch(I2C1_SLV_RW)
		{
			case 0: 	// Write
			{

			if(gbAdr_Flag1){
				sbDataPos = 0;
				snDataBuf = 0;
			}
			else
			{
					volatile BYTE bData = I2C1_RX_DAT;	//	Received Data from Master
								
					if(sbDataPos >= I2C_LENGTH) 	return;
			
					gbI2cPacket[sbDataPos++] = (bData&0xFF);
			
					if(sbDataPos == I2C_ADDR_NUM)	  {
						for(i=0; i<I2C_ADDR_NUM; i++)			gAddr |= (gbI2cPacket[i]<<(8*(I2C_ADDR_NUM-1-i)));
					}
			
					else if(sbDataPos == I2C_LENGTH){
		//				for(i=I2C_ADDR_NUM; i<I2C_LENGTH; i++)	gData |= (gbI2cPacket[i]<<((i-I2C_ADDR_NUM)*8));
						for(i=I2C_ADDR_NUM; i<I2C_LENGTH; i++)	gData |= (gbI2cPacket[i]<<(8*(I2C_DATA_NUM+1-i)));
						sbDataPos = 0;

						#if((model_IspO_MIPI)&&(model_USB_CX3))
							USB_MenuCtrl_I2C();
						#endif
						
						gAddr = 0;
						gData = 0;
					}
			}
				
				break;
			}
			case 1: 	// Read
			{
			
				if(gbLast_Flag1) {
					sbDataPos = 0;
					snDataBuf = 0;
//					TxStrNoIRQ("SLV NACK",0,0);
					
					break;		//	Read Process End - Master wasn't acknowledged
				}
				else	// Read continue
				{				
					if(sbDataPos==I2C_ADDR_NUM){
						snDataBuf = GetIsp(gAddr);
						gAddr = 0;
	//						for(i=I2C_ADDR_NUM; i<I2C_LENGTH; i++)	gbI2cPacket[i] = ((snDataBuf>>((I2C_DATA_NUM-i)*8))&0xFF);
						for(i=I2C_ADDR_NUM; i<I2C_LENGTH; i++)	gbI2cPacket[i] = ((snDataBuf>>((i-I2C_ADDR_NUM)*8))&0xFF); // lsb ???? ??��?. 
					}
					I2C1_TX_DAT = gbI2cPacket[sbDataPos++];
					
					break;
				}
					
			}
		}
//		WaitUs(1000);
		I2C1_SLV_GO = 1;		//	Release SCL holding, Master can put a next data
}

#endif



//*************************************************************************************************
// I2C Application driver (general 3.3V IO)
//-------------------------------------------------------------------------------------------------

#if (model_I2C_ch1 == 2)

BYTE gbEepromOff = 1;

BYTE ISPM0 i2c1_write(BYTE dat, BYTE last, BYTE repeat)
{
	I2C1_TX_DAT = dat;
	I2C1_CONT_MST = (I2C1_CONT_MST&0xFFFF0000) | (repeat<<3) | ((repeat | last)<<2) | 3;
	while(I2C1_MST_GO);
	return I2C1_MST_ACK /*|| I2C1_MST_COL*/;
}

BYTE ISPM0 i2c1_read(BYTE last, BYTE repeat)
{
	I2C1_CONT_MST = (I2C1_CONT_MST&0xFFFF0000) | (repeat<<3) | ((repeat | last)<<2) | 1;
	while(I2C1_MST_GO);
	return I2C1_RX_DAT;
}

BYTE eep_write(UINT anAddr, BYTE abData)	// 201 us
{
	if(gbEepromOff) return 0;

	while(i2c1_write(EEPROM_DEVICE,0,0));	// Avg. 47 us (I2C_CLK = 290KHz)
	
	i2c1_write((anAddr&0x1f00)>>8, 0,0);
	i2c1_write((anAddr&0xff), 0,0);

	i2c1_write(abData, 1,0);

	return 0;
}

BYTE eep_read(const WORD awAddr, BYTE* abData, const UINT anDataEa)	// 248 us (anDataEa = 1, I2C_CLK = 290KHz)
{
	if(gbEepromOff) return 0;

	while(i2c1_write(EEPROM_DEVICE,0,0));
	
	i2c1_write((awAddr&0x1f00)>>8, 0,0);
	i2c1_write((awAddr&0xff), 0,1);

	i2c1_write(EEPROM_DEVICE | 0x1, 0,0);

	UINT i;
	for(i=1; i<anDataEa; i++)
	{
		*abData = i2c1_read(0,0);
		abData++;
	}
	*abData = i2c1_read(1,0);
		
	return 0;
}

BYTE EepPageWrite(const WORD awWaddr, BYTE* apbBuf, const UINT anBufEa)
{
	// 24LC64 Page Write
	// The master transmits up to 31 additional bytes which are temporarily stored in the on-chip page buffer
	//  and will be written into memory after the master has transmitted a stop condition.
	// After receipt of each word, the 5 lower address pointer bits are internally incremented by 1.
	// If the master should transmit more than 32 bytes prior to generating the stop condition,
	//  the address counter will roll over and the previously received data will be overwritten.
	//
	// If an attempt is made to write to the array with the WP pin held high,
	//  the device will acknowledge the command but no write cycle will occur,
	//  no data will be written and the device will immediately accept a new command.

	if(gbEepromOff) return 0;

	while(i2c1_write(EEPROM_DEVICE,0,0));

	i2c1_write((awWaddr&0x1f00)>>8, 0,0);
	i2c1_write((awWaddr&0xff), 0,0);
	
	UINT i;
	for(i=1; i<anBufEa; i++)
	{
		i2c1_write(*apbBuf, 0,0);
		apbBuf++;
	}

	i2c1_write(*apbBuf, 1,0);

	return 0;
}


BYTE gbEeprom_Busy=0;	// 150128 HSH
BYTE ISPM TwiWrEep2( WORD awWaddr, BYTE* apbBuf, UINT anBufEa)
{	// I2C EEPROM Page(32byte) Write Function
	// CAUTION ! :
	//			1 page Tx per 2 frame , because EEP restart delay)
	//			Fuction recall delay = after (*apbBuf ea / TWI_EEP_BYTE_EA) frame
	// apwWaddr : Start address
	// * apbBuf : input data p
	// anBufEa	: input data ea of byte

	static WORD gwWaddr;
	static BYTE k,l;
	static BYTE* gpbBuf;
	static BYTE gbTwiCnt;
		   BYTE bTwiCnt;

	WORD 		wRegAddrBuf;
	//BYTE 		bRegAddr[2];
	//BYTE 		i,t;

	if (gbTwiCnt%2)	{ gbTwiCnt++; return 0; }					// 1 page Tx per 2 frame
	else 			{ bTwiCnt = gbTwiCnt>>1; }

	if (!bTwiCnt) {											// Burst Tx Ready
		if (!anBufEa)	return 0;
		else if ((awWaddr+anBufEa)>=(TWI_EEP_PAGE_EA*TWI_EEP_BYTE_EA)) {
			TxStrNoIRQ("WrEEP Size Over ! ", 0, 0);
			return 0;
		}
		else {
			gwWaddr = awWaddr;
			gpbBuf  = apbBuf;
			k = anBufEa / TWI_EEP_BYTE_EA;
			l = anBufEa % TWI_EEP_BYTE_EA;

			gbTwiCnt++;
			return 0;
		}
	}
	else if (bTwiCnt>=k+2) {								// Status reset at Tx end
		TxStrNoIRQ("TwiWrEep2 Done ! ", gwWaddr, 5);

		gwWaddr = 0;
		gpbBuf  = 0;
		k = 0;
		l = 0;
		gbTwiCnt = 0;
		gbEeprom_Busy = 0;
		return 1;											// Tx end flag
	}
	else {
		wRegAddrBuf = (bTwiCnt-1) * TWI_EEP_BYTE_EA;

		EepPageWrite(gwWaddr + wRegAddrBuf, gpbBuf + wRegAddrBuf, (bTwiCnt<k+1) ? TWI_EEP_BYTE_EA : l);
		//TxStrDec2("EepPageWrite :", gwWaddr + wRegAddrBuf, 5, (bTwiCnt<k+1) ? TWI_EEP_BYTE_EA : l, 3);

		gbTwiCnt++;

		gbEeprom_Busy = 1;

		return 0;
	}
}

#endif	// end of model_I2C_ch1 == 2 	// 171206 LH : postion moved

//*************************************************************************************************
// SI2C (dedicated channel for sensor control. 1.8v, Master only)
//-------------------------------------------------------------------------------------------------
BYTE gbSensorOff = 1;		// 171206 LH

BYTE ISPM0 i2c_write(BYTE dat, BYTE last, BYTE repeat)
{
	I2C0_TX_DAT = dat;
	I2C0_CONT_MST = (I2C0_CONT_MST&0xFFFF0000) | (repeat<<3) | ((repeat | last)<<2) | 3;
	while(I2C0_MST_GO);
	return I2C0_MST_ACK /*|| I2C0_MST_COL*/;
}

BYTE ISPM0 i2c_read(BYTE last, BYTE repeat)
{
	I2C0_CONT_MST = (I2C0_CONT_MST&0xFFFF0000) | (repeat<<3) | ((repeat | last)<<2) | 1;
	while(I2C0_MST_GO);
	return I2C0_RX_DAT;
}

//#if model_Sony
void ISPM0 SetSensTwi_Sony(BYTE abDevaddr, WORD awAddr, BYTE abData)
{	// Write to Sensor
	if(gbSensorOff) return;
	
	while(i2c_write(abDevaddr,0,0));	// Avg. 47 us (I2C_CLK = 290KHz)

	i2c_write((awAddr>>8)&0xff, 0,0);
	i2c_write((awAddr>>0)&0xff, 0,0);
	i2c_write(abData, 1,0);

	return;
}

BYTE ISPM0 GetSensTwi_Sony(BYTE abDevaddr, WORD awAddr)
{	// Read from Sensor
	if(gbSensorOff) return 0;
		
	BYTE bData;
	
	//----------------------------------------------------------------------------------------
	// Tx Addr
	while(i2c_write(abDevaddr,0,0));

	i2c_write((awAddr>>8)&0xff, 0,0);
	i2c_write((awAddr>>0)&0xff, 0,1);

	//----------------------------------------------------------------------------------------
	// Rx data
	i2c_write(abDevaddr|0x1,0,0);
	bData = i2c_read(1,0);

	return bData;
}

void ISPM0 SetSensTwiBst_Sony(BYTE abDevaddr, WORD awAddr, UINT anData, UINT anNum)
{	// Write to Sensor
	if(gbSensorOff) return;
	
	UINT i = 0;
	
	while(i2c_write(abDevaddr,0,0));	// Avg. 47 us (I2C_CLK = 290KHz)

	i2c_write((awAddr>>8)&0xff, 0,0);
	i2c_write((awAddr>>0)&0xff, 0,0);

	for(i = 0; i < anNum-1; i++){
	i2c_write(((anData>>(i*8))&0xFF), 0,0);
	}
		
	i2c_write(((anData>>(i*8))&0xFF), 1,0);
	
	return;
}


//#elif model_Onsemi
void ISPM0 SetSensTwi_Onsemi(BYTE abDevaddr, WORD awAddr, WORD abData)
{	// Write to Sensor

	if(gbSensorOff) return;
		
	while(i2c_write(abDevaddr,0,0));	// Avg. 47 us (I2C_CLK = 290KHz)

	i2c_write(awAddr>>8, 0,0);
	i2c_write(awAddr   , 0,0);

	i2c_write(abData>>8, 0,0);
	i2c_write(abData   , 1,0);

	return;
}

WORD ISPM0 GetSensTwi_Onsemi(BYTE abDevaddr, WORD awAddr)
{	// Read from Sensor

	if(gbSensorOff) return 0;

	WORD wData = 0;

	while(i2c_write(abDevaddr,0,0));

	//----------------------------------------------------------------------------------------
	// Tx Addr
	i2c_write(awAddr>>8, 0,0);
	i2c_write(awAddr   , 0,1);

	//----------------------------------------------------------------------------------------
	// Rx data
	i2c_write(abDevaddr | 0x1, 0,0);

	wData = i2c_read(0,0);
	wData = (wData<<8) | i2c_read(1,0);

	return wData;
}

void ISPM0 SetSensTwi_Omni(BYTE abDevaddr, WORD awAddr, BYTE abData)
{	// Write to Sensor
	if(gbSensorOff) return;

	while(i2c_write(abDevaddr,0,0));	// Avg. 47 us (I2C_CLK = 290KHz)

#if((model_Sens==SENS_OS02H10)||(model_Sens==SENS_OS02D20))
	i2c_write((awAddr>>0)&0xff, 0,0);
#else
	i2c_write((awAddr>>8)&0xff, 0,0);
	i2c_write((awAddr>>0)&0xff, 0,0);
#endif
	i2c_write(abData, 1,0);

	return;
}

BYTE ISPM0 GetSensTwi_Omni(BYTE abDevaddr, WORD awAddr)
{	// Read from Sensor
	if(gbSensorOff) return 0;
	
	BYTE bData;

	//----------------------------------------------------------------------------------------
	// Tx Addr
	while(i2c_write(abDevaddr,0,0));

#if((model_Sens==SENS_OS02H10)||(model_Sens==SENS_OS02D20))
	i2c_write((awAddr>>0)&0xff, 0,1);
#else
	i2c_write((awAddr>>8)&0xff, 0,0);
	i2c_write((awAddr>>0)&0xff, 0,1);
#endif

	//----------------------------------------------------------------------------------------
	// Rx data
	i2c_write(abDevaddr|0x1,0,0);
	bData = i2c_read(1,0);

	return bData;
}

void ISPM0 SetSensTwiBst_Omni(BYTE abDevaddr, WORD awAddr, UINT anData, UINT anNum)
{	// Write to Sensor
	if(gbSensorOff) return;
	
	UINT i = 0;
	
	while(i2c_write(abDevaddr,0,0));	// Avg. 47 us (I2C_CLK = 290KHz)

	i2c_write((awAddr>>8)&0xff, 0,0);
	i2c_write((awAddr>>0)&0xff, 0,0);

	for(i = anNum-1; i > 0; i--){
	i2c_write(((anData>>(i*8))&0xFF), 0,0);
	}
		
	i2c_write(((anData>>(i*8))&0xFF), 1,0);
	
	return;
}

void ISPM0 SetSensTwi_GC(BYTE abDevaddr, WORD wAddr, BYTE abData)
{	// Write to Sensor

	while(i2c_write(abDevaddr,0,0));	// Avg. 47 us (I2C_CLK = 290KHz)

#if(model_Sens==SENS_GC2053)
	i2c_write((BYTE)(wAddr&0xff),  0,0);
#else
	i2c_write(wAddr>>8&0xff, 0,0);
	i2c_write(wAddr&0xff,  0,0);
#endif

	i2c_write(abData, 1,0);
	return;
}

BYTE ISPM0 GetSensTwi_GC(BYTE abDevaddr, WORD wAddr)
{	// Read from Sensor

	BYTE bData;
	
	while(i2c_write(abDevaddr,0,0));

#if(model_Sens==SENS_GC2053)
	i2c_write((BYTE)(wAddr&0xff), 0,1);
#else
	i2c_write(wAddr>>8&0xff, 0,0);
	i2c_write(wAddr&0xff, 0,1);
#endif

	i2c_write(abDevaddr | 0x1, 0,0);

	bData = i2c_read(1,0);

	return bData;
}

void ISPM0 SetSensTwi_Pxpls(BYTE abDevaddr, BYTE abAddr, BYTE abData)
{	// Write to Sensor
	if(gbSensorOff) return;
	
	while(i2c_write(abDevaddr,0,0));	// Avg. 47 us (I2C_CLK = 290KHz)

	i2c_write((abAddr&0xff), 0,0);
	i2c_write(abData, 1,0);

	return;
}

BYTE ISPM0 GetSensTwi_Pxpls(BYTE abDevaddr, BYTE abAddr)
{	// Read from Sensor
	if(gbSensorOff) return 0;
		
	BYTE bData;
	
	//----------------------------------------------------------------------------------------
	// Tx Addr
	while(i2c_write(abDevaddr,0,0));

	i2c_write((abAddr&0xff), 0,1);
	//----------------------------------------------------------------------------------------
	// Rx data
	i2c_write(abDevaddr|0x1,0,0);
	bData = i2c_read(1,0);

	return bData;
}

void ISPM0 SetSensTwiBst_Pxpls(BYTE abDevaddr, BYTE abAddr, UINT anData, UINT anNum)
{	// Write to Sensor
	if(gbSensorOff) return;
	
	UINT i = 0;
	
	while(i2c_write(abDevaddr,0,0));	// Avg. 47 us (I2C_CLK = 290KHz)
	i2c_write((abAddr&0xff), 0,0);

	for(i = 0; i < anNum-1; i++){
	i2c_write(((anData>>(i*8))&0xFF), 0,0);
	}
		
	i2c_write(((anData>>(i*8))&0xFF), 1,0);
	
	return;
}

void ISPM0 SetSensTwi_SC(BYTE abDevaddr, WORD wAddr, BYTE abData)
{	// Write to Sensor

	while(i2c_write(abDevaddr,0,0));	// Avg. 47 us (I2C_CLK = 290KHz)

	i2c_write(wAddr>>8&0xff, 0,0);
	i2c_write(wAddr&0xff,  0,0);

	i2c_write(abData, 1,0);
	return;
}

BYTE ISPM0 GetSensTwi_SC(BYTE abDevaddr, WORD wAddr)
{	// Read from Sensor

	BYTE bData;
	
	while(i2c_write(abDevaddr,0,0));

	i2c_write(wAddr>>8&0xff, 0,0);
	i2c_write(wAddr&0xff, 0,1);

	i2c_write(abDevaddr | 0x1, 0,0);

	bData = i2c_read(1,0);

	return bData;
}


//#elif model_Pana
void ISPM0 SetSensTwi_Pana(BYTE abDevaddr, WORD awAddr, BYTE abData)
{	// Write to Sensor

	while(i2c_write(abDevaddr,0,0));	// Avg. 47 us (I2C_CLK = 290KHz)

	i2c_write((awAddr>>8)&0xff, 0,0);
	i2c_write((awAddr>>0)&0xff, 0,0);
	i2c_write(abData, 1,0);

	return;
}

BYTE ISPM0 GetSensTwi_Pana(BYTE abDevaddr, WORD awAddr)
{	// Read from Sensor
	if(gbSensorOff) return 0;
	
	BYTE bData;

	//----------------------------------------------------------------------------------------
	// Tx Addr
	while(i2c_write(abDevaddr,0,0));

	i2c_write((awAddr>>8)&0xff, 0,0);
	i2c_write((awAddr>>0)&0xff, 0,1);

	//----------------------------------------------------------------------------------------
	// Rx data
	i2c_write(abDevaddr|0x1,0,0);
	bData = i2c_read(1,0);

	return bData;
}

//#endif

