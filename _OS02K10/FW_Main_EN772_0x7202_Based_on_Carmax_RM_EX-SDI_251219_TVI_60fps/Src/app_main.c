/* **************************************************************************
 File Name	: 	app_main.c
 Description	:	EN772 - Main function
 Designer		:	Lee, Hoon
 Modifier		:	Lee, Gyu Hong
 Date		:	16.10.20
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

extern UINT gnIncrsBlkLv;

//*******************************************************************************
// Sub
//*******************************************************************************
// Define for Interrupt
// Main Loop
#define LOOP_START		UINT nTotalClkMainVdo = 0;\
						UINT nTotalClkMainVdi = 0;\
						while(1) {

#define LOOP_MN_VDO		if ((gbMnVdIrq==1)&&(gbVdiIrq == 0)&&(gbVdoIrq == 0)){\
							gbMnVdIrq = 0;
						
#define LOOP_VDO		}\
						if ((gbVdoIrq == 1)&&(gbVdiIrq == 0)) {/*���irq �� �ְ� �Է�irq ���� �� ����*/\
							gbVdoIrq = 0;\
							/*���IRQ ���� �ڵ�*/\
							static UINT nDispDbgYmax = 0;\
							if(gnDispDbgY > nDispDbgYmax) { nDispDbgYmax = gnDispDbgY; OsdClearAll(); OsdCamTitle(); if(gbMenuState) menu_redraw(1,0); }\
							else gnDispDbgY = nDispDbgYmax;\
							FUNC_TIME_START(MainVDO);

#define LOOP_VDI			/*���IRQ ���� �ڵ�*/\
							FUNC_TIME_END(MainVDO,"VDO Prc");\
							nTotalClkMainVdo = nTick_MainVDO;\
							\
							TxGrpRun();\
							gnDispDbgY = DispDbgYmin;\
							WdtRst;\
						}\
						if (gbVdiIrq == 1) {/*�Է�irq �� ���� �� ����*/\
							gbVdiIrq = 0;\
							/*Sensor Black Level*/\
							SetSensBst(0x300A, (gnIncrsBlkLv&0x1FF), 2);\
							/*�Է�IRQ ���� �ڵ�*/\
							gnDispDbgY = DispDbgYmin;\
							FUNC_TIME_START(MainVDI);

#define LOOP_END			/*�Է�IRQ ���� �ڵ�*/\
							FUNC_TIME_END(MainVDI,"VDI Prc");\
							nTotalClkMainVdi = nTick_MainVDI;\
							gnDispDbgY++;\
							\
							if(GRP_DEBUG_IMG_TUNE)\
							TxGrp();\
							TxGrpRun();\
						}\
					}\
					return	0;

//*******************************************************************************
// Main Top
//*******************************************************************************
int ISPM main(void)
{	
	Init();	

LOOP_START

LOOP_MN_VDO

		Comm();									// Communication Interface
		
		AppSavePar();
		AppLoadPar();
		
LOOP_VDO

		UccA();   								// 200819 HTY

		ModeChange();							// Output mode management (fixed function)
		
		KeyScan();								// Key input detection

		Menu();									// Menu
		
//		ModeLed();
		
LOOP_VDI
	
		static UINT nTickSta_VDI = 0;
//		TICK_END(VDI); if(gbMnDebugFnc==7) DispDatDec("VDI time", 10, 24, tick2us(VDI));	// VDI time checking
		nTickSta_VDI = GetTT();
		
		if (!(gbMnDebugBypass==1)) {	// Function Bypass for Debugging. CAUTION !! Erase after development	

//			Focus								// Auto Focus or Focus Assist
			
//			ModeChange();						// Output mode management (fixed function)

			Ae();								// Auto exposure
	
//			TDN();								// Day & Night
			
			Gamma();							// Gamma control
			
			AceDefog();							// ACE & Defog
			
			Awb();								// Auto white balance (Usage rate : All = 14.5%, Only LibAwbCmat() = 11.3%)

			Adnr();								// DNR 2D/3D

			Sharpness();						// Sharpness (aperture)
			
			Mirror();							// Mirror on/off			

			Flip();								// Flip on/off
			
//			HlMask();							// High light mask

			CSup();								// Color surpression

			ColorBar();							// Color Bar
			
			Shading();							// Shading correction

			Defect();							// Defect correction

//			PrivacyBox();						// Box Privacy
			
//			BoxLast();							// Last Box control

//			TxGrp();

		}
		else {
		}
		
		TICK_END(VDI); if(gbMnDebugFnc==8) DispDatDec("VDI time", 0, 24, tick2us(VDI));	// VDI time checking
		
		iKEY = 0;								// Key reset (VDI)	

LOOP_END

}

