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
 * $Id: WST_OSW.cpp 34182 2016-04-08 12:54:34Z eroemer $
 * $URL: https://svn.willert.de/V6/trunk/Component/RTOS/KeilRTX/Source/CPP/WST_OSW.cpp $
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


/* The project sources include wst.h which sets WST_H which value is tested in our include files.
 * 
 * It is not set when compiling the user project, in order to have WST.h include everything
 * in the right order, and 'ignore' generated include statements by the modelling tool.
 */

	
#include <stdlib.h>					/* size_t prototype */


/* WST_OSW for Keil-RTX needs to have access to malloc and protects it with a task lock.
 * So we need to define WST_DO_NOT_MAP_MALLO to stop WST_MEM.h from mapping it and to
 * make sure we do not have a deadly infinite recursion in WST_OSW_MEM_malloc().
 */
#define WST_DO_NOT_MAP_MALLOC


#include "WST.h"


#include <rtl.h>



#define WST_RXF_RUNNING_START_SEC_DATA_NOINIT_UNSPECIFIED_FAST
/* @MISRA_19.1,19.15=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

static uint32	timerTaskStack[ (WST_TMM_TASK_STACK_SIZE + 3) / 4 ];

#define WST_RXF_RUNNING_STOP_SEC_DATA_NOINIT_UNSPECIFIED_FAST
/* @MISRA_19.1,19.15=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */





#define WST_RXF_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

uint16 WST_OSW_MSQ_getCount( WST_MSQ* me )
{
    return ( me->getInitSize() - os_mbx_check ( *me->getRtosMessageQueue() ) );
}

void WST_OSW_TSK_init(WST_TSK* me)
{

}

void WST_OSW_TSK_userInit(void (*function)(void *), uint8 priority, void *stack, uint16 stacksize, void *taskArgument)
{
	OS_TID rtosTask = os_tsk_create_user_ex( function, priority, stack, stacksize, taskArgument );

	if( !rtosTask )
	{
		WST_ERR::error( WST_ERR::WST_ERR_TASK_START_FAILED, 0u );
	}
}

void WST_OSW_TSK_cleanup(WST_TSK* me)
{
	WST_MEM::returnMemory( me->getStackMemory() );
}


void WST_OSW_TSK_start(WST_TSK* me)
{	
	OS_TID rtosTask = os_tsk_create_user_ex( WST_TSK::task_start,
											me->getPriority(),
											me->getStackMemory(),
											me->getStackSize(),
											(void*)me
										) ;
	
	if( rtosTask == 0 )
	{                          
		WST_ERR::error( WST_ERR::WST_ERR_TASK_START_FAILED, 0u );
	}
}


/**
* \brief Timer Manager Task
* \return void
* \xrefitem RXFe "RXF Interface" "List of functions"
*
* Handles timeouts of the system.
*/
void WST_OSW_TMM_timerTask( void* arg )
{
	while(1)
	{
		os_dly_wait( 1U );
		WSTRTOS_incrementRxfTicks();
		WST_TMM::getInst()->processTimeouts();
	}
}


/**
* \brief Timer Manager Task
* \return void
* \xrefitem RXFe "RXF Interface" "List of functions"
*
* Handles timeouts of the system.
*/
void WST_OSW_TMM_delay( uint32 ms )
{
		os_dly_wait( ms );
}


bool WST_OSW_TSK_suspend( WST_TSK *me ){
	/* TODO: WST_OSW_TSK_suspend not implemented yet */
   	WST_ERR::error( WST_ERR::WST_ERR_NOT_IMPLEMENTED, 0U );
	return true;
}

bool WST_OSW_TSK_resume( WST_TSK *me ){
	/* TODO: WST_OSW_TSK_resume not implemented yet */
   	WST_ERR::error( WST_ERR::WST_ERR_NOT_IMPLEMENTED, 0U );
	return true;
}

/**
* \brief cancel all events for a certain destination
* \return void
* \xrefitem RXFe "RXF Interface"
*
* Deletes all events for a certain destination (if id == 0) or only the events with the 
* specified Id. Is not critical because it can not be interrupted by the consume function
* (which is not pre-emptive) and an interrupt can send an event but this will be added 
* to the head function. Hence the LclHead copy.
*/
void WST_OSW_MSQ_cancelEvents(WST_MSQ* me, WST_FSM*  destination, WST_EVT_ID_t id )
{
	if( WST_OSW_MSQ_getCount( me ) > 0 ){
		WST_MSQ*	tempMSQ = new WST_MSQ( me->getInitSize() );
		WST_EVT*	event;

		
		/* Move all events into a temporary message queue first. */
		while( os_mbx_wait( *me->getRtosMessageQueue(), (void**) &event, 0 ) != OS_R_TMO )
		{
			tempMSQ->put( event, false );
		}

		/* Now only move back the events which do not need to be canceled into the real message queue. */
		while( os_mbx_wait(*tempMSQ->getRtosMessageQueue(), (void**) &event, 0) != OS_R_TMO )
		{
			if( event->toBeCancelled( destination, id) == false )
			{
				me->put( event, false );
			}
			else
			{
				/* if event is removed from queue it must also be deleted to free memory */
				if( event->getIsStatic() == WSTFALSE )
				{
					delete event;
				}
			}
		}
		
		delete tempMSQ;
	}
}


/**
* \brief Gets an event from the queue.
* \return a pointer to the event
* \xrefitem RXFe "RXF Interface" "Called by Rhapsody" Called by Rhapsody generated code
* \xrefitem RXFr "RXF Critical Regions" "Critical Regions" Deals with critical regions
*
* Gets an event from the event structure. The event structure will be
* updated to make room for new events, the event itself is returned.
* Care must be taken to avoid race conditions, hence the critical region calls.
*/
void WST_OSW_MSQ_get( WST_MSQ* me, WST_EVT **event )
{
	
	os_mbx_wait (
			    *me->getRtosMessageQueue(),	/* The mailbox to get message from */
			    (void**)event,		/* Location to store the message pointer */
			    WST_MSQ_WAIT_FOREVER);	/* Wait time for message to become available */
}


MALLOC_RETURN_TYPE	WST_OSW_MEM_malloc( MALLOC_ARGUMENT_TYPE requestedSize )
{
	MALLOC_RETURN_TYPE	p = NULL;

#ifndef NO_MALLOC

	/* Keil documentation states:
	 * The variable length memory allocation functions are not reentrant.
	 * Therefore the system timer interrupts need to be disabled during the
	 * execution of the malloc() or free() function. Function tsk_lock()
	 * disables timer interrupts and function tsk_unlock() enables timer
	 * interrupts.
	 */
	if( WST_TSK::getOS_Started() != FALSE )
	{ 
		tsk_lock(); 
		p = malloc( requestedSize );
		tsk_unlock(); 
	}
	else
	{
		p = malloc( requestedSize );
	}
#endif	/* NO_MALLOC */

	/* Additional NULL pointer checking / error handling must be performed where this function is being called. */

    return p;
}

void WST_OSW_MEM_free( MALLOC_RETURN_TYPE memory )
{
#ifndef NO_MALLOC
	if( WST_TSK::getOS_Started() != FALSE )
	{ 
		tsk_lock(); 
		free( memory );
		tsk_unlock(); 
	}
	else
	{
		free( memory );
	}
#endif	/* NO_MALLOC */
}

void WST_OSW_TMM_initTimerTask()
{
    OS_TID tickTimerId;

    tickTimerId = os_tsk_create_user_ex( WST_OSW_TMM_timerTask,
											  WST_TMM_TASK_PRIORITY,
											  timerTaskStack,
											  WST_TMM_TASK_STACK_SIZE,
											  0
											);
	
	if( tickTimerId == 0 )
	{
		WST_ERR::error( WST_ERR::WST_ERR_TIMER_TASK_START_FAILED, 0u );
	}
}



/**
* \relates WST_MSQ
* \brief Initializes the message queue object.
* \return void
*
* Initialises the (global!!) event structure. It is an array where, for speed, next pointers are
* implemented. In this way, there is no Modulo operation needed (which is too long to block IRQ's)
*/
void WST_OSW_MSQ_init(  WST_MSQ* me )
{
	/* os_mbx_init is called with the sizeof the mailbox as second argument */
	if( me->getRtosMsgBuffer() == NULL )
	{
		me->setRtosMessageQueue( (WST_RTOS_MSQ_t*) WST_MEM::getMemory( ( me->getInitSize() + 4 ) * sizeof(gen_ptr) ) );
		me->setRtosMsgBuffer( *me->getRtosMessageQueue() );
		if( *me->getRtosMessageQueue() == NULL )
		{
			WST_ERR::error( WST_ERR::WST_ERR_EMPTY_MEMORY_PTR, 0u );
		}
	}
	else
	{
		me->setRtosMessageQueue( (WST_RTOS_MSQ_t) me->getRtosMsgBuffer() );
	}
	os_mbx_init( *me->getRtosMessageQueue(), ( me->getInitSize() + 4 ) * sizeof(gen_ptr) );
}

void WST_OSW_MSQ_put( WST_MSQ* me, WST_EVT*  event, WSTBoolean fromISR )
{
#ifdef  WST_MSQ_PUT_WITH_ISR_DETECTION
	fromISR = WSTTarget_isInISR();
#endif  /* WST_MSQ_PUT_WITH_ISR_DETECTION */

    /* Insert the event into the queue. */
	if( fromISR == true )
	{
		WSTTarget_enterCriticalRegion(); /* isr_mbx_send is not Interrupt Save */
		
		isr_mbx_send( *me->getRtosMessageQueue(),	/* The mailbox to put the message in */
				    event ); 						/* Pointer to the message */

		WSTTarget_exitCriticalRegion(); /* isr_mbx_send is not Interrupt Save */
	}
	else
	{
		OS_RESULT res;
		/* If the msg queue is full, the errorhandler will be called.
		 */
		res = os_mbx_send(	*me->getRtosMessageQueue(),	/* The mailbox to put the message in */
				    event, 							/* Pointer to the message */
				    0U );			/* Wait time for mailbox to be free */
				    
		if( res != OS_R_OK )
		{
			WST_ERR::error( WST_ERR::WST_ERR_MSQ_SEND_FAILED, res );
		}
	}
}



void WST_OSW_MTX_init( WST_MTX* me )
{
    os_mut_init( me->WST_MTX_getRtosMutex() );
}


void WST_OSW_MTX_cleanup( WST_MTX* me )
{
    /* Nothing to be done for the Keil-RTX */
}


void WST_OSW_MTX_enterCriticalRegion( WST_MTX* me )
{
	/* Keil Documentation sais:
	 * You must set timeout to 0xFFFF for an indefinite timeout period.
	 */
	
    (void) os_mut_wait(me->WST_MTX_getRtosMutex(), 0xFFFF);
    
}


void WST_OSW_MTX_exitCriticalRegion( WST_MTX* me )
{
	OS_RESULT res;
	
    res = os_mut_release( me->WST_MTX_getRtosMutex() );
    
    if( res != OS_R_OK )
	{
		WST_ERR::error( WST_ERR::WST_ERR_MTX_UNLOCK_FAILED, res );
	}
}


#define WST_RXF_RUNNING_STOP_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

