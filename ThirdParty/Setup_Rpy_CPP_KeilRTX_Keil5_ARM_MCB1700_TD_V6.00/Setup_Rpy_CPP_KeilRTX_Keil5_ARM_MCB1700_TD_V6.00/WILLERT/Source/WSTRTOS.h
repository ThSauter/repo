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
* $Id: WSTRTOS.h 34182 2016-04-08 12:54:34Z eroemer $
* $URL: https://svn.willert.de/V6/trunk/Component/RTOS/KeilRTX/Source/CPP/WSTRTOS.h $
*
**/


/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * Rpy_CPP_KeilRTX_Keil5_ARM_MCB1700_TD_V6.00 (2016-04-22).
 * Copyright (c) 2011, Willert Software Tools GmbH.
 *
 * For detailed information about this product see release info file:
 * C:/Program Files/Willert/Rpy_CPP_KeilRTX_Keil5_ARM_MCB1700_TD_V6.00/ReleaseInfo.txt
 *
 *****************************************************************************/

#include <rtl.h>

class WST_TSK;
extern WST_TSK theMainTask;

#define WST_RTOS_TASK_PRIORITY_LOWEST		  1
#define WST_RTOS_TASK_PRIORITY_LOW			 64
#define WST_RTOS_TASK_PRIORITY_NORMAL		128
#define WST_RTOS_TASK_PRIORITY_HIGH			196
#define WST_RTOS_TASK_PRIORITY_HIGHEST		254
#define WST_TSK_DEFAULT_NAME				"Active"

#define WST_MSQ_WAIT_FOREVER				0xFFFF
#define	WST_RTOS_ERR_NONE					0u


/* RTL Task identifier */
typedef uint16	WST_RTOS_TSK_t;
typedef uint16								WST_RTOS_ERROR_CODE_t; /**< \req{RXF-682} */

/* RTL mailbox identifier, actually a pointer */
typedef OS_ID	WST_RTOS_MSQ_t;

typedef OS_MUT								WST_RTOS_MTX_t;

/* Typedefs to support ActiveStatic Stereotype for active classes with statically allocated stack memory and message queue. */
typedef void*								WST_RTOS_STK_t;
typedef void*								WST_RTOS_MSQ_BUFFER_t;

extern struct WST_TSK mainTask;


#define WST_RXF_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */



extern void 			WSTRTOS_Init( void );
extern void 			WSTRTOS_Cleanup( void );



extern WST_TimeUnit_t			WSTRTOS_getRxfTicks( void );
extern void				WSTRTOS_incrementRxfTicks( void );

#define WST_RXF_RUNNING_END_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */




#endif /* WSTRTOS_H */

