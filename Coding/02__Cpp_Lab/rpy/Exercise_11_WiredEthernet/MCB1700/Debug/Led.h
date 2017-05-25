/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Led
//!	Generated Date	: Wed, 17, May 2017  
	File Path	: MCB1700\Debug\Led.h
*********************************************************************/

#ifndef Led_H
#define Led_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "DefaultPkg.h"
//## package DefaultPkg

//## class Led
class Led : public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## operation Led(int)
    Led(int aBitArg, WST_TSK* myTask = 0);
    
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
    int getBitIndicator() const;
    
    //## auto_generated
    void setBitIndicator(int p_bitIndicator);
    
    //## auto_generated
    int getBlinkTimeoutMs() const;
    
    //## auto_generated
    void setBlinkTimeoutMs(int p_blinkTimeoutMs);
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initStatechart();
    
    //## auto_generated
    void cancelTimeouts();
    
    //## auto_generated
    virtual bool cancelTimeout(const IOxfTimeout* arg);
    
    ////    Attributes    ////
    
    int bitIndicator;		//## attribute bitIndicator
    
    int blinkTimeoutMs;		//## attribute blinkTimeoutMs
    
    ////    Framework operations    ////

public :

    // rootState:
    //## statechart_method
    inline bool rootState_IN() const;
    
    //## statechart_method
    virtual void rootState_entDef();
    
    //## statechart_method
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // On:
    //## statechart_method
    inline bool On_IN() const;
    
    // Off:
    //## statechart_method
    inline bool Off_IN() const;
    
    // BlinkOn:
    //## statechart_method
    inline bool BlinkOn_IN() const;
    
    // BlinkOff:
    //## statechart_method
    inline bool BlinkOff_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum Led_Enum {
        OMNonState = 0,
        On = 1,
        Off = 2,
        BlinkOn = 3,
        BlinkOff = 4
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    IOxfTimeout* rootState_timeout;
//#]
};

inline bool Led::rootState_IN() const {
    return true;
}

inline bool Led::On_IN() const {
    return rootState_subState == On;
}

inline bool Led::Off_IN() const {
    return rootState_subState == Off;
}

inline bool Led::BlinkOn_IN() const {
    return rootState_subState == BlinkOn;
}

inline bool Led::BlinkOff_IN() const {
    return rootState_subState == BlinkOff;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Led.h
*********************************************************************/
