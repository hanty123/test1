/* **************************************************************************
 File Name	: 	dev_misc.h
 Description:	EN772 - miscellaneous define
 Designer	:	Lee, Hoon
 Modifier	 :	 Lee, Gyu Hong
 Date		:	16. 8. 12
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

// CAUTION !! Don't modify the code without support

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
// System definition
#define		model_1M			((model_Sens>=10)&&(model_Sens<20))
#define		model_2M_L			((model_Sens>=20)&&(model_Sens<30))
#define		model_2M_H			((model_Sens>=30)&&(model_Sens<40))
#define		model_2M			((model_2M_L)||(model_2M_H))
#define		model_5M			((model_Sens>=50)&&(model_Sens<60))

// SENSOR
#define		model_Sony			((model_Sens==SENS_IMX225)||(model_Sens==SENS_IMX224)||\
								(model_Sens==SENS_IMX290)||(model_Sens==SENS_IMX327)||(model_Sens==SENS_IMX307)||(model_Sens==SENS_IMX462)||(model_Sens==SENS_IMX662)||(model_Sens==SENS_IMX390)||\
								(model_Sens==SENS_IMX335)||(model_Sens==SENS_IMX675))
#define		model_Onsemi		((model_Sens==SENS_AR0233))
#define		model_Omni			((model_Sens==SENS_OX03C10)||(model_Sens==SENS_OS02H10)||(model_Sens==SENS_OS04C10)||(model_Sens==SENS_OS02K10))
#define		model_Pxpls			((model_Sens==SENS_PS6210K))
#define		model_Glxcore		((model_Sens==SENS_GC2053)||(model_Sens==SENS_GC2093))
#define		model_SmartSens		((model_Sens==SENS_SC500AI)||(model_Sens==SENS_SC200AI))
#define		model_Pana			(0)


#define		model_Sens_LWdr		((model_Sens==SENS_IMX224)||(model_Sens==SENS_IMX290)||(model_Sens==SENS_IMX327)||(model_Sens==SENS_IMX307)||(model_Sens==SENS_IMX462)||(model_Sens==SENS_IMX662)||(model_Sens==SENS_GC2093)||(model_Sens==SENS_SC200AI)||\
								(model_Sens==SENS_IMX335)||(model_Sens==SENS_IMX675)||(model_Sens==SENS_SC500AI)||(model_Sens==SENS_OS02H10)||(model_Sens==SENS_OS04C10)||(model_Sens==SENS_OS02K10))

#define		model_Sens_CLR_HDR	((model_Sens==SENS_IMX662)||(model_Sens==SENS_IMX675)||(model_Sens==SENS_OS02K10))
#define		model_Sens_Comp_HDR	((model_Sens==SENS_AR0233)||(model_Sens==SENS_OX03C10)||(model_Sens==SENS_OS02K10))
								
#define		model_Sens_LFM_HDR	((model_Sens==SENS_IMX390)||(model_Sens==SENS_AR0233)||(model_Sens==SENS_OX03C10))

#define		model_Sens_LWdr_Low	((model_Sens_LWdr)&&((model_Sens==SENS_IMX327)||(model_Sens==SENS_IMX307)||(model_Sens==SENS_IMX662)||(model_Sens==SENS_GC2093)||(model_Sens==SENS_OS02H10)||(model_Sens==SENS_OS02K10)))
#define		model_Sens_NonWdr	((model_Sens==SENS_GC2053)||(model_Sens==SENS_PS6210K))
#define		model_Sens_US2Mto5M ((model_Sens==SENS_IMX290)||(model_Sens==SENS_IMX327)||(model_Sens==SENS_IMX307)||(model_Sens==SENS_IMX462))			// Upscale 2M to 5M resolution
#define		model_Sens_FpsL		((model_Sens==SENS_GC2053)||(model_Sens==SENS_PS6210K))
#define		model_Sens_CVBS		((model_Sens==SENS_IMX290)||(model_Sens==SENS_IMX327)||(model_Sens==SENS_IMX307)||(model_Sens==SENS_IMX462)||(model_Sens==SENS_IMX662))
#define		model_Sens_Slave	((model_Sens==SENS_IMX335)/*||(model_Sens==SENS_IMX675)*/)																								// Sensor Slave Mode
#define		model_Sens_VTW_1250	((model_Sens==SENS_OX03C10))

#if(model_5M)
#define		model_Sens_Upto4M	((model_Sens==SENS_SC500AI)||(model_Sens==SENS_OS04C10))
#define		model_Sens_5M_805	(/*((model_Isp==ISP_EN805)||(model_Isp==ISP_EN805M))&&((model_Sens==SENS_IMX335)||(model_Sens==SENS_IMX675))*/0)
#endif

#define		model_Sens_H_Sens	((model_Sens==SENS_IMX225)||(model_Sens==SENS_IMX224)||(model_Sens==SENS_IMX327)||(model_Sens==SENS_IMX462)||(model_Sens==SENS_IMX662))
#define		model_Sens_M_Sens	((model_Sens==SENS_IMX290)||(model_Sens==SENS_IMX307)||(model_Sens==SENS_GC2053)||(model_Sens==SENS_GC2093)||(model_Sens==SENS_SC200AI)||(model_Sens==SENS_OS02K10))
#define		model_Sens_L_Sens	((model_Sens==SENS_PS6210K)||(model_Sens==SENS_IMX335)||(model_Sens==SENS_IMX675)||(model_Sens==SENS_SC500AI)||(model_Sens==SENS_OS02H10)||(model_Sens==SENS_OS04C10))

// ISP 
#define		mode_size			((model_5M) ? 6 : (model_2M) ? 8 : (model_1M) ? 3 : 2)	// Fixed : 1(Addr) + mode

#define		mode_IspO_A			((model_Isp==ISP_EN772)||(model_Isp==ISP_EN775))
#define		mode_IspO_AS		((model_Isp==ISP_EN772S)||(model_Isp==ISP_EN775S))
#define		mode_IspO_M			((model_Isp==ISP_EN801))
#define		mode_IspO_MS		((model_Isp==ISP_EN801M))

#define		model_IspO_ANL		(mode_IspO_A || mode_IspO_AS)
#define		model_IspO_SDI		(mode_IspO_AS|| mode_IspO_MS)
#define		model_IspO_MIPI		(mode_IspO_M || mode_IspO_MS)

#define		model_Isp_pkg68		((model_Isp==ISP_EN772)||(model_Isp==ISP_EN772S)||(model_Isp==ISP_EN775)||(model_Isp==ISP_EN775S))
#define		model_Isp_pkg56		((model_Isp==ISP_EN801)||(model_Isp==ISP_EN801M))

#if   ((model_Sens%10)==0)
#define		DFSEL_Sens(val0, val1, val2, val3, val4, val5, val6, val7, val8, val9)		val0
#elif ((model_Sens%10)==1)
#define		DFSEL_Sens(val0, val1, val2, val3, val4, val5, val6, val7, val8, val9)		val1
#elif ((model_Sens%10)==2)
#define		DFSEL_Sens(val0, val1, val2, val3, val4, val5, val6, val7, val8, val9)		val2
#elif ((model_Sens%10)==3)
#define		DFSEL_Sens(val0, val1, val2, val3, val4, val5, val6, val7, val8, val9)		val3
#elif ((model_Sens%10)==4)
#define		DFSEL_Sens(val0, val1, val2, val3, val4, val5, val6, val7, val8, val9)		val4
#elif ((model_Sens%10)==5)
#define		DFSEL_Sens(val0, val1, val2, val3, val4, val5, val6, val7, val8, val9)		val5
#elif ((model_Sens%10)==6)
#define		DFSEL_Sens(val0, val1, val2, val3, val4, val5, val6, val7, val8, val9)		val6
#elif ((model_Sens%10)==7)
#define		DFSEL_Sens(val0, val1, val2, val3, val4, val5, val6, val7, val8, val9)		val7
#elif ((model_Sens%10)==8)
#define		DFSEL_Sens(val0, val1, val2, val3, val4, val5, val6, val7, val8, val9)		val8
#elif ((model_Sens%10)==9)
#define		DFSEL_Sens(val0, val1, val2, val3, val4, val5, val6, val7, val8, val9)		val9
#else
#define		DFSEL_Sens(val0, val1, val2, val3, val4, val5, val6, val7, val8, val9)
#endif


#if(model_TgtBd==0)
	#define DFSEL_TgtBd(val0, val1, val2)	val0
#elif(model_TgtBd==1)
	#define DFSEL_TgtBd(val0, val1, val2)	val1
#else
	#define DFSEL_TgtBd(val0, val1, val2)	val2
#endif


#if(model_Sens_L_Sens)
	#define	DFSEL_SensIQ(val0, val1, val2, val3)	val0
#elif(model_Sens_M_Sens)
	#define	DFSEL_SensIQ(val0, val1, val2, val3)	val1
#elif(model_Sens_H_Sens)
	#define	DFSEL_SensIQ(val0, val1, val2, val3)	val2
#else
	#define	DFSEL_SensIQ(val0, val1, val2, val3)	val3
#endif
// -----------------------------------------------------------------------------------------------
// SW compile option

	#define 	model_Ispm				1		// 0 : no use ISPM(+Lib)
												//*1 : use ISPM(+Lib)

// -----------------------------------------------------------------------------------------------
// Clock & Frame info (reserved)

	#define MCLK			148500000		// AHB clock (core)

#if model_1M
	#define	FR				60              // Frame pre sec
	#define FR_DUTY			16				// Frame duty time (msec)
	#define FR_HW			1280            // Active H width
	#define FR_VW			720             // Active V width

#elif model_2M
	#define FR				60				// Frame pre sec
	#define FR_DUTY			16				// Frame duty time (msec)
	#define FR_HW			1920			// Active H width
	#define FR_VW			1080			// Active V width

#elif model_5M
	#define FR				30				// Frame pre sec
	#define FR_DUTY			33				// Frame duty time (msec)
	#define FR_HW			((!MODE_5M_ON)?(2560):(2592))			// Active H width
	#define FR_VW			((!MODE_5M_ON)?(1440):(1944))			// Active V width

#endif

//-------------------------------------------------------------------------------------------------
// Type definition

/* g(global)+p(pointer)+c(type)+name(under 8 characters)
   	Bit		Type					TypeDefine	Prefix

	 8		signed char			char			c	pc	gc	gpc		ac	apc
	16		signed short			short			s	ps	gs	gps		as	aps
	32		signed int				int			i	pi	gi	gpi		ai	api
	64		signed long long		s64			l	pl	gl	gpl		al	apl

	 8		unsigned char			BYTE 		b	pb	gb	gpb		ab	apb
	16		unsigned short			WORD 		w	pw	gw	gpw		aw	apw
	32		unsigned int			UINT 		n	pn	gn	gpn		an	apn
	64		unsigned long long		u64			d	pd	gd	gpd		ad	apd

	32		float					float			f	pf	gf	gpf		af	apf		// Point operation
	64		double				double		o	po	go	gpo		ao	apo		//		"
*/


typedef	unsigned char			BYTE;		// 8 bit
typedef	unsigned short			WORD;		// 16 bit
typedef	unsigned int			UINT;		// 16 bit or 32 bit according to system
typedef	unsigned long long		DWORD;		// 64 bit

typedef long long int			s64;
typedef long long unsigned int	u64;

//#if model_FPU == 1
typedef unsigned int 			float32;
typedef char					bool;
typedef	unsigned int			uint;		/* System V compatibility */

typedef union {
	float32	F;
	uint	U;
	float	f;
} tConv;

#define	TOFLOAT32(v)		(((tConv*)(&(v)))->F)		// soft float to hard float
#define	TOUINT(v)			(((tConv*)(&(v)))->U)

extern char gNumcode[17];

extern char* strrev(char* s);
extern int uitoan(uint value, char* str, int base, int width, char fill_val);
extern int ftoan(float32 f, char* str, int width, char fill_val, int prec);
extern int ftox(float32 f, char* str);

//	extern void hfloat_test(void);
//	#include "exr1k_float.h"

// 151110	ygkim	first designed -----
extern float32 _itof(int);
extern int _ftoi(float32);

extern float32 _fadd(float32, float32);
extern float32 _fsub(float32, float32);
extern float32 _fmul(float32, float32);
extern float32 _fdiv(float32, float32);
extern float32 _frem(float32, float32);
extern bool _feq(float32, float32);
extern bool _fge(float32, float32);
extern bool _fgt(float32, float32);
extern bool _fle(float32, float32);
extern bool _flt(float32, float32);
extern bool _fne(float32, float32);
// -------------------------------------
#if model_CharMax == 1
	#define EXCH		WORD
#else
	#define EXCH		char
#endif


#if model_Ispm == 1
	extern const UINT _rom_ispm_text_s;
	extern const UINT _ispm_text_s;
	extern const UINT _ispm_text_e;

	#define ISPM0	__attribute__((section(".ispmtext")))	// for Device driver or Mandatory (fixed)
	#define ISPM	//__attribute__((section(".ispmtext")))	// for Application
	#define ISPM2	//__attribute__((section(".ispmtext")))	// for Application code shirink
	#define ISPMt	//__attribute__((section(".ispmtext")))	// for test
#else
	#define ISPM0
	#define ISPM
	#define ISPM2
	#define ISPMt
#endif

#define DATA	__attribute__((section(".data")))

extern const UINT _reset_s;
extern const UINT _rom_data_e;
extern const UINT _rom_data_s;
extern const UINT _data_e;
extern const UINT _data_s;
extern const UINT _bss_e;
extern const UINT _bss_s;
extern const UINT _stack;

// -----------------------------------------------------------------------------------------------
// Clock & Frame info (reserved)
#define FPS_DEF		60
#define FPS			((MP(MpSysFreq) == MN_SYSFREQ_50) ? 25 : 30)//FR

extern UINT FPS_VDI;
extern UINT FPS_VDO;

//-------------------------------------------------------------------------------------------------
// Macro
#define	_regs_					typedef	union{UINT a; struct{	// Register union start
#define	_rege_					}b;}							// Register union end

#define	_am(uon,base,addr)		((volatile uon*)(UINT*)(base+(addr)))->a		// All macro
#define	_bm(uon,base,addr,mne)	((volatile uon*)(UINT*)(base+(addr)))->b.mne	// Bit macro

#if 1
#define	_wr8(a,d)				(*((volatile BYTE *)(a)) = (d))		// Write to peripheral	- Only used for Serial Flash Write
#define	_wr32(a,d)				(*((volatile UINT *)(a)) = (d))		//			"			- Always used for ISP Register Write
#else
extern void ISPM0 _wr8_fnc(const UINT anAddr, const BYTE abData);
extern void ISPM0 _wr32_fnc(const UINT anAddr, const UINT anData);
#define	_wr8					_wr8_fnc
#define	_wr32					_wr32_fnc
#endif

#define	_rd8(a)					(*((volatile BYTE *)(a)))				// Read from peripheral	- Only used for Serial Flash Read
#define	_rd32(a)				(*((volatile UINT *)(a)))				//			"			- Always used for ISP Register Read

#define sfw8(a,d)				_wr8( FLS_BASE | ((a)&FLASH_ADDR_MASK), d)
#define sfw32(a,d)				_wr32(FLS_BASE | ((a)&FLASH_ADDR_MASK), d)

#define sfr8(a)					_rd8( FLS_BASE | ((a)&FLASH_ADDR_MASK))
#define sfr32(a)				_rd32(FLS_BASE | ((a)&FLASH_ADDR_MASK))


#define UNUSED_ARG(x)			((void)(x))


// Arithmetic
#define ABS(x)					( (x) >= 0  ? (x) : -(x) )
#define MIN(x,y)				( (x) < (y) ? (x) :  (y) )
#define MAX(x,y)				( (x) > (y) ? (x) :  (y) )
#define MINMAX(x,min,max)		MIN(MAX(x, min), max)

#define ABSDIFF(A,B)			( (A)>(B) ? (A)-(B) : (B)-(A) )

#define	UROUND_DIV(NUME,DENO)	((((NUME)<<1) / (DENO) + 1) >> 1)	// Division and Round off unsigned number

#define GetBit(V,HB,LB)		(((V)>>(LB))&((1<<((HB)-(LB)+1))-1))
#define SetBit(V,HB,LB,D)	(V) = (((V) & (~(((1<<((HB)-(LB)+1))-1)<<(LB)))) | ((D)<<(LB)))

#define numberof(Arr)			(sizeof(Arr)/sizeof(Arr[0]))

#define CHANGE_VAL0(TYPE,VAL,TEMP,...) {\
			static TYPE d1_##TEMP = 0;\
			if(VAL != d1_##TEMP) { __VA_ARGS__;	d1_##TEMP = VAL; }\
		}
#define CHANGE_VALt(TYPE,VAL,TEMP,...)	CHANGE_VAL0(TYPE,VAL,TEMP,__VA_ARGS__)
#define CHANGE_VAL(TYPE,VAL,...)		CHANGE_VALt(TYPE,VAL,__LINE__,__VA_ARGS__)

//-------------------------------------------------------------------------------------------------
// Misc
#define	NULL		0
#define	OK			1
#define	NG			0
#define YES			OK
#define	NO			NG

#define BitMask_01			0x1
#define BitMask_02			0x3
#define BitMask_03			0x7
#define BitMask_04			0xf
#define BitMask_05			0x1f
#define BitMask_06			0x3f
#define BitMask_07			0x7f
#define BitMask_08			0xff
#define BitMask_09			0x1ff
#define BitMask_10			0x3ff
#define BitMask_11			0x7ff
#define BitMask_12			0xfff
#define BitMask_13			0x1fff
#define BitMask_14			0x3fff
#define BitMask_15			0x7fff
#define BitMask_16			0xffff
#define BitMask_17			0x1ffff
#define BitMask_18			0x3ffff
#define BitMask_19			0x7ffff
#define BitMask_20			0xfffff
#define BitMask_21			0x1fffff
#define BitMask_22			0x3fffff
#define BitMask_23			0x7fffff
#define BitMask_24			0xffffff
#define BitMask_25			0x1ffffff
#define BitMask_26			0x3ffffff
#define BitMask_27			0x7ffffff
#define BitMask_28			0xfffffff
#define BitMask_29			0x1fffffff
#define BitMask_30			0x3fffffff
#define BitMask_31			0x7fffffff
#define BitMask_32			0xffffffff

#define ValSft_R00(val)		((val)>> 0)
#define ValSft_R01(val)		((val)>> 1)
#define ValSft_R02(val)		((val)>> 2)
#define ValSft_R03(val)		((val)>> 3)
#define ValSft_R04(val)		((val)>> 4)
#define ValSft_R05(val)		((val)>> 5)
#define ValSft_R06(val)		((val)>> 6)
#define ValSft_R07(val)		((val)>> 7)
#define ValSft_R08(val)		((val)>> 8)
#define ValSft_R09(val)		((val)>> 9)
#define ValSft_R10(val)		((val)>>10)
#define ValSft_R11(val)		((val)>>11)
#define ValSft_R12(val)		((val)>>12)
#define ValSft_R13(val)		((val)>>13)
#define ValSft_R14(val)		((val)>>14)
#define ValSft_R15(val)		((val)>>15)
#define ValSft_R16(val)		((val)>>16)
#define ValSft_R17(val)		((val)>>17)
#define ValSft_R18(val)		((val)>>18)
#define ValSft_R19(val)		((val)>>19)
#define ValSft_R20(val)		((val)>>20)
#define ValSft_R21(val)		((val)>>21)
#define ValSft_R22(val)		((val)>>22)
#define ValSft_R23(val)		((val)>>23)
#define ValSft_R24(val)		((val)>>24)
#define ValSft_R25(val)		((val)>>25)
#define ValSft_R26(val)		((val)>>26)
#define ValSft_R27(val)		((val)>>27)
#define ValSft_R28(val)		((val)>>28)
#define ValSft_R29(val)		((val)>>29)
#define ValSft_R30(val)		((val)>>30)
#define ValSft_R31(val)		((val)>>31)

#define ValSft_L00(val)		((val)<< 0)
#define ValSft_L01(val)		((val)<< 1)
#define ValSft_L02(val)		((val)<< 2)
#define ValSft_L03(val)		((val)<< 3)
#define ValSft_L04(val)		((val)<< 4)
#define ValSft_L05(val)		((val)<< 5)
#define ValSft_L06(val)		((val)<< 6)
#define ValSft_L07(val)		((val)<< 7)
#define ValSft_L08(val)		((val)<< 8)
#define ValSft_L09(val)		((val)<< 9)
#define ValSft_L10(val)		((val)<<10)
#define ValSft_L11(val)		((val)<<11)
#define ValSft_L12(val)		((val)<<12)
#define ValSft_L13(val)		((val)<<13)
#define ValSft_L14(val)		((val)<<14)
#define ValSft_L15(val)		((val)<<15)
#define ValSft_L16(val)		((val)<<16)
#define ValSft_L17(val)		((val)<<17)
#define ValSft_L18(val)		((val)<<18)
#define ValSft_L19(val)		((val)<<19)
#define ValSft_L20(val)		((val)<<20)
#define ValSft_L21(val)		((val)<<21)
#define ValSft_L22(val)		((val)<<22)
#define ValSft_L23(val)		((val)<<23)
#define ValSft_L24(val)		((val)<<24)
#define ValSft_L25(val)		((val)<<25)
#define ValSft_L26(val)		((val)<<26)
#define ValSft_L27(val)		((val)<<27)
#define ValSft_L28(val)		((val)<<28)
#define ValSft_L29(val)		((val)<<29)
#define ValSft_L30(val)		((val)<<30)
#define ValSft_L31(val)		((val)<<31)

//-------------------------------------------------------------------------------------------------
// Test

#define ENABLE_WAIT_VLOCK	1

#define STR_PELCO_DATA		1		// Display 20~27 Lines

#define STATUS_ON			(gbMnDebugFnc == 9)

#define GRP_TI_UCC			0


#if ENABLE_WAIT_VLOCK == 1
	#define EWV(T,F)	T
#else
	#define EWV(T,F)	F
#endif

//----------------------------------------------------------------------------------------
// Library Link
//1M
#if model_Sens ==			SENS_IMX225
	#define Sens(a) a##___##SENS_IMX225
#elif model_Sens ==			SENS_IMX224
	#define Sens(a) a##___##SENS_IMX224
	
//2M
#elif model_Sens ==			SENS_IMX290
	#define Sens(a) a##___##SENS_IMX290
#elif model_Sens ==			SENS_IMX327
	#define Sens(a) a##___##SENS_IMX327
#elif model_Sens ==			SENS_IMX307
	#define Sens(a) a##___##SENS_IMX307
#elif model_Sens ==			SENS_IMX462
	#define Sens(a) a##___##SENS_IMX462
#elif model_Sens ==			SENS_IMX662
	#define Sens(a) a##___##SENS_IMX662
#elif model_Sens ==			SENS_GC2053
	#define Sens(a) a##___##SENS_GC2053
#elif model_Sens ==			SENS_GC2093
	#define Sens(a) a##___##SENS_GC2093
#elif model_Sens ==			SENS_SC200AI
	#define Sens(a) a##___##SENS_SC200AI
#elif model_Sens ==			SENS_PS6210K
	#define Sens(a) a##___##SENS_PS6210K
#elif model_Sens ==			SENS_OS02H10
	#define Sens(a) a##___##SENS_OS02H10

#elif model_Sens ==			SENS_OS02K10
	#define Sens(a) a##___##SENS_OS02K10

//2M LFM	
#elif model_Sens ==			SENS_IMX390
	#define Sens(a) a##___##SENS_IMX390
#elif model_Sens ==			SENS_AR0233
	#define Sens(a) a##___##SENS_AR0233	
#elif model_Sens ==			SENS_OX03C10
	#define Sens(a) a##___##SENS_OX03C10
	
//4M	
#elif model_Sens ==			SENS_IMX335
	#define Sens(a) a##___##SENS_IMX335
#elif model_Sens ==			SENS_IMX675
	#define Sens(a) a##___##SENS_IMX675
#elif model_Sens ==			SENS_SC500AI
	#define Sens(a) a##___##SENS_SC500AI
#elif model_Sens ==			SENS_OS04C10
	#define Sens(a) a##___##SENS_OS04C10
#else
	#define Sens(a) a
#endif

//--------------------------------------------------------------------------------------------------
// Lib Link

// System
#define LibInitSens			Sens(LibInitSens)
#define LibRdesIsp			Sens(LibRdesIsp)

// AE
#define LibAeShtLine		Sens(LibAeShtLine)
#define AeSHT				Sens(AeSHT)
#define AeAGC				Sens(AeAGC)
//#define AeIRS				Sens(AeIRS)

#define AE_SHTLw			Sens(AE_SHTLw)
#define AE_AGCw				Sens(AE_AGCw)
#define AE_DGCw				Sens(AE_DGCw)
#define AE_FREQw			Sens(AE_FREQw)

#define AE_GAIN_TOTAL		Sens(AE_GAIN_TOTAL)
#define AE_GAIN_TOTAL2		Sens(AE_GAIN_TOTAL2)

#if (model_Sens_LWdr)
#define AE_SHTSw			Sens(AE_SHTSw)
#define AeSHT_LWDR			Sens(AeSHT_LWDR)
#define AeAGC_LWDR			Sens(AeAGC_LWDR)
#endif

#if(model_Sens_CLR_HDR)
#define AeSHT_CHDR			Sens(AeSHT_CHDR)
#define AeAGC_CHDR			Sens(AeAGC_CHDR)
#endif
     
#if(model_Sens_LFM_HDR)
#define ExtWR_Reg			Sens(ExtWR_Reg)
#endif

// AWB
#define glMtxCf				Sens(glMtxCf)

// MIRROR & FLIP
#define SENS_MIRw			Sens(SENS_MIRw)
#define SENS_FLPw			Sens(SENS_FLPw)


//******************************************************
// 2. GPIO
//------------------------------------------------------



//******************************************************
// 3. ADC
//------------------------------------------------------



//******************************************************
// 4. UART
//------------------------------------------------------



//******************************************************
// 5. I2C
//------------------------------------------------------	
#if (model_I2C_ch1 == 1)
	#define eep_write(A,D)		{ UNUSED_ARG(A); UNUSED_ARG(D); }
	#define eep_read(A,D,S)		{ UNUSED_ARG(A); *(D) = 0; UNUSED_ARG(S); }
	#define EepPageWrite(...)

	typedef WORD	IADDR;
	typedef UINT	IDATA;

#define I2C_ADDR_NUM	(sizeof(IADDR))					//I2C Address type (BYTE)
#define I2C_DATA_NUM	(sizeof(IDATA))					//I2C Data type (BYTE)

#define I2C_LENGTH 		(I2C_ADDR_NUM+I2C_DATA_NUM)

	BYTE gbI2cPacket[I2C_LENGTH];		// [0] ADDR, [1] : DATA

	IADDR gAddr;
	IDATA gData;
#endif


//******************************************************
// 6. TIMER
//------------------------------------------------------
#define	TIMER_NUM			6

//#define		PwmEna				(TIM_CH0_EN=1     		)	// enable
//#define		PwmDis				(TIM_CH0_EN=0     		)	// disable
//#define		PwmSetPrd(anIn)		(TIM_CH0_LMT=(UINT)anIn )	// PWM period
//#define		PwmSetDty(anIn)		(TIM_CH0_TRIG=(UINT)anIn)	// PWM duty (Must be shorter than "TM2CNT_PWMW")
//#define		PwmSetNum(anIn)		(                       )	// PWM pulse number value
//extern void PwmCfg(BYTE abPreFact, BYTE abPol);

#define		PwmEna				(TIM_CH0_EN=1     		)	// enable
#define		PwmDis				(TIM_CH0_EN=0     		)	// disable
#define		PwmSetPrd(anIn)		(TIM_CH0_LMT=(UINT)anIn )	// PWM period
#define		PwmSetDty(anIn)		(TIM_CH0_TRIG=(UINT)anIn)	// PWM duty (Must be shorter than "TM2CNT_PWMW")
#define		PwmSetNum(anIn)		(                       )	// PWM pulse number value




// Tick Timer
#define TICK_STA(ID)	const UINT nTickSta_##ID = GetTT()
#define TICK_END(ID)	UINT nTick_##ID = GetTT();\
						nTick_##ID = (nTick_##ID > nTickSta_##ID) ? nTick_##ID - nTickSta_##ID :\
																	GetTTmax() - nTickSta_##ID + nTick_##ID + 1

// micro-sec = TICK / MCLK * 1000000
//           = TICK / 74250000 * 1000000
//           = TICK * 1000000 / 74250000
//           = TICK * 100 / 7425
//           = TICK * 4 / 297
//           = TICK * 4 / (MCLK / 250000)
#define tick2us(ID)		((nTick_##ID*4   ) / (MCLK/250000))
#define tick2ns(ID)		((nTick_##ID*4000) / (MCLK/250000))	// (+Lib)

#define TICK_OUT(ID,fname,fout) \
	/*if(nTick_##ID <= (0xFFFFFFFF/4000))	{ fout(fname" ns:", tick2ns(ID), 10); }\
	else*/								{ fout(fname" us:", tick2us(ID), 10); }


#define FUNC_TIME(ID,func) \
	TICK_STA(ID);\
	func;\
	TICK_END(ID);\

#define FUNC_TIME_DI(ID,func) \
	DI(ID);\
	FUNC_TIME(ID,func)\
	EI(ID);

#define FUNC_TIME_OUT_ID(AD,ID,fname,fout,func)		FUNC_TIME##AD(ID,func)	TICK_OUT(ID,fname,fout)

#define FUNC_TIME_TX(fname,func)					FUNC_TIME_OUT_ID(_DI,__LINE__,fname,TxStrDec,func)		// use DI()
//#define FUNC_TIME_DISP(fname,func)					FUNC_TIME_OUT_ID(_DI,__LINE__,fname,DispDbgD,func)
#define FUNC_TIME_TX_NoIRQ(fname,func)				FUNC_TIME_OUT_ID(,__LINE__,fname,TxStrDecNoIRQ,func)

#define xFUNC_TIME_TX(fname,func)					func
//#define xFUNC_TIME_DISP(fname,func)					func
#define xFUNC_TIME_TX_NoIRQ(fname,func)				func

#define FUNC_TIME_GET(ID)							tick2us(ID)		// micro-sec

// for MainVDO & MainVDI
#define FUNC_TIME_START(ID)							TICK_STA(ID)
#define FUNC_TIME_END(ID,fname)						TICK_END(ID); if(STATUS_ON) {TICK_OUT(ID,fname,DispDbgD)}

#define FUNC_TIME_OSD_ID(ID,fname,Y,X,func)			{ FUNC_TIME_DI(ID,func) DispDatDec(fname" us:", Y, X, tick2us(ID)); }
#define FUNC_TIME_OSD(fname,Y,X,func)				FUNC_TIME_OSD_ID(__LINE__,fname,Y,X,func)
#define xFUNC_TIME_OSD(fname,Y,X,func)				func



//******************************************************
// 7. SPI
//------------------------------------------------------



//******************************************************
// 8. IRQ
//------------------------------------------------------
#define MAX_INT_HANDLERS	10		// Number of interrupt handlers(+Lib)



//******************************************************
// 9. FLASH
//------------------------------------------------------



//******************************************************
// 10. WDT
//------------------------------------------------------



//******************************************************
// 11. ISP
//------------------------------------------------------
#define	ISP_BASE				ISP_REG_BASE	// Normal reg start addr.

#define ISP_BASE_SHADING		0x400			// (fix) Shading table start addr			(0x400 ~ 4ff)
#define	ISP_BASE_FONT_ID		0x1000			// Font
#define	ISP_BASE_FONT_ATTR		0x1800			// "
#define	ISP_BASE_FONT_CHAR		0x2000			// "

#define ISP_SHADING_EA			144				// (fix) number of Shading table
#define ISP_BOX_EA				32				// (fix) number of Box

#define ISP_FONT_EAX			46/*30*/			// number of Horizontal Font		ksh modi

#define ISP_FONT_ID_EA			2048			// number of Font id
#define ISP_FONT_ATTR_EA		2048			// number of Font attr
#define	ISP_FONT_CHAR_EA		255/*341*/		// number of font character

//#define ISP_FONT_DEBUG_X		24				// Start Position for Debugging
#define ISP_FONT_MAX_PATH		10				// number of String for Debugging
//#define ISP_FONT_SPACE			1				// number of Space for Debugging

#define SPACE_CHAR_ID			' '

// ISP interrupt number
#define ISP_IRQ_VLOCKL			0				// VLOCKI, Sensor �Է� Sync ����
#define ISP_IRQ_VLOCKW			1				// VLOCKW, Sensor �Է� Sync ���� (WDR ���� Sync)
#define ISP_IRQ_VLOCKO			2				// VLOCKO, ISP ��� Sync ����(Low Shutter �����ϰ��� VLOKCI�� VLOCKO�� ���� ��.)
#define ISP_IRQ_USERI0			3				// User Interrupt I 0 (VLOCKI ����)
#define ISP_IRQ_USERI1			4				// User Interrupt I 1 (VLOCKI ����)
#define ISP_IRQ_USERO0			5				// User Interrupt O 0 (VLOCKO ����)
#define ISP_IRQ_USERO1			6				// User Interrupt O 1 (VLOCKO ����)
#define ISP_IRQ_COAX			7				// Coaxial Comm.
#define ISP_IRQ_ADC				8				// ADC
#define ISP_IRQ_VLOCKM			9				// Manual vlock Sync (Based on register)


// Bridge addressing (Isp+Audio+Image+Voice...)
#define	SetIsp(anAddr, anData)			(_wr32(ISP_BASE+((UINT)(anAddr)<<2), (UINT)(anData)))	// Write to bridge(Isp,Aud)
#define	GetIsp(anAddr)					(_rd32(ISP_BASE+((UINT)(anAddr)<<2))                )	// Read from bridge(Isp,Aud)

extern UINT gnFontdummy;
#define SetFontChar(anAddr,anData)		{_wr32(ISP_BASE+((ISP_BASE_FONT_CHAR +(UINT)(anAddr))<<2),  (UINT)(anData));\
										gnFontdummy = *(volatile unsigned int*)(ISP_BASE+((ISP_BASE_FONT_CHAR +(UINT)(anAddr))<<2)); }

#define SetFontAttr(anAddr,anData)  	{_wr32(ISP_BASE+((ISP_BASE_FONT_ATTR +(UINT)(anAddr))<<2), ((UINT)(anData)&0x3));\
										gnFontdummy = *(volatile unsigned int*)(ISP_BASE+((ISP_BASE_FONT_ATTR +(UINT)(anAddr))<<2)); }

//#define SetFont(Y,X,A)		gbFont[Y][X] = A
#define SetFontId(anAddr,anData)		{_wr32(ISP_BASE+((ISP_BASE_FONT_ID	 +(UINT)(anAddr))<<2), ((UINT)(anData)&0x1ff));\
										gnFontdummy = *(volatile unsigned int*)(ISP_BASE+((ISP_BASE_FONT_ID +(UINT)(anAddr))<<2)); }

#define SETFONTATTR(Y,X,A)				{SetFontAttr((((Y)*ISP_FONT_EAX)+(X)), A);}
#define SETFONTID(Y,X,A)				{SetFontId((((Y)*ISP_FONT_EAX)+(X)), A);}

//******************************************************
// 12. SENSOR
//------------------------------------------------------
#define SENS_SONY_DEV		0x34		// Sony
#define SENS_ONSEMI_DEV 	0x20 		// Onsemi
#define SENS_OMNI_DEV		0x6C		// Omnivision

#if((model_Sens==SENS_OS02H10)||(model_Sens==SENS_OS02D20))
#undef  SENS_OMNI_DEV
#define	SENS_OMNI_DEV		(0x78)
#endif

#define SENS_GLXCOR_DEV		0x6E		// Galaxy Core

#define SENS_PXPLS_DEV		0xEE		// PixelPlus
#define SENS_SMARTS_DEV		0x60		// SmartSens
#define SENS_PANA_DEV       0x00		// Panasonic


#if model_Sony
	#define SetSens(ADDR, VAL)			SetSensTwi_Sony(SENS_SONY_DEV, ADDR, VAL)
	#define GetSens(ADDR)				GetSensTwi_Sony(SENS_SONY_DEV, ADDR)
	#define SetSensBst(ADDR, VAL, NUM)	SetSensTwiBst_Sony(SENS_SONY_DEV, ADDR, VAL, NUM)

#elif model_Onsemi
 	#define SetSens(DEV, ADDR, VAL)		SetSensTwi_Onsemi(SENS_ONSEMI_DEV, ADDR, VAL)
	#define GetSens(ADDR)				GetSensTwi_Onsemi(SENS_ONSEMI_DEV, ADDR)

#elif model_Omni
	#define SetSens(ADDR, VAL)			SetSensTwi_Omni(SENS_OMNI_DEV, ADDR, VAL)
	#define GetSens(ADDR)				GetSensTwi_Omni(SENS_OMNI_DEV, ADDR)
	#define SetSensBst(ADDR, VAL, NUM)	SetSensTwiBst_Omni(SENS_OMNI_DEV, ADDR, VAL, NUM)

#elif model_Glxcore
	#define SetSens(ADDR, VAL)			SetSensTwi_GC(SENS_GLXCOR_DEV, ADDR, VAL)
	#define GetSens(ADDR)				GetSensTwi_GC(SENS_GLXCOR_DEV, ADDR)

#elif model_Pxpls
	#define SetSens(ADDR, VAL)			SetSensTwi_Pxpls(SENS_PXPLS_DEV, ADDR, VAL)
	#define GetSens(ADDR)				GetSensTwi_Pxpls(SENS_PXPLS_DEV, ADDR)

#elif model_SmartSens
	#define SetSens(ADDR, VAL)			SetSensTwi_SC(SENS_SMARTS_DEV, ADDR, VAL)
	#define GetSens(ADDR)				GetSensTwi_SC(SENS_SMARTS_DEV, ADDR)

#elif model_Pana
	#define SetSens(ID, ADDR, VAL)	    SetSensTwi_Pana(SENS_PANA_DEV, ADDR, VAL)
	#define GetSens(ADDR)			    GetSensTwi_Pana(SENS_PANA_DEV, ADDR)

#endif


//******************************************************
// 13. TEST
//------------------------------------------------------



