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
 * $Id: WST_OSW.c 33273 2015-12-14 10:02:26Z mspieker $
 * $URL: https://svn.willert.de/V6/trunk/Component/RTOS/CMSIS/Source/C/WST_OSW.c $
 *
**/

/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01 (2017-02-27).
 * Copyright (c) 2013, Willert Software Tools GmbH.
 *
 * For detailed information about this product see release info file:
 * C:/Program Files/Willert/Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01/ReleaseInfo.txt
 *
 *****************************************************************************/




/* WST_OSW for Keil-RTX needs to have access to malloc and protects it with a task lock.
 * So we need to define WST_DO_NOT_MAP_MALLO to stop WST_MEM.h from mapping it and to
 * make sure we do not have a deadly infinite recursion in WST_OSW_MEM_malloc().
 */
#define WST_DO_NOT_MAP_MALLOC


#include "WST.H"

#include <cmsis_os.h>



#define WST_RXF_RUNNING_START_SEC_DATA_NOINIT_UNSPECIFIED_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

WST_RTOS_TSK_t	wstMonitorTask;
WST_RTOS_TMR_t	wstTimerMngr;
WST_MTX*				memoryMutex;
WSTBoolean			mutexInitialized = WSTFALSE;

#define WST_RXF_RUNNING_STOP_SEC_DATA_NOINIT_UNSPECIFIED_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */





#define WST_RXF_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

void WST_OSW_TSK_init(WST_TSK* me)
{
	/* WST_OSW_TSK_start uses osThreadCreate which directly initializes and starts the CMSIS task: no prior initialization required */
}

void WST_OSW_TMM_delay( uint32 ms )
{
	osDelay( ms );
}

void WST_OSW_TSK_userInit(void (*function)(void *), WST_RTOS_PRIORITY_t priority, void *stack, uint16 stacksize, void *taskArgument)
{
	wstMonitorTask.def.pthread = (os_pthread)function;
	wstMonitorTask.def.tpriority = priority;
	wstMonitorTask.def.instances = 1;
	wstMonitorTask.def.stacksize = stacksize;

  wstMonitorTask.id = osThreadCreate (&wstMonitorTask.def, taskArgument);
	
	if( wstMonitorTask.id == 0 )
	{
		WST_ERR::error( WST_ERR::WST_ERR_TASK_START_FAILED, WST_RTOS_ERR_NONE );
	}
}

void WST_OSW_TSK_cleanup(WST_TSK* me)
{	
		osThreadTerminate( me->getRtosTask()->id );
}

void WST_OSW_TSK_start(WST_TSK* me)
{
	me->getRtosTask()->def.pthread = (os_pthread)WST_TSK::task_start;
	me->getRtosTask()->def.tpriority = (osPriority)me->getPriority();
	me->getRtosTask()->def.instances = 1;
	me->getRtosTask()->def.stacksize = me->getStackSize();

	me->getRtosTask()->id = osThreadCreate( &me->getRtosTask()->def, (void*)me );
	
	if( !me->getRtosTask()->id )
	{
		WST_ERR::error( WST_ERR::WST_ERR_TASK_START_FAILED, WST_RTOS_ERR_NONE );
	}
}

/**
* \brief suspends Task (not implemented)
*/
void WST_OSW_TSK_suspend(WST_TSK* me)
{
		WST_ERR::error( WST_ERR::WST_ERR_NOT_IMPLEMENTED, 0U );
}

/**
* \brief resumes Task (not implemented)
*/
void WST_OSW_TSK_resume(WST_TSK* me)
{
		WST_ERR::error( WST_ERR::WST_ERR_NOT_IMPLEMENTED, 0U );
}


/**
* \brief Timer Manager Task
*
* Handles timeouts of the system.
*/
void WST_OSW_TMM_timerCallBack( const void* arg )
{
		WSTRTOS_incrementRxfTicks();
		WST_TMM::getInst()->processTimeouts();
}


/**
* \brief cancel all events for a certain destination
*
* Deletes all events for a certain destination (if id == 0) or only the events with the 
* specified Id. 
*/
void WST_OSW_MSQ_cancelEvents(WST_MSQ* me, const WST_FSM*  destination, WST_EVT_ID_t id )
{
	static WSTBoolean		firstTime = WSTTRUE;
	static WST_MSQ			tempMSQ;
	WST_EVT 				*tempWST_EVT;
	osEvent					tempEVT;
	osStatus				tempStatus;
	
	/* Initialise the temporary message queue to the correct values */
	tempMSQ.getRtosMessageQueue()->def.queue_sz = me->getInitSize();
	
	/* Memory allocation for temporary queue */
	tempMSQ.getRtosMessageQueue()->def.pool = WST_MEM::getMemory( ( 4 + me->getInitSize() ) * sizeof( uint32 ) );
	
	/* Check if the temporary queue must be created */
	if ( firstTime == WSTTRUE )
	{
		tempMSQ.getRtosMessageQueue()->id = osMessageCreate( &me->getRtosMessageQueue()->def, NULL );
		firstTime = WSTFALSE;
	}
	
	/* get all messages from the message queue into the temp queue */
	tempEVT = osMessageGet( me->getRtosMessageQueue()->id, WST_MSQ_NOWAIT );
	while ( tempEVT.status == osEventMessage )
	{
		if ( ( tempStatus = osMessagePut( tempMSQ.getRtosMessageQueue()->id, (uint32_t) tempEVT.value.p, WST_MSQ_NOWAIT ) ) != osOK ) 
		{
			WST_ERR::error ( WST_ERR::WST_ERR_MSQ_SEND_FAILED, tempStatus );
		}
		
		tempEVT = osMessageGet( me->getRtosMessageQueue()->id, WST_MSQ_NOWAIT );	
	}
	
	/* Now put the message back when they are NOT for the Object to be deleted. */
	tempEVT = osMessageGet( tempMSQ.getRtosMessageQueue()->id, WST_MSQ_NOWAIT );
	while ( tempEVT.status == osEventMessage )
	{
		tempWST_EVT = (WST_EVT *) tempEVT.value.p;
		if ( tempWST_EVT->toBeCancelled( destination, id ) )
		{
			delete tempWST_EVT;
		}
		else
		{
			if ( ( tempStatus = osMessagePut (me->getRtosMessageQueue()->id, (uint32_t) tempEVT.value.p, WST_MSQ_NOWAIT ) ) != osOK ) 
			{
				WST_ERR::error ( WST_ERR::WST_ERR_MSQ_SEND_FAILED, tempStatus );
			}			
		}
		tempEVT = osMessageGet( tempMSQ.getRtosMessageQueue()->id, WST_MSQ_NOWAIT );		
	}

	/* Free temporary queue memory */
	WST_MEM::returnMemory( tempMSQ.getRtosMessageQueue()->def.pool );
}


/**
* \brief Gets the count of messages in the queue. (not implemented)
*  me->getRtosMessageQueue()->def.queue_sz returns maximum number of elements in the queue,
*  not the current count of messages in the queue.
*/
uint16 WST_OSW_MSQ_getCount( WST_MSQ* me )
{
	WST_ERR::error( WST_ERR::WST_ERR_NOT_IMPLEMENTED, 0U );
	return 0U;
}



/**
* \brief Gets an event from the queue.
* \return a pointer to the event
*
* Gets an event from the event structure. The event structure will be
* updated to make room for new events, the event itself is returned.
* Care must be taken to avoid race conditions, hence the critical region calls.
*/
void WST_OSW_MSQ_get( WST_MSQ* me, WST_EVT** event )
{
    osEvent osEvt;
   
  	osEvt = osMessageGet( me->getRtosMessageQueue()->id, WST_MSQ_WAIT_FOREVER );
	
	if (osEvt.status != osEventMessage)             
	{
		WST_ERR::error( WST_ERR::WST_ERR_MSQ_GET_FAILED, osEvt.status );
	}
	  
	*event = (WST_EVT*) osEvt.value.p;
}

/**
* \brief Allocate memory.
* \return allocated memory pointer
* Memory allocation protected with mutex.
*/
MALLOC_RETURN_TYPE WST_OSW_MEM_malloc( MALLOC_ARGUMENT_TYPE requestedSize )
{
	MALLOC_RETURN_TYPE p = NULL;

#ifndef NO_MALLOC

	if(mutexInitialized == WSTFALSE)
	{
		memoryMutex = new WST_MTX();
		mutexInitialized = WSTTRUE;
	}
	
	WST_OSW_MTX_enterCriticalRegion( memoryMutex );
	
	p = new char[ requestedSize ];
	
	WST_OSW_MTX_exitCriticalRegion( memoryMutex ); 
	
#endif	/* NO_MALLOC */

	/* Additional NULL pointer checking / error handling must be performed where this function is being called. */

    return p;
}

/**
* \brief Free memory.
* Frees allocated memory protected with mutex.
*/
void WST_OSW_MEM_free( MALLOC_RETURN_TYPE memory )
{
#ifndef NO_MALLOC

	WST_OSW_MTX_enterCriticalRegion( memoryMutex );
	
	delete (char*) memory;
	
	WST_OSW_MTX_exitCriticalRegion( memoryMutex );  
	
#endif	/* NO_MALLOC */
}

void WST_OSW_TMM_initTimerTask()
{
	uint32_t tmr_arg;
	osStatus status;
	
	wstTimerMngr.def.ptimer = WST_OSW_TMM_timerCallBack;
	wstTimerMngr.def.timer = (void *) &wstTimerMngr.tmr_array[0];
	wstTimerMngr.id = osTimerCreate ( &wstTimerMngr.def, osTimerPeriodic, &tmr_arg );

	if( wstTimerMngr.id == 0 )
	{
		WST_ERR::error( WST_ERR::WST_ERR_TIMER_TASK_START_FAILED, WST_RTOS_ERR_NONE );
	}
	else
	{
		status = osTimerStart ( wstTimerMngr.id, WST_MS_PER_TICK );
		if ( status != osOK )
		{
			WST_ERR::error( WST_ERR::WST_ERR_TIMER_TASK_START_FAILED, status );
		}
	}
}

/**
* \relates WST_MSQ
* \brief Initializes the message queue object.
*
* Initialises the (global!!) event structure. It is an array where, for speed, next pointers are
* implemented. In this way, there is no Modulo operation needed (which is too long to block IRQ's)
*/
void WST_OSW_MSQ_init(  WST_MSQ* me )
{
	me->getRtosMessageQueue()->def.queue_sz = me->getInitSize();
	me->getRtosMessageQueue()->def.pool = WST_MEM::getMemory( (4 + me->getInitSize() ) * sizeof( uint32 ) );
	
	if ( me->getRtosMessageQueue()->def.pool == NULL )
	{
		WST_ERR::error( WST_ERR::WST_ERR_MSQ_INIT_FAILED, WST_RTOS_ERR_NONE );
	}
	me->getRtosMessageQueue()->id = osMessageCreate( &me->getRtosMessageQueue()->def, NULL );
	if ( me->getRtosMessageQueue()->id == NULL)
	{
		WST_ERR::error( WST_ERR::WST_ERR_MSQ_INIT_FAILED, WST_RTOS_ERR_NONE);
	}

}


/**
 * \relates WST_MSQ
 * \brief Cleans up the message queue object by freeing memory for the RTOS message queue.
 * \req{RXF-1074}
 */
void WST_OSW_MSQ_cleanup(  WST_MSQ* me )
{
	WST_MEM::returnMemory( me->getRtosMessageQueue()->def.pool);
}


void WST_OSW_MSQ_put( WST_MSQ* me, WST_EVT*  event, WSTBoolean fromISR )
{
	osStatus status;
	uint32 waitTimeMs;
	
	waitTimeMs = WST_MSQ_WAIT_FOREVER;
	if( fromISR ) 
	{
		/* CMSIS-RTOS Documentation: The parameter millisec must be 0 for using this function in an ISR. */
		waitTimeMs = 0U;
	}
	
	status = osMessagePut( me->getRtosMessageQueue()->id, (uint32_t)event, waitTimeMs );

	if( status != osOK )
	{
		WST_ERR::error( WST_ERR::WST_ERR_EVENT_QUEUE_FULL, status );
	}
}



void WST_OSW_MTX_init( WST_MTX* me )
{
	me->WST_MTX_getRtosMutex()->def.mutex = (void *) &me->WST_MTX_getRtosMutex()->mtx_array[0];
 	me->WST_MTX_getRtosMutex()->id = osMutexCreate ( &me->WST_MTX_getRtosMutex()->def );
	if ( me->WST_MTX_getRtosMutex()->id == NULL)
	{
		WST_ERR::error( WST_ERR::WST_ERR_MTX_INIT_FAILED, WST_RTOS_ERR_NONE);
	}
}


void WST_OSW_MTX_cleanup( WST_MTX* me )
{
	osStatus status;
	
  status = osMutexDelete ( me->WST_MTX_getRtosMutex()->id );
	
	if ( status != osOK )
	{
		WST_ERR::error( WST_ERR::WST_ERR_MTX_CLEANUP_FAILED, status );
	}
}


void WST_OSW_MTX_enterCriticalRegion( WST_MTX* me )
{
	osStatus status;

	status = osMutexWait ( me->WST_MTX_getRtosMutex()->id, WST_MTX_WAIT_FOREVER );
	
	if ( status != osOK )
	{
		WST_ERR::error( WST_ERR::WST_ERR_MTX_LOCK_FAILED, status );
	}
}


void WST_OSW_MTX_exitCriticalRegion( WST_MTX* me )
{
	osStatus status;

	status = osMutexRelease ( me->WST_MTX_getRtosMutex()->id );
	
	if ( status != osOK )
	{
		WST_ERR::error( WST_ERR::WST_ERR_MTX_CLEANUP_FAILED, status );
	}
}


#define WST_RXF_RUNNING_STOP_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */
