/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Poti
//!	Generated Date	: Wed, 5, Apr 2017  
	File Path	: MCB1700\Debug\Poti.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "Poti.h"
//## link itsBoard
#include "Board.h"
//## package Default

//## class Poti
Poti::Poti(WST_TSK* myTask) : AdcFullRangeDeflection(4096-1) {
    setTask( myTask, false );
    itsBoard = NULL;
    initStatechart();
    //#[ operation Poti()
    //ADC initialization
    LPC_PINCON->PINSEL1 &= ~(3<<18);/*P0.25 is GPIO */
    LPC_PINCON->PINSEL1 |= (1<<18);/*P0.25 is AD0.2 */             
    
    sampleInterval = 10;
    //#]
}

Poti::~Poti() {
    cleanUpRelations();
    cancelTimeouts();
}

void Poti::sample() {
    //#[ operation sample()
    LPC_SC->PCONP |= (1<<12);/*Enable power ADC block */
    LPC_ADC->ADCR = (1<< 2) | /*select AD0.2 pin */
    				(4<< 8) | /*ADC clock is 25MHz/5 */
    				(1<<21); /* enable ADC */
    
    LPC_ADC->ADCR |= 0x01200000; /*Start A/D Conversion*/
    do{
    adcValue = LPC_ADC->ADDR2; /*Read A/D Data Register into val*/
    }while((LPC_ADC->ADGDR & 0x80000000) == 0); /*Wait for end of A/D Conversion */
    
    LPC_ADC->ADCR &= ~0x01000000; /*Stop A/D Conversion*/
    adcValue = (adcValue >> 4) & 0x0FFF; /* Extract value Conversion*/      
                                                 
    // Convert to 100
    potiValue = adcValue * 100 / AdcFullRangeDeflection; 
    
    //#]
}

int Poti::getAdcValue() const {
    return adcValue;
}

void Poti::setAdcValue(int p_adcValue) {
    adcValue = p_adcValue;
}

int Poti::getPotiValue() const {
    return potiValue;
}

void Poti::setPotiValue(int p_potiValue) {
    potiValue = p_potiValue;
}

int Poti::getSampleInterval() const {
    return sampleInterval;
}

void Poti::setSampleInterval(int p_sampleInterval) {
    sampleInterval = p_sampleInterval;
}

Board* Poti::getItsBoard() const {
    return itsBoard;
}

void Poti::setItsBoard(Board* p_Board) {
    _setItsBoard(p_Board);
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

void Poti::cleanUpRelations() {
    if(itsBoard != NULL)
        {
            itsBoard = NULL;
        }
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

int Poti::getAdcFullRangeDeflection() const {
    return AdcFullRangeDeflection;
}

void Poti::setAdcFullRangeDeflection(int p_AdcFullRangeDeflection) {
    AdcFullRangeDeflection = p_AdcFullRangeDeflection;
}

int Poti::getLastPotiValue() const {
    return lastPotiValue;
}

void Poti::setLastPotiValue(int p_lastPotiValue) {
    lastPotiValue = p_lastPotiValue;
}

void Poti::__setItsBoard(Board* p_Board) {
    itsBoard = p_Board;
}

void Poti::_setItsBoard(Board* p_Board) {
    __setItsBoard(p_Board);
}

void Poti::_clearItsBoard() {
    itsBoard = NULL;
}

void Poti::rootState_entDef() {
    {
        pushNullTransition();
        rootState_subState = Sample;
        rootState_active = Sample;
        //#[ state Sample.(Entry) 
        sample();
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
                    //## transition 0 
                    if(potiValue != lastPotiValue)
                        {
                            popNullTransition();
                            //#[ transition 0 
                            CGEN( itsBoard, evPotiValue(potiValue));       
                                                                  
                            // Refresh last poti Value
                            lastPotiValue = potiValue;
                            //#]
                            rootState_subState = Hold;
                            rootState_active = Hold;
                            rootState_timeout = scheduleTimeout(sampleInterval, NULL);
                            res = eventConsumed;
                        }
                    else
                        {
                            popNullTransition();
                            rootState_subState = Hold;
                            rootState_active = Hold;
                            rootState_timeout = scheduleTimeout(sampleInterval, NULL);
                            res = eventConsumed;
                        }
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
    return res;
}

/*********************************************************************
	File Path	: MCB1700\Debug\Poti.cpp
*********************************************************************/
