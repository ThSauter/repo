/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: UartReceiver
//!	Generated Date	: Thu, 3, Aug 2017  
	File Path	: MCB1700\Debug\UartReceiver.h
*********************************************************************/

#ifndef UartReceiver_H
#define UartReceiver_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "DefaultPkg.h"
//## auto_generated
#include "WSTModelHeadersTSK.h"
//## class UartReceiver
#include "UartController.h"
//## link itsDisplay
class Display;

//## link itsLed
class Led;

//## link itsLedBar
class LedBar;

//## package DefaultPkg

//## class UartReceiver
class UartReceiver : public WST_TSK, public WST_FSM, public UartController {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    UartReceiver(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~UartReceiver();
    
    ////    Operations    ////
    
    //## operation receiveData()
    void receiveData();
    
    ////    Additional operations    ////
    
    //## auto_generated
    Display* getItsDisplay() const;
    
    //## auto_generated
    void setItsDisplay(Display* p_Display);
    
    //## auto_generated
    Led* getItsLed() const;
    
    //## auto_generated
    void setItsLed(Led* p_Led);
    
    //## auto_generated
    LedBar* getItsLedBar() const;
    
    //## auto_generated
    void setItsLedBar(LedBar* p_LedBar);
    
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
    
    Display* itsDisplay;		//## link itsDisplay
    
    Led* itsLed;		//## link itsLed
    
    LedBar* itsLedBar;		//## link itsLedBar
    
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
    enum UartReceiver_Enum {
        OMNonState = 0,
        state_0 = 1
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    IOxfTimeout* rootState_timeout;
//#]
};

inline bool UartReceiver::rootState_IN() const {
    return true;
}

inline bool UartReceiver::state_0_IN() const {
    return rootState_subState == state_0;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\UartReceiver.h
*********************************************************************/
