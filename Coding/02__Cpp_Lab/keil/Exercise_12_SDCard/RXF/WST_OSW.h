#ifdef WST_H

#ifndef WST_OSW_H
#define WST_OSW_H

/**
 * \brief Operating System Wrapper, which implements and maps RTOS specific functionality.
 * \ingroup runtime
 * \class WST_OSW
 *
 * The RTOS based RXF uses this class to interface functionalities like asynchronous messages,
 * timer managegemt via a timer task, dynamic memory allocation, mutexes and task handling
 * to the specific RTOS used in the RXF product.
 * 
 * Willert Software Tools - Realtime eXecution Framework
 *
 * Email: support@willert.de
 *
 * $Id: WST_OSW.h 32360 2015-05-26 13:05:36Z eroemer $
 * $URL: https://svn.willert.de/V6/trunk/Component/RTOS/CMSIS/Source/C/WST_OSW.h $
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


extern     WST_RTOS_TSK_t	wstTimerTask;


#define WST_RXF_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

void				WST_OSW_MSQ_init(  WST_MSQ* me );

/**
 * \relates WST_MSQ
 * \brief Cleans up the message queue object by freeing memory for the RTOS message queue.
 * \req{RXF-1074}
 */
void				WST_OSW_MSQ_cleanup(  WST_MSQ* me );

void				WST_OSW_MSQ_put( WST_MSQ* me, WST_EVT*  event, WSTBoolean fromISR );
void				WST_OSW_TMM_initTimerTask( void );

/* Called by functions inside WST_MEM.c */
MALLOC_RETURN_TYPE	WST_OSW_MEM_malloc( MALLOC_ARGUMENT_TYPE requestedSize );
void				WST_OSW_MEM_free( MALLOC_RETURN_TYPE memory );

/* Called by functions inside WST_MSQ.c */
void				WST_OSW_MSQ_cancelEvents(WST_MSQ* me, const WST_FSM* destination, WST_EVT_ID_t id);
void				WST_OSW_MSQ_get( WST_MSQ* me, WST_EVT** event);
uint16				WST_OSW_MSQ_getCount( WST_MSQ* me );

/* Called by functions inside WST_TMM.c */
void				WST_OSW_TMM_timerTask( void* arg );

/* Called by functions inside WST_RXF.c */
void				WST_OSW_TMM_delay( uint32 ms );

/* Called by functions inside WST_TSK.c */
void				WST_OSW_TSK_init(WST_TSK* me);
void				WST_OSW_TSK_cleanup(WST_TSK* me);
void				WST_OSW_TSK_start(WST_TSK* me);
void 				WST_OSW_TSK_suspend(WST_TSK* me);
void 				WST_OSW_TSK_resume(WST_TSK* me);
	
/* Called by functions inside WST_MTX.c */
void				WST_OSW_MTX_init( WST_MTX* me );
void				WST_OSW_MTX_cleanup( WST_MTX* me );
void				WST_OSW_MTX_enterCriticalRegion( WST_MTX* me );
void				WST_OSW_MTX_exitCriticalRegion( WST_MTX* me );

/* Called by functions inside WSTMonitor.c */
void				WST_OSW_TSK_userInit(void (*function)(void *), WST_RTOS_PRIORITY_t priority, void *stack, uint16 stacksize, void *taskArgument);


#define WST_RXF_RUNNING_STOP_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

#endif /* of WST_OSW_H */

#endif /* WST_H */
