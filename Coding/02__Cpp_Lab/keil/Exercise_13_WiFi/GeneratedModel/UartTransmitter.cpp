/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: UartTransmitter
//!	Generated Date	: Thu, 3, Aug 2017  
	File Path	: MCB1700\Debug\UartTransmitter.cpp
*********************************************************************/

//## auto_generated
#include "UartTransmitter.h"
//## link itsLed
#include "Led.h"
//## package DefaultPkg

//## class UartTransmitter
UartTransmitter::UartTransmitter(WST_TSK* myTask) {
    setTask( this, true );
    itsLed = NULL;
    initStatechart();
    this->setOwner( this );
    WSTMonitor_sendInit( this, 109, (void*)&itsLed);
    
}

UartTransmitter::~UartTransmitter() {
    cleanUpRelations();
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

void UartTransmitter::transmitData() {
    //#[ operation transmitData()
    if (dbuf == 0x00)
    {   
    	// In case of any invalid joystick position
    	dbuf = 0xFF;
    }    
    
    txChar(dbuf);
    
    // The led toggles when data is sent   
    FIRE(this->itsLed, evBlink());
    //#]
}

Led* UartTransmitter::getItsLed() const {
    return itsLed;
}

void UartTransmitter::setItsLed(Led* p_Led) {
    itsLed = p_Led;
}

bool UartTransmitter::startBehavior() {
    bool done = false;
    done = WST_FSM::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void UartTransmitter::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
}

void UartTransmitter::cleanUpRelations() {
    if(itsLed != NULL)
        {
            itsLed = NULL;
        }
}

void UartTransmitter::rootState_entDef() {
    {
        rootState_subState = state_0;
        rootState_active = state_0;
        //#[ state state_0.(Entry) 
        transmitData();
        //#]
    }
}

IOxfReactive::TakeEventStatus UartTransmitter::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State state_0
    if(rootState_active == state_0)
        {
            if(IS_EVENT_TYPE_OF(evNewJoystickPosition_DefaultPkg_id))
                {
                    OMSETPARAMS(evNewJoystickPosition);
                    //#[ transition 1 
                    dbuf = params->joystickPosition;
                    //#]
                    rootState_subState = state_0;
                    rootState_active = state_0;
                    //#[ state state_0.(Entry) 
                    transmitData();
                    //#]
                    res = eventConsumed;
                }
            
        }
    this->activeState[ 0 ] = rootState_active;
    return res;
}

/*********************************************************************
	File Path	: MCB1700\Debug\UartTransmitter.cpp
*********************************************************************/
