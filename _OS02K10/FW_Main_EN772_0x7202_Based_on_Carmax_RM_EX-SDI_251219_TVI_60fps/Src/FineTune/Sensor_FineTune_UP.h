/* **************************************************************************
 File Name	: 	Sensor_FineTune.h
 Description	:	Image Fine-tune common header file
 Designer		:	Lee, Gyu Hong
 Date		:	22. 04. 19
 Copyright �� DCOD  Co., Ltd. All Rights Reserved.
*************************************************************************** */
#if(model_Sens==SENS_IMX307)
#include "IMX307/Sensor_IMX307_UP.h"
#elif(model_Sens==SENS_IMX462)
#include "IMX462/Sensor_IMX462_UP.h"
#elif(model_Sens==SENS_IMX662)
#include "IMX662/Sensor_IMX662_UP.h"
#elif(model_Sens==SENS_IMX675)
#include "IMX675/Sensor_IMX675_UP.h"
#elif(model_Sens==SENS_OS02K10)
    #if(/*model_MODE_T*/1)
    #include "OS02K10/Sensor_OS02K10_UP_T.h"
    #else
    #include "OS02K10/Sensor_OS02K10_UP.h"
    #endif
#elif(model_Sens==SENS_OS04C10)
#include "OS04C10/Sensor_OS04C10_UP.h"
#endif