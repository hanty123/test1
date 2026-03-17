/* **************************************************************************
 File Name		:	SENS_Common.h
 Description	:	EN772_801 - Interface matching between ISP and sensor 
 Designer		:	Lee, Gyu Hong
 Date		:	21. 02. 08
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

extern UINT gnInModeVtw;
extern BYTE gbAeDebugOn;

extern UINT gnAeNorMax;
extern UINT gnAeLWdrMaxL0;
extern UINT gnAeLWdrMaxS1;

extern UINT gnAeLWdrMinL0;
extern UINT gnAeLWdrMinS1;

extern int	giAeLWdrGain;
extern BYTE gbAeWdrComp;

extern WORD gwAeSensAgcLmtNor;
extern WORD gwAeSensAgcLmtWdr;

extern BYTE gbMir, gbFlp;
extern BYTE gbMirFlp;

BYTE SENS_MST;

/* Sensor WDR AGC Limit */
//#define AE_SENS_AGC_LMT			(AE_GAIN_UNIT_MAX*AE_GAIN_UNIT_EA+AE_GAIN_UNIT_OVR)	// LWDR Mode AGC Limit 
#define AE_SENS_AGC_LMT_NOR		(gwAeSensAgcLmtNor)					// LWDR Mode AGC Limit 
#define AE_SENS_AGC_LMT_WDR		(gwAeSensAgcLmtWdr)					// LWDR Mode AGC Limit (Analog Gain : 300 * 0.1 = 30dB)

extern void LibISPtoSENS_Intf(BYTE abRdesType, BYTE abRdesLane, BYTE abRdesBit, WORD awRdesLdoSel, WORD awRdesWC, BYTE abWdrMipiMode, BYTE abWdrOn);

//abRdesType
#define LVDS	(0)
#define	MIPI	(1)

//abRdesLane
#define _1LANE	(0)
#define _2LANE	(1)
#define	_4LANE	(2)

//abRdesBit
#define	_10BIT	(0)
#define	_12BIT	(1)
#define _14BIT	(2)
#define	_16BIT	(3)

//awRdesLdoSel
#define _0		(0x0)
#define	_10		(0x10)
#define	_3210	(0x3210)

//abWdrMipiMode
#define	_MIPI_VC (0)
#define	_MIPI_LI (1)

#define	_NOT_USED	(0xFF)

//WDR MODE
#define	_NORMAL		(0x0 )
#define	_HDR_LINE	(0x1 )
#define _HDR_CLR	(0x10)

/* ISP MODE Enum */
extern void LibBrkCond(void);

enum{
	LIB_ISP_EN772 = 0,	// 0
	LIB_ISP_EN772S,		// 1
	LIB_ISP_EN775,		// 2
	LIB_ISP_EN775S,		// 3
	LIB_ISP_EN801,		// 4
	LIB_ISP_EN801M,		// 5
	LIB_ISP_EN805,		// 6
	LIB_ISP_EN805M		// 7
};