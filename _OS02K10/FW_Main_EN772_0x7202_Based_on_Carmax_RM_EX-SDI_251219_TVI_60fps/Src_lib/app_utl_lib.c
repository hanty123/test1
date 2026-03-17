/* **************************************************************************
 File Name	:	app_utl_lib.c
 Description:	EN772 - utillity function
 Designer	:	Kim, Sunghoon
 Date		:	14. 10. 21
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "../Src/dev.h"

//-------------------------------------------------------------------------------------------------
int ISPM LibUtlInterp1D (int aiXCur, int aiXPos1, int aiXPos2, int aiYPos1, int aiYPos2)
{	// interpolation val
	
	int	iResult=0;

	if (aiXPos1==aiXPos2)			return 0;										// Divide by 0 " error "
	else if (aiYPos1==aiYPos2)		return aiYPos1;									// Position equal
	else if (aiYPos1<aiYPos2) {														// Increase wgt

		iResult = (((aiYPos2-aiYPos1) * (aiXCur-aiXPos1)) / (aiXPos2-aiXPos1)) + aiYPos1;

	}
	else if (aiYPos1>aiYPos2) {													// Decrease wgt

		iResult = (((aiYPos1-aiYPos2) * (aiXPos2 - aiXCur)) / (aiXPos2-aiXPos1)) + aiYPos2;
	}

	iResult = (iResult<0) ? 0 : iResult;

	return iResult;
}

int ISPM LibUtlInterp1D_MINUS (int aiXCur, int aiXPos1, int aiXPos2, int aiYPos1, int aiYPos2)
{	// interpolation val
	
	int	iResult=0;

	if (aiXPos1==aiXPos2)			return 0;										// Divide by 0 " error "
	else if (aiYPos1==aiYPos2)		return aiYPos1;									// Position equal
	else if (aiYPos1<aiYPos2) {														// Increase wgt

		iResult = (((aiYPos2-aiYPos1) * (aiXCur-aiXPos1)) / (aiXPos2-aiXPos1)) + aiYPos1;

	}
	else if (aiYPos1>aiYPos2) {													// Decrease wgt

		iResult = (((aiYPos1-aiYPos2) * (aiXPos2 - aiXCur)) / (aiXPos2-aiXPos1)) + aiYPos2;
	}

	return iResult;
}

//-------------------------------------------------------------------------------------------------
float ISPM LibUtlInterp1F (int aiXCur, int aiXPos1, int aiXPos2, float aiYPos1, float aiYPos2)
{	// interpolation val
	
	float	iResult=0;

	if (aiXPos1==aiXPos2)			return 0;										// Divide by 0 " error "
	else if (aiYPos1==aiYPos2)		return aiYPos1;									// Position equal
	else if (aiYPos1<aiYPos2) {														// Increase wgt

		iResult = (((aiYPos2-aiYPos1) * (aiXCur-aiXPos1)) / (aiXPos2-aiXPos1)) + aiYPos1;

	}
	else if (aiYPos1>aiYPos2) {													// Decrease wgt

		iResult = (((aiYPos1-aiYPos2) * (aiXPos2 - aiXCur)) / (aiXPos2-aiXPos1)) + aiYPos2;
	}

	iResult = (iResult<0) ? 0 : iResult;

	return iResult;
}


//-------------------------------------------------------------------------------------------------	
BYTE ISPM LibUtlKeyPass (const BYTE* abpPassKeys, BYTE abKeySize, BYTE* abpPassCnt)
{	// Key pass function
	if(KEY == KEY_VAL_S) return	0;
	
	if(*abpPassCnt < abKeySize) {
		if (KEY == abpPassKeys[*abpPassCnt]) 	(*abpPassCnt) ++;
		else if (KEY)	 						(*abpPassCnt) = 0;
	}
	else {
		*abpPassCnt = 0;
	}
	
	if(*abpPassCnt == abKeySize) {		// OK pass code
		return	1;
	}
	else return	0;
	
//		// original
//		switch (gbMnPassCnt2) {															// Debug MENU start
//			case 0 : if (KEY_U) gbMnPassCnt2 ++; else if (KEY) gbMnPassCnt2 = 0; break;
//			case 1 : if (KEY_D) gbMnPassCnt2 ++; else if (KEY) gbMnPassCnt2 = 0; break;
//			case 2 : if (KEY_L) gbMnPassCnt2 ++; else if (KEY) gbMnPassCnt2 = 0; break;
//			case 3 : if (KEY_R) gbMnPassCnt2 ++; else if (KEY) gbMnPassCnt2 = 0; break;
//			case 4 : if (KEY_C) {gbMnPassCnt2 ++;
//								MENU_OPEN(DEBUG);
//								}				 else if (KEY) gbMnPassCnt2 = 0; break;
//			default : 	gbMnPassCnt2 = 0; break;
//		}
}

//-------------------------------------------------------------------------------------------------		

