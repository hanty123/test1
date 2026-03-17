/* **************************************************************************
 File Name	: 	dev_gpio.c
 Description:	EN772 - GPIO device driver
 Designer	:	Kim, Sunghoon
 Modifier	:	Lee, Gyu Hong
 Date		:	20. 12. 01
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

//****************************************************************************
// GPIO MUX setting
//****************************************************************************
void InitGpio(void)
{	// GPIO Pin mux
//	GPIO_PU_EN = 0xFFFFF;

// Common GPIO
// GPIO00, GPIO01, GPIO02 -----------------------------------
// Fixed configuration !!
	L_I2C_ONw(0x0);					// Logic I2C off
	
	//Sensor Only MCU I2C
	R_I2C0_ONw(0x1);
									// GPIO00 - I2C0-CK
									// GPIO01 - I2C0-DA
	GpioOutDir(GPIO_SRSTN); 		// GPIO02 - SRSTN

// GPIO05, GPIO06 -----------------------------------
	LSPI_ONw(0x0);					// Logic SPI off
	R_URT0_ONw(0x3);				// [0] : RX, [1] : TX
									// GPIO05 : RXD0
									// GPIO06 : TXD0

// GPIO08, GPIO09-----------------------------------
// UART2 > I2C1 > UccD
#if(model_Uart2)
	DUCC_MUXw(0x0);					// GPIO08,09  - UART1
	R_URT1_ONw(0x3);				// [0] : RX, [1] : TX
	R_I2C1_ONw(0x0);
	
#elif(model_I2C_ch1)
	DUCC_MUXw(0x0);					// GPIO08,09  - I2C ch1
	R_URT1_ONw(0x0);
	R_I2C1_ONw(0x1);

#elif(model_UccD)
	DUCC_MUXw(0x2);					// GPIO08 - UCC, GPIO09 - GPIO I/O
	R_URT1_ONw(0x0);				
	R_I2C1_ONw(0x0);
	
#else
	DUCC_MUXw(0x0);					// GPIO08,09 - GPIO I/O
	R_URT1_ONw(0x0);
	R_I2C1_ONw(0x0);

	#if(model_Cds)
	GpioInDir(GPIO_CDS_IN); 		// GPIO08 - CDS-IN
	#endif	
#endif

#if(model_Isp_pkg68)

// GPIO03, GPIO04 -----------------------------------
#if(model_Sens_Slave)
	SVSO_OEw(0x1);					// GPIO03 - ISP Master Mode only (VSO)
	SHSO_OEw(0x1);					// GPIO04 - ISP Master Mode only (HSO)
#else
	SVSO_OEw(0x0);					// GPIO03 - GPIO I/O
	SHSO_OEw(0x0);					// GPIO04 - GPIO I/O
#endif

// GPIO07, GPIO09, GPIO10, GPIO11 -------------------------------------------
#if(model_Iris)
	R_PWM_ONw(0x1);					// GPIO07 - IRIS PWM
#else
	R_PWM_ONw(0x0);					// GPIO07 - GPIO I/O
#endif

#if(model_Tdn==2)
	GpioOutDir(GPIO_TDN_1); 		// GPIO09 - TDN1
	GpioOutDir(GPIO_TDN_2); 		// GPIO10 - TDN2
#endif
	
#if ((model_Led==0)||(model_Led==2))
	IRIS2_MUXw(0x1);				// GPIO11 - IR-LED (LPWM)
#elif(model_Led==1)
	IRIS2_MUXw(0x0);	
	GpioOutDir(GPIO_LED_CTL); 		// GPIO11 - IR-LED (GPIO)
#else
	IRIS2_MUXw(0x0);				// GPIO11 - GPIO I/O
#endif
	
// GPIO12, GPIO13, GPIO14, GPIO15, GPIO16, GPIO17, GPIO18, GPIO19 -------------------------------------------
	R_SPI_ONw(0x0);

	#if (model_Lens==1)
	GpioOutDir(GPIO_MTR_FCS_AP	);	// GPIO12 - MOTOR_Focus_A+
	GpioOutDir(GPIO_MTR_FCS_AM	);  // GPIO13 - MOTOR_Focus_A-
	GpioOutDir(GPIO_MTR_FCS_BP	);  // GPIO14 - MOTOR_Focus_B+
	GpioOutDir(GPIO_MTR_FCS_BM	);  // GPIO15 - MOTOR_Focus_B-
	
	GpioOutDir(GPIO_MTR_ZOOM_AP	);  // GPIO16 - MOTOR_Zoom_A+
	GpioOutDir(GPIO_MTR_ZOOM_AM	);  // GPIO17 - MOTOR_Zoom_A-
	GpioOutDir(GPIO_MTR_ZOOM_BP	);  // GPIO18 - MOTOR_Zoom_B+
	GpioOutDir(GPIO_MTR_ZOOM_BM	);  // GPIO19 - MOTOR_Zoom_B-
	#endif
	
	#if(model_ModeLed)
	GpioOutDir(GPIO_MODE_LED );	// GPIO18 - LED Control
	#endif
#endif

}


//*************************************************************************************************
// GPIO Interrupt service routine
//-------------------------------------------------------------------------------------------------
//
volatile UINT gnIsrGpio = 0;

void ISPM0 IsrGpio(void)		// CAUTION!!! - Isr stack size = 0x400, Do not use a lot of variables.
{
	int		i;

	for(i=0; i<GPIO_NUM; i++)
	{
		if( GPIO_IRQ & (0x00000001L << i) )
		{
			GPIO_IRQ_CLR = (0x00000001L << i);						// Irq clear
			gnIsrGpio++;
		}
	}
}

