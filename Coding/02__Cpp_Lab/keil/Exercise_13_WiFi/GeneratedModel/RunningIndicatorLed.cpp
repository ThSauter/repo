/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: RunningIndicatorLed
//!	Generated Date	: Thu, 3, Aug 2017  
	File Path	: MCB1700\Debug\RunningIndicatorLed.cpp
*********************************************************************/

//## auto_generated
#include "RunningIndicatorLed.h"
//## link itsLed
#include "Led.h"
//## package DefaultPkg

//## class RunningIndicatorLed
RunningIndicatorLed::RunningIndicatorLed(WST_TSK* myTask) {
    setTask( this, true );
    itsLed = NULL;
    initStatechart();
    this->setOwner( this );
    WSTMonitor_sendInit( this, 101, (void*)&itsLed);
    
}

RunningIndicatorLed::~RunningIndicatorLed() {
    cleanUpRelations();
    cancelTimeouts();
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

Led* RunningIndicatorLed::getItsLed() const {
    return itsLed;
}

void RunningIndicatorLed::setItsLed(Led* p_Led) {
    itsLed = p_Led;
}

bool RunningIndicatorLed::startBehavior() {
    bool done = false;
    done = WST_FSM::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void RunningIndicatorLed::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void RunningIndicatorLed::cleanUpRelations() {
    if(itsLed != NULL)
        {
            itsLed = NULL;
        }
}

void RunningIndicatorLed::cancelTimeouts() {
    cancel(rootState_timeout);
}

bool RunningIndicatorLed::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

uint16 RunningIndicatorLed::ClassWSTMonitor_getTypeSize1() {
    return sizeof( int );
}

void RunningIndicatorLed::rootState_entDef() {
    {
        rootState_subState = Off;
        rootState_active = Off;
        //#[ state Off.(Entry) 
        FIRE(this->itsLed, evOff() );
        //#]
        rootState_timeout = scheduleTimeout(500, NULL);
    }
}

IOxfReactive::TakeEventStatus RunningIndicatorLed::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State Off
        case Off:
        {
            if(IS_EVENT_TYPE_OF(WST_TMR_id))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            cancel(rootState_timeout);
                            rootState_subState = On;
                            rootState_active = On;
                            //#[ state On.(Entry) 
                            FIRE(this->itsLed, evOn() );
                            //#]
                            rootState_timeout = scheduleTimeout(500, NULL);
                            res = eventConsumed;
                        }
                }
            
        }
        break;
        // State On
        case On:
        {
            if(IS_EVENT_TYPE_OF(WST_TMR_id))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            cancel(rootState_timeout);
                            rootState_subState = Off;
                            rootState_active = Off;
                            //#[ state Off.(Entry) 
                            FIRE(this->itsLed, evOff() );
                            //#]
                            rootState_timeout = scheduleTimeout(500, NULL);
                            res = eventConsumed;
                        }
                }
            
        }
        break;
        default:
            break;
    }
    this->activeState[ 0 ] = rootState_active;
    return res;
}

uint16 WSTMonitor_getTypeSize1() {
    return RunningIndicatorLed::ClassWSTMonitor_getTypeSize1( );
}

/*********************************************************************
	File Path	: MCB1700\Debug\RunningIndicatorLed.cpp
*********************************************************************/
