/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: LedBar
//!	Generated Date	: Mon, 3, Apr 2017  
	File Path	: MCB1700\Debug\LedBar.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "LedBar.h"
//## package Default

//## class LedBar
LedBar::LedBar(int aBitNr, int aDelay, WST_TSK* myTask) {
    setTask( myTask, false );
    initStatechart();
    //#[ operation LedBar(int,int)
    bitNr = aBitNr;
    delay = aDelay;
    
    LPC_GPIO1 -> FIODIR |= 0xB0000000;
    LPC_GPIO2 -> FIODIR |= 0x0000007C;
    //#]
}

LedBar::LedBar(WST_TSK* myTask) {
    setTask( myTask, false );
    initStatechart();
}

LedBar::~LedBar() {
    cancelTimeouts();
}

void LedBar::off() {
    //#[ operation off()
    LPC_GPIO2->FIOCLR |= (1 << bitNr);
    //#]
}

void LedBar::on() {
    //#[ operation on()
    LPC_GPIO2->FIOSET |= (1 << bitNr);
    //#]
}

int LedBar::getBitNr() const {
    return bitNr;
}

void LedBar::setBitNr(int p_bitNr) {
    bitNr = p_bitNr;
}

int LedBar::getDelay() const {
    return delay;
}

void LedBar::setDelay(int p_delay) {
    delay = p_delay;
}

bool LedBar::startBehavior() {
    bool done = false;
    done = WST_FSM::startBehavior();
    return done;
}

void LedBar::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void LedBar::cancelTimeouts() {
    cancel(rootState_timeout);
}

bool LedBar::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

void LedBar::rootState_entDef() {
    {
        pushNullTransition();
        rootState_subState = State_off;
        rootState_active = State_off;
        //#[ state State_off.(Entry) 
        off();      
        //#]
    }
}

IOxfReactive::TakeEventStatus LedBar::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State State_off
        case State_off:
        {
            if(IS_EVENT_TYPE_OF(WST_EVT_null_id ))
                {
                    //## transition 3 
                    if(bitNr == 6)
                        {
                            popNullTransition();
                            //#[ transition 3 
                            bitNr = 2;    
                            delay += 100;
                            //#]
                            rootState_subState = State_on;
                            rootState_active = State_on;
                            //#[ state State_on.(Entry) 
                            on();
                            //#]
                            rootState_timeout = scheduleTimeout(delay, NULL);
                            res = eventConsumed;
                        }
                    else
                        {
                            popNullTransition();
                            //#[ transition 4 
                            bitNr++;
                            //#]
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
                            //## transition 6 
                            if(delay == 1000)
                                {
                                    cancel(rootState_timeout);
                                    //#[ transition 6 
                                    delay = 100;
                                    //#]
                                    pushNullTransition();
                                    rootState_subState = State_off;
                                    rootState_active = State_off;
                                    //#[ state State_off.(Entry) 
                                    off();      
                                    //#]
                                    res = eventConsumed;
                                }
                            else
                                {
                                    cancel(rootState_timeout);
                                    pushNullTransition();
                                    rootState_subState = State_off;
                                    rootState_active = State_off;
                                    //#[ state State_off.(Entry) 
                                    off();      
                                    //#]
                                    res = eventConsumed;
                                }
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
	File Path	: MCB1700\Debug\LedBar.cpp
*********************************************************************/
