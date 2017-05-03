/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Poti
//!	Generated Date	: Fri, 14, Apr 2017  
	File Path	: MCB1700\Debug\Poti.h
*********************************************************************/

#ifndef Poti_H
#define Poti_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "Default.h"
//## class Poti
#include "PotiSubject.h"
//## auto_generated
class PotiObserver;

//## package Default

//## class Poti
class Poti : public WST_FSM, public PotiSubject {
    ////    Constructors and destructors    ////
    
public :

    //## operation Poti()
    Poti(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~Poti();
    
    ////    Operations    ////
    
    //## operation getAdcValue()
    int getAdcValue();
    
    //## operation samplePoti()
    void samplePoti();
    
    ////    Additional operations    ////
    
    //## auto_generated
    int getPotiVal() const;
    
    //## auto_generated
    void setPotiVal(int p_potiVal);
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initStatechart();
    
    //## auto_generated
    void cancelTimeouts();
    
    //## auto_generated
    virtual bool cancelTimeout(const IOxfTimeout* arg);

private :

    //## auto_generated
    int get_lastPotiVal() const;
    
    //## auto_generated
    void set_lastPotiVal(int p__lastPotiVal);
    
    //## auto_generated
    void setAdcValue(int p_adcValue);
    
    ////    Attributes    ////

protected :

    int _lastPotiVal;		//## attribute _lastPotiVal
    
    int adcValue;		//## attribute adcValue
    
    int potiVal;		//## attribute potiVal
    
    ////    Framework operations    ////

public :

    // rootState:
    //## statechart_method
    inline bool rootState_IN() const;
    
    //## statechart_method
    virtual void rootState_entDef();
    
    //## statechart_method
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // Sample:
    //## statechart_method
    inline bool Sample_IN() const;
    
    // Hold:
    //## statechart_method
    inline bool Hold_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum Poti_Enum {
        OMNonState = 0,
        Sample = 1,
        Hold = 2
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    IOxfTimeout* rootState_timeout;
//#]
};

inline bool Poti::rootState_IN() const {
    return true;
}

inline bool Poti::Sample_IN() const {
    return rootState_subState == Sample;
}

inline bool Poti::Hold_IN() const {
    return rootState_subState == Hold;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Poti.h
*********************************************************************/
