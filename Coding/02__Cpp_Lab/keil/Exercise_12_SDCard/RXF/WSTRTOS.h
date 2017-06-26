#ifndef WSTRTOS_H
#define WSTRTOS_H

/**
* RTOS dependent prototypes and defines.
* This file is used, if no RTOS is part of the product.
*
* Willert Software Tools - RealTime eXecution Framework
*
* Email: support@willert.de
*
* $Id: WSTRTOS.h 33255 2015-12-09 17:49:45Z wvdheiden $
* $URL: https://svn.willert.de/V6/trunk/Component/RTOS/CMSIS/Source/C/WSTRTOS.h $
*
**/


/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01 (2017-02-27).
 * Copyright (c) 2011, Willert Software Tools GmbH.
 *
 * For detailed information about this product see release info file:
 * C:/Program Files/Willert/Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01/ReleaseInfo.txt
 *
 *****************************************************************************/

#include <cmsis_os.h>


#define WST_RTOS_TASK_PRIORITY_LOWEST		osPriorityLow
#define WST_RTOS_TASK_PRIORITY_LOW			osPriorityBelowNormal
#define WST_RTOS_TASK_PRIORITY_NORMAL		osPriorityNormal
#define WST_RTOS_TASK_PRIORITY_HIGH			osPriorityAboveNormal
#define WST_RTOS_TASK_PRIORITY_HIGHEST		osPriorityHigh
#define WST_TSK_MAX_TASK_COUNT				20
#define WST_TSK_DEFAULT_NAME				"Active"
#define WST_MSQ_WAIT_FOREVER				osWaitForever
#define WST_MTX_WAIT_FOREVER				osWaitForever
#define WST_MSQ_NOWAIT						0
#define	WST_RTOS_ERR_NONE					osOK

typedef struct WST_RTOS_CMSIS_TSK_t
{
	osThreadId 		id;
	osThreadDef_t	def;
} WST_RTOS_CMSIS_TSK_t;

typedef struct WST_RTOS_CMSIS_MSQ_t
{
	osMessageQId 		id;
	osMessageQDef_t		def;
} WST_RTOS_CMSIS_MSQ_t;

typedef struct WST_RTOS_CMSIS_MTX_t
{
	osMutexId 		id;
	osMutexDef_t		def;
	uint32_t			mtx_array[4];
} WST_RTOS_CMSIS_MTX_t;

typedef struct WST_RTOS_CMSIS_TMR_t
{
	osTimerId 		id;
	osTimerDef_t		def;
	uint32_t			tmr_array[6];
} WST_RTOS_CMSIS_TMR_t;


/* CMSIS identifiers */
typedef WST_RTOS_CMSIS_TSK_t				WST_RTOS_TSK_t;
typedef WST_RTOS_CMSIS_TMR_t				WST_RTOS_TMR_t;
typedef WST_RTOS_CMSIS_MSQ_t 				WST_RTOS_MSQ_t;
typedef WST_RTOS_CMSIS_MTX_t 				WST_RTOS_MTX_t;
typedef	osPriority									WST_RTOS_PRIORITY_t;
typedef osStatus 										WST_RTOS_ERROR_CODE_t; /**< \req{RXF-682} */



extern WST_TSK theMainTask;


#define WST_RXF_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */


extern void 			WSTRTOS_Init( void );
extern void 			WSTRTOS_Cleanup( void );


extern WST_TimeUnit_t	WSTRTOS_getRxfTicks( void );
extern void				WSTRTOS_incrementRxfTicks( void );

#define WST_RXF_RUNNING_END_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */



#endif /* WSTRTOS_H */

