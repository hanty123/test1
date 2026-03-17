/* **************************************************************************
 File Name	: 	app.c
 Description	:	EN772 - common application
 Designer		:	Lee, Hoon
 Modifier		:	Lee, Gyu Hong
 Date		:	19. 12. 18
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

//*************************************************************************************************
// Variables
//-------------------------------------------------------------------------------------------------
const char *gsBuildDate = "FW Date : "__DATE__" "__TIME__;
WORD gDataID = 0;

//*************************************************************************************************
// Functions
//-------------------------------------------------------------------------------------------------
void InitDataID(void)
{
	const UINT gsBuildDateLen = strlen(gsBuildDate);
	gDataID  = (*(gsBuildDate + gsBuildDateLen-1) - '0');
	gDataID += (*(gsBuildDate + gsBuildDateLen-2) - '0')<<4;
	gDataID += (*(gsBuildDate + gsBuildDateLen-4) - '0')<<8;
	gDataID += (*(gsBuildDate + gsBuildDateLen-5) - '0')<<12;
}

// Common ----------------------------------------------------------
void ISPM AppSavePar(void)
{	// save parameter to memory
	static BYTE bTwiWrEep2Rdy = 1;	// TwiWrEep2() Ready

	if (bTwiWrEep2Rdy) {

		if (gbMnParSaveChk) {			// Menu Parameter

			#if model_Save
				SfWrite2(gbMnParTbl, MN_PAR_EA, FLASH_MENU_MODE);
			#else
				TwiWrEep2(TWI_EEP_MENU_STT, gbMnParTbl, MN_PAR_EA);
			#endif

			gbMnParSaveChk = 0;
			bTwiWrEep2Rdy = 0;
		}
	  #if (model_Par==1)
		else if (gbUsrParSaveChk) {		// User Parameter

			#if model_Save
				SfWrite2(gbUsrParTbl, USR_PAR_EA, FLASH_USER_MODE);
			#else
				TwiWrEep2(TWI_EEP_USER_STT, gbUsrParTbl, USR_PAR_EA);
			#endif

			gbUsrParSaveChk = 0;
			bTwiWrEep2Rdy = 0;
		}
	  #endif
		else if (gbUsrDataSaveChk) {	// User Data

			#if model_Save
				SfWrite2(gbUsrDataTbl, USR_DATA_EA, FLASH_DATA_MODE);
			#else
				TwiWrEep2(TWI_EEP_DATA_STT, gbUsrDataTbl, USR_DATA_EA);
			#endif

			gbUsrDataSaveChk = 0;
			bTwiWrEep2Rdy = 0;
		}
	  #if model_MenuDefSet == 1
		else if (gbMnSetParSaveChk) {	// Menu Setting Parameter

			#if model_Save
				SfWrite2(gbMnSetParTbl, MN_PAR_EA, FLASH_MENU_SET_MODE);
			#else
				TwiWrEep2(TWI_EEP_CSTM_STT, gbMnSetParTbl, MN_PAR_EA);
			#endif

			gbMnSetParSaveChk = 0;
			bTwiWrEep2Rdy = 0;
		}
	  #endif
	  
	}

	#if model_Save
		bTwiWrEep2Rdy = 1;
	#else
		TwiWrEep2_continue			// continuous EEP ROM page Write
	#endif
}

void ISPM AppLoadPar(void)
{	// read parameter from memory

	if (gbMnParReadChk) {			// Menu Parameter

		#if model_Save
			SfRead2(gbMnParTbl, MN_PAR_EA, FLASH_MENU_MODE);
		#else
		    TwiRdEep(TWI_EEP_MENU_STT, gbMnParTbl, MN_PAR_EA);
		#endif		
		
		gbMnParReadChk = 0;
	}

  #if (model_Par==1)
	if (gbUsrParReadChk) {			// User Parameter

		#if model_Save
			SfRead2(gbUsrParTbl, USR_PAR_EA, FLASH_USER_MODE);
		#else
			TwiRdEep(TWI_EEP_USER_STT, gbUsrParTbl, USR_PAR_EA);
		#endif

		if (UP_END_REAL>UP_END)	TxStrNoIRQ("USER PAR size over ", 0, 0);			// Size verify
		if ((WORD)((gbUsrParTbl[UP_START]<<8)|gbUsrParTbl[UP_END])!=(WORD)UP_DATA_ID) {			// reset condition		
			gbUsrParSaveChk = 1;

			// CAUTION !!! - Only it must be run in the initialization
			if(!gbUsrParTbl[UP_FLAG])	UsrParReset();
			
			TxStrNoIRQ("USER PAR reset ", 0, 0);
	    }
		gbUsrParReadChk = 0;
		gbUsrParTbl[UP_FLAG] = 0;
	}

  #endif

	if (gbUsrDataReadChk) {			// User Data

		#if model_Save
			SfRead2(gbUsrDataTbl, USR_DATA_EA, FLASH_DATA_MODE);
		#else
			TwiRdEep(TWI_EEP_DATA_STT, gbUsrDataTbl, USR_DATA_EA);
		#endif

		if (UD_END_REAL>UD_END)	TxStrNoIRQ("USER DATA size over ", 0, 0);			// Size verify

		if ((WORD)((UD(UD_START)<<8)|UD(UD_END))!=(WORD)UD_DATA_ID) {				// reset condition
			gbUsrDataSaveChk = 1;

			// CAUTION !!! - Only it must be run in the initialization
			if(!UD(UD_FLAG))			UsrDataReset();
			
			TxStrNoIRQ("USER DATA reset ", 0, 0);
	    }
		gbUsrDataReadChk = 0;
		UD(UD_FLAG) = 0;
	}

  #if model_MenuDefSet == 1
	if (gbMnSetParReadChk) {			// Menu Set Parameter

		#if model_Save
			SfRead2(gbMnSetParTbl, MN_PAR_EA, FLASH_MENU_SET_MODE);
		#else
		    TwiRdEep(TWI_EEP_CSTM_STT, gbMnSetParTbl, MN_PAR_EA);
		#endif

		gbMnSetParReadChk = 0;
	}
  #endif
}
