/********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_TSK
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_TSK.cpp
*********************************************************************/

//## auto_generated
#include "WST_TSK.h"
//## link messageQueue
#include "WST_MSQ.h"
//## auto_generated
#include "WST.h"
//## package RXF::RXF_BehaviorPkg


//## class WST_TSK

WST_TSK* WST_TSK::initList = NULL;

WSTBoolean WST_TSK::OS_Started = FALSE;


WST_TSK::WST_TSK(char* taskName, const uint8 taskPriority, const uint16 taskStackSize, const uint16 taskMessageQueueSize, WSTBoolean dynamicMessageQueue) : messageQueue( taskMessageQueueSize, OS_Started )
{
	//#[ operation WST_TSK(char*,uint8,uint16,uint8)
	priority			= taskPriority;
	stackSize			= taskStackSize;
	this->taskName = taskName;
	
	stackMemory = 	WST_MEM::getMemory( stackSize ) ;
	
	if( OS_Started != FALSE )
	{
		WST_OSW_TSK_init( this );
	}
	else
	{
		next = initList;
		initList = this;
	}
	//#]
}

WST_TSK::WST_TSK(uint8 *osw_stk, void* osw_msq, const uint8 taskPriority,const uint16 taskStackSize, const uint16 taskMessageQueueSize, WSTBoolean dynamicMessageQueue) : messageQueue( taskMessageQueueSize, osw_msq, OS_Started )
{
	//#[ operation WST_TSK(char*,uint8,uint16,uint8)
	priority			= taskPriority;
	stackSize			= taskStackSize;
	stackMemory 		= osw_stk;
	this->taskName = "static task";
	
	if( OS_Started != FALSE )
	{	
		WST_OSW_TSK_init( this );
	}
	else
	{
		next = initList;
		initList = this;
	}
	//#]
	
}

WST_TSK::~WST_TSK( void ) {
	WST_OSW_TSK_cleanup( this );
	cleanUpRelations();
}

void WST_TSK::endDispatching(){
	WST_OSW_TSK_cleanup(this);
}


void WST_TSK::suspend(){
	WST_OSW_TSK_suspend( this );
}


void WST_TSK::resume(){
	WST_OSW_TSK_resume( this );
}

void WST_TSK::startDispatching( void ) {
	//#[ operation startDispatching()
	WST_OSW_TSK_start( this );
	//#]
}

void WST_TSK::execute( void ) {
	//#[ operation execute()
	WST_FSM::TakeEventStatus result = WST_FSM::WST_EVT_handleEventError;
	
	WST_EVT*    event;
	
	
	for ( ;; )
	{
		/* wait for an event to be available for the current task */
		#ifdef WST_LIVE_ANIMATION
		while(monitorStopFlag == WSTTRUE){
			WST_OSW_TMM_delay(10);
		}
		#endif /* of WST_LIVE_ANIMATION */
		event = messageQueue.get();
		
		/* User defined hook before event consumption */
		WST_PRE_EVENT_CONSUMPTION_HOOK
	
		if ( event != NULL )
		{
    		if( event->getId() != WST_TMR_delete_id )
            {
    			if( event->getDestination() == NULL )
    			{
        			WST_ERR::error( WST_ERR::WST_ERR_NULL_DESTINATION, 0u );
        		}
        		else
    	        {
    	            /* find out who needs to receive it and send it them */
    	            result = event->getDestination()->takeEvent(event);    
    			}
            }
    
            /* If the Event was dynamic, return its memory to the memory pools */

			if ( event->getIsStatic() == false )
			{
				delete event;
			}

	
			/*
			 * Check if the statechart is finished. The Object must be destroyed then.
			 */
			if (result == WST_FSM::WST_EVT_handleEventReachTerminate)
			{
				delete this;
			}
		}
		/* User defined hook after event consumption */
		WST_POST_EVENT_CONSUMPTION_HOOK
		
	} /* end of for(;;) */
	
	//#]
}

void WST_TSK::executeOnce( void ) {
	//#[ operation executeOnce()
	WST_FSM::TakeEventStatus result = WST_FSM::WST_EVT_handleEventError;
	
	WST_EVT* event = messageQueue.get();
	
	if ( event != NULL )
	{
		/* User defined hook before event consumption */
		WST_PRE_EVENT_CONSUMPTION_HOOK
		
    	if( event->getId() != WST_TMR_delete_id )
        {
    		if( event->getDestination() == NULL )
    		{
    			WST_ERR::error( WST_ERR::WST_ERR_NULL_DESTINATION, 0u );
    		}
    		else
            {
                /* find out who needs to receive it and send it them */
                result = event->getDestination()->takeEvent(event);
    
    
    		}
        }
    
		/* If the Event was dynamic, return its memory to the memory pools */
		if ( event->getIsStatic() == false )
		{
			delete event;
		}

		/*
		 * Check if the statechart is finished. The Object must be destroyed then.
		 */
		if (result == WST_FSM::WST_EVT_handleEventReachTerminate)
		{
			delete this;
		}
		
		/* User defined hook after event consumption */
		WST_POST_EVENT_CONSUMPTION_HOOK
	}  
	
	//#]
}

void WST_TSK::task_start(void * myTask) {
	//#[ operation task_start(void *)
	((WST_TSK *) myTask) -> execute();
	
	//#]
}

void WST_TSK::startTaskAfterOSStart() {
	//#[ operation task_start(void *)
	WST_OSW_MSQ_init( &this->messageQueue );
	if( this != &theMainTask )
	{
		WST_OSW_TSK_init( this  );
	}
	//#]
}

void WST_TSK::cleanUpRelations( void ) {
	messageQueue = NULL;
}

/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_TSK.cpp
*********************************************************************/
