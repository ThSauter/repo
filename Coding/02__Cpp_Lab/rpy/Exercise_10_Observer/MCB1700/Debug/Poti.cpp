/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Poti
//!	Generated Date	: Fri, 14, Apr 2017  
	File Path	: MCB1700\Debug\Poti.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "Poti.h"
//## auto_generated
#include "PotiObserver.h"
//## package Default

//## class Poti
Poti::Poti(WST_TSK* myTask) {
    setTask( myTask, false );
    initStatechart();
    //#[ operation Poti()
    // Initialize Poti (page 574)
    LPC_PINCON->PINSEL1 &= ~(3<<18);	// P0.25 is GPIO - Reset (page 108)
    LPC_PINCON->PINSEL1 |= (1<<18);		// P0.25 is AD0.2 - Function 01 (page 108)
    //#]
}

Poti::~Poti() {
    cancelTimeouts();
}

int Poti::getAdcValue() {
    //#[ operation getAdcValue()
    return adcValue;
    //#]
}

void Poti::samplePoti() {
    //#[ operation samplePoti()
    LPC_SC->PCONP |= (1<<12);			// Enable power ADC block (page 63)
    LPC_ADC->ADCR = (1<<2) | 			// Select AD0.2 pin (page 577)
    				(4<<8) |			// ADC clock is 25MHz/5 (page 577)          
    				(1<<21); 			// Enable ADC (page 577)
    
    LPC_ADC->ADCR |= 0x01200000; 				// Start A/D conversion now (page 577)
    do{
    	adcValue = LPC_ADC->ADDR2; 				// Read A/D Data Register into potiVal (page 579)
    }while((LPC_ADC->ADGDR & 0x80000000) == 0); // Wait unitl A/D conversion completes (page 578)
    
    LPC_ADC->ADCR &= ~0x01000000; 				// Stop A/D Conversion (page 577)
    adcValue = (adcValue >> 4) & 0x0FFF; 		// Extract result (page 579)    
                    
    potiVal = (900 * adcValue / ADC_FullRangeDeflection) + 100;
                   
    // Only notify in case of changes
    if (_lastPotiVal != potiVal)
    {         
    	_lastPotiVal = potiVal;
    	notify();
    }
    
    //#]
}

int Poti::getPotiVal() const {
    return potiVal;
}

void Poti::setPotiVal(int p_potiVal) {
    potiVal = p_potiVal;
}

bool Poti::startBehavior() {
    bool done = false;
    done = WST_FSM::startBehavior();
    return done;
}

void Poti::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void Poti::cancelTimeouts() {
    cancel(rootState_timeout);
}

bool Poti::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

int Poti::get_lastPotiVal() const {
    return _lastPotiVal;
}

void Poti::set_lastPotiVal(int p__lastPotiVal) {
    _lastPotiVal = p__lastPotiVal;
}

void Poti::setAdcValue(int p_adcValue) {
    adcValue = p_adcValue;
}

void Poti::rootState_entDef() {
    {
        pushNullTransition();
        rootState_subState = Sample;
        rootState_active = Sample;
        //#[ state Sample.(Entry) 
        samplePoti();
        //#]
    }
}

IOxfReactive::TakeEventStatus Poti::rootState_processEvent() {
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
                    rootState_timeout = scheduleTimeout(100, NULL);
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
                            samplePoti();
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
	File Path	: MCB1700\Debug\Poti.cpp
*********************************************************************/
