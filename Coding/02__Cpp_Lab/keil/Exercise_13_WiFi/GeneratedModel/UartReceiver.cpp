/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: UartReceiver
//!	Generated Date	: Thu, 3, Aug 2017  
	File Path	: MCB1700\Debug\UartReceiver.cpp
*********************************************************************/

//## auto_generated
#include "UartReceiver.h"
//## link itsDisplay
#include "Display.h"
//## link itsLed
#include "Led.h"
//## link itsLedBar
#include "LedBar.h"
//## package DefaultPkg

//## class UartReceiver
UartReceiver::UartReceiver(WST_TSK* myTask) {
    setTask( this, true );
    itsDisplay = NULL;
    itsLed = NULL;
    itsLedBar = NULL;
    initStatechart();
    this->setOwner( this );
    WSTMonitor_sendInit( this, 108, (void*)&itsDisplay);
    
}

UartReceiver::~UartReceiver() {
    cleanUpRelations();
    cancelTimeouts();
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

void UartReceiver::receiveData() {
    //#[ operation receiveData()
    dbuf = rxChar();
    
    if (dbuf != 0x00) {
    		
    		dbuf = ~dbuf & 0x0F;
    		
    	// Valid identifier, received Data
    	FIRE(this->itsLed, evBlink()); 
    	FIRE(this->itsLedBar, evReceivedData(dbuf));    
    	FIRE(this->itsDisplay, evReceivedData(dbuf)); 
    }
    //#]
}

Display* UartReceiver::getItsDisplay() const {
    return itsDisplay;
}

void UartReceiver::setItsDisplay(Display* p_Display) {
    itsDisplay = p_Display;
}

Led* UartReceiver::getItsLed() const {
    return itsLed;
}

void UartReceiver::setItsLed(Led* p_Led) {
    itsLed = p_Led;
}

LedBar* UartReceiver::getItsLedBar() const {
    return itsLedBar;
}

void UartReceiver::setItsLedBar(LedBar* p_LedBar) {
    itsLedBar = p_LedBar;
}

bool UartReceiver::startBehavior() {
    bool done = false;
    done = WST_FSM::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void UartReceiver::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void UartReceiver::cleanUpRelations() {
    if(itsDisplay != NULL)
        {
            itsDisplay = NULL;
        }
    if(itsLed != NULL)
        {
            itsLed = NULL;
        }
    if(itsLedBar != NULL)
        {
            itsLedBar = NULL;
        }
}

void UartReceiver::cancelTimeouts() {
    cancel(rootState_timeout);
}

bool UartReceiver::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

void UartReceiver::rootState_entDef() {
    {
        rootState_subState = state_0;
        rootState_active = state_0;
        //#[ state state_0.(Entry) 
        receiveData();
        //#]
        rootState_timeout = scheduleTimeout(100, NULL);
    }
}

IOxfReactive::TakeEventStatus UartReceiver::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State state_0
    if(rootState_active == state_0)
        {
            if(IS_EVENT_TYPE_OF(WST_TMR_id))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            cancel(rootState_timeout);
                            rootState_subState = state_0;
                            rootState_active = state_0;
                            //#[ state state_0.(Entry) 
                            receiveData();
                            //#]
                            rootState_timeout = scheduleTimeout(100, NULL);
                            res = eventConsumed;
                        }
                }
            
        }
    this->activeState[ 0 ] = rootState_active;
    return res;
}

/*********************************************************************
	File Path	: MCB1700\Debug\UartReceiver.cpp
*********************************************************************/
