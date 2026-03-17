/* **************************************************************************
 File Name	: 	Sensor_IMX462_UD.h
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

// const UINT	gnTblWdrY1Gma[9] =	{0x00000008, 0x00120023, 0x003e006c, 0x00b8012f, 0x018f01dc, 0x0213023f, 0x029202e6, 0x034003a0, 0x03ff0000};  	//Y Day   (Ref)
// const UINT	gnTblWdrY2Gma[9] = 	{0x0000000b, 0x0016002b, 0x004c0082, 0x00d20144, 0x019801d8, 0x020e023f, 0x028e02d9, 0x0335039e, 0x03ff0000};	//Y Night (Ref) OK

const UINT	gnTblWdrY1Gma[9]    = {0x00000006, 0x000d001c, 0x00350063, 0x00aa011a, 0x017501ca, 0x02130253, 0x02cb032a, 0x037b03bd, 0x03ff0000};  	//Y Day   (Ref)
const UINT	gnTblWdrY2Gma[9]    = {0x00000012, 0x00270040, 0x00600089, 0x00c8012f, 0x018b01d8, 0x0213024c, 0x02b8030f, 0x036503b8, 0x03ff0000};    	//Y Night (Ref)

//const UINT	gnTblWdrC1Gma[9] =	{0x00000009, 0x00170038, 0x007300e4, 0x01890215, 0x02620290, 0x02a802b8, 0x02e3030f, 0x0348038a, 0x03ff0000};	//C Day
// const UINT	gnTblWdrC1Gma[9] =	{0x00000006, 0x000d001b, 0x004100b6, 0x015f01ff, 0x02590290, 0x02a802b8, 0x02e3030f, 0x0348038a, 0x03ff0000};	//C Day
// const UINT	gnTblWdrC2Gma[9] =	{0x00000008, 0x0015002d, 0x0058009c, 0x011201c2, 0x022f0264, 0x028e02af, 0x02e8030f, 0x0348038d, 0x03ff0000};	//C Night   OK

const UINT	gnTblWdrC1Gma[9] =	{0x00000015, 0x002c0056, 0x009600f8, 0x017901fb, 0x0255027e, 0x02a402bc, 0x02e3030f, 0x0348038a, 0x03ff0000}; 
const UINT	gnTblWdrC2Gma[9] =	{0x0000000b, 0x001e0039, 0x006a00bf, 0x016501f6, 0x0255027e, 0x02a402bc, 0x02e3030f, 0x0348038a, 0x03ff0000};   //C Night   Common
                                