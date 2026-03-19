/* **************************************************************************
 File Name	: 	dev.h
 Description	:	EN772 - Device Driver
 Designer		:	Lee, Gyu Hong
 Date		:	20. 06. 08
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */
/*
 INDEX	:
		 1. System
		 2. GPIO
		 3. ADC
		 4. UART
		 5. I2C
		 6. TIMER
		 7. SPI
		 8. IRQ
		 9. FLASH
		10. WDT
		11. ISP
		12. SENSOR
		13. TEST
*/

//******************************************************
// 1. System
//------------------------------------------------------
//*************************************************************************************************
// Software version info & fixed define
//-------------------------------------------------------------------------------------------------

	#define 	model_ver			0x7202		// Eyenix base code version

	// ISP model
	#define		ISP_EN772				0		// Analog		(Max. 2M)
	#define		ISP_EN772S				1		// Analog + SDI	(Max. 2M)
	#define		ISP_EN775				2		// Analog		(Max. 5M)
	#define		ISP_EN775S				3		// Analog + SDI	(Max. 5M)
	#define		ISP_EN801				4		// Mipi			(Max. 2M)
	#define		ISP_EN801M				5		// Mipi + SDI		(Max. 2M)
	
	// Sensor List
	#define 	SENS_IMX225				10		// Sony 1M 60p			
	#define 	SENS_IMX224				11		// Sony 1M 60p			

	#define 	SENS_IMX290				20		// Sony 2M 60p
	#define 	SENS_IMX327				21		// Sony 2M 60p
	#define		SENS_IMX307				22		// Sony 2M 60p
	#define		SENS_IMX462				23		// Sony 2M 60p
	#define		SENS_IMX662				24		// Sony 2M 60p 
	#define		SENS_GC2053				25		// Galaxcore 2M 30p
	#define		SENS_GC2093				26		// Galaxcore 2M 60p
	#define		SENS_SC200AI			27		// SmartSens 2M 60p
	#define		SENS_PS6210K			28		// PixelPlus 2M 30p
	#define		SENS_OS02H10			29		// Omni 2M 60p		(TBD)

	#define		SENS_IMX390				30		// Sony 2M60p (LFM)		(TBD)
	#define		SENS_OS02K10			33		// Omni 2M 60p			(Compressed HDR)
	#define		SENS_OX03C10			35		// Omni 2M 60p (LFM)		(TBD)
	#define		SENS_AR0233				37		// Onsemi 2M 60p (LFM)		(TBD)
	
	#define		SENS_IMX335				50		// Sony 5M 20p		
	#define		SENS_IMX675				51		// Sony 5M 25p	
	#define		SENS_SC500AI			58		// Smartsens 4M 30p
	#define		SENS_OS04C10			59		// Omni 4M 30p

//*************************************************************************************************
// System & HW config define
//-------------------------------------------------------------------------------------------------

#ifndef __LIB__

	// Image Quality Option -----------------------------------------------------------------------
	#define		Model_Rear				0		// 0 : IMX307, IMX662, IMX675
												// 1 : IMX462

	#define		model_ImgTune_Option	1		// 0 : Ref Setting Value
												//*1 : Fine Tuning data each sensor (default)

	#define 	model_Isp		ISP_EN772S	// ISP selection
// #define 	model_Isp			ISP_EN775S	// ISP selection

#if(Model_Rear==0)
//	#define 	model_Sens			SENS_IMX307	// Sensor selection
//	#define 	model_Sens			SENS_IMX662	// Sensor selection
//	#define 	model_Sens			SENS_IMX675	// Sensor selection
	#define 	model_Sens			SENS_OS04C10// Sensor selection
#else
	#define 	model_Sens			SENS_OS02K10// Sensor selection

	#define		model_IQ_Option			1		//*1 : Option 1
												// 2 : Option 2
#endif

	#define		model_TgtBd				0		// Target board
												// 0: Enx Socket Bd, 1: Enx EVM Module, 2: Customer

	// Digital Output config ----------------------------------------------------------------------
	#define		model_Dout				1		/* Digital Output mode selection */
												// 0 : Internal SDI
												// 1 : Digital all off

	#define 	model_ExSdiSel			0		// 0 : no use SDI
	                                            // 1 : EX-SDI /HD-SDI selection by physical Switch(GPIO)
												//*2 : EX-SDI /HD-SDI selection by sequencial hidden key

	#define 	model_UccD				1		/* Upstream communication via SDI */
												// 0 : no use
												// 1 : UCC via SDI Out

	#define		model_UccD_Stop		    0		/* Pelco-D stop protocol from DVR */
												// 0 : no use
												//*1 : use

	// Analog Output config -----------------------------------------------------------------------
	#define		model_Aout				1		/* internal Analog Output mode selection */
												// 0 : CVBS 720H (CVBS Only)
												//*1 : CVBS 720H or HD-Analog (Video amp circuit should be fixed either each mode)
												// 2 : Analog all off

	#define 	model_HdAnSel			2		// 0 : no use internal HD-analog
	                                            // 1 : Internal HD-Analog /CVBS selection by physical Switch(GPIO)
												//*2 : Internal HD-Analog /CVBS selection by sequencial hidden key

	#define 	model_UccA				0		/* Upstream communication via internal Analog Output */
												// 0 : no use
												// 1 : use Analog UCC (HD-analog, CVBS Coxitron)

	#define		model_CvbsAdc			0		// 0 : no use Auto detection for CVBS
												// 1 : use Auto detection for CVBS (need dedicated circuit for CVBS and no HD-analog)

	#define     model_UccA_T            0       /* HD_T Stop protocol from DVR */
											    //*0 : no use
												// 1 : use
												
	// -------------------------------------------------------------------------------------------

	#define 	model_Uart2				0		// 0 : no use UART CH2
												// 1 : use UART CH2 for normal purpose

	#define 	model_I2C_ch1			0		//*0 : no use (default)
												// 1 : I2C operate to Slave mode
												// 2 : I2C operate to Master mode
												
	#define		model_Lens				0		// Lens type
												// 0 : normal DC, 1 : 2Motor

	#define		model_Iris				0		// IRIS control by
												// 0 : no IRIS (module type), 1: MPWM(DC)

	#define		model_Tdn				2		// 0 : TDN control by 1 port 2 state (H, L)
												// 1 : TDN control by 1 port 3 state (H, L, Hi-z)
												// 2 : TDN control by 2 ports
	
	#define 	model_ModeLed			0		//*0 : no use MODE LED indicator
												// 1 : use MODE LED indicator (Use Frame Count)
												// 2 : use MODE LED indicator (Use Timer)

	#define 	model_Save				1		// 0 : save Parameter value to External EEPROM by I2C(TWI)
												//*1 : save Parameter value to internal Flash

	#define 	model_Flash				0		// 0 : Flash - Eon Quad
												// 1 : Flash - Winbond or GigaDevice Quad

	#define		model_Protect			1		// 0 : no use Flash Protection
												// 1 : use Flash Protection (default)

	#define 	model_Key				1		// 0 : KEY input by ADC
												// 1 : no physical key (UART Key only)

    // CDS, IR-LED config ---------------------------------------------------------------------------------

    #define     model_Cds               0       // 0 : CDS input by ADC
												//*1 : CDS input by GPIO

    #define     model_Led              	3		// 0 : IR LED Adaptive Light by LPWM
												// 1 : IR IO full control only  by GPIO
												// 2 : White LED Adaptive Light by LPWM
												//*3 : Not used Led function
	// -------------------------------------------------------------------------------------------

//*************************************************************************************************
// Application & SW config define
//-------------------------------------------------------------------------------------------------

	#define		model_Par				1		// 0 : user parameter NOT be controled by ECM (use defined parameter in app.h)
												//*1 : user parameter be controled by ECM     (use defined parameter in app.h)

	#define		model_ParID			0x12345678	// Enable parameter ID for control with ECM

	// Menu config -----------------------------------------------------------------------
	#define 	model_CharMax			0		// 0 : Font char max ea - 256 (BYTE)
												// 1 : Font char max ea - ISP_FONT_CHAR_EA (WORD)

	#define		model_MenuDefSet		0		// The function to change and save the MENU RESET values.
												// 0 : no use
												// 1 : use

//*************************************************************************************************
// Eyenix reserved define
//-------------------------------------------------------------------------------------------------
	#define		model_AwbCapOn			0		// CAUTION !! Use for Eyenix engineering
	
	#define		model_AWB_Matrix		0		//*0 : MP V1.0.0, MP V1.0.1
												// 1 : Only Test

	#define		GRP_DEBUG_IMG_TUNE		1		//*0 : OFF
												// 1 : Debug mode using graph viewer

	#if((model_Isp==ISP_EN801))
		#undef	model_Aout
		#define	model_Aout		2
		#undef	model_HdAnSel
		#define	model_HdAnSel	0
		#undef	model_UccA		
		#define model_UccA		0

		#undef	model_Key
		#define model_Key		1
	#endif


	#if(model_Aout==2)
		#undef	model_UccA		
		#define model_UccA		0
		#undef	model_CvbsAdc		
		#define model_CvbsAdc	0
		#undef	model_UccA_T		
		#define model_UccA_T	0
	#endif
	
	
#endif//__LIB__

#ifdef model_Sens	// ���� �� lib ���� ��

// Include header file 
#include "dev_misc.h"
#include "dev_extn.h"

#include "dev_reg_cpu.h"
#include "dev_reg_isp.h"

#include "dev_enc.h"	// Encoder header file
#include "dev_mipi.h"	// Mipi header file

#include "app.h"

#if(model_ImgTune_Option==0)
#include "app_isp_func_AT.h"
#else
#include "FineTune/Sensor_FineTune_UP.h"
#endif

//******************************************************
// 2. GPIO
//------------------------------------------------------
// assign GPIO Pin no. (0 ~ 19)

		#define 	GPIO_SI2C_CK		GPIO00		// Sensor interface (Fixed I2C, GPIO 0,1,2)
		#define 	GPIO_SI2C_DA		GPIO01		// "
		#define 	GPIO_SRSTN			GPIO02      // "

		#define		GPIO_UART_RX		GPIO05
		#define		GPIO_UART_TX		GPIO06

		#define		GPIO_UART2_RX		GPIO08		// UART2 RX
		#define		GPIO_UART2_TX		GPIO09		// UART2 TX		


		#define		GPIO_UART2_TX		GPIO09		// UART2 TX	

#ifndef __LIB__

//******************************************************
// EN772, 775
//******************************************************
#if (model_TgtBd==0) // reserved ------------

		#define		GPIO_MPWM			GPIO07		// Micom PWM out for IRIS control

	#if (model_Cds==1)
		#define		GPIO_CDS_IN			GPIO08		// CDS input
	#endif
	
		#define		GPIO_TDN_1			GPIO09		// TDN out Port1
	#if (model_Tdn==2)
		#define		GPIO_TDN_2			GPIO10		// TDN out Port2
	#endif
	
	#if (model_Led==1)
		#define		GPIO_LED_CTL		GPIO11		// LED control out (GPIO or LPWM)
	#endif

	#if (model_Lens==1)
		#define		GPIO_MTR_ZOOM_AP	GPIO12		// Motor Focus Control 	A+
		#define		GPIO_MTR_ZOOM_AM	GPIO13	    // "				   	A-
		#define		GPIO_MTR_ZOOM_BP	GPIO14	    // "			 	   	B+
		#define		GPIO_MTR_ZOOM_BM	GPIO15	    // "			       		B-
		#define		GPIO_MTR_FCS_AP		GPIO16		// Motor Zoom Control  	A+
		#define		GPIO_MTR_FCS_AM		GPIO17	    // "				   	A-
		#define		GPIO_MTR_FCS_BP		GPIO18	    // "			 	   	B+
		#define		GPIO_MTR_FCS_BM		GPIO19	    // "			       		B-
	#endif

	#if(model_ModeLed==2)
		#define		GPIO_MODE_LED		GPIO18		// LED Control (BlackBox)
	#endif


#elif (model_TgtBd==1) // reserved ----------

		#define		GPIO_MPWM			GPIO07		// Micom PWM out for IRIS control

	#if (model_Cds==1)
		#define		GPIO_CDS_IN			GPIO08		// CDS input
	#endif
	
		#define		GPIO_TDN_1			GPIO09		// TDN out Port1
	#if (model_Tdn==2)
		#define		GPIO_TDN_2			GPIO10		// TDN out Port2
	#endif
	
	#if (model_Led==1)
		#define		GPIO_LED_CTL		GPIO11		// LED control out (GPIO or LPWM)
	#endif

	#if (model_Lens==1)
		#define		GPIO_MTR_ZOOM_AP	GPIO12		// Motor Focus Control 	A+
		#define		GPIO_MTR_ZOOM_AM	GPIO13	    // "				   	A-
		#define		GPIO_MTR_ZOOM_BP	GPIO14	    // "			 	   	B+
		#define		GPIO_MTR_ZOOM_BM	GPIO15	    // "			       		B-
		#define		GPIO_MTR_FCS_AP		GPIO16		// Motor Zoom Control  	A+
		#define		GPIO_MTR_FCS_AM		GPIO17	    // "				   	A-
		#define		GPIO_MTR_FCS_BP		GPIO18	    // "			 	   	B+
		#define		GPIO_MTR_FCS_BM		GPIO19	    // "			       		B-
	#endif

	#if(model_ModeLed==2)
		#define 	GPIO_MODE_LED		GPIO18		// LED Control (BlackBox)
	#endif

#else	// Customer -------------------------

		#define		GPIO_MPWM			GPIO07		// Micom PWM out for IRIS control

	#if (model_Cds==1)
		#define		GPIO_CDS_IN			GPIO08		// CDS input
	#endif
	
		#define		GPIO_TDN_1			GPIO09		// TDN out Port1
	#if (model_Tdn==2)
		#define		GPIO_TDN_2			GPIO10		// TDN out Port2
	#endif
	
	#if (model_Led==1)
		#define		GPIO_LED_CTL		GPIO11		// LED control out (GPIO or LPWM)
	#endif

	#if (model_Lens==1)
		#define		GPIO_MTR_ZOOM_AP	GPIO12		// Motor Focus Control 	A+
		#define		GPIO_MTR_ZOOM_AM	GPIO13	    // "				   	A-
		#define		GPIO_MTR_ZOOM_BP	GPIO14	    // "			 	   	B+
		#define		GPIO_MTR_ZOOM_BM	GPIO15	    // "			       		B-
		#define		GPIO_MTR_FCS_AP		GPIO16		// Motor Zoom Control  	A+
		#define		GPIO_MTR_FCS_AM		GPIO17	    // "				   	A-
		#define		GPIO_MTR_FCS_BP		GPIO18	    // "			 	   	B+
		#define		GPIO_MTR_FCS_BM		GPIO19	    // "			       		B-
	#endif

#endif

#endif//__LIB__


//******************************************************
// 3. ADC (in ISP function)
//------------------------------------------------------
#ifndef __LIB__

#if (model_TgtBd==0) 	// reserved ----------
	#define ADC_KEYr			(ADC_RDATA0r)
	#define ADC_CDSr			(ADC_RDATA1r)
#elif (model_TgtBd==1) 	// reserved --------
	#define ADC_KEYr			(ADC_RDATA0r)
	#define ADC_CDSr			(ADC_RDATA1r)
#else					// Customer -------
	#define ADC_KEYr			(ADC_RDATA0r)
	#define ADC_CDSr			(ADC_RDATA1r)
#endif

#endif//__LIB__

#define POWER_ON_ADC		{ADC_INT_ENw(0); ACK_PDw(0); ADC_XPD_WRw(0x1);}
#define POWER_OFF_ADC       {ADC_INT_ENw(0); ACK_PDw(1); ADC_XPD_WRw(0x0);}

//******************************************************
// 4. UART
//------------------------------------------------------
// Select BaudRate
//UB2400, UB4800, UB9600, UB19200, UB38400, UB57600, UB115200
#define UB_INIT					(UB115200)
#define MN_BR_INIT				(MN_BR_115200)

#define UB_UCC_INIT				(UB9600)					// model_UccD �Ǵ� model_UartRx ���� �ʱ� �������� ���?


//******************************************************
// 5. I2C
//------------------------------------------------------
#ifndef __LIB__

#define I2C0_CLKDIV_MASTER		I2C_CLKDIV(I2C_CLKDIV384)	// I2C0 SCL frequency		// MCLK / CLKDIV512 = 148500000 / 384 = 386.718Kbps

#define I2C1_CLKDIV_MASTER		I2C_CLKDIV(I2C_CLKDIV384)	// I2C1 SCL frequency
#define I2C1_CLKDIV_SLAVE		I2C_CLKDIV(I2C_CLKDIV96)	// I2C1 sampling frequency	

// I2C Slave Mode config
//#define SLAVE_DEVICE			(0x20)
#define SLAVE_DEVICE			(0xAA)

// I2C external device
#define EEPROM_DEVICE			(0xa0)		// EVM : 24LC64F	SOT type (no address)

#define	TWI_EEP_PAGE_EA			(256)						// 24C64 PAGE No.
#define	TWI_EEP_BYTE_EA			( 32)						// 24C64 BYTE No. each Page

#define TWI_EEP_MENU_STT		(  0)						// Menu par save pos (1024 byte space)
#define TWI_EEP_USER_STT		(32*TWI_EEP_BYTE_EA)		// User par save pos (1024 byte space)
#define TWI_EEP_DATA_STT		(64*TWI_EEP_BYTE_EA)		// Application data save pos (1024 byte space)

#define TWI_EEP_CSTM_STT		(96*TWI_EEP_BYTE_EA)		// Customer area

#define TWI_EEP_END				((TWI_EEP_PAGE_EA*TWI_EEP_BYTE_EA)-1)	// End of address


#define TWI_EEP_AWBPRST_STT		(64*TWI_EEP_BYTE_EA)		// AWB Preset data save pos
#define TWI_EEP_IRIS_STT		(65+TWI_EEP_BYTE_EA)		// IRIS data save pos
#define TWI_EEP_ZOOM_STT		(66+TWI_EEP_BYTE_EA)		// ZOOM data save pos

#endif//__LIB__



//******************************************************
// 6. TIMER
//------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// LMT = N
// PWM = 0 ~ N   TRG, 0 = Low, N = High, (TRG == N) -> IRQ has not occurred
// IRQ = 0 ~ N-1 TRG, (TRG == CNT) -> IRQ occurs
// CNT = 0 ~ N-1


// MCLK = IRQ_CLK          x IRQ_HZ x 2
//        LMT * (CLKDIV+1) x IRQ_HZ x 2
#define TIMERx_LIMIT			(0x61A8)//0xFFFF		// 0xffff ���� MCLK �ִ� �����?
#define TIMERx_CLKDIV			(0xE)//0xF			// (0xe+1) ���� MCLK �ִ� �����?
//#define TIMERx_IRQ_HZ			99					// ������ MCLK �ִ� �����?
#define TIMERx_IRQ_HZ			(198)				// ������ MCLK �ִ� �����?

#if (model_Lens==1)		// 2015923 - WHL
	#define TIMER1_LIMIT		(0x1D01)	//7425
//	#define TIMER1_CLKDIV		(0x4)
	#define TIMER1_CLKDIV		(0x9)		// 210826 HTY : 2-motor speed according to MCU clock speed
#endif

// 1sec = (IsrTimerCnt * (TIM_CHx_LMT     ) + TIM_CHx_CNT) * 2 / (MCLK / (TIM_CHx_DIV+1))
//        (IsrTimerCnt * (0xFFFF          ) + TIM_CHx_CNT) * 2 / (MCLK / (0xF        +1))
//        (IsrTimerCnt * (0x10000 - 1     ) + TIM_CHx_CNT) * 2 / (MCLK / 0x10)
//        (((IsrTimerCnt<<16) - IsrTimerCnt + TIM_CHx_CNT)<<1) / (MCLK>>4)
//         ((IsrTimerCnt<<16) - IsrTimerCnt + TIM_CHx_CNT)     / (MCLK>>(4+1))
#define TIMERtoSEC(IsrTimerCnt)		((IsrTimerCnt/TIMERx_IRQ_HZ)+1)

//#if 0//model_VT_Test == 1
//	#define TIMER1_LIMIT	0x3e8/*0x2ee*/	// 0x2ee = ��300us,  0x3e8 = ��400us,
//#endif


//******************************************************
// 7. SPI
//------------------------------------------------------
#define SPI0_CLKDIV				(SPI_CLKDIV16)				// MAX = SPI_CLKDIV64
#define SPI1_CLKDIV				(SPI_CLKDIV16)				// MAX = SPI_CLKDIV64


//******************************************************
// 8. IRQ
//------------------------------------------------------
#define	MANUAL_SYNC_FPS			( 60)

//******************************************************
// 9. FLASH
//------------------------------------------------------
#define FLASH_SECT_SHD_STT		(123)										// sect no. of Shading table
#define FLASH_SECT_MENU_STT		(124)										// sect no. of Menu Parameter (Roll1)
#define FLASH_SECT_MENU_EA		(  1)
#define FLASH_SECT_MENU_BKUP	(FLASH_SECT_MENU_STT+FLASH_SECT_MENU_EA)	// sect no. of Menu Parameter (Roll2)

#define FLASH_SECT_USER_STT		(FLASH_SECT_TOTAL_EA-2)						// sect no. of User parameter
#define FLASH_SECT_DATA_STT		(FLASH_SECT_TOTAL_EA-1)						// sect no. of Application data

#define FLASH_SECT_MENU_SET_STT	(121)										// sect no. of Menu Setting Parameter
#define FLASH_SECT_TEST_STT		(120) 										// sect no. of Application data

//******************************************************
// 10. WDT
//------------------------------------------------------
#define WDT_TIME				(4)		// limit time (sec)



//******************************************************
// 11. ISP
//------------------------------------------------------


//******************************************************
// 12. SENSOR
//------------------------------------------------------


//******************************************************
// 13. TEST
//------------------------------------------------------
BYTE gbEXUC_AgcFlag;

WORD gwFW_Ver;
WORD gwIQ_Ver;

//******************************************************
// 14. CUSTOM
//------------------------------------------------------
void ISPM2 CTX_Initial(UINT* DSdata);
void ISPM2 ModeChangeACP(void);

extern volatile BYTE gbUpstreamFlag;
extern BYTE gbSaveFlag;
extern BYTE gbReadFlag;

extern UINT gnAckData;
extern UINT gnTimAckData;

extern WORD gwAesum_sht;
extern BYTE gbAesum_agc;
extern BYTE gbAwb_light;

#endif//model_Sens

/* EOF */
