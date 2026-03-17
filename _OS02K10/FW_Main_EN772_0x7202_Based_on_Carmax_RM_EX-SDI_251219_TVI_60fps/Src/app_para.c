/* **************************************************************************
 File Name	: 	app_para.c
 Description	:	EN772 - User Parameter
 Designer		:	Lee, Gyu Hong
 Date		:	19. 12. 18
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

//*************************************************************************************************
// Variables
//-------------------------------------------------------------------------------------------------
// User Parameter --------------------------------------------------
BYTE gbUsrParSaveChk=0;
BYTE gbUsrParReadChk=0;

#if (model_Par==1)
BYTE gbUsrParTbl[USR_PAR_EA];
#endif

// User Data -------------------------------------------------------
BYTE gbUsrDataSaveChk=0;
BYTE gbUsrDataReadChk=0;
BYTE gbUsrDataTbl[USR_DATA_EA];


//*************************************************************************************************
// Functions
//-------------------------------------------------------------------------------------------------
#if (model_Par==1)

void UsrParSet(const int aiAddr, const int aiInit)
{
	UNUSED_ARG(aiInit);

	switch(aiAddr) {
		/*---------------��SYSTEM��---------------*/
		case UP_ADDR_E(UpLVDS_CKDLY) 	: 	LVDS_CKDLYw(UP(UpLVDS_CKDLY));			break;
		case UP_ADDR_E(UpLDIDLY0) 		: 	LDIDLY0w(UP(UpLDIDLY0));				break;	
		case UP_ADDR_E(UpLDIDLY1) 		: 	LDIDLY1w(UP(UpLDIDLY1));				break;	
		case UP_ADDR_E(UpLDIDLY2) 		: 	LDIDLY2w(UP(UpLDIDLY2));				break;	
		case UP_ADDR_E(UpLDIDLY3) 		: 	LDIDLY3w(UP(UpLDIDLY3));				break;
		
    #if(model_Led==0 || model_Led==2)   // 180910 JJH Adaptive Lighting UP					//210225 YTM
        case UP_ADDR_E(UpAE_LED_TuningOn)           : gbAE_LED_TuningOn     = UP(UpAE_LED_TuningOn);    break;
        case UP_ADDR_E(UpAE_LED_TEST_STEP)          : gwAE_LED_TEST_STEP    = UP(UpAE_LED_TEST_STEP);   break;
        case UP_ADDR_E(UpAE_LED_TEST_MIN)           : gnAE_LED_TEST_MIN     = UP(UpAE_LED_TEST_MIN);    break;
        case UP_ADDR_E(UpAE_LED_TEST_MAX)           : gnAE_LED_TEST_MAX     = UP(UpAE_LED_TEST_MAX);    break;

        case UP_ADDR_E(UpAE_LED_TEST_RUN)           : gbAE_LED_TEST_RUN     = UP(UpAE_LED_TEST_RUN);    break;
        case UP_ADDR_E(UpAE_LED_AePos_STOP)         : gbAE_LED_AePos_STOP   = UP(UpAE_LED_AePos_STOP);  break;
        case UP_ADDR_E(UpAE_LED_LED)                : gnAE_LED_LED          = UP(UpAE_LED_LED);         break;
        case UP_ADDR_E(UpAE_LED_AGC)                : gwAE_LED_AGC          = UP(UpAE_LED_AGC);         break;
        case UP_ADDR_E(UpAE_LED_HEP_Hz)             : gwAE_LED_HEP_Hz       = UP(UpAE_LED_HEP_Hz);      break;
    #endif

		default : break;
	}
}

void UsrParReset(void)
{	// User Parameter Reset
	gbUsrParTbl[0]				= 0;
	gbUsrParTbl[UP_START]		= (BYTE)((UP_DATA_ID>>8)&0xff);		// for verify
	gbUsrParTbl[UP_END]			= (BYTE)((UP_DATA_ID)&0xff);			// "
	
	#undef UP_SET
	#define UP_SET(S,N,...)		ParSet0(N##_,N)
	#include "app_para_tbl.h"
	USR_PAR_LIST

	USR_PAR_READ_CHK_ALL
}

void InitPar(void)
{
	int i;
	for(i=UP_START+1; i<UP_END_REAL; i++) UsrParSet(i, 1);
}

void ISPM2 UsrParSetChgVal(void)
{	
	// Register to Parameter Buffer 
#if(0)
	ParSet(UpLVDS_CKDLY, UpLVDS_CKDLY);
	ParSet(UpLDIDLY0, UpLDIDLY0);
	ParSet(UpLDIDLY1, UpLDIDLY1);
	ParSet(UpLDIDLY2, UpLDIDLY2);
	ParSet(UpLDIDLY3, UpLDIDLY3);

	ParSet(UpAE2_HSP, UpAE2_HSP);
	ParSet(UpAE2_HEP, UpAE2_HEP);
	ParSet(UpAE2_VSP, UpAE2_VSP);
	ParSet(UpAE2_VEP, UpAE2_VEP);

	ParSet(UpAWB_HSP, UpAWB_HSP);
	ParSet(UpAWB_HW , UpAWB_HW );
	ParSet(UpAWB_VSP, UpAWB_VSP);
	ParSet(UpAWB_VW , UpAWB_VW );
#endif

}

void UsrDataReset(void)
{	// User Data Reset
	gbUsrDataTbl[0]				= 0;
	gbUsrDataTbl[UD_START]		= (BYTE)((UD_DATA_ID>>8)&0xff);		// for verify
	gbUsrDataTbl[UD_END]		= (BYTE)((UD_DATA_ID)&0xff);			// "

	USR_DAT_READ_CHK_ALL
}

#endif

