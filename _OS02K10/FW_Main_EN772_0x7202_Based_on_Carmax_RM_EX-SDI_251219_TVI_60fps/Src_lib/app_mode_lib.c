/* **************************************************************************
 File Name	:	app_mode_lib.c
 Description	:	EN772 - Mode change function library
 Designer		:	Lee, Gyu Hong
 Date		:	20. 12. 10
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "../Src/dev.h"

// SYSTEM
#define FORCE_SKEYr				(ValSft_R00(_rd32(_REG_BASE_+(0x3919<<2)))&BitMask_32)
#define FORCE_SKEYw(val)		_wr32(_REG_BASE_+(0x3919<<2),(UINT)((_rd32(_REG_BASE_+(0x3919<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define FORCE_SMODEr			(ValSft_R00(_rd32(_REG_BASE_+(0x4214<<2)))&BitMask_32)
#define FORCE_SMODEw(val)		_wr32(_REG_BASE_+(0x4214<<2),(UINT)((_rd32(_REG_BASE_+(0x4214<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define RMODEr					(ValSft_R00(_rd32(_REG_BASE_+(0x3a5b<<2)))&BitMask_02)

// ======================================================================================================================
// ISP Output Switch Macro	(ON/OFF)
// ======================================================================================================================
// SDI
#define POWER_ON_SDI    	{STX_POw(1); STX_UCCRX_POw(1); TSDI_DO_OFFw(0); SLCK_PDw(0); TPCK_PDw(0); MSCK_PDw(0);}
#define POWER_OFF_SDI   	{STX_POw(0); STX_UCCRX_POw(0); TSDI_DO_OFFw(1); SLCK_PDw(1); TPCK_PDw(1); MSCK_PDw(1);}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------
#define	MASTER_FW		0		//*0 : Default (Official release setting !!)
								// 1 : Master FW (Eyenix Engineer Only. but, Secure operation based on booting counter)
								
#define	DCOD			1		// 0 : It is for agency only
								//*1 : DCOD Only

//*************************************************************************************************
// ISP Model Infomation (CAUTION !!)
//-------------------------------------------------------------------------------------------------
enum{
	LIB_ISP_EN772 = 0,	// 0
	LIB_ISP_EN772S,		// 1
	LIB_ISP_EN775,		// 2
	LIB_ISP_EN775S,		// 3
	LIB_ISP_EN801,		// 4
	LIB_ISP_EN801M		// 5
};

enum{
	LIB_INVLD_RES = 0,
	LIB_UPTO_2M,
	LIB_UPTO_5M,
};

#if(DCOD)				// DCOD
	#define MODE_EN772_COND		(((RMODEr==0x0)||(RMODEr==0x2)||(RMODEr==0x1)||(RMODEr==0x3))&&\
								((gbModel_ISP==LIB_ISP_EN772)||(gbModel_ISP==LIB_ISP_EN772S)))		// EN772, EN772S, EN775, EN775S
	#define MODE_EN775_COND		(((RMODEr==0x2)||(RMODEr==0x3))&&\
								((gbModel_ISP==LIB_ISP_EN775)||(gbModel_ISP==LIB_ISP_EN775S)))		// EN775, EN775S
#else					// Agency
	#define MODE_EN772_COND		(((RMODEr==0x1)||(RMODEr==0x3))&&\
								((gbModel_ISP==LIB_ISP_EN772)||(gbModel_ISP==LIB_ISP_EN772S)))		// EN801A, EN801S, EN805A, EN805S
	#define MODE_EN775_COND		((RMODEr==0x3)&&\
								((gbModel_ISP==LIB_ISP_EN775)||(gbModel_ISP==LIB_ISP_EN775S)))		// EN805A, EN805S
#endif

	#define MODE_EN801_COND 	((RMODEr==0x0)&&\
								((gbModel_ISP==LIB_ISP_EN801)||(gbModel_ISP==LIB_ISP_EN801M))) 		// EN801, EN801M

//	#define MODE_EN805_COND 	((RMODEr==0x3)&&(gbModel_ISP==3 ))							// CAUTION !! (EN805)

// ------------------------------------------------------------------------------------------------------------------------------------------------------------
UINT gnCondN7 = 0;
extern BYTE gbModel_ISP;

void LibModeExUcc(void);


void ISPM LibModelInfo(void)
{
	if(MASTER_FW){	
								 	 TxStrNoIRQ("----- Master F/W Start !-----", 0,0);
	}
	else{
		if(DCOD){				// DCOD
			switch(gbModel_ISP){
				case LIB_ISP_EN772 : TxStrNoIRQ("----- EN772 Start !-----", 0,0);	break;
				case LIB_ISP_EN772S: TxStrNoIRQ("----- EN772S Start !-----", 0,0);	break;
				case LIB_ISP_EN775 : TxStrNoIRQ("----- EN775 Start !-----", 0,0);	break;
				case LIB_ISP_EN775S: TxStrNoIRQ("----- EN775S Start !-----", 0,0);	break;
				case LIB_ISP_EN801 : TxStrNoIRQ("----- EN801 Start !-----", 0,0);	break;
				case LIB_ISP_EN801M: TxStrNoIRQ("----- EN801M Start !-----", 0,0);	break;
				default		   	   : TxStrNoIRQ("----- Invalid ISP !-----", 0,0);	break;
			}
		}
		else{					// Agency
			switch(gbModel_ISP){
				case LIB_ISP_EN772 : TxStrNoIRQ("----- EN801A Start !-----", 0,0);	break;
				case LIB_ISP_EN772S: TxStrNoIRQ("----- EN801S Start !-----", 0,0);	break;
				case LIB_ISP_EN775 : TxStrNoIRQ("----- EN805A Start !-----", 0,0);	break;
				case LIB_ISP_EN775S: TxStrNoIRQ("----- EN805S Start !-----", 0,0);	break;
				case LIB_ISP_EN801 : TxStrNoIRQ("----- EN801 Start !-----", 0,0);	break;
				case LIB_ISP_EN801M: TxStrNoIRQ("----- EN801M Start !-----", 0,0);	break;
				default		   	   : TxStrNoIRQ("----- Invalid ISP !-----", 0,0);	break;
			}
		}
	}

	TxStrNoIRQ("\t\t\t\t\t", 0, 0);
}

void ISPM LibBrkIsp(void)
{
	TxStrNoIRQ("Mode is wrong !!", 0, 0);
	WaitXms(30);
	
	while(1);
}

void ISPM LibBrkCond(void)
{
	if(!gnCondN7)																LibBrkIsp();
	if ((!(gnCondN7==LIB_UPTO_5M))&&((RDES_HWr >= 0x800)||(HWIr >= 0x800))) 	LibBrkIsp();
}

void ISPM2 LibModeInit (void)
{
#if(!MASTER_FW)
	gnCondN7 = ((MODE_EN772_COND)||(MODE_EN801_COND))?(LIB_UPTO_2M):\
			   ((MODE_EN775_COND))?(LIB_UPTO_5M):(LIB_INVLD_RES);
#else
	gnCondN7 = LIB_UPTO_5M;

	// TEMP SEC DEV
	#define SWITCH	5000
	
	static WORD wRstCnt = 0;
	BYTE bRstCntCalBuf[2] = {0,};
	UINT nCurAddr;
	
	bRstCntCalBuf[0] = 0;
	bRstCntCalBuf[1] = 0;
	
	nCurAddr = (120*(4*1024));			// 120 sector

#if(1)
	SfRead(nCurAddr, bRstCntCalBuf, 2);
	wRstCnt = ((bRstCntCalBuf[1]<<8)|bRstCntCalBuf[0]);
	wRstCnt++;
	
	TxStrNoIRQ("Test Booting...", wRstCnt, 4);
	
	bRstCntCalBuf[0] = (wRstCnt>>0)&0xFF;
	bRstCntCalBuf[1] = (wRstCnt>>8)&0xFF;
	
	SfWrite(nCurAddr, bRstCntCalBuf, 2);
#else
	SfWrite(nCurAddr, bRstCntCalBuf, 2);
#endif
	
	if(wRstCnt > SWITCH)		LibBrkIsp();	
#endif

	FORCE_SKEYw(0x76152979);
	FORCE_SMODEw(0x1);
	FORCE_SKEYw(0x0);

	// LGH : (CAUTION !!) 
	STX_POw(1);
}

//-------------------------------------------------------------------------------------------------
// ISP - HDSDI
const UINT gnTblIspHdSdi[][3] = { 		//HD-SDI		//3G-SDI
								//Clock		          
								{0x0013,  0x00000000,	0x00000000},
          
								//Module          
								{0x0701,  0x00000009,	0x00000009},
								{0x0744,  0x00000000,	0x00000000},
								{0x0749,  0x00000430,	0x00002430}
								};

const UINT gnTblIspHdSdiEa = numberof(gnTblIspHdSdi);

//-------------------------------------------------------------------------------------------------
// ISP - EXSDI

const UINT gnTblIspExSdi[][4] = { 		//VER1.0 270		VER2.1 135M+		VER2.1 3G(2M60p/4M30p)
								//Clock
								{0x0013,  0x00000002,	0x00000002,		0x0000000b},
                                                                                    
								//Module                                            
								{0x0701,  0x00000001,   0x00000001,     0x00000001},
								{0x0744,  0x00000002,   0x00000002,     0x00000002},
								{0x0749,  0x00001430,   0x00003c38,     0x00001c38},
                                                                                    
								//EX-SDI Only                                       
								{0x0751,  0x00000000,   0x28000000,     0x28000000},
								{0x0752,  0x00000030,   0x00000230,     0x00000230},
								{0x0753,  0x01808800,   0x01808800,     0x01808800},
								{0x0754,  0x02000080,   0x02000080,     0x02000080},
								{0x0757,  0x80800000,   0x80800000,     0x00800000},
								{0x074d,  0x00000980,   0x00000980,     0x40000980},
//								{0x074d,  0x00800980,	0x00800980, 	0x44800980},
//								{0x0764,  0x28808436,   0x2b808476,     0x2b80847f},
								{0x0764,  0x28808436,	0x2b80847F, 	0x2b80847f},	// 250109 LGH : VER2.1 135M+, EXE_QUAL_LOW_A 0x16 to 0x1F
								{0x0765,  0x01400880,   0x07400820,     0x01400880},
								{0x0766,  0x00000000,   0xc1000000,     0xc1000000}
								};

const UINT gnTblIspExSdiEa = numberof(gnTblIspExSdi);

void ISPM2 LibModeSdi(UINT anMode, UINT anSdiMode)
{	// SDI config (CAUTION ! couldn't be call continuously)
	// anMode - 0: SDI Off, 1: HD-SDI, 2: EX-SDI
	// anSdiMode 
	// HD-SDI = 0 :  1.5G-SDI, 1 : 3G-SDI
	// EX-SDI = 0 : EX-SDI 1.0(270M), 1: EX-SDI 2.1(135M) ,2: EX-SDI 2.1(3G,4M - 270M)

enum{
	MODE_SDI_OUT_OFF = 0,	// 0 : OFF
	MODE_HD_SDI_OUT,		// 1 : HD-SDI
	MODE_EX_SDI_OUT			// 2 : EX-SDI
};
	UINT i;

	if((gbModel_ISP==LIB_ISP_EN772)||(gbModel_ISP==LIB_ISP_EN775)||(gbModel_ISP==LIB_ISP_EN801)){
		POWER_OFF_SDI;
		return;
	}
	else{
		// SDI OFF
		if(anMode==MODE_SDI_OUT_OFF)				{POWER_OFF_SDI;}
		else{
			if(anMode==MODE_HD_SDI_OUT){
				if(anSdiMode==1)					{LibBrkIsp();}	//3G-SDI
				for (i=0; i<gnTblIspHdSdiEa; i++)	{SetIsp(gnTblIspHdSdi[i][0], gnTblIspHdSdi[i][1+anSdiMode]);}
			}
			else if(anMode==MODE_EX_SDI_OUT){
				for (i=0; i<gnTblIspExSdiEa; i++) 	{SetIsp(gnTblIspExSdi[i][0], gnTblIspExSdi[i][(1+anSdiMode)]);}
			}
													{POWER_ON_SDI;}
			// 210114 LHJ : Default setting
			// SDI PHY
			STX_SWGw(0x7);
			SPLL_BWw(0x6);
			SPLL_RESw(0x6);	

			LibModeExUcc();
		}
	}
}

void LibModeExUcc(void)
{
	//UCC V1.0
	EXUD_SD_MANUALw(0);
	V1UD_MAX_THw(0x200);
	V1UD_UPPER_THw(0x1f0);
	V1UD_LOWER_THw(0xf);
	V1UD_SAMPLE_RATEw(0x1);
	UD_DATA_OSELw(1);	//uccv1
	V1UD_INSELw(0);	//not use
//	UCC_TXPHY_SELw(1);			// Internal UCC
	UCC_TXPHY_SELw(0);			// External UCC

	STX_UCC_MUXw(0x0);
	STX_UCCRX_FLTRw(0x3);
	STX_REF_CAPw(0x3);
	
	EXUD_FREQ_NUMw(0x4a);

#if(0)
	//EXUCC	1.5M
	UD_DATA_OSELw(0);	//exucc
	EXUD_SD_MANUALw(1);
	V1UD_MAX_THw(60);
	V1UD_UPPER_THw(40);
	V1UD_LOWER_THw(20);
	V1UD_SAMPLE_RATEw(0);
	UCC_TXPHY_SELw(1);
	DUCC_MUXw(0x2);
	EXUD_ATT_ENw(1);
	EXUD_INSELw(0);
	STX_UCC_MUXw(0x3);
	EXUD_FREQ_NUMw(0x63);

	//8b10b	
	EXUD_SD_MANUALw(1);
	V1UD_MAX_THw(91);
	V1UD_UPPER_THw(60);
	V1UD_LOWER_THw(31);
	V1UD_SAMPLE_RATEw(0);
	EXUD_INSELw(0);
	UCC_TXPHY_SELw(1);
	DUCC_MUXw(0x2);
	STX_UCC_MUXw(0x3);
	EXUD_FREQ_NUMw(0x96);
#endif
}

