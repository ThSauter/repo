/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: TargetComponent 
	Configuration 	: Debug
	Model Element	: LED
//!	Generated Date	: Wed, 3, May 2017  
	File Path	: TargetComponent\Debug\LED.h
*********************************************************************/

#ifndef LED_H
#define LED_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include "rl_net.h"
//## auto_generated
#include "ExamplePkg.h"
//## package ExamplePkg

//## class LED
class LED : public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## operation LED(int)
    LED(int aBitArg, WST_TSK* myTask = 0);
    
    //## auto_generated
    LED(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~LED();
    
    ////    Operations    ////

private :

    //## operation off()
    void off();
    
    //## operation on()
    void on();
    
    ////    Additional operations    ////

public :

    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initStatechart();

private :

    //## auto_generated
    int getBitIndicator() const;
    
    //## auto_generated
    void setBitIndicator(int p_bitIndicator);
    
    ////    Attributes    ////

protected :

    int bitIndicator;		//## attribute bitIndicator
    
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
    
    ////    Framework    ////

protected :

//#[ ignore
    enum LED_Enum {
        OMNonState = 0,
        On = 1,
        Off = 2
    };
    
    int rootState_subState;
    
    int rootState_active;
//#]
};

inline bool LED::rootState_IN() const {
    return true;
}

inline bool LED::On_IN() const {
    return rootState_subState == On;
}

inline bool LED::Off_IN() const {
    return rootState_subState == Off;
}

#endif
/*********************************************************************
	File Path	: TargetComponent\Debug\LED.h
*********************************************************************/
