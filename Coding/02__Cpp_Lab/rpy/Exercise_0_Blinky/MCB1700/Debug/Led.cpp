/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Led
//!	Generated Date	: Mon, 3, Apr 2017  
	File Path	: MCB1700\Debug\Led.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "Led.h"
//## package Default

//## class Led
Led::Led(int aBitNr, int aDelay, WST_TSK* myTask) {
    setTask( myTask, false );
    initStatechart();
    //#[ operation Led(int,int)
    bitNr = aBitNr;
    delay = aDelay;
    
    LPC_GPIO1 -> FIODIR |= 0xB0000000;
    LPC_GPIO2 -> FIODIR |= 0x0000007C;
    //#]
}

Led::Led(WST_TSK* myTask) {
    setTask( myTask, false );
    initStatechart();
}

Led::~Led() {
    cancelTimeouts();
}

void Led::off() {
    //#[ operation off()
    LPC_GPIO2->FIOCLR |= (1 << bitNr);
    //#]
}

void Led::on() {
    //#[ operation on()
    LPC_GPIO2->FIOSET |= (1 << bitNr);
    //#]
}

bool Led::startBehavior() {
    bool done = false;
    done = WST_FSM::startBehavior();
    return done;
}

void Led::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void Led::cancelTimeouts() {
    cancel(rootState_timeout);
}

bool Led::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

int Led::getBitNr() const {
    return bitNr;
}

void Led::setBitNr(int p_bitNr) {
    bitNr = p_bitNr;
}

int Led::getDelay() const {
    return delay;
}

void Led::setDelay(int p_delay) {
    delay = p_delay;
}

void Led::rootState_entDef() {
    {
        rootState_subState = State_off;
        rootState_active = State_off;
        //#[ state State_off.(Entry) 
        off();
        //#]
        rootState_timeout = scheduleTimeout(delay, NULL);
    }
}

IOxfReactive::TakeEventStatus Led::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State State_off
        case State_off:
        {
            if(IS_EVENT_TYPE_OF(WST_TMR_id))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            cancel(rootState_timeout);
                            rootState_subState = State_on;
                            rootState_active = State_on;
                            //#[ state State_on.(Entry) 
                            on();
                            //#]
                            rootState_timeout = scheduleTimeout(delay, NULL);
                            res = eventConsumed;
                        }
                }
            
        }
        break;
        // State State_on
        case State_on:
        {
            if(IS_EVENT_TYPE_OF(WST_TMR_id))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            cancel(rootState_timeout);
                            rootState_subState = State_off;
                            rootState_active = State_off;
                            //#[ state State_off.(Entry) 
                            off();
                            //#]
                            rootState_timeout = scheduleTimeout(delay, NULL);
                            res = eventConsumed;
                        }
                }
            
        }
        break;
        default:
            break;
    }
    return res;
}

/*********************************************************************
	File Path	: MCB1700\Debug\Led.cpp
*********************************************************************/
