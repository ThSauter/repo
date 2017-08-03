/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: RunningIndicatorLed
//!	Generated Date	: Thu, 3, Aug 2017  
	File Path	: MCB1700\Debug\RunningIndicatorLed.h
*********************************************************************/

#ifndef RunningIndicatorLed_H
#define RunningIndicatorLed_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "DefaultPkg.h"
//## auto_generated
#include "WSTModelHeadersTSK.h"
//## link itsLed
class Led;

//## package DefaultPkg

//## class RunningIndicatorLed
class RunningIndicatorLed : public WST_TSK, public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    RunningIndicatorLed(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~RunningIndicatorLed();
    
    ////    Additional operations    ////
    
    //## auto_generated
    Led* getItsLed() const;
    
    //## auto_generated
    void setItsLed(Led* p_Led);
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initStatechart();
    
    //## auto_generated
    void cleanUpRelations();
    
    //## auto_generated
    void cancelTimeouts();
    
    //## auto_generated
    virtual bool cancelTimeout(const IOxfTimeout* arg);

public :

    static uint16 ClassWSTMonitor_getTypeSize1();
    
    ////    Relations and components    ////

protected :

    Led* itsLed;		//## link itsLed
    
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
    enum RunningIndicatorLed_Enum {
        OMNonState = 0,
        On = 1,
        Off = 2
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    IOxfTimeout* rootState_timeout;
//#]
};

uint16 WSTMonitor_getTypeSize1();

inline bool RunningIndicatorLed::rootState_IN() const {
    return true;
}

inline bool RunningIndicatorLed::On_IN() const {
    return rootState_subState == On;
}

inline bool RunningIndicatorLed::Off_IN() const {
    return rootState_subState == Off;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\RunningIndicatorLed.h
*********************************************************************/
