/*********************************************************************
	Rhapsody	: 8.2 
	Login		: sauter
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: EthernetTransmitter
//!	Generated Date	: Sat, 20, May 2017  
	File Path	: MCB1700/Debug/EthernetTransmitter.h
*********************************************************************/

#ifndef EthernetTransmitter_H
#define EthernetTransmitter_H

//## auto_generated
#include <oxf/oxf.h>
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "DefaultPkg.h"
//## auto_generated
#include <oxf/omthread.h>
//## auto_generated
#include <oxf/omreactive.h>
//## auto_generated
#include <oxf/state.h>
//## auto_generated
#include <oxf/event.h>
//## class EthernetTransmitter
#include "EthernetController.h"
//## link itsLed
class Led;

//## package DefaultPkg

//## class EthernetTransmitter
class EthernetTransmitter : public OMThread, public OMReactive, public EthernetController {
    ////    Constructors and destructors    ////
    
public :

    //## operation EthernetTransmitter()
    EthernetTransmitter(IOxfActive* theActiveContext = 0);
    
    //## auto_generated
    ~EthernetTransmitter();
    
    ////    Operations    ////
    
    //## operation transmitData()
    void transmitData();
    
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
    
    ////    Relations and components    ////
    
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
    
    // state_0:
    //## statechart_method
    inline bool state_0_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum EthernetTransmitter_Enum {
        OMNonState = 0,
        state_0 = 1
    };
    
    int rootState_subState;
    
    int rootState_active;
//#]
};

inline bool EthernetTransmitter::rootState_IN() const {
    return true;
}

inline bool EthernetTransmitter::state_0_IN() const {
    return rootState_subState == state_0;
}

#endif
/*********************************************************************
	File Path	: MCB1700/Debug/EthernetTransmitter.h
*********************************************************************/
