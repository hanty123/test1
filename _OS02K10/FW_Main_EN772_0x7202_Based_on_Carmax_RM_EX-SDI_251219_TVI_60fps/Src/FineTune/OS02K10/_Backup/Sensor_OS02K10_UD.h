/* **************************************************************************
 File Name	: 	Sensor_OS02H10_UD.h
 Description	:	Image Fine-tune user data(open setting value)
 Designer		:	Lee, Gyu Hong
 Date		:	23. 05. 22
 Copyright �� DCOD  Co., Ltd. All Rights Reserved.
*************************************************************************** */

//******************************************************
// Gamma
//------------------------------------------------------

const UINT	gnTblY1Gma[9] = 	{0x00000007, 0x00130025, 0x004a0083, 0x00d40173, 0x01f00262, 0x02c3030f, 0x037b03bf, 0x03e703fa, 0x03ff0000};	//Y Day
const UINT	gnTblY2Gma[9] = 	{0x00000008, 0x0011001d, 0x00350057, 0x00a10124, 0x019201fb, 0x025002aa, 0x03330391, 0x03cd03ec, 0x03ff0000};	//Y Night

const UINT	gnTblC1Gma[9] = 	{0x00000019, 0x00380061, 0x009d00ec, 0x015401e7, 0x025502a6, 0x02f10323, 0x037b03b6, 0x03d703ef, 0x03ff0000};	//C Day
const UINT	gnTblC2Gma[9] = 	{0x0000000b, 0x001b0031, 0x0055009c, 0x011601b4, 0x0227027e, 0x02c7030b, 0x037b03b6, 0x03d703ef, 0x03ff0000};	//C Night

const UINT	gnTblWdrY1Gma[9] =	{0x00000011, 0x001b002b, 0x0044006b, 0x00a90109, 0x015901a0, 0x01e1021d, 0x028c02f2, 0x035103ab, 0x03ff0000};  	//Y Day   (Ref)
const UINT	gnTblWdrY2Gma[9] = 	{0x00000011, 0x001b002b, 0x0044006b, 0x00a90109, 0x015901a0, 0x01e1021d, 0x028c02f2, 0x035103ab, 0x03ff0000};	//Y Night (Ref)

const UINT	gnTblWdrC1Gma[9] =	{0x00000008, 0x0017002d, 0x006a00c5, 0x015801f9, 0x0259029b, 0x02ce02f7, 0x0340037b, 0x03ab03dc, 0x03ff0000};	//C Day
const UINT	gnTblWdrC2Gma[9] =	{0x00000009, 0x0015002b, 0x005600af, 0x014201d5, 0x0219024c, 0x02730294, 0x02c002fe, 0x034803a0, 0x03ff0000};	//C Night