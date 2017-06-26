/********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_MSQ
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MSQ.cpp
*********************************************************************/

//## auto_generated
#include "WST_MSQ.h"
//## operation get()
#include "WST_EVT.h"
//## operation cancelEvents(WST_FSM,WST_EVT_ID_t)
#include "WST_FSM.h"
//## auto_generated
#include "WST.h"
//## package RXF::RXF_BehaviorPkg

//## class WST_MSQ



WST_MSQ::WST_MSQ( uint16 size, WSTBoolean osStarted ) {
	initSize = size;
    //#[ operation WST_MSQ()
	rtosMsgBuffer = NULL;
	if( osStarted != FALSE ){
		WST_OSW_MSQ_init(  this ); 
	}
    //#]
}

WST_MSQ::WST_MSQ( uint16 size, void* msq, WSTBoolean osStarted ) {
	initSize = size;
	rtosMsgBuffer = msq;
    //#[ operation WST_MSQ()
	if( osStarted != FALSE ){
		WST_OSW_MSQ_init(  this ); 
    }       
    //#]
}

WST_MSQ::~WST_MSQ( void ) {
	WST_MEM::returnMemory(  rtosMsgBuffer );
}

void WST_MSQ::cancelEvents(WST_FSM* destination, const WST_EVT_ID_t id) {
    //#[ operation cancelEvents(WST_FSM,WST_EVT_ID_t)
    WST_OSW_MSQ_cancelEvents( this, destination, id);
    //#]
}

WST_EVT* WST_MSQ::get( void ) {
    //#[ operation get()
    WST_EVT* event;
    
    WST_OSW_MSQ_get( this, &event );
    
    return event;
    //#]
}

WSTBoolean WST_MSQ::isEmpty( void ) {
    //#[ operation isEmpty()
    return ( WST_OSW_MSQ_getCount( this ) == 0 );
    //#]
}

void WST_MSQ::put(WST_EVT* event, WSTBoolean fromISR) {
    //#[ operation put(WST_EVT)

#ifdef WST_LIVE_ANIMATION

	if (event->getId() == WST_TMR_id)
	{
		if (monitorTimeoutEnableFlag == 1)
		{
			WSTMonitorTimeoutEvent monitorTimeoutEvent;
			WSTMonitorEventID++;
			event->setEventID(WSTMonitorEventID);
			monitorTimeoutEvent.eventID = WSTMonitorEventID;
			monitorTimeoutEvent.destination = event->getDestination()->getOwner(); /* source is not filled in those events but same as destination */
			monitorTimeoutEvent.currentTick = WSTRTOS_getRxfTicks();
			WSTMonitor_sendTimeOut((uint8*)&monitorTimeoutEvent);
		}
	}
	else
	{
		uint8* eventArgument;
		WSTMonitorEventCreate monitorEventCreate;

		eventArgument = (uint8*)(event + 1);
		WSTMonitorEventID++;
		event->setEventID(WSTMonitorEventID);
		monitorEventCreate.eventID = WSTMonitorEventID;
		monitorEventCreate.source = event->getSource();
		monitorEventCreate.destination = event->getDestination()->getOwner();
		monitorEventCreate.id = event->getId();
		monitorEventCreate.currentTick = WSTRTOS_getRxfTicks();

		WSTMonitor_sendEventCreate((uint8*)&monitorEventCreate, event->getSize(), eventArgument);
	}

#endif /* WST_LIVE_ANIMATION */
    WST_OSW_MSQ_put( this, event, fromISR );  
    //#]
}



/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MSQ.cpp
*********************************************************************/
