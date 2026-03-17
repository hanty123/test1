/* **************************************************************************
 File Name	:	app_ae_lib.c
 Description	:	EN772 - Auto Exposure function
 Designer		:	Lee, Hoon
 Modifier		:	Lee, Gyu Hong
 Date		:	19. 12. 18
 Copyright �� DCOD Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "../Src/dev.h"

// ----------------------------------------------------------------------------------------------------
// LED Error Change
UINT gnAeLedWgtBit_Max;
UINT gnAeLedWgtBit_Min;
UINT gnAeLedTgt_Ofst;
UINT gnAeLedErrLmt_flag;
UINT gnAeLedDeblur_flag;
BYTE gbAeLedSatCtrl;

int ISPM LibAeLedErrChg (const int aiLedErrChgOn, int aiErr, const UINT anAe1Sum2, const UINT anAe1ClipCnt, const UINT anClipLvl, const UINT anAeWin1PxCnt)
{
	/*static int iErrSIIR = 0;
	static int aiLedErrChgOn1d = 0;
	if(aiLedErrChgOn1d == 0 && aiLedErrChgOn) IIRI(iErrSIIR, aiErr);
	aiLedErrChgOn1d = aiLedErrChgOn;*/

	if(aiLedErrChgOn == 0) return aiErr;

	UINT nSClipCntBuf = MIN(anAe1ClipCnt, (anAeWin1PxCnt>>gnAeLedWgtBit_Min));
		 nSClipCntBuf = MAX(nSClipCntBuf, (anAeWin1PxCnt>>gnAeLedWgtBit_Max));

	const int iSClipWgt = LibUtlInterp1D (nSClipCntBuf, (anAeWin1PxCnt>>gnAeLedWgtBit_Max), (anAeWin1PxCnt>>gnAeLedWgtBit_Min), 0, 0x100);

	UINT nSumMean1 = (anAe1ClipCnt==0) ? 0 : anAe1Sum2 / anAe1ClipCnt;
	nSumMean1 = ( (iSClipWgt * nSumMean1) + ((0x100-iSClipWgt) * anClipLvl) ) >> 8;

	const int iCur = (int)nSumMean1;
	const int iTgt = (int)anClipLvl + 1 + gnAeLedTgt_Ofst;

	const int iErrNight = iTgt - iCur;
	const int iErrDayOn = (iCur == (int)anClipLvl && aiErr > (int)(1 + gnAeLedTgt_Ofst));
	const int iErrTmp = ((iErrDayOn) ? aiErr : iErrNight)>>gnAeLedDeblur_flag;

	const int iErrS = gnAeLedErrLmt_flag ? iErrTmp : MAX(iErrTmp, -200);

//	return (MP(MpLedSatCtrl) * iErrS + (20-MP(MpLedSatCtrl)) * aiErr) / 20;		// 12.9.11	(shkim)
	return (gbAeLedSatCtrl * iErrS + (20-gbAeLedSatCtrl) * aiErr) / 20;		// 12.9.11	(shkim)
}

// ----------------------------------------------------------------------------------------------------
// Tracking Speed controller
extern void LibBrkCond(void);

int giAeErrLmt;

// 171211 LH : int ofst
#define AE_SPEED_BUNMO 		(20)	//40

int ISPM LibAeSpeed_Irs (int aiErr, int aiMargin, int aiGain )	
{	// Normal speed
	giAeErrLmt = 0x80;
	
	LibBrkCond();
		
	const int iErrMgn = (aiErr>0)? MIN(aiErr, (int)giAeErrLmt) : MAX(aiErr, -giAeErrLmt);
	const int fGain	= (ifmul8(1)) + (ifmul8(3*ABS(MINMAX(aiGain,0,255)-128))/128);			// float 8bit offset

	if (ABS(iErrMgn)>(aiMargin)) {
		if 		((aiGain-128)>=0)	return	( ifmul8(iErrMgn*fGain)/(AE_SPEED_BUNMO*256) );	// float 8bit offset : input * offset * gain / gain offset
		else if ((aiGain-128)<0)	return	( ifmul8(iErrMgn*256)/(AE_SPEED_BUNMO*fGain) );	// "				 : input * offset * gain offset / gain
		else 						return  0;
	}
	else							return	0;
}

extern int giIrsCent;

int ISPM LibAeSpeedDc (int aiErr, int aiMargin, int aiIrisOpenMax, int aiIrisCloseMax, int aiGain, int aiFncSel)
{	// DC IRIS Speed
	giAeErrLmt = 0x80;
	
	const int iErrOn   = ABS(aiErr)>aiMargin;
	const int iErrSign = (aiErr < 0) ? -1 : 1 ;//aiErr/ABS(aiErr);
	int iIrsVal;
	
	static UINT gnIrsInitCnt;
	#define	IrsInitCntMax	500
	gnIrsInitCnt++;
	gnIrsInitCnt = MIN(gnIrsInitCnt, IrsInitCntMax);
//			DispDatDec("IrsCnt__", 7, 24, gnIrsInitCnt);


	const int iIrsGain = (aiGain == 0) ? (aiErr<<1) : (aiErr / aiGain) ;

	#define IRIS_ERR_MIN	3/*10*/
	#define IRIS_ERR_MAX	20/*50*/


	if (iErrOn) {
		// Center control -------------
		if (gnIrsInitCnt<IrsInitCntMax)	giIrsCent -= (iErrSign*(50-(gnIrsInitCnt/10)));				// initialize center
		else							giIrsCent -= (iErrSign*3);									// normal center
										giIrsCent = MINMAX(giIrsCent, aiIrisOpenMax<<6, aiIrisCloseMax<<6);

		//giIrsCent = 0x260;	// Center of Stop = PS4100K:0x260, MN34227:0x254(0x242~0x248)

		// Speed control --------------
		if (aiFncSel==0) {
			//iIrsVal = (giIrsCent>>6) - (aiErr/ aiGain/*3*/) - (iErrSign*5);							// IRIS Control
//					iIrsVal = (giIrsCent>>6) - (aiErr/ 6/*3*/) - (iErrSign*5);							// IRIS Control

			iIrsVal = (giIrsCent>>6) - (iIrsGain) - (iErrSign*IRIS_ERR_MIN);							// IRIS Control


				//const int iErrLmt = MINMAX(aiErr*aiErr, 0, 2000);
				//if (aiErr>0)	iIrsVal = (giIrsCent>>6) - iErrSign*(iErrLmt/50) - 5;
				//else 		iIrsVal = (giIrsCent>>6) - iErrSign*(iErrLmt/50) + 5;
		}
		else {
			#define AE_IRS_SPD_BUMO 	200		// IRIS Speed (120(fast) ~ 200(slow))

//					int iErrSpeed = iErrSign*(((int)ABS(aiErr)*(int)ABS(aiErr)/(int)AE_IRS_SPD_BUMO)+1);                                                                      // 13.2.18
//					iErrSpeed = (aiErr>0)? MIN(iErrSpeed, (int)giAeErrLmt) : MAX(iErrSpeed, -(int)giAeErrLmt);
			int iErrSpeed = iErrSign*((4*(int)ABS(aiErr)*(int)ABS(aiErr)/(int)AE_IRS_SPD_BUMO)+1);                                                                      // 13.2.18
			iErrSpeed = (aiErr>0)? MIN(iErrSpeed, (int)giAeErrLmt>>1) : MAX(iErrSpeed, -(int)giAeErrLmt>>1);

			iIrsVal = (giIrsCent>>6) - (iErrSpeed) - (iErrSign*5);                                                                                                            // 13.2.18
//				DispDatDec("ErrSpeed", 7, 24, iErrSpeed);
		}
	}
	else {

			iIrsVal  = (giIrsCent>>6);
	}
	return iIrsVal;
}


// ----------------------------------------------------------------------------------------------------
// AE Speed control method PID		// 190527 PCB : New ae speed control function
#define SIGN(A)     ((A>=0)?1:2)

int ISPM LibAeSpeed (int aiErr, int aiMargin, int aiGain)	
{	// Normal speed
	giAeErrLmt = 0x400;
	
	LibBrkCond();
	
    const BYTE AE_SPEED_BUNMO_P   = 0x3;//0xa;  //12;      
    const BYTE AE_SPEED_BUNMO_M   = 0x6;//0x10;//13; 
	
    const WORD AE_SPEED_SIG_P     = 0xA;//0x5a;         // Maximum Current value * 0.3
    const WORD AE_SPEED_SIG_M     = 0x46;//0x80;//0x70;// Maximum Current value * 0.2
	
    const BYTE AE_SPEED_SUB_BUNMO = 2;

    const BYTE Dly_Cnt = 3;

    const float fKp_p = 0.6f;//0.5f; //0.4f  //0.7f;
    const float fKi_p = 0.3f;//0.12f;//0.03f //0.04f;
    const float fKd_p = 0.1f;//0.4f; //0.4f  //0.2f; 

    const float fKp_n = 0.4f;//0.32f; //0.4f  //0.7f;
    const float fKi_n = 0.1f;//0.05f;//0.03f //0.04f;
    const float fKd_n = 0.05f;//0.05f; //0.4f  //0.2f; 
    
    const float32 fhKp_p = TOFLOAT32(fKp_p);
    const float32 fhKi_p = TOFLOAT32(fKi_p);
    const float32 fhKd_p = TOFLOAT32(fKd_p);  
        
    const float32 fhKp_n = TOFLOAT32(fKp_n);
    const float32 fhKi_n = TOFLOAT32(fKi_n);
    const float32 fhKd_n = TOFLOAT32(fKd_n); 

    static int giErrMgn1d = 0, giErrMgn_I = 0;    
    static int giArr_I[5];
    int iErr_PID = 0, iErrMgn_D = 0, iErr_ISum = 0;
    BYTE i = 0;
	
	const int iErrMgn_P = (aiErr>0)? MIN(aiErr, (int)giAeErrLmt) : MAX(aiErr, -giAeErrLmt);
	const int iGain_P = ifmul8(AE_SPEED_BUNMO_P*128)/aiGain;    // Err +
    const int iGain_M = ifmul8(AE_SPEED_BUNMO_M*128)/aiGain;    // Err -

    if( (ABS(iErrMgn_P)>(aiMargin)) && (SIGN(aiErr)==SIGN(giErrMgn1d)) ){
    for(i=1; i<Dly_Cnt; i++) giArr_I[i-1] = giArr_I[i]; // 1906xx PCB
    }
    else{
        for(i=1; i<Dly_Cnt; i++) giArr_I[i-1] = 0; // 1906xx PCB
    }
    
	giArr_I[Dly_Cnt-1] = aiErr;
    for(i=0; i<Dly_Cnt; i++) iErr_ISum += giArr_I[i];

	iErrMgn_D = (ABS(iErrMgn_P)>(aiMargin)) ? ((SIGN(aiErr)==SIGN(giErrMgn1d)) ? aiErr - giErrMgn1d : aiErr) : 0;	
    giErrMgn_I = (ABS(iErrMgn_P)>(aiMargin)) ? /*(((SIGN(aiErr)==SIGN(giErrMgn1d))) ? iErr_ISum : aiErr)*/iErr_ISum : 0;

    giErrMgn1d = aiErr;

    const float32 fhErrEst = (iErrMgn_P > 0) ? _fadd(_fmul(fhKp_p,_itof(iErrMgn_P)), _fadd(_fmul(fhKi_p,_itof(giErrMgn_I)), _fmul(fhKd_p,_itof(iErrMgn_D))) ) :\
                                               _fadd(_fmul(fhKp_n,_itof(iErrMgn_P)), _fadd(_fmul(fhKi_n,_itof(giErrMgn_I)), _fmul(fhKd_n,_itof(iErrMgn_D))) ) ;
    
    iErr_PID = _ftoi(fhErrEst);

	int iErrMul_P = ifmul8(ifmul8((iErrMgn_P)) / (iGain_P*AE_SPEED_SUB_BUNMO));
	int iErrMul_M = ifmul8(ifmul8((iErrMgn_P)) / (iGain_M*AE_SPEED_SUB_BUNMO));

	if (ABS(iErrMgn_P)>(aiMargin)) {   
        if( iErr_PID > 0 ) {    // Error +
            if( iErr_PID > AE_SPEED_SIG_P )					return ifmul8(ifmul8(iErr_PID) / iGain_P);	// float 8bit offset : input * offset * gain / gain offset
//        	else if( iErr_PID > AE_SPEED_OFFSET_P )     	return ifmul8(iErr_PID*iErr_PID)          / ifdiv8(iGain_P*AE_SPEED_SIG_P*AE_SPEED_SUB_BUNMO);
//			else if( iErr_PID > AE_SPEED_OFT_P ) 			return ifmul8(ifmul8((iErrMgn_P)) / (iGain_P*AE_SPEED_SUB_BUNMO));
			else if( iErrMul_P > 256 )						return iErrMul_P;
			else                                            return (256);   // 220513 : OFFSET 
        }
        else{   				// Error -
            if( ABS(iErr_PID) > AE_SPEED_SIG_M )	    	return ifmul8(ifmul8(iErr_PID) / iGain_M);	// float 8bit offset : input * offset * gain / gain offset
//            else if( ABS(iErr_PID) > (AE_SPEED_OFFSET_M))   return ifmul8(ABS(iErr_PID)*iErr_PID)     / ifdiv8(iGain_M*AE_SPEED_SIG_M*AE_SPEED_SUB_BUNMO);
            else if( ABS(iErrMul_M) > 256 ) 				return iErrMul_M;
            else                							return (-256);  // 220513 : OFFSET 
		}
	}
	else{
		return	0;
	}
}

int ISPM LibAeSpeed_S1 (int aiErr, int aiMargin, int aiGain)	
{	// Normal speed
	giAeErrLmt = 0x400;
	
	LibBrkCond();
	
	UNUSED_ARG(aiGain);

    const BYTE AE_SPEED_BUNMO_P   = 11;  //12;      
    const BYTE AE_SPEED_BUNMO_M   = 13;
	
    const WORD AE_SPEED_SIG_P     = 300;
    const BYTE AE_SPEED_SIG_M     = 100;

    const BYTE AE_SPEED_OFFSET_P  = 60;
    const BYTE AE_SPEED_OFFSET_M  = 30;
	
    const BYTE AE_SPEED_SUB_BUNMO_P = 3;

    const BYTE Dly_Cnt = 3;

    const float fKp_p = 0.6f; //0.4f  //0.7f;
    const float fKi_p = 0.15f;//0.03f //0.04f;
    const float fKd_p = 0.4f; //0.4f  //0.2f; 

    const float fKp_n = 0.4f; //0.4f  //0.7f;
    const float fKi_n = 0.01f;//0.03f //0.04f;
    const float fKd_n = 0.1f; //0.4f  //0.2f; 
    
    const float32 fhKp_p = TOFLOAT32(fKp_p);
    const float32 fhKi_p = TOFLOAT32(fKi_p);
    const float32 fhKd_p = TOFLOAT32(fKd_p);  
        
    const float32 fhKp_n = TOFLOAT32(fKp_n);
    const float32 fhKi_n = TOFLOAT32(fKi_n);
    const float32 fhKd_n = TOFLOAT32(fKd_n); 

    static int giErrMgn1d = 0, giErrMgn_I = 0;    
    static int giArr_I[5];
    int iErr_PID = 0, iErrMgn_D = 0, iErr_ISum = 0;
    BYTE i = 0;
	
	const int iErrMgn_P = (aiErr>0)? MIN(aiErr, (int)giAeErrLmt) : MAX(aiErr, -giAeErrLmt);
	const int iGain_P = AE_SPEED_BUNMO_P*128/aiGain;    // Err +
    const int iGain_M = AE_SPEED_BUNMO_M*128/aiGain;    // Err -

    if( (ABS(iErrMgn_P)>(aiMargin)) && (SIGN(aiErr)==SIGN(giErrMgn1d)) ){
    for(i=1; i<Dly_Cnt; i++) giArr_I[i-1] = giArr_I[i]; // 1906xx PCB
    }
    else{
        for(i=1; i<Dly_Cnt; i++) giArr_I[i-1] = 0; // 1906xx PCB
    }
    
	giArr_I[Dly_Cnt-1] = aiErr;
    for(i=0; i<Dly_Cnt; i++) iErr_ISum += giArr_I[i];

	iErrMgn_D = (ABS(iErrMgn_P)>(aiMargin)) ? ((SIGN(aiErr)==SIGN(giErrMgn1d)) ? aiErr - giErrMgn1d : aiErr) : 0;	
    giErrMgn_I = (ABS(iErrMgn_P)>(aiMargin)) ? /*(((SIGN(aiErr)==SIGN(giErrMgn1d))) ? iErr_ISum : aiErr)*/iErr_ISum : 0;

    giErrMgn1d = aiErr;

    const float32 fhErrEst = (iErrMgn_P > 0) ? _fadd(_fmul(fhKp_p,_itof(iErrMgn_P)), _fadd(_fmul(fhKi_p,_itof(giErrMgn_I)), _fmul(fhKd_p,_itof(iErrMgn_D))) ) :\
                                               _fadd(_fmul(fhKp_n,_itof(iErrMgn_P)), _fadd(_fmul(fhKi_n,_itof(giErrMgn_I)), _fmul(fhKd_n,_itof(iErrMgn_D))) ) ;
    
    iErr_PID = _ftoi(fhErrEst);

	if (ABS(iErrMgn_P)>(aiMargin)) {        
        if( iErr_PID > 0 ) {    // Error +
            if( iErr_PID > AE_SPEED_SIG_P )					return ifmul8(iErr_PID)/( ((iErr_PID>0)?iGain_P:iGain_M));	// float 8bit offset : input * offset * gain / gain offset
        	else if( iErr_PID > AE_SPEED_OFFSET_P )     	return ifmul8(ABS(iErr_PID)*iErr_PID)/(((iErr_PID>0)?iGain_P:iGain_M)*(AE_SPEED_SIG_P*AE_SPEED_SUB_BUNMO_P));
			else                							return ifmul8((AE_SPEED_OFFSET_P*AE_SPEED_OFFSET_P)) / (((iErr_PID>0)?iGain_P:-iGain_M)*(AE_SPEED_SIG_P*AE_SPEED_SUB_BUNMO_P));
        }
        else{   				// Error -
            if( ABS(iErr_PID) > AE_SPEED_SIG_M )	    	return ifmul8(iErr_PID)/( ((iErr_PID>0)?iGain_P:iGain_M));	// float 8bit offset : input * offset * gain / gain offset
            else if( ABS(iErr_PID) > (AE_SPEED_OFFSET_M))   return ifmul8(ABS(iErr_PID)*iErr_PID)/(((iErr_PID>0)?iGain_P:iGain_M)*(AE_SPEED_SIG_M));
            else                							return ifmul8((AE_SPEED_OFFSET_M*AE_SPEED_OFFSET_M)) / (((iErr_PID>0)?iGain_P:-iGain_M)*(AE_SPEED_SIG_M));
		}
	}
	else{
		return	0;
	}
}

// ----------------------------------------------------------------------------------------------------
// PIRIS Interpolator

UINT ISPM LibAeIrsIntp (UINT anDTY, UINT anMin, UINT anMax)
{
	// normaliz BotTop range ----------------------------------------------
	//	anDTY = (anDTY<AF_IRS_BOT) ? 0 :  anDTY-AF_IRS_BOT;			// !
	//	anDTY = ((anDTY*anDTY*anDTY)/((AF_IRS_TOP-AF_IRS_BOT)*(AF_IRS_TOP-AF_IRS_BOT)))+AF_IRS_BOT;	// !

	// normaliz MinMax range ----------------------------------------------
		anDTY = (anDTY<anMin) ? 0 :  (UINT)(anDTY-anMin);
		anDTY = ((anDTY*anDTY*anDTY)/((anMax-anMin)*(anMax-anMin)))+anMin;

	return anDTY;
}


// ----------------------------------------------------------------------------------------------------
// AE Gain (x1 = WDR Gain : 0x100, Pre Gain : 0x100, Post Gain : 0x100)

//0.1dB Table
const UINT gnAeGainTbl[][2] = 	{
                                {0  , 256   },
                                {14 , 300   },
                                {28 , 353   },
                                {42 , 415   },
                                {56 , 487   },
                                {70 , 573   },
                                {84 , 673   },
                                {98 , 791   },
                                {112, 929   },
                                {126, 1092  },
                                {140, 1283  },
                                {154, 1507  },
                                {168, 1771  },
								{182, 2080  },
								{196, 2444  },
								{210, 2872  },
								{224, 3374  },
								{238, 3964  },
								{252, 4658  },
								{266, 5473  },
								{280, 6430  },
								{294, 7555  },
								{308, 8876  },
								{322, 10428 },	
								{336, 12252 },	
								{350, 14395 },	
								{364, 16913 },	
								{378, 19871 },	
								{392, 23347 },	
								{406, 27430 },	
								{420, 32228 },	
								{434, 37865 },	
								{448, 44487 },	
								{462, 52268 },	
								{476, 61410 },	
								{490, 72150 },	
								{504, 84769 },	
								{518, 99595 },	
								{532, 117014},	
								{546, 137480},	               
								{560, 161525},	               
								{574, 189775},	               
								{588, 222966},	               
								{602, 261963}	
                              	};

//0.125dB Table
const UINT gnAeGainTbl0125[][2] = 	{
	                            {0  , 256    },
								{14 , 313    },
								{28 , 383    },
								{42 , 468    },
								{56 , 573    },
								{70 , 701    },
								{84 , 857    },
								{98 , 1048   },
								{112, 1283   },
								{126, 1569   },
								{140, 1919   },
								{154, 2348   },
								{168, 2872   },
								{182, 3513   },
								{196, 4297   },
								{210, 5257   },
								{224, 6430   },
								{238, 7865   },
								{252, 9621   },
								{266, 11769  },
								{280, 14395  },
								{294, 17609  },
								{308, 21539  },
								{322, 26347  },
								{336, 32228  },
								{350, 39422  },
								{364, 48221  },
								{378, 58984  },
								{392, 72150  },
								{406, 88255  },
								{420, 107954 },
								{434, 132050 },
								{448, 161525 },
								{462, 197578 },
								{476, 241679 },
								{490, 295624 },
								{504, 361609 },
								{518, 442323 },
								{532, 541053 },
								{546, 661820 },
								{560, 809543 },
								{574, 990238 },
								{588, 1211267},
								{602, 1481630}
								};



#define AE_GAIN_TBL_EA		(sizeof(gnAeGainTbl)/8)
#define AE_GAIN_TBL_0125_EA	(sizeof(gnAeGainTbl0125)/8)


void ISPM LibAeGainIntp(int aiVal, UINT* apnGain)
{
	UINT 	i;
	UINT    nGain=0;

    if(aiVal == (int)gnAeGainTbl[AE_GAIN_TBL_EA-1][0]) nGain = gnAeGainTbl[AE_GAIN_TBL_EA-1][1];
    else{
    	for(i=1; i<AE_GAIN_TBL_EA; i++) {
    		if (aiVal<(int)gnAeGainTbl[i][0]) {
    			nGain = LibUtlInterp1D (aiVal, gnAeGainTbl[i-1][0], gnAeGainTbl[i][0], gnAeGainTbl[i-1][1], gnAeGainTbl[i][1]);
    			break;
    		}
    	}
    }
	*apnGain = (nGain - 0x100);
}

void ISPM LibAeGainIntp0125(int aiVal, UINT* apnGain)
{
	UINT 	i;
	UINT    nGain=0;

	UNUSED_ARG(*apnGain);
	
    if(aiVal == (int)gnAeGainTbl0125[AE_GAIN_TBL_0125_EA-1][0]) nGain = gnAeGainTbl0125[AE_GAIN_TBL_0125_EA-1][1];
    else{
    	for(i=1; i<AE_GAIN_TBL_0125_EA; i++) {
    		if (aiVal<(int)gnAeGainTbl0125[i][0]) {
    			nGain = LibUtlInterp1D (aiVal, gnAeGainTbl0125[i-1][0], gnAeGainTbl0125[i][0], gnAeGainTbl0125[i-1][1], gnAeGainTbl0125[i][1]);
    			break;
    		}
    	}
    }
	*apnGain = (nGain - 0x100);
}


// ----------------------------------------------------------------------------------------------------
// Pre Gain
UINT ISPM LibAePrgainIntp(int aiVal)
{
	static	UINT gnPgc;
	LibAeGainIntp(aiVal, &gnPgc);
	gnPgc = MINMAX((gnPgc+0x100), 0x100, 0xFFFF);

	return gnPgc;
}

UINT ISPM LibAePrgainIntp0125(int aiVal)
{
	static	UINT gnPgc;
	LibAeGainIntp0125(aiVal, &gnPgc);
	gnPgc = MINMAX((gnPgc+0x100), 0x100, 0xFFFF);

	return gnPgc;
}


void ISPM LibAePrgain_L (UINT anVal)
{
	PGAIN_GB_1w(anVal & 0xffff);
	PGAIN_GR_1w(anVal & 0xffff);
	PGAIN_R_1w(anVal & 0xffff);
	PGAIN_B_1w(anVal & 0xffff);
}

void ISPM LibAePrgain_S (UINT anVal)
{		
	PGAIN_GB_2w(anVal & 0xffff);
	PGAIN_GR_2w(anVal & 0xffff);
	PGAIN_R_2w(anVal & 0xffff);
	PGAIN_B_2w(anVal & 0xffff);
}


// ----------------------------------------------------------------------------------------------------
// Post Gain Hidden
void ISPM LibAePsGain (int aiVal, int aiTotal, float afDenorCf, int aiOver2, UINT anOsd)
{
	static	UINT gnPgc;
	int iValBuf;

	iValBuf = ((aiVal-aiTotal)<=0) ? 0 : (aiVal-aiTotal);
//	gnPgc = (UINT)((float)iValBuf*afDenorCf);
	gnPgc = (UINT)(ifdiv8(iValBuf*(int)(afDenorCf*256.f)));		// 171211 LH : int floating
	gnPgc = MINMAX(gnPgc, 0x100, (UINT)aiOver2);		// CIS limit
	
	PSGAIN_GBw(gnPgc & 0xffff);
	PSGAIN_GRw(gnPgc & 0xffff);
	PSGAIN_Rw(gnPgc & 0xffff);
	PSGAIN_Bw(gnPgc & 0xffff);

	DebugDisp(anOsd, Hex, "PGC_____", 7, 24, (0x100+gnPgc) & 0x3ff )
}


// ----------------------------------------------------------------------------------------------------
// // Fast 30p checker

#define AE_WDR_OFF		MN_OFF					// "

extern BYTE gbModeWdrOn_L;							// WDR on/off status

// ----------------------------------------------------------------------------------------------------
// WDR Tone Map
const UINT gnTblToneMapBase[][6] =  {//X    , 	Y 0.01,		Y 0.015 	Y 0.02   	Y 0.04 		Y 0.06 
									{0       , 	0x0  ,		0x0  ,		0x0  	,	0x0  ,		0x0  },     // 00
									{4       , 	0x0  ,		0x1  ,		0x1  	,	0x3  ,		0x4  },     // 01
									{8       , 	0x1  ,		0x2  ,		0x3  	,	0x6  ,		0x9  },     // 02
									{16      , 	0x3  ,		0x5  ,		0x6  	,	0xC  ,		0x11 },     // 03
									{32      , 	0x7  ,		0xA  ,		0xD  	,	0x17 ,		0x20 },     // 04
									{64      , 	0xE  ,		0x13 ,		0x19 	,	0x2A ,		0x37 },     // 05
									{128     , 	0x1A ,		0x24 ,		0x2C 	,	0x46 ,		0x58 },     // 06
									{256     , 	0x2F ,		0x3E ,		0x4A 	,	0x6B ,		0x81 },     // 07
									{512     , 	0x4F ,		0x63 ,		0x72 	,	0x9A ,		0xB1 },     // 08
									{1024    , 	0x7A ,		0x91 ,		0xA3 	,	0xCD ,		0xE5 },     // 09
									{2048    , 	0xAE ,		0xC8 ,		0xDA 	,	0x104,		0x11C},     // 10
									{3072    , 	0xCF ,		0xE9 ,		0xFC 	,	0x125,		0x13C},     // 11
									{4096    , 	0xE8 ,		0x102,		0x114	,	0x13D,		0x154},     // 12
									{6144    , 	0x10C,		0x126,		0x137	,	0x15F,		0x175},     // 13
									{8192    , 	0x126,		0x140,		0x151	,	0x177,		0x18C},     // 14
									{12288   , 	0x14C,		0x164,		0x175	,	0x199,		0x1AD},     // 15
									{16384   , 	0x167,		0x17E,		0x18E	,	0x1B2,		0x1C5},     // 16
									{24576   , 	0x18D,		0x1A3,		0x1B2	,	0x1D4,		0x1E6},     // 17
									{32768   , 	0x1A8,		0x1BE,		0x1CC	,	0x1EC,		0x1FD},     // 18
									{49152   , 	0x1CF,		0x1E3,		0x1F1	,	0x20F,		0x21F},     // 19
									{65536   , 	0x1EA,		0x1FD,		0x20A	,	0x227,		0x236},     // 20
									{98304   , 	0x211,		0x223,		0x22F	,	0x24A,		0x258},     // 21
									{131072  , 	0x22C,		0x23D,		0x249	,	0x262,		0x26F},     // 22
									{163840  , 	0x242,		0x252,		0x25D	,	0x275,		0x282},     // 23
									{196608  , 	0x253,		0x263,		0x26D	,	0x284,		0x291},     // 24
									{229376  , 	0x262,		0x271,		0x27B	,	0x292,		0x29D},     // 25
									{262144  , 	0x26F,		0x27E,		0x287	,	0x29D,		0x2A8},     // 26
									{294912  , 	0x27A,		0x288,		0x292	,	0x2A7,		0x2B2},     // 27
									{327680  , 	0x284,		0x292,		0x29B	,	0x2B0,		0x2BB},     // 28
									{360448  , 	0x28E,		0x29B,		0x2A4	,	0x2B8,		0x2C3},     // 29
									{393216  , 	0x296,		0x2A3,		0x2AC	,	0x2BF,		0x2CA},     // 30
									{458752  , 	0x2A5,		0x2B1,		0x2BA	,	0x2CC,		0x2D6},     // 31
									{524288  , 	0x2B1,		0x2BE,		0x2C6	,	0x2D8,		0x2E1},     // 32
									{589824  , 	0x2BD,		0x2C9,		0x2D0	,	0x2E2,		0x2EB},     // 33
									{655360  , 	0x2C7,		0x2D2,		0x2DA	,	0x2EB,		0x2F4},     // 34
									{720896  , 	0x2D0,		0x2DB,		0x2E3	,	0x2F3,		0x2FC},     // 35
									{786432  , 	0x2D8,		0x2E3,		0x2EA	,	0x2FA,		0x303},     // 36
									{851968  , 	0x2E0,		0x2EB,		0x2F2	,	0x301,		0x309},     // 37
									{917504  , 	0x2E7,		0x2F1,		0x2F8	,	0x307,		0x30F},     // 38
									{983040  , 	0x2EE,		0x2F8,		0x2FF	,	0x30D,		0x315},     // 39
									{1048576 , 	0x2F4,		0x2FE,		0x304	,	0x313,		0x31A},     // 40
									{1572864 , 	0x31B,		0x323,		0x329	,	0x335,		0x33C},     // 41
									{2097152 , 	0x337,		0x33E,		0x343	,	0x34E,		0x353},     // 42
									{2621440 , 	0x34C,		0x353,		0x357	,	0x361,		0x366},     // 43
									{3145728 , 	0x35E,		0x364,		0x367	,	0x370,		0x375},     // 44
									{3670016 , 	0x36C,		0x372,		0x375	,	0x37D,		0x381},     // 45
									{4194304 , 	0x379,		0x37E,		0x381	,	0x389,		0x38C},     // 46
									{4718592 , 	0x385,		0x389,		0x38C	,	0x393,		0x396},     // 47
									{5242880 , 	0x38F,		0x393,		0x396	,	0x39C,		0x39F},     // 48
									{5767168 , 	0x398,		0x39C,		0x39E	,	0x3A4,		0x3A7},     // 49
									{6291456 , 	0x3A0,		0x3A4,		0x3A6	,	0x3AB,		0x3AE},     // 50
									{7340032 , 	0x3AF,		0x3B2,		0x3B4	,	0x3B8,		0x3BA},     // 51
									{8388608 , 	0x3BC,		0x3BE,		0x3C0	,	0x3C4,		0x3C5},     // 52
									{9437184 , 	0x3C7,		0x3C9,		0x3CB	,	0x3CE,		0x3CF},     // 53
									{10485760, 	0x3D1,		0x3D3,		0x3D4	,	0x3D7,		0x3D8},     // 54
									{11534336, 	0x3DA,		0x3DC,		0x3DD	,	0x3DF,		0x3E0},     // 55
									{12582912, 	0x3E3,		0x3E4,		0x3E5	,	0x3E6,		0x3E7},     // 56
									{13631488, 	0x3EB,		0x3EB,		0x3EC	,	0x3ED,		0x3ED},     // 57
									{14680064, 	0x3F2,		0x3F2,		0x3F2	,	0x3F3,		0x3F4},     // 58
									{15728640, 	0x3F8,		0x3F9,		0x3F9	,	0x3F9,		0x3F9},     // 59
									{16777216, 	0x3FF,		0x3FF,		0x3FF	,	0x3FF,		0x3FF}      // 60
									};							

const UINT gnTblToneMapCurX[41]= 	{ // X	 
									0       ,   // 00
									64      ,   // 01
									128     ,   // 02
									256     ,   // 03
									512     ,   // 04
									1024    ,   // 05
									2048    ,   // 06
									4096    ,   // 07
									8192    ,   // 08
									16384   ,   // 09
									32768   ,   // 10
									49152   ,   // 11
									65536   ,   // 12
									98304   ,   // 13
									131072  ,   // 14
									196608  ,   // 15
									262144  ,   // 16
									393216  ,   // 17
									524288  ,   // 18
									786432  ,   // 19
									1048576 ,   // 20
									1572864 ,   // 21
									2097152 ,   // 22
									2621440 ,   // 23
									3145728 ,   // 24
									3670016 ,   // 25
									4194304 ,   // 26
									4718592 ,   // 27
									5242880 ,   // 28
									5767168 ,   // 29
									6291456 ,   // 30
									7340032 ,   // 31
									8388608 ,   // 32
									9437184 ,   // 33
									10485760,   // 34
									11534336,   // 35
									12582912,   // 36
									13631488,   // 37
									14680064,   // 38
									15728640,   // 39
									16777215    // 40
									};										
                                                        

// Normal Mode ToneMap Test                                                      
const UINT gbTblToneMapNor[][2] = 	{
									//1:1 Bypass	//Night Target
									// 0.00003
									//Tonemap		//Tonemap
									{0x0  ,		0x0  },		// 00
									{0x0  , 	0x0  },	    // 01
									{0x0  , 	0x0  },	    // 02
									{0x0  , 	0x0  },	    // 03
									{0x0  , 	0x0  },	    // 04
									{0x0  , 	0x0  },	    // 05
									{0x0  , 	0x0  },	    // 06
									{0x0  , 	0x0  },	    // 07
									{0x1  , 	0x1  },	    // 08
									{0x3  , 	0x2  },	    // 09
									{0x7  , 	0x5  },	    // 10
									{0xB  , 	0x7  },	    // 11
									{0xE  , 	0xA  },	    // 12
									{0x15 , 	0xF  },	    // 13
									{0x1C , 	0x14 },	    // 14
									{0x2A , 	0x1D },	    // 15
									{0x38 , 	0x27 },	    // 16
									{0x51 , 	0x3A },	    // 17
									{0x6A , 	0x4C },	    // 18
									{0x97 , 	0x6F },	    // 19
									{0xC0 , 	0x90 },	    // 20
									{0x109, 	0xCD },	    // 21
									{0x147, 	0x105},	    // 22
									{0x17E, 	0x138},	    // 23
									{0x1AF, 	0x168},	    // 24
									{0x1DC, 	0x194},	    // 25
									{0x204, 	0x1BD},	    // 26
									{0x229, 	0x1E3},	    // 27
									{0x24B, 	0x208},	    // 28
									{0x26B, 	0x22A},	    // 29
									{0x289, 	0x24A},	    // 30
									{0x2C0, 	0x287},	    // 31
									{0x2F0, 	0x2BD},	    // 32
									{0x31C, 	0x2F0},	    // 33
									{0x344, 	0x31F},	    // 34
									{0x369, 	0x34A},	    // 35
									{0x38B, 	0x372},	    // 36
									{0x3AB, 	0x399},	    // 37
									{0x3C8, 	0x3BC},	    // 38
									{0x3E4, 	0x3DE},	    // 39
									{0x3FF, 	0x3FF},	    // 40
									};



extern  BYTE gbModel_Sens;

extern	int giAeLWdrGain;
extern 	WORD gwAeWdrSatLv;		// SAT LV
extern	BYTE gbAeWdrComp;
extern  BYTE gbAeWdrTm;
extern 	UINT gnAeLWdrMaxS1, gnAeLWdrMinS1;
extern 	BYTE gbAeDebugOn;


#define	SENS_PWL_OS02K10	33	
#define LFM_SENS_OX03C10	35
#define LFM_SENS_AR0233		37

WORD	gwPWL_X[11];		// 12bit
UINT	gnPWL_Y[12];		// 24bit


#if(1)
UINT GetToneMap(const UINT anG1, const UINT anG2, UINT anWeight)
{
	return LibUtlInterp1D(MINMAX(anWeight, 0x0, 0x100), 0x0, 0x100, anG1, anG2);
}
#endif

// Long Saturation Level Calculation
WORD LibAeWdr_SATLV(void)
{
	WORD wWDR_SATVL = 0;

	if(gbModel_Sens==SENS_PWL_OS02K10){
		wWDR_SATVL = 0xFFFF + gwAeWdrSatLv;			// because Short Noise 
	}
	else{
		wWDR_SATVL = 0xFFF + gwAeWdrSatLv;			// because Short Noise 
	}

	return wWDR_SATVL;
}

int LibAeWdr_SGAIN(int aiSgain)
{
	int iWDR_SGAIN = 0;
	iWDR_SGAIN = aiSgain;						// because Short Noise
	iWDR_SGAIN = MINMAX(iWDR_SGAIN, 0x40, 0x3FFFFF);
	
	return iWDR_SGAIN;
}

void ISPM LibDeComp(void)
{// On Chip HDR Sensor PWL Curve -> Decompression
	UINT i = 0;
	
	if(gbModel_Sens==SENS_PWL_OS02K10){
		//PWL (Omnivision - OS02K10)
		gwPWL_X[0]  = (0x3FF ); gnPWL_Y[0]  = (0x3FF );    
		gwPWL_X[1]  = (0x4FF ); gnPWL_Y[1]  = (0x7FF );    
		gwPWL_X[2]  = (0x7FF ); gnPWL_Y[2]  = (0x1FFF);    
		gwPWL_X[3]  = (0xDFF ); gnPWL_Y[3]  = (0x7FFF);    
		gwPWL_X[4]  = (0xFFF ); gnPWL_Y[4]  = (0xFFFF);    
		gwPWL_X[5]  = (0xFFF ); gnPWL_Y[5]  = (0xFFFF);    
		gwPWL_X[6]  = (0xFFF ); gnPWL_Y[6]  = (0xFFFF);    
		gwPWL_X[7]  = (0xFFF ); gnPWL_Y[7]  = (0xFFFF);    
		gwPWL_X[8]  = (0xFFF ); gnPWL_Y[8]  = (0xFFFF);    
		gwPWL_X[9]  = (0xFFF ); gnPWL_Y[9]  = (0xFFFF);    
		gwPWL_X[10] = (0xFFF ); gnPWL_Y[10] = (0xFFFF);
								gnPWL_Y[11] = (0xFFFF);
	}

	else if(gbModel_Sens==LFM_SENS_OX03C10){
		//PWL (Omnivision - OX03C10)
		gwPWL_X[0]  = (0x100 ); gnPWL_Y[0]  = (0x100   );    
		gwPWL_X[1]  = (0x500 ); gnPWL_Y[1]  = (0x700   );    
		gwPWL_X[2]  = (0x900 ); gnPWL_Y[2]  = (0x1F00  );    
		gwPWL_X[3]  = (0x1300); gnPWL_Y[3]  = (0x7F00  );    
		gwPWL_X[4]  = (0x2300); gnPWL_Y[4]  = (0x13F00 );    
		gwPWL_X[5]  = (0x3300); gnPWL_Y[5]  = (0x27F00 );    
		gwPWL_X[6]  = (0x3F00); gnPWL_Y[6]  = (0x3FF00 );    
		gwPWL_X[7]  = (0x4F00); gnPWL_Y[7]  = (0x7FF00 );    
		gwPWL_X[8]  = (0x7F00); gnPWL_Y[8]  = (0x1FFF00);    
		gwPWL_X[9]  = (0x9F00); gnPWL_Y[9]  = (0x3FFF00);    
		gwPWL_X[10] = (0xFF00); gnPWL_Y[10] = (0xFFFF00);
								gnPWL_Y[11] = (0xFFFFFF);
	}
	else if(gbModel_Sens==LFM_SENS_AR0233){	
		gwPWL_X[0]  = (0x200);	gnPWL_Y[0]  = (0x200  );
		gwPWL_X[1]  = (0x345);	gnPWL_Y[1]  = (0x400  );	
		gwPWL_X[2]  = (0x48A);	gnPWL_Y[2]  = (0x800  );	
		gwPWL_X[3]  = (0x5CF);	gnPWL_Y[3]  = (0x1000 );	
		gwPWL_X[4]  = (0x714);	gnPWL_Y[4]  = (0x2000 );	
		gwPWL_X[5]  = (0x859);	gnPWL_Y[5]  = (0x4000 );
		gwPWL_X[6]  = (0x99E);	gnPWL_Y[6]  = (0x8000 );	
		gwPWL_X[7]  = (0xAE3);	gnPWL_Y[7]  = (0x10000);	
		gwPWL_X[8]  = (0xC28);	gnPWL_Y[8]  = (0x20000);
		gwPWL_X[9]  = (0xD6D);	gnPWL_Y[9]  = (0x40000);
		gwPWL_X[10] = (0xEB2);	gnPWL_Y[10] = (0x80000);
								gnPWL_Y[11] = (0xFFFFF);
	}
	
	// PWL_X
	for(i = 0; i < 5; i++){
		SetIsp((0x11C+i), ((gwPWL_X[i*2]<<16)|(gwPWL_X[i*2+1]<<0)));
	}
	SetIsp((0x11C+i), gwPWL_X[i*2]);
	
	// PWL_Y   
	PWL_Y0w(gnPWL_Y[0]);
	for(i = 1; i <= 11; i++)	SetIsp(0x110+i, gnPWL_Y[i]);
	
}

void ISPM LibAeWdr (int aiNonCmpWDR, int aiCmpWDR, UINT anLef, UINT anSef1, UINT anLgain, UINT anSgain, UINT anWeight)
{	// WDR Processor
	// aiNonCmpWDR  - 0 : WDR Off, 1 : Non-Compressed WDR
	// aiCmpWDR  	- 0 : WDR Off, 1 : Compressed WDR
	// anLef   		- Long Shutter Speed
	// anSef1  		- Short Shutter Speed
	// anLgain		- Long Gain
	// anSgain		- Short Gain
	// anWeight 	- WDR weight (0x100 => default X1)

	int iWdrGainS1 = 0x1000;
	int iWdrGain   = 0x7fff;
	int i = 0;
	UINT nTblToneMapCurY[41];
	static UINT SMAX = 0xfff;
	static UINT nSMAXIIR = 0x0;
	const WORD wSMAXIIRCF = 0x100;
	
	// *******************************************************
	// WDR OFF
	// *******************************************************
	if ((aiNonCmpWDR==0)&&(aiCmpWDR==0)){	

		WDR_ONw(0);
		TMG_ONw(0);
		
		WDR_GAINw(0x100+giAeLWdrGain);

		PWL_ONw(0x0);
		PWL_OBITw(0x1);
		PWL_OBITw(0x1);			// 0x0 : 10bit
								// 0x1 : 12bit	
								
	#if(0)
	// Normal Mode ToneMap Test
		TMG_ONw(1);
		TMG_YHLPFw(1);
		TMG_YHLPF_GAw(6);
		
		UINT nTmgVal = 0, nTmgValBuf = 0;
		
		for (i=0; i<41; i++){
			nTmgValBuf = GetToneMap(gbTblToneMapNor[i][0], gbTblToneMapNor[i][1], 0x0);
			nTmgVal |= (nTmgValBuf << ((!(i%2))*16));
			
			if(i%2){
				SetIsp(TMG_BASE+(i/2), nTmgVal);
				nTmgVal = 0;
			}
		}
		SetIsp(TMG_BASE+(i/2), nTmgVal);
	#endif							
	}

	// *******************************************************
	// WDR ON
	// *******************************************************
	else {
		// Compressed Combined WDR
		if(aiCmpWDR){
			WDR_ONw(0);
			PWL_ONw(1);
			
			if(gbModel_Sens==SENS_PWL_OS02K10){
				PWL_OBITw(0x3);			// Decompression Output 16bit
				PWL_IBITw(0x1);			// Compressed Data 12bit
			}

			else if(gbModel_Sens==LFM_SENS_AR0233){
				PWL_OBITw(0x5);			// Decompression Output 20bit
				PWL_IBITw(0x1);			// Compressed Data 12bit
			}
			else if(gbModel_Sens==LFM_SENS_OX03C10){
				PWL_OBITw(0x7);			// Decompression Output 24bit
				PWL_IBITw(0x3);			// Compressed Data 16bit
			}

			LibDeComp();
			
//			SMAX = MIN((anWeight*0xFFF), 0xFFFF); 					// Short max = 4095 * S gain	TEMP
			SMAX = /*0xC7F3*/0x3FFF; 								// Short max = 4095 * 12.5 (Original, but Noise, Set 14bit)
	
			if(gbModel_Sens==SENS_PWL_OS02K10)		iWdrGain   = (((u64)0x3FFF  *0x100)/(SMAX));			// Decompression Output 16bit
			else if(gbModel_Sens==LFM_SENS_AR0233)	iWdrGain   = (((u64)0xFFFFF *0x100)/(SMAX));			// Decompression Output 20bit
			else									iWdrGain   = (((u64)0xFFFFFF*0x100)/(SMAX));			// Decompression Output 24bit
			
			WDR_GAINw(MAX(iWdrGain+giAeLWdrGain, 0x100));						// WDR_GAIN : x1 Default
		}
		
		// Not Compressed, Not Combined WDR
		else {
			WDR_ONw(1);
			
			if(gbModel_Sens==SENS_PWL_OS02K10){
				PWL_ONw(1);
				PWL_OBITw(0x3);			// Decompression Output 16bit
				PWL_IBITw(0x1);			// Compressed Data 12bit

				LibDeComp();
			}
			else{
				PWL_ONw(0);
				PWL_OBITw(0x1);
				PWL_IBITw(0x1);
			}

			// Calculate SMAX
			int iSgain = 0x40, iSmax_K = 0xFFF;		// Gain Ratio
			
			float32 f_Sgain, f_Smax;				// Gain, SMAX
			float32 f_Agc = 0x1, f_WdrGainS1 = 0x1; 
			float32 f_anLef = 0, f_anSef1 = 0;		// Shutter
			float32 f_anLgain = 0, f_anSgain = 0;	// AGC Gain

			float32 f_SGainOffset = 1.0f;
			
			iSmax_K = ((gbModel_Sens==SENS_PWL_OS02K10)?(0xFFFF):(0xFFF));

			// int to float32
			f_anLef 	= _itof((int)anLef); 	// float32 Long shutter
			f_anSef1 	= _itof((int)anSef1); 	// float32 Short shutter
			f_anLgain	= _itof((int)anLgain);	// float32 Long AGC
			f_anSgain	= _itof((int)anSgain);	// float32 Short AGC
			f_Sgain 	= _itof(iSgain);		// float32 Sgain
			f_Smax 		= _itof(iSmax_K); 		// float32 Smax

			float fSGainOffset_Min = 1.0f;
			float fSGainOffset_Max = 1.0f;

			fSGainOffset_Min = ((gbModel_Sens==SENS_PWL_OS02K10)?(/*12.5f*//*15.0f*/9.9f):(1.0f));
			fSGainOffset_Max = ((gbModel_Sens==SENS_PWL_OS02K10)?(/*12.5f*//*15.0f*/9.9f):(1.0f));

			// (Sef1_Min -> Offset_Max) ~ (Sef1_MAX -> Offset_Min)
			f_SGainOffset = LibUtlInterp1F(MINMAX((int)anSef1, (int)gnAeLWdrMinS1, (int)gnAeLWdrMaxS1), (int)gnAeLWdrMinS1, (int)gnAeLWdrMaxS1,\
																								   		 TOFLOAT32(fSGainOffset_Min), TOFLOAT32(fSGainOffset_Max)); // gnAeLWdrMinS1 ~ gnAeLWdrMaxS1

			// WDR S1 Gain
			f_Agc = _fdiv(f_anLgain,f_anSgain);							// Long / Short Gain Ratio
//			f_WdrGainS1 = _fmul(_fdiv(_fmul(f_anLef,f_Sgain),f_anSef1), f_Agc); 	// f_WdrGainS1 = (Long*0x40 / Short Shutter) * (Long / Short Gain)
//			iWdrGainS1 = _ftoi(_fmul(f_WdrGainS1,f_SGainOffset));
			f_WdrGainS1 = _fmul(_fmul(_fmul(_fdiv(f_anLef,f_anSef1),f_Sgain),f_Agc), f_SGainOffset); 	// f_WdrGainS1 = (Long*0x40 / Short Shutter) * (Long / Short Gain)	// 240214 LGH
			iWdrGainS1 = _ftoi(f_WdrGainS1);

			// SMAX
			nSMAXIIR = SMAX;			
//			f_Smax = _fmul(_fdiv(_fmul(f_anLef,f_Smax),f_anSef1),f_Agc); // Short max = 4095 * S gain
			f_Smax = _fmul(f_WdrGainS1, f_Smax); 						// Short max = 4095 * S gain			// 240214 LGH

			SMAX = _ftoi(_fmul(f_Smax,f_SGainOffset));

			SMAX = MIN(SMAX,(0xFFFFFFFF/anWeight));
			SMAX = (SMAX * anWeight)>>8 ;										// 170213 LH : Brightness weight between Dark and Bright area
			SMAX = ((wSMAXIIRCF*SMAX)+((0x100-wSMAXIIRCF)*nSMAXIIR))/0x100;		// 210316 LGH : SMAX IIR

			iWdrGain   = (((u64)0xFFFFFF*0x100)/(SMAX));						// WDR last gain : 0x100 = x1
			

			WDR_SGAINw(LibAeWdr_SGAIN(iWdrGainS1)); 							// WDR_GAIN  : 0x100 = x1
			WDR_GAINw(MAX(iWdrGain+giAeLWdrGain, 0x100));

			WDR_SATVLw(LibAeWdr_SATLV());
			WDR_SATVWw(0x5);

			WDR_DOLCMPw(gbAeWdrComp);

			if(gbAeWdrComp)		WDR_BUFPWLw(0x1);
			else				WDR_BUFPWLw(0x0);						
		}


		// -------------------------------------
		// Tone Map Processing
		// -------------------------------------
		TMG_ONw(1);			// TMG OFF at ROI

		//Tone Map Y Horizontal HPF
		// ON
		TMG_YHLPFw(1);
		TMG_YHLPF_GAw(4);
		TMG_YHLPF_CLw(0xFFFFFF);
		
		//TMG_YHLPF_SCw(0x3FF);			
		BYTE bYHLPF_SC = 0x0;
//          bYHLPF_SC = LibUtlInterp1D (MINMAX(giCurAgc, 0x0, 0x30), 0x0, 0x30, 0x30, 0x0);
        TMG_YHLPF_SCw(bYHLPF_SC);

	// serch MAXY of Base table ---------------------------------------------	
	//		TMG_TBL00w(0x0  );
	//		i=60
	//		while (MAS_TBLX[i]>=SMAX) do	
	//			MAXX = MAS_TBLX[i]
	//			MAXY = MAS_TBLY[i]
	//			i=i-1
	//		end
	//		MAXY_P = MAS_TBLY[i]
	//		MAXX_P = MAS_TBLX[i]
	//			
	//		MAXY = (MAXY*(SMAX-MAXX_P)+MAXY_P*(MAXX-SMAX))/(1023*(MAXX-MAXX_P))
			
	//		DebugDisp(1, Hex, "SMAX   ", 0, 24, SMAX  	)
			UINT MAXX, MAXY, MAXX_P, MAXY_P;
			BYTE TmgIndex = 0;
			TmgIndex = gbAeWdrTm+1;
			TmgIndex = MINMAX(TmgIndex, 0, 5);
			
			MAXX = gnTblToneMapBase[60][0];
			MAXY = gnTblToneMapBase[60][TmgIndex];
			MAXX_P = gnTblToneMapBase[60-1][0];
			MAXY_P = gnTblToneMapBase[60-1][TmgIndex];
			
			for (i=1; i<=60; i++) {
				if (gnTblToneMapBase[i][0]>=SMAX){
					MAXX = gnTblToneMapBase[i][0];
					MAXY = gnTblToneMapBase[i][TmgIndex];
					MAXX_P = gnTblToneMapBase[i-1][0];
					MAXY_P = gnTblToneMapBase[i-1][TmgIndex];
					break;
				}
			}
	//		DebugDisp(1, Hex, "MAXX   ", 1, 24, MAXX  	)
	//		DebugDisp(1, Hex, "MAXY   ", 2, 24, MAXY  	)
	//		DebugDisp(1, Hex, "MAXX_P ", 3, 24, MAXX_P  	)
	//		DebugDisp(1, Hex, "MAXY_P ", 4, 24, MAXY_P  	)
			
	//		MAXY = (MAXY*(SMAX-MAXX_P)+MAXY_P*(MAXX-SMAX))/(1023*(MAXX-MAXX_P));
			MAXY = (MAXY*(SMAX-MAXX_P)+MAXY_P*(MAXX-SMAX))/(MAXX-MAXX_P);
			
	//		DebugDisp(1, Hex, "MAXY ", 5, 24, MAXY  	)
	
	// Normalization Base -> Cur table -------------------------------------
	// MADDR = 0;
	// for i=1, 40, 1 do
	// NTBLX = NOW_TBLX[i]*(SMAX/0x400000);
	// while MAS_TBLX[MADDR] <= NTBLX	do
	// MADDR=MADDR+1
	// end
	//			
	// WGT = ((NTBLX-MAS_TBLX[MADDR-1])/(MAS_TBLX[MADDR]-MAS_TBLX[MADDR-1]))
	// NOW_TBLY[i] = ((WGT*MAS_TBLY[MADDR])+((1-WGT)*MAS_TBLY[MADDR-1]))/MAXY;
	//	
	// end
			
		UINT MADDR = 0;
		u64 NTBLX;
		int  WGT;
		nTblToneMapCurY[0] = 0;
		
		for (i=1; i<=40; i++) {
			NTBLX = (gnTblToneMapCurX[i]*(u64)SMAX)/(u64)0xffffff;
			
			while (gnTblToneMapBase[MADDR][0]<=(UINT)NTBLX) {MADDR++;}
			
			WGT = (((UINT)NTBLX-gnTblToneMapBase[MADDR-1][0])*256)/(gnTblToneMapBase[MADDR][0]-gnTblToneMapBase[MADDR-1][0]);
//				nTblToneMapCurY[i] = (((WGT*gnTblToneMapBase[MADDR][1])+((256-WGT)*gnTblToneMapBase[MADDR-1][1]))*1023)/(MAXY*256);
			nTblToneMapCurY[i] = MIN((((WGT*gnTblToneMapBase[MADDR][TmgIndex])+((256-WGT)*gnTblToneMapBase[MADDR-1][TmgIndex]))*1023)/(MAXY*256), 0x3FF);
		}
		for (i=0; i<20; i++) 	{SetIsp(TMG_BASE+i, (nTblToneMapCurY[i*2]<<16)|(nTblToneMapCurY[(i*2)+1]));}
								{SetIsp(TMG_BASE+i,(0x3FF<<16));}
	}
}
	
// ----------------------------------------------------------------------------------------------------
