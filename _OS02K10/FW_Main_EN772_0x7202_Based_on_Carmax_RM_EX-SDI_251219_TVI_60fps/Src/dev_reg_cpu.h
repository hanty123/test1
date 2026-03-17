/* **************************************************************************
 File Name	: 	dev_reg_cpu.h
 Description:	OR - CPU Reg macro define
 Designer	:	Kim, Sunghoon
 Date		:	14. 1. 24
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */
/*
 INDEX	:
 		 1. BASE
		 2. UART
		 3. I2C
		 4. TIMER
		 5. SPI
		 6. IRQ
		 7. GPIO
		 8. FLASH
		 9. WDT
*/

//*************************************************************************************************
// DEV
//-------------------------------------------------------------------------------------------------
// Mem size
//#define FLS_SIZE				(16384*1024)			// Flash size (EN25F40)
	//#define USER_SIZE			(    4*1024)			// User data area size in internal flash
//#define RAM0_SIZE				(   64*1024)			// Main processor ram size (64KB)
//#define RAM1_SIZE				(   64*1024)			// Co   processor ram size (64KB)
//#define MSGBOX_SIZE 			(	64*1024)			// Message box size
//#define STACK_SIZE				(	64*1024)

//-------------------------------------------------------------------------------------------------
// Base address
#define FLS_BASE				0x01000000
#define SRAM_BASE				0x00000000

#define	SFLS_REG_BASE			0xf0000000

#define UART0_REG_BASE			0xf1000000
#define UART1_REG_BASE			0xf1000008

#define GPIO_REG_BASE			0xf2000000
#define I2C_REG_BASE			0xf3000000
#define SPI0_REG_BASE			0xf4000000
#define SPI1_REG_BASE			0xf5000000
#define TIMER_REG_BASE			0xf6000000
#define WDT_REG_BASE			0xf7000000
#define ISP_REG_BASE			0xf8000000

//-------------------------------------------------------------------------------------------------
// Extern
extern int cache_init(void);


//*************************************************************************************************
// UART
//-------------------------------------------------------------------------------------------------
// Bit field
_regs_	UINT _res		:16;
		UINT TX_DAT		: 8;
		UINT RX_DAT		: 8; _rege_  _UART_DAT;

_regs_	UINT CLKDIV		: 12;
		UINT _res		: 7;
		UINT STOP_BIT	: 1;
		UINT PARITY_EN	: 1;
		UINT PARITY_TYPE: 1;
		UINT TX_IRQ		: 1;
		UINT TX_IRQ_EN	: 1;
		UINT TX_IRQ_CLR	: 1;
		UINT TX_EMPTY	: 1;
		UINT TX_FULL	: 1;
		UINT RX_IRQ		: 1;
		UINT RX_IRQ_EN	: 1;
		UINT RX_IRQ_CLR	: 1;
		UINT RX_EMPTY	: 1;
		UINT RX_FULL	: 1; _rege_  _UART_CONT;


//-------------------------------------------------------------------------------------------------
// Addr/Bit macro
#define	UART0_CLKDIV		_bm(_UART_CONT, UART0_REG_BASE, 0x00, CLKDIV		)		//	RW
//#define UART_STOP_BIT		_bm(_UART_CONT, UART0_REG_BASE, 0x00, STOP_BIT		)		//	RW
//#define UART_PARITY_EN		_bm(_UART_CONT, UART0_REG_BASE, 0x00, PARITY_EN		)		//	RW
//#define UART_PARITY_TYPE	_bm(_UART_CONT, UART0_REG_BASE, 0x00, PARITY_TYPE	)		//	RW
#define	UART0_TX_IRQ		_bm(_UART_CONT, UART0_REG_BASE, 0x00, TX_IRQ		)		//	RO
#define	UART0_TX_IRQ_EN		_bm(_UART_CONT, UART0_REG_BASE, 0x00, TX_IRQ_EN		)		//	RW
//#define UART_TX_IRQ_CLR		_bm(_UART_CONT, UART0_REG_BASE, 0x00, TX_IRQ_CLR	)		//	WO
//#define UART_TX_EMPTY		_bm(_UART_CONT, UART0_REG_BASE, 0x00, TX_EMPTY		)		//	RO
#define	UART0_TX_FULL		_bm(_UART_CONT, UART0_REG_BASE, 0x00, TX_FULL		)		//	RO
#define	UART0_RX_IRQ		_bm(_UART_CONT, UART0_REG_BASE, 0x00, RX_IRQ		)		//	RO
#define	UART0_RX_IRQ_EN		_bm(_UART_CONT, UART0_REG_BASE, 0x00, RX_IRQ_EN		)		//	RW
#define	UART0_RX_IRQ_CLR	_bm(_UART_CONT, UART0_REG_BASE, 0x00, RX_IRQ_CLR	)		//	WO
#define	UART0_RX_EMPTY		_bm(_UART_CONT, UART0_REG_BASE, 0x00, RX_EMPTY		)		//	RO
//#define UART_RX_FULL		_bm(_UART_CONT, UART0_REG_BASE, 0x00, RX_FULL		)		//	RO
#define	UART0_TX_DAT		_bm(_UART_DAT , UART0_REG_BASE, 0x04, TX_DAT		)		//	WO
#define	UART0_RX_DAT		_bm(_UART_DAT , UART0_REG_BASE, 0x04, RX_DAT		)		//	WO


#define	UART1_CLKDIV		_bm(_UART_CONT, UART1_REG_BASE, 0x00, CLKDIV		)		//	RW
#define	UART1_TX_IRQ		_bm(_UART_CONT, UART1_REG_BASE, 0x00, TX_IRQ		)		//	RO
#define	UART1_TX_IRQ_EN		_bm(_UART_CONT, UART1_REG_BASE, 0x00, TX_IRQ_EN		)		//	RW
#define	UART1_TX_FULL		_bm(_UART_CONT, UART1_REG_BASE, 0x00, TX_FULL		)		//	RO
#define	UART1_RX_IRQ		_bm(_UART_CONT, UART1_REG_BASE, 0x00, RX_IRQ		)		//	RO
#define	UART1_RX_IRQ_EN		_bm(_UART_CONT, UART1_REG_BASE, 0x00, RX_IRQ_EN		)		//	RW
#define	UART1_RX_IRQ_CLR	_bm(_UART_CONT, UART1_REG_BASE, 0x00, RX_IRQ_CLR	)		//	WO
#define	UART1_RX_EMPTY		_bm(_UART_CONT, UART1_REG_BASE, 0x00, RX_EMPTY		)		//	RO
#define	UART1_TX_DAT		_bm(_UART_DAT , UART1_REG_BASE, 0x04, TX_DAT		)		//	WO
#define	UART1_RX_DAT		_bm(_UART_DAT , UART1_REG_BASE, 0x04, RX_DAT		)		//	WO

#define	UART_BAUD(baud)		((MCLK+(baud<<3)) / (baud<<4))
	#define	UB2400			UART_BAUD(2400)/*1934*/
	#define	UB4800			UART_BAUD(4800)/*967*/
	#define	UB9600			UART_BAUD(9600)/*483*/
	#define	UB19200			UART_BAUD(19200)/*242*/
	#define	UB38400			UART_BAUD(38400)/*121*/
	#define	UB57600			UART_BAUD(57600)/*81*/
	#define	UB115200		UART_BAUD(115200)/*40*/


//*************************************************************************************************
// I2C
//-------------------------------------------------------------------------------------------------
// Addr/Bit macro
_regs_  UINT RX_DAT			: 8;
		UINT TX_DAT			: 8;
		UINT _res0			: 5;
		UINT SYNC   		: 3;
		UINT _res1			: 2;
		UINT ACT			: 1;
		UINT MODE			: 1;
		UINT BIT_MODE		: 1;
		UINT IRQ			: 1;
		UINT IRQ_EN			: 1;
		UINT IRQ_CLR		: 1;	_rege_  _I2C_CONT;

_regs_  UINT CLK_DIV   		: 16;
        UINT _res3			: 10;
		UINT MST_COL		: 1;
		UINT MST_ACK		: 1;
		UINT MST_REPEAT		: 1;
		UINT MST_LAST		: 1;
		UINT MST_RW			: 1;
		UINT MST_GO			: 1;	_rege_  _I2C_CONT_MST;

_regs_  UINT _res4			: 17;
        UINT LAST_FLAG      : 1;
        UINT ADR_FLAG       : 1;
        UINT SLV_SDA        : 1;
        UINT SLV_SCL        : 1;
		UINT SLV_ACK_IN		: 1;
		UINT SLV_GO			: 1;
		UINT SLV_RW			: 1;
		UINT SLV_ACK_OUT	: 1;
		UINT SLV_ADR		: 7;	_rege_  _I2C_CONT_SLV;

#define I2C0_CONT			_am(_I2C_CONT		, I2C_REG_BASE, 0x0000				)
#define I2C0_RX_DAT			_bm(_I2C_CONT		, I2C_REG_BASE, 0x0000,	RX_DAT		)	//RW
#define I2C0_TX_DAT			_bm(_I2C_CONT		, I2C_REG_BASE, 0x0000,	TX_DAT		)	//RW
#define I2C0_SYNC			_bm(_I2C_CONT		, I2C_REG_BASE, 0x0000,	SYNC		)	//RW
#define I2C0_ACT			_bm(_I2C_CONT		, I2C_REG_BASE, 0x0000, ACT			)	//RO
#define I2C0_MODE			_bm(_I2C_CONT		, I2C_REG_BASE, 0x0000, MODE		)	//RW
#define I2C0_BIT_MODE		_bm(_I2C_CONT		, I2C_REG_BASE, 0x0000, BIT_MODE	)	//RW
#define I2C0_IRQ			_bm(_I2C_CONT		, I2C_REG_BASE, 0x0000, IRQ			)	//RO
#define I2C0_IRQ_EN			_bm(_I2C_CONT		, I2C_REG_BASE, 0x0000, IRQ_EN		)	//RW
#define I2C0_IRQ_CLR		_bm(_I2C_CONT		, I2C_REG_BASE, 0x0000, IRQ_CLR		)	//WO

#define I2C0_CONT_MST		_am(_I2C_CONT_MST	, I2C_REG_BASE, 0x0004				)
#define I2C0_CLK_DIV		_bm(_I2C_CONT_MST	, I2C_REG_BASE, 0x0004, CLK_DIV		)
#define I2C0_MST_COL		_bm(_I2C_CONT_MST	, I2C_REG_BASE, 0x0004, MST_COL		)
#define I2C0_MST_ACK		_bm(_I2C_CONT_MST	, I2C_REG_BASE, 0x0004, MST_ACK		)
#define I2C0_MST_REPEAT		_bm(_I2C_CONT_MST	, I2C_REG_BASE, 0x0004, MST_REPEAT	)	//RW
#define I2C0_MST_LAST		_bm(_I2C_CONT_MST	, I2C_REG_BASE, 0x0004, MST_LAST	)	//RW
#define I2C0_MST_RW			_bm(_I2C_CONT_MST	, I2C_REG_BASE, 0x0004, MST_RW		)	//RW
#define I2C0_MST_GO			_bm(_I2C_CONT_MST	, I2C_REG_BASE, 0x0004, MST_GO		)	//WO

#define I2C0_CONT_SLV		_am(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0008				)
#define I2C0_LAST_FLAG		_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0008, LAST_FLAG   )	
#define I2C0_ADR_FLAG		_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0008, ADR_FLAG	)	
#define I2C0_SLV_SDA		_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0008, SLV_SDA		)	
#define I2C0_SLV_SCL		_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0008,	SLV_SCL		)	
#define I2C0_SLV_GO			_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0008, SLV_GO		)	//WO
#define I2C0_SLV_RW			_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0008,	SLV_RW		)	//RO
#define I2C0_SLV_ACK_OUT	_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0008,	SLV_ACK_OUT	)	//RW
#define I2C0_SLV_ADR		_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0008,	SLV_ADR		)	//RW
#define I2C0_SLV_ACK_IN		_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0008,	SLV_ACK_IN	)	//RO

#define I2C1_CONT			_am(_I2C_CONT		, I2C_REG_BASE, 0x000c				)
#define I2C1_RX_DAT			_bm(_I2C_CONT		, I2C_REG_BASE, 0x000c,	RX_DAT		)	//RW
#define I2C1_TX_DAT			_bm(_I2C_CONT		, I2C_REG_BASE, 0x000c,	TX_DAT		)	//RW
#define I2C1_SYNC			_bm(_I2C_CONT		, I2C_REG_BASE, 0x000c,	SYNC		)	//RW
#define I2C1_ACT			_bm(_I2C_CONT		, I2C_REG_BASE, 0x000c, ACT			)	//RO
#define I2C1_MODE			_bm(_I2C_CONT		, I2C_REG_BASE, 0x000c, MODE		)	//RW
#define I2C1_BIT_MODE		_bm(_I2C_CONT		, I2C_REG_BASE, 0x000c, BIT_MODE	)	//RW
#define I2C1_IRQ			_bm(_I2C_CONT		, I2C_REG_BASE, 0x000c, IRQ			)	//RO
#define I2C1_IRQ_EN			_bm(_I2C_CONT		, I2C_REG_BASE, 0x000c, IRQ_EN		)	//RW
#define I2C1_IRQ_CLR		_bm(_I2C_CONT		, I2C_REG_BASE, 0x000c, IRQ_CLR		)	//WO

#define I2C1_CONT_MST		_am(_I2C_CONT_MST	, I2C_REG_BASE, 0x0010				)
#define I2C1_CLK_DIV		_bm(_I2C_CONT_MST	, I2C_REG_BASE, 0x0010, CLK_DIV		)
#define I2C1_MST_COL		_bm(_I2C_CONT_MST	, I2C_REG_BASE, 0x0010, MST_COL		)
#define I2C1_MST_ACK		_bm(_I2C_CONT_MST	, I2C_REG_BASE, 0x0010, MST_ACK		)
#define I2C1_MST_REPEAT		_bm(_I2C_CONT_MST	, I2C_REG_BASE, 0x0010, MST_REPEAT	)	//RW
#define I2C1_MST_LAST		_bm(_I2C_CONT_MST	, I2C_REG_BASE, 0x0010, MST_LAST	)	//RW
#define I2C1_MST_RW			_bm(_I2C_CONT_MST	, I2C_REG_BASE, 0x0010, MST_RW		)	//RW
#define I2C1_MST_GO			_bm(_I2C_CONT_MST	, I2C_REG_BASE, 0x0010, MST_GO		)	//WO

#define I2C1_CONT_SLV		_am(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0014				)
#define I2C1_LAST_FLAG		_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0014, LAST_FLAG   )	
#define I2C1_ADR_FLAG		_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0014, ADR_FLAG	)	
#define I2C1_SLV_SDA		_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0014, SLV_SDA		)	
#define I2C1_SLV_SCL		_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0014,	SLV_SCL		)	
#define I2C1_SLV_GO			_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0014, SLV_GO		)	//WO
#define I2C1_SLV_RW			_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0014,	SLV_RW		)	//RO
#define I2C1_SLV_ACK_OUT	_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0014,	SLV_ACK_OUT	)	//RW
#define I2C1_SLV_ADR		_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0014,	SLV_ADR		)	//RW
#define I2C1_SLV_ACK_IN		_bm(_I2C_CONT_SLV	, I2C_REG_BASE, 0x0014,	SLV_ACK_IN	)	//RO


// I2C Clock config
#define I2C_CLKDIV(DIV)			((DIV<<2)-1)

// I2C SCL Freq = MCLK / CLKDIV		ex) 148.5MHz / 32 = 4.64Mbps
#define I2C_CLKDIV32			1		// 4.64Mbps
#define I2C_CLKDIV64			2		// 2.32Mbps
#define I2C_CLKDIV96			3		// 1.54Mbps
#define I2C_CLKDIV128			4		// 1.16Mbps
#define I2C_CLKDIV160			5		// 928.125Kbps
#define I2C_CLKDIV192			6		// 773.437Kbps
#define I2C_CLKDIV224			7		// 662.946Kbps
#define I2C_CLKDIV256			8		// 580.078Kbps
#define I2C_CLKDIV288			9		// 515.625Kbps
#define I2C_CLKDIV320			10		// 464.062Kbps
#define I2C_CLKDIV352			11		// 421.875Kbps
#define I2C_CLKDIV384			12		// 386.718Kbps
#define I2C_CLKDIV416			13		// 356.971Kbps
#define I2C_CLKDIV448			14		// 331.473Kbps
#define I2C_CLKDIV480			15		// 309.375Kbps
#define I2C_CLKDIV512			16		// 290.039Kbps
#define I2C_CLKDIV832			26		// 178.485Kbps
#define I2C_CLKDIV1024			32		// 145.019Kbps
#define I2C_CLKDIV2048			64		//  72.509Kbps
#define I2C_CLKDIV8192			256		//  18.127Kbps


//*************************************************************************************************
// TIMER
//-------------------------------------------------------------------------------------------------
// Bit field
_regs_	UINT _res0		: 2;
		UINT CH0_EN		: 1;
		UINT CH1_EN		: 1;
		UINT CH2_EN		: 1;
		UINT CH3_EN		: 1;
		UINT CH4_EN		: 1;
		UINT CH5_EN		: 1;
		UINT _res1		: 2;
		UINT CH0_IRQ_EN	: 1;
		UINT CH1_IRQ_EN	: 1;
		UINT CH2_IRQ_EN	: 1;
		UINT CH3_IRQ_EN	: 1;
		UINT CH4_IRQ_EN	: 1;
		UINT CH5_IRQ_EN	: 1;
		UINT _res2		: 2;
		UINT CH0_IRQ_CLR : 1;
		UINT CH1_IRQ_CLR : 1;
		UINT CH2_IRQ_CLR : 1;
		UINT CH3_IRQ_CLR : 1;
		UINT CH4_IRQ_CLR : 1;
		UINT CH5_IRQ_CLR : 1;
		UINT _res3		: 2;
		UINT CH0_IRQ	: 1;
		UINT CH1_IRQ	: 1;
		UINT CH2_IRQ	: 1;
		UINT CH3_IRQ	: 1;
		UINT CH4_IRQ	: 1;
		UINT CH5_IRQ	: 1; _rege_  _TIM_CONT1;
_regs_	UINT _res0		: 2;
		UINT CH0_PWM_EN : 1;
		UINT CH1_PWM_EN : 1;
		UINT CH2_PWM_EN : 1;
		UINT CH3_PWM_EN : 1;
		UINT CH4_PWM_EN : 1;
		UINT CH5_PWM_EN : 1;
		UINT CH0_DIV	: 4;
		UINT CH1_DIV	: 4;
		UINT CH2_DIV	: 4;
		UINT CH3_DIV	: 4;
		UINT CH4_DIV	: 4;
		UINT CH5_DIV	: 4; _rege_  _TIM_CONT2;
_regs_	UINT CH0_LMT	: 16;
		UINT CH1_LMT 	: 16;_rege_  _TIM_LMT0;
_regs_	UINT CH2_LMT	: 16;
		UINT CH3_LMT 	: 16;_rege_  _TIM_LMT1;
_regs_	UINT CH4_LMT	: 16;
		UINT CH5_LMT 	: 16;_rege_  _TIM_LMT2;
_regs_	UINT CH0_TRIG	: 16;
		UINT CH1_TRIG 	: 16;_rege_  _TIM_TRIG0;
_regs_	UINT CH2_TRIG	: 16;
		UINT CH3_TRIG 	: 16;_rege_  _TIM_TRIG1;
_regs_	UINT CH4_TRIG	: 16;
		UINT CH5_TRIG 	: 16;_rege_  _TIM_TRIG2;
_regs_	UINT CH0_CNT	: 16;
		UINT CH1_CNT 	: 16;_rege_  _TIM_CNT0;
_regs_	UINT CH2_CNT	: 16;
		UINT CH3_CNT 	: 16;_rege_  _TIM_CNT1;
_regs_	UINT CH4_CNT	: 16;
		UINT CH5_CNT 	: 16;_rege_  _TIM_CNT2;
_regs_  UINT RXLMT      : 16;
        UINT RXDUTY     : 16;_rege_  _TIM_PWMRX;

//-------------------------------------------------------------------------------------------------
// Addr/Bit macro
#define	TIM_CH0_EN			_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH0_EN )		//RW
#define	TIM_CH1_EN			_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH1_EN )		//RW
#define	TIM_CH2_EN			_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH2_EN )		//RW
#define	TIM_CH3_EN			_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH3_EN )		//RW
#define	TIM_CH4_EN			_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH4_EN )		//RW
#define	TIM_CH5_EN			_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH5_EN )		//RW
#define	TIM_CH0_IRQ_EN		_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH0_IRQ_EN )	//RW
#define	TIM_CH1_IRQ_EN		_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH1_IRQ_EN )	//RW
#define	TIM_CH2_IRQ_EN		_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH2_IRQ_EN )	//RW
#define	TIM_CH3_IRQ_EN		_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH3_IRQ_EN )	//RW
#define	TIM_CH4_IRQ_EN		_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH4_IRQ_EN )	//RW
#define	TIM_CH5_IRQ_EN		_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH5_IRQ_EN )	//RW
#define	TIM_CH0_IRQ_CLR		_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH0_IRQ_CLR )//RW
#define	TIM_CH1_IRQ_CLR		_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH1_IRQ_CLR )//RW
#define	TIM_CH2_IRQ_CLR		_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH2_IRQ_CLR )//RW
#define	TIM_CH3_IRQ_CLR		_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH3_IRQ_CLR )//RW
#define	TIM_CH4_IRQ_CLR		_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH4_IRQ_CLR )//RW
#define	TIM_CH5_IRQ_CLR		_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH5_IRQ_CLR )//RW
#define	TIM_CH0_IRQ			_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH0_IRQ )	//RO
#define	TIM_CH1_IRQ			_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH1_IRQ )	//RO
#define	TIM_CH2_IRQ			_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH2_IRQ )	//RO
#define	TIM_CH3_IRQ			_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH3_IRQ )	//RO
#define	TIM_CH4_IRQ			_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH4_IRQ )	//RO
#define	TIM_CH5_IRQ			_bm(_TIM_CONT1 , TIMER_REG_BASE, 0x00, CH5_IRQ )	//RO
#define	TIM_CH0_PWM_EN		_bm(_TIM_CONT2 , TIMER_REG_BASE, 0x04, CH0_PWM_EN )	//RW
#define	TIM_CH1_PWM_EN		_bm(_TIM_CONT2 , TIMER_REG_BASE, 0x04, CH1_PWM_EN )	//RW
#define	TIM_CH2_PWM_EN		_bm(_TIM_CONT2 , TIMER_REG_BASE, 0x04, CH2_PWM_EN )	//RW
#define	TIM_CH3_PWM_EN		_bm(_TIM_CONT2 , TIMER_REG_BASE, 0x04, CH3_PWM_EN )	//RW
#define	TIM_CH4_PWM_EN		_bm(_TIM_CONT2 , TIMER_REG_BASE, 0x04, CH4_PWM_EN )	//RW
#define	TIM_CH5_PWM_EN		_bm(_TIM_CONT2 , TIMER_REG_BASE, 0x04, CH5_PWM_EN )	//RW
#define	TIM_CH0_DIV			_bm(_TIM_CONT2 , TIMER_REG_BASE, 0x04, CH0_DIV )	//RW
#define	TIM_CH1_DIV			_bm(_TIM_CONT2 , TIMER_REG_BASE, 0x04, CH1_DIV )	//RW
#define	TIM_CH2_DIV			_bm(_TIM_CONT2 , TIMER_REG_BASE, 0x04, CH2_DIV )	//RW
#define	TIM_CH3_DIV			_bm(_TIM_CONT2 , TIMER_REG_BASE, 0x04, CH3_DIV )	//RW
#define	TIM_CH4_DIV			_bm(_TIM_CONT2 , TIMER_REG_BASE, 0x04, CH4_DIV )	//RW
#define	TIM_CH5_DIV			_bm(_TIM_CONT2 , TIMER_REG_BASE, 0x04, CH5_DIV )	//RW
#define	TIM_CH0_LMT			_bm(_TIM_LMT0  , TIMER_REG_BASE, 0x08, CH0_LMT )	//RW
#define	TIM_CH1_LMT			_bm(_TIM_LMT0  , TIMER_REG_BASE, 0x08, CH1_LMT )	//RW
#define	TIM_CH2_LMT			_bm(_TIM_LMT1  , TIMER_REG_BASE, 0x0c, CH2_LMT )	//RW
#define	TIM_CH3_LMT			_bm(_TIM_LMT1  , TIMER_REG_BASE, 0x0c, CH3_LMT )	//RW
#define	TIM_CH4_LMT			_bm(_TIM_LMT2  , TIMER_REG_BASE, 0x10, CH4_LMT )	//RW
#define	TIM_CH5_LMT			_bm(_TIM_LMT2  , TIMER_REG_BASE, 0x10, CH5_LMT )	//RW
#define	TIM_CH0_TRIG		_bm(_TIM_TRIG0 , TIMER_REG_BASE, 0x14, CH0_TRIG )	//RW
#define	TIM_CH1_TRIG		_bm(_TIM_TRIG0 , TIMER_REG_BASE, 0x14, CH1_TRIG )	//RW
#define	TIM_CH2_TRIG		_bm(_TIM_TRIG1 , TIMER_REG_BASE, 0x18, CH2_TRIG )	//RW
#define	TIM_CH3_TRIG		_bm(_TIM_TRIG1 , TIMER_REG_BASE, 0x18, CH3_TRIG )	//RW
#define	TIM_CH4_TRIG		_bm(_TIM_TRIG2 , TIMER_REG_BASE, 0x1c, CH4_TRIG )	//RW
#define	TIM_CH5_TRIG		_bm(_TIM_TRIG2 , TIMER_REG_BASE, 0x1c, CH5_TRIG )	//RW
#define	TIM_CH0_CNT			_bm(_TIM_CNT0  , TIMER_REG_BASE, 0x20, CH0_CNT )	//RO
#define	TIM_CH1_CNT			_bm(_TIM_CNT0  , TIMER_REG_BASE, 0x20, CH1_CNT )	//RO
#define	TIM_CH2_CNT			_bm(_TIM_CNT1  , TIMER_REG_BASE, 0x24, CH2_CNT )	//RO
#define	TIM_CH3_CNT			_bm(_TIM_CNT1  , TIMER_REG_BASE, 0x24, CH3_CNT )	//RO
#define	TIM_CH4_CNT			_bm(_TIM_CNT2  , TIMER_REG_BASE, 0x28, CH4_CNT )	//RO
#define	TIM_CH5_CNT			_bm(_TIM_CNT2  , TIMER_REG_BASE, 0x28, CH5_CNT )	//RO
#define TIM_CH0_RXLMT       _bm(_TIM_PWMRX , TIMER_REG_BASE, 0x2c, RXLMT  )		//RO
#define TIM_CH0_RXDUTY      _bm(_TIM_PWMRX , TIMER_REG_BASE, 0x2c, RXDUTY )		//RO
#define TIM_CH1_RXLMT       _bm(_TIM_PWMRX , TIMER_REG_BASE, 0x30, RXLMT  )		//RO
#define TIM_CH1_RXDUTY      _bm(_TIM_PWMRX , TIMER_REG_BASE, 0x30, RXDUTY )		//RO
#define TIM_CH2_RXLMT       _bm(_TIM_PWMRX , TIMER_REG_BASE, 0x34, RXLMT  )		//RO
#define TIM_CH2_RXDUTY      _bm(_TIM_PWMRX , TIMER_REG_BASE, 0x34, RXDUTY )		//RO
#define TIM_CH3_RXLMT       _bm(_TIM_PWMRX , TIMER_REG_BASE, 0x38, RXLMT  )		//RO
#define TIM_CH3_RXDUTY      _bm(_TIM_PWMRX , TIMER_REG_BASE, 0x38, RXDUTY )		//RO
#define TIM_CH4_RXLMT       _bm(_TIM_PWMRX , TIMER_REG_BASE, 0x3c, RXLMT  )		//RO
#define TIM_CH4_RXDUTY      _bm(_TIM_PWMRX , TIMER_REG_BASE, 0x3c, RXDUTY )		//RO
#define TIM_CH5_RXLMT       _bm(_TIM_PWMRX , TIMER_REG_BASE, 0x40, RXLMT  )		//RO
#define TIM_CH5_RXDUTY      _bm(_TIM_PWMRX , TIMER_REG_BASE, 0x40, RXDUTY )		//RO


//*************************************************************************************************
// SPI
//-------------------------------------------------------------------------------------------------
// Bit field
_regs_  UINT RX_DAT			: 16;
		UINT TX_DAT		    : 16;	_rege_  _SPI_DAT;

_regs_	UINT _res0			: 16;
		UINT CLK_DIV		: 4;
		UINT _res1			: 1;
		UINT BIT_MODE		: 1;
		UINT SPI_CS			: 2;
		UINT IRQ			: 1;
		UINT IRQ_EN			: 1;
		UINT IRQ_CLI		: 1;
		UINT CMD_MODE		: 2;
		UINT CMD_WS			: 1;
		UINT CMD_RW			: 1;
		UINT CMD_GO		    : 1;	_rege_  _SPI_CONT;


//-------------------------------------------------------------------------------------------------
// Addr/Bit macro
#define SPI0_RX_DAT		_bm(_SPI_DAT		, SPI0_REG_BASE, 0x0000, RX_DAT		)	//RO
#define SPI0_TX_DAT		_bm(_SPI_DAT		, SPI0_REG_BASE, 0x0000, TX_DAT		)	//RW

#define SPI0_SPI_CONT	_am(_SPI_CONT		, SPI0_REG_BASE, 0x0004				)
#define SPI0_CLK_DIV	_bm(_SPI_CONT		, SPI0_REG_BASE, 0x0004, CLK_DIV	)	//RW
#define SPI0_BIT_MODE	_bm(_SPI_CONT		, SPI0_REG_BASE, 0x0004, BIT_MODE	)	//RW
#define SPI0_SPI_CS		_bm(_SPI_CONT		, SPI0_REG_BASE, 0x0004, SPI_CS		)	//RW
#define SPI0_IRQ		_bm(_SPI_CONT		, SPI0_REG_BASE, 0x0004, IRQ		)	//RO
#define SPI0_IRQ_EN		_bm(_SPI_CONT		, SPI0_REG_BASE, 0x0004, IRQ_EN		)	//RW
#define SPI0_IRQ_CLI	_bm(_SPI_CONT		, SPI0_REG_BASE, 0x0004, IRQ_CLI	)	//RO
#define SPI0_CMD_MODE	_bm(_SPI_CONT		, SPI0_REG_BASE, 0x0004, CMD_MODE	)	//RW
#define SPI0_CMD_WS		_bm(_SPI_CONT		, SPI0_REG_BASE, 0x0004, CMD_WS		)	//RW
#define SPI0_CMD_RW		_bm(_SPI_CONT		, SPI0_REG_BASE, 0x0004, CMD_RW		)	//RW
#define SPI0_CMD_GO		_bm(_SPI_CONT		, SPI0_REG_BASE, 0x0004, CMD_GO		)	//RW

#define SPI1_RX_DAT		_bm(_SPI_DAT		, SPI1_REG_BASE, 0x0000, RX_DAT		)	//RO
#define SPI1_TX_DAT		_bm(_SPI_DAT		, SPI1_REG_BASE, 0x0000, TX_DAT		)	//RW

#define SPI1_SPI_CONT	_am(_SPI_CONT		, SPI1_REG_BASE, 0x0004				)
#define SPI1_CLK_DIV	_bm(_SPI_CONT		, SPI1_REG_BASE, 0x0004, CLK_DIV	)	//RW
#define SPI1_BIT_MODE	_bm(_SPI_CONT		, SPI1_REG_BASE, 0x0004, BIT_MODE	)	//RW
#define SPI1_SPI_CS		_bm(_SPI_CONT		, SPI1_REG_BASE, 0x0004, SPI_CS		)	//RW
#define SPI1_IRQ		_bm(_SPI_CONT		, SPI1_REG_BASE, 0x0004, IRQ		)	//RO
#define SPI1_IRQ_EN		_bm(_SPI_CONT		, SPI1_REG_BASE, 0x0004, IRQ_EN		)	//RW
#define SPI1_IRQ_CLI	_bm(_SPI_CONT		, SPI1_REG_BASE, 0x0004, IRQ_CLI	)	//RO
#define SPI1_CMD_MODE	_bm(_SPI_CONT		, SPI1_REG_BASE, 0x0004, CMD_MODE	)	//RW
#define SPI1_CMD_WS		_bm(_SPI_CONT		, SPI1_REG_BASE, 0x0004, CMD_WS		)	//RW
#define SPI1_CMD_RW		_bm(_SPI_CONT		, SPI1_REG_BASE, 0x0004, CMD_RW		)	//RW
#define SPI1_CMD_GO		_bm(_SPI_CONT		, SPI1_REG_BASE, 0x0004, CMD_GO		)	//RW

// Values
#define SPI_CLKDIV4			0
#define SPI_CLKDIV8			1
#define SPI_CLKDIV12		2
#define SPI_CLKDIV16		3
#define SPI_CLKDIV20		4
#define SPI_CLKDIV24		5
#define SPI_CLKDIV28		6
#define SPI_CLKDIV32		7
#define SPI_CLKDIV36		8
#define SPI_CLKDIV40		9
#define SPI_CLKDIV44		10
#define SPI_CLKDIV48		11
#define SPI_CLKDIV52		12
#define SPI_CLKDIV56		13
#define SPI_CLKDIV60		14
#define SPI_CLKDIV64		15

#define SPI_MSB				0
#define SPI_LSB				1
#define SPI_START_LOW		0
#define SPI_START_HIGH		1
#define SPI_EDGE_RISING		0
#define SPI_EDGE_FALLING	1
#define SPI_BIT_BYTE		0
#define SPI_BIT_WORD		1

// Macro
#define SPI0_SET(CLKDIV,START/*,EDGE*/)	\
	SPI0_SPI_CONT = (CLKDIV<<12) | (START<<4) /*| (EDGE<<3)*/

#define SPI1_SET(CLKDIV,START/*,EDGE*/)	\
	SPI1_SPI_CONT = (CLKDIV<<12) | (START<<4) /*| (EDGE<<3)*/

#define SPI1_END(NUM)	SPI1_SPI_CONT |= (1<<(NUM+8))	// SPI1_SPI_CS:NUM = 1(HIGH)
#define SPI1_START(NUM)	SPI1_SPI_CONT &= (~1<<(NUM+8))	// SPI1_SPI_CS:NUM = 0(LOW)


//*************************************************************************************************
// IRQ
//-------------------------------------------------------------------------------------------------
#define	IRQ_ISP					 2						// Irq number
//#define	IRQ_SFLS			 3						//		"
#define	IRQ_TIMER				 4						//		"
#define	IRQ_UART				 5						//		"
#define	IRQ_GPIO				 6						//		"
#define	IRQ_I2C				 	 7						//		"
//#define	IRQ_SPI0			 8						//		"
//#define	IRQ_SPI1			 9						//		"


#ifndef __LIB__

#define DI(ID)	UINT nStNum_##ID;\
				const UINT nSt_##ID = GetSt(&nStNum_##ID);	/* Don't Use Groble Variable !!!*/\
				SetStDisIrq(nSt_##ID)

#define EI(ID)	SetSt(nSt_##ID, &nStNum_##ID)

#endif


//*************************************************************************************************
// GPIO
//-------------------------------------------------------------------------------------------------
_regs_					_rege_  _GPIO;

// Addr/Bit macro
#define	GPIO_I			_am(_GPIO , GPIO_REG_BASE, 0x00) 			//
#define	GPIO_O			_am(_GPIO , GPIO_REG_BASE, 0x04) 			//
#define	GPIO_OE			_am(_GPIO , GPIO_REG_BASE, 0x08) 			//
#define	GPIO_EDGE_DIR	_am(_GPIO , GPIO_REG_BASE, 0x0c) 			//
#define	GPIO_IRQ_EN		_am(_GPIO , GPIO_REG_BASE, 0x10) 			//
#define	GPIO_IRQ_CLR	_am(_GPIO , GPIO_REG_BASE, 0x14) 			//
#define	GPIO_IRQ		_am(_GPIO , GPIO_REG_BASE, 0x18) 			//
#define	GPIO_PU_EN		_am(_GPIO , GPIO_REG_BASE, 0x1c) 			//
#define	GPIO_MUX		_am(_GPIO , GPIO_REG_BASE, 0x20) 			//

#define GPIO_NUM	20

//enum
enum{GPIO00,GPIO01,GPIO02,GPIO03,GPIO04,GPIO05,GPIO06,GPIO07,GPIO08,GPIO09,GPIO10,GPIO11,GPIO12,GPIO13,GPIO14,GPIO15,GPIO16,GPIO17,GPIO18,GPIO19};

// GPIO Control Macro
#define GpioEi(SEL)				GPIO_IRQ_EN |= (0x00000001L<<SEL)
#define GpioDi(SEL)				GPIO_IRQ_EN &= ~(0x00000001L<<SEL)
#define GpioRiseEdge(SEL)		GPIO_EDGE_DIR |= (0x00000001L<<SEL)
#define GpioFallEdge(SEL)		GPIO_EDGE_DIR &= ~(0x00000001L<<SEL)
#define GpioOutDir(SEL)			GPIO_OE |= (0x00000001L<<SEL)
#define GpioInDir(SEL)			GPIO_OE &= ~(0x00000001L<<SEL)
#define GpioSetHi(SEL)			GPIO_O |=  (0x00000001L << SEL)
#define GpioSetLo(SEL)			GPIO_O &= ~(0x00000001L << SEL)
#define GpioGetPin(SEL)			((BYTE)((GPIO_I & (0x00000001L<<SEL)) >> SEL))
#define GpioPullUpEn(SEL)		GPIO_PU_EN |= (0x00000001L<<SEL)
#define GpioPullUpDis(SEL)		GPIO_PU_EN &= ~(0x00000001L<<SEL)

//*************************************************************************************************
// FLASH
//-------------------------------------------------------------------------------------------------
// Bit field
_regs_ 						  _rege_  _SFLS_DATIN;
_regs_ 						  _rege_  _SFLS_DATOUT;

_regs_  UINT _res0			: 16;
		UINT WB_RDCMD		: 8;
		UINT WB_WRCMD	    : 8;	_rege_  _SFLS_WBCMD;

_regs_  UINT _res0			: 9;
		UINT WB_WR_EN		: 1;
		UINT WB_WAIT_EN		: 1;
		UINT WB_GAP_EN		: 1;
		UINT WB_GAP_LEN		: 2;
		UINT WB_RDCMD_IOM	: 2;
		UINT WB_RDADR_IOM	: 2;
		UINT WB_RDDAT_IOM	: 2;
		UINT WB_WREN_IOM	: 2;
		UINT WB_WRCMD_IOM	: 2;
		UINT WB_WRADR_IOM	: 2;
		UINT WB_WRDAT_IOM	: 2;
		UINT WB_WAITCMD_IOM	: 2;
		UINT WB_WAITDAT_IOM	: 2;	_rege_  _SFLS_WBCONT;

_regs_  UINT REG_CMD    	: 8;
		UINT REG_ADR    	: 24;	_rege_  _SFLS_CMDADR;

_regs_  UINT CLKDIV			: 4;
		UINT _res0			: 10;
		UINT REG_REQ	    : 1;
		UINT WB_REQ			: 1;

		UINT _res1			: 1;
		UINT REG_ADR_EN		: 1;
		UINT REG_GAP_EN	    : 1;
		UINT REG_DAT_EN	    : 1;

		UINT REG_WAIT_EN    : 1;
		UINT REG_DAT_RW	    : 1;
		UINT REG_CMD_IOM    : 2;

		UINT REG_ADR_IOM    : 2;
		UINT REG_DAT_IOM    : 2;
		UINT REG_GAP_LEN    : 2;
		UINT REG_DAT_LEN    : 2;	_rege_  _SFLS_CMD;

//-------------------------------------------------------------------------------------------------
// Addr/Bit macro
#define SFLS_DATIN			_am(_SFLS_DATIN		, SFLS_REG_BASE, 0x0000					)	//RW
#define SFLS_DATOUT			_am(_SFLS_DATOUT	, SFLS_REG_BASE, 0x0004					)	//RW

#define SFLS_WB_RDCMD		_bm(_SFLS_WBCMD		, SFLS_REG_BASE, 0x0008, WB_RDCMD		)	//RW
#define SFLS_WB_WRCMD		_bm(_SFLS_WBCMD		, SFLS_REG_BASE, 0x0008, WB_WRCMD		)	//RW

#define SFLS_WBCONT			_am(_SFLS_WBCONT	, SFLS_REG_BASE, 0x000C					)	//RW
#define SFLS_WB_WR_EN		_bm(_SFLS_WBCONT	, SFLS_REG_BASE, 0x000C, WB_WR_EN		)	//RW
#define SFLS_WB_WAIT_EN		_bm(_SFLS_WBCONT	, SFLS_REG_BASE, 0x000C, WB_WAIT_EN		)	//RW
#define SFLS_WB_GAP_EN		_bm(_SFLS_WBCONT	, SFLS_REG_BASE, 0x000C, WB_GAP_EN		)	//RW
#define SFLS_WB_GAP_LEN		_bm(_SFLS_WBCONT	, SFLS_REG_BASE, 0x000C, WB_GAP_LEN		)	//RW
#define SFLS_WB_RDCMD_IOM	_bm(_SFLS_WBCONT	, SFLS_REG_BASE, 0x000C, WB_RDCMD_IOM	)	//RW
#define SFLS_WB_RDADR_IOM	_bm(_SFLS_WBCONT	, SFLS_REG_BASE, 0x000C, WB_RDADR_IOM	)	//RW
#define SFLS_WB_RDDAT_IOM	_bm(_SFLS_WBCONT	, SFLS_REG_BASE, 0x000C, WB_RDDAT_IOM	)	//RW
#define SFLS_WB_WREN_IOM	_bm(_SFLS_WBCONT	, SFLS_REG_BASE, 0x000C, WB_WREN_IOM	)	//RW
#define SFLS_WB_WRCMD_IOM	_bm(_SFLS_WBCONT	, SFLS_REG_BASE, 0x000C, WB_WRCMD_IOM	)	//RW
#define SFLS_WB_WRADR_IOM	_bm(_SFLS_WBCONT	, SFLS_REG_BASE, 0x000C, WB_WRADR_IOM	)	//RW
#define SFLS_WB_WRDAT_IOM	_bm(_SFLS_WBCONT	, SFLS_REG_BASE, 0x000C, WB_WRDAT_IOM	)	//RW
#define SFLS_WB_WAITCMD_IOM	_bm(_SFLS_WBCONT	, SFLS_REG_BASE, 0x000C, WB_WAITCMD_IOM	)	//RW
#define SFLS_WB_WAITDAT_IOM	_bm(_SFLS_WBCONT	, SFLS_REG_BASE, 0x000C, WB_WAITDAT_IOM	)	//RW

#define SFLS_REG_CMD		_bm(_SFLS_CMDADR	, SFLS_REG_BASE, 0x0010, REG_CMD		)	//RW
#define SFLS_REG_ADR		_bm(_SFLS_CMDADR	, SFLS_REG_BASE, 0x0010, REG_ADR		)	//RW

#define SFLS_CMD		    _am(_SFLS_CMD		, SFLS_REG_BASE, 0x0014					)	//RW
#define SFLS_CLKDIV			_bm(_SFLS_CMD		, SFLS_REG_BASE, 0x0014, CLKDIV			)	//RW
#define SFLS_REG_REQ		_bm(_SFLS_CMD		, SFLS_REG_BASE, 0x0014, REG_REQ		)	//RW
#define SFLS_REG_WB_REQ		_bm(_SFLS_CMD		, SFLS_REG_BASE, 0x0014, WB_REQ			)	//RW
#define SFLS_REG_ADR_EN	    _bm(_SFLS_CMD		, SFLS_REG_BASE, 0x0014, REG_ADR_EN		)	//RW
#define SFLS_REG_GAP_EN	    _bm(_SFLS_CMD		, SFLS_REG_BASE, 0x0014, REG_GAP_EN		)	//RW
#define SFLS_REG_DAT_EN	    _bm(_SFLS_CMD		, SFLS_REG_BASE, 0x0014, REG_DAT_EN		)	//RW
#define SFLS_REG_WAIT_EN	_bm(_SFLS_CMD		, SFLS_REG_BASE, 0x0014, REG_WAIT_EN	)	//RW
#define SFLS_REG_CMD_IOM	_bm(_SFLS_CMD		, SFLS_REG_BASE, 0x0014, REG_CMD_IOM	)	//RW
#define SFLS_REG_ADR_IOM	_bm(_SFLS_CMD		, SFLS_REG_BASE, 0x0014, REG_ADR_IOM	)	//RW
#define SFLS_REG_DAT_IOM	_bm(_SFLS_CMD		, SFLS_REG_BASE, 0x0014, REG_DAT_IOM	)	//RW
#define SFLS_REG_GAP_LEN	_bm(_SFLS_CMD		, SFLS_REG_BASE, 0x0014, REG_GAP_LEN	)	//RW
#define SFLS_REG_DAT_LEN	_bm(_SFLS_CMD		, SFLS_REG_BASE, 0x0014, REG_DAT_LEN	)	//RW
#define SFLS_REG_DAT_RW	    _bm(_SFLS_CMD		, SFLS_REG_BASE, 0x0014, REG_DAT_RW		)	//RW


// Flash Controller
enum { Req0, Req1 };
enum { WbReq0, WbReq1 };
enum { AdrEn0, AdrEn1 };
enum { GapEn0, GapEn1 };
enum { DatEn0, DatEn1 };
enum { WaitEn0, WaitEn1 };
enum { DatR, DatW };
enum { CmdIomS, CmdIomD, CmdIomQ };
enum { AdrIomS, AdrIomD, AdrIomQ };
enum { DatIomS, DatIomD, DatIomQ };
enum { GapLen0, GapLen1, GapLen2, GapLen3 };
enum { DatLen0, DatLen1, DatLen2, DatLen3 };

#define CmdIomA		gbSFLS_WB_RDCMD_IOM
#define AdrIomA		gbSFLS_WB_RDCMD_IOM
#define DatIomA		gbSFLS_WB_RDCMD_IOM

#define SFLS_CMD_SET(Req, WbReq, AdrEn, GapEn, DatEn, WaitEn, DatRw, CmdIom, AdrIom, DatIom, GapLen, DatLen) \
		((SFLS_CMD&0xF01C0000) | (Req<<17) | (WbReq<<16) | (AdrEn<<14) | (GapEn<<13) | (DatEn<<12) | (WaitEn<<11)\
							   | (DatRw<<10) | (CmdIom<<8) | (AdrIom<<6) | (DatIom<<4) | (GapLen<<2) | (DatLen<<0))

#define SFLS_CMD_GO(Req, WbReq, AdrEn, GapEn, DatEn, WaitEn, DatRw, CmdIom, AdrIom, DatIom, GapLen, DatLen)	{\
		SFLS_CMD = SFLS_CMD_SET(Req, WbReq, AdrEn, GapEn, DatEn, WaitEn, DatRw, CmdIom, AdrIom, DatIom, GapLen, DatLen);\
		while(SFLS_REG_REQ);}

#define SFLS_BP_SET(BP3,BP2,BP1,BP0)	sfls_write_reg( (BP3<<5) | (BP2<<4) | (BP1<<3) | (BP0<<2) )

// Write Protection
#if (model_Protect==1) && ((model_Flash==0)||(model_Flash==1)) // 170512 KSH
	#define SfWrEn		{ SFLS_WB_WR_EN = 1; SFLS_BP_SET(0,0,0,0); gbSF_Status = sfls_read_reg(); }
	#define SfWrDis		{ SFLS_WB_WR_EN = 0; SFLS_BP_SET(1,1,1,1); gbSF_Status = sfls_read_reg(); }
	#define SfWrInit	SfWrDis
#else
	#define SfWrEn		{ SFLS_WB_WR_EN = 1; }
	#define SfWrDis		{ SFLS_WB_WR_EN = 0; }
	#define SfWrInit	{ SFLS_WB_WR_EN = 0; SFLS_BP_SET(0,0,0,0); gbSF_Status = sfls_read_reg(); }
#endif

// Flash memory configuration
#define FLASH_ADDR_MASK			0x00FFFFFF		// Flash controller address masking up to 16Mbyte
#define FLASH_TOTAL_SIZE		(512*1024)		// 4M-bit : (4*1024)/8 =  512Kbyte
#define FLASH_SECT_SIZE			(4*1024)		// Sector : 4Kbyte
#define FLASH_SECT_TOTAL_EA		(128)			// 512Kbyte / 4Kbyte = 128sector

enum {
	FLASH_MENU_MODE,
	FLASH_USER_MODE,
	FLASH_DATA_MODE,
	FLASH_MENU_SET_MODE
};


//*************************************************************************************************
// WDT
//-------------------------------------------------------------------------------------------------
// Bit field
_regs_						_rege_  _WDT_LMT;
_regs_						_rege_  _WDT_CNT;
_regs_	UINT _res		:30;
		UINT CNT_RST	: 1;
		UINT CNT_EN		: 1;_rege_  _WDT_CONT;

//-------------------------------------------------------------------------------------------------
// Addr/Bit macro
#define	WDT_CNT_LMT		_am(_WDT_LMT  , WDT_REG_BASE, 0x00)				//
#define	WDT_CNT_VAL		_am(_WDT_CNT  , WDT_REG_BASE, 0x04)				//
#define	WDT_CNT_RST	    _bm(_WDT_CONT , WDT_REG_BASE, 0x08, CNT_RST	)	//
#define	WDT_CNT_EN		_bm(_WDT_CONT , WDT_REG_BASE, 0x08, CNT_EN	)	//

#define WdtEna			WDT_CNT_EN = 1
#define WdtDis			WDT_CNT_EN = 0
#define WdtRst			WDT_CNT_RST = 1


