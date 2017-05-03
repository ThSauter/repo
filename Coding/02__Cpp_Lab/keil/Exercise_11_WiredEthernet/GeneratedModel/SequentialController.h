/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: TargetComponent 
	Configuration 	: Debug
	Model Element	: SequentialController
//!	Generated Date	: Wed, 3, May 2017  
	File Path	: TargetComponent\Debug\SequentialController.h
*********************************************************************/

#ifndef SequentialController_H
#define SequentialController_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include "rl_net.h"
//## auto_generated
#include "ExamplePkg.h"
//## auto_generated
#include "WSTModelHeadersTSK.h"
//## link itsLED
class LED;

//## package ExamplePkg

//## class SequentialController
class SequentialController : public WST_TSK, public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    SequentialController(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~SequentialController();
    
    ////    Additional operations    ////
    
    //## auto_generated
    LED* getItsLED() const;
    
    //## auto_generated
    void setItsLED(LED* p_LED);
    
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
    
    ////    Relations and components    ////
    
    LED* itsLED;		//## link itsLED
    
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
    enum SequentialController_Enum {
        OMNonState = 0,
        On = 1,
        Off = 2
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    IOxfTimeout* rootState_timeout;
//#]
};

inline bool SequentialController::rootState_IN() const {
    return true;
}

inline bool SequentialController::On_IN() const {
    return rootState_subState == On;
}

inline bool SequentialController::Off_IN() const {
    return rootState_subState == Off;
}

#endif
/*********************************************************************
	File Path	: TargetComponent\Debug\SequentialController.h
*********************************************************************/
