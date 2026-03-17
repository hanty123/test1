/* **************************************************************************
 File Name	: 	dev_flash.c
 Description	:	EN772 - Serial flash controller
 Designer		:	Jang, Young Kyu / Kim Sung-Hoon
 Modifier		:	Lee, Gyu Hong
 Date		:	18. 4. 27
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

#define FLASH_EMPTY			0xFF
#define FLASH_VALID			0xFE
#define FLASH_INVALID		0xF0

/* Rolling addr seq.

  			begin    erase 	write  end
  user1 : 	FE	______ FE  ________ F0
  user2 :	F0  ______ FF  ________ FE

*/

// CAUTION ! WDT reset for long time burst proc

//*************************************************************************************************
// Base
//-------------------------------------------------------------------------------------------------
void InitFlash(void)
{
	TxStrNoIRQ("Flash Init.", 0, 0);

//	sfls_init();

	//SINGLE
	SFLS_CLKDIV = 1;		// Quad Read Mode�� ���� 2�� ���� ����. SFLS_CLKDIV = 2�� �ϸ� 3�� ���� ����.
//	SFLS_CLKDIV = 3;		// Quad Read Mode�� ���� 2�� ���� ����. SFLS_CLKDIV = 2�� �ϸ� 3�� ���� ����.		(18.625MHz)
	SFLS_REG_WB_REQ = 1;

	SetIsp(0x388, 0x0);
	
	#if(0)
	SFLS_WB_RDCMD = 0x3B;		//DUAL
	SFLS_WB_WRCMD = 0x02;
	SFLS_WBCONT = 0x00141000;
	SFLS_CMD = 0x10010000;
	while(SFLS_REG_REQ);
	#endif
	
	gbSFLS_WB_RDCMD_IOM = SFLS_WB_RDCMD_IOM;
	SFLS_WB_WAIT_EN = 1;
	SfWrInit;
}


#define UART_STR(STR)	TxStrNoIRQ(STR, 0, 0)/*uart_str(MSG)*/

BYTE gbSF_Status = 0;
BYTE gbSFLS_WB_RDCMD_IOM = 0;

void sfls_init(void)
{
	BYTE Manu, Type, Capa;
	// Get Flash Info
	SFLS_REG_CMD = 0x9f;
	SFLS_CMD = 0xf0021002;
	while(SFLS_REG_REQ);
	Manu = (SFLS_DATOUT & 0xFF000000)>>24;
	Type = (SFLS_DATOUT & 0x00FF0000)>>16;
	Capa = (SFLS_DATOUT & 0x0000FF00)>>8;
	
//	uart_printf("MANU : ",Manu);
//	uart_printf("TYPE : ",Type);
//	uart_printf("CAPA : ",Capa);
//	UART_STR("SerialFlash : ");

	switch(Manu)
	{
		case 0x1C:	//	EON
		{
			switch(Type)
			{
				case 0x30:	//	QUAD
				case 0x31:	//	SINGLE
					switch(Capa)
					{
						case 0x16:{UART_STR("EN25F32-SINGLE"); break;}//	EN25F32
						case 0x15:{UART_STR("EN25F16-SINGLE"); break;}//	EN25F16
						case 0x14:{UART_STR("EN25F80-SINGLE"); break;}//	EN25F80
						case 0x13:{UART_STR("EN25F40-SINGLE"); break;}//	EN25F40
						case 0x12:{UART_STR("EN25F20-SINGLE"); break;}//	EN25F20
						case 0x11:{UART_STR("EN25F10-SINGLE"); break;}//	EN25F10
					}
					SFLS_CMD = 0x10020000;
//					SFLS_CMD = 0x30020000;
					while(SFLS_REG_REQ);
					break;
			}
			break;
		}
		case 0xEF:	//	Winbond
		{
			switch(Type)
			{
				case 0x40:
				case 0x30:	//	DUAL
				{
					switch(Capa)
					{
						case 0x13:{UART_STR("W25X40-DUAL");break;}	//	W25X20DV
						case 0x12:{UART_STR("W25X20-DUAL");break;}	//	W25X20DV
						case 0x11:{UART_STR("W25X10-DUAL");break;}	//	W25X10DV
					}
					SFLS_WB_RDCMD = 0x3B;		//	DUAL
					SFLS_WB_WRCMD = 0x02;
					SFLS_WBCONT = 0x00141000;
					SFLS_CMD = 0x10010000;
//					SFLS_CMD = 0x30010000;
					while(SFLS_REG_REQ);
					break;
				}
			}
			break;
		}
		
		case 0xBF:	//	SST
		{
			switch(Type)
			{
				case 0x25:	//	SINGLE
				{
					switch(Capa)
					{
						case 0x8D:{UART_STR("SST25VF040B-SINGLE");break;}	//	SST25VF040B
						case 0x8E:{UART_STR("SST25VF080B-SINGLE");break;}	//	SST25VF080B
						case 0x41:{UART_STR("SST25VF016B-SINGLE");break;}	//	SST25VF016B
						case 0x4A:{UART_STR("SST25VF032B-SINGLE");break;}	//	SST25VF032B
						case 0x4B:{UART_STR("SST25VF064C-SINGLE");break;}	//	SST25VF064C
					}
					SFLS_REG_CMD = 0x50;
					SFLS_CMD = 0x10020000;		//	WE + MCK/2
					while(SFLS_REG_REQ);
					SFLS_WB_RDCMD = 0x0B;		//	High speed Read Cmd
					SFLS_WB_WRCMD = 0x02;
					SFLS_WBCONT = 0x00140000;
					SFLS_CMD = 0x10010000;	//
					while(SFLS_REG_REQ);
					SFLS_REG_CMD = 0x01;
					SFLS_DATIN = 0x00000000;	//	Delete Write Protection
					SFLS_CMD = 0x10021C00;
//					SFLS_CMD = 0x30021C00;
					while(SFLS_REG_REQ);
					break;
				}
				case 0x26:	//	SINGLE
				{
					switch(Capa)
					{
						case 0x01:	//	SST26VF016
						case 0x02:	//	SST26VF032
						{
							if(Capa==0x01) UART_STR("SST26VF016-SINGLE");
							else if(Capa==0x02) UART_STR("SST26VF032-SINGLE");
							SFLS_REG_CMD = 0x50;
							SFLS_CMD = 0x10020000;		//	WE + MCK/2
							while(SFLS_REG_REQ);
							SFLS_WB_RDCMD = 0x0B;		//	High speed Read Cmd
							SFLS_WB_WRCMD = 0x02;
							SFLS_WBCONT = 0x00140000;
							SFLS_CMD = 0x10010000;	//
							while(SFLS_REG_REQ);
							SFLS_REG_CMD = 0x01;
							SFLS_DATIN = 0x00000000;	//	Delete Write Protection
							SFLS_CMD = 0x10021C00;
//							SFLS_CMD = 0x30021C00;
							while(SFLS_REG_REQ);
						}
					}
					break;
				}
			}
			break;
		}
		case 0x8C:	//	ESMT
		{
			switch(Type)
			{
				case 0x40:	//	QUAD
				case 0x41:	//	QUAD
				case 0x30:	//	DUAL
				{
					switch(Capa)
					{
						case 0x10:{UART_STR("F25L05PA-DUAL");break;}	//	F25L05PA
						case 0x11:{UART_STR("F25L01PA-DUAL");break;}	//	F25L01PA
						case 0x12:{UART_STR("F25L02PA-DUAL");break;}	//	F25L02PA
						case 0x13:{UART_STR("F25L04PA-DUAL");break;}	//	F25L04PA
					}
					SFLS_WB_RDCMD = 0x3B;		//	DUAL
					SFLS_WB_WRCMD = 0x02;
					SFLS_WBCONT = 0x00141000;
					SFLS_CMD = 0x10010000;
//					SFLS_CMD = 0x30010000;
					while(SFLS_REG_REQ);
					break;
				}
				case 0x20:	//	DUAL
				{
					switch(Capa)
					{
						case 0x16:{UART_STR("F25L32PA-DUAL");break;}	//	F25L32PA
						case 0x15:{UART_STR("F25L16PA-DUAL");break;}	//	F25L16PA
						case 0x14:{UART_STR("F25L08PA-DUAL");break;}	//	F25L08PA
						case 0x13:{UART_STR("F25L04PA-DUAL");break;}	//	F25L04PA
						case 0x12:{UART_STR("F25L02PA-DUAL");break;}	//	F25L02PA
						case 0x11:{UART_STR("F25L01PA-DUAL");break;}	//	F25L01PA
						case 0x10:{UART_STR("F25L05PA-DUAL");break;}	//	F25L05PA
					}
					break;
				}
				case 0x21:	//	DUAL
				{
					switch(Capa)
					{
						case 0x15:{UART_STR("F25L16PA-DUAL");break;}	//	F25L16PA
					}
					SFLS_WB_RDCMD = 0x3B;		//	DUAL
					SFLS_WB_WRCMD = 0x02;
					SFLS_WBCONT = 0x00141000;
					SFLS_CMD = 0x10010000;
//					SFLS_CMD = 0x30010000;
					while(SFLS_REG_REQ);
					break;
				}
			}
			break;
		}
		case 0xC8:    //    GigaDevice	// 170512 KSH
        {
            switch(Type)
            {
                case 0x40:    //    QUAD
                {
                    switch(Capa)
                    {
                        case 0x13:{UART_STR("GD25Q40B-QUAD");break;}    //  GD25Q40B
                    }
                    SFLS_REG_CMD = 0x06;
                    SFLS_CMD = 0x10020000;      //  WE + MCK/2
                    while(SFLS_REG_REQ);
                    SFLS_REG_CMD = 0x01;
                    SFLS_DATIN = 0x00020000;    //  QE
                    SFLS_CMD = 0x10021C01;
                    while(SFLS_REG_REQ);
                    SFLS_WB_RDCMD = 0xEB;       //  QUAD read
                    SFLS_WB_WRCMD = 0x02;       //  SINGLE write
                    SFLS_WBCONT = 0x001CA000;   //  GapEn + Gap 3(M7-0) + Dummy2)
                    SFLS_CMD = 0x10010000;      //  WB Update
//				  	SFLS_CMD = 0x30010000;	  //  WB Update
                    while(SFLS_REG_REQ);
                    break;
                }
            }
            break;
        }
		default :	//	ETC
		{	
			switch(Type)
			{
				case 0x30:	//	QUAD
				case 0x31:	//	SINGLE
				{
					SFLS_CMD = 0x10020000;
//					SFLS_CMD = 0x30020000;
					while(SFLS_REG_REQ);
					break;
				}
			}
			break;
		}
	};
	return;
}

void sfls_write_en(void)
{
	SFLS_REG_CMD = 0x06;
	SFLS_CMD_GO(Req1,0,0,0,0,0,0,CmdIomA,0,0,0,0);
}

void sfls_erase_sect(int Adr)
{
	sfls_write_en();

	SFLS_REG_CMD = 0x20;
	SFLS_REG_ADR = (Adr & FLASH_ADDR_MASK);

	SFLS_CMD_GO(Req1,0,AdrEn1,0,0,WaitEn1,0,CmdIomA,AdrIomA,0,0,0);

	xFUNC_TIME_TX("DCACHE SET",
#if 1
	int i=0;
	UINT *p = (UINT*)( FLS_BASE | (Adr&(~(FLASH_SECT_SIZE-1))) );
	for(i=0; i<(0x1000>>2); i++);
	{
		*p++ = 0xFFFFFFFF;
	}
#else
	const UINT nAddr = FLS_BASE | (Adr&(~(FLASH_SECT_SIZE-1)));
	const UINT nStop = nAddr + 0x1000;

	//flush_dcache_range(nAddr, nStop);
	invalidate_dcache_range(nAddr, nStop);
	//invalidate_icache_range(nAddr, nStop);
#endif
	)

}

#if 0
void sfls_erase_all(void)
{
	sfls_write_en();

	SFLS_REG_CMD = 0xC7;

	SFLS_CMD_GO(Req1,0,AdrEn1,0,0,WaitEn1,0,CmdIomA,AdrIomA,0,0,0);
}
#endif

void sfls_write_reg(BYTE dat)
{
	sfls_write_en();

	SFLS_REG_CMD = 0x01;

	#if(model_Flash==0) 	// EON	
	    SFLS_DATIN = (dat<<24);
	    SFLS_CMD_GO(Req1,0,0,0,DatEn1,WaitEn1,DatW,CmdIomA,0,DatIomA,0,0);
	
	#else					// Winbond or GigaDevice	// 170512 KSH
	    SFLS_DATIN = ((dat<<24)|(2<<16));
	    SFLS_CMD_GO(Req1,0,0,0,DatEn1,WaitEn1,DatW,CmdIomA,0,DatIomA,0,1);
	#endif
	
}

BYTE sfls_read_reg(void)
{
	SFLS_REG_CMD = 0x05;
	SFLS_CMD_GO(Req1,0,0,0,DatEn1,WaitEn0,DatR,CmdIomA,0,DatIomA,0,0);
	return (SFLS_DATOUT>>24)&0xFF;
}

BYTE ISPM SfWrite(UINT anAddr, BYTE* apbData, UINT anNum)
{	// Byte Write to Serial Flash
	// anAddr must be start point of sector
	UINT 	i;

	SfWrEn;

	for (i=0; i<anNum; i++) {
		if (((anAddr+i)&(FLASH_SECT_SIZE-1))==0) {										// Sector erase
			sfls_erase_sect(anAddr+i);
//			TxStr("SFSEAw__", (anAddr+i), "\n");
		}
		sfw8(anAddr+i, apbData[i]);
	}

	for (i=0; i<anNum; i++) {															// Read & Verify
		if ( sfr8(anAddr+i) != apbData[i] ) {TxStrNoIRQ("SfWrErr_", i, 4); return 0;}
//		TxStr("Read data ", _rd8(anAddr+i),  "\n");		// Debug
	}

	SfWrDis;

	return 1;
}

BYTE ISPM SfRead(UINT anAddr, BYTE* apbData, UINT anNum)
{	// Byte Read from Serial Flash
	UINT 	i;

	for (i=0; i<anNum; i++) {															// read
		apbData[i] = sfr8(anAddr+i);
	}

	return 1;
}

//*************************************************************************************************
// Utillity
//-------------------------------------------------------------------------------------------------
//
BYTE ISPM SfAddrChk(BYTE abMode)
{	// Judgement Current address

	BYTE	bCurSect;

	BYTE 	bUser1chk;
	BYTE 	bUser2chk;

	if (abMode == FLASH_MENU_MODE){
		bUser1chk = sfr8(FLASH_SECT_MENU_STT*FLASH_SECT_SIZE);
		bUser2chk = sfr8(FLASH_SECT_MENU_BKUP*FLASH_SECT_SIZE);
	}
	else{
		return 0;
	}

//	TxStrNoIRQ("user1___", bUser1chk, 2);
//	TxStrNoIRQ("user2___", bUser2chk, 2);

	if (bUser1chk==FLASH_VALID) {
		if (bUser2chk==FLASH_EMPTY)	{
			TxStrNoIRQ("user2Err", FLASH_EMPTY, 2);
		}
		else if (bUser2chk==FLASH_VALID) {				// Warning! Both valid case
			TxStrNoIRQ("user2Err", FLASH_VALID, 2);
		}
		bCurSect = 0;
	}
	else if (bUser2chk==FLASH_VALID) {
		if (bUser1chk==FLASH_EMPTY)	{
			TxStrNoIRQ("user1Err", FLASH_EMPTY, 2);
		}
		bCurSect = 1;
	}
	else {
		TxStrNoIRQ("otherErr", 0x0, 2);
		bCurSect = 0;
	}

	return 	bCurSect;
}


BYTE ISPM SfRead2(BYTE* apbData, UINT anNum, BYTE abMode)
{	// Byte read from serial flash with Rolling address management
	// bMode : 0 - User, 1 - Parameter
	UINT 	nCurAddr;
	BYTE 	bCurSect = SfAddrChk(abMode);
	
	if (abMode == FLASH_USER_MODE) {
		nCurAddr = (FLASH_SECT_USER_STT*FLASH_SECT_SIZE);
 	}
 	else if (abMode == FLASH_DATA_MODE) {
 		nCurAddr = (FLASH_SECT_DATA_STT*FLASH_SECT_SIZE);
 	}
  #if model_MenuDefSet == 1
	else if (abMode == FLASH_MENU_SET_MODE) {
 		nCurAddr = (FLASH_SECT_MENU_SET_STT*FLASH_SECT_SIZE);
 	}
  #endif
	else {
		nCurAddr = ((FLASH_SECT_MENU_STT+(bCurSect*FLASH_SECT_MENU_EA))*FLASH_SECT_SIZE);
	}

//	UINT i;
//	for (i=0; i<anNum; i++) 														// read 1byte unit
//		apbData[i] = sfr8(nCurAddr+4+i);

	UINT	nBuf, i, j;
	const UINT nMok = anNum/4;
	const UINT nMod = anNum%4;

	for (i=0; i<anNum; i+=4) {
//		if ((i == anNum-4) && (nMod != 0)) {		// NG
		if ((i == (nMok*4)) && (nMod != 0)) {										// exception
			for (j = 0; j < nMod; j++)
				apbData[i+j] = sfr8(nCurAddr+4+i+j);
		}
		else {																		// read 4byte unit // EN778
			// Default Byte Ordering is MSB(Most Significant Byte)
			nBuf = sfr32(nCurAddr+4+i);
			apbData[i+3] = (nBuf >>  0) & 0xff;
			apbData[i+2] = (nBuf >>  8) & 0xff;
			apbData[i+1] = (nBuf >> 16) & 0xff;
			apbData[i+0] = (nBuf >> 24) & 0xff;
		}
	}

//	TxStr("ReadAddr", nCurAddr,  "\n");		// !!

	return 1;
}

BYTE ISPM SfWrite2(BYTE* apbData, UINT anNum, BYTE abMode)
{	// Byte write to serial flash with Rolling address management
	// bMode : 0 - User, 1 - Parameter
	UINT	nNewAddr = 0;
	UINT 	nCurAddr = 0;
	BYTE	bCurSect = SfAddrChk(abMode);

	SfWrEn;

	if (anNum>FLASH_SECT_SIZE-1)	{TxStrNoIRQ("WSizeErr", 0 , 0); return 0;}	// temporary limitation

	if (abMode == FLASH_USER_MODE) {
		nNewAddr = (FLASH_SECT_USER_STT*FLASH_SECT_SIZE);
	}
	else if (abMode == FLASH_DATA_MODE){
 		nNewAddr = (FLASH_SECT_DATA_STT*FLASH_SECT_SIZE);
 	}
  #if model_MenuDefSet == 1
	else if (abMode == FLASH_MENU_SET_MODE){
 		nNewAddr = (FLASH_SECT_MENU_SET_STT*FLASH_SECT_SIZE);
 	}
  #endif
	else {
		if (bCurSect==0) {
			nCurAddr = (FLASH_SECT_MENU_STT*FLASH_SECT_SIZE);
			nNewAddr = (FLASH_SECT_MENU_BKUP*FLASH_SECT_SIZE);
		}
		else {
			nCurAddr = (FLASH_SECT_MENU_BKUP*FLASH_SECT_SIZE);
			nNewAddr = (FLASH_SECT_MENU_STT*FLASH_SECT_SIZE);
		}
	}


	UINT	nBuf, i, j;
	const UINT nMok = anNum/4;
	const UINT nMod = anNum%4;

	for (i=0; i<anNum; i+=4) {

		if (((nNewAddr+i)&(FLASH_SECT_SIZE-1))==0) {							// sector erase
			sfls_erase_sect(nNewAddr+i);
			//TxStrNoIRQ("SfWrite2 Erase ! ", nNewAddr+i,  8);
		}

//		if ((i == anNum-4) && (nMod != 0)){			// NG
		if ((i == (nMok*4)) && (nMod != 0)) {									// exception
			for (j = 0; j < nMod; j++){
				sfw8(nNewAddr+4+i+j, apbData[i+j]);
//				TxStr("i+j_CNT", i+j,  "\n");
			}
		}
		else {																	// write 4 byte unit
			// Default Byte Ordering is MSB(Most Significant Byte)
			nBuf = apbData[i+3] + (apbData[i+2]<<8) + (apbData[i+1]<<16) + (apbData[i+0]<<24);
			sfw32(nNewAddr+4+i, nBuf);
//			TxStr("i___CNT", i,  "\n");
		}
	}

	for (i=0; i<anNum; i++) {													// read & verify
		if (sfr8(nNewAddr+4+i) != apbData[i]) {TxStrNoIRQ("SfWrite2 Verify Err__", nNewAddr+4+i, 8); return 0;}	// JYP
//		TxStr("val", sfr8(nNewAddr+4+i),  "\n");
	}

//	TxStr("WrAddr", nNewAddr,  "\n");		// !!

	sfw8(nNewAddr, FLASH_VALID);												// set valid flag to new Writed area

	if (abMode == FLASH_MENU_MODE) {
		sfw8(nCurAddr, FLASH_INVALID);											// set invalid flag to old area
	}

	SfWrDis;

	TxStrNoIRQ("SfWrite2 Done ! ", nNewAddr+i,  8);

	return 1;
}


BYTE ISPM MenuSfWrite2(BYTE* apbData, UINT anNum, UINT anAddr, BYTE abData)
{	
	UINT	nNewAddr = 0;
	UINT 	nCurAddr = 0;
	BYTE	bCurSect = SfAddrChk(FLASH_MENU_MODE);

	SfWrEn;

	if (anNum>FLASH_SECT_SIZE-1)	{TxStrNoIRQ("WSizeErr", 0 , 0); return 0;}	// temporary limitation

	if (bCurSect==0) {
		nCurAddr = (FLASH_SECT_MENU_STT*FLASH_SECT_SIZE);
		nNewAddr = (FLASH_SECT_MENU_BKUP*FLASH_SECT_SIZE);
	}
	else {
		nCurAddr = (FLASH_SECT_MENU_BKUP*FLASH_SECT_SIZE);
		nNewAddr = (FLASH_SECT_MENU_STT*FLASH_SECT_SIZE);
	}

	UINT	nBuf, i, j;
	const UINT nMok = anNum/4;
	const UINT nMod = anNum%4;

	for (i=0; i<anNum; i+=4) {

		if (((nNewAddr+i)&(FLASH_SECT_SIZE-1))==0) {							// sector erase
			sfls_erase_sect(nNewAddr+i);
			//TxStrNoIRQ("SfWrite2 Erase ! ", nNewAddr+i,  8);
		}

//		if ((i == anNum-4) && (nMod != 0)){			// NG
		if ((i == (nMok*4)) && (nMod != 0)) {									// exception
			for (j = 0; j < nMod; j++){
				sfw8(nNewAddr+4+i+j, apbData[i+j]);
//				TxStr("i+j_CNT", i+j,  "\n");
			}
		}
		else {																	// write 4 byte unit
			// Default Byte Ordering is MSB(Most Significant Byte)
			nBuf = apbData[i+3] + (apbData[i+2]<<8) + (apbData[i+1]<<16) + (apbData[i+0]<<24);
			sfw32(nNewAddr+4+i, nBuf);
//			TxStr("i___CNT", i,  "\n");
		}
	}

	for (i=0; i<anNum; i++) {													// read & verify
		if (sfr8(nNewAddr+4+i) != apbData[i]) {TxStrNoIRQ("SfWrite2 Verify Err__", nNewAddr+4+i, 8); return 0;}	// JYP
//		TxStr("val", sfr8(nNewAddr+4+i),  "\n");
	}

//	TxStr("WrAddr", nNewAddr,  "\n");		// !!

	TxStrNoIRQ("nNewAddr", nNewAddr, 8);
	TxStrNoIRQ("nCurAddr", nCurAddr, 8);

	sfw8(nNewAddr+anAddr, abData);

	sfw8(nNewAddr, FLASH_VALID);												// set valid flag to new Writed area
	sfw8(nCurAddr, FLASH_INVALID);											// set invalid flag to old area
	
															// Read & Verify
	if ( sfr8(nNewAddr+anAddr) != abData ) {TxStrNoIRQ("SfWrErr_", i, 4);	return 0;}
	else{
		TxStrNoIRQ("sfr8", sfr8(nNewAddr+anAddr), 2);
		TxStrNoIRQ("abData", abData, 2);
	}
	
	SfWrDis;

	return 1;
}


BYTE ISPM Isp2Sf( UINT anSfaddr, UINT anIspAddr, UINT anIspBufEa, BYTE abSizeByte)
{	// Copy Isp to Flash Function
	// anSfaddr  : Sf Start address (must be start point of sector)
	// anIspAddr : Isp Start address
	// anIspBufEa: Isp data ea
	// abSizeByte: Data cast BYTE ea (2 or 4)

//TimeChkStt();

	UINT*	pnDcpAddr;
	UINT 	nBuf,i, nBuf0;

	SfWrEn;

	if (!anIspBufEa || !((abSizeByte==2)||(abSizeByte==4)) ) { UartTxStr("Isp2Sf arg error ! \n"); return 0; }

	pnDcpAddr = (UINT*)(ISP_BASE+(anIspAddr<<2));

	for (i=0; i<anIspBufEa; i++) {
		if (((anSfaddr+(i*abSizeByte))&(FLASH_SECT_SIZE-1))==0)	{
			sfls_erase_sect(anSfaddr+(i*abSizeByte));
//			TxStr("SFSEAw__", (anSfaddr+(i*abSizeByte)), "\n");		// Sector erase
		}

		if (abSizeByte==2) {
			sfw8(anSfaddr+(i*abSizeByte)+0, *((BYTE*)pnDcpAddr+0));
	//		TxStr("addr0___", anSfaddr+(i*abSizeByte)+0, "\n");
	//		TxStr("data0___", *((BYTE*)pnDcpAddr+0), "\n");
			sfw8(anSfaddr+(i*abSizeByte)+1, *((BYTE*)pnDcpAddr+1));
	//		TxStr("addr1___", anSfaddr+(i*abSizeByte)+1, "\n");
	//		TxStr("data1___", *((BYTE*)pnDcpAddr+1), "\n");
		}
		else if (abSizeByte==4) {	// 160424 LH : defect mem access have to use this option because 1clock read delay and BYTE ordering
			nBuf0 = *pnDcpAddr;
			sfw32(anSfaddr+(i*abSizeByte), nBuf0);
//			if (i<16)		  TxStr("Isp_data", nBuf0, "\n");		// test
		}

		pnDcpAddr++;
	}

	pnDcpAddr = (UINT*)(ISP_BASE+(anIspAddr<<2));

	for (i=0; i<anIspBufEa; i++) {

		if (abSizeByte==2) {
			nBuf = 		  (sfr8(anSfaddr+(i*abSizeByte)+0)<<0);
			nBuf = nBuf | (sfr8(anSfaddr+(i*abSizeByte)+1)<<8);
		}
		else if (abSizeByte==4) {	// 160424 LH
			nBuf0 = *pnDcpAddr;
			nBuf = sfr32(anSfaddr+(i<<2));
			if ((i>0)&&(nBuf != nBuf0)) { TxStrNoIRQ("Isp2SfEr", (UINT)pnDcpAddr, 8);	return 0; }		// skip first data dummy
//			if (i<16) 			  TxStr("Sf__data", nBuf, "\n");		// test
		}

		pnDcpAddr++;
	}

//DispDat("Time____",  0, 24, TimeChkEnd());

	SfWrDis;

	return 1;
}

BYTE ISPM Sf2Isp( UINT anSfaddr, UINT anIspAddr, UINT anIspBufEa, BYTE abSizeByte)
{	// Copy Flash to Isp Function
	// anSfaddr  : Sf Start address
	// anIspAddr : Isp Start address
	// anIspBufEa: Isp data ea
	// abSizeByte: Data cast BYTE ea (2 or 4)

	UINT 	nBuf=0,i;

	if (!anIspBufEa || !((abSizeByte==2)||(abSizeByte==4)) ) { UartTxStr("Sf2Isp arg error ! \n"); return 0;}

	for (i=0; i<anIspBufEa; i++) {

		if (abSizeByte==2) {
			nBuf = 		  (sfr8(anSfaddr+(i*abSizeByte)+0)<<8);
			nBuf = nBuf | (sfr8(anSfaddr+(i*abSizeByte)+1)<<0);			
		}
		else if (abSizeByte==4) {
			nBuf = sfr32(anSfaddr+(i<<2));
//			if (i<16) TxStr("Sf2Isp__", nBuf, "\n");		// verify end of data
		}
		SetIsp(anIspAddr+i,nBuf);
	}
	return 1;
}


