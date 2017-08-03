/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: UartTransmitter
//!	Generated Date	: Thu, 3, Aug 2017  
	File Path	: MCB1700\Debug\UartTransmitter.h
*********************************************************************/

#ifndef UartTransmitter_H
#define UartTransmitter_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "DefaultPkg.h"
//## auto_generated
#include "WSTModelHeadersTSK.h"
//## class UartTransmitter
#include "UartController.h"
//## link itsLed
class Led;

//## package DefaultPkg

//## class UartTransmitter
class UartTransmitter : public WST_TSK, public WST_FSM, public UartController {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    UartTransmitter(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~UartTransmitter();
    
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
    enum UartTransmitter_Enum {
        OMNonState = 0,
        state_0 = 1
    };
    
    int rootState_subState;
    
    int rootState_active;
//#]
};

inline bool UartTransmitter::rootState_IN() const {
    return true;
}

inline bool UartTransmitter::state_0_IN() const {
    return rootState_subState == state_0;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\UartTransmitter.h
*********************************************************************/
