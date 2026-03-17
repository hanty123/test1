/* **************************************************************************
 File Name	: 	dev_reg_isp.h
 Description:	EN772 - ISP Reg macro define
 Designer	:	Lee, Gyu Hong
 Date		:	20. 08. 31
 Copyright ¨Ï Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */
#define _REG_BASE_				ISP_BASE

#define TMG_BASE				0x017A

#define AWBL_CM_BASE			0x0300

#define YGAMMA_BASE1			0x01CB
#define YGAMMA_BASE2			0x01D4
#define CGAMMA_BASE1			0x01DD
#define CGAMMA_BASE2			0x01E6

#define BOXTON_BASE				0x0274
#define BOXFIL_BASE				0x0276
#define BOXPOS_BASE				0x0280
#define BOXPLT_BASE				0x02C0

//*************************************************************************************************
// ISP (EN772/801)
//-------------------------------------------------------------------------------------------------

#define SPLL_RSTNr				(ValSft_R31(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_01)
#define SPLL_RSTNw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define SPLL_RATEr				(ValSft_R30(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_01)
#define SPLL_RATEw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define SPLL_POr				(ValSft_R29(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_01)
#define SPLL_POw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define STX_POr					(ValSft_R28(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_01)
#define STX_POw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define STX_SWGr				(ValSft_R24(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_04)
#define STX_SWGw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L24(BitMask_04)))|ValSft_L24((val)&BitMask_04)))

#define SDI_PRE_EMPr			(ValSft_R23(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_01)
#define SDI_PRE_EMPw(val)		_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define SPLL_BWr				(ValSft_R20(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_03)
#define SPLL_BWw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L20(BitMask_03)))|ValSft_L20((val)&BitMask_03)))

#define SPLL_RESr				(ValSft_R16(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_03)
#define SPLL_RESw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L16(BitMask_03)))|ValSft_L16((val)&BitMask_03)))

#define STX_UCCRX_POr			(ValSft_R15(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_01)
#define STX_UCCRX_POw(val)		_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define STX_UCCRX_FLTRr			(ValSft_R12(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_02)
#define STX_UCCRX_FLTRw(val)	_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L12(BitMask_02)))|ValSft_L12((val)&BitMask_02)))

#define STX_REF_CAPr			(ValSft_R10(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_02)
#define STX_REF_CAPw(val)		_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L10(BitMask_02)))|ValSft_L10((val)&BitMask_02)))

#define STX_TESTr				(ValSft_R08(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_02)
#define STX_TESTw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L08(BitMask_02)))|ValSft_L08((val)&BitMask_02)))

#define SPLL_AUTO_POr			(ValSft_R31(_rd32(_REG_BASE_+(0x0001<<2)))&BitMask_01)
#define SPLL_AUTO_POw(val)		_wr32(_REG_BASE_+(0x0001<<2),(UINT)((_rd32(_REG_BASE_+(0x0001<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define SPLL_AUTO_RSr			(ValSft_R30(_rd32(_REG_BASE_+(0x0001<<2)))&BitMask_01)
#define SPLL_AUTO_RSw(val)		_wr32(_REG_BASE_+(0x0001<<2),(UINT)((_rd32(_REG_BASE_+(0x0001<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define DPLL_ATRSINTr			(ValSft_R16(_rd32(_REG_BASE_+(0x0002<<2)))&BitMask_12)
#define DPLL_ATRSINTw(val)		_wr32(_REG_BASE_+(0x0002<<2),(UINT)((_rd32(_REG_BASE_+(0x0002<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define DPLL_LOCKTMr			(ValSft_R00(_rd32(_REG_BASE_+(0x0002<<2)))&BitMask_12)
#define DPLL_LOCKTMw(val)		_wr32(_REG_BASE_+(0x0002<<2),(UINT)((_rd32(_REG_BASE_+(0x0002<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define DPLL_Sr					(ValSft_R31(_rd32(_REG_BASE_+(0x0003<<2)))&BitMask_01)
#define DPLL_Sw(val)			_wr32(_REG_BASE_+(0x0003<<2),(UINT)((_rd32(_REG_BASE_+(0x0003<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DPLL_TESTr				(ValSft_R30(_rd32(_REG_BASE_+(0x0003<<2)))&BitMask_01)
#define DPLL_TESTw(val)			_wr32(_REG_BASE_+(0x0003<<2),(UINT)((_rd32(_REG_BASE_+(0x0003<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define DPLL_IDIVXr				(ValSft_R29(_rd32(_REG_BASE_+(0x0003<<2)))&BitMask_01)
#define DPLL_IDIVXw(val)		_wr32(_REG_BASE_+(0x0003<<2),(UINT)((_rd32(_REG_BASE_+(0x0003<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define DPLL_ATRSr				(ValSft_R28(_rd32(_REG_BASE_+(0x0003<<2)))&BitMask_01)
#define DPLL_ATRSw(val)			_wr32(_REG_BASE_+(0x0003<<2),(UINT)((_rd32(_REG_BASE_+(0x0003<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define DPLL_Kr					(ValSft_R08(_rd32(_REG_BASE_+(0x0003<<2)))&BitMask_07)
#define DPLL_Kw(val)			_wr32(_REG_BASE_+(0x0003<<2),(UINT)((_rd32(_REG_BASE_+(0x0003<<2))&(~ValSft_L08(BitMask_07)))|ValSft_L08((val)&BitMask_07)))

#define DPLL_IDIVFBr			(ValSft_R00(_rd32(_REG_BASE_+(0x0003<<2)))&BitMask_07)
#define DPLL_IDIVFBw(val)		_wr32(_REG_BASE_+(0x0003<<2),(UINT)((_rd32(_REG_BASE_+(0x0003<<2))&(~ValSft_L00(BitMask_07)))|ValSft_L00((val)&BitMask_07)))

#define DAC_PD_INr				(ValSft_R00(_rd32(_REG_BASE_+(0x0004<<2)))&BitMask_01)
#define DAC_PD_INw(val)			_wr32(_REG_BASE_+(0x0004<<2),(UINT)((_rd32(_REG_BASE_+(0x0004<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define UTC_POr					(ValSft_R31(_rd32(_REG_BASE_+(0x0005<<2)))&BitMask_01)
#define UTC_POw(val)			_wr32(_REG_BASE_+(0x0005<<2),(UINT)((_rd32(_REG_BASE_+(0x0005<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define UTC_BYPr				(ValSft_R30(_rd32(_REG_BASE_+(0x0005<<2)))&BitMask_01)
#define UTC_BYPw(val)			_wr32(_REG_BASE_+(0x0005<<2),(UINT)((_rd32(_REG_BASE_+(0x0005<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define UTC_REF_POr				(ValSft_R29(_rd32(_REG_BASE_+(0x0005<<2)))&BitMask_01)
#define UTC_REF_POw(val)		_wr32(_REG_BASE_+(0x0005<<2),(UINT)((_rd32(_REG_BASE_+(0x0005<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define UTC_Vr					(ValSft_R24(_rd32(_REG_BASE_+(0x0005<<2)))&BitMask_04)
#define UTC_Vw(val)				_wr32(_REG_BASE_+(0x0005<<2),(UINT)((_rd32(_REG_BASE_+(0x0005<<2))&(~ValSft_L24(BitMask_04)))|ValSft_L24((val)&BitMask_04)))

#define UTC_HPFr				(ValSft_R20(_rd32(_REG_BASE_+(0x0005<<2)))&BitMask_03)
#define UTC_HPFw(val)			_wr32(_REG_BASE_+(0x0005<<2),(UINT)((_rd32(_REG_BASE_+(0x0005<<2))&(~ValSft_L20(BitMask_03)))|ValSft_L20((val)&BitMask_03)))

#define UTC_SCHMr				(ValSft_R16(_rd32(_REG_BASE_+(0x0005<<2)))&BitMask_03)
#define UTC_SCHMw(val)			_wr32(_REG_BASE_+(0x0005<<2),(UINT)((_rd32(_REG_BASE_+(0x0005<<2))&(~ValSft_L16(BitMask_03)))|ValSft_L16((val)&BitMask_03)))

#define UTC_SCHM_SELr			(ValSft_R15(_rd32(_REG_BASE_+(0x0005<<2)))&BitMask_01)
#define UTC_SCHM_SELw(val)		_wr32(_REG_BASE_+(0x0005<<2),(UINT)((_rd32(_REG_BASE_+(0x0005<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define UTC_PHYSELr				(ValSft_R00(_rd32(_REG_BASE_+(0x0005<<2)))&BitMask_01)
#define UTC_PHYSELw(val)		_wr32(_REG_BASE_+(0x0005<<2),(UINT)((_rd32(_REG_BASE_+(0x0005<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define MPLL_RATEr				(ValSft_R31(_rd32(_REG_BASE_+(0x0006<<2)))&BitMask_01)
#define MPLL_RATEw(val)			_wr32(_REG_BASE_+(0x0006<<2),(UINT)((_rd32(_REG_BASE_+(0x0006<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define MPLL_BWr				(ValSft_R28(_rd32(_REG_BASE_+(0x0006<<2)))&BitMask_03)
#define MPLL_BWw(val)			_wr32(_REG_BASE_+(0x0006<<2),(UINT)((_rd32(_REG_BASE_+(0x0006<<2))&(~ValSft_L28(BitMask_03)))|ValSft_L28((val)&BitMask_03)))

#define MPLL_RSTNr				(ValSft_R27(_rd32(_REG_BASE_+(0x0006<<2)))&BitMask_01)
#define MPLL_RSTNw(val)			_wr32(_REG_BASE_+(0x0006<<2),(UINT)((_rd32(_REG_BASE_+(0x0006<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define MPLL_RESr				(ValSft_R24(_rd32(_REG_BASE_+(0x0006<<2)))&BitMask_03)
#define MPLL_RESw(val)			_wr32(_REG_BASE_+(0x0006<<2),(UINT)((_rd32(_REG_BASE_+(0x0006<<2))&(~ValSft_L24(BitMask_03)))|ValSft_L24((val)&BitMask_03)))

#define MPLL_POr				(ValSft_R23(_rd32(_REG_BASE_+(0x0006<<2)))&BitMask_01)
#define MPLL_POw(val)			_wr32(_REG_BASE_+(0x0006<<2),(UINT)((_rd32(_REG_BASE_+(0x0006<<2))&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define MPLL_SELr				(ValSft_R20(_rd32(_REG_BASE_+(0x0006<<2)))&BitMask_03)
#define MPLL_SELw(val)			_wr32(_REG_BASE_+(0x0006<<2),(UINT)((_rd32(_REG_BASE_+(0x0006<<2))&(~ValSft_L20(BitMask_03)))|ValSft_L20((val)&BitMask_03)))

#define MPLL_MCK_POr			(ValSft_R19(_rd32(_REG_BASE_+(0x0006<<2)))&BitMask_01)
#define MPLL_MCK_POw(val)		_wr32(_REG_BASE_+(0x0006<<2),(UINT)((_rd32(_REG_BASE_+(0x0006<<2))&(~ValSft_L19(BitMask_01)))|ValSft_L19((val)&BitMask_01)))

#define SMCKO_PDr				(ValSft_R31(_rd32(_REG_BASE_+(0x0010<<2)))&BitMask_01)
#define SMCKO_PDw(val)			_wr32(_REG_BASE_+(0x0010<<2),(UINT)((_rd32(_REG_BASE_+(0x0010<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define SMCKO_INVr				(ValSft_R30(_rd32(_REG_BASE_+(0x0010<<2)))&BitMask_01)
#define SMCKO_INVw(val)			_wr32(_REG_BASE_+(0x0010<<2),(UINT)((_rd32(_REG_BASE_+(0x0010<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define SMCKO_DIVr				(ValSft_R24(_rd32(_REG_BASE_+(0x0010<<2)))&BitMask_06)
#define SMCKO_DIVw(val)			_wr32(_REG_BASE_+(0x0010<<2),(UINT)((_rd32(_REG_BASE_+(0x0010<<2))&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define SMCKO_SELr				(ValSft_R22(_rd32(_REG_BASE_+(0x0010<<2)))&BitMask_02)
#define SMCKO_SELw(val)			_wr32(_REG_BASE_+(0x0010<<2),(UINT)((_rd32(_REG_BASE_+(0x0010<<2))&(~ValSft_L22(BitMask_02)))|ValSft_L22((val)&BitMask_02)))

#define SMCK_DIVr				(ValSft_R16(_rd32(_REG_BASE_+(0x0010<<2)))&BitMask_06)
#define SMCK_DIVw(val)			_wr32(_REG_BASE_+(0x0010<<2),(UINT)((_rd32(_REG_BASE_+(0x0010<<2))&(~ValSft_L16(BitMask_06)))|ValSft_L16((val)&BitMask_06)))

#define SMCKO_LOCKr				(ValSft_R15(_rd32(_REG_BASE_+(0x0010<<2)))&BitMask_01)
#define SMCKO_LOCKw(val)		_wr32(_REG_BASE_+(0x0010<<2),(UINT)((_rd32(_REG_BASE_+(0x0010<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define SMCKO_PHASEr			(ValSft_R08(_rd32(_REG_BASE_+(0x0010<<2)))&BitMask_06)
#define SMCKO_PHASEw(val)		_wr32(_REG_BASE_+(0x0010<<2),(UINT)((_rd32(_REG_BASE_+(0x0010<<2))&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define SMCKO_CDRV_INr			(ValSft_R06(_rd32(_REG_BASE_+(0x0010<<2)))&BitMask_02)
#define SMCKO_CDRV_INw(val)		_wr32(_REG_BASE_+(0x0010<<2),(UINT)((_rd32(_REG_BASE_+(0x0010<<2))&(~ValSft_L06(BitMask_02)))|ValSft_L06((val)&BitMask_02)))

#define FPCK_PDr				(ValSft_R07(_rd32(_REG_BASE_+(0x0011<<2)))&BitMask_01)
#define FPCK_PDw(val)			_wr32(_REG_BASE_+(0x0011<<2),(UINT)((_rd32(_REG_BASE_+(0x0011<<2))&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

#define FPCK_SELr				(ValSft_R03(_rd32(_REG_BASE_+(0x0011<<2)))&BitMask_01)
#define FPCK_SELw(val)			_wr32(_REG_BASE_+(0x0011<<2),(UINT)((_rd32(_REG_BASE_+(0x0011<<2))&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))

#define FPCK_DIVr				(ValSft_R00(_rd32(_REG_BASE_+(0x0011<<2)))&BitMask_03)
#define FPCK_DIVw(val)			_wr32(_REG_BASE_+(0x0011<<2),(UINT)((_rd32(_REG_BASE_+(0x0011<<2))&(~ValSft_L00(BitMask_03)))|ValSft_L00((val)&BitMask_03)))

#define PPCK_PDr				(ValSft_R07(_rd32(_REG_BASE_+(0x0012<<2)))&BitMask_01)
#define PPCK_PDw(val)			_wr32(_REG_BASE_+(0x0012<<2),(UINT)((_rd32(_REG_BASE_+(0x0012<<2))&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

#define PPCK_SELr				(ValSft_R03(_rd32(_REG_BASE_+(0x0012<<2)))&BitMask_02)
#define PPCK_SELw(val)			_wr32(_REG_BASE_+(0x0012<<2),(UINT)((_rd32(_REG_BASE_+(0x0012<<2))&(~ValSft_L03(BitMask_02)))|ValSft_L03((val)&BitMask_02)))

#define PPCK_DIVr				(ValSft_R00(_rd32(_REG_BASE_+(0x0012<<2)))&BitMask_03)
#define PPCK_DIVw(val)			_wr32(_REG_BASE_+(0x0012<<2),(UINT)((_rd32(_REG_BASE_+(0x0012<<2))&(~ValSft_L00(BitMask_03)))|ValSft_L00((val)&BitMask_03)))

#define SLCK_PDr				(ValSft_R06(_rd32(_REG_BASE_+(0x0013<<2)))&BitMask_01)
#define SLCK_PDw(val)			_wr32(_REG_BASE_+(0x0013<<2),(UINT)((_rd32(_REG_BASE_+(0x0013<<2))&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))

#define SLCK_SELr				(ValSft_R05(_rd32(_REG_BASE_+(0x0013<<2)))&BitMask_01)
#define SLCK_SELw(val)			_wr32(_REG_BASE_+(0x0013<<2),(UINT)((_rd32(_REG_BASE_+(0x0013<<2))&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))

#define MSCK_PDr				(ValSft_R04(_rd32(_REG_BASE_+(0x0013<<2)))&BitMask_01)
#define MSCK_PDw(val)			_wr32(_REG_BASE_+(0x0013<<2),(UINT)((_rd32(_REG_BASE_+(0x0013<<2))&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))

#define MSCK_SELr				(ValSft_R03(_rd32(_REG_BASE_+(0x0013<<2)))&BitMask_01)
#define MSCK_SELw(val)			_wr32(_REG_BASE_+(0x0013<<2),(UINT)((_rd32(_REG_BASE_+(0x0013<<2))&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))

#define TPCK_PDr				(ValSft_R02(_rd32(_REG_BASE_+(0x0013<<2)))&BitMask_01)
#define TPCK_PDw(val)			_wr32(_REG_BASE_+(0x0013<<2),(UINT)((_rd32(_REG_BASE_+(0x0013<<2))&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))

#define TPCK_SELr				(ValSft_R00(_rd32(_REG_BASE_+(0x0013<<2)))&BitMask_02)
#define TPCK_SELw(val)			_wr32(_REG_BASE_+(0x0013<<2),(UINT)((_rd32(_REG_BASE_+(0x0013<<2))&(~ValSft_L00(BitMask_02)))|ValSft_L00((val)&BitMask_02)))

#define MLCK_ENr				(ValSft_R05(_rd32(_REG_BASE_+(0x0014<<2)))&BitMask_01)
#define MLCK_ENw(val)			_wr32(_REG_BASE_+(0x0014<<2),(UINT)((_rd32(_REG_BASE_+(0x0014<<2))&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))

#define MPCK_PDr				(ValSft_R04(_rd32(_REG_BASE_+(0x0014<<2)))&BitMask_01)
#define MPCK_PDw(val)			_wr32(_REG_BASE_+(0x0014<<2),(UINT)((_rd32(_REG_BASE_+(0x0014<<2))&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))

#define MPCK_SELr				(ValSft_R02(_rd32(_REG_BASE_+(0x0014<<2)))&BitMask_02)
#define MPCK_SELw(val)			_wr32(_REG_BASE_+(0x0014<<2),(UINT)((_rd32(_REG_BASE_+(0x0014<<2))&(~ValSft_L02(BitMask_02)))|ValSft_L02((val)&BitMask_02)))

#define MBCK_PDr				(ValSft_R01(_rd32(_REG_BASE_+(0x0014<<2)))&BitMask_01)
#define MBCK_PDw(val)			_wr32(_REG_BASE_+(0x0014<<2),(UINT)((_rd32(_REG_BASE_+(0x0014<<2))&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define MBCK_SELr				(ValSft_R00(_rd32(_REG_BASE_+(0x0014<<2)))&BitMask_01)
#define MBCK_SELw(val)			_wr32(_REG_BASE_+(0x0014<<2),(UINT)((_rd32(_REG_BASE_+(0x0014<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define ECKO_PDr				(ValSft_R27(_rd32(_REG_BASE_+(0x0015<<2)))&BitMask_01)
#define ECKO_PDw(val)			_wr32(_REG_BASE_+(0x0015<<2),(UINT)((_rd32(_REG_BASE_+(0x0015<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define ECK_PDr					(ValSft_R26(_rd32(_REG_BASE_+(0x0015<<2)))&BitMask_01)
#define ECK_PDw(val)			_wr32(_REG_BASE_+(0x0015<<2),(UINT)((_rd32(_REG_BASE_+(0x0015<<2))&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define ECK_SELr				(ValSft_R25(_rd32(_REG_BASE_+(0x0015<<2)))&BitMask_01)
#define ECK_SELw(val)			_wr32(_REG_BASE_+(0x0015<<2),(UINT)((_rd32(_REG_BASE_+(0x0015<<2))&(~ValSft_L25(BitMask_01)))|ValSft_L25((val)&BitMask_01)))

#define ACK_PDr					(ValSft_R31(_rd32(_REG_BASE_+(0x0016<<2)))&BitMask_01)
#define ACK_PDw(val)			_wr32(_REG_BASE_+(0x0016<<2),(UINT)((_rd32(_REG_BASE_+(0x0016<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define ACKO_INVr				(ValSft_R30(_rd32(_REG_BASE_+(0x0016<<2)))&BitMask_01)
#define ACKO_INVw(val)			_wr32(_REG_BASE_+(0x0016<<2),(UINT)((_rd32(_REG_BASE_+(0x0016<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define ACK_DIVr				(ValSft_R24(_rd32(_REG_BASE_+(0x0016<<2)))&BitMask_06)
#define ACK_DIVw(val)			_wr32(_REG_BASE_+(0x0016<<2),(UINT)((_rd32(_REG_BASE_+(0x0016<<2))&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define MCK_SELr				(ValSft_R31(_rd32(_REG_BASE_+(0x0017<<2)))&BitMask_01)
#define MCK_SELw(val)			_wr32(_REG_BASE_+(0x0017<<2),(UINT)((_rd32(_REG_BASE_+(0x0017<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define RSYNC_UPr				(ValSft_R31(_rd32(_REG_BASE_+(0x0020<<2)))&BitMask_01)
#define RSYNC_UPw(val)			_wr32(_REG_BASE_+(0x0020<<2),(UINT)((_rd32(_REG_BASE_+(0x0020<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define RDES_CNTRSr				(ValSft_R30(_rd32(_REG_BASE_+(0x0020<<2)))&BitMask_01)
#define RDES_CNTRSw(val)		_wr32(_REG_BASE_+(0x0020<<2),(UINT)((_rd32(_REG_BASE_+(0x0020<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define RDES_HALNr				(ValSft_R29(_rd32(_REG_BASE_+(0x0020<<2)))&BitMask_01)
#define RDES_HALNw(val)			_wr32(_REG_BASE_+(0x0020<<2),(UINT)((_rd32(_REG_BASE_+(0x0020<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define RDES_VALNr				(ValSft_R28(_rd32(_REG_BASE_+(0x0020<<2)))&BitMask_01)
#define RDES_VALNw(val)			_wr32(_REG_BASE_+(0x0020<<2),(UINT)((_rd32(_REG_BASE_+(0x0020<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define RSYNC_AUTOr				(ValSft_R24(_rd32(_REG_BASE_+(0x0020<<2)))&BitMask_03)
#define RSYNC_AUTOw(val)		_wr32(_REG_BASE_+(0x0020<<2),(UINT)((_rd32(_REG_BASE_+(0x0020<<2))&(~ValSft_L24(BitMask_03)))|ValSft_L24((val)&BitMask_03)))

#define RDES_LVSETr				(ValSft_R23(_rd32(_REG_BASE_+(0x0020<<2)))&BitMask_01)
#define RDES_LVSETw(val)		_wr32(_REG_BASE_+(0x0020<<2),(UINT)((_rd32(_REG_BASE_+(0x0020<<2))&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define RDES_CHr				(ValSft_R20(_rd32(_REG_BASE_+(0x0020<<2)))&BitMask_02)
#define RDES_CHw(val)			_wr32(_REG_BASE_+(0x0020<<2),(UINT)((_rd32(_REG_BASE_+(0x0020<<2))&(~ValSft_L20(BitMask_02)))|ValSft_L20((val)&BitMask_02)))

#define RDES_BITr				(ValSft_R18(_rd32(_REG_BASE_+(0x0020<<2)))&BitMask_02)
#define RDES_BITw(val)			_wr32(_REG_BASE_+(0x0020<<2),(UINT)((_rd32(_REG_BASE_+(0x0020<<2))&(~ValSft_L18(BitMask_02)))|ValSft_L18((val)&BitMask_02)))

#define RDES_BITAr				(ValSft_R16(_rd32(_REG_BASE_+(0x0020<<2)))&BitMask_02)
#define RDES_BITAw(val)			_wr32(_REG_BASE_+(0x0020<<2),(UINT)((_rd32(_REG_BASE_+(0x0020<<2))&(~ValSft_L16(BitMask_02)))|ValSft_L16((val)&BitMask_02)))

#define LVDS_LSBr				(ValSft_R15(_rd32(_REG_BASE_+(0x0020<<2)))&BitMask_01)
#define LVDS_LSBw(val)			_wr32(_REG_BASE_+(0x0020<<2),(UINT)((_rd32(_REG_BASE_+(0x0020<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define MIPI_SELr				(ValSft_R14(_rd32(_REG_BASE_+(0x0020<<2)))&BitMask_01)
#define MIPI_SELw(val)			_wr32(_REG_BASE_+(0x0020<<2),(UINT)((_rd32(_REG_BASE_+(0x0020<<2))&(~ValSft_L14(BitMask_01)))|ValSft_L14((val)&BitMask_01)))

#define MIPI_ECCONr				(ValSft_R13(_rd32(_REG_BASE_+(0x0020<<2)))&BitMask_01)
#define MIPI_ECCONw(val)		_wr32(_REG_BASE_+(0x0020<<2),(UINT)((_rd32(_REG_BASE_+(0x0020<<2))&(~ValSft_L13(BitMask_01)))|ValSft_L13((val)&BitMask_01)))

#define MIPI_FSMSKr				(ValSft_R12(_rd32(_REG_BASE_+(0x0020<<2)))&BitMask_01)
#define MIPI_FSMSKw(val)		_wr32(_REG_BASE_+(0x0020<<2),(UINT)((_rd32(_REG_BASE_+(0x0020<<2))&(~ValSft_L12(BitMask_01)))|ValSft_L12((val)&BitMask_01)))

#define MIPI_LSMSKr				(ValSft_R11(_rd32(_REG_BASE_+(0x0020<<2)))&BitMask_01)
#define MIPI_LSMSKw(val)		_wr32(_REG_BASE_+(0x0020<<2),(UINT)((_rd32(_REG_BASE_+(0x0020<<2))&(~ValSft_L11(BitMask_01)))|ValSft_L11((val)&BitMask_01)))

#define RDES_MODEr				(ValSft_R08(_rd32(_REG_BASE_+(0x0020<<2)))&BitMask_03)
#define RDES_MODEw(val)			_wr32(_REG_BASE_+(0x0020<<2),(UINT)((_rd32(_REG_BASE_+(0x0020<<2))&(~ValSft_L08(BitMask_03)))|ValSft_L08((val)&BitMask_03)))

#define RDES_POr				(ValSft_R00(_rd32(_REG_BASE_+(0x0020<<2)))&BitMask_04)
#define RDES_POw(val)			_wr32(_REG_BASE_+(0x0020<<2),(UINT)((_rd32(_REG_BASE_+(0x0020<<2))&(~ValSft_L00(BitMask_04)))|ValSft_L00((val)&BitMask_04)))

#define RDES_VTLONr				(ValSft_R31(_rd32(_REG_BASE_+(0x0021<<2)))&BitMask_01)
#define RDES_VTLONw(val)		_wr32(_REG_BASE_+(0x0021<<2),(UINT)((_rd32(_REG_BASE_+(0x0021<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define RDES_VTLSTr				(ValSft_R16(_rd32(_REG_BASE_+(0x0021<<2)))&BitMask_08)
#define RDES_VTLSTw(val)		_wr32(_REG_BASE_+(0x0021<<2),(UINT)((_rd32(_REG_BASE_+(0x0021<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define RDES_VTLWr				(ValSft_R00(_rd32(_REG_BASE_+(0x0021<<2)))&BitMask_16)
#define RDES_VTLWw(val)			_wr32(_REG_BASE_+(0x0021<<2),(UINT)((_rd32(_REG_BASE_+(0x0021<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define LVDS_CKDLYr				(ValSft_R28(_rd32(_REG_BASE_+(0x0022<<2)))&BitMask_04)
#define LVDS_CKDLYw(val)		_wr32(_REG_BASE_+(0x0022<<2),(UINT)((_rd32(_REG_BASE_+(0x0022<<2))&(~ValSft_L28(BitMask_04)))|ValSft_L28((val)&BitMask_04)))

#define LCK4_PHASEr				(ValSft_R26(_rd32(_REG_BASE_+(0x0022<<2)))&BitMask_02)
#define LCK4_PHASEw(val)		_wr32(_REG_BASE_+(0x0022<<2),(UINT)((_rd32(_REG_BASE_+(0x0022<<2))&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define RDES_VSPOLr				(ValSft_R25(_rd32(_REG_BASE_+(0x0022<<2)))&BitMask_01)
#define RDES_VSPOLw(val)		_wr32(_REG_BASE_+(0x0022<<2),(UINT)((_rd32(_REG_BASE_+(0x0022<<2))&(~ValSft_L25(BitMask_01)))|ValSft_L25((val)&BitMask_01)))

#define RDES_HSPOLr				(ValSft_R24(_rd32(_REG_BASE_+(0x0022<<2)))&BitMask_01)
#define RDES_HSPOLw(val)		_wr32(_REG_BASE_+(0x0022<<2),(UINT)((_rd32(_REG_BASE_+(0x0022<<2))&(~ValSft_L24(BitMask_01)))|ValSft_L24((val)&BitMask_01)))

#define RDES_RDSEr				(ValSft_R23(_rd32(_REG_BASE_+(0x0022<<2)))&BitMask_01)
#define RDES_RDSEw(val)			_wr32(_REG_BASE_+(0x0022<<2),(UINT)((_rd32(_REG_BASE_+(0x0022<<2))&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define RDES_RCHSELr			(ValSft_R20(_rd32(_REG_BASE_+(0x0022<<2)))&BitMask_03)
#define RDES_RCHSELw(val)		_wr32(_REG_BASE_+(0x0022<<2),(UINT)((_rd32(_REG_BASE_+(0x0022<<2))&(~ValSft_L20(BitMask_03)))|ValSft_L20((val)&BitMask_03)))

#define RDES_TCHKr				(ValSft_R16(_rd32(_REG_BASE_+(0x0022<<2)))&BitMask_01)
#define RDES_TCHKw(val)			_wr32(_REG_BASE_+(0x0022<<2),(UINT)((_rd32(_REG_BASE_+(0x0022<<2))&(~ValSft_L16(BitMask_01)))|ValSft_L16((val)&BitMask_01)))

#define RDES_INVr				(ValSft_R04(_rd32(_REG_BASE_+(0x0022<<2)))&BitMask_04)
#define RDES_INVw(val)			_wr32(_REG_BASE_+(0x0022<<2),(UINT)((_rd32(_REG_BASE_+(0x0022<<2))&(~ValSft_L04(BitMask_04)))|ValSft_L04((val)&BitMask_04)))

#define RDES_SCHr				(ValSft_R00(_rd32(_REG_BASE_+(0x0022<<2)))&BitMask_04)
#define RDES_SCHw(val)			_wr32(_REG_BASE_+(0x0022<<2),(UINT)((_rd32(_REG_BASE_+(0x0022<<2))&(~ValSft_L00(BitMask_04)))|ValSft_L00((val)&BitMask_04)))

#define LDO3_SELr				(ValSft_R12(_rd32(_REG_BASE_+(0x0023<<2)))&BitMask_03)
#define LDO3_SELw(val)			_wr32(_REG_BASE_+(0x0023<<2),(UINT)((_rd32(_REG_BASE_+(0x0023<<2))&(~ValSft_L12(BitMask_03)))|ValSft_L12((val)&BitMask_03)))

#define LDO2_SELr				(ValSft_R08(_rd32(_REG_BASE_+(0x0023<<2)))&BitMask_03)
#define LDO2_SELw(val)			_wr32(_REG_BASE_+(0x0023<<2),(UINT)((_rd32(_REG_BASE_+(0x0023<<2))&(~ValSft_L08(BitMask_03)))|ValSft_L08((val)&BitMask_03)))

#define LDO1_SELr				(ValSft_R04(_rd32(_REG_BASE_+(0x0023<<2)))&BitMask_03)
#define LDO1_SELw(val)			_wr32(_REG_BASE_+(0x0023<<2),(UINT)((_rd32(_REG_BASE_+(0x0023<<2))&(~ValSft_L04(BitMask_03)))|ValSft_L04((val)&BitMask_03)))

#define LDO0_SELr				(ValSft_R00(_rd32(_REG_BASE_+(0x0023<<2)))&BitMask_03)
#define LDO0_SELw(val)			_wr32(_REG_BASE_+(0x0023<<2),(UINT)((_rd32(_REG_BASE_+(0x0023<<2))&(~ValSft_L00(BitMask_03)))|ValSft_L00((val)&BitMask_03)))

#define LDIDLY3r				(ValSft_R12(_rd32(_REG_BASE_+(0x0024<<2)))&BitMask_04)
#define LDIDLY3w(val)			_wr32(_REG_BASE_+(0x0024<<2),(UINT)((_rd32(_REG_BASE_+(0x0024<<2))&(~ValSft_L12(BitMask_04)))|ValSft_L12((val)&BitMask_04)))

#define LDIDLY2r				(ValSft_R08(_rd32(_REG_BASE_+(0x0024<<2)))&BitMask_04)
#define LDIDLY2w(val)			_wr32(_REG_BASE_+(0x0024<<2),(UINT)((_rd32(_REG_BASE_+(0x0024<<2))&(~ValSft_L08(BitMask_04)))|ValSft_L08((val)&BitMask_04)))

#define LDIDLY1r				(ValSft_R04(_rd32(_REG_BASE_+(0x0024<<2)))&BitMask_04)
#define LDIDLY1w(val)			_wr32(_REG_BASE_+(0x0024<<2),(UINT)((_rd32(_REG_BASE_+(0x0024<<2))&(~ValSft_L04(BitMask_04)))|ValSft_L04((val)&BitMask_04)))

#define LDIDLY0r				(ValSft_R00(_rd32(_REG_BASE_+(0x0024<<2)))&BitMask_04)
#define LDIDLY0w(val)			_wr32(_REG_BASE_+(0x0024<<2),(UINT)((_rd32(_REG_BASE_+(0x0024<<2))&(~ValSft_L00(BitMask_04)))|ValSft_L00((val)&BitMask_04)))

#define RDES_HTWr				(ValSft_R16(_rd32(_REG_BASE_+(0x0025<<2)))&BitMask_16)
#define RDES_HTWw(val)			_wr32(_REG_BASE_+(0x0025<<2),(UINT)((_rd32(_REG_BASE_+(0x0025<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define RDES_VTWr				(ValSft_R00(_rd32(_REG_BASE_+(0x0025<<2)))&BitMask_16)
#define RDES_VTWw(val)			_wr32(_REG_BASE_+(0x0025<<2),(UINT)((_rd32(_REG_BASE_+(0x0025<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define RDES_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x0026<<2)))&BitMask_12)
#define RDES_HSPw(val)			_wr32(_REG_BASE_+(0x0026<<2),(UINT)((_rd32(_REG_BASE_+(0x0026<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define RDES_HWr				(ValSft_R00(_rd32(_REG_BASE_+(0x0026<<2)))&BitMask_13)
#define RDES_HWw(val)			_wr32(_REG_BASE_+(0x0026<<2),(UINT)((_rd32(_REG_BASE_+(0x0026<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define RDES_OPOSLr				(ValSft_R00(_rd32(_REG_BASE_+(0x0027<<2)))&BitMask_16)
#define RDES_OPOSLw(val)		_wr32(_REG_BASE_+(0x0027<<2),(UINT)((_rd32(_REG_BASE_+(0x0027<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define RDES_OPOS1r				(ValSft_R16(_rd32(_REG_BASE_+(0x0028<<2)))&BitMask_16)
#define RDES_OPOS1w(val)		_wr32(_REG_BASE_+(0x0028<<2),(UINT)((_rd32(_REG_BASE_+(0x0028<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define RDES_SYNC0r				(ValSft_R16(_rd32(_REG_BASE_+(0x0029<<2)))&BitMask_16)
#define RDES_SYNC0w(val)		_wr32(_REG_BASE_+(0x0029<<2),(UINT)((_rd32(_REG_BASE_+(0x0029<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define RDES_SYNC1r				(ValSft_R00(_rd32(_REG_BASE_+(0x0029<<2)))&BitMask_16)
#define RDES_SYNC1w(val)		_wr32(_REG_BASE_+(0x0029<<2),(UINT)((_rd32(_REG_BASE_+(0x0029<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define RDES_SYNC2r				(ValSft_R16(_rd32(_REG_BASE_+(0x002a<<2)))&BitMask_16)
#define RDES_SYNC2w(val)		_wr32(_REG_BASE_+(0x002a<<2),(UINT)((_rd32(_REG_BASE_+(0x002a<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define HSGO_WIDr				(ValSft_R00(_rd32(_REG_BASE_+(0x002a<<2)))&BitMask_16)
#define HSGO_WIDw(val)			_wr32(_REG_BASE_+(0x002a<<2),(UINT)((_rd32(_REG_BASE_+(0x002a<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define RDES_SYNC3_LEFr			(ValSft_R16(_rd32(_REG_BASE_+(0x002b<<2)))&BitMask_16)
#define RDES_SYNC3_LEFw(val)	_wr32(_REG_BASE_+(0x002b<<2),(UINT)((_rd32(_REG_BASE_+(0x002b<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define RDES_SYNC3_LELr			(ValSft_R00(_rd32(_REG_BASE_+(0x002b<<2)))&BitMask_16)
#define RDES_SYNC3_LELw(val)	_wr32(_REG_BASE_+(0x002b<<2),(UINT)((_rd32(_REG_BASE_+(0x002b<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define RDES_SYNC3_LEVr			(ValSft_R16(_rd32(_REG_BASE_+(0x002c<<2)))&BitMask_16)
#define RDES_SYNC3_LEVw(val)	_wr32(_REG_BASE_+(0x002c<<2),(UINT)((_rd32(_REG_BASE_+(0x002c<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define RDES_SYNC3_S1Fr			(ValSft_R00(_rd32(_REG_BASE_+(0x002c<<2)))&BitMask_16)
#define RDES_SYNC3_S1Fw(val)	_wr32(_REG_BASE_+(0x002c<<2),(UINT)((_rd32(_REG_BASE_+(0x002c<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define RDES_SYNC3_S1Lr			(ValSft_R16(_rd32(_REG_BASE_+(0x002d<<2)))&BitMask_16)
#define RDES_SYNC3_S1Lw(val)	_wr32(_REG_BASE_+(0x002d<<2),(UINT)((_rd32(_REG_BASE_+(0x002d<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define RDES_SYNC3_S1Vr			(ValSft_R00(_rd32(_REG_BASE_+(0x002d<<2)))&BitMask_16)
#define RDES_SYNC3_S1Vw(val)	_wr32(_REG_BASE_+(0x002d<<2),(UINT)((_rd32(_REG_BASE_+(0x002d<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define RDES_SYNC3_MSKr			(ValSft_R00(_rd32(_REG_BASE_+(0x002f<<2)))&BitMask_16)
#define RDES_SYNC3_MSKw(val)	_wr32(_REG_BASE_+(0x002f<<2),(UINT)((_rd32(_REG_BASE_+(0x002f<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define RSYNC_THr				(ValSft_R00(_rd32(_REG_BASE_+(0x0030<<2)))&BitMask_32)
#define RSYNC_THw(val)			_wr32(_REG_BASE_+(0x0030<<2),(UINT)((_rd32(_REG_BASE_+(0x0030<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define MIPI_FSr				(ValSft_R24(_rd32(_REG_BASE_+(0x0031<<2)))&BitMask_06)
#define MIPI_FSw(val)			_wr32(_REG_BASE_+(0x0031<<2),(UINT)((_rd32(_REG_BASE_+(0x0031<<2))&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define MIPI_FEr				(ValSft_R16(_rd32(_REG_BASE_+(0x0031<<2)))&BitMask_06)
#define MIPI_FEw(val)			_wr32(_REG_BASE_+(0x0031<<2),(UINT)((_rd32(_REG_BASE_+(0x0031<<2))&(~ValSft_L16(BitMask_06)))|ValSft_L16((val)&BitMask_06)))

#define MIPI_LSr				(ValSft_R08(_rd32(_REG_BASE_+(0x0031<<2)))&BitMask_06)
#define MIPI_LSw(val)			_wr32(_REG_BASE_+(0x0031<<2),(UINT)((_rd32(_REG_BASE_+(0x0031<<2))&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define MIPI_LEr				(ValSft_R00(_rd32(_REG_BASE_+(0x0031<<2)))&BitMask_06)
#define MIPI_LEw(val)			_wr32(_REG_BASE_+(0x0031<<2),(UINT)((_rd32(_REG_BASE_+(0x0031<<2))&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define MIPI_IDSELr				(ValSft_R16(_rd32(_REG_BASE_+(0x0032<<2)))&BitMask_08)
#define MIPI_IDSELw(val)		_wr32(_REG_BASE_+(0x0032<<2),(UINT)((_rd32(_REG_BASE_+(0x0032<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define MIPI_IDLEr				(ValSft_R00(_rd32(_REG_BASE_+(0x0032<<2)))&BitMask_16)
#define MIPI_IDLEw(val)			_wr32(_REG_BASE_+(0x0032<<2),(UINT)((_rd32(_REG_BASE_+(0x0032<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define MIPI_IDS1r				(ValSft_R16(_rd32(_REG_BASE_+(0x0033<<2)))&BitMask_16)
#define MIPI_IDS1w(val)			_wr32(_REG_BASE_+(0x0033<<2),(UINT)((_rd32(_REG_BASE_+(0x0033<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define MIPI_IDS2r				(ValSft_R00(_rd32(_REG_BASE_+(0x0033<<2)))&BitMask_16)
#define MIPI_IDS2w(val)			_wr32(_REG_BASE_+(0x0033<<2),(UINT)((_rd32(_REG_BASE_+(0x0033<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define MIPI_IDMSKr				(ValSft_R16(_rd32(_REG_BASE_+(0x0034<<2)))&BitMask_16)
#define MIPI_IDMSKw(val)		_wr32(_REG_BASE_+(0x0034<<2),(UINT)((_rd32(_REG_BASE_+(0x0034<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define MIPI_EMBIDLr			(ValSft_R08(_rd32(_REG_BASE_+(0x0034<<2)))&BitMask_08)
#define MIPI_EMBIDLw(val)		_wr32(_REG_BASE_+(0x0034<<2),(UINT)((_rd32(_REG_BASE_+(0x0034<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define MIPI_EMBIDSr			(ValSft_R00(_rd32(_REG_BASE_+(0x0034<<2)))&BitMask_08)
#define MIPI_EMBIDSw(val)		_wr32(_REG_BASE_+(0x0034<<2),(UINT)((_rd32(_REG_BASE_+(0x0034<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define LWDR_POr				(ValSft_R31(_rd32(_REG_BASE_+(0x0035<<2)))&BitMask_01)
#define LWDR_POw(val)			_wr32(_REG_BASE_+(0x0035<<2),(UINT)((_rd32(_REG_BASE_+(0x0035<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define LWDR_3Pr				(ValSft_R30(_rd32(_REG_BASE_+(0x0035<<2)))&BitMask_01)
#define LWDR_3Pw(val)			_wr32(_REG_BASE_+(0x0035<<2),(UINT)((_rd32(_REG_BASE_+(0x0035<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define MIPI_ERR_CLRr			(ValSft_R29(_rd32(_REG_BASE_+(0x0035<<2)))&BitMask_01)
#define MIPI_ERR_CLRw(val)		_wr32(_REG_BASE_+(0x0035<<2),(UINT)((_rd32(_REG_BASE_+(0x0035<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define MIPI_EMBONr				(ValSft_R28(_rd32(_REG_BASE_+(0x0035<<2)))&BitMask_01)
#define MIPI_EMBONw(val)		_wr32(_REG_BASE_+(0x0035<<2),(UINT)((_rd32(_REG_BASE_+(0x0035<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define MIPI_EMBLCr				(ValSft_R16(_rd32(_REG_BASE_+(0x0035<<2)))&BitMask_08)
#define MIPI_EMBLCw(val)		_wr32(_REG_BASE_+(0x0035<<2),(UINT)((_rd32(_REG_BASE_+(0x0035<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define MIPI_EMBPCr				(ValSft_R00(_rd32(_REG_BASE_+(0x0035<<2)))&BitMask_16)
#define MIPI_EMBPCw(val)		_wr32(_REG_BASE_+(0x0035<<2),(UINT)((_rd32(_REG_BASE_+(0x0035<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define MIPI_LENr				(ValSft_R00(_rd32(_REG_BASE_+(0x0036<<2)))&BitMask_32)
#define MIPI_LENw(val)			_wr32(_REG_BASE_+(0x0036<<2),(UINT)((_rd32(_REG_BASE_+(0x0036<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define MIPI_ERSTr				(ValSft_R23(_rd32(_REG_BASE_+(0x0037<<2)))&BitMask_01)
#define MIPI_ERSTw(val)			_wr32(_REG_BASE_+(0x0037<<2),(UINT)((_rd32(_REG_BASE_+(0x0037<<2))&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define MIPI_CRCMONr			(ValSft_R22(_rd32(_REG_BASE_+(0x0037<<2)))&BitMask_01)
#define MIPI_CRCMONw(val)		_wr32(_REG_BASE_+(0x0037<<2),(UINT)((_rd32(_REG_BASE_+(0x0037<<2))&(~ValSft_L22(BitMask_01)))|ValSft_L22((val)&BitMask_01)))

#define MIPI_CRCRPOSr			(ValSft_R16(_rd32(_REG_BASE_+(0x0038<<2)))&BitMask_16)
#define MIPI_CRCRPOSw(val)		_wr32(_REG_BASE_+(0x0038<<2),(UINT)((_rd32(_REG_BASE_+(0x0038<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define MIPI_CRCMPOSr			(ValSft_R00(_rd32(_REG_BASE_+(0x0038<<2)))&BitMask_16)
#define MIPI_CRCMPOSw(val)		_wr32(_REG_BASE_+(0x0038<<2),(UINT)((_rd32(_REG_BASE_+(0x0038<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define RDES_FNCHKSr			(ValSft_R31(_rd32(_REG_BASE_+(0x0039<<2)))&BitMask_01)
#define RDES_FNCHKSw(val)		_wr32(_REG_BASE_+(0x0039<<2),(UINT)((_rd32(_REG_BASE_+(0x0039<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define RDES_FNCHKEr			(ValSft_R30(_rd32(_REG_BASE_+(0x0039<<2)))&BitMask_01)
#define RDES_FNCHKEw(val)		_wr32(_REG_BASE_+(0x0039<<2),(UINT)((_rd32(_REG_BASE_+(0x0039<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define RDES_FN0MSKr			(ValSft_R29(_rd32(_REG_BASE_+(0x0039<<2)))&BitMask_01)
#define RDES_FN0MSKw(val)		_wr32(_REG_BASE_+(0x0039<<2),(UINT)((_rd32(_REG_BASE_+(0x0039<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define RDES_LNCHKSr			(ValSft_R28(_rd32(_REG_BASE_+(0x0039<<2)))&BitMask_01)
#define RDES_LNCHKSw(val)		_wr32(_REG_BASE_+(0x0039<<2),(UINT)((_rd32(_REG_BASE_+(0x0039<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define RDES_LNCHKEr			(ValSft_R27(_rd32(_REG_BASE_+(0x0039<<2)))&BitMask_01)
#define RDES_LNCHKEw(val)		_wr32(_REG_BASE_+(0x0039<<2),(UINT)((_rd32(_REG_BASE_+(0x0039<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define RDES_LN0MSKr			(ValSft_R26(_rd32(_REG_BASE_+(0x0039<<2)))&BitMask_01)
#define RDES_LN0MSKw(val)		_wr32(_REG_BASE_+(0x0039<<2),(UINT)((_rd32(_REG_BASE_+(0x0039<<2))&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define RDES_FNMAXr				(ValSft_R00(_rd32(_REG_BASE_+(0x0039<<2)))&BitMask_16)
#define RDES_FNMAXw(val)		_wr32(_REG_BASE_+(0x0039<<2),(UINT)((_rd32(_REG_BASE_+(0x0039<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define RDES_MECCONr			(ValSft_R31(_rd32(_REG_BASE_+(0x003a<<2)))&BitMask_01)
#define RDES_MECCONw(val)		_wr32(_REG_BASE_+(0x003a<<2),(UINT)((_rd32(_REG_BASE_+(0x003a<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define RDES_MECC1r				(ValSft_R16(_rd32(_REG_BASE_+(0x003a<<2)))&BitMask_08)
#define RDES_MECC1w(val)		_wr32(_REG_BASE_+(0x003a<<2),(UINT)((_rd32(_REG_BASE_+(0x003a<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define RDES_MECC2r				(ValSft_R08(_rd32(_REG_BASE_+(0x003a<<2)))&BitMask_08)
#define RDES_MECC2w(val)		_wr32(_REG_BASE_+(0x003a<<2),(UINT)((_rd32(_REG_BASE_+(0x003a<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define RDES_MECC3r				(ValSft_R00(_rd32(_REG_BASE_+(0x003a<<2)))&BitMask_08)
#define RDES_MECC3w(val)		_wr32(_REG_BASE_+(0x003a<<2),(UINT)((_rd32(_REG_BASE_+(0x003a<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define RDES_VC0r				(ValSft_R30(_rd32(_REG_BASE_+(0x003b<<2)))&BitMask_02)
#define RDES_VC0w(val)			_wr32(_REG_BASE_+(0x003b<<2),(UINT)((_rd32(_REG_BASE_+(0x003b<<2))&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define RDES_VC1r				(ValSft_R28(_rd32(_REG_BASE_+(0x003b<<2)))&BitMask_02)
#define RDES_VC1w(val)			_wr32(_REG_BASE_+(0x003b<<2),(UINT)((_rd32(_REG_BASE_+(0x003b<<2))&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define RDES_SSCHr				(ValSft_R16(_rd32(_REG_BASE_+(0x003b<<2)))&BitMask_04)
#define RDES_SSCHw(val)			_wr32(_REG_BASE_+(0x003b<<2),(UINT)((_rd32(_REG_BASE_+(0x003b<<2))&(~ValSft_L16(BitMask_04)))|ValSft_L16((val)&BitMask_04)))

#define RDES_WCAUTOr			(ValSft_R02(_rd32(_REG_BASE_+(0x003b<<2)))&BitMask_01)
#define RDES_WCAUTOw(val)		_wr32(_REG_BASE_+(0x003b<<2),(UINT)((_rd32(_REG_BASE_+(0x003b<<2))&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))

#define RDES_WCCHKr				(ValSft_R01(_rd32(_REG_BASE_+(0x003b<<2)))&BitMask_01)
#define RDES_WCCHKw(val)		_wr32(_REG_BASE_+(0x003b<<2),(UINT)((_rd32(_REG_BASE_+(0x003b<<2))&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define RDES_WCCCHKr			(ValSft_R00(_rd32(_REG_BASE_+(0x003b<<2)))&BitMask_01)
#define RDES_WCCCHKw(val)		_wr32(_REG_BASE_+(0x003b<<2),(UINT)((_rd32(_REG_BASE_+(0x003b<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define RDES_WCr				(ValSft_R16(_rd32(_REG_BASE_+(0x003c<<2)))&BitMask_16)
#define RDES_WCw(val)			_wr32(_REG_BASE_+(0x003c<<2),(UINT)((_rd32(_REG_BASE_+(0x003c<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define RDES_WCGAPr				(ValSft_R00(_rd32(_REG_BASE_+(0x003c<<2)))&BitMask_16)
#define RDES_WCGAPw(val)		_wr32(_REG_BASE_+(0x003c<<2),(UINT)((_rd32(_REG_BASE_+(0x003c<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define RDES_LOCKPOSLr			(ValSft_R16(_rd32(_REG_BASE_+(0x003d<<2)))&BitMask_16)
#define RDES_LOCKPOSLw(val)		_wr32(_REG_BASE_+(0x003d<<2),(UINT)((_rd32(_REG_BASE_+(0x003d<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define RDES_LOCKPOS1r			(ValSft_R00(_rd32(_REG_BASE_+(0x003d<<2)))&BitMask_16)
#define RDES_LOCKPOS1w(val)		_wr32(_REG_BASE_+(0x003d<<2),(UINT)((_rd32(_REG_BASE_+(0x003d<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define RDES_VLOCKPOSLr			(ValSft_R16(_rd32(_REG_BASE_+(0x003e<<2)))&BitMask_16)
#define RDES_VLOCKPOSLw(val)	_wr32(_REG_BASE_+(0x003e<<2),(UINT)((_rd32(_REG_BASE_+(0x003e<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define RDES_VLOCKPOS1r			(ValSft_R00(_rd32(_REG_BASE_+(0x003e<<2)))&BitMask_16)
#define RDES_VLOCKPOS1w(val)	_wr32(_REG_BASE_+(0x003e<<2),(UINT)((_rd32(_REG_BASE_+(0x003e<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define MIPI_BITCONr			(ValSft_R31(_rd32(_REG_BASE_+(0x003f<<2)))&BitMask_01)
#define MIPI_BITCONw(val)		_wr32(_REG_BASE_+(0x003f<<2),(UINT)((_rd32(_REG_BASE_+(0x003f<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define MIPI_BITMODELr			(ValSft_R26(_rd32(_REG_BASE_+(0x003f<<2)))&BitMask_02)
#define MIPI_BITMODELw(val)		_wr32(_REG_BASE_+(0x003f<<2),(UINT)((_rd32(_REG_BASE_+(0x003f<<2))&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define MIPI_BITMODESr			(ValSft_R24(_rd32(_REG_BASE_+(0x003f<<2)))&BitMask_02)
#define MIPI_BITMODESw(val)		_wr32(_REG_BASE_+(0x003f<<2),(UINT)((_rd32(_REG_BASE_+(0x003f<<2))&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define SS_HTWr					(ValSft_R16(_rd32(_REG_BASE_+(0x0040<<2)))&BitMask_16)
#define SS_HTWw(val)			_wr32(_REG_BASE_+(0x0040<<2),(UINT)((_rd32(_REG_BASE_+(0x0040<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define SS_VTWr					(ValSft_R00(_rd32(_REG_BASE_+(0x0040<<2)))&BitMask_16)
#define SS_VTWw(val)			_wr32(_REG_BASE_+(0x0040<<2),(UINT)((_rd32(_REG_BASE_+(0x0040<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define SHSO_FPr				(ValSft_R16(_rd32(_REG_BASE_+(0x0041<<2)))&BitMask_16)
#define SHSO_FPw(val)			_wr32(_REG_BASE_+(0x0041<<2),(UINT)((_rd32(_REG_BASE_+(0x0041<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define SHSO_RPr				(ValSft_R00(_rd32(_REG_BASE_+(0x0041<<2)))&BitMask_16)
#define SHSO_RPw(val)			_wr32(_REG_BASE_+(0x0041<<2),(UINT)((_rd32(_REG_BASE_+(0x0041<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define SVSO_FPr				(ValSft_R16(_rd32(_REG_BASE_+(0x0042<<2)))&BitMask_16)
#define SVSO_FPw(val)			_wr32(_REG_BASE_+(0x0042<<2),(UINT)((_rd32(_REG_BASE_+(0x0042<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define SVSO_RPr				(ValSft_R00(_rd32(_REG_BASE_+(0x0042<<2)))&BitMask_16)
#define SVSO_RPw(val)			_wr32(_REG_BASE_+(0x0042<<2),(UINT)((_rd32(_REG_BASE_+(0x0042<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define SVSO_LPr				(ValSft_R16(_rd32(_REG_BASE_+(0x0043<<2)))&BitMask_16)
#define SVSO_LPw(val)			_wr32(_REG_BASE_+(0x0043<<2),(UINT)((_rd32(_REG_BASE_+(0x0043<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define SS_WAVEr				(ValSft_R30(_rd32(_REG_BASE_+(0x0044<<2)))&BitMask_01)
#define SS_WAVEw(val)			_wr32(_REG_BASE_+(0x0044<<2),(UINT)((_rd32(_REG_BASE_+(0x0044<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define SS_OFFr					(ValSft_R29(_rd32(_REG_BASE_+(0x0044<<2)))&BitMask_01)
#define SS_OFFw(val)			_wr32(_REG_BASE_+(0x0044<<2),(UINT)((_rd32(_REG_BASE_+(0x0044<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define SHSO_EXSSr				(ValSft_R28(_rd32(_REG_BASE_+(0x0044<<2)))&BitMask_01)
#define SHSO_EXSSw(val)			_wr32(_REG_BASE_+(0x0044<<2),(UINT)((_rd32(_REG_BASE_+(0x0044<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define SVSO_EXSSr				(ValSft_R27(_rd32(_REG_BASE_+(0x0044<<2)))&BitMask_01)
#define SVSO_EXSSw(val)			_wr32(_REG_BASE_+(0x0044<<2),(UINT)((_rd32(_REG_BASE_+(0x0044<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define SHSO_OEr				(ValSft_R26(_rd32(_REG_BASE_+(0x0044<<2)))&BitMask_01)
#define SHSO_OEw(val)			_wr32(_REG_BASE_+(0x0044<<2),(UINT)((_rd32(_REG_BASE_+(0x0044<<2))&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define SVSO_OEr				(ValSft_R25(_rd32(_REG_BASE_+(0x0044<<2)))&BitMask_01)
#define SVSO_OEw(val)			_wr32(_REG_BASE_+(0x0044<<2),(UINT)((_rd32(_REG_BASE_+(0x0044<<2))&(~ValSft_L25(BitMask_01)))|ValSft_L25((val)&BitMask_01)))

#define SHSO_INVr				(ValSft_R24(_rd32(_REG_BASE_+(0x0044<<2)))&BitMask_01)
#define SHSO_INVw(val)			_wr32(_REG_BASE_+(0x0044<<2),(UINT)((_rd32(_REG_BASE_+(0x0044<<2))&(~ValSft_L24(BitMask_01)))|ValSft_L24((val)&BitMask_01)))

#define SVSO_INVr				(ValSft_R23(_rd32(_REG_BASE_+(0x0044<<2)))&BitMask_01)
#define SVSO_INVw(val)			_wr32(_REG_BASE_+(0x0044<<2),(UINT)((_rd32(_REG_BASE_+(0x0044<<2))&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define SHSO_TRGr				(ValSft_R22(_rd32(_REG_BASE_+(0x0044<<2)))&BitMask_01)
#define SHSO_TRGw(val)			_wr32(_REG_BASE_+(0x0044<<2),(UINT)((_rd32(_REG_BASE_+(0x0044<<2))&(~ValSft_L22(BitMask_01)))|ValSft_L22((val)&BitMask_01)))

#define SVSO_TRGr				(ValSft_R21(_rd32(_REG_BASE_+(0x0044<<2)))&BitMask_01)
#define SVSO_TRGw(val)			_wr32(_REG_BASE_+(0x0044<<2),(UINT)((_rd32(_REG_BASE_+(0x0044<<2))&(~ValSft_L21(BitMask_01)))|ValSft_L21((val)&BitMask_01)))

#define EXSS_TRGENr				(ValSft_R31(_rd32(_REG_BASE_+(0x0045<<2)))&BitMask_01)
#define EXSS_TRGENw(val)		_wr32(_REG_BASE_+(0x0045<<2),(UINT)((_rd32(_REG_BASE_+(0x0045<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define EXSS_TRGINVr			(ValSft_R30(_rd32(_REG_BASE_+(0x0045<<2)))&BitMask_01)
#define EXSS_TRGINVw(val)		_wr32(_REG_BASE_+(0x0045<<2),(UINT)((_rd32(_REG_BASE_+(0x0045<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define EXSS_TRGMDr				(ValSft_R28(_rd32(_REG_BASE_+(0x0045<<2)))&BitMask_02)
#define EXSS_TRGMDw(val)		_wr32(_REG_BASE_+(0x0045<<2),(UINT)((_rd32(_REG_BASE_+(0x0045<<2))&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define EXSS_TRGWr				(ValSft_R00(_rd32(_REG_BASE_+(0x0045<<2)))&BitMask_16)
#define EXSS_TRGWw(val)			_wr32(_REG_BASE_+(0x0045<<2),(UINT)((_rd32(_REG_BASE_+(0x0045<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define SS_MSBr					(ValSft_R31(_rd32(_REG_BASE_+(0x0046<<2)))&BitMask_01)
#define SS_MSBw(val)			_wr32(_REG_BASE_+(0x0046<<2),(UINT)((_rd32(_REG_BASE_+(0x0046<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define SS_BCr					(ValSft_R28(_rd32(_REG_BASE_+(0x0046<<2)))&BitMask_03)
#define SS_BCw(val)				_wr32(_REG_BASE_+(0x0046<<2),(UINT)((_rd32(_REG_BASE_+(0x0046<<2))&(~ValSft_L28(BitMask_03)))|ValSft_L28((val)&BitMask_03)))

#define L_I2C_ONr				(ValSft_R15(_rd32(_REG_BASE_+(0x0046<<2)))&BitMask_01)
#define L_I2C_ONw(val)			_wr32(_REG_BASE_+(0x0046<<2),(UINT)((_rd32(_REG_BASE_+(0x0046<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define SS_RSTNr				(ValSft_R14(_rd32(_REG_BASE_+(0x0046<<2)))&BitMask_01)
#define SS_RSTNw(val)			_wr32(_REG_BASE_+(0x0046<<2),(UINT)((_rd32(_REG_BASE_+(0x0046<<2))&(~ValSft_L14(BitMask_01)))|ValSft_L14((val)&BitMask_01)))

#define HLOCKL_POSr				(ValSft_R16(_rd32(_REG_BASE_+(0x0050<<2)))&BitMask_13)
#define HLOCKL_POSw(val)		_wr32(_REG_BASE_+(0x0050<<2),(UINT)((_rd32(_REG_BASE_+(0x0050<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define VLOCKL_POSr				(ValSft_R00(_rd32(_REG_BASE_+(0x0050<<2)))&BitMask_13)
#define VLOCKL_POSw(val)		_wr32(_REG_BASE_+(0x0050<<2),(UINT)((_rd32(_REG_BASE_+(0x0050<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define HLOCKS_POSr				(ValSft_R16(_rd32(_REG_BASE_+(0x0051<<2)))&BitMask_13)
#define HLOCKS_POSw(val)		_wr32(_REG_BASE_+(0x0051<<2),(UINT)((_rd32(_REG_BASE_+(0x0051<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define VLOCKS_POSr				(ValSft_R00(_rd32(_REG_BASE_+(0x0051<<2)))&BitMask_13)
#define VLOCKS_POSw(val)		_wr32(_REG_BASE_+(0x0051<<2),(UINT)((_rd32(_REG_BASE_+(0x0051<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define HSPIr					(ValSft_R16(_rd32(_REG_BASE_+(0x0052<<2)))&BitMask_13)
#define HSPIw(val)				_wr32(_REG_BASE_+(0x0052<<2),(UINT)((_rd32(_REG_BASE_+(0x0052<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define VSPIr					(ValSft_R00(_rd32(_REG_BASE_+(0x0052<<2)))&BitMask_13)
#define VSPIw(val)				_wr32(_REG_BASE_+(0x0052<<2),(UINT)((_rd32(_REG_BASE_+(0x0052<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define BAY_CSTOMLr				(ValSft_R04(_rd32(_REG_BASE_+(0x0053<<2)))&BitMask_02)
#define BAY_CSTOMLw(val)		_wr32(_REG_BASE_+(0x0053<<2),(UINT)((_rd32(_REG_BASE_+(0x0053<<2))&(~ValSft_L04(BitMask_02)))|ValSft_L04((val)&BitMask_02)))

#define BAY_CSTOM1r				(ValSft_R02(_rd32(_REG_BASE_+(0x0053<<2)))&BitMask_02)
#define BAY_CSTOM1w(val)		_wr32(_REG_BASE_+(0x0053<<2),(UINT)((_rd32(_REG_BASE_+(0x0053<<2))&(~ValSft_L02(BitMask_02)))|ValSft_L02((val)&BitMask_02)))

#define HWIr					(ValSft_R16(_rd32(_REG_BASE_+(0x0054<<2)))&BitMask_13)
#define HWIw(val)				_wr32(_REG_BASE_+(0x0054<<2),(UINT)((_rd32(_REG_BASE_+(0x0054<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define VWIr					(ValSft_R00(_rd32(_REG_BASE_+(0x0054<<2)))&BitMask_13)
#define VWIw(val)				_wr32(_REG_BASE_+(0x0054<<2),(UINT)((_rd32(_REG_BASE_+(0x0054<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define TEST_PERIVr				(ValSft_R00(_rd32(_REG_BASE_+(0x0055<<2)))&BitMask_16)
#define TEST_PERIVw(val)		_wr32(_REG_BASE_+(0x0055<<2),(UINT)((_rd32(_REG_BASE_+(0x0055<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define FLDF_SETr				(ValSft_R00(_rd32(_REG_BASE_+(0x0056<<2)))&BitMask_01)
#define FLDF_SETw(val)			_wr32(_REG_BASE_+(0x0056<<2),(UINT)((_rd32(_REG_BASE_+(0x0056<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define POST_ACT_ENr			(ValSft_R05(_rd32(_REG_BASE_+(0x0057<<2)))&BitMask_01)
#define POST_ACT_ENw(val)		_wr32(_REG_BASE_+(0x0057<<2),(UINT)((_rd32(_REG_BASE_+(0x0057<<2))&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))

#define PRE_ACT_ENr				(ValSft_R04(_rd32(_REG_BASE_+(0x0057<<2)))&BitMask_01)
#define PRE_ACT_ENw(val)		_wr32(_REG_BASE_+(0x0057<<2),(UINT)((_rd32(_REG_BASE_+(0x0057<<2))&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))

#define ODM_DI1Dr				(ValSft_R03(_rd32(_REG_BASE_+(0x0057<<2)))&BitMask_01)
#define ODM_DI1Dw(val)			_wr32(_REG_BASE_+(0x0057<<2),(UINT)((_rd32(_REG_BASE_+(0x0057<<2))&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))

#define OCK_EN_INVr				(ValSft_R02(_rd32(_REG_BASE_+(0x0057<<2)))&BitMask_01)
#define OCK_EN_INVw(val)		_wr32(_REG_BASE_+(0x0057<<2),(UINT)((_rd32(_REG_BASE_+(0x0057<<2))&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))

#define OCK_LOCKSELr			(ValSft_R00(_rd32(_REG_BASE_+(0x0057<<2)))&BitMask_02)
#define OCK_LOCKSELw(val)		_wr32(_REG_BASE_+(0x0057<<2),(UINT)((_rd32(_REG_BASE_+(0x0057<<2))&(~ValSft_L00(BitMask_02)))|ValSft_L00((val)&BitMask_02)))

#define OSYNC_THr				(ValSft_R00(_rd32(_REG_BASE_+(0x0058<<2)))&BitMask_32)
#define OSYNC_THw(val)			_wr32(_REG_BASE_+(0x0058<<2),(UINT)((_rd32(_REG_BASE_+(0x0058<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define OSYNC_MODr				(ValSft_R31(_rd32(_REG_BASE_+(0x0059<<2)))&BitMask_01)
#define OSYNC_MODw(val)			_wr32(_REG_BASE_+(0x0059<<2),(UINT)((_rd32(_REG_BASE_+(0x0059<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define OSYNC_POLr				(ValSft_R30(_rd32(_REG_BASE_+(0x0059<<2)))&BitMask_01)
#define OSYNC_POLw(val)			_wr32(_REG_BASE_+(0x0059<<2),(UINT)((_rd32(_REG_BASE_+(0x0059<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define OSYNC_AUTOr				(ValSft_R29(_rd32(_REG_BASE_+(0x0059<<2)))&BitMask_01)
#define OSYNC_AUTOw(val)		_wr32(_REG_BASE_+(0x0059<<2),(UINT)((_rd32(_REG_BASE_+(0x0059<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define OSYNC_ALr				(ValSft_R22(_rd32(_REG_BASE_+(0x0059<<2)))&BitMask_01)
#define OSYNC_ALw(val)			_wr32(_REG_BASE_+(0x0059<<2),(UINT)((_rd32(_REG_BASE_+(0x0059<<2))&(~ValSft_L22(BitMask_01)))|ValSft_L22((val)&BitMask_01)))

#define OSYNC_UPSELr			(ValSft_R21(_rd32(_REG_BASE_+(0x0059<<2)))&BitMask_01)
#define OSYNC_UPSELw(val)		_wr32(_REG_BASE_+(0x0059<<2),(UINT)((_rd32(_REG_BASE_+(0x0059<<2))&(~ValSft_L21(BitMask_01)))|ValSft_L21((val)&BitMask_01)))

#define OSYNC_UPr				(ValSft_R20(_rd32(_REG_BASE_+(0x0059<<2)))&BitMask_01)
#define OSYNC_UPw(val)			_wr32(_REG_BASE_+(0x0059<<2),(UINT)((_rd32(_REG_BASE_+(0x0059<<2))&(~ValSft_L20(BitMask_01)))|ValSft_L20((val)&BitMask_01)))

#define HPOS_ROFSr				(ValSft_R00(_rd32(_REG_BASE_+(0x0059<<2)))&BitMask_13)
#define HPOS_ROFSw(val)			_wr32(_REG_BASE_+(0x0059<<2),(UINT)((_rd32(_REG_BASE_+(0x0059<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define HTWOr					(ValSft_R16(_rd32(_REG_BASE_+(0x005a<<2)))&BitMask_13)
#define HTWOw(val)				_wr32(_REG_BASE_+(0x005a<<2),(UINT)((_rd32(_REG_BASE_+(0x005a<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define VTWOr					(ValSft_R00(_rd32(_REG_BASE_+(0x005a<<2)))&BitMask_13)
#define VTWOw(val)				_wr32(_REG_BASE_+(0x005a<<2),(UINT)((_rd32(_REG_BASE_+(0x005a<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define HWOr					(ValSft_R16(_rd32(_REG_BASE_+(0x005b<<2)))&BitMask_13)
#define HWOw(val)				_wr32(_REG_BASE_+(0x005b<<2),(UINT)((_rd32(_REG_BASE_+(0x005b<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define VWOr					(ValSft_R00(_rd32(_REG_BASE_+(0x005b<<2)))&BitMask_13)
#define VWOw(val)				_wr32(_REG_BASE_+(0x005b<<2),(UINT)((_rd32(_REG_BASE_+(0x005b<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define FONT_HWOr				(ValSft_R16(_rd32(_REG_BASE_+(0x005c<<2)))&BitMask_12)
#define FONT_HWOw(val)			_wr32(_REG_BASE_+(0x005c<<2),(UINT)((_rd32(_REG_BASE_+(0x005c<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define EFT_HSPr				(ValSft_R00(_rd32(_REG_BASE_+(0x005c<<2)))&BitMask_13)
#define EFT_HSPw(val)			_wr32(_REG_BASE_+(0x005c<<2),(UINT)((_rd32(_REG_BASE_+(0x005c<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define HSPOr					(ValSft_R16(_rd32(_REG_BASE_+(0x005d<<2)))&BitMask_13)
#define HSPOw(val)				_wr32(_REG_BASE_+(0x005d<<2),(UINT)((_rd32(_REG_BASE_+(0x005d<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define VSPOr					(ValSft_R00(_rd32(_REG_BASE_+(0x005d<<2)))&BitMask_13)
#define VSPOw(val)				_wr32(_REG_BASE_+(0x005d<<2),(UINT)((_rd32(_REG_BASE_+(0x005d<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define HLOCKO_POSr				(ValSft_R16(_rd32(_REG_BASE_+(0x005e<<2)))&BitMask_13)
#define HLOCKO_POSw(val)		_wr32(_REG_BASE_+(0x005e<<2),(UINT)((_rd32(_REG_BASE_+(0x005e<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define VLOCKO_POSr				(ValSft_R00(_rd32(_REG_BASE_+(0x005e<<2)))&BitMask_13)
#define VLOCKO_POSw(val)		_wr32(_REG_BASE_+(0x005e<<2),(UINT)((_rd32(_REG_BASE_+(0x005e<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define TRG_HSIOr				(ValSft_R31(_rd32(_REG_BASE_+(0x005f<<2)))&BitMask_01)
#define TRG_HSIOw(val)			_wr32(_REG_BASE_+(0x005f<<2),(UINT)((_rd32(_REG_BASE_+(0x005f<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define TRG_VSIOr				(ValSft_R30(_rd32(_REG_BASE_+(0x005f<<2)))&BitMask_01)
#define TRG_VSIOw(val)			_wr32(_REG_BASE_+(0x005f<<2),(UINT)((_rd32(_REG_BASE_+(0x005f<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define FLDP_INVr				(ValSft_R29(_rd32(_REG_BASE_+(0x005f<<2)))&BitMask_01)
#define FLDP_INVw(val)			_wr32(_REG_BASE_+(0x005f<<2),(UINT)((_rd32(_REG_BASE_+(0x005f<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define FLDP_INV2r				(ValSft_R28(_rd32(_REG_BASE_+(0x005f<<2)))&BitMask_01)
#define FLDP_INV2w(val)			_wr32(_REG_BASE_+(0x005f<<2),(UINT)((_rd32(_REG_BASE_+(0x005f<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define POST_INTRr				(ValSft_R26(_rd32(_REG_BASE_+(0x005f<<2)))&BitMask_02)
#define POST_INTRw(val)			_wr32(_REG_BASE_+(0x005f<<2),(UINT)((_rd32(_REG_BASE_+(0x005f<<2))&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define YC_VDLYr				(ValSft_R08(_rd32(_REG_BASE_+(0x005f<<2)))&BitMask_08)
#define YC_VDLYw(val)			_wr32(_REG_BASE_+(0x005f<<2),(UINT)((_rd32(_REG_BASE_+(0x005f<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define YC_HDLYr				(ValSft_R00(_rd32(_REG_BASE_+(0x005f<<2)))&BitMask_08)
#define YC_HDLYw(val)			_wr32(_REG_BASE_+(0x005f<<2),(UINT)((_rd32(_REG_BASE_+(0x005f<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define INSEL_MODr				(ValSft_R31(_rd32(_REG_BASE_+(0x0091<<2)))&BitMask_01)
#define INSEL_MODw(val)			_wr32(_REG_BASE_+(0x0091<<2),(UINT)((_rd32(_REG_BASE_+(0x0091<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define INSELr					(ValSft_R28(_rd32(_REG_BASE_+(0x0091<<2)))&BitMask_03)
#define INSELw(val)				_wr32(_REG_BASE_+(0x0091<<2),(UINT)((_rd32(_REG_BASE_+(0x0091<<2))&(~ValSft_L28(BitMask_03)))|ValSft_L28((val)&BitMask_03)))

#define PRE_OSELr				(ValSft_R20(_rd32(_REG_BASE_+(0x0091<<2)))&BitMask_05)
#define PRE_OSELw(val)			_wr32(_REG_BASE_+(0x0091<<2),(UINT)((_rd32(_REG_BASE_+(0x0091<<2))&(~ValSft_L20(BitMask_05)))|ValSft_L20((val)&BitMask_05)))

#define ONSELr					(ValSft_R16(_rd32(_REG_BASE_+(0x0091<<2)))&BitMask_03)
#define ONSELw(val)				_wr32(_REG_BASE_+(0x0091<<2),(UINT)((_rd32(_REG_BASE_+(0x0091<<2))&(~ValSft_L16(BitMask_03)))|ValSft_L16((val)&BitMask_03)))

#define YC_OSELr				(ValSft_R08(_rd32(_REG_BASE_+(0x0091<<2)))&BitMask_05)
#define YC_OSELw(val)			_wr32(_REG_BASE_+(0x0091<<2),(UINT)((_rd32(_REG_BASE_+(0x0091<<2))&(~ValSft_L08(BitMask_05)))|ValSft_L08((val)&BitMask_05)))

#define POST_TSELr				(ValSft_R07(_rd32(_REG_BASE_+(0x0091<<2)))&BitMask_01)
#define POST_TSELw(val)			_wr32(_REG_BASE_+(0x0091<<2),(UINT)((_rd32(_REG_BASE_+(0x0091<<2))&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

#define POST_OSELr				(ValSft_R04(_rd32(_REG_BASE_+(0x0091<<2)))&BitMask_03)
#define POST_OSELw(val)			_wr32(_REG_BASE_+(0x0091<<2),(UINT)((_rd32(_REG_BASE_+(0x0091<<2))&(~ValSft_L04(BitMask_03)))|ValSft_L04((val)&BitMask_03)))

#define POST_MASKr				(ValSft_R03(_rd32(_REG_BASE_+(0x0091<<2)))&BitMask_01)
#define POST_MASKw(val)			_wr32(_REG_BASE_+(0x0091<<2),(UINT)((_rd32(_REG_BASE_+(0x0091<<2))&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))

#define OUT_SELr				(ValSft_R00(_rd32(_REG_BASE_+(0x0091<<2)))&BitMask_03)
#define OUT_SELw(val)			_wr32(_REG_BASE_+(0x0091<<2),(UINT)((_rd32(_REG_BASE_+(0x0091<<2))&(~ValSft_L00(BitMask_03)))|ValSft_L00((val)&BitMask_03)))

#define TEST_PAT_OFSr			(ValSft_R16(_rd32(_REG_BASE_+(0x0092<<2)))&BitMask_12)
#define TEST_PAT_OFSw(val)		_wr32(_REG_BASE_+(0x0092<<2),(UINT)((_rd32(_REG_BASE_+(0x0092<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define INSEL_TLVr				(ValSft_R00(_rd32(_REG_BASE_+(0x0092<<2)))&BitMask_16)
#define INSEL_TLVw(val)			_wr32(_REG_BASE_+(0x0092<<2),(UINT)((_rd32(_REG_BASE_+(0x0092<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define OUT_TC1r				(ValSft_R16(_rd32(_REG_BASE_+(0x0093<<2)))&BitMask_10)
#define OUT_TC1w(val)			_wr32(_REG_BASE_+(0x0093<<2),(UINT)((_rd32(_REG_BASE_+(0x0093<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define OUT_TC2r				(ValSft_R00(_rd32(_REG_BASE_+(0x0093<<2)))&BitMask_10)
#define OUT_TC2w(val)			_wr32(_REG_BASE_+(0x0093<<2),(UINT)((_rd32(_REG_BASE_+(0x0093<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define UDS_VSPOr				(ValSft_R00(_rd32(_REG_BASE_+(0x0096<<2)))&BitMask_04)
#define UDS_VSPOw(val)			_wr32(_REG_BASE_+(0x0096<<2),(UINT)((_rd32(_REG_BASE_+(0x0096<<2))&(~ValSft_L00(BitMask_04)))|ValSft_L00((val)&BitMask_04)))

#define US_VONr					(ValSft_R31(_rd32(_REG_BASE_+(0x0097<<2)))&BitMask_01)
#define US_VONw(val)			_wr32(_REG_BASE_+(0x0097<<2),(UINT)((_rd32(_REG_BASE_+(0x0097<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define US_VRSr					(ValSft_R29(_rd32(_REG_BASE_+(0x0097<<2)))&BitMask_02)
#define US_VRSw(val)			_wr32(_REG_BASE_+(0x0097<<2),(UINT)((_rd32(_REG_BASE_+(0x0097<<2))&(~ValSft_L29(BitMask_02)))|ValSft_L29((val)&BitMask_02)))

#define US_MSELr				(ValSft_R24(_rd32(_REG_BASE_+(0x0097<<2)))&BitMask_05)
#define US_MSELw(val)			_wr32(_REG_BASE_+(0x0097<<2),(UINT)((_rd32(_REG_BASE_+(0x0097<<2))&(~ValSft_L24(BitMask_05)))|ValSft_L24((val)&BitMask_05)))

#define UYKr					(ValSft_R16(_rd32(_REG_BASE_+(0x0097<<2)))&BitMask_07)
#define UYKw(val)				_wr32(_REG_BASE_+(0x0097<<2),(UINT)((_rd32(_REG_BASE_+(0x0097<<2))&(~ValSft_L16(BitMask_07)))|ValSft_L16((val)&BitMask_07)))

#define US_HONr					(ValSft_R31(_rd32(_REG_BASE_+(0x0098<<2)))&BitMask_01)
#define US_HONw(val)			_wr32(_REG_BASE_+(0x0098<<2),(UINT)((_rd32(_REG_BASE_+(0x0098<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define UXKr					(ValSft_R16(_rd32(_REG_BASE_+(0x0098<<2)))&BitMask_07)
#define UXKw(val)				_wr32(_REG_BASE_+(0x0098<<2),(UINT)((_rd32(_REG_BASE_+(0x0098<<2))&(~ValSft_L16(BitMask_07)))|ValSft_L16((val)&BitMask_07)))

#define DS_INTRr				(ValSft_R31(_rd32(_REG_BASE_+(0x0099<<2)))&BitMask_01)
#define DS_INTRw(val)			_wr32(_REG_BASE_+(0x0099<<2),(UINT)((_rd32(_REG_BASE_+(0x0099<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DS_VRSr					(ValSft_R00(_rd32(_REG_BASE_+(0x0099<<2)))&BitMask_12)
#define DS_VRSw(val)			_wr32(_REG_BASE_+(0x0099<<2),(UINT)((_rd32(_REG_BASE_+(0x0099<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define DS_ONr					(ValSft_R31(_rd32(_REG_BASE_+(0x009a<<2)))&BitMask_01)
#define DS_ONw(val)				_wr32(_REG_BASE_+(0x009a<<2),(UINT)((_rd32(_REG_BASE_+(0x009a<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DS_MEM4r				(ValSft_R30(_rd32(_REG_BASE_+(0x009a<<2)))&BitMask_01)
#define DS_MEM4w(val)			_wr32(_REG_BASE_+(0x009a<<2),(UINT)((_rd32(_REG_BASE_+(0x009a<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define DS_RMODr				(ValSft_R29(_rd32(_REG_BASE_+(0x009a<<2)))&BitMask_01)
#define DS_RMODw(val)			_wr32(_REG_BASE_+(0x009a<<2),(UINT)((_rd32(_REG_BASE_+(0x009a<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define DS_VLPFr				(ValSft_R26(_rd32(_REG_BASE_+(0x009a<<2)))&BitMask_01)
#define DS_VLPFw(val)			_wr32(_REG_BASE_+(0x009a<<2),(UINT)((_rd32(_REG_BASE_+(0x009a<<2))&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define DS_HLPFr				(ValSft_R24(_rd32(_REG_BASE_+(0x009a<<2)))&BitMask_02)
#define DS_HLPFw(val)			_wr32(_REG_BASE_+(0x009a<<2),(UINT)((_rd32(_REG_BASE_+(0x009a<<2))&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define DKXr					(ValSft_R16(_rd32(_REG_BASE_+(0x009a<<2)))&BitMask_08)
#define DKXw(val)				_wr32(_REG_BASE_+(0x009a<<2),(UINT)((_rd32(_REG_BASE_+(0x009a<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define DKYr					(ValSft_R08(_rd32(_REG_BASE_+(0x009a<<2)))&BitMask_08)
#define DKYw(val)				_wr32(_REG_BASE_+(0x009a<<2),(UINT)((_rd32(_REG_BASE_+(0x009a<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define DKY_STr					(ValSft_R00(_rd32(_REG_BASE_+(0x009a<<2)))&BitMask_06)
#define DKY_STw(val)			_wr32(_REG_BASE_+(0x009a<<2),(UINT)((_rd32(_REG_BASE_+(0x009a<<2))&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define DS_HOFFr				(ValSft_R16(_rd32(_REG_BASE_+(0x009b<<2)))&BitMask_12)
#define DS_HOFFw(val)			_wr32(_REG_BASE_+(0x009b<<2),(UINT)((_rd32(_REG_BASE_+(0x009b<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define DS_VOFFr				(ValSft_R00(_rd32(_REG_BASE_+(0x009b<<2)))&BitMask_12)
#define DS_VOFFw(val)			_wr32(_REG_BASE_+(0x009b<<2),(UINT)((_rd32(_REG_BASE_+(0x009b<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define DS_HWr					(ValSft_R16(_rd32(_REG_BASE_+(0x009c<<2)))&BitMask_13)
#define DS_HWw(val)				_wr32(_REG_BASE_+(0x009c<<2),(UINT)((_rd32(_REG_BASE_+(0x009c<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define DS_VWr					(ValSft_R00(_rd32(_REG_BASE_+(0x009c<<2)))&BitMask_13)
#define DS_VWw(val)				_wr32(_REG_BASE_+(0x009c<<2),(UINT)((_rd32(_REG_BASE_+(0x009c<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define DKX_STr					(ValSft_R00(_rd32(_REG_BASE_+(0x009d<<2)))&BitMask_10)
#define DKX_STw(val)			_wr32(_REG_BASE_+(0x009d<<2),(UINT)((_rd32(_REG_BASE_+(0x009d<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define OZONE_SELr				(ValSft_R28(_rd32(_REG_BASE_+(0x00a0<<2)))&BitMask_03)
#define OZONE_SELw(val)			_wr32(_REG_BASE_+(0x00a0<<2),(UINT)((_rd32(_REG_BASE_+(0x00a0<<2))&(~ValSft_L28(BitMask_03)))|ValSft_L28((val)&BitMask_03)))

#define PAWB_OFFSr				(ValSft_R16(_rd32(_REG_BASE_+(0x00a0<<2)))&BitMask_11)
#define PAWB_OFFSw(val)			_wr32(_REG_BASE_+(0x00a0<<2),(UINT)((_rd32(_REG_BASE_+(0x00a0<<2))&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define PRR_GAINr				(ValSft_R16(_rd32(_REG_BASE_+(0x00a1<<2)))&BitMask_11)
#define PRR_GAINw(val)			_wr32(_REG_BASE_+(0x00a1<<2),(UINT)((_rd32(_REG_BASE_+(0x00a1<<2))&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define PRG_GAINr				(ValSft_R00(_rd32(_REG_BASE_+(0x00a1<<2)))&BitMask_12)
#define PRG_GAINw(val)			_wr32(_REG_BASE_+(0x00a1<<2),(UINT)((_rd32(_REG_BASE_+(0x00a1<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define PRB_GAINr				(ValSft_R16(_rd32(_REG_BASE_+(0x00a2<<2)))&BitMask_12)
#define PRB_GAINw(val)			_wr32(_REG_BASE_+(0x00a2<<2),(UINT)((_rd32(_REG_BASE_+(0x00a2<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define PGR_GAINr				(ValSft_R00(_rd32(_REG_BASE_+(0x00a2<<2)))&BitMask_12)
#define PGR_GAINw(val)			_wr32(_REG_BASE_+(0x00a2<<2),(UINT)((_rd32(_REG_BASE_+(0x00a2<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define PGG_GAINr				(ValSft_R16(_rd32(_REG_BASE_+(0x00a3<<2)))&BitMask_11)
#define PGG_GAINw(val)			_wr32(_REG_BASE_+(0x00a3<<2),(UINT)((_rd32(_REG_BASE_+(0x00a3<<2))&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define PGB_GAINr				(ValSft_R00(_rd32(_REG_BASE_+(0x00a3<<2)))&BitMask_12)
#define PGB_GAINw(val)			_wr32(_REG_BASE_+(0x00a3<<2),(UINT)((_rd32(_REG_BASE_+(0x00a3<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define PBR_GAINr				(ValSft_R16(_rd32(_REG_BASE_+(0x00a4<<2)))&BitMask_12)
#define PBR_GAINw(val)			_wr32(_REG_BASE_+(0x00a4<<2),(UINT)((_rd32(_REG_BASE_+(0x00a4<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define PBG_GAINr				(ValSft_R00(_rd32(_REG_BASE_+(0x00a4<<2)))&BitMask_12)
#define PBG_GAINw(val)			_wr32(_REG_BASE_+(0x00a4<<2),(UINT)((_rd32(_REG_BASE_+(0x00a4<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define PBB_GAINr				(ValSft_R00(_rd32(_REG_BASE_+(0x00a5<<2)))&BitMask_11)
#define PBB_GAINw(val)			_wr32(_REG_BASE_+(0x00a5<<2),(UINT)((_rd32(_REG_BASE_+(0x00a5<<2))&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define PYR_GAINr				(ValSft_R16(_rd32(_REG_BASE_+(0x00a6<<2)))&BitMask_08)
#define PYR_GAINw(val)			_wr32(_REG_BASE_+(0x00a6<<2),(UINT)((_rd32(_REG_BASE_+(0x00a6<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define PYG_GAINr				(ValSft_R08(_rd32(_REG_BASE_+(0x00a6<<2)))&BitMask_08)
#define PYG_GAINw(val)			_wr32(_REG_BASE_+(0x00a6<<2),(UINT)((_rd32(_REG_BASE_+(0x00a6<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define PYB_GAINr				(ValSft_R00(_rd32(_REG_BASE_+(0x00a6<<2)))&BitMask_08)
#define PYB_GAINw(val)			_wr32(_REG_BASE_+(0x00a6<<2),(UINT)((_rd32(_REG_BASE_+(0x00a6<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define AE_LOCK_SELr			(ValSft_R31(_rd32(_REG_BASE_+(0x00a7<<2)))&BitMask_01)
#define AE_LOCK_SELw(val)		_wr32(_REG_BASE_+(0x00a7<<2),(UINT)((_rd32(_REG_BASE_+(0x00a7<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define AE_WIN_SELr				(ValSft_R24(_rd32(_REG_BASE_+(0x00a7<<2)))&BitMask_06)
#define AE_WIN_SELw(val)		_wr32(_REG_BASE_+(0x00a7<<2),(UINT)((_rd32(_REG_BASE_+(0x00a7<<2))&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define AE_BITSELr				(ValSft_R18(_rd32(_REG_BASE_+(0x00a7<<2)))&BitMask_03)
#define AE_BITSELw(val)			_wr32(_REG_BASE_+(0x00a7<<2),(UINT)((_rd32(_REG_BASE_+(0x00a7<<2))&(~ValSft_L18(BitMask_03)))|ValSft_L18((val)&BitMask_03)))

#define AE1_WIN_CHr				(ValSft_R15(_rd32(_REG_BASE_+(0x00a7<<2)))&BitMask_03)
#define AE1_WIN_CHw(val)		_wr32(_REG_BASE_+(0x00a7<<2),(UINT)((_rd32(_REG_BASE_+(0x00a7<<2))&(~ValSft_L15(BitMask_03)))|ValSft_L15((val)&BitMask_03)))

#define AE2_WIN_CHr				(ValSft_R12(_rd32(_REG_BASE_+(0x00a7<<2)))&BitMask_03)
#define AE2_WIN_CHw(val)		_wr32(_REG_BASE_+(0x00a7<<2),(UINT)((_rd32(_REG_BASE_+(0x00a7<<2))&(~ValSft_L12(BitMask_03)))|ValSft_L12((val)&BitMask_03)))

#define AE3_WIN_CHr				(ValSft_R09(_rd32(_REG_BASE_+(0x00a7<<2)))&BitMask_03)
#define AE3_WIN_CHw(val)		_wr32(_REG_BASE_+(0x00a7<<2),(UINT)((_rd32(_REG_BASE_+(0x00a7<<2))&(~ValSft_L09(BitMask_03)))|ValSft_L09((val)&BitMask_03)))

#define AE4_WIN_CHr				(ValSft_R06(_rd32(_REG_BASE_+(0x00a7<<2)))&BitMask_03)
#define AE4_WIN_CHw(val)		_wr32(_REG_BASE_+(0x00a7<<2),(UINT)((_rd32(_REG_BASE_+(0x00a7<<2))&(~ValSft_L06(BitMask_03)))|ValSft_L06((val)&BitMask_03)))

#define AE5_WIN_CHr				(ValSft_R03(_rd32(_REG_BASE_+(0x00a7<<2)))&BitMask_03)
#define AE5_WIN_CHw(val)		_wr32(_REG_BASE_+(0x00a7<<2),(UINT)((_rd32(_REG_BASE_+(0x00a7<<2))&(~ValSft_L03(BitMask_03)))|ValSft_L03((val)&BitMask_03)))

#define AE6_WIN_CHr				(ValSft_R00(_rd32(_REG_BASE_+(0x00a7<<2)))&BitMask_03)
#define AE6_WIN_CHw(val)		_wr32(_REG_BASE_+(0x00a7<<2),(UINT)((_rd32(_REG_BASE_+(0x00a7<<2))&(~ValSft_L00(BitMask_03)))|ValSft_L00((val)&BitMask_03)))

#define AE1_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00a8<<2)))&BitMask_12)
#define AE1_HSPw(val)			_wr32(_REG_BASE_+(0x00a8<<2),(UINT)((_rd32(_REG_BASE_+(0x00a8<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AE1_HEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00a8<<2)))&BitMask_12)
#define AE1_HEPw(val)			_wr32(_REG_BASE_+(0x00a8<<2),(UINT)((_rd32(_REG_BASE_+(0x00a8<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define AE1_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00a9<<2)))&BitMask_12)
#define AE1_VSPw(val)			_wr32(_REG_BASE_+(0x00a9<<2),(UINT)((_rd32(_REG_BASE_+(0x00a9<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AE1_VEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00a9<<2)))&BitMask_12)
#define AE1_VEPw(val)			_wr32(_REG_BASE_+(0x00a9<<2),(UINT)((_rd32(_REG_BASE_+(0x00a9<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define AE2_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00aa<<2)))&BitMask_12)
#define AE2_HSPw(val)			_wr32(_REG_BASE_+(0x00aa<<2),(UINT)((_rd32(_REG_BASE_+(0x00aa<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AE2_HEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00aa<<2)))&BitMask_12)
#define AE2_HEPw(val)			_wr32(_REG_BASE_+(0x00aa<<2),(UINT)((_rd32(_REG_BASE_+(0x00aa<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define AE2_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00ab<<2)))&BitMask_12)
#define AE2_VSPw(val)			_wr32(_REG_BASE_+(0x00ab<<2),(UINT)((_rd32(_REG_BASE_+(0x00ab<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AE2_VEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00ab<<2)))&BitMask_12)
#define AE2_VEPw(val)			_wr32(_REG_BASE_+(0x00ab<<2),(UINT)((_rd32(_REG_BASE_+(0x00ab<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define AE3_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00ac<<2)))&BitMask_12)
#define AE3_HSPw(val)			_wr32(_REG_BASE_+(0x00ac<<2),(UINT)((_rd32(_REG_BASE_+(0x00ac<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AE3_HEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00ac<<2)))&BitMask_12)
#define AE3_HEPw(val)			_wr32(_REG_BASE_+(0x00ac<<2),(UINT)((_rd32(_REG_BASE_+(0x00ac<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define AE3_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00ad<<2)))&BitMask_12)
#define AE3_VSPw(val)			_wr32(_REG_BASE_+(0x00ad<<2),(UINT)((_rd32(_REG_BASE_+(0x00ad<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AE3_VEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00ad<<2)))&BitMask_12)
#define AE3_VEPw(val)			_wr32(_REG_BASE_+(0x00ad<<2),(UINT)((_rd32(_REG_BASE_+(0x00ad<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define AE4_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00ae<<2)))&BitMask_12)
#define AE4_HSPw(val)			_wr32(_REG_BASE_+(0x00ae<<2),(UINT)((_rd32(_REG_BASE_+(0x00ae<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AE4_HEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00ae<<2)))&BitMask_12)
#define AE4_HEPw(val)			_wr32(_REG_BASE_+(0x00ae<<2),(UINT)((_rd32(_REG_BASE_+(0x00ae<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define AE4_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00af<<2)))&BitMask_12)
#define AE4_VSPw(val)			_wr32(_REG_BASE_+(0x00af<<2),(UINT)((_rd32(_REG_BASE_+(0x00af<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AE4_VEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00af<<2)))&BitMask_12)
#define AE4_VEPw(val)			_wr32(_REG_BASE_+(0x00af<<2),(UINT)((_rd32(_REG_BASE_+(0x00af<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define AE5_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00b0<<2)))&BitMask_12)
#define AE5_HSPw(val)			_wr32(_REG_BASE_+(0x00b0<<2),(UINT)((_rd32(_REG_BASE_+(0x00b0<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AE5_HEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00b0<<2)))&BitMask_12)
#define AE5_HEPw(val)			_wr32(_REG_BASE_+(0x00b0<<2),(UINT)((_rd32(_REG_BASE_+(0x00b0<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define AE5_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00b1<<2)))&BitMask_12)
#define AE5_VSPw(val)			_wr32(_REG_BASE_+(0x00b1<<2),(UINT)((_rd32(_REG_BASE_+(0x00b1<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AE5_VEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00b1<<2)))&BitMask_12)
#define AE5_VEPw(val)			_wr32(_REG_BASE_+(0x00b1<<2),(UINT)((_rd32(_REG_BASE_+(0x00b1<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define AE6_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00b2<<2)))&BitMask_12)
#define AE6_HSPw(val)			_wr32(_REG_BASE_+(0x00b2<<2),(UINT)((_rd32(_REG_BASE_+(0x00b2<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AE6_HEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00b2<<2)))&BitMask_12)
#define AE6_HEPw(val)			_wr32(_REG_BASE_+(0x00b2<<2),(UINT)((_rd32(_REG_BASE_+(0x00b2<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define AE6_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00b3<<2)))&BitMask_12)
#define AE6_VSPw(val)			_wr32(_REG_BASE_+(0x00b3<<2),(UINT)((_rd32(_REG_BASE_+(0x00b3<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AE6_VEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00b3<<2)))&BitMask_12)
#define AE6_VEPw(val)			_wr32(_REG_BASE_+(0x00b3<<2),(UINT)((_rd32(_REG_BASE_+(0x00b3<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define AE1_CLIPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00b4<<2)))&BitMask_10)
#define AE1_CLIPw(val)			_wr32(_REG_BASE_+(0x00b4<<2),(UINT)((_rd32(_REG_BASE_+(0x00b4<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AE1_SLICEr				(ValSft_R16(_rd32(_REG_BASE_+(0x00b4<<2)))&BitMask_10)
#define AE1_SLICEw(val)			_wr32(_REG_BASE_+(0x00b4<<2),(UINT)((_rd32(_REG_BASE_+(0x00b4<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AE2_CLIPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00b5<<2)))&BitMask_10)
#define AE2_CLIPw(val)			_wr32(_REG_BASE_+(0x00b5<<2),(UINT)((_rd32(_REG_BASE_+(0x00b5<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AE2_SLICEr				(ValSft_R16(_rd32(_REG_BASE_+(0x00b5<<2)))&BitMask_10)
#define AE2_SLICEw(val)			_wr32(_REG_BASE_+(0x00b5<<2),(UINT)((_rd32(_REG_BASE_+(0x00b5<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AE3_CLIPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00b6<<2)))&BitMask_10)
#define AE3_CLIPw(val)			_wr32(_REG_BASE_+(0x00b6<<2),(UINT)((_rd32(_REG_BASE_+(0x00b6<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AE3_SLICEr				(ValSft_R16(_rd32(_REG_BASE_+(0x00b6<<2)))&BitMask_10)
#define AE3_SLICEw(val)			_wr32(_REG_BASE_+(0x00b6<<2),(UINT)((_rd32(_REG_BASE_+(0x00b6<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AE4_CLIPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00b7<<2)))&BitMask_10)
#define AE4_CLIPw(val)			_wr32(_REG_BASE_+(0x00b7<<2),(UINT)((_rd32(_REG_BASE_+(0x00b7<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AE4_SLICEr				(ValSft_R16(_rd32(_REG_BASE_+(0x00b7<<2)))&BitMask_10)
#define AE4_SLICEw(val)			_wr32(_REG_BASE_+(0x00b7<<2),(UINT)((_rd32(_REG_BASE_+(0x00b7<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AE5_CLIPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00b8<<2)))&BitMask_10)
#define AE5_CLIPw(val)			_wr32(_REG_BASE_+(0x00b8<<2),(UINT)((_rd32(_REG_BASE_+(0x00b8<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AE5_SLICEr				(ValSft_R16(_rd32(_REG_BASE_+(0x00b8<<2)))&BitMask_10)
#define AE5_SLICEw(val)			_wr32(_REG_BASE_+(0x00b8<<2),(UINT)((_rd32(_REG_BASE_+(0x00b8<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AE6_CLIPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00b9<<2)))&BitMask_10)
#define AE6_CLIPw(val)			_wr32(_REG_BASE_+(0x00b9<<2),(UINT)((_rd32(_REG_BASE_+(0x00b9<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AE6_SLICEr				(ValSft_R16(_rd32(_REG_BASE_+(0x00b9<<2)))&BitMask_10)
#define AE6_SLICEw(val)			_wr32(_REG_BASE_+(0x00b9<<2),(UINT)((_rd32(_REG_BASE_+(0x00b9<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define HISTO0_MAXr				(ValSft_R24(_rd32(_REG_BASE_+(0x00ba<<2)))&BitMask_07)
#define HISTO0_MAXw(val)		_wr32(_REG_BASE_+(0x00ba<<2),(UINT)((_rd32(_REG_BASE_+(0x00ba<<2))&(~ValSft_L24(BitMask_07)))|ValSft_L24((val)&BitMask_07)))

#define HISTO1_MAXr				(ValSft_R16(_rd32(_REG_BASE_+(0x00ba<<2)))&BitMask_07)
#define HISTO1_MAXw(val)		_wr32(_REG_BASE_+(0x00ba<<2),(UINT)((_rd32(_REG_BASE_+(0x00ba<<2))&(~ValSft_L16(BitMask_07)))|ValSft_L16((val)&BitMask_07)))

#define HISTO2_MAXr				(ValSft_R08(_rd32(_REG_BASE_+(0x00ba<<2)))&BitMask_07)
#define HISTO2_MAXw(val)		_wr32(_REG_BASE_+(0x00ba<<2),(UINT)((_rd32(_REG_BASE_+(0x00ba<<2))&(~ValSft_L08(BitMask_07)))|ValSft_L08((val)&BitMask_07)))

#define HISTO3_MAXr				(ValSft_R00(_rd32(_REG_BASE_+(0x00ba<<2)))&BitMask_07)
#define HISTO3_MAXw(val)		_wr32(_REG_BASE_+(0x00ba<<2),(UINT)((_rd32(_REG_BASE_+(0x00ba<<2))&(~ValSft_L00(BitMask_07)))|ValSft_L00((val)&BitMask_07)))

#define HISTO4_MAXr				(ValSft_R24(_rd32(_REG_BASE_+(0x00bb<<2)))&BitMask_07)
#define HISTO4_MAXw(val)		_wr32(_REG_BASE_+(0x00bb<<2),(UINT)((_rd32(_REG_BASE_+(0x00bb<<2))&(~ValSft_L24(BitMask_07)))|ValSft_L24((val)&BitMask_07)))

#define HISTO5_MAXr				(ValSft_R16(_rd32(_REG_BASE_+(0x00bb<<2)))&BitMask_07)
#define HISTO5_MAXw(val)		_wr32(_REG_BASE_+(0x00bb<<2),(UINT)((_rd32(_REG_BASE_+(0x00bb<<2))&(~ValSft_L16(BitMask_07)))|ValSft_L16((val)&BitMask_07)))

#define HISTO6_MAXr				(ValSft_R08(_rd32(_REG_BASE_+(0x00bb<<2)))&BitMask_07)
#define HISTO6_MAXw(val)		_wr32(_REG_BASE_+(0x00bb<<2),(UINT)((_rd32(_REG_BASE_+(0x00bb<<2))&(~ValSft_L08(BitMask_07)))|ValSft_L08((val)&BitMask_07)))

#define HISTO7_MAXr				(ValSft_R00(_rd32(_REG_BASE_+(0x00bb<<2)))&BitMask_07)
#define HISTO7_MAXw(val)		_wr32(_REG_BASE_+(0x00bb<<2),(UINT)((_rd32(_REG_BASE_+(0x00bb<<2))&(~ValSft_L00(BitMask_07)))|ValSft_L00((val)&BitMask_07)))

#define HISTO8_MAXr				(ValSft_R24(_rd32(_REG_BASE_+(0x00bc<<2)))&BitMask_07)
#define HISTO8_MAXw(val)		_wr32(_REG_BASE_+(0x00bc<<2),(UINT)((_rd32(_REG_BASE_+(0x00bc<<2))&(~ValSft_L24(BitMask_07)))|ValSft_L24((val)&BitMask_07)))

#define HISTO9_MAXr				(ValSft_R16(_rd32(_REG_BASE_+(0x00bc<<2)))&BitMask_07)
#define HISTO9_MAXw(val)		_wr32(_REG_BASE_+(0x00bc<<2),(UINT)((_rd32(_REG_BASE_+(0x00bc<<2))&(~ValSft_L16(BitMask_07)))|ValSft_L16((val)&BitMask_07)))

#define HISTO10_MAXr			(ValSft_R08(_rd32(_REG_BASE_+(0x00bc<<2)))&BitMask_07)
#define HISTO10_MAXw(val)		_wr32(_REG_BASE_+(0x00bc<<2),(UINT)((_rd32(_REG_BASE_+(0x00bc<<2))&(~ValSft_L08(BitMask_07)))|ValSft_L08((val)&BitMask_07)))

#define HISTO11_MAXr			(ValSft_R00(_rd32(_REG_BASE_+(0x00bc<<2)))&BitMask_07)
#define HISTO11_MAXw(val)		_wr32(_REG_BASE_+(0x00bc<<2),(UINT)((_rd32(_REG_BASE_+(0x00bc<<2))&(~ValSft_L00(BitMask_07)))|ValSft_L00((val)&BitMask_07)))

#define HISTO12_MAXr			(ValSft_R24(_rd32(_REG_BASE_+(0x00bd<<2)))&BitMask_07)
#define HISTO12_MAXw(val)		_wr32(_REG_BASE_+(0x00bd<<2),(UINT)((_rd32(_REG_BASE_+(0x00bd<<2))&(~ValSft_L24(BitMask_07)))|ValSft_L24((val)&BitMask_07)))

#define HISTO13_MAXr			(ValSft_R16(_rd32(_REG_BASE_+(0x00bd<<2)))&BitMask_07)
#define HISTO13_MAXw(val)		_wr32(_REG_BASE_+(0x00bd<<2),(UINT)((_rd32(_REG_BASE_+(0x00bd<<2))&(~ValSft_L16(BitMask_07)))|ValSft_L16((val)&BitMask_07)))

#define HISTO14_MAXr			(ValSft_R08(_rd32(_REG_BASE_+(0x00bd<<2)))&BitMask_07)
#define HISTO14_MAXw(val)		_wr32(_REG_BASE_+(0x00bd<<2),(UINT)((_rd32(_REG_BASE_+(0x00bd<<2))&(~ValSft_L08(BitMask_07)))|ValSft_L08((val)&BitMask_07)))

#define HISTO0_MAX2r			(ValSft_R24(_rd32(_REG_BASE_+(0x00c1<<2)))&BitMask_07)
#define HISTO0_MAX2w(val)		_wr32(_REG_BASE_+(0x00c1<<2),(UINT)((_rd32(_REG_BASE_+(0x00c1<<2))&(~ValSft_L24(BitMask_07)))|ValSft_L24((val)&BitMask_07)))

#define HISTO1_MAX2r			(ValSft_R16(_rd32(_REG_BASE_+(0x00c1<<2)))&BitMask_07)
#define HISTO1_MAX2w(val)		_wr32(_REG_BASE_+(0x00c1<<2),(UINT)((_rd32(_REG_BASE_+(0x00c1<<2))&(~ValSft_L16(BitMask_07)))|ValSft_L16((val)&BitMask_07)))

#define HISTO2_MAX2r			(ValSft_R08(_rd32(_REG_BASE_+(0x00c1<<2)))&BitMask_07)
#define HISTO2_MAX2w(val)		_wr32(_REG_BASE_+(0x00c1<<2),(UINT)((_rd32(_REG_BASE_+(0x00c1<<2))&(~ValSft_L08(BitMask_07)))|ValSft_L08((val)&BitMask_07)))

#define HISTO3_MAX2r			(ValSft_R00(_rd32(_REG_BASE_+(0x00c1<<2)))&BitMask_07)
#define HISTO3_MAX2w(val)		_wr32(_REG_BASE_+(0x00c1<<2),(UINT)((_rd32(_REG_BASE_+(0x00c1<<2))&(~ValSft_L00(BitMask_07)))|ValSft_L00((val)&BitMask_07)))

#define HISTO4_MAX2r			(ValSft_R24(_rd32(_REG_BASE_+(0x00c2<<2)))&BitMask_07)
#define HISTO4_MAX2w(val)		_wr32(_REG_BASE_+(0x00c2<<2),(UINT)((_rd32(_REG_BASE_+(0x00c2<<2))&(~ValSft_L24(BitMask_07)))|ValSft_L24((val)&BitMask_07)))

#define HISTO5_MAX2r			(ValSft_R16(_rd32(_REG_BASE_+(0x00c2<<2)))&BitMask_07)
#define HISTO5_MAX2w(val)		_wr32(_REG_BASE_+(0x00c2<<2),(UINT)((_rd32(_REG_BASE_+(0x00c2<<2))&(~ValSft_L16(BitMask_07)))|ValSft_L16((val)&BitMask_07)))

#define HISTO6_MAX2r			(ValSft_R08(_rd32(_REG_BASE_+(0x00c2<<2)))&BitMask_07)
#define HISTO6_MAX2w(val)		_wr32(_REG_BASE_+(0x00c2<<2),(UINT)((_rd32(_REG_BASE_+(0x00c2<<2))&(~ValSft_L08(BitMask_07)))|ValSft_L08((val)&BitMask_07)))

#define HISTO7_MAX2r			(ValSft_R00(_rd32(_REG_BASE_+(0x00c2<<2)))&BitMask_07)
#define HISTO7_MAX2w(val)		_wr32(_REG_BASE_+(0x00c2<<2),(UINT)((_rd32(_REG_BASE_+(0x00c2<<2))&(~ValSft_L00(BitMask_07)))|ValSft_L00((val)&BitMask_07)))

#define HISTO8_MAX2r			(ValSft_R24(_rd32(_REG_BASE_+(0x00c3<<2)))&BitMask_07)
#define HISTO8_MAX2w(val)		_wr32(_REG_BASE_+(0x00c3<<2),(UINT)((_rd32(_REG_BASE_+(0x00c3<<2))&(~ValSft_L24(BitMask_07)))|ValSft_L24((val)&BitMask_07)))

#define HISTO9_MAX2r			(ValSft_R16(_rd32(_REG_BASE_+(0x00c3<<2)))&BitMask_07)
#define HISTO9_MAX2w(val)		_wr32(_REG_BASE_+(0x00c3<<2),(UINT)((_rd32(_REG_BASE_+(0x00c3<<2))&(~ValSft_L16(BitMask_07)))|ValSft_L16((val)&BitMask_07)))

#define HISTO10_MAX2r			(ValSft_R08(_rd32(_REG_BASE_+(0x00c3<<2)))&BitMask_07)
#define HISTO10_MAX2w(val)		_wr32(_REG_BASE_+(0x00c3<<2),(UINT)((_rd32(_REG_BASE_+(0x00c3<<2))&(~ValSft_L08(BitMask_07)))|ValSft_L08((val)&BitMask_07)))

#define HISTO11_MAX2r			(ValSft_R00(_rd32(_REG_BASE_+(0x00c3<<2)))&BitMask_07)
#define HISTO11_MAX2w(val)		_wr32(_REG_BASE_+(0x00c3<<2),(UINT)((_rd32(_REG_BASE_+(0x00c3<<2))&(~ValSft_L00(BitMask_07)))|ValSft_L00((val)&BitMask_07)))

#define HISTO12_MAX2r			(ValSft_R24(_rd32(_REG_BASE_+(0x00c4<<2)))&BitMask_07)
#define HISTO12_MAX2w(val)		_wr32(_REG_BASE_+(0x00c4<<2),(UINT)((_rd32(_REG_BASE_+(0x00c4<<2))&(~ValSft_L24(BitMask_07)))|ValSft_L24((val)&BitMask_07)))

#define HISTO13_MAX2r			(ValSft_R16(_rd32(_REG_BASE_+(0x00c4<<2)))&BitMask_07)
#define HISTO13_MAX2w(val)		_wr32(_REG_BASE_+(0x00c4<<2),(UINT)((_rd32(_REG_BASE_+(0x00c4<<2))&(~ValSft_L16(BitMask_07)))|ValSft_L16((val)&BitMask_07)))

#define HISTO14_MAX2r			(ValSft_R08(_rd32(_REG_BASE_+(0x00c4<<2)))&BitMask_07)
#define HISTO14_MAX2w(val)		_wr32(_REG_BASE_+(0x00c4<<2),(UINT)((_rd32(_REG_BASE_+(0x00c4<<2))&(~ValSft_L08(BitMask_07)))|ValSft_L08((val)&BitMask_07)))

#define IRIS_ONr				(ValSft_R31(_rd32(_REG_BASE_+(0x00c5<<2)))&BitMask_01)
#define IRIS_ONw(val)			_wr32(_REG_BASE_+(0x00c5<<2),(UINT)((_rd32(_REG_BASE_+(0x00c5<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define IRIS_INVr				(ValSft_R30(_rd32(_REG_BASE_+(0x00c5<<2)))&BitMask_01)
#define IRIS_INVw(val)			_wr32(_REG_BASE_+(0x00c5<<2),(UINT)((_rd32(_REG_BASE_+(0x00c5<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define IRIS_MODr				(ValSft_R28(_rd32(_REG_BASE_+(0x00c5<<2)))&BitMask_02)
#define IRIS_MODw(val)			_wr32(_REG_BASE_+(0x00c5<<2),(UINT)((_rd32(_REG_BASE_+(0x00c5<<2))&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define IRIS_SWr				(ValSft_R27(_rd32(_REG_BASE_+(0x00c5<<2)))&BitMask_01)
#define IRIS_SWw(val)			_wr32(_REG_BASE_+(0x00c5<<2),(UINT)((_rd32(_REG_BASE_+(0x00c5<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define IRIS_WSELr				(ValSft_R24(_rd32(_REG_BASE_+(0x00c5<<2)))&BitMask_03)
#define IRIS_WSELw(val)			_wr32(_REG_BASE_+(0x00c5<<2),(UINT)((_rd32(_REG_BASE_+(0x00c5<<2))&(~ValSft_L24(BitMask_03)))|ValSft_L24((val)&BitMask_03)))

#define IRIS_FBKr				(ValSft_R16(_rd32(_REG_BASE_+(0x00c5<<2)))&BitMask_08)
#define IRIS_FBKw(val)			_wr32(_REG_BASE_+(0x00c5<<2),(UINT)((_rd32(_REG_BASE_+(0x00c5<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define IRIS_CHSELr				(ValSft_R10(_rd32(_REG_BASE_+(0x00c5<<2)))&BitMask_02)
#define IRIS_CHSELw(val)		_wr32(_REG_BASE_+(0x00c5<<2),(UINT)((_rd32(_REG_BASE_+(0x00c5<<2))&(~ValSft_L10(BitMask_02)))|ValSft_L10((val)&BitMask_02)))

#define IRIS_TLVr				(ValSft_R00(_rd32(_REG_BASE_+(0x00c5<<2)))&BitMask_10)
#define IRIS_TLVw(val)			_wr32(_REG_BASE_+(0x00c5<<2),(UINT)((_rd32(_REG_BASE_+(0x00c5<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define IRIS_TGAr				(ValSft_R16(_rd32(_REG_BASE_+(0x00c6<<2)))&BitMask_10)
#define IRIS_TGAw(val)			_wr32(_REG_BASE_+(0x00c6<<2),(UINT)((_rd32(_REG_BASE_+(0x00c6<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define IRIS_OFSr				(ValSft_R00(_rd32(_REG_BASE_+(0x00c6<<2)))&BitMask_16)
#define IRIS_OFSw(val)			_wr32(_REG_BASE_+(0x00c6<<2),(UINT)((_rd32(_REG_BASE_+(0x00c6<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define IRIS_CLPLr				(ValSft_R16(_rd32(_REG_BASE_+(0x00c7<<2)))&BitMask_16)
#define IRIS_CLPLw(val)			_wr32(_REG_BASE_+(0x00c7<<2),(UINT)((_rd32(_REG_BASE_+(0x00c7<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define IRIS_CLPHr				(ValSft_R00(_rd32(_REG_BASE_+(0x00c7<<2)))&BitMask_16)
#define IRIS_CLPHw(val)			_wr32(_REG_BASE_+(0x00c7<<2),(UINT)((_rd32(_REG_BASE_+(0x00c7<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define IRIS_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00c8<<2)))&BitMask_16)
#define IRIS_VSPw(val)			_wr32(_REG_BASE_+(0x00c8<<2),(UINT)((_rd32(_REG_BASE_+(0x00c8<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define IRIS_VEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00c8<<2)))&BitMask_16)
#define IRIS_VEPw(val)			_wr32(_REG_BASE_+(0x00c8<<2),(UINT)((_rd32(_REG_BASE_+(0x00c8<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define IRIS_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00c9<<2)))&BitMask_16)
#define IRIS_HSPw(val)			_wr32(_REG_BASE_+(0x00c9<<2),(UINT)((_rd32(_REG_BASE_+(0x00c9<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define IRIS_HEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00c9<<2)))&BitMask_16)
#define IRIS_HEPw(val)			_wr32(_REG_BASE_+(0x00c9<<2),(UINT)((_rd32(_REG_BASE_+(0x00c9<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define AF_YLPFr				(ValSft_R31(_rd32(_REG_BASE_+(0x00d0<<2)))&BitMask_01)
#define AF_YLPFw(val)			_wr32(_REG_BASE_+(0x00d0<<2),(UINT)((_rd32(_REG_BASE_+(0x00d0<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define AF_BITSELr				(ValSft_R28(_rd32(_REG_BASE_+(0x00d0<<2)))&BitMask_03)
#define AF_BITSELw(val)			_wr32(_REG_BASE_+(0x00d0<<2),(UINT)((_rd32(_REG_BASE_+(0x00d0<<2))&(~ValSft_L28(BitMask_03)))|ValSft_L28((val)&BitMask_03)))

#define AF1_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00d0<<2)))&BitMask_12)
#define AF1_HSPw(val)			_wr32(_REG_BASE_+(0x00d0<<2),(UINT)((_rd32(_REG_BASE_+(0x00d0<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AF1_HEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00d0<<2)))&BitMask_12)
#define AF1_HEPw(val)			_wr32(_REG_BASE_+(0x00d0<<2),(UINT)((_rd32(_REG_BASE_+(0x00d0<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define AF1_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00d1<<2)))&BitMask_12)
#define AF1_VSPw(val)			_wr32(_REG_BASE_+(0x00d1<<2),(UINT)((_rd32(_REG_BASE_+(0x00d1<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AF1_VEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x00d1<<2)))&BitMask_12)
#define AF1_VEPw(val)			_wr32(_REG_BASE_+(0x00d1<<2),(UINT)((_rd32(_REG_BASE_+(0x00d1<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define AF_CLIPr				(ValSft_R16(_rd32(_REG_BASE_+(0x00d4<<2)))&BitMask_10)
#define AF_CLIPw(val)			_wr32(_REG_BASE_+(0x00d4<<2),(UINT)((_rd32(_REG_BASE_+(0x00d4<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AF_SLICEr				(ValSft_R00(_rd32(_REG_BASE_+(0x00d4<<2)))&BitMask_10)
#define AF_SLICEw(val)			_wr32(_REG_BASE_+(0x00d4<<2),(UINT)((_rd32(_REG_BASE_+(0x00d4<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AF_PDr					(ValSft_R31(_rd32(_REG_BASE_+(0x00d5<<2)))&BitMask_01)
#define AF_PDw(val)				_wr32(_REG_BASE_+(0x00d5<<2),(UINT)((_rd32(_REG_BASE_+(0x00d5<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define AF_CLIP_ONr				(ValSft_R30(_rd32(_REG_BASE_+(0x00d5<<2)))&BitMask_01)
#define AF_CLIP_ONw(val)		_wr32(_REG_BASE_+(0x00d5<<2),(UINT)((_rd32(_REG_BASE_+(0x00d5<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define AF2_HTABr				(ValSft_R12(_rd32(_REG_BASE_+(0x00d5<<2)))&BitMask_03)
#define AF2_HTABw(val)			_wr32(_REG_BASE_+(0x00d5<<2),(UINT)((_rd32(_REG_BASE_+(0x00d5<<2))&(~ValSft_L12(BitMask_03)))|ValSft_L12((val)&BitMask_03)))

#define AF1_HTABr				(ValSft_R08(_rd32(_REG_BASE_+(0x00d5<<2)))&BitMask_03)
#define AF1_HTABw(val)			_wr32(_REG_BASE_+(0x00d5<<2),(UINT)((_rd32(_REG_BASE_+(0x00d5<<2))&(~ValSft_L08(BitMask_03)))|ValSft_L08((val)&BitMask_03)))

#define AF_WIN_SELr				(ValSft_R04(_rd32(_REG_BASE_+(0x00d5<<2)))&BitMask_02)
#define AF_WIN_SELw(val)		_wr32(_REG_BASE_+(0x00d5<<2),(UINT)((_rd32(_REG_BASE_+(0x00d5<<2))&(~ValSft_L04(BitMask_02)))|ValSft_L04((val)&BitMask_02)))

#define AF_LOCK_SELr			(ValSft_R00(_rd32(_REG_BASE_+(0x00d5<<2)))&BitMask_01)
#define AF_LOCK_SELw(val)		_wr32(_REG_BASE_+(0x00d5<<2),(UINT)((_rd32(_REG_BASE_+(0x00d5<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define AF_CHSELr				(ValSft_R30(_rd32(_REG_BASE_+(0x00d6<<2)))&BitMask_02)
#define AF_CHSELw(val)			_wr32(_REG_BASE_+(0x00d6<<2),(UINT)((_rd32(_REG_BASE_+(0x00d6<<2))&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define AWB_BITSELr				(ValSft_R12(_rd32(_REG_BASE_+(0x00e0<<2)))&BitMask_03)
#define AWB_BITSELw(val)		_wr32(_REG_BASE_+(0x00e0<<2),(UINT)((_rd32(_REG_BASE_+(0x00e0<<2))&(~ValSft_L12(BitMask_03)))|ValSft_L12((val)&BitMask_03)))

#define AWB_CHSELr				(ValSft_R10(_rd32(_REG_BASE_+(0x00e0<<2)))&BitMask_02)
#define AWB_CHSELw(val)			_wr32(_REG_BASE_+(0x00e0<<2),(UINT)((_rd32(_REG_BASE_+(0x00e0<<2))&(~ValSft_L10(BitMask_02)))|ValSft_L10((val)&BitMask_02)))

#define AWB_SUBWIN_SPCr			(ValSft_R00(_rd32(_REG_BASE_+(0x00e0<<2)))&BitMask_10)
#define AWB_SUBWIN_SPCw(val)	_wr32(_REG_BASE_+(0x00e0<<2),(UINT)((_rd32(_REG_BASE_+(0x00e0<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AWB_SUBWIN_HSPr			(ValSft_R16(_rd32(_REG_BASE_+(0x00e1<<2)))&BitMask_12)
#define AWB_SUBWIN_HSPw(val)	_wr32(_REG_BASE_+(0x00e1<<2),(UINT)((_rd32(_REG_BASE_+(0x00e1<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AWB_SUBWIN_VSPr			(ValSft_R00(_rd32(_REG_BASE_+(0x00e1<<2)))&BitMask_12)
#define AWB_SUBWIN_VSPw(val)	_wr32(_REG_BASE_+(0x00e1<<2),(UINT)((_rd32(_REG_BASE_+(0x00e1<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define ODM_M1r					(ValSft_R20(_rd32(_REG_BASE_+(0x00e2<<2)))&BitMask_10)
#define ODM_M1w(val)			_wr32(_REG_BASE_+(0x00e2<<2),(UINT)((_rd32(_REG_BASE_+(0x00e2<<2))&(~ValSft_L20(BitMask_10)))|ValSft_L20((val)&BitMask_10)))

#define ODM_M2r					(ValSft_R10(_rd32(_REG_BASE_+(0x00e2<<2)))&BitMask_10)
#define ODM_M2w(val)			_wr32(_REG_BASE_+(0x00e2<<2),(UINT)((_rd32(_REG_BASE_+(0x00e2<<2))&(~ValSft_L10(BitMask_10)))|ValSft_L10((val)&BitMask_10)))

#define ODM_M3r					(ValSft_R00(_rd32(_REG_BASE_+(0x00e2<<2)))&BitMask_10)
#define ODM_M3w(val)			_wr32(_REG_BASE_+(0x00e2<<2),(UINT)((_rd32(_REG_BASE_+(0x00e2<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ODM_M4r					(ValSft_R20(_rd32(_REG_BASE_+(0x00e3<<2)))&BitMask_10)
#define ODM_M4w(val)			_wr32(_REG_BASE_+(0x00e3<<2),(UINT)((_rd32(_REG_BASE_+(0x00e3<<2))&(~ValSft_L20(BitMask_10)))|ValSft_L20((val)&BitMask_10)))

#define ODM_M5r					(ValSft_R10(_rd32(_REG_BASE_+(0x00e3<<2)))&BitMask_10)
#define ODM_M5w(val)			_wr32(_REG_BASE_+(0x00e3<<2),(UINT)((_rd32(_REG_BASE_+(0x00e3<<2))&(~ValSft_L10(BitMask_10)))|ValSft_L10((val)&BitMask_10)))

#define ODM_M6r					(ValSft_R00(_rd32(_REG_BASE_+(0x00e3<<2)))&BitMask_10)
#define ODM_M6w(val)			_wr32(_REG_BASE_+(0x00e3<<2),(UINT)((_rd32(_REG_BASE_+(0x00e3<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ODM_M7r					(ValSft_R20(_rd32(_REG_BASE_+(0x00e4<<2)))&BitMask_10)
#define ODM_M7w(val)			_wr32(_REG_BASE_+(0x00e4<<2),(UINT)((_rd32(_REG_BASE_+(0x00e4<<2))&(~ValSft_L20(BitMask_10)))|ValSft_L20((val)&BitMask_10)))

#define ODM_M8r					(ValSft_R10(_rd32(_REG_BASE_+(0x00e4<<2)))&BitMask_10)
#define ODM_M8w(val)			_wr32(_REG_BASE_+(0x00e4<<2),(UINT)((_rd32(_REG_BASE_+(0x00e4<<2))&(~ValSft_L10(BitMask_10)))|ValSft_L10((val)&BitMask_10)))

#define ODM_M9r					(ValSft_R00(_rd32(_REG_BASE_+(0x00e4<<2)))&BitMask_10)
#define ODM_M9w(val)			_wr32(_REG_BASE_+(0x00e4<<2),(UINT)((_rd32(_REG_BASE_+(0x00e4<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AWB_WIN1_HSPr			(ValSft_R16(_rd32(_REG_BASE_+(0x00e5<<2)))&BitMask_12)
#define AWB_WIN1_HSPw(val)		_wr32(_REG_BASE_+(0x00e5<<2),(UINT)((_rd32(_REG_BASE_+(0x00e5<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AWB_WIN1_HWr			(ValSft_R00(_rd32(_REG_BASE_+(0x00e5<<2)))&BitMask_12)
#define AWB_WIN1_HWw(val)		_wr32(_REG_BASE_+(0x00e5<<2),(UINT)((_rd32(_REG_BASE_+(0x00e5<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define AWB_WIN1_VSPr			(ValSft_R16(_rd32(_REG_BASE_+(0x00e6<<2)))&BitMask_12)
#define AWB_WIN1_VSPw(val)		_wr32(_REG_BASE_+(0x00e6<<2),(UINT)((_rd32(_REG_BASE_+(0x00e6<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AWB_WIN1_VWr			(ValSft_R00(_rd32(_REG_BASE_+(0x00e6<<2)))&BitMask_12)
#define AWB_WIN1_VWw(val)		_wr32(_REG_BASE_+(0x00e6<<2),(UINT)((_rd32(_REG_BASE_+(0x00e6<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define AWBL0_DBOFFSETr			(ValSft_R16(_rd32(_REG_BASE_+(0x00e7<<2)))&BitMask_10)
#define AWBL0_DBOFFSETw(val)	_wr32(_REG_BASE_+(0x00e7<<2),(UINT)((_rd32(_REG_BASE_+(0x00e7<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AWBL0_DROFFSETr			(ValSft_R00(_rd32(_REG_BASE_+(0x00e7<<2)))&BitMask_10)
#define AWBL0_DROFFSETw(val)	_wr32(_REG_BASE_+(0x00e7<<2),(UINT)((_rd32(_REG_BASE_+(0x00e7<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AWBL_HTAB_SELr			(ValSft_R30(_rd32(_REG_BASE_+(0x00e8<<2)))&BitMask_02)
#define AWBL_HTAB_SELw(val)		_wr32(_REG_BASE_+(0x00e8<<2),(UINT)((_rd32(_REG_BASE_+(0x00e8<<2))&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define AWB_LOCK_SELr			(ValSft_R29(_rd32(_REG_BASE_+(0x00e8<<2)))&BitMask_01)
#define AWB_LOCK_SELw(val)		_wr32(_REG_BASE_+(0x00e8<<2),(UINT)((_rd32(_REG_BASE_+(0x00e8<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define AWBLNOR_SELr			(ValSft_R28(_rd32(_REG_BASE_+(0x00e8<<2)))&BitMask_01)
#define AWBLNOR_SELw(val)		_wr32(_REG_BASE_+(0x00e8<<2),(UINT)((_rd32(_REG_BASE_+(0x00e8<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define AWBLCBCRO_SELr			(ValSft_R27(_rd32(_REG_BASE_+(0x00e8<<2)))&BitMask_01)
#define AWBLCBCRO_SELw(val)		_wr32(_REG_BASE_+(0x00e8<<2),(UINT)((_rd32(_REG_BASE_+(0x00e8<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define AWBLYEDGE_THr			(ValSft_R16(_rd32(_REG_BASE_+(0x00e8<<2)))&BitMask_10)
#define AWBLYEDGE_THw(val)		_wr32(_REG_BASE_+(0x00e8<<2),(UINT)((_rd32(_REG_BASE_+(0x00e8<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AWBL_DBGAIN0r			(ValSft_R08(_rd32(_REG_BASE_+(0x00e8<<2)))&BitMask_08)
#define AWBL_DBGAIN0w(val)		_wr32(_REG_BASE_+(0x00e8<<2),(UINT)((_rd32(_REG_BASE_+(0x00e8<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define AWBL_DRGAIN0r			(ValSft_R00(_rd32(_REG_BASE_+(0x00e8<<2)))&BitMask_08)
#define AWBL_DRGAIN0w(val)		_wr32(_REG_BASE_+(0x00e8<<2),(UINT)((_rd32(_REG_BASE_+(0x00e8<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define AWBL_CLSL_ISELr			(ValSft_R31(_rd32(_REG_BASE_+(0x00e9<<2)))&BitMask_01)
#define AWBL_CLSL_ISELw(val)	_wr32(_REG_BASE_+(0x00e9<<2),(UINT)((_rd32(_REG_BASE_+(0x00e9<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define AWBL_CYCLIPr			(ValSft_R16(_rd32(_REG_BASE_+(0x00e9<<2)))&BitMask_10)
#define AWBL_CYCLIPw(val)		_wr32(_REG_BASE_+(0x00e9<<2),(UINT)((_rd32(_REG_BASE_+(0x00e9<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AWBL_OSD_SELr			(ValSft_R00(_rd32(_REG_BASE_+(0x00e9<<2)))&BitMask_08)
#define AWBL_OSD_SELw(val)		_wr32(_REG_BASE_+(0x00e9<<2),(UINT)((_rd32(_REG_BASE_+(0x00e9<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define AWBLOSD_ONr				(ValSft_R31(_rd32(_REG_BASE_+(0x00ea<<2)))&BitMask_01)
#define AWBLOSD_ONw(val)		_wr32(_REG_BASE_+(0x00ea<<2),(UINT)((_rd32(_REG_BASE_+(0x00ea<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define AWBL_CYSLICEr			(ValSft_R00(_rd32(_REG_BASE_+(0x00ea<<2)))&BitMask_10)
#define AWBL_CYSLICEw(val)		_wr32(_REG_BASE_+(0x00ea<<2),(UINT)((_rd32(_REG_BASE_+(0x00ea<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AWBL_CRSLICEr			(ValSft_R16(_rd32(_REG_BASE_+(0x00eb<<2)))&BitMask_10)
#define AWBL_CRSLICEw(val)		_wr32(_REG_BASE_+(0x00eb<<2),(UINT)((_rd32(_REG_BASE_+(0x00eb<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AWBL_CRCLIPr			(ValSft_R00(_rd32(_REG_BASE_+(0x00eb<<2)))&BitMask_10)
#define AWBL_CRCLIPw(val)		_wr32(_REG_BASE_+(0x00eb<<2),(UINT)((_rd32(_REG_BASE_+(0x00eb<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AWBL_CGSLICEr			(ValSft_R16(_rd32(_REG_BASE_+(0x00ec<<2)))&BitMask_10)
#define AWBL_CGSLICEw(val)		_wr32(_REG_BASE_+(0x00ec<<2),(UINT)((_rd32(_REG_BASE_+(0x00ec<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AWBL_CGCLIPr			(ValSft_R00(_rd32(_REG_BASE_+(0x00ec<<2)))&BitMask_10)
#define AWBL_CGCLIPw(val)		_wr32(_REG_BASE_+(0x00ec<<2),(UINT)((_rd32(_REG_BASE_+(0x00ec<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AWBL_CBSLICEr			(ValSft_R16(_rd32(_REG_BASE_+(0x00ed<<2)))&BitMask_10)
#define AWBL_CBSLICEw(val)		_wr32(_REG_BASE_+(0x00ed<<2),(UINT)((_rd32(_REG_BASE_+(0x00ed<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define AWBL_CBCLIPr			(ValSft_R00(_rd32(_REG_BASE_+(0x00ed<<2)))&BitMask_10)
#define AWBL_CBCLIPw(val)		_wr32(_REG_BASE_+(0x00ed<<2),(UINT)((_rd32(_REG_BASE_+(0x00ed<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AWBL_CM_VSPr			(ValSft_R16(_rd32(_REG_BASE_+(0x00ee<<2)))&BitMask_12)
#define AWBL_CM_VSPw(val)		_wr32(_REG_BASE_+(0x00ee<<2),(UINT)((_rd32(_REG_BASE_+(0x00ee<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define AWBL_CM_HSPr			(ValSft_R00(_rd32(_REG_BASE_+(0x00ee<<2)))&BitMask_12)
#define AWBL_CM_HSPw(val)		_wr32(_REG_BASE_+(0x00ee<<2),(UINT)((_rd32(_REG_BASE_+(0x00ee<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define STACK0r					(ValSft_R00(_rd32(_REG_BASE_+(0x00f1<<2)))&BitMask_32)
#define STACK0w(val)			_wr32(_REG_BASE_+(0x00f1<<2),(UINT)((_rd32(_REG_BASE_+(0x00f1<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define STACK1r					(ValSft_R00(_rd32(_REG_BASE_+(0x00f2<<2)))&BitMask_32)
#define STACK1w(val)			_wr32(_REG_BASE_+(0x00f2<<2),(UINT)((_rd32(_REG_BASE_+(0x00f2<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define STACK2r					(ValSft_R00(_rd32(_REG_BASE_+(0x00f3<<2)))&BitMask_32)
#define STACK2w(val)			_wr32(_REG_BASE_+(0x00f3<<2),(UINT)((_rd32(_REG_BASE_+(0x00f3<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define STACK3r					(ValSft_R00(_rd32(_REG_BASE_+(0x00f4<<2)))&BitMask_32)
#define STACK3w(val)			_wr32(_REG_BASE_+(0x00f4<<2),(UINT)((_rd32(_REG_BASE_+(0x00f4<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define MANUAL_SYNC_UPr			(ValSft_R31(_rd32(_REG_BASE_+(0x00f5<<2)))&BitMask_01)
#define MANUAL_SYNC_UPw(val)	_wr32(_REG_BASE_+(0x00f5<<2),(UINT)((_rd32(_REG_BASE_+(0x00f5<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define MANUAL_SYNC_ALr			(ValSft_R30(_rd32(_REG_BASE_+(0x00f5<<2)))&BitMask_01)
#define MANUAL_SYNC_ALw(val)	_wr32(_REG_BASE_+(0x00f5<<2),(UINT)((_rd32(_REG_BASE_+(0x00f5<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define MANUAL_LWr				(ValSft_R00(_rd32(_REG_BASE_+(0x00f5<<2)))&BitMask_24)
#define MANUAL_LWw(val)			_wr32(_REG_BASE_+(0x00f5<<2),(UINT)((_rd32(_REG_BASE_+(0x00f5<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define UIRQ_FHPOS0r			(ValSft_R16(_rd32(_REG_BASE_+(0x00f6<<2)))&BitMask_13)
#define UIRQ_FHPOS0w(val)		_wr32(_REG_BASE_+(0x00f6<<2),(UINT)((_rd32(_REG_BASE_+(0x00f6<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define UIRQ_FVPOS0r			(ValSft_R00(_rd32(_REG_BASE_+(0x00f6<<2)))&BitMask_13)
#define UIRQ_FVPOS0w(val)		_wr32(_REG_BASE_+(0x00f6<<2),(UINT)((_rd32(_REG_BASE_+(0x00f6<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define UIRQ_FHPOS1r			(ValSft_R16(_rd32(_REG_BASE_+(0x00f7<<2)))&BitMask_13)
#define UIRQ_FHPOS1w(val)		_wr32(_REG_BASE_+(0x00f7<<2),(UINT)((_rd32(_REG_BASE_+(0x00f7<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define UIRQ_FVPOS1r			(ValSft_R00(_rd32(_REG_BASE_+(0x00f7<<2)))&BitMask_13)
#define UIRQ_FVPOS1w(val)		_wr32(_REG_BASE_+(0x00f7<<2),(UINT)((_rd32(_REG_BASE_+(0x00f7<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define UIRQ_PHPOS0r			(ValSft_R16(_rd32(_REG_BASE_+(0x00f8<<2)))&BitMask_13)
#define UIRQ_PHPOS0w(val)		_wr32(_REG_BASE_+(0x00f8<<2),(UINT)((_rd32(_REG_BASE_+(0x00f8<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define UIRQ_PVPOS0r			(ValSft_R00(_rd32(_REG_BASE_+(0x00f8<<2)))&BitMask_13)
#define UIRQ_PVPOS0w(val)		_wr32(_REG_BASE_+(0x00f8<<2),(UINT)((_rd32(_REG_BASE_+(0x00f8<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define UIRQ_PHPOS1r			(ValSft_R16(_rd32(_REG_BASE_+(0x00f9<<2)))&BitMask_13)
#define UIRQ_PHPOS1w(val)		_wr32(_REG_BASE_+(0x00f9<<2),(UINT)((_rd32(_REG_BASE_+(0x00f9<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define UIRQ_PVPOS1r			(ValSft_R00(_rd32(_REG_BASE_+(0x00f9<<2)))&BitMask_13)
#define UIRQ_PVPOS1w(val)		_wr32(_REG_BASE_+(0x00f9<<2),(UINT)((_rd32(_REG_BASE_+(0x00f9<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define CLI_VLOCKLr				(ValSft_R31(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define CLI_VLOCKLw(val)		_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define CLI_VLOCKWr				(ValSft_R30(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define CLI_VLOCKWw(val)		_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define CLI_VLOCKOr				(ValSft_R29(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define CLI_VLOCKOw(val)		_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define CLI_UIRQF0r				(ValSft_R26(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define CLI_UIRQF0w(val)		_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define CLI_UIRQF1r				(ValSft_R25(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define CLI_UIRQF1w(val)		_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L25(BitMask_01)))|ValSft_L25((val)&BitMask_01)))

#define CLI_UIRQP0r				(ValSft_R24(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define CLI_UIRQP0w(val)		_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L24(BitMask_01)))|ValSft_L24((val)&BitMask_01)))

#define CLI_UIRQP1r				(ValSft_R23(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define CLI_UIRQP1w(val)		_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define CLI_ADCr				(ValSft_R20(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define CLI_ADCw(val)			_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L20(BitMask_01)))|ValSft_L20((val)&BitMask_01)))

#define CLI_MANUALr				(ValSft_R19(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define CLI_MANUALw(val)		_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L19(BitMask_01)))|ValSft_L19((val)&BitMask_01)))

#define CLI_B8UDr				(ValSft_R18(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define CLI_B8UDw(val)			_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L18(BitMask_01)))|ValSft_L18((val)&BitMask_01)))

#define VIRQI_ENr				(ValSft_R15(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define VIRQI_ENw(val)			_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define VIRQW_ENr				(ValSft_R14(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define VIRQW_ENw(val)			_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L14(BitMask_01)))|ValSft_L14((val)&BitMask_01)))

#define VIRQO_ENr				(ValSft_R13(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define VIRQO_ENw(val)			_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L13(BitMask_01)))|ValSft_L13((val)&BitMask_01)))

#define VIRQF_EN0r				(ValSft_R10(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define VIRQF_EN0w(val)			_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L10(BitMask_01)))|ValSft_L10((val)&BitMask_01)))

#define VIRQF_EN1r				(ValSft_R09(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define VIRQF_EN1w(val)			_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L09(BitMask_01)))|ValSft_L09((val)&BitMask_01)))

#define VIRQP_EN0r				(ValSft_R08(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define VIRQP_EN0w(val)			_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L08(BitMask_01)))|ValSft_L08((val)&BitMask_01)))

#define VIRQP_EN1r				(ValSft_R07(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define VIRQP_EN1w(val)			_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

#define ADC_INT_ENr				(ValSft_R06(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define ADC_INT_ENw(val)		_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))

#define MANUAL_INT_ENr			(ValSft_R05(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define MANUAL_INT_ENw(val)		_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))

#define B8UD_IRQ_ENr			(ValSft_R04(_rd32(_REG_BASE_+(0x00fa<<2)))&BitMask_01)
#define B8UD_IRQ_ENw(val)		_wr32(_REG_BASE_+(0x00fa<<2),(UINT)((_rd32(_REG_BASE_+(0x00fa<<2))&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))

#define SS_DATA5r				(ValSft_R24(_rd32(_REG_BASE_+(0x00fd<<2)))&BitMask_08)
#define SS_DATA5w(val)			_wr32(_REG_BASE_+(0x00fd<<2),(UINT)((_rd32(_REG_BASE_+(0x00fd<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define SS_DATA1r				(ValSft_R24(_rd32(_REG_BASE_+(0x00fe<<2)))&BitMask_08)
#define SS_DATA1w(val)			_wr32(_REG_BASE_+(0x00fe<<2),(UINT)((_rd32(_REG_BASE_+(0x00fe<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define SS_DATA2r				(ValSft_R16(_rd32(_REG_BASE_+(0x00fe<<2)))&BitMask_08)
#define SS_DATA2w(val)			_wr32(_REG_BASE_+(0x00fe<<2),(UINT)((_rd32(_REG_BASE_+(0x00fe<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define SS_DATA3r				(ValSft_R08(_rd32(_REG_BASE_+(0x00fe<<2)))&BitMask_08)
#define SS_DATA3w(val)			_wr32(_REG_BASE_+(0x00fe<<2),(UINT)((_rd32(_REG_BASE_+(0x00fe<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define SS_DATA4r				(ValSft_R00(_rd32(_REG_BASE_+(0x00fe<<2)))&BitMask_08)
#define SS_DATA4w(val)			_wr32(_REG_BASE_+(0x00fe<<2),(UINT)((_rd32(_REG_BASE_+(0x00fe<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define SS_CMDr					(ValSft_R00(_rd32(_REG_BASE_+(0x00ff<<2)))&BitMask_01)
#define SS_CMDw(val)			_wr32(_REG_BASE_+(0x00ff<<2),(UINT)((_rd32(_REG_BASE_+(0x00ff<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define RGB_BYPr				(ValSft_R31(_rd32(_REG_BASE_+(0x0100<<2)))&BitMask_01)
#define RGB_BYPw(val)			_wr32(_REG_BASE_+(0x0100<<2),(UINT)((_rd32(_REG_BASE_+(0x0100<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define ICSELr					(ValSft_R28(_rd32(_REG_BASE_+(0x0102<<2)))&BitMask_02)
#define ICSELw(val)				_wr32(_REG_BASE_+(0x0102<<2),(UINT)((_rd32(_REG_BASE_+(0x0102<<2))&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define POST_YBGAINr			(ValSft_R16(_rd32(_REG_BASE_+(0x0104<<2)))&BitMask_08)
#define POST_YBGAINw(val)		_wr32(_REG_BASE_+(0x0104<<2),(UINT)((_rd32(_REG_BASE_+(0x0104<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define POST_YGGAINr			(ValSft_R08(_rd32(_REG_BASE_+(0x0104<<2)))&BitMask_08)
#define POST_YGGAINw(val)		_wr32(_REG_BASE_+(0x0104<<2),(UINT)((_rd32(_REG_BASE_+(0x0104<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define POST_YRGAINr			(ValSft_R00(_rd32(_REG_BASE_+(0x0104<<2)))&BitMask_08)
#define POST_YRGAINw(val)		_wr32(_REG_BASE_+(0x0104<<2),(UINT)((_rd32(_REG_BASE_+(0x0104<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define POST_CRGAINr			(ValSft_R16(_rd32(_REG_BASE_+(0x0105<<2)))&BitMask_08)
#define POST_CRGAINw(val)		_wr32(_REG_BASE_+(0x0105<<2),(UINT)((_rd32(_REG_BASE_+(0x0105<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define POST_CGGAINr			(ValSft_R08(_rd32(_REG_BASE_+(0x0105<<2)))&BitMask_08)
#define POST_CGGAINw(val)		_wr32(_REG_BASE_+(0x0105<<2),(UINT)((_rd32(_REG_BASE_+(0x0105<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define POST_CBGAINr			(ValSft_R00(_rd32(_REG_BASE_+(0x0105<<2)))&BitMask_08)
#define POST_CBGAINw(val)		_wr32(_REG_BASE_+(0x0105<<2),(UINT)((_rd32(_REG_BASE_+(0x0105<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define PR_OFSr					(ValSft_R00(_rd32(_REG_BASE_+(0x0106<<2)))&BitMask_11)
#define PR_OFSw(val)			_wr32(_REG_BASE_+(0x0106<<2),(UINT)((_rd32(_REG_BASE_+(0x0106<<2))&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define PG_OFSr					(ValSft_R12(_rd32(_REG_BASE_+(0x0107<<2)))&BitMask_11)
#define PG_OFSw(val)			_wr32(_REG_BASE_+(0x0107<<2),(UINT)((_rd32(_REG_BASE_+(0x0107<<2))&(~ValSft_L12(BitMask_11)))|ValSft_L12((val)&BitMask_11)))

#define PB_OFSr					(ValSft_R00(_rd32(_REG_BASE_+(0x0107<<2)))&BitMask_11)
#define PB_OFSw(val)			_wr32(_REG_BASE_+(0x0107<<2),(UINT)((_rd32(_REG_BASE_+(0x0107<<2))&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define WPRG_GAINr				(ValSft_R16(_rd32(_REG_BASE_+(0x0108<<2)))&BitMask_13)
#define WPRG_GAINw(val)			_wr32(_REG_BASE_+(0x0108<<2),(UINT)((_rd32(_REG_BASE_+(0x0108<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define WPRR_GAINr				(ValSft_R00(_rd32(_REG_BASE_+(0x0108<<2)))&BitMask_13)
#define WPRR_GAINw(val)			_wr32(_REG_BASE_+(0x0108<<2),(UINT)((_rd32(_REG_BASE_+(0x0108<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define WPGR_GAINr				(ValSft_R16(_rd32(_REG_BASE_+(0x0109<<2)))&BitMask_13)
#define WPGR_GAINw(val)			_wr32(_REG_BASE_+(0x0109<<2),(UINT)((_rd32(_REG_BASE_+(0x0109<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define WPRB_GAINr				(ValSft_R00(_rd32(_REG_BASE_+(0x0109<<2)))&BitMask_13)
#define WPRB_GAINw(val)			_wr32(_REG_BASE_+(0x0109<<2),(UINT)((_rd32(_REG_BASE_+(0x0109<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define WPGB_GAINr				(ValSft_R16(_rd32(_REG_BASE_+(0x010a<<2)))&BitMask_13)
#define WPGB_GAINw(val)			_wr32(_REG_BASE_+(0x010a<<2),(UINT)((_rd32(_REG_BASE_+(0x010a<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define WPGG_GAINr				(ValSft_R00(_rd32(_REG_BASE_+(0x010a<<2)))&BitMask_13)
#define WPGG_GAINw(val)			_wr32(_REG_BASE_+(0x010a<<2),(UINT)((_rd32(_REG_BASE_+(0x010a<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define WPBG_GAINr				(ValSft_R16(_rd32(_REG_BASE_+(0x010b<<2)))&BitMask_13)
#define WPBG_GAINw(val)			_wr32(_REG_BASE_+(0x010b<<2),(UINT)((_rd32(_REG_BASE_+(0x010b<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define WPBR_GAINr				(ValSft_R00(_rd32(_REG_BASE_+(0x010b<<2)))&BitMask_13)
#define WPBR_GAINw(val)			_wr32(_REG_BASE_+(0x010b<<2),(UINT)((_rd32(_REG_BASE_+(0x010b<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define WPBB_GAINr				(ValSft_R16(_rd32(_REG_BASE_+(0x010c<<2)))&BitMask_13)
#define WPBB_GAINw(val)			_wr32(_REG_BASE_+(0x010c<<2),(UINT)((_rd32(_REG_BASE_+(0x010c<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define PWL_ONr					(ValSft_R31(_rd32(_REG_BASE_+(0x0110<<2)))&BitMask_01)
#define PWL_ONw(val)			_wr32(_REG_BASE_+(0x0110<<2),(UINT)((_rd32(_REG_BASE_+(0x0110<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define PWL_OBITr				(ValSft_R28(_rd32(_REG_BASE_+(0x0110<<2)))&BitMask_03)
#define PWL_OBITw(val)			_wr32(_REG_BASE_+(0x0110<<2),(UINT)((_rd32(_REG_BASE_+(0x0110<<2))&(~ValSft_L28(BitMask_03)))|ValSft_L28((val)&BitMask_03)))

#define PWL_IBITr				(ValSft_R26(_rd32(_REG_BASE_+(0x0110<<2)))&BitMask_02)
#define PWL_IBITw(val)			_wr32(_REG_BASE_+(0x0110<<2),(UINT)((_rd32(_REG_BASE_+(0x0110<<2))&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define PWL_Y0r					(ValSft_R00(_rd32(_REG_BASE_+(0x0110<<2)))&BitMask_24)
#define PWL_Y0w(val)			_wr32(_REG_BASE_+(0x0110<<2),(UINT)((_rd32(_REG_BASE_+(0x0110<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define PWL_Y1r					(ValSft_R00(_rd32(_REG_BASE_+(0x0111<<2)))&BitMask_24)
#define PWL_Y1w(val)			_wr32(_REG_BASE_+(0x0111<<2),(UINT)((_rd32(_REG_BASE_+(0x0111<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define PWL_Y2r					(ValSft_R00(_rd32(_REG_BASE_+(0x0112<<2)))&BitMask_24)
#define PWL_Y2w(val)			_wr32(_REG_BASE_+(0x0112<<2),(UINT)((_rd32(_REG_BASE_+(0x0112<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define PWL_Y3r					(ValSft_R00(_rd32(_REG_BASE_+(0x0113<<2)))&BitMask_24)
#define PWL_Y3w(val)			_wr32(_REG_BASE_+(0x0113<<2),(UINT)((_rd32(_REG_BASE_+(0x0113<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define PWL_Y4r					(ValSft_R00(_rd32(_REG_BASE_+(0x0114<<2)))&BitMask_24)
#define PWL_Y4w(val)			_wr32(_REG_BASE_+(0x0114<<2),(UINT)((_rd32(_REG_BASE_+(0x0114<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define PWL_Y5r					(ValSft_R00(_rd32(_REG_BASE_+(0x0115<<2)))&BitMask_24)
#define PWL_Y5w(val)			_wr32(_REG_BASE_+(0x0115<<2),(UINT)((_rd32(_REG_BASE_+(0x0115<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define PWL_Y6r					(ValSft_R00(_rd32(_REG_BASE_+(0x0116<<2)))&BitMask_24)
#define PWL_Y6w(val)			_wr32(_REG_BASE_+(0x0116<<2),(UINT)((_rd32(_REG_BASE_+(0x0116<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define PWL_Y7r					(ValSft_R00(_rd32(_REG_BASE_+(0x0117<<2)))&BitMask_24)
#define PWL_Y7w(val)			_wr32(_REG_BASE_+(0x0117<<2),(UINT)((_rd32(_REG_BASE_+(0x0117<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define PWL_Y8r					(ValSft_R00(_rd32(_REG_BASE_+(0x0118<<2)))&BitMask_24)
#define PWL_Y8w(val)			_wr32(_REG_BASE_+(0x0118<<2),(UINT)((_rd32(_REG_BASE_+(0x0118<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define PWL_Y9r					(ValSft_R00(_rd32(_REG_BASE_+(0x0119<<2)))&BitMask_24)
#define PWL_Y9w(val)			_wr32(_REG_BASE_+(0x0119<<2),(UINT)((_rd32(_REG_BASE_+(0x0119<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define PWL_YAr					(ValSft_R00(_rd32(_REG_BASE_+(0x011a<<2)))&BitMask_24)
#define PWL_YAw(val)			_wr32(_REG_BASE_+(0x011a<<2),(UINT)((_rd32(_REG_BASE_+(0x011a<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define PWL_YBr					(ValSft_R00(_rd32(_REG_BASE_+(0x011b<<2)))&BitMask_24)
#define PWL_YBw(val)			_wr32(_REG_BASE_+(0x011b<<2),(UINT)((_rd32(_REG_BASE_+(0x011b<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define PWL_X0r					(ValSft_R16(_rd32(_REG_BASE_+(0x011c<<2)))&BitMask_16)
#define PWL_X0w(val)			_wr32(_REG_BASE_+(0x011c<<2),(UINT)((_rd32(_REG_BASE_+(0x011c<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define PWL_X1r					(ValSft_R00(_rd32(_REG_BASE_+(0x011c<<2)))&BitMask_16)
#define PWL_X1w(val)			_wr32(_REG_BASE_+(0x011c<<2),(UINT)((_rd32(_REG_BASE_+(0x011c<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define PWL_X2r					(ValSft_R16(_rd32(_REG_BASE_+(0x011d<<2)))&BitMask_16)
#define PWL_X2w(val)			_wr32(_REG_BASE_+(0x011d<<2),(UINT)((_rd32(_REG_BASE_+(0x011d<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define PWL_X3r					(ValSft_R00(_rd32(_REG_BASE_+(0x011d<<2)))&BitMask_16)
#define PWL_X3w(val)			_wr32(_REG_BASE_+(0x011d<<2),(UINT)((_rd32(_REG_BASE_+(0x011d<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define PWL_X4r					(ValSft_R16(_rd32(_REG_BASE_+(0x011e<<2)))&BitMask_16)
#define PWL_X4w(val)			_wr32(_REG_BASE_+(0x011e<<2),(UINT)((_rd32(_REG_BASE_+(0x011e<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define PWL_X5r					(ValSft_R00(_rd32(_REG_BASE_+(0x011e<<2)))&BitMask_16)
#define PWL_X5w(val)			_wr32(_REG_BASE_+(0x011e<<2),(UINT)((_rd32(_REG_BASE_+(0x011e<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define PWL_X6r					(ValSft_R16(_rd32(_REG_BASE_+(0x011f<<2)))&BitMask_16)
#define PWL_X6w(val)			_wr32(_REG_BASE_+(0x011f<<2),(UINT)((_rd32(_REG_BASE_+(0x011f<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define PWL_X7r					(ValSft_R00(_rd32(_REG_BASE_+(0x011f<<2)))&BitMask_16)
#define PWL_X7w(val)			_wr32(_REG_BASE_+(0x011f<<2),(UINT)((_rd32(_REG_BASE_+(0x011f<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define PWL_X8r					(ValSft_R16(_rd32(_REG_BASE_+(0x0120<<2)))&BitMask_16)
#define PWL_X8w(val)			_wr32(_REG_BASE_+(0x0120<<2),(UINT)((_rd32(_REG_BASE_+(0x0120<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define PWL_X9r					(ValSft_R00(_rd32(_REG_BASE_+(0x0120<<2)))&BitMask_16)
#define PWL_X9w(val)			_wr32(_REG_BASE_+(0x0120<<2),(UINT)((_rd32(_REG_BASE_+(0x0120<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define PWL_XAr					(ValSft_R00(_rd32(_REG_BASE_+(0x0121<<2)))&BitMask_16)
#define PWL_XAw(val)			_wr32(_REG_BASE_+(0x0121<<2),(UINT)((_rd32(_REG_BASE_+(0x0121<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define PWL_TSELr				(ValSft_R00(_rd32(_REG_BASE_+(0x0122<<2)))&BitMask_04)
#define PWL_TSELw(val)			_wr32(_REG_BASE_+(0x0122<<2),(UINT)((_rd32(_REG_BASE_+(0x0122<<2))&(~ValSft_L00(BitMask_04)))|ValSft_L00((val)&BitMask_04)))

#define CLAMP_ON_1r				(ValSft_R27(_rd32(_REG_BASE_+(0x0128<<2)))&BitMask_01)
#define CLAMP_ON_1w(val)		_wr32(_REG_BASE_+(0x0128<<2),(UINT)((_rd32(_REG_BASE_+(0x0128<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define CLAMP_OSD_ON_1r			(ValSft_R26(_rd32(_REG_BASE_+(0x0128<<2)))&BitMask_01)
#define CLAMP_OSD_ON_1w(val)	_wr32(_REG_BASE_+(0x0128<<2),(UINT)((_rd32(_REG_BASE_+(0x0128<<2))&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define CLAMP_GROFFSET_1r		(ValSft_R16(_rd32(_REG_BASE_+(0x0129<<2)))&BitMask_16)
#define CLAMP_GROFFSET_1w(val)	_wr32(_REG_BASE_+(0x0129<<2),(UINT)((_rd32(_REG_BASE_+(0x0129<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define CLAMP_GBOFFSET_1r		(ValSft_R00(_rd32(_REG_BASE_+(0x0129<<2)))&BitMask_16)
#define CLAMP_GBOFFSET_1w(val)	_wr32(_REG_BASE_+(0x0129<<2),(UINT)((_rd32(_REG_BASE_+(0x0129<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define CLAMP_ROFFSET_1r		(ValSft_R16(_rd32(_REG_BASE_+(0x012a<<2)))&BitMask_16)
#define CLAMP_ROFFSET_1w(val)	_wr32(_REG_BASE_+(0x012a<<2),(UINT)((_rd32(_REG_BASE_+(0x012a<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define CLAMP_BOFFSET_1r		(ValSft_R00(_rd32(_REG_BASE_+(0x012a<<2)))&BitMask_16)
#define CLAMP_BOFFSET_1w(val)	_wr32(_REG_BASE_+(0x012a<<2),(UINT)((_rd32(_REG_BASE_+(0x012a<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define CLAMP_HSP_1r			(ValSft_R16(_rd32(_REG_BASE_+(0x012b<<2)))&BitMask_13)
#define CLAMP_HSP_1w(val)		_wr32(_REG_BASE_+(0x012b<<2),(UINT)((_rd32(_REG_BASE_+(0x012b<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define CLAMP_VSP_1r			(ValSft_R00(_rd32(_REG_BASE_+(0x012b<<2)))&BitMask_12)
#define CLAMP_VSP_1w(val)		_wr32(_REG_BASE_+(0x012b<<2),(UINT)((_rd32(_REG_BASE_+(0x012b<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define CLAMP_ON_2r				(ValSft_R27(_rd32(_REG_BASE_+(0x012c<<2)))&BitMask_01)
#define CLAMP_ON_2w(val)		_wr32(_REG_BASE_+(0x012c<<2),(UINT)((_rd32(_REG_BASE_+(0x012c<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define CLAMP_OSD_ON_2r			(ValSft_R26(_rd32(_REG_BASE_+(0x012c<<2)))&BitMask_01)
#define CLAMP_OSD_ON_2w(val)	_wr32(_REG_BASE_+(0x012c<<2),(UINT)((_rd32(_REG_BASE_+(0x012c<<2))&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define CLAMP_GROFFSET_2r		(ValSft_R16(_rd32(_REG_BASE_+(0x012c<<2)))&BitMask_10)
#define CLAMP_GROFFSET_2w(val)	_wr32(_REG_BASE_+(0x012c<<2),(UINT)((_rd32(_REG_BASE_+(0x012c<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CLAMP_GBOFFSET_2r		(ValSft_R00(_rd32(_REG_BASE_+(0x012c<<2)))&BitMask_10)
#define CLAMP_GBOFFSET_2w(val)	_wr32(_REG_BASE_+(0x012c<<2),(UINT)((_rd32(_REG_BASE_+(0x012c<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CLAMP_ROFFSET_2r		(ValSft_R16(_rd32(_REG_BASE_+(0x012d<<2)))&BitMask_10)
#define CLAMP_ROFFSET_2w(val)	_wr32(_REG_BASE_+(0x012d<<2),(UINT)((_rd32(_REG_BASE_+(0x012d<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CLAMP_BOFFSET_2r		(ValSft_R00(_rd32(_REG_BASE_+(0x012d<<2)))&BitMask_10)
#define CLAMP_BOFFSET_2w(val)	_wr32(_REG_BASE_+(0x012d<<2),(UINT)((_rd32(_REG_BASE_+(0x012d<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CLAMP_HSP_2r			(ValSft_R16(_rd32(_REG_BASE_+(0x012e<<2)))&BitMask_13)
#define CLAMP_HSP_2w(val)		_wr32(_REG_BASE_+(0x012e<<2),(UINT)((_rd32(_REG_BASE_+(0x012e<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define CLAMP_VSP_2r			(ValSft_R00(_rd32(_REG_BASE_+(0x012e<<2)))&BitMask_12)
#define CLAMP_VSP_2w(val)		_wr32(_REG_BASE_+(0x012e<<2),(UINT)((_rd32(_REG_BASE_+(0x012e<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define CLAMP_HW_1r				(ValSft_R20(_rd32(_REG_BASE_+(0x012f<<2)))&BitMask_04)
#define CLAMP_HW_1w(val)		_wr32(_REG_BASE_+(0x012f<<2),(UINT)((_rd32(_REG_BASE_+(0x012f<<2))&(~ValSft_L20(BitMask_04)))|ValSft_L20((val)&BitMask_04)))

#define CLAMP_VW_1r				(ValSft_R16(_rd32(_REG_BASE_+(0x012f<<2)))&BitMask_04)
#define CLAMP_VW_1w(val)		_wr32(_REG_BASE_+(0x012f<<2),(UINT)((_rd32(_REG_BASE_+(0x012f<<2))&(~ValSft_L16(BitMask_04)))|ValSft_L16((val)&BitMask_04)))

#define CLAMP_HW_2r				(ValSft_R12(_rd32(_REG_BASE_+(0x012f<<2)))&BitMask_04)
#define CLAMP_HW_2w(val)		_wr32(_REG_BASE_+(0x012f<<2),(UINT)((_rd32(_REG_BASE_+(0x012f<<2))&(~ValSft_L12(BitMask_04)))|ValSft_L12((val)&BitMask_04)))

#define CLAMP_VW_2r				(ValSft_R08(_rd32(_REG_BASE_+(0x012f<<2)))&BitMask_04)
#define CLAMP_VW_2w(val)		_wr32(_REG_BASE_+(0x012f<<2),(UINT)((_rd32(_REG_BASE_+(0x012f<<2))&(~ValSft_L08(BitMask_04)))|ValSft_L08((val)&BitMask_04)))

#define SHD_BPr					(ValSft_R30(_rd32(_REG_BASE_+(0x0130<<2)))&BitMask_02)
#define SHD_BPw(val)			_wr32(_REG_BASE_+(0x0130<<2),(UINT)((_rd32(_REG_BASE_+(0x0130<<2))&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define SHD_MODEr				(ValSft_R30(_rd32(_REG_BASE_+(0x0131<<2)))&BitMask_02)
#define SHD_MODEw(val)			_wr32(_REG_BASE_+(0x0131<<2),(UINT)((_rd32(_REG_BASE_+(0x0131<<2))&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define SHD_TESTr				(ValSft_R28(_rd32(_REG_BASE_+(0x0131<<2)))&BitMask_02)
#define SHD_TESTw(val)			_wr32(_REG_BASE_+(0x0131<<2),(UINT)((_rd32(_REG_BASE_+(0x0131<<2))&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define SHD_DETOSDr				(ValSft_R27(_rd32(_REG_BASE_+(0x0131<<2)))&BitMask_01)
#define SHD_DETOSDw(val)		_wr32(_REG_BASE_+(0x0131<<2),(UINT)((_rd32(_REG_BASE_+(0x0131<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define SHD_ECHKr				(ValSft_R26(_rd32(_REG_BASE_+(0x0131<<2)))&BitMask_01)
#define SHD_ECHKw(val)			_wr32(_REG_BASE_+(0x0131<<2),(UINT)((_rd32(_REG_BASE_+(0x0131<<2))&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define SHD_GAINr				(ValSft_R00(_rd32(_REG_BASE_+(0x0131<<2)))&BitMask_08)
#define SHD_GAINw(val)			_wr32(_REG_BASE_+(0x0131<<2),(UINT)((_rd32(_REG_BASE_+(0x0131<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define SHD_KHr					(ValSft_R16(_rd32(_REG_BASE_+(0x0132<<2)))&BitMask_10)
#define SHD_KHw(val)			_wr32(_REG_BASE_+(0x0132<<2),(UINT)((_rd32(_REG_BASE_+(0x0132<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define SHD_KVr					(ValSft_R00(_rd32(_REG_BASE_+(0x0132<<2)))&BitMask_10)
#define SHD_KVw(val)			_wr32(_REG_BASE_+(0x0132<<2),(UINT)((_rd32(_REG_BASE_+(0x0132<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define SHD_DHOFFr				(ValSft_R16(_rd32(_REG_BASE_+(0x0133<<2)))&BitMask_13)
#define SHD_DHOFFw(val)			_wr32(_REG_BASE_+(0x0133<<2),(UINT)((_rd32(_REG_BASE_+(0x0133<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define SHD_DVOFFr				(ValSft_R00(_rd32(_REG_BASE_+(0x0133<<2)))&BitMask_13)
#define SHD_DVOFFw(val)			_wr32(_REG_BASE_+(0x0133<<2),(UINT)((_rd32(_REG_BASE_+(0x0133<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define SHD_CHOFFr				(ValSft_R16(_rd32(_REG_BASE_+(0x0134<<2)))&BitMask_12)
#define SHD_CHOFFw(val)			_wr32(_REG_BASE_+(0x0134<<2),(UINT)((_rd32(_REG_BASE_+(0x0134<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define SHD_CVOFFr				(ValSft_R00(_rd32(_REG_BASE_+(0x0134<<2)))&BitMask_12)
#define SHD_CVOFFw(val)			_wr32(_REG_BASE_+(0x0134<<2),(UINT)((_rd32(_REG_BASE_+(0x0134<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define SHD_DHWr				(ValSft_R16(_rd32(_REG_BASE_+(0x0135<<2)))&BitMask_13)
#define SHD_DHWw(val)			_wr32(_REG_BASE_+(0x0135<<2),(UINT)((_rd32(_REG_BASE_+(0x0135<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define SHD_DVWr				(ValSft_R00(_rd32(_REG_BASE_+(0x0135<<2)))&BitMask_13)
#define SHD_DVWw(val)			_wr32(_REG_BASE_+(0x0135<<2),(UINT)((_rd32(_REG_BASE_+(0x0135<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define PGAIN_GR_1r				(ValSft_R16(_rd32(_REG_BASE_+(0x0138<<2)))&BitMask_16)
#define PGAIN_GR_1w(val)		_wr32(_REG_BASE_+(0x0138<<2),(UINT)((_rd32(_REG_BASE_+(0x0138<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define PGAIN_GB_1r				(ValSft_R00(_rd32(_REG_BASE_+(0x0138<<2)))&BitMask_16)
#define PGAIN_GB_1w(val)		_wr32(_REG_BASE_+(0x0138<<2),(UINT)((_rd32(_REG_BASE_+(0x0138<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define PGAIN_R_1r				(ValSft_R16(_rd32(_REG_BASE_+(0x0139<<2)))&BitMask_16)
#define PGAIN_R_1w(val)			_wr32(_REG_BASE_+(0x0139<<2),(UINT)((_rd32(_REG_BASE_+(0x0139<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define PGAIN_B_1r				(ValSft_R00(_rd32(_REG_BASE_+(0x0139<<2)))&BitMask_16)
#define PGAIN_B_1w(val)			_wr32(_REG_BASE_+(0x0139<<2),(UINT)((_rd32(_REG_BASE_+(0x0139<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define PGAIN_GR_2r				(ValSft_R16(_rd32(_REG_BASE_+(0x013a<<2)))&BitMask_16)
#define PGAIN_GR_2w(val)		_wr32(_REG_BASE_+(0x013a<<2),(UINT)((_rd32(_REG_BASE_+(0x013a<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define PGAIN_GB_2r				(ValSft_R00(_rd32(_REG_BASE_+(0x013a<<2)))&BitMask_16)
#define PGAIN_GB_2w(val)		_wr32(_REG_BASE_+(0x013a<<2),(UINT)((_rd32(_REG_BASE_+(0x013a<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define PGAIN_R_2r				(ValSft_R16(_rd32(_REG_BASE_+(0x013b<<2)))&BitMask_16)
#define PGAIN_R_2w(val)			_wr32(_REG_BASE_+(0x013b<<2),(UINT)((_rd32(_REG_BASE_+(0x013b<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define PGAIN_B_2r				(ValSft_R00(_rd32(_REG_BASE_+(0x013b<<2)))&BitMask_16)
#define PGAIN_B_2w(val)			_wr32(_REG_BASE_+(0x013b<<2),(UINT)((_rd32(_REG_BASE_+(0x013b<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define PSGAIN_GRr				(ValSft_R16(_rd32(_REG_BASE_+(0x013c<<2)))&BitMask_16)
#define PSGAIN_GRw(val)			_wr32(_REG_BASE_+(0x013c<<2),(UINT)((_rd32(_REG_BASE_+(0x013c<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define PSGAIN_GBr				(ValSft_R00(_rd32(_REG_BASE_+(0x013c<<2)))&BitMask_16)
#define PSGAIN_GBw(val)			_wr32(_REG_BASE_+(0x013c<<2),(UINT)((_rd32(_REG_BASE_+(0x013c<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define PSGAIN_Rr				(ValSft_R16(_rd32(_REG_BASE_+(0x013d<<2)))&BitMask_16)
#define PSGAIN_Rw(val)			_wr32(_REG_BASE_+(0x013d<<2),(UINT)((_rd32(_REG_BASE_+(0x013d<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define PSGAIN_Br				(ValSft_R00(_rd32(_REG_BASE_+(0x013d<<2)))&BitMask_16)
#define PSGAIN_Bw(val)			_wr32(_REG_BASE_+(0x013d<<2),(UINT)((_rd32(_REG_BASE_+(0x013d<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define DF_TSEL_Lr				(ValSft_R29(_rd32(_REG_BASE_+(0x0141<<2)))&BitMask_03)
#define DF_TSEL_Lw(val)			_wr32(_REG_BASE_+(0x0141<<2),(UINT)((_rd32(_REG_BASE_+(0x0141<<2))&(~ValSft_L29(BitMask_03)))|ValSft_L29((val)&BitMask_03)))

#define DFS_RBG_SELr			(ValSft_R28(_rd32(_REG_BASE_+(0x0141<<2)))&BitMask_01)
#define DFS_RBG_SELw(val)		_wr32(_REG_BASE_+(0x0141<<2),(UINT)((_rd32(_REG_BASE_+(0x0141<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define DF_BITr					(ValSft_R24(_rd32(_REG_BASE_+(0x0141<<2)))&BitMask_03)
#define DF_BITw(val)			_wr32(_REG_BASE_+(0x0141<<2),(UINT)((_rd32(_REG_BASE_+(0x0141<<2))&(~ValSft_L24(BitMask_03)))|ValSft_L24((val)&BitMask_03)))

#define DF_DIFGA_Lr				(ValSft_R24(_rd32(_REG_BASE_+(0x0142<<2)))&BitMask_08)
#define DF_DIFGA_Lw(val)		_wr32(_REG_BASE_+(0x0142<<2),(UINT)((_rd32(_REG_BASE_+(0x0142<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define DF_DIFTH_Lr				(ValSft_R16(_rd32(_REG_BASE_+(0x0142<<2)))&BitMask_08)
#define DF_DIFTH_Lw(val)		_wr32(_REG_BASE_+(0x0142<<2),(UINT)((_rd32(_REG_BASE_+(0x0142<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define DF_CWEGHT_Lr			(ValSft_R14(_rd32(_REG_BASE_+(0x0142<<2)))&BitMask_02)
#define DF_CWEGHT_Lw(val)		_wr32(_REG_BASE_+(0x0142<<2),(UINT)((_rd32(_REG_BASE_+(0x0142<<2))&(~ValSft_L14(BitMask_02)))|ValSft_L14((val)&BitMask_02)))

#define DF_ALPHA_Lr				(ValSft_R08(_rd32(_REG_BASE_+(0x0142<<2)))&BitMask_06)
#define DF_ALPHA_Lw(val)		_wr32(_REG_BASE_+(0x0142<<2),(UINT)((_rd32(_REG_BASE_+(0x0142<<2))&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define DF_BETA_Lr				(ValSft_R00(_rd32(_REG_BASE_+(0x0142<<2)))&BitMask_08)
#define DF_BETA_Lw(val)			_wr32(_REG_BASE_+(0x0142<<2),(UINT)((_rd32(_REG_BASE_+(0x0142<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define DF_DIFOFS_Lr			(ValSft_R16(_rd32(_REG_BASE_+(0x0143<<2)))&BitMask_12)
#define DF_DIFOFS_Lw(val)		_wr32(_REG_BASE_+(0x0143<<2),(UINT)((_rd32(_REG_BASE_+(0x0143<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define DFS_DIFGA_Lr			(ValSft_R08(_rd32(_REG_BASE_+(0x0143<<2)))&BitMask_07)
#define DFS_DIFGA_Lw(val)		_wr32(_REG_BASE_+(0x0143<<2),(UINT)((_rd32(_REG_BASE_+(0x0143<<2))&(~ValSft_L08(BitMask_07)))|ValSft_L08((val)&BitMask_07)))

#define DFS_DIFTH_Lr			(ValSft_R00(_rd32(_REG_BASE_+(0x0143<<2)))&BitMask_08)
#define DFS_DIFTH_Lw(val)		_wr32(_REG_BASE_+(0x0143<<2),(UINT)((_rd32(_REG_BASE_+(0x0143<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define DF_TSEL_Sr				(ValSft_R29(_rd32(_REG_BASE_+(0x0144<<2)))&BitMask_03)
#define DF_TSEL_Sw(val)			_wr32(_REG_BASE_+(0x0144<<2),(UINT)((_rd32(_REG_BASE_+(0x0144<<2))&(~ValSft_L29(BitMask_03)))|ValSft_L29((val)&BitMask_03)))

#define DF_DIFGA_Sr				(ValSft_R24(_rd32(_REG_BASE_+(0x0145<<2)))&BitMask_08)
#define DF_DIFGA_Sw(val)		_wr32(_REG_BASE_+(0x0145<<2),(UINT)((_rd32(_REG_BASE_+(0x0145<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define DF_DIFTH_Sr				(ValSft_R16(_rd32(_REG_BASE_+(0x0145<<2)))&BitMask_08)
#define DF_DIFTH_Sw(val)		_wr32(_REG_BASE_+(0x0145<<2),(UINT)((_rd32(_REG_BASE_+(0x0145<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define DF_CWEGHT_Sr			(ValSft_R14(_rd32(_REG_BASE_+(0x0145<<2)))&BitMask_02)
#define DF_CWEGHT_Sw(val)		_wr32(_REG_BASE_+(0x0145<<2),(UINT)((_rd32(_REG_BASE_+(0x0145<<2))&(~ValSft_L14(BitMask_02)))|ValSft_L14((val)&BitMask_02)))

#define DF_ALPHA_Sr				(ValSft_R08(_rd32(_REG_BASE_+(0x0145<<2)))&BitMask_06)
#define DF_ALPHA_Sw(val)		_wr32(_REG_BASE_+(0x0145<<2),(UINT)((_rd32(_REG_BASE_+(0x0145<<2))&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define DF_BETA_Sr				(ValSft_R00(_rd32(_REG_BASE_+(0x0145<<2)))&BitMask_08)
#define DF_BETA_Sw(val)			_wr32(_REG_BASE_+(0x0145<<2),(UINT)((_rd32(_REG_BASE_+(0x0145<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define DF_DIFOFS_Sr			(ValSft_R16(_rd32(_REG_BASE_+(0x0146<<2)))&BitMask_08)
#define DF_DIFOFS_Sw(val)		_wr32(_REG_BASE_+(0x0146<<2),(UINT)((_rd32(_REG_BASE_+(0x0146<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define DFS_DIFGA_Sr			(ValSft_R08(_rd32(_REG_BASE_+(0x0146<<2)))&BitMask_07)
#define DFS_DIFGA_Sw(val)		_wr32(_REG_BASE_+(0x0146<<2),(UINT)((_rd32(_REG_BASE_+(0x0146<<2))&(~ValSft_L08(BitMask_07)))|ValSft_L08((val)&BitMask_07)))

#define DFS_DIFTH_Sr			(ValSft_R00(_rd32(_REG_BASE_+(0x0146<<2)))&BitMask_08)
#define DFS_DIFTH_Sw(val)		_wr32(_REG_BASE_+(0x0146<<2),(UINT)((_rd32(_REG_BASE_+(0x0146<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define DF_TESTONr				(ValSft_R31(_rd32(_REG_BASE_+(0x0147<<2)))&BitMask_01)
#define DF_TESTONw(val)			_wr32(_REG_BASE_+(0x0147<<2),(UINT)((_rd32(_REG_BASE_+(0x0147<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DF_TESTPH1r				(ValSft_R16(_rd32(_REG_BASE_+(0x0147<<2)))&BitMask_12)
#define DF_TESTPH1w(val)		_wr32(_REG_BASE_+(0x0147<<2),(UINT)((_rd32(_REG_BASE_+(0x0147<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define DF_TESTPV1r				(ValSft_R00(_rd32(_REG_BASE_+(0x0147<<2)))&BitMask_12)
#define DF_TESTPV1w(val)		_wr32(_REG_BASE_+(0x0147<<2),(UINT)((_rd32(_REG_BASE_+(0x0147<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define DF_TESTPH2r				(ValSft_R16(_rd32(_REG_BASE_+(0x0148<<2)))&BitMask_12)
#define DF_TESTPH2w(val)		_wr32(_REG_BASE_+(0x0148<<2),(UINT)((_rd32(_REG_BASE_+(0x0148<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define DF_TESTPV2r				(ValSft_R00(_rd32(_REG_BASE_+(0x0148<<2)))&BitMask_12)
#define DF_TESTPV2w(val)		_wr32(_REG_BASE_+(0x0148<<2),(UINT)((_rd32(_REG_BASE_+(0x0148<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define DF_TESTPH3r				(ValSft_R16(_rd32(_REG_BASE_+(0x0149<<2)))&BitMask_12)
#define DF_TESTPH3w(val)		_wr32(_REG_BASE_+(0x0149<<2),(UINT)((_rd32(_REG_BASE_+(0x0149<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define DF_TESTPV3r				(ValSft_R00(_rd32(_REG_BASE_+(0x0149<<2)))&BitMask_12)
#define DF_TESTPV3w(val)		_wr32(_REG_BASE_+(0x0149<<2),(UINT)((_rd32(_REG_BASE_+(0x0149<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define DF_TESTPH4r				(ValSft_R16(_rd32(_REG_BASE_+(0x014a<<2)))&BitMask_12)
#define DF_TESTPH4w(val)		_wr32(_REG_BASE_+(0x014a<<2),(UINT)((_rd32(_REG_BASE_+(0x014a<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define DF_TESTPV4r				(ValSft_R00(_rd32(_REG_BASE_+(0x014a<<2)))&BitMask_12)
#define DF_TESTPV4w(val)		_wr32(_REG_BASE_+(0x014a<<2),(UINT)((_rd32(_REG_BASE_+(0x014a<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define DF_TESTPLVr				(ValSft_R00(_rd32(_REG_BASE_+(0x014b<<2)))&BitMask_24)
#define DF_TESTPLVw(val)		_wr32(_REG_BASE_+(0x014b<<2),(UINT)((_rd32(_REG_BASE_+(0x014b<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define WDR_SOFFRr				(ValSft_R16(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_16)
#define WDR_SOFFRw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define WDR_SOFFGr				(ValSft_R00(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_16)
#define WDR_SOFFGw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define WDR_SOFFBr				(ValSft_R16(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_16)
#define WDR_SOFFBw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define WDR_LSSWr				(ValSft_R26(_rd32(_REG_BASE_+(0x0150<<2)))&BitMask_01)
#define WDR_LSSWw(val)			_wr32(_REG_BASE_+(0x0150<<2),(UINT)((_rd32(_REG_BASE_+(0x0150<<2))&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define WDR_CHMANr				(ValSft_R24(_rd32(_REG_BASE_+(0x0150<<2)))&BitMask_02)
#define WDR_CHMANw(val)			_wr32(_REG_BASE_+(0x0150<<2),(UINT)((_rd32(_REG_BASE_+(0x0150<<2))&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define WDR_DOLCMPr				(ValSft_R22(_rd32(_REG_BASE_+(0x0150<<2)))&BitMask_02)
#define WDR_DOLCMPw(val)		_wr32(_REG_BASE_+(0x0150<<2),(UINT)((_rd32(_REG_BASE_+(0x0150<<2))&(~ValSft_L22(BitMask_02)))|ValSft_L22((val)&BitMask_02)))

#define WDR_BUFPWLr				(ValSft_R20(_rd32(_REG_BASE_+(0x0150<<2)))&BitMask_02)
#define WDR_BUFPWLw(val)		_wr32(_REG_BASE_+(0x0150<<2),(UINT)((_rd32(_REG_BASE_+(0x0150<<2))&(~ValSft_L20(BitMask_02)))|ValSft_L20((val)&BitMask_02)))

#define WDR_LFONr				(ValSft_R16(_rd32(_REG_BASE_+(0x0150<<2)))&BitMask_01)
#define WDR_LFONw(val)			_wr32(_REG_BASE_+(0x0150<<2),(UINT)((_rd32(_REG_BASE_+(0x0150<<2))&(~ValSft_L16(BitMask_01)))|ValSft_L16((val)&BitMask_01)))

#define WDR_LFWr				(ValSft_R12(_rd32(_REG_BASE_+(0x0150<<2)))&BitMask_04)
#define WDR_LFWw(val)			_wr32(_REG_BASE_+(0x0150<<2),(UINT)((_rd32(_REG_BASE_+(0x0150<<2))&(~ValSft_L12(BitMask_04)))|ValSft_L12((val)&BitMask_04)))

#define WDR_LFMBr				(ValSft_R00(_rd32(_REG_BASE_+(0x0150<<2)))&BitMask_12)
#define WDR_LFMBw(val)			_wr32(_REG_BASE_+(0x0150<<2),(UINT)((_rd32(_REG_BASE_+(0x0150<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define WDR_ONr					(ValSft_R31(_rd32(_REG_BASE_+(0x0151<<2)))&BitMask_01)
#define WDR_ONw(val)			_wr32(_REG_BASE_+(0x0151<<2),(UINT)((_rd32(_REG_BASE_+(0x0151<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define WDR_SOVERr				(ValSft_R30(_rd32(_REG_BASE_+(0x0151<<2)))&BitMask_01)
#define WDR_SOVERw(val)			_wr32(_REG_BASE_+(0x0151<<2),(UINT)((_rd32(_REG_BASE_+(0x0151<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define WDR_OSDr				(ValSft_R28(_rd32(_REG_BASE_+(0x0151<<2)))&BitMask_02)
#define WDR_OSDw(val)			_wr32(_REG_BASE_+(0x0151<<2),(UINT)((_rd32(_REG_BASE_+(0x0151<<2))&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define WDR_CSELr				(ValSft_R26(_rd32(_REG_BASE_+(0x0151<<2)))&BitMask_02)
#define WDR_CSELw(val)			_wr32(_REG_BASE_+(0x0151<<2),(UINT)((_rd32(_REG_BASE_+(0x0151<<2))&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define WDR_SATVWr				(ValSft_R16(_rd32(_REG_BASE_+(0x0151<<2)))&BitMask_04)
#define WDR_SATVWw(val)			_wr32(_REG_BASE_+(0x0151<<2),(UINT)((_rd32(_REG_BASE_+(0x0151<<2))&(~ValSft_L16(BitMask_04)))|ValSft_L16((val)&BitMask_04)))

#define WDR_SATVLr				(ValSft_R00(_rd32(_REG_BASE_+(0x0151<<2)))&BitMask_16)
#define WDR_SATVLw(val)			_wr32(_REG_BASE_+(0x0151<<2),(UINT)((_rd32(_REG_BASE_+(0x0151<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define WDR_GAINr				(ValSft_R00(_rd32(_REG_BASE_+(0x0152<<2)))&BitMask_32)
#define WDR_GAINw(val)			_wr32(_REG_BASE_+(0x0152<<2),(UINT)((_rd32(_REG_BASE_+(0x0152<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define WDR_BLDSLr				(ValSft_R26(_rd32(_REG_BASE_+(0x0153<<2)))&BitMask_06)
#define WDR_BLDSLw(val)			_wr32(_REG_BASE_+(0x0153<<2),(UINT)((_rd32(_REG_BASE_+(0x0153<<2))&(~ValSft_L26(BitMask_06)))|ValSft_L26((val)&BitMask_06)))

#define WDR_BLDCLr				(ValSft_R20(_rd32(_REG_BASE_+(0x0153<<2)))&BitMask_06)
#define WDR_BLDCLw(val)			_wr32(_REG_BASE_+(0x0153<<2),(UINT)((_rd32(_REG_BASE_+(0x0153<<2))&(~ValSft_L20(BitMask_06)))|ValSft_L20((val)&BitMask_06)))

#define WDR_SGAINr				(ValSft_R00(_rd32(_REG_BASE_+(0x0153<<2)))&BitMask_18)
#define WDR_SGAINw(val)			_wr32(_REG_BASE_+(0x0153<<2),(UINT)((_rd32(_REG_BASE_+(0x0153<<2))&(~ValSft_L00(BitMask_18)))|ValSft_L00((val)&BitMask_18)))

#define WDR_LCLIPRr				(ValSft_R16(_rd32(_REG_BASE_+(0x0154<<2)))&BitMask_16)
#define WDR_LCLIPRw(val)		_wr32(_REG_BASE_+(0x0154<<2),(UINT)((_rd32(_REG_BASE_+(0x0154<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define WDR_LCLIPGr				(ValSft_R00(_rd32(_REG_BASE_+(0x0154<<2)))&BitMask_16)
#define WDR_LCLIPGw(val)		_wr32(_REG_BASE_+(0x0154<<2),(UINT)((_rd32(_REG_BASE_+(0x0154<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define WDR_LCLIPBr				(ValSft_R16(_rd32(_REG_BASE_+(0x0155<<2)))&BitMask_16)
#define WDR_LCLIPBw(val)		_wr32(_REG_BASE_+(0x0155<<2),(UINT)((_rd32(_REG_BASE_+(0x0155<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define WDR_SCLIPRr				(ValSft_R00(_rd32(_REG_BASE_+(0x0155<<2)))&BitMask_12)
#define WDR_SCLIPRw(val)		_wr32(_REG_BASE_+(0x0155<<2),(UINT)((_rd32(_REG_BASE_+(0x0155<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define WDR_SCLIPGr				(ValSft_R16(_rd32(_REG_BASE_+(0x0156<<2)))&BitMask_12)
#define WDR_SCLIPGw(val)		_wr32(_REG_BASE_+(0x0156<<2),(UINT)((_rd32(_REG_BASE_+(0x0156<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_SCLIPBr				(ValSft_R00(_rd32(_REG_BASE_+(0x0156<<2)))&BitMask_12)
#define WDR_SCLIPBw(val)		_wr32(_REG_BASE_+(0x0156<<2),(UINT)((_rd32(_REG_BASE_+(0x0156<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define WDR_WND_ONr				(ValSft_R28(_rd32(_REG_BASE_+(0x0157<<2)))&BitMask_04)
#define WDR_WND_ONw(val)		_wr32(_REG_BASE_+(0x0157<<2),(UINT)((_rd32(_REG_BASE_+(0x0157<<2))&(~ValSft_L28(BitMask_04)))|ValSft_L28((val)&BitMask_04)))

#define WDR_BACKGND_SELr		(ValSft_R26(_rd32(_REG_BASE_+(0x0157<<2)))&BitMask_02)
#define WDR_BACKGND_SELw(val)	_wr32(_REG_BASE_+(0x0157<<2),(UINT)((_rd32(_REG_BASE_+(0x0157<<2))&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define WDR_WND0_SELr			(ValSft_R24(_rd32(_REG_BASE_+(0x0157<<2)))&BitMask_02)
#define WDR_WND0_SELw(val)		_wr32(_REG_BASE_+(0x0157<<2),(UINT)((_rd32(_REG_BASE_+(0x0157<<2))&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define WDR_WND1_SELr			(ValSft_R22(_rd32(_REG_BASE_+(0x0157<<2)))&BitMask_02)
#define WDR_WND1_SELw(val)		_wr32(_REG_BASE_+(0x0157<<2),(UINT)((_rd32(_REG_BASE_+(0x0157<<2))&(~ValSft_L22(BitMask_02)))|ValSft_L22((val)&BitMask_02)))

#define WDR_WND2_SELr			(ValSft_R20(_rd32(_REG_BASE_+(0x0157<<2)))&BitMask_02)
#define WDR_WND2_SELw(val)		_wr32(_REG_BASE_+(0x0157<<2),(UINT)((_rd32(_REG_BASE_+(0x0157<<2))&(~ValSft_L20(BitMask_02)))|ValSft_L20((val)&BitMask_02)))

#define WDR_WND3_SELr			(ValSft_R18(_rd32(_REG_BASE_+(0x0157<<2)))&BitMask_02)
#define WDR_WND3_SELw(val)		_wr32(_REG_BASE_+(0x0157<<2),(UINT)((_rd32(_REG_BASE_+(0x0157<<2))&(~ValSft_L18(BitMask_02)))|ValSft_L18((val)&BitMask_02)))

#define WDR_WND_HOFFSr			(ValSft_R00(_rd32(_REG_BASE_+(0x0157<<2)))&BitMask_13)
#define WDR_WND_HOFFSw(val)		_wr32(_REG_BASE_+(0x0157<<2),(UINT)((_rd32(_REG_BASE_+(0x0157<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define WDR_WND_VOFFSr			(ValSft_R16(_rd32(_REG_BASE_+(0x0158<<2)))&BitMask_13)
#define WDR_WND_VOFFSw(val)		_wr32(_REG_BASE_+(0x0158<<2),(UINT)((_rd32(_REG_BASE_+(0x0158<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define WDR_WND0_VSP0r			(ValSft_R00(_rd32(_REG_BASE_+(0x0158<<2)))&BitMask_12)
#define WDR_WND0_VSP0w(val)		_wr32(_REG_BASE_+(0x0158<<2),(UINT)((_rd32(_REG_BASE_+(0x0158<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define WDR_WND0_HSP0r			(ValSft_R16(_rd32(_REG_BASE_+(0x0159<<2)))&BitMask_12)
#define WDR_WND0_HSP0w(val)		_wr32(_REG_BASE_+(0x0159<<2),(UINT)((_rd32(_REG_BASE_+(0x0159<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND0_HSD0r			(ValSft_R00(_rd32(_REG_BASE_+(0x0159<<2)))&BitMask_10)
#define WDR_WND0_HSD0w(val)		_wr32(_REG_BASE_+(0x0159<<2),(UINT)((_rd32(_REG_BASE_+(0x0159<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND0_HEP0r			(ValSft_R16(_rd32(_REG_BASE_+(0x015a<<2)))&BitMask_12)
#define WDR_WND0_HEP0w(val)		_wr32(_REG_BASE_+(0x015a<<2),(UINT)((_rd32(_REG_BASE_+(0x015a<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND0_HED0r			(ValSft_R00(_rd32(_REG_BASE_+(0x015a<<2)))&BitMask_10)
#define WDR_WND0_HED0w(val)		_wr32(_REG_BASE_+(0x015a<<2),(UINT)((_rd32(_REG_BASE_+(0x015a<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND0_VPS1r			(ValSft_R16(_rd32(_REG_BASE_+(0x015b<<2)))&BitMask_12)
#define WDR_WND0_VPS1w(val)		_wr32(_REG_BASE_+(0x015b<<2),(UINT)((_rd32(_REG_BASE_+(0x015b<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND0_HSD1r			(ValSft_R00(_rd32(_REG_BASE_+(0x015b<<2)))&BitMask_10)
#define WDR_WND0_HSD1w(val)		_wr32(_REG_BASE_+(0x015b<<2),(UINT)((_rd32(_REG_BASE_+(0x015b<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND0_VPE1r			(ValSft_R16(_rd32(_REG_BASE_+(0x015c<<2)))&BitMask_12)
#define WDR_WND0_VPE1w(val)		_wr32(_REG_BASE_+(0x015c<<2),(UINT)((_rd32(_REG_BASE_+(0x015c<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND0_HED1r			(ValSft_R00(_rd32(_REG_BASE_+(0x015c<<2)))&BitMask_10)
#define WDR_WND0_HED1w(val)		_wr32(_REG_BASE_+(0x015c<<2),(UINT)((_rd32(_REG_BASE_+(0x015c<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND0_VPS2r			(ValSft_R16(_rd32(_REG_BASE_+(0x015d<<2)))&BitMask_12)
#define WDR_WND0_VPS2w(val)		_wr32(_REG_BASE_+(0x015d<<2),(UINT)((_rd32(_REG_BASE_+(0x015d<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND0_HSD2r			(ValSft_R00(_rd32(_REG_BASE_+(0x015d<<2)))&BitMask_10)
#define WDR_WND0_HSD2w(val)		_wr32(_REG_BASE_+(0x015d<<2),(UINT)((_rd32(_REG_BASE_+(0x015d<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND0_VPE2r			(ValSft_R16(_rd32(_REG_BASE_+(0x015e<<2)))&BitMask_12)
#define WDR_WND0_VPE2w(val)		_wr32(_REG_BASE_+(0x015e<<2),(UINT)((_rd32(_REG_BASE_+(0x015e<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND0_HED2r			(ValSft_R00(_rd32(_REG_BASE_+(0x015e<<2)))&BitMask_10)
#define WDR_WND0_HED2w(val)		_wr32(_REG_BASE_+(0x015e<<2),(UINT)((_rd32(_REG_BASE_+(0x015e<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND0_VEPr			(ValSft_R00(_rd32(_REG_BASE_+(0x015f<<2)))&BitMask_12)
#define WDR_WND0_VEPw(val)		_wr32(_REG_BASE_+(0x015f<<2),(UINT)((_rd32(_REG_BASE_+(0x015f<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define WDR_WND1_VSP0r			(ValSft_R00(_rd32(_REG_BASE_+(0x0160<<2)))&BitMask_12)
#define WDR_WND1_VSP0w(val)		_wr32(_REG_BASE_+(0x0160<<2),(UINT)((_rd32(_REG_BASE_+(0x0160<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define WDR_WND1_HSP0r			(ValSft_R16(_rd32(_REG_BASE_+(0x0161<<2)))&BitMask_12)
#define WDR_WND1_HSP0w(val)		_wr32(_REG_BASE_+(0x0161<<2),(UINT)((_rd32(_REG_BASE_+(0x0161<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND1_HSD0r			(ValSft_R00(_rd32(_REG_BASE_+(0x0161<<2)))&BitMask_10)
#define WDR_WND1_HSD0w(val)		_wr32(_REG_BASE_+(0x0161<<2),(UINT)((_rd32(_REG_BASE_+(0x0161<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND1_HEP0r			(ValSft_R16(_rd32(_REG_BASE_+(0x0162<<2)))&BitMask_12)
#define WDR_WND1_HEP0w(val)		_wr32(_REG_BASE_+(0x0162<<2),(UINT)((_rd32(_REG_BASE_+(0x0162<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND1_HED0r			(ValSft_R00(_rd32(_REG_BASE_+(0x0162<<2)))&BitMask_10)
#define WDR_WND1_HED0w(val)		_wr32(_REG_BASE_+(0x0162<<2),(UINT)((_rd32(_REG_BASE_+(0x0162<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND1_VPS1r			(ValSft_R16(_rd32(_REG_BASE_+(0x0163<<2)))&BitMask_12)
#define WDR_WND1_VPS1w(val)		_wr32(_REG_BASE_+(0x0163<<2),(UINT)((_rd32(_REG_BASE_+(0x0163<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND1_HSD1r			(ValSft_R00(_rd32(_REG_BASE_+(0x0163<<2)))&BitMask_10)
#define WDR_WND1_HSD1w(val)		_wr32(_REG_BASE_+(0x0163<<2),(UINT)((_rd32(_REG_BASE_+(0x0163<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND1_VPE1r			(ValSft_R16(_rd32(_REG_BASE_+(0x0164<<2)))&BitMask_12)
#define WDR_WND1_VPE1w(val)		_wr32(_REG_BASE_+(0x0164<<2),(UINT)((_rd32(_REG_BASE_+(0x0164<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND1_HED1r			(ValSft_R00(_rd32(_REG_BASE_+(0x0164<<2)))&BitMask_10)
#define WDR_WND1_HED1w(val)		_wr32(_REG_BASE_+(0x0164<<2),(UINT)((_rd32(_REG_BASE_+(0x0164<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND1_VPS2r			(ValSft_R16(_rd32(_REG_BASE_+(0x0165<<2)))&BitMask_12)
#define WDR_WND1_VPS2w(val)		_wr32(_REG_BASE_+(0x0165<<2),(UINT)((_rd32(_REG_BASE_+(0x0165<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND1_HSD2r			(ValSft_R00(_rd32(_REG_BASE_+(0x0165<<2)))&BitMask_10)
#define WDR_WND1_HSD2w(val)		_wr32(_REG_BASE_+(0x0165<<2),(UINT)((_rd32(_REG_BASE_+(0x0165<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND1_VPE2r			(ValSft_R16(_rd32(_REG_BASE_+(0x0166<<2)))&BitMask_12)
#define WDR_WND1_VPE2w(val)		_wr32(_REG_BASE_+(0x0166<<2),(UINT)((_rd32(_REG_BASE_+(0x0166<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND1_HED2r			(ValSft_R00(_rd32(_REG_BASE_+(0x0166<<2)))&BitMask_10)
#define WDR_WND1_HED2w(val)		_wr32(_REG_BASE_+(0x0166<<2),(UINT)((_rd32(_REG_BASE_+(0x0166<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND1_VEPr			(ValSft_R00(_rd32(_REG_BASE_+(0x0167<<2)))&BitMask_12)
#define WDR_WND1_VEPw(val)		_wr32(_REG_BASE_+(0x0167<<2),(UINT)((_rd32(_REG_BASE_+(0x0167<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define WDR_WND2_VSP0r			(ValSft_R00(_rd32(_REG_BASE_+(0x0168<<2)))&BitMask_12)
#define WDR_WND2_VSP0w(val)		_wr32(_REG_BASE_+(0x0168<<2),(UINT)((_rd32(_REG_BASE_+(0x0168<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define WDR_WND2_HSP0r			(ValSft_R16(_rd32(_REG_BASE_+(0x0169<<2)))&BitMask_12)
#define WDR_WND2_HSP0w(val)		_wr32(_REG_BASE_+(0x0169<<2),(UINT)((_rd32(_REG_BASE_+(0x0169<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND2_HSD0r			(ValSft_R00(_rd32(_REG_BASE_+(0x0169<<2)))&BitMask_10)
#define WDR_WND2_HSD0w(val)		_wr32(_REG_BASE_+(0x0169<<2),(UINT)((_rd32(_REG_BASE_+(0x0169<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND2_HEP0r			(ValSft_R16(_rd32(_REG_BASE_+(0x016a<<2)))&BitMask_12)
#define WDR_WND2_HEP0w(val)		_wr32(_REG_BASE_+(0x016a<<2),(UINT)((_rd32(_REG_BASE_+(0x016a<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND2_HED0r			(ValSft_R00(_rd32(_REG_BASE_+(0x016a<<2)))&BitMask_10)
#define WDR_WND2_HED0w(val)		_wr32(_REG_BASE_+(0x016a<<2),(UINT)((_rd32(_REG_BASE_+(0x016a<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND2_VPS1r			(ValSft_R16(_rd32(_REG_BASE_+(0x016b<<2)))&BitMask_12)
#define WDR_WND2_VPS1w(val)		_wr32(_REG_BASE_+(0x016b<<2),(UINT)((_rd32(_REG_BASE_+(0x016b<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND2_HSD1r			(ValSft_R00(_rd32(_REG_BASE_+(0x016b<<2)))&BitMask_10)
#define WDR_WND2_HSD1w(val)		_wr32(_REG_BASE_+(0x016b<<2),(UINT)((_rd32(_REG_BASE_+(0x016b<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND2_VPE1r			(ValSft_R16(_rd32(_REG_BASE_+(0x016c<<2)))&BitMask_12)
#define WDR_WND2_VPE1w(val)		_wr32(_REG_BASE_+(0x016c<<2),(UINT)((_rd32(_REG_BASE_+(0x016c<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND2_HED1r			(ValSft_R00(_rd32(_REG_BASE_+(0x016c<<2)))&BitMask_10)
#define WDR_WND2_HED1w(val)		_wr32(_REG_BASE_+(0x016c<<2),(UINT)((_rd32(_REG_BASE_+(0x016c<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND2_VPS2r			(ValSft_R16(_rd32(_REG_BASE_+(0x016d<<2)))&BitMask_12)
#define WDR_WND2_VPS2w(val)		_wr32(_REG_BASE_+(0x016d<<2),(UINT)((_rd32(_REG_BASE_+(0x016d<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND2_HSD2r			(ValSft_R00(_rd32(_REG_BASE_+(0x016d<<2)))&BitMask_10)
#define WDR_WND2_HSD2w(val)		_wr32(_REG_BASE_+(0x016d<<2),(UINT)((_rd32(_REG_BASE_+(0x016d<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND2_VPE2r			(ValSft_R16(_rd32(_REG_BASE_+(0x016e<<2)))&BitMask_12)
#define WDR_WND2_VPE2w(val)		_wr32(_REG_BASE_+(0x016e<<2),(UINT)((_rd32(_REG_BASE_+(0x016e<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND2_HED2r			(ValSft_R00(_rd32(_REG_BASE_+(0x016e<<2)))&BitMask_10)
#define WDR_WND2_HED2w(val)		_wr32(_REG_BASE_+(0x016e<<2),(UINT)((_rd32(_REG_BASE_+(0x016e<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND2_VEPr			(ValSft_R00(_rd32(_REG_BASE_+(0x016f<<2)))&BitMask_12)
#define WDR_WND2_VEPw(val)		_wr32(_REG_BASE_+(0x016f<<2),(UINT)((_rd32(_REG_BASE_+(0x016f<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define WDR_WND3_VSP0r			(ValSft_R00(_rd32(_REG_BASE_+(0x0170<<2)))&BitMask_12)
#define WDR_WND3_VSP0w(val)		_wr32(_REG_BASE_+(0x0170<<2),(UINT)((_rd32(_REG_BASE_+(0x0170<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define WDR_WND3_HSP0r			(ValSft_R16(_rd32(_REG_BASE_+(0x0171<<2)))&BitMask_12)
#define WDR_WND3_HSP0w(val)		_wr32(_REG_BASE_+(0x0171<<2),(UINT)((_rd32(_REG_BASE_+(0x0171<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND3_HSD0r			(ValSft_R00(_rd32(_REG_BASE_+(0x0171<<2)))&BitMask_10)
#define WDR_WND3_HSD0w(val)		_wr32(_REG_BASE_+(0x0171<<2),(UINT)((_rd32(_REG_BASE_+(0x0171<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND3_HEP0r			(ValSft_R16(_rd32(_REG_BASE_+(0x0172<<2)))&BitMask_12)
#define WDR_WND3_HEP0w(val)		_wr32(_REG_BASE_+(0x0172<<2),(UINT)((_rd32(_REG_BASE_+(0x0172<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND3_HED0r			(ValSft_R00(_rd32(_REG_BASE_+(0x0172<<2)))&BitMask_10)
#define WDR_WND3_HED0w(val)		_wr32(_REG_BASE_+(0x0172<<2),(UINT)((_rd32(_REG_BASE_+(0x0172<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND3_VPS1r			(ValSft_R16(_rd32(_REG_BASE_+(0x0173<<2)))&BitMask_12)
#define WDR_WND3_VPS1w(val)		_wr32(_REG_BASE_+(0x0173<<2),(UINT)((_rd32(_REG_BASE_+(0x0173<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND3_HSD1r			(ValSft_R00(_rd32(_REG_BASE_+(0x0173<<2)))&BitMask_10)
#define WDR_WND3_HSD1w(val)		_wr32(_REG_BASE_+(0x0173<<2),(UINT)((_rd32(_REG_BASE_+(0x0173<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND3_VPE1r			(ValSft_R16(_rd32(_REG_BASE_+(0x0174<<2)))&BitMask_12)
#define WDR_WND3_VPE1w(val)		_wr32(_REG_BASE_+(0x0174<<2),(UINT)((_rd32(_REG_BASE_+(0x0174<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND3_HED1r			(ValSft_R00(_rd32(_REG_BASE_+(0x0174<<2)))&BitMask_10)
#define WDR_WND3_HED1w(val)		_wr32(_REG_BASE_+(0x0174<<2),(UINT)((_rd32(_REG_BASE_+(0x0174<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND3_VPS2r			(ValSft_R16(_rd32(_REG_BASE_+(0x0175<<2)))&BitMask_12)
#define WDR_WND3_VPS2w(val)		_wr32(_REG_BASE_+(0x0175<<2),(UINT)((_rd32(_REG_BASE_+(0x0175<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND3_HSD2r			(ValSft_R00(_rd32(_REG_BASE_+(0x0175<<2)))&BitMask_10)
#define WDR_WND3_HSD2w(val)		_wr32(_REG_BASE_+(0x0175<<2),(UINT)((_rd32(_REG_BASE_+(0x0175<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND3_VPE2r			(ValSft_R16(_rd32(_REG_BASE_+(0x0176<<2)))&BitMask_12)
#define WDR_WND3_VPE2w(val)		_wr32(_REG_BASE_+(0x0176<<2),(UINT)((_rd32(_REG_BASE_+(0x0176<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define WDR_WND3_HED2r			(ValSft_R00(_rd32(_REG_BASE_+(0x0176<<2)))&BitMask_10)
#define WDR_WND3_HED2w(val)		_wr32(_REG_BASE_+(0x0176<<2),(UINT)((_rd32(_REG_BASE_+(0x0176<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define WDR_WND3_VEPr			(ValSft_R00(_rd32(_REG_BASE_+(0x0177<<2)))&BitMask_12)
#define WDR_WND3_VEPw(val)		_wr32(_REG_BASE_+(0x0177<<2),(UINT)((_rd32(_REG_BASE_+(0x0177<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define TMG_ONr					(ValSft_R31(_rd32(_REG_BASE_+(0x0178<<2)))&BitMask_01)
#define TMG_ONw(val)			_wr32(_REG_BASE_+(0x0178<<2),(UINT)((_rd32(_REG_BASE_+(0x0178<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define TMG_BAYMODEr			(ValSft_R30(_rd32(_REG_BASE_+(0x0178<<2)))&BitMask_01)
#define TMG_BAYMODEw(val)		_wr32(_REG_BASE_+(0x0178<<2),(UINT)((_rd32(_REG_BASE_+(0x0178<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define TMG_YHLPFr				(ValSft_R28(_rd32(_REG_BASE_+(0x0178<<2)))&BitMask_01)
#define TMG_YHLPFw(val)			_wr32(_REG_BASE_+(0x0178<<2),(UINT)((_rd32(_REG_BASE_+(0x0178<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define TMG_YHLPF_GAr			(ValSft_R24(_rd32(_REG_BASE_+(0x0178<<2)))&BitMask_04)
#define TMG_YHLPF_GAw(val)		_wr32(_REG_BASE_+(0x0178<<2),(UINT)((_rd32(_REG_BASE_+(0x0178<<2))&(~ValSft_L24(BitMask_04)))|ValSft_L24((val)&BitMask_04)))

#define TMG_YHLPF_CLr			(ValSft_R00(_rd32(_REG_BASE_+(0x0178<<2)))&BitMask_24)
#define TMG_YHLPF_CLw(val)		_wr32(_REG_BASE_+(0x0178<<2),(UINT)((_rd32(_REG_BASE_+(0x0178<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define TMG_YHLPF_SCr			(ValSft_R00(_rd32(_REG_BASE_+(0x0179<<2)))&BitMask_10)
#define TMG_YHLPF_SCw(val)		_wr32(_REG_BASE_+(0x0179<<2),(UINT)((_rd32(_REG_BASE_+(0x0179<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define DNR2D_ONr				(ValSft_R31(_rd32(_REG_BASE_+(0x0191<<2)))&BitMask_01)
#define DNR2D_ONw(val)			_wr32(_REG_BASE_+(0x0191<<2),(UINT)((_rd32(_REG_BASE_+(0x0191<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DNR_CSELr				(ValSft_R28(_rd32(_REG_BASE_+(0x0191<<2)))&BitMask_02)
#define DNR_CSELw(val)			_wr32(_REG_BASE_+(0x0191<<2),(UINT)((_rd32(_REG_BASE_+(0x0191<<2))&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define DNR_RCSELr				(ValSft_R26(_rd32(_REG_BASE_+(0x0191<<2)))&BitMask_02)
#define DNR_RCSELw(val)			_wr32(_REG_BASE_+(0x0191<<2),(UINT)((_rd32(_REG_BASE_+(0x0191<<2))&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define RB_QSELr				(ValSft_R24(_rd32(_REG_BASE_+(0x0191<<2)))&BitMask_02)
#define RB_QSELw(val)			_wr32(_REG_BASE_+(0x0191<<2),(UINT)((_rd32(_REG_BASE_+(0x0191<<2))&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define DNR_OSELr				(ValSft_R22(_rd32(_REG_BASE_+(0x0191<<2)))&BitMask_02)
#define DNR_OSELw(val)			_wr32(_REG_BASE_+(0x0191<<2),(UINT)((_rd32(_REG_BASE_+(0x0191<<2))&(~ValSft_L22(BitMask_02)))|ValSft_L22((val)&BitMask_02)))

#define DNR_ODMCSELr			(ValSft_R20(_rd32(_REG_BASE_+(0x0191<<2)))&BitMask_02)
#define DNR_ODMCSELw(val)		_wr32(_REG_BASE_+(0x0191<<2),(UINT)((_rd32(_REG_BASE_+(0x0191<<2))&(~ValSft_L20(BitMask_02)))|ValSft_L20((val)&BitMask_02)))

#define DNR2D_DC_GAINr			(ValSft_R17(_rd32(_REG_BASE_+(0x0191<<2)))&BitMask_03)
#define DNR2D_DC_GAINw(val)		_wr32(_REG_BASE_+(0x0191<<2),(UINT)((_rd32(_REG_BASE_+(0x0191<<2))&(~ValSft_L17(BitMask_03)))|ValSft_L17((val)&BitMask_03)))

#define DNR2D_LVL0_GAINr		(ValSft_R14(_rd32(_REG_BASE_+(0x0191<<2)))&BitMask_03)
#define DNR2D_LVL0_GAINw(val)	_wr32(_REG_BASE_+(0x0191<<2),(UINT)((_rd32(_REG_BASE_+(0x0191<<2))&(~ValSft_L14(BitMask_03)))|ValSft_L14((val)&BitMask_03)))

#define DNR2D_LVL1_GAINr		(ValSft_R11(_rd32(_REG_BASE_+(0x0191<<2)))&BitMask_03)
#define DNR2D_LVL1_GAINw(val)	_wr32(_REG_BASE_+(0x0191<<2),(UINT)((_rd32(_REG_BASE_+(0x0191<<2))&(~ValSft_L11(BitMask_03)))|ValSft_L11((val)&BitMask_03)))

#define DNR2D_LVL2_GAINr		(ValSft_R08(_rd32(_REG_BASE_+(0x0191<<2)))&BitMask_03)
#define DNR2D_LVL2_GAINw(val)	_wr32(_REG_BASE_+(0x0191<<2),(UINT)((_rd32(_REG_BASE_+(0x0191<<2))&(~ValSft_L08(BitMask_03)))|ValSft_L08((val)&BitMask_03)))

#define DNR_RGB_DIR_THRr		(ValSft_R00(_rd32(_REG_BASE_+(0x0191<<2)))&BitMask_08)
#define DNR_RGB_DIR_THRw(val)	_wr32(_REG_BASE_+(0x0191<<2),(UINT)((_rd32(_REG_BASE_+(0x0191<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define RB_Q00r					(ValSft_R16(_rd32(_REG_BASE_+(0x01b2<<2)))&BitMask_13)
#define RB_Q00w(val)			_wr32(_REG_BASE_+(0x01b2<<2),(UINT)((_rd32(_REG_BASE_+(0x01b2<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define RB_Q01r					(ValSft_R00(_rd32(_REG_BASE_+(0x01b2<<2)))&BitMask_13)
#define RB_Q01w(val)			_wr32(_REG_BASE_+(0x01b2<<2),(UINT)((_rd32(_REG_BASE_+(0x01b2<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define RB_Q02r					(ValSft_R16(_rd32(_REG_BASE_+(0x01b3<<2)))&BitMask_13)
#define RB_Q02w(val)			_wr32(_REG_BASE_+(0x01b3<<2),(UINT)((_rd32(_REG_BASE_+(0x01b3<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define RB_Q03r					(ValSft_R00(_rd32(_REG_BASE_+(0x01b3<<2)))&BitMask_13)
#define RB_Q03w(val)			_wr32(_REG_BASE_+(0x01b3<<2),(UINT)((_rd32(_REG_BASE_+(0x01b3<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define RB_Q10r					(ValSft_R16(_rd32(_REG_BASE_+(0x01b4<<2)))&BitMask_13)
#define RB_Q10w(val)			_wr32(_REG_BASE_+(0x01b4<<2),(UINT)((_rd32(_REG_BASE_+(0x01b4<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define RB_Q11r					(ValSft_R00(_rd32(_REG_BASE_+(0x01b4<<2)))&BitMask_13)
#define RB_Q11w(val)			_wr32(_REG_BASE_+(0x01b4<<2),(UINT)((_rd32(_REG_BASE_+(0x01b4<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define RB_Q12r					(ValSft_R16(_rd32(_REG_BASE_+(0x01b5<<2)))&BitMask_13)
#define RB_Q12w(val)			_wr32(_REG_BASE_+(0x01b5<<2),(UINT)((_rd32(_REG_BASE_+(0x01b5<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define RB_Q13r					(ValSft_R00(_rd32(_REG_BASE_+(0x01b5<<2)))&BitMask_13)
#define RB_Q13w(val)			_wr32(_REG_BASE_+(0x01b5<<2),(UINT)((_rd32(_REG_BASE_+(0x01b5<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define RB_Q20r					(ValSft_R16(_rd32(_REG_BASE_+(0x01b6<<2)))&BitMask_13)
#define RB_Q20w(val)			_wr32(_REG_BASE_+(0x01b6<<2),(UINT)((_rd32(_REG_BASE_+(0x01b6<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define RB_Q21r					(ValSft_R00(_rd32(_REG_BASE_+(0x01b6<<2)))&BitMask_13)
#define RB_Q21w(val)			_wr32(_REG_BASE_+(0x01b6<<2),(UINT)((_rd32(_REG_BASE_+(0x01b6<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define RB_Q22r					(ValSft_R16(_rd32(_REG_BASE_+(0x01b7<<2)))&BitMask_13)
#define RB_Q22w(val)			_wr32(_REG_BASE_+(0x01b7<<2),(UINT)((_rd32(_REG_BASE_+(0x01b7<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define RB_Q23r					(ValSft_R00(_rd32(_REG_BASE_+(0x01b7<<2)))&BitMask_13)
#define RB_Q23w(val)			_wr32(_REG_BASE_+(0x01b7<<2),(UINT)((_rd32(_REG_BASE_+(0x01b7<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define RB_Q30r					(ValSft_R16(_rd32(_REG_BASE_+(0x01b8<<2)))&BitMask_13)
#define RB_Q30w(val)			_wr32(_REG_BASE_+(0x01b8<<2),(UINT)((_rd32(_REG_BASE_+(0x01b8<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define RB_Q31r					(ValSft_R00(_rd32(_REG_BASE_+(0x01b8<<2)))&BitMask_13)
#define RB_Q31w(val)			_wr32(_REG_BASE_+(0x01b8<<2),(UINT)((_rd32(_REG_BASE_+(0x01b8<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define RB_Q32r					(ValSft_R16(_rd32(_REG_BASE_+(0x01b9<<2)))&BitMask_13)
#define RB_Q32w(val)			_wr32(_REG_BASE_+(0x01b9<<2),(UINT)((_rd32(_REG_BASE_+(0x01b9<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define RB_Q33r					(ValSft_R00(_rd32(_REG_BASE_+(0x01b9<<2)))&BitMask_13)
#define RB_Q33w(val)			_wr32(_REG_BASE_+(0x01b9<<2),(UINT)((_rd32(_REG_BASE_+(0x01b9<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define NEGA_ONr				(ValSft_R28(_rd32(_REG_BASE_+(0x01be<<2)))&BitMask_01)
#define NEGA_ONw(val)			_wr32(_REG_BASE_+(0x01be<<2),(UINT)((_rd32(_REG_BASE_+(0x01be<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define BW_ONr					(ValSft_R27(_rd32(_REG_BASE_+(0x01be<<2)))&BitMask_01)
#define BW_ONw(val)				_wr32(_REG_BASE_+(0x01be<<2),(UINT)((_rd32(_REG_BASE_+(0x01be<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define AF_YSELr				(ValSft_R00(_rd32(_REG_BASE_+(0x01bf<<2)))&BitMask_02)
#define AF_YSELw(val)			_wr32(_REG_BASE_+(0x01bf<<2),(UINT)((_rd32(_REG_BASE_+(0x01bf<<2))&(~ValSft_L00(BitMask_02)))|ValSft_L00((val)&BitMask_02)))

#define APT_ONr					(ValSft_R31(_rd32(_REG_BASE_+(0x01c0<<2)))&BitMask_01)
#define APT_ONw(val)			_wr32(_REG_BASE_+(0x01c0<<2),(UINT)((_rd32(_REG_BASE_+(0x01c0<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define APT_GAIN_ONr			(ValSft_R30(_rd32(_REG_BASE_+(0x01c0<<2)))&BitMask_01)
#define APT_GAIN_ONw(val)		_wr32(_REG_BASE_+(0x01c0<<2),(UINT)((_rd32(_REG_BASE_+(0x01c0<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define APT_TESTr				(ValSft_R28(_rd32(_REG_BASE_+(0x01c0<<2)))&BitMask_02)
#define APT_TESTw(val)			_wr32(_REG_BASE_+(0x01c0<<2),(UINT)((_rd32(_REG_BASE_+(0x01c0<<2))&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define APT_TH1r				(ValSft_R00(_rd32(_REG_BASE_+(0x01c0<<2)))&BitMask_16)
#define APT_TH1w(val)			_wr32(_REG_BASE_+(0x01c0<<2),(UINT)((_rd32(_REG_BASE_+(0x01c0<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define APT_TH2r				(ValSft_R16(_rd32(_REG_BASE_+(0x01c1<<2)))&BitMask_16)
#define APT_TH2w(val)			_wr32(_REG_BASE_+(0x01c1<<2),(UINT)((_rd32(_REG_BASE_+(0x01c1<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define APT_TH3r				(ValSft_R00(_rd32(_REG_BASE_+(0x01c1<<2)))&BitMask_10)
#define APT_TH3w(val)			_wr32(_REG_BASE_+(0x01c1<<2),(UINT)((_rd32(_REG_BASE_+(0x01c1<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define APT_GAIN2_NEGr			(ValSft_R24(_rd32(_REG_BASE_+(0x01c2<<2)))&BitMask_08)
#define APT_GAIN2_NEGw(val)		_wr32(_REG_BASE_+(0x01c2<<2),(UINT)((_rd32(_REG_BASE_+(0x01c2<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define APT_GAIN1_NEGr			(ValSft_R16(_rd32(_REG_BASE_+(0x01c2<<2)))&BitMask_08)
#define APT_GAIN1_NEGw(val)		_wr32(_REG_BASE_+(0x01c2<<2),(UINT)((_rd32(_REG_BASE_+(0x01c2<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define APT_GAIN2_POSr			(ValSft_R08(_rd32(_REG_BASE_+(0x01c2<<2)))&BitMask_08)
#define APT_GAIN2_POSw(val)		_wr32(_REG_BASE_+(0x01c2<<2),(UINT)((_rd32(_REG_BASE_+(0x01c2<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define APT_GAIN1_POSr			(ValSft_R00(_rd32(_REG_BASE_+(0x01c2<<2)))&BitMask_08)
#define APT_GAIN1_POSw(val)		_wr32(_REG_BASE_+(0x01c2<<2),(UINT)((_rd32(_REG_BASE_+(0x01c2<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define APT_SLIC3r				(ValSft_R16(_rd32(_REG_BASE_+(0x01c3<<2)))&BitMask_14)
#define APT_SLIC3w(val)			_wr32(_REG_BASE_+(0x01c3<<2),(UINT)((_rd32(_REG_BASE_+(0x01c3<<2))&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define APT_CLIP3r				(ValSft_R00(_rd32(_REG_BASE_+(0x01c3<<2)))&BitMask_10)
#define APT_CLIP3w(val)			_wr32(_REG_BASE_+(0x01c3<<2),(UINT)((_rd32(_REG_BASE_+(0x01c3<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define APT_GAIN3r				(ValSft_R00(_rd32(_REG_BASE_+(0x01c4<<2)))&BitMask_08)
#define APT_GAIN3w(val)			_wr32(_REG_BASE_+(0x01c4<<2),(UINT)((_rd32(_REG_BASE_+(0x01c4<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define APT_LPFKr				(ValSft_R24(_rd32(_REG_BASE_+(0x01c5<<2)))&BitMask_08)
#define APT_LPFKw(val)			_wr32(_REG_BASE_+(0x01c5<<2),(UINT)((_rd32(_REG_BASE_+(0x01c5<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define APT_LPFGAr				(ValSft_R16(_rd32(_REG_BASE_+(0x01c5<<2)))&BitMask_08)
#define APT_LPFGAw(val)			_wr32(_REG_BASE_+(0x01c5<<2),(UINT)((_rd32(_REG_BASE_+(0x01c5<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define APT_LPFTHr				(ValSft_R00(_rd32(_REG_BASE_+(0x01c5<<2)))&BitMask_10)
#define APT_LPFTHw(val)			_wr32(_REG_BASE_+(0x01c5<<2),(UINT)((_rd32(_REG_BASE_+(0x01c5<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMA_ONr				(ValSft_R31(_rd32(_REG_BASE_+(0x01ca<<2)))&BitMask_01)
#define YGMA_ONw(val)			_wr32(_REG_BASE_+(0x01ca<<2),(UINT)((_rd32(_REG_BASE_+(0x01ca<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define CGMA_ONr				(ValSft_R30(_rd32(_REG_BASE_+(0x01ca<<2)))&BitMask_01)
#define CGMA_ONw(val)			_wr32(_REG_BASE_+(0x01ca<<2),(UINT)((_rd32(_REG_BASE_+(0x01ca<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define YGMKr					(ValSft_R08(_rd32(_REG_BASE_+(0x01ca<<2)))&BitMask_08)
#define YGMKw(val)				_wr32(_REG_BASE_+(0x01ca<<2),(UINT)((_rd32(_REG_BASE_+(0x01ca<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define CGMKr					(ValSft_R00(_rd32(_REG_BASE_+(0x01ca<<2)))&BitMask_08)
#define CGMKw(val)				_wr32(_REG_BASE_+(0x01ca<<2),(UINT)((_rd32(_REG_BASE_+(0x01ca<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define YGMY1_00r				(ValSft_R16(_rd32(_REG_BASE_+(0x01cb<<2)))&BitMask_10)
#define YGMY1_00w(val)			_wr32(_REG_BASE_+(0x01cb<<2),(UINT)((_rd32(_REG_BASE_+(0x01cb<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY1_01r				(ValSft_R00(_rd32(_REG_BASE_+(0x01cb<<2)))&BitMask_10)
#define YGMY1_01w(val)			_wr32(_REG_BASE_+(0x01cb<<2),(UINT)((_rd32(_REG_BASE_+(0x01cb<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY1_02r				(ValSft_R16(_rd32(_REG_BASE_+(0x01cc<<2)))&BitMask_10)
#define YGMY1_02w(val)			_wr32(_REG_BASE_+(0x01cc<<2),(UINT)((_rd32(_REG_BASE_+(0x01cc<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY1_03r				(ValSft_R00(_rd32(_REG_BASE_+(0x01cc<<2)))&BitMask_10)
#define YGMY1_03w(val)			_wr32(_REG_BASE_+(0x01cc<<2),(UINT)((_rd32(_REG_BASE_+(0x01cc<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY1_04r				(ValSft_R16(_rd32(_REG_BASE_+(0x01cd<<2)))&BitMask_10)
#define YGMY1_04w(val)			_wr32(_REG_BASE_+(0x01cd<<2),(UINT)((_rd32(_REG_BASE_+(0x01cd<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY1_05r				(ValSft_R00(_rd32(_REG_BASE_+(0x01cd<<2)))&BitMask_10)
#define YGMY1_05w(val)			_wr32(_REG_BASE_+(0x01cd<<2),(UINT)((_rd32(_REG_BASE_+(0x01cd<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY1_06r				(ValSft_R16(_rd32(_REG_BASE_+(0x01ce<<2)))&BitMask_10)
#define YGMY1_06w(val)			_wr32(_REG_BASE_+(0x01ce<<2),(UINT)((_rd32(_REG_BASE_+(0x01ce<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY1_07r				(ValSft_R00(_rd32(_REG_BASE_+(0x01ce<<2)))&BitMask_10)
#define YGMY1_07w(val)			_wr32(_REG_BASE_+(0x01ce<<2),(UINT)((_rd32(_REG_BASE_+(0x01ce<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY1_08r				(ValSft_R16(_rd32(_REG_BASE_+(0x01cf<<2)))&BitMask_10)
#define YGMY1_08w(val)			_wr32(_REG_BASE_+(0x01cf<<2),(UINT)((_rd32(_REG_BASE_+(0x01cf<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY1_09r				(ValSft_R00(_rd32(_REG_BASE_+(0x01cf<<2)))&BitMask_10)
#define YGMY1_09w(val)			_wr32(_REG_BASE_+(0x01cf<<2),(UINT)((_rd32(_REG_BASE_+(0x01cf<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY1_10r				(ValSft_R16(_rd32(_REG_BASE_+(0x01d0<<2)))&BitMask_10)
#define YGMY1_10w(val)			_wr32(_REG_BASE_+(0x01d0<<2),(UINT)((_rd32(_REG_BASE_+(0x01d0<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY1_11r				(ValSft_R00(_rd32(_REG_BASE_+(0x01d0<<2)))&BitMask_10)
#define YGMY1_11w(val)			_wr32(_REG_BASE_+(0x01d0<<2),(UINT)((_rd32(_REG_BASE_+(0x01d0<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY1_12r				(ValSft_R16(_rd32(_REG_BASE_+(0x01d1<<2)))&BitMask_10)
#define YGMY1_12w(val)			_wr32(_REG_BASE_+(0x01d1<<2),(UINT)((_rd32(_REG_BASE_+(0x01d1<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY1_13r				(ValSft_R00(_rd32(_REG_BASE_+(0x01d1<<2)))&BitMask_10)
#define YGMY1_13w(val)			_wr32(_REG_BASE_+(0x01d1<<2),(UINT)((_rd32(_REG_BASE_+(0x01d1<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY1_14r				(ValSft_R16(_rd32(_REG_BASE_+(0x01d2<<2)))&BitMask_10)
#define YGMY1_14w(val)			_wr32(_REG_BASE_+(0x01d2<<2),(UINT)((_rd32(_REG_BASE_+(0x01d2<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY1_15r				(ValSft_R00(_rd32(_REG_BASE_+(0x01d2<<2)))&BitMask_10)
#define YGMY1_15w(val)			_wr32(_REG_BASE_+(0x01d2<<2),(UINT)((_rd32(_REG_BASE_+(0x01d2<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY1_16r				(ValSft_R16(_rd32(_REG_BASE_+(0x01d3<<2)))&BitMask_10)
#define YGMY1_16w(val)			_wr32(_REG_BASE_+(0x01d3<<2),(UINT)((_rd32(_REG_BASE_+(0x01d3<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY2_00r				(ValSft_R16(_rd32(_REG_BASE_+(0x01d4<<2)))&BitMask_10)
#define YGMY2_00w(val)			_wr32(_REG_BASE_+(0x01d4<<2),(UINT)((_rd32(_REG_BASE_+(0x01d4<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY2_01r				(ValSft_R00(_rd32(_REG_BASE_+(0x01d4<<2)))&BitMask_10)
#define YGMY2_01w(val)			_wr32(_REG_BASE_+(0x01d4<<2),(UINT)((_rd32(_REG_BASE_+(0x01d4<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY2_02r				(ValSft_R16(_rd32(_REG_BASE_+(0x01d5<<2)))&BitMask_10)
#define YGMY2_02w(val)			_wr32(_REG_BASE_+(0x01d5<<2),(UINT)((_rd32(_REG_BASE_+(0x01d5<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY2_03r				(ValSft_R00(_rd32(_REG_BASE_+(0x01d5<<2)))&BitMask_10)
#define YGMY2_03w(val)			_wr32(_REG_BASE_+(0x01d5<<2),(UINT)((_rd32(_REG_BASE_+(0x01d5<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY2_04r				(ValSft_R16(_rd32(_REG_BASE_+(0x01d6<<2)))&BitMask_10)
#define YGMY2_04w(val)			_wr32(_REG_BASE_+(0x01d6<<2),(UINT)((_rd32(_REG_BASE_+(0x01d6<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY2_05r				(ValSft_R00(_rd32(_REG_BASE_+(0x01d6<<2)))&BitMask_10)
#define YGMY2_05w(val)			_wr32(_REG_BASE_+(0x01d6<<2),(UINT)((_rd32(_REG_BASE_+(0x01d6<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY2_06r				(ValSft_R16(_rd32(_REG_BASE_+(0x01d7<<2)))&BitMask_10)
#define YGMY2_06w(val)			_wr32(_REG_BASE_+(0x01d7<<2),(UINT)((_rd32(_REG_BASE_+(0x01d7<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY2_07r				(ValSft_R00(_rd32(_REG_BASE_+(0x01d7<<2)))&BitMask_10)
#define YGMY2_07w(val)			_wr32(_REG_BASE_+(0x01d7<<2),(UINT)((_rd32(_REG_BASE_+(0x01d7<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY2_08r				(ValSft_R16(_rd32(_REG_BASE_+(0x01d8<<2)))&BitMask_10)
#define YGMY2_08w(val)			_wr32(_REG_BASE_+(0x01d8<<2),(UINT)((_rd32(_REG_BASE_+(0x01d8<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY2_09r				(ValSft_R00(_rd32(_REG_BASE_+(0x01d8<<2)))&BitMask_10)
#define YGMY2_09w(val)			_wr32(_REG_BASE_+(0x01d8<<2),(UINT)((_rd32(_REG_BASE_+(0x01d8<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY2_10r				(ValSft_R16(_rd32(_REG_BASE_+(0x01d9<<2)))&BitMask_10)
#define YGMY2_10w(val)			_wr32(_REG_BASE_+(0x01d9<<2),(UINT)((_rd32(_REG_BASE_+(0x01d9<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY2_11r				(ValSft_R00(_rd32(_REG_BASE_+(0x01d9<<2)))&BitMask_10)
#define YGMY2_11w(val)			_wr32(_REG_BASE_+(0x01d9<<2),(UINT)((_rd32(_REG_BASE_+(0x01d9<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY2_12r				(ValSft_R16(_rd32(_REG_BASE_+(0x01da<<2)))&BitMask_10)
#define YGMY2_12w(val)			_wr32(_REG_BASE_+(0x01da<<2),(UINT)((_rd32(_REG_BASE_+(0x01da<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY2_13r				(ValSft_R00(_rd32(_REG_BASE_+(0x01da<<2)))&BitMask_10)
#define YGMY2_13w(val)			_wr32(_REG_BASE_+(0x01da<<2),(UINT)((_rd32(_REG_BASE_+(0x01da<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY2_14r				(ValSft_R16(_rd32(_REG_BASE_+(0x01db<<2)))&BitMask_10)
#define YGMY2_14w(val)			_wr32(_REG_BASE_+(0x01db<<2),(UINT)((_rd32(_REG_BASE_+(0x01db<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define YGMY2_15r				(ValSft_R00(_rd32(_REG_BASE_+(0x01db<<2)))&BitMask_10)
#define YGMY2_15w(val)			_wr32(_REG_BASE_+(0x01db<<2),(UINT)((_rd32(_REG_BASE_+(0x01db<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define YGMY2_16r				(ValSft_R16(_rd32(_REG_BASE_+(0x01dc<<2)))&BitMask_10)
#define YGMY2_16w(val)			_wr32(_REG_BASE_+(0x01dc<<2),(UINT)((_rd32(_REG_BASE_+(0x01dc<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY1_00r				(ValSft_R16(_rd32(_REG_BASE_+(0x01dd<<2)))&BitMask_10)
#define CGMY1_00w(val)			_wr32(_REG_BASE_+(0x01dd<<2),(UINT)((_rd32(_REG_BASE_+(0x01dd<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY1_01r				(ValSft_R00(_rd32(_REG_BASE_+(0x01dd<<2)))&BitMask_10)
#define CGMY1_01w(val)			_wr32(_REG_BASE_+(0x01dd<<2),(UINT)((_rd32(_REG_BASE_+(0x01dd<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY1_02r				(ValSft_R16(_rd32(_REG_BASE_+(0x01de<<2)))&BitMask_10)
#define CGMY1_02w(val)			_wr32(_REG_BASE_+(0x01de<<2),(UINT)((_rd32(_REG_BASE_+(0x01de<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY1_03r				(ValSft_R00(_rd32(_REG_BASE_+(0x01de<<2)))&BitMask_10)
#define CGMY1_03w(val)			_wr32(_REG_BASE_+(0x01de<<2),(UINT)((_rd32(_REG_BASE_+(0x01de<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY1_04r				(ValSft_R16(_rd32(_REG_BASE_+(0x01df<<2)))&BitMask_10)
#define CGMY1_04w(val)			_wr32(_REG_BASE_+(0x01df<<2),(UINT)((_rd32(_REG_BASE_+(0x01df<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY1_05r				(ValSft_R00(_rd32(_REG_BASE_+(0x01df<<2)))&BitMask_10)
#define CGMY1_05w(val)			_wr32(_REG_BASE_+(0x01df<<2),(UINT)((_rd32(_REG_BASE_+(0x01df<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY1_06r				(ValSft_R16(_rd32(_REG_BASE_+(0x01e0<<2)))&BitMask_10)
#define CGMY1_06w(val)			_wr32(_REG_BASE_+(0x01e0<<2),(UINT)((_rd32(_REG_BASE_+(0x01e0<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY1_07r				(ValSft_R00(_rd32(_REG_BASE_+(0x01e0<<2)))&BitMask_10)
#define CGMY1_07w(val)			_wr32(_REG_BASE_+(0x01e0<<2),(UINT)((_rd32(_REG_BASE_+(0x01e0<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY1_08r				(ValSft_R16(_rd32(_REG_BASE_+(0x01e1<<2)))&BitMask_10)
#define CGMY1_08w(val)			_wr32(_REG_BASE_+(0x01e1<<2),(UINT)((_rd32(_REG_BASE_+(0x01e1<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY1_09r				(ValSft_R00(_rd32(_REG_BASE_+(0x01e1<<2)))&BitMask_10)
#define CGMY1_09w(val)			_wr32(_REG_BASE_+(0x01e1<<2),(UINT)((_rd32(_REG_BASE_+(0x01e1<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY1_10r				(ValSft_R16(_rd32(_REG_BASE_+(0x01e2<<2)))&BitMask_10)
#define CGMY1_10w(val)			_wr32(_REG_BASE_+(0x01e2<<2),(UINT)((_rd32(_REG_BASE_+(0x01e2<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY1_11r				(ValSft_R00(_rd32(_REG_BASE_+(0x01e2<<2)))&BitMask_10)
#define CGMY1_11w(val)			_wr32(_REG_BASE_+(0x01e2<<2),(UINT)((_rd32(_REG_BASE_+(0x01e2<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY1_12r				(ValSft_R16(_rd32(_REG_BASE_+(0x01e3<<2)))&BitMask_10)
#define CGMY1_12w(val)			_wr32(_REG_BASE_+(0x01e3<<2),(UINT)((_rd32(_REG_BASE_+(0x01e3<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY1_13r				(ValSft_R00(_rd32(_REG_BASE_+(0x01e3<<2)))&BitMask_10)
#define CGMY1_13w(val)			_wr32(_REG_BASE_+(0x01e3<<2),(UINT)((_rd32(_REG_BASE_+(0x01e3<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY1_14r				(ValSft_R16(_rd32(_REG_BASE_+(0x01e4<<2)))&BitMask_10)
#define CGMY1_14w(val)			_wr32(_REG_BASE_+(0x01e4<<2),(UINT)((_rd32(_REG_BASE_+(0x01e4<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY1_15r				(ValSft_R00(_rd32(_REG_BASE_+(0x01e4<<2)))&BitMask_10)
#define CGMY1_15w(val)			_wr32(_REG_BASE_+(0x01e4<<2),(UINT)((_rd32(_REG_BASE_+(0x01e4<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY1_16r				(ValSft_R16(_rd32(_REG_BASE_+(0x01e5<<2)))&BitMask_10)
#define CGMY1_16w(val)			_wr32(_REG_BASE_+(0x01e5<<2),(UINT)((_rd32(_REG_BASE_+(0x01e5<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY2_00r				(ValSft_R16(_rd32(_REG_BASE_+(0x01e6<<2)))&BitMask_10)
#define CGMY2_00w(val)			_wr32(_REG_BASE_+(0x01e6<<2),(UINT)((_rd32(_REG_BASE_+(0x01e6<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY2_01r				(ValSft_R00(_rd32(_REG_BASE_+(0x01e6<<2)))&BitMask_10)
#define CGMY2_01w(val)			_wr32(_REG_BASE_+(0x01e6<<2),(UINT)((_rd32(_REG_BASE_+(0x01e6<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY2_02r				(ValSft_R16(_rd32(_REG_BASE_+(0x01e7<<2)))&BitMask_10)
#define CGMY2_02w(val)			_wr32(_REG_BASE_+(0x01e7<<2),(UINT)((_rd32(_REG_BASE_+(0x01e7<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY2_03r				(ValSft_R00(_rd32(_REG_BASE_+(0x01e7<<2)))&BitMask_10)
#define CGMY2_03w(val)			_wr32(_REG_BASE_+(0x01e7<<2),(UINT)((_rd32(_REG_BASE_+(0x01e7<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY2_04r				(ValSft_R16(_rd32(_REG_BASE_+(0x01e8<<2)))&BitMask_10)
#define CGMY2_04w(val)			_wr32(_REG_BASE_+(0x01e8<<2),(UINT)((_rd32(_REG_BASE_+(0x01e8<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY2_05r				(ValSft_R00(_rd32(_REG_BASE_+(0x01e8<<2)))&BitMask_10)
#define CGMY2_05w(val)			_wr32(_REG_BASE_+(0x01e8<<2),(UINT)((_rd32(_REG_BASE_+(0x01e8<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY2_06r				(ValSft_R16(_rd32(_REG_BASE_+(0x01e9<<2)))&BitMask_10)
#define CGMY2_06w(val)			_wr32(_REG_BASE_+(0x01e9<<2),(UINT)((_rd32(_REG_BASE_+(0x01e9<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY2_07r				(ValSft_R00(_rd32(_REG_BASE_+(0x01e9<<2)))&BitMask_10)
#define CGMY2_07w(val)			_wr32(_REG_BASE_+(0x01e9<<2),(UINT)((_rd32(_REG_BASE_+(0x01e9<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY2_08r				(ValSft_R16(_rd32(_REG_BASE_+(0x01ea<<2)))&BitMask_10)
#define CGMY2_08w(val)			_wr32(_REG_BASE_+(0x01ea<<2),(UINT)((_rd32(_REG_BASE_+(0x01ea<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY2_09r				(ValSft_R00(_rd32(_REG_BASE_+(0x01ea<<2)))&BitMask_10)
#define CGMY2_09w(val)			_wr32(_REG_BASE_+(0x01ea<<2),(UINT)((_rd32(_REG_BASE_+(0x01ea<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY2_10r				(ValSft_R16(_rd32(_REG_BASE_+(0x01eb<<2)))&BitMask_10)
#define CGMY2_10w(val)			_wr32(_REG_BASE_+(0x01eb<<2),(UINT)((_rd32(_REG_BASE_+(0x01eb<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY2_11r				(ValSft_R00(_rd32(_REG_BASE_+(0x01eb<<2)))&BitMask_10)
#define CGMY2_11w(val)			_wr32(_REG_BASE_+(0x01eb<<2),(UINT)((_rd32(_REG_BASE_+(0x01eb<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY2_12r				(ValSft_R16(_rd32(_REG_BASE_+(0x01ec<<2)))&BitMask_10)
#define CGMY2_12w(val)			_wr32(_REG_BASE_+(0x01ec<<2),(UINT)((_rd32(_REG_BASE_+(0x01ec<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY2_13r				(ValSft_R00(_rd32(_REG_BASE_+(0x01ec<<2)))&BitMask_10)
#define CGMY2_13w(val)			_wr32(_REG_BASE_+(0x01ec<<2),(UINT)((_rd32(_REG_BASE_+(0x01ec<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY2_14r				(ValSft_R16(_rd32(_REG_BASE_+(0x01ed<<2)))&BitMask_10)
#define CGMY2_14w(val)			_wr32(_REG_BASE_+(0x01ed<<2),(UINT)((_rd32(_REG_BASE_+(0x01ed<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CGMY2_15r				(ValSft_R00(_rd32(_REG_BASE_+(0x01ed<<2)))&BitMask_10)
#define CGMY2_15w(val)			_wr32(_REG_BASE_+(0x01ed<<2),(UINT)((_rd32(_REG_BASE_+(0x01ed<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CGMY2_16r				(ValSft_R16(_rd32(_REG_BASE_+(0x01ee<<2)))&BitMask_10)
#define CGMY2_16w(val)			_wr32(_REG_BASE_+(0x01ee<<2),(UINT)((_rd32(_REG_BASE_+(0x01ee<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define RMYGr					(ValSft_R16(_rd32(_REG_BASE_+(0x0201<<2)))&BitMask_10)
#define RMYGw(val)				_wr32(_REG_BASE_+(0x0201<<2),(UINT)((_rd32(_REG_BASE_+(0x0201<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define RMYRr					(ValSft_R00(_rd32(_REG_BASE_+(0x0201<<2)))&BitMask_10)
#define RMYRw(val)				_wr32(_REG_BASE_+(0x0201<<2),(UINT)((_rd32(_REG_BASE_+(0x0201<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define BMYRr					(ValSft_R16(_rd32(_REG_BASE_+(0x0202<<2)))&BitMask_10)
#define BMYRw(val)				_wr32(_REG_BASE_+(0x0202<<2),(UINT)((_rd32(_REG_BASE_+(0x0202<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define RMYBr					(ValSft_R00(_rd32(_REG_BASE_+(0x0202<<2)))&BitMask_10)
#define RMYBw(val)				_wr32(_REG_BASE_+(0x0202<<2),(UINT)((_rd32(_REG_BASE_+(0x0202<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define BMYBr					(ValSft_R16(_rd32(_REG_BASE_+(0x0203<<2)))&BitMask_10)
#define BMYBw(val)				_wr32(_REG_BASE_+(0x0203<<2),(UINT)((_rd32(_REG_BASE_+(0x0203<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define BMYGr					(ValSft_R00(_rd32(_REG_BASE_+(0x0203<<2)))&BitMask_10)
#define BMYGw(val)				_wr32(_REG_BASE_+(0x0203<<2),(UINT)((_rd32(_REG_BASE_+(0x0203<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define BYGAINNr				(ValSft_R24(_rd32(_REG_BASE_+(0x0204<<2)))&BitMask_08)
#define BYGAINNw(val)			_wr32(_REG_BASE_+(0x0204<<2),(UINT)((_rd32(_REG_BASE_+(0x0204<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define BYGAINPr				(ValSft_R16(_rd32(_REG_BASE_+(0x0204<<2)))&BitMask_08)
#define BYGAINPw(val)			_wr32(_REG_BASE_+(0x0204<<2),(UINT)((_rd32(_REG_BASE_+(0x0204<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define RYGAINNr				(ValSft_R08(_rd32(_REG_BASE_+(0x0204<<2)))&BitMask_08)
#define RYGAINNw(val)			_wr32(_REG_BASE_+(0x0204<<2),(UINT)((_rd32(_REG_BASE_+(0x0204<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define RYGAINPr				(ValSft_R00(_rd32(_REG_BASE_+(0x0204<<2)))&BitMask_08)
#define RYGAINPw(val)			_wr32(_REG_BASE_+(0x0204<<2),(UINT)((_rd32(_REG_BASE_+(0x0204<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define BYHUENr					(ValSft_R24(_rd32(_REG_BASE_+(0x0205<<2)))&BitMask_08)
#define BYHUENw(val)			_wr32(_REG_BASE_+(0x0205<<2),(UINT)((_rd32(_REG_BASE_+(0x0205<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define BYHUEPr					(ValSft_R16(_rd32(_REG_BASE_+(0x0205<<2)))&BitMask_08)
#define BYHUEPw(val)			_wr32(_REG_BASE_+(0x0205<<2),(UINT)((_rd32(_REG_BASE_+(0x0205<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define RYHUENr					(ValSft_R08(_rd32(_REG_BASE_+(0x0205<<2)))&BitMask_08)
#define RYHUENw(val)			_wr32(_REG_BASE_+(0x0205<<2),(UINT)((_rd32(_REG_BASE_+(0x0205<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define RYHUEPr					(ValSft_R00(_rd32(_REG_BASE_+(0x0205<<2)))&BitMask_08)
#define RYHUEPw(val)			_wr32(_REG_BASE_+(0x0205<<2),(UINT)((_rd32(_REG_BASE_+(0x0205<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define NBYGAINNr				(ValSft_R24(_rd32(_REG_BASE_+(0x0206<<2)))&BitMask_08)
#define NBYGAINNw(val)			_wr32(_REG_BASE_+(0x0206<<2),(UINT)((_rd32(_REG_BASE_+(0x0206<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define NBYGAINPr				(ValSft_R16(_rd32(_REG_BASE_+(0x0206<<2)))&BitMask_08)
#define NBYGAINPw(val)			_wr32(_REG_BASE_+(0x0206<<2),(UINT)((_rd32(_REG_BASE_+(0x0206<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define NRYGAINNr				(ValSft_R08(_rd32(_REG_BASE_+(0x0206<<2)))&BitMask_08)
#define NRYGAINNw(val)			_wr32(_REG_BASE_+(0x0206<<2),(UINT)((_rd32(_REG_BASE_+(0x0206<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define NRYGAINPr				(ValSft_R00(_rd32(_REG_BASE_+(0x0206<<2)))&BitMask_08)
#define NRYGAINPw(val)			_wr32(_REG_BASE_+(0x0206<<2),(UINT)((_rd32(_REG_BASE_+(0x0206<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define NBYHUENr				(ValSft_R24(_rd32(_REG_BASE_+(0x0207<<2)))&BitMask_08)
#define NBYHUENw(val)			_wr32(_REG_BASE_+(0x0207<<2),(UINT)((_rd32(_REG_BASE_+(0x0207<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define NBYHUEPr				(ValSft_R16(_rd32(_REG_BASE_+(0x0207<<2)))&BitMask_08)
#define NBYHUEPw(val)			_wr32(_REG_BASE_+(0x0207<<2),(UINT)((_rd32(_REG_BASE_+(0x0207<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define NRYHUENr				(ValSft_R08(_rd32(_REG_BASE_+(0x0207<<2)))&BitMask_08)
#define NRYHUENw(val)			_wr32(_REG_BASE_+(0x0207<<2),(UINT)((_rd32(_REG_BASE_+(0x0207<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define NRYHUEPr				(ValSft_R00(_rd32(_REG_BASE_+(0x0207<<2)))&BitMask_08)
#define NRYHUEPw(val)			_wr32(_REG_BASE_+(0x0207<<2),(UINT)((_rd32(_REG_BASE_+(0x0207<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define VVD_FSr					(ValSft_R16(_rd32(_REG_BASE_+(0x0208<<2)))&BitMask_11)
#define VVD_FSw(val)			_wr32(_REG_BASE_+(0x0208<<2),(UINT)((_rd32(_REG_BASE_+(0x0208<<2))&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define VVD_LW_Y_ITCTr			(ValSft_R00(_rd32(_REG_BASE_+(0x0208<<2)))&BitMask_09)
#define VVD_LW_Y_ITCTw(val)		_wr32(_REG_BASE_+(0x0208<<2),(UINT)((_rd32(_REG_BASE_+(0x0208<<2))&(~ValSft_L00(BitMask_09)))|ValSft_L00((val)&BitMask_09)))

#define VVD_LW_SLOPEr			(ValSft_R20(_rd32(_REG_BASE_+(0x0209<<2)))&BitMask_09)
#define VVD_LW_SLOPEw(val)		_wr32(_REG_BASE_+(0x0209<<2),(UINT)((_rd32(_REG_BASE_+(0x0209<<2))&(~ValSft_L20(BitMask_09)))|ValSft_L20((val)&BitMask_09)))

#define VVD_LW_MINr				(ValSft_R10(_rd32(_REG_BASE_+(0x0209<<2)))&BitMask_09)
#define VVD_LW_MINw(val)		_wr32(_REG_BASE_+(0x0209<<2),(UINT)((_rd32(_REG_BASE_+(0x0209<<2))&(~ValSft_L10(BitMask_09)))|ValSft_L10((val)&BitMask_09)))

#define VVD_LW_MAXr				(ValSft_R00(_rd32(_REG_BASE_+(0x0209<<2)))&BitMask_09)
#define VVD_LW_MAXw(val)		_wr32(_REG_BASE_+(0x0209<<2),(UINT)((_rd32(_REG_BASE_+(0x0209<<2))&(~ValSft_L00(BitMask_09)))|ValSft_L00((val)&BitMask_09)))

#define VVD_CW_Rr				(ValSft_R16(_rd32(_REG_BASE_+(0x020a<<2)))&BitMask_08)
#define VVD_CW_Rw(val)			_wr32(_REG_BASE_+(0x020a<<2),(UINT)((_rd32(_REG_BASE_+(0x020a<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define VVD_CW_Gr				(ValSft_R08(_rd32(_REG_BASE_+(0x020a<<2)))&BitMask_08)
#define VVD_CW_Gw(val)			_wr32(_REG_BASE_+(0x020a<<2),(UINT)((_rd32(_REG_BASE_+(0x020a<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define VVD_CW_Br				(ValSft_R00(_rd32(_REG_BASE_+(0x020a<<2)))&BitMask_08)
#define VVD_CW_Bw(val)			_wr32(_REG_BASE_+(0x020a<<2),(UINT)((_rd32(_REG_BASE_+(0x020a<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define HSUP_GAr				(ValSft_R01(_rd32(_REG_BASE_+(0x0210<<2)))&BitMask_02)
#define HSUP_GAw(val)			_wr32(_REG_BASE_+(0x0210<<2),(UINT)((_rd32(_REG_BASE_+(0x0210<<2))&(~ValSft_L01(BitMask_02)))|ValSft_L01((val)&BitMask_02)))

#define HSUP_ONr				(ValSft_R00(_rd32(_REG_BASE_+(0x0210<<2)))&BitMask_01)
#define HSUP_ONw(val)			_wr32(_REG_BASE_+(0x0210<<2),(UINT)((_rd32(_REG_BASE_+(0x0210<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define LSUP_ONr				(ValSft_R31(_rd32(_REG_BASE_+(0x0211<<2)))&BitMask_01)
#define LSUP_ONw(val)			_wr32(_REG_BASE_+(0x0211<<2),(UINT)((_rd32(_REG_BASE_+(0x0211<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define LSUP_GAr				(ValSft_R24(_rd32(_REG_BASE_+(0x0211<<2)))&BitMask_06)
#define LSUP_GAw(val)			_wr32(_REG_BASE_+(0x0211<<2),(UINT)((_rd32(_REG_BASE_+(0x0211<<2))&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define LSUP_THr				(ValSft_R16(_rd32(_REG_BASE_+(0x0211<<2)))&BitMask_08)
#define LSUP_THw(val)			_wr32(_REG_BASE_+(0x0211<<2),(UINT)((_rd32(_REG_BASE_+(0x0211<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define CES_ONr					(ValSft_R15(_rd32(_REG_BASE_+(0x0211<<2)))&BitMask_01)
#define CES_ONw(val)			_wr32(_REG_BASE_+(0x0211<<2),(UINT)((_rd32(_REG_BASE_+(0x0211<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define CES_GAINr				(ValSft_R08(_rd32(_REG_BASE_+(0x0211<<2)))&BitMask_06)
#define CES_GAINw(val)			_wr32(_REG_BASE_+(0x0211<<2),(UINT)((_rd32(_REG_BASE_+(0x0211<<2))&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define CES_LCLIPr				(ValSft_R00(_rd32(_REG_BASE_+(0x0211<<2)))&BitMask_08)
#define CES_LCLIPw(val)			_wr32(_REG_BASE_+(0x0211<<2),(UINT)((_rd32(_REG_BASE_+(0x0211<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define CHLPF_SELr				(ValSft_R07(_rd32(_REG_BASE_+(0x0212<<2)))&BitMask_01)
#define CHLPF_SELw(val)			_wr32(_REG_BASE_+(0x0212<<2),(UINT)((_rd32(_REG_BASE_+(0x0212<<2))&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

#define CHLPF_ONr				(ValSft_R06(_rd32(_REG_BASE_+(0x0212<<2)))&BitMask_01)
#define CHLPF_ONw(val)			_wr32(_REG_BASE_+(0x0212<<2),(UINT)((_rd32(_REG_BASE_+(0x0212<<2))&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))

#define RLPF_Sr					(ValSft_R04(_rd32(_REG_BASE_+(0x0212<<2)))&BitMask_02)
#define RLPF_Sw(val)			_wr32(_REG_BASE_+(0x0212<<2),(UINT)((_rd32(_REG_BASE_+(0x0212<<2))&(~ValSft_L04(BitMask_02)))|ValSft_L04((val)&BitMask_02)))

#define BLPF_Sr					(ValSft_R02(_rd32(_REG_BASE_+(0x0212<<2)))&BitMask_02)
#define BLPF_Sw(val)			_wr32(_REG_BASE_+(0x0212<<2),(UINT)((_rd32(_REG_BASE_+(0x0212<<2))&(~ValSft_L02(BitMask_02)))|ValSft_L02((val)&BitMask_02)))

#define RBFLG_INV2r				(ValSft_R01(_rd32(_REG_BASE_+(0x0212<<2)))&BitMask_01)
#define RBFLG_INV2w(val)		_wr32(_REG_BASE_+(0x0212<<2),(UINT)((_rd32(_REG_BASE_+(0x0212<<2))&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define RBFLG_INVr				(ValSft_R00(_rd32(_REG_BASE_+(0x0212<<2)))&BitMask_01)
#define RBFLG_INVw(val)			_wr32(_REG_BASE_+(0x0212<<2),(UINT)((_rd32(_REG_BASE_+(0x0212<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define HLMASK_ONr				(ValSft_R31(_rd32(_REG_BASE_+(0x0213<<2)))&BitMask_01)
#define HLMASK_ONw(val)			_wr32(_REG_BASE_+(0x0213<<2),(UINT)((_rd32(_REG_BASE_+(0x0213<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define CSUP_ONr				(ValSft_R30(_rd32(_REG_BASE_+(0x0213<<2)))&BitMask_01)
#define CSUP_ONw(val)			_wr32(_REG_BASE_+(0x0213<<2),(UINT)((_rd32(_REG_BASE_+(0x0213<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define CSUP_GAr				(ValSft_R24(_rd32(_REG_BASE_+(0x0213<<2)))&BitMask_06)
#define CSUP_GAw(val)			_wr32(_REG_BASE_+(0x0213<<2),(UINT)((_rd32(_REG_BASE_+(0x0213<<2))&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define CSUP_THr				(ValSft_R16(_rd32(_REG_BASE_+(0x0213<<2)))&BitMask_08)
#define CSUP_THw(val)			_wr32(_REG_BASE_+(0x0213<<2),(UINT)((_rd32(_REG_BASE_+(0x0213<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define CES_DLYr				(ValSft_R08(_rd32(_REG_BASE_+(0x0213<<2)))&BitMask_04)
#define CES_DLYw(val)			_wr32(_REG_BASE_+(0x0213<<2),(UINT)((_rd32(_REG_BASE_+(0x0213<<2))&(~ValSft_L08(BitMask_04)))|ValSft_L08((val)&BitMask_04)))

#define CVLPF_SELr				(ValSft_R07(_rd32(_REG_BASE_+(0x0213<<2)))&BitMask_01)
#define CVLPF_SELw(val)			_wr32(_REG_BASE_+(0x0213<<2),(UINT)((_rd32(_REG_BASE_+(0x0213<<2))&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

#define CVLPF_ONr				(ValSft_R06(_rd32(_REG_BASE_+(0x0213<<2)))&BitMask_01)
#define CVLPF_ONw(val)			_wr32(_REG_BASE_+(0x0213<<2),(UINT)((_rd32(_REG_BASE_+(0x0213<<2))&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))

#define ACE_BPr					(ValSft_R31(_rd32(_REG_BASE_+(0x0215<<2)))&BitMask_01)
#define ACE_BPw(val)			_wr32(_REG_BASE_+(0x0215<<2),(UINT)((_rd32(_REG_BASE_+(0x0215<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define ACE_ONr					(ValSft_R30(_rd32(_REG_BASE_+(0x0215<<2)))&BitMask_01)
#define ACE_ONw(val)			_wr32(_REG_BASE_+(0x0215<<2),(UINT)((_rd32(_REG_BASE_+(0x0215<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define ACE_TESTr				(ValSft_R29(_rd32(_REG_BASE_+(0x0215<<2)))&BitMask_01)
#define ACE_TESTw(val)			_wr32(_REG_BASE_+(0x0215<<2),(UINT)((_rd32(_REG_BASE_+(0x0215<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define ACE_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x0215<<2)))&BitMask_12)
#define ACE_HSPw(val)			_wr32(_REG_BASE_+(0x0215<<2),(UINT)((_rd32(_REG_BASE_+(0x0215<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define ACE_DTHr				(ValSft_R12(_rd32(_REG_BASE_+(0x0215<<2)))&BitMask_04)
#define ACE_DTHw(val)			_wr32(_REG_BASE_+(0x0215<<2),(UINT)((_rd32(_REG_BASE_+(0x0215<<2))&(~ValSft_L12(BitMask_04)))|ValSft_L12((val)&BitMask_04)))

#define ACE_VSPr				(ValSft_R00(_rd32(_REG_BASE_+(0x0215<<2)))&BitMask_12)
#define ACE_VSPw(val)			_wr32(_REG_BASE_+(0x0215<<2),(UINT)((_rd32(_REG_BASE_+(0x0215<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define ACE_LPFr				(ValSft_R31(_rd32(_REG_BASE_+(0x0216<<2)))&BitMask_01)
#define ACE_LPFw(val)			_wr32(_REG_BASE_+(0x0216<<2),(UINT)((_rd32(_REG_BASE_+(0x0216<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define ACE_HBSr				(ValSft_R26(_rd32(_REG_BASE_+(0x0216<<2)))&BitMask_02)
#define ACE_HBSw(val)			_wr32(_REG_BASE_+(0x0216<<2),(UINT)((_rd32(_REG_BASE_+(0x0216<<2))&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define ACE_VBSr				(ValSft_R24(_rd32(_REG_BASE_+(0x0216<<2)))&BitMask_02)
#define ACE_VBSw(val)			_wr32(_REG_BASE_+(0x0216<<2),(UINT)((_rd32(_REG_BASE_+(0x0216<<2))&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define ACE_HBr					(ValSft_R20(_rd32(_REG_BASE_+(0x0216<<2)))&BitMask_04)
#define ACE_HBw(val)			_wr32(_REG_BASE_+(0x0216<<2),(UINT)((_rd32(_REG_BASE_+(0x0216<<2))&(~ValSft_L20(BitMask_04)))|ValSft_L20((val)&BitMask_04)))

#define ACE_VBr					(ValSft_R16(_rd32(_REG_BASE_+(0x0216<<2)))&BitMask_04)
#define ACE_VBw(val)			_wr32(_REG_BASE_+(0x0216<<2),(UINT)((_rd32(_REG_BASE_+(0x0216<<2))&(~ValSft_L16(BitMask_04)))|ValSft_L16((val)&BitMask_04)))

#define ACE_TH1r				(ValSft_R24(_rd32(_REG_BASE_+(0x0217<<2)))&BitMask_08)
#define ACE_TH1w(val)			_wr32(_REG_BASE_+(0x0217<<2),(UINT)((_rd32(_REG_BASE_+(0x0217<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define ACE_TH2r				(ValSft_R16(_rd32(_REG_BASE_+(0x0217<<2)))&BitMask_08)
#define ACE_TH2w(val)			_wr32(_REG_BASE_+(0x0217<<2),(UINT)((_rd32(_REG_BASE_+(0x0217<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define ACE_IIRr				(ValSft_R08(_rd32(_REG_BASE_+(0x0217<<2)))&BitMask_06)
#define ACE_IIRw(val)			_wr32(_REG_BASE_+(0x0217<<2),(UINT)((_rd32(_REG_BASE_+(0x0217<<2))&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define ACE_GMGNr				(ValSft_R00(_rd32(_REG_BASE_+(0x0217<<2)))&BitMask_08)
#define ACE_GMGNw(val)			_wr32(_REG_BASE_+(0x0217<<2),(UINT)((_rd32(_REG_BASE_+(0x0217<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define ACE_GM00r				(ValSft_R24(_rd32(_REG_BASE_+(0x0218<<2)))&BitMask_08)
#define ACE_GM00w(val)			_wr32(_REG_BASE_+(0x0218<<2),(UINT)((_rd32(_REG_BASE_+(0x0218<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define ACE_GM01r				(ValSft_R16(_rd32(_REG_BASE_+(0x0218<<2)))&BitMask_08)
#define ACE_GM01w(val)			_wr32(_REG_BASE_+(0x0218<<2),(UINT)((_rd32(_REG_BASE_+(0x0218<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define ACE_GM02r				(ValSft_R08(_rd32(_REG_BASE_+(0x0218<<2)))&BitMask_08)
#define ACE_GM02w(val)			_wr32(_REG_BASE_+(0x0218<<2),(UINT)((_rd32(_REG_BASE_+(0x0218<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define ACE_GM03r				(ValSft_R00(_rd32(_REG_BASE_+(0x0218<<2)))&BitMask_08)
#define ACE_GM03w(val)			_wr32(_REG_BASE_+(0x0218<<2),(UINT)((_rd32(_REG_BASE_+(0x0218<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define ACE_GM04r				(ValSft_R24(_rd32(_REG_BASE_+(0x0219<<2)))&BitMask_08)
#define ACE_GM04w(val)			_wr32(_REG_BASE_+(0x0219<<2),(UINT)((_rd32(_REG_BASE_+(0x0219<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define ACE_GM05r				(ValSft_R16(_rd32(_REG_BASE_+(0x0219<<2)))&BitMask_08)
#define ACE_GM05w(val)			_wr32(_REG_BASE_+(0x0219<<2),(UINT)((_rd32(_REG_BASE_+(0x0219<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define ACE_GM06r				(ValSft_R08(_rd32(_REG_BASE_+(0x0219<<2)))&BitMask_08)
#define ACE_GM06w(val)			_wr32(_REG_BASE_+(0x0219<<2),(UINT)((_rd32(_REG_BASE_+(0x0219<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define ACE_GM07r				(ValSft_R00(_rd32(_REG_BASE_+(0x0219<<2)))&BitMask_08)
#define ACE_GM07w(val)			_wr32(_REG_BASE_+(0x0219<<2),(UINT)((_rd32(_REG_BASE_+(0x0219<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define ACE_GM08r				(ValSft_R24(_rd32(_REG_BASE_+(0x021a<<2)))&BitMask_08)
#define ACE_GM08w(val)			_wr32(_REG_BASE_+(0x021a<<2),(UINT)((_rd32(_REG_BASE_+(0x021a<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define ACE_GM09r				(ValSft_R16(_rd32(_REG_BASE_+(0x021a<<2)))&BitMask_08)
#define ACE_GM09w(val)			_wr32(_REG_BASE_+(0x021a<<2),(UINT)((_rd32(_REG_BASE_+(0x021a<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define ACE_GM10r				(ValSft_R08(_rd32(_REG_BASE_+(0x021a<<2)))&BitMask_08)
#define ACE_GM10w(val)			_wr32(_REG_BASE_+(0x021a<<2),(UINT)((_rd32(_REG_BASE_+(0x021a<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define ACE_GM11r				(ValSft_R00(_rd32(_REG_BASE_+(0x021a<<2)))&BitMask_08)
#define ACE_GM11w(val)			_wr32(_REG_BASE_+(0x021a<<2),(UINT)((_rd32(_REG_BASE_+(0x021a<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define ACE_GM12r				(ValSft_R24(_rd32(_REG_BASE_+(0x021b<<2)))&BitMask_08)
#define ACE_GM12w(val)			_wr32(_REG_BASE_+(0x021b<<2),(UINT)((_rd32(_REG_BASE_+(0x021b<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define ACE_GM13r				(ValSft_R16(_rd32(_REG_BASE_+(0x021b<<2)))&BitMask_08)
#define ACE_GM13w(val)			_wr32(_REG_BASE_+(0x021b<<2),(UINT)((_rd32(_REG_BASE_+(0x021b<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define ACE_GM14r				(ValSft_R08(_rd32(_REG_BASE_+(0x021b<<2)))&BitMask_08)
#define ACE_GM14w(val)			_wr32(_REG_BASE_+(0x021b<<2),(UINT)((_rd32(_REG_BASE_+(0x021b<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define ACE_GM15r				(ValSft_R00(_rd32(_REG_BASE_+(0x021b<<2)))&BitMask_08)
#define ACE_GM15w(val)			_wr32(_REG_BASE_+(0x021b<<2),(UINT)((_rd32(_REG_BASE_+(0x021b<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define HEQ_ONr					(ValSft_R31(_rd32(_REG_BASE_+(0x021c<<2)))&BitMask_01)
#define HEQ_ONw(val)			_wr32(_REG_BASE_+(0x021c<<2),(UINT)((_rd32(_REG_BASE_+(0x021c<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define HEQ_OSDr				(ValSft_R30(_rd32(_REG_BASE_+(0x021c<<2)))&BitMask_01)
#define HEQ_OSDw(val)			_wr32(_REG_BASE_+(0x021c<<2),(UINT)((_rd32(_REG_BASE_+(0x021c<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define HEQ_WGr					(ValSft_R16(_rd32(_REG_BASE_+(0x021c<<2)))&BitMask_09)
#define HEQ_WGw(val)			_wr32(_REG_BASE_+(0x021c<<2),(UINT)((_rd32(_REG_BASE_+(0x021c<<2))&(~ValSft_L16(BitMask_09)))|ValSft_L16((val)&BitMask_09)))

#define HEQ_THr					(ValSft_R00(_rd32(_REG_BASE_+(0x021c<<2)))&BitMask_15)
#define HEQ_THw(val)			_wr32(_REG_BASE_+(0x021c<<2),(UINT)((_rd32(_REG_BASE_+(0x021c<<2))&(~ValSft_L00(BitMask_15)))|ValSft_L00((val)&BitMask_15)))

#define HEQ_HWr					(ValSft_R28(_rd32(_REG_BASE_+(0x021d<<2)))&BitMask_04)
#define HEQ_HWw(val)			_wr32(_REG_BASE_+(0x021d<<2),(UINT)((_rd32(_REG_BASE_+(0x021d<<2))&(~ValSft_L28(BitMask_04)))|ValSft_L28((val)&BitMask_04)))

#define HEQ_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x021d<<2)))&BitMask_12)
#define HEQ_HSPw(val)			_wr32(_REG_BASE_+(0x021d<<2),(UINT)((_rd32(_REG_BASE_+(0x021d<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define HEQ_VWr					(ValSft_R12(_rd32(_REG_BASE_+(0x021d<<2)))&BitMask_04)
#define HEQ_VWw(val)			_wr32(_REG_BASE_+(0x021d<<2),(UINT)((_rd32(_REG_BASE_+(0x021d<<2))&(~ValSft_L12(BitMask_04)))|ValSft_L12((val)&BitMask_04)))

#define HEQ_VSPr				(ValSft_R00(_rd32(_REG_BASE_+(0x021d<<2)))&BitMask_12)
#define HEQ_VSPw(val)			_wr32(_REG_BASE_+(0x021d<<2),(UINT)((_rd32(_REG_BASE_+(0x021d<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define HEQ_IIRKr				(ValSft_R00(_rd32(_REG_BASE_+(0x021e<<2)))&BitMask_08)
#define HEQ_IIRKw(val)			_wr32(_REG_BASE_+(0x021e<<2),(UINT)((_rd32(_REG_BASE_+(0x021e<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define HLMASK_BLVr				(ValSft_R24(_rd32(_REG_BASE_+(0x0221<<2)))&BitMask_08)
#define HLMASK_BLVw(val)		_wr32(_REG_BASE_+(0x0221<<2),(UINT)((_rd32(_REG_BASE_+(0x0221<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define HLMASK_RLVr				(ValSft_R16(_rd32(_REG_BASE_+(0x0221<<2)))&BitMask_08)
#define HLMASK_RLVw(val)		_wr32(_REG_BASE_+(0x0221<<2),(UINT)((_rd32(_REG_BASE_+(0x0221<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define HLMASK_YLVr				(ValSft_R08(_rd32(_REG_BASE_+(0x0221<<2)))&BitMask_08)
#define HLMASK_YLVw(val)		_wr32(_REG_BASE_+(0x0221<<2),(UINT)((_rd32(_REG_BASE_+(0x0221<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define HLMASK_THr				(ValSft_R00(_rd32(_REG_BASE_+(0x0221<<2)))&BitMask_08)
#define HLMASK_THw(val)			_wr32(_REG_BASE_+(0x0221<<2),(UINT)((_rd32(_REG_BASE_+(0x0221<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define DCBAR_ONr				(ValSft_R31(_rd32(_REG_BASE_+(0x0223<<2)))&BitMask_01)
#define DCBAR_ONw(val)			_wr32(_REG_BASE_+(0x0223<<2),(UINT)((_rd32(_REG_BASE_+(0x0223<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DCBAR_HWr				(ValSft_R16(_rd32(_REG_BASE_+(0x0223<<2)))&BitMask_09)
#define DCBAR_HWw(val)			_wr32(_REG_BASE_+(0x0223<<2),(UINT)((_rd32(_REG_BASE_+(0x0223<<2))&(~ValSft_L16(BitMask_09)))|ValSft_L16((val)&BitMask_09)))

#define DCBAR_STr				(ValSft_R00(_rd32(_REG_BASE_+(0x0223<<2)))&BitMask_12)
#define DCBAR_STw(val)			_wr32(_REG_BASE_+(0x0223<<2),(UINT)((_rd32(_REG_BASE_+(0x0223<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define FONT_MASKONr			(ValSft_R31(_rd32(_REG_BASE_+(0x0224<<2)))&BitMask_01)
#define FONT_MASKONw(val)		_wr32(_REG_BASE_+(0x0224<<2),(UINT)((_rd32(_REG_BASE_+(0x0224<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define FONT_HMSTr				(ValSft_R16(_rd32(_REG_BASE_+(0x0224<<2)))&BitMask_12)
#define FONT_HMSTw(val)			_wr32(_REG_BASE_+(0x0224<<2),(UINT)((_rd32(_REG_BASE_+(0x0224<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define FONT_HMEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x0224<<2)))&BitMask_12)
#define FONT_HMEDw(val)			_wr32(_REG_BASE_+(0x0224<<2),(UINT)((_rd32(_REG_BASE_+(0x0224<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define FONT_VMSTr				(ValSft_R16(_rd32(_REG_BASE_+(0x0225<<2)))&BitMask_12)
#define FONT_VMSTw(val)			_wr32(_REG_BASE_+(0x0225<<2),(UINT)((_rd32(_REG_BASE_+(0x0225<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define FONT_VMEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x0225<<2)))&BitMask_12)
#define FONT_VMEDw(val)			_wr32(_REG_BASE_+(0x0225<<2),(UINT)((_rd32(_REG_BASE_+(0x0225<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define FONT_HSPr				(ValSft_R00(_rd32(_REG_BASE_+(0x0226<<2)))&BitMask_13)
#define FONT_HSPw(val)			_wr32(_REG_BASE_+(0x0226<<2),(UINT)((_rd32(_REG_BASE_+(0x0226<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define FONT_ONr				(ValSft_R31(_rd32(_REG_BASE_+(0x0227<<2)))&BitMask_01)
#define FONT_ONw(val)			_wr32(_REG_BASE_+(0x0227<<2),(UINT)((_rd32(_REG_BASE_+(0x0227<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define BOAD_ONr				(ValSft_R30(_rd32(_REG_BASE_+(0x0227<<2)))&BitMask_01)
#define BOAD_ONw(val)			_wr32(_REG_BASE_+(0x0227<<2),(UINT)((_rd32(_REG_BASE_+(0x0227<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define BOAD_MODEr				(ValSft_R29(_rd32(_REG_BASE_+(0x0227<<2)))&BitMask_01)
#define BOAD_MODEw(val)			_wr32(_REG_BASE_+(0x0227<<2),(UINT)((_rd32(_REG_BASE_+(0x0227<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define FONT_MUTEr				(ValSft_R28(_rd32(_REG_BASE_+(0x0227<<2)))&BitMask_01)
#define FONT_MUTEw(val)			_wr32(_REG_BASE_+(0x0227<<2),(UINT)((_rd32(_REG_BASE_+(0x0227<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define FONT_OFYr				(ValSft_R16(_rd32(_REG_BASE_+(0x0227<<2)))&BitMask_12)
#define FONT_OFYw(val)			_wr32(_REG_BASE_+(0x0227<<2),(UINT)((_rd32(_REG_BASE_+(0x0227<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define FONT_OFXr				(ValSft_R00(_rd32(_REG_BASE_+(0x0227<<2)))&BitMask_12)
#define FONT_OFXw(val)			_wr32(_REG_BASE_+(0x0227<<2),(UINT)((_rd32(_REG_BASE_+(0x0227<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define FONT_LV0r				(ValSft_R00(_rd32(_REG_BASE_+(0x0228<<2)))&BitMask_24)
#define FONT_LV0w(val)			_wr32(_REG_BASE_+(0x0228<<2),(UINT)((_rd32(_REG_BASE_+(0x0228<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define FONT_LV1r				(ValSft_R00(_rd32(_REG_BASE_+(0x0229<<2)))&BitMask_24)
#define FONT_LV1w(val)			_wr32(_REG_BASE_+(0x0229<<2),(UINT)((_rd32(_REG_BASE_+(0x0229<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define FONT_LV2r				(ValSft_R00(_rd32(_REG_BASE_+(0x022a<<2)))&BitMask_24)
#define FONT_LV2w(val)			_wr32(_REG_BASE_+(0x022a<<2),(UINT)((_rd32(_REG_BASE_+(0x022a<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define FONT_LV3r				(ValSft_R00(_rd32(_REG_BASE_+(0x022b<<2)))&BitMask_24)
#define FONT_LV3w(val)			_wr32(_REG_BASE_+(0x022b<<2),(UINT)((_rd32(_REG_BASE_+(0x022b<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOAD_LV0r				(ValSft_R00(_rd32(_REG_BASE_+(0x022c<<2)))&BitMask_24)
#define BOAD_LV0w(val)			_wr32(_REG_BASE_+(0x022c<<2),(UINT)((_rd32(_REG_BASE_+(0x022c<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define FONT_HHALFr				(ValSft_R31(_rd32(_REG_BASE_+(0x022d<<2)))&BitMask_01)
#define FONT_HHALFw(val)		_wr32(_REG_BASE_+(0x022d<<2),(UINT)((_rd32(_REG_BASE_+(0x022d<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define FONT_VHALFr				(ValSft_R30(_rd32(_REG_BASE_+(0x022d<<2)))&BitMask_01)
#define FONT_VHALFw(val)		_wr32(_REG_BASE_+(0x022d<<2),(UINT)((_rd32(_REG_BASE_+(0x022d<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define FONT_VBLKr				(ValSft_R16(_rd32(_REG_BASE_+(0x022d<<2)))&BitMask_08)
#define FONT_VBLKw(val)			_wr32(_REG_BASE_+(0x022d<<2),(UINT)((_rd32(_REG_BASE_+(0x022d<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define FONT_HBLKr				(ValSft_R08(_rd32(_REG_BASE_+(0x022d<<2)))&BitMask_08)
#define FONT_HBLKw(val)			_wr32(_REG_BASE_+(0x022d<<2),(UINT)((_rd32(_REG_BASE_+(0x022d<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define FONT_VSIZr				(ValSft_R04(_rd32(_REG_BASE_+(0x022d<<2)))&BitMask_04)
#define FONT_VSIZw(val)			_wr32(_REG_BASE_+(0x022d<<2),(UINT)((_rd32(_REG_BASE_+(0x022d<<2))&(~ValSft_L04(BitMask_04)))|ValSft_L04((val)&BitMask_04)))

#define FONT_HSIZr				(ValSft_R00(_rd32(_REG_BASE_+(0x022d<<2)))&BitMask_04)
#define FONT_HSIZw(val)			_wr32(_REG_BASE_+(0x022d<<2),(UINT)((_rd32(_REG_BASE_+(0x022d<<2))&(~ValSft_L00(BitMask_04)))|ValSft_L00((val)&BitMask_04)))

#define MASK_CHADr				(ValSft_R16(_rd32(_REG_BASE_+(0x022e<<2)))&BitMask_09)
#define MASK_CHADw(val)			_wr32(_REG_BASE_+(0x022e<<2),(UINT)((_rd32(_REG_BASE_+(0x022e<<2))&(~ValSft_L16(BitMask_09)))|ValSft_L16((val)&BitMask_09)))

#define HALF_CHADr				(ValSft_R00(_rd32(_REG_BASE_+(0x022e<<2)))&BitMask_09)
#define HALF_CHADw(val)			_wr32(_REG_BASE_+(0x022e<<2),(UINT)((_rd32(_REG_BASE_+(0x022e<<2))&(~ValSft_L00(BitMask_09)))|ValSft_L00((val)&BitMask_09)))

#define OSD_MUTEr				(ValSft_R29(_rd32(_REG_BASE_+(0x0231<<2)))&BitMask_01)
#define OSD_MUTEw(val)			_wr32(_REG_BASE_+(0x0231<<2),(UINT)((_rd32(_REG_BASE_+(0x0231<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define BOSD_ONr				(ValSft_R00(_rd32(_REG_BASE_+(0x0271<<2)))&BitMask_32)
#define BOSD_ONw(val)			_wr32(_REG_BASE_+(0x0271<<2),(UINT)((_rd32(_REG_BASE_+(0x0271<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define BOX_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x0273<<2)))&BitMask_12)
#define BOX_VSPw(val)			_wr32(_REG_BASE_+(0x0273<<2),(UINT)((_rd32(_REG_BASE_+(0x0273<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define BOX_HSPr				(ValSft_R00(_rd32(_REG_BASE_+(0x0273<<2)))&BitMask_12)
#define BOX_HSPw(val)			_wr32(_REG_BASE_+(0x0273<<2),(UINT)((_rd32(_REG_BASE_+(0x0273<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BTONE31r				(ValSft_R30(_rd32(_REG_BASE_+(0x0274<<2)))&BitMask_02)
#define BTONE31w(val)			_wr32(_REG_BASE_+(0x0274<<2),(UINT)((_rd32(_REG_BASE_+(0x0274<<2))&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define BTONE30r				(ValSft_R28(_rd32(_REG_BASE_+(0x0274<<2)))&BitMask_02)
#define BTONE30w(val)			_wr32(_REG_BASE_+(0x0274<<2),(UINT)((_rd32(_REG_BASE_+(0x0274<<2))&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define BTONE29r				(ValSft_R26(_rd32(_REG_BASE_+(0x0274<<2)))&BitMask_02)
#define BTONE29w(val)			_wr32(_REG_BASE_+(0x0274<<2),(UINT)((_rd32(_REG_BASE_+(0x0274<<2))&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define BTONE28r				(ValSft_R24(_rd32(_REG_BASE_+(0x0274<<2)))&BitMask_02)
#define BTONE28w(val)			_wr32(_REG_BASE_+(0x0274<<2),(UINT)((_rd32(_REG_BASE_+(0x0274<<2))&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define BTONE27r				(ValSft_R22(_rd32(_REG_BASE_+(0x0274<<2)))&BitMask_02)
#define BTONE27w(val)			_wr32(_REG_BASE_+(0x0274<<2),(UINT)((_rd32(_REG_BASE_+(0x0274<<2))&(~ValSft_L22(BitMask_02)))|ValSft_L22((val)&BitMask_02)))

#define BTONE26r				(ValSft_R20(_rd32(_REG_BASE_+(0x0274<<2)))&BitMask_02)
#define BTONE26w(val)			_wr32(_REG_BASE_+(0x0274<<2),(UINT)((_rd32(_REG_BASE_+(0x0274<<2))&(~ValSft_L20(BitMask_02)))|ValSft_L20((val)&BitMask_02)))

#define BTONE25r				(ValSft_R18(_rd32(_REG_BASE_+(0x0274<<2)))&BitMask_02)
#define BTONE25w(val)			_wr32(_REG_BASE_+(0x0274<<2),(UINT)((_rd32(_REG_BASE_+(0x0274<<2))&(~ValSft_L18(BitMask_02)))|ValSft_L18((val)&BitMask_02)))

#define BTONE24r				(ValSft_R16(_rd32(_REG_BASE_+(0x0274<<2)))&BitMask_02)
#define BTONE24w(val)			_wr32(_REG_BASE_+(0x0274<<2),(UINT)((_rd32(_REG_BASE_+(0x0274<<2))&(~ValSft_L16(BitMask_02)))|ValSft_L16((val)&BitMask_02)))

#define BTONE23r				(ValSft_R14(_rd32(_REG_BASE_+(0x0274<<2)))&BitMask_02)
#define BTONE23w(val)			_wr32(_REG_BASE_+(0x0274<<2),(UINT)((_rd32(_REG_BASE_+(0x0274<<2))&(~ValSft_L14(BitMask_02)))|ValSft_L14((val)&BitMask_02)))

#define BTONE22r				(ValSft_R12(_rd32(_REG_BASE_+(0x0274<<2)))&BitMask_02)
#define BTONE22w(val)			_wr32(_REG_BASE_+(0x0274<<2),(UINT)((_rd32(_REG_BASE_+(0x0274<<2))&(~ValSft_L12(BitMask_02)))|ValSft_L12((val)&BitMask_02)))

#define BTONE21r				(ValSft_R10(_rd32(_REG_BASE_+(0x0274<<2)))&BitMask_02)
#define BTONE21w(val)			_wr32(_REG_BASE_+(0x0274<<2),(UINT)((_rd32(_REG_BASE_+(0x0274<<2))&(~ValSft_L10(BitMask_02)))|ValSft_L10((val)&BitMask_02)))

#define BTONE20r				(ValSft_R08(_rd32(_REG_BASE_+(0x0274<<2)))&BitMask_02)
#define BTONE20w(val)			_wr32(_REG_BASE_+(0x0274<<2),(UINT)((_rd32(_REG_BASE_+(0x0274<<2))&(~ValSft_L08(BitMask_02)))|ValSft_L08((val)&BitMask_02)))

#define BTONE19r				(ValSft_R06(_rd32(_REG_BASE_+(0x0274<<2)))&BitMask_02)
#define BTONE19w(val)			_wr32(_REG_BASE_+(0x0274<<2),(UINT)((_rd32(_REG_BASE_+(0x0274<<2))&(~ValSft_L06(BitMask_02)))|ValSft_L06((val)&BitMask_02)))

#define BTONE18r				(ValSft_R04(_rd32(_REG_BASE_+(0x0274<<2)))&BitMask_02)
#define BTONE18w(val)			_wr32(_REG_BASE_+(0x0274<<2),(UINT)((_rd32(_REG_BASE_+(0x0274<<2))&(~ValSft_L04(BitMask_02)))|ValSft_L04((val)&BitMask_02)))

#define BTONE17r				(ValSft_R02(_rd32(_REG_BASE_+(0x0274<<2)))&BitMask_02)
#define BTONE17w(val)			_wr32(_REG_BASE_+(0x0274<<2),(UINT)((_rd32(_REG_BASE_+(0x0274<<2))&(~ValSft_L02(BitMask_02)))|ValSft_L02((val)&BitMask_02)))

#define BTONE16r				(ValSft_R00(_rd32(_REG_BASE_+(0x0274<<2)))&BitMask_02)
#define BTONE16w(val)			_wr32(_REG_BASE_+(0x0274<<2),(UINT)((_rd32(_REG_BASE_+(0x0274<<2))&(~ValSft_L00(BitMask_02)))|ValSft_L00((val)&BitMask_02)))

#define BTONE15r				(ValSft_R30(_rd32(_REG_BASE_+(0x0275<<2)))&BitMask_02)
#define BTONE15w(val)			_wr32(_REG_BASE_+(0x0275<<2),(UINT)((_rd32(_REG_BASE_+(0x0275<<2))&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define BTONE14r				(ValSft_R28(_rd32(_REG_BASE_+(0x0275<<2)))&BitMask_02)
#define BTONE14w(val)			_wr32(_REG_BASE_+(0x0275<<2),(UINT)((_rd32(_REG_BASE_+(0x0275<<2))&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define BTONE13r				(ValSft_R26(_rd32(_REG_BASE_+(0x0275<<2)))&BitMask_02)
#define BTONE13w(val)			_wr32(_REG_BASE_+(0x0275<<2),(UINT)((_rd32(_REG_BASE_+(0x0275<<2))&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define BTONE12r				(ValSft_R24(_rd32(_REG_BASE_+(0x0275<<2)))&BitMask_02)
#define BTONE12w(val)			_wr32(_REG_BASE_+(0x0275<<2),(UINT)((_rd32(_REG_BASE_+(0x0275<<2))&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define BTONE11r				(ValSft_R22(_rd32(_REG_BASE_+(0x0275<<2)))&BitMask_02)
#define BTONE11w(val)			_wr32(_REG_BASE_+(0x0275<<2),(UINT)((_rd32(_REG_BASE_+(0x0275<<2))&(~ValSft_L22(BitMask_02)))|ValSft_L22((val)&BitMask_02)))

#define BTONE10r				(ValSft_R20(_rd32(_REG_BASE_+(0x0275<<2)))&BitMask_02)
#define BTONE10w(val)			_wr32(_REG_BASE_+(0x0275<<2),(UINT)((_rd32(_REG_BASE_+(0x0275<<2))&(~ValSft_L20(BitMask_02)))|ValSft_L20((val)&BitMask_02)))

#define BTONE9r					(ValSft_R18(_rd32(_REG_BASE_+(0x0275<<2)))&BitMask_02)
#define BTONE9w(val)			_wr32(_REG_BASE_+(0x0275<<2),(UINT)((_rd32(_REG_BASE_+(0x0275<<2))&(~ValSft_L18(BitMask_02)))|ValSft_L18((val)&BitMask_02)))

#define BTONE8r					(ValSft_R16(_rd32(_REG_BASE_+(0x0275<<2)))&BitMask_02)
#define BTONE8w(val)			_wr32(_REG_BASE_+(0x0275<<2),(UINT)((_rd32(_REG_BASE_+(0x0275<<2))&(~ValSft_L16(BitMask_02)))|ValSft_L16((val)&BitMask_02)))

#define BTONE7r					(ValSft_R14(_rd32(_REG_BASE_+(0x0275<<2)))&BitMask_02)
#define BTONE7w(val)			_wr32(_REG_BASE_+(0x0275<<2),(UINT)((_rd32(_REG_BASE_+(0x0275<<2))&(~ValSft_L14(BitMask_02)))|ValSft_L14((val)&BitMask_02)))

#define BTONE6r					(ValSft_R12(_rd32(_REG_BASE_+(0x0275<<2)))&BitMask_02)
#define BTONE6w(val)			_wr32(_REG_BASE_+(0x0275<<2),(UINT)((_rd32(_REG_BASE_+(0x0275<<2))&(~ValSft_L12(BitMask_02)))|ValSft_L12((val)&BitMask_02)))

#define BTONE5r					(ValSft_R10(_rd32(_REG_BASE_+(0x0275<<2)))&BitMask_02)
#define BTONE5w(val)			_wr32(_REG_BASE_+(0x0275<<2),(UINT)((_rd32(_REG_BASE_+(0x0275<<2))&(~ValSft_L10(BitMask_02)))|ValSft_L10((val)&BitMask_02)))

#define BTONE4r					(ValSft_R08(_rd32(_REG_BASE_+(0x0275<<2)))&BitMask_02)
#define BTONE4w(val)			_wr32(_REG_BASE_+(0x0275<<2),(UINT)((_rd32(_REG_BASE_+(0x0275<<2))&(~ValSft_L08(BitMask_02)))|ValSft_L08((val)&BitMask_02)))

#define BTONE3r					(ValSft_R06(_rd32(_REG_BASE_+(0x0275<<2)))&BitMask_02)
#define BTONE3w(val)			_wr32(_REG_BASE_+(0x0275<<2),(UINT)((_rd32(_REG_BASE_+(0x0275<<2))&(~ValSft_L06(BitMask_02)))|ValSft_L06((val)&BitMask_02)))

#define BTONE2r					(ValSft_R04(_rd32(_REG_BASE_+(0x0275<<2)))&BitMask_02)
#define BTONE2w(val)			_wr32(_REG_BASE_+(0x0275<<2),(UINT)((_rd32(_REG_BASE_+(0x0275<<2))&(~ValSft_L04(BitMask_02)))|ValSft_L04((val)&BitMask_02)))

#define BTONE1r					(ValSft_R02(_rd32(_REG_BASE_+(0x0275<<2)))&BitMask_02)
#define BTONE1w(val)			_wr32(_REG_BASE_+(0x0275<<2),(UINT)((_rd32(_REG_BASE_+(0x0275<<2))&(~ValSft_L02(BitMask_02)))|ValSft_L02((val)&BitMask_02)))

#define BTONE0r					(ValSft_R00(_rd32(_REG_BASE_+(0x0275<<2)))&BitMask_02)
#define BTONE0w(val)			_wr32(_REG_BASE_+(0x0275<<2),(UINT)((_rd32(_REG_BASE_+(0x0275<<2))&(~ValSft_L00(BitMask_02)))|ValSft_L00((val)&BitMask_02)))

#define BFL_ON31r				(ValSft_R31(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON31w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define BFL_ON30r				(ValSft_R30(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON30w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define BFL_ON29r				(ValSft_R29(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON29w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define BFL_ON28r				(ValSft_R28(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON28w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define BFL_ON27r				(ValSft_R27(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON27w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define BFL_ON26r				(ValSft_R26(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON26w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define BFL_ON25r				(ValSft_R25(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON25w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L25(BitMask_01)))|ValSft_L25((val)&BitMask_01)))

#define BFL_ON24r				(ValSft_R24(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON24w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L24(BitMask_01)))|ValSft_L24((val)&BitMask_01)))

#define BFL_ON23r				(ValSft_R23(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON23w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define BFL_ON22r				(ValSft_R22(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON22w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L22(BitMask_01)))|ValSft_L22((val)&BitMask_01)))

#define BFL_ON21r				(ValSft_R21(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON21w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L21(BitMask_01)))|ValSft_L21((val)&BitMask_01)))

#define BFL_ON20r				(ValSft_R20(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON20w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L20(BitMask_01)))|ValSft_L20((val)&BitMask_01)))

#define BFL_ON19r				(ValSft_R19(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON19w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L19(BitMask_01)))|ValSft_L19((val)&BitMask_01)))

#define BFL_ON18r				(ValSft_R18(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON18w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L18(BitMask_01)))|ValSft_L18((val)&BitMask_01)))

#define BFL_ON17r				(ValSft_R17(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON17w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L17(BitMask_01)))|ValSft_L17((val)&BitMask_01)))

#define BFL_ON16r				(ValSft_R16(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON16w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L16(BitMask_01)))|ValSft_L16((val)&BitMask_01)))

#define BFL_ON15r				(ValSft_R15(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON15w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define BFL_ON14r				(ValSft_R14(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON14w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L14(BitMask_01)))|ValSft_L14((val)&BitMask_01)))

#define BFL_ON13r				(ValSft_R13(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON13w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L13(BitMask_01)))|ValSft_L13((val)&BitMask_01)))

#define BFL_ON12r				(ValSft_R12(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON12w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L12(BitMask_01)))|ValSft_L12((val)&BitMask_01)))

#define BFL_ON11r				(ValSft_R11(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON11w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L11(BitMask_01)))|ValSft_L11((val)&BitMask_01)))

#define BFL_ON10r				(ValSft_R10(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON10w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L10(BitMask_01)))|ValSft_L10((val)&BitMask_01)))

#define BFL_ON9r				(ValSft_R09(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON9w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L09(BitMask_01)))|ValSft_L09((val)&BitMask_01)))

#define BFL_ON8r				(ValSft_R08(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON8w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L08(BitMask_01)))|ValSft_L08((val)&BitMask_01)))

#define BFL_ON7r				(ValSft_R07(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON7w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

#define BFL_ON6r				(ValSft_R06(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON6w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))

#define BFL_ON5r				(ValSft_R05(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON5w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))

#define BFL_ON4r				(ValSft_R04(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON4w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))

#define BFL_ON3r				(ValSft_R03(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON3w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))

#define BFL_ON2r				(ValSft_R02(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON2w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))

#define BFL_ON1r				(ValSft_R01(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON1w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define BFL_ON0r				(ValSft_R00(_rd32(_REG_BASE_+(0x0276<<2)))&BitMask_01)
#define BFL_ON0w(val)			_wr32(_REG_BASE_+(0x0276<<2),(UINT)((_rd32(_REG_BASE_+(0x0276<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define B0_VSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x0280<<2)))&BitMask_12)
#define B0_VSPw(val)			_wr32(_REG_BASE_+(0x0280<<2),(UINT)((_rd32(_REG_BASE_+(0x0280<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B0_VEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x0280<<2)))&BitMask_12)
#define B0_VEDw(val)			_wr32(_REG_BASE_+(0x0280<<2),(UINT)((_rd32(_REG_BASE_+(0x0280<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B0_HSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x0281<<2)))&BitMask_12)
#define B0_HSPw(val)			_wr32(_REG_BASE_+(0x0281<<2),(UINT)((_rd32(_REG_BASE_+(0x0281<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B0_HEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x0281<<2)))&BitMask_12)
#define B0_HEDw(val)			_wr32(_REG_BASE_+(0x0281<<2),(UINT)((_rd32(_REG_BASE_+(0x0281<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B1_VSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x0282<<2)))&BitMask_12)
#define B1_VSPw(val)			_wr32(_REG_BASE_+(0x0282<<2),(UINT)((_rd32(_REG_BASE_+(0x0282<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B1_VEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x0282<<2)))&BitMask_12)
#define B1_VEDw(val)			_wr32(_REG_BASE_+(0x0282<<2),(UINT)((_rd32(_REG_BASE_+(0x0282<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B1_HSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x0283<<2)))&BitMask_12)
#define B1_HSPw(val)			_wr32(_REG_BASE_+(0x0283<<2),(UINT)((_rd32(_REG_BASE_+(0x0283<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B1_HEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x0283<<2)))&BitMask_12)
#define B1_HEDw(val)			_wr32(_REG_BASE_+(0x0283<<2),(UINT)((_rd32(_REG_BASE_+(0x0283<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B2_VSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x0284<<2)))&BitMask_12)
#define B2_VSPw(val)			_wr32(_REG_BASE_+(0x0284<<2),(UINT)((_rd32(_REG_BASE_+(0x0284<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B2_VEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x0284<<2)))&BitMask_12)
#define B2_VEDw(val)			_wr32(_REG_BASE_+(0x0284<<2),(UINT)((_rd32(_REG_BASE_+(0x0284<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B2_HSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x0285<<2)))&BitMask_12)
#define B2_HSPw(val)			_wr32(_REG_BASE_+(0x0285<<2),(UINT)((_rd32(_REG_BASE_+(0x0285<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B2_HEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x0285<<2)))&BitMask_12)
#define B2_HEDw(val)			_wr32(_REG_BASE_+(0x0285<<2),(UINT)((_rd32(_REG_BASE_+(0x0285<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B3_VSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x0286<<2)))&BitMask_12)
#define B3_VSPw(val)			_wr32(_REG_BASE_+(0x0286<<2),(UINT)((_rd32(_REG_BASE_+(0x0286<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B3_VEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x0286<<2)))&BitMask_12)
#define B3_VEDw(val)			_wr32(_REG_BASE_+(0x0286<<2),(UINT)((_rd32(_REG_BASE_+(0x0286<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B3_HSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x0287<<2)))&BitMask_12)
#define B3_HSPw(val)			_wr32(_REG_BASE_+(0x0287<<2),(UINT)((_rd32(_REG_BASE_+(0x0287<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B3_HEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x0287<<2)))&BitMask_12)
#define B3_HEDw(val)			_wr32(_REG_BASE_+(0x0287<<2),(UINT)((_rd32(_REG_BASE_+(0x0287<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B4_VSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x0288<<2)))&BitMask_12)
#define B4_VSPw(val)			_wr32(_REG_BASE_+(0x0288<<2),(UINT)((_rd32(_REG_BASE_+(0x0288<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B4_VEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x0288<<2)))&BitMask_12)
#define B4_VEDw(val)			_wr32(_REG_BASE_+(0x0288<<2),(UINT)((_rd32(_REG_BASE_+(0x0288<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B4_HSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x0289<<2)))&BitMask_12)
#define B4_HSPw(val)			_wr32(_REG_BASE_+(0x0289<<2),(UINT)((_rd32(_REG_BASE_+(0x0289<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B4_HEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x0289<<2)))&BitMask_12)
#define B4_HEDw(val)			_wr32(_REG_BASE_+(0x0289<<2),(UINT)((_rd32(_REG_BASE_+(0x0289<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B5_VSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x028a<<2)))&BitMask_12)
#define B5_VSPw(val)			_wr32(_REG_BASE_+(0x028a<<2),(UINT)((_rd32(_REG_BASE_+(0x028a<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B5_VEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x028a<<2)))&BitMask_12)
#define B5_VEDw(val)			_wr32(_REG_BASE_+(0x028a<<2),(UINT)((_rd32(_REG_BASE_+(0x028a<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B5_HSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x028b<<2)))&BitMask_12)
#define B5_HSPw(val)			_wr32(_REG_BASE_+(0x028b<<2),(UINT)((_rd32(_REG_BASE_+(0x028b<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B5_HEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x028b<<2)))&BitMask_12)
#define B5_HEDw(val)			_wr32(_REG_BASE_+(0x028b<<2),(UINT)((_rd32(_REG_BASE_+(0x028b<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B6_VSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x028c<<2)))&BitMask_12)
#define B6_VSPw(val)			_wr32(_REG_BASE_+(0x028c<<2),(UINT)((_rd32(_REG_BASE_+(0x028c<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B6_VEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x028c<<2)))&BitMask_12)
#define B6_VEDw(val)			_wr32(_REG_BASE_+(0x028c<<2),(UINT)((_rd32(_REG_BASE_+(0x028c<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B6_HSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x028d<<2)))&BitMask_12)
#define B6_HSPw(val)			_wr32(_REG_BASE_+(0x028d<<2),(UINT)((_rd32(_REG_BASE_+(0x028d<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B6_HEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x028d<<2)))&BitMask_12)
#define B6_HEDw(val)			_wr32(_REG_BASE_+(0x028d<<2),(UINT)((_rd32(_REG_BASE_+(0x028d<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B7_VSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x028e<<2)))&BitMask_12)
#define B7_VSPw(val)			_wr32(_REG_BASE_+(0x028e<<2),(UINT)((_rd32(_REG_BASE_+(0x028e<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B7_VEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x028e<<2)))&BitMask_12)
#define B7_VEDw(val)			_wr32(_REG_BASE_+(0x028e<<2),(UINT)((_rd32(_REG_BASE_+(0x028e<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B7_HSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x028f<<2)))&BitMask_12)
#define B7_HSPw(val)			_wr32(_REG_BASE_+(0x028f<<2),(UINT)((_rd32(_REG_BASE_+(0x028f<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B7_HEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x028f<<2)))&BitMask_12)
#define B7_HEDw(val)			_wr32(_REG_BASE_+(0x028f<<2),(UINT)((_rd32(_REG_BASE_+(0x028f<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B8_VSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x0290<<2)))&BitMask_12)
#define B8_VSPw(val)			_wr32(_REG_BASE_+(0x0290<<2),(UINT)((_rd32(_REG_BASE_+(0x0290<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B8_VEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x0290<<2)))&BitMask_12)
#define B8_VEDw(val)			_wr32(_REG_BASE_+(0x0290<<2),(UINT)((_rd32(_REG_BASE_+(0x0290<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B8_HSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x0291<<2)))&BitMask_12)
#define B8_HSPw(val)			_wr32(_REG_BASE_+(0x0291<<2),(UINT)((_rd32(_REG_BASE_+(0x0291<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B8_HEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x0291<<2)))&BitMask_12)
#define B8_HEDw(val)			_wr32(_REG_BASE_+(0x0291<<2),(UINT)((_rd32(_REG_BASE_+(0x0291<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B9_VSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x0292<<2)))&BitMask_12)
#define B9_VSPw(val)			_wr32(_REG_BASE_+(0x0292<<2),(UINT)((_rd32(_REG_BASE_+(0x0292<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B9_VEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x0292<<2)))&BitMask_12)
#define B9_VEDw(val)			_wr32(_REG_BASE_+(0x0292<<2),(UINT)((_rd32(_REG_BASE_+(0x0292<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B9_HSPr					(ValSft_R16(_rd32(_REG_BASE_+(0x0293<<2)))&BitMask_12)
#define B9_HSPw(val)			_wr32(_REG_BASE_+(0x0293<<2),(UINT)((_rd32(_REG_BASE_+(0x0293<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B9_HEDr					(ValSft_R00(_rd32(_REG_BASE_+(0x0293<<2)))&BitMask_12)
#define B9_HEDw(val)			_wr32(_REG_BASE_+(0x0293<<2),(UINT)((_rd32(_REG_BASE_+(0x0293<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B10_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x0294<<2)))&BitMask_12)
#define B10_VSPw(val)			_wr32(_REG_BASE_+(0x0294<<2),(UINT)((_rd32(_REG_BASE_+(0x0294<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B10_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x0294<<2)))&BitMask_12)
#define B10_VEDw(val)			_wr32(_REG_BASE_+(0x0294<<2),(UINT)((_rd32(_REG_BASE_+(0x0294<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B10_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x0295<<2)))&BitMask_12)
#define B10_HSPw(val)			_wr32(_REG_BASE_+(0x0295<<2),(UINT)((_rd32(_REG_BASE_+(0x0295<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B10_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x0295<<2)))&BitMask_12)
#define B10_HEDw(val)			_wr32(_REG_BASE_+(0x0295<<2),(UINT)((_rd32(_REG_BASE_+(0x0295<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B11_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x0296<<2)))&BitMask_12)
#define B11_VSPw(val)			_wr32(_REG_BASE_+(0x0296<<2),(UINT)((_rd32(_REG_BASE_+(0x0296<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B11_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x0296<<2)))&BitMask_12)
#define B11_VEDw(val)			_wr32(_REG_BASE_+(0x0296<<2),(UINT)((_rd32(_REG_BASE_+(0x0296<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B11_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x0297<<2)))&BitMask_12)
#define B11_HSPw(val)			_wr32(_REG_BASE_+(0x0297<<2),(UINT)((_rd32(_REG_BASE_+(0x0297<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B11_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x0297<<2)))&BitMask_12)
#define B11_HEDw(val)			_wr32(_REG_BASE_+(0x0297<<2),(UINT)((_rd32(_REG_BASE_+(0x0297<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B12_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x0298<<2)))&BitMask_12)
#define B12_VSPw(val)			_wr32(_REG_BASE_+(0x0298<<2),(UINT)((_rd32(_REG_BASE_+(0x0298<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B12_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x0298<<2)))&BitMask_12)
#define B12_VEDw(val)			_wr32(_REG_BASE_+(0x0298<<2),(UINT)((_rd32(_REG_BASE_+(0x0298<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B12_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x0299<<2)))&BitMask_12)
#define B12_HSPw(val)			_wr32(_REG_BASE_+(0x0299<<2),(UINT)((_rd32(_REG_BASE_+(0x0299<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B12_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x0299<<2)))&BitMask_12)
#define B12_HEDw(val)			_wr32(_REG_BASE_+(0x0299<<2),(UINT)((_rd32(_REG_BASE_+(0x0299<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B13_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x029a<<2)))&BitMask_12)
#define B13_VSPw(val)			_wr32(_REG_BASE_+(0x029a<<2),(UINT)((_rd32(_REG_BASE_+(0x029a<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B13_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x029a<<2)))&BitMask_12)
#define B13_VEDw(val)			_wr32(_REG_BASE_+(0x029a<<2),(UINT)((_rd32(_REG_BASE_+(0x029a<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B13_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x029b<<2)))&BitMask_12)
#define B13_HSPw(val)			_wr32(_REG_BASE_+(0x029b<<2),(UINT)((_rd32(_REG_BASE_+(0x029b<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B13_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x029b<<2)))&BitMask_12)
#define B13_HEDw(val)			_wr32(_REG_BASE_+(0x029b<<2),(UINT)((_rd32(_REG_BASE_+(0x029b<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B14_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x029c<<2)))&BitMask_12)
#define B14_VSPw(val)			_wr32(_REG_BASE_+(0x029c<<2),(UINT)((_rd32(_REG_BASE_+(0x029c<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B14_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x029c<<2)))&BitMask_12)
#define B14_VEDw(val)			_wr32(_REG_BASE_+(0x029c<<2),(UINT)((_rd32(_REG_BASE_+(0x029c<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B14_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x029d<<2)))&BitMask_12)
#define B14_HSPw(val)			_wr32(_REG_BASE_+(0x029d<<2),(UINT)((_rd32(_REG_BASE_+(0x029d<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B14_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x029d<<2)))&BitMask_12)
#define B14_HEDw(val)			_wr32(_REG_BASE_+(0x029d<<2),(UINT)((_rd32(_REG_BASE_+(0x029d<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B15_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x029e<<2)))&BitMask_12)
#define B15_VSPw(val)			_wr32(_REG_BASE_+(0x029e<<2),(UINT)((_rd32(_REG_BASE_+(0x029e<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B15_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x029e<<2)))&BitMask_12)
#define B15_VEDw(val)			_wr32(_REG_BASE_+(0x029e<<2),(UINT)((_rd32(_REG_BASE_+(0x029e<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B15_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x029f<<2)))&BitMask_12)
#define B15_HSPw(val)			_wr32(_REG_BASE_+(0x029f<<2),(UINT)((_rd32(_REG_BASE_+(0x029f<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B15_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x029f<<2)))&BitMask_12)
#define B15_HEDw(val)			_wr32(_REG_BASE_+(0x029f<<2),(UINT)((_rd32(_REG_BASE_+(0x029f<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B16_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02a0<<2)))&BitMask_12)
#define B16_VSPw(val)			_wr32(_REG_BASE_+(0x02a0<<2),(UINT)((_rd32(_REG_BASE_+(0x02a0<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B16_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02a0<<2)))&BitMask_12)
#define B16_VEDw(val)			_wr32(_REG_BASE_+(0x02a0<<2),(UINT)((_rd32(_REG_BASE_+(0x02a0<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B16_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02a1<<2)))&BitMask_12)
#define B16_HSPw(val)			_wr32(_REG_BASE_+(0x02a1<<2),(UINT)((_rd32(_REG_BASE_+(0x02a1<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B16_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02a1<<2)))&BitMask_12)
#define B16_HEDw(val)			_wr32(_REG_BASE_+(0x02a1<<2),(UINT)((_rd32(_REG_BASE_+(0x02a1<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B17_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02a2<<2)))&BitMask_12)
#define B17_VSPw(val)			_wr32(_REG_BASE_+(0x02a2<<2),(UINT)((_rd32(_REG_BASE_+(0x02a2<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B17_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02a2<<2)))&BitMask_12)
#define B17_VEDw(val)			_wr32(_REG_BASE_+(0x02a2<<2),(UINT)((_rd32(_REG_BASE_+(0x02a2<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B17_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02a3<<2)))&BitMask_12)
#define B17_HSPw(val)			_wr32(_REG_BASE_+(0x02a3<<2),(UINT)((_rd32(_REG_BASE_+(0x02a3<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B17_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02a3<<2)))&BitMask_12)
#define B17_HEDw(val)			_wr32(_REG_BASE_+(0x02a3<<2),(UINT)((_rd32(_REG_BASE_+(0x02a3<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B18_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02a4<<2)))&BitMask_12)
#define B18_VSPw(val)			_wr32(_REG_BASE_+(0x02a4<<2),(UINT)((_rd32(_REG_BASE_+(0x02a4<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B18_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02a4<<2)))&BitMask_12)
#define B18_VEDw(val)			_wr32(_REG_BASE_+(0x02a4<<2),(UINT)((_rd32(_REG_BASE_+(0x02a4<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B18_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02a5<<2)))&BitMask_12)
#define B18_HSPw(val)			_wr32(_REG_BASE_+(0x02a5<<2),(UINT)((_rd32(_REG_BASE_+(0x02a5<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B18_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02a5<<2)))&BitMask_12)
#define B18_HEDw(val)			_wr32(_REG_BASE_+(0x02a5<<2),(UINT)((_rd32(_REG_BASE_+(0x02a5<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B19_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02a6<<2)))&BitMask_12)
#define B19_VSPw(val)			_wr32(_REG_BASE_+(0x02a6<<2),(UINT)((_rd32(_REG_BASE_+(0x02a6<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B19_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02a6<<2)))&BitMask_12)
#define B19_VEDw(val)			_wr32(_REG_BASE_+(0x02a6<<2),(UINT)((_rd32(_REG_BASE_+(0x02a6<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B19_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02a7<<2)))&BitMask_12)
#define B19_HSPw(val)			_wr32(_REG_BASE_+(0x02a7<<2),(UINT)((_rd32(_REG_BASE_+(0x02a7<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B19_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02a7<<2)))&BitMask_12)
#define B19_HEDw(val)			_wr32(_REG_BASE_+(0x02a7<<2),(UINT)((_rd32(_REG_BASE_+(0x02a7<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B20_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02a8<<2)))&BitMask_12)
#define B20_VSPw(val)			_wr32(_REG_BASE_+(0x02a8<<2),(UINT)((_rd32(_REG_BASE_+(0x02a8<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B20_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02a8<<2)))&BitMask_12)
#define B20_VEDw(val)			_wr32(_REG_BASE_+(0x02a8<<2),(UINT)((_rd32(_REG_BASE_+(0x02a8<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B20_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02a9<<2)))&BitMask_12)
#define B20_HSPw(val)			_wr32(_REG_BASE_+(0x02a9<<2),(UINT)((_rd32(_REG_BASE_+(0x02a9<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B20_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02a9<<2)))&BitMask_12)
#define B20_HEDw(val)			_wr32(_REG_BASE_+(0x02a9<<2),(UINT)((_rd32(_REG_BASE_+(0x02a9<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B21_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02aa<<2)))&BitMask_12)
#define B21_VSPw(val)			_wr32(_REG_BASE_+(0x02aa<<2),(UINT)((_rd32(_REG_BASE_+(0x02aa<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B21_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02aa<<2)))&BitMask_12)
#define B21_VEDw(val)			_wr32(_REG_BASE_+(0x02aa<<2),(UINT)((_rd32(_REG_BASE_+(0x02aa<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B21_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02ab<<2)))&BitMask_12)
#define B21_HSPw(val)			_wr32(_REG_BASE_+(0x02ab<<2),(UINT)((_rd32(_REG_BASE_+(0x02ab<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B21_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02ab<<2)))&BitMask_12)
#define B21_HEDw(val)			_wr32(_REG_BASE_+(0x02ab<<2),(UINT)((_rd32(_REG_BASE_+(0x02ab<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B22_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02ac<<2)))&BitMask_12)
#define B22_VSPw(val)			_wr32(_REG_BASE_+(0x02ac<<2),(UINT)((_rd32(_REG_BASE_+(0x02ac<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B22_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02ac<<2)))&BitMask_12)
#define B22_VEDw(val)			_wr32(_REG_BASE_+(0x02ac<<2),(UINT)((_rd32(_REG_BASE_+(0x02ac<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B22_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02ad<<2)))&BitMask_12)
#define B22_HSPw(val)			_wr32(_REG_BASE_+(0x02ad<<2),(UINT)((_rd32(_REG_BASE_+(0x02ad<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B22_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02ad<<2)))&BitMask_12)
#define B22_HEDw(val)			_wr32(_REG_BASE_+(0x02ad<<2),(UINT)((_rd32(_REG_BASE_+(0x02ad<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B23_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02ae<<2)))&BitMask_12)
#define B23_VSPw(val)			_wr32(_REG_BASE_+(0x02ae<<2),(UINT)((_rd32(_REG_BASE_+(0x02ae<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B23_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02ae<<2)))&BitMask_12)
#define B23_VEDw(val)			_wr32(_REG_BASE_+(0x02ae<<2),(UINT)((_rd32(_REG_BASE_+(0x02ae<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B23_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02af<<2)))&BitMask_12)
#define B23_HSPw(val)			_wr32(_REG_BASE_+(0x02af<<2),(UINT)((_rd32(_REG_BASE_+(0x02af<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B23_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02af<<2)))&BitMask_12)
#define B23_HEDw(val)			_wr32(_REG_BASE_+(0x02af<<2),(UINT)((_rd32(_REG_BASE_+(0x02af<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B24_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02b0<<2)))&BitMask_12)
#define B24_VSPw(val)			_wr32(_REG_BASE_+(0x02b0<<2),(UINT)((_rd32(_REG_BASE_+(0x02b0<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B24_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02b0<<2)))&BitMask_12)
#define B24_VEDw(val)			_wr32(_REG_BASE_+(0x02b0<<2),(UINT)((_rd32(_REG_BASE_+(0x02b0<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B24_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02b1<<2)))&BitMask_12)
#define B24_HSPw(val)			_wr32(_REG_BASE_+(0x02b1<<2),(UINT)((_rd32(_REG_BASE_+(0x02b1<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B24_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02b1<<2)))&BitMask_12)
#define B24_HEDw(val)			_wr32(_REG_BASE_+(0x02b1<<2),(UINT)((_rd32(_REG_BASE_+(0x02b1<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B25_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02b2<<2)))&BitMask_12)
#define B25_VSPw(val)			_wr32(_REG_BASE_+(0x02b2<<2),(UINT)((_rd32(_REG_BASE_+(0x02b2<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B25_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02b2<<2)))&BitMask_12)
#define B25_VEDw(val)			_wr32(_REG_BASE_+(0x02b2<<2),(UINT)((_rd32(_REG_BASE_+(0x02b2<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B25_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02b3<<2)))&BitMask_12)
#define B25_HSPw(val)			_wr32(_REG_BASE_+(0x02b3<<2),(UINT)((_rd32(_REG_BASE_+(0x02b3<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B25_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02b3<<2)))&BitMask_12)
#define B25_HEDw(val)			_wr32(_REG_BASE_+(0x02b3<<2),(UINT)((_rd32(_REG_BASE_+(0x02b3<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B26_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02b4<<2)))&BitMask_12)
#define B26_VSPw(val)			_wr32(_REG_BASE_+(0x02b4<<2),(UINT)((_rd32(_REG_BASE_+(0x02b4<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B26_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02b4<<2)))&BitMask_12)
#define B26_VEDw(val)			_wr32(_REG_BASE_+(0x02b4<<2),(UINT)((_rd32(_REG_BASE_+(0x02b4<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B26_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02b5<<2)))&BitMask_12)
#define B26_HSPw(val)			_wr32(_REG_BASE_+(0x02b5<<2),(UINT)((_rd32(_REG_BASE_+(0x02b5<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B26_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02b5<<2)))&BitMask_12)
#define B26_HEDw(val)			_wr32(_REG_BASE_+(0x02b5<<2),(UINT)((_rd32(_REG_BASE_+(0x02b5<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B27_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02b6<<2)))&BitMask_12)
#define B27_VSPw(val)			_wr32(_REG_BASE_+(0x02b6<<2),(UINT)((_rd32(_REG_BASE_+(0x02b6<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B27_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02b6<<2)))&BitMask_12)
#define B27_VEDw(val)			_wr32(_REG_BASE_+(0x02b6<<2),(UINT)((_rd32(_REG_BASE_+(0x02b6<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B27_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02b7<<2)))&BitMask_12)
#define B27_HSPw(val)			_wr32(_REG_BASE_+(0x02b7<<2),(UINT)((_rd32(_REG_BASE_+(0x02b7<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B27_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02b7<<2)))&BitMask_12)
#define B27_HEDw(val)			_wr32(_REG_BASE_+(0x02b7<<2),(UINT)((_rd32(_REG_BASE_+(0x02b7<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B28_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02b8<<2)))&BitMask_12)
#define B28_VSPw(val)			_wr32(_REG_BASE_+(0x02b8<<2),(UINT)((_rd32(_REG_BASE_+(0x02b8<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B28_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02b8<<2)))&BitMask_12)
#define B28_VEDw(val)			_wr32(_REG_BASE_+(0x02b8<<2),(UINT)((_rd32(_REG_BASE_+(0x02b8<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B28_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02b9<<2)))&BitMask_12)
#define B28_HSPw(val)			_wr32(_REG_BASE_+(0x02b9<<2),(UINT)((_rd32(_REG_BASE_+(0x02b9<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B28_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02b9<<2)))&BitMask_12)
#define B28_HEDw(val)			_wr32(_REG_BASE_+(0x02b9<<2),(UINT)((_rd32(_REG_BASE_+(0x02b9<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B29_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02ba<<2)))&BitMask_12)
#define B29_VSPw(val)			_wr32(_REG_BASE_+(0x02ba<<2),(UINT)((_rd32(_REG_BASE_+(0x02ba<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B29_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02ba<<2)))&BitMask_12)
#define B29_VEDw(val)			_wr32(_REG_BASE_+(0x02ba<<2),(UINT)((_rd32(_REG_BASE_+(0x02ba<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B29_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02bb<<2)))&BitMask_12)
#define B29_HSPw(val)			_wr32(_REG_BASE_+(0x02bb<<2),(UINT)((_rd32(_REG_BASE_+(0x02bb<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B29_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02bb<<2)))&BitMask_12)
#define B29_HEDw(val)			_wr32(_REG_BASE_+(0x02bb<<2),(UINT)((_rd32(_REG_BASE_+(0x02bb<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B30_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02bc<<2)))&BitMask_12)
#define B30_VSPw(val)			_wr32(_REG_BASE_+(0x02bc<<2),(UINT)((_rd32(_REG_BASE_+(0x02bc<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B30_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02bc<<2)))&BitMask_12)
#define B30_VEDw(val)			_wr32(_REG_BASE_+(0x02bc<<2),(UINT)((_rd32(_REG_BASE_+(0x02bc<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B30_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02bd<<2)))&BitMask_12)
#define B30_HSPw(val)			_wr32(_REG_BASE_+(0x02bd<<2),(UINT)((_rd32(_REG_BASE_+(0x02bd<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B30_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02bd<<2)))&BitMask_12)
#define B30_HEDw(val)			_wr32(_REG_BASE_+(0x02bd<<2),(UINT)((_rd32(_REG_BASE_+(0x02bd<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B31_VSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02be<<2)))&BitMask_12)
#define B31_VSPw(val)			_wr32(_REG_BASE_+(0x02be<<2),(UINT)((_rd32(_REG_BASE_+(0x02be<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B31_VEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02be<<2)))&BitMask_12)
#define B31_VEDw(val)			_wr32(_REG_BASE_+(0x02be<<2),(UINT)((_rd32(_REG_BASE_+(0x02be<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define B31_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02bf<<2)))&BitMask_12)
#define B31_HSPw(val)			_wr32(_REG_BASE_+(0x02bf<<2),(UINT)((_rd32(_REG_BASE_+(0x02bf<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define B31_HEDr				(ValSft_R00(_rd32(_REG_BASE_+(0x02bf<<2)))&BitMask_12)
#define B31_HEDw(val)			_wr32(_REG_BASE_+(0x02bf<<2),(UINT)((_rd32(_REG_BASE_+(0x02bf<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define BOX0_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02c0<<2)))&BitMask_24)
#define BOX0_PLTw(val)			_wr32(_REG_BASE_+(0x02c0<<2),(UINT)((_rd32(_REG_BASE_+(0x02c0<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX1_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02c1<<2)))&BitMask_24)
#define BOX1_PLTw(val)			_wr32(_REG_BASE_+(0x02c1<<2),(UINT)((_rd32(_REG_BASE_+(0x02c1<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX2_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02c2<<2)))&BitMask_24)
#define BOX2_PLTw(val)			_wr32(_REG_BASE_+(0x02c2<<2),(UINT)((_rd32(_REG_BASE_+(0x02c2<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX3_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02c3<<2)))&BitMask_24)
#define BOX3_PLTw(val)			_wr32(_REG_BASE_+(0x02c3<<2),(UINT)((_rd32(_REG_BASE_+(0x02c3<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX4_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02c4<<2)))&BitMask_24)
#define BOX4_PLTw(val)			_wr32(_REG_BASE_+(0x02c4<<2),(UINT)((_rd32(_REG_BASE_+(0x02c4<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX5_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02c5<<2)))&BitMask_24)
#define BOX5_PLTw(val)			_wr32(_REG_BASE_+(0x02c5<<2),(UINT)((_rd32(_REG_BASE_+(0x02c5<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX6_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02c6<<2)))&BitMask_24)
#define BOX6_PLTw(val)			_wr32(_REG_BASE_+(0x02c6<<2),(UINT)((_rd32(_REG_BASE_+(0x02c6<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX7_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02c7<<2)))&BitMask_24)
#define BOX7_PLTw(val)			_wr32(_REG_BASE_+(0x02c7<<2),(UINT)((_rd32(_REG_BASE_+(0x02c7<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX8_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02c8<<2)))&BitMask_24)
#define BOX8_PLTw(val)			_wr32(_REG_BASE_+(0x02c8<<2),(UINT)((_rd32(_REG_BASE_+(0x02c8<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX9_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02c9<<2)))&BitMask_24)
#define BOX9_PLTw(val)			_wr32(_REG_BASE_+(0x02c9<<2),(UINT)((_rd32(_REG_BASE_+(0x02c9<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX10_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02ca<<2)))&BitMask_24)
#define BOX10_PLTw(val)			_wr32(_REG_BASE_+(0x02ca<<2),(UINT)((_rd32(_REG_BASE_+(0x02ca<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX11_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02cb<<2)))&BitMask_24)
#define BOX11_PLTw(val)			_wr32(_REG_BASE_+(0x02cb<<2),(UINT)((_rd32(_REG_BASE_+(0x02cb<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX12_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02cc<<2)))&BitMask_24)
#define BOX12_PLTw(val)			_wr32(_REG_BASE_+(0x02cc<<2),(UINT)((_rd32(_REG_BASE_+(0x02cc<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX13_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02cd<<2)))&BitMask_24)
#define BOX13_PLTw(val)			_wr32(_REG_BASE_+(0x02cd<<2),(UINT)((_rd32(_REG_BASE_+(0x02cd<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX14_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02ce<<2)))&BitMask_24)
#define BOX14_PLTw(val)			_wr32(_REG_BASE_+(0x02ce<<2),(UINT)((_rd32(_REG_BASE_+(0x02ce<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX15_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02cf<<2)))&BitMask_24)
#define BOX15_PLTw(val)			_wr32(_REG_BASE_+(0x02cf<<2),(UINT)((_rd32(_REG_BASE_+(0x02cf<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX16_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02d0<<2)))&BitMask_24)
#define BOX16_PLTw(val)			_wr32(_REG_BASE_+(0x02d0<<2),(UINT)((_rd32(_REG_BASE_+(0x02d0<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX17_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02d1<<2)))&BitMask_24)
#define BOX17_PLTw(val)			_wr32(_REG_BASE_+(0x02d1<<2),(UINT)((_rd32(_REG_BASE_+(0x02d1<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX18_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02d2<<2)))&BitMask_24)
#define BOX18_PLTw(val)			_wr32(_REG_BASE_+(0x02d2<<2),(UINT)((_rd32(_REG_BASE_+(0x02d2<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX19_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02d3<<2)))&BitMask_24)
#define BOX19_PLTw(val)			_wr32(_REG_BASE_+(0x02d3<<2),(UINT)((_rd32(_REG_BASE_+(0x02d3<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX20_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02d4<<2)))&BitMask_24)
#define BOX20_PLTw(val)			_wr32(_REG_BASE_+(0x02d4<<2),(UINT)((_rd32(_REG_BASE_+(0x02d4<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX21_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02d5<<2)))&BitMask_24)
#define BOX21_PLTw(val)			_wr32(_REG_BASE_+(0x02d5<<2),(UINT)((_rd32(_REG_BASE_+(0x02d5<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX22_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02d6<<2)))&BitMask_24)
#define BOX22_PLTw(val)			_wr32(_REG_BASE_+(0x02d6<<2),(UINT)((_rd32(_REG_BASE_+(0x02d6<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX23_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02d7<<2)))&BitMask_24)
#define BOX23_PLTw(val)			_wr32(_REG_BASE_+(0x02d7<<2),(UINT)((_rd32(_REG_BASE_+(0x02d7<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX24_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02d8<<2)))&BitMask_24)
#define BOX24_PLTw(val)			_wr32(_REG_BASE_+(0x02d8<<2),(UINT)((_rd32(_REG_BASE_+(0x02d8<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX25_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02d9<<2)))&BitMask_24)
#define BOX25_PLTw(val)			_wr32(_REG_BASE_+(0x02d9<<2),(UINT)((_rd32(_REG_BASE_+(0x02d9<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX26_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02da<<2)))&BitMask_24)
#define BOX26_PLTw(val)			_wr32(_REG_BASE_+(0x02da<<2),(UINT)((_rd32(_REG_BASE_+(0x02da<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX27_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02db<<2)))&BitMask_24)
#define BOX27_PLTw(val)			_wr32(_REG_BASE_+(0x02db<<2),(UINT)((_rd32(_REG_BASE_+(0x02db<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX28_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02dc<<2)))&BitMask_24)
#define BOX28_PLTw(val)			_wr32(_REG_BASE_+(0x02dc<<2),(UINT)((_rd32(_REG_BASE_+(0x02dc<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX29_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02dd<<2)))&BitMask_24)
#define BOX29_PLTw(val)			_wr32(_REG_BASE_+(0x02dd<<2),(UINT)((_rd32(_REG_BASE_+(0x02dd<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX30_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02de<<2)))&BitMask_24)
#define BOX30_PLTw(val)			_wr32(_REG_BASE_+(0x02de<<2),(UINT)((_rd32(_REG_BASE_+(0x02de<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define BOX31_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02df<<2)))&BitMask_24)
#define BOX31_PLTw(val)			_wr32(_REG_BASE_+(0x02df<<2),(UINT)((_rd32(_REG_BASE_+(0x02df<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define LINE0_ONr				(ValSft_R31(_rd32(_REG_BASE_+(0x02e0<<2)))&BitMask_01)
#define LINE0_ONw(val)			_wr32(_REG_BASE_+(0x02e0<<2),(UINT)((_rd32(_REG_BASE_+(0x02e0<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define LINE1_ONr				(ValSft_R30(_rd32(_REG_BASE_+(0x02e0<<2)))&BitMask_01)
#define LINE1_ONw(val)			_wr32(_REG_BASE_+(0x02e0<<2),(UINT)((_rd32(_REG_BASE_+(0x02e0<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define LINE2_ONr				(ValSft_R29(_rd32(_REG_BASE_+(0x02e0<<2)))&BitMask_01)
#define LINE2_ONw(val)			_wr32(_REG_BASE_+(0x02e0<<2),(UINT)((_rd32(_REG_BASE_+(0x02e0<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define LINE_HSPr				(ValSft_R16(_rd32(_REG_BASE_+(0x02e0<<2)))&BitMask_13)
#define LINE_HSPw(val)			_wr32(_REG_BASE_+(0x02e0<<2),(UINT)((_rd32(_REG_BASE_+(0x02e0<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define LINE_HBORDr				(ValSft_R25(_rd32(_REG_BASE_+(0x02e1<<2)))&BitMask_05)
#define LINE_HBORDw(val)		_wr32(_REG_BASE_+(0x02e1<<2),(UINT)((_rd32(_REG_BASE_+(0x02e1<<2))&(~ValSft_L25(BitMask_05)))|ValSft_L25((val)&BitMask_05)))

#define LINE_VBORDr				(ValSft_R20(_rd32(_REG_BASE_+(0x02e1<<2)))&BitMask_05)
#define LINE_VBORDw(val)		_wr32(_REG_BASE_+(0x02e1<<2),(UINT)((_rd32(_REG_BASE_+(0x02e1<<2))&(~ValSft_L20(BitMask_05)))|ValSft_L20((val)&BitMask_05)))

#define LINE0_GRADLr			(ValSft_R10(_rd32(_REG_BASE_+(0x02e1<<2)))&BitMask_10)
#define LINE0_GRADLw(val)		_wr32(_REG_BASE_+(0x02e1<<2),(UINT)((_rd32(_REG_BASE_+(0x02e1<<2))&(~ValSft_L10(BitMask_10)))|ValSft_L10((val)&BitMask_10)))

#define LINE0_GRADRr			(ValSft_R00(_rd32(_REG_BASE_+(0x02e1<<2)))&BitMask_10)
#define LINE0_GRADRw(val)		_wr32(_REG_BASE_+(0x02e1<<2),(UINT)((_rd32(_REG_BASE_+(0x02e1<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LINE0_STAXr				(ValSft_R16(_rd32(_REG_BASE_+(0x02e2<<2)))&BitMask_13)
#define LINE0_STAXw(val)		_wr32(_REG_BASE_+(0x02e2<<2),(UINT)((_rd32(_REG_BASE_+(0x02e2<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define LINE0_HWIDTHr			(ValSft_R00(_rd32(_REG_BASE_+(0x02e2<<2)))&BitMask_13)
#define LINE0_HWIDTHw(val)		_wr32(_REG_BASE_+(0x02e2<<2),(UINT)((_rd32(_REG_BASE_+(0x02e2<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define LINE0_STAYr				(ValSft_R16(_rd32(_REG_BASE_+(0x02e3<<2)))&BitMask_12)
#define LINE0_STAYw(val)		_wr32(_REG_BASE_+(0x02e3<<2),(UINT)((_rd32(_REG_BASE_+(0x02e3<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define LINE0_ENDYr				(ValSft_R00(_rd32(_REG_BASE_+(0x02e3<<2)))&BitMask_12)
#define LINE0_ENDYw(val)		_wr32(_REG_BASE_+(0x02e3<<2),(UINT)((_rd32(_REG_BASE_+(0x02e3<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define LINE1_Yr				(ValSft_R16(_rd32(_REG_BASE_+(0x02e4<<2)))&BitMask_12)
#define LINE1_Yw(val)			_wr32(_REG_BASE_+(0x02e4<<2),(UINT)((_rd32(_REG_BASE_+(0x02e4<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define LINE2_Yr				(ValSft_R00(_rd32(_REG_BASE_+(0x02e4<<2)))&BitMask_12)
#define LINE2_Yw(val)			_wr32(_REG_BASE_+(0x02e4<<2),(UINT)((_rd32(_REG_BASE_+(0x02e4<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define LINE0_TONEr				(ValSft_R30(_rd32(_REG_BASE_+(0x02e5<<2)))&BitMask_02)
#define LINE0_TONEw(val)		_wr32(_REG_BASE_+(0x02e5<<2),(UINT)((_rd32(_REG_BASE_+(0x02e5<<2))&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define LINE0_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02e5<<2)))&BitMask_24)
#define LINE0_PLTw(val)			_wr32(_REG_BASE_+(0x02e5<<2),(UINT)((_rd32(_REG_BASE_+(0x02e5<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define LINE1_TONEr				(ValSft_R30(_rd32(_REG_BASE_+(0x02e6<<2)))&BitMask_02)
#define LINE1_TONEw(val)		_wr32(_REG_BASE_+(0x02e6<<2),(UINT)((_rd32(_REG_BASE_+(0x02e6<<2))&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define LINE1_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02e6<<2)))&BitMask_24)
#define LINE1_PLTw(val)			_wr32(_REG_BASE_+(0x02e6<<2),(UINT)((_rd32(_REG_BASE_+(0x02e6<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define LINE2_TONEr				(ValSft_R30(_rd32(_REG_BASE_+(0x02e7<<2)))&BitMask_02)
#define LINE2_TONEw(val)		_wr32(_REG_BASE_+(0x02e7<<2),(UINT)((_rd32(_REG_BASE_+(0x02e7<<2))&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define LINE2_PLTr				(ValSft_R00(_rd32(_REG_BASE_+(0x02e7<<2)))&BitMask_24)
#define LINE2_PLTw(val)			_wr32(_REG_BASE_+(0x02e7<<2),(UINT)((_rd32(_REG_BASE_+(0x02e7<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define LSPI_ONr				(ValSft_R31(_rd32(_REG_BASE_+(0x0380<<2)))&BitMask_01)
#define LSPI_ONw(val)			_wr32(_REG_BASE_+(0x0380<<2),(UINT)((_rd32(_REG_BASE_+(0x0380<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define IRIS2_MUXr				(ValSft_R29(_rd32(_REG_BASE_+(0x0380<<2)))&BitMask_01)
#define IRIS2_MUXw(val)			_wr32(_REG_BASE_+(0x0380<<2),(UINT)((_rd32(_REG_BASE_+(0x0380<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define R_I2C0_ONr				(ValSft_R28(_rd32(_REG_BASE_+(0x0380<<2)))&BitMask_01)
#define R_I2C0_ONw(val)			_wr32(_REG_BASE_+(0x0380<<2),(UINT)((_rd32(_REG_BASE_+(0x0380<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define R_I2C1_ONr				(ValSft_R26(_rd32(_REG_BASE_+(0x0380<<2)))&BitMask_02)
#define R_I2C1_ONw(val)			_wr32(_REG_BASE_+(0x0380<<2),(UINT)((_rd32(_REG_BASE_+(0x0380<<2))&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define R_URT0_ONr				(ValSft_R24(_rd32(_REG_BASE_+(0x0380<<2)))&BitMask_02)
#define R_URT0_ONw(val)			_wr32(_REG_BASE_+(0x0380<<2),(UINT)((_rd32(_REG_BASE_+(0x0380<<2))&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define R_URT1_ONr				(ValSft_R22(_rd32(_REG_BASE_+(0x0380<<2)))&BitMask_02)
#define R_URT1_ONw(val)			_wr32(_REG_BASE_+(0x0380<<2),(UINT)((_rd32(_REG_BASE_+(0x0380<<2))&(~ValSft_L22(BitMask_02)))|ValSft_L22((val)&BitMask_02)))

#define R_PWM_ONr				(ValSft_R16(_rd32(_REG_BASE_+(0x0380<<2)))&BitMask_06)
#define R_PWM_ONw(val)			_wr32(_REG_BASE_+(0x0380<<2),(UINT)((_rd32(_REG_BASE_+(0x0380<<2))&(~ValSft_L16(BitMask_06)))|ValSft_L16((val)&BitMask_06)))

#define R_SPI_ONr				(ValSft_R15(_rd32(_REG_BASE_+(0x0380<<2)))&BitMask_01)
#define R_SPI_ONw(val)			_wr32(_REG_BASE_+(0x0380<<2),(UINT)((_rd32(_REG_BASE_+(0x0380<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define MTX_ONr					(ValSft_R14(_rd32(_REG_BASE_+(0x0380<<2)))&BitMask_01)
#define MTX_ONw(val)			_wr32(_REG_BASE_+(0x0380<<2),(UINT)((_rd32(_REG_BASE_+(0x0380<<2))&(~ValSft_L14(BitMask_01)))|ValSft_L14((val)&BitMask_01)))

#define DUCC_MUXr				(ValSft_R12(_rd32(_REG_BASE_+(0x0380<<2)))&BitMask_02)
#define DUCC_MUXw(val)			_wr32(_REG_BASE_+(0x0380<<2),(UINT)((_rd32(_REG_BASE_+(0x0380<<2))&(~ValSft_L12(BitMask_02)))|ValSft_L12((val)&BitMask_02)))

#define UTC_ACT_MUXr			(ValSft_R11(_rd32(_REG_BASE_+(0x0380<<2)))&BitMask_01)
#define UTC_ACT_MUXw(val)		_wr32(_REG_BASE_+(0x0380<<2),(UINT)((_rd32(_REG_BASE_+(0x0380<<2))&(~ValSft_L11(BitMask_01)))|ValSft_L11((val)&BitMask_01)))

#define UTC_OUT_MUXr			(ValSft_R10(_rd32(_REG_BASE_+(0x0380<<2)))&BitMask_01)
#define UTC_OUT_MUXw(val)		_wr32(_REG_BASE_+(0x0380<<2),(UINT)((_rd32(_REG_BASE_+(0x0380<<2))&(~ValSft_L10(BitMask_01)))|ValSft_L10((val)&BitMask_01)))

#define STX_UCC_MUXr			(ValSft_R08(_rd32(_REG_BASE_+(0x0380<<2)))&BitMask_02)
#define STX_UCC_MUXw(val)		_wr32(_REG_BASE_+(0x0380<<2),(UINT)((_rd32(_REG_BASE_+(0x0380<<2))&(~ValSft_L08(BitMask_02)))|ValSft_L08((val)&BitMask_02)))

#define UCC_VT_MUXr				(ValSft_R07(_rd32(_REG_BASE_+(0x0380<<2)))&BitMask_01)
#define UCC_VT_MUXw(val)		_wr32(_REG_BASE_+(0x0380<<2),(UINT)((_rd32(_REG_BASE_+(0x0380<<2))&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

#define GPIO_CDRV1_INr			(ValSft_R00(_rd32(_REG_BASE_+(0x0381<<2)))&BitMask_20)
#define GPIO_CDRV1_INw(val)		_wr32(_REG_BASE_+(0x0381<<2),(UINT)((_rd32(_REG_BASE_+(0x0381<<2))&(~ValSft_L00(BitMask_20)))|ValSft_L00((val)&BitMask_20)))

#define GPIO_CDRV2_INr			(ValSft_R00(_rd32(_REG_BASE_+(0x0382<<2)))&BitMask_20)
#define GPIO_CDRV2_INw(val)		_wr32(_REG_BASE_+(0x0382<<2),(UINT)((_rd32(_REG_BASE_+(0x0382<<2))&(~ValSft_L00(BitMask_20)))|ValSft_L00((val)&BitMask_20)))

#define SFDQ0_CDRV_INr			(ValSft_R30(_rd32(_REG_BASE_+(0x0388<<2)))&BitMask_02)
#define SFDQ0_CDRV_INw(val)		_wr32(_REG_BASE_+(0x0388<<2),(UINT)((_rd32(_REG_BASE_+(0x0388<<2))&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define SFDQ1_CDRV_INr			(ValSft_R28(_rd32(_REG_BASE_+(0x0388<<2)))&BitMask_02)
#define SFDQ1_CDRV_INw(val)		_wr32(_REG_BASE_+(0x0388<<2),(UINT)((_rd32(_REG_BASE_+(0x0388<<2))&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define SFDQ2_CDRVr				(ValSft_R26(_rd32(_REG_BASE_+(0x0388<<2)))&BitMask_02)
#define SFDQ2_CDRVw(val)		_wr32(_REG_BASE_+(0x0388<<2),(UINT)((_rd32(_REG_BASE_+(0x0388<<2))&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define SFDQ3_CDRVr				(ValSft_R24(_rd32(_REG_BASE_+(0x0388<<2)))&BitMask_02)
#define SFDQ3_CDRVw(val)		_wr32(_REG_BASE_+(0x0388<<2),(UINT)((_rd32(_REG_BASE_+(0x0388<<2))&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define SFCSN_CDRV_INr			(ValSft_R22(_rd32(_REG_BASE_+(0x0388<<2)))&BitMask_02)
#define SFCSN_CDRV_INw(val)		_wr32(_REG_BASE_+(0x0388<<2),(UINT)((_rd32(_REG_BASE_+(0x0388<<2))&(~ValSft_L22(BitMask_02)))|ValSft_L22((val)&BitMask_02)))

#define SFCKO_CDRV_INr			(ValSft_R20(_rd32(_REG_BASE_+(0x0388<<2)))&BitMask_02)
#define SFCKO_CDRV_INw(val)		_wr32(_REG_BASE_+(0x0388<<2),(UINT)((_rd32(_REG_BASE_+(0x0388<<2))&(~ValSft_L20(BitMask_02)))|ValSft_L20((val)&BitMask_02)))

#define SFLS_DQDLY0r			(ValSft_R12(_rd32(_REG_BASE_+(0x0388<<2)))&BitMask_03)
#define SFLS_DQDLY0w(val)		_wr32(_REG_BASE_+(0x0388<<2),(UINT)((_rd32(_REG_BASE_+(0x0388<<2))&(~ValSft_L12(BitMask_03)))|ValSft_L12((val)&BitMask_03)))

#define SFLS_DQDLY1r			(ValSft_R08(_rd32(_REG_BASE_+(0x0388<<2)))&BitMask_03)
#define SFLS_DQDLY1w(val)		_wr32(_REG_BASE_+(0x0388<<2),(UINT)((_rd32(_REG_BASE_+(0x0388<<2))&(~ValSft_L08(BitMask_03)))|ValSft_L08((val)&BitMask_03)))

#define SFLS_DQDLY2r			(ValSft_R04(_rd32(_REG_BASE_+(0x0388<<2)))&BitMask_03)
#define SFLS_DQDLY2w(val)		_wr32(_REG_BASE_+(0x0388<<2),(UINT)((_rd32(_REG_BASE_+(0x0388<<2))&(~ValSft_L04(BitMask_03)))|ValSft_L04((val)&BitMask_03)))

#define SFLS_DQDLY3r			(ValSft_R00(_rd32(_REG_BASE_+(0x0388<<2)))&BitMask_03)
#define SFLS_DQDLY3w(val)		_wr32(_REG_BASE_+(0x0388<<2),(UINT)((_rd32(_REG_BASE_+(0x0388<<2))&(~ValSft_L00(BitMask_03)))|ValSft_L00((val)&BitMask_03)))

#define ADC_VLOCK_SELr			(ValSft_R31(_rd32(_REG_BASE_+(0x0390<<2)))&BitMask_01)
#define ADC_VLOCK_SELw(val)		_wr32(_REG_BASE_+(0x0390<<2),(UINT)((_rd32(_REG_BASE_+(0x0390<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define ADC_MASK_ENr			(ValSft_R20(_rd32(_REG_BASE_+(0x0390<<2)))&BitMask_01)
#define ADC_MASK_ENw(val)		_wr32(_REG_BASE_+(0x0390<<2),(UINT)((_rd32(_REG_BASE_+(0x0390<<2))&(~ValSft_L20(BitMask_01)))|ValSft_L20((val)&BitMask_01)))

#define ADC_MASK_ZERO_POINTr	(ValSft_R10(_rd32(_REG_BASE_+(0x0390<<2)))&BitMask_10)
#define ADC_MASK_ZERO_POINTw(val)	_wr32(_REG_BASE_+(0x0390<<2),(UINT)((_rd32(_REG_BASE_+(0x0390<<2))&(~ValSft_L10(BitMask_10)))|ValSft_L10((val)&BitMask_10)))

#define ADC_SAMPLE_STARTr		(ValSft_R00(_rd32(_REG_BASE_+(0x0390<<2)))&BitMask_10)
#define ADC_SAMPLE_STARTw(val)	_wr32(_REG_BASE_+(0x0390<<2),(UINT)((_rd32(_REG_BASE_+(0x0390<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ADC_WAIT_MAXr			(ValSft_R22(_rd32(_REG_BASE_+(0x0391<<2)))&BitMask_10)
#define ADC_WAIT_MAXw(val)		_wr32(_REG_BASE_+(0x0391<<2),(UINT)((_rd32(_REG_BASE_+(0x0391<<2))&(~ValSft_L22(BitMask_10)))|ValSft_L22((val)&BitMask_10)))

#define ADC_SAMPLE_DUTYr		(ValSft_R11(_rd32(_REG_BASE_+(0x0391<<2)))&BitMask_10)
#define ADC_SAMPLE_DUTYw(val)	_wr32(_REG_BASE_+(0x0391<<2),(UINT)((_rd32(_REG_BASE_+(0x0391<<2))&(~ValSft_L11(BitMask_10)))|ValSft_L11((val)&BitMask_10)))

#define ADC_CYCLEr				(ValSft_R00(_rd32(_REG_BASE_+(0x0391<<2)))&BitMask_10)
#define ADC_CYCLEw(val)			_wr32(_REG_BASE_+(0x0391<<2),(UINT)((_rd32(_REG_BASE_+(0x0391<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ADC_SEL_TRGr			(ValSft_R26(_rd32(_REG_BASE_+(0x0392<<2)))&BitMask_01)
#define ADC_SEL_TRGw(val)		_wr32(_REG_BASE_+(0x0392<<2),(UINT)((_rd32(_REG_BASE_+(0x0392<<2))&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define ADC_CH0_SELr			(ValSft_R25(_rd32(_REG_BASE_+(0x0392<<2)))&BitMask_01)
#define ADC_CH0_SELw(val)		_wr32(_REG_BASE_+(0x0392<<2),(UINT)((_rd32(_REG_BASE_+(0x0392<<2))&(~ValSft_L25(BitMask_01)))|ValSft_L25((val)&BitMask_01)))

#define ADC_CH1_SELr			(ValSft_R24(_rd32(_REG_BASE_+(0x0392<<2)))&BitMask_01)
#define ADC_CH1_SELw(val)		_wr32(_REG_BASE_+(0x0392<<2),(UINT)((_rd32(_REG_BASE_+(0x0392<<2))&(~ValSft_L24(BitMask_01)))|ValSft_L24((val)&BitMask_01)))

#define ADC_CHANNEL0r			(ValSft_R12(_rd32(_REG_BASE_+(0x0392<<2)))&BitMask_12)
#define ADC_CHANNEL0w(val)		_wr32(_REG_BASE_+(0x0392<<2),(UINT)((_rd32(_REG_BASE_+(0x0392<<2))&(~ValSft_L12(BitMask_12)))|ValSft_L12((val)&BitMask_12)))

#define ADC_CHANNEL1r			(ValSft_R00(_rd32(_REG_BASE_+(0x0392<<2)))&BitMask_12)
#define ADC_CHANNEL1w(val)		_wr32(_REG_BASE_+(0x0392<<2),(UINT)((_rd32(_REG_BASE_+(0x0392<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define ADC_RDATA_VLOCKr		(ValSft_R29(_rd32(_REG_BASE_+(0x0393<<2)))&BitMask_01)
#define ADC_RDATA_VLOCKw(val)	_wr32(_REG_BASE_+(0x0393<<2),(UINT)((_rd32(_REG_BASE_+(0x0393<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define ADC_STC_TRGr			(ValSft_R27(_rd32(_REG_BASE_+(0x0393<<2)))&BitMask_01)
#define ADC_STC_TRGw(val)		_wr32(_REG_BASE_+(0x0393<<2),(UINT)((_rd32(_REG_BASE_+(0x0393<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define ADC_EOC_SELr			(ValSft_R24(_rd32(_REG_BASE_+(0x0393<<2)))&BitMask_02)
#define ADC_EOC_SELw(val)		_wr32(_REG_BASE_+(0x0393<<2),(UINT)((_rd32(_REG_BASE_+(0x0393<<2))&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define ADC_MODEr				(ValSft_R21(_rd32(_REG_BASE_+(0x0393<<2)))&BitMask_02)
#define ADC_MODEw(val)			_wr32(_REG_BASE_+(0x0393<<2),(UINT)((_rd32(_REG_BASE_+(0x0393<<2))&(~ValSft_L21(BitMask_02)))|ValSft_L21((val)&BitMask_02)))

#define ADC_ERCLRr				(ValSft_R19(_rd32(_REG_BASE_+(0x0393<<2)))&BitMask_01)
#define ADC_ERCLRw(val)			_wr32(_REG_BASE_+(0x0393<<2),(UINT)((_rd32(_REG_BASE_+(0x0393<<2))&(~ValSft_L19(BitMask_01)))|ValSft_L19((val)&BitMask_01)))

#define ADC_ENr					(ValSft_R13(_rd32(_REG_BASE_+(0x0393<<2)))&BitMask_01)
#define ADC_ENw(val)			_wr32(_REG_BASE_+(0x0393<<2),(UINT)((_rd32(_REG_BASE_+(0x0393<<2))&(~ValSft_L13(BitMask_01)))|ValSft_L13((val)&BitMask_01)))

#define ADC_XPD_WRr				(ValSft_R11(_rd32(_REG_BASE_+(0x0393<<2)))&BitMask_01)
#define ADC_XPD_WRw(val)		_wr32(_REG_BASE_+(0x0393<<2),(UINT)((_rd32(_REG_BASE_+(0x0393<<2))&(~ValSft_L11(BitMask_01)))|ValSft_L11((val)&BitMask_01)))

#define ADC_CH_UPDATE_POINTr	(ValSft_R00(_rd32(_REG_BASE_+(0x0393<<2)))&BitMask_10)
#define ADC_CH_UPDATE_POINTw(val)	_wr32(_REG_BASE_+(0x0393<<2),(UINT)((_rd32(_REG_BASE_+(0x0393<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define ADC_XPD_INVr			(ValSft_R01(_rd32(_REG_BASE_+(0x0394<<2)))&BitMask_01)
#define ADC_XPD_INVw(val)		_wr32(_REG_BASE_+(0x0394<<2),(UINT)((_rd32(_REG_BASE_+(0x0394<<2))&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define ADC_CMDr				(ValSft_R00(_rd32(_REG_BASE_+(0x0394<<2)))&BitMask_01)
#define ADC_CMDw(val)			_wr32(_REG_BASE_+(0x0394<<2),(UINT)((_rd32(_REG_BASE_+(0x0394<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define ENC_ONr					(ValSft_R01(_rd32(_REG_BASE_+(0x0601<<2)))&BitMask_01)
#define ENC_ONw(val)			_wr32(_REG_BASE_+(0x0601<<2),(UINT)((_rd32(_REG_BASE_+(0x0601<<2))&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define ENC_TSELr				(ValSft_R00(_rd32(_REG_BASE_+(0x0601<<2)))&BitMask_01)
#define ENC_TSELw(val)			_wr32(_REG_BASE_+(0x0601<<2),(UINT)((_rd32(_REG_BASE_+(0x0601<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define HSC_Kr					(ValSft_R00(_rd32(_REG_BASE_+(0x0602<<2)))&BitMask_13)
#define HSC_Kw(val)				_wr32(_REG_BASE_+(0x0602<<2),(UINT)((_rd32(_REG_BASE_+(0x0602<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define HSC_HSPr				(ValSft_R00(_rd32(_REG_BASE_+(0x0603<<2)))&BitMask_24)
#define HSC_HSPw(val)			_wr32(_REG_BASE_+(0x0603<<2),(UINT)((_rd32(_REG_BASE_+(0x0603<<2))&(~ValSft_L00(BitMask_24)))|ValSft_L00((val)&BitMask_24)))

#define ESYNC_THr				(ValSft_R00(_rd32(_REG_BASE_+(0x0605<<2)))&BitMask_32)
#define ESYNC_THw(val)			_wr32(_REG_BASE_+(0x0605<<2),(UINT)((_rd32(_REG_BASE_+(0x0605<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define ESYNC_MODEr				(ValSft_R30(_rd32(_REG_BASE_+(0x0606<<2)))&BitMask_02)
#define ESYNC_MODEw(val)		_wr32(_REG_BASE_+(0x0606<<2),(UINT)((_rd32(_REG_BASE_+(0x0606<<2))&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define ENC_TIMG_SELr			(ValSft_R24(_rd32(_REG_BASE_+(0x0606<<2)))&BitMask_02)
#define ENC_TIMG_SELw(val)		_wr32(_REG_BASE_+(0x0606<<2),(UINT)((_rd32(_REG_BASE_+(0x0606<<2))&(~ValSft_L24(BitMask_02)))|ValSft_L24((val)&BitMask_02)))

#define FLDE_INVr				(ValSft_R23(_rd32(_REG_BASE_+(0x0606<<2)))&BitMask_01)
#define FLDE_INVw(val)			_wr32(_REG_BASE_+(0x0606<<2),(UINT)((_rd32(_REG_BASE_+(0x0606<<2))&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define FLDE_INV2r				(ValSft_R22(_rd32(_REG_BASE_+(0x0606<<2)))&BitMask_01)
#define FLDE_INV2w(val)			_wr32(_REG_BASE_+(0x0606<<2),(UINT)((_rd32(_REG_BASE_+(0x0606<<2))&(~ValSft_L22(BitMask_01)))|ValSft_L22((val)&BitMask_01)))

#define FLDE_INV3r				(ValSft_R21(_rd32(_REG_BASE_+(0x0606<<2)))&BitMask_01)
#define FLDE_INV3w(val)			_wr32(_REG_BASE_+(0x0606<<2),(UINT)((_rd32(_REG_BASE_+(0x0606<<2))&(~ValSft_L21(BitMask_01)))|ValSft_L21((val)&BitMask_01)))

#define ESYNC_UPr				(ValSft_R20(_rd32(_REG_BASE_+(0x0606<<2)))&BitMask_01)
#define ESYNC_UPw(val)			_wr32(_REG_BASE_+(0x0606<<2),(UINT)((_rd32(_REG_BASE_+(0x0606<<2))&(~ValSft_L20(BitMask_01)))|ValSft_L20((val)&BitMask_01)))

#define ESYNC_AUTOr				(ValSft_R19(_rd32(_REG_BASE_+(0x0606<<2)))&BitMask_01)
#define ESYNC_AUTOw(val)		_wr32(_REG_BASE_+(0x0606<<2),(UINT)((_rd32(_REG_BASE_+(0x0606<<2))&(~ValSft_L19(BitMask_01)))|ValSft_L19((val)&BitMask_01)))

#define HTWEr					(ValSft_R16(_rd32(_REG_BASE_+(0x0607<<2)))&BitMask_16)
#define HTWEw(val)				_wr32(_REG_BASE_+(0x0607<<2),(UINT)((_rd32(_REG_BASE_+(0x0607<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define VTWEr					(ValSft_R00(_rd32(_REG_BASE_+(0x0607<<2)))&BitMask_12)
#define VTWEw(val)				_wr32(_REG_BASE_+(0x0607<<2),(UINT)((_rd32(_REG_BASE_+(0x0607<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define HSPEr					(ValSft_R16(_rd32(_REG_BASE_+(0x0608<<2)))&BitMask_16)
#define HSPEw(val)				_wr32(_REG_BASE_+(0x0608<<2),(UINT)((_rd32(_REG_BASE_+(0x0608<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define VSPEr					(ValSft_R00(_rd32(_REG_BASE_+(0x0608<<2)))&BitMask_12)
#define VSPEw(val)				_wr32(_REG_BASE_+(0x0608<<2),(UINT)((_rd32(_REG_BASE_+(0x0608<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define HWEr					(ValSft_R16(_rd32(_REG_BASE_+(0x0609<<2)))&BitMask_16)
#define HWEw(val)				_wr32(_REG_BASE_+(0x0609<<2),(UINT)((_rd32(_REG_BASE_+(0x0609<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define VWEr					(ValSft_R00(_rd32(_REG_BASE_+(0x0609<<2)))&BitMask_12)
#define VWEw(val)				_wr32(_REG_BASE_+(0x0609<<2),(UINT)((_rd32(_REG_BASE_+(0x0609<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define HLOCKE_POSr				(ValSft_R16(_rd32(_REG_BASE_+(0x060a<<2)))&BitMask_16)
#define HLOCKE_POSw(val)		_wr32(_REG_BASE_+(0x060a<<2),(UINT)((_rd32(_REG_BASE_+(0x060a<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define VLOCKE_EV_POSr			(ValSft_R16(_rd32(_REG_BASE_+(0x060b<<2)))&BitMask_12)
#define VLOCKE_EV_POSw(val)		_wr32(_REG_BASE_+(0x060b<<2),(UINT)((_rd32(_REG_BASE_+(0x060b<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define VLOCKE_OD_POSr			(ValSft_R00(_rd32(_REG_BASE_+(0x060b<<2)))&BitMask_12)
#define VLOCKE_OD_POSw(val)		_wr32(_REG_BASE_+(0x060b<<2),(UINT)((_rd32(_REG_BASE_+(0x060b<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define ENC_RYGAINPr			(ValSft_R24(_rd32(_REG_BASE_+(0x0611<<2)))&BitMask_08)
#define ENC_RYGAINPw(val)		_wr32(_REG_BASE_+(0x0611<<2),(UINT)((_rd32(_REG_BASE_+(0x0611<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define ENC_RYGAINNr			(ValSft_R16(_rd32(_REG_BASE_+(0x0611<<2)))&BitMask_08)
#define ENC_RYGAINNw(val)		_wr32(_REG_BASE_+(0x0611<<2),(UINT)((_rd32(_REG_BASE_+(0x0611<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define ENC_BYGAINPr			(ValSft_R08(_rd32(_REG_BASE_+(0x0611<<2)))&BitMask_08)
#define ENC_BYGAINPw(val)		_wr32(_REG_BASE_+(0x0611<<2),(UINT)((_rd32(_REG_BASE_+(0x0611<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define ENC_BYGAINNr			(ValSft_R00(_rd32(_REG_BASE_+(0x0611<<2)))&BitMask_08)
#define ENC_BYGAINNw(val)		_wr32(_REG_BASE_+(0x0611<<2),(UINT)((_rd32(_REG_BASE_+(0x0611<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define ENC_RYHUEPr				(ValSft_R24(_rd32(_REG_BASE_+(0x0612<<2)))&BitMask_08)
#define ENC_RYHUEPw(val)		_wr32(_REG_BASE_+(0x0612<<2),(UINT)((_rd32(_REG_BASE_+(0x0612<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define ENC_RYHUENr				(ValSft_R16(_rd32(_REG_BASE_+(0x0612<<2)))&BitMask_08)
#define ENC_RYHUENw(val)		_wr32(_REG_BASE_+(0x0612<<2),(UINT)((_rd32(_REG_BASE_+(0x0612<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define ENC_BYHUEPr				(ValSft_R08(_rd32(_REG_BASE_+(0x0612<<2)))&BitMask_08)
#define ENC_BYHUEPw(val)		_wr32(_REG_BASE_+(0x0612<<2),(UINT)((_rd32(_REG_BASE_+(0x0612<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define ENC_BYHUENr				(ValSft_R00(_rd32(_REG_BASE_+(0x0612<<2)))&BitMask_08)
#define ENC_BYHUENw(val)		_wr32(_REG_BASE_+(0x0612<<2),(UINT)((_rd32(_REG_BASE_+(0x0612<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define ENC_NRYGAINPr			(ValSft_R24(_rd32(_REG_BASE_+(0x0613<<2)))&BitMask_08)
#define ENC_NRYGAINPw(val)		_wr32(_REG_BASE_+(0x0613<<2),(UINT)((_rd32(_REG_BASE_+(0x0613<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define ENC_NRYGAINNr			(ValSft_R16(_rd32(_REG_BASE_+(0x0613<<2)))&BitMask_08)
#define ENC_NRYGAINNw(val)		_wr32(_REG_BASE_+(0x0613<<2),(UINT)((_rd32(_REG_BASE_+(0x0613<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define ENC_NBYGAINPr			(ValSft_R08(_rd32(_REG_BASE_+(0x0613<<2)))&BitMask_08)
#define ENC_NBYGAINPw(val)		_wr32(_REG_BASE_+(0x0613<<2),(UINT)((_rd32(_REG_BASE_+(0x0613<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define ENC_NBYGAINNr			(ValSft_R00(_rd32(_REG_BASE_+(0x0613<<2)))&BitMask_08)
#define ENC_NBYGAINNw(val)		_wr32(_REG_BASE_+(0x0613<<2),(UINT)((_rd32(_REG_BASE_+(0x0613<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define ENC_NRYHUEPr			(ValSft_R24(_rd32(_REG_BASE_+(0x0614<<2)))&BitMask_08)
#define ENC_NRYHUEPw(val)		_wr32(_REG_BASE_+(0x0614<<2),(UINT)((_rd32(_REG_BASE_+(0x0614<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define ENC_NRYHUENr			(ValSft_R16(_rd32(_REG_BASE_+(0x0614<<2)))&BitMask_08)
#define ENC_NRYHUENw(val)		_wr32(_REG_BASE_+(0x0614<<2),(UINT)((_rd32(_REG_BASE_+(0x0614<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define ENC_NBYHUEPr			(ValSft_R08(_rd32(_REG_BASE_+(0x0614<<2)))&BitMask_08)
#define ENC_NBYHUEPw(val)		_wr32(_REG_BASE_+(0x0614<<2),(UINT)((_rd32(_REG_BASE_+(0x0614<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define ENC_NBYHUENr			(ValSft_R00(_rd32(_REG_BASE_+(0x0614<<2)))&BitMask_08)
#define ENC_NBYHUENw(val)		_wr32(_REG_BASE_+(0x0614<<2),(UINT)((_rd32(_REG_BASE_+(0x0614<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define TEST_SELr				(ValSft_R04(_rd32(_REG_BASE_+(0x0621<<2)))&BitMask_03)
#define TEST_SELw(val)			_wr32(_REG_BASE_+(0x0621<<2),(UINT)((_rd32(_REG_BASE_+(0x0621<<2))&(~ValSft_L04(BitMask_03)))|ValSft_L04((val)&BitMask_03)))

#define NTSCr					(ValSft_R03(_rd32(_REG_BASE_+(0x0621<<2)))&BitMask_01)
#define NTSCw(val)				_wr32(_REG_BASE_+(0x0621<<2),(UINT)((_rd32(_REG_BASE_+(0x0621<<2))&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))

#define LBURST_ONr				(ValSft_R02(_rd32(_REG_BASE_+(0x0621<<2)))&BitMask_01)
#define LBURST_ONw(val)			_wr32(_REG_BASE_+(0x0621<<2),(UINT)((_rd32(_REG_BASE_+(0x0621<<2))&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))

#define SERR_TYPEr				(ValSft_R01(_rd32(_REG_BASE_+(0x0621<<2)))&BitMask_01)
#define SERR_TYPEw(val)			_wr32(_REG_BASE_+(0x0621<<2),(UINT)((_rd32(_REG_BASE_+(0x0621<<2))&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define LBURST_HC0r				(ValSft_R16(_rd32(_REG_BASE_+(0x0622<<2)))&BitMask_12)
#define LBURST_HC0w(val)		_wr32(_REG_BASE_+(0x0622<<2),(UINT)((_rd32(_REG_BASE_+(0x0622<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define LBURST_HC1r				(ValSft_R00(_rd32(_REG_BASE_+(0x0622<<2)))&BitMask_12)
#define LBURST_HC1w(val)		_wr32(_REG_BASE_+(0x0622<<2),(UINT)((_rd32(_REG_BASE_+(0x0622<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define LBURST_HC2r				(ValSft_R16(_rd32(_REG_BASE_+(0x0623<<2)))&BitMask_12)
#define LBURST_HC2w(val)		_wr32(_REG_BASE_+(0x0623<<2),(UINT)((_rd32(_REG_BASE_+(0x0623<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define LBURST_HC3r				(ValSft_R00(_rd32(_REG_BASE_+(0x0623<<2)))&BitMask_12)
#define LBURST_HC3w(val)		_wr32(_REG_BASE_+(0x0623<<2),(UINT)((_rd32(_REG_BASE_+(0x0623<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define LBURST_HC4r				(ValSft_R16(_rd32(_REG_BASE_+(0x0624<<2)))&BitMask_12)
#define LBURST_HC4w(val)		_wr32(_REG_BASE_+(0x0624<<2),(UINT)((_rd32(_REG_BASE_+(0x0624<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define LBURST_HC5r				(ValSft_R00(_rd32(_REG_BASE_+(0x0624<<2)))&BitMask_12)
#define LBURST_HC5w(val)		_wr32(_REG_BASE_+(0x0624<<2),(UINT)((_rd32(_REG_BASE_+(0x0624<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define LBURST_HC6r				(ValSft_R16(_rd32(_REG_BASE_+(0x0625<<2)))&BitMask_12)
#define LBURST_HC6w(val)		_wr32(_REG_BASE_+(0x0625<<2),(UINT)((_rd32(_REG_BASE_+(0x0625<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define LBURST_HC7r				(ValSft_R00(_rd32(_REG_BASE_+(0x0625<<2)))&BitMask_12)
#define LBURST_HC7w(val)		_wr32(_REG_BASE_+(0x0625<<2),(UINT)((_rd32(_REG_BASE_+(0x0625<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define LBURST_HC8r				(ValSft_R16(_rd32(_REG_BASE_+(0x0626<<2)))&BitMask_12)
#define LBURST_HC8w(val)		_wr32(_REG_BASE_+(0x0626<<2),(UINT)((_rd32(_REG_BASE_+(0x0626<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define LBURST_HC9r				(ValSft_R00(_rd32(_REG_BASE_+(0x0626<<2)))&BitMask_12)
#define LBURST_HC9w(val)		_wr32(_REG_BASE_+(0x0626<<2),(UINT)((_rd32(_REG_BASE_+(0x0626<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define LBURST_HCar				(ValSft_R16(_rd32(_REG_BASE_+(0x0627<<2)))&BitMask_12)
#define LBURST_HCaw(val)		_wr32(_REG_BASE_+(0x0627<<2),(UINT)((_rd32(_REG_BASE_+(0x0627<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define LBURST_HCbr				(ValSft_R00(_rd32(_REG_BASE_+(0x0627<<2)))&BitMask_12)
#define LBURST_HCbw(val)		_wr32(_REG_BASE_+(0x0627<<2),(UINT)((_rd32(_REG_BASE_+(0x0627<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define LBURST_HCcr				(ValSft_R16(_rd32(_REG_BASE_+(0x0628<<2)))&BitMask_12)
#define LBURST_HCcw(val)		_wr32(_REG_BASE_+(0x0628<<2),(UINT)((_rd32(_REG_BASE_+(0x0628<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define LBURST_HCdr				(ValSft_R00(_rd32(_REG_BASE_+(0x0628<<2)))&BitMask_12)
#define LBURST_HCdw(val)		_wr32(_REG_BASE_+(0x0628<<2),(UINT)((_rd32(_REG_BASE_+(0x0628<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define LBURST_HCer				(ValSft_R16(_rd32(_REG_BASE_+(0x0629<<2)))&BitMask_12)
#define LBURST_HCew(val)		_wr32(_REG_BASE_+(0x0629<<2),(UINT)((_rd32(_REG_BASE_+(0x0629<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define LBURST_HCfr				(ValSft_R00(_rd32(_REG_BASE_+(0x0629<<2)))&BitMask_12)
#define LBURST_HCfw(val)		_wr32(_REG_BASE_+(0x0629<<2),(UINT)((_rd32(_REG_BASE_+(0x0629<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define IHDVD_GENr				(ValSft_R31(_rd32(_REG_BASE_+(0x0631<<2)))&BitMask_01)
#define IHDVD_GENw(val)			_wr32(_REG_BASE_+(0x0631<<2),(UINT)((_rd32(_REG_BASE_+(0x0631<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define IHDVD_ICNT_CLIPr		(ValSft_R16(_rd32(_REG_BASE_+(0x0631<<2)))&BitMask_13)
#define IHDVD_ICNT_CLIPw(val)	_wr32(_REG_BASE_+(0x0631<<2),(UINT)((_rd32(_REG_BASE_+(0x0631<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define IHDVD_JCNT_CLIPr		(ValSft_R00(_rd32(_REG_BASE_+(0x0631<<2)))&BitMask_13)
#define IHDVD_JCNT_CLIPw(val)	_wr32(_REG_BASE_+(0x0631<<2),(UINT)((_rd32(_REG_BASE_+(0x0631<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define IHDVD_HSWr				(ValSft_R16(_rd32(_REG_BASE_+(0x0632<<2)))&BitMask_13)
#define IHDVD_HSWw(val)			_wr32(_REG_BASE_+(0x0632<<2),(UINT)((_rd32(_REG_BASE_+(0x0632<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define IHDVD_VSWr				(ValSft_R00(_rd32(_REG_BASE_+(0x0632<<2)))&BitMask_13)
#define IHDVD_VSWw(val)			_wr32(_REG_BASE_+(0x0632<<2),(UINT)((_rd32(_REG_BASE_+(0x0632<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define ESYNC_POLr				(ValSft_R27(_rd32(_REG_BASE_+(0x0633<<2)))&BitMask_01)
#define ESYNC_POLw(val)			_wr32(_REG_BASE_+(0x0633<<2),(UINT)((_rd32(_REG_BASE_+(0x0633<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define EFLD_INVr				(ValSft_R29(_rd32(_REG_BASE_+(0x0633<<2)))&BitMask_01)
#define EFLD_INVw(val)			_wr32(_REG_BASE_+(0x0633<<2),(UINT)((_rd32(_REG_BASE_+(0x0633<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define ICNT_CLIPr				(ValSft_R16(_rd32(_REG_BASE_+(0x0635<<2)))&BitMask_13)
#define ICNT_CLIPw(val)			_wr32(_REG_BASE_+(0x0635<<2),(UINT)((_rd32(_REG_BASE_+(0x0635<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define HLOCK_CATr				(ValSft_R00(_rd32(_REG_BASE_+(0x0635<<2)))&BitMask_13)
#define HLOCK_CATw(val)			_wr32(_REG_BASE_+(0x0635<<2),(UINT)((_rd32(_REG_BASE_+(0x0635<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define VLOCK_CAT_EVr			(ValSft_R16(_rd32(_REG_BASE_+(0x0636<<2)))&BitMask_13)
#define VLOCK_CAT_EVw(val)		_wr32(_REG_BASE_+(0x0636<<2),(UINT)((_rd32(_REG_BASE_+(0x0636<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define VLOCK_CAT_ODr			(ValSft_R00(_rd32(_REG_BASE_+(0x0636<<2)))&BitMask_13)
#define VLOCK_CAT_ODw(val)		_wr32(_REG_BASE_+(0x0636<<2),(UINT)((_rd32(_REG_BASE_+(0x0636<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define TEST_ONr				(ValSft_R31(_rd32(_REG_BASE_+(0x0637<<2)))&BitMask_01)
#define TEST_ONw(val)			_wr32(_REG_BASE_+(0x0637<<2),(UINT)((_rd32(_REG_BASE_+(0x0637<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define TEST_HTWr				(ValSft_R16(_rd32(_REG_BASE_+(0x0637<<2)))&BitMask_12)
#define TEST_HTWw(val)			_wr32(_REG_BASE_+(0x0637<<2),(UINT)((_rd32(_REG_BASE_+(0x0637<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define TEST_HSPr				(ValSft_R00(_rd32(_REG_BASE_+(0x0637<<2)))&BitMask_13)
#define TEST_HSPw(val)			_wr32(_REG_BASE_+(0x0637<<2),(UINT)((_rd32(_REG_BASE_+(0x0637<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define Y_MGAINr				(ValSft_R00(_rd32(_REG_BASE_+(0x0638<<2)))&BitMask_12)
#define Y_MGAINw(val)			_wr32(_REG_BASE_+(0x0638<<2),(UINT)((_rd32(_REG_BASE_+(0x0638<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define CB_MGAINr				(ValSft_R16(_rd32(_REG_BASE_+(0x0639<<2)))&BitMask_12)
#define CB_MGAINw(val)			_wr32(_REG_BASE_+(0x0639<<2),(UINT)((_rd32(_REG_BASE_+(0x0639<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define CR_MGAINr				(ValSft_R00(_rd32(_REG_BASE_+(0x0639<<2)))&BitMask_12)
#define CR_MGAINw(val)			_wr32(_REG_BASE_+(0x0639<<2),(UINT)((_rd32(_REG_BASE_+(0x0639<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define SERR_VSP_EVr			(ValSft_R16(_rd32(_REG_BASE_+(0x063a<<2)))&BitMask_13)
#define SERR_VSP_EVw(val)		_wr32(_REG_BASE_+(0x063a<<2),(UINT)((_rd32(_REG_BASE_+(0x063a<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define SERR_VEP_EVr			(ValSft_R00(_rd32(_REG_BASE_+(0x063a<<2)))&BitMask_13)
#define SERR_VEP_EVw(val)		_wr32(_REG_BASE_+(0x063a<<2),(UINT)((_rd32(_REG_BASE_+(0x063a<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define BLANK_VEP_EVr			(ValSft_R16(_rd32(_REG_BASE_+(0x063b<<2)))&BitMask_13)
#define BLANK_VEP_EVw(val)		_wr32(_REG_BASE_+(0x063b<<2),(UINT)((_rd32(_REG_BASE_+(0x063b<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define BURST_VSP_EVr			(ValSft_R00(_rd32(_REG_BASE_+(0x063b<<2)))&BitMask_13)
#define BURST_VSP_EVw(val)		_wr32(_REG_BASE_+(0x063b<<2),(UINT)((_rd32(_REG_BASE_+(0x063b<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define ACT_VSP_EVr				(ValSft_R16(_rd32(_REG_BASE_+(0x063c<<2)))&BitMask_13)
#define ACT_VSP_EVw(val)		_wr32(_REG_BASE_+(0x063c<<2),(UINT)((_rd32(_REG_BASE_+(0x063c<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define ACT_VEP_EVr				(ValSft_R00(_rd32(_REG_BASE_+(0x063c<<2)))&BitMask_13)
#define ACT_VEP_EVw(val)		_wr32(_REG_BASE_+(0x063c<<2),(UINT)((_rd32(_REG_BASE_+(0x063c<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define BURST_VEP_EVr			(ValSft_R16(_rd32(_REG_BASE_+(0x063d<<2)))&BitMask_13)
#define BURST_VEP_EVw(val)		_wr32(_REG_BASE_+(0x063d<<2),(UINT)((_rd32(_REG_BASE_+(0x063d<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define BLANK_VSP_EVr			(ValSft_R00(_rd32(_REG_BASE_+(0x063d<<2)))&BitMask_13)
#define BLANK_VSP_EVw(val)		_wr32(_REG_BASE_+(0x063d<<2),(UINT)((_rd32(_REG_BASE_+(0x063d<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define LBURST_VSP_EVr			(ValSft_R16(_rd32(_REG_BASE_+(0x063e<<2)))&BitMask_13)
#define LBURST_VSP_EVw(val)		_wr32(_REG_BASE_+(0x063e<<2),(UINT)((_rd32(_REG_BASE_+(0x063e<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define LBURST_VEP_EVr			(ValSft_R00(_rd32(_REG_BASE_+(0x063e<<2)))&BitMask_13)
#define LBURST_VEP_EVw(val)		_wr32(_REG_BASE_+(0x063e<<2),(UINT)((_rd32(_REG_BASE_+(0x063e<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define SERR_VSP_ODr			(ValSft_R16(_rd32(_REG_BASE_+(0x0641<<2)))&BitMask_13)
#define SERR_VSP_ODw(val)		_wr32(_REG_BASE_+(0x0641<<2),(UINT)((_rd32(_REG_BASE_+(0x0641<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define SERR_VEP_ODr			(ValSft_R00(_rd32(_REG_BASE_+(0x0641<<2)))&BitMask_13)
#define SERR_VEP_ODw(val)		_wr32(_REG_BASE_+(0x0641<<2),(UINT)((_rd32(_REG_BASE_+(0x0641<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define BLANK_VEP_ODr			(ValSft_R16(_rd32(_REG_BASE_+(0x0642<<2)))&BitMask_13)
#define BLANK_VEP_ODw(val)		_wr32(_REG_BASE_+(0x0642<<2),(UINT)((_rd32(_REG_BASE_+(0x0642<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define BURST_VSP_ODr			(ValSft_R00(_rd32(_REG_BASE_+(0x0642<<2)))&BitMask_13)
#define BURST_VSP_ODw(val)		_wr32(_REG_BASE_+(0x0642<<2),(UINT)((_rd32(_REG_BASE_+(0x0642<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define ACT_VSP_ODr				(ValSft_R16(_rd32(_REG_BASE_+(0x0643<<2)))&BitMask_13)
#define ACT_VSP_ODw(val)		_wr32(_REG_BASE_+(0x0643<<2),(UINT)((_rd32(_REG_BASE_+(0x0643<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define ACT_VEP_ODr				(ValSft_R00(_rd32(_REG_BASE_+(0x0643<<2)))&BitMask_13)
#define ACT_VEP_ODw(val)		_wr32(_REG_BASE_+(0x0643<<2),(UINT)((_rd32(_REG_BASE_+(0x0643<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define BURST_VEP_ODr			(ValSft_R16(_rd32(_REG_BASE_+(0x0644<<2)))&BitMask_13)
#define BURST_VEP_ODw(val)		_wr32(_REG_BASE_+(0x0644<<2),(UINT)((_rd32(_REG_BASE_+(0x0644<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define BLANK_VSP_ODr			(ValSft_R00(_rd32(_REG_BASE_+(0x0644<<2)))&BitMask_13)
#define BLANK_VSP_ODw(val)		_wr32(_REG_BASE_+(0x0644<<2),(UINT)((_rd32(_REG_BASE_+(0x0644<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define LBURST_VSP_ODr			(ValSft_R16(_rd32(_REG_BASE_+(0x0645<<2)))&BitMask_13)
#define LBURST_VSP_ODw(val)		_wr32(_REG_BASE_+(0x0645<<2),(UINT)((_rd32(_REG_BASE_+(0x0645<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define LBURST_VEP_ODr			(ValSft_R00(_rd32(_REG_BASE_+(0x0645<<2)))&BitMask_13)
#define LBURST_VEP_ODw(val)		_wr32(_REG_BASE_+(0x0645<<2),(UINT)((_rd32(_REG_BASE_+(0x0645<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define ACT_BLANK_HWr			(ValSft_R16(_rd32(_REG_BASE_+(0x0646<<2)))&BitMask_14)
#define ACT_BLANK_HWw(val)		_wr32(_REG_BASE_+(0x0646<<2),(UINT)((_rd32(_REG_BASE_+(0x0646<<2))&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define ACT_BLANK_HSPr			(ValSft_R00(_rd32(_REG_BASE_+(0x0646<<2)))&BitMask_14)
#define ACT_BLANK_HSPw(val)		_wr32(_REG_BASE_+(0x0646<<2),(UINT)((_rd32(_REG_BASE_+(0x0646<<2))&(~ValSft_L00(BitMask_14)))|ValSft_L00((val)&BitMask_14)))

#define SERR_SYNC_HWr			(ValSft_R16(_rd32(_REG_BASE_+(0x0647<<2)))&BitMask_13)
#define SERR_SYNC_HWw(val)		_wr32(_REG_BASE_+(0x0647<<2),(UINT)((_rd32(_REG_BASE_+(0x0647<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define SERR_SYNC_HSPr			(ValSft_R00(_rd32(_REG_BASE_+(0x0647<<2)))&BitMask_13)
#define SERR_SYNC_HSPw(val)		_wr32(_REG_BASE_+(0x0647<<2),(UINT)((_rd32(_REG_BASE_+(0x0647<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define EQUAL_SYNC_HWr			(ValSft_R16(_rd32(_REG_BASE_+(0x0648<<2)))&BitMask_13)
#define EQUAL_SYNC_HWw(val)		_wr32(_REG_BASE_+(0x0648<<2),(UINT)((_rd32(_REG_BASE_+(0x0648<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define EQUAL_SYNC_HSPr			(ValSft_R00(_rd32(_REG_BASE_+(0x0648<<2)))&BitMask_13)
#define EQUAL_SYNC_HSPw(val)	_wr32(_REG_BASE_+(0x0648<<2),(UINT)((_rd32(_REG_BASE_+(0x0648<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define ACT_SYNC_HWr			(ValSft_R16(_rd32(_REG_BASE_+(0x0649<<2)))&BitMask_14)
#define ACT_SYNC_HWw(val)		_wr32(_REG_BASE_+(0x0649<<2),(UINT)((_rd32(_REG_BASE_+(0x0649<<2))&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define ACT_SYNC_HSPr			(ValSft_R00(_rd32(_REG_BASE_+(0x0649<<2)))&BitMask_14)
#define ACT_SYNC_HSPw(val)		_wr32(_REG_BASE_+(0x0649<<2),(UINT)((_rd32(_REG_BASE_+(0x0649<<2))&(~ValSft_L00(BitMask_14)))|ValSft_L00((val)&BitMask_14)))

#define ACT_BURST_HWr			(ValSft_R16(_rd32(_REG_BASE_+(0x064a<<2)))&BitMask_14)
#define ACT_BURST_HWw(val)		_wr32(_REG_BASE_+(0x064a<<2),(UINT)((_rd32(_REG_BASE_+(0x064a<<2))&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define ACT_BURST_HSPr			(ValSft_R00(_rd32(_REG_BASE_+(0x064a<<2)))&BitMask_14)
#define ACT_BURST_HSPw(val)		_wr32(_REG_BASE_+(0x064a<<2),(UINT)((_rd32(_REG_BASE_+(0x064a<<2))&(~ValSft_L00(BitMask_14)))|ValSft_L00((val)&BitMask_14)))

#define ACT_ACT_HWr				(ValSft_R16(_rd32(_REG_BASE_+(0x064b<<2)))&BitMask_14)
#define ACT_ACT_HWw(val)		_wr32(_REG_BASE_+(0x064b<<2),(UINT)((_rd32(_REG_BASE_+(0x064b<<2))&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define ACT_ACT_HSPr			(ValSft_R00(_rd32(_REG_BASE_+(0x064b<<2)))&BitMask_14)
#define ACT_ACT_HSPw(val)		_wr32(_REG_BASE_+(0x064b<<2),(UINT)((_rd32(_REG_BASE_+(0x064b<<2))&(~ValSft_L00(BitMask_14)))|ValSft_L00((val)&BitMask_14)))

#define LBURST_HWr				(ValSft_R16(_rd32(_REG_BASE_+(0x064c<<2)))&BitMask_14)
#define LBURST_HWw(val)			_wr32(_REG_BASE_+(0x064c<<2),(UINT)((_rd32(_REG_BASE_+(0x064c<<2))&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define LBURST_HSPr				(ValSft_R00(_rd32(_REG_BASE_+(0x064c<<2)))&BitMask_14)
#define LBURST_HSPw(val)		_wr32(_REG_BASE_+(0x064c<<2),(UINT)((_rd32(_REG_BASE_+(0x064c<<2))&(~ValSft_L00(BitMask_14)))|ValSft_L00((val)&BitMask_14)))

#define CXIN_SELr				(ValSft_R31(_rd32(_REG_BASE_+(0x0651<<2)))&BitMask_01)
#define CXIN_SELw(val)			_wr32(_REG_BASE_+(0x0651<<2),(UINT)((_rd32(_REG_BASE_+(0x0651<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define CRX_SELr				(ValSft_R30(_rd32(_REG_BASE_+(0x0651<<2)))&BitMask_01)
#define CRX_SELw(val)			_wr32(_REG_BASE_+(0x0651<<2),(UINT)((_rd32(_REG_BASE_+(0x0651<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define CRXRST_SELr				(ValSft_R28(_rd32(_REG_BASE_+(0x0651<<2)))&BitMask_02)
#define CRXRST_SELw(val)		_wr32(_REG_BASE_+(0x0651<<2),(UINT)((_rd32(_REG_BASE_+(0x0651<<2))&(~ValSft_L28(BitMask_02)))|ValSft_L28((val)&BitMask_02)))

#define CXIN_FILDr				(ValSft_R00(_rd32(_REG_BASE_+(0x0651<<2)))&BitMask_16)
#define CXIN_FILDw(val)			_wr32(_REG_BASE_+(0x0651<<2),(UINT)((_rd32(_REG_BASE_+(0x0651<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define CRX_AUTOr				(ValSft_R30(_rd32(_REG_BASE_+(0x0652<<2)))&BitMask_02)
#define CRX_AUTOw(val)			_wr32(_REG_BASE_+(0x0652<<2),(UINT)((_rd32(_REG_BASE_+(0x0652<<2))&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define CRX_AUTO_CATr			(ValSft_R16(_rd32(_REG_BASE_+(0x0652<<2)))&BitMask_10)
#define CRX_AUTO_CATw(val)		_wr32(_REG_BASE_+(0x0652<<2),(UINT)((_rd32(_REG_BASE_+(0x0652<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CRX_AST_POSr			(ValSft_R12(_rd32(_REG_BASE_+(0x0652<<2)))&BitMask_04)
#define CRX_AST_POSw(val)		_wr32(_REG_BASE_+(0x0652<<2),(UINT)((_rd32(_REG_BASE_+(0x0652<<2))&(~ValSft_L12(BitMask_04)))|ValSft_L12((val)&BitMask_04)))

#define CTX_ENr					(ValSft_R31(_rd32(_REG_BASE_+(0x0653<<2)))&BitMask_01)
#define CTX_ENw(val)			_wr32(_REG_BASE_+(0x0653<<2),(UINT)((_rd32(_REG_BASE_+(0x0653<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define CRX_ENr					(ValSft_R30(_rd32(_REG_BASE_+(0x0653<<2)))&BitMask_01)
#define CRX_ENw(val)			_wr32(_REG_BASE_+(0x0653<<2),(UINT)((_rd32(_REG_BASE_+(0x0653<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define CRX_DEGLCHTABr			(ValSft_R24(_rd32(_REG_BASE_+(0x0653<<2)))&BitMask_05)
#define CRX_DEGLCHTABw(val)		_wr32(_REG_BASE_+(0x0653<<2),(UINT)((_rd32(_REG_BASE_+(0x0653<<2))&(~ValSft_L24(BitMask_05)))|ValSft_L24((val)&BitMask_05)))

#define CRX_DEGLCHTH1r			(ValSft_R16(_rd32(_REG_BASE_+(0x0653<<2)))&BitMask_05)
#define CRX_DEGLCHTH1w(val)		_wr32(_REG_BASE_+(0x0653<<2),(UINT)((_rd32(_REG_BASE_+(0x0653<<2))&(~ValSft_L16(BitMask_05)))|ValSft_L16((val)&BitMask_05)))

#define CRX_DEGLCHTH2r			(ValSft_R10(_rd32(_REG_BASE_+(0x0653<<2)))&BitMask_05)
#define CRX_DEGLCHTH2w(val)		_wr32(_REG_BASE_+(0x0653<<2),(UINT)((_rd32(_REG_BASE_+(0x0653<<2))&(~ValSft_L10(BitMask_05)))|ValSft_L10((val)&BitMask_05)))

#define CRX_VPOSEVSr			(ValSft_R16(_rd32(_REG_BASE_+(0x0654<<2)))&BitMask_13)
#define CRX_VPOSEVSw(val)		_wr32(_REG_BASE_+(0x0654<<2),(UINT)((_rd32(_REG_BASE_+(0x0654<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define CRX_VPOSEVEr			(ValSft_R00(_rd32(_REG_BASE_+(0x0654<<2)))&BitMask_13)
#define CRX_VPOSEVEw(val)		_wr32(_REG_BASE_+(0x0654<<2),(UINT)((_rd32(_REG_BASE_+(0x0654<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define CRX_VPOSODSr			(ValSft_R16(_rd32(_REG_BASE_+(0x0655<<2)))&BitMask_13)
#define CRX_VPOSODSw(val)		_wr32(_REG_BASE_+(0x0655<<2),(UINT)((_rd32(_REG_BASE_+(0x0655<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define CRX_VPOSODEr			(ValSft_R00(_rd32(_REG_BASE_+(0x0655<<2)))&BitMask_13)
#define CRX_VPOSODEw(val)		_wr32(_REG_BASE_+(0x0655<<2),(UINT)((_rd32(_REG_BASE_+(0x0655<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define CRX_HPOSEVSr			(ValSft_R16(_rd32(_REG_BASE_+(0x0656<<2)))&BitMask_14)
#define CRX_HPOSEVSw(val)		_wr32(_REG_BASE_+(0x0656<<2),(UINT)((_rd32(_REG_BASE_+(0x0656<<2))&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define CRX_HPOSEVEr			(ValSft_R00(_rd32(_REG_BASE_+(0x0656<<2)))&BitMask_14)
#define CRX_HPOSEVEw(val)		_wr32(_REG_BASE_+(0x0656<<2),(UINT)((_rd32(_REG_BASE_+(0x0656<<2))&(~ValSft_L00(BitMask_14)))|ValSft_L00((val)&BitMask_14)))

#define CRX_HPOSODSr			(ValSft_R16(_rd32(_REG_BASE_+(0x0657<<2)))&BitMask_14)
#define CRX_HPOSODSw(val)		_wr32(_REG_BASE_+(0x0657<<2),(UINT)((_rd32(_REG_BASE_+(0x0657<<2))&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define CRX_HPOSODEr			(ValSft_R00(_rd32(_REG_BASE_+(0x0657<<2)))&BitMask_14)
#define CRX_HPOSODEw(val)		_wr32(_REG_BASE_+(0x0657<<2),(UINT)((_rd32(_REG_BASE_+(0x0657<<2))&(~ValSft_L00(BitMask_14)))|ValSft_L00((val)&BitMask_14)))

#define CRX_LBITNUMr			(ValSft_R24(_rd32(_REG_BASE_+(0x0658<<2)))&BitMask_07)
#define CRX_LBITNUMw(val)		_wr32(_REG_BASE_+(0x0658<<2),(UINT)((_rd32(_REG_BASE_+(0x0658<<2))&(~ValSft_L24(BitMask_07)))|ValSft_L24((val)&BitMask_07)))

#define CRX_BUF_CLRr			(ValSft_R23(_rd32(_REG_BASE_+(0x0658<<2)))&BitMask_01)
#define CRX_BUF_CLRw(val)		_wr32(_REG_BASE_+(0x0658<<2),(UINT)((_rd32(_REG_BASE_+(0x0658<<2))&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define CRX_BITMIN_RSTr			(ValSft_R22(_rd32(_REG_BASE_+(0x0658<<2)))&BitMask_01)
#define CRX_BITMIN_RSTw(val)	_wr32(_REG_BASE_+(0x0658<<2),(UINT)((_rd32(_REG_BASE_+(0x0658<<2))&(~ValSft_L22(BitMask_01)))|ValSft_L22((val)&BitMask_01)))

#define CRX_BITRATEr			(ValSft_R00(_rd32(_REG_BASE_+(0x0658<<2)))&BitMask_14)
#define CRX_BITRATEw(val)		_wr32(_REG_BASE_+(0x0658<<2),(UINT)((_rd32(_REG_BASE_+(0x0658<<2))&(~ValSft_L00(BitMask_14)))|ValSft_L00((val)&BitMask_14)))

#define CTX_VPOSEVSr			(ValSft_R16(_rd32(_REG_BASE_+(0x0659<<2)))&BitMask_13)
#define CTX_VPOSEVSw(val)		_wr32(_REG_BASE_+(0x0659<<2),(UINT)((_rd32(_REG_BASE_+(0x0659<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define CTX_VPOSEVEr			(ValSft_R00(_rd32(_REG_BASE_+(0x0659<<2)))&BitMask_13)
#define CTX_VPOSEVEw(val)		_wr32(_REG_BASE_+(0x0659<<2),(UINT)((_rd32(_REG_BASE_+(0x0659<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define CTX_VPOSODSr			(ValSft_R16(_rd32(_REG_BASE_+(0x065a<<2)))&BitMask_13)
#define CTX_VPOSODSw(val)		_wr32(_REG_BASE_+(0x065a<<2),(UINT)((_rd32(_REG_BASE_+(0x065a<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define CTX_VPOSODEr			(ValSft_R00(_rd32(_REG_BASE_+(0x065a<<2)))&BitMask_13)
#define CTX_VPOSODEw(val)		_wr32(_REG_BASE_+(0x065a<<2),(UINT)((_rd32(_REG_BASE_+(0x065a<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define CTX_HPOSEVSr			(ValSft_R16(_rd32(_REG_BASE_+(0x065b<<2)))&BitMask_14)
#define CTX_HPOSEVSw(val)		_wr32(_REG_BASE_+(0x065b<<2),(UINT)((_rd32(_REG_BASE_+(0x065b<<2))&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define CTX_HPOSEVEr			(ValSft_R00(_rd32(_REG_BASE_+(0x065b<<2)))&BitMask_14)
#define CTX_HPOSEVEw(val)		_wr32(_REG_BASE_+(0x065b<<2),(UINT)((_rd32(_REG_BASE_+(0x065b<<2))&(~ValSft_L00(BitMask_14)))|ValSft_L00((val)&BitMask_14)))

#define CTX_HPOSODSr			(ValSft_R16(_rd32(_REG_BASE_+(0x065c<<2)))&BitMask_14)
#define CTX_HPOSODSw(val)		_wr32(_REG_BASE_+(0x065c<<2),(UINT)((_rd32(_REG_BASE_+(0x065c<<2))&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define CTX_HPOSODEr			(ValSft_R00(_rd32(_REG_BASE_+(0x065c<<2)))&BitMask_14)
#define CTX_HPOSODEw(val)		_wr32(_REG_BASE_+(0x065c<<2),(UINT)((_rd32(_REG_BASE_+(0x065c<<2))&(~ValSft_L00(BitMask_14)))|ValSft_L00((val)&BitMask_14)))

#define CXAL_WOPr				(ValSft_R31(_rd32(_REG_BASE_+(0x065d<<2)))&BitMask_01)
#define CXAL_WOPw(val)			_wr32(_REG_BASE_+(0x065d<<2),(UINT)((_rd32(_REG_BASE_+(0x065d<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define CLI_CXALr				(ValSft_R27(_rd32(_REG_BASE_+(0x065e<<2)))&BitMask_01)
#define CLI_CXALw(val)			_wr32(_REG_BASE_+(0x065e<<2),(UINT)((_rd32(_REG_BASE_+(0x065e<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define CTX_LBITNUMr			(ValSft_R16(_rd32(_REG_BASE_+(0x065e<<2)))&BitMask_06)
#define CTX_LBITNUMw(val)		_wr32(_REG_BASE_+(0x065e<<2),(UINT)((_rd32(_REG_BASE_+(0x065e<<2))&(~ValSft_L16(BitMask_06)))|ValSft_L16((val)&BitMask_06)))

#define CTX_BITRATEr			(ValSft_R00(_rd32(_REG_BASE_+(0x065e<<2)))&BitMask_10)
#define CTX_BITRATEw(val)		_wr32(_REG_BASE_+(0x065e<<2),(UINT)((_rd32(_REG_BASE_+(0x065e<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define INT_ENr					(ValSft_R31(_rd32(_REG_BASE_+(0x0661<<2)))&BitMask_01)
#define INT_ENw(val)			_wr32(_REG_BASE_+(0x0661<<2),(UINT)((_rd32(_REG_BASE_+(0x0661<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define INT_VALIDr				(ValSft_R30(_rd32(_REG_BASE_+(0x0661<<2)))&BitMask_01)
#define INT_VALIDw(val)			_wr32(_REG_BASE_+(0x0661<<2),(UINT)((_rd32(_REG_BASE_+(0x0661<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define CTX_CONTINUEr			(ValSft_R29(_rd32(_REG_BASE_+(0x0661<<2)))&BitMask_01)
#define CTX_CONTINUEw(val)		_wr32(_REG_BASE_+(0x0661<<2),(UINT)((_rd32(_REG_BASE_+(0x0661<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define CTX_LSBKEEPr			(ValSft_R28(_rd32(_REG_BASE_+(0x0661<<2)))&BitMask_01)
#define CTX_LSBKEEPw(val)		_wr32(_REG_BASE_+(0x0661<<2),(UINT)((_rd32(_REG_BASE_+(0x0661<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define CRX_INT_NEWr			(ValSft_R27(_rd32(_REG_BASE_+(0x0661<<2)))&BitMask_01)
#define CRX_INT_NEWw(val)		_wr32(_REG_BASE_+(0x0661<<2),(UINT)((_rd32(_REG_BASE_+(0x0661<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define INT_BITCNT_NUMr			(ValSft_R16(_rd32(_REG_BASE_+(0x0661<<2)))&BitMask_08)
#define INT_BITCNT_NUMw(val)	_wr32(_REG_BASE_+(0x0661<<2),(UINT)((_rd32(_REG_BASE_+(0x0661<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define INT_HSPr				(ValSft_R00(_rd32(_REG_BASE_+(0x0661<<2)))&BitMask_13)
#define INT_HSPw(val)			_wr32(_REG_BASE_+(0x0661<<2),(UINT)((_rd32(_REG_BASE_+(0x0661<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define INT_VSP_Er				(ValSft_R16(_rd32(_REG_BASE_+(0x0662<<2)))&BitMask_13)
#define INT_VSP_Ew(val)			_wr32(_REG_BASE_+(0x0662<<2),(UINT)((_rd32(_REG_BASE_+(0x0662<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define INT_VSP_Or				(ValSft_R00(_rd32(_REG_BASE_+(0x0662<<2)))&BitMask_13)
#define INT_VSP_Ow(val)			_wr32(_REG_BASE_+(0x0662<<2),(UINT)((_rd32(_REG_BASE_+(0x0662<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define INT_BITCNT_ENr			(ValSft_R31(_rd32(_REG_BASE_+(0x0663<<2)))&BitMask_01)
#define INT_BITCNT_ENw(val)		_wr32(_REG_BASE_+(0x0663<<2),(UINT)((_rd32(_REG_BASE_+(0x0663<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define INT_VEP_Er				(ValSft_R16(_rd32(_REG_BASE_+(0x0663<<2)))&BitMask_13)
#define INT_VEP_Ew(val)			_wr32(_REG_BASE_+(0x0663<<2),(UINT)((_rd32(_REG_BASE_+(0x0663<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define INT_VEP_Or				(ValSft_R00(_rd32(_REG_BASE_+(0x0663<<2)))&BitMask_13)
#define INT_VEP_Ow(val)			_wr32(_REG_BASE_+(0x0663<<2),(UINT)((_rd32(_REG_BASE_+(0x0663<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define CTX00r					(ValSft_R00(_rd32(_REG_BASE_+(0x0665<<2)))&BitMask_32)
#define CTX00w(val)				_wr32(_REG_BASE_+(0x0665<<2),(UINT)((_rd32(_REG_BASE_+(0x0665<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define CTX01r					(ValSft_R00(_rd32(_REG_BASE_+(0x0666<<2)))&BitMask_32)
#define CTX01w(val)				_wr32(_REG_BASE_+(0x0666<<2),(UINT)((_rd32(_REG_BASE_+(0x0666<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define CTX02r					(ValSft_R00(_rd32(_REG_BASE_+(0x0667<<2)))&BitMask_32)
#define CTX02w(val)				_wr32(_REG_BASE_+(0x0667<<2),(UINT)((_rd32(_REG_BASE_+(0x0667<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define CTX03r					(ValSft_R00(_rd32(_REG_BASE_+(0x0668<<2)))&BitMask_32)
#define CTX03w(val)				_wr32(_REG_BASE_+(0x0668<<2),(UINT)((_rd32(_REG_BASE_+(0x0668<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define CTX04r					(ValSft_R00(_rd32(_REG_BASE_+(0x0669<<2)))&BitMask_32)
#define CTX04w(val)				_wr32(_REG_BASE_+(0x0669<<2),(UINT)((_rd32(_REG_BASE_+(0x0669<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define CTX05r					(ValSft_R00(_rd32(_REG_BASE_+(0x066a<<2)))&BitMask_32)
#define CTX05w(val)				_wr32(_REG_BASE_+(0x066a<<2),(UINT)((_rd32(_REG_BASE_+(0x066a<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define CTX06r					(ValSft_R00(_rd32(_REG_BASE_+(0x066b<<2)))&BitMask_32)
#define CTX06w(val)				_wr32(_REG_BASE_+(0x066b<<2),(UINT)((_rd32(_REG_BASE_+(0x066b<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define CTX07r					(ValSft_R00(_rd32(_REG_BASE_+(0x066c<<2)))&BitMask_32)
#define CTX07w(val)				_wr32(_REG_BASE_+(0x066c<<2),(UINT)((_rd32(_REG_BASE_+(0x066c<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define CRX_BITRATE_MANr		(ValSft_R31(_rd32(_REG_BASE_+(0x066d<<2)))&BitMask_01)
#define CRX_BITRATE_MANw(val)	_wr32(_REG_BASE_+(0x066d<<2),(UINT)((_rd32(_REG_BASE_+(0x066d<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define CRX_PRE_SPr				(ValSft_R24(_rd32(_REG_BASE_+(0x066d<<2)))&BitMask_06)
#define CRX_PRE_SPw(val)		_wr32(_REG_BASE_+(0x066d<<2),(UINT)((_rd32(_REG_BASE_+(0x066d<<2))&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define CRX_PREAMBLEr			(ValSft_R16(_rd32(_REG_BASE_+(0x066d<<2)))&BitMask_08)
#define CRX_PREAMBLEw(val)		_wr32(_REG_BASE_+(0x066d<<2),(UINT)((_rd32(_REG_BASE_+(0x066d<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define CRX_PREWIDTHr			(ValSft_R08(_rd32(_REG_BASE_+(0x066d<<2)))&BitMask_06)
#define CRX_PREWIDTHw(val)		_wr32(_REG_BASE_+(0x066d<<2),(UINT)((_rd32(_REG_BASE_+(0x066d<<2))&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define Y_DLY_ADJr				(ValSft_R00(_rd32(_REG_BASE_+(0x0678<<2)))&BitMask_04)
#define Y_DLY_ADJw(val)			_wr32(_REG_BASE_+(0x0678<<2),(UINT)((_rd32(_REG_BASE_+(0x0678<<2))&(~ValSft_L00(BitMask_04)))|ValSft_L00((val)&BitMask_04)))

#define WHITE_LVr				(ValSft_R16(_rd32(_REG_BASE_+(0x0681<<2)))&BitMask_10)
#define WHITE_LVw(val)			_wr32(_REG_BASE_+(0x0681<<2),(UINT)((_rd32(_REG_BASE_+(0x0681<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define BLANK_LVr				(ValSft_R00(_rd32(_REG_BASE_+(0x0681<<2)))&BitMask_10)
#define BLANK_LVw(val)			_wr32(_REG_BASE_+(0x0681<<2),(UINT)((_rd32(_REG_BASE_+(0x0681<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define PEDESTAL_LVr			(ValSft_R16(_rd32(_REG_BASE_+(0x0682<<2)))&BitMask_11)
#define PEDESTAL_LVw(val)		_wr32(_REG_BASE_+(0x0682<<2),(UINT)((_rd32(_REG_BASE_+(0x0682<<2))&(~ValSft_L16(BitMask_11)))|ValSft_L16((val)&BitMask_11)))

#define Y_LPF_ONr				(ValSft_R14(_rd32(_REG_BASE_+(0x0682<<2)))&BitMask_02)
#define Y_LPF_ONw(val)			_wr32(_REG_BASE_+(0x0682<<2),(UINT)((_rd32(_REG_BASE_+(0x0682<<2))&(~ValSft_L14(BitMask_02)))|ValSft_L14((val)&BitMask_02)))

#define Y_SLEW_SELr				(ValSft_R12(_rd32(_REG_BASE_+(0x0682<<2)))&BitMask_02)
#define Y_SLEW_SELw(val)		_wr32(_REG_BASE_+(0x0682<<2),(UINT)((_rd32(_REG_BASE_+(0x0682<<2))&(~ValSft_L12(BitMask_02)))|ValSft_L12((val)&BitMask_02)))

#define SYNC_LVr				(ValSft_R00(_rd32(_REG_BASE_+(0x0682<<2)))&BitMask_10)
#define SYNC_LVw(val)			_wr32(_REG_BASE_+(0x0682<<2),(UINT)((_rd32(_REG_BASE_+(0x0682<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_Y0r				(ValSft_R16(_rd32(_REG_BASE_+(0x0683<<2)))&BitMask_10)
#define LBURST_Y0w(val)			_wr32(_REG_BASE_+(0x0683<<2),(UINT)((_rd32(_REG_BASE_+(0x0683<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_Y1r				(ValSft_R00(_rd32(_REG_BASE_+(0x0683<<2)))&BitMask_10)
#define LBURST_Y1w(val)			_wr32(_REG_BASE_+(0x0683<<2),(UINT)((_rd32(_REG_BASE_+(0x0683<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_Y2r				(ValSft_R16(_rd32(_REG_BASE_+(0x0684<<2)))&BitMask_10)
#define LBURST_Y2w(val)			_wr32(_REG_BASE_+(0x0684<<2),(UINT)((_rd32(_REG_BASE_+(0x0684<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_Y3r				(ValSft_R00(_rd32(_REG_BASE_+(0x0684<<2)))&BitMask_10)
#define LBURST_Y3w(val)			_wr32(_REG_BASE_+(0x0684<<2),(UINT)((_rd32(_REG_BASE_+(0x0684<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_Y4r				(ValSft_R16(_rd32(_REG_BASE_+(0x0685<<2)))&BitMask_10)
#define LBURST_Y4w(val)			_wr32(_REG_BASE_+(0x0685<<2),(UINT)((_rd32(_REG_BASE_+(0x0685<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_Y5r				(ValSft_R00(_rd32(_REG_BASE_+(0x0685<<2)))&BitMask_10)
#define LBURST_Y5w(val)			_wr32(_REG_BASE_+(0x0685<<2),(UINT)((_rd32(_REG_BASE_+(0x0685<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_Y6r				(ValSft_R16(_rd32(_REG_BASE_+(0x0686<<2)))&BitMask_10)
#define LBURST_Y6w(val)			_wr32(_REG_BASE_+(0x0686<<2),(UINT)((_rd32(_REG_BASE_+(0x0686<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_Y7r				(ValSft_R00(_rd32(_REG_BASE_+(0x0686<<2)))&BitMask_10)
#define LBURST_Y7w(val)			_wr32(_REG_BASE_+(0x0686<<2),(UINT)((_rd32(_REG_BASE_+(0x0686<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_Y8r				(ValSft_R16(_rd32(_REG_BASE_+(0x0687<<2)))&BitMask_10)
#define LBURST_Y8w(val)			_wr32(_REG_BASE_+(0x0687<<2),(UINT)((_rd32(_REG_BASE_+(0x0687<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_Y9r				(ValSft_R00(_rd32(_REG_BASE_+(0x0687<<2)))&BitMask_10)
#define LBURST_Y9w(val)			_wr32(_REG_BASE_+(0x0687<<2),(UINT)((_rd32(_REG_BASE_+(0x0687<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_Yar				(ValSft_R16(_rd32(_REG_BASE_+(0x0688<<2)))&BitMask_10)
#define LBURST_Yaw(val)			_wr32(_REG_BASE_+(0x0688<<2),(UINT)((_rd32(_REG_BASE_+(0x0688<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_Ybr				(ValSft_R00(_rd32(_REG_BASE_+(0x0688<<2)))&BitMask_10)
#define LBURST_Ybw(val)			_wr32(_REG_BASE_+(0x0688<<2),(UINT)((_rd32(_REG_BASE_+(0x0688<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_Ycr				(ValSft_R16(_rd32(_REG_BASE_+(0x0689<<2)))&BitMask_10)
#define LBURST_Ycw(val)			_wr32(_REG_BASE_+(0x0689<<2),(UINT)((_rd32(_REG_BASE_+(0x0689<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_Ydr				(ValSft_R00(_rd32(_REG_BASE_+(0x0689<<2)))&BitMask_10)
#define LBURST_Ydw(val)			_wr32(_REG_BASE_+(0x0689<<2),(UINT)((_rd32(_REG_BASE_+(0x0689<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_Yer				(ValSft_R16(_rd32(_REG_BASE_+(0x068a<<2)))&BitMask_10)
#define LBURST_Yew(val)			_wr32(_REG_BASE_+(0x068a<<2),(UINT)((_rd32(_REG_BASE_+(0x068a<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_Yfr				(ValSft_R00(_rd32(_REG_BASE_+(0x068a<<2)))&BitMask_10)
#define LBURST_Yfw(val)			_wr32(_REG_BASE_+(0x068a<<2),(UINT)((_rd32(_REG_BASE_+(0x068a<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define CTX_LVLr				(ValSft_R00(_rd32(_REG_BASE_+(0x068c<<2)))&BitMask_10)
#define CTX_LVLw(val)			_wr32(_REG_BASE_+(0x068c<<2),(UINT)((_rd32(_REG_BASE_+(0x068c<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define C_LPF_ONr				(ValSft_R12(_rd32(_REG_BASE_+(0x0691<<2)))&BitMask_03)
#define C_LPF_ONw(val)			_wr32(_REG_BASE_+(0x0691<<2),(UINT)((_rd32(_REG_BASE_+(0x0691<<2))&(~ValSft_L12(BitMask_03)))|ValSft_L12((val)&BitMask_03)))

#define BURST_FREEr				(ValSft_R11(_rd32(_REG_BASE_+(0x0691<<2)))&BitMask_01)
#define BURST_FREEw(val)		_wr32(_REG_BASE_+(0x0691<<2),(UINT)((_rd32(_REG_BASE_+(0x0691<<2))&(~ValSft_L11(BitMask_01)))|ValSft_L11((val)&BitMask_01)))

#define SIG_SELr				(ValSft_R04(_rd32(_REG_BASE_+(0x0691<<2)))&BitMask_05)
#define SIG_SELw(val)			_wr32(_REG_BASE_+(0x0691<<2),(UINT)((_rd32(_REG_BASE_+(0x0691<<2))&(~ValSft_L04(BitMask_05)))|ValSft_L04((val)&BitMask_05)))

#define C_SLEW_SELr				(ValSft_R00(_rd32(_REG_BASE_+(0x0691<<2)))&BitMask_02)
#define C_SLEW_SELw(val)		_wr32(_REG_BASE_+(0x0691<<2),(UINT)((_rd32(_REG_BASE_+(0x0691<<2))&(~ValSft_L00(BitMask_02)))|ValSft_L00((val)&BitMask_02)))

#define FSC_TGTr				(ValSft_R00(_rd32(_REG_BASE_+(0x0692<<2)))&BitMask_32)
#define FSC_TGTw(val)			_wr32(_REG_BASE_+(0x0692<<2),(UINT)((_rd32(_REG_BASE_+(0x0692<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define CB_BSTr					(ValSft_R16(_rd32(_REG_BASE_+(0x0693<<2)))&BitMask_10)
#define CB_BSTw(val)			_wr32(_REG_BASE_+(0x0693<<2),(UINT)((_rd32(_REG_BASE_+(0x0693<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define CR_BSTr					(ValSft_R00(_rd32(_REG_BASE_+(0x0693<<2)))&BitMask_10)
#define CR_BSTw(val)			_wr32(_REG_BASE_+(0x0693<<2),(UINT)((_rd32(_REG_BASE_+(0x0693<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define BURST_VRSTr				(ValSft_R00(_rd32(_REG_BASE_+(0x0694<<2)))&BitMask_11)
#define BURST_VRSTw(val)		_wr32(_REG_BASE_+(0x0694<<2),(UINT)((_rd32(_REG_BASE_+(0x0694<<2))&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define TSET_FSCr				(ValSft_R00(_rd32(_REG_BASE_+(0x0695<<2)))&BitMask_32)
#define TSET_FSCw(val)			_wr32(_REG_BASE_+(0x0695<<2),(UINT)((_rd32(_REG_BASE_+(0x0695<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define LBURST_CB0r				(ValSft_R16(_rd32(_REG_BASE_+(0x0696<<2)))&BitMask_10)
#define LBURST_CB0w(val)		_wr32(_REG_BASE_+(0x0696<<2),(UINT)((_rd32(_REG_BASE_+(0x0696<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_CB1r				(ValSft_R00(_rd32(_REG_BASE_+(0x0696<<2)))&BitMask_10)
#define LBURST_CB1w(val)		_wr32(_REG_BASE_+(0x0696<<2),(UINT)((_rd32(_REG_BASE_+(0x0696<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_CB2r				(ValSft_R16(_rd32(_REG_BASE_+(0x0697<<2)))&BitMask_10)
#define LBURST_CB2w(val)		_wr32(_REG_BASE_+(0x0697<<2),(UINT)((_rd32(_REG_BASE_+(0x0697<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_CB3r				(ValSft_R00(_rd32(_REG_BASE_+(0x0697<<2)))&BitMask_10)
#define LBURST_CB3w(val)		_wr32(_REG_BASE_+(0x0697<<2),(UINT)((_rd32(_REG_BASE_+(0x0697<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_CB4r				(ValSft_R16(_rd32(_REG_BASE_+(0x0698<<2)))&BitMask_10)
#define LBURST_CB4w(val)		_wr32(_REG_BASE_+(0x0698<<2),(UINT)((_rd32(_REG_BASE_+(0x0698<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_CB5r				(ValSft_R00(_rd32(_REG_BASE_+(0x0698<<2)))&BitMask_10)
#define LBURST_CB5w(val)		_wr32(_REG_BASE_+(0x0698<<2),(UINT)((_rd32(_REG_BASE_+(0x0698<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_CB6r				(ValSft_R16(_rd32(_REG_BASE_+(0x0699<<2)))&BitMask_10)
#define LBURST_CB6w(val)		_wr32(_REG_BASE_+(0x0699<<2),(UINT)((_rd32(_REG_BASE_+(0x0699<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_CB7r				(ValSft_R00(_rd32(_REG_BASE_+(0x0699<<2)))&BitMask_10)
#define LBURST_CB7w(val)		_wr32(_REG_BASE_+(0x0699<<2),(UINT)((_rd32(_REG_BASE_+(0x0699<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_CB8r				(ValSft_R16(_rd32(_REG_BASE_+(0x069a<<2)))&BitMask_10)
#define LBURST_CB8w(val)		_wr32(_REG_BASE_+(0x069a<<2),(UINT)((_rd32(_REG_BASE_+(0x069a<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_CB9r				(ValSft_R00(_rd32(_REG_BASE_+(0x069a<<2)))&BitMask_10)
#define LBURST_CB9w(val)		_wr32(_REG_BASE_+(0x069a<<2),(UINT)((_rd32(_REG_BASE_+(0x069a<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_CBar				(ValSft_R16(_rd32(_REG_BASE_+(0x069b<<2)))&BitMask_10)
#define LBURST_CBaw(val)		_wr32(_REG_BASE_+(0x069b<<2),(UINT)((_rd32(_REG_BASE_+(0x069b<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_CBbr				(ValSft_R00(_rd32(_REG_BASE_+(0x069b<<2)))&BitMask_10)
#define LBURST_CBbw(val)		_wr32(_REG_BASE_+(0x069b<<2),(UINT)((_rd32(_REG_BASE_+(0x069b<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_CBcr				(ValSft_R16(_rd32(_REG_BASE_+(0x069c<<2)))&BitMask_10)
#define LBURST_CBcw(val)		_wr32(_REG_BASE_+(0x069c<<2),(UINT)((_rd32(_REG_BASE_+(0x069c<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_CBdr				(ValSft_R00(_rd32(_REG_BASE_+(0x069c<<2)))&BitMask_10)
#define LBURST_CBdw(val)		_wr32(_REG_BASE_+(0x069c<<2),(UINT)((_rd32(_REG_BASE_+(0x069c<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_CBer				(ValSft_R16(_rd32(_REG_BASE_+(0x069d<<2)))&BitMask_10)
#define LBURST_CBew(val)		_wr32(_REG_BASE_+(0x069d<<2),(UINT)((_rd32(_REG_BASE_+(0x069d<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_CBfr				(ValSft_R00(_rd32(_REG_BASE_+(0x069d<<2)))&BitMask_10)
#define LBURST_CBfw(val)		_wr32(_REG_BASE_+(0x069d<<2),(UINT)((_rd32(_REG_BASE_+(0x069d<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_CR0r				(ValSft_R16(_rd32(_REG_BASE_+(0x06a1<<2)))&BitMask_10)
#define LBURST_CR0w(val)		_wr32(_REG_BASE_+(0x06a1<<2),(UINT)((_rd32(_REG_BASE_+(0x06a1<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_CR1r				(ValSft_R00(_rd32(_REG_BASE_+(0x06a1<<2)))&BitMask_10)
#define LBURST_CR1w(val)		_wr32(_REG_BASE_+(0x06a1<<2),(UINT)((_rd32(_REG_BASE_+(0x06a1<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_CR2r				(ValSft_R16(_rd32(_REG_BASE_+(0x06a2<<2)))&BitMask_10)
#define LBURST_CR2w(val)		_wr32(_REG_BASE_+(0x06a2<<2),(UINT)((_rd32(_REG_BASE_+(0x06a2<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_CR3r				(ValSft_R00(_rd32(_REG_BASE_+(0x06a2<<2)))&BitMask_10)
#define LBURST_CR3w(val)		_wr32(_REG_BASE_+(0x06a2<<2),(UINT)((_rd32(_REG_BASE_+(0x06a2<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_CR4r				(ValSft_R16(_rd32(_REG_BASE_+(0x06a3<<2)))&BitMask_10)
#define LBURST_CR4w(val)		_wr32(_REG_BASE_+(0x06a3<<2),(UINT)((_rd32(_REG_BASE_+(0x06a3<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_CR5r				(ValSft_R00(_rd32(_REG_BASE_+(0x06a3<<2)))&BitMask_10)
#define LBURST_CR5w(val)		_wr32(_REG_BASE_+(0x06a3<<2),(UINT)((_rd32(_REG_BASE_+(0x06a3<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_CR6r				(ValSft_R16(_rd32(_REG_BASE_+(0x06a4<<2)))&BitMask_10)
#define LBURST_CR6w(val)		_wr32(_REG_BASE_+(0x06a4<<2),(UINT)((_rd32(_REG_BASE_+(0x06a4<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_CR7r				(ValSft_R00(_rd32(_REG_BASE_+(0x06a4<<2)))&BitMask_10)
#define LBURST_CR7w(val)		_wr32(_REG_BASE_+(0x06a4<<2),(UINT)((_rd32(_REG_BASE_+(0x06a4<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_CR8r				(ValSft_R16(_rd32(_REG_BASE_+(0x06a5<<2)))&BitMask_10)
#define LBURST_CR8w(val)		_wr32(_REG_BASE_+(0x06a5<<2),(UINT)((_rd32(_REG_BASE_+(0x06a5<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_CR9r				(ValSft_R00(_rd32(_REG_BASE_+(0x06a5<<2)))&BitMask_10)
#define LBURST_CR9w(val)		_wr32(_REG_BASE_+(0x06a5<<2),(UINT)((_rd32(_REG_BASE_+(0x06a5<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_CRar				(ValSft_R16(_rd32(_REG_BASE_+(0x06a6<<2)))&BitMask_10)
#define LBURST_CRaw(val)		_wr32(_REG_BASE_+(0x06a6<<2),(UINT)((_rd32(_REG_BASE_+(0x06a6<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_CRbr				(ValSft_R00(_rd32(_REG_BASE_+(0x06a6<<2)))&BitMask_10)
#define LBURST_CRbw(val)		_wr32(_REG_BASE_+(0x06a6<<2),(UINT)((_rd32(_REG_BASE_+(0x06a6<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_CRcr				(ValSft_R16(_rd32(_REG_BASE_+(0x06a7<<2)))&BitMask_10)
#define LBURST_CRcw(val)		_wr32(_REG_BASE_+(0x06a7<<2),(UINT)((_rd32(_REG_BASE_+(0x06a7<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_CRdr				(ValSft_R00(_rd32(_REG_BASE_+(0x06a7<<2)))&BitMask_10)
#define LBURST_CRdw(val)		_wr32(_REG_BASE_+(0x06a7<<2),(UINT)((_rd32(_REG_BASE_+(0x06a7<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define LBURST_CRer				(ValSft_R16(_rd32(_REG_BASE_+(0x06a8<<2)))&BitMask_10)
#define LBURST_CRew(val)		_wr32(_REG_BASE_+(0x06a8<<2),(UINT)((_rd32(_REG_BASE_+(0x06a8<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define LBURST_CRfr				(ValSft_R00(_rd32(_REG_BASE_+(0x06a8<<2)))&BitMask_10)
#define LBURST_CRfw(val)		_wr32(_REG_BASE_+(0x06a8<<2),(UINT)((_rd32(_REG_BASE_+(0x06a8<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define AY_OSELr				(ValSft_R28(_rd32(_REG_BASE_+(0x06aa<<2)))&BitMask_03)
#define AY_OSELw(val)			_wr32(_REG_BASE_+(0x06aa<<2),(UINT)((_rd32(_REG_BASE_+(0x06aa<<2))&(~ValSft_L28(BitMask_03)))|ValSft_L28((val)&BitMask_03)))

#define AY_IORDERr				(ValSft_R27(_rd32(_REG_BASE_+(0x06aa<<2)))&BitMask_01)
#define AY_IORDERw(val)			_wr32(_REG_BASE_+(0x06aa<<2),(UINT)((_rd32(_REG_BASE_+(0x06aa<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define YC_LEVEL_TESTr			(ValSft_R00(_rd32(_REG_BASE_+(0x06aa<<2)))&BitMask_10)
#define YC_LEVEL_TESTw(val)		_wr32(_REG_BASE_+(0x06aa<<2),(UINT)((_rd32(_REG_BASE_+(0x06aa<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define DAC_RECLK_RSTr			(ValSft_R31(_rd32(_REG_BASE_+(0x06ab<<2)))&BitMask_01)
#define DAC_RECLK_RSTw(val)		_wr32(_REG_BASE_+(0x06ab<<2),(UINT)((_rd32(_REG_BASE_+(0x06ab<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DAC_RECLK_SELr			(ValSft_R28(_rd32(_REG_BASE_+(0x06ab<<2)))&BitMask_03)
#define DAC_RECLK_SELw(val)		_wr32(_REG_BASE_+(0x06ab<<2),(UINT)((_rd32(_REG_BASE_+(0x06ab<<2))&(~ValSft_L28(BitMask_03)))|ValSft_L28((val)&BitMask_03)))

#define DAC_OUT_POLr			(ValSft_R27(_rd32(_REG_BASE_+(0x06ab<<2)))&BitMask_01)
#define DAC_OUT_POLw(val)		_wr32(_REG_BASE_+(0x06ab<<2),(UINT)((_rd32(_REG_BASE_+(0x06ab<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define MTX_TSELr				(ValSft_R08(_rd32(_REG_BASE_+(0x06b0<<2)))&BitMask_01)
#define MTX_TSELw(val)			_wr32(_REG_BASE_+(0x06b0<<2),(UINT)((_rd32(_REG_BASE_+(0x06b0<<2))&(~ValSft_L08(BitMask_01)))|ValSft_L08((val)&BitMask_01)))

#define MTX_TBITr				(ValSft_R05(_rd32(_REG_BASE_+(0x06b0<<2)))&BitMask_03)
#define MTX_TBITw(val)			_wr32(_REG_BASE_+(0x06b0<<2),(UINT)((_rd32(_REG_BASE_+(0x06b0<<2))&(~ValSft_L05(BitMask_03)))|ValSft_L05((val)&BitMask_03)))

#define MTX_OSELr				(ValSft_R04(_rd32(_REG_BASE_+(0x06b0<<2)))&BitMask_01)
#define MTX_OSELw(val)			_wr32(_REG_BASE_+(0x06b0<<2),(UINT)((_rd32(_REG_BASE_+(0x06b0<<2))&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))

#define MTX_OBITr				(ValSft_R00(_rd32(_REG_BASE_+(0x06b0<<2)))&BitMask_04)
#define MTX_OBITw(val)			_wr32(_REG_BASE_+(0x06b0<<2),(UINT)((_rd32(_REG_BASE_+(0x06b0<<2))&(~ValSft_L00(BitMask_04)))|ValSft_L00((val)&BitMask_04)))

#define MTX_TESTr				(ValSft_R31(_rd32(_REG_BASE_+(0x06b1<<2)))&BitMask_01)
#define MTX_TESTw(val)			_wr32(_REG_BASE_+(0x06b1<<2),(UINT)((_rd32(_REG_BASE_+(0x06b1<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define MTX_TEST_RSTNr			(ValSft_R30(_rd32(_REG_BASE_+(0x06b1<<2)))&BitMask_01)
#define MTX_TEST_RSTNw(val)		_wr32(_REG_BASE_+(0x06b1<<2),(UINT)((_rd32(_REG_BASE_+(0x06b1<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define MTX_RSTNr				(ValSft_R29(_rd32(_REG_BASE_+(0x06b1<<2)))&BitMask_01)
#define MTX_RSTNw(val)			_wr32(_REG_BASE_+(0x06b1<<2),(UINT)((_rd32(_REG_BASE_+(0x06b1<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define MTX_MSBr				(ValSft_R28(_rd32(_REG_BASE_+(0x06b1<<2)))&BitMask_01)
#define MTX_MSBw(val)			_wr32(_REG_BASE_+(0x06b1<<2),(UINT)((_rd32(_REG_BASE_+(0x06b1<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define MTX_YC_ODRr				(ValSft_R26(_rd32(_REG_BASE_+(0x06b1<<2)))&BitMask_02)
#define MTX_YC_ODRw(val)		_wr32(_REG_BASE_+(0x06b1<<2),(UINT)((_rd32(_REG_BASE_+(0x06b1<<2))&(~ValSft_L26(BitMask_02)))|ValSft_L26((val)&BitMask_02)))

#define MTX_RDY_POLr			(ValSft_R25(_rd32(_REG_BASE_+(0x06b1<<2)))&BitMask_01)
#define MTX_RDY_POLw(val)		_wr32(_REG_BASE_+(0x06b1<<2),(UINT)((_rd32(_REG_BASE_+(0x06b1<<2))&(~ValSft_L25(BitMask_01)))|ValSft_L25((val)&BitMask_01)))

#define MTX_MEM_OPE_SELr		(ValSft_R23(_rd32(_REG_BASE_+(0x06b1<<2)))&BitMask_02)
#define MTX_MEM_OPE_SELw(val)	_wr32(_REG_BASE_+(0x06b1<<2),(UINT)((_rd32(_REG_BASE_+(0x06b1<<2))&(~ValSft_L23(BitMask_02)))|ValSft_L23((val)&BitMask_02)))

#define MTX_MEM_TOG_SELr		(ValSft_R21(_rd32(_REG_BASE_+(0x06b1<<2)))&BitMask_02)
#define MTX_MEM_TOG_SELw(val)	_wr32(_REG_BASE_+(0x06b1<<2),(UINT)((_rd32(_REG_BASE_+(0x06b1<<2))&(~ValSft_L21(BitMask_02)))|ValSft_L21((val)&BitMask_02)))

#define MTX0_SELr				(ValSft_R14(_rd32(_REG_BASE_+(0x06b1<<2)))&BitMask_02)
#define MTX0_SELw(val)			_wr32(_REG_BASE_+(0x06b1<<2),(UINT)((_rd32(_REG_BASE_+(0x06b1<<2))&(~ValSft_L14(BitMask_02)))|ValSft_L14((val)&BitMask_02)))

#define MTX1_SELr				(ValSft_R12(_rd32(_REG_BASE_+(0x06b1<<2)))&BitMask_02)
#define MTX1_SELw(val)			_wr32(_REG_BASE_+(0x06b1<<2),(UINT)((_rd32(_REG_BASE_+(0x06b1<<2))&(~ValSft_L12(BitMask_02)))|ValSft_L12((val)&BitMask_02)))

#define MTX2_SELr				(ValSft_R10(_rd32(_REG_BASE_+(0x06b1<<2)))&BitMask_02)
#define MTX2_SELw(val)			_wr32(_REG_BASE_+(0x06b1<<2),(UINT)((_rd32(_REG_BASE_+(0x06b1<<2))&(~ValSft_L10(BitMask_02)))|ValSft_L10((val)&BitMask_02)))

#define MTX3_SELr				(ValSft_R08(_rd32(_REG_BASE_+(0x06b1<<2)))&BitMask_02)
#define MTX3_SELw(val)			_wr32(_REG_BASE_+(0x06b1<<2),(UINT)((_rd32(_REG_BASE_+(0x06b1<<2))&(~ValSft_L08(BitMask_02)))|ValSft_L08((val)&BitMask_02)))

#define MTX_MLCK_POLr			(ValSft_R04(_rd32(_REG_BASE_+(0x06b1<<2)))&BitMask_01)
#define MTX_MLCK_POLw(val)		_wr32(_REG_BASE_+(0x06b1<<2),(UINT)((_rd32(_REG_BASE_+(0x06b1<<2))&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))

#define MTX_CLK_ONr				(ValSft_R03(_rd32(_REG_BASE_+(0x06b1<<2)))&BitMask_01)
#define MTX_CLK_ONw(val)		_wr32(_REG_BASE_+(0x06b1<<2),(UINT)((_rd32(_REG_BASE_+(0x06b1<<2))&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))

#define MTX_DATA_ONr			(ValSft_R02(_rd32(_REG_BASE_+(0x06b1<<2)))&BitMask_01)
#define MTX_DATA_ONw(val)		_wr32(_REG_BASE_+(0x06b1<<2),(UINT)((_rd32(_REG_BASE_+(0x06b1<<2))&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))

#define MTX_VCr					(ValSft_R00(_rd32(_REG_BASE_+(0x06b1<<2)))&BitMask_02)
#define MTX_VCw(val)			_wr32(_REG_BASE_+(0x06b1<<2),(UINT)((_rd32(_REG_BASE_+(0x06b1<<2))&(~ValSft_L00(BitMask_02)))|ValSft_L00((val)&BitMask_02)))

#define MTX_HLOCKW_POSr			(ValSft_R16(_rd32(_REG_BASE_+(0x06b2<<2)))&BitMask_13)
#define MTX_HLOCKW_POSw(val)	_wr32(_REG_BASE_+(0x06b2<<2),(UINT)((_rd32(_REG_BASE_+(0x06b2<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define MTX_VLOCKW_POSr			(ValSft_R00(_rd32(_REG_BASE_+(0x06b2<<2)))&BitMask_13)
#define MTX_VLOCKW_POSw(val)	_wr32(_REG_BASE_+(0x06b2<<2),(UINT)((_rd32(_REG_BASE_+(0x06b2<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define MTX_LINE_OPTr			(ValSft_R31(_rd32(_REG_BASE_+(0x06b8<<2)))&BitMask_01)
#define MTX_LINE_OPTw(val)		_wr32(_REG_BASE_+(0x06b8<<2),(UINT)((_rd32(_REG_BASE_+(0x06b8<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define MTX_MODr				(ValSft_R29(_rd32(_REG_BASE_+(0x06b8<<2)))&BitMask_02)
#define MTX_MODw(val)			_wr32(_REG_BASE_+(0x06b8<<2),(UINT)((_rd32(_REG_BASE_+(0x06b8<<2))&(~ValSft_L29(BitMask_02)))|ValSft_L29((val)&BitMask_02)))

#define MTX_LANE_HWIr			(ValSft_R16(_rd32(_REG_BASE_+(0x06b8<<2)))&BitMask_13)
#define MTX_LANE_HWIw(val)		_wr32(_REG_BASE_+(0x06b8<<2),(UINT)((_rd32(_REG_BASE_+(0x06b8<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define MTX_LANEr				(ValSft_R08(_rd32(_REG_BASE_+(0x06b8<<2)))&BitMask_03)
#define MTX_LANEw(val)			_wr32(_REG_BASE_+(0x06b8<<2),(UINT)((_rd32(_REG_BASE_+(0x06b8<<2))&(~ValSft_L08(BitMask_03)))|ValSft_L08((val)&BitMask_03)))

#define MTX_DT_Lr				(ValSft_R00(_rd32(_REG_BASE_+(0x06b8<<2)))&BitMask_06)
#define MTX_DT_Lw(val)			_wr32(_REG_BASE_+(0x06b8<<2),(UINT)((_rd32(_REG_BASE_+(0x06b8<<2))&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define MTX_DT_VSr				(ValSft_R24(_rd32(_REG_BASE_+(0x06b9<<2)))&BitMask_06)
#define MTX_DT_VSw(val)			_wr32(_REG_BASE_+(0x06b9<<2),(UINT)((_rd32(_REG_BASE_+(0x06b9<<2))&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define MTX_DT_VEr				(ValSft_R16(_rd32(_REG_BASE_+(0x06b9<<2)))&BitMask_06)
#define MTX_DT_VEw(val)			_wr32(_REG_BASE_+(0x06b9<<2),(UINT)((_rd32(_REG_BASE_+(0x06b9<<2))&(~ValSft_L16(BitMask_06)))|ValSft_L16((val)&BitMask_06)))

#define MTX_DT_HSr				(ValSft_R08(_rd32(_REG_BASE_+(0x06b9<<2)))&BitMask_06)
#define MTX_DT_HSw(val)			_wr32(_REG_BASE_+(0x06b9<<2),(UINT)((_rd32(_REG_BASE_+(0x06b9<<2))&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define MTX_DT_HEr				(ValSft_R00(_rd32(_REG_BASE_+(0x06b9<<2)))&BitMask_06)
#define MTX_DT_HEw(val)			_wr32(_REG_BASE_+(0x06b9<<2),(UINT)((_rd32(_REG_BASE_+(0x06b9<<2))&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define MTX_ENr					(ValSft_R28(_rd32(_REG_BASE_+(0x06ba<<2)))&BitMask_04)
#define MTX_ENw(val)			_wr32(_REG_BASE_+(0x06ba<<2),(UINT)((_rd32(_REG_BASE_+(0x06ba<<2))&(~ValSft_L28(BitMask_04)))|ValSft_L28((val)&BitMask_04)))

#define MTX_SAP_TLPX_Dr			(ValSft_R24(_rd32(_REG_BASE_+(0x06ba<<2)))&BitMask_04)
#define MTX_SAP_TLPX_Dw(val)	_wr32(_REG_BASE_+(0x06ba<<2),(UINT)((_rd32(_REG_BASE_+(0x06ba<<2))&(~ValSft_L24(BitMask_04)))|ValSft_L24((val)&BitMask_04)))

#define MTX_ULPS_CLKr			(ValSft_R23(_rd32(_REG_BASE_+(0x06ba<<2)))&BitMask_01)
#define MTX_ULPS_CLKw(val)		_wr32(_REG_BASE_+(0x06ba<<2),(UINT)((_rd32(_REG_BASE_+(0x06ba<<2))&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define MTX_SAP_HS0_Dr			(ValSft_R16(_rd32(_REG_BASE_+(0x06ba<<2)))&BitMask_05)
#define MTX_SAP_HS0_Dw(val)		_wr32(_REG_BASE_+(0x06ba<<2),(UINT)((_rd32(_REG_BASE_+(0x06ba<<2))&(~ValSft_L16(BitMask_05)))|ValSft_L16((val)&BitMask_05)))

#define MTX_SAP_PRE_Dr			(ValSft_R08(_rd32(_REG_BASE_+(0x06ba<<2)))&BitMask_05)
#define MTX_SAP_PRE_Dw(val)		_wr32(_REG_BASE_+(0x06ba<<2),(UINT)((_rd32(_REG_BASE_+(0x06ba<<2))&(~ValSft_L08(BitMask_05)))|ValSft_L08((val)&BitMask_05)))

#define MTX_SAP_TRAIL_Dr		(ValSft_R00(_rd32(_REG_BASE_+(0x06ba<<2)))&BitMask_04)
#define MTX_SAP_TRAIL_Dw(val)	_wr32(_REG_BASE_+(0x06ba<<2),(UINT)((_rd32(_REG_BASE_+(0x06ba<<2))&(~ValSft_L00(BitMask_04)))|ValSft_L00((val)&BitMask_04)))

#define MTX_SAP_TLPX_Cr			(ValSft_R24(_rd32(_REG_BASE_+(0x06bb<<2)))&BitMask_04)
#define MTX_SAP_TLPX_Cw(val)	_wr32(_REG_BASE_+(0x06bb<<2),(UINT)((_rd32(_REG_BASE_+(0x06bb<<2))&(~ValSft_L24(BitMask_04)))|ValSft_L24((val)&BitMask_04)))

#define MTX_SAP_HS0_Cr			(ValSft_R16(_rd32(_REG_BASE_+(0x06bb<<2)))&BitMask_06)
#define MTX_SAP_HS0_Cw(val)		_wr32(_REG_BASE_+(0x06bb<<2),(UINT)((_rd32(_REG_BASE_+(0x06bb<<2))&(~ValSft_L16(BitMask_06)))|ValSft_L16((val)&BitMask_06)))

#define MTX_SAP_TRAIL_Cr		(ValSft_R08(_rd32(_REG_BASE_+(0x06bb<<2)))&BitMask_04)
#define MTX_SAP_TRAIL_Cw(val)	_wr32(_REG_BASE_+(0x06bb<<2),(UINT)((_rd32(_REG_BASE_+(0x06bb<<2))&(~ValSft_L08(BitMask_04)))|ValSft_L08((val)&BitMask_04)))

#define MTX_SAP_PRE_Cr			(ValSft_R00(_rd32(_REG_BASE_+(0x06bb<<2)))&BitMask_05)
#define MTX_SAP_PRE_Cw(val)		_wr32(_REG_BASE_+(0x06bb<<2),(UINT)((_rd32(_REG_BASE_+(0x06bb<<2))&(~ValSft_L00(BitMask_05)))|ValSft_L00((val)&BitMask_05)))

#define MTX_SYNC_UPr			(ValSft_R31(_rd32(_REG_BASE_+(0x06bc<<2)))&BitMask_01)
#define MTX_SYNC_UPw(val)		_wr32(_REG_BASE_+(0x06bc<<2),(UINT)((_rd32(_REG_BASE_+(0x06bc<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define MTX_SYNC_AUTOr			(ValSft_R30(_rd32(_REG_BASE_+(0x06bc<<2)))&BitMask_01)
#define MTX_SYNC_AUTOw(val)		_wr32(_REG_BASE_+(0x06bc<<2),(UINT)((_rd32(_REG_BASE_+(0x06bc<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define MTX_SYNC_THr			(ValSft_R00(_rd32(_REG_BASE_+(0x06bd<<2)))&BitMask_32)
#define MTX_SYNC_THw(val)		_wr32(_REG_BASE_+(0x06bd<<2),(UINT)((_rd32(_REG_BASE_+(0x06bd<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define MTX_WC_SELr				(ValSft_R31(_rd32(_REG_BASE_+(0x06be<<2)))&BitMask_01)
#define MTX_WC_SELw(val)		_wr32(_REG_BASE_+(0x06be<<2),(UINT)((_rd32(_REG_BASE_+(0x06be<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define MTX_CRC_ODRr			(ValSft_R29(_rd32(_REG_BASE_+(0x06be<<2)))&BitMask_02)
#define MTX_CRC_ODRw(val)		_wr32(_REG_BASE_+(0x06be<<2),(UINT)((_rd32(_REG_BASE_+(0x06be<<2))&(~ValSft_L29(BitMask_02)))|ValSft_L29((val)&BitMask_02)))

#define MTX_WC_Lr				(ValSft_R16(_rd32(_REG_BASE_+(0x06bf<<2)))&BitMask_16)
#define MTX_WC_Lw(val)			_wr32(_REG_BASE_+(0x06bf<<2),(UINT)((_rd32(_REG_BASE_+(0x06bf<<2))&(~ValSft_L16(BitMask_16)))|ValSft_L16((val)&BitMask_16)))

#define MTX_WC_Sr				(ValSft_R00(_rd32(_REG_BASE_+(0x06bf<<2)))&BitMask_16)
#define MTX_WC_Sw(val)			_wr32(_REG_BASE_+(0x06bf<<2),(UINT)((_rd32(_REG_BASE_+(0x06bf<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define MTX_HTWIr				(ValSft_R16(_rd32(_REG_BASE_+(0x06c0<<2)))&BitMask_13)
#define MTX_HTWIw(val)			_wr32(_REG_BASE_+(0x06c0<<2),(UINT)((_rd32(_REG_BASE_+(0x06c0<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define MTX_VTWIr				(ValSft_R00(_rd32(_REG_BASE_+(0x06c0<<2)))&BitMask_13)
#define MTX_VTWIw(val)			_wr32(_REG_BASE_+(0x06c0<<2),(UINT)((_rd32(_REG_BASE_+(0x06c0<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define MTX_READ_HWIr			(ValSft_R16(_rd32(_REG_BASE_+(0x06c1<<2)))&BitMask_13)
#define MTX_READ_HWIw(val)		_wr32(_REG_BASE_+(0x06c1<<2),(UINT)((_rd32(_REG_BASE_+(0x06c1<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define MTX_READ_VWIr			(ValSft_R00(_rd32(_REG_BASE_+(0x06c1<<2)))&BitMask_13)
#define MTX_READ_VWIw(val)		_wr32(_REG_BASE_+(0x06c1<<2),(UINT)((_rd32(_REG_BASE_+(0x06c1<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define MTX_WRITE_HWIr			(ValSft_R16(_rd32(_REG_BASE_+(0x06c2<<2)))&BitMask_13)
#define MTX_WRITE_HWIw(val)		_wr32(_REG_BASE_+(0x06c2<<2),(UINT)((_rd32(_REG_BASE_+(0x06c2<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define MTX_WRITE_VWIr			(ValSft_R00(_rd32(_REG_BASE_+(0x06c2<<2)))&BitMask_13)
#define MTX_WRITE_VWIw(val)		_wr32(_REG_BASE_+(0x06c2<<2),(UINT)((_rd32(_REG_BASE_+(0x06c2<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define MTX_FSYNC_ALNr			(ValSft_R31(_rd32(_REG_BASE_+(0x06c3<<2)))&BitMask_01)
#define MTX_FSYNC_ALNw(val)		_wr32(_REG_BASE_+(0x06c3<<2),(UINT)((_rd32(_REG_BASE_+(0x06c3<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define MTX_HSYNC_ALNr			(ValSft_R30(_rd32(_REG_BASE_+(0x06c3<<2)))&BitMask_01)
#define MTX_HSYNC_ALNw(val)		_wr32(_REG_BASE_+(0x06c3<<2),(UINT)((_rd32(_REG_BASE_+(0x06c3<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define MTX_HLOCKR_POSr			(ValSft_R16(_rd32(_REG_BASE_+(0x06c3<<2)))&BitMask_13)
#define MTX_HLOCKR_POSw(val)	_wr32(_REG_BASE_+(0x06c3<<2),(UINT)((_rd32(_REG_BASE_+(0x06c3<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define MTX_VLOCKR_POSr			(ValSft_R00(_rd32(_REG_BASE_+(0x06c3<<2)))&BitMask_13)
#define MTX_VLOCKR_POSw(val)	_wr32(_REG_BASE_+(0x06c3<<2),(UINT)((_rd32(_REG_BASE_+(0x06c3<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define MTX_CSI_READ_HPOSr		(ValSft_R16(_rd32(_REG_BASE_+(0x06c4<<2)))&BitMask_13)
#define MTX_CSI_READ_HPOSw(val)	_wr32(_REG_BASE_+(0x06c4<<2),(UINT)((_rd32(_REG_BASE_+(0x06c4<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define MTX_CSI_READ_VPOSr		(ValSft_R00(_rd32(_REG_BASE_+(0x06c4<<2)))&BitMask_13)
#define MTX_CSI_READ_VPOSw(val)	_wr32(_REG_BASE_+(0x06c4<<2),(UINT)((_rd32(_REG_BASE_+(0x06c4<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define MTX_CSI_WRITE_HPOSr		(ValSft_R16(_rd32(_REG_BASE_+(0x06c5<<2)))&BitMask_13)
#define MTX_CSI_WRITE_HPOSw(val)	_wr32(_REG_BASE_+(0x06c5<<2),(UINT)((_rd32(_REG_BASE_+(0x06c5<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define MTX_CSI_WRITE_VPOSr		(ValSft_R00(_rd32(_REG_BASE_+(0x06c5<<2)))&BitMask_13)
#define MTX_CSI_WRITE_VPOSw(val)	_wr32(_REG_BASE_+(0x06c5<<2),(UINT)((_rd32(_REG_BASE_+(0x06c5<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define MTX_CSI_READ_MASKr		(ValSft_R31(_rd32(_REG_BASE_+(0x06c6<<2)))&BitMask_01)
#define MTX_CSI_READ_MASKw(val)	_wr32(_REG_BASE_+(0x06c6<<2),(UINT)((_rd32(_REG_BASE_+(0x06c6<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define MTX_CSI_READ_HSP_MASKr	(ValSft_R16(_rd32(_REG_BASE_+(0x06c6<<2)))&BitMask_13)
#define MTX_CSI_READ_HSP_MASKw(val)	_wr32(_REG_BASE_+(0x06c6<<2),(UINT)((_rd32(_REG_BASE_+(0x06c6<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define MTX_CSI_READ_VSP_MASKr	(ValSft_R00(_rd32(_REG_BASE_+(0x06c6<<2)))&BitMask_13)
#define MTX_CSI_READ_VSP_MASKw(val)	_wr32(_REG_BASE_+(0x06c6<<2),(UINT)((_rd32(_REG_BASE_+(0x06c6<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define MTX_CSI_READ_HPOS_MASKr	(ValSft_R16(_rd32(_REG_BASE_+(0x06c7<<2)))&BitMask_13)
#define MTX_CSI_READ_HPOS_MASKw(val)	_wr32(_REG_BASE_+(0x06c7<<2),(UINT)((_rd32(_REG_BASE_+(0x06c7<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define MTX_CSI_READ_VPOS_MASKr	(ValSft_R00(_rd32(_REG_BASE_+(0x06c7<<2)))&BitMask_13)
#define MTX_CSI_READ_VPOS_MASKw(val)	_wr32(_REG_BASE_+(0x06c7<<2),(UINT)((_rd32(_REG_BASE_+(0x06c7<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define TX_CLK_ESCr				(ValSft_R31(_rd32(_REG_BASE_+(0x06e0<<2)))&BitMask_01)
#define TX_CLK_ESCw(val)		_wr32(_REG_BASE_+(0x06e0<<2),(UINT)((_rd32(_REG_BASE_+(0x06e0<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define TX_REQ_ESCr				(ValSft_R27(_rd32(_REG_BASE_+(0x06e0<<2)))&BitMask_04)
#define TX_REQ_ESCw(val)		_wr32(_REG_BASE_+(0x06e0<<2),(UINT)((_rd32(_REG_BASE_+(0x06e0<<2))&(~ValSft_L27(BitMask_04)))|ValSft_L27((val)&BitMask_04)))

#define TX_LPDT_ESCr			(ValSft_R23(_rd32(_REG_BASE_+(0x06e0<<2)))&BitMask_04)
#define TX_LPDT_ESCw(val)		_wr32(_REG_BASE_+(0x06e0<<2),(UINT)((_rd32(_REG_BASE_+(0x06e0<<2))&(~ValSft_L23(BitMask_04)))|ValSft_L23((val)&BitMask_04)))

#define TX_ULP_EXIT_Dr			(ValSft_R19(_rd32(_REG_BASE_+(0x06e0<<2)))&BitMask_04)
#define TX_ULP_EXIT_Dw(val)		_wr32(_REG_BASE_+(0x06e0<<2),(UINT)((_rd32(_REG_BASE_+(0x06e0<<2))&(~ValSft_L19(BitMask_04)))|ValSft_L19((val)&BitMask_04)))

#define TX_ULP_EXIT_Cr			(ValSft_R18(_rd32(_REG_BASE_+(0x06e0<<2)))&BitMask_01)
#define TX_ULP_EXIT_Cw(val)		_wr32(_REG_BASE_+(0x06e0<<2),(UINT)((_rd32(_REG_BASE_+(0x06e0<<2))&(~ValSft_L18(BitMask_01)))|ValSft_L18((val)&BitMask_01)))

#define TX_ULPS_ESCr			(ValSft_R14(_rd32(_REG_BASE_+(0x06e0<<2)))&BitMask_04)
#define TX_ULPS_ESCw(val)		_wr32(_REG_BASE_+(0x06e0<<2),(UINT)((_rd32(_REG_BASE_+(0x06e0<<2))&(~ValSft_L14(BitMask_04)))|ValSft_L14((val)&BitMask_04)))

#define TX_VALID_ESCr			(ValSft_R28(_rd32(_REG_BASE_+(0x06e1<<2)))&BitMask_04)
#define TX_VALID_ESCw(val)		_wr32(_REG_BASE_+(0x06e1<<2),(UINT)((_rd32(_REG_BASE_+(0x06e1<<2))&(~ValSft_L28(BitMask_04)))|ValSft_L28((val)&BitMask_04)))

#define TX_TRIG_ESCr			(ValSft_R00(_rd32(_REG_BASE_+(0x06e1<<2)))&BitMask_16)
#define TX_TRIG_ESCw(val)		_wr32(_REG_BASE_+(0x06e1<<2),(UINT)((_rd32(_REG_BASE_+(0x06e1<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define TX_DATA_ESCr			(ValSft_R00(_rd32(_REG_BASE_+(0x06e2<<2)))&BitMask_32)
#define TX_DATA_ESCw(val)		_wr32(_REG_BASE_+(0x06e2<<2),(UINT)((_rd32(_REG_BASE_+(0x06e2<<2))&(~ValSft_L00(BitMask_32)))|ValSft_L00((val)&BitMask_32)))

#define MTX_PCr					(ValSft_R23(_rd32(_REG_BASE_+(0x06e3<<2)))&BitMask_01)
#define MTX_PCw(val)			_wr32(_REG_BASE_+(0x06e3<<2),(UINT)((_rd32(_REG_BASE_+(0x06e3<<2))&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define MTX_EFNr				(ValSft_R20(_rd32(_REG_BASE_+(0x06e3<<2)))&BitMask_03)
#define MTX_EFNw(val)			_wr32(_REG_BASE_+(0x06e3<<2),(UINT)((_rd32(_REG_BASE_+(0x06e3<<2))&(~ValSft_L20(BitMask_03)))|ValSft_L20((val)&BitMask_03)))

#define MTX_CTL_CLKr			(ValSft_R17(_rd32(_REG_BASE_+(0x06e3<<2)))&BitMask_03)
#define MTX_CTL_CLKw(val)		_wr32(_REG_BASE_+(0x06e3<<2),(UINT)((_rd32(_REG_BASE_+(0x06e3<<2))&(~ValSft_L17(BitMask_03)))|ValSft_L17((val)&BitMask_03)))

#define MTX_CTL_D0r				(ValSft_R14(_rd32(_REG_BASE_+(0x06e3<<2)))&BitMask_03)
#define MTX_CTL_D0w(val)		_wr32(_REG_BASE_+(0x06e3<<2),(UINT)((_rd32(_REG_BASE_+(0x06e3<<2))&(~ValSft_L14(BitMask_03)))|ValSft_L14((val)&BitMask_03)))

#define MTX_CTL_D1r				(ValSft_R11(_rd32(_REG_BASE_+(0x06e3<<2)))&BitMask_03)
#define MTX_CTL_D1w(val)		_wr32(_REG_BASE_+(0x06e3<<2),(UINT)((_rd32(_REG_BASE_+(0x06e3<<2))&(~ValSft_L11(BitMask_03)))|ValSft_L11((val)&BitMask_03)))

#define MTX_CTL_D2r				(ValSft_R08(_rd32(_REG_BASE_+(0x06e3<<2)))&BitMask_03)
#define MTX_CTL_D2w(val)		_wr32(_REG_BASE_+(0x06e3<<2),(UINT)((_rd32(_REG_BASE_+(0x06e3<<2))&(~ValSft_L08(BitMask_03)))|ValSft_L08((val)&BitMask_03)))

#define MTX_CTL_D3r				(ValSft_R05(_rd32(_REG_BASE_+(0x06e3<<2)))&BitMask_03)
#define MTX_CTL_D3w(val)		_wr32(_REG_BASE_+(0x06e3<<2),(UINT)((_rd32(_REG_BASE_+(0x06e3<<2))&(~ValSft_L05(BitMask_03)))|ValSft_L05((val)&BitMask_03)))

#define MTX_SUSPTr				(ValSft_R31(_rd32(_REG_BASE_+(0x06e4<<2)))&BitMask_01)
#define MTX_SUSPTw(val)			_wr32(_REG_BASE_+(0x06e4<<2),(UINT)((_rd32(_REG_BASE_+(0x06e4<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define MTX_CHTr				(ValSft_R30(_rd32(_REG_BASE_+(0x06e4<<2)))&BitMask_01)
#define MTX_CHTw(val)			_wr32(_REG_BASE_+(0x06e4<<2),(UINT)((_rd32(_REG_BASE_+(0x06e4<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define MTX_ALPr				(ValSft_R29(_rd32(_REG_BASE_+(0x06e4<<2)))&BitMask_01)
#define MTX_ALPw(val)			_wr32(_REG_BASE_+(0x06e4<<2),(UINT)((_rd32(_REG_BASE_+(0x06e4<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define MTX_ALNr				(ValSft_R28(_rd32(_REG_BASE_+(0x06e4<<2)))&BitMask_01)
#define MTX_ALNw(val)			_wr32(_REG_BASE_+(0x06e4<<2),(UINT)((_rd32(_REG_BASE_+(0x06e4<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define MTX_CLTr				(ValSft_R27(_rd32(_REG_BASE_+(0x06e4<<2)))&BitMask_01)
#define MTX_CLTw(val)			_wr32(_REG_BASE_+(0x06e4<<2),(UINT)((_rd32(_REG_BASE_+(0x06e4<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define MTX_HS_MODEr			(ValSft_R26(_rd32(_REG_BASE_+(0x06e4<<2)))&BitMask_01)
#define MTX_HS_MODEw(val)		_wr32(_REG_BASE_+(0x06e4<<2),(UINT)((_rd32(_REG_BASE_+(0x06e4<<2))&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define MTX_HS_DINr				(ValSft_R23(_rd32(_REG_BASE_+(0x06e4<<2)))&BitMask_03)
#define MTX_HS_DINw(val)		_wr32(_REG_BASE_+(0x06e4<<2),(UINT)((_rd32(_REG_BASE_+(0x06e4<<2))&(~ValSft_L23(BitMask_03)))|ValSft_L23((val)&BitMask_03)))

#define SDI_CINVr				(ValSft_R13(_rd32(_REG_BASE_+(0x0701<<2)))&BitMask_01)
#define SDI_CINVw(val)			_wr32(_REG_BASE_+(0x0701<<2),(UINT)((_rd32(_REG_BASE_+(0x0701<<2))&(~ValSft_L13(BitMask_01)))|ValSft_L13((val)&BitMask_01)))

#define SDI_OSELr				(ValSft_R12(_rd32(_REG_BASE_+(0x0701<<2)))&BitMask_01)
#define SDI_OSELw(val)			_wr32(_REG_BASE_+(0x0701<<2),(UINT)((_rd32(_REG_BASE_+(0x0701<<2))&(~ValSft_L12(BitMask_01)))|ValSft_L12((val)&BitMask_01)))

#define SDI_OBITr				(ValSft_R04(_rd32(_REG_BASE_+(0x0701<<2)))&BitMask_05)
#define SDI_OBITw(val)			_wr32(_REG_BASE_+(0x0701<<2),(UINT)((_rd32(_REG_BASE_+(0x0701<<2))&(~ValSft_L04(BitMask_05)))|ValSft_L04((val)&BitMask_05)))

#define ENC_VDI_SELr			(ValSft_R03(_rd32(_REG_BASE_+(0x0701<<2)))&BitMask_01)
#define ENC_VDI_SELw(val)		_wr32(_REG_BASE_+(0x0701<<2),(UINT)((_rd32(_REG_BASE_+(0x0701<<2))&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))

#define EXE_ANC_SELr			(ValSft_R02(_rd32(_REG_BASE_+(0x0701<<2)))&BitMask_01)
#define EXE_ANC_SELw(val)		_wr32(_REG_BASE_+(0x0701<<2),(UINT)((_rd32(_REG_BASE_+(0x0701<<2))&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))

#define ENC_ANC0_SELr			(ValSft_R01(_rd32(_REG_BASE_+(0x0701<<2)))&BitMask_01)
#define ENC_ANC0_SELw(val)		_wr32(_REG_BASE_+(0x0701<<2),(UINT)((_rd32(_REG_BASE_+(0x0701<<2))&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define ENC_ANC1_SELr			(ValSft_R00(_rd32(_REG_BASE_+(0x0701<<2)))&BitMask_01)
#define ENC_ANC1_SELw(val)		_wr32(_REG_BASE_+(0x0701<<2),(UINT)((_rd32(_REG_BASE_+(0x0701<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define SDI_INTRr				(ValSft_R31(_rd32(_REG_BASE_+(0x0711<<2)))&BitMask_01)
#define SDI_INTRw(val)			_wr32(_REG_BASE_+(0x0711<<2),(UINT)((_rd32(_REG_BASE_+(0x0711<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define HLOCKO_IT_POSr			(ValSft_R16(_rd32(_REG_BASE_+(0x0712<<2)))&BitMask_13)
#define HLOCKO_IT_POSw(val)		_wr32(_REG_BASE_+(0x0712<<2),(UINT)((_rd32(_REG_BASE_+(0x0712<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define VLOCKO_IT_POS_EVr		(ValSft_R16(_rd32(_REG_BASE_+(0x0713<<2)))&BitMask_13)
#define VLOCKO_IT_POS_EVw(val)	_wr32(_REG_BASE_+(0x0713<<2),(UINT)((_rd32(_REG_BASE_+(0x0713<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define VLOCKO_IT_POS_ODr		(ValSft_R00(_rd32(_REG_BASE_+(0x0713<<2)))&BitMask_13)
#define VLOCKO_IT_POS_ODw(val)	_wr32(_REG_BASE_+(0x0713<<2),(UINT)((_rd32(_REG_BASE_+(0x0713<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define HSPCr					(ValSft_R16(_rd32(_REG_BASE_+(0x0714<<2)))&BitMask_13)
#define HSPCw(val)				_wr32(_REG_BASE_+(0x0714<<2),(UINT)((_rd32(_REG_BASE_+(0x0714<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define VSPCr					(ValSft_R00(_rd32(_REG_BASE_+(0x0714<<2)))&BitMask_13)
#define VSPCw(val)				_wr32(_REG_BASE_+(0x0714<<2),(UINT)((_rd32(_REG_BASE_+(0x0714<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define HWCr					(ValSft_R16(_rd32(_REG_BASE_+(0x0715<<2)))&BitMask_13)
#define HWCw(val)				_wr32(_REG_BASE_+(0x0715<<2),(UINT)((_rd32(_REG_BASE_+(0x0715<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define VWCr					(ValSft_R00(_rd32(_REG_BASE_+(0x0715<<2)))&BitMask_13)
#define VWCw(val)				_wr32(_REG_BASE_+(0x0715<<2),(UINT)((_rd32(_REG_BASE_+(0x0715<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define ITU_MASKr				(ValSft_R31(_rd32(_REG_BASE_+(0x0716<<2)))&BitMask_01)
#define ITU_MASKw(val)			_wr32(_REG_BASE_+(0x0716<<2),(UINT)((_rd32(_REG_BASE_+(0x0716<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define HSPC_MASKr				(ValSft_R16(_rd32(_REG_BASE_+(0x0716<<2)))&BitMask_13)
#define HSPC_MASKw(val)			_wr32(_REG_BASE_+(0x0716<<2),(UINT)((_rd32(_REG_BASE_+(0x0716<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define VSPC_MASKr				(ValSft_R00(_rd32(_REG_BASE_+(0x0716<<2)))&BitMask_13)
#define VSPC_MASKw(val)			_wr32(_REG_BASE_+(0x0716<<2),(UINT)((_rd32(_REG_BASE_+(0x0716<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define HWC_MASKr				(ValSft_R16(_rd32(_REG_BASE_+(0x0717<<2)))&BitMask_13)
#define HWC_MASKw(val)			_wr32(_REG_BASE_+(0x0717<<2),(UINT)((_rd32(_REG_BASE_+(0x0717<<2))&(~ValSft_L16(BitMask_13)))|ValSft_L16((val)&BitMask_13)))

#define VWC_MASKr				(ValSft_R00(_rd32(_REG_BASE_+(0x0717<<2)))&BitMask_13)
#define VWC_MASKw(val)			_wr32(_REG_BASE_+(0x0717<<2),(UINT)((_rd32(_REG_BASE_+(0x0717<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define JLDO_INV2r				(ValSft_R01(_rd32(_REG_BASE_+(0x0718<<2)))&BitMask_01)
#define JLDO_INV2w(val)			_wr32(_REG_BASE_+(0x0718<<2),(UINT)((_rd32(_REG_BASE_+(0x0718<<2))&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define JLDO_INV3r				(ValSft_R00(_rd32(_REG_BASE_+(0x0718<<2)))&BitMask_01)
#define JLDO_INV3w(val)			_wr32(_REG_BASE_+(0x0718<<2),(UINT)((_rd32(_REG_BASE_+(0x0718<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define LAST_YCGONr				(ValSft_R31(_rd32(_REG_BASE_+(0x0719<<2)))&BitMask_01)
#define LAST_YCGONw(val)		_wr32(_REG_BASE_+(0x0719<<2),(UINT)((_rd32(_REG_BASE_+(0x0719<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define LAST_YCLIPr				(ValSft_R24(_rd32(_REG_BASE_+(0x071a<<2)))&BitMask_08)
#define LAST_YCLIPw(val)		_wr32(_REG_BASE_+(0x071a<<2),(UINT)((_rd32(_REG_BASE_+(0x071a<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define LAST_YSLICr				(ValSft_R16(_rd32(_REG_BASE_+(0x071a<<2)))&BitMask_08)
#define LAST_YSLICw(val)		_wr32(_REG_BASE_+(0x071a<<2),(UINT)((_rd32(_REG_BASE_+(0x071a<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define LAST_YOFFSr				(ValSft_R08(_rd32(_REG_BASE_+(0x071a<<2)))&BitMask_08)
#define LAST_YOFFSw(val)		_wr32(_REG_BASE_+(0x071a<<2),(UINT)((_rd32(_REG_BASE_+(0x071a<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define LAST_CBGAINr			(ValSft_R00(_rd32(_REG_BASE_+(0x071a<<2)))&BitMask_08)
#define LAST_CBGAINw(val)		_wr32(_REG_BASE_+(0x071a<<2),(UINT)((_rd32(_REG_BASE_+(0x071a<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define LAST_CRGAINr			(ValSft_R24(_rd32(_REG_BASE_+(0x071b<<2)))&BitMask_08)
#define LAST_CRGAINw(val)		_wr32(_REG_BASE_+(0x071b<<2),(UINT)((_rd32(_REG_BASE_+(0x071b<<2))&(~ValSft_L24(BitMask_08)))|ValSft_L24((val)&BitMask_08)))

#define LAST_YGAINr				(ValSft_R16(_rd32(_REG_BASE_+(0x071b<<2)))&BitMask_08)
#define LAST_YGAINw(val)		_wr32(_REG_BASE_+(0x071b<<2),(UINT)((_rd32(_REG_BASE_+(0x071b<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define LAST_CCLIPr				(ValSft_R08(_rd32(_REG_BASE_+(0x071b<<2)))&BitMask_08)
#define LAST_CCLIPw(val)		_wr32(_REG_BASE_+(0x071b<<2),(UINT)((_rd32(_REG_BASE_+(0x071b<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define LAST_CSLICr				(ValSft_R00(_rd32(_REG_BASE_+(0x071b<<2)))&BitMask_08)
#define LAST_CSLICw(val)		_wr32(_REG_BASE_+(0x071b<<2),(UINT)((_rd32(_REG_BASE_+(0x071b<<2))&(~ValSft_L00(BitMask_08)))|ValSft_L00((val)&BitMask_08)))

#define ITU_VIDr				(ValSft_R05(_rd32(_REG_BASE_+(0x071c<<2)))&BitMask_01)
#define ITU_VIDw(val)			_wr32(_REG_BASE_+(0x071c<<2),(UINT)((_rd32(_REG_BASE_+(0x071c<<2))&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))

#define ITU_FIDr				(ValSft_R04(_rd32(_REG_BASE_+(0x071c<<2)))&BitMask_01)
#define ITU_FIDw(val)			_wr32(_REG_BASE_+(0x071c<<2),(UINT)((_rd32(_REG_BASE_+(0x071c<<2))&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))

#define ITU_LCONr				(ValSft_R03(_rd32(_REG_BASE_+(0x071c<<2)))&BitMask_01)
#define ITU_LCONw(val)			_wr32(_REG_BASE_+(0x071c<<2),(UINT)((_rd32(_REG_BASE_+(0x071c<<2))&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))

#define LNUM_EXT_ONr			(ValSft_R02(_rd32(_REG_BASE_+(0x071c<<2)))&BitMask_01)
#define LNUM_EXT_ONw(val)		_wr32(_REG_BASE_+(0x071c<<2),(UINT)((_rd32(_REG_BASE_+(0x071c<<2))&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))

#define ITU_FLDO_INVr			(ValSft_R01(_rd32(_REG_BASE_+(0x071c<<2)))&BitMask_01)
#define ITU_FLDO_INVw(val)		_wr32(_REG_BASE_+(0x071c<<2),(UINT)((_rd32(_REG_BASE_+(0x071c<<2))&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define FLDO_NUM_SELr			(ValSft_R00(_rd32(_REG_BASE_+(0x071c<<2)))&BitMask_01)
#define FLDO_NUM_SELw(val)		_wr32(_REG_BASE_+(0x071c<<2),(UINT)((_rd32(_REG_BASE_+(0x071c<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define REG_ANC0_D01r			(ValSft_R12(_rd32(_REG_BASE_+(0x0720<<2)))&BitMask_10)
#define REG_ANC0_D01w(val)		_wr32(_REG_BASE_+(0x0720<<2),(UINT)((_rd32(_REG_BASE_+(0x0720<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define REG_ANC0_D00r			(ValSft_R00(_rd32(_REG_BASE_+(0x0720<<2)))&BitMask_10)
#define REG_ANC0_D00w(val)		_wr32(_REG_BASE_+(0x0720<<2),(UINT)((_rd32(_REG_BASE_+(0x0720<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define REG_ANC0_D02r			(ValSft_R12(_rd32(_REG_BASE_+(0x0721<<2)))&BitMask_10)
#define REG_ANC0_D02w(val)		_wr32(_REG_BASE_+(0x0721<<2),(UINT)((_rd32(_REG_BASE_+(0x0721<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define REG_ANC0_D03r			(ValSft_R00(_rd32(_REG_BASE_+(0x0721<<2)))&BitMask_10)
#define REG_ANC0_D03w(val)		_wr32(_REG_BASE_+(0x0721<<2),(UINT)((_rd32(_REG_BASE_+(0x0721<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define REG_ANC0_D04r			(ValSft_R12(_rd32(_REG_BASE_+(0x0722<<2)))&BitMask_10)
#define REG_ANC0_D04w(val)		_wr32(_REG_BASE_+(0x0722<<2),(UINT)((_rd32(_REG_BASE_+(0x0722<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define REG_ANC0_D05r			(ValSft_R00(_rd32(_REG_BASE_+(0x0722<<2)))&BitMask_10)
#define REG_ANC0_D05w(val)		_wr32(_REG_BASE_+(0x0722<<2),(UINT)((_rd32(_REG_BASE_+(0x0722<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define REG_ANC0_D06r			(ValSft_R12(_rd32(_REG_BASE_+(0x0723<<2)))&BitMask_10)
#define REG_ANC0_D06w(val)		_wr32(_REG_BASE_+(0x0723<<2),(UINT)((_rd32(_REG_BASE_+(0x0723<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define REG_ANC0_D07r			(ValSft_R00(_rd32(_REG_BASE_+(0x0723<<2)))&BitMask_10)
#define REG_ANC0_D07w(val)		_wr32(_REG_BASE_+(0x0723<<2),(UINT)((_rd32(_REG_BASE_+(0x0723<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define REG_ANC0_D08r			(ValSft_R12(_rd32(_REG_BASE_+(0x0724<<2)))&BitMask_10)
#define REG_ANC0_D08w(val)		_wr32(_REG_BASE_+(0x0724<<2),(UINT)((_rd32(_REG_BASE_+(0x0724<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define REG_ANC0_D09r			(ValSft_R00(_rd32(_REG_BASE_+(0x0724<<2)))&BitMask_10)
#define REG_ANC0_D09w(val)		_wr32(_REG_BASE_+(0x0724<<2),(UINT)((_rd32(_REG_BASE_+(0x0724<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define REG_ANC0_D10r			(ValSft_R12(_rd32(_REG_BASE_+(0x0725<<2)))&BitMask_10)
#define REG_ANC0_D10w(val)		_wr32(_REG_BASE_+(0x0725<<2),(UINT)((_rd32(_REG_BASE_+(0x0725<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define REG_ANC0_D11r			(ValSft_R00(_rd32(_REG_BASE_+(0x0725<<2)))&BitMask_10)
#define REG_ANC0_D11w(val)		_wr32(_REG_BASE_+(0x0725<<2),(UINT)((_rd32(_REG_BASE_+(0x0725<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define REG_ANC0_D12r			(ValSft_R12(_rd32(_REG_BASE_+(0x0726<<2)))&BitMask_10)
#define REG_ANC0_D12w(val)		_wr32(_REG_BASE_+(0x0726<<2),(UINT)((_rd32(_REG_BASE_+(0x0726<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define REG_ANC0_D13r			(ValSft_R00(_rd32(_REG_BASE_+(0x0726<<2)))&BitMask_10)
#define REG_ANC0_D13w(val)		_wr32(_REG_BASE_+(0x0726<<2),(UINT)((_rd32(_REG_BASE_+(0x0726<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define REG_ANC0_D14r			(ValSft_R12(_rd32(_REG_BASE_+(0x0727<<2)))&BitMask_10)
#define REG_ANC0_D14w(val)		_wr32(_REG_BASE_+(0x0727<<2),(UINT)((_rd32(_REG_BASE_+(0x0727<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define REG_ANC0_D15r			(ValSft_R00(_rd32(_REG_BASE_+(0x0727<<2)))&BitMask_10)
#define REG_ANC0_D15w(val)		_wr32(_REG_BASE_+(0x0727<<2),(UINT)((_rd32(_REG_BASE_+(0x0727<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define REG_ANC1_D00r			(ValSft_R12(_rd32(_REG_BASE_+(0x0728<<2)))&BitMask_10)
#define REG_ANC1_D00w(val)		_wr32(_REG_BASE_+(0x0728<<2),(UINT)((_rd32(_REG_BASE_+(0x0728<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define REG_ANC1_D01r			(ValSft_R00(_rd32(_REG_BASE_+(0x0728<<2)))&BitMask_10)
#define REG_ANC1_D01w(val)		_wr32(_REG_BASE_+(0x0728<<2),(UINT)((_rd32(_REG_BASE_+(0x0728<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define REG_ANC1_D02r			(ValSft_R12(_rd32(_REG_BASE_+(0x0729<<2)))&BitMask_10)
#define REG_ANC1_D02w(val)		_wr32(_REG_BASE_+(0x0729<<2),(UINT)((_rd32(_REG_BASE_+(0x0729<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define REG_ANC1_D03r			(ValSft_R00(_rd32(_REG_BASE_+(0x0729<<2)))&BitMask_10)
#define REG_ANC1_D03w(val)		_wr32(_REG_BASE_+(0x0729<<2),(UINT)((_rd32(_REG_BASE_+(0x0729<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define REG_ANC1_D04r			(ValSft_R12(_rd32(_REG_BASE_+(0x072a<<2)))&BitMask_10)
#define REG_ANC1_D04w(val)		_wr32(_REG_BASE_+(0x072a<<2),(UINT)((_rd32(_REG_BASE_+(0x072a<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define REG_ANC1_D05r			(ValSft_R00(_rd32(_REG_BASE_+(0x072a<<2)))&BitMask_10)
#define REG_ANC1_D05w(val)		_wr32(_REG_BASE_+(0x072a<<2),(UINT)((_rd32(_REG_BASE_+(0x072a<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define REG_ANC1_D06r			(ValSft_R12(_rd32(_REG_BASE_+(0x072b<<2)))&BitMask_10)
#define REG_ANC1_D06w(val)		_wr32(_REG_BASE_+(0x072b<<2),(UINT)((_rd32(_REG_BASE_+(0x072b<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define REG_ANC1_D07r			(ValSft_R00(_rd32(_REG_BASE_+(0x072b<<2)))&BitMask_10)
#define REG_ANC1_D07w(val)		_wr32(_REG_BASE_+(0x072b<<2),(UINT)((_rd32(_REG_BASE_+(0x072b<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define REG_ANC1_D08r			(ValSft_R12(_rd32(_REG_BASE_+(0x072c<<2)))&BitMask_10)
#define REG_ANC1_D08w(val)		_wr32(_REG_BASE_+(0x072c<<2),(UINT)((_rd32(_REG_BASE_+(0x072c<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define REG_ANC1_D09r			(ValSft_R00(_rd32(_REG_BASE_+(0x072c<<2)))&BitMask_10)
#define REG_ANC1_D09w(val)		_wr32(_REG_BASE_+(0x072c<<2),(UINT)((_rd32(_REG_BASE_+(0x072c<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define REG_ANC1_D10r			(ValSft_R12(_rd32(_REG_BASE_+(0x072d<<2)))&BitMask_10)
#define REG_ANC1_D10w(val)		_wr32(_REG_BASE_+(0x072d<<2),(UINT)((_rd32(_REG_BASE_+(0x072d<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define REG_ANC1_D11r			(ValSft_R00(_rd32(_REG_BASE_+(0x072d<<2)))&BitMask_10)
#define REG_ANC1_D11w(val)		_wr32(_REG_BASE_+(0x072d<<2),(UINT)((_rd32(_REG_BASE_+(0x072d<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define REG_ANC1_D12r			(ValSft_R12(_rd32(_REG_BASE_+(0x072e<<2)))&BitMask_10)
#define REG_ANC1_D12w(val)		_wr32(_REG_BASE_+(0x072e<<2),(UINT)((_rd32(_REG_BASE_+(0x072e<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define REG_ANC1_D13r			(ValSft_R00(_rd32(_REG_BASE_+(0x072e<<2)))&BitMask_10)
#define REG_ANC1_D13w(val)		_wr32(_REG_BASE_+(0x072e<<2),(UINT)((_rd32(_REG_BASE_+(0x072e<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define REG_ANC1_D14r			(ValSft_R12(_rd32(_REG_BASE_+(0x072f<<2)))&BitMask_10)
#define REG_ANC1_D14w(val)		_wr32(_REG_BASE_+(0x072f<<2),(UINT)((_rd32(_REG_BASE_+(0x072f<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define REG_ANC1_D15r			(ValSft_R00(_rd32(_REG_BASE_+(0x072f<<2)))&BitMask_10)
#define REG_ANC1_D15w(val)		_wr32(_REG_BASE_+(0x072f<<2),(UINT)((_rd32(_REG_BASE_+(0x072f<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define UCCTX_ENr				(ValSft_R08(_rd32(_REG_BASE_+(0x0736<<2)))&BitMask_01)
#define UCCTX_ENw(val)			_wr32(_REG_BASE_+(0x0736<<2),(UINT)((_rd32(_REG_BASE_+(0x0736<<2))&(~ValSft_L08(BitMask_01)))|ValSft_L08((val)&BitMask_01)))

#define UCCTX_ICr				(ValSft_R04(_rd32(_REG_BASE_+(0x0736<<2)))&BitMask_03)
#define UCCTX_ICw(val)			_wr32(_REG_BASE_+(0x0736<<2),(UINT)((_rd32(_REG_BASE_+(0x0736<<2))&(~ValSft_L04(BitMask_03)))|ValSft_L04((val)&BitMask_03)))

#define UCCTX_SRr				(ValSft_R00(_rd32(_REG_BASE_+(0x0736<<2)))&BitMask_03)
#define UCCTX_SRw(val)			_wr32(_REG_BASE_+(0x0736<<2),(UINT)((_rd32(_REG_BASE_+(0x0736<<2))&(~ValSft_L00(BitMask_03)))|ValSft_L00((val)&BitMask_03)))

#define V1UD_MAX_THr			(ValSft_R12(_rd32(_REG_BASE_+(0x0738<<2)))&BitMask_10)
#define V1UD_MAX_THw(val)		_wr32(_REG_BASE_+(0x0738<<2),(UINT)((_rd32(_REG_BASE_+(0x0738<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define V1UD_UPPER_THr			(ValSft_R00(_rd32(_REG_BASE_+(0x0738<<2)))&BitMask_10)
#define V1UD_UPPER_THw(val)		_wr32(_REG_BASE_+(0x0738<<2),(UINT)((_rd32(_REG_BASE_+(0x0738<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define V1UD_LOWER_THr			(ValSft_R12(_rd32(_REG_BASE_+(0x0739<<2)))&BitMask_10)
#define V1UD_LOWER_THw(val)		_wr32(_REG_BASE_+(0x0739<<2),(UINT)((_rd32(_REG_BASE_+(0x0739<<2))&(~ValSft_L12(BitMask_10)))|ValSft_L12((val)&BitMask_10)))

#define V1UD_SAMPLE_RATEr		(ValSft_R00(_rd32(_REG_BASE_+(0x0739<<2)))&BitMask_10)
#define V1UD_SAMPLE_RATEw(val)	_wr32(_REG_BASE_+(0x0739<<2),(UINT)((_rd32(_REG_BASE_+(0x0739<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define V1UD_INSELr				(ValSft_R31(_rd32(_REG_BASE_+(0x0739<<2)))&BitMask_01)
#define V1UD_INSELw(val)		_wr32(_REG_BASE_+(0x0739<<2),(UINT)((_rd32(_REG_BASE_+(0x0739<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define EXUD_INSELr				(ValSft_R31(_rd32(_REG_BASE_+(0x073a<<2)))&BitMask_01)
#define EXUD_INSELw(val)		_wr32(_REG_BASE_+(0x073a<<2),(UINT)((_rd32(_REG_BASE_+(0x073a<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define EXUD_SD_MANUALr			(ValSft_R16(_rd32(_REG_BASE_+(0x073a<<2)))&BitMask_01)
#define EXUD_SD_MANUALw(val)	_wr32(_REG_BASE_+(0x073a<<2),(UINT)((_rd32(_REG_BASE_+(0x073a<<2))&(~ValSft_L16(BitMask_01)))|ValSft_L16((val)&BitMask_01)))

#define EXUD_FREQ_NUMr			(ValSft_R00(_rd32(_REG_BASE_+(0x073a<<2)))&BitMask_16)
#define EXUD_FREQ_NUMw(val)		_wr32(_REG_BASE_+(0x073a<<2),(UINT)((_rd32(_REG_BASE_+(0x073a<<2))&(~ValSft_L00(BitMask_16)))|ValSft_L00((val)&BitMask_16)))

#define EXUD_ATT_ENr			(ValSft_R17(_rd32(_REG_BASE_+(0x073a<<2)))&BitMask_01)
#define EXUD_ATT_ENw(val)		_wr32(_REG_BASE_+(0x073a<<2),(UINT)((_rd32(_REG_BASE_+(0x073a<<2))&(~ValSft_L17(BitMask_01)))|ValSft_L17((val)&BitMask_01)))

#define EXUD_ATT_SELr			(ValSft_R18(_rd32(_REG_BASE_+(0x073a<<2)))&BitMask_02)
#define EXUD_ATT_SELw(val)		_wr32(_REG_BASE_+(0x073a<<2),(UINT)((_rd32(_REG_BASE_+(0x073a<<2))&(~ValSft_L18(BitMask_02)))|ValSft_L18((val)&BitMask_02)))

#define B8UD_ERR_CNT_RSTr		(ValSft_R30(_rd32(_REG_BASE_+(0x073a<<2)))&BitMask_01)
#define B8UD_ERR_CNT_RSTw(val)	_wr32(_REG_BASE_+(0x073a<<2),(UINT)((_rd32(_REG_BASE_+(0x073a<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define UD_DATA_OSELr			(ValSft_R29(_rd32(_REG_BASE_+(0x073a<<2)))&BitMask_01)
#define UD_DATA_OSELw(val)		_wr32(_REG_BASE_+(0x073a<<2),(UINT)((_rd32(_REG_BASE_+(0x073a<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define UCC_TXPHY_SELr			(ValSft_R31(_rd32(_REG_BASE_+(0x073f<<2)))&BitMask_01)
#define UCC_TXPHY_SELw(val)		_wr32(_REG_BASE_+(0x073f<<2),(UINT)((_rd32(_REG_BASE_+(0x073f<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define TSDI_OBUF_BPr			(ValSft_R03(_rd32(_REG_BASE_+(0x0744<<2)))&BitMask_01)
#define TSDI_OBUF_BPw(val)		_wr32(_REG_BASE_+(0x0744<<2),(UINT)((_rd32(_REG_BASE_+(0x0744<<2))&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))

#define TSDI_DO_OFFr			(ValSft_R02(_rd32(_REG_BASE_+(0x0744<<2)))&BitMask_01)
#define TSDI_DO_OFFw(val)		_wr32(_REG_BASE_+(0x0744<<2),(UINT)((_rd32(_REG_BASE_+(0x0744<<2))&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))

#define BT1120_SDI_BPr			(ValSft_R01(_rd32(_REG_BASE_+(0x0744<<2)))&BitMask_01)
#define BT1120_SDI_BPw(val)		_wr32(_REG_BASE_+(0x0744<<2),(UINT)((_rd32(_REG_BASE_+(0x0744<<2))&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define SDI_ENC_PATHO_TOG_ONr	(ValSft_R22(_rd32(_REG_BASE_+(0x0745<<2)))&BitMask_01)
#define SDI_ENC_PATHO_TOG_ONw(val)	_wr32(_REG_BASE_+(0x0745<<2),(UINT)((_rd32(_REG_BASE_+(0x0745<<2))&(~ValSft_L22(BitMask_01)))|ValSft_L22((val)&BitMask_01)))

#define SDI_ENC_PATHO_ONr		(ValSft_R21(_rd32(_REG_BASE_+(0x0745<<2)))&BitMask_01)
#define SDI_ENC_PATHO_ONw(val)	_wr32(_REG_BASE_+(0x0745<<2),(UINT)((_rd32(_REG_BASE_+(0x0745<<2))&(~ValSft_L21(BitMask_01)))|ValSft_L21((val)&BitMask_01)))

#define SDI_ENC_TRS_REONr		(ValSft_R20(_rd32(_REG_BASE_+(0x0745<<2)))&BitMask_01)
#define SDI_ENC_TRS_REONw(val)	_wr32(_REG_BASE_+(0x0745<<2),(UINT)((_rd32(_REG_BASE_+(0x0745<<2))&(~ValSft_L20(BitMask_01)))|ValSft_L20((val)&BitMask_01)))

#define SDI_ENC_BLK_REONr		(ValSft_R19(_rd32(_REG_BASE_+(0x0745<<2)))&BitMask_01)
#define SDI_ENC_BLK_REONw(val)	_wr32(_REG_BASE_+(0x0745<<2),(UINT)((_rd32(_REG_BASE_+(0x0745<<2))&(~ValSft_L19(BitMask_01)))|ValSft_L19((val)&BitMask_01)))

#define SDI_ENC_LNO_REONr		(ValSft_R18(_rd32(_REG_BASE_+(0x0745<<2)))&BitMask_01)
#define SDI_ENC_LNO_REONw(val)	_wr32(_REG_BASE_+(0x0745<<2),(UINT)((_rd32(_REG_BASE_+(0x0745<<2))&(~ValSft_L18(BitMask_01)))|ValSft_L18((val)&BitMask_01)))

#define SDI_ENC_CRC_REONr		(ValSft_R17(_rd32(_REG_BASE_+(0x0745<<2)))&BitMask_01)
#define SDI_ENC_CRC_REONw(val)	_wr32(_REG_BASE_+(0x0745<<2),(UINT)((_rd32(_REG_BASE_+(0x0745<<2))&(~ValSft_L17(BitMask_01)))|ValSft_L17((val)&BitMask_01)))

#define SDI_ENC_INS_CHID_HBIr	(ValSft_R16(_rd32(_REG_BASE_+(0x0745<<2)))&BitMask_01)
#define SDI_ENC_INS_CHID_HBIw(val)	_wr32(_REG_BASE_+(0x0745<<2),(UINT)((_rd32(_REG_BASE_+(0x0745<<2))&(~ValSft_L16(BitMask_01)))|ValSft_L16((val)&BitMask_01)))

#define SDI_ENC_INS_CHID_TRSr	(ValSft_R15(_rd32(_REG_BASE_+(0x0745<<2)))&BitMask_01)
#define SDI_ENC_INS_CHID_TRSw(val)	_wr32(_REG_BASE_+(0x0745<<2),(UINT)((_rd32(_REG_BASE_+(0x0745<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define SDI_ENC_INS_STIDr		(ValSft_R14(_rd32(_REG_BASE_+(0x0745<<2)))&BitMask_01)
#define SDI_ENC_INS_STIDw(val)	_wr32(_REG_BASE_+(0x0745<<2),(UINT)((_rd32(_REG_BASE_+(0x0745<<2))&(~ValSft_L14(BitMask_01)))|ValSft_L14((val)&BitMask_01)))

#define SDI_ENC_VPRESr			(ValSft_R12(_rd32(_REG_BASE_+(0x0745<<2)))&BitMask_01)
#define SDI_ENC_VPRESw(val)		_wr32(_REG_BASE_+(0x0745<<2),(UINT)((_rd32(_REG_BASE_+(0x0745<<2))&(~ValSft_L12(BitMask_01)))|ValSft_L12((val)&BitMask_01)))

#define SDI_ENC_CHANNEL_IDr		(ValSft_R08(_rd32(_REG_BASE_+(0x0745<<2)))&BitMask_04)
#define SDI_ENC_CHANNEL_IDw(val)	_wr32(_REG_BASE_+(0x0745<<2),(UINT)((_rd32(_REG_BASE_+(0x0745<<2))&(~ValSft_L08(BitMask_04)))|ValSft_L08((val)&BitMask_04)))

#define SDI_ENC_STREAM_IDr		(ValSft_R00(_rd32(_REG_BASE_+(0x0745<<2)))&BitMask_07)
#define SDI_ENC_STREAM_IDw(val)	_wr32(_REG_BASE_+(0x0745<<2),(UINT)((_rd32(_REG_BASE_+(0x0745<<2))&(~ValSft_L00(BitMask_07)))|ValSft_L00((val)&BitMask_07)))

#define SDI_ENC_PATHO_LINEr		(ValSft_R16(_rd32(_REG_BASE_+(0x0746<<2)))&BitMask_10)
#define SDI_ENC_PATHO_LINEw(val)	_wr32(_REG_BASE_+(0x0746<<2),(UINT)((_rd32(_REG_BASE_+(0x0746<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define SDI_ENC_ANC0_ONr		(ValSft_R24(_rd32(_REG_BASE_+(0x0747<<2)))&BitMask_01)
#define SDI_ENC_ANC0_ONw(val)	_wr32(_REG_BASE_+(0x0747<<2),(UINT)((_rd32(_REG_BASE_+(0x0747<<2))&(~ValSft_L24(BitMask_01)))|ValSft_L24((val)&BitMask_01)))

#define SDI_ENC_ANCI0_PNr		(ValSft_R12(_rd32(_REG_BASE_+(0x0747<<2)))&BitMask_12)
#define SDI_ENC_ANCI0_PNw(val)	_wr32(_REG_BASE_+(0x0747<<2),(UINT)((_rd32(_REG_BASE_+(0x0747<<2))&(~ValSft_L12(BitMask_12)))|ValSft_L12((val)&BitMask_12)))

#define SDI_ENC_ANCI0_LNr		(ValSft_R00(_rd32(_REG_BASE_+(0x0747<<2)))&BitMask_11)
#define SDI_ENC_ANCI0_LNw(val)	_wr32(_REG_BASE_+(0x0747<<2),(UINT)((_rd32(_REG_BASE_+(0x0747<<2))&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define SDI_ENC_ANC1_ONr		(ValSft_R24(_rd32(_REG_BASE_+(0x0748<<2)))&BitMask_01)
#define SDI_ENC_ANC1_ONw(val)	_wr32(_REG_BASE_+(0x0748<<2),(UINT)((_rd32(_REG_BASE_+(0x0748<<2))&(~ValSft_L24(BitMask_01)))|ValSft_L24((val)&BitMask_01)))

#define SDI_ENC_ANCI1_PNr		(ValSft_R12(_rd32(_REG_BASE_+(0x0748<<2)))&BitMask_12)
#define SDI_ENC_ANCI1_PNw(val)	_wr32(_REG_BASE_+(0x0748<<2),(UINT)((_rd32(_REG_BASE_+(0x0748<<2))&(~ValSft_L12(BitMask_12)))|ValSft_L12((val)&BitMask_12)))

#define SDI_ENC_ANCI1_LNr		(ValSft_R00(_rd32(_REG_BASE_+(0x0748<<2)))&BitMask_11)
#define SDI_ENC_ANCI1_LNw(val)	_wr32(_REG_BASE_+(0x0748<<2),(UINT)((_rd32(_REG_BASE_+(0x0748<<2))&(~ValSft_L00(BitMask_11)))|ValSft_L00((val)&BitMask_11)))

#define SDI_OPOLr				(ValSft_R16(_rd32(_REG_BASE_+(0x0749<<2)))&BitMask_01)
#define SDI_OPOLw(val)			_wr32(_REG_BASE_+(0x0749<<2),(UINT)((_rd32(_REG_BASE_+(0x0749<<2))&(~ValSft_L16(BitMask_01)))|ValSft_L16((val)&BitMask_01)))

#define OBUF_RATEr				(ValSft_R12(_rd32(_REG_BASE_+(0x0749<<2)))&BitMask_03)
#define OBUF_RATEw(val)			_wr32(_REG_BASE_+(0x0749<<2),(UINT)((_rd32(_REG_BASE_+(0x0749<<2))&(~ValSft_L12(BitMask_03)))|ValSft_L12((val)&BitMask_03)))

#define OBUF_ISELr				(ValSft_R11(_rd32(_REG_BASE_+(0x0749<<2)))&BitMask_01)
#define OBUF_ISELw(val)			_wr32(_REG_BASE_+(0x0749<<2),(UINT)((_rd32(_REG_BASE_+(0x0749<<2))&(~ValSft_L11(BitMask_01)))|ValSft_L11((val)&BitMask_01)))

#define OBUF_AUTO_FRST_ONr		(ValSft_R10(_rd32(_REG_BASE_+(0x0749<<2)))&BitMask_01)
#define OBUF_AUTO_FRST_ONw(val)	_wr32(_REG_BASE_+(0x0749<<2),(UINT)((_rd32(_REG_BASE_+(0x0749<<2))&(~ValSft_L10(BitMask_01)))|ValSft_L10((val)&BitMask_01)))

#define OBUF_ETXDr				(ValSft_R09(_rd32(_REG_BASE_+(0x0749<<2)))&BitMask_01)
#define OBUF_ETXDw(val)			_wr32(_REG_BASE_+(0x0749<<2),(UINT)((_rd32(_REG_BASE_+(0x0749<<2))&(~ValSft_L09(BitMask_01)))|ValSft_L09((val)&BitMask_01)))

#define OBUF_INVr				(ValSft_R08(_rd32(_REG_BASE_+(0x0749<<2)))&BitMask_01)
#define OBUF_INVw(val)			_wr32(_REG_BASE_+(0x0749<<2),(UINT)((_rd32(_REG_BASE_+(0x0749<<2))&(~ValSft_L08(BitMask_01)))|ValSft_L08((val)&BitMask_01)))

#define OBUF_RST_PID_ENr		(ValSft_R07(_rd32(_REG_BASE_+(0x0749<<2)))&BitMask_01)
#define OBUF_RST_PID_ENw(val)	_wr32(_REG_BASE_+(0x0749<<2),(UINT)((_rd32(_REG_BASE_+(0x0749<<2))&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

#define OBUF_RSTr				(ValSft_R06(_rd32(_REG_BASE_+(0x0749<<2)))&BitMask_01)
#define OBUF_RSTw(val)			_wr32(_REG_BASE_+(0x0749<<2),(UINT)((_rd32(_REG_BASE_+(0x0749<<2))&(~ValSft_L06(BitMask_01)))|ValSft_L06((val)&BitMask_01)))

#define SCR_NRZ_ONr				(ValSft_R05(_rd32(_REG_BASE_+(0x0749<<2)))&BitMask_01)
#define SCR_NRZ_ONw(val)		_wr32(_REG_BASE_+(0x0749<<2),(UINT)((_rd32(_REG_BASE_+(0x0749<<2))&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))

#define SCR_ONr					(ValSft_R04(_rd32(_REG_BASE_+(0x0749<<2)))&BitMask_01)
#define SCR_ONw(val)			_wr32(_REG_BASE_+(0x0749<<2),(UINT)((_rd32(_REG_BASE_+(0x0749<<2))&(~ValSft_L04(BitMask_01)))|ValSft_L04((val)&BitMask_01)))

#define SCR_BYPr				(ValSft_R03(_rd32(_REG_BASE_+(0x0749<<2)))&BitMask_01)
#define SCR_BYPw(val)			_wr32(_REG_BASE_+(0x0749<<2),(UINT)((_rd32(_REG_BASE_+(0x0749<<2))&(~ValSft_L03(BitMask_01)))|ValSft_L03((val)&BitMask_01)))

#define SCR_OSELr				(ValSft_R02(_rd32(_REG_BASE_+(0x0749<<2)))&BitMask_01)
#define SCR_OSELw(val)			_wr32(_REG_BASE_+(0x0749<<2),(UINT)((_rd32(_REG_BASE_+(0x0749<<2))&(~ValSft_L02(BitMask_01)))|ValSft_L02((val)&BitMask_01)))

#define SCR_TESTr				(ValSft_R01(_rd32(_REG_BASE_+(0x0749<<2)))&BitMask_01)
#define SCR_TESTw(val)			_wr32(_REG_BASE_+(0x0749<<2),(UINT)((_rd32(_REG_BASE_+(0x0749<<2))&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define SCR_ODRr				(ValSft_R00(_rd32(_REG_BASE_+(0x0749<<2)))&BitMask_01)
#define SCR_ODRw(val)			_wr32(_REG_BASE_+(0x0749<<2),(UINT)((_rd32(_REG_BASE_+(0x0749<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define EX_SPLIT_ONr			(ValSft_R31(_rd32(_REG_BASE_+(0x074d<<2)))&BitMask_01)
#define EX_SPLIT_ONw(val)		_wr32(_REG_BASE_+(0x074d<<2),(UINT)((_rd32(_REG_BASE_+(0x074d<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define EX_SPLIT_PCK2_POLr		(ValSft_R30(_rd32(_REG_BASE_+(0x074d<<2)))&BitMask_01)
#define EX_SPLIT_PCK2_POLw(val)	_wr32(_REG_BASE_+(0x074d<<2),(UINT)((_rd32(_REG_BASE_+(0x074d<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define EX_DEC_DI_SEL_Ar		(ValSft_R29(_rd32(_REG_BASE_+(0x074d<<2)))&BitMask_01)
#define EX_DEC_DI_SEL_Aw(val)	_wr32(_REG_BASE_+(0x074d<<2),(UINT)((_rd32(_REG_BASE_+(0x074d<<2))&(~ValSft_L29(BitMask_01)))|ValSft_L29((val)&BitMask_01)))

#define EX_DEC_DI_SEL_Br		(ValSft_R28(_rd32(_REG_BASE_+(0x074d<<2)))&BitMask_01)
#define EX_DEC_DI_SEL_Bw(val)	_wr32(_REG_BASE_+(0x074d<<2),(UINT)((_rd32(_REG_BASE_+(0x074d<<2))&(~ValSft_L28(BitMask_01)))|ValSft_L28((val)&BitMask_01)))

#define EX_MERGE_ONr			(ValSft_R27(_rd32(_REG_BASE_+(0x074d<<2)))&BitMask_01)
#define EX_MERGE_ONw(val)		_wr32(_REG_BASE_+(0x074d<<2),(UINT)((_rd32(_REG_BASE_+(0x074d<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define EX_MERGE_PCK_POLr		(ValSft_R26(_rd32(_REG_BASE_+(0x074d<<2)))&BitMask_01)
#define EX_MERGE_PCK_POLw(val)	_wr32(_REG_BASE_+(0x074d<<2),(UINT)((_rd32(_REG_BASE_+(0x074d<<2))&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define EX_SPLIT_MODEr			(ValSft_R25(_rd32(_REG_BASE_+(0x074d<<2)))&BitMask_01)
#define EX_SPLIT_MODEw(val)		_wr32(_REG_BASE_+(0x074d<<2),(UINT)((_rd32(_REG_BASE_+(0x074d<<2))&(~ValSft_L25(BitMask_01)))|ValSft_L25((val)&BitMask_01)))

#define EX_SPLIT_LPF_ENr		(ValSft_R24(_rd32(_REG_BASE_+(0x074d<<2)))&BitMask_01)
#define EX_SPLIT_LPF_ENw(val)	_wr32(_REG_BASE_+(0x074d<<2),(UINT)((_rd32(_REG_BASE_+(0x074d<<2))&(~ValSft_L24(BitMask_01)))|ValSft_L24((val)&BitMask_01)))

#define EX_SLPNr				(ValSft_R23(_rd32(_REG_BASE_+(0x074d<<2)))&BitMask_01)
#define EX_SLPNw(val)			_wr32(_REG_BASE_+(0x074d<<2),(UINT)((_rd32(_REG_BASE_+(0x074d<<2))&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define DS_SMIX_ONr				(ValSft_R13(_rd32(_REG_BASE_+(0x074d<<2)))&BitMask_01)
#define DS_SMIX_ONw(val)		_wr32(_REG_BASE_+(0x074d<<2),(UINT)((_rd32(_REG_BASE_+(0x074d<<2))&(~ValSft_L13(BitMask_01)))|ValSft_L13((val)&BitMask_01)))

#define DS_SMIX_FRSTr			(ValSft_R12(_rd32(_REG_BASE_+(0x074d<<2)))&BitMask_01)
#define DS_SMIX_FRSTw(val)		_wr32(_REG_BASE_+(0x074d<<2),(UINT)((_rd32(_REG_BASE_+(0x074d<<2))&(~ValSft_L12(BitMask_01)))|ValSft_L12((val)&BitMask_01)))

#define DS_SMIX_FIFO_ARST_ONr	(ValSft_R11(_rd32(_REG_BASE_+(0x074d<<2)))&BitMask_01)
#define DS_SMIX_FIFO_ARST_ONw(val)	_wr32(_REG_BASE_+(0x074d<<2),(UINT)((_rd32(_REG_BASE_+(0x074d<<2))&(~ValSft_L11(BitMask_01)))|ValSft_L11((val)&BitMask_01)))

#define DS_SMIX_FIFO_LMTr		(ValSft_R00(_rd32(_REG_BASE_+(0x074d<<2)))&BitMask_10)
#define DS_SMIX_FIFO_LMTw(val)	_wr32(_REG_BASE_+(0x074d<<2),(UINT)((_rd32(_REG_BASE_+(0x074d<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define DS_EXSDI_VER_Ar			(ValSft_R28(_rd32(_REG_BASE_+(0x0751<<2)))&BitMask_04)
#define DS_EXSDI_VER_Aw(val)	_wr32(_REG_BASE_+(0x0751<<2),(UINT)((_rd32(_REG_BASE_+(0x0751<<2))&(~ValSft_L28(BitMask_04)))|ValSft_L28((val)&BitMask_04)))

#define DS_BIT_MODE_Ar			(ValSft_R27(_rd32(_REG_BASE_+(0x0751<<2)))&BitMask_01)
#define DS_BIT_MODE_Aw(val)		_wr32(_REG_BASE_+(0x0751<<2),(UINT)((_rd32(_REG_BASE_+(0x0751<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define DS_ID_CH_Ar				(ValSft_R16(_rd32(_REG_BASE_+(0x0751<<2)))&BitMask_04)
#define DS_ID_CH_Aw(val)		_wr32(_REG_BASE_+(0x0751<<2),(UINT)((_rd32(_REG_BASE_+(0x0751<<2))&(~ValSft_L16(BitMask_04)))|ValSft_L16((val)&BitMask_04)))

#define DS_ID_SPLIT_Ar			(ValSft_R14(_rd32(_REG_BASE_+(0x0751<<2)))&BitMask_02)
#define DS_ID_SPLIT_Aw(val)		_wr32(_REG_BASE_+(0x0751<<2),(UINT)((_rd32(_REG_BASE_+(0x0751<<2))&(~ValSft_L14(BitMask_02)))|ValSft_L14((val)&BitMask_02)))

#define DSD_ID_MATCH_ON_Ar		(ValSft_R13(_rd32(_REG_BASE_+(0x0751<<2)))&BitMask_01)
#define DSD_ID_MATCH_ON_Aw(val)	_wr32(_REG_BASE_+(0x0751<<2),(UINT)((_rd32(_REG_BASE_+(0x0751<<2))&(~ValSft_L13(BitMask_01)))|ValSft_L13((val)&BitMask_01)))

#define DSE_SLCK_FREQ_Ar		(ValSft_R09(_rd32(_REG_BASE_+(0x0751<<2)))&BitMask_02)
#define DSE_SLCK_FREQ_Aw(val)	_wr32(_REG_BASE_+(0x0751<<2),(UINT)((_rd32(_REG_BASE_+(0x0751<<2))&(~ValSft_L09(BitMask_02)))|ValSft_L09((val)&BitMask_02)))

#define DSD_DEC_PGEN_ON_Ar		(ValSft_R05(_rd32(_REG_BASE_+(0x0751<<2)))&BitMask_01)
#define DSD_DEC_PGEN_ON_Aw(val)	_wr32(_REG_BASE_+(0x0751<<2),(UINT)((_rd32(_REG_BASE_+(0x0751<<2))&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))

#define DSD_DEC_PGEN_MODE_Ar	(ValSft_R02(_rd32(_REG_BASE_+(0x0751<<2)))&BitMask_03)
#define DSD_DEC_PGEN_MODE_Aw(val)	_wr32(_REG_BASE_+(0x0751<<2),(UINT)((_rd32(_REG_BASE_+(0x0751<<2))&(~ValSft_L02(BitMask_03)))|ValSft_L02((val)&BitMask_03)))

#define DSD_8B10B_ERST_Ar		(ValSft_R01(_rd32(_REG_BASE_+(0x0751<<2)))&BitMask_01)
#define DSD_8B10B_ERST_Aw(val)	_wr32(_REG_BASE_+(0x0751<<2),(UINT)((_rd32(_REG_BASE_+(0x0751<<2))&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define DSD_CRC_ERST_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x0751<<2)))&BitMask_01)
#define DSD_CRC_ERST_Aw(val)	_wr32(_REG_BASE_+(0x0751<<2),(UINT)((_rd32(_REG_BASE_+(0x0751<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define DSE_BLK_DAT_SEL_Ar		(ValSft_R09(_rd32(_REG_BASE_+(0x0752<<2)))&BitMask_01)
#define DSE_BLK_DAT_SEL_Aw(val)	_wr32(_REG_BASE_+(0x0752<<2),(UINT)((_rd32(_REG_BASE_+(0x0752<<2))&(~ValSft_L09(BitMask_01)))|ValSft_L09((val)&BitMask_01)))

#define DS_FMT_HDTRS_ON_Ar		(ValSft_R08(_rd32(_REG_BASE_+(0x0752<<2)))&BitMask_01)
#define DS_FMT_HDTRS_ON_Aw(val)	_wr32(_REG_BASE_+(0x0752<<2),(UINT)((_rd32(_REG_BASE_+(0x0752<<2))&(~ValSft_L08(BitMask_01)))|ValSft_L08((val)&BitMask_01)))

#define DSE_FMT_FIFO_LMT_Ar		(ValSft_R02(_rd32(_REG_BASE_+(0x0752<<2)))&BitMask_06)
#define DSE_FMT_FIFO_LMT_Aw(val)	_wr32(_REG_BASE_+(0x0752<<2),(UINT)((_rd32(_REG_BASE_+(0x0752<<2))&(~ValSft_L02(BitMask_06)))|ValSft_L02((val)&BitMask_06)))

#define DSD_DEFMT_BYPASS_Ar		(ValSft_R00(_rd32(_REG_BASE_+(0x0752<<2)))&BitMask_01)
#define DSD_DEFMT_BYPASS_Aw(val)	_wr32(_REG_BASE_+(0x0752<<2),(UINT)((_rd32(_REG_BASE_+(0x0752<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define DSE_MEM_AFULL_TH_Ar		(ValSft_R16(_rd32(_REG_BASE_+(0x0753<<2)))&BitMask_10)
#define DSE_MEM_AFULL_TH_Aw(val)	_wr32(_REG_BASE_+(0x0753<<2),(UINT)((_rd32(_REG_BASE_+(0x0753<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define DSE_MEM_RD_LMT_ON_Ar	(ValSft_R15(_rd32(_REG_BASE_+(0x0753<<2)))&BitMask_01)
#define DSE_MEM_RD_LMT_ON_Aw(val)	_wr32(_REG_BASE_+(0x0753<<2),(UINT)((_rd32(_REG_BASE_+(0x0753<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define DSE_MEM_RD_LMT_CNT_Ar	(ValSft_R00(_rd32(_REG_BASE_+(0x0753<<2)))&BitMask_12)
#define DSE_MEM_RD_LMT_CNT_Aw(val)	_wr32(_REG_BASE_+(0x0753<<2),(UINT)((_rd32(_REG_BASE_+(0x0753<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define DSE_RD_SYNC_ON_Ar		(ValSft_R31(_rd32(_REG_BASE_+(0x0754<<2)))&BitMask_01)
#define DSE_RD_SYNC_ON_Aw(val)	_wr32(_REG_BASE_+(0x0754<<2),(UINT)((_rd32(_REG_BASE_+(0x0754<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DSE_RD_SYNC_TCNT_Ar		(ValSft_R16(_rd32(_REG_BASE_+(0x0754<<2)))&BitMask_12)
#define DSE_RD_SYNC_TCNT_Aw(val)	_wr32(_REG_BASE_+(0x0754<<2),(UINT)((_rd32(_REG_BASE_+(0x0754<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define DSE_RD_SYNC_ACNT_Ar		(ValSft_R00(_rd32(_REG_BASE_+(0x0754<<2)))&BitMask_12)
#define DSE_RD_SYNC_ACNT_Aw(val)	_wr32(_REG_BASE_+(0x0754<<2),(UINT)((_rd32(_REG_BASE_+(0x0754<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define DS_AUD_ON_Ar			(ValSft_R23(_rd32(_REG_BASE_+(0x0755<<2)))&BitMask_01)
#define DS_AUD_ON_Aw(val)		_wr32(_REG_BASE_+(0x0755<<2),(UINT)((_rd32(_REG_BASE_+(0x0755<<2))&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define DSE_AUD_MSCK_FREQ_Ar	(ValSft_R20(_rd32(_REG_BASE_+(0x0755<<2)))&BitMask_03)
#define DSE_AUD_MSCK_FREQ_Aw(val)	_wr32(_REG_BASE_+(0x0755<<2),(UINT)((_rd32(_REG_BASE_+(0x0755<<2))&(~ValSft_L20(BitMask_03)))|ValSft_L20((val)&BitMask_03)))

#define DSE_AUD_ENC_ACT0_Ar		(ValSft_R17(_rd32(_REG_BASE_+(0x0755<<2)))&BitMask_01)
#define DSE_AUD_ENC_ACT0_Aw(val)	_wr32(_REG_BASE_+(0x0755<<2),(UINT)((_rd32(_REG_BASE_+(0x0755<<2))&(~ValSft_L17(BitMask_01)))|ValSft_L17((val)&BitMask_01)))

#define DSE_AUD_ENC_ACT1_Ar		(ValSft_R16(_rd32(_REG_BASE_+(0x0755<<2)))&BitMask_01)
#define DSE_AUD_ENC_ACT1_Aw(val)	_wr32(_REG_BASE_+(0x0755<<2),(UINT)((_rd32(_REG_BASE_+(0x0755<<2))&(~ValSft_L16(BitMask_01)))|ValSft_L16((val)&BitMask_01)))

#define DSE_AUD_ENC_RATE_Ar		(ValSft_R08(_rd32(_REG_BASE_+(0x0755<<2)))&BitMask_08)
#define DSE_AUD_ENC_RATE_Aw(val)	_wr32(_REG_BASE_+(0x0755<<2),(UINT)((_rd32(_REG_BASE_+(0x0755<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define DSD_AUD_MSCK_FREQ_ON_Ar	(ValSft_R31(_rd32(_REG_BASE_+(0x0756<<2)))&BitMask_01)
#define DSD_AUD_MSCK_FREQ_ON_Aw(val)	_wr32(_REG_BASE_+(0x0756<<2),(UINT)((_rd32(_REG_BASE_+(0x0756<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DSD_AUD_MSCK_FREQ_Ar	(ValSft_R28(_rd32(_REG_BASE_+(0x0756<<2)))&BitMask_03)
#define DSD_AUD_MSCK_FREQ_Aw(val)	_wr32(_REG_BASE_+(0x0756<<2),(UINT)((_rd32(_REG_BASE_+(0x0756<<2))&(~ValSft_L28(BitMask_03)))|ValSft_L28((val)&BitMask_03)))

#define DSD_AUD_INTP_ON_Ar		(ValSft_R27(_rd32(_REG_BASE_+(0x0756<<2)))&BitMask_01)
#define DSD_AUD_INTP_ON_Aw(val)	_wr32(_REG_BASE_+(0x0756<<2),(UINT)((_rd32(_REG_BASE_+(0x0756<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define DSD_AUD_ADET_ON_Ar		(ValSft_R26(_rd32(_REG_BASE_+(0x0756<<2)))&BitMask_01)
#define DSD_AUD_ADET_ON_Aw(val)	_wr32(_REG_BASE_+(0x0756<<2),(UINT)((_rd32(_REG_BASE_+(0x0756<<2))&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define DSD_AUD_ADET_CNT_Ar		(ValSft_R00(_rd32(_REG_BASE_+(0x0756<<2)))&BitMask_26)
#define DSD_AUD_ADET_CNT_Aw(val)	_wr32(_REG_BASE_+(0x0756<<2),(UINT)((_rd32(_REG_BASE_+(0x0756<<2))&(~ValSft_L00(BitMask_26)))|ValSft_L00((val)&BitMask_26)))

#define DS_ANC_ON_Ar			(ValSft_R31(_rd32(_REG_BASE_+(0x0757<<2)))&BitMask_01)
#define DS_ANC_ON_Aw(val)		_wr32(_REG_BASE_+(0x0757<<2),(UINT)((_rd32(_REG_BASE_+(0x0757<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DSD_ANC_ADET_CNT_Ar		(ValSft_R00(_rd32(_REG_BASE_+(0x0757<<2)))&BitMask_26)
#define DSD_ANC_ADET_CNT_Aw(val)	_wr32(_REG_BASE_+(0x0757<<2),(UINT)((_rd32(_REG_BASE_+(0x0757<<2))&(~ValSft_L00(BitMask_26)))|ValSft_L00((val)&BitMask_26)))

#define EXE_PGN_ON_Ar			(ValSft_R24(_rd32(_REG_BASE_+(0x0761<<2)))&BitMask_01)
#define EXE_PGN_ON_Aw(val)		_wr32(_REG_BASE_+(0x0761<<2),(UINT)((_rd32(_REG_BASE_+(0x0761<<2))&(~ValSft_L24(BitMask_01)))|ValSft_L24((val)&BitMask_01)))

#define EXE_PGN_YPAT_Ar			(ValSft_R20(_rd32(_REG_BASE_+(0x0761<<2)))&BitMask_04)
#define EXE_PGN_YPAT_Aw(val)	_wr32(_REG_BASE_+(0x0761<<2),(UINT)((_rd32(_REG_BASE_+(0x0761<<2))&(~ValSft_L20(BitMask_04)))|ValSft_L20((val)&BitMask_04)))

#define EXE_PGN_CPAT_Ar			(ValSft_R16(_rd32(_REG_BASE_+(0x0761<<2)))&BitMask_04)
#define EXE_PGN_CPAT_Aw(val)	_wr32(_REG_BASE_+(0x0761<<2),(UINT)((_rd32(_REG_BASE_+(0x0761<<2))&(~ValSft_L16(BitMask_04)))|ValSft_L16((val)&BitMask_04)))

#define EXE_PGN_INTER_Ar		(ValSft_R15(_rd32(_REG_BASE_+(0x0761<<2)))&BitMask_01)
#define EXE_PGN_INTER_Aw(val)	_wr32(_REG_BASE_+(0x0761<<2),(UINT)((_rd32(_REG_BASE_+(0x0761<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define EXE_PGN_VSP_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x0761<<2)))&BitMask_13)
#define EXE_PGN_VSP_Aw(val)		_wr32(_REG_BASE_+(0x0761<<2),(UINT)((_rd32(_REG_BASE_+(0x0761<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define EXE_PGN_HTC_Ar			(ValSft_R16(_rd32(_REG_BASE_+(0x0762<<2)))&BitMask_14)
#define EXE_PGN_HTC_Aw(val)		_wr32(_REG_BASE_+(0x0762<<2),(UINT)((_rd32(_REG_BASE_+(0x0762<<2))&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define EXE_PGN_VTC_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x0762<<2)))&BitMask_13)
#define EXE_PGN_VTC_Aw(val)		_wr32(_REG_BASE_+(0x0762<<2),(UINT)((_rd32(_REG_BASE_+(0x0762<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define EXE_PGN_HW_Ar			(ValSft_R16(_rd32(_REG_BASE_+(0x0763<<2)))&BitMask_14)
#define EXE_PGN_HW_Aw(val)		_wr32(_REG_BASE_+(0x0763<<2),(UINT)((_rd32(_REG_BASE_+(0x0763<<2))&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define EXE_PGN_VW_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x0763<<2)))&BitMask_13)
#define EXE_PGN_VW_Aw(val)		_wr32(_REG_BASE_+(0x0763<<2),(UINT)((_rd32(_REG_BASE_+(0x0763<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define EXE_ELOCK_OFFSET_Ar		(ValSft_R28(_rd32(_REG_BASE_+(0x0764<<2)))&BitMask_04)
#define EXE_ELOCK_OFFSET_Aw(val)	_wr32(_REG_BASE_+(0x0764<<2),(UINT)((_rd32(_REG_BASE_+(0x0764<<2))&(~ValSft_L28(BitMask_04)))|ValSft_L28((val)&BitMask_04)))

#define EXE_RST_IVL_Ar			(ValSft_R27(_rd32(_REG_BASE_+(0x0764<<2)))&BitMask_01)
#define EXE_RST_IVL_Aw(val)		_wr32(_REG_BASE_+(0x0764<<2),(UINT)((_rd32(_REG_BASE_+(0x0764<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define EXE_LPF_EN_Ar			(ValSft_R25(_rd32(_REG_BASE_+(0x0764<<2)))&BitMask_01)
#define EXE_LPF_EN_Aw(val)		_wr32(_REG_BASE_+(0x0764<<2),(UINT)((_rd32(_REG_BASE_+(0x0764<<2))&(~ValSft_L25(BitMask_01)))|ValSft_L25((val)&BitMask_01)))

#define EXE_DCT_CUT_EN_Ar		(ValSft_R24(_rd32(_REG_BASE_+(0x0764<<2)))&BitMask_01)
#define EXE_DCT_CUT_EN_Aw(val)	_wr32(_REG_BASE_+(0x0764<<2),(UINT)((_rd32(_REG_BASE_+(0x0764<<2))&(~ValSft_L24(BitMask_01)))|ValSft_L24((val)&BitMask_01)))

#define EXE_DCT_CUT_NUM_Ar		(ValSft_R18(_rd32(_REG_BASE_+(0x0764<<2)))&BitMask_06)
#define EXE_DCT_CUT_NUM_Aw(val)	_wr32(_REG_BASE_+(0x0764<<2),(UINT)((_rd32(_REG_BASE_+(0x0764<<2))&(~ValSft_L18(BitMask_06)))|ValSft_L18((val)&BitMask_06)))

#define EXE_QUAL_AUTO_ON_Ar		(ValSft_R15(_rd32(_REG_BASE_+(0x0764<<2)))&BitMask_01)
#define EXE_QUAL_AUTO_ON_Aw(val)	_wr32(_REG_BASE_+(0x0764<<2),(UINT)((_rd32(_REG_BASE_+(0x0764<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define EXE_QUAL_VAL_Ar			(ValSft_R10(_rd32(_REG_BASE_+(0x0764<<2)))&BitMask_05)
#define EXE_QUAL_VAL_Aw(val)	_wr32(_REG_BASE_+(0x0764<<2),(UINT)((_rd32(_REG_BASE_+(0x0764<<2))&(~ValSft_L10(BitMask_05)))|ValSft_L10((val)&BitMask_05)))

#define EXE_QUAL_HIGH_Ar		(ValSft_R05(_rd32(_REG_BASE_+(0x0764<<2)))&BitMask_05)
#define EXE_QUAL_HIGH_Aw(val)	_wr32(_REG_BASE_+(0x0764<<2),(UINT)((_rd32(_REG_BASE_+(0x0764<<2))&(~ValSft_L05(BitMask_05)))|ValSft_L05((val)&BitMask_05)))

#define EXE_QUAL_LOW_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x0764<<2)))&BitMask_05)
#define EXE_QUAL_LOW_Aw(val)	_wr32(_REG_BASE_+(0x0764<<2),(UINT)((_rd32(_REG_BASE_+(0x0764<<2))&(~ValSft_L00(BitMask_05)))|ValSft_L00((val)&BitMask_05)))

#define EXE_QUAL_QP_FREQ_Ar		(ValSft_R24(_rd32(_REG_BASE_+(0x0765<<2)))&BitMask_06)
#define EXE_QUAL_QP_FREQ_Aw(val)	_wr32(_REG_BASE_+(0x0765<<2),(UINT)((_rd32(_REG_BASE_+(0x0765<<2))&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define EXE_QUAL_P_GAIN_Ar		(ValSft_R16(_rd32(_REG_BASE_+(0x0765<<2)))&BitMask_08)
#define EXE_QUAL_P_GAIN_Aw(val)	_wr32(_REG_BASE_+(0x0765<<2),(UINT)((_rd32(_REG_BASE_+(0x0765<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define EXE_QUAL_I_GAIN_Ar		(ValSft_R10(_rd32(_REG_BASE_+(0x0765<<2)))&BitMask_06)
#define EXE_QUAL_I_GAIN_Aw(val)	_wr32(_REG_BASE_+(0x0765<<2),(UINT)((_rd32(_REG_BASE_+(0x0765<<2))&(~ValSft_L10(BitMask_06)))|ValSft_L10((val)&BitMask_06)))

#define EXE_QUAL_I_OFFSET_Ar	(ValSft_R00(_rd32(_REG_BASE_+(0x0765<<2)))&BitMask_10)
#define EXE_QUAL_I_OFFSET_Aw(val)	_wr32(_REG_BASE_+(0x0765<<2),(UINT)((_rd32(_REG_BASE_+(0x0765<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define EXE_QP_MODE_Ar			(ValSft_R30(_rd32(_REG_BASE_+(0x0766<<2)))&BitMask_02)
#define EXE_QP_MODE_Aw(val)		_wr32(_REG_BASE_+(0x0766<<2),(UINT)((_rd32(_REG_BASE_+(0x0766<<2))&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define EXE_YDC_QTBL_Ar			(ValSft_R24(_rd32(_REG_BASE_+(0x0766<<2)))&BitMask_06)
#define EXE_YDC_QTBL_Aw(val)	_wr32(_REG_BASE_+(0x0766<<2),(UINT)((_rd32(_REG_BASE_+(0x0766<<2))&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define EXE_CDC_QTBL_Ar			(ValSft_R18(_rd32(_REG_BASE_+(0x0766<<2)))&BitMask_06)
#define EXE_CDC_QTBL_Aw(val)	_wr32(_REG_BASE_+(0x0766<<2),(UINT)((_rd32(_REG_BASE_+(0x0766<<2))&(~ValSft_L18(BitMask_06)))|ValSft_L18((val)&BitMask_06)))

#define EXE_YQT_GAIN_Ar			(ValSft_R12(_rd32(_REG_BASE_+(0x0766<<2)))&BitMask_06)
#define EXE_YQT_GAIN_Aw(val)	_wr32(_REG_BASE_+(0x0766<<2),(UINT)((_rd32(_REG_BASE_+(0x0766<<2))&(~ValSft_L12(BitMask_06)))|ValSft_L12((val)&BitMask_06)))

#define EXE_CQT_GAIN_Ar			(ValSft_R06(_rd32(_REG_BASE_+(0x0766<<2)))&BitMask_06)
#define EXE_CQT_GAIN_Aw(val)	_wr32(_REG_BASE_+(0x0766<<2),(UINT)((_rd32(_REG_BASE_+(0x0766<<2))&(~ValSft_L06(BitMask_06)))|ValSft_L06((val)&BitMask_06)))

#define EXE_DC_FIX_Ar			(ValSft_R05(_rd32(_REG_BASE_+(0x0766<<2)))&BitMask_01)
#define EXE_DC_FIX_Aw(val)		_wr32(_REG_BASE_+(0x0766<<2),(UINT)((_rd32(_REG_BASE_+(0x0766<<2))&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))

#define EXE_FLD_SKIP_Ar			(ValSft_R31(_rd32(_REG_BASE_+(0x0767<<2)))&BitMask_01)
#define EXE_FLD_SKIP_Aw(val)	_wr32(_REG_BASE_+(0x0767<<2),(UINT)((_rd32(_REG_BASE_+(0x0767<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define EXE_VSP_SEL_Ar			(ValSft_R30(_rd32(_REG_BASE_+(0x0767<<2)))&BitMask_01)
#define EXE_VSP_SEL_Aw(val)		_wr32(_REG_BASE_+(0x0767<<2),(UINT)((_rd32(_REG_BASE_+(0x0767<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define EXE_VSP_USR_Ar			(ValSft_R16(_rd32(_REG_BASE_+(0x0767<<2)))&BitMask_14)
#define EXE_VSP_USR_Aw(val)		_wr32(_REG_BASE_+(0x0767<<2),(UINT)((_rd32(_REG_BASE_+(0x0767<<2))&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define EXE_HTC_SEL_Ar			(ValSft_R15(_rd32(_REG_BASE_+(0x0767<<2)))&BitMask_01)
#define EXE_HTC_SEL_Aw(val)		_wr32(_REG_BASE_+(0x0767<<2),(UINT)((_rd32(_REG_BASE_+(0x0767<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define EXE_HTC_USR_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x0767<<2)))&BitMask_15)
#define EXE_HTC_USR_Aw(val)		_wr32(_REG_BASE_+(0x0767<<2),(UINT)((_rd32(_REG_BASE_+(0x0767<<2))&(~ValSft_L00(BitMask_15)))|ValSft_L00((val)&BitMask_15)))

#define EXD_EXPGN_ON_Ar			(ValSft_R31(_rd32(_REG_BASE_+(0x0769<<2)))&BitMask_01)
#define EXD_EXPGN_ON_Aw(val)	_wr32(_REG_BASE_+(0x0769<<2),(UINT)((_rd32(_REG_BASE_+(0x0769<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define EXD_EXPGN_MODE_Ar		(ValSft_R29(_rd32(_REG_BASE_+(0x0769<<2)))&BitMask_02)
#define EXD_EXPGN_MODE_Aw(val)	_wr32(_REG_BASE_+(0x0769<<2),(UINT)((_rd32(_REG_BASE_+(0x0769<<2))&(~ValSft_L29(BitMask_02)))|ValSft_L29((val)&BitMask_02)))

#define EXD_PARSER_MODE_Ar		(ValSft_R27(_rd32(_REG_BASE_+(0x0769<<2)))&BitMask_01)
#define EXD_PARSER_MODE_Aw(val)	_wr32(_REG_BASE_+(0x0769<<2),(UINT)((_rd32(_REG_BASE_+(0x0769<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define EXD_SYNC_MODE_Ar		(ValSft_R17(_rd32(_REG_BASE_+(0x0769<<2)))&BitMask_01)
#define EXD_SYNC_MODE_Aw(val)	_wr32(_REG_BASE_+(0x0769<<2),(UINT)((_rd32(_REG_BASE_+(0x0769<<2))&(~ValSft_L17(BitMask_01)))|ValSft_L17((val)&BitMask_01)))

#define EXD_FLD_TOGGLE_Ar		(ValSft_R16(_rd32(_REG_BASE_+(0x0769<<2)))&BitMask_01)
#define EXD_FLD_TOGGLE_Aw(val)	_wr32(_REG_BASE_+(0x0769<<2),(UINT)((_rd32(_REG_BASE_+(0x0769<<2))&(~ValSft_L16(BitMask_01)))|ValSft_L16((val)&BitMask_01)))

#define EXD_HRESET_GAP_Ar		(ValSft_R08(_rd32(_REG_BASE_+(0x0769<<2)))&BitMask_08)
#define EXD_HRESET_GAP_Aw(val)	_wr32(_REG_BASE_+(0x0769<<2),(UINT)((_rd32(_REG_BASE_+(0x0769<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define EXD_VOFFSET_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x0769<<2)))&BitMask_06)
#define EXD_VOFFSET_Aw(val)		_wr32(_REG_BASE_+(0x0769<<2),(UINT)((_rd32(_REG_BASE_+(0x0769<<2))&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define EXD_VOFF_AUTO_ON_Ar		(ValSft_R31(_rd32(_REG_BASE_+(0x076a<<2)))&BitMask_01)
#define EXD_VOFF_AUTO_ON_Aw(val)	_wr32(_REG_BASE_+(0x076a<<2),(UINT)((_rd32(_REG_BASE_+(0x076a<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define EXD_VOFF_720P24_Ar		(ValSft_R24(_rd32(_REG_BASE_+(0x076a<<2)))&BitMask_06)
#define EXD_VOFF_720P24_Aw(val)	_wr32(_REG_BASE_+(0x076a<<2),(UINT)((_rd32(_REG_BASE_+(0x076a<<2))&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define EXD_VOFF_720P25_Ar		(ValSft_R16(_rd32(_REG_BASE_+(0x076a<<2)))&BitMask_06)
#define EXD_VOFF_720P25_Aw(val)	_wr32(_REG_BASE_+(0x076a<<2),(UINT)((_rd32(_REG_BASE_+(0x076a<<2))&(~ValSft_L16(BitMask_06)))|ValSft_L16((val)&BitMask_06)))

#define EXD_VOFF_720P30_Ar		(ValSft_R08(_rd32(_REG_BASE_+(0x076a<<2)))&BitMask_06)
#define EXD_VOFF_720P30_Aw(val)	_wr32(_REG_BASE_+(0x076a<<2),(UINT)((_rd32(_REG_BASE_+(0x076a<<2))&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define EXD_VOFF_720P50_Ar		(ValSft_R00(_rd32(_REG_BASE_+(0x076a<<2)))&BitMask_06)
#define EXD_VOFF_720P50_Aw(val)	_wr32(_REG_BASE_+(0x076a<<2),(UINT)((_rd32(_REG_BASE_+(0x076a<<2))&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define EXD_VOFF_720P60_Ar		(ValSft_R24(_rd32(_REG_BASE_+(0x076b<<2)))&BitMask_06)
#define EXD_VOFF_720P60_Aw(val)	_wr32(_REG_BASE_+(0x076b<<2),(UINT)((_rd32(_REG_BASE_+(0x076b<<2))&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define EXD_VOFF_1080P24_Ar		(ValSft_R16(_rd32(_REG_BASE_+(0x076b<<2)))&BitMask_06)
#define EXD_VOFF_1080P24_Aw(val)	_wr32(_REG_BASE_+(0x076b<<2),(UINT)((_rd32(_REG_BASE_+(0x076b<<2))&(~ValSft_L16(BitMask_06)))|ValSft_L16((val)&BitMask_06)))

#define EXD_VOFF_1080P25_Ar		(ValSft_R08(_rd32(_REG_BASE_+(0x076b<<2)))&BitMask_06)
#define EXD_VOFF_1080P25_Aw(val)	_wr32(_REG_BASE_+(0x076b<<2),(UINT)((_rd32(_REG_BASE_+(0x076b<<2))&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define EXD_VOFF_1080P30_Ar		(ValSft_R00(_rd32(_REG_BASE_+(0x076b<<2)))&BitMask_06)
#define EXD_VOFF_1080P30_Aw(val)	_wr32(_REG_BASE_+(0x076b<<2),(UINT)((_rd32(_REG_BASE_+(0x076b<<2))&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define EXD_PGN_ON_Ar			(ValSft_R08(_rd32(_REG_BASE_+(0x076c<<2)))&BitMask_01)
#define EXD_PGN_ON_Aw(val)		_wr32(_REG_BASE_+(0x076c<<2),(UINT)((_rd32(_REG_BASE_+(0x076c<<2))&(~ValSft_L08(BitMask_01)))|ValSft_L08((val)&BitMask_01)))

#define EXD_PGN_YPAT_Ar			(ValSft_R04(_rd32(_REG_BASE_+(0x076c<<2)))&BitMask_04)
#define EXD_PGN_YPAT_Aw(val)	_wr32(_REG_BASE_+(0x076c<<2),(UINT)((_rd32(_REG_BASE_+(0x076c<<2))&(~ValSft_L04(BitMask_04)))|ValSft_L04((val)&BitMask_04)))

#define EXD_PGN_CPAT_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x076c<<2)))&BitMask_04)
#define EXD_PGN_CPAT_Aw(val)	_wr32(_REG_BASE_+(0x076c<<2),(UINT)((_rd32(_REG_BASE_+(0x076c<<2))&(~ValSft_L00(BitMask_04)))|ValSft_L00((val)&BitMask_04)))

#define EXD_Y_UPPER_Ar			(ValSft_R20(_rd32(_REG_BASE_+(0x076d<<2)))&BitMask_10)
#define EXD_Y_UPPER_Aw(val)		_wr32(_REG_BASE_+(0x076d<<2),(UINT)((_rd32(_REG_BASE_+(0x076d<<2))&(~ValSft_L20(BitMask_10)))|ValSft_L20((val)&BitMask_10)))

#define EXD_Y_LOWER_Ar			(ValSft_R10(_rd32(_REG_BASE_+(0x076d<<2)))&BitMask_10)
#define EXD_Y_LOWER_Aw(val)		_wr32(_REG_BASE_+(0x076d<<2),(UINT)((_rd32(_REG_BASE_+(0x076d<<2))&(~ValSft_L10(BitMask_10)))|ValSft_L10((val)&BitMask_10)))

#define EXD_C_UPPER_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x076d<<2)))&BitMask_10)
#define EXD_C_UPPER_Aw(val)		_wr32(_REG_BASE_+(0x076d<<2),(UINT)((_rd32(_REG_BASE_+(0x076d<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define EXD_C_LOWER_Ar			(ValSft_R20(_rd32(_REG_BASE_+(0x076e<<2)))&BitMask_10)
#define EXD_C_LOWER_Aw(val)		_wr32(_REG_BASE_+(0x076e<<2),(UINT)((_rd32(_REG_BASE_+(0x076e<<2))&(~ValSft_L20(BitMask_10)))|ValSft_L20((val)&BitMask_10)))

#define EXD_VINT_EN_Ar			(ValSft_R14(_rd32(_REG_BASE_+(0x076e<<2)))&BitMask_01)
#define EXD_VINT_EN_Aw(val)		_wr32(_REG_BASE_+(0x076e<<2),(UINT)((_rd32(_REG_BASE_+(0x076e<<2))&(~ValSft_L14(BitMask_01)))|ValSft_L14((val)&BitMask_01)))

#define EXD_VINT_LN_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x076e<<2)))&BitMask_14)
#define EXD_VINT_LN_Aw(val)		_wr32(_REG_BASE_+(0x076e<<2),(UINT)((_rd32(_REG_BASE_+(0x076e<<2))&(~ValSft_L00(BitMask_14)))|ValSft_L00((val)&BitMask_14)))

#define EXD_OSD_ON_Ar			(ValSft_R31(_rd32(_REG_BASE_+(0x076f<<2)))&BitMask_01)
#define EXD_OSD_ON_Aw(val)		_wr32(_REG_BASE_+(0x076f<<2),(UINT)((_rd32(_REG_BASE_+(0x076f<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DS_EXSDI_VER_Br			(ValSft_R28(_rd32(_REG_BASE_+(0x0771<<2)))&BitMask_04)
#define DS_EXSDI_VER_Bw(val)	_wr32(_REG_BASE_+(0x0771<<2),(UINT)((_rd32(_REG_BASE_+(0x0771<<2))&(~ValSft_L28(BitMask_04)))|ValSft_L28((val)&BitMask_04)))

#define DS_BIT_MODE_Br			(ValSft_R27(_rd32(_REG_BASE_+(0x0771<<2)))&BitMask_01)
#define DS_BIT_MODE_Bw(val)		_wr32(_REG_BASE_+(0x0771<<2),(UINT)((_rd32(_REG_BASE_+(0x0771<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define DS_ID_CH_Br				(ValSft_R16(_rd32(_REG_BASE_+(0x0771<<2)))&BitMask_04)
#define DS_ID_CH_Bw(val)		_wr32(_REG_BASE_+(0x0771<<2),(UINT)((_rd32(_REG_BASE_+(0x0771<<2))&(~ValSft_L16(BitMask_04)))|ValSft_L16((val)&BitMask_04)))

#define DS_ID_SPLIT_Br			(ValSft_R14(_rd32(_REG_BASE_+(0x0771<<2)))&BitMask_02)
#define DS_ID_SPLIT_Bw(val)		_wr32(_REG_BASE_+(0x0771<<2),(UINT)((_rd32(_REG_BASE_+(0x0771<<2))&(~ValSft_L14(BitMask_02)))|ValSft_L14((val)&BitMask_02)))

#define DSD_ID_MATCH_ON_Br		(ValSft_R13(_rd32(_REG_BASE_+(0x0771<<2)))&BitMask_01)
#define DSD_ID_MATCH_ON_Bw(val)	_wr32(_REG_BASE_+(0x0771<<2),(UINT)((_rd32(_REG_BASE_+(0x0771<<2))&(~ValSft_L13(BitMask_01)))|ValSft_L13((val)&BitMask_01)))

#define DSE_SLCK_FREQ_Br		(ValSft_R09(_rd32(_REG_BASE_+(0x0771<<2)))&BitMask_02)
#define DSE_SLCK_FREQ_Bw(val)	_wr32(_REG_BASE_+(0x0771<<2),(UINT)((_rd32(_REG_BASE_+(0x0771<<2))&(~ValSft_L09(BitMask_02)))|ValSft_L09((val)&BitMask_02)))

#define DSD_DEC_PGEN_ON_Br		(ValSft_R05(_rd32(_REG_BASE_+(0x0771<<2)))&BitMask_01)
#define DSD_DEC_PGEN_ON_Bw(val)	_wr32(_REG_BASE_+(0x0771<<2),(UINT)((_rd32(_REG_BASE_+(0x0771<<2))&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))

#define DSD_DEC_PGEN_MODE_Br	(ValSft_R02(_rd32(_REG_BASE_+(0x0771<<2)))&BitMask_03)
#define DSD_DEC_PGEN_MODE_Bw(val)	_wr32(_REG_BASE_+(0x0771<<2),(UINT)((_rd32(_REG_BASE_+(0x0771<<2))&(~ValSft_L02(BitMask_03)))|ValSft_L02((val)&BitMask_03)))

#define DSD_8B10B_ERST_Br		(ValSft_R01(_rd32(_REG_BASE_+(0x0771<<2)))&BitMask_01)
#define DSD_8B10B_ERST_Bw(val)	_wr32(_REG_BASE_+(0x0771<<2),(UINT)((_rd32(_REG_BASE_+(0x0771<<2))&(~ValSft_L01(BitMask_01)))|ValSft_L01((val)&BitMask_01)))

#define DSD_CRC_ERST_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x0771<<2)))&BitMask_01)
#define DSD_CRC_ERST_Bw(val)	_wr32(_REG_BASE_+(0x0771<<2),(UINT)((_rd32(_REG_BASE_+(0x0771<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define DSE_BLK_DAT_SEL_Br		(ValSft_R09(_rd32(_REG_BASE_+(0x0772<<2)))&BitMask_01)
#define DSE_BLK_DAT_SEL_Bw(val)	_wr32(_REG_BASE_+(0x0772<<2),(UINT)((_rd32(_REG_BASE_+(0x0772<<2))&(~ValSft_L09(BitMask_01)))|ValSft_L09((val)&BitMask_01)))

#define DS_FMT_HDTRS_ON_Br		(ValSft_R08(_rd32(_REG_BASE_+(0x0772<<2)))&BitMask_01)
#define DS_FMT_HDTRS_ON_Bw(val)	_wr32(_REG_BASE_+(0x0772<<2),(UINT)((_rd32(_REG_BASE_+(0x0772<<2))&(~ValSft_L08(BitMask_01)))|ValSft_L08((val)&BitMask_01)))

#define DSE_FMT_FIFO_LMT_Br		(ValSft_R02(_rd32(_REG_BASE_+(0x0772<<2)))&BitMask_06)
#define DSE_FMT_FIFO_LMT_Bw(val)	_wr32(_REG_BASE_+(0x0772<<2),(UINT)((_rd32(_REG_BASE_+(0x0772<<2))&(~ValSft_L02(BitMask_06)))|ValSft_L02((val)&BitMask_06)))

#define DSD_DEFMT_BYPASS_Br		(ValSft_R00(_rd32(_REG_BASE_+(0x0772<<2)))&BitMask_01)
#define DSD_DEFMT_BYPASS_Bw(val)	_wr32(_REG_BASE_+(0x0772<<2),(UINT)((_rd32(_REG_BASE_+(0x0772<<2))&(~ValSft_L00(BitMask_01)))|ValSft_L00((val)&BitMask_01)))

#define DSE_MEM_AFULL_TH_Br		(ValSft_R16(_rd32(_REG_BASE_+(0x0773<<2)))&BitMask_10)
#define DSE_MEM_AFULL_TH_Bw(val)	_wr32(_REG_BASE_+(0x0773<<2),(UINT)((_rd32(_REG_BASE_+(0x0773<<2))&(~ValSft_L16(BitMask_10)))|ValSft_L16((val)&BitMask_10)))

#define DSE_MEM_RD_LMT_ON_Br	(ValSft_R15(_rd32(_REG_BASE_+(0x0773<<2)))&BitMask_01)
#define DSE_MEM_RD_LMT_ON_Bw(val)	_wr32(_REG_BASE_+(0x0773<<2),(UINT)((_rd32(_REG_BASE_+(0x0773<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define DSE_MEM_RD_LMT_CNT_Br	(ValSft_R00(_rd32(_REG_BASE_+(0x0773<<2)))&BitMask_12)
#define DSE_MEM_RD_LMT_CNT_Bw(val)	_wr32(_REG_BASE_+(0x0773<<2),(UINT)((_rd32(_REG_BASE_+(0x0773<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define DSE_RD_SYNC_ON_Br		(ValSft_R31(_rd32(_REG_BASE_+(0x0774<<2)))&BitMask_01)
#define DSE_RD_SYNC_ON_Bw(val)	_wr32(_REG_BASE_+(0x0774<<2),(UINT)((_rd32(_REG_BASE_+(0x0774<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DSE_RD_SYNC_TCNT_Br		(ValSft_R16(_rd32(_REG_BASE_+(0x0774<<2)))&BitMask_12)
#define DSE_RD_SYNC_TCNT_Bw(val)	_wr32(_REG_BASE_+(0x0774<<2),(UINT)((_rd32(_REG_BASE_+(0x0774<<2))&(~ValSft_L16(BitMask_12)))|ValSft_L16((val)&BitMask_12)))

#define DSE_RD_SYNC_ACNT_Br		(ValSft_R00(_rd32(_REG_BASE_+(0x0774<<2)))&BitMask_12)
#define DSE_RD_SYNC_ACNT_Bw(val)	_wr32(_REG_BASE_+(0x0774<<2),(UINT)((_rd32(_REG_BASE_+(0x0774<<2))&(~ValSft_L00(BitMask_12)))|ValSft_L00((val)&BitMask_12)))

#define DS_AUD_ON_Br			(ValSft_R23(_rd32(_REG_BASE_+(0x0775<<2)))&BitMask_01)
#define DS_AUD_ON_Bw(val)		_wr32(_REG_BASE_+(0x0775<<2),(UINT)((_rd32(_REG_BASE_+(0x0775<<2))&(~ValSft_L23(BitMask_01)))|ValSft_L23((val)&BitMask_01)))

#define DSE_AUD_MSCK_FREQ_Br	(ValSft_R20(_rd32(_REG_BASE_+(0x0775<<2)))&BitMask_03)
#define DSE_AUD_MSCK_FREQ_Bw(val)	_wr32(_REG_BASE_+(0x0775<<2),(UINT)((_rd32(_REG_BASE_+(0x0775<<2))&(~ValSft_L20(BitMask_03)))|ValSft_L20((val)&BitMask_03)))

#define DSE_AUD_ENC_ACT0_Br		(ValSft_R17(_rd32(_REG_BASE_+(0x0775<<2)))&BitMask_01)
#define DSE_AUD_ENC_ACT0_Bw(val)	_wr32(_REG_BASE_+(0x0775<<2),(UINT)((_rd32(_REG_BASE_+(0x0775<<2))&(~ValSft_L17(BitMask_01)))|ValSft_L17((val)&BitMask_01)))

#define DSE_AUD_ENC_ACT1_Br		(ValSft_R16(_rd32(_REG_BASE_+(0x0775<<2)))&BitMask_01)
#define DSE_AUD_ENC_ACT1_Bw(val)	_wr32(_REG_BASE_+(0x0775<<2),(UINT)((_rd32(_REG_BASE_+(0x0775<<2))&(~ValSft_L16(BitMask_01)))|ValSft_L16((val)&BitMask_01)))

#define DSE_AUD_ENC_RATE_Br		(ValSft_R08(_rd32(_REG_BASE_+(0x0775<<2)))&BitMask_08)
#define DSE_AUD_ENC_RATE_Bw(val)	_wr32(_REG_BASE_+(0x0775<<2),(UINT)((_rd32(_REG_BASE_+(0x0775<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define DSD_AUD_MSCK_FREQ_ON_Br	(ValSft_R31(_rd32(_REG_BASE_+(0x0776<<2)))&BitMask_01)
#define DSD_AUD_MSCK_FREQ_ON_Bw(val)	_wr32(_REG_BASE_+(0x0776<<2),(UINT)((_rd32(_REG_BASE_+(0x0776<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DSD_AUD_MSCK_FREQ_Br	(ValSft_R28(_rd32(_REG_BASE_+(0x0776<<2)))&BitMask_03)
#define DSD_AUD_MSCK_FREQ_Bw(val)	_wr32(_REG_BASE_+(0x0776<<2),(UINT)((_rd32(_REG_BASE_+(0x0776<<2))&(~ValSft_L28(BitMask_03)))|ValSft_L28((val)&BitMask_03)))

#define DSD_AUD_INTP_ON_Br		(ValSft_R27(_rd32(_REG_BASE_+(0x0776<<2)))&BitMask_01)
#define DSD_AUD_INTP_ON_Bw(val)	_wr32(_REG_BASE_+(0x0776<<2),(UINT)((_rd32(_REG_BASE_+(0x0776<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define DSD_AUD_ADET_ON_Br		(ValSft_R26(_rd32(_REG_BASE_+(0x0776<<2)))&BitMask_01)
#define DSD_AUD_ADET_ON_Bw(val)	_wr32(_REG_BASE_+(0x0776<<2),(UINT)((_rd32(_REG_BASE_+(0x0776<<2))&(~ValSft_L26(BitMask_01)))|ValSft_L26((val)&BitMask_01)))

#define DSD_AUD_ADET_CNT_Br		(ValSft_R00(_rd32(_REG_BASE_+(0x0776<<2)))&BitMask_26)
#define DSD_AUD_ADET_CNT_Bw(val)	_wr32(_REG_BASE_+(0x0776<<2),(UINT)((_rd32(_REG_BASE_+(0x0776<<2))&(~ValSft_L00(BitMask_26)))|ValSft_L00((val)&BitMask_26)))

#define DS_ANC_ON_Br			(ValSft_R31(_rd32(_REG_BASE_+(0x0777<<2)))&BitMask_01)
#define DS_ANC_ON_Bw(val)		_wr32(_REG_BASE_+(0x0777<<2),(UINT)((_rd32(_REG_BASE_+(0x0777<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define DSD_ANC_ADET_CNT_Br		(ValSft_R00(_rd32(_REG_BASE_+(0x0777<<2)))&BitMask_26)
#define DSD_ANC_ADET_CNT_Bw(val)	_wr32(_REG_BASE_+(0x0777<<2),(UINT)((_rd32(_REG_BASE_+(0x0777<<2))&(~ValSft_L00(BitMask_26)))|ValSft_L00((val)&BitMask_26)))

#define EXE_PGN_ON_Br			(ValSft_R24(_rd32(_REG_BASE_+(0x0781<<2)))&BitMask_01)
#define EXE_PGN_ON_Bw(val)		_wr32(_REG_BASE_+(0x0781<<2),(UINT)((_rd32(_REG_BASE_+(0x0781<<2))&(~ValSft_L24(BitMask_01)))|ValSft_L24((val)&BitMask_01)))

#define EXE_PGN_YPAT_Br			(ValSft_R20(_rd32(_REG_BASE_+(0x0781<<2)))&BitMask_04)
#define EXE_PGN_YPAT_Bw(val)	_wr32(_REG_BASE_+(0x0781<<2),(UINT)((_rd32(_REG_BASE_+(0x0781<<2))&(~ValSft_L20(BitMask_04)))|ValSft_L20((val)&BitMask_04)))

#define EXE_PGN_CPAT_Br			(ValSft_R16(_rd32(_REG_BASE_+(0x0781<<2)))&BitMask_04)
#define EXE_PGN_CPAT_Bw(val)	_wr32(_REG_BASE_+(0x0781<<2),(UINT)((_rd32(_REG_BASE_+(0x0781<<2))&(~ValSft_L16(BitMask_04)))|ValSft_L16((val)&BitMask_04)))

#define EXE_PGN_INTER_Br		(ValSft_R15(_rd32(_REG_BASE_+(0x0781<<2)))&BitMask_01)
#define EXE_PGN_INTER_Bw(val)	_wr32(_REG_BASE_+(0x0781<<2),(UINT)((_rd32(_REG_BASE_+(0x0781<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define EXE_PGN_VSP_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x0781<<2)))&BitMask_13)
#define EXE_PGN_VSP_Bw(val)		_wr32(_REG_BASE_+(0x0781<<2),(UINT)((_rd32(_REG_BASE_+(0x0781<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define EXE_PGN_HTC_Br			(ValSft_R16(_rd32(_REG_BASE_+(0x0782<<2)))&BitMask_14)
#define EXE_PGN_HTC_Bw(val)		_wr32(_REG_BASE_+(0x0782<<2),(UINT)((_rd32(_REG_BASE_+(0x0782<<2))&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define EXE_PGN_VTC_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x0782<<2)))&BitMask_13)
#define EXE_PGN_VTC_Bw(val)		_wr32(_REG_BASE_+(0x0782<<2),(UINT)((_rd32(_REG_BASE_+(0x0782<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define EXE_PGN_HW_Br			(ValSft_R16(_rd32(_REG_BASE_+(0x0783<<2)))&BitMask_14)
#define EXE_PGN_HW_Bw(val)		_wr32(_REG_BASE_+(0x0783<<2),(UINT)((_rd32(_REG_BASE_+(0x0783<<2))&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define EXE_PGN_VW_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x0783<<2)))&BitMask_13)
#define EXE_PGN_VW_Bw(val)		_wr32(_REG_BASE_+(0x0783<<2),(UINT)((_rd32(_REG_BASE_+(0x0783<<2))&(~ValSft_L00(BitMask_13)))|ValSft_L00((val)&BitMask_13)))

#define EXE_ELOCK_OFFSET_Br		(ValSft_R28(_rd32(_REG_BASE_+(0x0784<<2)))&BitMask_04)
#define EXE_ELOCK_OFFSET_Bw(val)	_wr32(_REG_BASE_+(0x0784<<2),(UINT)((_rd32(_REG_BASE_+(0x0784<<2))&(~ValSft_L28(BitMask_04)))|ValSft_L28((val)&BitMask_04)))

#define EXE_RST_IVL_Br			(ValSft_R27(_rd32(_REG_BASE_+(0x0784<<2)))&BitMask_01)
#define EXE_RST_IVL_Bw(val)		_wr32(_REG_BASE_+(0x0784<<2),(UINT)((_rd32(_REG_BASE_+(0x0784<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define EXE_LPF_EN_Br			(ValSft_R25(_rd32(_REG_BASE_+(0x0784<<2)))&BitMask_01)
#define EXE_LPF_EN_Bw(val)		_wr32(_REG_BASE_+(0x0784<<2),(UINT)((_rd32(_REG_BASE_+(0x0784<<2))&(~ValSft_L25(BitMask_01)))|ValSft_L25((val)&BitMask_01)))

#define EXE_DCT_CUT_EN_Br		(ValSft_R24(_rd32(_REG_BASE_+(0x0784<<2)))&BitMask_01)
#define EXE_DCT_CUT_EN_Bw(val)	_wr32(_REG_BASE_+(0x0784<<2),(UINT)((_rd32(_REG_BASE_+(0x0784<<2))&(~ValSft_L24(BitMask_01)))|ValSft_L24((val)&BitMask_01)))

#define EXE_DCT_CUT_NUM_Br		(ValSft_R18(_rd32(_REG_BASE_+(0x0784<<2)))&BitMask_06)
#define EXE_DCT_CUT_NUM_Bw(val)	_wr32(_REG_BASE_+(0x0784<<2),(UINT)((_rd32(_REG_BASE_+(0x0784<<2))&(~ValSft_L18(BitMask_06)))|ValSft_L18((val)&BitMask_06)))

#define EXE_QUAL_AUTO_ON_Br		(ValSft_R15(_rd32(_REG_BASE_+(0x0784<<2)))&BitMask_01)
#define EXE_QUAL_AUTO_ON_Bw(val)	_wr32(_REG_BASE_+(0x0784<<2),(UINT)((_rd32(_REG_BASE_+(0x0784<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define EXE_QUAL_VAL_Br			(ValSft_R10(_rd32(_REG_BASE_+(0x0784<<2)))&BitMask_05)
#define EXE_QUAL_VAL_Bw(val)	_wr32(_REG_BASE_+(0x0784<<2),(UINT)((_rd32(_REG_BASE_+(0x0784<<2))&(~ValSft_L10(BitMask_05)))|ValSft_L10((val)&BitMask_05)))

#define EXE_QUAL_HIGH_Br		(ValSft_R05(_rd32(_REG_BASE_+(0x0784<<2)))&BitMask_05)
#define EXE_QUAL_HIGH_Bw(val)	_wr32(_REG_BASE_+(0x0784<<2),(UINT)((_rd32(_REG_BASE_+(0x0784<<2))&(~ValSft_L05(BitMask_05)))|ValSft_L05((val)&BitMask_05)))

#define EXE_QUAL_LOW_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x0784<<2)))&BitMask_05)
#define EXE_QUAL_LOW_Bw(val)	_wr32(_REG_BASE_+(0x0784<<2),(UINT)((_rd32(_REG_BASE_+(0x0784<<2))&(~ValSft_L00(BitMask_05)))|ValSft_L00((val)&BitMask_05)))

#define EXE_QUAL_QP_FREQ_Br		(ValSft_R24(_rd32(_REG_BASE_+(0x0785<<2)))&BitMask_06)
#define EXE_QUAL_QP_FREQ_Bw(val)	_wr32(_REG_BASE_+(0x0785<<2),(UINT)((_rd32(_REG_BASE_+(0x0785<<2))&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define EXE_QUAL_P_GAIN_Br		(ValSft_R16(_rd32(_REG_BASE_+(0x0785<<2)))&BitMask_08)
#define EXE_QUAL_P_GAIN_Bw(val)	_wr32(_REG_BASE_+(0x0785<<2),(UINT)((_rd32(_REG_BASE_+(0x0785<<2))&(~ValSft_L16(BitMask_08)))|ValSft_L16((val)&BitMask_08)))

#define EXE_QUAL_I_GAIN_Br		(ValSft_R10(_rd32(_REG_BASE_+(0x0785<<2)))&BitMask_06)
#define EXE_QUAL_I_GAIN_Bw(val)	_wr32(_REG_BASE_+(0x0785<<2),(UINT)((_rd32(_REG_BASE_+(0x0785<<2))&(~ValSft_L10(BitMask_06)))|ValSft_L10((val)&BitMask_06)))

#define EXE_QUAL_I_OFFSET_Br	(ValSft_R00(_rd32(_REG_BASE_+(0x0785<<2)))&BitMask_10)
#define EXE_QUAL_I_OFFSET_Bw(val)	_wr32(_REG_BASE_+(0x0785<<2),(UINT)((_rd32(_REG_BASE_+(0x0785<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define EXE_QP_MODE_Br			(ValSft_R30(_rd32(_REG_BASE_+(0x0786<<2)))&BitMask_02)
#define EXE_QP_MODE_Bw(val)		_wr32(_REG_BASE_+(0x0786<<2),(UINT)((_rd32(_REG_BASE_+(0x0786<<2))&(~ValSft_L30(BitMask_02)))|ValSft_L30((val)&BitMask_02)))

#define EXE_YDC_QTBL_Br			(ValSft_R24(_rd32(_REG_BASE_+(0x0786<<2)))&BitMask_06)
#define EXE_YDC_QTBL_Bw(val)	_wr32(_REG_BASE_+(0x0786<<2),(UINT)((_rd32(_REG_BASE_+(0x0786<<2))&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define EXE_CDC_QTBL_Br			(ValSft_R18(_rd32(_REG_BASE_+(0x0786<<2)))&BitMask_06)
#define EXE_CDC_QTBL_Bw(val)	_wr32(_REG_BASE_+(0x0786<<2),(UINT)((_rd32(_REG_BASE_+(0x0786<<2))&(~ValSft_L18(BitMask_06)))|ValSft_L18((val)&BitMask_06)))

#define EXE_YQT_GAIN_Br			(ValSft_R12(_rd32(_REG_BASE_+(0x0786<<2)))&BitMask_06)
#define EXE_YQT_GAIN_Bw(val)	_wr32(_REG_BASE_+(0x0786<<2),(UINT)((_rd32(_REG_BASE_+(0x0786<<2))&(~ValSft_L12(BitMask_06)))|ValSft_L12((val)&BitMask_06)))

#define EXE_CQT_GAIN_Br			(ValSft_R06(_rd32(_REG_BASE_+(0x0786<<2)))&BitMask_06)
#define EXE_CQT_GAIN_Bw(val)	_wr32(_REG_BASE_+(0x0786<<2),(UINT)((_rd32(_REG_BASE_+(0x0786<<2))&(~ValSft_L06(BitMask_06)))|ValSft_L06((val)&BitMask_06)))

#define EXE_DC_FIX_Br			(ValSft_R05(_rd32(_REG_BASE_+(0x0786<<2)))&BitMask_01)
#define EXE_DC_FIX_Bw(val)		_wr32(_REG_BASE_+(0x0786<<2),(UINT)((_rd32(_REG_BASE_+(0x0786<<2))&(~ValSft_L05(BitMask_01)))|ValSft_L05((val)&BitMask_01)))

#define EXE_FLD_SKIP_Br			(ValSft_R31(_rd32(_REG_BASE_+(0x0787<<2)))&BitMask_01)
#define EXE_FLD_SKIP_Bw(val)	_wr32(_REG_BASE_+(0x0787<<2),(UINT)((_rd32(_REG_BASE_+(0x0787<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define EXE_VSP_SEL_Br			(ValSft_R30(_rd32(_REG_BASE_+(0x0787<<2)))&BitMask_01)
#define EXE_VSP_SEL_Bw(val)		_wr32(_REG_BASE_+(0x0787<<2),(UINT)((_rd32(_REG_BASE_+(0x0787<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define EXE_VSP_USR_Br			(ValSft_R16(_rd32(_REG_BASE_+(0x0787<<2)))&BitMask_14)
#define EXE_VSP_USR_Bw(val)		_wr32(_REG_BASE_+(0x0787<<2),(UINT)((_rd32(_REG_BASE_+(0x0787<<2))&(~ValSft_L16(BitMask_14)))|ValSft_L16((val)&BitMask_14)))

#define EXE_HTC_SEL_Br			(ValSft_R15(_rd32(_REG_BASE_+(0x0787<<2)))&BitMask_01)
#define EXE_HTC_SEL_Bw(val)		_wr32(_REG_BASE_+(0x0787<<2),(UINT)((_rd32(_REG_BASE_+(0x0787<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define EXE_HTC_USR_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x0787<<2)))&BitMask_15)
#define EXE_HTC_USR_Bw(val)		_wr32(_REG_BASE_+(0x0787<<2),(UINT)((_rd32(_REG_BASE_+(0x0787<<2))&(~ValSft_L00(BitMask_15)))|ValSft_L00((val)&BitMask_15)))

#define EXD_EXPGN_ON_Br			(ValSft_R31(_rd32(_REG_BASE_+(0x0789<<2)))&BitMask_01)
#define EXD_EXPGN_ON_Bw(val)	_wr32(_REG_BASE_+(0x0789<<2),(UINT)((_rd32(_REG_BASE_+(0x0789<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define EXD_EXPGN_MODE_Br		(ValSft_R29(_rd32(_REG_BASE_+(0x0789<<2)))&BitMask_02)
#define EXD_EXPGN_MODE_Bw(val)	_wr32(_REG_BASE_+(0x0789<<2),(UINT)((_rd32(_REG_BASE_+(0x0789<<2))&(~ValSft_L29(BitMask_02)))|ValSft_L29((val)&BitMask_02)))

#define EXD_PARSER_MODE_Br		(ValSft_R27(_rd32(_REG_BASE_+(0x0789<<2)))&BitMask_01)
#define EXD_PARSER_MODE_Bw(val)	_wr32(_REG_BASE_+(0x0789<<2),(UINT)((_rd32(_REG_BASE_+(0x0789<<2))&(~ValSft_L27(BitMask_01)))|ValSft_L27((val)&BitMask_01)))

#define EXD_SYNC_MODE_Br		(ValSft_R17(_rd32(_REG_BASE_+(0x0789<<2)))&BitMask_01)
#define EXD_SYNC_MODE_Bw(val)	_wr32(_REG_BASE_+(0x0789<<2),(UINT)((_rd32(_REG_BASE_+(0x0789<<2))&(~ValSft_L17(BitMask_01)))|ValSft_L17((val)&BitMask_01)))

#define EXD_FLD_TOGGLE_Br		(ValSft_R16(_rd32(_REG_BASE_+(0x0789<<2)))&BitMask_01)
#define EXD_FLD_TOGGLE_Bw(val)	_wr32(_REG_BASE_+(0x0789<<2),(UINT)((_rd32(_REG_BASE_+(0x0789<<2))&(~ValSft_L16(BitMask_01)))|ValSft_L16((val)&BitMask_01)))

#define EXD_HRESET_GAP_Br		(ValSft_R08(_rd32(_REG_BASE_+(0x0789<<2)))&BitMask_08)
#define EXD_HRESET_GAP_Bw(val)	_wr32(_REG_BASE_+(0x0789<<2),(UINT)((_rd32(_REG_BASE_+(0x0789<<2))&(~ValSft_L08(BitMask_08)))|ValSft_L08((val)&BitMask_08)))

#define EXD_HRESET_SEL_Br		(ValSft_R07(_rd32(_REG_BASE_+(0x0789<<2)))&BitMask_01)
#define EXD_HRESET_SEL_Bw(val)	_wr32(_REG_BASE_+(0x0789<<2),(UINT)((_rd32(_REG_BASE_+(0x0789<<2))&(~ValSft_L07(BitMask_01)))|ValSft_L07((val)&BitMask_01)))

#define EXD_VOFFSET_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x0789<<2)))&BitMask_06)
#define EXD_VOFFSET_Bw(val)		_wr32(_REG_BASE_+(0x0789<<2),(UINT)((_rd32(_REG_BASE_+(0x0789<<2))&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define EXD_VOFF_AUTO_ON_Br		(ValSft_R31(_rd32(_REG_BASE_+(0x078a<<2)))&BitMask_01)
#define EXD_VOFF_AUTO_ON_Bw(val)	_wr32(_REG_BASE_+(0x078a<<2),(UINT)((_rd32(_REG_BASE_+(0x078a<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define EXD_VOFF_720P24_Br		(ValSft_R24(_rd32(_REG_BASE_+(0x078a<<2)))&BitMask_06)
#define EXD_VOFF_720P24_Bw(val)	_wr32(_REG_BASE_+(0x078a<<2),(UINT)((_rd32(_REG_BASE_+(0x078a<<2))&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define EXD_VOFF_720P25_Br		(ValSft_R16(_rd32(_REG_BASE_+(0x078a<<2)))&BitMask_06)
#define EXD_VOFF_720P25_Bw(val)	_wr32(_REG_BASE_+(0x078a<<2),(UINT)((_rd32(_REG_BASE_+(0x078a<<2))&(~ValSft_L16(BitMask_06)))|ValSft_L16((val)&BitMask_06)))

#define EXD_VOFF_720P30_Br		(ValSft_R08(_rd32(_REG_BASE_+(0x078a<<2)))&BitMask_06)
#define EXD_VOFF_720P30_Bw(val)	_wr32(_REG_BASE_+(0x078a<<2),(UINT)((_rd32(_REG_BASE_+(0x078a<<2))&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define EXD_VOFF_720P50_Br		(ValSft_R00(_rd32(_REG_BASE_+(0x078a<<2)))&BitMask_06)
#define EXD_VOFF_720P50_Bw(val)	_wr32(_REG_BASE_+(0x078a<<2),(UINT)((_rd32(_REG_BASE_+(0x078a<<2))&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define EXD_VOFF_720P60_Br		(ValSft_R24(_rd32(_REG_BASE_+(0x078b<<2)))&BitMask_06)
#define EXD_VOFF_720P60_Bw(val)	_wr32(_REG_BASE_+(0x078b<<2),(UINT)((_rd32(_REG_BASE_+(0x078b<<2))&(~ValSft_L24(BitMask_06)))|ValSft_L24((val)&BitMask_06)))

#define EXD_VOFF_1080P24_Br		(ValSft_R16(_rd32(_REG_BASE_+(0x078b<<2)))&BitMask_06)
#define EXD_VOFF_1080P24_Bw(val)	_wr32(_REG_BASE_+(0x078b<<2),(UINT)((_rd32(_REG_BASE_+(0x078b<<2))&(~ValSft_L16(BitMask_06)))|ValSft_L16((val)&BitMask_06)))

#define EXD_VOFF_1080P25_Br		(ValSft_R08(_rd32(_REG_BASE_+(0x078b<<2)))&BitMask_06)
#define EXD_VOFF_1080P25_Bw(val)	_wr32(_REG_BASE_+(0x078b<<2),(UINT)((_rd32(_REG_BASE_+(0x078b<<2))&(~ValSft_L08(BitMask_06)))|ValSft_L08((val)&BitMask_06)))

#define EXD_VOFF_1080P30_Br		(ValSft_R00(_rd32(_REG_BASE_+(0x078b<<2)))&BitMask_06)
#define EXD_VOFF_1080P30_Bw(val)	_wr32(_REG_BASE_+(0x078b<<2),(UINT)((_rd32(_REG_BASE_+(0x078b<<2))&(~ValSft_L00(BitMask_06)))|ValSft_L00((val)&BitMask_06)))

#define EXD_PGN_ON_Br			(ValSft_R08(_rd32(_REG_BASE_+(0x078c<<2)))&BitMask_01)
#define EXD_PGN_ON_Bw(val)		_wr32(_REG_BASE_+(0x078c<<2),(UINT)((_rd32(_REG_BASE_+(0x078c<<2))&(~ValSft_L08(BitMask_01)))|ValSft_L08((val)&BitMask_01)))

#define EXD_PGN_YPAT_Br			(ValSft_R04(_rd32(_REG_BASE_+(0x078c<<2)))&BitMask_04)
#define EXD_PGN_YPAT_Bw(val)	_wr32(_REG_BASE_+(0x078c<<2),(UINT)((_rd32(_REG_BASE_+(0x078c<<2))&(~ValSft_L04(BitMask_04)))|ValSft_L04((val)&BitMask_04)))

#define EXD_PGN_CPAT_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x078c<<2)))&BitMask_04)
#define EXD_PGN_CPAT_Bw(val)	_wr32(_REG_BASE_+(0x078c<<2),(UINT)((_rd32(_REG_BASE_+(0x078c<<2))&(~ValSft_L00(BitMask_04)))|ValSft_L00((val)&BitMask_04)))

#define EXD_Y_UPPER_Br			(ValSft_R20(_rd32(_REG_BASE_+(0x078d<<2)))&BitMask_10)
#define EXD_Y_UPPER_Bw(val)		_wr32(_REG_BASE_+(0x078d<<2),(UINT)((_rd32(_REG_BASE_+(0x078d<<2))&(~ValSft_L20(BitMask_10)))|ValSft_L20((val)&BitMask_10)))

#define EXD_Y_LOWER_Br			(ValSft_R10(_rd32(_REG_BASE_+(0x078d<<2)))&BitMask_10)
#define EXD_Y_LOWER_Bw(val)		_wr32(_REG_BASE_+(0x078d<<2),(UINT)((_rd32(_REG_BASE_+(0x078d<<2))&(~ValSft_L10(BitMask_10)))|ValSft_L10((val)&BitMask_10)))

#define EXD_C_UPPER_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x078d<<2)))&BitMask_10)
#define EXD_C_UPPER_Bw(val)		_wr32(_REG_BASE_+(0x078d<<2),(UINT)((_rd32(_REG_BASE_+(0x078d<<2))&(~ValSft_L00(BitMask_10)))|ValSft_L00((val)&BitMask_10)))

#define EXD_C_LOWER_Br			(ValSft_R20(_rd32(_REG_BASE_+(0x078e<<2)))&BitMask_10)
#define EXD_C_LOWER_Bw(val)		_wr32(_REG_BASE_+(0x078e<<2),(UINT)((_rd32(_REG_BASE_+(0x078e<<2))&(~ValSft_L20(BitMask_10)))|ValSft_L20((val)&BitMask_10)))

#define EXD_VINT_EN_Br			(ValSft_R14(_rd32(_REG_BASE_+(0x078e<<2)))&BitMask_01)
#define EXD_VINT_EN_Bw(val)		_wr32(_REG_BASE_+(0x078e<<2),(UINT)((_rd32(_REG_BASE_+(0x078e<<2))&(~ValSft_L14(BitMask_01)))|ValSft_L14((val)&BitMask_01)))

#define EXD_VINT_LN_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x078e<<2)))&BitMask_14)
#define EXD_VINT_LN_Bw(val)		_wr32(_REG_BASE_+(0x078e<<2),(UINT)((_rd32(_REG_BASE_+(0x078e<<2))&(~ValSft_L00(BitMask_14)))|ValSft_L00((val)&BitMask_14)))

#define EXD_OSD_ON_Br			(ValSft_R31(_rd32(_REG_BASE_+(0x078f<<2)))&BitMask_01)
#define EXD_OSD_ON_Bw(val)		_wr32(_REG_BASE_+(0x078f<<2),(UINT)((_rd32(_REG_BASE_+(0x078f<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define TEST_ADCr				(ValSft_R31(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_01)
#define TEST_ADCw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L31(BitMask_01)))|ValSft_L31((val)&BitMask_01)))

#define TEST_DACr				(ValSft_R30(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_01)
#define TEST_DACw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L30(BitMask_01)))|ValSft_L30((val)&BitMask_01)))

#define TEST_DO10_Ar			(ValSft_R27(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_03)
#define TEST_DO10_Aw(val)		_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L27(BitMask_03)))|ValSft_L27((val)&BitMask_03)))

#define TEST_DO10_Br			(ValSft_R24(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_03)
#define TEST_DO10_Bw(val)		_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L24(BitMask_03)))|ValSft_L24((val)&BitMask_03)))

#define TEST_DO8r				(ValSft_R20(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_04)
#define TEST_DO8w(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L20(BitMask_04)))|ValSft_L20((val)&BitMask_04)))

#define TEST_MTXr				(ValSft_R19(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_01)
#define TEST_MTXw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L19(BitMask_01)))|ValSft_L19((val)&BitMask_01)))

#define TEST_SDIAr				(ValSft_R18(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_01)
#define TEST_SDIAw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L18(BitMask_01)))|ValSft_L18((val)&BitMask_01)))

#define TEST_SDIBr				(ValSft_R17(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_01)
#define TEST_SDIBw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L17(BitMask_01)))|ValSft_L17((val)&BitMask_01)))

#define TEST_MPLLr				(ValSft_R16(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_01)
#define TEST_MPLLw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L16(BitMask_01)))|ValSft_L16((val)&BitMask_01)))

#define TEST_MFUNr				(ValSft_R15(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_01)
#define TEST_MFUNw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L15(BitMask_01)))|ValSft_L15((val)&BitMask_01)))

#define TEST_DPLLr				(ValSft_R14(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_01)
#define TEST_DPLLw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L14(BitMask_01)))|ValSft_L14((val)&BitMask_01)))

#define TEST_SPLLr				(ValSft_R13(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_01)
#define TEST_SPLLw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L13(BitMask_01)))|ValSft_L13((val)&BitMask_01)))

#define TEST_BPLLr				(ValSft_R11(_rd32(_REG_BASE_+(0x0000<<2)))&BitMask_01)
#define TEST_BPLLw(val)			_wr32(_REG_BASE_+(0x0000<<2),(UINT)((_rd32(_REG_BASE_+(0x0000<<2))&(~ValSft_L11(BitMask_01)))|ValSft_L11((val)&BitMask_01)))

#define EXRISC_IRQr				(ValSft_R00(_rd32(_REG_BASE_+(0x0800<<2)))&BitMask_11)
#define RDES_HCNT_Lr			(ValSft_R16(_rd32(_REG_BASE_+(0x0801<<2)))&BitMask_16)
#define RDES_VCNT_Lr			(ValSft_R00(_rd32(_REG_BASE_+(0x0801<<2)))&BitMask_16)
#define RDES_HCNT_S1r			(ValSft_R16(_rd32(_REG_BASE_+(0x0802<<2)))&BitMask_16)
#define RDES_VCNT_S1r			(ValSft_R00(_rd32(_REG_BASE_+(0x0802<<2)))&BitMask_16)
#define RDES_CKCHKr				(ValSft_R16(_rd32(_REG_BASE_+(0x0804<<2)))&BitMask_08)
#define RDES_FSETLr				(ValSft_R12(_rd32(_REG_BASE_+(0x0804<<2)))&BitMask_01)
#define RDES_FSET1r				(ValSft_R11(_rd32(_REG_BASE_+(0x0804<<2)))&BitMask_01)
#define LWDR_MODEr				(ValSft_R08(_rd32(_REG_BASE_+(0x0804<<2)))&BitMask_02)
#define LWDR_LONG2S1r			(ValSft_R16(_rd32(_REG_BASE_+(0x0805<<2)))&BitMask_16)
#define HCNTL_SVr				(ValSft_R16(_rd32(_REG_BASE_+(0x0806<<2)))&BitMask_16)
#define VCNTL_SVr				(ValSft_R00(_rd32(_REG_BASE_+(0x0806<<2)))&BitMask_16)
#define RDES_READ0r				(ValSft_R16(_rd32(_REG_BASE_+(0x0807<<2)))&BitMask_16)
#define RDES_READ1r				(ValSft_R00(_rd32(_REG_BASE_+(0x0807<<2)))&BitMask_16)
#define RDES_READ2r				(ValSft_R16(_rd32(_REG_BASE_+(0x0808<<2)))&BitMask_16)
#define RDES_READ3r				(ValSft_R00(_rd32(_REG_BASE_+(0x0808<<2)))&BitMask_16)
#define RDES_READ4r				(ValSft_R16(_rd32(_REG_BASE_+(0x0809<<2)))&BitMask_16)
#define RDES_READ5r				(ValSft_R00(_rd32(_REG_BASE_+(0x0809<<2)))&BitMask_16)
#define RDES_READ6r				(ValSft_R16(_rd32(_REG_BASE_+(0x080a<<2)))&BitMask_16)
#define RDES_READ7r				(ValSft_R00(_rd32(_REG_BASE_+(0x080a<<2)))&BitMask_16)
#define RDES_SE3r				(ValSft_R24(_rd32(_REG_BASE_+(0x080c<<2)))&BitMask_08)
#define RDES_SE2r				(ValSft_R16(_rd32(_REG_BASE_+(0x080c<<2)))&BitMask_08)
#define RDES_SE1r				(ValSft_R08(_rd32(_REG_BASE_+(0x080c<<2)))&BitMask_08)
#define RDES_SE0r				(ValSft_R00(_rd32(_REG_BASE_+(0x080c<<2)))&BitMask_08)
#define DS_RECNTr				(ValSft_R16(_rd32(_REG_BASE_+(0x080d<<2)))&BitMask_16)
#define DS_WECNTr				(ValSft_R00(_rd32(_REG_BASE_+(0x080d<<2)))&BitMask_16)
#define RDES_WCRr				(ValSft_R00(_rd32(_REG_BASE_+(0x0810<<2)))&BitMask_16)
#define RDES_FN1r				(ValSft_R16(_rd32(_REG_BASE_+(0x0811<<2)))&BitMask_16)
#define RDES_FN2r				(ValSft_R00(_rd32(_REG_BASE_+(0x0811<<2)))&BitMask_16)
#define RDES_LN1r				(ValSft_R00(_rd32(_REG_BASE_+(0x0812<<2)))&BitMask_16)
#define RDES_LN2r				(ValSft_R16(_rd32(_REG_BASE_+(0x0813<<2)))&BitMask_16)
#define RDES_ECC1r				(ValSft_R16(_rd32(_REG_BASE_+(0x0814<<2)))&BitMask_08)
#define RDES_ECC2r				(ValSft_R08(_rd32(_REG_BASE_+(0x0814<<2)))&BitMask_08)
#define MIPI_FSCNT1r			(ValSft_R16(_rd32(_REG_BASE_+(0x0815<<2)))&BitMask_10)
#define MIPI_FSCNT2r			(ValSft_R00(_rd32(_REG_BASE_+(0x0815<<2)))&BitMask_10)
#define MIPI_FECNT1r			(ValSft_R16(_rd32(_REG_BASE_+(0x0816<<2)))&BitMask_10)
#define MIPI_FECNT2r			(ValSft_R00(_rd32(_REG_BASE_+(0x0816<<2)))&BitMask_10)
#define MIPI_LSCNT1r			(ValSft_R16(_rd32(_REG_BASE_+(0x0817<<2)))&BitMask_10)
#define MIPI_LSCNT2r			(ValSft_R00(_rd32(_REG_BASE_+(0x0817<<2)))&BitMask_10)
#define MIPI_LECNT1r			(ValSft_R16(_rd32(_REG_BASE_+(0x0818<<2)))&BitMask_10)
#define MIPI_LECNT2r			(ValSft_R00(_rd32(_REG_BASE_+(0x0818<<2)))&BitMask_10)
#define MIPI_CRCRr				(ValSft_R16(_rd32(_REG_BASE_+(0x0819<<2)))&BitMask_16)
#define MIPI_CRCCr				(ValSft_R00(_rd32(_REG_BASE_+(0x0819<<2)))&BitMask_16)
#define MIPI_CRCEr				(ValSft_R00(_rd32(_REG_BASE_+(0x081a<<2)))&BitMask_32)
#define MIPI_CRCCHr				(ValSft_R16(_rd32(_REG_BASE_+(0x081b<<2)))&BitMask_01)
#define MIPI_CRCLNr				(ValSft_R00(_rd32(_REG_BASE_+(0x081b<<2)))&BitMask_16)
#define MIPI_ECNTr				(ValSft_R00(_rd32(_REG_BASE_+(0x081c<<2)))&BitMask_32)
#define MIPI_EMBDATALr			(ValSft_R00(_rd32(_REG_BASE_+(0x081d<<2)))&BitMask_32)
#define MIPI_EMBDATASr			(ValSft_R00(_rd32(_REG_BASE_+(0x081e<<2)))&BitMask_32)
#define MIPI_ID0_Lr				(ValSft_R16(_rd32(_REG_BASE_+(0x0821<<2)))&BitMask_16)
#define MIPI_ID1_Lr				(ValSft_R00(_rd32(_REG_BASE_+(0x0821<<2)))&BitMask_16)
#define MIPI_ID2_Lr				(ValSft_R16(_rd32(_REG_BASE_+(0x0822<<2)))&BitMask_16)
#define MIPI_ID3_Lr				(ValSft_R00(_rd32(_REG_BASE_+(0x0822<<2)))&BitMask_16)
#define MIPI_ID0_S1r			(ValSft_R16(_rd32(_REG_BASE_+(0x0825<<2)))&BitMask_16)
#define MIPI_ID1_S1r			(ValSft_R00(_rd32(_REG_BASE_+(0x0825<<2)))&BitMask_16)
#define MIPI_ID2_S1r			(ValSft_R16(_rd32(_REG_BASE_+(0x0826<<2)))&BitMask_16)
#define MIPI_ID3_S1r			(ValSft_R00(_rd32(_REG_BASE_+(0x0826<<2)))&BitMask_16)
#define MIPI_SYNC_PRDr			(ValSft_R00(_rd32(_REG_BASE_+(0x0827<<2)))&BitMask_32)
#define MIPI_SYNC_ERRr			(ValSft_R00(_rd32(_REG_BASE_+(0x0828<<2)))&BitMask_32)
#define MIPI_SYNC_EDAr			(ValSft_R00(_rd32(_REG_BASE_+(0x0829<<2)))&BitMask_32)
#define RSYNC_UPL_INTr			(ValSft_R03(_rd32(_REG_BASE_+(0x082a<<2)))&BitMask_01)
#define RSYNC_UP1_INTr			(ValSft_R02(_rd32(_REG_BASE_+(0x082a<<2)))&BitMask_01)
#define OSYNC_UP_INTr			(ValSft_R01(_rd32(_REG_BASE_+(0x082a<<2)))&BitMask_01)
#define ESYNC_UP_INTr			(ValSft_R00(_rd32(_REG_BASE_+(0x082a<<2)))&BitMask_01)
#define RDES_VPHASELr			(ValSft_R00(_rd32(_REG_BASE_+(0x082b<<2)))&BitMask_32)
#define RDES_VPHASE1r			(ValSft_R00(_rd32(_REG_BASE_+(0x082c<<2)))&BitMask_32)
#define OSYNC_VPHASEr			(ValSft_R00(_rd32(_REG_BASE_+(0x082d<<2)))&BitMask_32)
#define ESYNC_VPHASEr			(ValSft_R00(_rd32(_REG_BASE_+(0x082e<<2)))&BitMask_32)
#define AE1_SUM0_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0830<<2)))&BitMask_32)
#define AE1_SUM1_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0831<<2)))&BitMask_32)
#define AE1_SUM2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0832<<2)))&BitMask_32)
#define AE2_SUM0_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0833<<2)))&BitMask_32)
#define AE2_SUM1_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0834<<2)))&BitMask_32)
#define AE2_SUM2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0835<<2)))&BitMask_32)
#define AE3_SUM0_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0836<<2)))&BitMask_32)
#define AE3_SUM1_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0837<<2)))&BitMask_32)
#define AE3_SUM2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0838<<2)))&BitMask_32)
#define AE4_SUM0_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0839<<2)))&BitMask_32)
#define AE4_SUM1_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x083a<<2)))&BitMask_32)
#define AE4_SUM2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x083b<<2)))&BitMask_32)
#define AE5_SUM0_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x083c<<2)))&BitMask_32)
#define AE5_SUM1_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x083d<<2)))&BitMask_32)
#define AE5_SUM2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x083e<<2)))&BitMask_32)
#define AE6_SUM0_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x083f<<2)))&BitMask_32)
#define AE6_SUM1_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0841<<2)))&BitMask_32)
#define AE6_SUM2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0842<<2)))&BitMask_32)
#define AE1_CLCNT_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0843<<2)))&BitMask_22)
#define AE2_CLCNT_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0844<<2)))&BitMask_22)
#define AE3_CLCNT_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0845<<2)))&BitMask_22)
#define AE4_CLCNT_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0846<<2)))&BitMask_22)
#define AE5_CLCNT_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0847<<2)))&BitMask_22)
#define AE6_CLCNT_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0848<<2)))&BitMask_22)
#define AE1_SLCNT_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0849<<2)))&BitMask_22)
#define AE2_SLCNT_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x084a<<2)))&BitMask_22)
#define AE3_SLCNT_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x084b<<2)))&BitMask_22)
#define AE4_SLCNT_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x084c<<2)))&BitMask_22)
#define AE5_SLCNT_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x084d<<2)))&BitMask_22)
#define AE6_SLCNT_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x084e<<2)))&BitMask_22)
#define HISTO0_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0850<<2)))&BitMask_22)
#define HISTO1_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0851<<2)))&BitMask_22)
#define HISTO2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0852<<2)))&BitMask_22)
#define HISTO3_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0853<<2)))&BitMask_22)
#define HISTO4_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0854<<2)))&BitMask_22)
#define HISTO5_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0855<<2)))&BitMask_22)
#define HISTO6_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0856<<2)))&BitMask_22)
#define HISTO7_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0857<<2)))&BitMask_22)
#define HISTO8_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0858<<2)))&BitMask_22)
#define HISTO9_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0859<<2)))&BitMask_22)
#define HISTO10_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x085a<<2)))&BitMask_22)
#define HISTO11_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x085b<<2)))&BitMask_22)
#define HISTO12_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x085c<<2)))&BitMask_22)
#define HISTO13_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x085d<<2)))&BitMask_22)
#define HISTO14_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x085e<<2)))&BitMask_22)
#define HISTO15_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x085f<<2)))&BitMask_22)
#define HISTO0_W2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0860<<2)))&BitMask_22)
#define HISTO1_W2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0861<<2)))&BitMask_22)
#define HISTO2_W2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0862<<2)))&BitMask_22)
#define HISTO3_W2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0863<<2)))&BitMask_22)
#define HISTO4_W2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0864<<2)))&BitMask_22)
#define HISTO5_W2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0865<<2)))&BitMask_22)
#define HISTO6_W2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0866<<2)))&BitMask_22)
#define HISTO7_W2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0867<<2)))&BitMask_22)
#define HISTO8_W2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0868<<2)))&BitMask_22)
#define HISTO9_W2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0869<<2)))&BitMask_22)
#define HISTO10_W2_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x086a<<2)))&BitMask_22)
#define HISTO11_W2_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x086b<<2)))&BitMask_22)
#define HISTO12_W2_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x086c<<2)))&BitMask_22)
#define HISTO13_W2_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x086d<<2)))&BitMask_22)
#define HISTO14_W2_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x086e<<2)))&BitMask_22)
#define HISTO15_W2_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x086f<<2)))&BitMask_22)
#define AF1_SUM1_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0870<<2)))&BitMask_32)
#define AF1_SUM2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0871<<2)))&BitMask_32)
#define AF1_LPSUM1_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x0874<<2)))&BitMask_22)
#define AF1_LPSUM2_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x0875<<2)))&BitMask_22)
#define AF1_CLP_SUM1_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x0878<<2)))&BitMask_32)
#define AF1_CLP_SUM2_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x0879<<2)))&BitMask_32)
#define AF1_YSUM1_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x087c<<2)))&BitMask_32)
#define AF1_YSUM2_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x087d<<2)))&BitMask_32)
#define AF1_YLPSUM1_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x0881<<2)))&BitMask_22)
#define AF1_YLPSUM2_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x0882<<2)))&BitMask_22)
#define AF1_CLCNT_LOCKr			(ValSft_R00(_rd32(_REG_BASE_+(0x0885<<2)))&BitMask_22)
#define AWBL_CCR_SUM_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x0889<<2)))&BitMask_32)
#define AWBL_CCG_SUM_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x088a<<2)))&BitMask_32)
#define AWBL_CCB_SUM_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x088b<<2)))&BitMask_32)
#define AWBL_CCT_SUM_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x088c<<2)))&BitMask_22)
#define AWBL_CY_SUM_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x088d<<2)))&BitMask_32)
#define AWBL_CBDB_SUM_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x088e<<2)))&BitMask_32)
#define AWBL_CRDR_SUM_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x088f<<2)))&BitMask_32)
#define AWBL_R_CLCNT_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x0890<<2)))&BitMask_22)
#define AWBL_G_CLCNT_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x0891<<2)))&BitMask_22)
#define AWBL_B_CLCNT_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x0892<<2)))&BitMask_22)
#define AWBL_R_SLCNT_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x0893<<2)))&BitMask_22)
#define AWBL_G_SLCNT_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x0894<<2)))&BitMask_22)
#define AWBL_B_SLCNT_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x0895<<2)))&BitMask_22)
#define AWBL_CCT_SUM0_LOCKr		(ValSft_R16(_rd32(_REG_BASE_+(0x0898<<2)))&BitMask_15)
#define AWBL_CCT_SUM1_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x0898<<2)))&BitMask_15)
#define AWBL_CCT_SUM2_LOCKr		(ValSft_R16(_rd32(_REG_BASE_+(0x0899<<2)))&BitMask_15)
#define AWBL_CCT_SUM3_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x0899<<2)))&BitMask_15)
#define AWBL_CCT_SUM4_LOCKr		(ValSft_R16(_rd32(_REG_BASE_+(0x089a<<2)))&BitMask_15)
#define AWBL_CCT_SUM5_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x089a<<2)))&BitMask_15)
#define AWBL_CCT_SUM6_LOCKr		(ValSft_R16(_rd32(_REG_BASE_+(0x089b<<2)))&BitMask_15)
#define AWBL_CCT_SUM7_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x089b<<2)))&BitMask_15)
#define AWBL_DB_SUM0_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x089c<<2)))&BitMask_25)
#define AWBL_DB_SUM1_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x089d<<2)))&BitMask_25)
#define AWBL_DB_SUM2_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x089e<<2)))&BitMask_25)
#define AWBL_DB_SUM3_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x089f<<2)))&BitMask_25)
#define AWBL_DB_SUM4_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x08a0<<2)))&BitMask_25)
#define AWBL_DB_SUM5_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x08a1<<2)))&BitMask_25)
#define AWBL_DB_SUM6_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x08a2<<2)))&BitMask_25)
#define AWBL_DB_SUM7_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x08a3<<2)))&BitMask_25)
#define AWBL_DR_SUM0_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x08a4<<2)))&BitMask_25)
#define AWBL_DR_SUM1_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x08a5<<2)))&BitMask_25)
#define AWBL_DR_SUM2_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x08a6<<2)))&BitMask_25)
#define AWBL_DR_SUM3_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x08a7<<2)))&BitMask_25)
#define AWBL_DR_SUM4_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x08a8<<2)))&BitMask_25)
#define AWBL_DR_SUM5_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x08a9<<2)))&BitMask_25)
#define AWBL_DR_SUM6_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x08aa<<2)))&BitMask_25)
#define AWBL_DR_SUM7_LOCKr		(ValSft_R00(_rd32(_REG_BASE_+(0x08ab<<2)))&BitMask_25)
#define ADC_ERRCNTr				(ValSft_R28(_rd32(_REG_BASE_+(0x08b0<<2)))&BitMask_04)
#define ADC_RD_FLAGr			(ValSft_R26(_rd32(_REG_BASE_+(0x08b0<<2)))&BitMask_01)
#define ADC_RDATA1r				(ValSft_R16(_rd32(_REG_BASE_+(0x08b1<<2)))&BitMask_10)
#define ADC_RDATA0r				(ValSft_R00(_rd32(_REG_BASE_+(0x08b1<<2)))&BitMask_10)
#define SHD_MAXr				(ValSft_R00(_rd32(_REG_BASE_+(0x08b3<<2)))&BitMask_10)
#define GPI_Rr					(ValSft_R00(_rd32(_REG_BASE_+(0x08b6<<2)))&BitMask_20)
#define PWL_PCNTr				(ValSft_R00(_rd32(_REG_BASE_+(0x08b8<<2)))&BitMask_32)
#define WDR_LBUFr				(ValSft_R00(_rd32(_REG_BASE_+(0x08b9<<2)))&BitMask_14)
#define WDR_BLDCNTr				(ValSft_R00(_rd32(_REG_BASE_+(0x08ba<<2)))&BitMask_32)
#define CRX00r					(ValSft_R00(_rd32(_REG_BASE_+(0x0904<<2)))&BitMask_32)
#define CRX01r					(ValSft_R00(_rd32(_REG_BASE_+(0x0905<<2)))&BitMask_32)
#define CRX02r					(ValSft_R00(_rd32(_REG_BASE_+(0x0906<<2)))&BitMask_32)
#define CRX03r					(ValSft_R00(_rd32(_REG_BASE_+(0x0907<<2)))&BitMask_32)
#define CRX04r					(ValSft_R00(_rd32(_REG_BASE_+(0x0908<<2)))&BitMask_32)
#define CRX05r					(ValSft_R00(_rd32(_REG_BASE_+(0x0909<<2)))&BitMask_32)
#define CRX06r					(ValSft_R00(_rd32(_REG_BASE_+(0x090a<<2)))&BitMask_32)
#define CRX07r					(ValSft_R00(_rd32(_REG_BASE_+(0x090b<<2)))&BitMask_32)
#define CRX_AST_DETr			(ValSft_R00(_rd32(_REG_BASE_+(0x090c<<2)))&BitMask_10)
#define CXAL_WOP_Rr				(ValSft_R31(_rd32(_REG_BASE_+(0x090d<<2)))&BitMask_01)
#define CRX_BITMINr				(ValSft_R00(_rd32(_REG_BASE_+(0x090d<<2)))&BitMask_10)
#define CRX_PRE_READr			(ValSft_R24(_rd32(_REG_BASE_+(0x090e<<2)))&BitMask_08)
#define CRX_BITRATE_NEWr		(ValSft_R00(_rd32(_REG_BASE_+(0x090e<<2)))&BitMask_14)
#define CRX_BITRATE_SELr		(ValSft_R00(_rd32(_REG_BASE_+(0x090f<<2)))&BitMask_14)
#define TX_RDY_ESCr				(ValSft_R17(_rd32(_REG_BASE_+(0x0911<<2)))&BitMask_04)
#define MTX_STOP_STDr			(ValSft_R12(_rd32(_REG_BASE_+(0x0911<<2)))&BitMask_04)
#define MTX_STOP_STCr			(ValSft_R08(_rd32(_REG_BASE_+(0x0911<<2)))&BitMask_01)
#define MTX_ACT_NOT_Dr			(ValSft_R04(_rd32(_REG_BASE_+(0x0911<<2)))&BitMask_04)
#define MTX_ACT_NOT_Cr			(ValSft_R00(_rd32(_REG_BASE_+(0x0911<<2)))&BitMask_01)
#define MTX_REQ_Dr				(ValSft_R04(_rd32(_REG_BASE_+(0x0912<<2)))&BitMask_04)
#define MTX_RDY_Dr				(ValSft_R00(_rd32(_REG_BASE_+(0x0912<<2)))&BitMask_04)
#define MTX_DATA_HSr			(ValSft_R00(_rd32(_REG_BASE_+(0x0913<<2)))&BitMask_32)
#define MTX_HLOCKB_CNTr			(ValSft_R16(_rd32(_REG_BASE_+(0x0914<<2)))&BitMask_13)
#define MTX_HLOCKO_CNTr			(ValSft_R00(_rd32(_REG_BASE_+(0x0914<<2)))&BitMask_13)
#define MTX_VLOCKB_CNTr			(ValSft_R16(_rd32(_REG_BASE_+(0x0915<<2)))&BitMask_13)
#define MTX_VLOCKO_CNTr			(ValSft_R00(_rd32(_REG_BASE_+(0x0915<<2)))&BitMask_13)
#define MTX_CRC_DATAr			(ValSft_R16(_rd32(_REG_BASE_+(0x0916<<2)))&BitMask_16)
#define MTX_ECC_DATAr			(ValSft_R00(_rd32(_REG_BASE_+(0x0916<<2)))&BitMask_08)
#define FLDOr					(ValSft_R00(_rd32(_REG_BASE_+(0x0929<<2)))&BitMask_01)
#define EX_MRG_DIF_CNT0r		(ValSft_R24(_rd32(_REG_BASE_+(0x0930<<2)))&BitMask_08)
#define EX_MRG_DIF_CNT1r		(ValSft_R16(_rd32(_REG_BASE_+(0x0930<<2)))&BitMask_08)
#define EX_SPLIT_INFO_Rr		(ValSft_R14(_rd32(_REG_BASE_+(0x0930<<2)))&BitMask_02)
#define DSE_MEM_DEPTH_R_Ar		(ValSft_R16(_rd32(_REG_BASE_+(0x0931<<2)))&BitMask_12)
#define DSE_MEM_AFULL_R_Ar		(ValSft_R15(_rd32(_REG_BASE_+(0x0931<<2)))&BitMask_01)
#define DSE_MEM_FULL_R_Ar		(ValSft_R14(_rd32(_REG_BASE_+(0x0931<<2)))&BitMask_01)
#define DSD_8B10B_ECNT_Ar		(ValSft_R00(_rd32(_REG_BASE_+(0x0932<<2)))&BitMask_32)
#define DSD_CRC_ECNT_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x0933<<2)))&BitMask_32)
#define DSD_ANC_DO00_R_Ar		(ValSft_R12(_rd32(_REG_BASE_+(0x0935<<2)))&BitMask_10)
#define DSD_ANC_DO01_R_Ar		(ValSft_R00(_rd32(_REG_BASE_+(0x0935<<2)))&BitMask_10)
#define DSD_ANC_DO02_R_Ar		(ValSft_R12(_rd32(_REG_BASE_+(0x0936<<2)))&BitMask_10)
#define DSD_ANC_DO03_R_Ar		(ValSft_R00(_rd32(_REG_BASE_+(0x0936<<2)))&BitMask_10)
#define DSD_ANC_DO04_R_Ar		(ValSft_R12(_rd32(_REG_BASE_+(0x0937<<2)))&BitMask_10)
#define DSD_ANC_DO05_R_Ar		(ValSft_R00(_rd32(_REG_BASE_+(0x0937<<2)))&BitMask_10)
#define DSD_ANC_DO06_R_Ar		(ValSft_R12(_rd32(_REG_BASE_+(0x0938<<2)))&BitMask_10)
#define DSD_ANC_DO07_R_Ar		(ValSft_R00(_rd32(_REG_BASE_+(0x0938<<2)))&BitMask_10)
#define DSD_ANC_DO08_R_Ar		(ValSft_R12(_rd32(_REG_BASE_+(0x0939<<2)))&BitMask_10)
#define DSD_ANC_DO09_R_Ar		(ValSft_R00(_rd32(_REG_BASE_+(0x0939<<2)))&BitMask_10)
#define DSD_ANC_DO10_R_Ar		(ValSft_R12(_rd32(_REG_BASE_+(0x093a<<2)))&BitMask_10)
#define DSD_ANC_DO11_R_Ar		(ValSft_R00(_rd32(_REG_BASE_+(0x093a<<2)))&BitMask_10)
#define DSD_ANC_DO12_R_Ar		(ValSft_R12(_rd32(_REG_BASE_+(0x093b<<2)))&BitMask_10)
#define DSD_ANC_DO13_R_Ar		(ValSft_R00(_rd32(_REG_BASE_+(0x093b<<2)))&BitMask_10)
#define DSD_ANC_DO14_R_Ar		(ValSft_R12(_rd32(_REG_BASE_+(0x093c<<2)))&BitMask_10)
#define DSD_ANC_DO15_R_Ar		(ValSft_R00(_rd32(_REG_BASE_+(0x093c<<2)))&BitMask_10)
#define DSD_ANC_LOSS_Ar			(ValSft_R31(_rd32(_REG_BASE_+(0x093d<<2)))&BitMask_01)
#define DSD_AUD0_LOSS_Ar		(ValSft_R30(_rd32(_REG_BASE_+(0x093d<<2)))&BitMask_01)
#define DSD_AUD1_LOSS_Ar		(ValSft_R29(_rd32(_REG_BASE_+(0x093d<<2)))&BitMask_01)
#define DSD_SLCK_FREQ_R_Ar		(ValSft_R24(_rd32(_REG_BASE_+(0x093d<<2)))&BitMask_02)
#define EXE_HTC_R_Ar			(ValSft_R16(_rd32(_REG_BASE_+(0x0941<<2)))&BitMask_15)
#define EXE_HW_R_Ar				(ValSft_R00(_rd32(_REG_BASE_+(0x0941<<2)))&BitMask_15)
#define EXE_VTC_R_Ar			(ValSft_R16(_rd32(_REG_BASE_+(0x0942<<2)))&BitMask_14)
#define EXE_VSP_R_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x0942<<2)))&BitMask_14)
#define EXE_VW_R_Ar				(ValSft_R16(_rd32(_REG_BASE_+(0x0943<<2)))&BitMask_14)
#define EXE_QUAL_HST_Ar			(ValSft_R08(_rd32(_REG_BASE_+(0x0943<<2)))&BitMask_05)
#define EXE_QUAL_LST_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x0943<<2)))&BitMask_05)
#define EXE_FSIZE_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x0944<<2)))&BitMask_28)
#define EXD_EXSDI_VER_R_Ar		(ValSft_R28(_rd32(_REG_BASE_+(0x0948<<2)))&BitMask_04)
#define EXD_INTERLACE_R_Ar		(ValSft_R00(_rd32(_REG_BASE_+(0x0948<<2)))&BitMask_01)
#define EXD_HTC_R_Ar			(ValSft_R16(_rd32(_REG_BASE_+(0x0949<<2)))&BitMask_15)
#define EXD_HW_R_Ar				(ValSft_R00(_rd32(_REG_BASE_+(0x0949<<2)))&BitMask_15)
#define EXD_VTC_R_Ar			(ValSft_R16(_rd32(_REG_BASE_+(0x094a<<2)))&BitMask_14)
#define EXD_VSP_R_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x094a<<2)))&BitMask_14)
#define EXD_VW_ORG_R_Ar			(ValSft_R16(_rd32(_REG_BASE_+(0x094b<<2)))&BitMask_14)
#define EXD_VW_FIX_R_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x094b<<2)))&BitMask_14)
#define EXD_QUALITY_R_Ar		(ValSft_R24(_rd32(_REG_BASE_+(0x094c<<2)))&BitMask_05)
#define EXD_FSIZE_R_Ar			(ValSft_R00(_rd32(_REG_BASE_+(0x094d<<2)))&BitMask_28)
#define EXD_DEPTH_R_Ar			(ValSft_R16(_rd32(_REG_BASE_+(0x094e<<2)))&BitMask_12)
#define EXD_OVRFLOW_R_Ar		(ValSft_R15(_rd32(_REG_BASE_+(0x094e<<2)))&BitMask_01)
#define EXD_UDRFLOW_R_Ar		(ValSft_R14(_rd32(_REG_BASE_+(0x094e<<2)))&BitMask_01)
#define EXD_VOFFSET_R_Ar		(ValSft_R08(_rd32(_REG_BASE_+(0x094e<<2)))&BitMask_06)
#define DSE_MEM_DEPTH_R_Br		(ValSft_R16(_rd32(_REG_BASE_+(0x0951<<2)))&BitMask_12)
#define DSE_MEM_AFULL_R_Br		(ValSft_R15(_rd32(_REG_BASE_+(0x0951<<2)))&BitMask_01)
#define DSE_MEM_FULL_R_Br		(ValSft_R14(_rd32(_REG_BASE_+(0x0951<<2)))&BitMask_01)
#define DSD_8B10B_ECNT_Br		(ValSft_R00(_rd32(_REG_BASE_+(0x0952<<2)))&BitMask_32)
#define DSD_CRC_ECNT_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x0953<<2)))&BitMask_32)
#define DSD_ANC_DO00_R_Br		(ValSft_R12(_rd32(_REG_BASE_+(0x0955<<2)))&BitMask_10)
#define DSD_ANC_DO01_R_Br		(ValSft_R00(_rd32(_REG_BASE_+(0x0955<<2)))&BitMask_10)
#define DSD_ANC_DO02_R_Br		(ValSft_R12(_rd32(_REG_BASE_+(0x0956<<2)))&BitMask_10)
#define DSD_ANC_DO03_R_Br		(ValSft_R00(_rd32(_REG_BASE_+(0x0956<<2)))&BitMask_10)
#define DSD_ANC_DO04_R_Br		(ValSft_R12(_rd32(_REG_BASE_+(0x0957<<2)))&BitMask_10)
#define DSD_ANC_DO05_R_Br		(ValSft_R00(_rd32(_REG_BASE_+(0x0957<<2)))&BitMask_10)
#define DSD_ANC_DO06_R_Br		(ValSft_R12(_rd32(_REG_BASE_+(0x0958<<2)))&BitMask_10)
#define DSD_ANC_DO07_R_Br		(ValSft_R00(_rd32(_REG_BASE_+(0x0958<<2)))&BitMask_10)
#define DSD_ANC_DO08_R_Br		(ValSft_R12(_rd32(_REG_BASE_+(0x0959<<2)))&BitMask_10)
#define DSD_ANC_DO09_R_Br		(ValSft_R00(_rd32(_REG_BASE_+(0x0959<<2)))&BitMask_10)
#define DSD_ANC_DO10_R_Br		(ValSft_R12(_rd32(_REG_BASE_+(0x095a<<2)))&BitMask_10)
#define DSD_ANC_DO11_R_Br		(ValSft_R00(_rd32(_REG_BASE_+(0x095a<<2)))&BitMask_10)
#define DSD_ANC_DO12_R_Br		(ValSft_R12(_rd32(_REG_BASE_+(0x095b<<2)))&BitMask_10)
#define DSD_ANC_DO13_R_Br		(ValSft_R00(_rd32(_REG_BASE_+(0x095b<<2)))&BitMask_10)
#define DSD_ANC_DO14_R_Br		(ValSft_R12(_rd32(_REG_BASE_+(0x095c<<2)))&BitMask_10)
#define DSD_ANC_DO15_R_Br		(ValSft_R00(_rd32(_REG_BASE_+(0x095c<<2)))&BitMask_10)
#define DSD_ANC_LOSS_Br			(ValSft_R31(_rd32(_REG_BASE_+(0x095d<<2)))&BitMask_01)
#define DSD_AUD0_LOSS_Br		(ValSft_R30(_rd32(_REG_BASE_+(0x095d<<2)))&BitMask_01)
#define DSD_AUD1_LOSS_Br		(ValSft_R29(_rd32(_REG_BASE_+(0x095d<<2)))&BitMask_01)
#define DSD_SLCK_FREQ_R_Br		(ValSft_R24(_rd32(_REG_BASE_+(0x095d<<2)))&BitMask_02)
#define EXE_HTC_R_Br			(ValSft_R16(_rd32(_REG_BASE_+(0x0961<<2)))&BitMask_15)
#define EXE_HW_R_Br				(ValSft_R00(_rd32(_REG_BASE_+(0x0961<<2)))&BitMask_15)
#define EXE_VTC_R_Br			(ValSft_R16(_rd32(_REG_BASE_+(0x0962<<2)))&BitMask_14)
#define EXE_VSP_R_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x0962<<2)))&BitMask_14)
#define EXE_VW_R_Br				(ValSft_R16(_rd32(_REG_BASE_+(0x0963<<2)))&BitMask_14)
#define EXE_QUAL_HST_Br			(ValSft_R08(_rd32(_REG_BASE_+(0x0963<<2)))&BitMask_05)
#define EXE_QUAL_LST_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x0963<<2)))&BitMask_05)
#define EXE_FSIZE_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x0964<<2)))&BitMask_28)
#define EXD_EXSDI_VER_R_Br		(ValSft_R28(_rd32(_REG_BASE_+(0x0968<<2)))&BitMask_04)
#define EXD_INTERLACE_R_Br		(ValSft_R00(_rd32(_REG_BASE_+(0x0968<<2)))&BitMask_01)
#define EXD_HTC_R_Br			(ValSft_R16(_rd32(_REG_BASE_+(0x0969<<2)))&BitMask_15)
#define EXD_HW_R_Br				(ValSft_R00(_rd32(_REG_BASE_+(0x0969<<2)))&BitMask_15)
#define EXD_VTC_R_Br			(ValSft_R16(_rd32(_REG_BASE_+(0x096a<<2)))&BitMask_14)
#define EXD_VSP_R_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x096a<<2)))&BitMask_14)
#define EXD_VW_ORG_R_Br			(ValSft_R16(_rd32(_REG_BASE_+(0x096b<<2)))&BitMask_14)
#define EXD_VW_FIX_R_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x096b<<2)))&BitMask_14)
#define EXD_QUALITY_R_Br		(ValSft_R24(_rd32(_REG_BASE_+(0x096c<<2)))&BitMask_05)
#define EXD_FSIZE_R_Br			(ValSft_R00(_rd32(_REG_BASE_+(0x096d<<2)))&BitMask_28)
#define EXD_DEPTH_R_Br			(ValSft_R16(_rd32(_REG_BASE_+(0x096e<<2)))&BitMask_12)
#define EXD_OVRFLOW_R_Br		(ValSft_R15(_rd32(_REG_BASE_+(0x096e<<2)))&BitMask_01)
#define EXD_UDRFLOW_R_Br		(ValSft_R14(_rd32(_REG_BASE_+(0x096e<<2)))&BitMask_01)
#define EXD_VOFFSET_R_Br		(ValSft_R08(_rd32(_REG_BASE_+(0x096e<<2)))&BitMask_06)
#define EXUD_ERR_CNTr			(ValSft_R00(_rd32(_REG_BASE_+(0x0983<<2)))&BitMask_16)
#define B8UD_ERR_CNTr			(ValSft_R00(_rd32(_REG_BASE_+(0x0984<<2)))&BitMask_32)
#define rB8UD_BYTE_NUMr			(ValSft_R00(_rd32(_REG_BASE_+(0x0985<<2)))&BitMask_07)

