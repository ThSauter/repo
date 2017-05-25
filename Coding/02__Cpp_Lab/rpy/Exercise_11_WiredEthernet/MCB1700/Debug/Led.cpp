/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Led
//!	Generated Date	: Wed, 17, May 2017  
	File Path	: MCB1700\Debug\Led.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "Led.h"
//## auto_generated
#include <lpc17xx.h>
//## package DefaultPkg

//## class Led
Led::Led(int aBitArg, WST_TSK* myTask) {
    blinkTimeoutMs = 100;
    setTask( myTask, false );
    initStatechart();
    //#[ operation Led(int)
    // Init
    switch (aBitArg)
    {
    	case 0: 
    		LPC_GPIO1->FIODIR |=  (1U<<28);
    		break;   
    	case 1:
    		LPC_GPIO1->FIODIR |=  (1U<<29);   
    		break;
    	case 2: 
    		LPC_GPIO1->FIODIR |=  (1U<<31);   
    		break;	      
    	case 3:
    	case 4:
    	case 5:
    	case 6:
    		LPC_GPIO2->FIODIR |= (1 << bitIndicator);
    		break;
    }         
    
    bitIndicator = aBitArg; 
    
    
    
    this->setOwner( this );
    WSTMonitor_sendInit( this, 104, (void*)&bitIndicator);
    
    //#]
}

Led::Led(WST_TSK* myTask) {
    blinkTimeoutMs = 100;
    setTask( myTask, false );
    initStatechart();
    //#[ operation Led()
    LPC_GPIO2 -> FIODIR |= 0x0000007C;
    this->setOwner( this );
    WSTMonitor_sendInit( this, 104, (void*)&bitIndicator);
    
    //#]
}

Led::~Led() {
    cancelTimeouts();
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

void Led::off() {
    //#[ operation off()
    // switch off 
    switch (bitIndicator)
    {
    	case 0: 
    		LPC_GPIO1->FIOPIN &= ~ (1U<<28);
    		break;   
    	case 1:
    		LPC_GPIO1->FIOPIN &= ~ (1U<<29);   
    		break;
    	case 2: 
    		LPC_GPIO1->FIOPIN &= ~ (1U<<31);   
    		break;	      
    	case 3:
    	case 4:
    	case 5:
    	case 6:
    		LPC_GPIO2->FIOCLR |= (1 << bitIndicator);
    		break;
    }
    //#]
}

void Led::on() {
    //#[ operation on()
    // switch on 
    switch (bitIndicator)
    {
    	case 0: 
    		LPC_GPIO1->FIOPIN |=  (1U<<28);
    		break;   
    	case 1:
    		LPC_GPIO1->FIOPIN |=  (1U<<29);   
    		break;
    	case 2: 
    		LPC_GPIO1->FIOPIN |=  (1U<<31);   
    		break;	      
    	case 3:
    	case 4:
    	case 5:
    	case 6:
    		LPC_GPIO2->FIOSET |= (1 << bitIndicator);
    		break;
    }
    //#]
}

int Led::getBitIndicator() const {
    return bitIndicator;
}

void Led::setBitIndicator(int p_bitIndicator) {
    bitIndicator = p_bitIndicator;
}

int Led::getBlinkTimeoutMs() const {
    return blinkTimeoutMs;
}

void Led::setBlinkTimeoutMs(int p_blinkTimeoutMs) {
    blinkTimeoutMs = p_blinkTimeoutMs;
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

void Led::rootState_entDef() {
    {
        rootState_subState = Off;
        rootState_active = Off;
        //#[ state Off.(Entry) 
        off();
        //#]
    }
}

IOxfReactive::TakeEventStatus Led::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State Off
        case Off:
        {
            if(IS_EVENT_TYPE_OF(evToggle_DefaultPkg_id))
                {
                    rootState_subState = On;
                    rootState_active = On;
                    //#[ state On.(Entry) 
                    on();
                    //#]
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(evBlink_DefaultPkg_id))
                {
                    rootState_subState = BlinkOn;
                    rootState_active = BlinkOn;
                    //#[ state BlinkOn.(Entry) 
                    on();
                    //#]
                    rootState_timeout = scheduleTimeout(blinkTimeoutMs, NULL);
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(evOn_DefaultPkg_id))
                {
                    rootState_subState = On;
                    rootState_active = On;
                    //#[ state On.(Entry) 
                    on();
                    //#]
                    res = eventConsumed;
                }
            
        }
        break;
        // State On
        case On:
        {
            if(IS_EVENT_TYPE_OF(evToggle_DefaultPkg_id))
                {
                    rootState_subState = Off;
                    rootState_active = Off;
                    //#[ state Off.(Entry) 
                    off();
                    //#]
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(evOff_DefaultPkg_id))
                {
                    rootState_subState = Off;
                    rootState_active = Off;
                    //#[ state Off.(Entry) 
                    off();
                    //#]
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(evBlink_DefaultPkg_id))
                {
                    rootState_subState = BlinkOff;
                    rootState_active = BlinkOff;
                    //#[ state BlinkOff.(Entry) 
                    off();
                    //#]
                    rootState_timeout = scheduleTimeout(blinkTimeoutMs, NULL);
                    res = eventConsumed;
                }
            
        }
        break;
        // State BlinkOn
        case BlinkOn:
        {
            if(IS_EVENT_TYPE_OF(WST_TMR_id))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            cancel(rootState_timeout);
                            rootState_subState = Off;
                            rootState_active = Off;
                            //#[ state Off.(Entry) 
                            off();
                            //#]
                            res = eventConsumed;
                        }
                }
            
        }
        break;
        // State BlinkOff
        case BlinkOff:
        {
            if(IS_EVENT_TYPE_OF(WST_TMR_id))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            cancel(rootState_timeout);
                            rootState_subState = On;
                            rootState_active = On;
                            //#[ state On.(Entry) 
                            on();
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
	File Path	: MCB1700\Debug\Led.cpp
*********************************************************************/
