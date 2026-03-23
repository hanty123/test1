/* **************************************************************************
 File Name	: 	menu.c
 Description	:	EN772 - Menu function
 Designer		:	Lee, Gyu Hong
 Date		:	19. 12. 09
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"
#include "app_menu.h"
#include "app_menu_tbl.h"

//*************************************************************************************************
// Global Menu Parameter & variables
//-------------------------------------------------------------------------------------------------
	BYTE gbMnParSaveChk = 0;
	BYTE gbMnParReadChk = 0;
	BYTE gbMnParTbl[MN_PAR_EA], gbMnParTblOld[MN_PAR_EA];	// Storage for MENU Parameter

  #if model_MenuDefSet == 1
	BYTE gbMnSetParSaveChk = 0;
	BYTE gbMnSetParReadChk = 0;
	BYTE gbMnSetParTbl[MN_PAR_EA];
	BYTE gbMnSave = 0;
  #endif
  
	BYTE gbMnBlcOsdOn = 0;

	BYTE gbBaudrate = 0;
	BYTE gbBaudrateSetDone = 0;

	BYTE gbMnDebugFnc = 0;

	BYTE gbMnDebugBypass = 0;
	BYTE gbMenuState = 0;
	BYTE gbMenuPushState = 0;

	BYTE gbMnUpReset = 0;
	BYTE gbMnClose = 0;		// 170706 KSH

#if(model_Lens==0)
	BYTE gbMnFaOn = 0;

#elif(model_Lens==1)
    extern BYTE gbMAF_SETUP, gbMAF_MZrange_T, gbMAF_MFrange_T, gbMAF_MZpos_S, gbMAF_MZpos_E, gbMAF_MFpos_S, gbMAF_MFpos_E;  // 180702 JJH Box control
	BYTE gbDispMaf_flag=0; // 191202 PChan : Long menu erase problem due to 2-motor string display
#endif

	int giKeyAdd = 0;

	BYTE gbModeBufOutFps = 0;
	BYTE gbModeBufSysFreq = 0;
	BYTE gbModeBufSdiForm = 0;
	BYTE gbModeBufSdiMode = 0;
	BYTE gbModeBufAnlForm = 0;

	//170825 LGH : Mode change flag
	BYTE gbModeConfirm = 0;
	BYTE gbModeBufReturn = 0;
	BYTE gbModeBufBefore = 0;
	BYTE gbModeSdiBufBefore = 0;

	BYTE gbModeChgHotKey = 0;

	BYTE gbMirBuf = 0;
	BYTE gbFlpBuf = 0;
  
//*************************************************************************************************
// variables
//-------------------------------------------------------------------------------------------------
//BYTE    gbStgPos[4]     = {MN_IV_POS,MN_IV_POS,MN_IV_POS,MN_IV_POS};    // Index = 0~3 : Stage Level,      Value = 0~8 : Position,  other : invalid
//BYTE	gbStgSubPos[4]	= {0,0,0,0};									// special case stage
BYTE    gbStgPos[5]     = {MN_IV_POS,MN_IV_POS,MN_IV_POS,MN_IV_POS,MN_IV_POS};    // Index = 0~3 : Stage Level,      Value = 0~8 : Position,  other : invalid
BYTE	gbStgSubPos[5]	= {0,0,0,0,0};									// special case stage
int     giLV            = -1;											// menu step level

BYTE 	gbPushCnt		= 0;

#define gbMenuY	  MN_YSTART

//UINT	DRAW_Y	= MN_YSTART;
UINT	DRAW_Y	= 3;

BYTE 	gbIMDMenuStep	= 0;

BYTE	MN_MXSP = MN_MXSP_DEF;

//MENU_STR_LIST(SHUT__LIST, 21,	SHUT_30, SHUT_60, SHUT_120, SHUT_250, SHUT_500, SHUT_1000, SHUT_2000, SHUT_4000, SHUT_8000, SHUT_15000,
								//SHUT_30000, SHUT_25, SHUT_50, SHUT_100, SHUT_200, SHUT_400, SHUT_800, SHUT_1600, SHUT_3200, SHUT_6400,
								//SHUT_12800);
// fdfdfdfdffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffjjj
//*************************************************************************************************
// Fixed define Functions
//-------------------------------------------------------------------------------------------------
#define OsdAttrsStgPos(Y, ATTR)         	SetFontAttrs(gbMenuY+Y, MN_MXSP, MN_LINESIZE, ATTR)
#define OsdAttrsStgPosAr(Y, ATTR)			SetFontAttrs(gbMenuY+Y, MN_MXSP, MN_LINESIZE, ATTR)		// 160330 KSH

//*************************************************************************************************
// Sub Functions
//-------------------------------------------------------------------------------------------------
void DispHex(const UINT anDispY, const UINT anDispX, const UINT anVal, const UINT anLen)
{
	uint2strh(gbStr, anVal, anLen);
	DispStr((const char*)gbStr, anDispY, anDispX, anLen);
}

void DispDec(const UINT anDispY, const UINT anDispX, const int aiVal, const UINT anLen)
{
	int2str(gbStr, aiVal, anLen);
	DispStr((const char*)gbStr, anDispY, anDispX, anLen);
}

void DispBin(const UINT anDispY, const UINT anDispX, const UINT anVal, const UINT anLen)
{
	uchar2strb(gbStr, anVal, anLen);
	DispStr((const char*)gbStr, anDispY, anDispX, anLen);
}

void DispPer(const UINT anDispY, const UINT anDispX, const int aiVal, const int aiValMax, const UINT anLen)
{
	per2str(gbStr, aiVal, aiValMax, anLen);
	DispStr((const char*)gbStr, anDispY, anDispX, anLen);
}

void DispFlt(const UINT anDispY, const UINT anDispX, const float afVal, const int aiValNum, const UINT anLen)
{	// 150104 KSH
	flt2str(gbStr, afVal, aiValNum, anLen);
	DispStr((const char*)gbStr, anDispY, anDispX, anLen);
}

void DispDatHex(char* cStr, const UINT anDispY, const UINT anDispX, const UINT anVal) //noclear
{	// Value Monitoring tool (limit to MN_FONT_MAX_PATH)
	DispStr(cStr, anDispY, anDispX, MN_FONT_MAX_PATH);
	DispHex(anDispY, ((anDispX+MN_FONT_MAX_PATH)+MN_FONT_SPACE+(MN_FONT_MAX_PATH-8)), anVal, 8);
}

void DispDatDec(char* cStr, const UINT anDispY, const UINT anDispX, const int aiVal) //noclear
{	// Value Monitoring tool
	DispStr(cStr, anDispY, anDispX, MN_FONT_MAX_PATH);
	DispDec(anDispY, ((anDispX+MN_FONT_MAX_PATH)+MN_FONT_SPACE), aiVal, MN_FONT_MAX_PATH);
}

void DispDatPer(char* cStr, const UINT anDispY, const UINT anDispX, const int aiVal, const int aiValMax) //noclear
{	// Value Monitoring tool
	DispStr(cStr, anDispY, anDispX, MN_FONT_MAX_PATH);
	DispPer(anDispY, ((anDispX+MN_FONT_MAX_PATH)+MN_FONT_SPACE), aiVal, aiValMax, MN_FONT_MAX_PATH);
}

void DispDatFlt(char* cStr, const UINT anDispY, const UINT anDispX, const float afVal) //noclear
{	// Value Monitoring tool
	DispStr(cStr, anDispY, anDispX, MN_FONT_MAX_PATH);
	DispFlt(anDispY, ((anDispX+MN_FONT_MAX_PATH)+MN_FONT_SPACE), afVal, 4, MN_FONT_MAX_PATH);
}

void DispClrDec(UINT anVal, UINT anPosY, UINT anPosX, UINT anLen)
{
    UINT nDiv;
    UINT nPos = 0;
	BYTE gbVals[3+1];

    if(anVal>999) return;

    nDiv = anVal/100;
    anVal -= nDiv*100;
    if(nDiv) gbVals[nPos++] = '0' + nDiv;

    nDiv = anVal/10;
    anVal -= nDiv*10;
    if(nDiv || nPos) gbVals[nPos++] = '0' + nDiv;

    gbVals[nPos++] = '0' + anVal;
	gbVals[nPos] = 0;

	if(anLen) DispClrStr((const char*)gbVals, anPosY, anPosX, nPos, anLen);
	else	  DispStr((const char*)gbVals, anPosY, anPosX, nPos);
}

//-------------------------------------------------------------------------------------------------
void OsdClearAll(void)
{	// init ID
    UINT i;

	for(i=0; i<ISP_FONT_ID_EA; i++){										// Initial Font ID
		if (i==(ISP_FONT_ID_EA-1))			{
			SetFontId(i, 0x1ff);
		}			// Page returnID
		else if (((i+1)%ISP_FONT_EAX) == 0)	{
			SetFontId(i, 0x1fe);
		}			// Line returnID
		else 								{
			SetFontId(i, SPACE_CHAR_ID);
		}	// fill space
	}
}

//-------------------------------------------------------------------------------------------------
void OsdWhiteAll(void)
{
    UINT i;
    for(i=0; i<ISP_FONT_ATTR_EA; i++) {
		SetFontAttr(i, MN_WHITE);
	}
}

//-------------------------------------------------------------------------------------------------
void OsdDispBar(UINT anVal, UINT anPosY, UINT anMin, UINT anMax)
{
	if(anVal > anMin) anVal -= anMin;
	else anVal = 0;

	//if(anMax > anMin) anMax -= anMin;
	//else anMax = anMin;
	anMax -= anMin;                                        // !! Must be 'anMax > anMin'

    UINT Pos1;
	UINT Pos2;

     if(anVal >= anMax) {
		Pos1 = (MN_BAR_SIZE-1);                                       // Set Max Position
		Pos2 = 2;
     }
    else {
		anMax <<= 5;                   // x32 : 32 > 7x3  -->  Increase Resolution
		anVal <<= 5;

		const UINT nDiv1 = (anMax / MN_BAR_SIZE) + 1;
		const UINT nDiv2 = ((nDiv1 - 1) / 3) + 1;

		Pos1 = anVal / nDiv1;
		Pos2 = (anVal % nDiv1) / nDiv2;
    }

    UINT Typ = 0;

	switch(Pos2) {
	case 0 : Typ = (Pos1==(MN_BAR_SIZE-1)) ? _IOI : _IOO; break;
	case 1 : Typ = (Pos1==(MN_BAR_SIZE-1)) ? _OII : (Pos1==0) ? _IIO : _OIO; break;
	case 2 : Typ = (Pos1==0) ? _IOI : _OOI; break;
	}

    UINT i;

	SETFONTID(anPosY,MN_XBAR,_IOO);
	SETFONTID(anPosY,MN_XBAR+(MN_BAR_SIZE-1),_OOI);
	for(i=1; i<(MN_BAR_SIZE-1); i++) SETFONTID(anPosY,MN_XBAR+i,_OOO);
	SETFONTID(anPosY,MN_XBAR+Pos1,Typ);

	for(i=(MN_XBAR+MN_BAR_SIZE); i<(UINT)(MN_SXSP+MN_SUBSIZE); i++) SETFONTID(anPosY,i,' ');
}

void OsdCamTitle(void)
{
	const BYTE bPosRghUp = (ISP_FONT_EAX-9);
	const BYTE bPosLftDn = 0x10;

	DispClr(0, bPosRghUp, 0x8);		SetFontAttrs(0, bPosRghUp, 0x8, MN_WHITE);
	DispClr(bPosLftDn, 0, 0x8);		SetFontAttrs(bPosLftDn, 0, 0x8, MN_WHITE);

	switch(MP(MpCamTitleOn)) {

		case MN_CT_RIGHT_UP  :	DispStr((const char*)&gbCamTitle(0), 0, bPosRghUp, 0x8);
								SetFontAttrs(0, bPosRghUp, 0x8, MN_BLACK);
								break;

		case MN_CT_LEFT_DOWN :	DispStr((const char*)&gbCamTitle(0), bPosLftDn, 0, 0x8);
								SetFontAttrs(bPosLftDn, 0, 0x8, MN_BLACK);
								break;

		default :				break;
	}
}


//*************************************************************************************************
// Add Functions
//-------------------------------------------------------------------------------------------------
int  giMenuDispPos	= 0;
int  giMenuDispChg	= 0;
int  giGrayOnly		= 0;
int  giMenuNum		= 0;

PEXCH *gbMenuTitle	= (PEXCH*)_S(OFF);
PEXCH *gbMenuList	= 0;
PEXCH *gbMenuVal	= 0;

PEXCH *gbStgTitle[4] = {(PEXCH*)_S(OFF),};

#if model_CharMax == 1
UINT ISPM strlenEx(const EXCH* apbStr)
{	// String length
	UINT	nLen = 0;
    while(*apbStr++) nLen++;
	return nLen;
}
#endif

void menu_redraw(int iChg, int iGrayOnly)
{
	//OsdClearAll();
	giMenuDispPos = gbStgPos[giLV] + 1;
	giMenuDispChg = iChg;
	giGrayOnly = iGrayOnly;
	gbStgPos[giLV] = 0;
}

void menu_in(const PEXCH* Title)
{	
	gbMenuTitle = (PEXCH*)Title;

	if(giLV >= 0) {		// ���� �޴��� �ִ� ��� (���� �޴��� MENU_EXT�����̸� �ȵ�!!!)
		OsdMenuPos(0);
		//OsdClearAll();
	}
	else {				// ���� �޴��� ���� ���
		OSD_ON();
	}

	giLV++;
	gbStgPos[giLV] = 0;
	gbStgTitle[giLV] = gbMenuTitle;

	//OsdMenuPos(1)
	giMenuDispPos = gbStgPos[giLV] + 1;
	giMenuDispChg = 1;
	giGrayOnly = 0;
}

void menu_close(void)
{ //�޴� �ݱ�
	giLV = -1;
	gbMenuTitle = (PEXCH*)_S(OFF);

	int i;
	if(giMenuNum == 0) giMenuNum = 16;	// 170706 KSH
	DispClr(MN_TITLE, MN_MXSP, MN_LINESIZE);
	
	for(i=0; i<giMenuNum; i++)
	{
		DispClr(gbMenuY+i, MN_MXSP, MN_LINESIZE);
	}
	giMenuNum = 0;
	giMenuDispPos = 1;
	gbMenuVal = 0;
	gbMenuList = 0;

	OsdCamTitle();

	OSD_OFF();
}

void menu_out(const int aiClearFinger/*const PEXCH* Title*/)
{ //�����ܰ� �޴�
	//gbMenuTitle = (PEXCH*)Title;
	if(aiClearFinger) { OsdMenuPos(0); }
	//OsdClearAll();

	giLV--;

	//if(MENU_TITLE_IS(OFF)) giLV = -1;
	//if(((const PEXCH*)Title) == _S(OFF)) { giLV = -1; gbMenuTitle = (PEXCH*)_S(OFF); }

	if(giLV >= 0) {		// ���� �޴��� �ִ� ���
		gbMenuTitle = gbStgTitle[giLV];

		//OsdMenuPos(1);
		giMenuDispPos = gbStgPos[giLV] + 1;
		giMenuDispChg = 1;
		giGrayOnly = 0;
		gbStgPos[giLV] = 0;
	}
	else
	{				// ���� �޴��� ���� ���
		menu_close();
	}
}

void menu_dir(const int aiOn)
{
	if(!aiOn) {
		OsdAttrsStgPosAr(gbStgPos[giLV], MN_GRAY);
		gbMenuVal = (PEXCH*)_S(NOT_USED);
	}

	if(giMenuDispPos) {
		if(aiOn) {
			if(giMenuDispPos != gbStgPos[giLV] + 1) OsdAttrsStgPosAr(gbStgPos[giLV], MN_WHITE);
		}
		else {
			if(giMenuDispPos == gbStgPos[giLV] + 1) giMenuDispPos++;
			if(giGrayOnly == 0) DISPCLRSTR(_S(NOT_USED), gbMenuY+gbStgPos[giLV], MN_SXSP, MN_SUBSIZE, MN_SUBSIZE);
		}
		gbStgPos[giLV]++;
	}
}

void menu_one(const int aiOn, const PEXCH* Str)
{
	gbMenuVal = (PEXCH*)Str;

	if(giMenuDispPos && (aiOn || giGrayOnly)) {
		DISPCLRSTR(Str, gbMenuY+gbStgPos[giLV], MN_SXSP, MN_SUBSIZE, MN_SUBSIZE);
	}

	menu_dir(aiOn);
}

BYTE menu_push(const int aiOn, BYTE *Val, const PEXCH* StrNor, const PEXCH* StrPush, const BYTE abDelay)
{
	BYTE bPushOn = 0;

	if(giMenuDispPos && (aiOn || giGrayOnly)) {
		gbPushCnt = 0;
		*Val = 0;
		goto DISPLAY_PUSH_STR;
	}

	if(giMenuDispPos == 0) {
		gbMenuPushState = 1;
		if(pKEY_C) {
			if(gbPushCnt < 0xFF) gbPushCnt++;
			if(gbPushCnt == abDelay) {
				bPushOn = 1;
				*Val = 1;
				goto DISPLAY_PUSH_STR;
			}
		}
		else {
			if(gbPushCnt) {
				gbPushCnt = 0;
				*Val = 0;
				goto DISPLAY_PUSH_STR;
			}
		}
	}

	gbMenuVal = (PEXCH*)((*Val) ? StrPush : StrNor);
	menu_dir(aiOn);
	return 0;

DISPLAY_PUSH_STR:
	gbMenuVal = (PEXCH*)((*Val) ? StrPush : StrNor);
	DISPCLRSTR(gbMenuVal, gbMenuY+gbStgPos[giLV], MN_SXSP, MN_SUBSIZE, MN_SUBSIZE);
	menu_dir(aiOn);
	return bPushOn;
}
#if (0)
void menu_str(const int aiOn, BYTE *Val, int OpNum, const PEXCH** Str)
{
	if(giMenuDispPos == 0 && aiOn) {
		if(KEY_L)	*Val = (*Val == 0) ? OpNum - 1 : *Val - 1;
		if(KEY_R)	*Val = (*Val >= OpNum - 1) ? 0 : *Val + 1;
	}

	gbMenuVal = (PEXCH*)Str[*Val];

	if((giMenuDispPos || KEY_R || KEY_L) && (aiOn || giGrayOnly)) {
		if(*Val >= OpNum) *Val = 0;
		DISPCLRSTR(Str[*Val], gbMenuY+gbStgPos[giLV], MN_SXSP, MN_SUBSIZE, MN_SUBSIZE);
	}

	menu_dir(aiOn);
}
#else
void menu_str(const int aiOn, BYTE *Val, int OpNum, const PEXCH** Str)
{	// 170209 KSH

    if(giMenuDispPos && aiOn) {     // 170530 KSH
        if(*Val >= OpNum) *Val = 0;
        const BYTE bOld = *Val;
        gbMenuVal = (PEXCH*)Str[*Val];

        while(gbMenuVal == _S()) {
            *Val = *Val + 1;
            if(*Val >= OpNum) *Val = 0;
            gbMenuVal = (PEXCH*)Str[*Val];
            if(*Val == bOld) goto DISPLAY_STR;
        }
    }
    do {
        if(giMenuDispPos == 0 && aiOn) {
            if(KEY_L)   *Val = (*Val == 0) ? OpNum - 1 : *Val - 1;
            if(KEY_R)   *Val = (*Val >= OpNum - 1) ? 0 : *Val + 1;
        }
        gbMenuVal = (PEXCH*)Str[*Val];
    } while(gbMenuVal == _S());

DISPLAY_STR:
    if((giMenuDispPos || KEY_R || KEY_L) && (aiOn || giGrayOnly)) {
        DISPCLRSTR(Str[*Val], gbMenuY+gbStgPos[giLV], MN_SXSP, MN_SUBSIZE, MN_SUBSIZE);
    }
    menu_dir(aiOn);
}
#endif

void menu_val(BYTE *Val, UINT anMin, UINT anMax, UINT anRotation)
{
	if(giMenuDispPos == 0) {
		UINT nA, nB;

		if(anRotation) {
			nA = anMax;
			nB = anMin;
		}
		else {
			nA = anMin;
			nB = anMax;
		}

		if(KEY_L) *Val = (*Val <= anMin) ? (BYTE)nA : *Val - 1;
		if(KEY_R) *Val = (*Val >= anMax) ? (BYTE)nB : *Val + 1;
	}
	else {
		if(*Val < anMin) *Val = anMin;
		if(*Val > anMax) *Val = anMax;
	}
}

void menu_bar(const int aiOn, BYTE *Val, const UINT anMin, const UINT anMax, const UINT anRotation, const PEXCH *Unit)
{
	if(aiOn) menu_val(Val, anMin, anMax, anRotation);

	if((giMenuDispPos || KEY_R || KEY_L) && (aiOn || giGrayOnly)) {
		const UINT nPosY = gbMenuY+gbStgPos[giLV];
    	DispClrDec(*Val, nPosY, MN_SXSP, 3);
		if(Unit) {
			DISPCLRSTR(Unit, nPosY, MN_SXSP+3, MN_SUBSIZE-3, MN_SUBSIZE-3);
		}
		else {
			OsdDispBar(*Val, nPosY, anMin, anMax);
		}
	}

	//if(gbMenuList) TxStr((BYTE*)MENU_NAME, *Val, "\n");

	gbMenuVal = 0;

	menu_dir(aiOn);
}

void menu_val_ex(const int aiOn, BYTE *apbValL, BYTE *apbValH, const WORD awMin, const WORD awMax)
{
	int iVal = ((*apbValH)<<8) | (*apbValL);

	if(giMenuDispPos == 0 && aiOn)
	{
		KeyAccLevel(&giKeyAdd);

		if(KEY_L) {
			const int iValTmp = iVal - giKeyAdd;
			iVal = MAX(awMin, iValTmp);
		}
		if(KEY_R) {
			const int iValTmp = iVal + giKeyAdd;
			iVal = MIN(awMax, iValTmp);
		}

		*apbValH = (iVal>>8)&0xff;
		*apbValL = iVal&0xff;

		gbMenuVal = 0;
	}

	if((giMenuDispPos || KEY_R || KEY_L) && (aiOn || giGrayOnly)) {
		int2str(gbStr, iVal, (iVal < 10) ? 1 : (iVal < 100) ? 2 : (iVal < 1000) ? 3 : 4);
		DispClrStr(gbStr, DRAW_Y, MN_SXSP, 4, MN_SUBSIZE);
	}

	menu_dir(aiOn);
}

void menu_pos(const PEXCH* Title, int MenuNum, const PEXCH** Str)
{
	if(giMenuDispChg)
	{
		if(MenuNum) giMenuDispChg = 0;

		int i;

		STRLEN(i, Title);
		//DispClr(MN_TITLE, h760(0x8,MN_MXSP), LINESIZE - h760(0x8,MN_MXSP) - 3);
		DispClr(MN_TITLE, MN_MXSP, MN_LINESIZE);
		DISPSTR(Title, MN_TITLE, MN_XCENT - (i>>1) - (giLV==1), i);

//			gbMenuY = MN_YSTART;

		for(i=0; i<MenuNum; i++)
		{
			DISPCLRSTR(Str[i], gbMenuY+i, MN_MXSP, (MN_SXSP-MN_MXSP)/*MN_LINESIZE*/, (MN_SXSP-MN_MXSP)/*MN_LINESIZE*/);
		}

		for(; i<giMenuNum; i++)
		{
			DispClr(gbMenuY+i, MN_MXSP, MN_LINESIZE);
		}
		giMenuNum = MenuNum;

	}
	else if(!giMenuDispPos){		// 13.11.8 LJH ���� Ű ����  ����
		if((KEY_U || KEY_D) && MenuNum) {
			if((const PEXCH*)gbMenuVal != _S(NOT_USED)) OsdMenuPos(0);	// !! if���� MN_WHITE���� ����, finger clear�� �׻� ����

			if(KEY_U)	gbStgPos[giLV] = (gbStgPos[giLV] == 0) ? MenuNum - 1 : gbStgPos[giLV] - 1;
			if(KEY_D)	gbStgPos[giLV] = (gbStgPos[giLV] == MenuNum - 1) ? 0 : gbStgPos[giLV] + 1;

			//OsdMenuPos(1);
		}
	}

	DRAW_Y = gbMenuY+gbStgPos[giLV];

	if(MenuNum && Str) gbMenuList = (PEXCH*)Str[gbStgPos[giLV]];
}

void MenuSave(UINT anSaveOn)
{
	int i;
//	UINT bParSaveChk=0;

 	if (!anSaveOn) {										// No save & Exit
		//for(i=0; i<MN_PAR_EA; i++) gbMnParTblOld[i] = gbMnParTbl[i];		// �ƹ��͵� ����	// 15.08.24 ksh
		for(i=0; i<MN_PAR_EA; i++) gbMnParTbl[i] = gbMnParTblOld[i];		// ����				// 15.08.24 ksh
		MenuResetFnc();
 	}
	else {													// Save
		MP(MP_START) = (BYTE)((MN_DATA_ID>>8)&0xff);
		MP(MP_END)	 = (BYTE)((MN_DATA_ID)&0xff);

		for(i=0; i<MN_PAR_EA; i++) {
			if(gbMnParTblOld[i] != gbMnParTbl[i])
			{
				gbMnParTblOld[i] = gbMnParTbl[i];
//				bParSaveChk = 1;
				gbMnParSaveChk = 1;		// EN778
			}
		}
	}
//
//	if(bParSaveChk&&anSaveOn) {
//		#if model_Save
//			SfWrite2(gbMnParTbl, MN_PAR_EA, FLASH_MENU_MODE);
//		#else
//			TwiWrEep2(TWI_EEP_MENU_STT, gbMnParTbl, MN_PAR_EA);
//		#endif
//	}
}

void MenuPar2Buf(void)
{
	//MENU_PAR -> BUF
	gbModeBufOutFps		= MP(MpOutFps);
	gbModeBufSysFreq	= MP(MpSysFreq);
	gbModeBufSdiForm	= MP(MpSdiForm);
	gbModeBufSdiMode	= MP(MpSdiMode);
	gbModeBufAnlForm	= MP(MpAnlForm);
}

void MenuBuf2Par(void)
{
	//BUF -> MENU_PAR
	MP(MpOutFps) 	= gbModeBufOutFps;
	MP(MpSysFreq)	= gbModeBufSysFreq;
	MP(MpSdiForm)	= gbModeBufSdiForm;
	MP(MpSdiMode)	= gbModeBufSdiMode;
	MP(MpAnlForm)	= gbModeBufAnlForm;

//	MenuSave(MN_ON); 
}

void ChangeMenuSize(void)
{
	if(gbMnDebugFnc == 0) {
		MN_MXSP = MN_MXSP_DEF;

		if(!MODE_CVBS_ON){
			if(MODE_1M_ON)			MN_FONT_1M
			else if(MODE_2M_ON)		MN_FONT_2M
			else if(MODE_4M_ON)		MN_FONT_4M
			else if(MODE_5M_ON)		MN_FONT_5M
			else					MN_FONT_2M
		}
		else{
									MN_FONT_CVBS
		}
	}
	else {
		MN_MXSP = 0;
		if(MODE_5M_ON)				MN_FONT_DEBUG_H
		else						MN_FONT_DEBUG			// Test & Debug
	}

}

void MenuResetFnc(void)
{
	SetFontChg();			// Language sel

	UartBaudRate();
}

void MenuChangeRedraw(void)
{
	OsdWhiteAll();
	OsdClearAll();
	ChangeMenuSize();
	OsdCamTitle();
	menu_redraw(1,0);
}

void MpUpSharePar(void)
{
	//AGC - 1Byte
	// Mirror - 1bit, Flip - 1bit
	
}

//*************************************************************************************************
// Initial
//-------------------------------------------------------------------------------------------------
void InitMenuSet(void)
{
	MENU_LIB_LIST
}

void InitMenu(void)
{	// Initiate Menu
	TxStrDecNoIRQ("Menu Init... ", 0, 0);

	UINT i;
	UINT nResetKey = 0;

	InitMenuSet();

	#if (model_Key==0)		// AD Key
//		nResetKey = (ADC_KEYr>(UINT)UP(UpADC_LEVEL_C))&&(ADC_KEYr<(UINT)UP(UpADC_LEVEL_U));
//		nResetKey = (ADC_KEYr>((UINT)UP(UpADC_LEVEL_U)-0x10))&&(ADC_KEYr<((UINT)UP(UpADC_LEVEL_U)+0x10));		// if up key is pressed
		nResetKey = (ADC_KEYr<(((UINT)UP(UpADC_LEVEL_U)+(UINT)UP(UpADC_LEVEL_D))>>1));           // 141031 LH

	#else
//		nResetKey = 0;

	#endif


#if model_MenuDefSet == 1
	if (((WORD)((MSP(MP_START)<<8)|MSP(MP_END))!=(WORD)MN_DATA_ID)||nResetKey) {	// Parameter reset condition
		MenuResetSet(1);
		gbMnParSaveChk = 1;
		TxStrNoIRQ("MENU SET PAR reset ", 0, 0);
	}
#endif

	for(i=0; i<MN_PAR_EA; i++) gbMnParTblOld[i] = gbMnParTbl[i];     		// Make backup - �̹� Init() -> AppLoadPar() ���� Flash�κ��� gbMnParTbl�� �����

	if (MP_END_REAL>MP_END)	TxStrNoIRQ("MENU PAR size over ", 0, 0);			// Parameter verify
	if (((WORD)((MP(MP_START)<<8)|MP(MP_END))!=(WORD)MN_DATA_ID)||nResetKey) {	// Parameter reset condition
		MenuReset();
		MenuSave(MN_ON);
		TxStrNoIRQ("MENU PAR reset ", 0, 0);
    }

	//----------------------------------------------------------------------------------------
	// OSD FONT
	FONT_ONw(1);

	MASK_CHADw(SPACE_CHAR_ID);	// null char
	HALF_CHADw(0x1f0);			// not use half char

	FONT_LV0w(FONT_LV0);
	FONT_LV1w(FONT_LV1);
	FONT_LV2w(FONT_LV2);
	FONT_LV3w(FONT_LV3);

	ChangeMenuSize();

    OsdWhiteAll();															// ATTR reset
    //OsdAttrsStgPos(0, MN_YELLOW);

	OsdClearAll();

	OsdCamTitle();															// Display CAM title

	MenuResetFnc();

	MenuPar2Buf();

	gbModeBufBefore		= MP(MpOutFps);
	gbModeSdiBufBefore	= MP(MpSdiForm);
	
	gbMirBuf			= MP(MpMirror);
	gbFlpBuf			= MP(MpFlip);

}

//------------------------------------------------------------------------------
void MenuReset(void)
{	// parameter reset
	UINT i = 0;

#if model_MenuDefSet == 1
	for(i=0; i<MN_PAR_EA; i++) gbMnParTbl[i] = gbMnSetParTbl[i];

	OsdCamTitle();

	MenuPar2Buf();
}

void MenuResetSet(const int aiReset)
{
	UINT i = 0;

	if(aiReset == 0) {	// aiReset = 0:MENU - SAVE, 1:InitMenu()
		for(i=0; i<MN_PAR_EA; i++) gbMnSetParTbl[i] = gbMnParTbl[i];
		gbMnSetParSaveChk = 1;
		return;
}
#endif

	//----------------------------------------------------------------------------------------
	MP(MP_START)		= (BYTE)((MN_DATA_ID>>8)&0xff);		// Parameter verify
	MP(MP_END)			= (BYTE)((MN_DATA_ID)&0xff);			// "

//*******************************
// Output Format
//*******************************
// Frequency (50Hz or 60Hz)
	// System
//	MP(MpSysFreq)		= MN_SYSFREQ_60;
	MP(MpSysFreq)		= MN_SYSFREQ_50;

#if(Model_Rear)
	MP(MpOutFps)		= MN_2M_1080p_50_60;
	MP(MpSdiForm)		= MN_EXSDI_270M_3G;
#else
//	MP(MpOutFps)		= MN_2M_1080p_25_30;
//	MP(MpSdiForm)		= MN_EXSDI_135MP;
	MP(MpOutFps)		= MN_4M_1440p_25_30;
	MP(MpSdiForm)		= MN_EXSDI_270M;
#endif

	MP(MpSdiMode)		= MN_EXSDI;

	//HD-Analog
	MP(MpAnlMode)		= MN_HDANALOG_ON;
	MP(MpAnlForm)		= MN_HD_T;	

	MP(MpCBar)			= MN_OFF;
//	MP(MpCBar)			= MN_ON;

	MP(MpLanguageSel)	= 0;
	MP(MpOutFormat)		= MN_FRMT_HD;				// (Fixed)
	MP(MpCamID)			= /*0*/1;
	MP(MpBaudrate)		= MN_BR_INIT;

	MP(MpCamTitleOn)	= /*MN_CT_RIGHT_UP*//*MN_CT_LEFT_DOWN*/MN_CT_OFF;

	gbCamTitle(0) 		= '0';
	gbCamTitle(1) 		= '0';
	gbCamTitle(2) 		= '0';
	gbCamTitle(3) 		= '0';
	gbCamTitle(4) 		= '0';
	gbCamTitle(5) 		= '0';
	gbCamTitle(6) 		= '0';
	gbCamTitle(7) 		= '0';

	// AE
	MP(MpBrightness)	= 6;
	MP(MpIris)			= MN_LENS_MNL;					// Enx Socket Bd

	MP(MpIrisLvl)		= 20;
	MP(MpShutter)		= MN_SHUT_AUTO;
	MP(MpShutSpd)		= MN_MNL_SHUT_30;
	MP(MpDcMode)		= MN_DC_IN;
	MP(MpShtMode)		= MN_SHT_NORMAL;
	
	MP(MpAgc)			= 8;

	// Backlight
	MP(MpHlMaskThrs)	= 10;
	MP(MpHlMaskColor)	= 7;

	MP(MpBlcPosX)		= 8;
	MP(MpBlcPosY)       = 7;
	MP(MpBlcSizX)       = 3;
	MP(MpBlcSizY)       = 3;

#if(model_Sens_CLR_HDR)
//	MP(MpBackLight)		= MN_BL_OFF;
	MP(MpBackLight) 	= MN_BL_WDR;

	MP(MpWdrMode)		= MN_WDR_SENS_CLR;
//	MP(MpWdrMode)		= MN_WDR_SENSF;
#else

	MP(MpBackLight) 	= MN_BL_WDR;
	MP(MpWdrMode)		= MN_WDR_SENSF;
#endif


#if(Model_BW==1)
	MP(MpTdn)			= MN_TDN_NIGHT;					//210112 YTM
#else
	MP(MpTdn)			= MN_TDN_DAY;					//210112 YTM
#endif

#if(model_Led == 1 || model_Led == 3)															//210225 YTM

    MP(MpAdaptive)      = 0;
#else // 190219 JJH
	MP(MpAdaptive)      = 1;
	MP(MpLedDrv)        = MN_LED_DRV;
    MP(MpLedSw)	        = AE_LED_INVERT;	
    MP(MpLedPower)      = AE_LED_Power;	
#endif

	MP(MpTdnDly)		= MN_3sLOW;//MN_3sMID/*MN_3sLOW*/;
//	MP(MpLedSatCtrl)	= 10;
	MP(MpLedSatCtrl)	= 5;
	MP(MpTdnSw) 		= 0; 				// High
	MP(MpTdnDNThres) 	= 13;
	MP(MpTdnNDThres) 	= 7;

    gbMnTdnCfg(0)->bDNThres   = 13;
    gbMnTdnCfg(0)->bNDThres   = 7;
//    gbMnTdnCfg(1)->bDNThres   = 5;
//    gbMnTdnCfg(1)->bNDThres   = 3;
  	gbMnTdnCfg(1)->bDNThres	= 6;
  	gbMnTdnCfg(1)->bNDThres	= 8;

	
	// ACE,Defog
//	MP(MpAce)			= MN_4sOFF;
	MP(MpAce)			= MN_4sLOW;
	
	MP(MpDefog)			= MN_OFF;
	MP(MpDefogMode)		= MN_DEFOG_AUTO;
	MP(MpDefogLevel)	= MN_3sMID;

	// AWB
	MP(MpAwb)			= MN_AWB_AUTO;
	MP(MpAwbPrst)		= MN_OFF;
	MP(MpAwbMnl)		= MN_3sMID;
	MP(MpRgain)			= 10;
	MP(MpBgain)			= 10;
	MP(MpSaturation)	= 12;	// COLOR GAIN
//	MP(MpSaturation)	= 10;	// COLOR GAIN

	MP(MpColorTone) 	= MN_COOL_TONE;

	// DNR
	MP(MpAdnr)			= MN_ON;
	MP(MpSharpness) 	= 5;

//	MP(MpGamma)			= MN_GAMMA_055;
	MP(MpGamma) 		= MN_GAMMA_AUTO;

#if(Model_Rear)
	MP(MpMirror)		= MN_OFF;
//	MP(MpFlip)			= MN_ON;
//	MP(MpMirror)		= MN_ON;
	MP(MpFlip)			= MN_OFF;
#else
	#if(model_Sens==SENS_IMX307)
	MP(MpMirror)		= MN_ON;
	MP(MpFlip)			= MN_ON;
	#else
	MP(MpMirror)		= MN_OFF;
	MP(MpFlip)			= MN_OFF;
	#endif
#endif

	MP(MpShading)		= MN_ON;
	MP(MpShdWeight)		= /*80;*/ 40;					// Next Version

	// Privacy Box, Polygon
	MP(MpPrivacy)		= MN_OFF;
	MP(MpPvcZone)		= 0;
	MP(MpPvcTrans)		= 0/*2*/;
	MP(MpPvcYLevel)		= 10;
	MP(MpPvcCRLevel)	= 10;
	MP(MpPvcCBLevel)	= 10;
	for (i=0; i<PVC_EA; i++) {
		gbMnPvcCfg(i)->bAction = 1;
		gbMnPvcCfg(i)->bPosX   = 12+((i%6)*4);
		gbMnPvcCfg(i)->bPosY   = 2+((i/6)*4);
		gbMnPvcCfg(i)->bSizX   = 3;
		gbMnPvcCfg(i)->bSizY   = 3;
	}
	
	// Hidden MENU
	MP(MpShdDet)		= MN_OFF;

#if(model_Lens==0) 	// Focus assist	// 170301 LH
	MP(MpFaThrs)		= 5;
	MP(MpFaColor)		= 1;
#endif

	// 20130724
#if(model_Lens==1)   //TwoMotorAF
    MP(MpMAF_mode)		= 0;    // 180702 JJH
    MP(MpMAF_Filter)	= 0;
    MP(MpMAF_MotorInit)	= 0;
    MP(MpMAF_LensModel)	= 0;
    MP(MpMAF_TestMode) = 0;
	MP(MpMAF_UccZoomHold) = 0;  // 181128 JJH        
#endif

#if model_MenuDefSet == 1
	for(i=0; i<MN_PAR_EA; i++) gbMnSetParTbl[i] = gbMnParTbl[i];
	gbMnSetParSaveChk = 1;
#else

	MP(MpColorSat)	= 64;
	MP(MpColorHue) 	= 128;
	MP(MpContrast) 	= 20;

	OsdCamTitle();

#endif

//*************************************************************************************************
// Eyenix reserved setting
//-------------------------------------------------------------------------------------------------
#if(model_Sens_NonWdr)
	MP(MpBackLight)		= MN_BL_OFF;
#endif

	MP(MpOutScl)		= MN_OUTSCL_FULL;			// (Fixed)
	MP(MpOutSclUser)	= 10/*0*/;					// (Fixed)

	MP(MpLedCtrl)		= LED_ON;					// LED ON (Default)
//	MP(MpFrameRate)		= FPS_275;					// Frame Rate (Default)
	MP(MpFrameRate)		= FPS_30;					// Frame Rate (Default)

	MP(MpIQVer)			= 0x00;

	MenuPar2Buf();
}


//*************************************************************************************************
// Menu
//-------------------------------------------------------------------------------------------------
void Menu(void)
{
//	if (gbMnClose==0)	return;

	static BYTE gbPassCnt1=0;
	static BYTE gbPassCnt2=0;
	static BYTE gbPassCnt3=0;
	static BYTE gbPassCnt4=0;
	static BYTE gbPassCnt5=0;
	static BYTE gbPassCnt6=0;

	const BYTE gbPassKeys1[] = MENU_PK_SETUP;
	const BYTE gbPassKeys2[] = MENU_PK_DEBUG;

	const int iSetMnOn = (!MENU_TITLE_IS(OFF)) ? (LibUtlKeyPass(gbPassKeys1, sizeof(gbPassKeys1), &gbPassCnt1) == 1) : 0 ;

	  //----------------------------------------------------------------------------------------
	  // Menu Exit by Time out
#if (MN_AUTO_OFF)
	  static UINT gnMnTimeCnt = 0;

	  //  if(giLV >= 0) {
  //  if ( (!MENU_TITLE_IS(OFF))&&(!MENU_TITLE_IS(DEBUG)) ) {
	  if ( (!MENU_TITLE_IS(OFF))&&(gbMnDebugFnc==0) ) {

		  if (KEY) gnMnTimeCnt = 0;
		  else {
			   gnMnTimeCnt++;
			  if ( gnMnTimeCnt >= ( MN_OFF_TIME * (MN_FPS_LOW ? (FR>>1) : FR) ) )
			  {
				  gnMnTimeCnt = 0;
				  MenuSave(MN_OFF);
				  MENU_CLOSE();
			  }

		  }
	  }
	  else	  gnMnTimeCnt = 0;

	  /* Debug
		  FONT_ONw(1);
		  DispDatDec("giLV____",  1, 24, giLV);
		  DispDatDec("MenuCnt_",  2, 24, gnMnTimeCnt);
	  */
#endif

	  //----------------------------------------------------------------------------------------

	  if((MENU_NAME_IS(FRAMERATE) || MENU_NAME_IS(FREQ)) && (KEY_L || KEY_R)) {
		  #if(model_IspO_ANL)
			  extern BYTE gbCkeyDir;
			  gbCkeyDir = 0;
		  #endif
	  }
    // 180910 JJH Adaptive Lighting

	#if (model_Led==0 || model_Led==2)				//210112 YTM				//210225 YTM
        if (MENU_TITLE_IS(DAYnNIGHT) && (KEY_L || KEY_R)) gbLedMenuChg = 1;
    #endif

	// for BLC Mode
	if(MP(MpMirror) != gbMirBuf)	MP(MpBlcPosX) = (AE_BLC_WIN_MENU_H-MIN((MP(MpBlcPosX)+MP(MpBlcSizX)), AE_BLC_WIN_MENU_H));
	if(MP(MpFlip) != gbFlpBuf)		MP(MpBlcPosY) = (AE_BLC_WIN_MENU_V-MIN((MP(MpBlcPosY)+MP(MpBlcSizY)), AE_BLC_WIN_MENU_V));

	gbMirBuf = MP(MpMirror);
	gbFlpBuf = MP(MpFlip);
	
  	//----------------------------------------------------------------------------------------
	
	MENU_START

// Main MENU --------------------------------------------------------------------------------
// EN772
#if(model_Iris==0)						// no Iris
	#if(model_Lens==1)
	MENU_SET(  9, MENU, MN_ON, MN_OFF,
	#else
	MENU_SET(  8, MENU, MN_ON, MN_OFF,
	#endif
#else									// DC Iris
	#if(model_Lens==1)
	MENU_SET( 10, MENU, MN_ON, MN_OFF,
	#else
	MENU_SET(  9, MENU, MN_ON, MN_OFF,
	#endif
			IRIS,			MENU_STRn(MN_ON, , MP(MpIris), 2, ELC, ALC),
#endif
		#if(model_Lens==1)    // 180802 JJH
            MOTORIZED,      MENU_ONEi(MN_ON, e, MN_ON, MOTORIZED, ),
		#endif

			EXPOSURE,		MENU_ONEi(MN_ON, e, MN_ON, EXPOSURE, ),
			BACKLIGHT,			
			({if(MODE_DISABLE_WDR)	{ MENU_STRi(MN_ON, (MP(MpBackLight)!= MN_OFF), BACKLIGHT, ,	,MP(MpBackLight), 3, OFF, HLCe, BLCe);}
			  else				  	{ MENU_STRi(MN_ON, (MP(MpBackLight)!= MN_OFF), BACKLIGHT, ,	,MP(MpBackLight), 4, OFF, HLCe, BLCe, WDRe);}}),
			
            DAYnNIGHT,      MENU_ONEi(MN_ON, e, MN_ON, DAYnNIGHT, ),
			COLORm,			MENU_ONEi(MN_ON, e, MN_ON, COLORm, ),
			DNR,			MENU_STRn(MN_ON, , MP(MpAdnr), 2, OFF, ON),		
			IMAGE,			MENU_ONEi(MN_ON, e, MN_ON, IMAGE, ),
			SYSTEM, 		MENU_ONEi(MN_ON, e, !iSetMnOn, SYSTEM, /*MENU_OFF_GRAY_ONLY();*/ ),		// if not Setup menu
			EXIT,			MENU_ONEo(MN_ON,  , MN_ON, MenuSave(MN_ON);))

	// MENU - IRIS
	MENU_SET( 2, IRIS, MN_ON, MN_OFF,
			LEVEL,			MENU_BARn(MN_ON, , MP(MpIrisLvl), 0, 20, 1 ),
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))

#if(model_Lens==0) // 170301 LH
	// MENU - Focus ADJ
	MENU_SET( 3, FOCUS_ADJ, MN_ON, MN_OFF,
			LEVEL,			MENU_BARn(MN_ON, , MP(MpFaThrs), 0, 10, 1),
			COLOR,			MENU_STRn(MN_ON, , MP(MpFaColor), 8, WHT, YEL, CYN, GRN, MAG, RED, BLU, BLK),
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))
#endif

#if(model_Lens==1)
	// MENU - MOTORIZED     180802 JJH
	MENU_SET( 4, MOTORIZED, MN_ON, MN_OFF,
			AF_MODE,			MENU_STRn(MN_ON, , MP(MpMAF_mode), 2, ONESHOT, MANUAL),
			DnN_FILTER,			MENU_STRn(MN_ON, , MP(MpMAF_Filter), 2, SYNC_OFF, SYNC_ON),
			INITIAL,			MENU_PUSH(MN_ON, MP(MpMAF_MotorInit), ONp, PUSHING, PUSH_DELAY_NOT/*PUSH_DELAY_NOR*/, ),
			RETURN,				MENU_ONEo(MN_ON, e, MN_ON, ))
#endif

	// MENU - EXPOSURE
	MENU_SET( 4, EXPOSURE, MN_ON, MN_OFF,
			BRIGHTNESS, 	MENU_BARn(MN_ON, , MP(MpBrightness), 0, 12, 1),
			SHUTTER,		MENU_STRi(MN_ON, MENU_VAL_IS(AUTOe) || MENU_VAL_IS(MANUALe), SHUTTER, , , MP(MpShutter), 3, AUTOe, MANUALe, FLICKER),
			AGC,			MENU_BARn(MN_ON, , MP(MpAgc), 0, 20, 1),
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))

	// MENU - EXPOSURE - SHUTTER:MANUAL
	MENU_SET( 2, SHUTTER, MP(MpShutter)==MN_SHUT_MNL, MN_OFF,
			SPEED,
			
			({if(MP(MpSysFreq) == MN_SYSFREQ_60){
				if(MN_FPS_LOW)	{ MENU_STR(MN_ON, MP(MpShutSpd), 11, SHUT_30, SHUT_60, SHUT_120, SHUT_250, SHUT_500, SHUT_1000, SHUT_2000, SHUT_4000, SHUT_8000, SHUT_15000, SHUT_30000)}
				else			{ MENU_STR(MN_ON, MP(MpShutSpd), 10,          SHUT_60, SHUT_120, SHUT_250, SHUT_500, SHUT_1000, SHUT_2000, SHUT_4000, SHUT_8000, SHUT_15000, SHUT_30000)}
			}else{
				if(MN_FPS_LOW)	{ MENU_STR(MN_ON, MP(MpShutSpd), 11, SHUT_25, SHUT_50, SHUT_100, SHUT_200, SHUT_400, SHUT_800, SHUT_1600, SHUT_3200, SHUT_6400, SHUT_12800, SHUT_25600)}
				else			{ MENU_STR(MN_ON, MP(MpShutSpd), 10,          SHUT_50, SHUT_100, SHUT_200, SHUT_400, SHUT_800, SHUT_1600, SHUT_3200, SHUT_6400, SHUT_12800, SHUT_25600)} } }),
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))


	// MENU - EXPOSURE - SHUTTER:AUTO
	MENU_SET( 2, SHUTTER, MP(MpShutter)==MN_SHUT_AUTO, MN_OFF,
			MODE,
					#if(model_Iris_DC)
						({if(MP(MpIris)==MN_LENS_MNL) {
							MENU_STR(MN_ON, MP(MpShtMode), 2, NORMAL, DEBLUR )				// CAUTION ! -> MENU_STR
						}else{	//MP(MpIris) == MN_LENS_DC
							MENU_STR(MN_ON, MP(MpDcMode), 3, INDOOR, OUTDOOR, DEBLUR)} }),
					#else
							MENU_STRn(MN_ON, , MP(MpShtMode), 2, NORMAL, DEBLUR ),			// CAUTION ! -> MENU_STRn
					#endif
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))

	// MENU - BACKLIGHT:HLC
	MENU_SET( 3, BACKLIGHT, MP(MpBackLight) == MN_BL_HLC, MN_OFF,
			LEVEL,			MENU_BARn(MN_ON, , MP(MpHlMaskThrs), 0, 20, 1),
			COLOR,			MENU_STRn(MN_ON, , MP(MpHlMaskColor), 8, WHT, YEL, CYN, GRN, MAG, RED, BLU, BLK),
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))


	// MENU - BACKLIGHT:BLC
	MENU_SET( 5, BACKLIGHT, MP(MpBackLight) == MN_BL_BLC, MN_OFF,
			HPOS,			MENU_VARn(MN_ON, , MP(MpBlcPosX), 0, AE_BLC_WIN_MENU_H, 1, ),
			VPOS,			MENU_VARn(MN_ON, , MP(MpBlcPosY), 0, AE_BLC_WIN_MENU_V, 1, ),
			HSIZE,			MENU_VARn(MN_ON, , MP(MpBlcSizX), 1, AE_BLC_WIN_MENU_H, 1, ),
			VSIZE,			MENU_VARn(MN_ON, , MP(MpBlcSizY), 1, AE_BLC_WIN_MENU_V, 1, ),
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))

	// MENU - BACKLIGHT:WDR
	MENU_SET( 2, BACKLIGHT, MP(MpBackLight) == MN_BL_WDR, MN_OFF,
	
		#if(model_Sens_LFM_HDR)
			WDR_MODE,		MENU_STRn(MN_ON, , MP(MpWdrMode), 2, , SENS_LFM),
		#else
			#if(model_Sens_CLR_HDR)
			WDR_MODE,		MENU_STRn(MN_ON, , MP(MpWdrMode), 2, SENSF, SENS_CLR),
			#else
			WDR_MODE,		MENU_STRn(MN_ON, , MP(MpWdrMode), 1, SENSF),
			#endif
		#endif
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))

    // MENU - DAY&NIGHT
	//----------------------------------WHITE LED(ONLY COLOR MODE)-------------------------------------
#if (model_Led == 2)																																				//210225 YTM
		MENU_SET( 7, DAYnNIGHT, MN_ON, MN_OFF,		
			WHITE_LED,      MENU_STRn( MN_ON, if_KEY_LR(MENU_REDRAW()) , MP(MpAdaptive), 3, OFF, Adaptive, FULL ),
            ANTI_SAT,       MENU_BARn( (MP(MpAdaptive)!=MN_OFF), , MP(MpLedSatCtrl), 0, 20, 1),
            LED_POWER,      MENU_BARn( MP(MpAdaptive)==2, , MP(MpLedPower), 0, 10, 1),
            DN_THRES,       MENU_BARn((MP(MpAdaptive)!=0), if(TDN_DNTHRS <= TDN_NDTHRS){ gbMnTdnCfg(0)->bDNThres =(KEY_L) ? 20 : (KEY_R) ? gbMnTdnCfg(0)->bNDThres+1 : gbMnTdnCfg(0)->bDNThres;}		//210312 YTM
                                                                                                        if_KEY_LR(MENU_REDRAW());, gbMnTdnCfg((MP(MpAdaptive)==1))->bDNThres, 0, 20, 1),
            ND_THRES,       MENU_BARn((MP(MpAdaptive)!=0), if(TDN_NDTHRS >= TDN_DNTHRS){ gbMnTdnCfg(0)->bNDThres =(KEY_R) ? 0 : (KEY_L) ? gbMnTdnCfg(0)->bDNThres-1 : gbMnTdnCfg(0)->bNDThres;}			//210312 YTM
                                                                                                        if_KEY_LR(MENU_REDRAW());, gbMnTdnCfg((MP(MpAdaptive)==1))->bNDThres, 0, 20, 1),
            DELAY,          MENU_STRn((MP(MpAdaptive)!=0), , MP(MpTdnDly), 3, LOW, MIDDLE, HIGH),																										//210312 YTM
            RETURN,         MENU_ONEo(MN_ON, e, MN_ON, ))
#else
	//---------------------------------------IR LED----------------------------------------------------
	//---------------------------------------AUTO MODE-------------------------------------------------
	#if (model_Led == 0)																										// Adaptive Light (LPWM)
		MENU_SET( 7, DAYnNIGHT, MP(MpTdn) == MN_TDN_AUTO, MN_OFF,		
	#else																														//FULL MODE(1), NOT USE(3)
		MENU_SET( 5, DAYnNIGHT, MP(MpTdn) == MN_TDN_AUTO, MN_OFF,	
	#endif
            MODE,           MENU_STRn(MN_ON, if_KEY_LR(MENU_CHANGE()), MP(MpTdn), 4, AUTO, COLOR, BnW, EXTERN),
		#if(model_Led == 0)
			IR_LED, 		MENU_STRn( MP(MpTdn) == MN_TDN_AUTO, if_KEY_LR(MENU_REDRAW()) ,MP(MpAdaptive), 2, OFF, Adaptive),
			ANTI_SAT,		MENU_BARn( ((MP(MpAdaptive)!=MN_OFF)&&(MP(MpTdn)!= MN_TDN_DAY)), , MP(MpLedSatCtrl), 0, 20, 1),
    	#endif
            DN_THRES,       MENU_BARn(MN_ON, if(TDN_DNTHRS <= TDN_NDTHRS){ gbMnTdnCfg(0)->bDNThres =(KEY_L) ? 20 : (KEY_R) ? gbMnTdnCfg(0)->bNDThres+1 : gbMnTdnCfg(0)->bDNThres;}
                                                                                                        if_KEY_LR(MENU_REDRAW());, gbMnTdnCfg((MP(MpAdaptive)==1))->bDNThres, 0, 20, 1),
            ND_THRES,       MENU_BARn(MN_ON, if(TDN_NDTHRS >= TDN_DNTHRS){ gbMnTdnCfg(0)->bNDThres =(KEY_R) ? 0 : (KEY_L) ? gbMnTdnCfg(0)->bDNThres-1 : gbMnTdnCfg(0)->bNDThres;}
                                                                                                        if_KEY_LR(MENU_REDRAW());, gbMnTdnCfg((MP(MpAdaptive)==1))->bNDThres, 0, 20, 1),
            DELAY,          MENU_STRn(MN_ON, , MP(MpTdnDly), 3, LOW, MIDDLE, HIGH),
        	RETURN,         MENU_ONEo(MN_ON, e, MN_ON, ))
	//---------------------------------------COLOR MODE------------------------------------------------
		MENU_SET( 2, DAYnNIGHT, MP(MpTdn) == MN_TDN_DAY, MN_OFF,																															//210312 YTM
            MODE,           MENU_STRn(MN_ON, if_KEY_LR(MENU_CHANGE()), MP(MpTdn), 4, AUTO, COLOR, BnW, EXTERN),

            RETURN,         MENU_ONEo(MN_ON, e, MN_ON, ))
	//---------------------------------------B&W MODE--------------------------------------------------
	#if (model_Led == 3)																																					//210225 YTM
		MENU_SET( 2, DAYnNIGHT, MP(MpTdn) == MN_TDN_NIGHT , MN_OFF,						//3	  - NOT USED																	//210225 YTM
	#elif (model_Led == 1)																																					//210225 YTM
		MENU_SET( 7, DAYnNIGHT, MP(MpTdn) == MN_TDN_NIGHT, MN_OFF,						//1   - GPIO							//210112 YTM: GPIO full
    #else
		MENU_SET( 8, DAYnNIGHT, MP(MpTdn) == MN_TDN_NIGHT, MN_OFF,						//0	  - LPWM							//210112 YTM: LPWM Adaptive or LPWM full	
	#endif
            MODE,           MENU_STRn(MN_ON,  if_KEY_LR(MENU_CHANGE()), MP(MpTdn), 4, AUTO, COLOR, BnW, EXTERN),
		#if (model_Led != 3)																																								//210312 YTM
			#if (model_Led == 0)																								// Adaptive Light (LPWM)					
				IR_LED, 		MENU_STRn( MP(MpTdn) == MN_TDN_NIGHT, if_KEY_LR(MENU_REDRAW()) ,MP(MpAdaptive), 3, OFF, Adaptive, FULL),									
			#else																												//FULL MODE(1:GPIO)							
				IR_LED, 		MENU_STRn( MP(MpTdn) == MN_TDN_NIGHT, if_KEY_LR(MENU_REDRAW()) ,MP(MpAdaptive), 3, OFF, , FULL),
			#endif
				ANTI_SAT,		MENU_BARn( ((MP(MpAdaptive)!=MN_OFF)&&(MP(MpTdn)!= MN_TDN_DAY)), , MP(MpLedSatCtrl), 0, 20, 1),																													//210225 YTM
			#if (model_Led == 0)																																			
				LED_POWER,		MENU_BARn( ((MP(MpAdaptive)==2)&&(MP(MpTdn)!= MN_TDN_DAY)), , MP(MpLedPower), 0, 10, 1),
			#endif
		
            DN_THRES,       MENU_BARn((MP(MpAdaptive)!=0), if(TDN_DNTHRS <= TDN_NDTHRS){ gbMnTdnCfg(0)->bDNThres =(KEY_L) ? 20 : (KEY_R) ? gbMnTdnCfg(0)->bNDThres+1 : gbMnTdnCfg(0)->bDNThres;}
																									if_KEY_LR(MENU_REDRAW());, gbMnTdnCfg((MP(MpAdaptive)==1))->bDNThres, 0, 20, 1),			//gbMnTdnCfg((MP(MpAdaptive)==1)
            ND_THRES,       MENU_BARn((MP(MpAdaptive)!=0), if(TDN_NDTHRS >= TDN_DNTHRS){ gbMnTdnCfg(0)->bNDThres =(KEY_R) ? 0 : (KEY_L) ? gbMnTdnCfg(0)->bDNThres-1 : gbMnTdnCfg(0)->bNDThres;}
                                                                                                        if_KEY_LR(MENU_REDRAW());, gbMnTdnCfg((MP(MpAdaptive)==1))->bNDThres, 0, 20, 1),
            DELAY,          MENU_STRn((MP(MpAdaptive)!=0), , MP(MpTdnDly), 3, LOW, MIDDLE, HIGH),
       #endif																																												//210312 YTM
            RETURN,         MENU_ONEo(MN_ON, e, MN_ON, ))
	//---------------------------------------EXTERN MODE------------------------------------------------
	#if (model_Led == 3)																											//210225 YTM
		MENU_SET( 6, DAYnNIGHT, MP(MpTdn) == MN_TDN_EXTERN , MN_OFF,						//3	  - NOT USED
	#elif (model_Led == 1)
		MENU_SET( 8, DAYnNIGHT, MP(MpTdn) == MN_TDN_EXTERN , MN_OFF,						//1   - GPIO							//210225 YTM
    #else
		MENU_SET( 9, DAYnNIGHT, MP(MpTdn) == MN_TDN_EXTERN , MN_OFF,						//0   - LPWM							//210225 YTM
    #endif
			MODE,			MENU_STRn(MN_ON,  if_KEY_LR(MENU_CHANGE()), MP(MpTdn), 4, AUTO, COLOR, BnW, EXTERN),
		#if (model_Led != 3)																										//210225 YTM
			#if (model_Led == 0)																								// Adaptive Light (LPWM)
				IR_LED, 		MENU_STRn(MP(MpTdn) == MN_TDN_EXTERN, if_KEY_LR(MENU_REDRAW()) ,MP(MpAdaptive), 3, OFF, Adaptive, FULL),
			#else																															//FULL MODE(1:GPIO)			//210225 YTM
				IR_LED, 		MENU_STRn(MP(MpTdn) == MN_TDN_EXTERN, if_KEY_LR(MENU_REDRAW()) ,MP(MpAdaptive), 3, OFF, , FULL),
    		#endif

				ANTI_SAT,		MENU_BARn( (MP(MpAdaptive)!=MN_OFF), , MP(MpLedSatCtrl), 0, 20, 1),
			#if (model_Led == 0)																									//210225 YTM	
				LED_POWER,		MENU_BARn( ((MP(MpAdaptive)==2)&&(MP(MpTdn)!= MN_TDN_DAY)), , MP(MpLedPower), 0, 10, 1),
			#endif
		#endif
			EXTERN_SW,      MENU_STRn(MN_ON, , MP(MpTdnSw), 2, HIGH, LOW),
            DN_THRES,       MENU_BARn(MN_ON, , MP(MpTdnDNThres), 0, 20, 1),
            ND_THRES,       MENU_BARn(MN_ON, , MP(MpTdnNDThres), 0, 20, 1),
            DELAY,          MENU_STRn(MN_ON, , MP(MpTdnDly), 3, LOW, MIDDLE, HIGH),
            RETURN,         MENU_ONEo(MN_ON, e, MN_ON, ))
#endif	


	MENU_SET( 4, COLORm, MN_ON, MN_OFF,
			AWB,			MENU_STRi(MN_ON, MENU_VAL_IS(MANUALe), AWB, ,
										MENU_VAL_PUSH(PRESETp, PUSHING, PUSH_DELAY_NOR, MP(MpAwbPrst) = MN_OFF, MP(MpAwbPrst) = MN_ON),
										MP(MpAwb), 4, AUTO, AUTOext, PRESETp, MANUALe),
			COLORGAIN,		MENU_BARn(MN_ON, , MP(MpSaturation), 0, 20, 1 ),
			// COLORSAT,		MENU_BARn(MN_ON, , MP(MpColorSat), 0, 128, 1 ),
			// COLORHUE,		MENU_BARn(MN_ON, , MP(MpColorHue), 0, 255, 1 ),
			COLORTONE,		MENU_STRn(MN_ON, , MP(MpColorTone), 2, COOL_TONE, WARM_TONE),
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))

	// MENU - WHITE BAL:MANUAL
	MENU_SET( 4, AWB, MP(MpAwb) == MN_AWB_MNL, MN_OFF,
			C_TEMP,			MENU_STRn(MN_ON, , MP(MpAwbMnl), 3, TEMP1, TEMP2, TEMP3),
			RGAIN,			MENU_BARn(MN_ON, , MP(MpRgain), 0, 20, 1),
			BGAIN,			MENU_BARn(MN_ON, , MP(MpBgain), 0, 20, 1),
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))
			
	// MENU - IMAGE
	MENU_SET( 10, IMAGE, MN_ON, MN_OFF,
			SHARPNESS,		MENU_BARn(MN_ON, , MP(MpSharpness), 0, 10, 1 ),
			GAMMA,			
			({if(MODE_WDR_ON){MENU_STRn(MN_ON, , MP(MpGamma), 5, , , , , AUTO);}
			  else			  {MENU_STRn(MN_ON, , MP(MpGamma), 5, GAMMA_045, GAMMA_055, GAMMA_065, GAMMA_075, AUTO);}}),
			MIRROR,			MENU_STRn(MN_ON, , MP(MpMirror), 2, OFF, ON),
			FLIP,			MENU_STRn(MN_ON, , MP(MpFlip), 2, OFF, ON),		
			DWDR/*ACE*/,	
			({if(MODE_WDR_ON){MENU_STRn(MN_ON, , MP(MpAce), 1, AUTO);}
			  else			  {MENU_STRn(MN_ON, , MP(MpAce), 4, OFF, LOW, MIDDLE, HIGH);}}),
			CONTRAST,		MENU_BARn(MN_ON, , MP(MpContrast), 0, 40, 1 ),  
		 	DEFOG,		  	
		 	({if(MODE_WDR_ON){MENU_STRn(MN_ON, , MP(MpDefog), 1, AUTO);}
			  else			  {MENU_STRi(MN_ON, MENU_VAL_IS(ONe), DEFOG, , , MP(MpDefog), 2, OFF, ONe);}}),

			SHADING,		MENU_ONEi(MN_ON, e, MN_ON, SHADING, ),
			PRIVACY,		MENU_ONEi(MN_ON, e, MN_ON, PRIVACY, ),
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))

											
	// MENU - IMAGE - DEFOG
	MENU_SET( 3, DEFOG, MN_ON, MN_OFF,
			MODE,			MENU_STRn(MN_ON, , MP(MpDefogMode), 2, MANUAL, AUTO),
			LEVEL,			MENU_STRn(MN_ON, , MP(MpDefogLevel), 3, LOW, MIDDLE, HIGH),
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))

	// MENU - IMAGE - SHADING
	MENU_SET( 4, SHADING, MN_ON, MN_OFF,
			MODE,			MENU_STRn(MN_ON, , MP(MpShading), 2, OFF, ON),
			WEIGHT,			MENU_VARn(MN_ON, , MP(MpShdWeight), 0, 100, 1, PERCENT/*%*/),
		  	SHADINGDET,		MENU_ONEo(MN_ON, ONp, MN_ON,
											MP(MpShdDet) = 1;
											MP(MpShading) = 0;
											MENU_CLOSE();
											goto menu_start;
											),	
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))

		// MENU - IMAGE - PRIVACY
	MENU_SET( 2, PRIVACY, MN_ON, MN_OFF,
			BOX,			MENU_STRi(MN_ON, MENU_VAL_IS(ONe),	   BOX, MENU_OFF_GRAY_ONLY(), , MP(MpPrivacy), 2, OFF, ONe),			
			RETURN, 		MENU_ONEo(MN_ON, e, MN_ON, ))

	// MENU - IMAGE - PRIVACY - BOX
	MENU_SET( 8, BOX, MN_ON, MN_OFF,
			ZONENUM,		MENU_VARn(MN_ON, if_KEY_LR(MENU_REDRAW_GRAY_ONLY();), MP(MpPvcZone), 0, PVC_EA-1, 1, ),
			ZONEDISP,		MENU_STRn(MN_ON, if_KEY_LR(MENU_REDRAW_GRAY_ONLY();), gbMnPvcCfg(MP(MpPvcZone))->bAction, 2, OFF, ON),
			HPOS,			MENU_VARn(gbMnPvcCfg(MP(MpPvcZone))->bAction, , gbMnPvcCfg(MP(MpPvcZone))->bPosX, 0, BOX_XMAX, 0, ),
			VPOS,			MENU_VARn(gbMnPvcCfg(MP(MpPvcZone))->bAction, , gbMnPvcCfg(MP(MpPvcZone))->bPosY, 0, BOX_YMAX, 0, ),
			HSIZE,			MENU_VARn(gbMnPvcCfg(MP(MpPvcZone))->bAction, , gbMnPvcCfg(MP(MpPvcZone))->bSizX, 0, BOX_XMAX, 0, ),
			VSIZE,			MENU_VARn(gbMnPvcCfg(MP(MpPvcZone))->bAction, , gbMnPvcCfg(MP(MpPvcZone))->bSizY, 0, BOX_YMAX, 0, ),
			BOX_ATTR,		MENU_ONEi(MN_ON, e, MN_ON, BOX_ATTR, ),
//			YLEVEL, 		MENU_BARn(MN_ON, , MP(MpPvcYLevel), 0, UP(UpBOX_COLOR_STEP), 1),
//			CBLEVEL,		MENU_BARn(MN_ON, , MP(MpPvcCBLevel),0, UP(UpBOX_COLOR_STEP), 1),
//			CRLEVEL,		MENU_BARn(MN_ON, , MP(MpPvcCRLevel),0, UP(UpBOX_COLOR_STEP), 1),
//			TRANS,			MENU_VARn(MN_ON, , MP(MpPvcTrans), 0, 3, 1, ),
			RETURN, 		MENU_ONEo(MN_ON, e, MN_ON, ))

	MENU_SET( 5, BOX_ATTR, MN_ON, MN_OFF,
			YLEVEL, 		MENU_BARn(MN_ON, , MP(MpPvcYLevel), 0, BOX_COLOR_STEP, 1),
			CBLEVEL,		MENU_BARn(MN_ON, , MP(MpPvcCBLevel),0, BOX_COLOR_STEP, 1),
			CRLEVEL,		MENU_BARn(MN_ON, , MP(MpPvcCRLevel),0, BOX_COLOR_STEP, 1),
			TRANS,			MENU_VARn(MN_ON, , MP(MpPvcTrans), 0, 3, 1, ),
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))


	// MENU - SYSTEM
//	MENU_SET( 9, SYSTEM, MN_ON, MN_OFF,
	MENU_SET( 7, SYSTEM, MN_ON, MN_OFF,
			COMM,			MENU_ONEi(MN_ON, e, MN_ON, COMM, ),
//			OUTPUT,			MENU_ONEi(MN_ON, e, MN_ON, OUTPUT, ),
			OUTPUT, 		MENU_ONEi(MN_ON, e, MN_ON, OUTPUT, if(MODE_CVBS_ON) gbModeBufOutFps = 0;),
//			IMAGERANGE,		MENU_STRi(MN_ON, MENU_VAL_IS(USERe), IMAGERANGE, , , MP(MpOutScl), 3, FULL, COMP, USERe),
//			COLORSPACE,		MENU_STRn(MN_ON, , MP(MpOutFormat), 3, SD_CbCr, HD_CbCr, YUV),
			COLORBAR,		MENU_STRn(MN_ON, , MP(MpCBar), 2, OFF, ON),
			LANGUAGE,		MENU_STRn(MN_ON, if_KEY_LR(SetFontChg(); MENU_CHANGE()), MP(MpLanguageSel), 5, ENG, CHN, CHNs, JPN, KOR),
			CAMTITLE,		MENU_STRi(MN_ON, MP(MpCamTitleOn)!=MN_CT_OFF, CAMTITLE, , if_KEY_LR(OsdCamTitle();), MP(MpCamTitleOn), 3, OFF, RIGHT_UPe, LEFT_DOWNe),
			RESET,			//MENU_PUSH(MN_ON, MP(MpReset), ONp, PUSHING, PUSH_DELAY_NOR, MenuReset(); SetFontChg(); MENU_CHANGE(); ),
							({ if(gbPushCnt >= PUSH_DELAY_NOR) { if(pKEY_C) { MENU_ONEn(MN_ON,PUSHING) } else { gbPushCnt = 0; MENU_VAL_REDRAW(ONp); } }
							else { MENU_ONEn(MN_ON,ONp)  MENU_CODE( MENU_VAL_PUSH(ONp, PUSHING, PUSH_DELAY_NOR, , MenuReset(); MenuResetFnc(); MENU_CHANGE();) ) } }),
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))

	// MENU - SYSTEM - COMM.
	MENU_SET( 3, COMM, MN_ON, MN_OFF,
			CAMID,			MENU_VARn(MN_ON, , MP(MpCamID), 0, 255, 1, ),
			BAUDRATE,		MENU_STRn(MN_ON, if_KEY_LR(UartBaudRate();), MP(MpBaudrate), 5, 2400, 4800, 9600, 57600, 115200),
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))

	// MENU - SYSTEM - OUTPUT.

#if(mode_IspO_M)
	MENU_SET( 4, OUTPUT, MN_ON, MN_OFF,
#elif((mode_IspO_A)||(mode_IspO_MS))
	MENU_SET( 5, OUTPUT, MN_ON, MN_OFF,
#else
	MENU_SET( 6, OUTPUT, MN_ON, MN_OFF,
#endif

			FRAMERATE,
			
  			#if (model_1M)
					({if(gbModeBufSysFreq == MN_SYSFREQ_50){
						{MENU_STRn(MODE_MENU_CVBS_OFF, if_KEY_LR(if (!MODE_3G_BASE_MENU) gbModeBufSdiForm=1; MENU_REDRAW()), gbModeBufOutFps, 2, 720p_25, 720p_50);}}
					else{
						{MENU_STRn(MODE_MENU_CVBS_OFF, if_KEY_LR(if (!MODE_3G_BASE_MENU) gbModeBufSdiForm=1; MENU_REDRAW()), gbModeBufOutFps, 2, 720p_30, 720p_60);}}} ),
				
			#elif (model_2M)
				#if(model_Sens_US2Mto5M)
					({if(gbModeBufSysFreq == MN_SYSFREQ_50){
						{if(MODE_C_MENU)	{MENU_STRn(MODE_MENU_CVBS_OFF, if_KEY_LR(if (!MODE_3G_BASE_MENU) gbModeBufSdiForm=1; MENU_REDRAW()), gbModeBufOutFps, 7, 720p_25, 720p_50, 1080p_25, 1080p_50, 1440p_25, , 1944p_20);}
						 else				{MENU_STRn(MODE_MENU_CVBS_OFF, if_KEY_LR(if (!MODE_3G_BASE_MENU) gbModeBufSdiForm=1; MENU_REDRAW()), gbModeBufOutFps, 7, 720p_25, 720p_50, 1080p_25, 1080p_50, 1440p_25, 1944p_12p5, 1944p_20);}}}
					else{
						{if(MODE_C_MENU)	{MENU_STRn(MODE_MENU_CVBS_OFF, if_KEY_LR(if (!MODE_3G_BASE_MENU) gbModeBufSdiForm=1; MENU_REDRAW()), gbModeBufOutFps, 7, 720p_30, 720p_60, 1080p_30, 1080p_60, 1440p_30, , 1944p_20);}
						 else				{MENU_STRn(MODE_MENU_CVBS_OFF, if_KEY_LR(if (!MODE_3G_BASE_MENU) gbModeBufSdiForm=1; MENU_REDRAW()), gbModeBufOutFps, 7, 720p_30, 720p_60, 1080p_30, 1080p_60, 1440p_30, 1944p_12p5, 1944p_20);}}}}),
				#else
					({if(gbModeBufSysFreq == MN_SYSFREQ_50){
						{MENU_STRn(MODE_MENU_CVBS_OFF, if_KEY_LR(if (!MODE_3G_BASE_MENU) gbModeBufSdiForm=1; MENU_REDRAW()), gbModeBufOutFps, 9, 720p_25, 720p_50, 1080p_25, 1080p_50, 1440p_25, , ,1080p_29p1, 1080p_27p5);}}
					else{
						{MENU_STRn(MODE_MENU_CVBS_OFF, if_KEY_LR(if (!MODE_3G_BASE_MENU) gbModeBufSdiForm=1; MENU_REDRAW()), gbModeBufOutFps, 9, 720p_30, 720p_60, 1080p_30, 1080p_60, 1440p_30, , ,1080p_29p1, 1080p_27p5);}}} ),
				#endif
				
			#elif (model_5M)
					#if(model_Sens_Upto4M)
					({if(gbModeBufSysFreq == MN_SYSFREQ_50){
						{MENU_STRn(MODE_MENU_CVBS_OFF, if_KEY_LR(if (!MODE_3G_BASE_MENU) gbModeBufSdiForm=1; MENU_REDRAW()), gbModeBufOutFps, 3, 720p_25, 1080p_25, 1440p_25);}}
					else{
						{MENU_STRn(MODE_MENU_CVBS_OFF, if_KEY_LR(if (!MODE_3G_BASE_MENU) gbModeBufSdiForm=1; MENU_REDRAW()), gbModeBufOutFps, 3, 720p_30, 1080p_30, 1440p_30);}}}),
							
					#else
					({if(gbModeBufSysFreq == MN_SYSFREQ_50){
						{MENU_STRn(MODE_MENU_CVBS_OFF, if_KEY_LR(if (!MODE_3G_BASE_MENU) gbModeBufSdiForm=1; MENU_REDRAW()), gbModeBufOutFps, 5, 720p_25, 1080p_25, 1440p_25, 1944p_12p5, 1944p_20);}}
					else{
						{MENU_STRn(MODE_MENU_CVBS_OFF, if_KEY_LR(if (!MODE_3G_BASE_MENU) gbModeBufSdiForm=1; MENU_REDRAW()), gbModeBufOutFps, 5, 720p_30, 1080p_30, 1440p_30, 1944p_12p5, 1944p_20);}}}),
					#endif
			#endif

			FREQ,
					({if(MODE_MENU_CVBS_OFF){
						if(MODE_5M_20_ON_MENU)			{{MENU_STRn(MN_ON, if_KEY_LR(MENU_REDRAW()), gbModeBufSysFreq, 2, , 60HZ);}}
						else if(MODE_5M_125_ON_MENU)	{{MENU_STRn(MN_ON, if_KEY_LR(MENU_REDRAW()), gbModeBufSysFreq, 2, 50HZ, );}}
						else							{{MENU_STRn(MN_ON, if_KEY_LR(MENU_REDRAW()), gbModeBufSysFreq, 2, 50HZ, 60HZ);}}}
					  else								{{MENU_STRn(MN_ON, if_KEY_LR(MENU_REDRAW()), gbModeBufSysFreq, 2, PAL, NTSC);}}}),

		#if(model_IspO_SDI)
			SDI_MODE,
				({
				//*********************
				//--EX-SDI --
				//*********************
				#if (model_ExSdiSel==1)
				if (MODE_EXSDI_COND_CF&&(!GpioGetPin(GPIO_EXSDI_SEL))) {
				#elif (model_ExSdiSel==2)
				if (MODE_EXSDI_COND_CF&&(gbModeBufSdiMode==MN_EXSDI)) {
				#else
				if (0) {
				#endif
					if(MODE_3G_BASE_MENU)	{MENU_STRn(MODE_MENU_CVBS_OFF, , gbModeBufSdiForm, 4, OFF, , ,EX_SDI_270M3G);}
					else					{MENU_STRn(MODE_MENU_CVBS_OFF, , gbModeBufSdiForm, 3, OFF, EX_SDI_135MP, EX_SDI_270M);}
				}

				//*********************
				//--HD-SDI --
				//*********************
				#if (model_ExSdiSel==1)
				else if (MODE_HDSDI_COND_CF&&(GpioGetPin(GPIO_EXSDI_SEL))) {
				#elif (model_ExSdiSel==2)
				else if (MODE_HDSDI_COND_CF&&(gbModeBufSdiMode==MN_HDSDI)) {
				#else
//				else if (MODE_HDSDI_COND_CF) {
				if (0) {
				#endif
					if(MODE_3G_BASE_MENU)	{gbModeBufSdiMode = MN_EXSDI;}
					else					{MENU_STRn(MODE_MENU_CVBS_OFF, , gbModeBufSdiForm, 2, OFF, HD_SDI);}
				}
				else {
											{MENU_ONEn(MN_OFF, OFF);}
				}
				}),
		#endif
		
		#if(model_IspO_ANL)
			#if ((model_Aout==0)||(model_HdAnSel==0))
					CVBS_,			MENU_STRn((model_Aout!=2), if_KEY_LR(MENU_REDRAW()), gbModeBufAnlForm, 2, OFF, ON),
			#else
				//*********************
				//--HD-Analog --
				//*********************
					ANALOG_MODE,	MENU_STRn((model_Aout!=2), if_KEY_LR(MENU_REDRAW()), gbModeBufAnlForm, 5, OFF, CVBS_, HD_T, HD_C, HD_A),
			#endif
		#endif
		
			CONFIRM,		//MENU_PUSH(MN_ON, MP(MpReset), ONp, PUSHING, PUSH_DELAY_NOR, MenuReset(); SetFontChg(); MENU_CHANGE(); ),
							({ if(gbPushCnt >= PUSH_DELAY_NOR) { if(pKEY_C) { MENU_ONEn(MN_ON,PUSHING) } else { gbPushCnt = 0; MENU_VAL_REDRAW(YESp); } }
							else { MENU_ONEn(MN_ON,YESp)  MENU_CODE( MENU_VAL_PUSH(YESp, PUSHING, PUSH_DELAY_NOR, , gbModeConfirm = 1; gbModeChgHotKey = 0;)) } }),
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, gbModeBufReturn = 1;))
			

	// MENU - SYSTEM - IMAGE RANGE:USER
	MENU_SET( 2, IMAGERANGE, MP(MpOutScl) == 2, MN_OFF,
			OFFSET, 		MENU_BARn(MN_ON, ,MP(MpOutSclUser),0,32,1),
			RETURN,			MENU_ONEo(MN_ON, e, MN_ON, ))

	// MENU - SYSTEM - CAMTITLE
	MENU_EXT( CAMTITLE, MN_ON, MN_ON, giMenuNum = 8;/*������ ���� SubMenu 8��° ���α��� ����*/,


	OsdAttrsStgPosAr(1, MN_WHITE);
	OsdAttrsStgPosAr(2, MN_WHITE);
	OsdAttrsStgPosAr(3, MN_WHITE);

	SETFONTID(gbMenuY+1, MN_XTITL, 162);										// Display Arrow-down

	SETFONTATTR(gbMenuY+2, MN_XTITL, MN_YELLOW);								// Display Cam-title
	DispStr((const char*)&gbCamTitle(0), gbMenuY+2, MN_XTITL, 0x8);			//		"

	SETFONTATTR(gbMenuY+1, MN_XTITL, MN_YELLOW);								// Display line
	DrawStr(TLx8, gbMenuY+3, MN_XTITL, 8);

	//---------------------------------------------------------
	OsdAttrsStgPosAr(5, MN_WHITE);
	OsdAttrsStgPosAr(6, MN_WHITE);
	OsdAttrsStgPosAr(7, MN_WHITE);

	DrawStr(UPsDN_d_CHAR_SELECT,gbMenuY+5, MN_MXSP+3, 19);		// Display UP/DN Instruction
	DrawStr(LEsRI_d_POSITION,	gbMenuY+6, MN_MXSP+3, 16);		// Display LE/RI Instruction
	DrawStr(ENTER_d_RETURN,		gbMenuY+7, MN_MXSP+3, 14);		// Display ENTER Instruction
	)


// Setup MENU --------------------------------------------------------------------------------
#if(model_Lens==1)
    MENU_SET(6, SETUP, MN_ON, MN_OFF,
#else					// DC, 2Motor
	MENU_SET(4, SETUP, MN_ON, MN_OFF,
#endif
			CAMVERSION,		MENU_DIRn(MN_ON
							/* MENU_DIRn:Pre Code */,
							/* MENU_DIRn:Value Change */,
							/* MENU_DIRn:Display Code */,
							static char bVal1[11] = "0000(0000)";
							uint2strh(bVal1, model_ver, 4);
							uint2strh(bVal1+5, gDataID, 4);
							bVal1[4] = '(';
							bVal1[9] = ')';
							bVal1[10] = 0;
							DispStr(bVal1, DRAW_Y, MN_SXSP, 10);
							/* MENU_DIRn:End Code */,),

  		#if(model_Lens==1) // 181128 JJH
            MOTOR_SETUP,    MENU_STRi(MN_ON, MENU_VAL_IS(ONe), MOTOR_SETUP, /*MENU_OFF_GRAY_ONLY()*/,  if_KEY_LR(OsdWhiteAll(); OsdClearAll(); ChangeMenuSize(); MENU_CHANGE()) , gbMAF_SETUP, 2, OFF, ONe),
            UCC_ZOOMKEY,	MENU_STRn(MN_ON, , MP(MpMAF_UccZoomHold), 2, ON, HOLDING),
  		#endif

		#if model_MenuDefSet == 1
			SAVE,			MENU_PUSH(MN_ON, gbMnSave, ONp, PUSHING, PUSH_DELAY_NOR, MenuResetSet(0);),
		#else
			SAVE,			MENU_ONEn(MN_OFF, ONp),
		#endif

         // 190219 JJH
            LED_SET,        MENU_ONEi(MP(MpAdaptive), e, MN_ON, LED_SET, ),

			RETURN,			MENU_ONEo(MN_ON, , MN_ON, MenuSave(MN_ON); ))


        //#if(model_Led==0)
		#if(Adaptive_led)														//210302 YTM          
            MENU_SET( 3, LED_SET, MN_ON, MN_OFF,
            LED_DRV,        MENU_STRn(MN_ON,  if_KEY_LR(MENU_REDRAW()), MP(MpLedDrv), 3, AP, BP, EUP),
            LED_SW,         MENU_STRn(MN_ON, , MP(MpLedSw), 2, LOW, HIGH), 
            RETURN,         MENU_ONEo(MN_ON, e, MN_ON, ))
        #endif

#if(model_Lens==1) // 180802 JJH remove lens selection
                MENU_SET( 5, MOTOR_SETUP, MN_ON, MN_OFF,
                      MAF_DEVMODE,        MENU_STRn(MN_ON, , gbMAF_DevMode, 2, OFF, ON),
//                      MAF_TESTMODE,		  MENU_STRn(MN_ON, , MP(MpMAF_TestMode), 2, OFF, ON),
                      MAF_ZOOM_AREA,      MENU_ONEi(MN_ON, e, MN_ON, MAF_ZOOM_AREA, ),
                      MAF_FOCUS_AREA,     MENU_ONEi(MN_ON, e, MN_ON, MAF_FOCUS_AREA, ),
//                      INITIAL,            MENU_PUSH(MN_ON, MP(MpMAF_MotorInit), ONp, PUSHING, PUSH_DELAY_NOT/*PUSH_DELAY_NOR*/, ),
                      MAF_AUTO_TRACE,     MENU_PUSH(MN_ON, gbMAF_Calibration, ONp, PUSHING, PUSH_DELAY_NOT/*PUSH_DELAY_NOR*/, ),
                      RETURN,             MENU_ONEo(MN_ON, e, MN_ON, ))

                MENU_SET( 4, MAF_ZOOM_AREA, MN_ON, MN_OFF,
                        MAF_TOTAL_AREA,     MENU_VARn(MN_ON, gbMAF_MZpos_S=(gbMAF_MZpos_S > gbMAF_MZrange_T) ? gbMAF_MZrange_T : gbMAF_MZpos_S;
                                                             gbMAF_MZpos_E=(gbMAF_MZpos_E > gbMAF_MZrange_T) ? gbMAF_MZrange_T : gbMAF_MZpos_E;
                                                             if_KEY_LR(MENU_CHANGE());
                                                             , gbMAF_MZrange_T, 0, 200, 1, ),
                        MAF_START_POS,      MENU_VARn(MN_ON, gbMAF_MZpos_S= (gbMAF_MZpos_S > gbMAF_MZrange_T) ?  0 : gbMAF_MZpos_S;
                                                             if_KEY_LR(MENU_CHANGE());
                                                             , gbMAF_MZpos_S, 0, 200, 1, ),
                        MAF_END_POS,        MENU_VARn(MN_ON, gbMAF_MZpos_E=(gbMAF_MZpos_E > gbMAF_MZrange_T) ? gbMAF_MZrange_T : gbMAF_MZpos_E;
                                                             if_KEY_LR(MENU_CHANGE());
                                                             , gbMAF_MZpos_E, 0, 200, 1, ),
                        RETURN,             MENU_ONEo(MN_ON, e, MN_ON, ))

                MENU_SET( 4, MAF_FOCUS_AREA, MN_ON, MN_OFF,
                        MAF_TOTAL_AREA,     MENU_VARn(MN_ON, gbMAF_MFpos_S=(gbMAF_MFpos_S > gbMAF_MFrange_T) ? gbMAF_MFrange_T : gbMAF_MFpos_S;
                                                             gbMAF_MFpos_E=(gbMAF_MFpos_E > gbMAF_MFrange_T) ? gbMAF_MFrange_T : gbMAF_MFpos_E;
                                                             if_KEY_LR(MENU_CHANGE());
                                                             , gbMAF_MFrange_T, 0, 200, 1, ),
                        MAF_START_POS,      MENU_VARn(MN_ON, gbMAF_MFpos_S=(gbMAF_MFpos_S > gbMAF_MFrange_T) ?  0 : gbMAF_MFpos_S;
                                                             if_KEY_LR(MENU_CHANGE());
                                                             , gbMAF_MFpos_S, 0, 200, 1, ),
                        MAF_END_POS,        MENU_VARn(MN_ON, gbMAF_MFpos_E=(gbMAF_MFpos_E > gbMAF_MFrange_T) ? gbMAF_MFrange_T : gbMAF_MFpos_E;
                                                             if_KEY_LR(MENU_CHANGE());
                                                             , gbMAF_MFpos_E, 0, 200, 1, ),
                        RETURN,             MENU_ONEo(MN_ON, e, MN_ON, ))

#endif

// Debug MENU --------------------------------------------------------------------------------

	MENU_SET(4, DEBUG, MN_ON, MN_OFF,

			FUNCTION,		MENU_STRn(MN_ON, if_KEY_LR(OsdWhiteAll(); OsdClearAll(); ChangeMenuSize(); OsdCamTitle(); MENU_CHANGE();) , gbMnDebugFnc, 9, OFF, AE, AF, AWB, DBG_4, DBG_5, DBG_6, TDN_DBG, STATUS),
			BYPASS,			MENU_STRn(MN_ON,
								//if_KEY_LR(if(gbMnDebugBypass) { TIM_CH3_EN = 0; } else { TIM_CH3_EN = 1; } )
								, gbMnDebugBypass, 2, OFF, ON),
			UP_RESET,		({ if(gbPushCnt >= PUSH_DELAY_NOR) { if(pKEY_C) { MENU_ONEn(MN_ON,PUSHING) } else { gbPushCnt = 0; MENU_VAL_REDRAW(ONp); } }
							else { MENU_ONEn(MN_ON,ONp)  MENU_CODE( MENU_VAL_PUSH(ONp, PUSHING, PUSH_DELAY_NOR, , extern void UpReset(void); UpReset(); ) ) } }),
			RETURN, 		MENU_ONEo(MN_ON, e, MN_ON, ))


	MENU_DISPLAY_END()

// Condition for Menu call --------------------------------------------------------------------
	if(gbMenuPushState == 2) {
		gbMenuPushState = 0;
		MP(MpAwbPrst) = 0;
		MENU_REDRAW();
	}

	if(iSetMnOn&&MENU_NAME_IS(SYSTEM)) {										// Setup MENU start
		MENU_OPEN(SETUP);
		goto menu_start;
	}

	if(MENU_TITLE_IS(OFF)) {	// if not Main Menu

		if(LibUtlKeyPass(gbPassKeys2, sizeof(gbPassKeys2), &gbPassCnt2) == 1) {	// Debug MENU start
			//OsdWhiteAll(); OsdClearAll();
			//MN_MXSP = 0;
			//MN_POS_SIZ_SMALL
			MENU_OPEN(DEBUG);
			goto menu_start;
		}


	// KEY reset time
	#define PRESS_CNT	(FPS_VDO*3)

	static UINT nPrsCnt = 0;
	if(KEY)		nPrsCnt = PRESS_CNT;
	
	if(nPrsCnt == 0)	{gbPassCnt3 = 0; gbPassCnt4 = 0; gbPassCnt5 = 0; gbPassCnt6 = 0;}
	else				{nPrsCnt--;}

#if(model_IspO_SDI)
	#if (model_ExSdiSel)

		const BYTE gbPassKeys3[] = MENU_PK_EXSDI_ON;
		const BYTE gbPassKeys4[] = MENU_PK_EXSDI_OFF;

		#if(model_ExSdiSel==1)													
		if(MODE_EXSDI_ON){														

		#elif(model_ExSdiSel==2)												
		if(LibUtlKeyPass(gbPassKeys3, sizeof(gbPassKeys3), &gbPassCnt3) == 1) {	// EX-SDI Selection
		#endif																	
			MP(MpSdiMode) = MN_EXSDI;
			gbModeBufSdiMode = MN_EXSDI;

			if(MODE_EXSDI_3G_BASE)	{MP(MpSdiForm) = MN_EXSDI_270M_3G; gbModeBufSdiForm = MN_EXSDI_270M_3G;}
			else					{MP(MpSdiForm) = MN_EXSDI_135MP; 	gbModeBufSdiForm = MN_EXSDI_135MP;}
			MenuSave(MN_ON);
		}

		#if(model_ExSdiSel==1)													
		if(MODE_HDSDI_ON){														
		#elif(model_ExSdiSel==2)												
		if(LibUtlKeyPass(gbPassKeys4, sizeof(gbPassKeys4), &gbPassCnt4) == 1) {	// HD-SDI Selection
		#endif
			MP(MpSdiMode) = MN_HDSDI;
			gbModeBufSdiMode = MN_HDSDI;
			
			if(MODE_SDI_3G_BASE){ 		//Don't modify !! (CAUTION!!)
				MP(MpSdiForm) = MN_EXSDI_270M_3G;
				gbModeBufSdiForm = MN_EXSDI_270M_3G;
			}
			else{
				MP(MpSdiForm) = MN_EXSDI_135MP;	
				gbModeBufSdiForm = MN_EXSDI_135MP;
				MenuSave(MN_ON);
			}
		}
	#endif
#endif

#if(model_IspO_ANL)
	#if (model_HdAnSel==2)
		#if(model_Aout==1)
		const BYTE gbPassKeys5[] = MENU_PK_HDANL_ON;
		const BYTE gbPassKeys6[] = MENU_PK_CVBS_ON;

		static BYTE gbPreBufAnlMode = 0x0;

		if(LibUtlKeyPass(gbPassKeys5, sizeof(gbPassKeys5), &gbPassCnt5) == 1) {
			MP(MpAnlMode) = MN_HDANALOG_ON;
			MP(MpAnlForm) = (gbPreBufAnlMode==MN_OFF)?(MN_HD_T):(gbPreBufAnlMode);
			gbModeBufAnlForm = MP(MpAnlForm);
			MenuSave(MN_ON);

			gbModeChgHotKey = 0x1;
		}
		
		if(LibUtlKeyPass(gbPassKeys6, sizeof(gbPassKeys6), &gbPassCnt6) == 1) {
			gbPreBufAnlMode = gbModeBufAnlForm;				// for Mode history

			// CVBS ON
			MP(MpAnlMode) = MN_CVBS_ON;
			MP(MpAnlForm) = MN_CVBS;
			gbModeBufAnlForm = MN_CVBS;
			MenuSave(MN_ON);

			gbModeChgHotKey = 0x0;
		}
		#endif
		
	#endif
#endif
		if (KEY_C &&										// 170215 KSH
			(!gbPassCnt2) && (!gbPassCnt3) && (!gbPassCnt4) &&
			(!gbPassCnt5) && (!gbPassCnt6)						) {

			MENU_OPEN(MENU);
			goto menu_start;
		}
	}
 	else if(KEY_E) 	MENU_CLOSE();		// Menu out by ECM KEY_E

//	FONT_ONw(1);
//	DispDat("CNT1",  5, 24, gbPassCnt1);
//	DispDat("CNT2",  6, 24, gbPassCnt2);


// Exceptional Menu --------------------------------------------------------------------------------

// CAM_TITLE
	if(MENU_TITLE_IS(CAMTITLE)) {
		if(KEY_L || KEY_R) {
			SETFONTATTR(gbMenuY+2, MN_XTITL+gbStgPos[giLV], MN_WHITE);
			SETFONTATTR(gbMenuY+1, MN_XTITL+gbStgPos[giLV], MN_WHITE);
			SETFONTID(gbMenuY+1, MN_XTITL+gbStgPos[giLV], 0);

			menu_val(gbStgPos+giLV, 0, 7, 1);
			SETFONTATTR(gbMenuY+2, MN_XTITL+gbStgPos[giLV], MN_YELLOW);
			SETFONTATTR(gbMenuY+1, MN_XTITL+gbStgPos[giLV], MN_YELLOW);
			SETFONTID(gbMenuY+1, MN_XTITL+gbStgPos[giLV], 162);
		}
		/*
		DispStr("gbCamTitle", 0, 30, 10);
		DispClrDec(gbCamTitle(gbStgPos[giLV]), 0, 42, 10);
		*/
		if(KEY_D || KEY_U) {
			switch( gbCamTitle(gbStgPos[giLV]) ) {
				case ' ' :	if(KEY_U) gbCamTitle(gbStgPos[giLV]) = '0';
							if(KEY_D) gbCamTitle(gbStgPos[giLV]) = 'Z';	break;
				case '0' :	if(KEY_U) gbCamTitle(gbStgPos[giLV]) = '1';
							if(KEY_D) gbCamTitle(gbStgPos[giLV]) = ' ';	break;
				case '9' :	if(KEY_U) gbCamTitle(gbStgPos[giLV]) = 'A';
							if(KEY_D) gbCamTitle(gbStgPos[giLV]) = '8';	break;
				case 'A' :	if(KEY_U) gbCamTitle(gbStgPos[giLV]) = 'B';
							if(KEY_D) gbCamTitle(gbStgPos[giLV]) = '9';	break;
				case 'Z' :	if(KEY_U) gbCamTitle(gbStgPos[giLV]) = ' ';
							if(KEY_D) gbCamTitle(gbStgPos[giLV]) = 'Y';	break;
				default  :	if(KEY_U) gbCamTitle(gbStgPos[giLV])++;
							if(KEY_D) gbCamTitle(gbStgPos[giLV])--;		break;
			}
			DispStr((const char*)&gbCamTitle(0), gbMenuY+2, MN_XTITL, 0x8);
			OsdCamTitle();
		}
	}

	if (MENU_TITLE_IS(BACKLIGHT)&&(MP(MpBackLight)==MN_BL_BLC))	gbMnBlcOsdOn = 1;
	else 															gbMnBlcOsdOn = 0;

	if(gbModeConfirm)	{MenuBuf2Par();	 gbModeConfirm = 0;	}
	if(gbModeBufReturn){MenuPar2Buf();	 gbModeBufReturn = 0;}

	
#if(model_IspO_ANL)
	if(MP(MpAnlForm)==MN_CVBS)			MP(MpAnlMode) = MN_CVBS_ON;
	else								MP(MpAnlMode) = MN_HDANALOG_ON;
#endif

	// WDR ON - Auto processing function
	static BYTE bWdrOnMenu = 0x0;
	static BYTE bAceMenuBuf = 0x0, bGammaMenuBuf = 0x0, bDefogMenuBuf = 0x0;

	if(bWdrOnMenu != MODE_WDR_ON){
		if(MODE_WDR_ON){
			bAceMenuBuf = MP(MpAce);
			bGammaMenuBuf = MP(MpGamma);
			bDefogMenuBuf = MP(MpDefog);
		}
		else{
			MP(MpAce) = bAceMenuBuf;
			MP(MpGamma) = bGammaMenuBuf;
			MP(MpDefog) = bDefogMenuBuf;
		}
	}
	bWdrOnMenu = MODE_WDR_ON;

	MpUpSharePar();
	
menu_end:

	gbMenuState = !MENU_TITLE_IS(OFF);	// 0:Menu Close 1:Menu Open

	return;
}

