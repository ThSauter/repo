/********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_FSM
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_FSM.cpp
*********************************************************************/

//## auto_generated
#include "WST_FSM.h"
//## operation consumeGivenEvent(WST_EVT)
#include "WST_EVT.h"
//## operation cancel(WST_TMR)
#include "WST_TMR.h"
//## auto_generated
#include "WST.h"
//## package RXF::RXF_BehaviorPkg

//## class WST_FSM

WST_FSM::WST_FSM() {
    currentEvent = NULL;
    ownerTask = &theMainTask;
    //#[ operation WST_FSM(WST_TSK)
    status = statusDefault;
    nullTransitionCount = 0U;
    rootState_active = 0;

#ifdef WST_LIVE_ANIMATION
	for( int i = 0; i < WST_MONITOR_MAX_PARALLEL_STATES; i++)
	{
		this->activeState[i] = 0U;
	}
#endif /* of WST_LIVE_ANIMATION */

    //#]
}

WST_FSM::~WST_FSM( void ) {
    //#[ operation ~WST_FSM()
    /* Used to be local setInCleanup() function like macro */
    status |= statusInCleanup;
    
    cancelEventsAndTimeouts();
    //#]
    cleanUpRelations();
}

void WST_FSM::cancel(WST_TMR* timeout) {
    //#[ operation cancel(WST_TMR)

    if(timeout != NULL)
    {    
        timeout->getDestination()->cancelTimeout(timeout);
        WST_TMM::getInst()->stop( timeout );
    }

    //#]
}

void WST_FSM::cancelEventsAndTimeouts( void ) {
    //#[ operation cancelEventsAndTimeouts()
	if (WST_TMM::getInst() != NULL)
	{
		WST_TMM::getInst()->cancelEvents(this);
	}

	//Make sure all events with this destination are deleted
	
	if (ownerTask != NULL)
	{
		WST_MSQ* destinationMessageQueue = ownerTask->getMessageQueue();
		if (destinationMessageQueue != NULL)
		{
			destinationMessageQueue->cancelEvents(this, 0);
		}
	}
	
    
	//KomponenteRxf::framework->EventCancel( this );
    setBehaviorStarted( WSTFALSE );
    //#]
}

void WST_FSM::destroy( void ) {
    //#[ operation destroy()
    //#]
}

void WST_FSM::endBehavior( void ) {
    //#[ operation endBehavior()
    setShouldTerminate( WSTTRUE );
    //#]
}

WSTBoolean WST_FSM::gen(WST_EVT* event, WSTBoolean fromISR ) {
    //#[ operation gen(WST_EVT)
    /*lint -save -e613 -e831  Possible use of null pointer, Reference cited in prior message */
    
    WSTBoolean ret;
    
    /*lint restore */
    if ( NULL == event )
    {
    	ret = WSTFALSE;
    }
    else
    {
    	if ( isInCleanup()  )
    	{
    		ret = WSTFALSE;
    	}
    	else
    	{
    		/* Set the destination for the event */
    		event->setDestination( this );
    
    		/* put it in the queue */
    		ownerTask->getMessageQueue()->put( event, fromISR );
    
    		ret = WSTTRUE;
    	}
    }
    return ret;
    //#]
}

WST_FSM::TakeEventStatus WST_FSM::handleSyncEvent(WST_EVT* event) {
    //#[ operation handleSyncEvent(WST_EVT)
#ifdef WST_LIVE_ANIMATION
	{
		WST_TimeUnit_t		currentTickCount = WSTRTOS_getRxfTicks(); 
		uint8 *eventArgument = (uint8*) ( event + 1 );
		
		WSTMonitorEventCreate monitorEventCreate;  
		WSTMonitorEventID++;
		event->setEventID( WSTMonitorEventID );
		monitorEventCreate.eventID = WSTMonitorEventID;
		monitorEventCreate.source = event->getSource();
		monitorEventCreate.destination = event->getDestination();
		monitorEventCreate.id = event->getId();
		monitorEventCreate.currentTick = currentTickCount;
		
		WSTMonitor_sendEventCreate( (uint8*) &monitorEventCreate , event->getSize(), eventArgument );
		
	}	
#endif /* WST_LIVE_ANIMATION */
    return takeEvent( event );
    //#]
}

void WST_FSM::popNullTransition( void ) {
    //#[ operation popNullTransition()
    if ( nullTransitionCount > 0U )
    {
    	nullTransitionCount--;
    }
    else
    {
    	WST_ERR::error( WST_ERR::WST_ERR_TOO_FEW_NULL_CONFIGS, 0U );
    }
    //#]
}

bool WST_FSM::send( WST_EVT *event, const void* &params ) {
    //#[ operation send()
	return gen(event, false);
    //#]
}

bool WST_FSM::send( WST_EVT *event ) {
    //#[ operation send()
	return gen(event, false);
    //#]
}

void WST_FSM::pushNullTransition( void ) {
    //#[ operation pushNullTransition()
    nullTransitionCount++;
    //#]
}

void WST_FSM::rootState_entDef( void ) {
    //#[ operation rootState_entDef()
    //#]
}

bool WST_FSM::cancelTimeout( const WST_TMR* timeout ) {
    //#[ operation cancelTimeout()
	return false;
    //#]
}

WST_FSM::TakeEventStatus WST_FSM::rootState_processEvent( void ) {
    //#[ operation rootState_processEvent()
    return WST_EVT_handleEventNotConsumed; /* To be implemented! */
    //#]
}

WST_TMR* WST_FSM::scheduleTimeout(const WST_TimeUnit_t delay, char *) {
    //#[ operation scheduleTimeout(uint16,char*)
    return WST_TMM::getInst()->start( delay, this );
    //#]
}

void WST_FSM::setShouldDelete(bool b) {
    //#[ operation setShouldDelete(bool)
    if ( b == WSTTRUE )
    {
    	status |= statusShouldDelete;
    }
    else
    {
    	status = status & (uint8)(~statusShouldDelete);
    }
    //#]
}

void WST_FSM::setTask(WST_TSK* ownerTaskPtr, WSTBoolean isActive) {
    //#[ operation setTask(WST_TSK,bool)
    if( isActive || ownerTaskPtr != NULL ){
    	this->ownerTask = ownerTaskPtr;
    }
    else
    {
    	this->ownerTask = &theMainTask;
    }
    //#]
}

WSTBoolean WST_FSM::startBehavior( void ) {
    //#[ operation startBehavior()
    WSTBoolean returnValue = WSTFALSE;
    
    /* start behavior only once */
    if ( isBehaviorStarted() == WSTFALSE )
    {
    	/* mark that startBehavior was called */
    	setBehaviorStarted( WSTTRUE );
    
    	rootState_entDef();
    
    	/* Generate a dummy event in case the instance doesn't receive */
    	/* any external events. This causes the runToCompletion()      */
    	/* operation to be taken after the default transition.         */
    	if ( shouldCompleteRun() )
    	{
    		setCompleteStartBehavior( WSTTRUE );
    
    		WST_EVT* startBehaviorEvent = new WST_EVT();     
    		startBehaviorEvent->setId( WSTStartBehavior_id );
    		gen( startBehaviorEvent, false );
    
    	}
    }
    
    /* Delete the object if it reached a terminate connector */
    if ( shouldTerminate() )
    {
    	if ( shouldDelete() )
    	{
    		delete this;
    	}
    }
    else
    {
    	returnValue = WSTTRUE;
    }
    
    return returnValue;
    //#]
}


WST_FSM::TakeEventStatus WST_FSM::takeEvent(WST_EVT* event) {
    //#[ operation takeEvent(WST_EVT)
    TakeEventStatus returnValue = WST_EVT_handleEventCompleted;
    
    if ( isInCleanup() )
    {
    	returnValue = WST_EVT_handleEventInCleanup;
    }
	/* When a static object is in termination state ignore incomming events from extern objects */
	else if( shouldTerminate() && !shouldDelete() )
	{
		returnValue = WST_EVT_handleEventCompleted;
	}
    else
	{
#ifdef WST_LIVE_ANIMATION
		{
						
			WST_TimeUnit_t		currentTickCount = WSTRTOS_getRxfTicks(); 
		
			if( ( event->getId() == WST_TMR_id && monitorTimeoutEnableFlag == 1) || 
				( (event->getId() != WST_TMR_id) && (event->getId() != WST_TMR_delete_id) ) )
			{    
				WSTMonitorEventStart monitorEventStart;
				monitorEventStart.currentTick = currentTickCount;
				monitorEventStart.eventID = event->getEventID();
				WSTMonitor_sendEventStart( (uint8*) &monitorEventStart );
			}		
		
		}
#endif /* WST_LIVE_ANIMATION */
		consumeGivenEvent( event );
		
		if ( shouldTerminate() )
		{
			returnValue = WST_EVT_handleEventReachTerminate;
		}
	}

#ifdef WST_LIVE_ANIMATION
	{
		if( ( event->getId() == WST_TMR_delete_id && monitorTimeoutEnableFlag == 1) ||
		    ( (event->getId() != WST_TMR_id) && (event->getId() != WST_TMR_delete_id) ) )
		{    
			int i;
			WSTMonitorEventEnd monitorEventEnd;
			monitorEventEnd.eventID = event->getEventID();
			for( i = 0; i < WST_MONITOR_MAX_PARALLEL_STATES; i++)
			{
				monitorEventEnd.currentState[i] = this->activeState[i];
			}
			WSTMonitor_sendEventEnd( (uint8*) &monitorEventEnd );
			
		}

		if( firstBreakPoint != NULL ) {
			WSTMonitorBreakPoint *tmpBreakPoint = firstBreakPoint;		
			while( tmpBreakPoint != NULL )
			{
				if( ( ( (uint32)tmpBreakPoint->destination | (uint32)event->getDestination()->owner) == (uint32)event->getDestination()->owner) && 
					( ( (uint16)tmpBreakPoint->eventID | (uint16)event->getId() ) == (uint16)event->getId() )   )
				{
					if( (uint16)tmpBreakPoint->state == 0U )
					{
						monitorStopFlag = WSTTRUE;
					}
					else
					{
						for( int i = 0; i < WST_MONITOR_MAX_PARALLEL_STATES; i++)
						{
							if( (uint16)tmpBreakPoint->state == (uint16)this->activeState[i] ){
								monitorStopFlag = WSTTRUE;
							}
						}
					}
					tmpBreakPoint = tmpBreakPoint->next;
				}
				else{
					tmpBreakPoint = tmpBreakPoint->next;
				}
			}
		}
	}
#endif /* of WST_LIVE_ANIMATION */


    return returnValue;
    //#]
}

void WST_FSM::terminate( void ) {
    //#[ operation terminate()
    setShouldTerminate( WSTTRUE );
    //#]
}

void WST_FSM::handleTrigger(WST_EVT* event) {
    //#[ operation handleTrigger(WST_EVT)
    WST_EVT *saveEvent = currentEvent;
	
#ifdef WST_LIVE_ANIMATION
	event->setDestination( this );
	event->setSource( this );
#endif /* WST_LIVE_ANIMATION */

    takeEvent(event);
    currentEvent = saveEvent;
    //#]
}

WST_INLINE_OP void WST_FSM::consumeGivenEvent(WST_EVT* event) {
    //#[ operation consumeGivenEvent(WST_EVT)
    
	/* ignore event if startBehavior has not been called */
	if( isBehaviorStarted() )
	{
		currentEvent = event;

		if ( !isBusy() )
		{
			TakeEventStatus	eventstatus;
			/* Protect from recursive triggered operation calls */
			status |= statusBusy; /* busy flag = true */

			/* handle the event */
			eventstatus = rootState_processEvent();
			
			/* check if timeout need to be cleared */
			if( event->getId() == WST_TMR_id && eventstatus == WST_EVT_handleEventNotConsumed)
			{
				cancelTimeout( (WST_TMR*)event );
			}

			/* check runToCompletion() */
			if ( nullTransitionCount > 0 )
			{

				if ( !runToCompletion() )
				{
					/* Infinite loop, notify the user and return */
					WST_ERR::error ( WST_ERR::WST_ERR_INFINITE_NULL_TRANSITIONS, 0U );
				}
			}
			status &= ~statusBusy; /* busy flag = false */

			currentEvent = NULL;
		}
	}
    //#]
}


WST_INLINE_OP WSTBoolean WST_FSM::runToCompletion( void ) {
    //#[ operation runToCompletion()
    WSTBoolean			 		nullStepsInRange = WSTTRUE;
    sint16				 		nullStepCount = 0;
    TakeEventStatus				eventstatus;
    WSTBoolean			 		stopNullSteps = WSTFALSE;
    
    /* set NULL event for test and save current event in temp variable */
    WST_EVT nullEvent;
    WST_EVT *evPtr;
    evPtr = this->currentEvent;
    nullEvent.setId( WST_EVT_null_id );
    this->currentEvent = &nullEvent;
    
    
    /* If untriggered transitions are "hot" take them */
    while ( nullTransitionCount > 0U )
    {
    	nullStepCount++;
    	if ( nullStepCount > MAX_NULL_STEPS )
    	{
    		/* Found infinite loop */
    		nullStepsInRange = WSTFALSE;
    		stopNullSteps = WSTTRUE;
    
    		WST_ERR::error( WST_ERR::WST_ERR_INFINITE_NULL_TRANSITIONS, 0U );
    
    		/* reset the null config count */
    		nullTransitionCount = 0U;
    	}
    	/* Abort when in Cleanup */
    	else if ( isInCleanup() )
    	{
    		stopNullSteps = WSTTRUE;
    	}
    	else
    	{
    		eventstatus = rootState_processEvent();
    
    		/* Perform the null transition */
    		if ( ( eventstatus == WST_EVT_handleEventNotConsumed ) ||
    			 ( eventstatus == WST_EVT_handleEventError ) )
    		{
    			stopNullSteps = WSTTRUE;
    		}
    	}
    	if( stopNullSteps )
    	{
    		break;
    	}
    }
    /* reset event Pointer */
    this->currentEvent = evPtr;
    
    return nullStepsInRange;
    //#]
}

WST_INLINE_OP void WST_FSM::setBehaviorStarted(WSTBoolean b) {
    //#[ operation setBehaviorStarted(bool)
    if ( b == WSTTRUE )
    {
    	status |= statusStarted;
    }
    else
    {
    	status = status & (uint8)(~statusStarted);
    }
    //#]
}

WST_INLINE_OP void WST_FSM::setCompleteStartBehavior(WSTBoolean b) {
    //#[ operation setCompleteStartBehavior(bool)
    if ( b == WSTTRUE )
    {
    	status |= statusShouldCompleteStartBehavior;
    }
    else
    {
    	status = status & (uint8)(~statusShouldCompleteStartBehavior);
    }
    //#]
}

WST_INLINE_OP void WST_FSM::setShouldTerminate(WSTBoolean b) {
    //#[ operation setShouldTerminate(bool)
    if ( b == WSTTRUE )
    {
    	status |= statusTerminating;
    }
    else
    {
    	status = status & (uint8)(~statusTerminating);
    }
    //#]
}

WST_INLINE_OP WSTBoolean WST_FSM::shouldCompleteRun( void ) {
    //#[ operation shouldCompleteRun()
    WSTBoolean ret;
    
    if (nullTransitionCount > 0U)
    {
    	ret =  WSTTRUE;
    }
    else if ( (status & ((uint8) ~statusShouldDelete) & ((uint8) ~statusStarted)) != statusFALSE )
    {
    	ret =  WSTTRUE;
    }
    else
    {
    	ret = WSTFALSE;
    }
    return ret;
    //#]
}



void WST_FSM::cleanUpRelations( void ) {
    if(currentEvent != NULL)
        {
            currentEvent = NULL;
        }
    if(ownerTask != NULL)
        {
            ownerTask = NULL;
        }
}





/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_FSM.cpp
*********************************************************************/
