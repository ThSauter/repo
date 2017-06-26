/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: EthernetReceiver
//!	Generated Date	: Tue, 23, May 2017  
	File Path	: MCB1700\Debug\EthernetReceiver.h
*********************************************************************/

#ifndef EthernetReceiver_H
#define EthernetReceiver_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "DefaultPkg.h"
//## auto_generated
#include "WSTModelHeadersTSK.h"
//## class EthernetReceiver
#include "EthernetController.h"
//## link itsDisplay
class Display;

//## link itsLed
class Led;

//## link itsLedBar
class LedBar;

//## package DefaultPkg

//## class EthernetReceiver
class EthernetReceiver : public WST_TSK, public WST_FSM, public EthernetController {
    ////    Constructors and destructors    ////
    
public :

    //## operation EthernetReceiver()
    EthernetReceiver(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~EthernetReceiver();
    
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

    //## auto_generated
    void __setItsDisplay(Display* p_Display);
    
    //## auto_generated
    void _setItsDisplay(Display* p_Display);
    
    //## auto_generated
    void _clearItsDisplay();
    
    // rootState:
    //## statechart_method
    inline bool rootState_IN() const;
    
    //## statechart_method
    virtual void rootState_entDef();
    
    //## statechart_method
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // Receive:
    //## statechart_method
    inline bool Receive_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum EthernetReceiver_Enum {
        OMNonState = 0,
        Receive = 1
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    IOxfTimeout* rootState_timeout;
//#]
};

inline bool EthernetReceiver::rootState_IN() const {
    return true;
}

inline bool EthernetReceiver::Receive_IN() const {
    return rootState_subState == Receive;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\EthernetReceiver.h
*********************************************************************/
