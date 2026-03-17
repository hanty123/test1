/* **************************************************************************
 File Name	: 	Sensor_IMX307_UD.h
 Description	:	Image Fine-tune user data(open setting value)
 Designer		:	Lee, Gyu Hong
 Date		:	22. 04. 19
 Copyright ¨Ï DCOD  Co., Ltd. All Rights Reserved.
*************************************************************************** */

//******************************************************
// Gamma
//------------------------------------------------------

const UINT	gnTblY1Gma[9] = 	{0x00000007, 0x00110020, 0x00350053, 0x00920103, 0x01790206, 0x027c02d0, 0x033b0384, 0x03bb03e4, 0x03ff0000};	//Y Day
const UINT	gnTblY2Gma[9] = 	{0x00000008, 0x001e0046, 0x007500b4, 0x011001a9, 0x022d0287, 0x02c902fc, 0x034d0391, 0x03cd03ec, 0x03ff0000};	//Y Night

const UINT	gnTblC1Gma[9] = 	{0x00000019, 0x00490081, 0x00fa0158, 0x01bf0241, 0x029702d6, 0x0304032e, 0x036c039c, 0x03c603eb, 0x03ff0000};	//C Day
const UINT	gnTblC2Gma[9] = 	{0x0000000b, 0x001b0031, 0x0055009c, 0x011601b4, 0x0227027e, 0x02c7030b, 0x037b03b6, 0x03d703ef, 0x03ff0000};	//C Night

const UINT	gnTblWdrY1Gma[9] =	{0x0000000a, 0x00140025, 0x00400072, 0x00d10176, 0x01ff0266, 0x02ad02e1, 0x03280363, 0x039803ca, 0x03ff0000};	//Y Day(Ref)
const UINT	gnTblWdrY2Gma[9] = 	{0x0000001d, 0x0037004f, 0x007400a6, 0x011001bb, 0x02270276, 0x02c70307, 0x036e03ab, 0x03d303ef, 0x03ff0000};	//Y Night (Ref)

const UINT	gnTblWdrC1Gma[9] =	{0x00000009, 0x002c007f, 0x00cc0147, 0x01bb022d, 0x029402db, 0x030d032e, 0x036c039c, 0x03c603eb, 0x03ff0000};	//C Day
const UINT	gnTblWdrC2Gma[9] = 	{0x00000009, 0x0016002f, 0x005d009c, 0x012d01f9, 0x026d02b3, 0x02ec0321, 0x037b03b6, 0x03d703ef, 0x03ff0000};  	//C Night	

	