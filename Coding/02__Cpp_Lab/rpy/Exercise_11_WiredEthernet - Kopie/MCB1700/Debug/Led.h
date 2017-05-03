/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Led
//!	Generated Date	: Mon, 24, Apr 2017  
	File Path	: MCB1700\Debug\Led.h
*********************************************************************/

#ifndef Led_H
#define Led_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include "Default.h"
//## package Default

//## class Led
class Led : public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## operation Led()
    Led(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~Led();
    
    ////    Operations    ////
    
    //## operation off()
    void off();
    
    //## operation on()
    void on();
    
    ////    Additional operations    ////
    
    //## auto_generated
    int getBitNr() const;
    
    //## auto_generated
    void setBitNr(int p_bitNr);
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initStatechart();
    
    ////    Attributes    ////
    
    int bitNr;		//## attribute bitNr
    
    ////    Framework operations    ////

public :

    // rootState:
    //## statechart_method
    inline bool rootState_IN() const;
    
    //## statechart_method
    virtual void rootState_entDef();
    
    //## statechart_method
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // State_on:
    //## statechart_method
    inline bool State_on_IN() const;
    
    // State_off:
    //## statechart_method
    inline bool State_off_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum Led_Enum {
        OMNonState = 0,
        State_on = 1,
        State_off = 2
    };
    
    int rootState_subState;
    
    int rootState_active;
//#]
};

inline bool Led::rootState_IN() const {
    return true;
}

inline bool Led::State_on_IN() const {
    return rootState_subState == State_on;
}

inline bool Led::State_off_IN() const {
    return rootState_subState == State_off;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Led.h
*********************************************************************/
