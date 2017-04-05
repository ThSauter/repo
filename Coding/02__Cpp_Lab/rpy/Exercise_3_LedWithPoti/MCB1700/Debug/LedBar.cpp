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
                      
    // Initialize LedBar
    LPC_GPIO1 -> FIODIR |= 0xB0000000;
    LPC_GPIO2 -> FIODIR |= 0x0000007C;      
                     
    // Initialize Poti (page 574)
    LPC_PINCON->PINSEL1 &= ~(3<<18);	// P0.25 is GPIO - Reset (page 108)
    LPC_PINCON->PINSEL1 |= (1<<18);		// P0.25 is AD0.2 - Function 01 (page 108)
    
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

void LedBar::samplePoti() {
    //#[ operation samplePoti()
    LPC_SC->PCONP |= (1<<12);			// Enable power ADC block (page 63)
    LPC_ADC->ADCR = (1<<2) | 			// Select AD0.2 pin (page 577)
    				(4<<8) |			// ADC clock is 25MHz/5 (page 577)          
    				(1<<21); 			// Enable ADC (page 577)
    
    LPC_ADC->ADCR |= 0x01200000; 				// Start A/D conversion now (page 577)
    do{
    	potiVal = LPC_ADC->ADDR2; 				// Read A/D Data Register into potiVal (page 579)
    }while((LPC_ADC->ADGDR & 0x80000000) == 0); // Wait unitl A/D conversion completes (page 578)
    
    LPC_ADC->ADCR &= ~0x01000000; 				// Stop A/D Conversion (page 577)
    delay = (potiVal >> 8) & 0x03FF; 			// Extract result (page 579)    
           
    // To ensure any value
    if (delay == 0)	delay = 1000;
    
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

int LedBar::getPotiVal() const {
    return potiVal;
}

void LedBar::setPotiVal(int p_potiVal) {
    potiVal = p_potiVal;
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
        samplePoti();
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
                            cancel(rootState_timeout);
                            pushNullTransition();
                            rootState_subState = State_off;
                            rootState_active = State_off;
                            //#[ state State_off.(Entry) 
                            samplePoti();
                            off();      
                            //#]
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
	File Path	: MCB1700\Debug\LedBar.cpp
*********************************************************************/
