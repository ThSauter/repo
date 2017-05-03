/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: TargetComponent 
	Configuration 	: Debug
	Model Element	: SequentialController
//!	Generated Date	: Wed, 3, May 2017  
	File Path	: TargetComponent\Debug\SequentialController.cpp
*********************************************************************/

//## auto_generated
#include "SequentialController.h"
//## link itsLED
#include "LED.h"
//## package ExamplePkg

//## class SequentialController
SequentialController::SequentialController(WST_TSK* myTask) {
    setTask( this, true );
    itsLED = NULL;
    initStatechart();
    this->setOwner( this );
    WSTMonitor_sendInit( this, 102, (void*)&itsLED);
    
}

SequentialController::~SequentialController() {
    cleanUpRelations();
    cancelTimeouts();
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

LED* SequentialController::getItsLED() const {
    return itsLED;
}

void SequentialController::setItsLED(LED* p_LED) {
    itsLED = p_LED;
}

bool SequentialController::startBehavior() {
    bool done = false;
    done = WST_FSM::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void SequentialController::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void SequentialController::cleanUpRelations() {
    if(itsLED != NULL)
        {
            itsLED = NULL;
        }
}

void SequentialController::cancelTimeouts() {
    cancel(rootState_timeout);
}

bool SequentialController::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

void SequentialController::rootState_entDef() {
    {
        rootState_subState = Off;
        rootState_active = Off;
        //#[ state Off.(Entry) 
        FIRE(this->itsLED, evOff() );
        //#]
        rootState_timeout = scheduleTimeout(500, NULL);
    }
}

IOxfReactive::TakeEventStatus SequentialController::rootState_processEvent() {
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
                            FIRE(this->itsLED, evOn() );
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
                            FIRE(this->itsLED, evOff() );
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

/*********************************************************************
	File Path	: TargetComponent\Debug\SequentialController.cpp
*********************************************************************/
