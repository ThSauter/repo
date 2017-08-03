/********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_TMM
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_TMM.cpp
*********************************************************************/

//## auto_generated
#include "WST_TMM.h"
//## operation cancelEvents(WST_FSM *)
#include "WST_FSM.h"
//## auto_generated
#include "WST.h"
//## package RXF::RXF_BehaviorPkg

//## class WST_TMM
//#[ ignore
WST_TMM WST_TMM::inst;

WST_TMM::WST_TMM() { 
	// For internal use only (Singleton).
	// Use WST_TMM::getInst() to access instance.

#if WST_MAX_TIMEOUTS > 0
	WST_TMR::initTimeoutLists();
#endif /* WST_MAX_TIMEOUTS > 0 */
	
#ifdef WST_CFG_HIGHWATERMARKS
	usedTimeouts = 0U;
#endif /* WST_CFG_HIGHWATERMARKS */
	
    itsBusyList = NULL;
    
    processedTicks = WSTRTOS_getRxfTicks();	/* set to number of ticks at framework initialization */
}

WST_TMM* WST_TMM::getInst() {
	return &inst;
}
//#]

WST_TimeUnit_t WST_TMM::WSTTimeToTicks(WST_TimeUnit_t delayTime) {
    //#[ operation WSTTimeToTicks(WST_TimeUnit_t)
    WST_TimeUnit_t ticks;
    
    ticks = (WST_TimeUnit_t) (delayTime / (uint16) WST_MS_PER_TICK );
    if ( ticks == (WST_TimeUnit_t) 0 )
    {
        ticks = (WST_TimeUnit_t) 1;
    }
    return ticks;
    //#]
}

void WST_TMM::initMutex(){
	//#[ operation initMutex()
	mutex = new WST_MTX();
	//#]
}

void WST_TMM::cancelEvents(WST_FSM * destination) {
    //#[ operation cancelEvents(WST_FSM *)
    WST_TMR* timeout;	
    WSTBoolean timeoutFound = false;
    
	mutex->WST_MTX_enterCriticalRegion();
    
    /* Iterate down the busy list looking for any timeouts with this destination */
    timeout = itsBusyList;
    
    while ( timeout != NULL )
    {
    
    	if ( timeout->getDestination() == destination )
    	{
			stop( timeout );
    		timeoutFound = true;
		}
		timeout = timeout->nextTm;
    }
    mutex->WST_MTX_exitCriticalRegion();

    /* A timeout could have been added to the event queue
     * when another event already existed.
     */
	if ( timeoutFound == false && destination != NULL)
	{
		WST_TSK* destinationTask = destination->getOwnerTask();
		if (destinationTask != NULL)
		{
			WST_MSQ* destinationMessageQueue = destinationTask->getMessageQueue();
			if (destinationMessageQueue != NULL)
			{
				destinationMessageQueue->cancelEvents(destination, WST_TMR_id);
			}
		}
	}
    
    //#]
}

WST_TMR* WST_TMM::getExpiredTimeout( void ) {
    //#[ operation getExpiredTimeout()
	WST_TMR* timeout = NULL;
    
	mutex->WST_MTX_enterCriticalRegion();
	
    if ( itsBusyList != NULL )
    {
    	if ( itsBusyList->remainingTicks == (WST_TimeUnit_t) 0)
    	{
    		timeout = itsBusyList;
    
    		itsBusyList = itsBusyList->nextTm;
			if( itsBusyList != NULL )
			{
				itsBusyList->prevTm = NULL;
			}
            timeout->nextTm = NULL;
			timeout->prevTm = NULL;
    	}
    } /* WST_TMM.itsBusyList != NULL */
    
	mutex->WST_MTX_exitCriticalRegion();
    return timeout;
    //#]
}

void WST_TMM::processTimeouts( void ) {
    //#[ operation processTimeouts()
    WST_TMR* timeout;
    
    WST_TimeUnit_t currentTickCount = WSTRTOS_getRxfTicks();
    sint16 tickCount = ((sint16) currentTickCount) - ((sint16) processedTicks);
    processedTicks = currentTickCount;
    
    tick(tickCount);
    
    timeout = getExpiredTimeout();
    
    while ( timeout != NULL )
    {
    /*lint -save -e740 Unusual pointer cast (incompatible indirect types) */
    /* @MISRA_11.4=OFF ID-0004: Rhapsody uses different types of event structures that need to be casted to each other, e.g. a timer event has to be casted to a normal event before it is consumed. */
    
    	/* Add expired timeout to the event queue */
    	WST_TSK* destinationTask = timeout->getDestination()->getOwnerTask();     
        if(destinationTask == NULL)
    	{
    		destinationTask = &theMainTask;
    	}
    
    	destinationTask->getMessageQueue()->put( (WST_EVT*) timeout, false );
    
    /* @MISRA_11.4=ON */
    /*lint -restore */
    
    	timeout = getExpiredTimeout();
    }
    //#]
}


WST_TMR* WST_TMM::start(WST_TimeUnit_t delayTime, WST_FSM * destination) {
    //#[ operation start(WST_TimeUnit_t,WST_FSM *)
    WST_TMR* timeout = NULL;
    WST_TMR* p;
    WST_TimeUnit_t ticks;
    
	
	mutex->WST_MTX_enterCriticalRegion();

	/* get Free Timeout from Free list */
	timeout = new WST_TMR();

#ifdef WST_CFG_HIGHWATERMARKS
	usedTimeouts++;
	if( usedTimeouts > WST_CFG_Highwater::timeoutsMax ) {
		WST_CFG_Highwater::timeoutsMax = usedTimeouts;
	}
#endif /* WST_CFG_HIGHWATERMARKS */

	/* Initialize with the appropriate info */
	ticks = WSTTimeToTicks( delayTime );
	timeout->setId(WST_TMR_id);
	timeout->setDestination(destination);
	timeout->remainingTicks = ticks;
	timeout->prevTm = NULL;

	/* And insert timeout into the busy list */
	/* List empty First element */
	if ( itsBusyList == NULL )
	{
		/* The list was empty so we place it in the list.

		   Before: ->NULL

		   New:    [150]

		   After:  [150]->NULL

		 */

		itsBusyList = timeout;
		timeout->nextTm = NULL;
	}
	else
	{
		/* Check if the new element must be placed _before_ the first in the busy list */
		if ( itsBusyList->remainingTicks >= timeout->remainingTicks )
		{
			/* Yes must be before. Do it now. */
			timeout->nextTm = itsBusyList;
			itsBusyList = timeout;

			/* The next elements time must be decreased with the new elements
			   time. In that way we store the time relative.

			   Before: [100]->[100]->[25]->NULL

			   New:    [50]

			   After:  [50]->[50]->[100]->[25]->NULL

			 */
		}
		else
		{
			/* No it must be after the first element. Good, now we only have to
			   walk across the list. Now let p point to the first element
			 */
			p = itsBusyList;

			/* Since we store the time relative we must subtract the first element's
			   time from the new elements time.
			 */

			timeout->remainingTicks -= p->remainingTicks;

			while ( (p->nextTm != NULL) && (timeout->remainingTicks > p->nextTm->remainingTicks ))
			{
				timeout->remainingTicks -= p->nextTm->remainingTicks;
				p = p->nextTm;
			}

			/* OK, we found the element where we place the new one after
			   This can be the last, the last element's next pointer is NULL
			   but we can handle that.
			 */
			timeout->prevTm = p;
			timeout->nextTm = p->nextTm;
			p->nextTm = timeout;
			/* The next elements time must be decreased with the new elements
			   time. In that way we store the time relative.

			   Before: [100]->[100]->[25]->NULL

			   New:    [150]

			   After:  [100]->[50]->[50]->[25]->NULL

			 */
		}
		if (timeout->nextTm != NULL)
		{
			/*	Only adjust next timer when there is a next timer.....
			 */

			if ( timeout->nextTm->remainingTicks >= timeout->remainingTicks )
			{
				timeout->nextTm->remainingTicks -= timeout->remainingTicks;
			}
			else
			{
				timeout->nextTm->remainingTicks = (WST_TimeUnit_t) 0;
			}
			timeout->nextTm->prevTm = timeout;
		}
	}
	
	mutex->WST_MTX_exitCriticalRegion();
    
    
    return timeout;
    //#]
}

void WST_TMM::stop(WST_TMR* timeoutToStop) {
    //#[ operation stop(WST_TMR)
	WSTBoolean isInMSQ = WSTTRUE;

    
	mutex->WST_MTX_enterCriticalRegion();
	
	if( timeoutToStop == itsBusyList )
	{
		isInMSQ = WSTFALSE;
		itsBusyList = itsBusyList->nextTm;
		if( itsBusyList != NULL )
		{
			itsBusyList->prevTm = NULL;
		}
	}
	
	if( timeoutToStop->prevTm != NULL )
	{
		isInMSQ = WSTFALSE;
		timeoutToStop->prevTm->nextTm = timeoutToStop->nextTm;
	}
	
	if( timeoutToStop->nextTm != NULL )
	{
		isInMSQ = WSTFALSE;
		timeoutToStop->nextTm->remainingTicks += timeoutToStop->remainingTicks;
		timeoutToStop->nextTm->prevTm = timeoutToStop->prevTm;
	}
	
	if( WSTTRUE == isInMSQ )
	{
		/* Timeout is in progress or it is inside the MSQ
		 So we need to set the event ID that is not processed by the Framework */
		timeoutToStop->setId( WST_TMR_delete_id );
	}
	else
	{
		/* Timeout is stopped before it is processed */
		delete timeoutToStop;
	}
	
#ifdef WST_CFG_HIGHWATERMARKS
	usedTimeouts--;
#endif /* WST_CFG_HIGHWATERMARKS */
	mutex->WST_MTX_exitCriticalRegion();
    //#]
}

void WST_TMM::tick(sint16 elapsedTime) {
    //#[ operation tick(sint16)
    if ( itsBusyList != NULL )
    {
    
    /*lint -save -e571	Suspicious cast */
    	/* PC-Lint complains about a Prohibited Implicit Conversion: Signed versus Unsigned, but all types are actually TimeUnit. The underlying type will be preserved. */
		
		/*
		 * When the system is very busy it is possible that timerticks are not handled immediately
		 * To prevent timer errors we add the timer ticks in the elapsedTime attribute
		 * When we check if timer are expired there are multiple situations that can occur:
		 * - The first timer is larger then elapsedTime
		 *   => just subtract the elapsed time from the remaining time
		 * - The first timer is larger then the elapsed time
		 *   => the first timer is expired BUT...
		 *   - The next timer is not expired 
		 *      => subtract the remaining part of elapsedTime from that timer
		 *   - The next timer is also expired
		 *      => set timer to 0 and subtract the remainder from the next list
		 */ 
    	if ( itsBusyList->remainingTicks > ( (WST_TimeUnit_t) elapsedTime) )
    	{
			/*
			
			Situation before:
			
			elapsedTime = 1
			
			[42]->[100]->[100]->NULL
			
			
			Situation after:
						
			[41]->[100]->[100]->NULL
			
			*/
    		itsBusyList->remainingTicks -= ( (WST_TimeUnit_t) elapsedTime);
    	}
    	else
    	{
			WST_TMR* tempTimer;	
			
			/*
			
			Situation before:
			
			elapsedTime = 2
			
			[1]->[100]->[100]->NULL
			
			
			Situation after:
						
			[99]->[100]->NULL
			
			*/
    		elapsedTime -= itsBusyList->remainingTicks;
			itsBusyList->remainingTicks = (WST_TimeUnit_t) 0U;
			tempTimer = itsBusyList->nextTm;
			
			while (tempTimer != NULL)
			{
			/*
			
			Situation before:
			
			elapsedTime = 5
			
			[2]->[1]->[2]->[100]->[100]->NULL
			
			
			Situation after:
						
			[99]->[100]->NULL
			
			*/
				if ( tempTimer->remainingTicks > (WST_TimeUnit_t) elapsedTime )
				{
					tempTimer->remainingTicks -= elapsedTime;
					tempTimer = NULL;
				}
				else
				{
					elapsedTime -= tempTimer->remainingTicks;
					tempTimer->remainingTicks = (WST_TimeUnit_t) 0U;
					tempTimer = tempTimer->nextTm;
				}
			}     	
		}
    /*lint restore */
    }
    //#]
}



/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_TMM.cpp
*********************************************************************/
