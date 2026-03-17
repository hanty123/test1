/* **************************************************************************
 File Name	: 	dev_spi.c
 Description:	EN772 - Spi control device driver
 Designer	:	Jang, Young Kyu / Kim Sung-Hoon
 Date		:	14. 6. 18
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

void InitSpi(void)
{
	TxStrNoIRQ("SPI Init.", 0, 0);

//	SPI0_SET(SPI0_CLKDIV, SPI_START_HIGH);
//	SPI0_SPI_CS = 1;
}

void SPI0_LSB_WRITE(BYTE abData)
{
	SPI0_TX_DAT = abData;

	SPI0_SPI_CONT = (SPI0_SPI_CONT&(~0x40B)) | (SPI_LSB<<10) | (SPI_EDGE_RISING<<3) | (SPI_BIT_BYTE<<2) | 3; // 3 => SPI0_CMD_RW[1] = 1 & SPI0_CMD_GO[0] = 1
	while(SPI0_CMD_GO);
}

BYTE SPI0_LSB_READ(void)				//
{
	SPI0_SPI_CONT = (SPI0_SPI_CONT&(~0x40B)) | (SPI_LSB<<10) | (SPI_EDGE_RISING<<3) | (SPI_BIT_BYTE<<2) | 1; // 1 => SPI0_CMD_RW[1] = 0 & SPI0_CMD_GO[0] = 1
	while(SPI0_CMD_GO);

	return (SPI0_RX_DAT>>8);
}

void SPI_MSB_WRITE(BYTE abData)
{
	SPI1_TX_DAT = abData<<8;

	SPI1_SPI_CONT = (SPI1_SPI_CONT&(~0x40B)) | (SPI_MSB<<10) | (SPI_EDGE_RISING<<3) | (SPI_BIT_BYTE<<2) | 3; // 3 => SPI1_CMD_RW[1] = 1 & SPI1_CMD_GO[0] = 1
	while(SPI1_CMD_GO);
}

BYTE SPI_MSB_READ(void)
{
	SPI1_SPI_CONT = (SPI1_SPI_CONT&(~0x40B)) | (SPI_MSB<<10) | (SPI_EDGE_RISING<<3) | (SPI_BIT_BYTE<<2) | 1; // 1 => SPI1_CMD_RW[1] = 0 & SPI1_CMD_GO[0] = 1
	while(SPI1_CMD_GO);

	return (SPI1_RX_DAT>>8);
}


