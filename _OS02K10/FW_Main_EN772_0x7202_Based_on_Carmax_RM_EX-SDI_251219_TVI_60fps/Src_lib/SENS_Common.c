/* **************************************************************************
 File Name	:	EN772_SENS_Common.c
 Description	:	EN772 -Interface matching between ISP and sensor 
 Designer		:	Lee, Gyu Hong
 Date		:	21. 02. 08
 Copyright �� Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "../Src/dev.h"
#include "SENS_Common.h"

BYTE gbMir = 0, gbFlp = 0;
BYTE gbMirFlp = 0;

// -----------------------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------------------
void LibISPtoSENS_Intf(BYTE abRdesType, BYTE abRdesLane, BYTE abRdesBit, WORD awRdesLdoSel, WORD awRdesWC, BYTE abWdrMipiMode, BYTE abWdrOn)
{
	RDES_POw((abRdesLane==_1LANE)?(0x1):(abRdesLane==_2LANE)?(0x3):(0xF));
	RDES_CHw(abRdesLane);
	RDES_SCHw(RDES_POr);
	
	RDES_BITw(abRdesBit);
	RDES_BITAw(abRdesBit);

	SetIsp(0x23, awRdesLdoSel);

	RDES_WCw(awRdesWC);
	
	switch(abRdesType){
		case LVDS : 		// TBD
			break;

		case MIPI : 
				MIPI_SELw(0x1);
				
				// Sync Code
				RDES_SYNC0w(0xB8);
				RDES_SYNC1w(0x00);
				RDES_SYNC2w(0x00);
				HSGO_WIDw(0x0);			//check clock before SOT (0x0 : 8clock)

				//Long Channel 
				RDES_SYNC3_LEFw(0x0);
				// _12BIT or _10BIT
				RDES_SYNC3_LELw((abRdesBit==_16BIT)?(0x2A):(abRdesBit==_12BIT)?(0x2C):(0x2B));
				RDES_SYNC3_LEVw(0x37);											// Sensor ??

				//Short Channel
				if(abWdrOn){					
				RDES_SYNC3_S1Fw((abWdrMipiMode==_MIPI_LI)?(0x0):(RDES_SYNC3_LEFr|0x40));
				RDES_SYNC3_S1Lw((abWdrMipiMode==_MIPI_LI)?(RDES_SYNC3_LELr):(RDES_SYNC3_LELr|0x40));
				RDES_SYNC3_S1Vw((abWdrMipiMode==_MIPI_LI)?(0x37):(RDES_SYNC3_LEVr|0x40));

					//Line Information Mode
					if(abWdrMipiMode==_MIPI_LI){
					RDES_MODEw(0x3);
					MIPI_IDSELw(0x1);
					
					// Reference IMX290,307,327,462 sensor
					MIPI_IDLEw(0x241);
					MIPI_IDS1w(0x252);
					MIPI_IDS2w(0x254);
					MIPI_IDMSKw(0x10);
					}

					// Virtual channel Mode
					else if(abWdrMipiMode==_MIPI_VC){
					RDES_MODEw(0x0);
					MIPI_IDSELw(0x0);
					}	

					// Not Used
					else{
					}
				}

				// Not WDR
				else{
				}
				
				RDES_SYNC3_MSKw(0x0);
				break;
			
		default :
			break;
	}
		
}

