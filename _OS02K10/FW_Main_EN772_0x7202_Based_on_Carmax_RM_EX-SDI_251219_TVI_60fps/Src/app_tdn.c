/* **************************************************************************
 File Name	: 	app_tdn.c
 Description:	EN772 - TDN
 Designer	:	Lee, Hoon
 Modifier	:	Kim, Sunghoon
 Date		:	14. 8. 4
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */


#include "dev.h"

UINT gnTdnChkOut=TDN_DAY;

//#define ADC_LIMIT 				511 							// 9bit ADC
#define ADC_LIMIT 				1023 						//10bit ADC

BYTE gbTdnDebugOn;
BYTE gbTdnExtflag=0;                            //  180910 JJH white Led extern flag
UINT gnGetTdnDly;                               //  180910 JJH Led Tdn delay

void ISPM2 TDN(void)			// 180104 LH
{	// Day & Night Filter Changer
 	gbTdnDebugOn = (gbMnDebugFnc==MN_DBG_TDN);

	static 	UINT gnDnChk, gnDnSeq;
	static 	BYTE gbMnTdnBuf, gbMnAdpBuf;
	static 	UINT gnDnChkBuf, gnDnCnt;
	int  iDnDayThrs, iDnNightThrs;
	UINT nDnDelay;
	WORD wCdsIn = TDN_CDS_IN;



#if(model_Led==0 || model_Led==2)														//210225 YTM

	if( LibLedTdnChg(&gnDnChk, &gnDnSeq, MP(MpTdn)!=gbMnTdnBuf, gbMnAdpBuf!=MP(MpAdaptive), gbMnTdnCfg(1)) )
	{
#endif		
	if (MP(MpTdn) == MN_TDN_EXTERN) {   
	
		iDnDayThrs 		= ((int)MP(MpTdnNDThres)*UP(UpTDN_EXTN_THRS_STEP));
		iDnDayThrs 		= (iDnDayThrs<=0)				? 0					:
						  (iDnDayThrs>=(int)ADC_LIMIT)	? (int)ADC_LIMIT	:	iDnDayThrs;

		iDnNightThrs 	= ((int)MP(MpTdnDNThres)*UP(UpTDN_EXTN_THRS_STEP));
		//iDnNightThrs 	= (int)MP(MpTdnDNThres);
		iDnNightThrs 	= (iDnNightThrs>=(int)ADC_LIMIT) ? ADC_LIMIT		:
						  (iDnNightThrs<=0)				? 0					:	iDnNightThrs;
	}
	else {
	
        iDnDayThrs      = (int)TDN_NDTHRS;    // N>D
		iDnDayThrs 		= (iDnDayThrs<=0)				? 0					:
						  (iDnDayThrs>=(int)gnAgcLim)	? (int)gnAgcLim		:	iDnDayThrs;

        iDnNightThrs    = (int)TDN_DNTHRS;    // D>N
		iDnNightThrs 	= (iDnNightThrs>=(int)gnAgcLim) ? gnAgcLim			:
						  (iDnNightThrs<=0)				? 0					:	iDnNightThrs;
	}

	DebugDisp(gbTdnDebugOn, Hex, "AGC_____", 0, 24, giCurAgc);
	DebugDisp(gbTdnDebugOn, Hex, "CDS_IN__", 1, 24, TDN_CDS_IN);

    if((MP(MpAdaptive)!=1)||(MP(MpTdn) == MN_TDN_EXTERN)){
	    DebugDisp(gbTdnDebugOn, Hex, "D>N Thrs", 3, 24, iDnNightThrs);
    	DebugDisp(gbTdnDebugOn, Hex, "N>D Thrs", 4, 24, iDnDayThrs);	    
    }

	switch (MP(MpTdnDly)){
		case 0	: 	nDnDelay = TDN_DLY_1 ;		break;
		case 1	: 	nDnDelay = TDN_DLY_2 ;		break;
		case 2	: 	nDnDelay = TDN_DLY_3 ;		break;
		default :   nDnDelay = TDN_DLY_3 ;		break;
	}
//nDnDelay <<= (FPS_VDI>30);  // 180910 JJH Adaptive Lighting 
 //   #if(model_Led==0)				//210112 YTM
 //	#if(model_Led==0 || model_Led==3)
 //      gnGetTdnDly=nDnDelay;
 // #endif

    if (MP(MpTdn)!=gbMnTdnBuf)        gnDnCnt=0;	

	switch (MP(MpTdn)) {
		case MN_TDN_AUTO	:													// Change by internal AGC value

			if 		(giCurAgc<=iDnDayThrs)		gnDnChk = TDN_DAY;				// Day zone
			else if	(giCurAgc>=iDnNightThrs) 	gnDnChk = TDN_NIT;				// Night zone
			else 								gnDnChk = TDN_HLD;				// Hold zone

			if ((gnDnChk==gnDnChkBuf)&&(gnDnChk!=TDN_HLD)&&(gnDnChk!=gnTdnChkOut)) {
				if (gnDnCnt>=(nDnDelay+1))		{gnDnCnt=0;asm volatile("l.nop");}
				else if (gnDnCnt==nDnDelay)		{gnDnSeq=0;gnDnCnt++;}			// TDN sequance start, Delay cnt hold
				else							gnDnCnt++;						// Delay for smooth act
			}
			else 								gnDnCnt=0;

			break;

		case MN_TDN_DAY	:
			if (gbMnTdnBuf!=MN_TDN_DAY) 	{gnDnSeq=0; gnDnChk=TDN_DAY;}
			break;

		case MN_TDN_NIGHT:
			if (gbMnTdnBuf!=MN_TDN_NIGHT) 	{gnDnSeq=0; gnDnChk=TDN_NIT;}
			break;
		
		case MN_TDN_EXTERN:														// Change by external CDS sensor

 			#if (model_Cds == 1) 												// GPIO input
				wCdsIn = (MP(MpTdnSw) == MN_ON) ? wCdsIn : !wCdsIn;

				if (wCdsIn) 						gnDnChk = TDN_DAY;			// Day zone
				else 								gnDnChk = TDN_NIT;			// Night zone
			#else 																// ADC input
 				if (MP(MpTdnSw) == MN_ON) { 		// EXTERN SW : LOW (=night)
 					if 		(wCdsIn>=iDnDayThrs)	gnDnChk = TDN_DAY;			// Day zone
					else if	(wCdsIn<=iDnNightThrs) 	gnDnChk = TDN_NIT;			// Night zone
					else 							gnDnChk = TDN_HLD;			// Hold zone
 				}
				else { 							// EXTERN SW : HIGH (=day) 
					if 		(wCdsIn<=iDnDayThrs)	gnDnChk = TDN_DAY;			// Day zone
					else if	(wCdsIn>=iDnNightThrs) 	gnDnChk = TDN_NIT;			// Night zone
					else 							gnDnChk = TDN_HLD;			// Hold zone
				}
			#endif
//----------------------------------------------210112 YTM-------------------------------------------
//            #if((model_Led_Sel))						//210108 YTM
//			#if((model_Led == 3))						//210108 YTM

			//210104 YTM
                // gnDnChk : F/W TDN condition, gnDnSeq : TDN device change,  gbMnTdnBuf : previous menu status, (gbTdnExtflag==1) LED on 
                // white led, extern mode, device: day, chkout: day, chk(CDS condition): night     
//                if(gbMnAdpBuf!=MP(MpAdaptive)){
//                    if((gnDnChk == TDN_NIT)&&MP(MpAdaptive)){
//                       TDN_MECH_DAY; gnTdnChkOut=TDN_DAY;
//                    }
//                    else    gbTdnExtflag=0;
//                }                
                /*  F/W and device condition are different and gbTdnExtflag=0 (White LED is on when TDN DAY). 
                    gbTdnExtflag=1 and F/W condition DAY (When the Led is on in EXTERN and the TDN state is Day in B/W). */
//              if ((gnDnChk==gnDnChkBuf)&&(((gnDnChk!=gnTdnChkOut)&&!gbTdnExtflag)||(gbTdnExtflag&&(gnDnChk==TDN_DAY)))) {
//                  if (gnDnCnt>=(nDnDelay+1))      {gnDnCnt=0; asm volatile("l.nop");}
//                  else if (gnDnCnt==nDnDelay)     {gnDnSeq=0; gnDnCnt++;  gbTdnExtflag=(gnDnChk==TDN_NIT)? 1 : 0;}   // TDN sequance start, Delay cnt hold  White LED on -> gbTdnExtflag=1 
//            #else
//----------------------------------------------210112 YTM-------------------------------------------

			    if ((gnDnChk==gnDnChkBuf)&&(gnDnChk!=gnTdnChkOut)) {
                    if (gnDnCnt>=(nDnDelay+1))      {gnDnCnt=0; asm volatile("l.nop");}
                    else if (gnDnCnt==nDnDelay)     {gnDnSeq=0; gnDnCnt++;}             // TDN sequance start, Delay cnt hold
				    else							gnDnCnt++;						    // Delay for smooth act
			    }
			    else 								gnDnCnt=0;						
			break;		
	}

#if (model_Led==0 || model_Led==2)													//210225 YTM
    }
#endif

	gnDnChkBuf = gnDnChk;
	gbMnTdnBuf = MP(MpTdn);
    gbMnAdpBuf = MP(MpAdaptive);
    
	if (gnDnSeq<=20) {															// Change Sequance
		if (gnDnSeq==2) {
			switch (gnDnChk) {
                case TDN_NIT    :   TDN_MECH_NIT;   gnTdnChkOut=TDN_NIT; break;        
				case TDN_DAY	:	TDN_MECH_DAY;	gnTdnChkOut=TDN_DAY; break;
				default 		:	TDN_MECH_HLD;	break;
			}
			#if(model_Led==0 || model_Led==2)												//210225 YTM
                LibLedTdnChk(); 
            #endif
		}
		else if (gnDnSeq==16) TDN_MECH_HLD;
//		else if (gnDnSeq==8) TDN_MECH_HLD;
//		else if (gnDnSeq==30) TDN_MECH_HLD;
		gnDnSeq++;
	}
	
////  Monitoring (CAUTION ! Erase after engineering) ----------
//
//	DispDat("CNT       "	, 8, 24, gnDnCnt);
//	DispDat("CHK       "	, 9, 24, gnDnChk);
//	DispDat("SEQ       "	,10, 24, gnDnSeq);
//
// 	GRP0 = (UINT)giCurAgc		;
//	GRP1 = (UINT)iDnThrs		;
//	GRP2 = (UINT)iDnDayThrs		;
//	GRP3 = (UINT)iDnNightThrs 	;
//	TxGrp();							

}

