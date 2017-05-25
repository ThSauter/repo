/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Display
//!	Generated Date	: Wed, 17, May 2017  
	File Path	: MCB1700\Debug\Display.h
*********************************************************************/

#ifndef Display_H
#define Display_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "DefaultPkg.h"
//## dependency Board_GLCD
//#[ ignore
extern "C"
{
//#]
#include <Board_GLCD.h>
}
//## dependency GLCD_Config
//#[ ignore
extern "C"
{
//#]
#include <GLCD_Config.h>
}
//## link itsEthernetReceiver
class EthernetReceiver;

//## package DefaultPkg

//## class Display
class Display : public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## operation Display()
    Display(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~Display();
    
    ////    Operations    ////
    
    //## operation drawReceivedPosition(char)
    void drawReceivedPosition(char data);
    
    ////    Additional operations    ////
    
    //## auto_generated
    EthernetReceiver* getItsEthernetReceiver() const;
    
    //## auto_generated
    void setItsEthernetReceiver(EthernetReceiver* p_EthernetReceiver);
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initStatechart();
    
    //## auto_generated
    void cleanUpRelations();
    
    ////    Relations and components    ////
    
    EthernetReceiver* itsEthernetReceiver;		//## link itsEthernetReceiver
    
    ////    Framework operations    ////

public :

    //## auto_generated
    void __setItsEthernetReceiver(EthernetReceiver* p_EthernetReceiver);
    
    //## auto_generated
    void _setItsEthernetReceiver(EthernetReceiver* p_EthernetReceiver);
    
    //## auto_generated
    void _clearItsEthernetReceiver();
    
    // rootState:
    //## statechart_method
    inline bool rootState_IN() const;
    
    //## statechart_method
    virtual void rootState_entDef();
    
    //## statechart_method
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // Refresh:
    //## statechart_method
    inline bool Refresh_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum Display_Enum {
        OMNonState = 0,
        Refresh = 1
    };
    
    int rootState_subState;
    
    int rootState_active;
//#]
};

inline bool Display::rootState_IN() const {
    return true;
}

inline bool Display::Refresh_IN() const {
    return rootState_subState == Refresh;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Display.h
*********************************************************************/
