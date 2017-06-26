/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Joystick
//!	Generated Date	: Tue, 23, May 2017  
	File Path	: MCB1700\Debug\Joystick.cpp
*********************************************************************/

//## auto_generated
#include "Joystick.h"
//## link itsEthernetTransmitter
#include "EthernetTransmitter.h"
//## auto_generated
#include <lpc17xx.h>
//## package DefaultPkg

//## class Joystick
Joystick::Joystick(WST_TSK* myTask) {
    setTask( this, true );
    itsEthernetTransmitter = NULL;
    initStatechart();
    //#[ operation Joystick()
    LPC_GPIO1->FIODIR&= ~((1UL<<20)|(1UL<<23)|
    (1UL<<24)| (1UL<<25)| (1UL<<26));
    /* Port P1.20 and 1.23 to 1.26 is input (Joystick)*/
    
    sampleTime = 100;
    this->setOwner( this );
    WSTMonitor_sendInit( this, 107, (void*)&lastPosition);
    
    //#]
}

Joystick::~Joystick() {
    cleanUpRelations();
    cancelTimeouts();
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

void Joystick::sample() {
    //#[ operation sample()
    int position = (LPC_GPIO1->FIOPIN >> 20) & Joystick_Mask ;
    
    // Bit 4-7 contain the position information
    position = position >> 3; 
    
    if (position == Joystick_CENTER)
    {   
    	// Only update the position in case the Joystick got back to the center
        lastPosition = position;  
    }
    else if (position != lastPosition)
    {
    	lastPosition = position;    	
    	FIRE( this->itsEthernetTransmitter, evNewJoystickPosition(position)); 
    } 
      
    //#]
}

int Joystick::getLastPosition() const {
    return lastPosition;
}

void Joystick::setLastPosition(int p_lastPosition) {
    lastPosition = p_lastPosition;
}

int Joystick::getSampleTime() const {
    return sampleTime;
}

void Joystick::setSampleTime(int p_sampleTime) {
    sampleTime = p_sampleTime;
}

EthernetTransmitter* Joystick::getItsEthernetTransmitter() const {
    return itsEthernetTransmitter;
}

void Joystick::setItsEthernetTransmitter(EthernetTransmitter* p_EthernetTransmitter) {
    itsEthernetTransmitter = p_EthernetTransmitter;
}

bool Joystick::startBehavior() {
    bool done = false;
    done = WST_FSM::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void Joystick::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void Joystick::cleanUpRelations() {
    if(itsEthernetTransmitter != NULL)
        {
            itsEthernetTransmitter = NULL;
        }
}

void Joystick::cancelTimeouts() {
    cancel(rootState_timeout);
}

bool Joystick::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

void Joystick::rootState_entDef() {
    {
        pushNullTransition();
        rootState_subState = Sample;
        rootState_active = Sample;
        //#[ state Sample.(Entry) 
        sample();
        //#]
    }
}

IOxfReactive::TakeEventStatus Joystick::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State Sample
        case Sample:
        {
            if(IS_EVENT_TYPE_OF(WST_EVT_null_id ))
                {
                    popNullTransition();
                    rootState_subState = Hold;
                    rootState_active = Hold;
                    rootState_timeout = scheduleTimeout(sampleTime, NULL);
                    res = eventConsumed;
                }
            
        }
        break;
        // State Hold
        case Hold:
        {
            if(IS_EVENT_TYPE_OF(WST_TMR_id))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            cancel(rootState_timeout);
                            pushNullTransition();
                            rootState_subState = Sample;
                            rootState_active = Sample;
                            //#[ state Sample.(Entry) 
                            sample();
                            //#]
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
	File Path	: MCB1700\Debug\Joystick.cpp
*********************************************************************/
