/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: TargetComponent 
	Configuration 	: Debug
	Model Element	: LED
//!	Generated Date	: Wed, 3, May 2017  
	File Path	: TargetComponent\Debug\LED.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "LED.h"
//## auto_generated
#include <lpc17xx.h>
//## package ExamplePkg

//## class LED
LED::LED(int aBitArg, WST_TSK* myTask) {
    setTask( myTask, false );
    initStatechart();
    //#[ operation LED(int)
    /* Init */
    
    if( aBitArg == 0 )
    {              
    	LPC_GPIO1->FIODIR |=  (1<<28);
    }
    else if ( aBitArg == 1)
    {               
    	LPC_GPIO1->FIODIR |=  (1<<29);
    }       
    else
    {
    	LPC_GPIO1->FIODIR |=  (1<<31);
    }
    
    bitIndicator = aBitArg;
    
    this->setOwner( this );
    WSTMonitor_sendInit( this, 103, (void*)&bitIndicator);
    
    //#]
}

LED::LED(WST_TSK* myTask) {
    setTask( myTask, false );
    initStatechart();
    this->setOwner( this );
    WSTMonitor_sendInit( this, 103, (void*)&bitIndicator);
    
}

LED::~LED() {
    
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

void LED::off() {
    //#[ operation off()
    /* switch off */
    if( bitIndicator == 0 )
    {              
    	LPC_GPIO1->FIOPIN &= ~(1<<28);
    }
    else
    {               
    	LPC_GPIO1->FIOPIN &= ~(1<<29);
    }
    //#]
}

void LED::on() {
    //#[ operation on()
    /* switch on */
    if( bitIndicator == 0 )
    {              
    	LPC_GPIO1->FIOPIN |=  (1<<28);
    }
    else
    {               
    	LPC_GPIO1->FIOPIN |=  (1<<29);
    }
    //#]
}

bool LED::startBehavior() {
    bool done = false;
    done = WST_FSM::startBehavior();
    return done;
}

void LED::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
}

int LED::getBitIndicator() const {
    return bitIndicator;
}

void LED::setBitIndicator(int p_bitIndicator) {
    bitIndicator = p_bitIndicator;
}

void LED::rootState_entDef() {
    {
        rootState_subState = Off;
        rootState_active = Off;
        //#[ state Off.(Entry) 
        off();
        //#]
    }
}

IOxfReactive::TakeEventStatus LED::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State Off
        case Off:
        {
            if(IS_EVENT_TYPE_OF(evToggle_ExamplePkg_id))
                {
                    rootState_subState = On;
                    rootState_active = On;
                    //#[ state On.(Entry) 
                    on();
                    //#]
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(evOn_ExamplePkg_id))
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
            if(IS_EVENT_TYPE_OF(evToggle_ExamplePkg_id))
                {
                    rootState_subState = Off;
                    rootState_active = Off;
                    //#[ state Off.(Entry) 
                    off();
                    //#]
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(evOff_ExamplePkg_id))
                {
                    rootState_subState = Off;
                    rootState_active = Off;
                    //#[ state Off.(Entry) 
                    off();
                    //#]
                    res = eventConsumed;
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
	File Path	: TargetComponent\Debug\LED.cpp
*********************************************************************/
